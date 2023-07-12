//User selectable configurations.
#define RIVERDI_EVE_35 0
#define MATRIX_ORBITAL_EVE_35 1

//Configure for the EVE board version you are using.
//#define EVE2
#define EVE3 // EVE3, EVE3x or EVE4x boards
 
//Configure what touch screen is being used. I no touch screen is used
//comment out the following two lines
#define TOUCH_RESISTIVE
//#define TOUCH_CAPACITIVE

#if defined(RIVERDI_EVE_35) || defined(MATRIX_ORBITAL_EVE_35)
#define DWIDTH     320
#define DHEIGHT    240
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     408
#define HOFFSET     68
#define HSYNC0       0
#define HSYNC1      10
#define VCYCLE     262
#define VOFFSET     18
#define VSYNC0       0
#define VSYNC1       2
#define PCLK         8
#define SWIZZLE      0
#define PCLK_POL     0
#define HSIZE      320
#define VSIZE      240
#define CSPREAD      1
#define DITHER       1
#endif
