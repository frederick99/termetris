#include <ncurses.h>
#include <time.h>
#include "block.c"

#define WIDTH 16

void rotateblock(struct Block* block,int direction){
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
}

int main(int argc, char const *argv[])
{
  // initscr();
  // printw("Hello, world!");
  // refresh();
  // getch();
  // endwin();
  int grid[20][16] ={0} ;
  int count = 1;
  while(count) {
    struct Block cur_block = get_block();
    display_coods(&cur_block);
    int starting_x = rand()%(WIDTH - max_x_cood(&cur_block)) + -1*min_x_cood(&cur_block) ;
    cur_block.x = starting_x;
    count--;

  }


  return 0;
}
