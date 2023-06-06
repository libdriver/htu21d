### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. HTU21D

#### 3.1 Command Instruction

1. Show htu21d chip and driver information.

   ```shell
   htu21d (-i | --information)
   ```

2. Show htu21d help.

   ```shell
   htu21d (-h | --help)
   ```

3. Show htu21d pin connections of the current board.

   ```shell
   htu21d (-p | --port)
   ```

4. Run htu21d register test.

   ```shell
   htu21d (-t reg | --test=reg)
   ```

5. Run htu21d read test, num is test times.

   ```shell
   htu21d (-t read | --test=read) [--times=<num>]
   ```

6. Run htu21d read function, num is read times.

   ```shell
   htu21d (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
htu21d -i

htu21d: chip is TE HTU21D.
htu21d: manufacturer is TE.
htu21d: interface is IIC.
htu21d: driver version is 1.0.
htu21d: min supply voltage is 1.5V.
htu21d: max supply voltage is 3.6V.
htu21d: max current is 0.50mA.
htu21d: max temperature is 125.0C.
htu21d: min temperature is -40.0C.
```

```shell
htu21d -p

htu21d: SCL connected to GPIOB PIN8.
htu21d: SDA connected to GPIOB PIN9.
```

```shell
htu21d -t reg

htu21d: chip is TE HTU21D.
htu21d: manufacturer is TE.
htu21d: interface is IIC.
htu21d: driver version is 1.0.
htu21d: min supply voltage is 1.5V.
htu21d: max supply voltage is 3.6V.
htu21d: max current is 0.50mA.
htu21d: max temperature is 125.0C.
htu21d: min temperature is -40.0C.
htu21d: start register test.
htu21d: htu21d_set_mode/htu21d_get_mode test.
htu21d: set hold master mode.
htu21d: check mode pin ok.
htu21d: set no hold master mode.
htu21d: check mode pin ok.
htu21d: htu21d_set_resolution/htu21d_get_resolution test.
htu21d: set resolution temp 11 bits and rh 11 bits.
htu21d: check resolution ok.
htu21d: set resolution temp 12 bits and rh 8 bits.
htu21d: check resolution ok.
htu21d: set resolution temp 13 bits and rh 10 bits.
htu21d: check resolution ok.
htu21d: set resolution temp 14 bits and rh 12 bits.
htu21d: check resolution ok.
htu21d: htu21d_set_heater/htu21d_get_heater test.
htu21d: enable heater.
htu21d: check heater ok.
htu21d: disable heater.
htu21d: check heater ok.
htu21d: htu21d_set_disable_otp_reload/htu21d_get_disable_otp_reload test.
htu21d: enable otp reload.
htu21d: check otp reload ok.
htu21d: disable otp reload.
htu21d: check otp reload ok.
htu21d: htu21d_get_serial_number test.
htu21d: serial number is 0xDDEECE32114854.
htu21d: htu21d_get_battery_status test.
htu21d: status is 0x00.
htu21d: htu21d_soft_reset test.
htu21d: finish register test.
```

```shell
htu21d -t read --times=3

htu21d: chip is TE HTU21D.
htu21d: manufacturer is TE.
htu21d: interface is IIC.
htu21d: driver version is 1.0.
htu21d: min supply voltage is 1.5V.
htu21d: max supply voltage is 3.6V.
htu21d: max current is 0.50mA.
htu21d: max temperature is 125.0C.
htu21d: min temperature is -40.0C.
htu21d: start read test.
htu21d: set no hold master mode.
htu21d: temperature is 28.91C.
htu21d: humidity is 25.55%.
htu21d: temperature is 29.71C.
htu21d: humidity is 23.42%.
htu21d: temperature is 29.88C.
htu21d: humidity is 22.22%.
htu21d: set resolution temp 11 bits and rh 11 bits.
htu21d: temperature is 29.98C.
htu21d: humidity is 21.71%.
htu21d: temperature is 29.98C.
htu21d: humidity is 20.55%.
htu21d: temperature is 30.08C.
htu21d: humidity is 21.36%.
htu21d: set resolution temp 12 bits and rh 8 bits.
htu21d: temperature is 30.16C.
htu21d: humidity is 20.28%.
htu21d: temperature is 30.20C.
htu21d: humidity is 19.71%.
htu21d: temperature is 30.25C.
htu21d: humidity is 18.98%.
htu21d: set resolution temp 13 bits and rh 10 bits.
htu21d: temperature is 30.27C.
htu21d: humidity is 18.59%.
htu21d: temperature is 30.31C.
htu21d: humidity is 20.58%.
htu21d: temperature is 30.35C.
htu21d: humidity is 24.57%.
htu21d: set resolution temp 14 bits and rh 12 bits.
htu21d: temperature is 30.37C.
htu21d: humidity is 22.48%.
htu21d: temperature is 30.41C.
htu21d: humidity is 20.26%.
htu21d: temperature is 30.42C.
htu21d: humidity is 19.04%.
htu21d: finish read test.
```

```shell
htu21d -e read --times=3

htu21d: 1/3.
htu21d: temperature is 29.56C.
htu21d: humidity is 24.20%.
htu21d: 2/3.
htu21d: temperature is 29.76C.
htu21d: humidity is 23.61%.
htu21d: 3/3.
htu21d: temperature is 29.87C.
htu21d: humidity is 22.41%.
```

```shell
htu21d -h

Usage:
  htu21d (-i | --information)
  htu21d (-h | --help)
  htu21d (-p | --port)
  htu21d (-t reg | --test=reg)
  htu21d (-t read | --test=read) [--times=<num>]
  htu21d (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>    Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                                 Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

