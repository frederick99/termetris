#include <time.h>
#include "block.c"

#define WIDTH 16
int NEW_BLOCK = 0;

void rotateblock(struct Block* block, int direction){
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
}

void slam_down(int grid[20][16], struct Block *block) {
  // while can go down
  // go down
  while (move_down() != -1);
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

void  step(int grid[20][16], struct Block *block) {
  if (NEW_BLOCK) {
    *block = get_block();
    // initialise params
    NEW_BLOCK = 0;
  } else {
    // has collided?
    int hasCollided = 0;
    int newCoords[4][2];
    getCoords(block, newCoords);
    for (int i = 0; i < 4; i++) {
      if (grid[newCoords[i][0]][newCoords[i][1]]) {
        hasCollided = 1;
        break;
      }
    }
    // if not pull down
    if (!hasCollided) {
      for (int i = 0; i < 4; i++) {
        block->cells[i][1]++;
      }
    } else {
      NEW_BLOCK = 1;
      step(grid, block);
    }
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

int Bmain(int argc, char const *argv[])
{
  srand(time(0));
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
