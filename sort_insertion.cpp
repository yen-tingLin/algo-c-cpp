#include <stdio.h>

void InsertionSort(int* arr, int size) 
{
	for(int i = 1; i < size; ++i) {
		int j = i-1;
		int key = arr[i];
		while(j >= 0 && arr[j] > key) {
			arr[j+1] = arr[j];
			j--; 
		}
		arr[j+1] = key;
	}
}

int main()
{
	int size = 10;
	int arr[size] = {25, 8, 19, 103, 33, 78, 43, 21, 99, 1};
	InsertionSort(arr, size);
	
	for(int i = 0; i < size; ++i) {
		printf("%d ", arr[i]);
	}
	
	return 0;
}
