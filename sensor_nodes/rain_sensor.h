/*
 * Copyright (C) 2020, 2021  Cornelius Schulz-Trieglaff <schulztr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jens Bücker <jebu@uni-bremen.de>
 * Copyright (C) 2020, 2021  Maurice Springholz <mau_spr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jan Romann <jan.romann@uni-bremen.de>
 * 
 * SPDX-License-Identifier: LGPL-2.1 OR MIT
 *
 */

#ifndef RAIN_H_
#define RAIN_H_

bool get_rain_value(void);
float get_rain_measurement(void);
float get_rain_precision(void);
unsigned int *get_rain_range(void);
float get_rain_step(void);

#endif // RAIN_H_
