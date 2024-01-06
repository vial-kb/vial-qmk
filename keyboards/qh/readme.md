   platforms/chibios/boards/STM32_F103_STM32DUINO/board/board.c
  //  AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
   AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE;
   
   drivers/ps2/ps2_mouse.c
       ps2_mouse_moved_user(&mouse_report);

   
   srgb
   
   