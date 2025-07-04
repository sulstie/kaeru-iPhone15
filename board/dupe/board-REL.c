//
// SPDX-FileCopyrightText: 2025 Your name <your.email@example.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//

#include <board_ops.h>

#define BUTTON_ACTION 0
#define BUTTON_VOLUME_UP 1
#define BUTTON_VOLUME_DOWN 2
#define BUTTON_POWER 8


void board_late_init(void) {

    //Better bootmode keys!
    if (mtk_detect_key(BUTTON_VOLUME_UP)) {
        set_bootmode(BOOTMODE_RECOVERY);
    } else if (mtk_detect_key(BUTTON_VOLUME_DOWN)) {
        set_bootmode(BOOTMODE_FASTBOOT);
    } else if (mtk_detect_key(BUTTON_ACTION)) {
        set_bootmode(BOOTMODE_FACTORY);
    }

    //Bypass orange state warning
    uint32_t addr = SEARCH_PATTERN(LK_START, LK_END, 0xB508, 0x4B0A, 0x447B);
    if (addr) {
        printf("Found orange_state_warning at 0x%08X\n", addr);
        FORCE_RETURN(addr, 0);
    }

    //Bootmode logging
    show_bootmode(get_bootmode());
    video_printf("\n\n\n");

}
