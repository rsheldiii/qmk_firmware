/* Copyright 2016 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "process_combo.h"
#include "print.h"

__attribute__ ((weak))
combo_t key_combos[] = {};

__attribute__ ((weak))
void process_combo_event(uint8_t combo_index, bool pressed) {}

static bool clear_current_buffer = false;
static keyrecord_t keypress_buffer[8];
static uint8_t buffer_size = 0;
static uint16_t timer = 0;

static inline void send_combo(uint8_t combo_index, bool pressed) {
    combo_t *combo = &key_combos[combo_index];
    uint16_t action = combo->keycode;

    if (action) {
        if (pressed) {
            register_code16(action);
        } else {
            unregister_code16(action);
        }
    } else {
        process_combo_event(combo_index, pressed);
    }
}

static inline void dump_keypress_buffer(bool print) {
    if (print) {
        for (uint8_t i = 0; i < buffer_size; i++) {
            const action_t action = store_or_get_action(keypress_buffer[i].event.pressed, keypress_buffer[i].event.key);
            process_action(&(keypress_buffer[i]), action);
        }
    }

    buffer_size = 0;
}

#define ALL_COMBO_KEYS_ARE_DOWN     (((1<<count)-1) == combo->state)
#define KEY_STATE_DOWN(key)         do{ combo->state |= (1<<key); } while(0)
#define KEY_STATE_UP(key)           do{ combo->state &= ~(1<<key); } while(0)

static bool process_single_combo(uint8_t combo_index, uint16_t keycode, keyrecord_t *record) {
    combo_t *combo = &(key_combos[combo_index]);
    uint8_t count = 0;
    uint8_t index = -1;

    /* Find index of keycode and number of combo keys */
    for (const uint16_t *keys = combo->keys; ;++count) {
        uint16_t key = pgm_read_word(&(keys[count]));
        if (keycode == key) index = count;
        if (COMBO_END == key) break;
    }

    /* Continue processing if not a combo key */
    if (-1 == (int8_t)index) {
        return true;
    }

    if (record->event.pressed) {
        KEY_STATE_DOWN(index);

        if (ALL_COMBO_KEYS_ARE_DOWN) {
            /* Combo was pressed, send combo and clear buffer */
            send_combo(combo_index, true);
            clear_current_buffer = true;
        }

        /* Pressed combo key, don't process */
        return false;
    } else {
        bool continue_processing = true;
        if (ALL_COMBO_KEYS_ARE_DOWN) {
            /* Combo released, unsend and don't process */
            send_combo(combo_index, false);
            /* don't continue processing */
            continue_processing = false;
        }

        KEY_STATE_UP(index);
        /* continue processing if incomplete combo was released */
        return continue_processing;
    }
}

bool process_combo(uint16_t keycode, keyrecord_t *record) {
    bool continue_processing_record = true;

    clear_current_buffer = false;
    for (uint8_t combo_index = 0; combo_index < COMBO_COUNT; ++combo_index) {
        continue_processing_record &= process_single_combo(combo_index, keycode, record);
    }

    if (clear_current_buffer) {
        /* Just clear, no print */
        dump_keypress_buffer(false);
    } else if (continue_processing_record) {
        /* If no combo consumes the record, we spit out our buffer */
        dump_keypress_buffer(true);
    } else if (record->event.pressed) {
      /* Record all keypresses that don't drop the buffer */
        timer = timer_read();
        keypress_buffer[buffer_size] = *record;
        buffer_size++;
    }

    return continue_processing_record;
}

void matrix_scan_combo(void) {
    if (timer != 0) {
        if (timer_elapsed(timer) > COMBO_TERM) {
            dump_keypress_buffer(true);
            timer = 0;
        }
    }
}
