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
#include <stdlib.h>
#include <stdbool.h>

#include "net/gnrc/netif.h"
#include "net/dhcpv6/client.h"
#include "net/wot/coap.h"
#include "shell.h"
#include "xtimer.h"

#ifndef IS_NATIVE
extern int led_cmd(int argc, char **argv);
extern void led_cmd_init(void);
#endif

#define MAIN_QUEUE_SIZE (4)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

static const shell_command_t shell_commands[] = {
#ifndef IS_NATIVE
    {"led", "Control an LED.", led_cmd},
#endif
    {NULL, NULL, NULL}};

ipv6_addr_t all_coap_nodes_group_addr = {{ 0xff, 0x02, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0xfd }};

int main(void)
{
    /* Configure netifs for DHCPv6 IA_NA */
    gnrc_netif_t *netif = NULL;
    while ((netif = gnrc_netif_iter(netif))) {
        netif->ipv6.aac_mode |= GNRC_NETIF_AAC_DHCP;
        dhcpv6_client_req_ia_na(netif->pid);
    }

    xtimer_sleep(3);
    /* for the thread running the shell */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    //Todo: Implement auto init
    wot_td_coap_server_init();

    /* join CoAP IPv6 multicast group */
    netif = NULL;
    while ((netif = gnrc_netif_iter(netif))) {
        gnrc_netif_ipv6_group_join(netif, &all_coap_nodes_group_addr);
    }

#ifndef IS_NATIVE
    led_cmd_init();
#endif

    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
