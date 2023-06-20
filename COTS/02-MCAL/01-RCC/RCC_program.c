/********************************************************************/
/************* Author    : Mahmoud Abdelraouf Mahmoud   *************/
/************* Date		 : 25 Feb 2022                  *************/
/************* Version   : V01                          *************/
/********************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidInitSysClock(void)
{
	#if 	RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
		RCC_CR_R   = 0x00010000; 						/**< Enable HSI with no bypass */
		while(!GET_BIT(RCC_CR_R, RCC_HSERDY_BIT)); 		/**< wait for the External clock be stable */
		RCC_CFGR_R = 0x00000001; 						/**< HSE selected as system clock */
	#elif	RCC_CLOCK_TYPE == RCC_HSE_RC
		RCC_CR_R = 0x00050000; 							/**< Enable HSI with bypass */
		while(!GET_BIT(RCC_CR_R, RCC_HSERDY_BIT)); 	/**< wait for the External clock be stable */
		RCC_CFGR_R = 0x00000001; 						/**< HSE selected as system clock */
	#elif	RCC_CLOCK_TYPE == RCC_HSI
		RCC_CR_R = 0x00000081; 						/**< Enable HSI + Trimming = 0 */
		while(!GET_BIT(RCC_CR_R, RCC_HSIRDY_BIT));
		RCC_CFGR_R = 0x00000000;						/**< HSI selected as system clock */
	#elif	RCC_CLOCK_TYPE == RCC_PLL
		#if RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
			CLR_BIT(MRCC_CFGR_R, RCC_PLLSRC_BIT);		/**< 0: HSI OSCILLATOR CLOCK / 2 SELECTED AS PLL INPUT CLOCK */
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
			SET_BIT(RCC_CFGR_R, RCC_PLLSRC_BIT);		/**< 1: HSE OSCILLATOR CLOCK SELECTED AS PLL INPUT CLOCK */
			SET_BIT(RCC_CFGR_R, RCC_PLLXTPRE_BIT);		/**< 1: HSE CLOCK DIVIDED BY 2 */
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
			SET_BIT(RCC_CFGR_R, RCC_PLLSRC_BIT);		/**< 1: HSE OSCILLATOR CLOCK SELECTED AS PLL INPUT CLOCK */
			CLR_BIT(RCC_CFGR_R, RCC_PLLXTPRE_BIT);    	/**< 0: HSE CLOCK NOT DIVIDED */
		#else
			#error("YOU CHOSED WRONG CLOCK INPUT FOR PLL!!")
		#endif
	#else
		#error("YOU CHOSED WRONG CLOCK TYPE!!")
	#endif
	
	
}


void RCC_voidEnableClock(u8 Copy_u8BusId,u8 Copy_u8PeriphId)
{
	if(Copy_u8PeriphId <=31)
	{
		switch(Copy_u8BusId)
		{
			case RCC_AHB  : SET_BIT(RCC_AHBENR_R , Copy_u8PeriphId); break;
			case RCC_APB1 : SET_BIT(RCC_APB1ENR_R, Copy_u8PeriphId); break;
			case RCC_APB2 : SET_BIT(RCC_APB2ENR_R, Copy_u8PeriphId); break;
			//default       : /* Return Error */                  break;
		}
	}
	else
	{
		//Return Error
	}
}


void RCC_voidDisableClock(u8 Copy_u8BusId,u8 Copy_u8PeriphId)
{
	if(Copy_u8PeriphId <=31)
	{
		switch(Copy_u8BusId)
		{
			case RCC_AHB  : CLR_BIT(RCC_AHBENR_R , Copy_u8PeriphId); break;
			case RCC_APB1 : CLR_BIT(RCC_APB1ENR_R, Copy_u8PeriphId); break;
			case RCC_APB2 : CLR_BIT(RCC_APB2ENR_R, Copy_u8PeriphId); break;
			//default       : /* Return Error */                    break;
		}
	}
	else
	{
		//Return Error
	}
}
