# Quantum Mechanical Keyboard Firmware

## このフォークについて

これは [vial-kb/vial-qmk](https://github.com/vial-kb/vial-qmk) の個人用フォークで、
**Keyball39（Pro Micro RP2040 換装版）** 用のキーマップをカスタマイズしたものです。
本体は [holykeebs の QMK フォーク](https://github.com/holykeebs/qmk_firmware) をベースに、
元々 Pro Micro (ATmega32U4) だった Keyball39 を Pro Micro RP2040 に載せ替えて運用しています。

キーマップ本体は [`keyboards/keyball/keyball39/keymaps/my_keymap/`](keyboards/keyball/keyball39/keymaps/my_keymap/) にあり、主な内容は：

- ホームロウ修飾（LALT_T/LGUI_T/LCTL_T/LSFT_T など）を使ったキーマップ
- Keyball標準の特殊キーコード（`KBC_RST`/`CPI_*`/`AML_*`/`SSNP_*` など）をVialの remap 画面上で名前付きで表示できるように対応
- 自作のLEDアニメーション（PLASMA/AURORA/METEOR）を `RGB_MOD`/`RGB_RMOD` の一連の流れに統合
- Dynamic Tapping Term (`DT_UP`/`DT_DOWN`) と Vial の「QMK Settings」パネル（`Tap-Hold`タブ）の数値を、同じ`QS.tapping_term`に一本化して連動するよう修正
- 自動マウスレイヤー、スクロール、CPIなどのEEPROM永続化まわりの調整

詳しい変更点は [`SESSION_NOTES_2026-07-21.md`](keyboards/keyball/keyball39/keymaps/my_keymap/SESSION_NOTES_2026-07-21.md) と、キーマップ内の [`README.md`](keyboards/keyball/keyball39/keymaps/my_keymap/README.md) を参照してください。

ビルドは通常のQMK同様、以下のコマンドで行えます。

```bash
qmk compile -kb keyball/keyball39 -km my_keymap
```

---

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/qmk)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the Clueboard product line.

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls).

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
