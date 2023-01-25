#include "ttt.h"

// unused
char *replace_char (char *str, char f, char r) {
	char *pos = strchr(str, f);
	while (pos) {
		*pos = r;
		pos = strchr(pos, f);
	}
	return str;
}

char *board_to_str (char *str, int b, int x) {
	for (int i = 8; i >= 0; i--) {
		if (b & 1<<i) {
			if (!x) {
				str[8 - i] = 'O';
			} else {
				str[8 - i] = 'X';
			}
		} else {
			str[8 - i] = 'n';
		}
	}
	str[9] = '\0';
	return str;
}

char *combine_xo(char *str, char *x, char *o) {
	for (int i = 0; i < 9; i++) {			
		if (x[i] == 'X') {
			str[i] =  'X';
		} else if (o[i] == 'O') {
			str[i] =  'O';;
		} else {
			str[i] = ' ';
		}
	}
	str[9] = '\0';
	return str;
}

char *get_board (char *str, char *xo) { 
	sprintf(str, "%c|%c|%c\n-----\n%c|%c|%c\n-----\n%c|%c|%c\n",
			xo[0], xo[1], xo[2], xo[3], xo[4], xo[5], xo[6], xo[7], xo[8]);
	return str;
}

bool win(int board) {
	int states[] = {
		0b111000000,
		0b000111000,
		0b000000111,
		0b100100100,
		0b010010010,
		0b001001001,
		0b100010001,
		0b001010100};
	for (int i = 0; i < 8; i++)
		if ((board & states[i]) == states[i])
			return true;
	return false;
}

// move #1-9
int turn(int board, int move) {
	return board | (int)pow(2, 9 - move);
	printf("");
}

void print_board(int x_board, int o_board) {
	char str_x_board[10];
	char str_o_board[10];
	char str_xo_board[10];
	char str_board[50];

	board_to_str(str_x_board, x_board, 1);
	board_to_str(str_o_board, o_board, 0);
	combine_xo(str_xo_board, str_x_board, str_o_board);
	printf("%s", get_board(str_board, str_xo_board));
}

// returns evaluation of board (-1,0,1)
// move is set to best move found in bitboard representation
find_move(int board, int x_board, int o_board, char side, int d, int *move, int *count) {
	if (side == 'X' && win(o_board) || side == 'O' && win(x_board)) {
		return -1;
	} else if (board == 511) {
		return 0;
	}

	// value = win/draw/loss (1/0/-1)
	int value;
	int best = -1;
	int temp_board = board;
	int temp_x_board = x_board;
	int temp_o_board = o_board;
	char temp_side = side;

	for (int i = 0; i < 9; i++) {
		// current candidate
		int c = 1<<i;

		// check if candidate is a valid move
		if (!(board & c)) {
			*count = *count + 1;
			// add move to boards
			if (d== 0 && c == 3) {
				d;
			}
			board |= c;
			if (side == 'X') {
				x_board |= c;
				side = 'O';
			} else {
				o_board |= c;
				side = 'X';
			}

			//printf("move:\n");
			//print_board(x_board, o_board);
			value = -find_move(board, x_board, o_board, side, d + 1, move, count);

			// reset boards and sides for this function level
			board = temp_board;
			x_board = temp_x_board;
			o_board = temp_o_board;
			side = temp_side;

			if (value > best) {
				best = value;
			}
			// if winning move found, return immediately
			// if drawing move found, update move and keep searching
			if (d == 0) {
				if (value == 1) {
					*move = c;
					return value;
				} else if (value == 0) {
					*move = c;
				}
			}
		}
	}
	return best;
}

bool game_over(board, x_board, o_board, side) {
	bool over = false;
	system("cls");
	printf("Welcome to Tic Tac Toe.\n\n");
	print_board(x_board, o_board);
	printf("\n");
	if (win(x_board)) {
		if (side == 'X') {
			printf("You win!\n");
		} else {
			printf("Your moves weren't the best.\n");
		}
		over = true;
	} else if (win(o_board)) {
		if (side == 'O') {
			printf("You win!\n");
		} else {
			printf("Your moves weren't the best.\n");
		}
		over = true;
	}
	if (board == 511) {
		printf("Draw.\n");
		over = true;
	}
	return over;
}

void clear(int n) {
	char *str = malloc(sizeof(char) * n * 3 + 1);
	for (int i = 0; i < 3*n; i++) {
		if (i < n || 2*n <= i) {
			str[i] = '\b';
		} else {
			str[i] = ' ';
		}
	}
	printf("%s", str);
	fflush(stdout);
	free(str);
	return;
}

