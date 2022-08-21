
namespace MatrixStuff {

template<typename T>
void Matrix<T>::clear(Matrix& m) {
	m.~Matrix();
}

template<typename T>
inline short Matrix<T>::size() const {
	return row*column;
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
	
	for(size_t i = 0; i < row; i++ ) 
		for(size_t j = 0; j < column; j++ )	
			mtr[i][j] = T();

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

	for(size_t i = 0; i < row; i++)
		delete [] mtr[i];
	
	delete[] mtr;

	row    = 0;
	column = 0;
}

};