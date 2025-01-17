#include <Arduino.h>

extern "C" {
  #include "gpio_tpi.h"
}; 

// ATTiny10 firmware
static const uint8_t tiny10_bin[] = {
    0x0A, 0xC0, 0x11, 0xC0, 0x10, 0xC0, 0x0F, 0xC0, 0x0E, 0xC0, 0x0D, 0xC0, 0x0C, 0xC0, 0x0B, 0xC0,
    0x0A, 0xC0, 0x09, 0xC0, 0x08, 0xC0, 0x11, 0x27, 0x1F, 0xBF, 0xCF, 0xE5, 0xD0, 0xE0, 0xDE, 0xBF,
    0xCD, 0xBF, 0xB3, 0xD0, 0xB5, 0xC0, 0xEC, 0xCF, 0x0A, 0x9A, 0x12, 0x9A, 0x08, 0x95, 0x12, 0x98,
    0x4D, 0xE2, 0x4A, 0x95, 0xF1, 0xF7, 0x48, 0xE0, 0x50, 0xE0, 0x7C, 0xE2, 0x80, 0xFF, 0x0D, 0xC0,
    0x12, 0x9A, 0x86, 0x95, 0x67, 0x2F, 0x6A, 0x95, 0xF1, 0xF7, 0x41, 0x50, 0x51, 0x0B, 0xB1, 0xF7,
    0x12, 0x9A, 0x4D, 0xE2, 0x4A, 0x95, 0xF1, 0xF7, 0x08, 0x95, 0x12, 0x98, 0xF2, 0xCF, 0x2F, 0x93,
    0x3F, 0x93, 0xCF, 0x93, 0xDF, 0x93, 0xCD, 0xB7, 0xDE, 0xB7, 0x26, 0x2F, 0x34, 0x2F, 0x80, 0x57,
    0xDE, 0xDF, 0x82, 0x2F, 0xDC, 0xDF, 0x83, 0x2F, 0xDF, 0x91, 0xCF, 0x91, 0x3F, 0x91, 0x2F, 0x91,
    0xD6, 0xCF, 0x45, 0xE0, 0x49, 0xBF, 0x48, 0xED, 0x4C, 0xBF, 0x17, 0xBF, 0x4C, 0xBF, 0x16, 0xBF,
    0xCB, 0xCF, 0x4F, 0xE7, 0x64, 0xE2, 0x89, 0xE0, 0xE2, 0xDF, 0x4F, 0xEF, 0x50, 0xE7, 0x62, 0xE0,
    0x41, 0x50, 0x50, 0x40, 0x60, 0x40, 0xE1, 0xF7, 0x00, 0xC0, 0x00, 0x00, 0x4F, 0xE7, 0x6A, 0xE2,
    0x89, 0xE0, 0xD5, 0xDF, 0x4F, 0xEF, 0x50, 0xE7, 0x62, 0xE0, 0x41, 0x50, 0x50, 0x40, 0x60, 0x40,
    0xE1, 0xF7, 0x00, 0xC0, 0x00, 0x00, 0x4F, 0xE7, 0x66, 0xE2, 0x89, 0xE0, 0xC8, 0xDF, 0x4F, 0xEF,
    0x50, 0xE7, 0x62, 0xE0, 0x41, 0x50, 0x50, 0x40, 0x60, 0x40, 0xE1, 0xF7, 0x00, 0xC0, 0x00, 0x00,
    0x4F, 0xE7, 0x6A, 0xE2, 0x89, 0xE0, 0xBB, 0xDF, 0x4F, 0xEF, 0x50, 0xE7, 0x62, 0xE0, 0x41, 0x50,
    0x50, 0x40, 0x60, 0x40, 0xE1, 0xF7, 0x00, 0xC0, 0x00, 0x00, 0x08, 0x95, 0x6F, 0x93, 0x2F, 0x93,
    0x60, 0xE8, 0x28, 0x2F, 0x26, 0x23, 0x10, 0x9A, 0x11, 0xF4, 0x10, 0x98, 0x02, 0xC0, 0x10, 0x9A,
    0x00, 0x00, 0x10, 0x98, 0x66, 0x95, 0xA9, 0xF7, 0x2F, 0x91, 0x6F, 0x91, 0x08, 0x95, 0x6F, 0x93,
    0x2F, 0x93, 0x60, 0xE8, 0x28, 0x2F, 0x26, 0x23, 0x12, 0x9A, 0x11, 0xF4, 0x12, 0x98, 0x02, 0xC0,
    0x12, 0x9A, 0x00, 0x00, 0x12, 0x98, 0x66, 0x95, 0xA9, 0xF7, 0x2F, 0x91, 0x6F, 0x91, 0x08, 0x95,
    0x2F, 0x93, 0x3F, 0x93, 0x8A, 0x32, 0x58, 0xF4, 0x90, 0xE0, 0x28, 0x2F, 0x39, 0x2F, 0x88, 0x0F,
    0x99, 0x1F, 0x88, 0x0F, 0x99, 0x1F, 0x22, 0x0F, 0x33, 0x1F, 0x82, 0x0F, 0x13, 0xC0, 0x87, 0xFF,
    0x0E, 0xC0, 0x8A, 0x3A, 0x70, 0xF4, 0x28, 0x2F, 0x30, 0xE0, 0x20, 0x58, 0x88, 0x27, 0x38, 0x0B,
    0x82, 0x2F, 0x88, 0x0F, 0x22, 0x0F, 0x22, 0x0F, 0x82, 0x0F, 0x80, 0x95, 0x03, 0xC0, 0x8F, 0xEF,
    0x01, 0xC0, 0x80, 0xE0, 0x3F, 0x91, 0x2F, 0x91, 0x08, 0x95, 0x7B, 0xDF, 0x82, 0xDF, 0xFE, 0xCF,
    0xF8, 0x94, 0xFF, 0xCF
};

int Init( const char * code )
{
	int initcode = TPIInit();
	if( initcode < 0 )
	{
	  printf( "Error: Cannot connect to ATTiny (Error %d)\n", initcode );
    return initcode;
	}
  	char initcodesat[10];
	sprintf( initcodesat, "%06x", initcode );
	if( memcmp( code, initcodesat, 6 ) != 0 )
	{
		printf( "Error: Device code mismatch.  Expected: \"%s\", got \"%s\"\n", code, initcodesat ); 
    return initcode;
	}
  return 0;
}


void setup() {
  // Start the TPI session
  Init( "1e9003" ); // Tiny10

  // Erase and write the firmware
  TPIEraseAndWriteAllFlash( tiny10_bin, sizeof(tiny10_bin), 0 );

  // End the TPI session
  TPIEnd();
}

void loop() {
}
