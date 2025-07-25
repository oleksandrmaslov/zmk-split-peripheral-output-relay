/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#define MAX_PAYLOAD_LEN 32

struct zmk_split_bt_output_relay_event {
    uint8_t relay_channel;
    uint8_t value;
    uint8_t payload_size;
    uint8_t payload[MAX_PAYLOAD_LEN];
} __packed;

struct zmk_split_output_event {
    const struct device *dev;
    uint8_t value;
    uint8_t payload_len;
    uint8_t payload[MAX_PAYLOAD_LEN];
};

int zmk_split_bt_invoke_output(const struct device *dev, 
                               struct zmk_split_bt_output_relay_event event);
