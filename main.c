#include <wchar.h>
#include <locale.h>
#include <time.h>

#include "game.c"

int startx, starty, width, height, scaling;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

void fill(int x, int y, WINDOW *win) {
	x *= 2*scaling;
	y *= scaling;
	for(int i=0; i < 2*scaling; i+=2)
		for(int j=0; j < scaling; j++)
			mvwprintw(win, y+j+1, x+i+1, "\u2588\u2588");
}

void drawGrid(int grid[20][16], WINDOW *win) {
	wclear(win);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 16; j++)
			if (grid[i][j])
				fill(j, i, win);
	box(win, 0,0);
	wrefresh(win);
}

int main(int argc, char *argv[])
{
	WINDOW *my_win;
	int ch;
	setlocale(LC_ALL, "");
	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on*
						 * everty thing to me 		*/
	noecho();
	keypad(stdscr,TRUE);/* I need that nifty F1 	*/
	halfdelay(1);

	// int timestep = 0.5;
	scaling = LINES / 20;
	height = 20 * scaling;
	width = 32 * scaling;
	starty = (LINES - height - 2) / 2;	/* Calculating for a center placement */
	startx = (COLS - width - 2) / 2;	/* of the window		*/
	my_win = create_newwin(height+2, width+2, starty, startx);
	mvprintw(LINES-1, 0, "Press Q to exit");
	refresh();

	srand(time(0));
  int grid[20][16];
	for(int i=0;i<20;i++){
    for(int j=0;j<16;j++){
      grid[i][j] = 0;
    }
  }
  NEW_BLOCK = 1;
	struct Block _block = {0};
	struct Block *block = &_block;
	incr_and_print(0);
	step(grid, block);

	int t0 = time(0);
	// int x = 0, y = 0;
	drawGrid(grid, my_win);
	// fill(x,y,my_win);
	// wrefresh(my_win);
	while((ch = getch()) != 'q') {
		int doRefresh = 1;
		switch(ch) {
			case KEY_LEFT: if (USER_CAN_INTERACT) move_lr(grid, block, -1); break;
			case KEY_RIGHT: if (USER_CAN_INTERACT) move_lr(grid, block, 1); break;
			case KEY_UP:
				if (USER_CAN_INTERACT) {
					remove_from_grid(grid, block);
					rotateblock(block, -1, grid);
					insert_in_grid(grid, block);
				}
				break;
			case KEY_DOWN: if (USER_CAN_INTERACT) slam_down(grid, block); break;
			case ERR: {
				int t = time(0);
				int dt = t - t0;
				if (dt < 1) {
					// pass;
					doRefresh = 0;
				} else {
					t0++;
					// if (y<19) y++;
					step(grid, block);
		// for(int i=0;i<16;i++)printw("%d", grid[0][i]);
					// printw("stepping");
				}
			}
		}
		if (doRefresh) {
			// wclear(my_win);
			// fill(x,y,my_win);
			// box(my_win, 0, 0);
			// wrefresh(my_win);
			drawGrid(grid, my_win);
		}
	}
		
	endwin();			/* End curses mode		  */
	return 0;
}


WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 			 * for the vertical and horizontal
					 			 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}
