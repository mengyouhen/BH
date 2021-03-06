/******************************************************************************
 Copyright (c) 2017 Flex(Shanghai) Co.,Ltd. 
 All rights reserved.

 [Module Name]:		
 		flex_app_osd_menu.h
 [Date]:       
 		2018-06-17
 [Author]:   	
 		carson.qian 
 [Reversion History]:
 		v1.0
*******************************************************************************/
#ifndef _FLEX_APP_OSD_MENU_H_
#define _FLEX_APP_OSD_MENU_H_

#ifdef __cplusplus 
extern "C" {
#endif


/*========================================================================================================
										I N C L U D E
========================================================================================================*/
#include "flex_common.h"
#include "flex_app_osd_def.h"
#include "flex_app_osd_global.h"



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
uint8_t Osd_Menu_Get_First_Item_Index(OSD_PAGE_ENUM PageIdx);
uint8_t Osd_Menu_Get_Next_Item_Index(OSD_MIA_ENUM Action);
uint8_t Osd_Menu_Get_ParentMenu_Index(uint8_t ParentMenuIdx, uint8_t SonMenuIdx);

void Osd_Menu_Draw_Page(OSD_PAGE_ENUM PageIdx, uint8_t SelItemIdx);
void Osd_Menu_Draw_Item(OSD_PAGE_ENUM PageIdx, uint8_t ItemIdx, bool bSelect);
void Osd_Menu_Draw_Content(OSD_PAGE_ENUM PageIdx, uint8_t ItemIdx, bool bSelect);



/*========================================================================================================
										End
========================================================================================================*/
#ifdef __cplusplus 
}
#endif

#endif//_FLEX_APP_OSD_MENU_H_


