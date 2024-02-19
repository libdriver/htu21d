/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_htu21d_basic.h
 * @brief     driver htu21d basic header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-10-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/10/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_HTU21D_BASIC_H
#define DRIVER_HTU21D_BASIC_H

#include "driver_htu21d_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup htu21d_example_driver htu21d example driver function
 * @brief    htu21d example driver modules
 * @ingroup  htu21d_driver
 * @{
 */

/**
 * @brief htu21d basic example default definition
 */
#define HTU21D_BASIC_DEFAULT_MODE              HTU21D_MODE_NO_HOLD_MASTER                       /**< no hold master mode */
#define HTU21D_BASIC_DEFAULT_RESOLUTION        HTU21D_RESOLUTION_TEMP_14_BITS_RH_12_BITS        /**< temp 14 bits and rh 12 bits */
#define HTU21D_BASIC_DEFAULT_HEATER            HTU21D_BOOL_FALSE                                /**< disable heater */
#define HTU21D_BASIC_DEFAULT_OTP_RELOAD        HTU21D_BOOL_FALSE                                /**< enable otp reload */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t htu21d_basic_init(void);

/**
 * @brief      basic example read
 * @param[out] *temperature points to a converted temperature buffer
 * @param[out] *humidity points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t htu21d_basic_read(float *temperature, float *humidity);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t htu21d_basic_deinit(void);

/**
 * @brief      basic example get the serial number
 * @param[out] *number points to a number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial number failed
 * @note       none
 */
uint8_t htu21d_basic_get_serial_number(uint64_t *number);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
