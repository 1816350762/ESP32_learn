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


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	if (style_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_main_default);
	else
		lv_style_init(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_main_main_default, 0);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_1
	ui->screen_img_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_img_1, -2, -1);
	lv_obj_set_size(ui->screen_img_1, 109, 128);
	lv_obj_set_scrollbar_mode(ui->screen_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_1_main_main_default
	static lv_style_t style_screen_img_1_main_main_default;
	if (style_screen_img_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_img_1_main_main_default);
	else
		lv_style_init(&style_screen_img_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_img_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_img_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_img_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_img_1, &style_screen_img_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_1,&_111_109x128);
	lv_img_set_pivot(ui->screen_img_1, 50,50);
	lv_img_set_angle(ui->screen_img_1, 0);

	//Write codes screen_spangroup_1
	ui->screen_spangroup_1 = lv_spangroup_create(ui->screen);
	lv_obj_set_pos(ui->screen_spangroup_1, 107, 5);
	lv_obj_set_size(ui->screen_spangroup_1, 49, 122);
	lv_obj_set_scrollbar_mode(ui->screen_spangroup_1, LV_SCROLLBAR_MODE_OFF);
	lv_spangroup_set_align(ui->screen_spangroup_1, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_spangroup_1, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_spangroup_1, LV_SPAN_MODE_BREAK);

	//Write style state: LV_STATE_DEFAULT for style_screen_spangroup_1_main_main_default
	static lv_style_t style_screen_spangroup_1_main_main_default;
	if (style_screen_spangroup_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_spangroup_1_main_main_default);
	else
		lv_style_init(&style_screen_spangroup_1_main_main_default);
	lv_style_set_radius(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_spangroup_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_spangroup_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_spangroup_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_spangroup_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_spangroup_1_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_border_color(&style_screen_spangroup_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_spangroup_1_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_spangroup_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_spangroup_1, &style_screen_spangroup_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//create spans
	lv_span_t *screen_spangroup_1_span;

	//create a new span
	screen_spangroup_1_span = lv_spangroup_new_span(ui->screen_spangroup_1);
	lv_span_set_text(screen_spangroup_1_span, "Man!\nwellcome\nto\nhome!\n");
	lv_style_set_text_color(&screen_spangroup_1_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&screen_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_1_span->style, &lv_font_Abel_regular_13);
	lv_spangroup_refr_mode(ui->screen_spangroup_1);
}