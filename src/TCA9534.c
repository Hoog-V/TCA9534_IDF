#include <stdio.h>
#include "TCA9534.h"
#include "esp_log.h"
#include "driver/i2c.h"

typedef enum{
input_port,
output_port,
polarity_inversion,
configuration
}TCA9534_COMMANDS;


esp_err_t writeReg(TCA9534_IO_EXP io_exp, TCA9534_COMMANDS cmd, uint8_t data){
    uint8_t write_buffer[2] = {cmd, data};
    return i2c_master_write_to_device(io_exp.i2c_master_port, io_exp.I2C_ADDR, write_buffer,
                                      sizeof(write_buffer), I2C_MASTER_TIMEOUT_MS/portTICK_RATE_MS);
}

esp_err_t readReg(TCA9534_IO_EXP io_exp, TCA9534_COMMANDS cmd, uint8_t *read_buff){
    uint8_t reg = cmd;
    return i2c_master_write_read_device(io_exp.i2c_master_port, io_exp.I2C_ADDR, &reg,
                                        1, read_buff, 1, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}

int16_t get_io_pin_input_status(TCA9534_IO_EXP io_exp, TCA9534_PINS io_pin)
{
    int16_t result = get_tca9534_all_io_pin_input_status(io_exp);
    if(result != -1)
        result &= (1<< io_pin);
    else
        result = -1;
    return result;
}

int16_t get_tca9534_all_io_pin_input_status(TCA9534_IO_EXP io_exp)
{
    uint8_t result = 0;
    esp_err_t status = readReg(io_exp, input_port, &result);
    return (status == ESP_OK) ? result : -1;
}

esp_err_t set_all_tca9534_io_pins_direction(TCA9534_IO_EXP io_exp, TCA9534_PORT_PROPERTIES properties)
{
    uint8_t dir = (properties == TCA9534_OUTPUT) ? 0x00 : 0xFF;
    esp_err_t status = writeReg(io_exp, configuration, dir);
    return status;
}

esp_err_t set_tca9534_io_pin_direction(TCA9534_IO_EXP io_exp, TCA9534_PINS io_pin, TCA9534_PORT_PROPERTIES properties)
{
    uint8_t port_status = 0;
    esp_err_t status = readReg(io_exp, configuration, &port_status);
    port_status = (properties != TCA9534_OUTPUT) ? (port_status | (1 << io_pin)) : (port_status & ~(1 << io_pin));

    status |= writeReg(io_exp, configuration, port_status);
    return status;
}

esp_err_t set_tca9534_io_pin_output_state(TCA9534_IO_EXP io_exp, TCA9534_PINS io_pin, uint8_t state)
{
    uint8_t port_status = 0;
    esp_err_t status = readReg(io_exp, output_port, &port_status);
    port_status = (state != 0) ? (port_status | (1 << io_pin)) : (port_status & ~(1 << io_pin));

    status |= writeReg(io_exp, output_port, port_status);
    return status;
}