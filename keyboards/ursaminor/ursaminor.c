/* Copyright 2021 Mark Story
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

#include "ursaminor.h"

#if RGB_MATRIX_ENABLE
/*
 * Driver addresses to LED matrix
 */
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |    G location
 *   |  |    |    B location
 *   |  |    |    | */

// Left Hand
     {0, K_1, J_1, L_1}, {0, K_2, J_2, L_2}, {0, K_3, J_3, L_3}, {0, K_4, J_4, L_4}, {0, K_5, J_5, L_5}, {0, K_6, J_6, L_6},
     {0, H_1, G_1, I_1}, {0, H_2, G_2, I_2}, {0, H_3, G_3, I_3}, {0, H_4, G_4, I_4}, {0, H_5, G_5, I_5}, {0, H_6, G_6, I_6},
     {0, E_1, D_1, F_1}, {0, E_2, D_2, F_2}, {0, E_3, D_3, F_3}, {0, E_4, D_4, F_4}, {0, E_5, D_5, F_5}, {0, E_6, D_6, F_6},
     {0, B_1, A_1, C_1}, {0, B_2, A_2, C_2}, {0, B_3, A_3, C_3}, {0, B_4, A_4, C_4}, {0, B_5, A_5, C_5}, {0, B_6, A_6, C_6},
                                                                 {0, B_7, A_7, C_7}, {0, B_8, A_8, C_8}, {0, B_9, A_9, C_9},
// Right Hand
     {1, K_1, J_1, L_1}, {1, K_2, J_2, L_2}, {1, K_3, J_3, L_3}, {1, K_4, J_4, L_4}, {1, K_5, J_5, L_5}, {1, K_6, J_6, L_6},
     {1, H_1, G_1, I_1}, {1, H_2, G_2, I_2}, {1, H_3, G_3, I_3}, {1, H_4, G_4, I_4}, {1, H_5, G_5, I_5}, {1, H_6, G_6, I_6},
     {1, E_1, D_1, F_1}, {1, E_2, D_2, F_2}, {1, E_3, D_3, F_3}, {1, E_4, D_4, F_4}, {1, E_5, D_5, F_5}, {1, E_6, D_6, F_6},
     {1, B_1, A_1, C_1}, {1, B_2, A_2, C_2}, {1, B_3, A_3, C_3}, {1, B_4, A_4, C_4}, {1, B_5, A_5, C_5}, {1, B_6, A_6, C_6},
     {1, B_7, A_7, C_7}, {1, B_8, A_8, C_8}, {1, B_9, A_9, C_9}
};

/*
 * Key switch to LED mappings
 */
led_config_t g_led_config = {
    // Key matrix to LED Index
    {
        // Left hand
        {0,   1,  2,  3,  4,  5},
        {6,   7,  8,  9, 10, 11},
        {12, 13, 14, 15, 16, 17},
        {18, 19, 20, 21, 22, 23},
        {24, 25, 26},

        // Right hand
        {27, 28, 29, 30, 31, 32},
        {33, 34, 35, 36, 37, 38},
        {39, 40, 41, 42, 43, 44},
        {45, 46, 47, 48, 49, 50},
        {51, 52, 53}
    },
    // LED Index to Phyiscal Position 
    // Map index to {x, y} where x = 0...224  and y = 0...64
    // Each x increment is 224/14 = 16. Each y increment is 64/5 = 12
    {
        // left hand
        {0, 0},  {16, 0},  {32, 0},  {48, 0},  {64, 0},  {80, 0},
        {0, 12}, {16, 12}, {32, 12}, {48, 12}, {64, 12}, {80, 12},
        {0, 24}, {16, 24}, {32, 24}, {48, 24}, {64, 24}, {80, 24},
        {0, 36}, {16, 36}, {32, 36}, {48, 36}, {64, 36}, {80, 36},
                                              {72, 48}, {85, 48}, {96, 48},

        // right hand
        {128, 0},  {144, 0},  {160, 0},  {176, 0},  {192, 0},  {208, 0},
        {128, 12}, {144, 12}, {160, 12}, {176, 12}, {192, 12}, {208, 12},
        {128, 24}, {144, 24}, {160, 24}, {176, 24}, {192, 24}, {208, 24},
        {128, 36}, {144, 36}, {160, 36}, {176, 36}, {192, 36}, {208, 36},
    {112, 48}, {123, 48}, {136, 48}
    },
    // LED Index to Flag
    {
        // left hand
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,

        // Right hand
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
        LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
    }
};
#endif
