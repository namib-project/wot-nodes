/*
 * Copyright (C) 2020, 2021  Cornelius Schulz-Trieglaff <schulztr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jens Bücker <jebu@uni-bremen.de>
 * Copyright (C) 2020, 2021  Maurice Springholz <mau_spr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jan Romann <jan.romann@uni-bremen.de>
 * 
 * SPDX-License-Identifier: LGPL-2.1 OR MIT
 *
 */

#define GNRC_NETIF_IPV6_GROUPS_NUMOF    (5)

#include <stddef.h>
#include <stdio.h>

#include "led.h"
#include "msg.h"
#include "net/gcoap.h"
#include "net/gnrc/netif.h"
#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#include "net/sock.h"
#include "net/wot/coap.h"
#include "shell.h"
#include "periph/gpio.h"
#include "xtimer.h"

#ifdef DHT_SENSOR
static char _dht_humidity_stack[THREAD_STACKSIZE_DEFAULT];
extern int sensor_set_extreme(int *hum);
#endif
extern int _gnrc_netif_config(int argc, char **argv);
extern int _gnrc_ipv6_nib(int argc, char **argv);

#ifdef DHT_SENSOR
void *_fetch_humidity_values(void *args)
{
    while (1)
    {
        int num;
        if (sensor_set_extreme(&num)) {
            printf("Measured humidity of %d.%01d%%\n", num / 10, num % 10);
        }
        xtimer_sleep(20);
    }
    return NULL;
}
#endif

#define MAIN_QUEUE_SIZE (4)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

#ifdef DHT_SENSOR
#include "dht_sensor.h"
#endif
#ifdef RAIN_SENSOR
extern int rain_cmd(int argc, char **argv);
extern void rain_init(void);
#endif

#ifdef UV_SENSOR
#include "uv_sensor.h"
#endif
#ifdef UV_SENSOR
extern int uv_cmd(int argc, char **argv);
extern void uv_init(void);
#endif


static const shell_command_t shell_commands[] = {
#ifdef DHT_SENSOR
    {"dht", "Reads temperature and humidity (default GPIO: 27).", dht_cmd},
#endif
#ifdef UV_SENSOR
    {"uv", "Reads UV sensor data (default GPIO: 33).", uv_cmd},
#endif
    {NULL, NULL, NULL}};

ipv6_addr_t all_coap_nodes_group_addr = {{ 0xff, 0x02, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xfd }};

int main(void)
{

    /* for the thread running the shell */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("NAMIB sensor prototype app");

#ifdef DHT_SENSOR
    dht_sensor_init();
    thread_create(_dht_humidity_stack, sizeof(_dht_humidity_stack),
                  THREAD_PRIORITY_MIN - 1, THREAD_CREATE_STACKTEST,
                  _fetch_humidity_values, NULL, "dht_fetch_humidity");
#endif

#ifdef RAIN_SENSOR
    rain_init();
#endif

#ifdef UV_SENSOR
    uv_init();
#endif

    wot_td_coap_server_init();

    /* join CoAP IPv6 multicast group */
    gnrc_netif_t *netif = NULL;
    while ((netif = gnrc_netif_iter(netif))) {
        gnrc_netif_ipv6_group_join(netif, &all_coap_nodes_group_addr);
    }

    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should never be reached */
    return 0;
}
