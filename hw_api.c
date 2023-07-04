#include "include/hw_api.h"
#include "tm4c_os.h"

void HAL_SPI_Enable(void) {
  gpio(GPIO_PORTE, PIN_NUMBER, GPIO_STATE_OFF);
}
void HAL_SPI_Disable(void) {
  gpio(GPIO_PORTE, PIN_NUMBER, GPIO_STATE_ON);
}
uint8_t HAL_SPI_Write(uint8_t data) {
  spi(SPI_TRANSMIT, &data);
}
uint8_t HAL_SPI_WriteByte(uint8_t data) {
  spi(SPI_TRANSMIT, &data);
}
void HAL_SPI_WriteBuffer(uint8_t *Buffer, uint32_t Length) {
  for (int i = 0; i < Length; i++) {
    spi(SPI_TRANSMIT, &Buffer[i]);
  }
}
void HAL_SPI_ReadBuffer(uint8_t *Buffer, uint32_t Length) {
  for (int i = 0; i < Length; i++) {
    spi(SPI_RECEIVE, &Buffer[i]);
  }
}
void HAL_Delay(uint32_t milliseconds) {
  delay(milliseconds);
}
void HAL_Eve_Reset_HW(void) {
  gpio(GPIO_PORTE, PIN_NUMBER, GPIO_STATE_OFF);
  gpio(GPIO_PORTE, PIN_NUMBER, GPIO_STATE_ON);
}
void HAL_Open(void) {
  HAL_SPI_Disable();
}
void HAL_Close(void) {}
