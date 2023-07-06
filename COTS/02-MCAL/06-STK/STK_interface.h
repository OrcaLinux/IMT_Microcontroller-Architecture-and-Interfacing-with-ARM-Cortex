/**
 * @file STK_interface.h
 * @brief This file contains the public interface for the SysTick timer module.
 *
 * @copyright Copyright (c) 2023
 * 
 * This module provides functions for configuring and using the SysTick timer in the STM32F10xx microcontroller.
 *
 * @date 06 Jul 2023
 * @version V01
 * @author Mahmoud Abdelraouf Mahmoud
 */

#ifndef __STK_INTERFACE_H__
#define __STK_INTERFACE_H__

/**
 * @brief Initializes the SysTick timer with the specified reload value.
 *
 * This function initializes the SysTick timer with the specified reload value. The timer is configured to generate an interrupt
 * when it reaches zero, and then reloads the timer with the specified value. The interrupt can be used to implement a periodic
 * timebase for the application.
 *
 * @param[in] Copy_u32LoadValue The reload value to use for the SysTick timer. This value should be less than or equal to 0x00FFFFFF.
 *
 * @return None.
 */
void MSTK_voidInit(u32 Copy_u32LoadValue);

/**
 * @brief Starts the SysTick timer.
 *
 * This function starts the SysTick timer. Once the timer is started, it will count down from the reload value specified in the
 * `STK_voidInit` function until it reaches zero. When the timer reaches zero, it will generate an interrupt and reload with
 * the initial value.
 *
 * @param None.
 *
 * @return None.
 */
void MSTK_voidStart(void);

/**
 * @brief Stops the SysTick timer.
 *
 * This function stops the SysTick timer. Once the timer is stopped, it will no longer count down or generate interrupts.
 *
 * @param None.
 *
 * @return None.
 */
void MSTK_voidStop(void);


/**
 * @brief Resets the SysTick timer.
 *
 * This function disables the SysTick timer, clears the current value, sets the reload value to 0,
 * and clears the count flag.
 *
 * @param None
 *
 * @return None
 */
void MSTK_voidReset(void);

/**
 * @brief Gets the current value of the SysTick timer.
 *
 * This function gets the current value of the SysTick timer. The timer value represents the number of ticks remaining until
 * the timer reaches zero.
 *
 * @param None.
 *
 * @return The current value of the SysTick timer.
 */
u32 MSTK_u32GetCount(void);

/**
 * @brief Blocks the CPU for the specified number of microseconds.
 *
 * This function blocks the CPU for the specified number of microseconds using the SysTick timer. The function calculates the
 * number of ticks required to wait for the specified number of microseconds based on the current system clock frequency and
 * the reload value of the SysTick timer.
 *
 * @param[in] Copy_u32Microseconds The number of microseconds to wait. This value should be less than or equal to 16777215 (0x00FFFFFF).
 *
 * @return None.
 */
void MSTK_voidSetBusyWait(u32 Copy_u32Microseconds);

/**
 * @brief Calls a function after the specified number of microseconds.
 *
 * This function sets a callback function to be called after the specified number of microseconds using the SysTick timer. The
 * function calculates the number of ticks required to wait for the specified number of microseconds based on the current system
 * clock frequency and the reload value of the SysTick timer. When the requested delay has elapsed, the callback function will be
 * called.
 *
 * @param[in] Copy_u32Microseconds The number of microseconds to wait. This value should be less than or equal to 16777215 (0x00FFFFFF).
 * @param[in] Copy_pfCallback The callback function to call when the requested delay has elapsed.
 *
 * @return None.
 */
void MSTK_voidSetIntervalSingle(u32 Copy_u32Microseconds, void (*Copy_pfCallback)(void));

/**
 * @brief Calls a function periodically with the specified period in microseconds.
 *
 * This function sets a callback function to be called periodically with the specified period using the SysTick timer. The
 * function calculates the number of ticks required to wait for the specified period based on the current system clock frequency
 * and the reload value of the SysTick timer. When the requested period has elapsed, the callback function will be called.
 *
 * @param[in] Copy_u32Microseconds The period of the callback function in microseconds. This value should be less than or equal to 16777215 (0x00FFFFFF).
 * @param[in] Copy_pfCallback The callback function to call periodically.
 *
 * @return None.
 */
void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Microseconds, void (*Copy_pfCallback)(void));

#endif /**<  __STK_INTERFACE_H__ */

