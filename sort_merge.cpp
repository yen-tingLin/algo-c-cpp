#include <stdio.h>

void Merge(int left, int mid, int right, int* arr)
{
	int left_size = mid-left+1;
	int right_size = right-mid;	
	
	int left_arr[left_size];
	int right_arr[right_size];
	
	for(int i = left; i <= mid; ++i) {
		left_arr[i-left] = arr[i];
	}
	for(int i = mid+1; i <= right; ++i) {
		right_arr[i-mid-1] = arr[i];
	}
	
	int left_idx = 0; 
	int right_idx = 0;
	for(int k = left; k <= right; ++k) {
		if(left_idx < left_size && right_idx < right_size) {
			if(left_arr[left_idx] <= right_arr[right_idx]) {
				arr[k] = left_arr[left_idx];
				++left_idx;
			} else {
				arr[k] = right_arr[right_idx];
				++right_idx;
			}
		} else if(left_idx < left_size) {
			arr[k] = left_arr[left_idx];
			++left_idx;
		} else if(right_idx < right_size) {
			arr[k] = right_arr[right_idx];
			++right_idx;
		}
	}
		
}

void MergeSort(int left, int right, int* arr) 
{
	if(left < right) {
		int mid = (left + right) / 2;
		MergeSort(left, mid, arr);
		MergeSort(mid+1, right, arr);
		Merge(left, mid, right, arr);
	}
	
}

int main() {
	
	int size = 9;
	int array[size] = {0, 28, 87, 89, 55, 14, 123, 22, 10};

	MergeSort(0, 8, array);
	
	for(int i = 0; i < size; ++i) {
		printf("%d ", array[i]);
	}
	
	return 0;
}
