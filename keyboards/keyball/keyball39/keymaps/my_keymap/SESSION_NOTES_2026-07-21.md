# 作業記録 (2026-07-21〜07-22)

Keyball39用キーマップ (`keymaps/my_keymap/`) に対して行った変更のまとめ。

## 1. Keyball標準特殊キーコードをVialで名前付き表示できるようにした

Keyballドライバ本体 (`lib/keyball/keyball.h`) が提供する16個の特殊キーコード
(`KBC_RST` / `KBC_SAVE` / `CPI_I100` / `CPI_D100` / `CPI_I1K` / `CPI_D1K` /
`SCRL_TO` / `SCRL_MO` / `SCRL_DVI` / `SCRL_DVD` / `AML_TO` / `AML_I50` /
`AML_D50` / `SSNP_VRT` / `SSNP_HOR` / `SSNP_FRE`) が、`vial.json` の
`customKeycodes` に登録されておらず、Vial上で生の値やそっけない名前 (`Kb 0`など)
としてしか表示されていなかった。

- `vial.json` の `customKeycodes` 配列の先頭に、この16個を正しい順序 (`QK_KB_0`
  から順に対応) で追加。
- 既存のカスタムキー (`ESC_ML` 系、`MY_ANI`) は配列の末尾にそのまま残した。

### 副次的に見つかった不整合の修正

Vialの `customKeycodes` はインデックス0が `QK_KB_0` (`0x7E00`) に対応する仕様
だが、`keymap.c` 側の独自キーコード (`ESC_ML` など) は
`KEYBALL_SAFE_RANGE`(=`QK_USER_0`=`0x7E40`) を起点にしていた。これはズレていて、
Vial上で「Exit AML」等を選んでキーに割り当てると、実際にはKeyballの特殊キー
(`KBC_RST`等)の値が書き込まれてしまうバグが潜在していた。

- `enum my_keycodes` の起点を `KEYBALL_SAFE_RANGE` → `QK_KB_16` に変更し、
  `vial.json` の並び順と実際のキーコード値を一致させた。

## 2. `shortName` のキーキャップはみ出しを修正

`KBC_RST` や `CPI_I100` など7〜8文字の `shortName` がVialのキーキャップ表示で
はみ出していたため、5文字以内に短縮 (`KbRst` / `Cpi+1` など)。`name` フィールド
には元のキーコード名を括弧書きで残し、ツールチップ等で確認できるようにした。

## 3. Dynamic Tapping Term (`DT_PRNT`/`DT_UP`/`DT_DOWN`) の命名対応

これらはQMK標準の"Quantum"機能キーコード (`0x7C70`台) で、`vial.json`の
`customKeycodes` (`QK_KB`範囲専用) では名前を付けられない。同じ挙動をする
独自キー `MY_DT_PRNT` / `MY_DT_UP` / `MY_DT_DOWN` (`QK_KB_20`〜`22`) を追加し、
`vial.json` で名前を付けられるようにした。レイアウト上の `DT_DOWN`/`DT_UP` も
新しいキーに置き換え済み。

## 4. タッピングターム管理を`QS.tapping_term`一本化に統合

**発端**: `MY_DT_UP`/`DOWN`で調整した値がVialの「QMK Settings」パネルの数値と
連動していない、という相談。

**調査の過程でわかったこと**:
- Vial本体 (`quantum/vial.c`) は、`TAPPING_TERM_PER_KEY`が有効な場合
  (Vialのデフォルト設定で常に有効)、`get_tapping_term()`という関数を既に強い
  シンボルとして提供しており、これが`QS.tapping_term`
  (`quantum/qmk_settings.c`、Vialの「QMK Settings」→「Tap-Hold」パネルが
  読み書きする実体)を返す。
- 一方、それまでの`DT_UP`/`DT_DOWN`は独立した`g_tapping_term`という変数
  (独自实装のraw EEPROM保存付き、`Dynamic Tapping Term`機能)を操作していた。
- 実際にキー判定へ使われるのは`get_tapping_term()`の戻り値の方なので、
  理屈上は`g_tapping_term`側の調整が実際の挙動に反映されていなかった可能性が
  あった。

**行った変更**:
- 独自EEPROM保存 (`tt_save`/`tt_load`、`TT_EEPROM_VAL`/`TT_EEPROM_MAGIC`) と
  `g_tapping_term`、`housekeeping_task_user`内の自動保存ポーリングを削除。
- `MY_DT_UP`/`MY_DT_DOWN`/`MY_DT_PRNT`は`QS.tapping_term`を直接
  `qmk_settings_set()`経由で読み書きするように変更 (EEPROM保存も自動)。
- OLED表示 (`oledkit_render_info_user`の`T NNN`行) も`QS.tapping_term`を
  参照するように修正。
