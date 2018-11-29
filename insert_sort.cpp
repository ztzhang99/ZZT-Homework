#include<iostream>
#include<vector>

template<typename T>
void insert(std::vector<T> &, T);

template<typename T>
void insert_sort(std::vector<T> &);

int main(){
	std::vector<int> v = {60, 65, 75, 80, 90, 95};
	insert(v, 50);
	insert(v, 67);
	insert(v, 99);
	for(int i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
}

template<typename T>
void insert(std::vector<T> &v, T element){
	v.push_back(element);
	insert_sort(v);
}

template<typename T>
void insert_sort(std::vector<T> &v){
	for(int i = 1; i < v.size(); i++){
		for(int j = i; j > 0; j--){
			if(v[j-1] > v[j]){
				T tmp = v[j-1];
				v[j-1] = v[j];
				v[j] = tmp;
			}
		}
	}
}

//50 60 65 67 75 80 90 95 99