#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "print.h"

void keyboard_post_init_user(void) {
    debug_enable = true;
    // debug_matrix = true;
    debug_keyboard = true;
}

enum layers {
    // The base layer for most english typing
    _QWERTY,
    // Special characters
    _SPECIAL,
    // Numpad on right hand
    // Media keys on the left hand
    _NUMBERS,
    // Keys often required while using numbers on the right hand - plus, minus, etc.
    // Function keys on the left hand
    _NUMBERS_AUX,
    // Arrow key layer WIP
    _ARROWS,

    // EPHEMERAL LAYERS
    // The following layers are not in the same spirit as the rest of the board,
    // and thus are more difficult to access in everyday use.
    // The EPHEMERAL_HOME layer can be reached from the normal layers, and the
    // other ephemeral layers can be reached from there.
    _EPHEMERAL_HOME,
};

#define EP_HOME OSL(_EPHEMERAL_HOME)
#define OS_NUMX OSL(_NUMBERS_AUX)

#define GUI_SLS LGUI_T(KC_SLSH)
#define GUI_Z LGUI_T(KC_Z)
#define ALT_X LALT_T(KC_X)
#define SHFT_C LSFT(KC_C)
#define ALT_LFT LALT(KC_LEFT)
#define ALT_RHT LALT(KC_RIGHT)
#define ALT_DWN LALT(KC_DOWN)
#define ALT_UP LALT(KC_UP)
#define GO_BACK LCTL(LSFT(KC_LEFT))
#define GO_FWD LCTL(LSFT(KC_RIGHT))
#define ALT_DOT LALT_T(KC_DOT)
#define CMD_PLT LGUI(LSFT(KC_P))
#define CMD_P LGUI(KC_P)
#define CMD_F LGUI(KC_F)
#define CMD_SF LGUI(LSFT(KC_F))
#define ALT_TAB LALT(KC_TAB)
#define ALT_TLD LALT(KC_TILD)
#define ALT_BSP LALT(KC_BSPC)
#define SHT_ALT LSFT(KC_LALT)
#define ALT_ENT LALT(KC_ENT)

// Defines a layout for auxiliary layers; the layout will be common on the
// different layers, so it is better to only define it once.
#define LAYOUT_SUPER( \
    L01, L02, L03, L04, L05, R01, R02, R03, R04, R05, \
    L06, L07, L08, L09, L10, R06, R07, R08, R09, R10, \
    L11, L12, L13, L14, L15, R11, R12, R13, R14, R15, \
                   L16, L17, R16, R17 \
) LAYOUT( \
    KC_ESC,  L02, L03, L04, L05, R01, R02, R03, R04, KC_BSPC, \
    KC_TAB,  L07, L08, L09, L10, R06, R07, R08, R09, KC_ENT, \
    KC_BTN1, L12, L13, L14, L15, R11, R12, R13, R14, R15, \
               KC_LCTL, _______, R16, KC_LSFT \
)

