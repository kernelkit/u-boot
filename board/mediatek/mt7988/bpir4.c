// SPDX-License-Identifier: GPL-2.0
/*
 * BPI-R4 / BPI-R4-2g5 board variant detection
 */

#include <image.h>
#include <linux/string.h>

enum bpir4_variant {
	BPIR4,
	BPIR4_2G5,
};

/*
 * Detect which BPI-R4 variant this board is.
 * TODO: implement real hardware detection
 */
static enum bpir4_variant detect_bpir4_variant(void)
{
	/* Stub: always report BPI-R4 */
	return BPIR4;
}

int board_fit_config_name_match(const char *name)
{
	switch (detect_bpir4_variant()) {
	case BPIR4_2G5:
		return strcmp(name, "mt7988a-bananapi-bpi-r4-2g5") ? -1 : 0;
	case BPIR4:
	default:
		return strcmp(name, "mt7988a-bananapi-bpi-r4") ? -1 : 0;
	}
}
