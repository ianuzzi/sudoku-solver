#include <iostream>

using namespace std;

// todo
// Clean up output
// begin adding optimizations
  // only try remaining digits in a set of available numbers for the row, col, sqr, etc.

void display_board (const int bd[9][9]){
  // displays a board to the screen
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      cout << bd[i][j] << " ";
      if (j % 3 == 2 && j != 8) cout << "| ";
    }
    cout << endl;
    if (i % 3 == 2 && i != 8) cout << "---------------------" << endl;
  }
  cout << endl;
}

bool check_row (int bd[9][9], int c[2]){
  // returns true if the current row does not contain any duplicates
  int* test_list = new int[10] {0};
  for (int j=0; j<9; j++){
    if (test_list[bd[c[0]][j]]++ >= 1 && bd[c[0]][j] != 0) return false;
  }
  delete[] test_list;
  return true;
}

bool check_rows (int bd[9][9]){
  for (int i=0; i<9; i++){
    int* test_list = new int[10] {0};
    for (int j=0; j<9; j++){
      if (test_list[bd[i][j]]++ >= 1 && bd[i][j] != 0) return false;
    }
    delete[] test_list;
  }
  return true;
}

bool check_col (int bd[9][9], int c[2]){
  // returns true if the current column contains no duplicates
  int* test_list = new int[10] {0};
  for (int i=0; i<9; i++){
    if (test_list[bd[i][c[1]]]++ >= 1 && bd[i][c[1]] != 0) return false;
  }
  delete[] test_list;
  return true;
}

bool check_cols (int bd[9][9]){
  // returns true if there are no columns with duplicated digits
  for (int j=0; j<9; j++){
    int* test_list = new int[10] {0};
    for (int i=0; i<9; i++){
      if (test_list[bd[i][j]]++ >= 1 && bd[i][j] != 0) return false;
    }
    delete[] test_list;
  }
  return true;
}

bool check_sqr (int bd[9][9], int c[2]){
  // returns true if the current sqaure contains no dupliacted digits
  int i_os = (c[0]/3)*3; // find the row and col offset for the square
  int j_os = (c[1]/3)*3; // int div times 3 drops remainder
  int* test_list = new int[10] {0};
  for (int i=0; i<3; i++){
    for (int j=0; j<3; j++){
      if (test_list[bd[i_os + i][j_os + j]]++ >=1 && bd[i_os + i][j_os + j] != 0) return false;
    }
  }
  delete[] test_list;

  return true;
}

bool check_sqrs (int bd[9][9]){
  // returns true if there are no squares with dupliacted digits
  for (int i_os=0; i_os<9; i_os+=3){
    for (int j_os=0; j_os<9; j_os+=3){
      int* test_list = new int[10] {0};
      for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
          if (test_list[bd[i_os + i][j_os + j]]++ >=1 && bd[i_os + i][j_os + j] != 0) return false;
        }
      }
      delete[] test_list;
    }
  }
  return true;
}

bool check_board (int bd[9][9]){
  // returns true if there are no duplicats in any row, column, or square
  // for the entire board
  if (!check_rows(bd)) return false;
  if (!check_cols(bd)) return false;
  if (!check_sqrs(bd)) return false;
  return true;
}

bool check_valid_move (int bd[9][9], int c[2]){
  // returns true if the row, col, and sqaure containing the current square square
  // are valid
  if (!check_row(bd, c)) return false;
  if (!check_col(bd, c)) return false;
  if (!check_sqr(bd, c)) return false;
  return true;
}

void copy_board(const int src[9][9], int dest[9][9]){
  // take 2 boards and copies the first into the second, overwriting the second
  for (int i=0; i<9; i++){
    for (int j=0; j<9; j++){
      dest[i][j] = src[i][j];
    }
  }
}

bool advance_cursor(const int bd[9][9], int c[2]){
  // Advances the cursor to the next blank space in the game board and returns
  // true or returns false if the cursor is at the last square on the board
cout << "here" << c[0]<<c[1]<<" "<<bd[c[0]][c[1]]<< endl;
  do {
    if (c[0] == 8 && c[1] == 8){
      return false;
    } else if (c[1] != 8){
      c[1]++;
    } else {
      c[0]++;
      c[1] = 0;
    }
  } while (bd[c[0]][c[1]] != 0);

  return true;
  cout << "cursor advanced - from advance cursor function" << endl;
}

bool rewind_cursor(const int bd[9][9], int c[2]){
  // Rewinds the cursor to the previous blank space in the game board and returns
  // true or returns false if the cursor is at the first square on the board
  do {
    if (c[0] == 0 && c[1] == 0){
      return false;
    } else if (c[1] != 0){
      c[1]--;
    } else {
      c[0]--;
      c[1] = 8;
    }
  } while (bd[c[0]][c[1]] != 0);
  return true;
}

int main(){

  cout << "Sudoku Solver" << endl << endl;

  // Cerate the board
  const int orig_board[9][9] {
    {0, 0, 7,  6, 9, 0,  5, 0, 4},
    {0, 0, 0,  3, 0, 2,  0, 0, 7},
    {2, 0, 5,  0, 7, 0,  0, 8, 9},

    {6, 0, 0,  5, 0, 0,  0, 0, 1},
    {9, 0, 0,  0, 3, 0,  0, 0, 5},
    {5, 0, 0,  0, 0, 9,  0, 0, 2},

    {7, 9, 0,  0, 2, 0,  4, 0, 3},
    {3, 0, 0,  1, 0, 7,  0, 0, 0},
    {4, 0, 1,  0, 6, 3,  7, 0, 0}};

  display_board(orig_board);


  int board[9][9] {0};  // Create a working copy of the original board
  copy_board(orig_board, board);

  int cursor[2] {0,0}; // initialize the cursor

  //advance_cursor(orig_board, cursor); // advance the cursor to the first blank space

// diagnostics
  cout << "cursor location: " << cursor[0] << " " << cursor[1] << endl;
  cout << "column check:    " << check_col(board, cursor) << endl;
  cout << "row check:       " << check_row(board, cursor) << endl;
  cout << "square check:    " << check_sqr(board, cursor) << endl;

  int input_val;

  while (true) {

    //cin >> input_val;

    board[cursor[0]][cursor[1]]++;                    display_board(board); cout << "Increment square" << endl;
    if (check_valid_move(board, cursor)){ // a
      if (advance_cursor(orig_board, cursor)) {
        display_board(board); cout << "Cursor advanced to: " << cursor[0] << "," << cursor[1] <<  endl;
        continue;
      } else {
        display_board(board); cout << "Solved!!!" << endl;
        return 0;
      }
    } else {
      while (board[cursor[0]][cursor[1]] == 9){ //b
        board[cursor[0]][cursor[1]] = 0;
        rewind_cursor(orig_board, cursor);       display_board(board); cout << "Zeroed and cursor rewound" << endl;
      }
    }




  }
}
