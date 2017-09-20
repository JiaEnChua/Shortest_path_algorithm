#include "river.h"
#define left 1
#define right 2
#define up 3
#define down 4

static int find_shortest_path(int** mat, int row, int size, int* arr_board, int idx, int* queue_arr);
static int** build_mat(int** map, int row, int size, int* arr, int* idx);
static void destroy(int** temp, int row);
static void connect(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear);
static void search(int** mat, int curr, int* x, int* y, int row, int size);
int get_w_horizontal(int** mat, int x, int y, int row, int size);
int get_w_vertical(int** mat, int x, int y, int size);
int get_min_neighbor(int** mat, int x, int y, int direction, int row, int size);
static void color(int* num);
static void enqueue(int num, int* queue_arr, int *rear);
int dequeue(int* queue_arr, int* front);
static void print_mat(int**mat, int row, int size);
static void checkup(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear);
static void checkright(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear);
static void checkleft(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear);
static void checkdown(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear);
static void clear_color(int** mat, int row, int size, int* arr, int idx);
static void get_path(int** mat, int row, int size, int*rtn);

static void print_mat(int**mat, int row, int size) {
	for(int i = 0; i < (row); i++) {
		for(int j = 0; j < (size); j++) {
			printf("%d ",mat[i][j]); 
		}
		printf("\n");
	}
	printf("\n");
}

static void get_path(int** mat, int row, int size, int*rtn) 
{
	for(int i = 0; i < row; i++) {
		if(mat[i][size-1] < *rtn && mat[i][size-1] >= 0) {
			if(mat[i][size-1] == 9999)
				*rtn = mat[i-1][size-2];
			else
				*rtn = mat[i][size-1];
		}
	}
}

static void clear_color(int** mat, int row, int size, int* arr, int idx)
{
	int j1 = 0;
	int i1 = 0;
	for(int i = 0; i < row; i++) {
		if(i % 2 == 0) {
			for(int j = 0; j < size; j++) {
				if(j % 2 == 0 && mat[i][j] < 0) {
					mat[i][j] *= -1;
				}
			}
		}
	}
	int num = 0;
	int num2 = 0;
	for(int i = 0; i < idx; i++) {
		num = arr[i];
		i++;
		num2 = arr[i];
		mat[num][num2] = 9999;
	}
}

static void search(int** mat, int curr, int* x, int* y, int row, int size)
{
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < size; j++) {
			if(curr == (mat[i][j] *-1)) {
				*x = i;
				*y = j;
				return;
			}
		}
	}
}

static void checkup(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear)
{
	if(x-2 >= 0) {		 //checkup
		int min_edge = get_min_neighbor(mat, x, y, up, row, size); 
		if((mat[x-2][y] >= 0)|| (min_edge + 1 < mat[x-1][y])) { 
			if(mat[x-2][y] >= 0) {
				enqueue(mat[x-2][y], queue_arr, rear);
				color(&mat[x-2][y]);
			}
			if(min_edge == 1000) 
				min_edge = 0;
			if(min_edge < mat[x-1][y]) {
				if(mat[x-1][y] == 9999) {
					if(y == 0)
						mat[x-1][y] = 0;
					else if(x+1 < row && mat[x+1][y] < min_edge)
						mat[x-1][y] = mat[x+1][y];
					else
						mat[x-1][y] = min_edge;
				}
				else
					mat[x-1][y] = min_edge + 1;
			}
		}
	}
}

static void checkdown(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear)
{
	if(x+2 < (row)) {  //checkdown
		int min_edge = get_min_neighbor(mat, x, y, down, row, size); 
		if((mat[x+2][y] >= 0)|| (min_edge + 1 < mat[x+1][y])) { 
			if(mat[x+2][y] >= 0) {
				enqueue(mat[x+2][y], queue_arr, rear);
				color(&mat[x+2][y]);
			}
			if(min_edge == 1000) 
				min_edge = 0;
			if(min_edge < mat[x+1][y]) {
				if(mat[x+1][y] == 9999) {
					if(y == 0)
						mat[x+1][y] = 0;
					else if(x-1 >= 0 && mat[x-1][y] < min_edge)
						mat[x+1][y] = mat[x-1][y];
					else
						mat[x+1][y] = min_edge;
				}
				else
					mat[x+1][y] = min_edge + 1;
			}
		}
	}
}

