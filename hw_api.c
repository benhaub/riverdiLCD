#include "include/hw_api.h"
#include "tm4c_os.h"

void HAL_SPI_Enable(void) {
  gpio(GPIO_PORTE, CS_PIN_NUMBER, GPIO_STATE_OFF);
}

void HAL_SPI_Disable(void) {
  gpio(GPIO_PORTE, CS_PIN_NUMBER, GPIO_STATE_ON);
}

uint8_t HAL_SPI_Write(uint8_t data) {
  spi(SPI_TRANSMIT, &data);
  return 0;
}

uint8_t HAL_SPI_WriteByte(uint8_t data) {
  spi(SPI_TRANSMIT, &data);
  return 0;
}

void HAL_SPI_WriteBuffer(uint8_t *Buffer, uint32_t Length) {
  for (int i = 0; i < Length; i++) {
    spi(SPI_TRANSMIT, &Buffer[i]);
  }
}

void HAL_SPI_ReadBuffer(uint8_t *Buffer, uint32_t Length) {
  const uint8_t dummyByte = 0x0;

  for (int i = 0; i < Length; i++) {
//After the dummy byte, BT81x responds to each host byte with read data bytes
    spi(SPI_TRANSMIT, &dummyByte);
    spi(SPI_RECEIVE, &Buffer[i]);
  }
}

void HAL_Delay(uint32_t milliseconds) {
  delay(milliseconds);
}

void HAL_Eve_Reset_HW(void) {
//Minimum time for PD to be held low is 5ms. Sect. 4.9.2
  const uint32_t minimumPowerdownTimeMs = 6;

  gpio(GPIO_PORTE, PD_PIN_NUMBER, GPIO_STATE_OFF);
  HAL_Delay(minimumPowerdownTimeMs);
  gpio(GPIO_PORTE, PD_PIN_NUMBER, GPIO_STATE_ON);
}

void HAL_Open(void) {
  HAL_SPI_Disable();
}

void HAL_Close(void) {}
