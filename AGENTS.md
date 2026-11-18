# AGENTS.md

Personal QMK fork. The only thing that matters here is the **`retro` keymap for a handwired Dactyl Manuform 5x6**:
`keyboards/handwired/dactyl_manuform/5x6/keymaps/retro/`. Everything else is upstream QMK.

## Files

| File | Role |
|---|---|
| `retro/keymap.c` | Hand-written: layer/keycode enums, all custom keycode logic (`process_record_user`), tri-layers. `#include`s `retro_keymap.c`. |
| `retro/retro_keymap.c` | **GENERATED** by `qmk json2c backups/manuform_5x6.json`. Contains the `keymaps[]` array (one `LAYOUT_5x6(...)` per layer). Don't hand-edit — edit the JSON (or in QMK Configurator) and regenerate. |
| `backups/manuform_5x6.json` | QMK Configurator export — source of truth for the layer contents. Custom keycodes appear as `ANY(NAME)`. |
| `retro/combos.def` | String-substitution combos (`SUBS(name, "text", keys...)`) via `keyboards/gboards/g/keymap_combo.h` (`VPATH += keyboards/gboards/` in `rules.mk`). |
| `retro/config.h` | `MASTER_LEFT`, `USE_SERIAL`, `TAPPING_TOGGLE 2`, `RETRO_TAPPING`(+`_PER_KEY`, no callback defined), `HOLD_ON_OTHER_KEY_PRESS`, `COMBO_VARIABLE_LEN`, `ABBR_TERM 500`, and the `LT(0, …)` tap/hold aliases. Default TAPPING_TERM/COMBO_TERM. |
| `retro/rules.mk` | `UNICODE_ENABLE`, `COMBO_ENABLE`. Board: atmega32u4 / caterina, mousekeys + extrakeys on. |
| `update.sh` / `waitforupdate.sh` / `push.sh` / `flash.sh` (repo root) | WSL workflow: watch Downloads for the Configurator JSON export → copy to `backups/manuform_5x6.json` → `json2c` → `make handwired/dactyl_manuform/5x6:retro` → commit `updateBackup` → push. `flash.sh` runs from its own dir: `git pull` + `make …:retro:flash` (avrdude/caterina; needs usbipd-win to see the board from WSL — not set up). |

**Keymap finder web app** — `keymap-viewer/` (static `index.html` + `app.js` + `style.css`, no build step). It reads `backups/manuform_5x6.json` and `combos.def` at runtime, so it follows keymap changes automatically. Human labels for custom keycodes, layer names and the CSA character table are hardcoded in `app.js` (`CUSTOM`, `LAYER_NAMES`, `CSA`) — update them when adding custom keycodes or layers. "How to reach" a layer is computed (BFS over hold keys + `TRI_LAYERS`). Local preview: `python -m http.server 8137` from repo root → `http://localhost:8137/keymap-viewer/` (`.claude/launch.json` has this). Deployed by `.github/workflows/keymap-viewer.yml` to GitHub Pages (repo Settings → Pages → Source: GitHub Actions); the workflow strips combo lines containing `@` before publishing.

**GitHub Actions on the fork:** every upstream QMK workflow is **disabled on GitHub** (`gh workflow disable`, not deleted, so upstream merges don't conflict); only `Keymap viewer` (and GitHub's automatic Dependency Graph) stay active. After merging upstream, check `gh workflow list -R billybraga/qmk_firmware --all` and disable any newly added upstream workflow.

Build: `make handwired/dactyl_manuform/5x6:retro` (or `qmk compile -kb handwired/dactyl_manuform/5x6 -km retro`).

## OS layout assumption: Canadian Multilingual Standard (CSA)

The host OS uses **Canadian Multilingual Standard** (`sendstring_canadian_multilingual.h`). So keycodes do NOT mean their US names. Translation used throughout this doc:

