'use strict';

// Data files: `data/` is what the GitHub Pages workflow publishes; the `../` paths work when serving the repo root locally.
const SOURCES = {
  keymap: ['data/manuform_5x6.json', '../backups/manuform_5x6.json'],
  combos: ['data/combos.def', '../keyboards/handwired/dactyl_manuform/5x6/keymaps/retro/combos.def'],
};

const LAYER_NAMES = {
  0: 'Base (BÉPO)', 1: 'QWERTY', 2: 'Nav & mouse', 3: 'F-keys & numpad', 4: 'Symbols & windows',
  5: 'Ctrl', 6: 'Nav & Ctrl+digits', 7: 'Ctrl+Shift', 8: 'Mouse & Ctrl+Shift+arrows', 9: 'Left numpad',
  10: 'Nolan QWERTY', 11: 'Shift', 12: 'Shift + nav', 13: 'Arrows',
};
const TRI_LAYERS = { 4: [2, 3], 12: [2, 11] };
const IMPLICIT_MODS = { 5: ['Ctrl'] }; // layer 5 is held together with Ctrl

// ---------- physical layout (LAYOUT_5x6 argument order) ----------
const THUMB_CODES = ['L42', 'L43', 'R42', 'R43', 'L44', 'L45', 'R40', 'R41', 'L54', 'L55', 'R50', 'R51', 'L52', 'L53', 'R52', 'R53'];

// Dactyl-style geometry, in key units: [x, y, angle°] for each key centre (LAYOUT_5x6 argument order).
const STAGGER = [0.5, 0.5, 0.15, 0, 0.15, 0.25]; // left columns, outer pinky → inner index (positive = lower)
const LEFT_EXTRA = {
  L42: [2, 4 + STAGGER[2], 0], L43: [3, 4 + STAGGER[3], 0],
  L44: [4.3, 5.0, 15], L45: [5.27, 5.26, 15],
  // Lower thumb keys form a diamond: L55 top, L54 outer, L53 inner, L52 bottom
  L55: [6.1, 6.39, 45], L54: [5.39, 7.1, 45], L53: [6.81, 7.1, 45], L52: [6.1, 7.81, 45],
};
const RIGHT_MIRROR = { R42: 'L43', R43: 'L42', R40: 'L45', R41: 'L44', R50: 'L55', R51: 'L54', R52: 'L53', R53: 'L52' };
const RIGHT_X = 16.5; // right half x = RIGHT_X - mirrored left x
const HALF_TILT = 6;

function rotatePoint(x, y, px, py, deg) {
  const r = deg * Math.PI / 180, c = Math.cos(r), s = Math.sin(r);
  return [px + (x - px) * c - (y - py) * s, py + (x - px) * s + (y - py) * c];
}
const GEOM = [];
for (let r = 0; r < 4; r++) for (let c = 0; c < 12; c++) {
  GEOM.push(c < 6 ? [c, r + STAGGER[c], 0] : [RIGHT_X - (11 - c), r + STAGGER[11 - c], 0]);
}
for (const code of THUMB_CODES) {
  if (code[0] === 'L') GEOM.push(LEFT_EXTRA[code]);
  else { const [x, y, a] = LEFT_EXTRA[RIGHT_MIRROR[code]]; GEOM.push([RIGHT_X - x, y, -a]); }
}
GEOM.forEach((g, i) => {
  const left = i < 48 ? i % 12 < 6 : THUMB_CODES[i - 48][0] === 'L';
  const tilt = left ? -HALF_TILT : HALF_TILT;
  const [x, y] = rotatePoint(g[0], g[1], left ? 2.75 : RIGHT_X - 2.75, 3, tilt);
  GEOM[i] = [x, y, g[2] + tilt];
});
const THUMB_NAMES = [
  'left bottom row, ring', 'left bottom row, middle', 'right bottom row, middle', 'right bottom row, ring',
  'left thumb, main row, outer', 'left thumb, main row, inner', 'right thumb, main row, inner', 'right thumb, main row, outer',
  'left thumb diamond, outer', 'left thumb diamond, top', 'right thumb diamond, top', 'right thumb diamond, outer',
  'left thumb diamond, bottom', 'left thumb diamond, inner', 'right thumb diamond, inner', 'right thumb diamond, bottom',
];
const FINGERS_L = ['outer pinky', 'pinky', 'ring', 'middle', 'index', 'inner index'];
const FINGERS_R = ['inner index', 'index', 'middle', 'ring', 'pinky', 'outer pinky'];
const ROWS = ['number row', 'top row', 'home row', 'bottom row'];

function posCode(i) {
  if (i >= 48) return THUMB_CODES[i - 48];
  const r = Math.floor(i / 12), c = i % 12;
  return (c < 6 ? 'L' : 'R') + r + (c % 6);
}
function posName(i) {
  if (i >= 48) return THUMB_NAMES[i - 48];
  const r = Math.floor(i / 12), c = i % 12;
  return c < 6 ? `left ${ROWS[r]}, ${FINGERS_L[c]}` : `right ${ROWS[r]}, ${FINGERS_R[c - 6]}`;
}

