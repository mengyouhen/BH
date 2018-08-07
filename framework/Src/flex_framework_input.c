/******************************************************************************
 Copyright (c) 2017 Flex(Shanghai) Co.,Ltd. 
 All rights reserved.

 [Module Name]:		
 		flex_framework_input.c
 [Date]:       
 		2018-06-13
 [Author]:   	
 		carson.qian 
 [Reversion History]:
 		v1.0
*******************************************************************************/

/*========================================================================================================
										I N C L U D E
========================================================================================================*/
// external
#include "flex_app_blotter_menu.h"
// internal
#include "flex_framework_input.h"

/*========================================================================================================
										D E B U G
========================================================================================================*/
#ifndef MOD_NAME
#define MOD_NAME								"[INPUT]--"
#endif

#if defined(__FLEX_TRACE_ENABLE__)
#define TRACE_F(fmt, arg...)				DBG_MSG(MOD_NAME "[F]--%s.\r\n", __func__)
#define TRACE_I(fmt, arg...)				DBG_MSG(MOD_NAME "[I]--" fmt, ##arg)
#define TRACE_W(fmt, arg...)				DBG_MSG(MOD_NAME "[W]--" fmt, ##arg)
#else
#define TRACE_F()										//do{}while(0)
#define TRACE_I(fmt, arg...)				//do{}while(0)	
#define TRACE_W(fmt, arg...)				//do{}while(0)	
#endif
#define TRACE_E(fmt, arg...)				DBG_MSG(MOD_NAME "[E]--" fmt, ##arg)

//========================================
// DEBUG
//========================================
#if defined(__FLEX_TRACE_ENABLE__)
#define DEBUG_TRACE				
#endif

/*========================================================================================================
										E X T E R N 
========================================================================================================*/







/*========================================================================================================
										D E F I N E
========================================================================================================*/








/*========================================================================================================
										T Y P E D E F
========================================================================================================*/
//========================================
// BUTTON 
//========================================
typedef struct
{
	DRV_BTN_ENUM nButton;
	FRM_KEY_ENUM nKey;
}BTN2KEY_ST;



typedef struct _KEY_CB_NODE_ST_   
{
	fpFrmInputKeyCallback pCallback;
	struct _KEY_CB_NODE_ST_  *next;
}KEY_CB_NODE_ST;


//========================================
// TOUCH 
//========================================




/*========================================================================================================
										V A R I A B L E S
========================================================================================================*/
static osMessageQId g_QueueId_Input = NULL;

//========================================
// BUTTON 
//========================================
static KEY_CB_NODE_ST* g_input_key_cb_chain_pHead=NULL;  // for app use
static KEY_CB_NODE_ST* g_input_key_cb_chain_pTail=NULL;  // for app use
static DRV_BTN_INFO_ST g_input_BtnInfo={.nBtn=LIST_BTN_NONE, .nAct=LIST_BTN_ACT_RELEASE};


static const BTN2KEY_ST button_key_map[]=
{
	{ LIST_BTN_NONE,       LIST_KEY_INVALID},
//-----------------------------------
	{ LIST_BTN_0,          LIST_KEY_0},
	{ LIST_BTN_1,          LIST_KEY_1},
	{ LIST_BTN_2,          LIST_KEY_2},
	{ LIST_BTN_3,          LIST_KEY_3},
	{ LIST_BTN_4,          LIST_KEY_4},
	{ LIST_BTN_5,          LIST_KEY_5},
	{ LIST_BTN_6,          LIST_KEY_6},
	{ LIST_BTN_7,          LIST_KEY_7},
	{ LIST_BTN_8,          LIST_KEY_8},
	{ LIST_BTN_9,          LIST_KEY_9},
	{ LIST_BTN_OK,         LIST_KEY_OK},
	{ LIST_BTN_DEL,        LIST_KEY_DEL},
//-----------------------------------
	{ LIST_BTN_UP,         LIST_KEY_UP},
	{ LIST_BTN_DOWN,       LIST_KEY_DOWN},
	{ LIST_BTN_LEFT,       LIST_KEY_LEFT},
	{ LIST_BTN_RIGHT,      LIST_KEY_RIGHT},
//-----------------------------------
	{ LIST_BTN_GEAR_1,     LIST_KEY_GEAR_1},
	{ LIST_BTN_GEAR_2,     LIST_KEY_GEAR_2},
	{ LIST_BTN_GEAR_3,     LIST_KEY_GEAR_3},
	{ LIST_BTN_GEAR_4,     LIST_KEY_GEAR_4},
	{ LIST_BTN_GEAR_5,     LIST_KEY_GEAR_5},
	{ LIST_BTN_GEAR_6,     LIST_KEY_GEAR_6},
	{ LIST_BTN_GEAR_7,     LIST_KEY_GEAR_7},
	{ LIST_BTN_GEAR_8,     LIST_KEY_GEAR_8},
//-----------------------------------
	{ LIST_BTN_WIFI,       LIST_KEY_WIFI},
	{ LIST_BTN_BT,         LIST_KEY_BT},
//-----------------------------------
	{ LIST_BTN_PLAY,       LIST_KEY_PLAY},
	{ LIST_BTN_PAUSE,      LIST_KEY_PAUSE},
//-----------------------------------
	{ LIST_BTN_PAGE_UP,    LIST_KEY_PAGE_UP},
	{ LIST_BTN_PAGE_DOWN,  LIST_KEY_PAGE_DOWN},
//-----------------------------------
	{ LIST_BTN_INC,        LIST_KEY_INC},
	{ LIST_BTN_DEC,        LIST_KEY_DEC},
//-----------------------------------
	{ LIST_BTN_MAX,        LIST_KEY_MAX}
};