static bool alt_tab_entered;
static bool cmd_tld_entered;
static bool did_detect_windows = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    if(!layer_state_cmp(state, _NUMBERS) && alt_tab_entered) {
        // exited the numbers layer... release the alt_tab
        printf("moving away from NUMBERS layer\n");
        printf("releasing alt key\n");
        if(did_detect_windows) {
            del_mods(MOD_MASK_ALT | MOD_MASK_SHIFT);
        } else {
            del_mods(MOD_MASK_GUI | MOD_MASK_SHIFT);
        }
        unregister_code(KC_TAB);
        alt_tab_entered = false;
    }

    if(!layer_state_cmp(state, _NUMBERS) && cmd_tld_entered) {
        // exited the numbers layer... release the alt_tab
        printf("moving away from NUMBERS layer\n");
        printf("releasing cmd ~ key\n");
        
        del_mods(MOD_MASK_GUI | MOD_MASK_SHIFT);
        unregister_code(KC_GRAVE);
        cmd_tld_entered = false;
    }

    return update_tri_layer_state(state, _SPECIAL, _NUMBERS, _ARROWS);
}
//
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        GUI_Z,   ALT_X,   KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, ALT_DOT, GUI_SLS,
              LCTL_T(KC_ENT), LT(_NUMBERS, KC_BSPC),    LT(_SPECIAL, KC_SPC), KC_LSFT
    ),

    [_SPECIAL] = LAYOUT_SUPER(
        _______, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD, _______,
        _______, KC_EXLM, KC_EQL,  KC_MINS, KC_QUOT,   KC_GRV,  KC_BSLS, KC_LCBR, KC_RCBR, _______,
        _______, KC_PIPE, KC_PLUS, KC_UNDS, KC_DQUO,   KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, _______,
                                   _______, _______,   _______, _______
    ),

    [_NUMBERS] = LAYOUT_SUPER(
        _______, _______, SHT_ALT, KC_LSFT, _______,   KC_UNDS, KC_7,    KC_8,    KC_9,    _______,
        _______, KC_VOLD, KC_VOLU, KC_MPLY, _______,   KC_SPC,  KC_4,    KC_5,    KC_6,    _______,
        _______, _______, _______, _______, _______,   KC_0,    KC_1,    KC_2,    KC_3,    OS_NUMX,
                                   _______, _______,   _______, _______
    ),

    [_NUMBERS_AUX] = LAYOUT_SUPER(
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F12,    _______, _______, _______, _______, _______,
        _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,    _______, KC_PLUS, KC_ASTR, KC_DOT,  _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F10,    KC_COLN, KC_MINS, KC_SLSH, KC_COMM, KC_NO,
                                   _______, _______,   _______, _______
    ),

    [_ARROWS] = LAYOUT_SUPER(
        _______, CMD_SF,  _______, CMD_P,   CMD_PLT,   ALT_LFT, GO_BACK, GO_FWD,  ALT_RHT, _______,
        _______, _______, ALT_ENT, KC_LSFT, ALT_BSP,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, _______, _______, _______, EP_HOME,   KC_HOME, ALT_DWN, ALT_UP,  KC_END,  _______,
                                   _______, _______,   _______, _______
    ),

    [_EPHEMERAL_HOME] = LAYOUT(
        _______, _______, _______, _______, CG_TOGG,   _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______,   _______, _______, _______, _______, QK_BOOT,

                            _______, TO(_QWERTY), TO(_SPECIAL),   _______
    ),
};
// clang-format on

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            // rgb_matrix_set_color_all(RGB_WHITE);
            print("detected mac, deactivating swapping of gui and control\n");
            keymap_config.raw = eeconfig_read_keymap();
            keymap_config.swap_lctl_lgui = false;
            keymap_config.swap_rctl_rgui = false;
            eeconfig_update_keymap(keymap_config.raw);
            clear_keyboard();
            break;
        case OS_WINDOWS:
            // rgb_matrix_set_color_all(RGB_BLUE);
            did_detect_windows = true;
            print("detected windows, swapping gui and control\n");
            keymap_config.raw = eeconfig_read_keymap();
            keymap_config.swap_lctl_lgui = true;
            keymap_config.swap_rctl_rgui = true;
            eeconfig_update_keymap(keymap_config.raw);
            clear_keyboard();
            break;
        case OS_LINUX:
            // rgb_matrix_set_color_all(RGB_ORANGE);
            print("detected linux\n");
            break;
        case OS_UNSURE:
            // rgb_matrix_set_color_all(RGB_RED);
            print("unknown os\n");
            break;
    }
    
    return true;
}

