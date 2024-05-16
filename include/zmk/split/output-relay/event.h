/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

struct zmk_split_bt_output_relay_event {
  uint8_t relay_channel;
	bool state;
	uint8_t force;
} __packed;

struct zmk_split_output_event {
	const struct device *dev;
	bool state;
	uint8_t force;
};

int zmk_split_bt_invoke_output(const struct device *dev, 
															 struct zmk_split_bt_output_relay_event event);
