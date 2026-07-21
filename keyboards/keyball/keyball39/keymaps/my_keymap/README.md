# my_keymap — Keyball39 用カスタムキーマップ（RP2040 移植版）

## 背景：Pro Micro → Pro Micro RP2040 への移植

もともと Keyball39 は ATmega32U4 搭載の **Pro Micro** で動いていたが、VIA・OLED・トラックボール・RGB すべてを有効にするとファームウェアが **Pro Micro のフラッシュ容量（32KB）** に収まらなくなった。

そこで **[holykeebs の QMK フォーク](https://github.com/holykeebs/qmk_firmware)** が対応する **Pro Micro RP2040**（フラッシュ 16MB）に換装し、RP2040 ネイティブの PIO half-duplex シリアルで左右通信を行う構成に移行した。

キーマップ本体はすべて `keymaps/my_keymap/` 以下に閉じており、holykeebs のライブラリ本体（`keyboards/keyball/lib/` 等）には手を加えていない。

---

## ハードウェア構成

| 項目 | 内容 |
|------|------|
| キーボード | Keyball39（39 キー + トラックボール） |
| MCU | Pro Micro RP2040（左右ともに同一 .uf2 を書き込む） |
| 左右通信 | PIO half-duplex シリアル（`SERIAL_DRIVER = vendor`） |
| OLED | 0.91 inch 128×32、左右各 1 枚（ポートレート配置） |
| マスター検出 | USB VBUS ピン（`USB_VBUS_PIN GP19`） |

---

## カスタマイズ内容

### 1. レイヤー構成（7 レイヤー）

| レイヤー | 用途 |
|----------|------|
| 0 | デフォルト（QWERTY） |
| 1 | **自動マウスレイヤー**（トラックボール操作時に自動遷移） |
| 2–6 | 任意（VIA で変更可） |

- `AUTO_MOUSE_TIME 650`ms でマウスレイヤーに入り、`AUTO_MOUSE_LAYER_KEEP_TIME 30000`ms で復帰。

### 2. USB HID を 8-bit 報告に戻す

holykeebs のデフォルトは `MOUSE_EXTENDED_REPORT` が有効（±32767 の 16-bit 報告）だが、macOS でポインタ移動が遅く感じられたため無効化した。

```c
#undef MOUSE_EXTENDED_REPORT
#undef WHEEL_EXTENDED_REPORT
```

これにより Pro Micro 時代と同等の ±127 の 8-bit HID 報告に戻る。

### 3. スクロール余り保持（デッドゾーン解消）

デフォルトの `keyball_on_apply_motion_to_mouse_scroll` は毎サイクル余りを捨てるため、スクロール除数が大きいと入力が完全に無視される（デッドゾーン）問題があった。

`__attribute__((weak))` 関数をキーマップ内でオーバーライドし、余りを静的変数で持ち越すことで解消。

```
KEYBALL_SCROLL_DIV_DEFAULT 4  （除数 = 2^(4-1) = 8）
```

### 4. タッピングタームの EEPROM 永続化

`DYNAMIC_TAPPING_TERM_ENABLE` を有効にしつつ、電源を切っても値が消えないよう EEPROM に保存。

- 保存アドレス: bytes 1020–1023（値 + `0xBEEF` マジック）
- VIA のマクロ領域が上書きしないよう `DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 1019` で上限を設定。

### 5. スレーブ OLED へのレイヤー・MOD 同期

`SPLIT_LAYER_STATE_ENABLE` だけでは信頼性が低かったため、独自の RPC トランザクション `MY_LAYER_SYNC` を実装。

- マスターが `housekeeping_task_user` 内でレイヤー番号と MOD 状態（各 1 byte）を毎変化時に送信。
- スレーブが受信して静的変数 `slave_layer` / `slave_mods` に保存し、OLED 描画に利用。

---

## OLED 表示

### マスター OLED（トラックボール側）

```
R?C?   ← 最後に押したキーの行・列
K??    ← キーコード（hex）
????? ← 押しているキー一覧
x NNN  ← トラックボール X 移動量
y NNN  ← トラックボール Y 移動量
CNNNN  ← 現在の CPI
Am:??  ← 自動マウスレイヤー状態
T NNN  ← タッピングターム (ms)
[空白]
[大きな5行レイヤー番号]  ← 0–6
```

### スレーブ OLED（親指側）

```
[押中の MOD キーだけ大きなビットマップ文字で表示]
  1–2 キー → 5 行のビットマップ
  3–4 キー → 3 行のコンパクト版
  なし     → Div:N（スクロール除数）
[空白]
[大きな5行レイヤー番号]  ← マスターと同じ値
```

MOD 表示の文字パターン例（5 行 × 5 文字幅）：

```
S キーが押されたとき
.####
#....
.###.
....#
####.
```

---

## ビルド方法

```bash
qmk compile -kb keyball/keyball39 -km my_keymap
```

生成された `.uf2` を **左右両方** に書き込む（同一ファイル）。  
書き込み中は **TRRS ケーブルを抜いた状態**で行うこと。
