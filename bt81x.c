#include "include/bt81x.h"
#include "tm4c123gh6pm.h"
#include "hw_memmap.h"

#include "timer.h"
#include "sysctl.h"

uint8_t initEve() {
  //uint8_t status;
  
  gpio(GPIO_PORTE, 3, GPIO_STATE_ON);

  hostCommand(0x44, 0); //CLKEXT
  hostCommand(0x0, 0); //ACTIVE
  hostCommand(0x68,0); //RST_PULSE
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
  TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_ONE_SHOT);
  TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()*3);
  TimerEnable(TIMER0_BASE, TIMER_A);
  while (TIMER_RIS_TATORIS != TimerIntStatus(TIMER0_BASE, false));

  while (0x7C != read8Bits(__RAM_REG));

  //status = hostMemoryRead(__RAM_REG + 0x20);
  //if (status & 0x1) {
    printf("Coprocessor engine is in reset status\n\r");
  //  return 1;
  //}
  //if (status & 0x2) {
  //  printf("Touch engine is in reset status\n\r");
  //  return 1;
  //}
  //if (status & 0x4) {
  //  printf("Audio engine is in reset status\n\r");
  //  return 1;
  //}

  return 0;
}

void hostCommand(uint8_t command, uint8_t parameter) {
  uint8_t hostTransaction[3];
  hostTransaction[0] = command;
  hostTransaction[1] = parameter;
  hostTransaction[2] = 0;

  gpio(GPIO_PORTE, 3, GPIO_STATE_OFF);
  for (int i = 0; i < 3; i++)
    spi(SPI_TRANSMIT, &hostTransaction[i]);
  gpio(GPIO_PORTE, 3, GPIO_STATE_ON);
}

void writeBytes(const uint32_t address, const uint8_t numBytes, uint32_t data) {
  //3 bytes for the transaction and up to 4 data bytes
  uint8_t transaction[7];

  if (numBytes > 4)
    return;

  transaction[2] = ((uint8_t *)&address)[2];
  transaction[1] = ((uint8_t *)&address)[1];
  transaction[0] = ((uint8_t *)&address)[0];

  int i, j;
  for (i = 3, j = i; i < 3 + numBytes; i++, j--)
    transaction[i] = ((uint8_t *)&data)[j];

  //gpio(GPIO_PORTE, 3, GPIO_STATE_OFF);
  for (int i = 0; i < 3 + numBytes; i++)
    spi(SPI_TRANSMIT, &transaction[i]);
  //gpio(GPIO_PORTE, 3, GPIO_STATE_ON);
}

uint8_t read8Bits(const uint32_t address) {
  uint8_t transaction[3];
  uint8_t data_rx;

  transaction[0] = ((uint8_t *)&address)[2];
  transaction[1] = ((uint8_t *)&address)[1];
  transaction[2] = ((uint8_t *)&address)[0];

  gpio(GPIO_PORTE, 3, GPIO_STATE_OFF);
  for (int i = 0; i < 3; i++)
    spi(SPI_TRANSMIT, &transaction[i]);
  gpio(GPIO_PORTE, 3, GPIO_STATE_ON);

  spi(SPI_RECEIVE, &data_rx);

  return data_rx;
}

uint16_t read16Bits(const uint32_t address) {
  uint8_t transaction[3];
  uint8_t data_rx;
  uint16_t data16;

  transaction[2] = ((uint8_t *)&address)[2];
  transaction[1] = ((uint8_t *)&address)[1];
  transaction[0] = ((uint8_t *)&address)[0];

  //gpio(GPIO_PORTE, 3, GPIO_STATE_OFF);
  for (int i = 0; i < 3; i++)
    spi(SPI_TRANSMIT, &transaction[i]);
  //gpio(GPIO_PORTE, 3, GPIO_STATE_ON);

  //TODO: How to consolidate the 8 bits at a time into 16 and 32
  for (int i = 0; i < 2; i++) {
    spi(SPI_RECEIVE, &data_rx);
  }

  return data16;
}

uint8_t hostMemoryRead(uint32_t address) {
  uint8_t data_rx = 0;
  uint8_t transaction[4];

  gpio(GPIO_PORTE, 3, GPIO_STATE_OFF);
  for (int i = 0; i < 4; i++)
    spi(SPI_TRANSMIT, &transaction[i]);
  gpio(GPIO_PORTE, 3, GPIO_STATE_ON);
  
  //If statements are debug code. Read 4 bytes from address 0xC0000 and we
  //should receive 4 bytes back. One of them will be 0x15
  spi(SPI_RECEIVE, &data_rx);
  if (data_rx == 0x15)
    return data_rx;
  spi(SPI_RECEIVE, &data_rx);
  if (data_rx == 0x15)
    return data_rx;
  spi(SPI_RECEIVE, &data_rx);
  if (data_rx == 0x15)
    return data_rx;
  spi(SPI_RECEIVE, &data_rx);
  if (data_rx == 0x15)
    return data_rx;

  //return data_rx;
  return 222;
}

void hostMemoryWrite(uint32_t address, uint8_t *data, uint8_t len) {
}

//void setPowerMode(enum bt81xPowerMode mode) {
//  uint8_t transaction[3];
//
//  switch (mode) {
//    case ACTIVE:
//      createHostTransaction(0x00, 0x00, transaction);
//      break;
//    case STANDBY:
//      createHostTransaction(0x41, 0x00, transaction);
//      break;
//    case SLEEP:
//      createHostTransaction(0x42, 0x00, transaction);
//      break;
//    case PWRDOWN:
//      createHostTransaction(0x43, 0x00, transaction);
//      break;
//  }
//
//  GPIO_PORTE_DATA_R &= ~(1 << 3);
//  for (int i = 0; i < 3; i++)
//    spi(SPI_TRANSMIT, &transaction[i]);
//  GPIO_PORTE_DATA_R |= (1 << 3);
//}

//void initExternalClock(struct ClockFrequencies freq) {
//  uint8_t transaction[3];
//  uint8_t clkselParam;
//  uint32_t frequency;
//  if (freq == _24MHZ) {
//    clkselParam = 0x02;
//    frequency = 24E6;
//  }
//  else if (freq == _36MHZ) {
//    clkselParam = 0x03;
//    frequency = 36E6;
//  }
//  else if (freq == _48MHZ) {
//    clkselParam = 0x14;
//    frequency = 48E6;
//  }
//  else if (freq == _60MHZ) {
//    clkselParam = 0x15;
//    frequency = 60E5;
//  }
//  else if (freq == _72MHZ) {
//    clkselParam = 0x16;
//    frequency = 72E6;
//  }
//  else {
//    //Default speed of 60MHz
//    clkselParam = 0x0;
//    frequency = 60E6;
//  }
//
//  //Switch to external oscillator
//  createHostTransaction(0x44, 0x0, transaction);
//  GPIO_PORTE_DATA_R &= ~(1 << 3);
//  for (int i = 0; i < 3; i++)
//    spi(SPI_TRANSMIT, &transaction[i]);
//  GPIO_PORTE_DATA_R |= (1 << 3);

  //createHostTransaction(0x62, clkselParam, transaction);
  //for (int i = 0; i < 3; i++)
  //  spi(SPI_TRANSMIT, &transaction[i]);
//}
