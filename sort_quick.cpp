#include <stdio.h>

#define swap(t, x, y) t temp = x; \
	x = y;  \
	y = temp;  

/*
void Swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}
*/

void QuickSort(int* arr, int left, int right)
{
	if(left < right) {
		int pivot = right;
		int i = 0;
		
		// partition
		for(int j = 0; j < right; ++j) {
			if(arr[j] <= arr[pivot]) {
				swap(int, arr[i], arr[j]);
				++i;
			}
		}
		swap(int, arr[i], arr[pivot]);
		pivot = i; 
		
		QuickSort(arr, left, pivot-1);
		QuickSort(arr, pivot+1, right);
	}
	
}

int main() {
	int size = 10;
	int arr[size] = {4, 89, 2, 10, 26, 88, 3, 29, 19, 109};
	QuickSort(arr, 0, size-1);
	
	for(int i = 0; i < size; ++i) {
		printf("%d ", arr[i]);
	}
	
	return 0;
}