| Keycode | Produces | | Keycode | Produces |
|---|---|---|---|---|
| `KC_SLSH` | é (shift: É) | | `KC_GRV` | `/` (shift `\`, AltGr `\|`) |
| `KC_QUOT` | è | | `KC_BSLS` | à |
| `KC_RBRC` | ç | | `KC_LBRC` | `^` dead key (shift: `¨` dead, AltGr: `` ` `` dead) |
| `S(KC_COMM)` / `KC_LT` | `'` | | `S(KC_DOT)` | `"` |
| `S(KC_6)` / `KC_CIRC` | `?` | | `AltGr+,` / `AltGr+.` | `<` / `>` |
| `AltGr+7/8/9/0` | `{ } [ ]` | | `KC_SCLN` / shift | `;` / `:` |

## Physical layout & `LAYOUT_5x6` argument order

`LAYOUT_5x6` takes 64 args: 4 rows × (6 left + 6 right), then the 16 bottom/thumb keys in this order:
`L42 L43, R42 R43, L44 L45, R40 R41, L54 L55, R50 R51, L52 L53, R52 R53`.

- `L42 L43` / `R42 R43`: the two-key bottom row under columns 3-4 (ring/middle).
- Thumb cluster row 1 (main thumbs): `L44 L45` (L45 = innermost) / `R40 R41` (R40 = innermost).
- Below the main thumb pair, the other 4 thumb keys form a **diamond** (confirmed by the user for the left side; right side assumed mirrored):
  left: top `L55` (Alt), outer `L54` (MO6), inner `L53` (MO9), bottom `L52` (Win) — right: top `R50` (Bksp), outer `R51` (MO3), inner `R52` (L9_ALT), bottom `R53` (RCtrl).

Below, grids are written `col0 … col5 ‖ col0 … col5` (left half ‖ right half). Generated-file index of key in a row: left = 0-5, right = 6-11.

## Layers

Enum names in `keymap.c` are **misleading**: `_QWERTY` (0) is actually the BÉPO-style layout, `_BEPO` (1) is actually QWERTY.

| # | Enum | What it is | How to reach |
|---|---|---|---|
| 0 | `_QWERTY` | **Base: BÉPO-like French layout** | default |
| 1 | `_BEPO` | QWERTY letters overlay (thumbs fall through to 0) | `DF(1)` on layer 3 |
| 2 | `_R_THUM_2_4` | Nav (right) + mouse/symbols (left) | hold `R_THUM_2_4` (right thumb R41) |
| 3 | `_L_THUM_3_4` | F-keys (left) + numpad (right) + default-layer switches | hold `L_THUM_3_4` (left thumb L44) **or** `MO(3)` (R51) |
| 4 | `_THUMBS` | Symbols (left) + window management (right) | tri-layer: 2 + 3 together |
| 5 | `_CTL_ENT` | Ctrl + QWERTY-position shortcuts | hold `CTL_ENT_5` (left thumb L45) |
| 6 | `_L_THUMB2` | Left nav cluster + Ctrl+digits (right) | `MO(6)` (L54) |
| 7 | `_L2_THUMB` | Ctrl+Shift + QWERTY-position shortcuts | `MO(7)` from layer 3 (L45) or 5 (L44) |
| 8 | `_R2_THUMB` | Mouse (left) + Ctrl+Shift+arrows (right) | `MO(8)` from layer 2 (R40) |
| 9 | `_L_THUMB_R_KB_NUMS` | Left-hand numpad + Win+N taskbar (right) | `MO(9)` (L53) or `L9_ALT` (R52 = Alt held + layer 9) |
| 10 | `_NOLAN` | Plain US-style QWERTY (full number row, shifted one column) | `DF(10)` on layer 3 |
| 11 | `_BEPO_SFT` | Shift layer for base (shift held + overrides) | hold `BEPO_SFT_11_12` (L20 or R35) |
| 12 | `_SFT_ARROWS` | Shift+nav (selection) | tri-layer: 2 + 11 |
| 13 | `_ARROWS` | Base + arrows on right home (TRNS elsewhere, L45 = Enter) | `DF(13)` on layer 3 |

