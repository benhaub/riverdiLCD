#include "include/bt81x.h"

int main() {
  printf("Hello Riverdi\r\n");
  if (initEve())
    printf("Could not init riverdi display\n\r");
  uint32_t dataRx;
  dataRx = read32Bits(REG_CHIP_ID);
  printf("Chip ID %x\r\n", dataRx);

  ramCommand(CMD_DLSTART);                   //Start a new display list
  ramCommand(VERTEXFORMAT(0));               //setup VERTEX2F to take pixel coordinates
  ramCommand(CLEAR_COLOR_RGB(0, 0, 0));      //Determine the clear screen color
  ramCommand(CLEAR(1, 1, 1));                //Clear the screen and the current display list
  ramCommand(COLOR_RGB(26, 26, 192));        // change colour to blue
  ramCommand(POINT_SIZE(30 * 16));      // set point size to DotSize pixels. Points = (pixels x 16)
  ramCommand(BEGIN(POINTS));                 // start drawing point
  ramCommand(TAG(1));                        // Tag the blue dot with a touch ID
  ramCommand(VERTEX2F(DWIDTH / 2, DHEIGHT / 2));     // place blue point
  ramCommand(END());                         // end drawing point
  ramCommand(COLOR_RGB(255, 255, 255));      //Change color to white for text
  //Cmd_Text(DWIDTH / 2, DHEIGHT / 2, 30, OPT_CENTER, " MATRIX         ORBITAL"); //Write text in the center of the screen
  ramCommand(DISPLAY());                     //End the display list
  ramCommand(CMD_SWAP);                      //Swap commands into RAM
  UpdateFIFO();                            // Trigger the CoProcessor to start processing the FIFO
  exit(0);
}
