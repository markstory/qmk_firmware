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

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
/* left hand            right hand */
#define LAYOUT( \
    K0_0, K0_1, K0_2, K0_3, K0_4, K0_5,        K0_6, K0_7, K0_8, K0_9, K0_10, K0_11,\
    K1_0, K1_1, K1_2, K1_3, K1_4, K1_5,        K1_6, K1_7, K1_8, K1_9, K1_10, K1_11,\
    K2_0, K2_1, K2_2, K2_3, K2_4, K2_5,        K2_6, K2_7, K2_8, K2_9, K2_10, K2_11,\
    K3_0, K3_1, K3_2, K3_3, K3_4, K3_5,        K3_6, K3_7, K3_8, K3_9, K3_10, K3_11,\
                      K4_3, K4_4, K4_5,        K4_6, K4_7, K4_8  \
) { \
    {K0_0,  K0_1,  K0_2,  K0_3, K0_4, K0_5},\
    {K1_0,  K1_1,  K1_2,  K1_3, K1_4, K1_5},\
    {K2_0,  K2_1,  K2_2,  K2_3, K2_4, K2_5},\
    {K3_0,  K3_1,  K3_2,  K3_3, K3_4, K3_5},\
    {KC_NO, KC_NO, KC_NO, K4_3, K4_4, K4_5},\
    \
    {K0_6, K0_7, K0_8, K0_9,  K0_10, K0_11},\
    {K1_6, K1_7, K1_8, K1_9,  K1_10, K1_11},\
    {K2_6, K2_7, K2_8, K2_9,  K2_10, K2_11},\
    {K3_6, K3_7, K3_8, K3_9,  K3_10, K3_11},\
    {K4_6, K4_7, K4_8, KC_NO, KC_NO, KC_NO}\
}
