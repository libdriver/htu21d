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
 * @file      driver_htu21d_read_test.c
 * @brief     driver htu21d read test source file
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

#include "driver_htu21d_read_test.h"

static htu21d_handle_t gs_handle;        /**< htu21d handle */

/**
 * @brief     read test
 * @param[in] hold_master_enable is a bool value
 * @param[in] times is test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t htu21d_read_test(htu21d_bool_t hold_master_enable, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    htu21d_info_t info;
    
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
    
    /* htu21d info */
    res = htu21d_info(&info);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        htu21d_interface_debug_print("htu21d: chip is %s.\n", info.chip_name);
        htu21d_interface_debug_print("htu21d: manufacturer is %s.\n", info.manufacturer_name);
        htu21d_interface_debug_print("htu21d: interface is %s.\n", info.interface);
        htu21d_interface_debug_print("htu21d: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        htu21d_interface_debug_print("htu21d: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        htu21d_interface_debug_print("htu21d: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        htu21d_interface_debug_print("htu21d: max current is %0.2fmA.\n", info.max_current_ma);
        htu21d_interface_debug_print("htu21d: max temperature is %0.1fC.\n", info.temperature_max);
        htu21d_interface_debug_print("htu21d: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    htu21d_interface_debug_print("htu21d: start read test.\n");
    
    /* init */
    res = htu21d_init(&gs_handle);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: init failed.\n");
       
        return 1;
    }
    
    /* enable heater */
    res = htu21d_set_heater(&gs_handle, HTU21D_BOOL_TRUE);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set heater failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable otp reload */
    res = htu21d_set_disable_otp_reload(&gs_handle, HTU21D_BOOL_FALSE);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set disable otp reload failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    /* if hold master enable */
    if (hold_master_enable == HTU21D_BOOL_TRUE)
    {
        /* set hold master mode */
        res = htu21d_set_mode(&gs_handle, HTU21D_MODE_HOLD_MASTER);
        if (res != 0)
        {
            htu21d_interface_debug_print("htu21d: set mode failed.\n");
            (void)htu21d_deinit(&gs_handle);
           
            return 1;
        }
        
        /* set hold master mode */
        htu21d_interface_debug_print("htu21d: set hold master mode.\n");
        
        for (i = 0; i < times; i++)
        {
            uint16_t temperature_raw;
            float temperature_s;
            uint16_t humidity_raw;
            float humidity_s;
            
            res = htu21d_read_temperature_humidity(&gs_handle,
                                                   &temperature_raw, &temperature_s,
                                                   &humidity_raw, &humidity_s
                                                  );
            if (res != 0)
            {
                htu21d_interface_debug_print("htu21d: read temperature humidity failed.\n");
                (void)htu21d_deinit(&gs_handle);
               
                return 1;
            }
            
            /* output */
            htu21d_interface_debug_print("htu21d: temperature is %0.2fC.\n", temperature_s);
            htu21d_interface_debug_print("htu21d: humidity is %0.2f%%.\n", humidity_s);
            
            /* delay 2000ms */
            htu21d_interface_delay_ms(2000);
        }
    }
    
    /* set no hold master mode */
    res = htu21d_set_mode(&gs_handle, HTU21D_MODE_NO_HOLD_MASTER);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set mode failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set no hold master mode */
    htu21d_interface_debug_print("htu21d: set no hold master mode.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = htu21d_read_temperature_humidity(&gs_handle,
                                               &temperature_raw, &temperature_s,
                                               &humidity_raw, &humidity_s
                                              );
        if (res != 0)
        {
            htu21d_interface_debug_print("htu21d: read temperature humidity failed.\n");
            (void)htu21d_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        htu21d_interface_debug_print("htu21d: temperature is %0.2fC.\n", temperature_s);
        htu21d_interface_debug_print("htu21d: humidity is %0.2f%%.\n", humidity_s);
        
        /* delay 2000ms */
        htu21d_interface_delay_ms(2000);
    }
    
    /* set resolution temp 11 bits and rh 11 bits */
    htu21d_interface_debug_print("htu21d: set resolution temp 11 bits and rh 11 bits.\n");
    
    /* set resolution temp 11 bits and rh 11 bits */
    res = htu21d_set_resolution(&gs_handle, HTU21D_RESOLUTION_TEMP_11_BITS_RH_11_BITS);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = htu21d_read_temperature_humidity(&gs_handle,
                                               &temperature_raw, &temperature_s,
                                               &humidity_raw, &humidity_s
                                              );
        if (res != 0)
        {
            htu21d_interface_debug_print("htu21d: read temperature humidity failed.\n");
            (void)htu21d_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        htu21d_interface_debug_print("htu21d: temperature is %0.2fC.\n", temperature_s);
        htu21d_interface_debug_print("htu21d: humidity is %0.2f%%.\n", humidity_s);
        
        /* delay 2000ms */
        htu21d_interface_delay_ms(2000);
    }
    
    /* set resolution temp 12 bits and rh 8 bits */
    htu21d_interface_debug_print("htu21d: set resolution temp 12 bits and rh 8 bits.\n");
    
    /* set resolution temp 12 bits and rh 8 bits */
    res = htu21d_set_resolution(&gs_handle, HTU21D_RESOLUTION_TEMP_12_BITS_RH_8_BITS);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = htu21d_read_temperature_humidity(&gs_handle,
                                               &temperature_raw, &temperature_s,
                                               &humidity_raw, &humidity_s
                                              );
        if (res != 0)
        {
            htu21d_interface_debug_print("htu21d: read temperature humidity failed.\n");
            (void)htu21d_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        htu21d_interface_debug_print("htu21d: temperature is %0.2fC.\n", temperature_s);
        htu21d_interface_debug_print("htu21d: humidity is %0.2f%%.\n", humidity_s);
        
        /* delay 2000ms */
        htu21d_interface_delay_ms(2000);
    }
    
    /* set resolution temp 13 bits and rh 10 bits */
    htu21d_interface_debug_print("htu21d: set resolution temp 13 bits and rh 10 bits.\n");
    
    /* set resolution temp 13 bits and rh 10 bits */
    res = htu21d_set_resolution(&gs_handle, HTU21D_RESOLUTION_TEMP_13_BITS_RH_10_BITS);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = htu21d_read_temperature_humidity(&gs_handle,
                                               &temperature_raw, &temperature_s,
                                               &humidity_raw, &humidity_s
                                              );
        if (res != 0)
        {
            htu21d_interface_debug_print("htu21d: read temperature humidity failed.\n");
            (void)htu21d_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        htu21d_interface_debug_print("htu21d: temperature is %0.2fC.\n", temperature_s);
        htu21d_interface_debug_print("htu21d: humidity is %0.2f%%.\n", humidity_s);
        
        /* delay 2000ms */
        htu21d_interface_delay_ms(2000);
    }
    
    /* set resolution temp 14 bits and rh 12 bits */
    htu21d_interface_debug_print("htu21d: set resolution temp 14 bits and rh 12 bits.\n");
    
    /* set resolution temp 14 bits and rh 12 bits */
    res = htu21d_set_resolution(&gs_handle, HTU21D_RESOLUTION_TEMP_14_BITS_RH_12_BITS);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = htu21d_read_temperature_humidity(&gs_handle,
                                               &temperature_raw, &temperature_s,
                                               &humidity_raw, &humidity_s
                                              );
        if (res != 0)
        {
            htu21d_interface_debug_print("htu21d: read temperature humidity failed.\n");
            (void)htu21d_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        htu21d_interface_debug_print("htu21d: temperature is %0.2fC.\n", temperature_s);
        htu21d_interface_debug_print("htu21d: humidity is %0.2f%%.\n", humidity_s);
        
        /* delay 2000ms */
        htu21d_interface_delay_ms(2000);
    }
    
    /* finish read test */
    htu21d_interface_debug_print("htu21d: finish read test.\n");
    (void)htu21d_deinit(&gs_handle);

    return 0;
}
