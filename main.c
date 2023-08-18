#include "include/Eve2_81x.h"
#include "include/hw_api.h"
#include "include/MatrixEve2Conf.h"

/****************************************************************************
*                             IMPORTANT NOTICE                              *
* Please make sure to configure the display timing values and define what   *
* touch variant you are using in the MatrixEve2Conf.h file.                 *
*                                                                           *
****************************************************************************/

void startupScreen(uint8_t DotSize)
{
  //Start a new display list
	sendCmd(CMD_DLSTART);
  //setup VERTEX2F to take pixel coordinates
	sendCmd(VERTEXFORMAT(0));
  //Determine the clear screen color
	sendCmd(CLEAR_COLOR_RGB(0, 0, 0));
  //Clear the screen and the current display list
	sendCmd(CLEAR(1, 1, 1));
  // change colour to red
	sendCmd(COLOR_RGB(255, 0, 0));
	sendCmd(POINT_SIZE(DotSize * 16));
  // set point size to DotSize pixels. Points = (pixels x 16)
	sendCmd(BEGIN(POINTS));
  // start drawing point
	sendCmd(TAG(1));
  //place point
	sendCmd(VERTEX2F(DWIDTH / 2, DHEIGHT / 2));
  //end drawing point
	sendCmd(END());
  //Change color to white for text
	sendCmd(COLOR_RGB(255, 255, 255));
	Cmd_Text(DWIDTH / 2, DHEIGHT / 2, 30, OPT_CENTER, "TM4C_OS");
  //End the display list
	sendCmd(DISPLAY());
  //Swap commands into RAM
	sendCmd(CMD_SWAP);
  //Trigger the CoProcessor to start processing the FIFO
	updateFifo();
	//isCoProFifoEmpty();
}


// A calibration screen for the touch digitizer 
void Calibrate(void)
{
	Calibrate_Manual(DWIDTH, DHEIGHT, PIXVOFFSET, PIXHOFFSET);
}

// A Clear screen function 
void ClearScreen(void)
{
	sendCmd(CMD_DLSTART);
	sendCmd(CLEAR_COLOR_RGB(0, 0, 0));
	sendCmd(CLEAR(1, 1, 1));
	sendCmd(DISPLAY());
	sendCmd(CMD_SWAP);
  // Trigger the CoProcessor to start processing commands out of the FIFO
	updateFifo();
  // wait here until the coprocessor has read and executed every pending command.	
	isCoProFifoEmpty();
}

int main()
{
  uint32_t chipId;

  HAL_Open();

  //Initialize the EVE graphics controller. Make sure to define which display you are using in the MatrixEveConf.h
  while (!(chipId = bt81xInit()));
  printf("Chip ID = %x\n\r", chipId);

  //Clear any remnants in the RAM
	ClearScreen();

  //If you are using a touch screen, make sure to define what variant you are
  //using in the MatrixEveConf.h file
#ifdef TOUCH_RESISTIVE
  Calibrate();
#endif

  startupScreen(30);
  //Draw the Matrix Orbital Screen
  uint8_t pressed = 0;
  uint32_t tag = 0;

while (1) {
    // Check for touches on the red circle
    //tag = rd8(REG_TOUCH_TAG + RAM_REG);
    tag = rd32(REG_TOUCH_DIRECT_XY + RAM_REG);

    if ((tag & 1<<31) && pressed) {
      pressed = 0;
      startupScreen(30);
    }
    else if (!(tag & 1<<31)) {
      pressed = 1;
      startupScreen(120);
    }
}
  HAL_Close();
  exit(1);
}
