# Default Makefile, for host native GNRC-based networking

# name of your application
APPLICATION = namib_wot_sensor_node

# If no BOARD is found in the environment, use this default:
BOARD ?= esp32-wroom-32

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# Set this variable to any value, if the sensor is in use.
DHT := 1
RAIN := 1

# GPIO Bindings
DHT_GPIO = GPIO27
RAIN_GPIO = GPIO32

# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Specify the mandatory networking modules
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_dhcpv6_client
USEMODULE += auto_init_dhcpv6_client
USEMODULE += gnrc_dhcpv6_client_mud_url
USEMODULE += gcoap
# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_icmpv6_echo

# Required by gcoap example
USEMODULE += od
USEMODULE += fmt
# Add also the shell, some shell commands
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += esp_wifi
WIFI_SSID?=\"Namib\"
WIFI_PASS?=\"NamibTest\"
CFLAGS += -DESP_WIFI_SSID=$(WIFI_SSID)
CFLAGS += -DESP_WIFI_PASS=$(WIFI_PASS)

USEMODULE += gnrc_dhcpv6_client
USEMODULE += gnrc_dhcpv6_client_mud_url
USEMODULE += gnrc_pktdump
USEMODULE += xtimer

# WoT
USEMODULE += wot_core
USEMODULE += wot_coap
USEMODULE += wot_coap_config

# Triggers for Node Configuration. Currently all are required.
ifeq ($(DHT), 1)
CFLAGS += -DDHT_SENSOR
endif
ifeq ($(RAIN), 1)
CFLAGS += -DRAIN_SENSOR
endif

# Define initial location name
CFLAGS += -DINITIAL_LOCATION_NAME=\"Balkon\"

# Define MUD-URL
CFLAGS += -DDHCPV6_CLIENT_MUD_URL=\"https://git.sr.ht/~s0/MUD-Files/blob/master/temperature-node.json\"

WOT_META_DATA := wot-config/meta-data.json
WOT_BINDINGS_PATH := wot-config/bindings.json
WOT_PLACEHOLDERS_PATH := wot-config/placeholders.json
WOT_THING_MODELS += wot-config/location.tm.json

ifeq ($(DHT), 1)
WOT_THING_MODELS += wot-config/dht_thing-model.tm.json
endif
ifeq ($(RAIN), 1)
WOT_THING_MODELS += wot-config/rain_thing-model.tm.json
endif
CFLAGS += -DDHT_GPIO=$(DHT_GPIO)
CFLAGS += -DRAIN_GPIO=$(RAIN_GPIO)

FEATURES_REQUIRED = periph_adc
CONFIG_MODULE_PERIPH_ADC=y

# add sensor driver(s)
USEMODULE += dht

include $(RIOTBASE)/Makefile.include
