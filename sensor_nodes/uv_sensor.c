#include <stdio.h>
#include <string.h>

#include "msg.h"
#include "math.h"
#include "periph/gpio.h"
#include "board.h"
#include "periph/adc.h"

#include "uv_sensor.h"

#define RES                       (ADC_RES_12BIT)
#define MAX_UV_VALUE              (15.0)
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
float uvIntensity;

int uv_cmd(int argc, char **argv) {
    if ( strcmp( argv[0] , "uv" ) == 0 ) {
        update_uv();
        printf("UV reference value: %d\n", uv_reference_val);
        printf("UV value: %d\n", recent_val_uv);
        printf("UV intensity: %.2f mW/cm²\n", uvIntensity);
        return 0;
    }

    puts("uv: Invalid command");
    return 1;
}

void update_uv(void) {
    uv_reference_val = adc_sample(ADC_LINE(UV_ADC_LINE), RES);
    recent_val_uv = adc_sample(ADC_LINE(UV_REFERENCE_ADC_LINE), RES);
    uvIntensity = MAX_UV_VALUE / uv_reference_val * recent_val_uv;
}

float get_uv_step(void) {
    return step_uv;
}

void uv_init(void) {
    adc_init(ADC_LINE(UV_ADC_LINE));
    adc_init(ADC_LINE(UV_REFERENCE_ADC_LINE));
}
