# Copyright 2022 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=160,h=128)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(160*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 160
disp_drv.ver_res = 128
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)



# create screen
screen = lv.obj()
screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_main_main_default
style_screen_main_main_default = lv.style_t()
style_screen_main_main_default.init()
style_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_main_default.set_bg_opa(0)

# add style for screen
screen.add_style(style_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_img_1
screen_img_1 = lv.img(screen)
screen_img_1.set_pos(int(-2),int(-1))
screen_img_1.set_size(109,128)
screen_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('E:\\esp31\\TEST3\\generated\\mPythonImages\\mp-287729148.png','rb') as f:
        screen_img_1_img_data = f.read()
except:
    print('Could not open E:\\esp31\\TEST3\\generated\\mPythonImages\\mp-287729148.png')
    sys.exit()

screen_img_1_img = lv.img_dsc_t({
  'data_size': len(screen_img_1_img_data),
  'header': {'always_zero': 0, 'w': 109, 'h': 128, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_img_1_img_data
})

screen_img_1.set_src(screen_img_1_img)
screen_img_1.set_pivot(50,50)
screen_img_1.set_angle(0)
# create style style_screen_img_1_main_main_default
style_screen_img_1_main_main_default = lv.style_t()
style_screen_img_1_main_main_default.init()
style_screen_img_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_img_1_main_main_default.set_img_recolor_opa(0)
style_screen_img_1_main_main_default.set_img_opa(255)

# add style for screen_img_1
screen_img_1.add_style(style_screen_img_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_spangroup_1
screen_spangroup_1 = lv.spangroup(screen)
screen_spangroup_1.set_pos(int(107),int(5))
screen_spangroup_1.set_size(49,122)
screen_spangroup_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_spangroup_1.set_align(lv.TEXT_ALIGN.LEFT)
screen_spangroup_1.set_overflow(lv.SPAN_OVERFLOW.CLIP)
screen_spangroup_1.set_mode(lv.SPAN_MODE.BREAK)
screen_spangroup_1_span = screen_spangroup_1.new_span()
screen_spangroup_1_span.set_text("Man!\nwellcome\nto\nhome!\n")
screen_spangroup_1_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
screen_spangroup_1_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    screen_spangroup_1_span.style.set_text_font(lv.font_Abel_regular_13)
except AttributeError:
    try:
        screen_spangroup_1_span.style.set_text_font(lv.font_montserrat_13)
    except AttributeError:
        screen_spangroup_1_span.style.set_text_font(lv.font_montserrat_16)
screen_spangroup_1.refr_mode()
# create style style_screen_spangroup_1_main_main_default
style_screen_spangroup_1_main_main_default = lv.style_t()
style_screen_spangroup_1_main_main_default.init()
style_screen_spangroup_1_main_main_default.set_radius(0)
style_screen_spangroup_1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_spangroup_1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_spangroup_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_spangroup_1_main_main_default.set_bg_opa(0)
style_screen_spangroup_1_main_main_default.set_border_color(lv.color_make(0x00,0x00,0x00))
style_screen_spangroup_1_main_main_default.set_border_width(0)
style_screen_spangroup_1_main_main_default.set_border_opa(255)
style_screen_spangroup_1_main_main_default.set_pad_left(0)
style_screen_spangroup_1_main_main_default.set_pad_right(0)
style_screen_spangroup_1_main_main_default.set_pad_top(0)
style_screen_spangroup_1_main_main_default.set_pad_bottom(0)

# add style for screen_spangroup_1
screen_spangroup_1.add_style(style_screen_spangroup_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)




# content from custom.py

# Load the default screen
lv.scr_load(screen)

while SDL.check():
    time.sleep_ms(5)
