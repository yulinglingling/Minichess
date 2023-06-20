#include <iostream>
#include <fstream>

#include "../config.hpp"
#include "../state/state.hpp"
#include "../policy/submission.hpp"


State* root;
const std::string file_log = "gamelog2.txt";
/**
 * @brief Read the board from the file
 * 
 * @param fin 
 */
void read_board(std::ifstream& fin) {
  Board board;
  int player;
  fin >> player;

  for (int pl=0; pl<2; pl++) {
    for (int i=0; i<BOARD_H; i++) {
      for (int j=0; j<BOARD_W; j++) {
        int c; fin >> c;
        // std::cout << c << " ";
        board.board[pl][i][j] = c;
      }
      // std::cout << std::endl;
    }
  }
  root = new State(board, player);
  root->get_legal_actions();
}


/**
 * @brief randomly choose a move and then write it into output file
 * 
 * @param fout 
 */


void write_valid_spot(std::ofstream& fout) {
  // Keep updating the output until getting killed.
  
  int depth = 5;
  while(true) {
    // Choose a random spot.
    
    int p = 0;
    if(root -> player) p = -1;
    else if(!root -> player) p = 1; 
    auto move = submit::get_move(root, depth, p);
    fout << move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second << std::endl;
    
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
    depth++;
    //break;
  }
  
}


/**
 * @brief Main function for player
 * 
 * @param argv 
 * @return int 
 */

int main(int, char** argv) {
  
  
  srand(RANDOM_SEED);
  std::ifstream fin(argv[1]);
  //log << "fin" << argv[1] << std::endl;
  std::ofstream fout(argv[2]);
  //log << "fout" << argv[2] << std::endl;

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
