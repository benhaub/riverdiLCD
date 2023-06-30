#include "include/bt81x.h"

#define WorkBuffSz 512

// Global Variables
uint16_t FifoWriteLocation = 0;
char LogBuf[WorkBuffSz];         // The singular universal data array used for all things including logging

uint8_t initEve() {
  uint32_t dataRx;

  gpio(GPIO_PORTE, 3, GPIO_STATE_ON);
  FifoWriteLocation = 0;

  hostCommand(0x44, 0); //CLKEXT
  hostCommand(0x0, 0);  //ACTIVE
  hostCommand(0x68, 0); //RST_PULSE
 
 //Comment out this loop to fix a hardfault. 
  //while(1) {
  //  delay(1000);
  //  led(LED_RED, LED_ON);
  //  delay(1000);
  //  led(LED_RED, LED_OFF);
  //}

  while (0x7C != read8Bits(RAM_REG));
  while (0 != read8Bits(RAM_REG + REG_CPU_RESET));

  dataRx = read32Bits(REG_CHIP_ID);
  printf("Chip ID %x\r\n", dataRx);

  //Configure system clock to 60MHz
  writeBytes(RAM_REG + REG_FREQUENCY, 4, 0x3938700);

  // turn off screen output during startup
  writeBytes(REG_GPIOX + RAM_REG, 1, 0);             // Set REG_GPIOX to 0 to turn off the LCD DISP signal
  writeBytes(REG_PCLK + RAM_REG, 1, 0);              // Pixel Clock Output disable

  // load parameters of the physical screen to the Eve
  // All of these registers are 32 bits, but most bits are reserved, so only write what is actually used
  writeBytes(REG_HCYCLE + RAM_REG, 2, HCYCLE);         // Set H_Cycle to 548
  writeBytes(REG_HOFFSET + RAM_REG, 2, HOFFSET);       // Set H_Offset to 43
  writeBytes(REG_HSYNC0 + RAM_REG, 2, HSYNC0);         // Set H_SYNC_0 to 0
  writeBytes(REG_HSYNC1 + RAM_REG, 2, HSYNC1);         // Set H_SYNC_1 to 41
  writeBytes(REG_VCYCLE + RAM_REG, 2, VCYCLE);         // Set V_Cycle to 292
  writeBytes(REG_VOFFSET + RAM_REG, 2, VOFFSET);       // Set V_OFFSET to 12
  writeBytes(REG_VSYNC0 + RAM_REG, 2, VSYNC0);         // Set V_SYNC_0 to 0
  writeBytes(REG_VSYNC1 + RAM_REG, 2, VSYNC1);         // Set V_SYNC_1 to 10
  writeBytes(REG_SWIZZLE + RAM_REG, 1, SWIZZLE);       // Set SWIZZLE to 0
  writeBytes(REG_PCLK_POL + RAM_REG, 1, PCLK_POL);     // Set PCLK_POL to 1
  writeBytes(REG_CSPREAD + RAM_REG, 1, CSPREAD);       // Set CSPREAD to 1    (32 bit register - write only 8 bits)
  writeBytes(REG_HSIZE + RAM_REG, 2, HSIZE);           // Set H_SIZE to 480
  writeBytes(REG_VSIZE + RAM_REG, 2, VSIZE);           // Set V_SIZE to 272
  writeBytes(REG_DITHER + RAM_REG, 1, DITHER);         // Set DITHER to 1     (32 bit register - write only 8 bits)

  // configure touch & audio
#ifdef TOUCH_RESISTIVE
  writeBytes(REG_TOUCH_CONFIG + RAM_REG, 2, 0x8381);
#elif defined TOUCH_CAPACITIVE
  writeBytes(REG_TOUCH_CONFIG + RAM_REG, 2, 0x5d0);
#endif
  // set touch resistance threshold
  writeBytes(REG_TOUCH_RZTHRESH + RAM_REG, 2, 1200);
  // set touch on: continous - this is default
  writeBytes(REG_TOUCH_MODE + RAM_REG, 1, 0x02);
  // set ADC mode: differential - this is default
  writeBytes(REG_TOUCH_ADC_MODE + RAM_REG, 1, 0x01);
  // set touch oversampling to max
  writeBytes(REG_TOUCH_OVERSAMPLE + RAM_REG, 1, 15);
  // Set Disp GPIO Direction
  writeBytes(REG_GPIOX_DIR + RAM_REG, 2, 0x8000);
  // Enable Disp (if used)
  writeBytes(REG_GPIOX + RAM_REG, 2, 0x8000);
  // Backlight PWM frequency
  writeBytes(REG_PWM_HZ + RAM_REG, 2, 0x00FA);
  // Backlight PWM duty (on)
  writeBytes(REG_PWM_DUTY + RAM_REG, 1, 128);

  // write first display list (which is a clear and blank screen)
  writeBytes(RAM_DL+0, 4, CLEAR_COLOR_RGB(0,0,0));
  writeBytes(RAM_DL+4, 4, CLEAR(1,1,1));
  writeBytes(RAM_DL+8, 4, DISPLAY());
  // swap display lists
  writeBytes(REG_DLSWAP + RAM_REG, 1, DLSWAP_FRAME);
  // after this display is visible on the LCD
  writeBytes(REG_PCLK + RAM_REG, 1, PCLK);

  return 0;
}

