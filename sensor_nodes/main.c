/*
 * Copyright (c) 2015-2016 Ken Bannister. All rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       gcoap example
 *
 * @author      Ken Bannister <kb2ma@runbox.com>
 *
 * @}
 */

#include <stdio.h>
#include "msg.h"

#include "net/gcoap.h"
#include "shell.h"
#include "led.h"
#include "periph/gpio.h"

#include <stddef.h>

#include "net/gnrc/netif.h"
#include "net/dhcpv6/client.h"
#include "net/sock.h"
#include "xtimer.h"
#include "net/wot/coap.h"

#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"

static char _dhcpv6_client_stack[DHCPV6_CLIENT_STACK_SIZE];
#ifdef DHT_SENSOR
static char _dht_humidity_stack[THREAD_STACKSIZE_DEFAULT];
extern int sensor_set_extreme(int *hum);
#endif
extern int _gnrc_netif_config(int argc, char **argv);
extern int _gnrc_ipv6_nib(int argc, char **argv);

void *_dhcpv6_client_thread(void *args)
{
    event_queue_t event_queue;
    gnrc_netif_t *netif = gnrc_netif_iter(NULL);

    (void)args;
    /* initialize client event queue */
    event_queue_init(&event_queue);
    /* initialize DHCPv6 client on any interface */
    dhcpv6_client_init(&event_queue, SOCK_ADDR_ANY_NETIF);
    /* configure client to request prefix delegation of /64 subnet
     * interface netif */
    dhcpv6_client_req_ia_pd(netif->pid, 64U);
    /* start DHCPv6 client */
    dhcpv6_client_start();
    /* start event loop of DHCPv6 client */
    event_loop(&event_queue); /* never returns */
    return NULL;
}

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

int main(void)
{
    /* DHCPv6 Client */

    char *pl[] = {"nib", "prefix"};

    _gnrc_netif_config(0, NULL);
    thread_create(_dhcpv6_client_stack, DHCPV6_CLIENT_STACK_SIZE,
                  DHCPV6_CLIENT_PRIORITY, THREAD_CREATE_STACKTEST,
                  _dhcpv6_client_thread, NULL, "dhcpv6-client");
    xtimer_sleep(5);

    /* global address should now be configured */

    _gnrc_netif_config(0, NULL);
    _gnrc_ipv6_nib(2, pl);

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

    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should never be reached */
    return 0;
}
