//
// Created by victor on 11-11-22.
//

#ifndef TCA9534_IDF_TCA9534_H
#define TCA9534_IDF_TCA9534_H
#include <driver/i2c.h>

#define I2C_MASTER_TIMEOUT_MS       1000

typedef enum {
    TCA9534_IO0,
    TCA9534_IO1,
    TCA9534_IO2,
    TCA9534_IO3,
    TCA9534_IO4,
    TCA9534_IO5,
    TCA9534_IO6,
    TCA9534_IO7
}TCA9534_PINS;

typedef enum{
    TCA9534_OUTPUT,
    TCA9534_INPUT
}TCA9534_PORT_PROPERTIES;

typedef struct{
    uint8_t I2C_ADDR;
    uint8_t output_pins;
    i2c_config_t i2c_conf;
    int i2c_master_port;
}TCA9534_IO_EXP;

int16_t get_io_pin_input_status(TCA9534_IO_EXP io_exp, TCA9534_PINS io_pin);

int16_t get_tca9534_all_io_pin_input_status(TCA9534_IO_EXP io_exp);

esp_err_t set_all_tca9534_io_pins_direction(TCA9534_IO_EXP io_exp, TCA9534_PORT_PROPERTIES properties);

esp_err_t set_tca9534_io_pin_direction(TCA9534_IO_EXP io_exp, TCA9534_PINS io_pin, TCA9534_PORT_PROPERTIES properties);

esp_err_t set_tca9534_io_pin_output_state(TCA9534_IO_EXP io_exp, TCA9534_PINS io_pin, uint8_t state);


#endif //TCA9534_IDF_TCA9534_H
