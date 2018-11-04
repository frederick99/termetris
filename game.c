#include <ncurses.h>
#include "block.c"

#define WIDTH 16
int NEW_BLOCK = 0, REMOVE_ROWS = 0;
int USER_CAN_INTERACT = 1;
int score = 0;

void insert_in_grid(int grid[20][16],struct Block* block){
  for(int i=0;i<4;i++){
    int y = block->cells[i][1] +block->y;
    int x = block->cells[i][0] +block->x;
    if (x>=0 && x <16 && y>=0 && y<20)
      grid[y][x] = 1;
  }
}

void remove_from_grid(int grid[20][16],struct Block* block){
  for(int i=0;i<4;i++){
    int y = block->cells[i][1] +block->y;
    int x = block->cells[i][0] +block->x;
    if (x>=0 && x <16 && y>=0 && y<20)
      grid[y][x] = 0;
  }
}

int collides(int grid[20][16],struct Block* block){
  //returns 1 if collision otherwise 0
  int hasCollided = 0;
  int newCoords[4][2];
  getCoords(block, newCoords);
  for (int i = 0; i < 4; i++) {
    int x = newCoords[i][0];
    int y = newCoords[i][1];
    if (x<0 || x>15 || y>19 || y>=0 && grid[y][x]) {
      hasCollided = 1;
      break;
    }
  }
  return hasCollided;
}

int rotateblock(struct Block* block, int direction, int grid[20][16]) {
  
  if(direction==1){
    for(int i=0;i<4;i++) {
      int temp  = block->cells[i][0];
      block->cells[i][0] = block->cells[i][1];
      block->cells[i][1] = -1*temp;
    }
  }
  else if(direction==-1) {
    for(int i=0;i<4;i++) {
      int temp  = block->cells[i][0];
      block->cells[i][0] = -1*block->cells[i][1];
      block->cells[i][1] = temp;
    }
  }
  int hasCollided = collides(grid,block);
  if(hasCollided){
    rotateblock(block,direction*-1, grid);
    return -1;
  }
  return 0;
}

int move_lr(int grid[20][16],struct Block* block,int direction){
  //dir=-1 for left and 1 for right
  remove_from_grid(grid, block);
  block->x  += direction;
  int hasCollided = collides(grid,block);
  if(hasCollided){
    block->x  += -1*direction;
    insert_in_grid(grid, block);
    return -1;
  }
  insert_in_grid(grid, block);
  return 0;
}

int move_down(int grid[20][16],struct Block* block){  
  remove_from_grid(grid, block);
  block->y  += 1;
  int hasCollided = collides(grid,block);
  if(hasCollided){
    block->y  += -1;
    insert_in_grid(grid, block);
    return -1;
  }
  insert_in_grid(grid, block);
  return 0;
}

void incr_and_print(int v) {
  score += v;
  mvprintw(0,0, "Score: %d", score);
  refresh();
}

void slam_down(int grid[20][16], struct Block *block) {
  // while can go down
  // go down
  while (move_down(grid, block) != -1);
  REMOVE_ROWS = 1;
  USER_CAN_INTERACT = 0;
  incr_and_print(10);
}

void  step(int grid[20][16], struct Block *block) {
  if (NEW_BLOCK) {
    NEW_BLOCK = 0;
    get_block(block);
    int starting_x = rand() % (WIDTH - 2*max_x_cood(block)) + max_x_cood(block) ;
    block->x = starting_x;
    block->y = 0;
    // initialise params
    insert_in_grid(grid, block);
    USER_CAN_INTERACT = 1;
  } else if (REMOVE_ROWS) {
    REMOVE_ROWS = 0;
    NEW_BLOCK = 1;
    // write code
    for (int i = min_y_cood(block) + block->y; i <= max_y_cood(block) + block->y; i++) {
      int isFull = 1;
      for (int j = 0; j < WIDTH; j++) {
        if (grid[i][j] == 0) {
          isFull = 0;
          break;
        }
      }
      if (isFull) {
        incr_and_print(100);
        for (int k = i; k > 0; k--)
          for (int l = 0; l < WIDTH; l++)
            grid[k][l] = grid[k - 1][l];
        for (int l = 0; l < WIDTH; l++) grid[0][l] = 0;
      }
    }
  } else if (move_down(grid,block)==-1) {
    // remove filled rows
    REMOVE_ROWS = 1;
    USER_CAN_INTERACT = 0;
    incr_and_print(10);
  }
}

void print_grid(int grid[20][16]){
  for(int i=0;i<20;i++){
    for(int j=0;j<16;j++){
      printf("%d",grid[i][j]);
    }
      printf("\n");
  }
}

void print_block(struct Block *block) {
  int coords[4][2];
  getCoords(block, coords);
  for (int i = 0; i < 4; i++)
    printf("(%d, %d), ", coords[i][0], coords[i][1]);
  printf("\n");
}

int amain(int argc, char const *argv[])
{
  srand(time(0));
  int grid[20][16] ;
  for(int i=0;i<20;i++){
    for(int j=0;j<16;j++){
      grid[i][j] = 0;
    }
  }
  char c;
  int count = 10;
  NEW_BLOCK = 1;
  struct Block block = {0};
  while(c!='q') {
    step(grid, &block);
    // insert_in_grid(grid, &block);
    print_grid(grid);
    print_block(&block);
    scanf("%c", &c);
  }


  return 0;
}
