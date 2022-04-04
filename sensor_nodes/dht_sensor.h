/*
 * Copyright (C) 2020, 2021  Cornelius Schulz-Trieglaff <schulztr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jens Bücker <jebu@uni-bremen.de>
 * Copyright (C) 2020, 2021  Maurice Springholz <mau_spr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jan Romann <jan.romann@uni-bremen.de>
 *
 * SPDX-License-Identifier: LGPL-2.1 OR MIT
 *
 */

#ifndef SENSOR_H_
#define SENSOR_H_

typedef enum units {C, K, F} Unit;
static const char * const unit_string[]={"C", "K", "F"};
bool validUnit(unsigned int i);//needs to get modified if the number of supported units change

int dht_sensor_init(void);
int dht_cmd(int argc, char **argv);

int sensor_get_temperature(int16_t *temp_i);
Unit sensor_get_temperature_unit(void);
void sensor_set_temperature_unit(Unit u);
void convertTo(int16_t *temp_i);

int sensor_get_humidity(int16_t *hum_i);
char* sensor_get_humidity_unit(void);
int sensor_get_humidity_max(void);
int sensor_get_humidity_min(void);
void sensor_humidity_reset_extreme(void);

#endif // SENSOR_H_
