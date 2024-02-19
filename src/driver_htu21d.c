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
 * @file      driver_htu21d.c
 * @brief     driver htu21d source file
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

#include "driver_htu21d.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "TE HTU21D"        /**< chip name */
#define MANUFACTURER_NAME         "TE"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.5f               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f               /**< chip max supply voltage */
#define MAX_CURRENT               0.5f               /**< chip max current */
#define TEMPERATURE_MIN           -40.0f             /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f             /**< chip max operating temperature */
#define DRIVER_VERSION            1000               /**< driver version */

/**
 * @brief chip address definition
 */
#define HTU21D_ADDRESS        0x80        /**< iic device address */

/**
 * @brief chip command definition
 */
#define HTU21D_COMMAND_TRIG_TEMP_HOLD_MASTER        0xE3        /**< trigger temperature measurement with hold master command */
#define HTU21D_COMMAND_TRIG_HUMI_HOLD_MASTER        0xE5        /**< trigger humidity measurement with hold master command */
#define HTU21D_COMMAND_TRIG_TEMP_NO_HOLD_MASTER     0xF3        /**< trigger temperature measurement command */
#define HTU21D_COMMAND_TRIG_HUMI_NO_HOLD_MASTER     0xF5        /**< trigger humidity measurement command */
#define HTU21D_COMMAND_WRITE_USER_REGISTER          0xE6        /**< write user register command */
#define HTU21D_COMMAND_READ_USER_REGISTER           0xE7        /**< read user register command */
#define HTU21D_COMMAND_SOFT_RESET                   0xFE        /**< soft reset command */

/**
 * @brief     write command
 * @param[in] *handle points to an htu21d handle structure
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_htu21d_write_cmd(htu21d_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle->iic_write_cmd(HTU21D_ADDRESS, buf, len) != 0)        /* iic write */
    {
        return 1;                                                    /* return error */
    }
    else
    {
        return 0;                                                    /* success return 0 */
    }
}

/**
 * @brief      read command
 * @param[in]  *handle points to an htu21d handle structure
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_htu21d_read_cmd(htu21d_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle->iic_read_cmd(HTU21D_ADDRESS, buf, len) != 0)        /* iic read */
    {
        return 1;                                                   /* return error */
    }
    else
    {
        return 0;                                                   /* success return 0 */
    }
}

/**
 * @brief     write bytes
 * @param[in] *handle points to an htu21d handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_htu21d_write(htu21d_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle->iic_write(HTU21D_ADDRESS, reg, buf, len) != 0)        /* iic write */
    {
        return 1;                                                     /* return error */
    }
    else
    {
        return 0;                                                     /* success return 0 */
    }
}

/**
 * @brief      read bytes
 * @param[in]  *handle points to an htu21d handle structure
 * @param[in]  mode is the read mode
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_htu21d_read(htu21d_handle_t *handle, uint8_t mode, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (mode == HTU21D_MODE_HOLD_MASTER)                                          /* hold master */
    {
        if (handle->iic_read_with_scl(HTU21D_ADDRESS, reg, buf, len) != 0)        /* iic read */
        {
            return 1;                                                             /* return error */
        }
        else
        {
            return 0;                                                             /* success return 0 */
        }
    }
    else                                                                          /* no hold master */
    {
        if (handle->iic_read(HTU21D_ADDRESS, reg, buf, len) != 0)                 /* iic read */
        {
            return 1;                                                             /* return error */
        }
        else
        {
            return 0;                                                             /* success return 0 */
        }
    }
}

/**
 * @brief     check the crc
 * @param[in] value is the input value
 * @param[in] crc is the checked crc
 * @return    status code
 *            - 0 pass
 *            - 1 error
 * @note      none
 */
