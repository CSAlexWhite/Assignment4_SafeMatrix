/* 
Assignment_4 - Safe Matrix
Prepared for Dr. Waxman, June 9, 2015
CS780 Advanced OOP in C++
by Alex White
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <class T>
class SafeArray 
{

public:

	/* Default Constructor*/
	SafeArray() : 
		low{ 0 }, 
		high{ -1 }, 
		array{ nullptr } 
	{}

	/* Single-parameter Constructor*/
	SafeArray(int size) : 
		low{ 0 }, 
		high{ size - 1 }, 
		array{ new T[size] } 
	{}

	/* Two-parameter Constructor */
	SafeArray(int l, int h){

		if (h - l < 0)
		{
			cout << "Constructor Error in Bounds Definition";
			exit(1);
		}

		low = 0;
		high = h;
		array = new T[h - l + 1];
	}

	/* Copy Constructor */
	SafeArray(const SafeArray& input)
	{
		int size = input.high - input.low + 1;
		array = new T[size];

		for (int i = 0; i < size; i++)
			array[i] = input.array[i];

		low = input.low;
		high = input.high;
	}

	/* Destructor */
	~SafeArray()
	{
		delete[] array;
	}

	/* Overloaded [] */
	T& operator[] (int index)
	{
		if (index < low || index > high){

			cout << "Column index " << index << " out of range." << endl;
			cout << this;
			exit(1);
		}

		return array[index - low];
	}

	/* Overloaded Assignment */
	SafeArray& operator= (const SafeArray input)
	{
		if (this == &input) return *this;

		delete[] array;
		int size = input.high - input.low + 1;
		array = new T[size];

		for (int i = 0; i < size; i++)
			array[i] = input.array[i];

		low = input.low;
		high = input.high;

		return *this;
	}
	
	template <class T1>
	friend ostream& operator << (ostream& os, SafeArray<T1> s);

private:

	int low, high;
	T* array;
};

template <class T>
ostream& operator<< (ostream& os, SafeArray<T> input)
{
	int size = input.high - input.low + 1;
	for (int i = 0; i < size; i++)
		cout << input.array[i] << endl;
	return os;
}

template <class T>
class SafeMatrix 
{

public:

	/* Default Constructor */
	SafeMatrix() :
		row_low{ 0 },
		row_high{ -1 },
		col_low{ 0 },
		col_high{ -1 },
		rows{ 0 },
		cols{ 0 },
		matrix{ nullptr }
	{}

	/* Single-argument Constructor */
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

	/* Two-argument Constructor */
	SafeMatrix(int row, int col) :
		row_low{ 0 },
		row_high{ row - 1 },
		col_low{ 0 },
		col_high{ col - 1 },
		rows{ row },
		cols{ col },
		matrix{ new SafeArray<T>[row] }
	{
		for (int i = 0; i < row; i++)
			matrix[i] = SafeArray<T>(col);
	}

	/* Four-argument Constructor*/
	SafeMatrix(int rlow, int rhigh, int clow, int chigh)
	{
		if (row_high < row_low
			|| col_high < col_low) {

			cout << "Constructor Error in Bounds Definition" << endl;
			exit(1);
		}

		row_low = rlow;
		row_high = rhigh - 1;
		col_low = clow;
		col_high = chigh - 1;
		rows = rhigh - rlow;
		cols = chigh - clow;
		matrix = new SafeArray<T>[rows];

		for (int i = 0; i < rows; i++)
			matrix[i] = SafeArray<T>(cols);
	}

	/* Copy Constructor */
	SafeMatrix(const SafeMatrix &input) :
		row_low{ input.row_low },
		row_high{ input.row_high },
		col_low{ input.col_low },
		col_high{ input.col_high },
		rows{ input.rows },
		cols{ input.cols },
		matrix{ new SafeArray<T>[rows] }
	{
		for (int i = 0; i < rows; i++)
			matrix[i] = SafeArray<T>(cols);

		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++)
				matrix[i][j] = input.matrix[i][j];
		}
	}

	/* Destructor */
	~SafeMatrix()
	{
		delete[] matrix;
	}

	/* Overloaded [] */
	SafeArray<T>& operator[] (int index)
	{
		if (index < row_low || index > row_high){
			
			cout << "Row index " << index << " out of range." << endl;
			exit(1);
		}

		return matrix[index - row_low];
	}

	/* Overloaded Assignment */
	SafeMatrix<T>& operator= (const SafeMatrix<T> input)
	{
		if (this == &input) return *this;

		delete[] matrix;
		matrix = new SafeArray<T>[input.rows];

		for (int i = 0; i < input.rows; i++)
			matrix[i] = SafeArray<T>(input.cols);

		for (int i = 0; i < input.rows; i++)
		{
			for (int j = 0; j < input.cols; j++)
				matrix[i][j] = input.matrix[i][j];
		}

		rows = input.rows ;
		cols = input.cols;
		row_low = input.row_low;
		row_high = input.row_high;
		col_low = input.col_low;
		col_high = input.col_high;

		return *this;
	}

	/* Overloaded * */
	SafeMatrix<T> operator* (const SafeMatrix<T> input)
	{
		SafeMatrix<T> output(rows, input.cols);

		if (cols != input.rows)
		{
			cout << "Incompatible Matrix Dimensions: " << cols << " != " << input.rows;
			return SafeMatrix<int>(0,0);
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < input.cols; j++)
			{
				output[i][j] = 0;
				for (int k = 0; k < input.rows; k++)
				{
					output[i][j] += matrix[i][k] * input.matrix[k][j];				}
			}
		}
		return output;
	}

	template <class T1>
	friend ostream& operator << (ostream &os, SafeMatrix<T1> matrix);

private:

	int rows, cols, row_low, row_high, col_low, col_high;
	SafeArray<T>* matrix;
};

template <class T>
ostream& operator << (ostream &os, SafeMatrix<T> matrix)
{
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			//cout << matrix[i][j] << ' ';
			os << matrix[i][j] << ' ';
		}
		//cout << endl;
		os << endl;
	}
	return os;
}

int main(){

	SafeMatrix<int> pair[2];

	string infilename, outfilename, dimensions, values;
	cout << "Please enter the input file name : ";
	cin >> infilename;
	cout << "Please enter the output file name : ";
	cin >> outfilename;

	ofstream myfile;
	myfile.open(outfilename);
	
	int count = 0;
	ifstream infile(infilename);
	while (!infile.eof())
	{
		cout << "\nProcessing Matrix Pair " << count++ << "...";
		
		for (int member = 0; member < 2; member++)
		{
			int row, col;

			infile >> row;
			infile >> col;

			pair[member] = SafeMatrix<int>(row, col);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					infile >> pair[member][i][j];
				}
			}

			myfile << "\nMatrix " << member+1  <<   " : \n" << endl;
			myfile << pair[member];
		}

		myfile << "\nMatrix 1 x Matrix 2 : \n" << endl;
		myfile << pair[0] * pair[1];
		myfile << "\n= = = = = = = = = = = = = = = =" << endl;

		cout << "...Done" << endl;
	}
	
	cout << endl << "Please see output file \"" << outfilename << "\" for results\n" << endl;
	myfile.close();
	system("pause");
	return 0;
}