// ---------- keycode → human text (host OS layout: Canadian Multilingual Standard) ----------
const CSA = {
  KC_1: ['1', '!'], KC_2: ['2', '@'], KC_3: ['3', '#'], KC_4: ['4', '$'], KC_5: ['5', '%'],
  KC_6: ['6', '?'], KC_7: ['7', '&'], KC_8: ['8', '*'], KC_9: ['9', '('], KC_0: ['0', ')'],
  KC_MINS: ['-', '_'], KC_EQL: ['=', '+'], KC_COMM: [',', "'"], KC_DOT: ['.', '"'], KC_SCLN: [';', ':'],
  KC_SLSH: ['é', 'É'], KC_QUOT: ['è', 'È'], KC_BSLS: ['à', 'À'], KC_RBRC: ['ç', 'Ç'], KC_GRV: ['/', '\\'],
  KC_LBRC: ['^', '¨'],
};
for (const ch of 'abcdefghijklmnopqrstuvwxyz') CSA['KC_' + ch.toUpperCase()] = [ch, ch.toUpperCase()];
const DEAD = new Set(['KC_LBRC']);
const ALTGR = { KC_7: '{', KC_8: '}', KC_9: '[', KC_0: ']', KC_COMM: '<', KC_DOT: '>', KC_GRV: '|', KC_LBRC: '`', KC_RBRC: '~' };
const ALTGR_DEAD = new Set(['KC_LBRC', 'KC_RBRC']);
const SHIFTED = {
  KC_EXLM: 'KC_1', KC_AT: 'KC_2', KC_HASH: 'KC_3', KC_DLR: 'KC_4', KC_PERC: 'KC_5', KC_CIRC: 'KC_6',
  KC_AMPR: 'KC_7', KC_ASTR: 'KC_8', KC_LPRN: 'KC_9', KC_RPRN: 'KC_0', KC_UNDS: 'KC_MINS', KC_PLUS: 'KC_EQL',
  KC_LT: 'KC_COMM', KC_GT: 'KC_DOT', KC_COLN: 'KC_SCLN', KC_DQUO: 'KC_QUOT', KC_TILD: 'KC_GRV',
};
const NAMES = {
  KC_ESC: 'Esc', KC_TAB: 'Tab', KC_ENT: 'Enter', KC_ENTER: 'Enter', KC_SPC: 'Space', KC_BSPC: 'Bksp', KC_DEL: 'Del',
  KC_LEFT: '←', KC_RGHT: '→', KC_UP: '↑', KC_DOWN: '↓', KC_PGUP: 'PgUp', KC_PGDN: 'PgDn', KC_HOME: 'Home', KC_END: 'End',
  KC_LCTL: 'Ctrl', KC_RCTL: 'RCtrl', KC_LSFT: 'Shift', KC_RSFT: 'RShift', KC_LALT: 'Alt', KC_RALT: 'AltGr',
  KC_LGUI: 'Win', KC_RGUI: 'Win', KC_CAPS: 'Caps', KC_PSCR: 'PrtSc', KC_PAUS: 'Pause', KC_APP: 'Menu', KC_PWR: 'Power',
  KC_MPLY: 'Play', KC_MSTP: 'Stop', KC_MPRV: 'Prev', KC_MNXT: 'Next', KC_VOLU: 'Vol+', KC_VOLD: 'Vol-', KC_MUTE: 'Mute',
  KC_PMNS: 'KP-', KC_PPLS: 'KP+', KC_PEQL: 'KP=', KC_PDOT: 'KP.', KC_PAST: 'KP*', KC_PSLS: 'KP/',
  MS_UP: 'Ms↑', MS_DOWN: 'Ms↓', MS_LEFT: 'Ms←', MS_RGHT: 'Ms→', MS_BTN1: 'Click', MS_BTN2: 'RClick', MS_BTN3: 'MClick',
  MS_WHLU: 'Whl↑', MS_WHLD: 'Whl↓',
};
for (let i = 1; i <= 24; i++) NAMES['KC_F' + i] = 'F' + i;
for (let i = 0; i <= 9; i++) NAMES['KC_P' + i] = 'KP' + i;
const LONG_NAMES = {
  'Ms↑': 'mouse up', 'Ms↓': 'mouse down', 'Ms←': 'mouse left', 'Ms→': 'mouse right', Click: 'mouse left click',
  RClick: 'mouse right click', MClick: 'mouse middle click', 'Whl↑': 'mouse wheel up', 'Whl↓': 'mouse wheel down',
  Play: 'media play/pause', Stop: 'media stop', Prev: 'media previous track', Next: 'media next track',
  'Vol+': 'volume up', 'Vol-': 'volume down', Caps: 'caps lock', Menu: 'context menu key',
};

// What well-known Windows shortcuts do, so they can be searched by purpose
const SHORTCUT_NOTES = {
  'Win+H': 'Windows voice typing / dictation', 'Win+Space': 'switch input language (English / French)',
  'Win+L': 'lock the computer', 'Win+↑': 'maximize window', 'Win+↓': 'restore / minimize window',
  'Win+←': 'snap window left', 'Win+→': 'snap window right', 'Ctrl+Win+←': 'previous virtual desktop',
  'Ctrl+Win+→': 'next virtual desktop', 'Alt+F4': 'close window', 'Ctrl+Tab': 'next tab / session',
  'Ctrl+Shift+Tab': 'previous tab / session', 'Alt+R': 'answer Teams call',
};

