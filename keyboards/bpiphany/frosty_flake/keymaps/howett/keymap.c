#include QMK_KEYBOARD_H

enum howett_keycodes {
	HKC_TOGGLE_GUI = SAFE_RANGE
};

enum howett_layers {
	_QWERTY,
	_QFR_FN, // mimics the default FN layer from the quickfire rapid
	_NUMPAD,
};

#define H_CTESC MT(MOD_LCTL, KC_ESC)
#define H_L1APP LT(_QFR_FN, KC_APP)
#define H_L2NUM TG(_NUMPAD)
#define H_TGUI  HKC_TOGGLE_GUI

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_tkl_ansi(
		KC_ESC,    KC_F1,  KC_F2,  KC_F3,  KC_F4,     KC_F5,  KC_F6,  KC_F7,  KC_F8,     KC_F9,  KC_F10, KC_F11, KC_F12,KC_PSCR,KC_SLCK,KC_PAUS,
		KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,KC_INS, KC_HOME,KC_PGUP,
		KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,KC_DEL, KC_END, KC_PGDN,
		H_CTESC,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,
		KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,                        KC_UP,
		KC_LCTL,KC_LGUI,KC_LALT,                KC_SPC,                 KC_RALT,KC_RGUI,H_L1APP,KC_RCTL,                KC_LEFT,KC_DOWN,KC_RGHT),
	[_QFR_FN] = LAYOUT_tkl_ansi(
		_______,   _______,_______,_______,_______,   KC_MPLY,KC_MSTP,KC_MRWD,KC_MFFD,  H_TGUI, KC_MUTE,KC_VOLD,KC_VOLU,_______,H_L2NUM,_______,
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
		KC_CAPS,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                        _______,
		_______,_______,_______,                _______,                _______,_______,_______,_______,                _______,_______,_______),
	[_NUMPAD] = LAYOUT_tkl_ansi(
		_______,   _______,_______,_______,_______,   _______,_______,_______,_______,  _______,_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,_______,_______,KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,_______,_______,KC_KP_7,KC_KP_8,KC_KP_9,KC_PPLS,_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,_______,_______,KC_KP_4,KC_KP_5,KC_KP_6,KC_PENT,_______,_______,
		_______,_______,_______,_______,_______,_______,KC_KP_0,KC_KP_1,KC_KP_2,KC_KP_3,KC_PDOT,_______,                        _______,
		_______,_______,_______,                _______,                _______,_______,_______,_______,                _______,_______,_______),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		if (keycode == HKC_TOGGLE_GUI) {
			keymap_config.no_gui ^= 1;
			frosty_winlock_led_set(keymap_config.no_gui);
			return false; // Skip
		}
	}
	return true;
}

// :syn match LineNr /\<KC_NO\>/
// :syn match Title /\<KC_[0-9A-Z]\>/
// :syn match Type /\<KC_F\d\+\>/
// :syn match Ignore /\<H_[A-Z0-9]\{1,5}\>/
// :syn match ErrorMsg /KC_ESC/
// :hi KcTransparent ctermfg=239 | syn match KcTransparent /\(\<KC_TRANS\>\|_______\)/
