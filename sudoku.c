#include <stdio.h>
#include <stdbool.h>

#define SIZE_GRID 9

/* list solutions for the line */
void check_row_solution(int grid[SIZE_GRID][SIZE_GRID], int possible_solutions[SIZE_GRID], int r) {
  for (int i = 0; i < SIZE_GRID; i++)
    if (grid[r][i])
      possible_solutions[grid[r][i] - 1] = 0;
}


/* list solutions for the columns */
void check_col_solution(int grid[SIZE_GRID][SIZE_GRID], int possible_solutions[SIZE_GRID], int c) {
  for (int i = 0; i < SIZE_GRID; i++)
    if (grid[i][c])
      possible_solutions[grid[i][c] - 1] = 0;
}

/* list solutions for the 3x3 grid */
void check_box_solution (int grid [SIZE_GRID][SIZE_GRID], int possible_solutions[SIZE_GRID], int r, int c) {
  int r_block = (r / 3)*3;
  int c_block = (c / 3)*3;
  for(int i = r_block; i < r_block + 3; i++)
    for(int j = c_block; j < c_block + 3; j++)
      if (grid[i][j])
        possible_solutions[grid[i][j] - 1] = 0;
}

/* list choice */
void list_choice(int grid[SIZE_GRID][SIZE_GRID], int possible_solutions[SIZE_GRID], int r, int c) { 
  check_row_solution(grid, possible_solutions, r);
  check_col_solution(grid, possible_solutions, c);
  check_box_solution(grid, possible_solutions, r, c);
}

/* make choice */
int make_choice(int possible_solutions[SIZE_GRID]) {
  // choose a random possible solution
  for (int i = 0; i < SIZE_GRID; i++)
    if (possible_solutions[i])
      return possible_solutions[i];
  return 0;
}

/* backtracking */
bool backtracking (int grid[SIZE_GRID][SIZE_GRID]) {
  
  int r_choice = -1;
  int c_choice = -1;
  for (int i = 0; i < SIZE_GRID; i++)
    for (int j = 0; j < SIZE_GRID; j++)
      if (!grid[i][j]) {
        r_choice = i;
        c_choice = j;
        break;
      }

  if (r_choice == -1 && c_choice == -1)
    return true;

  /* tant qu'il y a des choix */
  int possible_solutions[SIZE_GRID] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  list_choice(grid, possible_solutions, r_choice, c_choice);
  int choice = make_choice(possible_solutions);

  while (choice) {

    grid[r_choice][c_choice] = choice;
    bool result = backtracking(grid); /* call backtracking */

    if (result)
      return true;

    possible_solutions[choice - 1] = 0; /* remove choice from possible solutions */
    choice = make_choice(possible_solutions);
  }
  
  grid[r_choice][c_choice] = 0;
  return false;
}

// we want to create a sudoku solver
int main(int argc, char ** argv) {
  int sudoku_grid[SIZE_GRID][SIZE_GRID] = {
    {0, 0, 3, 0, 2, 0, 6, 0, 0},
    {9, 0, 0, 3, 0, 5, 0, 0, 1},
    {0, 0, 1, 8, 0, 6, 4, 0, 0},
    {0, 0, 8, 1, 0, 2, 9, 0, 0},
    {7, 0, 0, 0, 0, 0, 0, 0, 8},
    {0, 0, 6, 7, 0, 8, 2, 0, 0},
    {0, 0, 2, 6, 0, 9, 5, 0, 0},
    {8, 0, 0, 2, 0, 3, 0, 0, 9},
  };

  bool result = backtracking(sudoku_grid);
  if (result) {
    printf("Sudoku solved!\n");
    for (int i = 0; i < SIZE_GRID; i++) {
      for (int j = 0; j < SIZE_GRID; j++)
        printf("%d ", sudoku_grid[i][j]);
      printf("\n");
    }
  }
  return 0;
}