#ifndef _RGB_SEN_H_
#define _RGB_SEN_H_

#include "../I2C_PORT/I2C_PORT.h"
#ifdef ARDUINO
#include <Arduino.h>
#include <Wire.h>
#endif

#define RGB_SEN_DEV_ADDR 0x10

class RGB_SEN : public I2C_PORT {
    public:
        enum SD {
            SEN_ENABLE  = 0B00000000,
            SEN_DISABLE = 0B00000001,
        };
        enum AF {
            AUTO_MODE   = 0B00000000,
            FORCE_MODE  = 0B00000010,
        };
        enum IT_TIME {
            IT_40ms     = 0B00000000,
            IT_80ms     = 0B00010000,
            IT_160ms    = 0B00100000,
            IT_320ms    = 0B00110000,
            IT_640ms    = 0B01000000,
            IT_1280ms   = 0B01010000,
        };
        enum DATA_CHANNEL {
            RED   = 0x08,
            GREEN = 0x09,
            BLUE  = 0x0A,
            WHITE = 0x0B,
        };
        #ifdef ARDUINO
        bool begin(TwoWire * wire);
        bool begin(TwoWire * wire, SD sd, AF af, IT_TIME it_time);
        #endif
        void config(SD sd, AF af, IT_TIME it_time);
        void trig();
        uint16_t getRawData(DATA_CHANNEL data_channel);
};

#endif