static void checkleft(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear)
{
	if(y-2 >= 0) {		//checkleft
		int min_edge = get_min_neighbor(mat, x, y, right, row, size); 
		if((mat[x][y-2] >= 0) || (min_edge + 1 < mat[x][y-1])) { 
			if(mat[x][y-2] >= 0) {
				enqueue(mat[x][y-2], queue_arr, rear);
				color(&mat[x][y-2]);
			}
			if(min_edge == 1000) 	min_edge = 0;
			if(min_edge < mat[x][y-1])		mat[x][y-1] = min_edge + 1;
		}
	}

}

static void checkright(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear)
{
	if(y+2 < (size)) {		//checkright 
		int min_edge = get_min_neighbor(mat, x, y, right, row, size); 
		if((mat[x][y+2] >= 0) || (min_edge + 1 < mat[x][y+1])) { 
			if(mat[x][y+2] >= 0) {
				enqueue(mat[x][y+2], queue_arr, rear);
				color(&mat[x][y+2]);
			}
			if(min_edge == 1000) 
				min_edge = 0;
			if(min_edge < mat[x][y+1]) {
				mat[x][y+1] = min_edge + 1;
			}
		}
	}

}

static void connect(int** mat, int x, int y, int size, int row, int* queue_arr, int *rear)
{
	if(y == 0 && x != 0) {
		checkright(mat, x, y, size, row, queue_arr, rear);
		checkdown(mat, x, y, size, row, queue_arr, rear);
	}else{
		checkdown(mat, x, y, size, row, queue_arr, rear);
		checkright(mat, x, y, size, row, queue_arr, rear);
	}
	checkup(mat, x, y, size, row, queue_arr, rear);
}

int get_w_horizontal(int** mat, int x, int y, int row, int size)
{
	int weight = 0;
	if(x-1 < 0) {					//check out of bound
		weight = mat[x+1][y];		
		if(weight == 9999) {
			weight = mat[x+2][y-1];
		}
		return weight;
	}
	else if(x+1 > row-1) {         //check out of bound
		weight = mat[x-1][y];		
		if(x-2 >= 0 && y-1 >= 0 && weight == 9999) {
			weight = mat[x-2][y-1];
		}
		return weight;
	}
	int num = mat[x-1][y];
	int num1 = mat[x+1][y];
	if(num == 9999){
		num = get_min_neighbor(mat,x,y,up,row,size);
	}
	if(num1 == 9999){
		num1 = get_min_neighbor(mat,x,y,down,row,size);
	}
	if(num < num1)
		weight = num;
	else
		weight = num1;
	return weight;
}

int get_w_vertical(int** mat, int x, int y, int size)
{
	int weight = 0;
	if(y-1 < 0){					//check out of bound
		weight = mat[x][y+1];		
	}
	else if(y+1 > size-1)	{		
		weight = mat[x][y-1];
	}
	else if(mat[x][y+1] > mat[x][y-1]) {
		weight = mat[x][y-1];
	}
	else{
		weight = mat[x][y+1];
	}
	return weight;
}

int get_min_neighbor(int** mat, int x, int y, int direction, int row, int size) 
{
	int weight = 0;
	int weight1 = 0;
	if(direction == right){
		weight = get_w_horizontal(mat, x, y, row, size);
		weight1 = get_w_horizontal(mat, x, y+2, row, size);
	}
	else if(direction == up){
		weight = get_w_vertical(mat, x, y, size);
		weight1 = get_w_vertical(mat, x-2, y, size);
	}
	else{
		weight = get_w_vertical(mat, x, y, size);
		weight1 = get_w_vertical(mat, x+2, y, size);
	}
	if(weight1 < weight)
		weight = weight1;
	return weight;
}


static void destroy(int** temp, int row)
{
	for(int i = 0; i < row; i++) {
		free(temp[i]);	
	}
	free(temp);
}

