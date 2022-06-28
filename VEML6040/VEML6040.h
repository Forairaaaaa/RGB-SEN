#ifndef _VEML6040_H_
#define _VEML6040_H_

#include "../I2C_PORT/I2C_PORT.h"
#ifdef ARDUINO
#include <Arduino.h>
#include <Wire.h>
#endif

/* I2C address of RGB sensor */
#define RGB_SEN_DEV_ADDR 0x10

/* RGB sensor class */
class RGB_SEN:public I2C_PORT {
    public:
        /* Sensor enable or disable */
        enum SD {
            SEN_ENABLE  = 0B00000000,
            SEN_DISABLE = 0B00000001,
        };
        /* Sensor work mode */
        enum AF {
            AUTO_MODE  = 0B00000000,
            FORCE_MODE = 0B00000010,
        };
        /* Sensor integration time */
        enum IT_TIME {
            IT_40ms   = 0B00000000,
            IT_80ms   = 0B00010000,
            IT_160ms  = 0B00100000,
            IT_320ms  = 0B00110000,
            IT_640ms  = 0B01000000,
            IT_1280ms = 0B01010000,
        };
        /* Sensor data channel */
        enum DATA_CHANNEL {
            RED   = 0x08,
            GREEN = 0x09,
            BLUE  = 0x0A,
            WHITE = 0x0B,
        };
        /* Public functions */
        #ifdef ARDUINO
        bool     begin(TwoWire * wire, AF af = AUTO_MODE, IT_TIME it_time = IT_160ms);
        #endif
        void     config(SD sd, AF af, IT_TIME it_time);
        void     trig();
        uint16_t getRawData(DATA_CHANNEL data_channel);
        double   getLux(DATA_CHANNEL data_channel);
    private:
        /* Sensor G sensitivity */
        double   _G_SENSITIVITY;
        /* Private functions */
        void     _updateGSEN(IT_TIME it_time);
};

#endif