- `rules.mk`から`DYNAMIC_TAPPING_TERM_ENABLE = yes`を削除 (もう使わないため)。
- `config.h`の該当コメントを更新 (実際の`#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR
  4091`の値自体は、EEPROMレイアウト変更によるリセットリスクを避けるため変更せず
  据え置き)。

**実機ログでの検証**: `qmk console`でログを確認したところ、`MY_DT_UP`/`DOWN`は
正常に`QS.tapping_term`を書き換えていた (`rc=0`)。Vial側の「QMK Settings」で
値を変更した場合にログが出なかったため一時的に「GUI側のキャッシュ問題では」と
疑ったが、**最終的には「Tap Dance」タブと「Tap-Hold」タブを見間違えていた**こと
が判明。実際は最初から正常に連動していた (誤報告、実装に問題なし)。

デバッグ用に追加した`uprintf`ログ (`housekeeping_task_user`内の変化検知、
`MY_DT_UP`/`DOWN`内の詳細ログ) は調査完了後に削除済み。

副次的な発見: このビルドではVial側のオプション (`build_vial.mk`) が
`-DNO_DEBUG`を強制するため、`dprintf`は常に無効 (既存コードの
`dprintf("is_master: ...")`も含め、これまで一度もコンソールに出力されていな
かった)。デバッグ出力が必要な場合は`uprintf`/`xprintf`を使うこと。

## 5. Vialで調整済みのキーマップをソースに焼き込み

Vialでエクスポートしたキーマップ (8レイヤー) を`LAYOUT_universal`の引数順に
変換し、`keymap.c`の`keymaps[]`配列を丸ごと置き換えた。ホームロウ修飾
(`LALT_T`等)、レイヤータップ、独自キーコードなどをすべて正しい識別子に変換。

### 見つかった問題と対応

- **LEDアニメキーが死んでいた**: エクスポートに生の`0x7e43`という値が1箇所
  残っていた。これは上記4番の変更前、`ESC_ML`系が`QK_USER_0`起点だった頃の
  `MY_ANI`の値の残骸で、enum起点変更後は何にも対応しない値になっていた。
  `MY_ANI`として正しく書き直した。
- **VialのダイナミックマクロM1/M2をコンパイル済みキーに置き換え**:
  「LNG1/LNG2をタップしてレイヤー0に戻る」という内容のマクロだったが、
  EEPROM保存に依存しないよう`LNG1_TO0`/`LNG2_TO0`という新しいカスタム
  キーコード (`QK_KB_23`/`24`) として実装し直した。`vial.json`にも登録。

**重要な注意**: `keymap.c`内の配列はEEPROM未初期化時のみ使われる初期値。
普段はEEPROM上のVial保存内容がそのまま使われるため、今回の変更をフラッシュ
しても体感上の挙動は変わらない (今回の目的はソースへのバックアップ)。

## 6. LEDアニメーション実装についての質疑

`RGB_MOD`/`RGB_RMOD`を使った自作アニメーション (`MY_ANI`,
PLASMA/AURORA/METEOR) の実装が複雑だった理由を確認。

- このキーボードが使う**RGBLIGHT**(単純なLEDテープ用)には、`RGB_MATRIX`に
  ある`RGB_MATRIX_CUSTOM_EFFECT_IMPLS`のような「自作エフェクトを正式なモード
  として登録する」公式な拡張機構が存在しない。
- 現実的な選択肢は「QMKコア(`rgblight.c`)を直接改造」か「RGB_MATRIXへ全面
  移行」の2つで、どちらも今回のキーマップ単体で完結する方法ではないため、
  既存の「ネイティブモードを一周後に自前ステートマシンへ引き継ぐ」実装が
  現実的な落とし所だった。

## 7. 設定確認

- `COMBO_ENABLE = yes` (`rules.mk`)。`COMBO_TERM 100`、
  `COMBO_ONLY_FROM_LAYER 0`も設定済み。ただしVial側のコンボ定義は現状未設定。
- `QMK_SETTINGS = yes` はVialビルドのデフォルト (`builddefs/build_vial.mk`)
  で有効になっており、キーマップ側で上書きしていないため有効。

## 変更したファイル

- `keyboards/keyball/keyball39/keymaps/my_keymap/keymap.c`
- `keyboards/keyball/keyball39/keymaps/my_keymap/vial.json`
- `keyboards/keyball/keyball39/keymaps/my_keymap/rules.mk`
- `keyboards/keyball/keyball39/keymaps/my_keymap/config.h` (コメントのみ)

## 未対応・要フォローアップ

- `README.md`の「4. タッピングタームのEEPROM永続化」の節は、今回の変更で
  古い実装 (`bytes 1020–1023`への独自保存) を前提にした説明になっており、
  実態 (`QS.tapping_term`経由) と合わなくなっている。更新が必要。
- RGB_MATRIXへの移行は「また考える」とのことで保留中。
