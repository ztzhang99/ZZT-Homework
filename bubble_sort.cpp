#include<iostream>

const int LENGTH = 6;

template<typename T>
void bubble_sort(T [], int);

int main(){
	int arr[LENGTH] = {33, 56, 17, 8, 95, 22};
	bubble_sort(arr, LENGTH);
	for(int i = 0; i < LENGTH; i++)
		std::cout << arr[i] << ' ';
}

template<typename T>
void bubble_sort(T arr[], int length){
	int i, j;
	T temp;
	for(i = 0; i < length - 1; i++){
		for(j = 0; j < length - 1 - i; j++){
			if(arr[j] > arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}