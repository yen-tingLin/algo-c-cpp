#include <stdio.h>
#include <stdlib.h>

#define swap(t, x, y) t temp = x; \
	x = y; \
	y = temp


// time : O(logN)
void MinHeapify(int* arr, int idx, int arr_size)
{
	int left, right;
	int smallest = -1;
	
	while(idx > 0) {		
		left = idx*2;
		right = idx*2 + 1;
		if(left < arr_size && arr[left] <= arr[idx]) {
			smallest = left;
		} else {
			smallest = idx;
		}
		if(right < arr_size && arr[right] <= arr[smallest]) {
			smallest = right;
		}
		if(smallest != idx) {
			swap(int, arr[smallest], arr[idx]);
			idx = smallest;
		} else {
			return;
		}	
	}
}

// tighter upper time bond : O(N), not O(NlogN)
void BuildMinHeap(int* arr, int arr_size)
{	
	for(int idx = (arr_size-1)/2; idx >= 1; --idx) {
		MinHeapify(arr, idx, arr_size);
	}
}

// time : O(NlogN)
void HeapSort(int* arr, int arr_size)
{
	BuildMinHeap(arr, arr_size);

	for(int i = arr_size-1; i > 1; --i) {
		swap(int, arr[1], arr[arr_size-1]);
		--arr_size;
		MinHeapify(arr, 1, arr_size);		
	}

}

int main() {
	int arr_size = 11;
	int arr[arr_size] = {-1, 12 ,3 ,254 , 21, 6, 23, 65, 33, 9, 10};

	HeapSort(arr, arr_size);
	
	for(int i = arr_size-1; i > 0; --i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	return 0;
}
