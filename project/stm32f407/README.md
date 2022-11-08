### 1. Chip

#### 1.1 Chip Info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

### 2. Shell

#### 2.1 Shell Parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. HTU21D

#### 3.1 Command Instruction

​           htu21d is a basic command which can test all htu21d driver function:

​           -i        show htu21d chip and driver information.

​           -h       show htu21d help.

​           -p       show htu21d pin connections of the current board.

​           -t (reg | read <times>)

​           -t reg        run htu21d register test.

​           -t read <times>       run htu21d read test. times is test times.

​           -c read <times>      run htu21d read function. times is read times.

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
htu21d -t read 3

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
htu21d: set hold master mode.
htu21d: temperature is 28.41C.
htu21d: humidity is 35.05%.
htu21d: temperature is 29.18C.
htu21d: humidity is 33.70%.
htu21d: temperature is 29.37C.
htu21d: humidity is 33.04%.
htu21d: set no hold master mode.
htu21d: temperature is 29.49C.
htu21d: humidity is 32.78%.
htu21d: temperature is 29.61C.
htu21d: humidity is 32.47%.
htu21d: temperature is 29.66C.
htu21d: humidity is 32.20%.
htu21d: set resolution temp 11 bits and rh 11 bits.
htu21d: temperature is 29.71C.
htu21d: humidity is 32.04%.
htu21d: temperature is 29.78C.
htu21d: humidity is 31.88%.
htu21d: temperature is 29.82C.
htu21d: humidity is 31.78%.
htu21d: set resolution temp 12 bits and rh 8 bits.
htu21d: temperature is 29.88C.
htu21d: humidity is 31.78%.
htu21d: temperature is 29.93C.
htu21d: humidity is 31.74%.
htu21d: temperature is 29.95C.
htu21d: humidity is 31.63%.
htu21d: set resolution temp 13 bits and rh 10 bits.
htu21d: temperature is 30.01C.
htu21d: humidity is 31.58%.
htu21d: temperature is 30.06C.
htu21d: humidity is 31.59%.
htu21d: temperature is 30.08C.
htu21d: humidity is 31.51%.
htu21d: set resolution temp 14 bits and rh 12 bits.
htu21d: temperature is 30.12C.
htu21d: humidity is 31.43%.
htu21d: temperature is 30.13C.
htu21d: humidity is 31.27%.
htu21d: temperature is 30.17C.
htu21d: humidity is 31.11%.
htu21d: finish read test.
```

```shell
htu21d -c read 3

htu21d: 1/3.
htu21d: temperature is 29.17C.
htu21d: humidity is 33.98%.
htu21d: 2/3.
htu21d: temperature is 29.35C.
htu21d: humidity is 33.46%.
htu21d: 3/3.
htu21d: temperature is 29.46C.
htu21d: humidity is 33.10%.
```

```shell
htu21d -h

htu21d -i
	show htu21d chip and driver information.
htu21d -h
	show htu21d help.
htu21d -p
	show htu21d pin connections of the current board.
htu21d -t reg
	run htu21d register test.
htu21d -t read <times>
	run htu21d read test.times is test times.
htu21d -c read <times>
	run htu21d read function.times is read times.
```

