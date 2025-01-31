/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *img_3;
	bool img_3_del;
	lv_obj_t *img_3_animimg_1;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_img_3(lv_ui *ui);

#include "extra/widgets/animimg/lv_animimg.h"
LV_IMG_DECLARE(img_3_animimg_16420)
LV_IMG_DECLARE(img_3_animimg_11)
LV_IMG_DECLARE(img_3_animimg_111)
LV_IMG_DECLARE(img_3_animimg_144)
LV_IMG_DECLARE(img_3_animimg_14)
LV_IMG_DECLARE(img_3_animimg_1131)
LV_IMG_DECLARE(img_3_animimg_1123123)
LV_IMG_DECLARE(img_3_animimg_112323)

#ifdef __cplusplus
}
#endif
#endif