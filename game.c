#include <ncurses.h>
#include <time.h>
#include "block.c"

#define WIDTH 16
int NEW_BLOCK = 0;

int collides(int grid[20][16],struct Block* block){
  //returns 1 if collision otherwise 0
  int hasCollided = 0;
  int newCoords[4][2];
  getCoords(block, newCoords);
  for (int i = 0; i < 4; i++) {
    if (grid[newCoords[i][0]][newCoords[i][1]]) {
      hasCollided = 1;
      break;
    }
  }
  return hasCollided;
}

void rotateblock(struct Block* block, int direction,int grid[20][16]){
  if(direction==1){
    for(int i=0;i<4;i++){
      int temp  = block->cells[i][0];
      block->cells[i][0] = block->cells[i][1];
      block->cells[i][1] = -1*temp;
    }
  }
  else if(direction==-1){
    for(int i=0;i<4;i++){
      int temp  = block->cells[i][0];
      block->cells[i][0] = -1*block->cells[i][1];
      block->cells[i][1] = temp;
    }
  }
  int hasCollided = collides(grid,block);
  if(hasCollided){
    rotateblock(block,direction*-1,grid);
    return -1;
  }
  return 0;
}

int move_lr(int grid[20][16],struct Block* block,int direction){
  //dir=-1 for left and 1 for right
  block->x  += direction;
  int hasCollided = collides(grid,block);
  if(hasCollided){
    block->x  += -1*direction;
    return -1;
    }
  return 0;
}

void insert_in_grid(int grid[20][16],struct Block* block){
  for(int i=0;i<4;i++){
    grid[block->cells[i][1] +block->y][block->cells[i][0] +block->x] = 1;
  }
}

void remove_from_grid(int grid[20][16],struct Block* block){
  for(int i=0;i<4;i++){
    grid[block->cells[i][1] +block->y][block->cells[i][0] +block->x] = 0;
  }
}

int move_down(int grid[20][16],struct Block* block){  
  block->y  += 1;
  int hasCollided = collides(grid,block);
  if(hasCollided){
    block->y  += -1;
    return -1;
    }
  return 0;
}

void  step(int grid[20][16], struct Block *block) {
  if (NEW_BLOCK) {
    *block = get_block();
    // initialise params
    NEW_BLOCK = 0;
  }
   else if (move_down(grid,block)==-1) {
      NEW_BLOCK = 1;
      step(grid, block);
  }
}

void print_grid(int grid[20][16]){
  for(int i=0;i<20;i++){
    for(int j=0;j<16;j++){
      printf("%d ",grid[i][j]);
    }
      printf("\n");
  }
}

int main(int argc, char const *argv[])
{  srand(time(0));
  int grid[20][16] ;
  for(int i=0;i<20;i++){
    for(int j=0;j<16;j++){
    grid[i][j] = 0;
  }
}
  int count = 1;
  NEW_BLOCK = 1;
  while(count) {
    struct Block cur_block = get_block();
    display_coods(&cur_block);
    int starting_x = rand()%(WIDTH - max_x_cood(&cur_block)) + -1*min_x_cood(&cur_block) ;
    cur_block.x = starting_x;
    cur_block.y = 2;
    count--;
    insert_in_grid(grid,&cur_block);
    print_grid(grid);
  }


  return 0;
}
