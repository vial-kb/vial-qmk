# 固件修改

    1，注释掉         // if (mouse_report.x || mouse_report.y || mouse_report.v) {
        //     ps2_mouse_moved_user(&mouse_report);
        // }，把ps2_mouse_moved_user(&mouse_report);移到mouse_report.buttons |= tp_buttons;下面
    2，srgb