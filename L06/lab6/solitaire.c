#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printBoard(const int board[7][7]); 

int parseMove(char *input, int *x1, int *y1, int *x2, int *y2);
int isValidMove(const int board[7][7], char *input);
void effectMove(int board[7][7], char *input);
int isWon(const int board[7][7]);


// BEGIN SOLUTION
// Note: This solution does not contain a solution to the bonus question. 
int parseMove(char *input, int *x1, int *y1, int *x2, int *y2) {
	char c = input[0];
	// x1
	if (c >= 0x61 && c <= 0x63) { 
		*x1 = 0;
	} else if (c >= 0x64 && c <= 0x66) {
		*x1 = 1;
	} else if (c >= 0x67 && c <= 0x6D) {
		*x1 = 2;
	} else if ((c >= 0x6E && c <= 0x70) || (c == 0x78) || (c <= 0x50 && c >= 0x4E)) {
		*x1 = 3;
	} else if (c >= 0x47 && c <= 0x4D) {
		*x1 = 4;
	} else if (c >= 0x44 && c <= 0x46) {
		*x1 = 5;
	} else if (c >= 0x41 && c <= 0x43) {
		*x1 = 6;
	} else {
		return -1;
	}
	if (c == 'g' || c == 'n' || c == 'M') {
		*y1 = 0;
	} else if (c == 'h' || c == 'o' || c == 'L') {
		*y1 = 1;
	} else if (c == 'a' || c == 'd' || c == 'i' || c == 'p' || c == 'K' || c == 'F' || c == 'C') {
		*y1 = 2;
	} else if (c == 'b' || c == 'e' || c == 'j' || c == 'x' || c == 'J' || c == 'E' || c == 'B') {
		*y1 = 3;
	} else if (c == 'c' || c == 'f' || c == 'k' || c == 'P' || c == 'I' || c == 'D' || c == 'A') {
		*y1 = 4;
	} else if (c == 'l' || c == 'O' || c == 'H') {
		*y1 = 5;
	} else if (c == 'm' || c == 'N' || c == 'G') {
		*y1 = 6;
	} else {
		return -1;
	}
	
	// x2
	c = input[1];
	if (c >= 0x61 && c <= 0x63) { 
		*x2 = 0;
	} else if (c >= 0x64 && c <= 0x66) {
		*x2 = 1;
	} else if (c >= 0x67 && c <= 0x6D) {
		*x2 = 2;
	} else if ((c >= 0x6E && c <= 0x70) || (c == 0x78) || (c <= 0x50 && c >= 0x4E)) {
		*x2 = 3;
	} else if (c >= 0x47 && c <= 0x4D) {
		*x2 = 4;
	} else if (c >= 0x44 && c <= 0x46) {
		*x2 = 5;
	} else if (c >= 0x41 && c <= 0x43) {
		*x2 = 6;
	} else {
		return -1;
	}
	if (c == 'g' || c == 'n' || c == 'M') {
		*y2 = 0;
	} else if (c == 'h' || c == 'o' || c == 'L') {
		*y2 = 1;
	} else if (c == 'a' || c == 'd' || c == 'i' || c == 'p' || c == 'K' || c == 'F' || c == 'C') {
		*y2 = 2;
	} else if (c == 'b' || c == 'e' || c == 'j' || c == 'x' || c == 'J' || c == 'E' || c == 'B') {
		*y2 = 3;
	} else if (c == 'c' || c == 'f' || c == 'k' || c == 'P' || c == 'I' || c == 'D' || c == 'A') {
		*y2 = 4;
	} else if (c == 'l' || c == 'O' || c == 'H') {
		*y2 = 5;
	} else if (c == 'm' || c == 'N' || c == 'G') {
		*y2 = 6;
	} else {
		return -1;
	}
	return 0;
}

int isValidMove(const int board[7][7], char *input) {
	int x1, y1, x2, y2;
	if (parseMove(input, &x1, &y1, &x2, &y2) == -1) {
		return 0;
	} 
	// is the new space exactly two spaces away orthogonally?
//	printf("dx = %d, dy = %d", abs(x1 - x2), abs(y1 - y2));
	if (!((abs(x1 - x2) == 2 && abs(y1-y2) == 0) || (abs(x1 - x2) == 0 && abs(y1-y2) == 2))) {
		//printf("New Space isn't two spaces away!\n");
		return 0;
	} 
	// is the new space unoccupied?
	if (board[x2][y2] != 0) {
		//printf("New Space is Occupied!\n");
		return 0;
	} 
	// are we jumping a peg? 
	if (board[(x1+x2)>>1][(y1+y2)>>1] != 1) {
		//printf("Jumpable Peg Present!\n");
		return 0;
	}
	// Does the peg we're moving exist? 
	if (board[x1][y1] != 1) {
		//printf("Attempting to move piece that doesn't exist!");
		return 0;
	}
	return 1;
}