const MOD_FNS = {
  LCTL: ['Ctrl'], C: ['Ctrl'], RCTL: ['Ctrl'], LSFT: ['Shift'], S: ['Shift'], RSFT: ['Shift'],
  LALT: ['Alt'], A: ['Alt'], RALT: ['AltGr'], ALGR: ['AltGr'], LGUI: ['Win'], G: ['Win'], RGUI: ['Win'],
  LCA: ['Ctrl', 'Alt'], LSA: ['Shift', 'Alt'], RSA: ['Shift', 'AltGr'], LAG: ['Alt', 'Win'], RCS: ['Ctrl', 'Shift'],
  LCS: ['Ctrl', 'Shift'], LCG: ['Ctrl', 'Win'], LSG: ['Shift', 'Win'], MEH: ['Ctrl', 'Shift', 'Alt'], HYPR: ['Ctrl', 'Shift', 'Alt', 'Win'],
};
const MOD_ORDER = ['Ctrl', 'Shift', 'Alt', 'AltGr', 'Win'];
const MOD_ABBR = { Ctrl: 'Ctl', Shift: 'Sft', Alt: 'Alt', AltGr: 'AGr', Win: 'Win' };

const CUSTOM = {
  CTL_ENT_5: { label: 'Ctl/Ent', text: 'Hold: Ctrl + layer 5. Tap: Enter. Tap then hold: hold Enter.', hold: 5 },
  BEPO_SFT_11_12: { label: 'Shift', text: 'Shift (+ layer 11, the shift layer)', hold: 11 },
  R_THUM_2_4: { label: 'L2', text: 'Hold: layer 2 (together with L3 → layer 4)', hold: 2 },
  L_THUM_3_4: { label: 'L3', text: 'Hold: layer 3 (together with L2 → layer 4)', hold: 3 },
  L9_ALT: { label: 'Alt+L9', text: 'Hold: Alt + layer 9', hold: 9 },
  MUTE_LEFT_DESKTOP: { label: 'Mute', tapKeys: 'Win+Alt+K', holdKeys: 'Ctrl+Win+←', text: 'Tap: mute microphone (Win+Alt+K). Hold: previous virtual desktop (Ctrl+Win+←).' },
  ANSWER_RIGHT_DESKTOP: { label: 'Answer', tapKeys: 'Alt+R', holdKeys: 'Ctrl+Win+→', text: 'Tap: answer call (Alt+R). Hold: next virtual desktop (Ctrl+Win+→).' },
  LEFT_PREV: { label: '←/Prev', text: 'Tap: ← left arrow. Hold: media previous track.' },
  RIGHT_NEXT: { label: '→/Next', text: 'Tap: → right arrow. Hold: media next track.' },
  COMM_PGUP: { label: ',', text: ', comma. With Alt held: PgUp.' },
  E_ACUTE: { label: 'é', text: 'é' },
  E_TREM: { label: '¨', text: '¨ dead key (then e → ë)' },
  U_GRAVE: { label: 'ù', text: 'ù (Ù with Shift)' },
  TICK_KEY: { label: '`', text: '` backtick' },
  TILDE: { label: '~', text: '~ tilde' },
  PIPE: { label: '|', text: '| pipe' },
  SEM_COL: { label: ';', text: '; semicolon (even with Shift held)' },
  HAT: { label: '^', text: '^ dead key' },
  LALT_TICK: { label: 'Alt+`', text: 'Alt+`' },
  L_ARR1: { label: 'x=>x.', text: 'Types "x => x." (lambda)' },
  L_ARR2: { label: 'λ', text: 'Lambda: next letter K types "K => K." (this key again: "() => "; Esc cancels)' },
  GO_FILE: { label: 'GoFile', tapKeys: 'Ctrl+Shift+Space…', text: 'Go-to-file macro: Ctrl+Shift+Space, paste, Ctrl+←, Ctrl+Bksp, Enter' },
  SNAP_LEFT: { label: 'Snap L', tapKeys: 'Win+Z 4 1', text: 'Snap window: left half (Win+Z, 4, 1)' },
  SNAP_RIGHT: { label: 'Snap R', tapKeys: 'Win+Z 4 2', text: 'Snap window: right half (Win+Z, 4, 2)' },
  SNAP_TOP_LEFT: { label: 'Snap TL', tapKeys: 'Win+Z 8 1', text: 'Snap window: top-left quarter (Win+Z, 8, 1)' },
  SNAP_TOP_RIGHT: { label: 'Snap TR', tapKeys: 'Win+Z 8 2', text: 'Snap window: top-right quarter (Win+Z, 8, 2)' },
  SNAP_BOTTOM_LEFT: { label: 'Snap BL', tapKeys: 'Win+Z 8 3', text: 'Snap window: bottom-left quarter (Win+Z, 8, 3)' },
  SNAP_BOTTOM_RIGHT: { label: 'Snap BR', tapKeys: 'Win+Z 8 4', text: 'Snap window: bottom-right quarter (Win+Z, 8, 4)' },
  SNAP_CENTER: { label: 'Snap C', tapKeys: 'Win+Z 9 2', text: 'Snap window: center column (Win+Z, 9, 2)' },
  SNAP_BOTTOM: { label: 'Snap ↓', tapKeys: 'Win+Alt+↓ ×2', text: 'Snap window: bottom / minimize (Win+Alt+↓ twice)' },
  PAUSE_ANSWER: { label: '—', text: 'Does nothing (disabled in keymap.c)' },
};

