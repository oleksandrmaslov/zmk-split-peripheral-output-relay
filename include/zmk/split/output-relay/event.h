/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

struct zmk_split_bt_output_relay_event {
    uint8_t relay_channel;
    uint8_t value;

    //** TODO: send payload_size & payload, only if size > 0

    // uint8_t payload_size;
    // void *payload;

} __packed;

struct zmk_split_output_event {
    const struct device *dev;
    uint8_t value;

    //** TODO: send payload_size & payload, only if size > 0

    // uint8_t payload_size;
    // void *payload;

};

int zmk_split_bt_invoke_output(const struct device *dev, 
                               struct zmk_split_bt_output_relay_event event);
