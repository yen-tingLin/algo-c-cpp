#include <iostream>

#define tableLen 4
#define tableWidth 2

void createArr(int*** arr_ptr, int num, int weight)
{
	*arr_ptr = new int*[num];
	for(int i = 0; i < num; ++i) (*arr_ptr)[i] = new int[weight]; 
}

void initialArr(int*** arr, int num, int weight) 
{
	for(int i = 0; i < num; ++i) {
		for(int j = 0; j < weight; ++j) {
			(*arr)[i][j] = 0;
		}
	}
}


void printDP(int*** arr, int num, int weight)
{
	for(int i = 0; i < num; ++i) {
		for(int j = 0; j < weight; ++j) {
			std::cout << (*arr)[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void DPknapsack(int*** arr, int num, int weight, int matrix[tableWidth][tableLen])
{
	for(int j = 1; j < weight; ++j) {
		if(j >= matrix[0][0]) {
			(*arr)[1][j] = matrix[1][0]; 
		}
	}
	
	for(int i = 1; i < num; ++i) {
	 	for(int j = 1; j < weight; ++j) {
	 		int remain_weight = j-matrix[0][i-1];
	 		if(remain_weight>= 0) {
		 		int temp1 = (*arr)[i-1][j];
		 		int temp2 = (*arr)[i-1][remain_weight] + matrix[1][i-1];
		 		(*arr)[i][j] = (temp1 >= temp2) ? temp1 : temp2;
		 	} else {
		 		(*arr)[i][j] = (*arr)[i-1][j];
			 }
		 }
	 }
	
}

void freeSpace(int*** arr, int num, int weight)
{
	for(int i = 0; i < num; ++i) {
		delete (*arr)[i];
	}
	delete *arr;
}

int main() {
	int item_num = tableLen + 1;
	int max_weight = tableLen + 5;
	int table[tableWidth][tableLen] = { {2,3,4,5}, {1,2,5,6} };
	int **DP_table;
	
	createArr(&DP_table, item_num, max_weight);	
	initialArr(&DP_table, item_num, max_weight);
	
	DPknapsack(&DP_table, item_num, max_weight, table);
	printDP(&DP_table, item_num, max_weight);
	freeSpace(&DP_table, item_num, max_weight);

	return 0;
}
