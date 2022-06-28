#include "VEML6040.h"


/* Public functions */
#ifdef ARDUINO
/**
 * @brief RGB sensor init
 * 
 * @param wire Wire pointer
 * @param af Sensor work mode
 * @param it_time Integration time 
 * @return true : Init error
 * @return false 
 */
bool RGB_SEN::begin(TwoWire * wire, AF af, IT_TIME it_time) {
    _I2C_init(wire, RGB_SEN_DEV_ADDR);
    if (_I2C_checkDevAvl())
        return true;
    else
        config(SEN_ENABLE, af, it_time);
    return false;
}
#endif

/**
 * @brief RGB sensor config
 * 
 * @param sd Sensor enable
 * @param af Sensor work mode
 * @param it_time Integration time 
 */
void RGB_SEN::config(SD sd, AF af, IT_TIME it_time) {
    _updateGSEN(it_time);
    uint8_t buff = sd | af | it_time;
    _I2C_write16Bit(0x00, buff, 0x00);
}

/**
 * @brief RGB sensor triger
 * 
 */
void RGB_SEN::trig() {
    uint16_t buff = _I2C_read16Bit_lowFirst(0x00);
    buff = buff | 0B00000100;
    _I2C_write16Bit(0x00, (uint8_t)buff, 0x00);
}

/**
 * @brief Get RGB sensor raw data
 * 
 * @param data_channel RGBW channel
 * @return uint16_t Raw data
 */
uint16_t RGB_SEN::getRawData(DATA_CHANNEL data_channel) {
    return _I2C_read16Bit_lowFirst(data_channel);
}

/**
 * @brief Get RGB sensor Lux data
 * 
 * @param data_channel RGBW channel
 * @return double Lux data
 */
double RGB_SEN::getLux(DATA_CHANNEL data_channel) {
    uint16_t rawData = _I2C_read16Bit_lowFirst(data_channel);
    return rawData * _G_SENSITIVITY;
}


/* Private functions */
/**
 * @brief Update sensitivity
 * 
 * @param it_time Integration time 
 */
void RGB_SEN::_updateGSEN(IT_TIME it_time) {
    switch (it_time) {
        case IT_40ms:
            _G_SENSITIVITY = 0.25168;
            break;
        case IT_80ms:
            _G_SENSITIVITY = 0.12584;
            break;
        case IT_160ms:
            _G_SENSITIVITY = 0.06292;
            break;
        case IT_320ms:
            _G_SENSITIVITY = 0.03146;
            break;
        case IT_640ms:
            _G_SENSITIVITY = 0.01573;
            break;
        case IT_1280ms:
            _G_SENSITIVITY = 0.007865;
            break;
        default:
            _G_SENSITIVITY = 0.1;
            break;
    }
}
