/******************************************************************************
 Copyright (c) 2017 Flex(Shanghai) Co.,Ltd. 
 All rights reserved.

 [Module Name]:		
 		flex_drv_captouch.h
 [Date]:       
 		2017-12-20
 [Author]:   	
 		carson.qian 
 [Reversion History]:
 		v1.0
*******************************************************************************/
#ifndef _FLEX_DRV_CAPTOUCH_H_
#define _FLEX_DRV_CAPTOUCH_H_

#ifdef __cplusplus 
extern "C" {
#endif

/*========================================================================================================
										I N C L U D E
========================================================================================================*/
#include "flex_common.h"
#include "flex_drv_captouch_def.h"


/*========================================================================================================
										D E F I N E
========================================================================================================*/




/*========================================================================================================
										T Y P E D E F
========================================================================================================*/






/*========================================================================================================
										V A R I A B L E S
========================================================================================================*/







/*========================================================================================================
										F U N C T I O N
========================================================================================================*/
bool Drv_CapTouch_Init(void);

bool Drv_CapTouch_Get_Led(flex_led_name_enum led_name);
void Drv_CapTouch_Set_Led(flex_led_name_enum led_name, bool on);

bool Drv_CapTouch_Support_Polling(void);
void Drv_CapTouch_Polling(void);

void Drv_CapTouch_Set_Callback(fpDrvBtnEvent func_ptr);



/*========================================================================================================
										End
========================================================================================================*/
#ifdef __cplusplus 
}
#endif

#endif//_FLEX_DRV_CAPTOUCH_H_


