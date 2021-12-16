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

const is31_led __flash g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |    G location
 *   |  |    |    B location
 *   |  |    |    | */

/*   Left Hand */
     {0, K_1, J_1, L_1}, {0, K_2, J_2, L_2}, {0, K_3, J_3, L_3}, {0, K_4, J_4, L_4}, {0, K_5, J_5, L_5}, {0, K_6, J_6, L_6},
     {0, H_1, G_1, I_1}, {0, H_2, G_2, I_2}, {0, H_3, G_3, I_3}, {0, H_4, G_4, I_4}, {0, H_5, G_5, I_5}, {0, H_6, G_6, I_6},
     {0, E_1, D_1, F_1}, {0, E_2, D_2, F_2}, {0, E_3, D_3, F_3}, {0, E_4, D_4, F_4}, {0, E_5, D_5, F_5}, {0, E_6, D_6, F_6},
     {0, B_1, A_1, C_1}, {0, B_2, A_2, C_2}, {0, B_3, A_3, C_3}, {0, B_4, A_4, C_4}, {0, B_5, A_5, C_5}, {0, B_6, A_6, C_6},
                                                                 {0, B_7, A_7, C_7}, {0, B_8, A_8, C_8}, {0, B_9, A_9, C_9},
/*   Right Hand */
     {1, K_1, J_1, L_1}, {1, K_2, J_2, L_2}, {1, K_3, J_3, L_3}, {1, K_4, J_4, L_4}, {1, K_5, J_5, L_5}, {1, K_6, J_6, L_6},
     {1, H_1, G_1, I_1}, {1, H_2, G_2, I_2}, {1, H_3, G_3, I_3}, {1, H_4, G_4, I_4}, {1, H_5, G_5, I_5}, {1, H_6, G_6, I_6},
     {1, E_1, D_1, F_1}, {1, E_2, D_2, F_2}, {1, E_3, D_3, F_3}, {1, E_4, D_4, F_4}, {1, E_5, D_5, F_5}, {1, E_6, D_6, F_6},
     {1, B_1, A_1, C_1}, {1, B_2, A_2, C_2}, {1, B_3, A_3, C_3}, {1, B_4, A_4, C_4}, {1, B_5, A_5, C_5}, {1, B_6, A_6, C_6},
     {1, B_7, A_7, C_7}, {1, B_8, A_8, C_8}, {1, B_9, A_9, C_9}
}
