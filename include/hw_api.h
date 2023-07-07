#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>              
#include <stdbool.h>

/**
 * @def CS_PIN_NUMBER
 *   GPIO pin number to control SPI chip select.
 */
#define CS_PIN_NUMBER 3
/**
 * @def PD_PIN_NUMBER
 *   GPIO pin number to control bt81x powerdown.
 */
#define PD_PIN_NUMBER 2

void HAL_SPI_Enable(void);
void HAL_SPI_Disable(void);
uint8_t HAL_SPI_Write(uint8_t data);
uint8_t HAL_SPI_WriteByte(uint8_t data);
void HAL_SPI_WriteBuffer(uint8_t *Buffer, uint32_t Length);
void HAL_SPI_ReadBuffer(uint8_t *Buffer, uint32_t Length);
void HAL_Delay(uint32_t milliseconds);
void HAL_Eve_Reset_HW(void);
void HAL_Open(void);
void HAL_Close(void);

#ifdef __cplusplus
}
#endif