Tri-layers (`layer_state_set_user`): `2 + 3 → 4`, `2 + 11 → 12`.
Default-layer switches live on layer 3 thumbs: `L54=DF(0)`, `L55=DF(13)`, `L52=DF(10)`, `L53=DF(1)`. (With a non-0 default, transparent keys resolve down to layer 0.)

### Layer 0 — base (BÉPO-like)
```
Esc   MuteTeams/DeskL  Sft+Alt+←  Sft+Alt+→  Win+H(voice) Play  ‖ Alt+R  ←/Prev  Vol-  Vol+  →/Next  Win+L
Tab   b     é     p     o     è                             ‖ w     v     d     l     j     z
Shift a     u     i     e     ,(Alt:PgUp)                   ‖ c     t     s     r     n     m
Ctrl  à     y     x     .     '                             ‖ k     q     g     h     f     Shift
            ù     ^dead                                     ‖             ç     =
Thumbs L: L44=L_THUM_3_4(L3)  L45=CTL_ENT_5   L54=MO(6)  L55=LAlt   L52=LGui  L53=MO(9)
Thumbs R: R40=Space           R41=R_THUM_2_4(L2) R50=Bksp R51=MO(3) R52=L9_ALT R53=RCtrl
```
"Shift" = `BEPO_SFT_11_12` (Shift + layer 11), not plain LSFT.

### Layer 1 — QWERTY overlay
Rows 1-3 = standard QWERTY letters (`q w e r t y u i o p ^` / `Shift a s d f g h j k l ; è` / `z x c v b n m , . é ¨`), `L43 = à`. Everything else transparent → layer 0 (thumbs, top row). Note L20 becomes plain LSFT here.

### Layer 2 — R_THUM (right thumb outer)
```
·     1     2     MStop  4    PAUSE_ANSWER(no-op) ‖ —      F7    F8    F9    F10   F11
·     '     ~     MsUp   |    L_ARR1               ‖ Win+1  PgUp  ↑     Home  —     ç
·     "     MsL   MsDn   MsR  ·                    ‖ Home   ←     ↓     →     End   RShift
·     `     WhUp  Btn1   WhDn L_ARR2               ‖ Bksp   PgDn  ↓     End   Del   Enter
            <     >                                ‖              ·     KP0