static uint8_t a_htu21d_crc(uint16_t value, uint32_t crc)
{
    uint32_t polynom = 0x988000U;
    uint32_t msb     = 0x800000U;
    uint32_t mask    = 0xFF8000U;
    uint32_t result  = (uint32_t)value << 8;
    
    while (msb != 0x80)                                                       /* check the msb */
    {
        if ((result & msb) != 0)                                              /* check the result */
        {
            result = ((result ^ polynom) & mask) | (result & (~mask));        /* get the new result */
        }
        msb >>= 1;                                                            /* right shift 1 */
        mask >>= 1;                                                           /* right shift 1 */
        polynom >>= 1;                                                        /* right shift 1 */
    }
    if (result == crc)                                                        /* check the result */
    {
        return 0;                                                             /* success return 0 */
    }
    else
    {
        return 1;                                                             /* return error */
    }
}

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
uint8_t htu21d_set_mode(htu21d_handle_t *handle, htu21d_mode_t mode)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    handle->mode = mode;            /* set the mode */
    
    return 0;                       /* success return 0 */
}

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
uint8_t htu21d_get_mode(htu21d_handle_t *handle, htu21d_mode_t *mode)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }
    
    *mode = (htu21d_mode_t)(handle->mode);        /* get the mode */
    
    return 0;                                     /* success return 0 */
}

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
uint8_t htu21d_soft_reset(htu21d_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_htu21d_write(handle, HTU21D_COMMAND_SOFT_RESET, NULL, 0);        /* soft reset */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("htu21d: write failed.\n");                      /* write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_ms(15);                                                    /* delay 15 ms */
    
    return 0;                                                                /* success return 0 */
}

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
                                        )
{
    uint8_t res;
    uint8_t buf[3];
    uint8_t status;
    uint16_t data;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    if (handle->mode == HTU21D_MODE_HOLD_MASTER)                                          /* hold master mode */
    {
        res = a_htu21d_read(handle, HTU21D_MODE_HOLD_MASTER, 
                            HTU21D_COMMAND_TRIG_TEMP_HOLD_MASTER, buf, 3);                /* read temperature */
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: read failed.\n");                                /* read failed */
            
            return 1;                                                                     /* return error */
        }
        data = ((uint16_t)buf[0] << 8) | buf[1];                                          /* get the raw data */
        if (a_htu21d_crc(data, buf[2]) != 0)                                              /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                               /* crc is error */
            
            return 4;                                                                     /* return error */
        }
        status = data & 0x3;                                                              /* get the status */
        if (status != 0x00)                                                               /* check the status */
        {
            handle->debug_print("htu21d: status is error.\n");                            /* status is error */
            
            return 5;                                                                     /* return error */
        }
        *temperature_raw = data;                                                          /* copy data */
        
        res = a_htu21d_read(handle, HTU21D_MODE_HOLD_MASTER, 
                            HTU21D_COMMAND_TRIG_HUMI_HOLD_MASTER, buf, 3);                /* read humidity */
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: read failed.\n");                                /* read failed */
            
            return 1;                                                                     /* return error */
        }
        data = ((uint16_t)buf[0] << 8) | buf[1];                                          /* get the raw data */
        if (a_htu21d_crc(data, buf[2]) != 0)                                              /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                               /* crc is error */
            
            return 4;                                                                     /* return error */
        }
        status = data & 0x3;                                                              /* get the status */
        if (status != 0x02)                                                               /* check the status */
        {
            handle->debug_print("htu21d: status is error.\n");                            /* status is error */
            
            return 5;                                                                     /* return error */
        }
        *humidity_raw = data;                                                             /* copy data */
    }
    else                                                                                  /* no hold master mode */
    {
        uint8_t cmd;
        
        cmd = HTU21D_COMMAND_TRIG_TEMP_NO_HOLD_MASTER;                                    /* read temperature */
        res = a_htu21d_write_cmd(handle, &cmd, 1);                                        /* write the command */
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: write cmd failed.\n");                           /* write cmd failed */
            
            return 1;                                                                     /* return error */
        }
        if (handle->resolution == HTU21D_RESOLUTION_TEMP_11_BITS_RH_11_BITS)              /* temp 11 bits and rh 11 bits */
        {
            handle->delay_ms(7);                                                          /* delay 7 ms */
        }
        else if (handle->resolution == HTU21D_RESOLUTION_TEMP_12_BITS_RH_8_BITS)          /* temp 12 bits and rh 8 bits */
        {
            handle->delay_ms(13);                                                         /* delay 13 ms */
        }
        else if (handle->resolution == HTU21D_RESOLUTION_TEMP_13_BITS_RH_10_BITS)         /* temp 13 bits and rh 10 bits */
        {
            handle->delay_ms(25);                                                         /* delay 25 ms */
        }
        else                                                                              /* temp 14 bits and rh 12 bits */
        {
            handle->delay_ms(50);                                                         /* delay 50 ms */
        }
        res = a_htu21d_read_cmd(handle, buf, 3);
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: read cmd failed.\n");                            /* read cmd failed */
            
            return 1;                                                                     /* return error */
        }
        data = ((uint16_t)buf[0] << 8) | buf[1];                                          /* get the raw data */
        if (a_htu21d_crc(data, buf[2]) != 0)                                              /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                               /* crc is error */
            
            return 4;                                                                     /* return error */
        }
        status = data & 0x3;                                                              /* get the status */
        if (status != 0x00)                                                               /* check the status */
        {
            handle->debug_print("htu21d: status is error.\n");                            /* status is error */
            
            return 5;                                                                     /* return error */
        }
        *temperature_raw = data;                                                          /* copy data */
        
        cmd = HTU21D_COMMAND_TRIG_HUMI_NO_HOLD_MASTER;                                    /* read humidity */
        res = a_htu21d_write_cmd(handle, &cmd, 1);                                        /* write the command */
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: write cmd failed.\n");                           /* write cmd failed */
            
            return 1;                                                                     /* return error */
        }
        if (handle->resolution == HTU21D_RESOLUTION_TEMP_11_BITS_RH_11_BITS)              /* temp 11 bits and rh 11 bits */
        {
            handle->delay_ms(7);                                                          /* delay 7 ms */
        }
        else if (handle->resolution == HTU21D_RESOLUTION_TEMP_12_BITS_RH_8_BITS)          /* temp 12 bits and rh 8 bits */
        {
            handle->delay_ms(13);                                                         /* delay 13 ms */
        }
        else if (handle->resolution == HTU21D_RESOLUTION_TEMP_13_BITS_RH_10_BITS)         /* temp 13 bits and rh 10 bits */
        {
            handle->delay_ms(25);                                                         /* delay 25 ms */
        }
        else                                                                              /* temp 14 bits and rh 12 bits */
        {
            handle->delay_ms(50);                                                         /* delay 50 ms */
        }
        res = a_htu21d_read_cmd(handle, buf, 3);
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: read cmd failed.\n");                            /* read cmd failed */
            
            return 1;                                                                     /* return error */
        }
        data = ((uint16_t)buf[0] << 8) | buf[1];                                          /* get the raw data */
        if (a_htu21d_crc(data, buf[2]) != 0)                                              /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                               /* crc is error */
            
            return 4;                                                                     /* return error */
        }
        status = data & 0x3;                                                              /* get the status */
        if (status != 0x02)                                                               /* check the status */
        {
            handle->debug_print("htu21d: status is error.\n");                            /* status is error */
            
            return 5;                                                                     /* return error */
        }
        *humidity_raw = data;                                                             /* copy data */
    }

    *temperature_s = (float)(*temperature_raw) / 65536.0f * 175.72f - 46.85f;             /* convert raw temperature */
    *humidity_s = (float)(*humidity_raw) / 65536.0f * 125.0f - 6.0f;                      /* convert raw humidity */
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t htu21d_read_temperature(htu21d_handle_t *handle, uint16_t *temperature_raw, float *temperature_s)
{
    uint8_t res;
    uint8_t buf[3];
    uint8_t status;
    uint16_t data;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    if (handle->mode == HTU21D_MODE_HOLD_MASTER)                                          /* hold master mode */
    {
        res = a_htu21d_read(handle, HTU21D_MODE_HOLD_MASTER, 
                            HTU21D_COMMAND_TRIG_TEMP_HOLD_MASTER, buf, 3);                /* read temperature */
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: read failed.\n");                                /* read failed */
            
            return 1;                                                                     /* return error */
        }
        data = ((uint16_t)buf[0] << 8) | buf[1];                                          /* get the raw data */
        if (a_htu21d_crc(data, buf[2]) != 0)                                              /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                               /* crc is error */
            
            return 4;                                                                     /* return error */
        }
        status = data & 0x3;                                                              /* get the status */
        if (status != 0x00)                                                               /* check the status */
        {
            handle->debug_print("htu21d: status is error.\n");                            /* status is error */
            
            return 5;                                                                     /* return error */
        }
        *temperature_raw = data;                                                          /* copy data */
    }
    else                                                                                  /* no hold master mode */
    {
        uint8_t cmd;
        
        cmd = HTU21D_COMMAND_TRIG_TEMP_NO_HOLD_MASTER;                                    /* read temperature */
        res = a_htu21d_write_cmd(handle, &cmd, 1);                                        /* write the command */
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: write cmd failed.\n");                           /* write cmd failed */
            
            return 1;                                                                     /* return error */
        }
        if (handle->resolution == HTU21D_RESOLUTION_TEMP_11_BITS_RH_11_BITS)              /* temp 11 bits and rh 11 bits */
        {
            handle->delay_ms(7);                                                          /* delay 7 ms */
        }
        else if (handle->resolution == HTU21D_RESOLUTION_TEMP_12_BITS_RH_8_BITS)          /* temp 12 bits and rh 8 bits */
        {
            handle->delay_ms(13);                                                         /* delay 13 ms */
        }
        else if (handle->resolution == HTU21D_RESOLUTION_TEMP_13_BITS_RH_10_BITS)         /* temp 13 bits and rh 10 bits */
        {
            handle->delay_ms(25);                                                         /* delay 25 ms */
        }
        else                                                                              /* temp 14 bits and rh 12 bits */
        {
            handle->delay_ms(50);                                                         /* delay 50 ms */
        }
        res = a_htu21d_read_cmd(handle, buf, 3);
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: read cmd failed.\n");                            /* read cmd failed */
            
            return 1;                                                                     /* return error */
        }
        data = ((uint16_t)buf[0] << 8) | buf[1];                                          /* get the raw data */
        if (a_htu21d_crc(data, buf[2]) != 0)                                              /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                               /* crc is error */
            
            return 4;                                                                     /* return error */
        }
        status = data & 0x3;                                                              /* get the status */
        if (status != 0x00)                                                               /* check the status */
        {
            handle->debug_print("htu21d: status is error.\n");                            /* status is error */
            
            return 5;                                                                     /* return error */
        }
        *temperature_raw = data;                                                          /* copy data */
    }

    *temperature_s = (float)(*temperature_raw) / 65536.0f * 175.72f - 46.85f;             /* convert raw temperature */
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t htu21d_read_humidity(htu21d_handle_t *handle, uint16_t *humidity_raw, float *humidity_s)
{
    uint8_t res;
    uint8_t buf[3];
    uint8_t status;
    uint16_t data;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    if (handle->mode == HTU21D_MODE_HOLD_MASTER)                                          /* hold master mode */
    {
        res = a_htu21d_read(handle, HTU21D_MODE_HOLD_MASTER, 
                            HTU21D_COMMAND_TRIG_HUMI_HOLD_MASTER, buf, 3);                /* read humidity */
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: read failed.\n");                                /* read failed */
            
            return 1;                                                                     /* return error */
        }
        data = ((uint16_t)buf[0] << 8) | buf[1];                                          /* get the raw data */
        if (a_htu21d_crc(data, buf[2]) != 0)                                              /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                               /* crc is error */
            
            return 4;                                                                     /* return error */
        }
        status = data & 0x3;                                                              /* get the status */
        if (status != 0x02)                                                               /* check the status */
        {
            handle->debug_print("htu21d: status is error.\n");                            /* status is error */
            
            return 5;                                                                     /* return error */
        }
        *humidity_raw = data;                                                             /* copy data */
    }
    else                                                                                  /* no hold master mode */
    {
        uint8_t cmd;
        
        cmd = HTU21D_COMMAND_TRIG_HUMI_NO_HOLD_MASTER;                                    /* read humidity */
        res = a_htu21d_write_cmd(handle, &cmd, 1);                                        /* write the command */
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: write cmd failed.\n");                           /* write cmd failed */
            
            return 1;                                                                     /* return error */
        }
        if (handle->resolution == HTU21D_RESOLUTION_TEMP_11_BITS_RH_11_BITS)              /* temp 11 bits and rh 11 bits */
        {
            handle->delay_ms(7);                                                          /* delay 7 ms */
        }
        else if (handle->resolution == HTU21D_RESOLUTION_TEMP_12_BITS_RH_8_BITS)          /* temp 12 bits and rh 8 bits */
        {
            handle->delay_ms(13);                                                         /* delay 13 ms */
        }
        else if (handle->resolution == HTU21D_RESOLUTION_TEMP_13_BITS_RH_10_BITS)         /* temp 13 bits and rh 10 bits */
        {
            handle->delay_ms(25);                                                         /* delay 25 ms */
        }
        else                                                                              /* temp 14 bits and rh 12 bits */
        {
            handle->delay_ms(50);                                                         /* delay 50 ms */
        }
        res = a_htu21d_read_cmd(handle, buf, 3);
        if (res != 0)                                                                     /* check the result */
        {
            handle->debug_print("htu21d: read cmd failed.\n");                            /* read cmd failed */
            
            return 1;                                                                     /* return error */
        }
        data = ((uint16_t)buf[0] << 8) | buf[1];                                          /* get the raw data */
        if (a_htu21d_crc(data, buf[2]) != 0)                                              /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                               /* crc is error */
            
            return 4;                                                                     /* return error */
        }
        status = data & 0x3;                                                              /* get the status */
        if (status != 0x02)                                                               /* check the status */
        {
            handle->debug_print("htu21d: status is error.\n");                            /* status is error */
            
            return 5;                                                                     /* return error */
        }
        *humidity_raw = data;                                                             /* copy data */
    }

    *humidity_s = (float)(*humidity_raw) / 65536.0f * 125.0f - 6.0f;                      /* convert raw humidity */
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t htu21d_set_resolution(htu21d_handle_t *handle, htu21d_resolution_t resolution)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_htu21d_read(handle, HTU21D_MODE_NO_HOLD_MASTER,
                        HTU21D_COMMAND_READ_USER_REGISTER, &prev, 1);                  /* read config */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("htu21d: read failed.\n");                                 /* read failed */
        
        return 1;                                                                      /* return error */
    }
    prev &= ~(1 << 7);                                                                 /* clear bit 7 */
    prev &= ~(1 << 0);                                                                 /* clear bit 0 */
    prev |= ((resolution >> 1) & 0x01) << 7;                                           /* set bit 7 */
    prev |= ((resolution >> 0) & 0x01) << 0;                                           /* set bit 0 */
    res = a_htu21d_write(handle, HTU21D_COMMAND_WRITE_USER_REGISTER, &prev, 1);        /* write config */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("htu21d: write failed.\n");                                /* write failed */
        
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t htu21d_get_resolution(htu21d_handle_t *handle, htu21d_resolution_t *resolution)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_htu21d_read(handle, HTU21D_MODE_NO_HOLD_MASTER,
                        HTU21D_COMMAND_READ_USER_REGISTER, &prev, 1);                  /* read config */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("htu21d: read failed.\n");                                 /* read failed */
        
        return 1;                                                                      /* return error */
    }
    *resolution = (htu21d_resolution_t)((((prev >> 7) & 0x01) << 1) 
                                       | (((prev >> 0) & 0x01) << 0));                 /* get the resolution */
    handle->resolution = *resolution;                                                  /* save the resolution */
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t htu21d_get_battery_status(htu21d_handle_t *handle, htu21d_status_t *status)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_htu21d_read(handle, HTU21D_MODE_NO_HOLD_MASTER,
                        HTU21D_COMMAND_READ_USER_REGISTER, &prev, 1);        /* read config */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("htu21d: read failed.\n");                       /* read failed */
        
        return 1;                                                            /* return error */
    }
    *status = (htu21d_status_t)((prev >> 6) & 0x01);                         /* get the status */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t htu21d_set_heater(htu21d_handle_t *handle, htu21d_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_htu21d_read(handle, HTU21D_MODE_NO_HOLD_MASTER,
                        HTU21D_COMMAND_READ_USER_REGISTER, &prev, 1);                  /* read config */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("htu21d: read failed.\n");                                 /* read failed */
        
        return 1;                                                                      /* return error */
    }
    prev &= ~(1 << 2);                                                                 /* clear bit 2 */
    prev |= enable << 2;                                                               /* set the bool */
    res = a_htu21d_write(handle, HTU21D_COMMAND_WRITE_USER_REGISTER, &prev, 1);        /* write config */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("htu21d: write failed.\n");                                /* write failed */
        
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t htu21d_get_heater(htu21d_handle_t *handle, htu21d_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_htu21d_read(handle, HTU21D_MODE_NO_HOLD_MASTER,
                        HTU21D_COMMAND_READ_USER_REGISTER, &prev, 1);        /* read config */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("htu21d: read failed.\n");                       /* read failed */
        
        return 1;                                                            /* return error */
    }
    *enable = (htu21d_bool_t)((prev >> 2) & 0x01);                           /* set the bool */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t htu21d_set_disable_otp_reload(htu21d_handle_t *handle, htu21d_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_htu21d_read(handle, HTU21D_MODE_NO_HOLD_MASTER,
                        HTU21D_COMMAND_READ_USER_REGISTER, &prev, 1);                  /* read config */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("htu21d: read failed.\n");                                 /* read failed */
        
        return 1;                                                                      /* return error */
    }
    prev &= ~(1 << 1);                                                                 /* clear bit 1 */
    prev |= enable << 1;                                                               /* set the bool */
    res = a_htu21d_write(handle, HTU21D_COMMAND_WRITE_USER_REGISTER, &prev, 1);        /* write config */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("htu21d: write failed.\n");                                /* write failed */
        
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t htu21d_get_disable_otp_reload(htu21d_handle_t *handle, htu21d_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_htu21d_read(handle, HTU21D_MODE_NO_HOLD_MASTER,
                        HTU21D_COMMAND_READ_USER_REGISTER, &prev, 1);        /* read config */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("htu21d: read failed.\n");                       /* read failed */
        
        return 1;                                                            /* return error */
    }
    *enable = (htu21d_bool_t)((prev >> 1) & 0x01);                           /* set the bool */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t htu21d_get_serial_number(htu21d_handle_t *handle, uint64_t *number)
{
    uint8_t i;
    uint8_t res;
    uint8_t cmd[2];
    uint8_t data[14];
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }

    cmd[0] = 0xFA;                                                                         /* command 0 */
    cmd[1] = 0x0F;                                                                         /* command 1 */
    res = a_htu21d_write_cmd(handle, cmd, 2);                                              /* write command */
    if (res != 0)                                                                          /* check the result */
    {
        handle->debug_print("htu21d: write command failed.\n");                            /* write command failed */
        
        return 1;                                                                          /* return error */
    }
    res = a_htu21d_read_cmd(handle, data, 8);                                              /* read command */
    if (res != 0)                                                                          /* check the result */
    {
        handle->debug_print("htu21d: read command failed.\n");                             /* read command failed */
        
        return 1;                                                                          /* return error */
    }
    cmd[0] = 0xFC;                                                                         /* command 0 */
    cmd[1] = 0xC9;                                                                         /* command 1 */
    res = a_htu21d_write_cmd(handle, cmd, 2);                                              /* write command */
    if (res != 0)                                                                          /* check the result */
    {
        handle->debug_print("htu21d: write command failed.\n");                            /* write command failed */
        
        return 1;                                                                          /* return error */
    }
    res = a_htu21d_read_cmd(handle, data + 8, 6);                                          /* read command */
    if (res != 0)                                                                          /* check the result */
    {
        handle->debug_print("htu21d: read command failed.\n");                             /* read command failed */
        
        return 1;                                                                          /* return error */
    }
    
    for (i = 0; i < 8; i += 2)                                                             /* check first data */
    {
        if (a_htu21d_crc(data[i], data[i + 1]) != 0)                                       /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                                /* crc is error */
            
            return 4;                                                                      /* return error */
        }
    }
    for (i = 8; i < 14; i += 3)                                                            /* check last data */
    {
        if (a_htu21d_crc(((uint16_t)data[i] << 8) | data[i + 1], data[i + 2]) != 0)        /* check the crc */
        {
            handle->debug_print("htu21d: crc is error.\n");                                /* crc is error */
            
            return 4;                                                                      /* return error */
        }
    }
    
    *number = ((uint64_t)data[0] << 56) | ((uint64_t)data[2] << 48) 
               | ((uint64_t)data[4] << 40) | ((uint64_t)data[6] << 32)
               | ((uint64_t)data[8] << 24) | ((uint64_t)data[9] << 16)
               | ((uint64_t)data[11] << 8) | ((uint64_t)data[12] << 0);                    /* set the number */
    
    return 0;                                                                              /* success return 0 */
}

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
uint8_t htu21d_init(htu21d_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                                 /* check debug_print */
    {
        return 3;                                                                    /* return error */
    }
    if (handle->iic_init == NULL)                                                    /* check iic_init */
    {
        handle->debug_print("htu21d: iic_init is null.\n");                          /* iic_init is null */
       
        return 3;                                                                    /* return error */
    }
    if (handle->iic_deinit == NULL)                                                  /* check iic_deinit */
    {
        handle->debug_print("htu21d: iic_deinit is null.\n");                        /* iic_deinit is null */
       
        return 3;                                                                    /* return error */
    }
    if (handle->iic_read == NULL)                                                    /* check iic_read */
    {
        handle->debug_print("htu21d: iic_read is null.\n");                          /* iic_read is null */
       
        return 3;                                                                    /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                                /* check iic_read_cmd */
    {
        handle->debug_print("htu21d: iic_read_cmd is null.\n");                      /* iic_read_cmd is null */
       
        return 3;                                                                    /* return error */
    }
    if (handle->iic_read_with_scl == NULL)                                           /* check iic_read_with_scl */
    {
        handle->debug_print("htu21d: iic_read_with_scl is null.\n");                 /* iic_read_with_scl is null */
       
        return 3;                                                                    /* return error */
    }
    if (handle->iic_write == NULL)                                                   /* check iic_write */
    {
        handle->debug_print("htu21d: iic_write is null.\n");                         /* iic_write is null */
       
        return 3;                                                                    /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                               /* check iic_write_cmd */
    {
        handle->debug_print("htu21d: iic_write_cmd is null.\n");                     /* iic_write_cmd is null */
       
        return 3;                                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                                    /* check delay_ms */
    {
        handle->debug_print("htu21d: delay_ms is null.\n");                          /* delay_ms is null */
       
        return 3;                                                                    /* return error */
    }
    
    if (handle->iic_init() != 0)                                                     /* iic init */
    {
        handle->debug_print("htu21d: iic init failed.\n");                           /* iic init failed */
       
        return 1;                                                                    /* return error */
    }
    res = a_htu21d_write(handle, HTU21D_COMMAND_SOFT_RESET, NULL, 0);                /* soft reset */
    if (res != 0)                                                                    /* check the result */
    {
        handle->debug_print("htu21d: soft reset failed.\n");                         /* soft reset failed */
        (void)handle->iic_deinit();                                                  /* iic deinit */
        
        return 4;                                                                    /* return error */
    }
    handle->delay_ms(15);                                                            /* delay 15 ms */
    res = a_htu21d_read(handle, HTU21D_MODE_NO_HOLD_MASTER,
                        HTU21D_COMMAND_READ_USER_REGISTER, &prev, 1);                /* read config */
    if (res != 0)                                                                    /* check the result */
    {
        handle->debug_print("htu21d: read config failed.\n");                        /* read config failed */
        (void)handle->iic_deinit();                                                  /* iic deinit */
        
        return 5;                                                                    /* return error */
    }
    handle->resolution = (htu21d_resolution_t)((((prev >> 7) & 0x01) << 1) 
                                              | (((prev >> 0) & 0x01) << 0));        /* save the resolution */
    handle->mode = HTU21D_MODE_NO_HOLD_MASTER;                                       /* set no hold master */
    
    handle->inited = 1;                                                              /* flag finish initialization */
    
    return 0;                                                                        /* success return 0 */
}

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
uint8_t htu21d_deinit(htu21d_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_htu21d_write(handle, HTU21D_COMMAND_SOFT_RESET, NULL, 0);        /* soft reset */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("htu21d: soft reset failed.\n");                 /* soft reset failed */
        
        return 4;                                                            /* return error */
    }
    handle->delay_ms(15);                                                    /* delay 15 ms */
    if (handle->iic_deinit() != 0)                                           /* iic deinit */
    {
        handle->debug_print("htu21d: iic deinit failed.\n");                 /* iic deinit failed */
       
        return 1;                                                            /* return error */
    }
    handle->inited = 0;                                                      /* flag close */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t htu21d_set_reg(htu21d_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_htu21d_write_cmd(handle, buf, len);        /* write command */
}

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
uint8_t htu21d_get_reg(htu21d_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_htu21d_read_cmd(handle, buf, len);        /* read command */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an htu21d info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t htu21d_info(htu21d_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(htu21d_info_t));                         /* initialize htu21d info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
