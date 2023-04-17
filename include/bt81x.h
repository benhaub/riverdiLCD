#include "bt81xMemory.h"
#include "tm4c_os.h"

/**
 * init the bt81x Embedded Video Engine
 */
uint8_t initEve();

/**
 * Read bytes starting from address
 * @param address
 *   The address to read from
 * @see Bt81X datasheet, Section 4.1.3 Host Memory Read
 */
uint8_t read8Bits(const uint32_t address);
uint16_t read16Bits(const uint32_t address);
uint32_t read32Bits(const uint32_t address);

/**
 * Write data to address
 * @param address
 *   The address to write to
 * @param numBytes
 *   The number of bytes to write
 * @see BT81X datasheet, Section 4.1.4 Host Memory Write
 */
void writeBytes(const uint32_t address, const uint8_t numBytes, uint32_t data);

/**
 * Send a host command
 * @see BT81X datasheet, Section 4.1.5 Host Command
 */
void hostCommand(uint8_t address, uint8_t parameter);
uint8_t hostMemoryRead(uint32_t address);
