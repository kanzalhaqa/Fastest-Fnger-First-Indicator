#include "DS1307.h"
#include "I2C.h"

#define DS1307_ID 0x00
#define SEC_ADDRESS 0x00
#define DATE_ADDRESS 0x04
#define CONTROL 0x07