/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

static const lv_img_dsc_t* img_3_animimg_1_imgs[8] = {
	&img_3_animimg_16420,
	&img_3_animimg_11,
	&img_3_animimg_111,
	&img_3_animimg_144,
	&img_3_animimg_14,
	&img_3_animimg_1131,
	&img_3_animimg_1123123,
	&img_3_animimg_112323
};

void setup_scr_img_3(lv_ui *ui){

	//Write codes img_3
	ui->img_3 = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->img_3, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_img_3_main_main_default
	static lv_style_t style_img_3_main_main_default;
	if (style_img_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_img_3_main_main_default);
	else
		lv_style_init(&style_img_3_main_main_default);
	lv_style_set_img_recolor(&style_img_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_img_3_main_main_default, 0);
	lv_style_set_img_opa(&style_img_3_main_main_default, 255);
	lv_obj_add_style(ui->img_3, &style_img_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update pos for widget img_3
	lv_obj_update_layout(ui->img_3);

	//Write codes img_3_animimg_1
	ui->img_3_animimg_1 = lv_animimg_create(ui->img_3);
	lv_obj_set_pos(ui->img_3_animimg_1, 0, 0);
	lv_obj_set_size(ui->img_3_animimg_1, 160, 127);
	lv_obj_set_scrollbar_mode(ui->img_3_animimg_1, LV_SCROLLBAR_MODE_OFF);
	lv_animimg_set_src(ui->img_3_animimg_1, (const void **) img_3_animimg_1_imgs, 8);
	lv_animimg_set_duration(ui->img_3_animimg_1, 8000);
	lv_animimg_t* img_3_animimg_1_ext = (lv_animimg_t *)ui->img_3_animimg_1;
	lv_animimg_set_repeat_count(ui->img_3_animimg_1, 3000);
	lv_animimg_start(ui->img_3_animimg_1);
}