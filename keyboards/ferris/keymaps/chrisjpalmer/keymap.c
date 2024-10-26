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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
        KC_Q,           KC_W,           KC_E,           KC_R,         KC_T,                     KC_Y,           KC_U,         KC_I,              KC_O,             KC_P,              
        LSFT_T(KC_A),   LT(5,KC_S),     LT(1,KC_D),     LT(3,KC_F),   KC_G,                     KC_H,           LT(4,KC_J),   LT(2,KC_K),        LT(6,KC_L),       LSFT_T(KC_SCLN),   
        KC_Z,           LCTL_T(KC_X),   LALT_T(KC_C),   KC_V,         KC_B,                     KC_N,           KC_M,         LALT_T(KC_COMM),   LCTL_T(KC_DOT),   KC_SLSH,           
                                                        CG_TOGG,      KC_BSPC,                  LT(7,KC_SPC),   KC_P1                                                                 
    ),
    [1] = LAYOUT_split_3x5_2(
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,            KC_TRNS,   KC_BTN1,   KC_WH_U,   KC_BTN2,   KC_TRNS,   
        KC_TRNS,   KC_BTN2,   KC_NO,     KC_BTN1,   KC_TRNS,            KC_TRNS,   KC_MS_L,   KC_MS_D,   KC_MS_U,   KC_MS_R,   
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,            KC_TRNS,   KC_WH_L,   KC_WH_D,   KC_WH_R,   KC_TRNS,   
                                         KC_TRNS,   KC_TRNS,            KC_TRNS,   KC_TRNS                                     
    ),
    [2] = LAYOUT_split_3x5_2(
        KC_TRNS,   KC_TRNS,   KC_PGUP,   KC_TRNS,   KC_TRNS,            KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,         KC_TRNS,        
        KC_LEFT,   KC_UP,     KC_DOWN,   KC_RGHT,   KC_TRNS,            KC_TRNS,   KC_LGUI,   KC_NO,     LCTL(KC_LALT),   LCA(KC_LSFT),   
        KC_TRNS,   KC_HOME,   KC_PGDN,   KC_END,    KC_TRNS,            KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,         KC_TRNS,        
                                         KC_TRNS,   KC_TRNS,            KC_TRNS,   KC_TRNS                                                
    ),
    [3] = LAYOUT_split_3x5_2(
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,                   KC_TRNS,   KC_UNDS,   KC_PIPE,   KC_QUOT,   KC_TRNS,   
        KC_CIRC,   KC_ASTR,   KC_AMPR,   KC_NO,      KC_TRNS,                   KC_HASH,   KC_TILD,   KC_SLSH,   KC_DQUO,   KC_DLR,    
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,                   KC_TRNS,   KC_MINS,   KC_BSLS,   KC_GRV,    KC_TRNS,   
                                         RGB_RMOD,   KC_TRNS,                   KC_TRNS,   RGB_MOD                                     
    ),
    [4] = LAYOUT_split_3x5_2(
        KC_TRNS,   KC_COLN,   KC_LT,     KC_GT,     KC_SCLN,            KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   
        KC_LCBR,   KC_RCBR,   KC_LPRN,   KC_RPRN,   KC_AT,              KC_TRNS,   KC_NO,     KC_EQL,    KC_PLUS,   KC_PERC,   
        KC_TRNS,   KC_EXLM,   KC_LBRC,   KC_RBRC,   KC_TRNS,            KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   
                                         KC_VOLD,   KC_TRNS,            KC_TRNS,   KC_VOLU                                     
    ),
    [5] = LAYOUT_split_3x5_2(
        KC_TRNS,   KC_TRNS,   KC_TRNS,         KC_TRNS,   KC_TRNS,              KC_TRNS,   KC_F7,    KC_F8,   KC_F9,   KC_F10,   
        KC_TRNS,   KC_NO,     LCTL(KC_LALT),   KC_TRNS,   KC_TRNS,              KC_TRNS,   KC_F4,    KC_F5,   KC_F6,   KC_F11,   
        KC_TRNS,   KC_TRNS,   KC_TRNS,         KC_TRNS,   KC_TRNS,              KC_TRNS,   KC_F1,    KC_F2,   KC_F3,   KC_F12,   
                                               KC_TRNS,   KC_TRNS,              KC_TRNS,   KC_TRNS                               
    ),
    [6] = LAYOUT_split_3x5_2(
        KC_PSLS,   KC_7,   KC_8,   KC_9,      KC_PPLS,                  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   
        KC_0,      KC_1,   KC_2,   KC_3,      KC_PMNS,                  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_NO,     KC_TRNS,   
        KC_PAST,   KC_4,   KC_5,   KC_6,      KC_PEQL,                  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   
                                   KC_TRNS,   KC_TRNS,                  KC_TRNS,   KC_TRNS                                     
    ),
    [7] = LAYOUT_split_3x5_2(
        KC_TRNS,   KC_TRNS,   KC_COLN,   KC_ESC,    KC_TRNS,            KC_TRNS,   KC_TRNS,   KC_TRNS,           KC_TRNS,          KC_DEL,    
        KC_TRNS,   KC_PERC,   KC_SLSH,   KC_ENT,    KC_TRNS,            DF(1),     KC_LGUI,   KC_TRNS,           KC_TRNS,          KC_TRNS,   
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_EXLM,   KC_TRNS,            DF(0),     KC_TRNS,   RALT_T(KC_COMM),   RCTL_T(KC_DOT),   QK_BOOT,   
                                         KC_TRNS,   KC_TAB,             KC_NO,     KC_TRNS                                                    
    )
};
// clang-format on
static bool did_detect_mac = false;
bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            // rgb_matrix_set_color_all(RGB_WHITE);
            did_detect_mac = true;
            print("detected mac\n");
            break;
        case OS_WINDOWS:
            // rgb_matrix_set_color_all(RGB_BLUE);
            print("detected windows\n");
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
bool ctrl_down = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
    // return true;
    // Store the current modifier state in the variable for later reference
    // uint8_t mod_state = get_mods();
    // if(mod_state & MOD_MASK_CTRL) {
    //     // del_mods(MOD_MASK_CTRL);
    //     set_mods(MOD_LGUI);
    //     ctrl_down = true;
    // } else if(ctrl_down) {
    //     ctrl_down = false;
    //     del_mods(MOD_LGUI);
    // }
    // return true;
    // switch (keycode) {

    // case KC_BSPC:
    //     {
    //     // Initialize a boolean variable that keeps track
    //     // of the delete key status: registered or not?
    //     static bool delkey_registered;
    //     if (record->event.pressed) {
    //         // Detect the activation of either shift keys
    //         if (mod_state & MOD_MASK_SHIFT) {
    //             // First temporarily canceling both shifts so that
    //             // shift isn't applied to the KC_DEL keycode
    //             del_mods(MOD_MASK_SHIFT);
    //             register_code(KC_DEL);
    //             // Update the boolean variable to reflect the status of KC_DEL
    //             delkey_registered = true;
    //             // Reapplying modifier state so that the held shift key(s)
    //             // still work even after having tapped the Backspace/Delete key.
    //             set_mods(mod_state);
    //             return false;
    //         }
    //     } else { // on release of KC_BSPC
    //         // In case KC_DEL is still being sent even after the release of KC_BSPC
    //         if (delkey_registered) {
    //             unregister_code(KC_DEL);
    //             delkey_registered = false;
    //             return false;
    //         }
    //     }
    //     // Let QMK process the KC_BSPC keycode as usual outside of shift
    //     return true;
    // }

    // }
    // return true;
};

