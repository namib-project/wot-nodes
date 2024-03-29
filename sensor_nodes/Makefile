# Makefile for modular Web of Things sensor nodes

# name of your application
APPLICATION = namib_wot_sensor_node

# If no BOARD is found in the environment, use this default:
BOARD ?= esp32-wroom-32

# Absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# Set correcsponding variable to 1 if sensor is available:
DHT ?= 1
RAIN ?= 0
UV ?= 0

# GPIO Bindings
DHT_GPIO = GPIO27
RAIN_GPIO = GPIO32
UV_ADC_LINE = 11 # GPIO33
UV_REFERENCE_ADC_LINE = 13 # GPIO35

# Networking modules
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gcoap

# DHCPv6 modules
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_dhcpv6_client
USEMODULE += auto_init_dhcpv6_client
USEMODULE += dhcpv6_client_ia_na

# Modules for string formatting and memory dumping
USEMODULE += fmt
USEMODULE += od

# Modules for the shell and shell commands
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

# Timer module
USEMODULE += xtimer

# Web of Things
USEMODULE += wot_core
USEMODULE += wot_coap
USEMODULE += wot_coap_config

# ESP modules and configuration
USEMODULE += esp_wifi

WIFI_SSID?=\"Namib\"
WIFI_PASS?=\"NamibTest\"
CFLAGS += -DESP_WIFI_SSID=$(WIFI_SSID)
CFLAGS += -DESP_WIFI_PASS=$(WIFI_PASS)

# MUD DHCPv6 configuration
USEMODULE += dhcpv6_client_mud_url
CFLAGS += -DCONFIG_DHCPV6_CLIENT_MUD_URL=\"https://raw.githubusercontent.com/namib-project/wot-nodes/master/mud_files/sensor-node.mud.json\"

# Common Web of Things definitions
WOT_META_DATA := wot-config/meta-data.json
WOT_BINDINGS_PATH := wot-config/bindings.json
WOT_PLACEHOLDERS_PATH := wot-config/placeholders.json

# Thing Model for the sensor node's location
WOT_THING_MODELS += wot-config/location.tm.json

# Initial location name
CFLAGS += -DINITIAL_LOCATION_NAME=\"Balcony\"

# Sensor specific Thing Models and configurations
ifeq ($(DHT), 1)
USEMODULE += dht
WOT_THING_MODELS += wot-config/dht-sensor.tm.json
CFLAGS += -DDHT_SENSOR
CFLAGS += -DDHT_GPIO=$(DHT_GPIO)
endif
ifeq ($(RAIN), 1)
WOT_THING_MODELS += wot-config/rain-sensor.tm.json
CFLAGS += -DRAIN_SENSOR
endif
ifeq ($(UV), 1)
WOT_THING_MODELS += wot-config/uv-sensor.tm.json
CFLAGS += -DUV_SENSOR
CFLAGS += -DUV_ADC_LINE=$(UV_ADC_LINE)
CFLAGS += -DUV_REFERENCE_ADC_LINE=$(UV_REFERENCE_ADC_LINE)
endif

FEATURES_REQUIRED = periph_adc
CONFIG_MODULE_PERIPH_ADC=y

include $(RIOTBASE)/Makefile.include