void writeBytes(const uint32_t address, const uint8_t numBytes, uint32_t data) {
  //3 bytes for the transaction and up to 4 data bytes
  uint8_t transaction[7];

  if (numBytes > 4)
    return;

  transaction[0] = ((uint8_t *)&address)[2];
  transaction[1] = ((uint8_t *)&address)[1];
  transaction[2] = ((uint8_t *)&address)[0];

  int i, j;
  for (i = 3, j = i; i < 3 + numBytes; i++, j--)
    transaction[i] = ((uint8_t *)&data)[j];

  gpio(GPIO_PORTE, 3, GPIO_STATE_OFF);
  for (int i = 0; i < 3 + numBytes; i++)
    spi(SPI_TRANSMIT, &transaction[i]);
  gpio(GPIO_PORTE, 3, GPIO_STATE_ON);
}

uint8_t read8Bits(const uint32_t address) {
  uint8_t transaction[4];
  uint8_t dataRx;

  transaction[0] = ((uint8_t *)&address)[2];
  transaction[1] = ((uint8_t *)&address)[1];
  transaction[2] = ((uint8_t *)&address)[0];
  transaction[3] = 0; //Dummy


  gpio(GPIO_PORTE, 3, GPIO_STATE_OFF);
  for (int i = 0; i < 4; i++) {
    spi(SPI_TRANSMIT, &transaction[i]);
  }
  spi(SPI_RECEIVE, &dataRx);
  gpio(GPIO_PORTE, 3, GPIO_STATE_ON);

  return dataRx;
}

uint16_t read16Bits(const uint32_t address) {
  uint8_t transaction[4];
  uint8_t partialData[2];

  transaction[0] = ((uint8_t *)&address)[2];
  transaction[1] = ((uint8_t *)&address)[1];
  transaction[2] = ((uint8_t *)&address)[0];
  transaction[3] = 0; //Dummy

  gpio(GPIO_PORTE, 3, GPIO_STATE_OFF);
  for (int i = 0; i < 4; i++) {
    spi(SPI_TRANSMIT, &transaction[i]);
  }
  for ( int i = 0; i < 2; i++) {
    spi(SPI_RECEIVE, &partialData[i]);
    partialData[i] = 1;
  }
  gpio(GPIO_PORTE, 3, GPIO_STATE_ON);

  return partialData[1] << 8 |
         partialData[0];
}

uint32_t read32Bits(const uint32_t address) {
  uint8_t transaction[4];
  uint8_t partialData[4];

  transaction[0] = ((uint8_t *)&address)[2];
  transaction[1] = ((uint8_t *)&address)[1];
  transaction[2] = ((uint8_t *)&address)[0];
  transaction[3] = 0; //Dummy

  gpio(GPIO_PORTE, 3, GPIO_STATE_OFF);
  for (int i = 0; i < 4; i++) {
    spi(SPI_TRANSMIT, &transaction[i]);
  }
  for (int i = 0; i < 4; i++) {
    spi(SPI_RECEIVE, &partialData[i]);
  }
  gpio(GPIO_PORTE, 3, GPIO_STATE_ON);

  return partialData[3] << 24 |
         partialData[2] << 16 |
         partialData[1] << 8 |
         partialData[0];
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

void ramCommand(uint32_t data) {
  // write the command at the globally tracked "write pointer" for the FIFO
  writeBytes(FifoWriteLocation + RAM_CMD, 4, data);
  // Increment the Write Address by the size of a command - which we just sent
  FifoWriteLocation += FT_CMD_SIZE;
  // Wrap the address to the FIFO space
  FifoWriteLocation %= FT_CMD_FIFO_SIZE;
  //writeBytes(REG_CMD_WRITE + RAM_REG, 2, FifoWriteLocation);
}

// updateFifo - Cause the CoProcessor to realize that it has work to do in the form of a
// differential between the read pointer and write pointer.  The CoProcessor (FIFO or "Command buffer") does
// nothing until you tell it that the write position in the FIFO RAM has changed
void updateFifo(void) {
  // We manually update the write position pointer
  writeBytes(REG_CMD_WRITE + RAM_REG, 2, FifoWriteLocation);
}

void waitForCoProcFifoEmpty(void) {
  uint16_t ReadReg;
  uint8_t errChar;
  do
  {
    ReadReg = read16Bits(REG_CMD_READ + RAM_REG);
    if(ReadReg == 0xFFF)
    {
      uint8_t offset = 0;
      do
      {
        // Get the error character and display it
        errChar = read8Bits(RAM_ERR_REPORT + offset);
        offset++;
        // when the last stuffed character was null, we are done
      }while ( (errChar != 0) && (offset < 128) );

      // Eve is unhappy - needs a paddling.
      uint32_t Patch_Add = read32Bits(REG_COPRO_PATCH_PTR + RAM_REG);
      writeBytes(REG_CPU_RESET + RAM_REG, 1, 1);
      writeBytes(REG_CMD_READ + RAM_REG, 1, 0);
      writeBytes(REG_CMD_WRITE + RAM_REG, 1, 0);
      writeBytes(REG_CMD_DL + RAM_REG, 1, 0);
      writeBytes(REG_CPU_RESET + RAM_REG, 1, 0);
      writeBytes(REG_COPRO_PATCH_PTR + RAM_REG, 4, Patch_Add);
    }
  }while( ReadReg != read16Bits(REG_CMD_WRITE + RAM_REG) );
}
