// SPDX-License-Identifier: GPL-2.0+
/*
 * Raspberry Pi 7" DSI Display Detection Command
 * Detects if the official Raspberry Pi 7" DSI display is connected
 */

#include <command.h>
#include <asm/arch/msg.h>

static int do_rpi_display(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	int width, height;
	int ret;

	printf("=== Raspberry Pi 7\" DSI Display Detection ===\n");

	/* Use official VideoCore mailbox interface to get display resolution */
	ret = bcm2835_get_video_size(&width, &height);
	if (ret) {
		printf("Failed to query VideoCore display size (ret=%d)\n", ret);
		printf("Display Status: NOT DETECTED\n");
		return 2;
	}

	printf("VideoCore reports display: %dx%d", width, height);

	/* Official Raspberry Pi 7" DSI display is 800x480 */
	if (width == 800 && height == 480) {
		printf(" - RASPBERRY PI 7\" DSI DISPLAY DETECTED!\n");
		printf("Display Status: CONNECTED\n");
		return 0;
	}
	/* No resolution could indicate no display */
	else if (width == 0 || height == 0) {
		printf(" - No active display\n");
		printf("Display Status: NOT DETECTED\n");
		return 1;
	}
	else {
		printf(" - Not Raspberry Pi DSI display (resolution %dx%d)\n", width, height);
		printf("Display Status: NOT DETECTED\n");
		return 1;
	}
}

static int do_test_rpi_display(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	int width, height;
	int ret;

	/* Silent test using VideoCore mailbox interface */
	ret = bcm2835_get_video_size(&width, &height);
	if (ret) {
		return 2; /* Failed to query VideoCore */
	}

	/* Check for Raspberry Pi DSI display resolutions */
	if ((width == 800 && height == 480)) {
		return 0; /* DSI display found */
	}

	return 1; /* DSI display not found */
}

U_BOOT_CMD(
	rpidisplay, 1, 1, do_rpi_display,
	"detect Raspberry Pi DSI display",
	"\n"
	"Detects Raspberry Pi 7\" DSI display by checking resolution:\n"
	"  - 800x480 = Official Raspberry Pi 7\" DSI display\n"
	"Returns: 0=connected, 1=not detected, 2=no video"
);

U_BOOT_CMD(
	testrpidisplay, 1, 1, do_test_rpi_display,
	"silent test for Raspberry Pi DSI display",
	"\n"
	"Silent test for Raspberry Pi DSI display (for use in scripts):\n"
	"Returns: 0=connected, 1=not detected, 2=no video\n"
	"Usage: if testrpidisplay; then echo DSI found; fi"
);
