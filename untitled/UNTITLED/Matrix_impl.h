
namespace MatrixStuff {

template<typename T>
void Matrix<T>::clear(Matrix& m) {
	m.~Matrix();
}

template<typename T>
inline short Matrix<T>::size() const {
	return row*column;
}

template<typename T>
void Matrix<T>::intrusive()
{
	for (size_t i = 0; i < column; i++)
    {
        for (size_t j = 0; j < row; j++) 
        {
			if ( j == 0 && i == 0)
				mtr[i][j].intrusive(nullptr, &mtr[i][j+1]);
			
			else if (j == 0)		// Почему row-3 ??
				mtr[i][j].intrusive(&mtr[i-1][row-3], &mtr[i][j+1]);

			else if (j == row-1) 
				mtr[i][j].intrusive(&mtr[i][j-1], &mtr[i+1][0]);
				
			else mtr[i][j].intrusive(&mtr[i][j-1], &mtr[i][j+1]);
			
		}	  
    }
}

// Операторы матрицы
template<typename T>
std::ostream& operator<< ( std::ostream& os, Matrix<T>& m ) {
	m.print();
	return os;
} 

template<typename T>
void Matrix<T>::fill_row(const size_t& id, T* values)
{
	for(size_t i = 0; i < column; i++)
		mtr[id][i] = values[i];	// Возможен ub: column может быть больше, чем 
								// кол-во элементов в values
}

template<typename T>
void Matrix<T>::fill_column(const size_t& id, T* values)
{
	for(size_t i = 0; i < row; i++)
		mtr[i][id] = values[i];	// Возможен ub: row может быть больше, чем 
								// кол-во элементов в values
}

template<typename T>
Matrix<T>::Matrix(const int x, const int y)
: row(y), column(x)
{
	mtr = (T**) new T*[row];

	for(size_t i = 0; i < row; i++ )
		mtr[i] = (T*) new T[column];

	first = &mtr[0][0];
}

template<typename T>
typename Matrix<T>::Proxy Matrix<T>::operator[](const int& id)
{
	return Proxy(*(mtr+id));
}

template<typename T>
void Matrix<T>::print() const
{
	using std::cout;

	for(size_t i = 0; i < row; i++ ) {
		for(size_t j = 0; j < column; j++ )	
			cout << mtr[i][j] << ' '; 
		cout << '\n'; // Перенос после каждой строки
	}
}

template<typename T>
Matrix<T>::~Matrix() {

	for(size_t i = 0; i < column; i++)
		delete [] mtr[i];
	
	delete[] mtr;

	row    = 0;
	column = 0;
}

};