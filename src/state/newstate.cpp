#include <iostream>
#include <sstream>
#include <cstdint>
#include <cmath>
#include "./newstate.hpp"
#include <climits>
#include "../config.hpp"
//int dir[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

/**
 * @brief evaluate the state
 * 
 * @return int 
 */

// bool atk_by_bqueen(Board b, int r1, int c1, int r2, int c2){
//   if(r1 == r2){
//     for(int i = std :: min(c1, c2) + 1; i < std :: max(c1, c2); i++){
//       if(b.board[0][r1][i] || b.board[1][r1][i]) return false;
//     }
//     return true;
//   }
//   if(c1 == c2){
//     for(int i = std :: min(r1, r2) + 1; i < std :: max(r1, r2); i++){
//       if(b.board[0][i][c1] || b.board[1][i][c1]) return false;
//     }
//     return true;
//   }
//   if(abs(r1 - r2) == abs(c1 - c2)){
//     int dx = (r2 - r1) / abs(r1 - r2), dy = (c2 - c1) / abs(c1 - c2);
//     for(int i = 1; i < abs(r1 - r2); i++){
//       if(b.board[0][r1 + dx * i][c1 + dy * i] || b.board[1][r1 + dx * i][c1 + dy * i]) return false;
//     }
//     return true;
//   }
// }

bool atk_by_bbishop(Board b, int r1, int c1, int r2, int c2){
  if(abs(r1 - r2) == abs(c1 - c2)){
    int dx = (r2 - r1) / abs(r1 - r2), dy = (c2 - c1) / abs(c1 - c2);
    for(int i = 1; i < abs(r1 - r2); i++){
      if(b.board[0][r1 + dx * i][c1 + dy * i] || b.board[1][r1 + dx * i][c1 + dy * i]) return false;
    }
    return true;
  }
  return false;
}

bool atk_by_brook(Board b, int r1, int c1, int r2, int c2){
  if(r1 == r2){
    for(int i = std :: min(c1, c2) + 1; i < std :: max(c1, c2); i++){
      if(b.board[0][r1][i] || b.board[1][r1][i]) return false;
    }
    return true;
  }
  if(c1 == c2){
    for(int i = std :: min(r1, r2) + 1; i < std :: max(r1, r2); i++){
      if(b.board[0][i][c1] || b.board[1][i][c1]) return false;
    }
    return true;
  }
  return false;
}

int newState::evaluate(){
  // [TODO] design your own evaluation function
  int king = 10000, queen = 100, bishop = 80, knight = 70, rook = 60, pawn = 20;
  int myvalue = 0, opvalue = 0;
  int ok[6][2] = {0};
  int kr[2] = {0}, kc[2] = {0}, qr[2] = {0}, qc[2] = {0}, br[2] = {0}, bc[2] = {0}, rr[2] = {0}, rc[2] = {0};  
  // int myrow[10] = {0}, mycol[10] = {0}, oprow[10] = {0}, opcol[10];
  if(this -> player && this -> game_state == WIN) return INT_MIN;
  if(!this -> player && this -> game_state == WIN) return INT_MAX;
  for(int j = 0; j < BOARD_H; j++){
    for(int k = 0; k < BOARD_W; k++){
      int mytype = board.board[0][j][k], optype = board.board[1][j][k];
      // if(mytype) myrow[j]++, myrow[k]++;
      // if(optype) oprow[j]++, opcol[k]++;
      if(mytype == 1){
        myvalue += pawn; 
      }
      else if(mytype == 2){
        rr[0] = j, rc[0] =  k, ok[2][0] = 1;
        myvalue += rook;
      } 
      else if(mytype == 3) myvalue += knight;
      else if(mytype == 4){
        br[0] = j, bc[0] = k, ok[4][0] = 1;
        myvalue += bishop;
      } 
      else if(mytype == 5){
        qr[0] = j, qc[0] = k, ok[5][0] = 1;
        myvalue += queen;
      } 
      else if(mytype == 6){
        kr[0] = j, kc[0] = k, ok[6][0] = 1;
        myvalue += king; 
      } 
      if(optype == 1) opvalue += pawn;
      else if(optype == 2){
        rr[1] = j, rc[1] =  k, ok[2][1] = 1;
        opvalue += rook;
      } 
      else if(optype == 3) opvalue += knight;
      else if(optype == 4){
        br[1] = j, bc[1] = k, ok[4][1] = 1;
        opvalue += bishop;
      } 
      else if(optype == 5){
        qr[1] = j, qc[1] = k, ok[5][1] = 1;
        opvalue += queen;
      } 
      else if(optype == 6){
        kr[0] = j, kc[0] = k, ok[6][1] = 1;
        opvalue += king; 
      } 
    } 
  }
  if(!ok[6][0]) return INT_MIN;
  if(!ok[6][1]) return INT_MAX;
  if(player && ok[2][1] && atk_by_brook(board, kr[0], kc[0], rr[1], rc[1])) return INT_MIN;
  if(player && ok[4][1] && atk_by_bbishop(board, kr[0], kc[0], br[1], bc[1])) return INT_MIN;
  if(player && ok[5][1] && (atk_by_brook(board, kr[0], kc[0], qr[1], qc[1]) || atk_by_bbishop(board, kr[0], kc[0], qr[1], qc[1]))) return INT_MIN;
  if(!player && ok[2][0] && atk_by_brook(board, kr[1], kc[1], rr[0], rc[0])) return INT_MAX;
  if(!player && ok[4][0] && atk_by_bbishop(board, kr[1], kc[1], br[0], bc[0])) return INT_MAX;
  if(!player && ok[5][0] && (atk_by_brook(board, kr[1], kc[1], qr[0], qc[0]) || atk_by_bbishop(board, kr[0], kc[0], qr[1], qc[1]))) return INT_MAX;

  //if(myvalue >= king && opvalue < king) return INT_MAX;
  //if(myvalue < king && opvalue >= king) return INT_MIN;
  return myvalue - opvalue;
}


