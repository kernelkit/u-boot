# SPDX-License-Identifier:      GPL-2.0+
#
# Copyright (c) 2023 Addiva Elektronik
# Author: Tobias Waldekranz <tobias@waldekranz.com>

""" Unit test for blkmap command
"""

import pytest

BLKSZ = 0x200

MAPPING = [
    ((0, 1), 3),
    ((1, 3), 0),
    ((4, 2), 6),
    ((6, 2), 4),
]

ORDERED   = 0x0000
UNORDERED = 0x1000
BUFFER    = 0x2000

def mkblob(base, mapping):
    cmds = []

    for ((blksrc, blkcnt), blkdst) in mapping:
        for blknr in range(blkcnt):
            cmds.append(f"mw.b 0x{base + (blkdst + blknr) * BLKSZ:x}" +
                        f" 0x{blksrc + blknr:x} 0x{BLKSZ:x}")
    return cmds

class Blkmap(object):
    def __init__(self, console, num):
        self.console, self.num = console, num

    def __enter__(self):
        r = self.console.run_command(f"blkmap create {self.num}")
        assert(f"Created device {self.num}" in r)

        r = self.console.run_command(f"blkmap dev {self.num}")
        assert("is now current device" in r)

        return self

    def __exit__(self, typ, value, traceback):
        r = self.console.run_command(f"blkmap destroy {self.num}")
        assert(f"Destroyed device {self.num}" in r)

    def map_mem(self, blknr, blkcnt, addr):
        r = self.console.run_command(
            f"blkmap map {self.num} {blknr:#x} {blkcnt:#x} mem {addr:#x}"
        )
        assert(" mapped to " in r)

    def read(self, addr, blknr, blkcnt):
        r = self.console.run_command(
            f"blkmap read {addr:#x} {blknr:#x} {blkcnt:#x}"
        )
        assert(" OK" in r)

    def write(self, addr, blknr, blkcnt):
        r = self.console.run_command(
            f"blkmap write {addr:#x} {blknr:#x} {blkcnt:#x}"
        )
        assert(" OK" in r)

@pytest.mark.boardspec('sandbox')
@pytest.mark.buildconfigspec('cmd_blkmap')
def test_blkmap_creation(u_boot_console):
    """ Verify that blkmaps can be created and destroyed

    Args:
        u_boot_console -- U-Boot console
    """
    with Blkmap(u_boot_console, 0):
        # Can't have 2 blkmap 0's
        with pytest.raises(AssertionError):
            with Blkmap(u_boot_console, 0):
                pass

        # But blkmap 1 should be fine
        with Blkmap(u_boot_console, 1):
            pass

    # Once blkmap 0 is destroyed, we should be able to create it again
    with Blkmap(u_boot_console, 0):
        pass

@pytest.mark.boardspec('sandbox')
@pytest.mark.buildconfigspec('cmd_blkmap')
def test_blkmap_slicing(u_boot_console):
    """ Verify that slices aren't allowed to overlap

    Args:
        u_boot_console -- U-Boot console
    """
    with Blkmap(u_boot_console, 0) as bm:
        bm.map_mem(8, 8, 0)

        # Can't overlap on the low end
        with pytest.raises(AssertionError):
            bm.map_mem(4, 5, 0)

        # Can't be inside
        with pytest.raises(AssertionError):
            bm.map_mem(10, 2, 0)

        # Can't overlap on the high end
        with pytest.raises(AssertionError):
            bm.map_mem(15, 4, 0)

        # But we should be able to add slices right before and after
        bm.map_mem( 4, 4, 0)
        bm.map_mem(16, 4, 0)

@pytest.mark.boardspec('sandbox')
@pytest.mark.buildconfigspec('cmd_blkmap')
def test_blkmap_mem_read(u_boot_console):
    """ Test reading from a memory backed blkmap

    Args:
        u_boot_console -- U-Boot console
    """

    # Generate an ordered and an unordered pattern in memory
    u_boot_console.run_command_list(mkblob(ORDERED, (((0, 8), 0),)))
    u_boot_console.run_command_list(mkblob(UNORDERED, MAPPING))

    with Blkmap(u_boot_console, 0) as bm:
        # Create a blkmap that cancels out the disorder
        for ((blksrc, blkcnt), blkdst) in MAPPING:
            bm.map_mem(blksrc, blkcnt, UNORDERED + blkdst * BLKSZ)

        # Read out the data via the blkmap device to another area
        bm.read(BUFFER, 0, 8)

    # And verify that it matches the ordered pattern
    response = u_boot_console.run_command(f"cmp.b 0x{BUFFER:x} 0x{ORDERED:x} 0x1000")
    assert("Total of 4096 byte(s) were the same" in response)

@pytest.mark.boardspec('sandbox')
@pytest.mark.buildconfigspec('cmd_blkmap')
def test_blkmap_mem_write(u_boot_console):
    """ Test writing to a memory backed blkmap

    Args:
        u_boot_console -- U-Boot console
    """
    # Generate an ordered and an unordered pattern in memory
    u_boot_console.run_command_list(mkblob(ORDERED, (((0, 8), 0),)))
    u_boot_console.run_command_list(mkblob(UNORDERED, MAPPING))

    with Blkmap(u_boot_console, 0) as bm:
        # Create a blkmap that mimics the disorder
        for ((blksrc, blkcnt), blkdst) in MAPPING:
            bm.map_mem(blksrc, blkcnt, BUFFER + blkdst * BLKSZ)

        # Write the ordered data via the blkmap device to another area
        bm.write(ORDERED, 0, 8)

    # And verify that the result matches the unordered pattern
    response = u_boot_console.run_command(f"cmp.b 0x{BUFFER:x} 0x{UNORDERED:x} 0x1000")
    assert("Total of 4096 byte(s) were the same" in response)
