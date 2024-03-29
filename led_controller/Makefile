# name of your application
APPLICATION = wot_coap

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# WoT
USEMODULE += wot_core
USEMODULE += wot_coap
USEMODULE += wot_coap_config
USEMODULE += xtimer

WOT_META_DATA := wot-config/meta-data.json
WOT_BINDINGS_PATH := wot-config/bindings.json
WOT_PLACEHOLDERS_PATH := wot-config/placeholders.json
WOT_THING_MODELS += wot-config/thing_model.json

ifeq ($(BOARD),esp32-wroom-32)
# ESP wifi configuration
USEMODULE += esp_wifi
WIFI_SSID?=\"Namib\"
WIFI_PASS?=\"NamibTest\"
CFLAGS += -DESP_WIFI_SSID=$(WIFI_SSID)
CFLAGS += -DESP_WIFI_PASS=$(WIFI_PASS)

# GPIO Bindings
LED_GPIO = GPIO33
CFLAGS += -DLED_GPIO=$(LED_GPIO)
endif

ifeq ($(BOARD),native)
CFLAGS += -DIS_NATIVE
endif

# Shell
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Activate ICMPv6 error messages
USEMODULE += gnrc_icmpv6_error
USEMODULE += gnrc_icmpv6_echo
# Specify the mandatory networking modules for IPv6 and UDP
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_udp
# Add a routing protocol
USEMODULE += gnrc_rpl
USEMODULE += auto_init_gnrc_rpl
# This application dumps received packets to STDIO using the pktdump module
USEMODULE += gnrc_pktdump
# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_icmpv6_echo
USEMODULE += netstats_l2
USEMODULE += netstats_ipv6
USEMODULE += netstats_rpl

USEMODULE += gnrc_dhcpv6_client
USEMODULE += auto_init_dhcpv6_client
USEMODULE += dhcpv6_client_ia_na
USEMODULE += dhcpv6_client_mud_url
CFLAGS += -DCONFIG_DHCPV6_CLIENT_MUD_URL=\"https://raw.githubusercontent.com/namib-project/wot-nodes/master/mud_files/sensor-node.mud.json\"

# Enables DTLS-secured CoAP messaging
GCOAP_ENABLE_DTLS ?= 0
ifeq (1,$(GCOAP_ENABLE_DTLS))
	# Required by DTLS. Currently, only tinyDTLS is supported by sock_dtls.
	USEPKG += tinydtls
	USEMODULE += sock_dtls
	USEMODULE += tinydtls_sock_dtls
	USEMODULE += gcoap_dtls
	# tinydtls needs crypto secure PRNG
	USEMODULE += prng_sha1prng

	# Maximum number of DTLS sessions
	CFLAGS += -DDTLS_PEER_MAX=1

	CFLAGS += -DWOT_GCOAP_DTLS_ID=\"Client_identity\"
	CFLAGS += -DWOT_GCOAP_DTLS_PSK=\"secretPSK\"
	CFLAGS += -DWOT_GCOAP_DTLS_CREDENTIAL_TAG=8
	CFLAGS += -DGCOAP_STACK_SIZE=1536
endif

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
