# Zmk Split Peripheral Output Relay

This module add a output relay for ZMK. This is an add-on for [zmk-output-behavior-listener](https://github.com/badjeff/zmk-output-behavior-listener) to broadcast output event to split peripheral(s) via bluetooth.

## What it does

This module sideload a new set of GATT Service and Characteratics into existing split bt paired connection. The new characteristics allow to transfer output event from central to peripherals with a relay-channel id. Then, output events would trigger output device(s) on peripheral(s).

## Installation

Include this project on your ZMK's west manifest in `config/west.yml`:

```yaml
manifest:
  remotes:
    # ...
    - name: badjeff
      url-base: https://github.com/badjeff
  projects:
    # ...
    # START #####
    - name: zmk-split-peripheral-output-relay
      remote: badjeff
      revision: main
    # END #######
    # ...
```

In below config, a DRV2605 driven LRA (<&fb_lra0>) will be triggered on peripheral shield on key press `q`.

Additional modules are used in below config:
* [zmk-output-behavior-listener](https://github.com/badjeff/zmk-output-behavior-listener)
* [zmk-drv2605-driver](https://github.com/badjeff/zmk-drv2605-driver)

Update `board.keymap`. The detail explanation for `zmk,output-behavior-listener` and `zmk,output-behavior-generic` could be find at [here](https://github.com/badjeff/zmk-output-behavior-listener/blob/main/README.md).
```keymap
#define OUTPUT_SOURCE_KEYCODE_STATE_CHANGE  3
/{
        lra0_obl__press_key_code_q {
                compatible = "zmk,output-behavior-listener";
                layers = < DEF LHB >;
                sources = < OUTPUT_SOURCE_KEYCODE_STATE_CHANGE >;
                position = < 0x14 >;
                bindings = < &ob_lra0 >;
        };
        ob_lra0: ob_lra0 {
                compatible = "zmk,output-behavior-generic";
                #binding-cells = <0>;
                device = <&fb_lra0>;
                force = <7>;
        };
};
```

Once the trigger is called, `zmk,output-split-output-relay` is used to intercept that event on central, and broadcast it as a payload with a `relay-channel` header via `zmk,split-peripheral-output-relay`.

Update split central devicetree file `board_left.overlay`:
```dts
/{
  fb_lra0: fb_lra0 {
    compatible = "zmk,output-split-output-relay";
    #binding-cells = <0>;
  };
  output_relay_config_201 {
    compatible = "zmk,split-peripheral-output-relay";
    device = <&fb_lra0>;
    relay-channel = <201>;
  };
};
```

On peripheral(s) side, `zmk,output-split-output-relay` is used to decode the payload to output event from `relay-channel`. And, a `zmk,output-haptic-feedback` or `zmk,output-generic` is used to reflect the event context on peripheral(s). Currently, its only supporting one output device per `relay-channel` on same shield, and all shield will be triggered by same event simultaneously.

Update split peripheral devicetree file `board_right.overlay`:
```dts
/ {
  output_relay_config_201_a {
    compatible = "zmk,split-peripheral-output-relay";
    relay-channel = <201>;
    device = <&fb_lra0>;
  };
  fb_lra0: fb_lra0 {
    compatible = "zmk,output-haptic-feedback";
    #binding-cells = <0>;
    driver = "drv2605";
    device = <&drv2605_0>;
  };
};
```