const SEARCH_ALIASES = {
  Ctrl: 'control ctl', Win: 'gui windows super meta', AltGr: 'ralt', Enter: 'return', Bksp: 'backspace',
  Del: 'delete', Esc: 'escape', PgUp: 'page up pageup', PgDn: 'page down pagedown', Space: 'spc spacebar',
  '←': 'left arrow', '→': 'right arrow', '↑': 'up arrow', '↓': 'down arrow', PrtSc: 'print screen',
  KP: 'keypad numpad', Caps: 'caps lock', 'Click': 'mouse button',
};

function splitArgs(s) {
  const out = []; let depth = 0, cur = '';
  for (const ch of s) {
    if (ch === '(') depth++;
    if (ch === ')') depth--;
    if (ch === ',' && depth === 0) { out.push(cur); cur = ''; } else cur += ch;
  }
  if (cur.trim()) out.push(cur);
  return out;
}
function parse(s) {
  s = s.trim();
  const m = s.match(/^([A-Za-z0-9_]+)\((.*)\)$/s);
  return m ? { fn: m[1], args: splitArgs(m[2]).map(parse) } : { name: s };
}
function stripAny(code) { return code.replace(/^ANY\((.*)\)$/s, '$1'); }

function keyName(base) {
  if (NAMES[base]) return NAMES[base];
  if (CSA[base]) return /^[a-z]$/.test(CSA[base][0]) ? CSA[base][0].toUpperCase() : CSA[base][0];
  return base.replace(/^KC_/, '');
}

function withMods(mods, base) {
  mods = MOD_ORDER.filter(m => mods.includes(m));
  if (mods.length === 1 && mods[0] === 'Shift' && CSA[base]) {
    const ch = CSA[base][1] + (DEAD.has(base) ? ' (dead key)' : '');
    return { kind: 'key', label: CSA[base][1], text: `${ch} — Shift+${keyName(base)}` };
  }
  if (mods.length === 1 && mods[0] === 'AltGr' && ALTGR[base]) {
    const ch = ALTGR[base] + (ALTGR_DEAD.has(base) ? ' (dead key)' : '');
    return { kind: 'key', label: ALTGR[base], text: `${ch} — AltGr+${keyName(base)}` };
  }
  const label = [...mods, keyName(base)].join('+');
  const long = SHORTCUT_NOTES[label] || LONG_NAMES[keyName(base)];
  return { kind: 'key', label, text: long ? `${label} (${long})` : label, mods };
}

function plainKey(k) {
  if (CSA[k]) return { kind: 'key', label: CSA[k][0], text: CSA[k][0] + (DEAD.has(k) ? ' (dead key)' : ''), base: k };
  if (NAMES[k]) return { kind: 'key', label: NAMES[k], text: LONG_NAMES[NAMES[k]] ? `${NAMES[k]} (${LONG_NAMES[NAMES[k]]})` : NAMES[k], base: k };
  return { kind: 'key', label: k.replace(/^KC_/, ''), text: k };
}

function describeNode(n) {
  if (!n.fn) {
    const k = n.name;
    if (k === 'KC_TRNS' || k === '_______' || k === 'KC_TRANSPARENT') return { kind: 'trns', label: '', text: 'Transparent (falls through)' };
    if (k === 'KC_NO' || k === 'XXXXXXX') return { kind: 'none', label: '', text: 'Nothing' };
    if (CUSTOM[k]) return { kind: CUSTOM[k].hold != null ? 'layer' : 'custom', ...CUSTOM[k] };
    if (SHIFTED[k]) return withMods(['Shift'], SHIFTED[k]);
    if (k === 'KC_PWR') return { kind: 'key', label: 'Power', text: 'Power (only sent when the left-thumb L3 key is released)' };
    return plainKey(k);
  }
  const f = n.fn;
  if (f === 'ANY') return describeNode(n.args[0]);
  if (MOD_FNS[f]) {
    const mods = [...MOD_FNS[f]];
    let inner = n.args[0];
    while (inner.fn && MOD_FNS[inner.fn]) { mods.push(...MOD_FNS[inner.fn]); inner = inner.args[0]; }
    if (!inner.fn && SHIFTED[inner.name]) { mods.push('Shift'); inner = { name: SHIFTED[inner.name] }; }
    return withMods(mods, inner.name);
  }
  const L = Number(n.args[0] && n.args[0].name);
  const lname = LAYER_NAMES[L] ? ` (${LAYER_NAMES[L]})` : ' (does not exist)';
  if (f === 'MO' || f === 'TT' || f === 'OSL') return { kind: 'layer', label: `L${L}`, text: `Hold: layer ${L}${lname}`, hold: L };
  if (f === 'TG') return { kind: 'layer', label: `TG${L}`, text: `Toggle layer ${L}${lname}`, toggle: L };
  if (f === 'DF') return { kind: 'layer', label: `Base→${L}`, text: `Make layer ${L}${lname} the default layer`, df: L };
  return { kind: 'key', label: f, text: f };
}

