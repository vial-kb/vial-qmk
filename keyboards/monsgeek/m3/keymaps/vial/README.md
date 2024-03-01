# Flashing MonsGeek M3

MonsGeek M3 requires `wb32-dfu-uptader` to flash QMK (Vial)

## Debian instructions

These instructions have been tested on Debian Trixie. The binary
`wb32-dfu-updater` will be placed in `/usr/local/bin`

```sh
# you may need some other dependencies
sudo apt install -y cmake
git clone https://github.com/WestberryTech/wb32-dfu-updater
cd wb32-dfu-updater
# script requires sudo privileges to install binaries in /usr/local/
sudo ./boostrap.sh install
# select option 1
```

## Flashing

Once `wb32-dfu-updater` is installed and available on the default `$PATH`,
you can put the keyboard in bootlader moder and run:

```sh
qmk flash -kb monsgeek/m3 -km vial
```

You can put the MonsGeek M3 in bootloader mode by using Via to associate
the special keycode `RESET` to a key of your choice.
