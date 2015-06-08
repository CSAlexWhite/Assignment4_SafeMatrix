#include <iostream>
//#include "SafeArray.h"
using namespace std;

template <class T>
class SafeArray {

private:

	int low, high;
	T* array;

public:

	/* Default Constructor*/
	SafeArray() : low{ 0 }, high{ -1 }, array{ nullptr } {}

	/* Two-parameter Constructor */
	SafeArray(int l, int h){

		if (h - l < 0){

			cout << "Constructor Error in Bounds Definition";
			exit(1);
		}

		low{ l };
		high{ h };
		array = new T[h - l + 1];
	}

	/* Single-parameter Constructor*/
	SafeArray(int size) : low{ 0 }, high{ size - 1 }, array{ new T[size] } {}

	/* Copy Constructor */
	SafeArray(const SafeArray& s){

		int size = s.high - s.low + 1;
		array = new T[size];

		for (int i = 0; i < size; i++) 
			array[i] = s.array[i];

		low = s.low;
		high = s.high;
	}

	/* Destructor */
	~SafeArray(){

		delete[] array;
	}

	/* Overloaded [] */
	T& operator[] (int index){

		if ( index < low || index > high ){

			cout << "Index " << i << " out of range." << endl;
			exit(1);
		}

		return array[index - low];
	}

	/* Overloaded Assignment */
	SafeArray& operator= (const SafeArray s){

		if (this == &s) return this;

		delete[] array;
		int size = s.high - s.low + 1;
		array = new T[size];

		for (int i = 0; i < size; i++) 
			array[i] = s.array[i];

		low = s.low;
		high = s.high;

		return *this;
	}

	friend ostream& operator << <T> (ostream& os, SafeArray<T> s);
};

template <class T>
ostream& operator<< (ostream& os, SafeArray<T> s){

	int size = s.high - s.low + 1;
	for (int i = 0; i < size; i++) 
		cout << s.array[i] << endl;
	return os;
}

template <class T>
class SafeMatrix {

private:

	int rows, cols, row_low, row_high, col_low, col_high;
	SafeArray<T>* matrix;

public:

	SafeMatrix() :
		row_low{ 0 },
		row_high{ -1 },
		col_low{ 0 },
		col_high{ -1 },
		rows{ 0 },
		cols{ 0 },
		matrix{ nullptr }
	{}

	SafeMatrix(int size) :
		row_low{ 0 },
		row_high{ size - 1 },
		col_low{ 0 },
		col_high{ size - 1 },
		rows{ size },
		cols{ size },
		matrix{ new SafeArray<T>[size] }
	{
		for (int i = 0; i < size; i++) 
			matrix[i] = SafeArray<T>(size);
	}

	SafeMatrix(int row, int col) :
		row_low{ 0 },
		row_high{ row - 1 },
		col_low{ 0 },
		col_high{ col - 1 },
		rows{ row },
		cols{ col },
		matrix{ new SafeArray<T>[row] }
	{
		for (int i = 0; i < size; i++) 
			matrix[i] = SafeArray<T>(col);
	}

	SafeMatrix(int row_low, int row_high, int col_low, int col_high)
	{
		if (row_high < row_low
			|| col_high < col_low) {

			cout << "Constructor Error in Bounds Definition" << endl;
			exit(1);
		}

		row_low{ row_low };
		row_high{ row_high - 1 };
		col_low{ col_low };
		col_high{ col_high - 1 };
		rows{ row_high - row_low };
		cols{ col_high - col_low };
		matrix{ new SafeArray<T>[rows] };

		for (int i = 0; i < rows; i++) 
			matrix[i] = SafeArray<T>(cols)
	}

	SafeMatrix(const SafeMatrix &s) :
		row_low{ s.row_low },
		row_high{ s.row_high },
		col_low{ s.col_low },
		col_high{ s.col_high },
		rows{ s.rows },
		cols{ s.cols },
		matrix{ new SafeArray<T>[rows] }
	{
		for (int i = 0; i < rows; i++)
			matrix[i] = SafeArray<T>(cols);

		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++)
				matrix[i][j] = s.matrix[i][j];
		}
	}

	SafeArray<T>& operator[] (int index){

		if ( index < row_low || index > row_high ){

			cout << "Index " << i << " out of range." << endl;
			exit(1);
		}

		return matrix[index - row_low];
	}

	SafeMatrix<T>& operator= (const SafeMatrix<T> s){

		if (this == &s) return *this;

		delete[] matrix;
		matrix = new SafeArray<t>[s.rows];

		for (int i = 0; i < s.rows); i++)
			matrix[i] = SafeArray<T>(s.cols);

		for (int i = 0; i < s.rows; i++){
			for (int j = 0; j < s.cols; j++)
				matrix[i][j] = s.matrix[i][j];
		}

		rows = s.rows;
		cols = s.cols;
		row_low = s.row_low;
		row_high = s.row_high;
		col_low = s.col_low;
		col_high = s.col_high;

		return *this;
	}

	SafeMatrix<T> operator* (const SafeMatrix<T> s){

		if (cols != s.rows){

			cout << "Incompatible Matrix Dimensions: " << cols << " != " << s.rows << endl;
			return NULL;
		}

		SafeMatrix<T> output(rows, s.cols);


	}
};

int main(){

	//SafeMatrix <int> A();
	SafeMatrix <int> B = new SafeMatrix<int>(10);
	B[1][1] = 5;
	cout << B[1][1];
	//SafeMatrix <int> C(5, 10);
	//SafeMatrix <int> D(1, 4, 2, 5);
}
