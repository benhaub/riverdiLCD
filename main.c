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
	Send_CMD(CMD_DLSTART);
  //setup VERTEX2F to take pixel coordinates
	Send_CMD(VERTEXFORMAT(0));
  //Determine the clear screen color
	Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));
  //Clear the screen and the current display list
	Send_CMD(CLEAR(1, 1, 1));
  // change colour to red
	Send_CMD(COLOR_RGB(255, 0, 0));
	Send_CMD(POINT_SIZE(DotSize * 16));
  // set point size to DotSize pixels. Points = (pixels x 16)
	Send_CMD(BEGIN(POINTS));
  // start drawing point
	Send_CMD(TAG(1));
  //place point
	Send_CMD(VERTEX2F(DWIDTH / 2, DHEIGHT / 2));
  //end drawing point
	Send_CMD(END());
  //Change color to white for text
	Send_CMD(COLOR_RGB(255, 255, 255));
	Cmd_Text(DWIDTH / 2, DHEIGHT / 2, 30, OPT_CENTER, " TM4C_OS ");
  //End the display list
	Send_CMD(DISPLAY());
  //Swap commands into RAM
	Send_CMD(CMD_SWAP);
  //Trigger the CoProcessor to start processing the FIFO
	UpdateFIFO();
}


// A calibration screen for the touch digitizer 
void Calibrate(void)
{
	//Calibrate_Manual(DWIDTH, DHEIGHT, PIXVOFFSET, PIXHOFFSET);
}

// A Clear screen function 
void ClearScreen(void)
{
	Send_CMD(CMD_DLSTART);
	Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));
	Send_CMD(CLEAR(1, 1, 1));
	Send_CMD(DISPLAY());
	Send_CMD(CMD_SWAP);
  // Trigger the CoProcessor to start processing commands out of the FIFO
	UpdateFIFO();
  // wait here until the coprocessor has read and executed every pending command.	
	Wait4CoProFIFOEmpty();
	HAL_Delay(10);
}

int main()
{
  uint32_t chipId;
  HAL_Open();
  //Initialize the EVE graphics controller. Make sure to define which display you are using in the MatrixEveConf.h
  while (!(chipId = FT81x_Init()));
  printf("Chip ID = %x\n\r", chipId);
  //Clear any remnants in the RAM
	ClearScreen();
  printf("Done initializing bt81x.\n\r");

  //If you are using a touch screen, make sure to define what variant you are
  //using in the MatrixEveConf.h file
#ifdef TOUCH_RESISTIVE
  Calibrate();
#endif

  //Draw the Matrix Orbital Screen
  startupScreen(30);
  uint8_t pressed = 0;

  while (1)
  {
    // Check for touches
    uint8_t Tag = rd8(REG_TOUCH_TAG + RAM_REG);
    switch (Tag)
    {
      case 1:
        if (!pressed)
        {
          //Blue dot is 120 when not touched
          startupScreen(120);
          pressed = 1;
        }
        break;
      default:
        if (pressed)
        {
          pressed = 0;
          //Blue dot size is 30 when not touched
          startupScreen(30);
        }
        break;
    }
  }
  HAL_Close();
  exit(1);
}