R40 = MO(8); L53 = TG(14) (layer 14 doesn't exist — dead key)
```

### Layer 3 — L_THUM (F-keys + numpad)
```
PrtSc  ·      ·      ·        Win+Spc ·     ‖ F6    F7  F8  F9  Alt+R  Power*
F12    F1     F2     F3       F4   F5       ‖ _     1   2   3   {      }
C+F12  Bksp   Del    F10      F11  S+F11    ‖ KP-   4   5   6   [      ]
S+F12  C+Bksp S+Del  C+A+Ent  Spc  C+F5     ‖ Menu  7   8   9   /      \
              LCtrl  Ctrl+.                 ‖           0   .
L45 = MO(7); R40 = Ctrl+Shift+Space; L54/L55/L52/L53 = DF(0)/DF(13)/DF(10)/DF(1)
```
*Power: only sent on **release of the `L_THUM_3_4` key** (safety). Reached via `MO(3)` it is never sent.

### Layer 4 — THUMBS (layers 2+3)
```
Sft+Alt+0  ·  ·  ·  ·   ·   ‖ ·           ·            Alt+Win+↑    ·           ·          ·
CapsLk     !  &  *  (   )   ‖ SNAP_TL     Ctrl+PgUp    Win+↑        Ctrl+PgDn   SNAP_TR    —
Shift      ?  @  #  $   %   ‖ SNAP_LEFT   ←            Win+↓        →           SNAP_RIGHT —
·          ·  ·  ·  F23 ·   ‖ SNAP_BL     Ctrl+Alt+PgDn SNAP_CENTER Ctrl+Alt+PgUp SNAP_BR  —
                            ‖                          SNAP_BOTTOM  F17
```

### Layer 5 — CTL_ENT (Ctrl held)
Ctrl is registered while held, and letters are mapped so Ctrl shortcuts sit at their **QWERTY positions** (Ctrl+Q W E R T / Y U I L P, Ctrl+S D F G / H J K L ,, Ctrl+Y Z X C V B / N M , .). Extras: `L00=Ctrl+Pause`, `L10=Ctrl+H`, `L21=a` (→ Ctrl+A), `L42=E_TREM`, `L43=Ctrl+.`, `R42=Ctrl+KP+`, `R43=Ctrl+KP=`, `L44=MO(7)`. Oddity: R13 is `Ctrl+L` where QWERTY would be O.

### Layer 6 — MO(6) (L54)
Left: `Win+Space PgUp ↑ Home Win+H` / `Win+← ← ↓ → Win+→` / `GO_FILE PgDn ↓ End Enter` (cols 1-5). `L11=Win+Space` switches input language (EN/FR), `L15=Win+H` starts Windows voice typing. Right: Ctrl+1..9 in a 3×3 numpad grid (cols 7-9), `R42=Ctrl+0`. Inner index column: `R10=Ctrl+Shift+Tab` / `R20=Ctrl+Tab` — previous / next tab, also used to cycle Claude desktop sessions.

### Layer 7 — Ctrl+Shift (from 3 or 5)
Ctrl+Shift+letter at QWERTY positions (Q W E R T, I O P, A S D F G, H, C V B, `.`), plus `L03=MStop`, `L04=Alt+F4`, `L05=Ctrl+F5`, `L20=Shift+Del`, `L30=Ctrl+Shift+Space`, `L43=Win+Space`, `L10=Ctrl+Shift+H`.

### Layer 8 — MO(8) from layer 2
Left: `Esc Ctrl+1..5` top row, mouse: `Btn2 MsUp Btn1` / `MsL MsDn MsR` / `WhUp _ WhDn`, Tab, LShift, `L45=Ctrl+Alt+Enter`. Right: Ctrl+Shift+`PgUp ↑ PgDn` / `← ↓ →`, `R20=Ctrl+H`.

### Layer 9 — left numpad
```
-        6  7  8  9  0        ‖ —      —            —   —            —      —
^dead    y  1  2  3  —        ‖ Win+2  Win+3        Win+4 Win+5      Win+6  Win+7
Alt+PgDn KP- 4 5  6  Alt+PgUp ‖ Win+1  Ctrl+Win+←   —   Ctrl+Win+→   —      Win+9
LCtrl GO_FILE 7 8 9  é(KC_SLSH) ‖ —   …
       L43 = 0
```
`L9_ALT` holds LAlt while on this layer (Alt+digit, Alt+PgUp/PgDn …).

### Layer 10 — NOLAN
Full US-style keyboard shifted right by one column on the left half: number row `Esc 1-5 ‖ 6-0 -`, `Tab ^ q w e r ‖ t y u i o p`, `Shift Enter a s d f ‖ g h j k l ;`, `Ctrl / z x c v ‖ b n m , . ;`, `L42=è R42=à R43==`, `L45=Space`. Symbols are still interpreted by CSA.

### Layer 11 — BEPO_SFT (Shift held)
Shift is held, so transparent keys = capitals of layer 0. Overrides: number row `! @ # $ %  ‖ & * ( ) _`, `L12=É`, `L25=;` (shift removed by `SEM_COL`), `L34=:`, `L42=ù/Ù (U_GRAVE)`, `L43=¨ dead (E_TREM)`.

### Layer 12 — SFT_ARROWS (2 + 11)
Right: Shift+`PgUp ↑ PgDn` / Shift+`Home ← ↓ → End` (selection), `L30=LCtrl`.

### Layer 13 — ARROWS
Transparent except `R12=↑`, `R21 R22 R23 = ← ↓ →`, `L45=Enter` (replaces CTL_ENT).

## Custom keycodes (`process_record_user` in keymap.c)

| Key | Behavior |
|---|---|
| `CTL_ENT_5` | Hold: LCtrl + layer 5. Tap (press+release with nothing else): Enter. Tap then press again within TAPPING_TERM: holds Enter (auto-repeat). Only unregisters Ctrl if it registered it. |
| `BEPO_SFT_11_12` | LShift + layer 11 while held. |
| `R_THUM_2_4` / `L_THUM_3_4` | Momentary layer 2 / 3 (tri-layer → 4). `L_THUM_3_4` release also fires deferred `KC_PWR`. |
| `L9_ALT` | LAlt + layer 9 while held. |
| `MUTE_LEFT_DESKTOP` = `LT(0,KC_M)` | Tap: Win+Alt+K (Windows mic mute; was Ctrl+Shift+Alt+M via an external tool, still commented in code). Hold: Ctrl+Win+← (prev virtual desktop). |
| `ANSWER_RIGHT_DESKTOP` = `LT(0,KC_A)` | Tap: Alt+R (answer call). Hold: Ctrl+Win+→. |
| `LEFT_PREV` / `RIGHT_NEXT` = `LT(0,…)` | Tap: ← / →. Hold: media prev / next. |
| `COMM_PGUP` | `,` normally; PgUp if Alt is held. |
| `E_ACUTE` | `KC_SLSH` → é. |
| `E_TREM` | Shift+`KC_LBRC` with Ctrl temporarily released → `¨` dead key. |
| `U_GRAVE` | AltGr+`KC_LBRC` (`` ` `` dead, shift suppressed) then `u` → ù. |
| `TICK_KEY` / `TILDE` | AltGr dead key + Space → literal `` ` `` / `~`. |
| `PIPE` | AltGr+`KC_GRV` → `\|`. |
| `SEM_COL` | `;` with Shift suppressed. |
| `L_ARR1` | Types `x => x.` |
| `L_ARR2` | One-shot lambda: on release, the **next** key K types `K => K.`; `L_ARR2` again types `() => `; Esc cancels. |
| `GO_FILE` | Ctrl+Shift+Space, Ctrl+V, Ctrl+←, Ctrl+Bksp, 250 ms, Enter (paste a path into a go-to-file prompt and trim the last segment). |
| `SNAP_*` | Win+Z snap layouts: `WIN_SNAP_2_COLUMNS` (key 4) → LEFT=1/RIGHT=2; `WIN_SNAP_2x2` (key 8) → TL=1 TR=2 BL=3 BR=4; `WIN_SNAP_3_UNBALANCED_COLUMNS` (key 9) → CENTER=2. 100 ms delays. `SNAP_BOTTOM` = Win+Alt+↓ ×2. |
| `PAUSE_ANSWER` | No-op (implementation commented out — "doesn't work"). |
| `KC_PWR` | Never sent directly; queued and sent on `L_THUM_3_4` release. |

Declared but unused in the layout: `ANSWER_RIGHT_DESKTOP` (replaced by Win+H on base L04), `HAT`, `LALT_TICK`, `QWERTY`, `BEPO`, `L_THUMB2`, `L2_THUMB`, `R2_THUMB`, `L_THUMB_R_KB`, `NOLAN`, `SFT_ARROWS`, `ARROWS`. New custom keycodes must be appended to `enum retro_keys` and referenced in the Configurator JSON as `ANY(NAME)`.

## Abbreviation expander (`handle_abbr`)
Runs on every key **release**: tracks runs of letter keycodes (`KC_A..KC_Z`, any non-letter resets); after 3 letters typed within `ABBR_TERM` (500 ms) it compares against `ABBR`, and on match sends 3 Backspaces + the word. Table: `qqn → quelqu'un`, `qq␣ → "quelque "`, `qqs → quelques`.
Known bugs: `handle_abbr_end` returns after the first non-matching entry, so only `qqn` can ever match; and `KC_SPACE` resets the run so `qq␣` couldn't match anyway.

## Combos (`combos.def`)
Press keys simultaneously (keycodes, i.e. layer-0 letters) to type text. Groups:
- French: `s q e`→"est-ce que ", `+i`→capitalised; `s q o`→"est-ce qu'", `+p`→capitalised; `e s t u`→"es-tu ", `e i s t u`→"Es-tu ", `a s t u`→"as-tu ", `p t e`→"peut-être " (`s p t e` capitalised), `p t u`→"peux-tu ", `a t o n`→"a-t-on ", `a t i l`→"a-t-il ", `p k`→"pourquoi ", `p r b`→"probablement", `b c p`→"beaucoup ", `a j d`→"aujourd'hui ".
- English/dev: `d o t` or `d o n`→"doesn't ", `c o n i`→"config", `k s`→"k8s", `a n d`→" AND ", `p e l n`→"pipeline", `s b n`→"subscription", `p r o t s`→"properties".
- Operators: `^dead =`→" >= ", `ù =`→" <= ", `^dead c`→"->", `b =`→" != ".
- Work/personal: company name/product name and email-address snippets (`a p c`, `p r g`, `p r o n`, `b i r`, `b r g`) — see the file for exact text.

## Gotchas when answering questions / editing
- To find what a physical key does on layer N, look at `retro_keymap.c` `[N] = LAYOUT_5x6(...)`: index 0-47 are the 4 main rows (12 per row, left 6 then right 6), 48-63 are the thumb/bottom keys in the order given above.
- Always translate keycodes through CSA before saying what character a key types.
- `retro_keymap.c` is regenerated by `update.sh`; layout changes belong in `backups/manuform_5x6.json`, behavior changes in `keymap.c`.
- Layer 9 `L35 = KC_SLSH` types é under CSA (maybe intended `/`); layer 2 `TG(14)` looks like a mistake.
- Building: the checkout lives **inside WSL** (Ubuntu-24.04) at `~/dev/thirdparty/qmk_firmware`, which has `gcc-avr`/`avr-libc`/`avrdude`; the qmk CLI lives in a venv at `~/.qmk-venv` (not on PATH by default). Build natively (fast):
  `PATH=~/.qmk-venv/bin:$PATH make -j8 handwired/dactyl_manuform/5x6:retro`
  Output: `handwired_dactyl_manuform_5x6_retro.hex` in repo root. Flash with QMK Toolbox on Windows (caterina bootloader; WSL has no USB access). **When telling the user where the hex is, give the Windows path:** `\\wsl.localhost\Ubuntu-24.04\home\billy\dev\thirdparty\qmk_firmware\handwired_dactyl_manuform_5x6_retro.hex` (backups: same prefix + `\firmware-backups\<file>.hex`). **After every build, copy the hex to `firmware-backups/<date>_<commit>.hex`** (local-only, gitignored) so the user can flash the previous one if a build is broken; `firmware-backups/README.md` lists what each file is. Firmware is ~86% of flash — watch the size. Submodules `lib/lufa` and `lib/printf` must be initialized. The scripts `cd` to their own dir, put `~/.qmk-venv/bin` on PATH, and watch `/mnt/c/Users/BillyProgi/Downloads/billybraga.json` for the Configurator export.
- Regenerate the keymap from JSON with `~/.qmk-venv/bin/qmk json2c backups/manuform_5x6.json` (in WSL); otherwise mirror JSON edits into `retro_keymap.c` by hand (`ANY(x)` in JSON → `x` in C).