// bool is_mac(bool key_down, void *layer) {
//     printf("is_mac() called, returning %i\n", did_detect_mac);
//     return did_detect_mac;
// }
// // key_override_t lctl_override2 = ko_make_basic();

// key_override_t lctl_override = {.trigger_mods           = MOD_BIT(KC_LCTL),                       //
//                                 .layers                 = ~0,                                          //
//                                 .suppressed_mods        = MOD_BIT(KC_LCTL),                       //
//                                 .options                = ko_options_all_activations,                 //
//                                 .negative_mod_mask      = 0,          //
//                                 .custom_action          = is_mac,                                           //
//                                 .context                = NULL,                                          //
//                                 .trigger                = KC_NO,                                                     //
//                                 .replacement            = KC_LGUI,                                                     //
//                                 .enabled                = NULL};

// key_override_t rctl_override = {.trigger_mods           = MOD_BIT(KC_RCTL),                       //
//                                 .layers                 = ~0,                                          //
//                                 .suppressed_mods        = MOD_BIT(KC_RCTL),                       //
//                                 .options                = ko_options_all_activations,                 //
//                                 .negative_mod_mask      = 0,          //
//                                 .custom_action          = is_mac,                                           //
//                                 .context                = NULL,                                          //
//                                 .trigger                = KC_NO,                                                     //
//                                 .replacement            = KC_RGUI,                                                     //
//                                 .enabled                = NULL};

// const key_override_t *key_overrides[] = {
// 	// &delete_key_override
//     &lctl_override,
//     &rctl_override,
// };

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)



