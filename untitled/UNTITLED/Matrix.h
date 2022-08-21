#include <iostream>

namespace MatrixStuff
{

template<typename T>
class Matrix
{

private:

	T** mtr;
	short row, column;	

	struct Proxy
	{
		Proxy(T* r) { _row = r; }
		T& operator[](const int& id_y) { return *(_row+id_y); } // _row = *(mtr+id)
		T* _row;
	};
	
public:	
	
	Matrix(const int, const int);
	Matrix(const Matrix&);
	Matrix(Matrix&&);

	Matrix& operator=(const Matrix&);
	Matrix& operator=(Matrix&&);

	Proxy operator[](const int&);
	const Proxy operator[](const int&) const;
	
	void print() const;
	short size() const;

	// Агрегаты
	void fill_row(const size_t&, T*);
	void fill_column(const size_t&, T*);
		
	~Matrix();

	static void clear(Matrix&);

	// Proxy pr;
	T* t_row;

}; // Matrix 


}; // MatrixStuff

#include "Matrix_impl.h"
