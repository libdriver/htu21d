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
 * @file      driver_htu21d_register_test.c
 * @brief     driver htu21d register test source file
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
 
#include "driver_htu21d_register_test.h"

static htu21d_handle_t gs_handle;        /**< htu21d handle */

/**
 * @brief     register test
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t htu21d_register_test(void)
{
    uint8_t res;
    htu21d_info_t info;
    htu21d_mode_t mode;
    htu21d_resolution_t resolution;
    htu21d_bool_t enable;
    uint64_t number;
    htu21d_status_t status;
    
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
    
    /* start register test */
    htu21d_interface_debug_print("htu21d: start register test.\n");
    
    /* init */
    res = htu21d_init(&gs_handle);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: init failed.\n");
       
        return 1;
    }
    
    /* htu21d_set_mode/htu21d_get_mode test */
    htu21d_interface_debug_print("htu21d: htu21d_set_mode/htu21d_get_mode test.\n");
    
    /* hold master mode */
    res = htu21d_set_mode(&gs_handle, HTU21D_MODE_HOLD_MASTER);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set mode failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set hold master mode */
    htu21d_interface_debug_print("htu21d: set hold master mode.\n");
    
    /* get mode */
    res = htu21d_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get mode failed.\n");
        (void)htu21d_deinit(&gs_handle);
       
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check mode pin %s.\n", (HTU21D_MODE_HOLD_MASTER == mode) ? "ok" : "error");
    
    /* no hold master mode */
    res = htu21d_set_mode(&gs_handle, HTU21D_MODE_NO_HOLD_MASTER);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set mode failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set hold master mode */
    htu21d_interface_debug_print("htu21d: set no hold master mode.\n");
    
    /* get mode */
    res = htu21d_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get mode failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check mode pin %s.\n", (HTU21D_MODE_NO_HOLD_MASTER == mode) ? "ok" : "error");
    
    /* htu21d_set_resolution/htu21d_get_resolution test */
    htu21d_interface_debug_print("htu21d: htu21d_set_resolution/htu21d_get_resolution test.\n");
    
    /* set resolution temp 11 bits and rh 11 bits */
    res = htu21d_set_resolution(&gs_handle, HTU21D_RESOLUTION_TEMP_11_BITS_RH_11_BITS);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set resolution temp 11 bits and rh 11 bits */
    htu21d_interface_debug_print("htu21d: set resolution temp 11 bits and rh 11 bits.\n");
    
    /* get resolution */
    res = htu21d_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check resolution %s.\n", (HTU21D_RESOLUTION_TEMP_11_BITS_RH_11_BITS == resolution) ? "ok" : "error");
    
    /* set resolution temp 12 bits and rh 8 bits */
    res = htu21d_set_resolution(&gs_handle, HTU21D_RESOLUTION_TEMP_12_BITS_RH_8_BITS);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set resolution temp 12 bits and rh 8 bits */
    htu21d_interface_debug_print("htu21d: set resolution temp 12 bits and rh 8 bits.\n");
    
    /* get resolution */
    res = htu21d_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check resolution %s.\n", (HTU21D_RESOLUTION_TEMP_12_BITS_RH_8_BITS == resolution) ? "ok" : "error");
    
    /* set resolution temp 13 bits and rh 10 bits */
    res = htu21d_set_resolution(&gs_handle, HTU21D_RESOLUTION_TEMP_13_BITS_RH_10_BITS);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set resolution temp 13 bits and rh 10 bits */
    htu21d_interface_debug_print("htu21d: set resolution temp 13 bits and rh 10 bits.\n");
    
    /* get resolution */
    res = htu21d_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check resolution %s.\n", (HTU21D_RESOLUTION_TEMP_13_BITS_RH_10_BITS == resolution) ? "ok" : "error");
    
    /* set resolution temp 14 bits and rh 12 bits */
    res = htu21d_set_resolution(&gs_handle, HTU21D_RESOLUTION_TEMP_14_BITS_RH_12_BITS);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set resolution temp 14 bits and rh 12 bits */
    htu21d_interface_debug_print("htu21d: set resolution temp 14 bits and rh 12 bits.\n");
    
    /* get resolution */
    res = htu21d_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get resolution failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check resolution %s.\n", (HTU21D_RESOLUTION_TEMP_14_BITS_RH_12_BITS == resolution) ? "ok" : "error");
    
    /* htu21d_set_heater/htu21d_get_heater test */
    htu21d_interface_debug_print("htu21d: htu21d_set_heater/htu21d_get_heater test.\n");
    
    /* enable heater */
    res = htu21d_set_heater(&gs_handle, HTU21D_BOOL_TRUE);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set heater failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable heater */
    htu21d_interface_debug_print("htu21d: enable heater.\n");
    
    /* get the heater status */
    res = htu21d_get_heater(&gs_handle, &enable);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get heater failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check heater %s.\n", (HTU21D_BOOL_TRUE == enable) ? "ok" : "error");
    
    /* disable heater */
    res = htu21d_set_heater(&gs_handle, HTU21D_BOOL_FALSE);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set heater failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable heater */
    htu21d_interface_debug_print("htu21d: disable heater.\n");
    
    /* get the heater status */
    res = htu21d_get_heater(&gs_handle, &enable);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get heater failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check heater %s.\n", (HTU21D_BOOL_FALSE == enable) ? "ok" : "error");
    
    /* htu21d_set_disable_otp_reload/htu21d_get_disable_otp_reload test */
    htu21d_interface_debug_print("htu21d: htu21d_set_disable_otp_reload/htu21d_get_disable_otp_reload test.\n");
    
    /* enable otp reload */
    res = htu21d_set_disable_otp_reload(&gs_handle, HTU21D_BOOL_FALSE);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set disable otp reload failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable otp reload */
    htu21d_interface_debug_print("htu21d: enable otp reload.\n");
    
    /* get disable otp reload */
    res = htu21d_get_disable_otp_reload(&gs_handle, &enable);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get disable otp reload failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check otp reload %s.\n", (HTU21D_BOOL_FALSE == enable) ? "ok" : "error");
    
    /* disable otp reload */
    res = htu21d_set_disable_otp_reload(&gs_handle, HTU21D_BOOL_TRUE);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: set disable otp reload failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable otp reload */
    htu21d_interface_debug_print("htu21d: disable otp reload.\n");
    
    /* get disable otp reload */
    res = htu21d_get_disable_otp_reload(&gs_handle, &enable);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get disable otp reload failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    htu21d_interface_debug_print("htu21d: check otp reload %s.\n", (HTU21D_BOOL_TRUE == enable) ? "ok" : "error");
    
    /* htu21d_get_serial_number test */
    htu21d_interface_debug_print("htu21d: htu21d_get_serial_number test.\n");
    
    /* get serial number */
    res = htu21d_get_serial_number(&gs_handle, &number);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get serial number failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    htu21d_interface_debug_print("htu21d: serial number is 0x%0llX.\n", number);
    
    /* htu21d_get_battery_status test */
    htu21d_interface_debug_print("htu21d: htu21d_get_battery_status test.\n");
    
    /* get battery status */
    res =htu21d_get_battery_status(&gs_handle, &status);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: get battery status failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    htu21d_interface_debug_print("htu21d: status is 0x%02X.\n", status);
    
    /* htu21d_soft_reset test */
    htu21d_interface_debug_print("htu21d: htu21d_soft_reset test.\n");
    
    /* soft reset */
    res = htu21d_soft_reset(&gs_handle);
    if (res != 0)
    {
        htu21d_interface_debug_print("htu21d: soft reset failed.\n");
        (void)htu21d_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish register test */
    htu21d_interface_debug_print("htu21d: finish register test.\n");
    (void)htu21d_deinit(&gs_handle);
    
    return 0;
}
