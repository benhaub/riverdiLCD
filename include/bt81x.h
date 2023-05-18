#include "bt81xMemory.h"
#include "tm4c_os.h"
#include "eveConf.h"

/**
 * init the bt81x Embedded Video Engine
 */
uint8_t initEve();
/**
 * Send a host command
 * @see BT81X datasheet, Section 4.1.5 Host Command
 */
void hostCommand(uint8_t address, uint8_t parameter);

// This is like cmd() in (some) Eve docs - sends 32 bits but does not update the write pointer ***
// FT81x Series Programmers Guide Section 5.1.1 - Circular Buffer (AKA "the FIFO" and "Command buffer" and "CoProcessor")
// Don't miss section 5.3 - Interaction with RAM_DL
void ramCommand(uint32_t data);

// UpdateFIFO - Cause the CoProcessor to realize that it has work to do in the form of a
// differential between the read pointer and write pointer.  The CoProcessor (FIFO or "Command buffer") does
// nothing until you tell it that the write position in the FIFO RAM has changed
void UpdateFIFO(void);

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
 * Read bytes starting from address
 * @param address
 *   The address to read from
 * @see Bt81X datasheet, Section 4.1.3 Host Memory Read
 */
uint8_t read8Bits(const uint32_t address);
uint16_t read16Bits(const uint32_t address);
uint32_t read32Bits(const uint32_t address);
