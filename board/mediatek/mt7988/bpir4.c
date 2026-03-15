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
 *
 * Unlike BPI-R3 vs R3-Mini, the R4-2g5 uses the MT7988A's internal 2.5G
 * PHY (always present in SoC silicon at MDIO addr 15) rather than an
 * external EN8811H, so MDIO probing cannot distinguish the variants.
 *
 * TODO: read variant ID from the 24C02 EEPROM on I2C2/PCA9545 ch0 (addr
 * 0x57) once BananaPi's board-ID byte offset/format is known.
 */
static enum bpir4_variant detect_bpir4_variant(void)
{
	/* Stub: always report standard BPI-R4 */
	return BPIR4;
}

int board_fit_config_name_match(const char *name)
{
	static int variant = -1;

	if (variant < 0)
		variant = detect_bpir4_variant();

	switch (variant) {
	case BPIR4_2G5:
		return strcmp(name, "mt7988a-bananapi-bpi-r4-2g5") ? -1 : 0;
	case BPIR4:
	default:
		if (!strcmp(name, "mt7988a-bananapi-bpi-r4") ||
		    !strcmp(name, "mt7988a-bananapi-bpi-r4-sd"))
			return 0;
		return -1;
	}
}