//========================================
// TOUCH 
//========================================






/*========================================================================================================
										F U N C T I O N----local
========================================================================================================*/
//========================================
// BUTTON 
//========================================
//---------------------
static FRM_KEY_ENUM Frm_Input_Button_To_Key(DRV_BTN_ENUM button)
{	
	DRV_BTN_ENUM index;
	FRM_KEY_ENUM ret;
	
	for(index=LIST_BTN_NONE; index<LIST_BTN_MAX; index++)
	{
		if(button == button_key_map[index].nButton)
		{
			ret= button_key_map[index].nKey;
			break;
		}
	}
	return ret;
}

static void Frm_Input_Button_Parse(DRV_BTN_INFO_ST btn_info)
{
	FRM_INPUT_KEY_ST key_info;
	KEY_CB_NODE_ST* pLoop=g_input_key_cb_chain_pHead;

#if defined(DEBUG_TRACE)	
	switch(btn_info.nBtn)
	{
	//------------------------
		case LIST_BTN_0:         TRACE_I("Parse: BTN_KEY0 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_1:         TRACE_I("Parse: BTN_KEY1 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_2:         TRACE_I("Parse: BTN_KEY2 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_3:         TRACE_I("Parse: BTN_KEY3 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_4:         TRACE_I("Parse: BTN_KEY4 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_5:         TRACE_I("Parse: BTN_KEY5 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_6:         TRACE_I("Parse: BTN_KEY6 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_7:         TRACE_I("Parse: BTN_KEY7 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_8:         TRACE_I("Parse: BTN_KEY8 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_9:         TRACE_I("Parse: BTN_KEY9 %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_OK:        TRACE_I("Parse: BTN_OK %s.\r\n",    (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_DEL:       TRACE_I("Parse: BTN_DEL %s.\r\n",   (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
	//------------------------
		case LIST_BTN_UP:        TRACE_I("Parse: BTN_UP %s.\r\n",    (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_DOWN:      TRACE_I("Parse: BTN_DOWN %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_LEFT:      TRACE_I("Parse: BTN_LEFT %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_RIGHT:     TRACE_I("Parse: BTN_RIGHT %s.\r\n", (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
	//------------------------
		case LIST_BTN_GEAR_1:    TRACE_I("Parse: BTN_GEAR_1 %s.\r\n",(LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_GEAR_2:    TRACE_I("Parse: BTN_GEAR_2 %s.\r\n",(LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_GEAR_3:    TRACE_I("Parse: BTN_GEAR_3 %s.\r\n",(LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_GEAR_4:    TRACE_I("Parse: BTN_GEAR_4 %s.\r\n",(LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_GEAR_5:    TRACE_I("Parse: BTN_GEAR_5 %s.\r\n",(LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_GEAR_6:    TRACE_I("Parse: BTN_GEAR_6 %s.\r\n",(LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_GEAR_7:    TRACE_I("Parse: BTN_GEAR_7 %s.\r\n",(LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_GEAR_8:    TRACE_I("Parse: BTN_GEAR_8 %s.\r\n",(LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
	//------------------------
		case LIST_BTN_WIFI:      TRACE_I("Parse: BTN_WIFI %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_BT:        TRACE_I("Parse: BTN_BT %s.\r\n",    (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
	//------------------------
		case LIST_BTN_PLAY:      TRACE_I("Parse: BTN_PLAY %s.\r\n",  (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_PAUSE:     TRACE_I("Parse: BTN_PAUSE %s.\r\n", (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
	//------------------------ vkey star
		case LIST_BTN_PAGE_UP:   TRACE_I("Parse: PAGE_UP %s.\r\n",   (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_PAGE_DOWN: TRACE_I("Parse: PAGE_DOWN %s.\r\n", (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_INC:       TRACE_I("Parse: BTN_INC %s.\r\n",   (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
		case LIST_BTN_DEC:       TRACE_I("Parse: BTN_DEC %s.\r\n",   (LIST_BTN_ACT_PRESS==btn_info.nAct)? "press":"release");  break;
	//------------------------ vkey end
		default:
			TRACE_E("Parse: btn out of range.\r\n");
			break;
	}
#endif

	key_info.nKey=Frm_Input_Button_To_Key(btn_info.nBtn);
	key_info.nAction = (btn_info.nAct)? LIST_KEY_ACT_PRESS : LIST_KEY_ACT_RELEASE;

	do
	{
		pLoop->pCallback(key_info);
		pLoop=pLoop->next;
	}while(pLoop!=NULL);
}

//========================================
// TOUCH 
//========================================






/*========================================================================================================
										F U N C T I O N----extern
========================================================================================================*/
void Frm_Input_Button_Callback(DRV_BTN_INFO_ST btn_info) // recv drv button event, send to input task
{
#if 1 // mutex
	switch(btn_info.nBtn)
	{
		case LIST_BTN_PAGE_DOWN:
		case LIST_BTN_PAGE_UP:
		case LIST_BTN_INC:
		case LIST_BTN_DEC:
			//THESE BUTTON HAS ONLY RELEASE EVENT, NO PRESS EVENT
			pf_memcpy(&g_input_BtnInfo, &btn_info, sizeof(DRV_BTN_INFO_ST));
			//TRACE_I("SEND: addr:(0x%X).\r\n", (uint32_t)(&g_input_BtnInfo));
			osMessagePut(g_QueueId_Input, (uint32_t)(&g_input_BtnInfo), 50);
			break;


		case LIST_BTN_0:
		case LIST_BTN_1:
		case LIST_BTN_2:
		case LIST_BTN_3:
		case LIST_BTN_4:
		case LIST_BTN_5:
		case LIST_BTN_6:
		case LIST_BTN_7:
		case LIST_BTN_8:
		case LIST_BTN_9:
		case LIST_BTN_OK:
		case LIST_BTN_DEL:
			//----------------
		case LIST_BTN_UP:
		case LIST_BTN_DOWN:
		case LIST_BTN_LEFT:
		case LIST_BTN_RIGHT:
			if((LIST_BTN_NONE == btn_info.nBtn)\
				||((btn_info.nBtn == g_input_BtnInfo.nBtn)&&(btn_info.nAct == g_input_BtnInfo.nAct))\
				||((btn_info.nBtn != g_input_BtnInfo.nBtn)&&(g_input_BtnInfo.nAct != LIST_BTN_ACT_RELEASE)))
			{
				TRACE_W("CONDITION NOT FIT\r\n");
			}
			else
			{
				pf_memcpy(&g_input_BtnInfo, &btn_info, sizeof(DRV_BTN_INFO_ST));
				//TRACE_I("SEND: addr:(0x%X).\r\n", (uint32_t)(&g_input_BtnInfo));
				osMessagePut(g_QueueId_Input, (uint32_t)(&g_input_BtnInfo), 50);
			}
		default:
			break;
	}
#else
	//TRACE_I("Callback---BTN=%d, ACT=%d.\r\n", btn_info.nBtn, btn_info.nAct);
	if(btn_info.nBtn != LIST_BTN_NONE)
	{
		pf_memcpy(&g_input_BtnInfo, &btn_info, sizeof(DRV_BTN_INFO_ST));
		//TRACE_I("SEND: addr:(0x%X).\r\n", (uint32_t)(&g_input_BtnInfo));
		osMessagePut(g_QueueId_Input, (uint32_t)(&g_input_BtnInfo), 50);
	}
#endif
}

void Frm_Input_Task(void const * argument)
{
	osEvent event;

	TRACE_F();
	
//	g_TaskHandle_Input = osThreadGetId();

// create message queue
  osMessageQDef(buttonQueue, 16, uint32_t);
  g_QueueId_Input = osMessageCreate(osMessageQ(buttonQueue), NULL);

	for(;;)
	{
		event = osMessageGet(g_QueueId_Input, osWaitForever);

		//TRACE_I("<<<RECV: event.status=%d.\r\n", event.status);
		if(event.status==osEventMessage)  
		{
			DRV_BTN_INFO_ST btn_info;
		
			//TRACE_I("RECV: addr(0x%X).\r\n", event.value.p);
			pf_memcpy(&btn_info, event.value.p, sizeof(DRV_BTN_INFO_ST));
			//TRACE_I("Parse---BTN=%d, ACT=%d.\r\n", btn_info.nBtn,  btn_info.nAct);
			Frm_Input_Button_Parse(btn_info);
		}
	}
}

//========================================
// KEY 
//========================================
void Frm_Input_Key_Register_Callback(fpFrmInputKeyCallback func_ptr) // for app
{
	if(func_ptr)
	{
		KEY_CB_NODE_ST *pNewNode=pf_malloc(sizeof(KEY_CB_NODE_ST));
		
		if(pNewNode)
		{
			pNewNode->pCallback = func_ptr;
			pNewNode->next = NULL;
		}
		
		if(NULL==g_input_key_cb_chain_pHead)
		{
			g_input_key_cb_chain_pHead = pNewNode;
			g_input_key_cb_chain_pTail = pNewNode;
		}
		else
		{
			g_input_key_cb_chain_pTail->next = pNewNode;
			g_input_key_cb_chain_pTail=pNewNode;
		}
	}
}

//========================================
// TOUCH 
//========================================
void Frm_Input_Touch_Register_Callback(fpFrmInputTouchCallback func_ptr) // for app use
{
	
}
/*========================================================================================================
										End
========================================================================================================*/



