#include "RGB_SEN.h"


#ifdef ARDUINO
/**
 * @brief Sensor init
 * 
 * @param wire 
 * @return true Init failed
 * @return false Init successful
 */
bool RGB_SEN::begin(TwoWire * wire) {
    _I2C_init(wire, RGB_SEN_DEV_ADDR);
    return _I2C_checkDevAvl();
}

bool RGB_SEN::begin(TwoWire * wire, SD sd, AF af, IT_TIME it_time) {
    _I2C_init(wire, RGB_SEN_DEV_ADDR);
    if (_I2C_checkDevAvl())
        return true;
    else
        config(sd, af, it_time);
}
#endif

void RGB_SEN::config(SD sd, AF af, IT_TIME it_time) {
    uint8_t buff = sd | af | it_time;
    _I2C_write16Bit(0x00, buff, 0x00);
}

void RGB_SEN::trig() {
    uint16_t buff = _I2C_read16Bit_lowFirst(0x00);
    buff = buff | 0B00000100;
    _I2C_write16Bit(0x00, (uint8_t)buff, 0x00);
}