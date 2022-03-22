/*
 * Copyright (C) 2020, 2021  Cornelius Schulz-Trieglaff <schulztr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jens Bücker <jebu@uni-bremen.de>
 * Copyright (C) 2020, 2021  Maurice Springholz <mau_spr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jan Romann <jan.romann@uni-bremen.de>
 *
 * SPDX-License-Identifier: LGPL-2.1 OR MIT
 *
 */

#ifdef DHT_SENSOR

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "periph_conf.h"
#include "xtimer.h"
#include "periph/i2c.h"

#define SENSOR_TIMEOUT_MS       (5000*1000)
#define DHT_PARAM_PIN           (DHT_GPIO)

#include "dht.h"
#include "dht_params.h"

dht_t dev_dht;

#include "dht_sensor.h"
Unit unit = C;
bool validUnit(unsigned int i){
    return i<3;
}

int16_t hum_max = -1;
int16_t hum_min = -1;
int16_t h100;
int16_t t100;

int dht_cmd(int argc, char **argv) {
    if ( argc != 2 ) {
        (void) puts("Usage: dht [humidity|temperature]");
        return 1;
    }
    if ( strcmp( argv[1] , "humidity" ) == 0 ) {
        if (sensor_get_humidity(&h100) == DHT_OK) {
            printf("Humidity: %d.%01d%%\n", h100 / 10, h100 % 10);
        }
        return 0;
    }
    if ( strcmp( argv[1] , "temperature" ) == 0 ) {
        if (sensor_get_temperature(&t100) == DHT_OK) {
            convertTo(&t100);
            printf("Temperature: %d.%01d %s\n", t100 / 10, t100 % 10, sensor_get_humidity_unit());
        }
        return 0;
    }

    puts("dht: Invalid command");
    return 1;
}

int dht_sensor_init(void) {
    int init_ret;
    if ((dht_init(&dev_dht, dht_params) != DHT_OK)) {
        puts("ERROR: DHT init");
        init_ret = -1;
    }
    else
    {
        printf("DHT init ok.\n");
        init_ret = 0;
    }
    return init_ret;
}

int sensor_dht_measure(int16_t *temp, int16_t *hum) {
    return (dht_read(&dev_dht, temp, hum));
}
/**
 * Converts the given temperature value in to the current unit.
 * @param temp the temperature value in °C * 10^-2
 */
void convertTo(int16_t *temp){
    switch (unit)
    {
        case F:
            *temp = *temp * (9/5) + 3200;
            break;
        case K:
            *temp += 27315;
            break;
        case C:
            break;
    }
}

/**
 * @return the temperature in u * 10^-1 where u is represents the chosen unit.
 */
int sensor_get_temperature(int16_t* temp) {
	int err = sensor_dht_measure( temp, NULL);
	if (err) {
        puts("Error reading DHT values");
    }

    return err;
}

/**
 * @return the current unit of the temperature value
 */
Unit sensor_get_temperature_unit(void){
    return unit;
}

/**
 * Sets the Unit to u.
 * @param u the unit the global variable unit is set to.
 */
void sensor_set_temperature_unit(Unit u){
    unit = u;
}

/**
 * @return humidity in %*10^-1
 */
int sensor_get_humidity(int16_t* hum_i) {
	int err = sensor_dht_measure(NULL, hum_i);
	if (err != DHT_OK) {
        puts("Error reading DHT values");
    }

    return err;
}

/**
 * The unit of the humidity value is always percent.
 * @return the unit as character(s)
 */
char* sensor_get_humidity_unit(void){
    char* unit_h = "%";
    return unit_h;
}


bool unitIsPercent(void){
    return strcmp(sensor_get_humidity_unit(), "%") == 0;
}

/**
 * @return Reads the current humidity and eventually updates the hum_max or hum_min value.
 */
int sensor_set_extreme(int16_t *hum){

    if(!sensor_get_humidity(hum)) {
        return -1;
    }

    if (hum_min == -1 && hum_max == -1){
        hum_min = *hum;
        hum_max = *hum;
    }

    if (*hum < hum_min) {
        hum_min = *hum;
    }

    if (*hum > hum_max) {
        hum_max = *hum;
    }

    return 0;
}

/**
 * @return maximum humidity value measured since running or reset
 */
int sensor_get_humidity_max(void){
    return hum_max;
}

/**
 * @return minimum humidity value measured since running or reset
 */
int sensor_get_humidity_min(void){
    return hum_min;
}

/**
 * Resets the current minimum and maximum values to -1.
 */
void sensor_humidity_reset_extreme(void){
    hum_max=-1;
    hum_min=-1;
}

#endif
