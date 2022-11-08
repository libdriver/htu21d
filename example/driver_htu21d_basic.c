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
 * @file      driver_htu21d_basic.c
 * @brief     driver htu21d basic source file
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

#include "driver_htu21d_basic.h"

static htu21d_handle_t gs_handle;        /**< htu21d handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t htu21d_basic_init(void)
{
    uint8_t res;
    
    /* link functions */
    DRIVER_HTU21D_LINK_INIT(&gs_handle, htu21d_handle_t);
    DRIVER_HTU21D_LINK_IIC_INIT(&gs_handle, htu21d_interface_iic_init);
    DRIVER_HTU21D_LINK_IIC_DEINIT(&gs_handle, htu21d_interface_iic_deinit);
    DRIVER_HTU21D_LINK_IIC_WRITE_CMD(&gs_handle, htu21d_interface_iic_write_cmd);
    DRIVER_HTU21D_LINK_IIC_READ_CMD(&gs_handle, htu21d_interface_iic_read_cmd);
    DRIVER_HTU21D_LINK_IIC_WRITE(&gs_handle, htu21d_interface_iic_write);
    DRIVER_HTU21D_LINK_IIC_READ(&gs_handle, htu21d_interface_iic_read);
    DRIVER_HTU21D_LINK_IIC_READ_WITH_SCL(&gs_handle, htu21d_interface_iic_read_with_scl);
    DRIVER_HTU21D_LINK_DELAY_MS(&gs_handle, htu21d_interface_delay_ms);
    DRIVER_HTU21D_LINK_DEBUG_PRINT(&gs_handle, htu21d_interface_debug_print);

    /* htu21d init */
    res = htu21d_init(&gs_handle);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: init failed.\n");
        
        return 1;
    }
    
    /* set default mode */
    res = htu21d_set_mode(&gs_handle, HTU21D_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set mode failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default resolution */
    res = htu21d_set_resolution(&gs_handle, HTU21D_BASIC_DEFAULT_RESOLUTION);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default heater */
    res = htu21d_set_heater(&gs_handle, HTU21D_BASIC_DEFAULT_HEATER);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set heater failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default otp reload */
    res = htu21d_set_disable_otp_reload(&gs_handle, HTU21D_BASIC_DEFAULT_OTP_RELOAD);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set disable otp reload failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *temperature points to a converted temperature buffer
 * @param[out] *humidity points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t htu21d_basic_read(float *temperature, float *humidity)
{
    uint16_t temperature_raw;
    uint16_t humidity_raw;
   
    /* read data */
    if (htu21d_read_temperature_humidity(&gs_handle, (uint16_t *)&temperature_raw, temperature,
                                        (uint16_t *)&humidity_raw, humidity) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t htu21d_basic_deinit(void)
{
    /* close htu21d */
    if (htu21d_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief      basic example get the serial number
 * @param[out] *number points to a number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial number failed
 * @note       none
 */
uint8_t htu21d_basic_get_serial_number(uint64_t *number)
{
    /* get the serial number */
    if (htu21d_get_serial_number(&gs_handle, number) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