const describeCache = new Map();
function describe(code, layer) {
  const key = code + '|' + (IMPLICIT_MODS[layer] ? layer : '');
  if (!describeCache.has(key)) {
    const n = parse(stripAny(code));
    let d = describeNode(n);
    if (IMPLICIT_MODS[layer] && !n.fn && d.kind === 'key' && d.base) d = withMods(IMPLICIT_MODS[layer], d.base);
    describeCache.set(key, d);
  }
  return describeCache.get(key);
}

// ---------- state ----------
let LAYERS = [];
let COMBOS = [];
let STACKS = {};   // layer → active layer stack when it is reached by holding keys
let PATHS = {};    // layer → [{layer, idx}] keys to hold
let VIA = {};      // layer → [{layer, idx}] every key that activates it
let DEFAULTS = {}; // layer → {hold:[...], tap:{layer, idx}} for DF layers
let ENTRIES = [];  // searchable keys
const state = { layer: 0, query: '', selected: null, combo: null };

function effective(stack, idx) {
  for (let s = stack.length - 1; s >= 0; s--) {
    const code = LAYERS[stack[s]][idx];
    if (!describe(code, stack[s]).kind.startsWith('trns')) return { layer: stack[s], code };
  }
  return { layer: 0, code: LAYERS[0][idx] };
}
function stackFor(layer) { return STACKS[layer] || (layer === 0 ? [0] : [0, layer]); }

function computeReach() {
  STACKS = { 0: [0] }; PATHS = { 0: [] }; VIA = {}; DEFAULTS = {};
  const queue = [0];
  const visit = (A) => {
    const held = new Set(PATHS[A].map(p => p.idx));
    for (let idx = 0; idx < 64; idx++) {
      if (held.has(idx)) continue;
      const eff = effective(STACKS[A], idx);
      const d = describe(eff.code, eff.layer);
      if (d.hold != null && d.hold !== A && LAYERS[d.hold]) {
        (VIA[d.hold] ||= []).push({ layer: A, idx });
        if (!(d.hold in PATHS)) {
          PATHS[d.hold] = [...PATHS[A], { layer: eff.layer, idx }];
          STACKS[d.hold] = [...STACKS[A], d.hold];
          queue.push(d.hold);
        }
      }
      if (d.df != null && LAYERS[d.df] && !(d.df in DEFAULTS)) DEFAULTS[d.df] = { hold: PATHS[A], tap: { layer: eff.layer, idx } };
    }
  };
  while (queue.length) {
    visit(queue.shift());
    for (const [t, [a, b]] of Object.entries(TRI_LAYERS)) {
      if (!(t in PATHS) && a in PATHS && b in PATHS && LAYERS[t]) {
        const seen = new Set();
        PATHS[t] = [...PATHS[a], ...PATHS[b]].filter(p => !seen.has(p.idx) && seen.add(p.idx));
        STACKS[t] = [0, a, b, Number(t)];
        queue.push(Number(t));
      }
    }
  }
}

function buildEntries() {
  ENTRIES = [];
  LAYERS.forEach((keys, layer) => keys.forEach((code, idx) => {
    const d = describe(code, layer);
    if (d.kind === 'trns' || d.kind === 'none') return;
    ENTRIES.push({ type: 'key', layer, idx, d, search: searchText(d, code) });
  }));
  for (const c of COMBOS) {
    const keyLabels = c.keys.map(k => describe(k, 0).label);
    ENTRIES.push({ type: 'combo', combo: c, keyLabels, search: (c.text + ' ' + keyLabels.join(' ') + ' combo').toLowerCase() });
  }
}
function words(s) { return s.split(/[^\p{L}\p{N}←→↑↓]+/u).filter(Boolean); }
function searchText(d, code) {
  let s = `${d.label} ${d.text} ${stripAny(code).replace(/_/g, ' ')}`;
  const present = new Set(words(s));
  for (const [k, v] of Object.entries(SEARCH_ALIASES)) if (present.has(k)) s += ' ' + v;
  return s.toLowerCase();
}

// ---------- search ----------
function tokens(q) { return q.toLowerCase().split(/[\s+]+/).filter(Boolean); }
function entryAtoms(e) {
  if (e.type === 'combo') return [];
  const d = e.d;
  return [d.label, ...d.label.split('+')].map(s => s.toLowerCase());
}
function matches(e, toks) {
  const atoms = entryAtoms(e);
  return toks.every(t => {
    if ([...t].length === 1) return atoms.includes(t) || (e.type === 'combo' && e.search.includes(t) && /[^a-z0-9]/.test(t));
    if (/^[\p{L}\p{N}]+$/u.test(t)) return words(e.search).some(w => w.startsWith(t));
    return e.search.includes(t);
  });
}
function score(e, q) {
  if (e.type === 'combo') return 50 + e.combo.text.length / 100;
  const norm = q.toLowerCase().replace(/\s+/g, '+');
  const label = e.d.label.toLowerCase();
  let s = label === norm ? 0 : label.startsWith(norm) ? 10 : 20;
  s += (PATHS[e.layer] ? PATHS[e.layer].length : 3) * 2 + label.length / 50;
  return s;
}
function search(q) {
  const toks = tokens(q);
  if (!toks.length) return [];
  return ENTRIES.filter(e => matches(e, toks)).sort((a, b) => score(a, q) - score(b, q));
}

