/**
 * @file TFT_Displays_program.c
 * @brief This file contains the implementation of the TFT Displays module functions.
 * 
 * This module provides functions for interfacing with TFT (Thin-Film Transistor) displays
 * to control graphical user interfaces (GUIs), display images, and render text.
 *
 * @date 20 Jul 2023
 * @version V01
 * @author Mahmoud Abdelraouf Mahmoud
 *
 * @note Before using this module, make sure to configure the display controller
 * and the required GPIO pins for communication and control.
 *
 * @see TFT_Displays_interface.h for the public interface and function descriptions.
 */

/**< LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/**< MCAL */
#include "GPIO_interface.h"
#include "SPI_interface.h"
#include "STK_interface.h"

/**< HAL */
#include "TFT_config.h"
#include "TFT_private.h"
#include "TFT_interface.h"

/**
 * @brief Initializes the TFT display module.
 *
 * This function initializes the TFT display by configuring the display controller,
 * setting up the communication interface, and performing any required initialization steps.
 *
 * @param None
 * @retval None
 */
void TFT_voidInit(SPI_Peripheral_t Copy_Spi, const TFT_Config_t *Copy_psTftDisplay)
{   
    /**< Initialization sequence for the TFT display */ 
    TFT_SendCommand(Copy_Spi, Copy_psTftDisplay, TFT_COMMAND_SOFT_RESET);
    HAL_Delay(100); // Delay after reset
    
    TFT_SendCommand(Copy_Spi, Copy_psTftDisplay, TFT_COMMAND_SLEEP_OUT);
    HAL_Delay(100); // Delay after sleep out

    // Configure display settings, gamma correction, etc.
    TFT_SendCommand(Copy_Spi, Copy_psTftDisplay, TFT_COMMAND_DISPLAY_ON);
    
    // Additional configuration steps as needed

    // End of initialization
}


/**
 * @brief Clears the display screen.
 *
 * This function clears the entire display screen and sets all pixels to the background color.
 *
 * @param None
 * @retval None
 */
void TFT_voidClearScreen(void)
{
    /**< Implement the TFT display screen clearing */
    
}

/**
 * @brief Draws a pixel at the specified coordinates with the given color.
 *
 * This function draws a single pixel at the specified (x, y) coordinates with the specified color.
 *
 * @param[in] x The X-coordinate of the pixel.
 * @param[in] y The Y-coordinate of the pixel.
 * @param[in] color The color of the pixel in 16-bit RGB565 format.
 * @retval None
 */
void TFT_voidDrawPixel(u16 x, u16 y, u16 color)
{
    /* Implement the TFT pixel drawing function */
    
}

/**
 * @brief Draws a line between two points with the given color.
 *
 * This function draws a line between the specified starting point (x1, y1) and
 * the ending point (x2, y2) with the specified color.
 *
 * @param[in] x1 The X-coordinate of the starting point.
 * @param[in] y1 The Y-coordinate of the starting point.
 * @param[in] x2 The X-coordinate of the ending point.
 * @param[in] y2 The Y-coordinate of the ending point.
 * @param[in] color The color of the line in 16-bit RGB565 format.
 * @retval None
 */
void TFT_voidDrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    /*<* Implement the TFT line drawing function */
   
}

/**
 * @brief Displays an image on the TFT screen.
 *
 * This function displays an image stored in memory at the specified (x, y) coordinates.
 *
 * @param[in] x The X-coordinate where the image will be displayed.
 * @param[in] y The Y-coordinate where the image will be displayed.
 * @param[in] image Pointer to the image data in RGB565 format.
 * @param[in] width The width of the image in pixels.
 * @param[in] height The height of the image in pixels.
 * @retval None
 */
void TFT_voidDisplayImage(u16 x, u16 y, const u16* image, u16 width, u16 height)
{
    /**< Implement the TFT image display function */
    
}

/**
 * @brief Displays text on the TFT screen.
 *
 * This function displays text at the specified (x, y) coordinates with the given color.
 *
 * @param[in] x The X-coordinate where the text will be displayed.
 * @param[in] y The Y-coordinate where the text will be displayed.
 * @param[in] text Pointer to the text string to be displayed.
 * @param[in] font The font size and style to use for rendering the text.
 * @param[in] color The color of the text in 16-bit RGB565 format.
 * @retval None
 */
void TFT_voidDisplayText(u16 x, u16 y, const char* text, const Font_t* font, u16 color)
{
    /**< Implement the TFT text display function */

}

/**
 * @addtogroup TFT_Private_Functions
 * @{
 */

static void TFT_SendCommand(SPI_Peripheral_t Copy_Spi,const TFT_Config_t *Copy_psTftDisplay, u8 Copy_Command)
{
    /**< Set RS (Register Select) pin low to indicate command mode */ 
    MGPIO_voidSetPinValue(Copy_psTftDisplay->TFT_Port, Copy_psTftDisplay->TFT_RsPin,MGPIO_LOW); 

    /**<  Set CS (Chip Select) pin low to select the TFT display for communication */
    MGPIO_voidSetPinValue(Copy_psTftDisplay->TFT_Port, Copy_psTftDisplay->TFT_CsPin,MGPIO_LOW); 

    SPI_t *spi = SPI_SelectSpi(Copy_Spi);

    /**< Perform SPI data transfer to send the command byte */ 
    SPI_voidTransfer(spi, &Copy_Command, NULL, 1); 

    /**< Set CS pin high to release the TFT display */ 
    MGPIO_voidSetPinValue(Copy_psTftDisplay->TFT_Port, Copy_psTftDisplay->TFT_CsPin,MGPIO_HIGH); 
    
}

static void TFT_SendData(SPI_Peripheral_t Copy_Spi, const TFT_Config_t *Copy_psTftDisplay, u8 Copy_Data)
{
    /**< Set RS (Register Select) pin high to indicate data mode */
    MGPIO_voidSetPinValue(Copy_psTftDisplay->TFT_Port, Copy_psTftDisplay->TFT_RsPin, MGPIO_HIGH);

    /**< Set CS (Chip Select) pin low to select the TFT display for communication */
    MGPIO_voidSetPinValue(Copy_psTftDisplay->TFT_Port, Copy_psTftDisplay->TFT_CsPin, MGPIO_LOW);

    SPI_t *spi = SPI_SelectSpi(Copy_Spi);

    /**< Perform SPI data transfer to send the data byte */
    SPI_voidTransfer(spi, &Copy_Data, NULL, 1);

    /**< Set CS pin high to release the TFT display */
    MGPIO_voidSetPinValue(Copy_psTftDisplay->TFT_Port, Copy_psTftDisplay->TFT_CsPin, MGPIO_HIGH);
}


/**
 * @} TFT_Private_Functions
 */

/** @} */ // End of TFT_Displays_program.c module.