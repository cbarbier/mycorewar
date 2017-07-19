#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <ncurses.h>

static int	print_arr(WINDOW *warr, uint8_t *arr)
{
	int i;
	int j;

	j = 0;
	init_pair(1, COLOR_RED, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_YELLOW);
	while (j < 64)
	{
		i = 0;
		while (i < 64)
		{
			mvwprintw(warr, j + 1, 3 * i + 1, "%.2x", arr[j * 4 + i]);
			i++;
		}
		j++;
	}
	return (1);
}
static int	put_pc(WINDOW *warr, int add)
{
	int i;
	int j;

	j = add / 64;
	i = add % 64;
	mvwchgat(warr, j + 1, 3 * i + 1, 2, A_NORMAL, 1, 0);
	return (1);
}
	
int	main(void)
{
	uint8_t arr[4096];
	int		add = 0x800;
	WINDOW	*warr;
	WINDOW	*win;
	WINDOW	*winfo;

	initscr();
	noecho();
	start_color();
	init_color(COLOR_YELLOW, 420, 420, 420);
	assume_default_colors(COLOR_YELLOW, COLOR_BLACK);
	win = newwin(68, 260, 0, 0);
	warr = newwin(66, 190, 1, 2);
	winfo = newwin(68, 67, 0, 193);
	wattron(win, COLOR_PAIR(3));
	wattron(winfo, COLOR_PAIR(3));
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); 
	wborder(winfo, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); 
	printw("Hello World\n");
	attroff(A_BLINK);
	printw("this term's got %d lines and %d columns\n", LINES, COLS);
	arr[2] = 16;
	arr[8] = 128;
	arr[10] = 255;
	print_arr(warr, arr);
	attron(COLOR_PAIR(1));
	wattron(warr, COLOR_PAIR(1));
	printw("TESt");
	wprintw(winfo, "window winfo test");
//	box(warr, 0, 0);
	mvchgat(0, 0, 1, A_BOLD, 0, 0);
	mvchgat(0, 1, 2, A_BOLD, 2, 0);
	mvchgat(0, 3, 1, A_NORMAL, 2, 0);
	mvchgat(0, 3, 1, A_NORMAL, 0, 0);
	curs_set(0);
	refresh();
	wrefresh(win);
	put_pc(warr, add);
	wrefresh(warr);
	wrefresh(winfo);
	printf("test");
	usleep(1000000);
	put_pc(warr, 0x400);
	wrefresh(warr);
	while (getch() != ' ');
	endwin();
	return (0);
}
