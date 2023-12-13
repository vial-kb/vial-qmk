# EstarDyn Raspberry Pi Pico Clone

Like [this](https://www.aliexpress.us/item/3256803610338545.html)

Because of a difference in how `VIN` and `VOUT` (called `VBUS` and `VSYS` on the genuine Pico) are wired,
`USB_VBUS_PIN` cannot be used.

For the same reason as above, you will have to bridge the `VIN` and `VOUT` pins for the right half to be powered properly

The EstarDyn clone has a ws2812 wired to pin `GP23`. Both (one per half) have been enabled 
in this config and configured as layer indicator leds
