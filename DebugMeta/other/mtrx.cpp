#include <iostream>

#define HEIGHT 3
#define WEIGHT 3

int arr [HEIGHT][WEIGHT];

class WorkWithMatrix{
	private:
		
		int _sumOfLine(auto& arr){
			int sum = 0;

			for(int i : arr ){
				sum += i; 
			}
			return sum;
		}
		
		void _bbl_sort(int array [], int sz){
			int *temp = new int; 
			for(int i = 0; i < sz; i++){
				for(int j = i+1; j < sz; j++ ){
					if (array[i] > array[j]){
						*temp = array[i];
						array[i] = array[j];
						array[j] = *temp; 
					}
				}
			}
			delete temp;
		}

	public:
		print(auto& mtrx, int h, int w){
			for(h = 0; h < HEIGHT; h++){
				for(w = 0; w < WEIGHT; w++){
					std::cout << " " << mtrx[h][w]; 
				}
				std::cout << std::endl;
			}
		}	

		upend_lines(auto& mtrx, int h, int w, int indx = WEIGHT-2){
			for(h = 0; h < HEIGHT; h++){
				auto start = mtrx[h][0];
				auto end = mtrx[h][WEIGHT-1];
				
				mtrx[h][0] = end;
				mtrx[h][WEIGHT-1] = start;
				
				for(w = 1; w < indx; w++, indx--){
					mtrx[h][w] = mtrx[h][indx];
				}

			}
		}

		void sort_lines(auto& mtrx, char typeSort){
			if (typeSort == 'b'){
				for(int h = 0; h < HEIGHT; h++ ){
					_bbl_sort(mtrx[h], WEIGHT);
				}
			}
		}

		void first_element_sort(auto& mtrx){
			
			int i,j; 
			int	*temp; 
			temp = (int*) std::malloc(sizeof(int)*HEIGHT);
			
			for(i = 0; i < HEIGHT; i++ ){
				for(j = i+1; j < HEIGHT; j++ ){
					if(mtrx[i][0] > mtrx[j][0]){
						*temp = *mtrx[i];
						*mtrx[i] = *mtrx[j];
						*mtrx[j] = *temp;
					}
				}
			}
			std::free(temp);
		}


		WorkWithMatrix operator++(int){
			for(int h = 0; h < HEIGHT; h++ ){
				for(int w = 0; w < WEIGHT; w++ ){
					arr[h][w] = arr[h][w]+1;
				}
			}
		}
		
		WorkWithMatrix operator--(int){
			for(int h = 0; h < HEIGHT; h++ ){
				for(int w = 0; w < WEIGHT; w++ ){
					arr[h][w] = arr[h][w]-1;
				}
			}
		}
};


int main()
{

	WorkWithMatrix mtrx;

	int h = 0,w = 0, j = 0;

	for(; h < HEIGHT; h++){
		for(w = 0; w < WEIGHT; w++){
			std::cin >> arr[h][w];
		} 
	}
	for (; j < 6; j++ ){ std::cout << "-"; } std::cout << std::endl;
	
	mtrx.print(arr, h, w);
}