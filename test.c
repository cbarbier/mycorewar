#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <ncurses.h>

static int	print_arr(WINDOW *win, uint8_t *arr)
{
	int i;
	int j;

	j = 0;
	init_pair(1, COLOR_RED, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			mvwprintw(win, j + 1, 3 * i + 1, "%.2x%c", arr[j * 4 + i], (i < 3 ? ' ': '\n'));
			i++;
		}
		j++;
	}
	return (1);
}
	
int	main(void)
{
	uint8_t arr[16];
	WINDOW	*win;

	initscr();
	noecho();
	start_color();
	win = newwin(6, 13, 3, 5);
	attron(A_BLINK);
	printw("Hello World\n");
	attroff(A_BLINK);
	printw("this term's got %d lines and %d columns\n", LINES, COLS);
	arr[2] = 16;
	arr[8] = 128;
	arr[10] = 255;
	print_arr(win, arr);
	attron(COLOR_PAIR(1));
	printw("TESt");
	box(win, 0, 0);
	mvchgat(0, 0, 1, A_BOLD, 0, 0);
	mvchgat(0, 1, 2, A_BOLD, 2, 0);
	mvchgat(0, 3, 1, A_NORMAL, 2, 0);
	mvchgat(0, 3, 1, A_NORMAL, 0, 0);
	curs_set(0);
	refresh();
	wrefresh(win);
	while (getch() != ' ');
	endwin();
	return (0);
}
