// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2023 Addiva Elektronik
 * Author: Tobias Waldekranz <tobias@waldekranz.com>
 */

#include <blk.h>
#include <blkmap.h>
#include <common.h>
#include <command.h>
#include <malloc.h>

static int blkmap_curr_dev;

struct map_ctx {
	int devnum;
	lbaint_t blknr, blkcnt;
};

typedef int (*map_parser_fn)(struct map_ctx *ctx, int argc, char *const argv[]);

struct map_handler {
	const char *name;
	map_parser_fn fn;
};


int do_blkmap_map_linear(struct map_ctx *ctx, int argc, char *const argv[])
{
	struct blk_desc *lbd;
	int err, ldevnum;
	lbaint_t lblknr;

	if (argc < 4)
		return CMD_RET_USAGE;

	ldevnum = dectoul(argv[2], NULL);
	lblknr = dectoul(argv[3], NULL);

	lbd = blk_get_devnum_by_uclass_idname(argv[1], ldevnum);
	if (!lbd) {
		printf("Found no device matching \"%s %d\"\n",
		       argv[1], ldevnum);
		return CMD_RET_FAILURE;
	}

	err = blkmap_map_linear(ctx->devnum, ctx->blknr, ctx->blkcnt,
				lbd->uclass_id, ldevnum, lblknr);
	if (err) {
		printf("Unable to map \"%s %d\" at block 0x"LBAF": %d\n",
		       argv[1], ldevnum, ctx->blknr, err);

		return CMD_RET_FAILURE;
	}

	printf("Block 0x"LBAF"+0x"LBAF" mapped to block 0x"LBAF" of \"%s %d\"\n",
	       ctx->blknr, ctx->blkcnt, lblknr, argv[1], ldevnum);
	return CMD_RET_SUCCESS;
}

int do_blkmap_map_mem(struct map_ctx *ctx, int argc, char *const argv[])
{
	phys_addr_t addr;
	int err;

	if (argc < 2)
		return CMD_RET_USAGE;

	addr = hextoul(argv[1], NULL);

	err = blkmap_map_pmem(ctx->devnum, ctx->blknr, ctx->blkcnt, addr);
	if (err) {
		printf("Unable to map %#llx at block 0x"LBAF": %d\n",
		       (unsigned long long)addr, ctx->blknr, err);
		return CMD_RET_FAILURE;
	}

	printf("Block 0x"LBAF"+0x"LBAF" mapped to %#llx\n",
	       ctx->blknr, ctx->blkcnt, (unsigned long long)addr);
	return CMD_RET_SUCCESS;
}

struct map_handler map_handlers[] = {
	{ .name = "linear", .fn = do_blkmap_map_linear },
	{ .name = "mem", .fn = do_blkmap_map_mem },

	{ .name = NULL }
};

static int do_blkmap_map(struct cmd_tbl *cmdtp, int flag,
			    int argc, char *const argv[])
{
	struct map_handler *handler;
	struct map_ctx ctx;

	if (argc < 5)
		return CMD_RET_USAGE;

	ctx.devnum = dectoul(argv[1], NULL);
	ctx.blknr = hextoul(argv[2], NULL);
	ctx.blkcnt = hextoul(argv[3], NULL);
	argc -= 4;
	argv += 4;

	for (handler = map_handlers; handler->name; handler++) {
		if (!strcmp(handler->name, argv[0]))
			return handler->fn(&ctx, argc, argv);
	}

	printf("Unknown map type \"%s\"\n", argv[0]);
	return CMD_RET_USAGE;
}

static int do_blkmap_create(struct cmd_tbl *cmdtp, int flag,
			    int argc, char *const argv[])
{
	int devnum = -1;

	if (argc == 2)
		devnum = dectoul(argv[1], NULL);

	devnum = blkmap_create(devnum);
	if (devnum < 0) {
		printf("Unable to create device: %d\n", devnum);
		return CMD_RET_FAILURE;
	}

	printf("Created device %d\n", devnum);
	return CMD_RET_SUCCESS;
}

static int do_blkmap_destroy(struct cmd_tbl *cmdtp, int flag,
			    int argc, char *const argv[])
{
	int err, devnum;

	if (argc != 2)
		return CMD_RET_USAGE;

	devnum = dectoul(argv[1], NULL);

	err = blkmap_destroy(devnum);
	if (err) {
		printf("Unable to destroy device %d: %d\n", devnum, err);
		return CMD_RET_FAILURE;
	}

	printf("Destroyed device %d\n", devnum);
	return CMD_RET_SUCCESS;
}

static int do_blkmap_common(struct cmd_tbl *cmdtp, int flag,
			    int argc, char *const argv[])
{
	/* The subcommand parsing pops the original argv[0] ("blkmap")
	 * which blk_common_cmd expects. Push it back again.
	 */
	argc++;
	argv--;

	return blk_common_cmd(argc, argv, UCLASS_BLKMAP, &blkmap_curr_dev);
}

U_BOOT_CMD_WITH_SUBCMDS(
	blkmap, "Composeable virtual block devices",
	"info - list configured devices\n"
	"blkmap part - list available partitions on current blkmap device\n"
	"blkmap dev [<dev>] - show or set current blkmap device\n"
	"blkmap read <addr> <blk#> <cnt>\n"
	"blkmap write <addr> <blk#> <cnt>\n"
	"blkmap create [<dev>] - create device\n"
	"blkmap destroy <dev> - destroy device\n"
	"blkmap map <dev> <blk#> <cnt> linear <interface> <dev> <blk#> - device mapping\n"
	"blkmap map <dev> <blk#> <cnt> mem <addr> - memory mapping\n",
	U_BOOT_SUBCMD_MKENT(info, 2, 1, do_blkmap_common),
	U_BOOT_SUBCMD_MKENT(part, 2, 1, do_blkmap_common),
	U_BOOT_SUBCMD_MKENT(dev, 4, 1, do_blkmap_common),
	U_BOOT_SUBCMD_MKENT(read, 5, 1, do_blkmap_common),
	U_BOOT_SUBCMD_MKENT(write, 5, 1, do_blkmap_common),
	U_BOOT_SUBCMD_MKENT(create, 2, 1, do_blkmap_create),
	U_BOOT_SUBCMD_MKENT(destroy, 2, 1, do_blkmap_destroy),
	U_BOOT_SUBCMD_MKENT(map, 32, 1, do_blkmap_map));
