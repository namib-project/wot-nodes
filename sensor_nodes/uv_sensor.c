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

#include "uv_sensor.h"

#define ADC_ERROR                 (-1)
#define ADC_SUCCESS               (0)

#define RES                       (ADC_RES_12BIT)

#define MAX_UV_VALUE              (15.0)

#define VOLTS                     (3.3)

#ifndef UV_ADC_LINE
#define UV_ADC_LINE               (11) /* GPIO33 */
#endif
#ifndef UV_REFERENCE_ADC_LINE
#define UV_REFERENCE_ADC_LINE     (13) /* GPIO35 */
#endif

extern int adc_init (adc_t);
extern int32_t adc_sample (adc_t, adc_res_t);

const float step_uv = 1;

int uv_reference_val;
int recent_val_uv;
float output_voltage;
float uv_intensity;

int uv_cmd(int argc, char **argv) {
    if ( strcmp( argv[0] , "uv" ) == 0 ) {
        get_uv_value(&uv_intensity);
        printf("UV reference value: %d\n", uv_reference_val);
        printf("UV value: %d\n", recent_val_uv);
        printf("Output voltage: %.2f\n", output_voltage);
        printf("UV intensity: %.2f mW/cm²\n", uv_intensity);
        return ADC_SUCCESS;
    }

    puts("uv: Invalid command");
    return 1;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int get_uv_value(float *uv_intensity) {
    uv_reference_val = adc_sample(ADC_LINE(UV_ADC_LINE), RES);
    recent_val_uv = adc_sample(ADC_LINE(UV_REFERENCE_ADC_LINE), RES);
    if (uv_reference_val == ADC_ERROR || uv_reference_val == ADC_ERROR) {
        return ADC_ERROR;
    }
    output_voltage = VOLTS / uv_reference_val * recent_val_uv;
    *uv_intensity = mapfloat(output_voltage, 0.89, 2.8, 0.0, MAX_UV_VALUE);

    return ADC_SUCCESS;
}

float get_uv_step(void) {
    return step_uv;
}

void uv_init(void) {
    adc_init(ADC_LINE(UV_ADC_LINE));
    adc_init(ADC_LINE(UV_REFERENCE_ADC_LINE));
}
