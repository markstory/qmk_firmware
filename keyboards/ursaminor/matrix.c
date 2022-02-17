/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
          2020 Pierre Chevalier <pierrechevalier83@gmail.com>
          2021 Mark Story <mark@mark-story.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * This code was heavily inspired by the ferris and ergodox_ez keymap, and modernized
 * to take advantage of the quantum.h microcontroller agnostics gpio control
 * abstractions and use the macros defined in config.h for the wiring as opposed
 * to repeating that information all over the place.
 */
#include "quantum.h"
#include "mcp23018.h"
#include <print.h>


// For a better understanding of the i2c protocol, this is a good read:
// https://www.robot-electronics.co.uk/i2c-tutorial

// I2C address:
// See the datasheet, section 3.3.1 on addressing I2C devices and figure 3-6 for an
// illustration
// http://ww1.microchip.com/downloads/en/devicedoc/20001952c.pdf
// All address pins of the mcp23017 are connected to the ground on the triptych
// | 0  | 1  | 0  | 0  | A2 | A1 | A0 |
// | 0  | 1  | 0  | 0  | 0  | 0  | 0  |
#define I2C_ADDR 0b0100000

static uint8_t mcp23017_error = 0;
static uint16_t mcp23017_reset_loop = 0;

static const pin_t row_pins[MATRIX_ROWS_PER_SIDE] = MATRIX_ROW_PINS_MCU;
static const pin_t col_pins[MATRIX_COLS_PER_SIDE] = MATRIX_COL_PINS_MCU;

// --
// -- Row selection functions
// --
static void unselect_row(uint8_t row) {
    setPinInputHigh(row_pins[row]);
}

static void unselect_rows(void) {
    // no need to unselect on mcp23017, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction

    // unselect rows on microcontroller
    for (int pin_index = 0; pin_index < MATRIX_ROWS_PER_SIDE; pin_index++) {
        setPinInputHigh(row_pins[pin_index]);
    }
}

// TODO are column functions necessary? The viktus doesn't have these functions
static void unselect_cols(void) {
    // Unselect colum
    for (int pin_index = 0; pin_index < MATRIX_COLS_PER_SIDE; pin_index++) {
        setPinInputHigh(col_pins[pin_index]);
    }
}

static void select_row_mcu(uint8_t row) {
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void select_row_mcp(uint8_t row) {
    if (mcp23017_error) {
        return;
    }
    // Select the desired row by writing a byte to the GPIOB bus where
    // the row we want to read is a 0 all other rows bits are a 1.
    // Note that the row - MATRIX_ROWS_PER_SIDE reflects the fact that being on
    // the right hand, the columns are numbered from MATRIX_ROWS_PER_SIDE to
    // MATRIX_ROWS, but the pins we want to write to are indexed from zero up
    // on the GPIOB bus.
    uint8_t mask = 0xFF & ~(1 << (row - MATRIX_ROWS_PER_SIDE));
    mcp23017_error += !mcp23018_set_output(I2C_ADDR, mcp23018_PORTB, mask);
}

static matrix_row_t read_cols_mcu(uint8_t current_row) {
    matrix_row_t current_row_value = 0;
    matrix_io_delay();

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS_PER_SIDE; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }
    unselect_row(current_row);

    return current_row_value;
}

static matrix_row_t read_cols_mcp(uint8_t current_row) {
    if (mcp23017_error) {
        // if there was an error reading from the io expander.
        return 0;
    }
    select_row_mcp(current_row);

    // Read all pins from the MCP23017
    // We will get both GPIOA & GPIOB as u16.
    // The return value is a row as represented in the generic matrix code were
    // the rightmost bits represent the lower columns and zeroes represent
    // non-depressed keys while ones represent depressed keys.
    uint16_t data = 0;
    mcp23017_error += !mcp23018_readPins_all(I2C_ADDR, &data);

    // Remove the high 8 bits as they are GPOIB, and we want to read GPIOA
    uint8_t col_data = data;

    // Invert the bits as we get 1 for open keys and 0 for closed
    // ones from the mcp23017, but QMK wants active keys to be 1
    return (~col_data);
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_matrix_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t current_value = 0;
    if (current_row < MATRIX_ROWS_PER_SIDE) {
        select_row_mcu(current_row);
        current_value = read_cols_mcu(current_row);
    } else {
        select_row_mcp(current_row);
        current_value = read_cols_mcp(current_row);
    }
    if (current_matrix[current_row] == current_value) {
        return false;
    }
    current_matrix[current_row] = current_value;
    return true;
}

static void init_pins_mcp23017(void) {
    // This means: we will read all the bits on GPIOA (in read_cols_mcp)
    mcp23017_error += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTA, 0b11111111);
    // This means: we will write to the pins 0-5 on GPIOB (in select_rows_mcp)
    mcp23017_error += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTB, 0b11100000);
}

static void init_pins_mcu(void) {
    unselect_rows();
    unselect_cols();
}

// --
// -- Custom Matrix Implementation
// --
void matrix_init_custom(void) {
    // initialize row and col
    mcp23018_init(I2C_ADDR);

    init_pins_mcu();
    init_pins_mcp23017();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS_PER_SIDE; current_row++) {
        changed |= store_matrix_row(current_matrix, current_row);
    }

    if (mcp23017_error) {  // if there was an error
        print("right side disconnected!\n");
        if (++mcp23017_reset_loop > 0xFF) {
            print("Attempting to reset mcp23017\n");
            mcp23017_error = 0;
            mcp23017_reset_loop = 0;
            init_pins_mcp23017();

            if (mcp23017_error) {
                print("right side not responding\n");
            } else {
                print("right side attached\n");
                // Restart RGB when the right side
                // is reattached.
                rgb_matrix_init();
            }
        }
        return changed;
    }

    for (uint8_t current_row = MATRIX_ROWS_PER_SIDE; current_row < MATRIX_ROWS; current_row++) {
        changed |= store_matrix_row(current_matrix, current_row);
    }

    return changed;
}