// ---------- rendering ----------
const $ = (id) => document.getElementById(id);
const esc = (s) => String(s).replace(/[&<>"]/g, c => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]));

function baseHint(idx) {
  const d = describe(LAYERS[0][idx], 0);
  return d.label ? ` (base: ${d.label})` : '';
}
function keyRef(layer, idx) {
  const eff = effective(stackFor(layer), idx);
  const d = describe(eff.code, eff.layer);
  return `<kbd>${esc(d.label || '—')}</kbd> ${esc(posCode(idx))} · ${esc(posName(idx))}${esc(baseHint(idx))}`;
}

function howToSteps(layer, idx) {
  const steps = [];
  if (DEFAULTS[layer] && !(layer in PATHS)) {
    const df = DEFAULTS[layer];
    df.hold.forEach(p => steps.push(`Hold ${keyRef(p.layer, p.idx)}`));
    steps.push(`Tap ${keyRef(df.tap.layer, df.tap.idx)} to make layer ${layer} the default`);
    if (idx != null) steps.push(`Then press ${keyRef(layer, idx)}`);
    return steps;
  }
  (PATHS[layer] || []).forEach(p => steps.push(`Hold ${keyRef(p.layer, p.idx)}`));
  if (idx != null) steps.push(`${steps.length ? 'Press' : 'Press'} ${keyRef(layer, idx)}`);
  return steps;
}
function shortHow(layer, idx) {
  const hold = DEFAULTS[layer] && !(layer in PATHS) ? null : (PATHS[layer] || []);
  const press = `${posCode(idx)}${baseHint(idx)}`;
  if (hold === null) return `default-layer mode ${layer} → ${press}`;
  if (!hold.length) return `press ${press}`;
  return 'hold ' + hold.map(p => `${posCode(p.idx)}${baseHint(p.idx)}`).join(' + ') + ` → ${press}`;
}

function renderLayers(results) {
  const counts = {};
  results.forEach(e => { if (e.type === 'key') counts[e.layer] = (counts[e.layer] || 0) + 1; });
  $('layers').innerHTML = LAYERS.map((_, i) =>
    `<button data-layer="${i}" class="${i === state.layer ? 'active' : ''} ${counts[i] ? 'has-match' : ''}">` +
    `<span class="n">${i}</span>${esc(LAYER_NAMES[i] || 'Layer ' + i)}${counts[i] ? ` · ${counts[i]}` : ''}</button>`).join('');
}

function abbrMods(shortcut) {
  return shortcut.replace(/\b(Ctrl|Shift|AltGr|Alt|Win)\+/g, (_, m) => MOD_ABBR[m] + '+');
}
function capLines(label) {
  if (label.includes('+') && label.length > 5) {
    const parts = label.split('+');
    const last = parts.pop() || '+';
    return [parts.map(p => MOD_ABBR[p] || p).join('+'), last];
  }
  return [label];
}
function fontFor(s) {
  const n = [...s].length;
  return n <= 2 ? 17 : n <= 4 ? 13 : n <= 6 ? 11 : 9;
}
function clip(s, n) { return [...s].length > n ? [...s].slice(0, n - 1).join('') + '…' : s; }

function renderBoard(results) {
  const U = 60, K = 54;
  const layer = state.layer;
  const stack = stackFor(layer);
  const matchIdx = new Set(results.filter(e => e.type === 'key' && e.layer === layer).map(e => e.idx));
  if (state.combo) state.combo.keys.forEach(k => {
    const idx = LAYERS[0].findIndex(c => stripAny(c) === k);
    if (idx >= 0) matchIdx.add(idx);
  });
  const holdIdx = new Set((PATHS[layer] || []).map(p => p.idx));
  let svg = '';
  let minX = Infinity, minY = Infinity, maxX = -Infinity, maxY = -Infinity;
  for (let idx = 0; idx < 64; idx++) {
    const [x, y, angle] = GEOM[idx];
    minX = Math.min(minX, x); maxX = Math.max(maxX, x); minY = Math.min(minY, y); maxY = Math.max(maxY, y);
    const own = describe(LAYERS[layer][idx], layer);
    const eff = effective(stack, idx);
    const d = own.kind === 'trns' ? describe(eff.code, eff.layer) : own;
    const cls = ['key'];
    if (holdIdx.has(idx)) cls.push('hold');
    else if (matchIdx.has(idx)) cls.push('match');
    else if (own.kind === 'trns') cls.push('trns');
    else if (own.kind === 'none') cls.push('none');
    else if (own.kind === 'layer') cls.push('layer');
    if (state.selected && state.selected.layer === layer && state.selected.idx === idx) cls.push('selected');
    const label = own.kind === 'none' ? '' : d.label;
    const lines = capLines(label);
    const ty = -3; // keycap top sits slightly above the centre
    let text;
    if (own.kind !== 'none' && d.tapKeys) {
      // Named key: show the name plus the shortcut(s) it sends
      const fit = (s, y, size) => {
        const tooWide = [...s].length * size * 0.56 > K - 12;
        return `<text y="${y}" font-size="${size}"${tooWide ? ` textLength="${K - 12}" lengthAdjust="spacingAndGlyphs"` : ''}>${esc(s)}</text>`;
      };
      text = d.holdKeys
        ? fit(d.label, ty - 12, 10) + fit(abbrMods(d.tapKeys), ty, 8) + fit('hold ' + abbrMods(d.holdKeys), ty + 11, 8)
        : fit(d.label, ty - 7, 11) + fit(abbrMods(d.tapKeys), ty + 7, 8);
    } else if (lines.length === 2) {
      text = `<text y="${ty - 8}" font-size="9">${esc(clip(lines[0], 9))}</text>` +
             `<text y="${ty + 8}" font-size="${Math.min(13, fontFor(lines[1]))}">${esc(clip(lines[1], 7))}</text>`;
    } else {
      text = `<text y="${ty}" font-size="${fontFor(label)}">${esc(clip(label, 8))}</text>`;
    }
    // Only the keycap shape is rotated; labels stay horizontal.
    svg += `<g class="${cls.join(' ')}" data-idx="${idx}" transform="translate(${(x * U).toFixed(1)} ${(y * U).toFixed(1)})">` +
           `<title>${esc(posCode(idx))}: ${esc(d.text || '')}</title>` +
           `<g transform="rotate(${angle.toFixed(1)})">` +
           `<rect class="skirt" x="${-K / 2}" y="${-K / 2}" width="${K}" height="${K}" rx="8"/>` +
           `<rect class="top" x="${-K / 2 + 5}" y="${-K / 2 + 3}" width="${K - 10}" height="${K - 12}" rx="6"/></g>${text}</g>`;
  }
  const board = $('board');
  const pad = U * 0.8;
  board.setAttribute('viewBox', `${(minX * U - pad).toFixed(0)} ${(minY * U - pad).toFixed(0)} ${((maxX - minX) * U + 2 * pad).toFixed(0)} ${((maxY - minY) * U + 2 * pad).toFixed(0)}`);
  board.innerHTML = svg;
}

function renderDetails() {
  const layer = state.layer;
  let html = '';
  if (state.combo) {
    const c = state.combo;
    html = `<h2>Combo → “${esc(c.text)}”</h2><p>Press these keys at the same time (base layer):</p><ol class="steps">` +
      c.keys.map(k => {
        const idx = LAYERS[0].findIndex(code => stripAny(code) === k);
        return `<li>${idx >= 0 ? keyRef(0, idx) : `<kbd>${esc(describe(k, 0).label)}</kbd>`}</li>`;
      }).join('') + '</ol>';
  } else if (state.selected && state.selected.layer === layer) {
    const idx = state.selected.idx;
    const own = describe(LAYERS[layer][idx], layer);
    const eff = effective(stackFor(layer), idx);
    const d = own.kind === 'trns' ? describe(eff.code, eff.layer) : own;
    html = `<h2>${esc(d.label || '(nothing)')}</h2><p>${esc(own.kind === 'trns' ? `Falls through to layer ${eff.layer}: ${d.text}` : d.text)}</p>` +
      `<p class="muted"><code>${esc(stripAny(LAYERS[layer][idx]))}</code> · layer ${layer} · ${esc(posCode(idx))} (${esc(posName(idx))})</p>` +
      `<p><b>How to type it</b></p><ol class="steps">${howToSteps(layer, idx).map(s => `<li>${s}</li>`).join('')}</ol>`;
  } else {
    const steps = howToSteps(layer, null);
    html = `<h2>Layer ${layer} — ${esc(LAYER_NAMES[layer] || '')}</h2>` +
      (layer === 0 ? '<p>Default layer.</p>' : steps.length ? `<p><b>How to get here</b></p><ol class="steps">${steps.map(s => `<li>${s}</li>`).join('')}</ol>` : '<p>Not reachable from the base layer.</p>');
    const via = (VIA[layer] || []).filter(v => !(PATHS[layer] || []).some(p => p.idx === v.idx));
    if (via.length) html += `<p class="muted">Also activated by: ${via.map(v => `${posCode(v.idx)} on layer ${v.layer}`).join(', ')}</p>`;
    if (TRI_LAYERS[layer]) {
      html += `<p class="muted">Tri-layer: active when layers ${TRI_LAYERS[layer].join(' and ')} are both on.</p>`;
      const used = new Set((PATHS[layer] || []).map(p => p.idx));
      const alts = TRI_LAYERS[layer].flatMap(l => (VIA[l] || []).filter(v => v.layer === 0 && !used.has(v.idx)).map(v => `${posCode(v.idx)}${baseHint(v.idx)} for layer ${l}`));
      if (alts.length) html += `<p class="muted">Alternatives: ${esc(alts.join(', '))}</p>`;
    }
    html += '<p class="muted">Click a key for details.</p>';
  }
  $('details').innerHTML = html;
}

function renderResults(results) {
  const el = $('results');
  if (!state.query.trim()) {
    el.innerHTML = '<p class="muted">Type a character (é, {, ?), a shortcut (ctrl tab, win up), a key name (pgup, f5, enter) or a word (snap, mute, pourquoi). Press / to focus, Esc to clear.</p>';
    return;
  }
  if (!results.length) { el.innerHTML = `<p>No key found for “${esc(state.query)}”.</p>`; return; }
  const shown = results.slice(0, 150);
  el.innerHTML = `<h2>${results.length} result${results.length > 1 ? 's' : ''}</h2><ul>` + shown.map((e, i) => {
    if (e.type === 'combo') {
      return `<li data-i="${i}"><div class="what">“${esc(e.combo.text)}”</div><div class="where">combo: ${esc(e.keyLabels.join(' + '))} together</div></li>`;
    }
    const active = state.selected && state.selected.layer === e.layer && state.selected.idx === e.idx;
    return `<li data-i="${i}" class="${active ? 'active' : ''}"><div class="what">${esc(e.d.label)}${e.d.text !== e.d.label ? ` <span class="muted">${esc(e.d.text)}</span>` : ''}</div>` +
      `<div class="where">L${e.layer} ${esc(LAYER_NAMES[e.layer] || '')} · ${esc(shortHow(e.layer, e.idx))}</div></li>`;
  }).join('') + '</ul>';
  el.querySelectorAll('li').forEach(li => li.addEventListener('click', () => {
    const e = shown[Number(li.dataset.i)];
    if (e.type === 'combo') { state.combo = e.combo; state.selected = null; state.layer = 0; }
    else { state.combo = null; state.layer = e.layer; state.selected = { layer: e.layer, idx: e.idx }; }
    render();
  }));
}

let lastResults = [];
function render() {
  lastResults = search(state.query);
  renderLayers(lastResults);
  renderBoard(lastResults);
  renderDetails();
  renderResults(lastResults);
}

// ---------- loading ----------
async function fetchFirst(urls) {
  for (const url of urls) {
    try {
      const r = await fetch(url, { cache: 'no-cache' });
      if (r.ok) return await r.text();
    } catch (_) { /* try next */ }
  }
  throw new Error('Could not load ' + urls.join(' or '));
}

function parseCombos(text) {
  const out = [];
  for (const line of text.split(/\r?\n/)) {
    const m = line.match(/^\s*SUBS\(\s*(\w+)\s*,\s*((?:"(?:[^"\\]|\\.)*"|SS_TAP\(\w+\)|\s)+?)\s*,\s*(.+)\)\s*$/);
    if (!m) continue;
    let s = '';
    m[2].replace(/"((?:[^"\\]|\\.)*)"|SS_TAP\((\w+)\)/g, (_, str, tap) => {
      s += str != null ? str.replace(/\\(.)/g, '$1') : tap === 'X_LBRC' ? '^' : `[${tap}]`;
      return '';
    });
    s = s.replace(/\^e/g, 'ê');
    if (s.includes('@')) continue; // keep email snippets off the page
    out.push({ name: m[1], text: s, keys: m[3].split(',').map(k => k.trim()) });
  }
  return out;
}