/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
newState* newState::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  newState* next_state = new newState(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void newState::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  bool ok[6][2] = {0};
  int pos[6][2] = {0};
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      int now_piece = self_board[i][j];
      if(now_piece == 1);
      // if((now_piece=self_board[i][j])){
      //   // std::cout << this->player << "," << now_piece << ' ';
      //   switch (now_piece){
      //     case 1: //pawn
      //       if(this->player && i<BOARD_H-1){
      //         //black
      //         if(!oppn_board[i+1][j] && !self_board[i+1][j])
      //           all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
      //         if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
      //           all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
      //           if(oppn_piece==6){
      //             this->game_state = WIN;
      //             this->legal_actions = all_actions;
      //             return;
      //           }
      //         }
      //         if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
      //           all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
      //           if(oppn_piece==6){
      //             this->game_state = WIN;
      //             this->legal_actions = all_actions;
      //             return;
      //           }
      //         }
      //       }else if(!this->player && i>0){
      //         //white
      //         if(!oppn_board[i-1][j] && !self_board[i-1][j])
      //           all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
      //         if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
      //           all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
      //           if(oppn_piece==6){
      //             this->game_state = WIN;
      //             this->legal_actions = all_actions;
      //             return;
      //           }
      //         }
      //         if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
      //           all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
      //           if(oppn_piece==6){
      //             this->game_state = WIN;
      //             this->legal_actions = all_actions;
      //             return;
      //           }
      //         }
      //       }
      //       break;
          
      //     case 2: //rook
      //     case 4: //bishop
      //     case 5: //queen
      //       int st, end;
      //       switch (now_piece){
      //         case 2: st=0; end=4; break; //rook
      //         case 4: st=4; end=8; break; //bishop
      //         case 5: st=0; end=8; break; //queen
      //         default: st=0; end=-1;
      //       }
      //       for(int part=st; part<end; part+=1){
      //         auto move_list = move_table_rook_bishop[part];
      //         for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
      //           int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
      //           if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
      //           now_piece = self_board[p[0]][p[1]];
      //           if(now_piece) break;
                
      //           all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
      //           oppn_piece = oppn_board[p[0]][p[1]];
      //           if(oppn_piece){
      //             if(oppn_piece==6){
      //               this->game_state = WIN;
      //               this->legal_actions = all_actions;
      //               return;
      //             }else
      //               break;
      //           };
      //         }
      //       }
      //       break;
          
      //     case 3: //knight
      //       for(auto move: move_table_knight){
      //         int x = move[0] + i;
      //         int y = move[1] + j;
              
      //         if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
      //         now_piece = self_board[x][y];
      //         if(now_piece) continue;
      //         all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
      //         oppn_piece = oppn_board[x][y];
      //         if(oppn_piece==6){
      //           this->game_state = WIN;
      //           this->legal_actions = all_actions;
      //           return;
      //         }
      //       }
      //       break;
          
      //     case 6: //king
      //       for(auto move: move_table_king){
      //         int p[2] = {move[0] + i, move[1] + j};
              
      //         if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
      //         now_piece = self_board[p[0]][p[1]];
      //         if(now_piece) continue;
              
      //         all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
      //         oppn_piece = oppn_board[p[0]][p[1]];
      //         if(oppn_piece==6){
      //           this->game_state = WIN;
      //           this->legal_actions = all_actions;
      //           return;
      //         }
      //       }
      //       break;
      //   }
      // }
    }
  }
  std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string newState::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string newState::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}