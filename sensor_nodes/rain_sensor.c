/*
 * Copyright (C) 2020, 2021  Cornelius Schulz-Trieglaff <schulztr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jens Bücker <jebu@uni-bremen.de>
 * Copyright (C) 2020, 2021  Maurice Springholz <mau_spr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jan Romann <jan.romann@uni-bremen.de>
 * 
 * SPDX-License-Identifier: LGPL-2.1 OR MIT
 *
 */

#include <stdio.h>
#include <string.h>

#include "msg.h"
#include "math.h"
#include "periph/gpio.h"
#include "board.h"
#include "periph/adc.h"

#include "rain_sensor.h"

#define RES             ADC_RES_12BIT
#define MAX_RAIN_VAL    (pow(2, 12) - 1)


extern int adc_init (adc_t);
extern int32_t adc_sample (adc_t, adc_res_t);

const float step = 1;
static unsigned int range [2] = {0, MAX_RAIN_VAL};

int recent_val;

void update(void) {
    recent_val = MAX_RAIN_VAL - adc_sample(ADC_LINE(10), RES);
}

bool get_rain_value(void) {
    update();
    return recent_val > 0;
}

float get_rain_measurement(void) {
    update();
    return recent_val / MAX_RAIN_VAL;
}

float get_rain_precision(void) {
    return 0.0;     // This does not make sense for a simple resistant sensor.
}

unsigned int * get_rain_range(void) {
    return range;
}

float get_rain_step(void) {
    return step;
}

void rain_init(void) {
    adc_init(ADC_LINE(10));
}
