#include <stdio.h> 
#include <stdlib.h>    

#define N 9
#define UNASSIGNED 0

int initialGrid[N][N];

int is_exist_row(int grid[N][N], int row, int num){
	for (int col = 0; col < 9; col++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_col(int grid[N][N], int col, int num) {
	for (int row = 0; row < 9; row++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_box(int grid[N][N], int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row + startRow][col + startCol] == num) {
				return 1;
			} 
		}
	}
	return 0;
}

int is_safe_num(int grid[N][N], int row, int col, int num) {
	return !is_exist_row(grid, row, num) 
			&& !is_exist_col(grid, col, num) 
			&& !is_exist_box(grid, row - (row % 3), col - (col %3), num);
}

int find_unassigned(int grid[N][N], int *row, int *col) {
	for (*row = 0; *row < N; (*row)++) {
		for (*col = 0; *col < N; (*col)++) {
			if (grid[*row][*col] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int solve(int grid[N][N]) {
	
	int row = 0;
	int col = 0;
	
	if (!find_unassigned(grid, &row, &col)){
		return 1;
	}
	
	for (int num = 1; num <= N; num++ ) {
		
		if (is_safe_num(grid, row, col, num)) {
			grid[row][col] = num;
			
			if (solve(grid)) {
				return 1;
			}
			
			grid[row][col] = UNASSIGNED;
		}
	}
	
	return 0;
} 

void setColor(int color){ 
	/* TODO: Add color on terminal */
}

void print_grid(int grid[N][N]) {
	for (int row = 0; row < N; row++) {
		if( row == 3 || row == 6 ){ printf("____________________\n"); }
		for (int col = 0; col < N; col++) {
			if( col == 3 || col == 6 ){ printf("|"); }  
			if( grid[row][col] == initialGrid[row][col] ){
				/** This Number is a Initial Number print there with another color **/
				/* TODO: change to set color here */  
			} 
			printf("%2d", grid[row][col]);   
		}
		printf("\n");
	}
}

int main() {
	
	int grid[N][N] = {{0,0,0, 0,0,3, 2,9,0},
			 {0,8,6, 5,0,0, 0,0,0},
			 {0,2,0, 0,0,1, 0,0,0},
			 {0,0,3, 7,0,5, 1,0,0},
			 {9,0,0, 0,0,0, 0,0,8},
			 {0,0,2, 9,0,8, 3,0,0},
			 {0,0,0, 4,0,0, 0,8,0},
			 {0,4,7, 1,0,0, 0,0,0}};

	for (int row = 0; row < N; row++) { 
		for (int col = 0; col < N; col++) { 
			initialGrid[row][col] = grid[row][col]; 
		} 
	} 
	
	if (solve(grid)) {
		print_grid(grid);
	} else {
		printf("no solution");
	}
	
	return 0;
}