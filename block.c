#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int kinds[][4][2] = {
  {{-1,0}, {0,0}, {1,0}, {2,0}},  // oooo
  {{-1,0}, {0,0}, {1,0}, {0,1}},  // o8o
  {{0,0}, {1,0}, {0,1}, {1,1}},   // 88
  {{0,0}, {0,1}, {1,0}, {2,0}},   // 8oo
  {{-2,0}, {-1,0}, {0,0}, {0,1}}, // oo8
  {{-1,0}, {0,0}, {0,1}, {1,1}},  // o8º
  {{-1,1}, {0,1}, {0,0}, {1,0}},  // º8o
};


struct Block {
  int type;
  int x,y;
  int orientation;
  int cells[4][2];
};

void display_coods(struct Block* block){
  for(int i=0;i<4;i++){
    printf("%d,%d\n",block->cells[i][0],block->cells[i][1]);
    }
    printf("-----\n");
}

void getcood(struct Block* block){
  if(block->orientation==1){
    for(int i=0;i<4;i++){
      int temp  = block->cells[i][0];
      block->cells[i][0] = block->cells[i][1];
      block->cells[i][1] = -1*temp;
    }
  }
  else if(block->orientation==3){
    for(int i=0;i<4;i++){
      int temp  = block->cells[i][0];
      block->cells[i][0] = -1*block->cells[i][1];
      block->cells[i][1] = temp;
    }
  }
  if(block->orientation==2){
    for(int i=0;i<4;i++){
      block->cells[i][0] = -1*block->cells[i][0];
      block->cells[i][1] *=-1;
    }
  }
}

void getCoords(struct Block *block, int res[4][2]) {
  for (int i = 0; i < 4; i++) {
    res[i][0] = block->cells[i][0] + block->x;
    res[i][1] = block->cells[i][1] + block->y;
  }
}

struct Block get_block() {
  int k = rand() % 7;
  struct Block block = {0};
  block.type = k;
  block.y = 0;
  //block.cells = kinds[i];
  for(int i=0;i<4;i++){
    block.cells[i][0] = kinds[k][i][0];
    block.cells[i][1] = kinds[k][i][1];
  }
  block.orientation = rand() % 4;
  getcood(&block);
  return block;
}



int min_x_cood(struct Block* block){
  int temp  = 1000;
    for(int i=0;i<4;i++){
      if(temp>block->cells[i][0])
        temp = block->cells[i][0];
    }
    return temp;
}

int max_x_cood(struct Block* block){
  int temp  = -1000;
    for(int i=0;i<4;i++){
      if(temp<block->cells[i][0])
        temp = block->cells[i][0];
    }
    return temp;
}

void Dmain() {
  struct Block b = get_block();
  printf("%d %d\n", b.type, b.orientation);
  for (int i = 0; i < 4; i++)
    printf("%d %d\n", b.cells[i][0], b.cells[i][1]);
};