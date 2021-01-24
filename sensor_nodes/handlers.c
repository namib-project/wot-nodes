#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net/gcoap.h"
#include "od.h"
#include "fmt.h"

#ifdef DHT_SENSOR
#include "dht_sensor.h"
#endif

#ifdef RAIN_SENSOR
#include "rain_sensor.h"
#endif

#ifdef DHT_SENSOR
ssize_t _dht_hum_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    int h100 = sensor_get_humidity();
    char bufstr[10];
    sprintf(bufstr, "%d.%01d", h100 / 10, h100 % 10);

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the humidity in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_hum_unit_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char *unit_h = sensor_get_humidity_unit();

    char bufstr[strlen(unit_h)];
    sprintf(bufstr, "%s", unit_h);

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the humidity in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_hum_min_range_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    int min = sensor_get_humidity_min_range();

    if (min == -1)
        return gcoap_response(pdu, buf, len, COAP_CODE_NOT_IMPLEMENTED);

    char bufstr[10];
    sprintf(bufstr, "%d.%01d", min / 10, min % 10);

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the humidity in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_hum_max_range_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    int max = sensor_get_humidity_max_range();

    if (max == -1)
        return gcoap_response(pdu, buf, len, COAP_CODE_NOT_IMPLEMENTED);

    char bufstr[10];
    sprintf(bufstr, "%d.%01d", max / 10, max % 10);

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the humidity in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_hum_step_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    int step = sensor_get_humidity_step();

    if (step == -1)
        return gcoap_response(pdu, buf, len, COAP_CODE_NOT_IMPLEMENTED);

    char bufstr[10];
    sprintf(bufstr, "%d.%01d", step / 10, step % 10);

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the humidity in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_hum_precision_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    int precision = sensor_get_humidity_precision();

    if (precision == -1)
        return gcoap_response(pdu, buf, len, COAP_CODE_NOT_IMPLEMENTED);

    char bufstr[10];
    sprintf(bufstr, "%d.%01d", precision / 10, precision % 10);

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the humidity in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_hum_min_value_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    int min = sensor_get_humidity_min();

    if (min == -1)
        return gcoap_response(pdu, buf, len, COAP_CODE_NOT_IMPLEMENTED);

    char bufstr[10];
    sprintf(bufstr, "%d.%01d", min / 10, min % 10);

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the humidity in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_hum_max_value_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    int max = sensor_get_humidity_max();

    if (max == -1)
        return gcoap_response(pdu, buf, len, COAP_CODE_NOT_IMPLEMENTED);

    char bufstr[10];
    sprintf(bufstr, "%d.%01d", max / 10, max % 10);

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the humidity in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_hum_reset_min_max_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;

    unsigned method_flag = coap_method2flag(coap_get_code_detail(pdu));

    if (method_flag == COAP_POST)
    {
        sensor_humidity_reset_extreme();
        return gcoap_response(pdu, buf, len, COAP_CODE_VALID);
    }

    return 0;
}

ssize_t _dht_temp_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    int t100 = sensor_get_temperature();
    int rest = t100 % 100;
    char bufstr[10];
    sprintf(bufstr, "%d.%02d", t100 / 100, rest);

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the temperature in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_temp_unit_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char bufstr[2];
    sprintf(bufstr, "%u", sensor_get_temperature_unit());

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the temperature in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_temp_range_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char bufstr[10];
    int *range = sensor_get_temperature_range();
    if (range)
    {
        sprintf(bufstr, "[%d.%02d,%d.%02d]", range[0] / 100, range[0] % 100, range[1] / 100, range[1] % 100);
    }
    else
    {
        puts("gcoap_cli: resource not given");
        return gcoap_response(pdu, buf, len, COAP_CODE_NOT_IMPLEMENTED);
    }

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the temperature in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_temp_step_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char bufstr[6];
    int step = sensor_get_temperature_step();
    if (step != -1)
    {
        sprintf(bufstr, "%d.%01d", step / 10, step % 10);
    }
    else
    {
        puts("gcoap_cli: resource not given");
        return gcoap_response(pdu, buf, len, COAP_CODE_NOT_IMPLEMENTED);
    }

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the temperature in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_temp_precision_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char bufstr[6];
    int precision = sensor_get_temperature_precision();
    if (precision != -1)
    {
        sprintf(bufstr, "%d.%01d", precision / 10, precision % 10);
    }
    else
    {
        puts("gcoap_cli: resource not given");
        return gcoap_response(pdu, buf, len, COAP_CODE_NOT_IMPLEMENTED);
    }

    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the temperature in the response buffer */
    if (pdu->payload_len >= strlen(bufstr))
    {
        memcpy(pdu->payload, bufstr, strlen(bufstr));
        return resp_len + strlen(bufstr);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

    return 0;
}

ssize_t _dht_temp_set_unit_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;

    /* read coap method type in packet */
    unsigned method_flag = coap_method2flag(coap_get_code_detail(pdu));

    if (method_flag == COAP_POST)
    {
        char payload_str[(pdu->payload_len) + 1];
        strncpy(payload_str, (const char *)pdu->payload, pdu->payload_len);
        errno = 0;
        char *endptr;
        int payload_i = strtol(payload_str, &endptr, 10);
        if (!errno && endptr != payload_str)
        { //wenn der payload mit etwas nützlichem beginnt wird es verwendet
            if (validUnit(payload_i))
            {
                sensor_set_temperature_unit(payload_i);
                printf("Unit was changed to %u \n", payload_i);
                return gcoap_response(pdu, buf, len, COAP_CODE_VALID);
            }
            else
            {
                return gcoap_response(pdu, buf, len, COAP_CODE_BAD_REQUEST);
            }
        }
        else
        {
            return gcoap_response(pdu, buf, len, COAP_CODE_BAD_REQUEST);
        }
    }

    return 0;
}
#endif

#ifdef RAIN_SENSOR

ssize_t _rain_precision_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char val[6];
    snprintf(val, 6, "%f", get_rain_precision());
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    if (pdu->payload_len >= strlen(val))
    {
        memcpy(pdu->payload, val, strlen(val));
        return resp_len + strlen(val);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }
}

ssize_t _rain_step_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char val[6];
    snprintf(val, 6, "%f", get_rain_step());
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    if (pdu->payload_len >= strlen(val))
    {
        memcpy(pdu->payload, val, strlen(val));
        return resp_len + strlen(val);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }
}

ssize_t _rain_value_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char *val = get_rain_value() ? "true" : "false";
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    if (pdu->payload_len >= strlen(val))
    {
        memcpy(pdu->payload, val, strlen(val));
        return resp_len + strlen(val);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }
}

ssize_t _rain_measurement_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char val[4];
    sprintf(val, "%4f", get_rain_measurement());
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    if (pdu->payload_len >= strlen(val))
    {
        memcpy(pdu->payload, val, strlen(val));
        return resp_len + strlen(val);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }
}

ssize_t _rain_range_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;
    char val[] = "";
    unsigned int *ans = get_rain_range();
    sprintf(val, "[%d,%d]", ans[0], ans[1]);
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    if (pdu->payload_len >= strlen(val))
    {
        memcpy(pdu->payload, val, strlen(val));
        return resp_len + strlen(val);
    }
    else
    {
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }
}
#endif