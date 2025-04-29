.. SPDX-License-Identifier: GPL-2.0-or-later

U-Boot for Vest i.MX8M Plus Dev Kit
===================================

The VEST i.MX8M Plus Dev Kit consists of a carrier board and a SOM (of
SO-DIMM type, not SMARC).  In many regards the board and SOM are very
similar to the NXP i.MX8MP EVK, hence the similarities in this doc.

- https://www.apc-vest.com/wp-content/Documents/User%20Manual/VEST/VEST%20i.MX8M%20Plus%20Carrier%20Board%20Hardware%20Reference%20Manual%20Rev%20C%20(20240301).pdf
- https://www.apc-vest.com/wp-content/Documents/User%20Manual/VEST/i.MX8M%20Plus%20SOM%20Board%20Hardware%20Reference%20Manual%20Rev%20C%20(20240229).pdf

Quick Start
-----------

- Build the ARM Trusted firmware binary
- Get the firmware-imx package
- Build U-Boot
- Boot

Get and Build the ARM Trusted firmware
--------------------------------------

Get ATF from <https://github.com/ARM-software/arm-trusted-firmware>,
use tag v2.12 or later.

.. code-block:: bash

   $ cd arm-trusted-firmware/
   $ cp ../arm-trusted-firmware/build/imx8mp/release/bl31.bin $(builddir)
   $ make PLAT=imx8mp bl31

Get the DDR firmware
--------------------

.. code-block:: bash

   $ wget https://www.nxp.com/lgfiles/NMG/MAD/YOCTO/firmware-imx-8.26.bin
   $ chmod +x firmware-imx-8.26.bin
   $ ./firmware-imx-8.26.bin

Build U-Boot
------------

.. code-block:: bash

Note: builddir is U-Boot build directory (source directory for in-tree builds).

   $ export CROSS_COMPILE=aarch64-poky-linux-
   $ make O=build imx8mp_vest_e2i_plus_defconfig 
   $ cp ../arm-trusted-firmware/build/imx8mp/release/bl31.bin $(builddir)
   $ cp ../firmware-imx-8.26/firmware/ddr/synopsys/lpddr4*.bin $(builddir)
   $ make

Burn the flash.bin to the MicroSD card at offset 32KB:

.. code-block:: bash

   $ sudo dd if=flash.bin of=/dev/sd[x] bs=1K seek=32 conv=notrunc; sync

Boot
----

Set SW1 (on the SOM) to boot from SD card: 0011

+------------+------+
| Boot Media |  SW1 |
+------------+------+
| Fuse       | 0000 |
| Serial     | 0001 |
| eMMC       | 0010 |
| SD card    | 0011 |
+------------+------+

Connect the USB-to-serial connector to CN21 (CN22 is the the Cortex-M
console), speed 115200 8N1.  The pinout of both connectors are:

.. code-block:: none

     v
    1 2 3 4 5 6   CN21 (UART1)
    G N N R T N
    N C C x x C
    D     D D

     v
    1 2 3 4 5 6   CN22 (UART2)
    G N N R T N
    N C C x x C
    D     D D

Use an `FTDI TTL-232R-RPi
<https://ftdichip.com/wp-content/uploads/2020/07/DS_TTL-232R_RPi.pdf>`_,
for instance, to connect:

- Connect the black GND to pin 1 (on CN21)
- Connect the orange TxD to pin 4 (RxD on CN21)
- Connect the yellow RxD to pin 5 (TxD on CN21)
