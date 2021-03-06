/******************************************************************************
 Copyright (c) 2017 Flex(Shanghai) Co.,Ltd. 
 All rights reserved.

 [Module Name]:		
 		flex_trace.h
 [Date]:       
 		2017-12-20
 [Author]:   	
 		carson.qian 
 [Reversion History]:
 		v1.0
*******************************************************************************/
#ifndef _FLEX_TRACE_H_
#define _FLEX_TRACE_H_

#ifdef __cplusplus 
extern "C" {
#endif

/*========================================================================================================
										I N C L U D E
========================================================================================================*/
// ST
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_conf.h"

// FLEX
#include "flex_project_config.h"

/*========================================================================================================
										D E F I N E
========================================================================================================*/
//#define __FLEX_TRACE_ENABLE__     

#if defined(HAL_UART_MODULE_ENABLED)
#define DBG_MSG(arg...)   	printf(arg)
#else 
#define DBG_MSG(fmt, arg...)
#endif




/*========================================================================================================
										T Y P E D E F
========================================================================================================*/






/*========================================================================================================
										V A R I A B L E S
========================================================================================================*/






/*========================================================================================================
										F U N C T I O N
========================================================================================================*/





/*========================================================================================================
										End
========================================================================================================*/
#ifdef __cplusplus 
}
#endif

#endif//_FLEX_TRACE_H_

