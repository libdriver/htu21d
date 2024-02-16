[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver HTU21D

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/htu21d/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

HTU21D(F)는 MEAS에서 온도를 출력하는 새로운 디지털 습도 센서입니다. 크기와 인텔리전스 면에서 새로운 표준을 설정하는 이 제품은 작은 3 x 3 x 0.9mm 실장 면적을 가진 리플로 납땜 가능한 DFN(Dual Flat No Leads) 패키지에 내장되어 있습니다. 이 센서는 디지털 I²C 형식으로 교정되고 선형화된 신호를 제공합니다. HTU21D(F) 디지털 습도 센서는 신뢰할 수 있고 정확한 측정이 필요한 OEM 애플리케이션을 위한 전용 습도 및 온도 플러그 앤 플레이 변환기입니다. 습도 및 온도 디지털 출력용 모듈로 마이크로 컨트롤러와의 직접 인터페이스가 가능합니다. 이 저전력 센서는 공간 제약이 있는 고용량 및 비용에 민감한 애플리케이션을 위해 설계되었습니다. 모든 센서는 개별적으로 교정 및 테스트됩니다. 로트 식별은 센서에 인쇄되고 전자 식별 코드는 명령으로 읽을 수 있는 칩에 저장됩니다. 배터리 부족을 감지할 수 있으며 체크섬은 통신 신뢰성을 향상시킵니다. 이 디지털 습도 센서의 해상도는 명령에 의해 변경될 수 있습니다(RH/T의 경우 8/12bit ~ 12/14bit). 가전 제품, 의료, 프린터, 가습기 등에 사용됩니다.

LibDriver HTU21D는 LibDriver에서 출시한 HTU21D의 전체 기능 드라이버입니다. 온도 및 상대 습도를 읽는 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver HTU21D의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver HTU21D용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver HTU21D드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver HTU21D프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver HTU21D오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 HTU21D데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 IIC버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/htu21d/index.html](https://www.libdriver.com/docs/htu21d/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.