# Default Makefile, for host native GNRC-based networking

# name of your application
APPLICATION = namib_wot_sensor_node

# If no BOARD is found in the environment, use this default:
BOARD ?= esp32-wroom-32

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# generate random free port
DHCPV6_SERVER_PORT := 67

# GPIO Bindings
DHT_GPIO = GPIO27
RAIN_GPIO = GPIO32

# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Specify the mandatory networking modules
USEMODULE += gnrc_ipv6_default
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
CFLAGS += -DESP_WIFI_SSID=\"Namib\" -DESP_WIFI_PASS=\"NamibTest\"
USEMODULE += gnrc_dhcpv6_client
USEMODULE += gnrc_dhcpv6_client_mud_url
USEMODULE += gnrc_pktdump
USEMODULE += xtimer

# WoT
USEMODULE += wot_core
USEMODULE += wot_coap
USEMODULE += wot_coap_config

# Triggers for Node Configuration. Comment out if node hardware doesn't
# support feature.
CFLAGS += -DDHT_SENSOR
CFLAGS += -DRAIN_SENSOR

# TODO: Rework modular system
WOT_THING_MODEL += wot-config/thing-model.json
WOT_INSTANCE_INFO += wot-config/instance.json

CFLAGS += -DDHCPV6_SERVER_PORT=$(DHCPV6_SERVER_PORT)
ifneq (,$(findstring -DDHT_SENSOR,$(CFLAGS)))
CFLAGS += -DDHT_GPIO=$(DHT_GPIO)
endif
ifneq (,$(findstring -DRAIN_SENSOR,$(CFLAGS)))
CFLAGS += -DRAIN_GPIO=$(RAIN_GPIO)
endif

FEATURES_REQUIRED = periph_adc
CONFIG_MODULE_PERIPH_ADC=y

# add sensor(s)
USEMODULE += dht

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

# For now this goes after the inclusion of Makefile.include so Kconfig symbols
# are available. Only set configuration via CFLAGS if Kconfig is not being used
# for this module.
ifndef CONFIG_KCONFIG_MODULE_GCOAP
## Uncomment to redefine port, for example use 61616 for RFC 6282 UDP compression.
#GCOAP_PORT = 5683
#CFLAGS += -DCONFIG_GCOAP_PORT=$(GCOAP_PORT)

## Uncomment to redefine request token length, max 8.
#GCOAP_TOKENLEN = 2
#CFLAGS += -DCONFIG_GCOAP_TOKENLEN=$(GCOAP_TOKENLEN)

# Increase from default for confirmable block2 follow-on requests
GCOAP_RESEND_BUFS_MAX ?= 2
CFLAGS += -DCONFIG_GCOAP_RESEND_BUFS_MAX=$(GCOAP_RESEND_BUFS_MAX)
endif
