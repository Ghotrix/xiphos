/*
  Xiphos, a UCI chess engine
  Copyright (C) 2018 Milos Tatarevic

  Xiphos is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Xiphos is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SEARCH_H
#define SEARCH_H

#include "move.h"
#include "position.h"
#include "util.h"

#define MAX_GAME_PLY  1024
#define TM_STEPS      10

typedef struct {
  int tid, hash_keys_cnt;
  uint64_t nodes, hash_key;
  position_t *pos,
              pos_list[PLY_LIMIT];
  move_t   killer_moves[PLY_LIMIT][MAX_KILLER_MOVES],
           counter_moves[P_LIMIT][BOARD_SIZE];
  int16_t  history[N_SIDES][BOARD_SIZE][BOARD_SIZE],
           counter_move_history[P_LIMIT][BOARD_SIZE][P_LIMIT * BOARD_SIZE];
  uint64_t hash_keys[MAX_GAME_PLY];
} search_data_t;

struct {
  int max_threads, max_depth, done, score, depth, best_move_cnt,
      search_depth_cnt[MAX_DEPTH];
  move_t best_move;
  uint64_t time_in_ms, max_time, target_time[TM_STEPS];
  struct {
    int time, inc, movestogo, depth, movetime;
  } go;
} shared_search_info;

void init_lmr();
void search(search_data_t *, search_data_t *);
void reset_search_data(search_data_t *);
void full_reset_search_data(search_data_t *);

#endif