static void color(int* num) 
{
	(*num) = (*num) * (-1);
}

static void enqueue(int num, int* queue_arr, int *rear)
{
	queue_arr[(*rear)] = num;
	(*rear)++;
}

int dequeue(int* queue_arr, int* front)
{
	int num = queue_arr[(*front)];
	(*front)++;
	return num;
}

static int** build_mat(int** map, int row, int size, int* arr, int* idx)
{
	int i1 = 0;
	int j1 = 0;
	int index = 1;
	int** mat = calloc(row, sizeof(int*));
	for(int i = 0; i < row; i++) {
		mat[i] = calloc(size, sizeof(int));
	}
	for(int i = 0; i < row; i++) {
		j1 = 0;
		for(int j = 0; j < size; j++) {
			if(i % 2 == 0 && j % 2 == 0) {
				if(map[i1][j1] == 1 && i + 1 < row) {
					mat[i+1][j] = 9999;
					arr[(*idx)] = i+1;
					arr[(*idx) + 1] = j;
					(*idx) += 2 ;
				}
				mat[i][j] =  index;
				j1++;
				index++;
			}
			else { 
				if(mat[i][j] != 9999)
					mat[i][j] = 1000;
			}
		}
		if(i % 2 == 0 && i1+2 < (row+1) / 2)
			i1++;
	}
	destroy(map, ((row+1)/2) -1);
	return mat;
}

static int find_shortest_path(int** mat, int row, int size, int* arr_board, int idx, int* queue_arr)
{
	int front = 0;
	int rear = 0;
	int path = 100000;
	int x = 0;
	int y = 0;
	int curr = 0;
	int a =0;
	for(int i = 0; i < row-2; i += 2) {
		color(&(mat[i][0]));
		connect(mat, i, 0, size, row, queue_arr, &rear);
		while(front < rear) { 		//while queue is not empty
			curr = dequeue(queue_arr, &front);
			search(mat, curr, &x, &y, row, size);
			connect(mat, x, y, size, row, queue_arr, &rear);
		}
		//	printf("%d-----------------------------new interation-------------------------------------\n",a++);
		get_path(mat, row, size, &path);
		clear_color(mat, row, size, arr_board, idx);
		//print_mat(mat, row, size);
	}
	free(queue_arr);
	return path+1;
}

int load_file(char *filename)
{
	int row = 0;
	int size = 0;
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		fprintf(stderr,"fopen fail\n");
		return 0;
	}
	fscanf(fp, "%d", &row);
	fscanf(fp, "%d", &size);

	char** temp = malloc(sizeof(char*) * (row-1));
	for(int i = 0; i < (row-1); i++) {
		temp[i] = malloc(sizeof(char) * size);
	}
	for(int i = 0; i < (row-1); i++) {
		for(int j = 0; j < size; j++) {
			fscanf(fp, "%c", &(temp[i][j]));
			if(temp[i][j] == '\n' || temp[i][j] == ' ')
				j--;
		}
	}
	//convert from char to int
	int** mat = malloc(sizeof(int*) * (row-1));
	for(int i = 0; i < (row-1); i++) {
		mat[i] = malloc(sizeof(int) * (size));
	}
	for(int i = 0; i < (row-1); i++) {
		for(int j = 0; j < size; j++) {
			mat[i][j] = (int) temp[i][j] -48;
		}
	}
	for(int i = 0; i < (row-1); i++) {
		free(temp[i]);	
	}
	free(temp);
	fclose(fp);

	int size_queArr = (row-1)*(row*size-1);
	int* queue_arr = malloc(sizeof(int) * (size_queArr));
	row = (2*row)-1;
	size = (2*size)-1;
	int* arr = malloc(sizeof(int)* (row*size));
	int idx_board = 0;
	mat = build_mat(mat, row, size, arr, &idx_board);
	print_mat(mat,row,size);
	int distance = find_shortest_path(mat, row, size, arr, idx_board, queue_arr); 
	destroy(mat, row);
	free(arr);
	return distance;
}

