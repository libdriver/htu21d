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
 * @file      driver_htu21d.h
 * @brief     driver htu21d header file
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

#ifndef DRIVER_HTU21D_H
#define DRIVER_HTU21D_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup htu21d_driver htu21d driver function
 * @brief    htu21d driver modules
 * @{
 */

/**
 * @addtogroup htu21d_base_driver
 * @{
 */

/**
 * @brief htu21d bool enumeration definition
 */
typedef enum
{
    HTU21D_BOOL_FALSE = 0x00,        /**< false */
    HTU21D_BOOL_TRUE  = 0x01,        /**< true */
} htu21d_bool_t;

/**
 * @brief htu21d mode enumeration definition
 */
typedef enum
{
    HTU21D_MODE_HOLD_MASTER    = 0x00,        /**< hold master mode */
    HTU21D_MODE_NO_HOLD_MASTER = 0x01,        /**< no hold master mode */
} htu21d_mode_t;

/**
 * @brief htu21d status enumeration definition
 */
typedef enum
{
    HTU21D_STATUS_OVER_2P25 = 0x00,        /**< >2.25V */
    HTU21D_STATUS_LESS_2P25 = 0x01,        /**< <2.25V */
} htu21d_status_t;

/**
 * @brief htu21d resolution enumeration definition
 */
typedef enum
{
    HTU21D_RESOLUTION_TEMP_11_BITS_RH_11_BITS = 0x03,        /**< temp 11 bits and rh 11 bits */
    HTU21D_RESOLUTION_TEMP_12_BITS_RH_8_BITS  = 0x01,        /**< temp 12 bits and rh 8 bits */
    HTU21D_RESOLUTION_TEMP_13_BITS_RH_10_BITS = 0x02,        /**< temp 13 bits and rh 10 bits */
    HTU21D_RESOLUTION_TEMP_14_BITS_RH_12_BITS = 0x00,        /**< temp 14 bits and rh 12 bits */
} htu21d_resolution_t;

/**
 * @brief htu21d handle structure definition
 */
typedef struct htu21d_handle_s
{
    uint8_t (*iic_init)(void);                                                                  /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                                /**< point to an iic_deinit function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);                         /**< point to an iic_write_cmd function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);                          /**< point to an iic_read_cmd function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                /**< point to an iic_write function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                 /**< point to an iic_read function address */
    uint8_t (*iic_read_with_scl)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_read_with_scl function address */
    void (*delay_ms)(uint32_t ms);                                                              /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                            /**< point to a debug_print function address */
    uint8_t mode;                                                                               /**< chip mode */
    uint8_t resolution;                                                                         /**< chip resolution */
    uint8_t inited;                                                                             /**< inited flag */
} htu21d_handle_t;

/**
 * @brief htu21d information structure definition
 */
typedef struct htu21d_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} htu21d_info_t;

/**
 * @}
 */

/**
 * @defgroup htu21d_link_driver htu21d link driver function
 * @brief    htu21d link driver modules
 * @ingroup  htu21d_driver
 * @{
 */

/**
 * @brief     initialize htu21d_handle_t structure
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] STRUCTURE is htu21d_handle_t
 * @note      none
 */
#define DRIVER_HTU21D_LINK_INIT(HANDLE, STRUCTURE)               memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_HTU21D_LINK_IIC_INIT(HANDLE, FUC)                 (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_HTU21D_LINK_IIC_DEINIT(HANDLE, FUC)               (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] FUC points to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_HTU21D_LINK_IIC_WRITE_CMD(HANDLE, FUC)            (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_HTU21D_LINK_IIC_READ_CMD(HANDLE, FUC)             (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_HTU21D_LINK_IIC_WRITE(HANDLE, FUC)                (HANDLE)->iic_write = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_HTU21D_LINK_IIC_READ(HANDLE, FUC)                 (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_read_with_scl function
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] FUC points to an iic_read_with_scl function address
 * @note      none
 */
