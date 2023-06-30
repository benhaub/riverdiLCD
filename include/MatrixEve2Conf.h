 //User selectable configurations.
//#define EVE_70
//#define EVE_50
//#define EVE_43
//#define EVE_39
//#define EVE_38
#define EVE_35
//#define EVE_29
//#define EVE_40
//#define EVE_101

//Configure for the EVE board version you are using.
//#define EVE2
#define EVE3 // EVE3, EVE3x or EVE4x boards
 
//Configure what touch screen is being used. I no touch screen is used
//comment out the following two lines
#define TOUCH_RESISTIVE
//#define TOUCH_CAPACITIVE

#ifdef EVE_70
#define DWIDTH     800
#define DHEIGHT    480
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     928
#define HOFFSET     88
#define HSYNC0       0
#define HSYNC1      48
#define VCYCLE     525
#define VOFFSET     32
#define VSYNC0       0
#define VSYNC1       3
#define PCLK         2
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      800
#define VSIZE      480
#define CSPREAD      0
#define DITHER       1
#endif

#ifdef EVE_50
#define DWIDTH     800
#define DHEIGHT    480
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     928
#define HOFFSET     88
#define HSYNC0       0
#define HSYNC1      48
#define VCYCLE     525
#define VOFFSET     32
#define VSYNC0       0
#define VSYNC1       3
#define PCLK         2
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      800
#define VSIZE      480
#define CSPREAD      0
#define DITHER       1
#endif

#ifdef EVE_43
#define DWIDTH     480
#define DHEIGHT    272
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     548
#define HOFFSET     43
#define HSYNC0       0
#define HSYNC1      41
#define VCYCLE     292
#define VOFFSET     12
#define VSYNC0       0
#define VSYNC1      10
#define PCLK         5
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      480
#define VSIZE      272
#define CSPREAD      1
#define DITHER       1
#endif

#ifdef EVE_39
#define DWIDTH     480
#define DHEIGHT    128
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     524
#define HOFFSET     16
#define HSYNC1      44
#define HSYNC0       0
#define VCYCLE     288
#define VOFFSET     12
#define VSYNC1       8
#define VSYNC0       7
#define PCLK         5
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      480
#define VSIZE      272
#define CSPREAD      1
#define DITHER       1
#endif

#ifdef EVE_38
#define DWIDTH     480
#define DHEIGHT    116
#define PIXVOFFSET  10
#define PIXHOFFSET   0
#define HCYCLE     524
#define HOFFSET     43
#define HSYNC0       0
#define HSYNC1      41
#define VCYCLE     292
#define VOFFSET     12
#define VSYNC0     152
#define VSYNC1      10
#define PCLK         5
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      480
#define VSIZE      272
#define CSPREAD      1
#define DITHER       1
#endif

#ifdef EVE_35
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

#ifdef EVE_29
#define DWIDTH     320
#define DHEIGHT    102
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     408
#define HOFFSET     70
#define HSYNC0       0
#define HSYNC1      10
#define VCYCLE     262
#define VOFFSET    156
#define VSYNC0       0
#define VSYNC1       2
#define PCLK         8
#define SWIZZLE      0
#define PCLK_POL     0
#define HSIZE      320
#define VSIZE      102
#define CSPREAD      1
#define DITHER       1
#endif

#ifdef EVE_40
#define DWIDTH     720
#define DHEIGHT    720
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     812
#define HOFFSET     91
#define HSYNC0      46
#define HSYNC1      48
#define VCYCLE     756
#define VOFFSET     35
#define VSYNC0      16
#define VSYNC1      18
#define PCLK         2
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      720
#define VSIZE      720
#define CSPREAD      0
#define DITHER       0
#endif

#ifdef EVE_101
#define DWIDTH    1280
#define DHEIGHT    800
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE    1440
#define HOFFSET    158
#define HSYNC0      78
#define HSYNC1      80
#define VCYCLE     823
#define VOFFSET     22
#define VSYNC0      11
#define VSYNC1      12
#define PCLK         1
#define SWIZZLE      0
#define PCLK_POL     0
#define HSIZE     1280
#define VSIZE      800
#define CSPREAD      0
#define DITHER       1
#endif
