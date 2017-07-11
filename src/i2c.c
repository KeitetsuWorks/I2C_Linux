/**
 * @file        i2c.c
 * @brief       I2C Device Register Access Functions
 * @author      Keitetsu
 * @date        2016/09/05
 * @copyright   Copyright (c) 2016 Keitetsu
 * @license     This software is released under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "i2c.h"


int i2c_open_bus(
        char *i2c_bus)
{
    int fd;

    if((fd = open(i2c_bus, O_RDWR)) < 0) {
        perror("Error: Failed to open I2C Bus");
    }

    return fd;
}


void i2c_close_bus(
        int fd)
{
    close(fd);

    return;
}


int i2c_read_register(
        int fd,
        uint8_t dev_addr,
        uint8_t reg_addr,
        uint8_t *reg_data)
{
    uint8_t inbuf, outbuf;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];
    int result;
    
    result = 0;
    
    outbuf = reg_addr;
    messages[0].addr  = dev_addr;
    messages[0].flags = 0;
    messages[0].len   = sizeof(outbuf);
    messages[0].buf   = &outbuf;
    
    messages[1].addr  = dev_addr;
    messages[1].flags = I2C_M_RD;
    messages[1].len   = sizeof(inbuf);
    messages[1].buf   = &inbuf;
    
    packets.msgs      = messages;
    packets.nmsgs     = 2;
    
    if(ioctl(fd, I2C_RDWR, &packets) < 0) {
        perror("Error: Failed to send data");
        result = 1;
    }
    else {
        *reg_data = inbuf;
    }
    
    return result;
}


int i2c_write_register(
        int fd,
        uint8_t dev_addr,
        uint8_t reg_addr,
        uint8_t reg_data)
{
    uint8_t outbuf[2];
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];
    int result;
    
    result = 0;
    
    messages[0].addr  = dev_addr;
    messages[0].flags = 0;
    messages[0].len   = sizeof(outbuf);
    messages[0].buf   = outbuf;
    
    outbuf[0] = reg_addr;
    outbuf[1] = reg_data;
    
    packets.msgs  = messages;
    packets.nmsgs = 1;
    
    if(ioctl(fd, I2C_RDWR, &packets) < 0) {
        perror("Error: Failed to send data");
        result = 1;
    }
    
    return result;
}
