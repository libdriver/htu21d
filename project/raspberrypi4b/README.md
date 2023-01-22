### 1. Board

#### 1.1 Board Info

Chip Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(htu21d REQUIRED)
```


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
./htu21d -i

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
./htu21d -p

htu21d: SCL connected to GPIO3(BCM).
htu21d: SDA connected to GPIO2(BCM).
```

```shell
./htu21d -t reg

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
./htu21d -t read --times=3

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
htu21d: temperature is 29.66C.
htu21d: humidity is 19.95%.
htu21d: temperature is 30.36C.
htu21d: humidity is 18.47%.
htu21d: temperature is 30.48C.
htu21d: humidity is 17.69%.
htu21d: set resolution temp 11 bits and rh 11 bits.
htu21d: temperature is 30.55C.
htu21d: humidity is 19.40%.
htu21d: temperature is 30.62C.
htu21d: humidity is 18.85%.
htu21d: temperature is 30.65C.
htu21d: humidity is 18.06%.
htu21d: set resolution temp 12 bits and rh 8 bits.
htu21d: temperature is 30.66C.
htu21d: humidity is 19.21%.
htu21d: temperature is 30.69C.
htu21d: humidity is 20.22%.
htu21d: temperature is 30.71C.
htu21d: humidity is 18.25%.
htu21d: set resolution temp 13 bits and rh 10 bits.
htu21d: temperature is 30.70C.
htu21d: humidity is 17.51%.
htu21d: temperature is 30.70C.
htu21d: humidity is 17.58%.
htu21d: temperature is 30.74C.
htu21d: humidity is 17.72%.
htu21d: set resolution temp 14 bits and rh 12 bits.
htu21d: temperature is 30.74C.
htu21d: humidity is 17.69%.
htu21d: temperature is 30.75C.
htu21d: humidity is 17.59%.
htu21d: temperature is 30.76C.
htu21d: humidity is 17.62%.
htu21d: finish read test.
```

```shell
./htu21d -e read --times=3

htu21d: 1/3.
htu21d: temperature is 29.19C.
htu21d: humidity is 20.62%.
htu21d: 2/3.
htu21d: temperature is 29.36C.
htu21d: humidity is 19.94%.
htu21d: 3/3.
htu21d: temperature is 29.45C.
htu21d: humidity is 19.39%.
```

```shell
./htu21d -h

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