// Initialize variable holding the binary
// representation of active modifiers.

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod_state = get_mods();
    
    static bool ctl_left_registered;
    static bool ctl_right_registered;
    static bool alt_shift_left_registered;
    static bool alt_shift_right_registered;
    static bool ctl_bspc_registered;

    switch (keycode) {

    case KC_VOLU:
        printf("volu pressed\n");
        if (layer_state_is(_NUMBERS)) {
            if (record->event.pressed) {
                if(did_detect_windows) {
                    printf("triggering alt tab\n");
                    set_mods(MOD_MASK_ALT);
                } else {
                    printf("triggering cmd tab\n");
                    set_mods(MOD_MASK_GUI);
                }
                register_code(KC_TAB);
                alt_tab_entered = true;
                return false;
            } else { 
                // on release of tab key unregister tab,
                // but avoid normal processing as we modified
                // the mod state.
                printf("releasing tab key\n");
                if (alt_tab_entered) {
                    unregister_code(KC_TAB);
                    return false;
                }
            }
            return true;
        }
        return true;

    case KC_VOLD:
        printf("vold pressed\n");
        if(layer_state_is(_NUMBERS)) {
            if (record->event.pressed) {
                if(did_detect_windows) {
                    printf("triggering alt shift tab\n");
                    set_mods(MOD_MASK_ALT | MOD_MASK_SHIFT);
                } else {
                    printf("triggering cmd shift tab\n");
                    set_mods(MOD_MASK_GUI | MOD_MASK_SHIFT);
                }
                register_code(KC_TAB);
                alt_tab_entered = true;
                return false;
            } else { 
                // on release of tab key unregister tab,
                // but avoid normal processing as we modified
                // the mod state.
                printf("releasing tab key\n");
                if (alt_tab_entered) {
                    unregister_code(KC_TAB);
                    return false;
                }
            }
            return true;
        }
        return true;

    case KC_MPLY:
        printf("media mply pressed\n");
        if(!did_detect_windows) {
            if (record->event.pressed) {
                
                printf("triggering cmd ~\n");
                set_mods(MOD_MASK_GUI | MOD_MASK_SHIFT);
                register_code(KC_GRAVE);
                cmd_tld_entered = true;

                set_mods(mod_state);
                return false;
            } else { 
                // on release of media mply unregister grave,
                // but avoid normal processing as we modified
                // the mod state.
                if (cmd_tld_entered) {
                    printf("releasing ~\n");
                    unregister_code(KC_GRAVE);
                    return false;
                }
            }
        }
        return true;

    // as alt left is a key combo in the keymap
    // both are hit at the same time and mod_state
    // wont contain alt yet. Also the key code contains
    // the bitwise OR of both keys.. we must handle
    // accordingly
    case QK_LALT | KC_LEFT:
        printf("alt left pressed\n");
        if(did_detect_windows) {
            if(record->event.pressed) {
                printf("replacing alt left -> ctrl left\n");
                add_mods(MOD_MASK_CTRL);
                
                // send ctrl + left
                register_code(KC_LEFT);
                ctl_left_registered = true;

                // put mod state back so 
                // subsequent presses are considered 'alt'
                set_mods(mod_state);
                return false;
            } else {
                if(ctl_left_registered) {
                    printf("releasing ctl left \n");
                    unregister_code(KC_LEFT);
                    ctl_left_registered = false;
                    return false;
                }
                return true;
            }
        }
        return true;

     case QK_LALT | KC_RIGHT:
        printf("alt right pressed\n");
        if(did_detect_windows) {
            if(record->event.pressed) {
                printf("replacing alt right -> ctrl right\n");
                add_mods(MOD_MASK_CTRL);
                
                // send ctrl + right
                register_code(KC_RIGHT);
                ctl_right_registered = true;

                // put mod state back so 
                // subsequent presses are considered 'alt'
                set_mods(mod_state);
                return false;
            } else {
                if(ctl_right_registered) {
                    printf("releasing ctl right \n");
                    unregister_code(KC_RIGHT);
                    ctl_right_registered = false;
                    return false;
                }
                return true;
            }
        }
        return true;

    case QK_LALT | KC_BSPC:
        printf("alt backspace pressed\n");
        if(did_detect_windows) {
            if(record->event.pressed) {
                printf("replacing alt backspace -> ctrl backspace\n");
                add_mods(MOD_MASK_CTRL);
                
                // send ctrl + right
                register_code(KC_BSPC);
                ctl_bspc_registered = true;

                // put mod state back so 
                // subsequent presses are considered 'alt'
                set_mods(mod_state);
                return false;
            } else {
                if(ctl_bspc_registered) {
                    printf("releasing ctl right \n");
                    unregister_code(KC_BSPC);
                    ctl_bspc_registered = false;
                    return false;
                }
                return true;
            }
        }
        return true;

    case QK_LCTL | QK_LSFT | KC_LEFT:
        printf("ctl shift left pressed\n");
        if(did_detect_windows) {
            if(record->event.pressed) {
                printf("replacing ctl shift left -> alt shift left\n");
                set_mods(MOD_LALT | MOD_LSFT);
                
                // send ctrl + left
                register_code(KC_LEFT);
                alt_shift_left_registered = true;

                // put mod state back
                set_mods(mod_state);
                return false;
            } else {
                if(alt_shift_left_registered) {
                    printf("releasing ctl left \n");
                    unregister_code(KC_LEFT);
                    alt_shift_left_registered = false;
                    return false;
                }
                return true;
            }
        }
        return true;
    case QK_LCTL | QK_LSFT | KC_RIGHT:
        printf("ctl shift right pressed\n");
        if(did_detect_windows) {
            if(record->event.pressed) {
                printf("replacing ctl shift right -> alt shift right\n");
                set_mods(MOD_LALT | MOD_LSFT);
                
                // send ctrl + right
                register_code(KC_RIGHT);
                alt_shift_right_registered = true;

                // put mod state back
                set_mods(mod_state);
                return false;
            } else {
                if(alt_shift_right_registered) {
                    printf("releasing ctl right \n");
                    unregister_code(KC_RIGHT);
                    alt_shift_right_registered = false;
                    return false;
                }
                return true;
            }
        }
        return true;

    }
    return true;
};

bool is_windows(bool key_down, void *layer) {
    printf("is_windows() called, returning %i\n", did_detect_windows);
    return did_detect_windows;
}

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)



