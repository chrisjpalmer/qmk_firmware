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
    _FUNCTION_KEYS,
    // Arrow key layer WIP
    _ARROWS,

    // EPHEMERAL LAYERS
    // The following layers are not in the same spirit as the rest of the board,
    // and thus are more difficult to access in everyday use.
    // The EPHEMERAL_HOME layer can be reached from the normal layers, and the
    // other ephemeral layers can be reached from there.
    _EPHEMERAL_HOME,

    _UNREAL
};

#define EP_HOME OSL(_EPHEMERAL_HOME)
#define OS_FX OSL(_FUNCTION_KEYS)
#define LU(KEY) LT(_UNREAL, KEY)
#define TO_QRTY TO(_QWERTY)

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
#define SHT_TAB LSFT(KC_TAB)
#define ALT_ENT LALT(KC_ENT)
#define LIVE_CP LGUI(LALT(KC_F11))
#define VS_BLD LGUI(LSFT(KC_B))
#define VS_RUN KC_F5
#define SW_FWD PB_1
#define SW_BK PB_2
#define SW_WND PB_3
#define OP_TRM PB_4
#define MAX_MZ PB_5
#define DCK_LFT PB_6
#define DCK_RHT PB_7


#define BOOL_STATE(name) static bool name##_registered;

#define DOCK(state, key) \
printf(#state "pressed\n"); \
if(record->event.pressed) { \
    printf("sending " #state "\n"); \
    if(did_detect_windows) { \
        set_mods(MOD_MASK_GUI); \
    } else { \
        set_mods(MOD_MASK_CTRL | MOD_MASK_ALT); \
    } \
    register_code(key); \
    state##_registered = true; \
    set_mods(mod_state); \
    return false; \
} else { \
    if(state##_registered) { \
        printf("releasing " #state "\n"); \
        if(did_detect_windows) { \
            set_mods(MOD_MASK_GUI); \
        } \
        unregister_code(key); \
        if(did_detect_windows) { \
            set_mods(mod_state); \
            unregister_mods(MOD_MASK_GUI); \
        } \
        state##_registered = false; \
        return false; \
    } \
    return true; \
} \
return true;

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
        LU(KC_A),KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
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
        _______, SHT_TAB, SHT_ALT, SW_WND,  KC_DEL ,   _______, KC_7,    KC_8,    KC_9,    _______,
        _______, SW_BK,   SW_FWD,  KC_LSFT, _______,   KC_DOT,  KC_4,    KC_5,    KC_6,    _______,
        _______, _______, _______, _______, OS_FX  ,   KC_0,    KC_1,    KC_2,    KC_3,    _______,
                                   _______, _______,   _______, _______
    ),

    [_FUNCTION_KEYS] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12,
        XXXXXXX, VS_RUN,  LIVE_CP, VS_BLD,  XXXXXXX,   XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F10,
                                   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX
    ),

    [_ARROWS] = LAYOUT_SUPER(
        _______, CMD_SF,  OP_TRM,  CMD_P,   CMD_PLT,   ALT_LFT, GO_BACK, GO_FWD,  ALT_RHT, _______,
        _______, MAX_MZ,  ALT_ENT, KC_LSFT, ALT_BSP,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, DCK_LFT, DCK_RHT, _______, EP_HOME,   KC_HOME, ALT_DWN, ALT_UP,  KC_END,  _______,
                                   _______, _______,   _______, _______
    ),

    [_EPHEMERAL_HOME] = LAYOUT(
        EH_LEFT, XXXXXXX, XXXXXXX, XXXXXXX, EH_RGHT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_REBOOT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
                            TO(_UNREAL), TO(_QWERTY), TO(_SPECIAL),   XXXXXXX
    ),

    [_UNREAL] = LAYOUT(
        TO_QRTY, KC_Q,    KC_W,    KC_E,    KC_R,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_C,    KC_V,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   XXXXXXX, KC_SPC,    XXXXXXX, XXXXXXX
    ),
};
// clang-format on

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }

    switch (detected_os) {
        case OS_MACOS:
            print("detected mac\n");
            break;
        case OS_IOS:
            print("detected ios\n");
            break;
        case OS_WINDOWS:
            print("detected windows\n");
            break;
        case OS_LINUX:
            print("detected linux\n");
            break;
        case OS_UNSURE:
            print("unknown os\n");
            break;
    }

    if(detected_os == OS_MACOS || detected_os == OS_IOS) {
        print("using mac keyboard layout\n");
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.swap_lctl_lgui = false;
        keymap_config.swap_rctl_rgui = false;
        eeconfig_update_keymap(keymap_config.raw);
        clear_keyboard();        
    } else {
        did_detect_windows = true;
        print("detected windows, swapping gui and control\n");
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.swap_lctl_lgui = true;
        keymap_config.swap_rctl_rgui = true;
        eeconfig_update_keymap(keymap_config.raw);
        clear_keyboard();
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
    static bool open_terminal_registered;
    static bool maximize_registered;
    BOOL_STATE(dock_left)
    BOOL_STATE(dock_right)
    BOOL_STATE(close_window);

    switch (keycode) {

    case SW_FWD:
        printf("SW_FWD pressed\n");
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

    case SW_BK:
          printf("SW_BK pressed\n");
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
    
    // override escape to send a different sequence
    // when alt_tab mode is activated    
    case KC_ESC:
        // send this as q on mac and del on windows
        if (record->event.pressed) {
            if(alt_tab_entered) {
                if(did_detect_windows) {
                    printf("triggering alt del\n");
                    register_code(KC_DEL);
                } else {
                    printf("triggering cmd q\n");
                    register_code(KC_Q);
                }
                close_window_registered = true;
                return false;
            }
        } else { 
            if (close_window_registered) {
                if(did_detect_windows) {
                    printf("releasing alt del\n");
                    unregister_code(KC_DEL);
                } else {
                    printf("releasing cmd q\n");
                    unregister_code(KC_Q);
                }
                close_window_registered = false;
                return false;
            }
            return true;
        }
        return true;

    case SW_WND:
        printf("SW_WND pressed\n");
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

    // open terminal for vscode is ctrl + grave
    // on both mac and windows
    case OP_TRM:
        printf("open terminal pressed\n");
        if(record->event.pressed) {
            printf("sending ctrl grave\n");
            add_mods(MOD_MASK_CTRL);
            
            // send ctrl + grave
            register_code(KC_GRAVE);
            open_terminal_registered = true;

            // put mod state back so 
            // subsequent presses are considered 'alt'
            set_mods(mod_state);
            return false;
        } else {
            if(open_terminal_registered) {
                printf("releasing ctl grave \n");
                unregister_code(KC_GRAVE);
                open_terminal_registered = false;
                return false;
            }
            return true;
        }
        return true;

    // maximize button
    case MAX_MZ:
        printf("maximize pressed\n");
        if(record->event.pressed) {
            printf("sending maximize\n");
            if(did_detect_windows) {
                set_mods(MOD_MASK_GUI);
                register_code(KC_UP);
            } else {
                set_mods(MOD_MASK_CTRL | MOD_MASK_ALT);
                register_code(KC_ENTER);
            }
            
            
            maximize_registered = true;

            // put mod state back
            set_mods(mod_state);
            return false;
        } else {
            if(maximize_registered) {
                printf("releasing maximize \n");
                if(did_detect_windows) {
                    unregister_code(KC_UP);
                } else {
                    unregister_code(KC_ENTER);
                }
                maximize_registered = false;
                return false;
            }
            return true;
        }
        return true;

    // dock left
    case DCK_LFT:
        DOCK(dock_left, KC_LEFT)

    case DCK_RHT:
        DOCK(dock_right, KC_RIGHT)
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



