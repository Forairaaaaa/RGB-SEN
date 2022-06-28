# Arduino lib for RGBW color sensor
Arduino lib for VEML6040

#### 目前支持：

- VEML6040

#### 示例：

```c++
#include "Wire.h"
#include "RGB_SEN.h"

...
    
RGB_SEN rgbs;

/* Init color sensor */
Wire.begin();
rgbs.begin(&Wire);

/* Config color sensor */
rgbs.config(RGB_SEN::SEN_ENABLE, RGB_SEN::AUTO_MODE, RGB_SEN::IT_160ms);

/* Get color data */
Serial.println(rgbs.getLux(RGB_SEN::GREEN));
Serial.println(rgbs.getRawData(RGB_SEN::BLUE));

...

```

#### 参考链接：

- [VEML6040A3OG)](https://item.szlcsc.com/79600.html)

