/*
 * Copyright (C) 2020, 2021  Cornelius Schulz-Trieglaff <schulztr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jens Bücker <jebu@uni-bremen.de>
 * Copyright (C) 2020, 2021  Maurice Springholz <mau_spr@uni-bremen.de>
 * Copyright (C) 2020, 2021  Jan Romann <jan.romann@uni-bremen.de>
 *
 * SPDX-License-Identifier: LGPL-2.1 OR MIT
 *
 */

#ifndef UV_H_
#define UV_H_

void update_uv(void);
int get_uv_value(float *uv_intensity);
float get_uv_step(void);

#endif // UV_H_
