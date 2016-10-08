/**
 * @file    i2c.h
 * @brief   I2C Device Register Access Functions
 * @author  Keitetsu
 * @date    2016/09/05
 */

#pragma once    // __I2C_H__

// プロトタイプ宣言
/**
 * @brief   Open Function for I2C Bus
 * @param[in]       i2c_bus     Device File for I2C Bus
 * @return          File Descriptor
 */
int open_i2c_bus(
        char *i2c_bus);


/**
 * @brief   Close Function for DS3231
 * @param[in]       fd          Device File for I2C Bus
 */
void close_i2c_bus(
        int fd);


/**
 * @brief   Read Data from I2C Device Register
 * @param[in]       fd          Device File for I2C Bus
 * @param[in]       dev_addr    I2C Device Address
 * @param[in]       reg_addr    I2c Device Register Address
 * @param[out]      reg_data    Read Data from I2C Device Register
 */
int read_i2c_register(
        int fd,
        uint8_t dev_addr,
        uint8_t reg_addr,
        uint8_t *reg_data);


/**
 * @brief   Write Data to I2C Device Register
 * @param[in]       fd          Device File for I2C Bus
 * @param[in]       dev_addr    I2C Device Address
 * @param[in]       reg_addr    I2c Device Register Address
 * @param[out]      reg_data    Write Data for I2C Device Register
 */
int write_i2c_register(
        int fd,
        uint8_t dev_addr,
        uint8_t reg_addr,
        uint8_t reg_data);
