[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver HTU21D

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/htu21d/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The HTU21D(F) is a new digital humidity sensor with temperature output by MEAS. Setting new standards in terms of size and intelligence, it is embedded in a reflow solderable Dual Flat No leads (DFN) package with a small 3 x 3 x 0.9 mm footprint. This sensor provides calibrated, linearized signals in digital, I²C format. HTU21D(F) digital humidity sensors are dedicated humidity and temperature plug and play transducers for OEM applications where reliable and accurate measurements are needed. Direct interface with a micro-controller is made possible with the module for humidity and temperature digital outputs. These low power sensors are designed for high volume and cost sensitive applications with tight space constraints.Every sensor is individually calibrated and tested. Lot identification is printed on the sensor and an electronic identification code is stored on the chip – which can be read out by command. Low battery can be detected and a checksum improves communication reliability. The resolution of these digital humidity sensors can be changed by command (8/12bit up to 12/14bit for RH/T).It is used in Home appliance, medical, printers, humidifier and so on .

LibDriver HTU21D is the full function driver of HTU21D launched by LibDriver.It provides the function of reading temperature and relative humidity. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver HTU21D source files.

/interface includes LibDriver HTU21D IIC platform independent template.

/test includes LibDriver HTU21D driver test code and this code can test the chip necessary function simply.

/example includes LibDriver HTU21D sample code.

/doc includes LibDriver HTU21D offline document.

/datasheet includes HTU21D datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_htu21d_basic.h"

uint8_t res;
uint8_t i;
float temperature;
uint8_t humidity;

res = htu21d_basic_init();
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    htu21d_interface_delay_ms(2000);
    res = htu21d_basic_read((float *)&temperature, (uint8_t *)&humidity);
    if (res != 0)
    {
        (void)htu21d_basic_deinit();

        return 1;
    }
    htu21d_interface_debug_print("htu21d: temperature is %0.2fC.\n", temperature);
    htu21d_interface_debug_print("htu21d: humidity is %d%%.\n", humidity); 
    
    ...
        
}

...

(void)htu21d_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/htu21d/index.html](https://www.libdriver.com/docs/htu21d/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.