function selectFirstResult() {
  state.combo = null;
  const first = search(state.query)[0];
  if (!first) { if (!state.query) state.selected = null; return; }
  if (first.type === 'combo') { state.combo = first.combo; state.selected = null; state.layer = 0; }
  else { state.layer = first.layer; state.selected = { layer: first.layer, idx: first.idx }; }
}

async function init() {
  try {
    const keymap = JSON.parse(await fetchFirst(SOURCES.keymap));
    LAYERS = keymap.layers;
    try { COMBOS = parseCombos(await fetchFirst(SOURCES.combos)); } catch (_) { COMBOS = []; }
  } catch (err) {
    $('details').innerHTML = `<h2>Could not load the keymap</h2><p>${esc(err.message)}</p>`;
    return;
  }
  computeReach();
  buildEntries();

  const params = new URLSearchParams(location.hash.slice(1));
  state.query = params.get('q') || '';
  if (params.has('layer')) state.layer = Math.min(LAYERS.length - 1, Number(params.get('layer')) || 0);
  $('search').value = state.query;
  selectFirstResult();

  $('search').addEventListener('input', (ev) => {
    state.query = ev.target.value;
    selectFirstResult();
    history.replaceState(null, '', state.query ? '#q=' + encodeURIComponent(state.query) : location.pathname);
    render();
  });
  $('layers').addEventListener('click', (ev) => {
    const b = ev.target.closest('button');
    if (!b) return;
    state.layer = Number(b.dataset.layer); state.selected = null; state.combo = null;
    render();
  });
  $('board').addEventListener('click', (ev) => {
    const g = ev.target.closest('.key');
    if (!g) return;
    state.combo = null;
    state.selected = { layer: state.layer, idx: Number(g.dataset.idx) };
    render();
  });
  document.addEventListener('keydown', (ev) => {
    if (ev.key === '/' && document.activeElement !== $('search')) { ev.preventDefault(); $('search').focus(); }
    if (ev.key === 'Escape') { $('search').value = ''; $('search').dispatchEvent(new Event('input')); }
  });
  render();
}

init();
