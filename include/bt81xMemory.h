#define __RAM_G 0x0
#define RAM_G__ 0x0FFFFF
#define RAM_G_SIZE_BYTES (RAM_G__ - __RAM_G)

#define __ROM_FRONT 0x1E0000
#define ROM_FRONT__ 0x2FFFFB
#define ROM_FRONT_SIZE_BYTES (ROM_FRONT__ - __ROM_FRONT)

#define __RAM_DL 0x300000
#define RAM_DL__ 0x301FFF
#define RAM_DL_SIZE_BYTES (__RAM_DL - RAM_DL__)

#define __RAM_REG 0x302000
#define RAM_REG__ 0x302FFF
#define RAM_REG_SIZE_BYTES (__RAM_REG - RAM_REG__)

#define __RAM_CMD 0x308000
#define RAM_CMD__ 0x308FFF
#define RAM_CMD_SIZE_BYTES (__RAM_CMD - RAM_CMD__)

#define __RAM_ERR_REPORT 0x309800
#define RAM_ERR_REPORT__ 0x3098FF
#define RAM_ERR_REPORT_SIZE_BYTES (__RAM_ERR_REPORT - RAM_ERR_REPORT__)

#define __FLASH 0x800000
//TODO: How big is flash?
#define FLASH__ 
