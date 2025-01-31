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



# create img_3
img_3 = lv.obj()
img_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
img_3.update_layout()


# create style style_img_3_main_main_default
style_img_3_main_main_default = lv.style_t()
style_img_3_main_main_default.init()
style_img_3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_img_3_main_main_default.set_img_recolor_opa(0)
style_img_3_main_main_default.set_img_opa(255)

# add style for img_3
img_3.add_style(style_img_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create img_3_animimg_1
img_3_animimg_1 = lv.animimg(img_3)
img_3_animimg_1.set_pos(int(0),int(0))
img_3_animimg_1.set_size(160,127)
img_3_animimg_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
img_3_animimg_1_animimgs = [None]*8
try:
    with open('E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp1693952080.png','rb') as f:
        img_3_animimg_1_animimg_data_0 = f.read()
except:
    print('Could not open E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp1693952080.png')
    sys.exit()

img_3_animimg_1_animimgs[0] = lv.img_dsc_t({
  'data_size': len(img_3_animimg_1_animimg_data_0),
  'header': {'always_zero': 0, 'w': 160, 'h': 127, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': img_3_animimg_1_animimg_data_0
})
try:
    with open('E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp1343881927.png','rb') as f:
        img_3_animimg_1_animimg_data_1 = f.read()
except:
    print('Could not open E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp1343881927.png')
    sys.exit()

img_3_animimg_1_animimgs[1] = lv.img_dsc_t({
  'data_size': len(img_3_animimg_1_animimg_data_1),
  'header': {'always_zero': 0, 'w': 160, 'h': 127, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': img_3_animimg_1_animimg_data_1
})
try:
    with open('E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp-218539596.png','rb') as f:
        img_3_animimg_1_animimg_data_2 = f.read()
except:
    print('Could not open E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp-218539596.png')
    sys.exit()

img_3_animimg_1_animimgs[2] = lv.img_dsc_t({
  'data_size': len(img_3_animimg_1_animimg_data_2),
  'header': {'always_zero': 0, 'w': 160, 'h': 127, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': img_3_animimg_1_animimg_data_2
})
try:
    with open('E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp-1522453996.png','rb') as f:
        img_3_animimg_1_animimg_data_3 = f.read()
except:
    print('Could not open E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp-1522453996.png')
    sys.exit()

img_3_animimg_1_animimgs[3] = lv.img_dsc_t({
  'data_size': len(img_3_animimg_1_animimg_data_3),
  'header': {'always_zero': 0, 'w': 160, 'h': 127, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': img_3_animimg_1_animimg_data_3
})
try:
    with open('E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp1571570058.png','rb') as f:
        img_3_animimg_1_animimg_data_4 = f.read()
except:
    print('Could not open E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp1571570058.png')
    sys.exit()

img_3_animimg_1_animimgs[4] = lv.img_dsc_t({
  'data_size': len(img_3_animimg_1_animimg_data_4),
  'header': {'always_zero': 0, 'w': 160, 'h': 127, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': img_3_animimg_1_animimg_data_4
})
try:
    with open('E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp1864932389.png','rb') as f:
        img_3_animimg_1_animimg_data_5 = f.read()
except:
    print('Could not open E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp1864932389.png')
    sys.exit()

img_3_animimg_1_animimgs[5] = lv.img_dsc_t({
  'data_size': len(img_3_animimg_1_animimg_data_5),
  'header': {'always_zero': 0, 'w': 160, 'h': 127, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': img_3_animimg_1_animimg_data_5
})
try:
    with open('E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp-1995061548.png','rb') as f:
        img_3_animimg_1_animimg_data_6 = f.read()
except:
    print('Could not open E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp-1995061548.png')
    sys.exit()

img_3_animimg_1_animimgs[6] = lv.img_dsc_t({
  'data_size': len(img_3_animimg_1_animimg_data_6),
  'header': {'always_zero': 0, 'w': 160, 'h': 127, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': img_3_animimg_1_animimg_data_6
})
try:
    with open('E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp-1277352311.png','rb') as f:
        img_3_animimg_1_animimg_data_7 = f.read()
except:
    print('Could not open E:\\esp31\\lvgl23\\generated\\mPythonImages\\mp-1277352311.png')
    sys.exit()

img_3_animimg_1_animimgs[7] = lv.img_dsc_t({
  'data_size': len(img_3_animimg_1_animimg_data_7),
  'header': {'always_zero': 0, 'w': 160, 'h': 127, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': img_3_animimg_1_animimg_data_7
})

img_3_animimg_1.set_src(img_3_animimg_1_animimgs, 8)
img_3_animimg_1.set_duration(1000 * 8)
img_3_animimg_1.set_repeat_count(3000)
img_3_animimg_1.start()



# content from custom.py

# Load the default screen
lv.scr_load(img_3)

while SDL.check():
    time.sleep_ms(5)
