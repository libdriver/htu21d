[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver HTU21D

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/htu21d/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

HTU21D（F）是一種新型的數位濕度感測器，它在尺寸和智慧方面樹立了新的標準，它被嵌入到一個3 x 3 x 0.9 mm可回流焊接的雙扁平無引線（DFN）封裝中。 該感測器提供數位I²C格式的校準線性化訊號。 HTU21D（F）數位濕度感測器是專門的濕度和溫度隨插即用感測器，適用於需要可靠和準確量測的OEM應用。 濕度和溫度數位輸出模組可與微控制器直接相連。 這些低功率感測器設計用於具有緊湊空間限制的高容量和成本敏感應用。 每個感測器都經過單獨校準和測試。 批次標識列印在感測器上，電子標識碼存儲在晶片上，可通過命令讀取。 數位濕度感測器的分辯率可以通過命令更改（RH/T為8/12bit至12/14bit）。 它被用於家用電器、醫療、打印機、加濕器等。

LibDriver HTU21D是LibDriver推出的HTU21D全功能驅動，該驅動提供溫度、相對濕度讀取的功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver HTU21D的源文件。

/interface目錄包含了LibDriver HTU21D與平台無關的IIC總線模板。

/test目錄包含了LibDriver HTU21D驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver HTU21D編程範例。

/doc目錄包含了LibDriver HTU21D離線文檔。

/datasheet目錄包含了HTU21D數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/htu21d/index.html](https://www.libdriver.com/docs/htu21d/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