void effectMove(int board[7][7], char *input) {
	int x1, y1, x2, y2;
	if (parseMove(input, &x1, &y1, &x2, &y2) == -1) {
		return;
	} 
	board[x1][y1] = 0;
	board[(x1+x2)>>1][(y1+y2)>>1] = 0;
	board[x2][y2] = 1;
}



int isWon(const int board[7][7]) {
	int lostflag = 1;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (board[i][j] == 1 && i != 3 && j != 3) {
				lostflag = 0;
			}
		}
	}
    return lostflag;
}

// END SOLUTION

int main () {

	char buffer[50];
	int board[7][7] = {	{2, 2, 1, 1, 1, 2, 2}
					  , {2, 2, 1, 1, 1, 2, 2}
					  , {1, 1, 1, 1, 1, 1, 1}
					  , {1, 1, 1, 0, 1, 1, 1}
					  , {1, 1, 1, 1, 1, 1, 1}
					  , {2, 2, 1, 1, 1, 2, 2}
					  , {2, 2, 1, 1, 1, 2, 2}
					  };

// */ // Winning board 
/*					{	{2, 2, 0, 0, 0, 2, 2}
					  , {2, 2, 0, 0, 0, 2, 2}
					  , {0, 0, 0, 0, 0, 0, 0}
					  , {0, 0, 0, 1, 0, 0, 0}
					  , {0, 0, 0, 0, 0, 0, 0}
					  , {2, 2, 0, 0, 0, 2, 2}
					  , {2, 2, 0, 0, 0, 2, 2}
					  }; // */


	printf("><><><><><><><><><><><><\n");
	printf("  Welcome to Solitaire!\n");
	printf("><><><><><><><><><><><><\n");
	printf("Enter your moves by typing the character corresponding\nto the piece you wish to move, then typing the character\nof the place you wish to move it to.\nEnter 'q' to quit at any time.\n\n");
	int won = isWon(board);
	printf("won = %d\n", won);
	while (won != 1 && won != -1) {
		printBoard(board);
		printf("S >> ");
		scanf("%s", buffer);
		if (strcmp(buffer, "q") == 0) {
			break;
		}
		if (isValidMove(board, buffer)) {
			effectMove(board, buffer);
		} else {
			printf("Move Invalid\n");
		}
		won = isWon(board);
	}
	if (won == 1) {
		printf("A winner is you!\n");
	} else if (won == -1) {
		printf("Ya Done Son! No Moves Remaining!\n");
	} else {
		printf("Game Over, Yeah!\n");
	}
	printf("Solitaire Terminated!\n");
}

// THIS IS A GIFT: Don't touch until December 25th
void printBoard(const int board[7][7]){ 
	char temp[5];
	char buf[150]; 
	char moveKey[15][100]  =
{ "    ╔═╤═╤═╗     │     ╔═╤═╤═╗    "
, " ☻  ║a│b│c║  ☻  │     ║"
, "    ╟─┼─┼─╢     │     ╟─┼─┼─╢    "
, "    ║d│e│f║     │     ║"
, "╔═╤═╃─┼─┼─╄═╤═╗ │ ╔═╤═╃─┼─┼─╄═╤═╗"
, "║g│h│i│j│k│l│m║ │ ║"
, "╟─┼─┼─┼─┼─┼─┼─╢ │ ╟─┼─┼─┼─┼─┼─┼─╢"
, "║n│o│p│x│P│O│N║ │ ║"
, "╟─┼─┼─┼─┼─┼─┼─╢ │ ╟─┼─┼─┼─┼─┼─┼─╢"
, "║M│L│K│J│I│H│G║ │ ║"
, "╚═╧═╅─┼─┼─╆═╧═╝ │ ╚═╧═╅─┼─┼─╆═╧═╝"
, "    ║F│E│D║     │     ║"
, "    ╟─┼─┼─╢     │     ╟─┼─┼─╢"
, " ☻  ║C│B│A║  ☻  │     ║"
, "    ╚═╧═╧═╝     │     ╚═╧═╧═╝"
};
	for (int i = 0; i < 15; i++) {
		strcpy(buf, moveKey[i]);
		if (i == 1 || i == 3 || i == 11 || i == 13) {
			for (int j = 2; j <= 4; j++) {
				if (board[i>>1][j] == 1) {
					strcpy(temp,"●");
				} else {
					strcpy(temp," ");
				}
				strcat(buf, temp);
				if (j < 4) {
					strcat(buf, "│");
				} else {
					strcat(buf, "║");
				}
			}
		} else if (i == 5 || i == 7 || i == 9) {
			for (int j = 0; j < 7; j++) {
				if (board[i>>1][j] == 1) {
					strcpy(temp,"●");
				} else {
					strcpy(temp," ");
				}
				strcat(buf, temp);
				if (j < 6) {
					strcat(buf, "│");
				} else {
					strcat(buf, "║");
				}
			}
		}
		printf("%s\n", buf);
	}
}