#define DRIVER_HTU21D_LINK_IIC_READ_WITH_SCL(HANDLE, FUC)        (HANDLE)->iic_read_with_scl = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_HTU21D_LINK_DELAY_MS(HANDLE, FUC)                 (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an htu21d handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_HTU21D_LINK_DEBUG_PRINT(HANDLE, FUC)              (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup htu21d_base_driver htu21d base driver function
 * @brief    htu21d base driver modules
 * @ingroup  htu21d_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an htu21d info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t htu21d_info(htu21d_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an htu21d handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 soft reset failed
 *            - 5 read config failed
 * @note      none
 */
uint8_t htu21d_init(htu21d_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an htu21d handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 soft reset failed
 * @note      none
 */
uint8_t htu21d_deinit(htu21d_handle_t *handle);

/**
 * @brief     set the chip mode
 * @param[in] *handle points to an htu21d handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t htu21d_set_mode(htu21d_handle_t *handle, htu21d_mode_t mode);

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *mode points to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t htu21d_get_mode(htu21d_handle_t *handle, htu21d_mode_t *mode);

/**
 * @brief     soft reset
 * @param[in] *handle points to an htu21d handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t htu21d_soft_reset(htu21d_handle_t *handle);

/**
 * @brief      read the temperature and humidity data
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *temperature_raw points to a raw temperature buffer
 * @param[out] *temperature_s points to a converted temperature buffer
 * @param[out] *humidity_raw points to a raw humidity buffer
 * @param[out] *humidity_s points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 *             - 5 status is error
 * @note       none
 */
uint8_t htu21d_read_temperature_humidity(htu21d_handle_t *handle,
                                         uint16_t *temperature_raw, float *temperature_s,
                                         uint16_t *humidity_raw, float *humidity_s
                                        );

/**
 * @brief      read the temperature data
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *temperature_raw points to a raw temperature buffer
 * @param[out] *temperature_s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 *             - 5 status is error
 * @note       none
 */
uint8_t htu21d_read_temperature(htu21d_handle_t *handle, uint16_t *temperature_raw, float *temperature_s);

/**
 * @brief      read the humidity data
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *humidity_raw points to a raw humidity buffer
 * @param[out] *humidity_s points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 *             - 5 status is error
 * @note       none
 */
uint8_t htu21d_read_humidity(htu21d_handle_t *handle, uint16_t *humidity_raw, float *humidity_s);

/**
 * @brief     set the resolution
 * @param[in] *handle points to an htu21d handle structure
 * @param[in] resolution is the set resolution
 * @return    status code
 *            - 0 success
 *            - 1 set resolution failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t htu21d_set_resolution(htu21d_handle_t *handle, htu21d_resolution_t resolution);

/**
 * @brief      get the resolution
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *resolution points to a resolution buffer
 * @return     status code
 *             - 0 success
 *             - 1 get resolution failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t htu21d_get_resolution(htu21d_handle_t *handle, htu21d_resolution_t *resolution);

/**
 * @brief      get the battery status
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get battery status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t htu21d_get_battery_status(htu21d_handle_t *handle, htu21d_status_t *status);

/**
 * @brief     enable or disable the heater
 * @param[in] *handle points to an htu21d handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set heater failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t htu21d_set_heater(htu21d_handle_t *handle, htu21d_bool_t enable);

/**
 * @brief      get the heater status
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t htu21d_get_heater(htu21d_handle_t *handle, htu21d_bool_t *enable);

/**
 * @brief     enable or disable otp reload
 * @param[in] *handle points to an htu21d handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set disable otp reload failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t htu21d_set_disable_otp_reload(htu21d_handle_t *handle, htu21d_bool_t enable);

/**
 * @brief      get the disable otp reload status
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get disable otp reload failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t htu21d_get_disable_otp_reload(htu21d_handle_t *handle, htu21d_bool_t *enable);

/**
 * @brief      get the serial number
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *number points to a number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial number failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 * @note       none
 */
uint8_t htu21d_get_serial_number(htu21d_handle_t *handle, uint64_t *number);

/**
 * @}
 */

/**
 * @defgroup htu21d_extend_driver htu21d extend driver function
 * @brief    htu21d extend driver modules
 * @ingroup  htu21d_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an htu21d handle structure
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t htu21d_set_reg(htu21d_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *buf points to data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t htu21d_get_reg(htu21d_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
