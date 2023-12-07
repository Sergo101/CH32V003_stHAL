/**
 * original author:  Tilen Majerle<tilen@majerle.eu>
 * modification for STM32f10x: Alexander Lutsai<s.lyra@ya.ru>

   ----------------------------------------------------------------------
   	Copyright (C) Alexander Lutsai, 2016
    Copyright (C) Tilen Majerle, 2015
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
 */
#ifndef SSD1306_H
#define SSD1306_H 100

/* C++ detection */
#ifdef __cplusplus
extern C {
#endif

/**
 * This SSD1306 LCD uses I2C for communication
 *
 * Library features functions for drawing lines, rectangles and circles.
 *
 * It also allows you to draw texts and characters using appropriate functions provided in library.
 *
 * Default pinout
 *
SSD1306    |STM32F10x    |DESCRIPTION

VCC        |3.3V         |
GND        |GND          |
SCL        |PB6          |Serial clock line
SDA        |PB7          |Serial data line
 */

#include "fonts.h"
#include "i2c_hal.h"
#include "stdlib.h"
#include "string.h"
#include "systick_hal.h"


/*#define DC_port		GPIOA
#define DC_pin		GPIO_PIN_8
#define ssd130x_command			gpio_bit_write (DC_port, DC_pin, RESET);
#define ssd130x_data				gpio_bit_write (DC_port, DC_pin, SET);

#define CS_port		GPIOB
#define CS_pin		GPIO_PIN_2
#define ssd130x_select			gpio_bit_write (CS_port, CS_pin, RESET);
#define ssd130x_unselect		gpio_bit_write (CS_port, CS_pin, SET);

#define	RST_port		GPIOB
#define RST_pin			GPIO_PIN_12
#define ssd130x_reset					gpio_bit_write (RST_port, RST_pin, RESET);
#define ssd130x_unreset				gpio_bit_write (RST_port, RST_pin, SET);*/


#define SSD1306_128x64
//#define SSD1306_128x32
//#define TURN_90_DEGREE
/* I2C settings */
#ifndef SSD1306_I2C
#define SSD1306_I2C              I2C1
#endif

#ifndef SSD1306_SPI
#define SSD1306_SPI              SPI1
#endif

#ifndef SSD1306_I2C_TIMEOUT
#define SSD1306_I2C_TIMEOUT					200
#endif

/* I2C address */
#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR         0x78
//#define SSD1306_I2C_ADDR       0x7A
#endif

/* SSD1306 settings */
/* SSD1306 width in pixels */
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH            128
#endif
/* SSD1306 LCD height in pixels */
#ifdef SSD1306_128x32
#define SSD1306_HEIGHT           32
#define COMPINS									 0x02
#define MULTIPLEX								 0x1F
#endif

#ifdef SSD1306_128x64
#define SSD1306_HEIGHT           64
#define COMPINS									 0x12
#define MULTIPLEX								 0x3F
#endif

// Commands
#define SSD1306_SETCONTRAST                  0x81
#define SSD1306_DISPLAYALLON_RESUME          0xA4
#define SSD1306_DISPLAYALLON                 0xA5
#define SSD1306_NORMALDISPLAY                0xA6
#define SSD1306_INVERTDISPLAY                0xA7
#define SSD1306_DISPLAYOFF                   0xAE
#define SSD1306_DISPLAYON                    0xAF
#define SSD1306_SETDISPLAYOFFSET             0xD3
#define SSD1306_SETCOMPINS                   0xDA
#define SSD1306_SETVCOMDETECT                0xDB
#define SSD1306_SETDISPLAYCLOCKDIV           0xD5
#define SSD1306_SETPRECHARGE                 0xD9
#define SSD1306_SETMULTIPLEX                 0xA8
#define SSD1306_SETLOWCOLUMN                 0x00
#define SSD1306_SETHIGHCOLUMN                0x10
#define SSD1306_SETSTARTLINE                 0x40
#define SSD1306_MEMORYMODE                   0x20
#define SSD1306_COLUMNADDR                   0x21
#define SSD1306_PAGEADDR                     0x22
#define SSD1306_COMSCANINC                   0xC0
#define SSD1306_COMSCANDEC                   0xC8
#define SSD1306_SEGREMAP                     0xA0
#define SSD1306_CHARGEPUMP                   0x8D
#define SSD1306_EXTERNALVCC                  0x01
#define SSD1306_SWITCHCAPVCC                 0x02
// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL               0x2F
#define SSD1306_DEACTIVATE_SCROLL             0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA      0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL       0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL        0x27
#define SSD1306_VERT_AND_RIGHT_HORIZ_SCROLL   0x29
#define SSD1306_VERT_AND_LEFT_HORIZ_SCROLL    0x2A

/**
 * @brief  SSD1306 color enumeration
 */
typedef enum {
	SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;



/**
 * @brief  Initializes SSD1306 LCD
 * @param  None
 * @retval Initialization status:
 *           - 0: LCD was not detected on I2C port
 *           - > 0: LCD initialized OK and ready to use
 */
uint8_t SSD1306_Init(void);

/** 
 * @brief  Updates buffer from internal RAM to LCD
 * @note   This function must be called each time you do some changes to LCD, to update buffer from RAM to LCD
 * @param  None
 * @retval None
 */
void SSD1306_UpdateScreen(void);

/** 
 * @brief  Write command to LCD
 * @note   None
 * @param  Commands see in datasheet
 * @retval None
 */
void ssd1306_writecommand ( uint8_t command);
/**
 * @brief  Toggles pixels invertion inside internal RAM
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  None
 * @retval None
 */
void SSD1306_ToggleInvert(void);

/** 
 * @brief  Fills entire LCD with desired color
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  Color: Color to be used for screen fill. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_Fill(SSD1306_COLOR_t Color);

/**
 * @brief  Draws pixel at desired location
 * @note   @ref SSD1306_UpdateScreen() must called after that in order to see updated LCD screen
 * @param  x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
 * @param  y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
 * @param  color: Color to be used for screen fill. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);

/**
 * @brief  Sets cursor pointer to desired location for strings
 * @param  x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
 * @param  y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
 * @retval None
 */
void SSD1306_GotoXY(uint16_t x, uint16_t y);

/**
 * @brief  Puts character to internal RAM
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  ch: Character to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval Character written
 */
char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color);

/**
 * @brief  Puts string to internal RAM
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  *str: String to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval Zero on success or character value when function failed
 */
char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);

/**
 * @brief  Draws line on LCD
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x0: Line X start point. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y0: Line Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  x1: Line X end point. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y1: Line Y end point. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c);

/**
 * @brief  Draws rectangle on LCD
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: Top left X start point. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y: Top left Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  w: Rectangle width in units of pixels
 * @param  h: Rectangle height in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);

/**
 * @brief  Draws filled rectangle on LCD
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: Top left X start point. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y: Top left Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  w: Rectangle width in units of pixels
 * @param  h: Rectangle height in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);

/**
 * @brief  Draws triangle on LCD
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x1: First coordinate X location. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y1: First coordinate Y location. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  x2: Second coordinate X location. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y2: Second coordinate Y location. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  x3: Third coordinate X location. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y3: Third coordinate Y location. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);

/**
 * @brief  Draws circle to STM buffer
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: X location for center of circle. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y: Y location for center of circle. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  r: Circle radius in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

/**
 * @brief  Draws filled circle to STM buffer
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: X location for center of circle. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y: Y location for center of circle. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  r: Circle radius in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);



/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
