# NAMIB MUD and WoT Nodes

This repository contains RIOT applications which both support the Manufacturer Usage Description (MUD, RFC 8520) and the Web of Things Thing Description (WoT TD).
They are designed to be used with ESP32 boards from Espressif but can be easily adapted to other boards supported by RIOT.
The applications (an LED controller and a modular sensor node) were developed as part of the bachelor computer science project NAMIB, which is based at the University of Bremen, Germany.

To realize MUD Support, the nodes use DHCPv6 and include the MUD option that is specified in RFC 8520 in request, renew, and rebind messages.
To realize support for the WoT Thing Description, so called Thing Models (TMs) and additional information can be specified during compile time which are then transformed into the needed data structures to create a TD dynamically at runtime.
A decive's TD can be retrieved using CoAP by either sending a GET request to `/.well-known/wot-thing-description` or by quering `/.well-known/core` and extracting the link which points to the TD resource by its content or resource type.

## Setup

The repository contains scripts that can be used to set up the ESP toolchain, install the needed dependencies, and flashing an application to an ESP32.
On Ubuntu or other systems that support `apt` the `install_dependencies.sh` script in the folder `installer_scripts` can be used to install all of the needed packages (as root).
The ESP toolchain from espressif can be installed in the `home` directory by using the `install_esp_toolchain.sh` script provided in the same directory.
This second script should not be executed as root.
However, both scripts need to be declared executable by using `sudo chmod +x`.
Finally, as the actual basis on which the applications will run the RIOT OS submodule has to be retrieved by using `git submodule update --init --recursive`.

After installing the needed dependencies, the applications can be compiled by navigating into their respective directory in a terminal and executing `../compile_esp_app.sh`.
For compiling and flashing the appplication onto an ESP32 you can run the script with the argument `flash`, i. e. `../compile_esp_app.sh "flash"`.
An arbitrary number of options like the USB port that should be used for flashing can be specified in the second argument, e. g. `../compile_esp_app.sh "flash" "PORT=/dev/ttyUSB1"`.
