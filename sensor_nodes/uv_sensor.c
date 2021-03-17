#include <stdio.h>
#include <string.h>

#include "msg.h"
#include "math.h"
#include "periph/gpio.h"
#include "board.h"
#include "periph/adc.h"

#include "uv_sensor.h"

#define RES             ADC_RES_12BIT

extern int adc_init (adc_t);
extern int32_t adc_sample (adc_t, adc_res_t);

const float step_uv = 1;

int recent_val_uv;

void update_uv(void) {
    recent_val_uv = adc_sample(ADC_LINE(10), RES);
}

bool get_uv_value(void) {
    update_uv();
    return recent_val_uv;
}

float get_uv_step(void) {
    return step_uv;
}

void uv_init(void) {
    adc_init(ADC_LINE(10));
}