void init_game() {
	int board = 0b000000000;
	int x_board = 0b000000000;
	int o_board = 0b000000000;
	int move;
	int *computer_move = malloc(sizeof(int));
	char side;
	char computer_side;
	int load = 0;
	int *count = malloc(sizeof(int));
	*count = 0;
	char moves [9];

	printf("Welcome to Tic Tac Toe.\n\n");
	print_board(x_board, o_board);
	printf("\n");
	side = 's';
	while (side != 'X' && side != 'O') {
		printf("Would you like to be X or O?\n\n");
		scanf(" %c", &side);
		side = strupr(&side)[0];
	}
	(side == 'X') ? (computer_side = 'O') : (computer_side = 'X');

	while (board != 511) {
		system("cls");
		printf("Welcome to Tic Tac Toe.\n\n");
		print_board(x_board, o_board);
		if (board) {
			printf("\nAfter thinking about it really hard, the computer picked a move!\n", *count);
		}
		
		for (int i = 0; i < 9; i++) {
			if (!(board & 1<<(8 - i))) {
				moves[i] = (i + 1) + '0';
			} else {
				moves[i] = ' ';
			}
		}

		printf("\n%c|%c|%c\n-----\n%c|%c|%c\n-----\n%c|%c|%c\n\nEnter your move position\n\n", 
			moves[0], moves[1], moves[2], moves[3], moves[4], moves[5], moves[6], moves[7], moves[8]);
		
		scanf(" %d", &move);

		if (board & (int)pow(2, 9 - move)) {
			printf("\n");
			for (int i = 0; i < 3; i++) {
				printf("Bad move!");
				fflush(stdout);
				Sleep(250);
				clear(9);
				Sleep(250);
			}
			continue;
		}

		board = turn(board, move);

		if (side == 'X') {
			x_board = turn(x_board, move);
		} else {
			o_board = turn(o_board, move);
		}
		if (game_over(board, x_board, o_board, side)) {
			break;
		}

		system("cls");
		printf("Welcome to Tic Tac Toe.\n\n");
		print_board(x_board, o_board);
		printf("\nNice move!\n\n");
		Sleep(200);
		printf("Computer is thinking |");
		fflush(stdout);
		// loading bar
		for (int i = 0; i < 15; i++) {
			Sleep(150);
			printf("\b \b");
			fflush(stdout);
			switch (load) {
				case 0: printf("/"); break;
				case 1: printf("-"); break;
				case 2: printf("\\"); break;
				case 3: printf("|"); break;
			}
			fflush(stdout);
			if (load++ == 3) {
				load = 0;
			}
		}
		printf("\b \b\n\n");
		*count = 0;
		find_move(board, x_board, o_board, computer_side, 0, computer_move, count);
		board ^= *computer_move;
		if (computer_side == 'X') {
			x_board ^= *computer_move;
		} else {
			o_board ^= *computer_move;
		}

		if (game_over(board, x_board, o_board, side)) {
			break;
		}
	}
	
	
	free(computer_move);
	free(count);
}

int main () {
	char play_again = 'n';

	do {
		system("cls");
		init_game();
		printf("Would you like to play again? y/n\n");
		scanf(" %c", &play_again);
	} while (strlwr(&play_again)[0] == 'y');


	return 0;	
}

// Notes
// char *c is pointer to static array, char c[] is like normal array
// don't use pointer increment in format specifiers- undefined eval order
// use fgets instead of scanf
// + '0' convert int to char

	
	

	// board_to_str(str_x_board, x_board, 1);
	// printf("%s", board_to_str(str_x_board, x_board, 1));
	
	//////////////////
	// find move testing
	/////////
	/*
	x_board = 0b010101100; 
	o_board = 0b101010000;
	board = x_board | o_board;
	print_board(x_board, o_board);
	int *m = malloc (sizeof(int));
	*m = 3;
	find_move(board, x_board, o_board, 'X', 0, m);
	printf("%d\n", *m);
	*/
	/*
	board |= m;
	x_board |= m;
	printf("\n%d\n", m);
	print_board(x_board, o_board);
	
	x_board = 0b010111000;
	o_board = 0b101000111;
	
	board_to_str(str_o_board, o_board, 0);
	board_to_str(str_x_board, x_board, 1);
	printf("%s\n", str_x_board);
	printf("%s\n", str_o_board);
	
	combine_xo(str_xo_board, str_x_board, str_o_board);
	printf("%s\n", str_xo_board);

	get_board(str_board, str_xo_board);
	printf("%s\n", str_board);
	*/
	// print_board(x_board, o_board);