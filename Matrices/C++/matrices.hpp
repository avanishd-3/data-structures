#include <iostream>
#include <iomanip>
#include <sstream>

#include "Arrays/array.hpp"

template<typename T>
class DiagonalMatrix {
    private: 
        T *data;
        int diagonal_length;

    public:
        DiagonalMatrix(int i)
            : data(new T[i-1])
            , diagonal_length(i)
        {
        }

        int num_diagonals() const {
            return diagonal_length;
        }

        ~DiagonalMatrix() {
            delete[] data;
        }

        T& operator[](int row) {
			return data[row];
		}

		const T& operator[](int row) const {
			return data[row];
		}

        friend std::ostream& operator<<(std::ostream &out, const DiagonalMatrix<T> &matrix) {
	        for (int i = 0; i < matrix.num_diagonals(); ++i) {
		        out << matrix[i] << ' ';
	    }

	    return out;
}
};

template<typename T>
class LowerTriangularMatrix { // Using row-major mapping
    private: 
        T *data;
        int rows;
        int cols;

    public:
        LowerTriangularMatrix(int i)
            : data(new T[n(n+1)]/2)
            , rows{i}
            , cols{n}
        {
        }

        int num_rows() const {
            return rows;
        }

        int num_cols() const {
            return cols;
        }

        ~LowerTriangularMatrix() {
            delete[] data;
        }

        T& operator[](int i, int j) {
            int num = i(i-1)/2+j-1;
			return data[num];
		}

		const T& operator[](int i, int j) const {
			int num = i(i-1)/2+j-1;
			return data[num];
		}

        friend std::ostream& operator<<(std::ostream &out, const LowerTriangularMatrix<T> &matrix) {
	        for (int i = 1; i < matrix.num_rows(); ++i) {
                for (int j = 0; j < i; ++j) {
                    out << matrix[i] << ' ';
                }
                out << std::endl;
		        
	        }

	    return out;
        }
};

template <typename T>
class SparseMatrix {
    private:
        struct Element {
            int row_num;
            int column_num;
            T element;
        };

        int num_rows;
        int num_cols;
        int num_values;

        Element *elements;

    public:
        Element(int r, int c, int n)
            : num_rows{r}
            , num_cols{c}
            , num_values{n}
            , elements(new Element[num])
        {
        }

        ~Element() {
            delete[] elements;
        }

        friend std::ostream& operator<<(std::ostream &out, const SparseMatrix<T> &matrix) {
            int k = 0;

	        for (int i = 1; i < matrix.num_rows; ++i) {
                for (int j = 0; j < matrix.num_columns; ++j) {
                    if (matrix.elements[k].row_num == i && matrix.elements[k].column_num == j) {
                        out << matrix.elements[k++].element << ' ';
                    }
                    else {
                        out << '0' << ' ';
                    }
                out << std::endl;
                }
                out << std::endl;
		        
	            }
	        return out;
        }

        SparseMatrix* operator+(SparseMatrix &B) {
            // First check dimensions
            if (num_rows != B.num_rows || num_cols != B.num_cols) {
                throw std::invalid_argument("Dimensions do not match")
            }

            SparseMatrix<T> *sum = new Sparse(m,n,num_values + B.num_values);

            int i,j,k;

            i = j = k = 0;
            while (i < num_values && j < B.num_values) {
                if (elements[i].row_num < B.elements[j].row_num) { 
                    sum->elements[k++] = elements[i++];
                }
                else if (elements[i].row_num > B.elements[j].row_num) { 
                    sum->elements[k++] = B.elements[i++];
                }

                else {
                    // Check column numbers
                    if (elements[i].column_num < B.elements[j].column_num) { 
                        sum->elements[k++] = elements[i++];
                    }

                    else if (elements[i].column_num > B.elements[j].column_num) { 
                        sum->elements[k++] = B.elements[i++];
                    }

                    else {
                        // Perform actual addition
                        sum->elements[k++].element = elements[i++].element + B.elements[j++].element;
                    }
                }
            }
            // Copy the remaining elements from either the first or second matrix
            for (;i<num_values; +++i) { // Copy remaining elements from first matrix if any
                sum->elements[k++] = elements[i];
            }

            for (;j<B.num_values; +++j) { // Copy remaining elements from second matrix if any
                sum->elements[k++] = B.elements[i];
            }

            // Put actual number of non-zero elements
            sum->num_values = k;
            return sum;
        }
};

template <typename T>
class Matrix {
	public:
		Matrix()
			: rows{0}
			, cols{0}
			, data(0)
		{
		}

		Matrix(int rows, int cols)
			: rows{rows}
			, cols{cols}
			, data(rows)
			{
			for (int i = 0; i < rows; ++i) { // Each array is a row of the matrix
				data[i] = Array<T>{cols};
			}
		}

		Array<T>& operator[](int row) {
			return data[row];
		}

		const Array<T>& operator[](int row) const {
			return data[row];
		}

		
		int num_rows() const {
			return rows;
		}
		int num_cols() const {
			return cols;
		}

		void fill(const T &val) {
			for (int i = 0; i < rows; ++i) {
				data[i].fill(val);
			}
		}
	
		template <typename Fn>
		void fill_with_fn(Fn fn) {
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					data[i][j] = fn(i, j);
				}
			}
		}

        friend std::ostream& operator<<(std::ostream &out, const Matrix<T> &matrix) {
	        for (int i = 0; i < matrix.num_rows(); ++i) {
		        out << matrix[i] << std::endl;
	        }

	        return out;
        }

        friend std::istream& operator>>(std::istream &in, Matrix<T> &matrix) {
	        std::string line;
	        int i = 0;


	        while (std::getline(in, line) && i < matrix.num_rows()) {
		        if (line == "") {
			        continue;
		        }
		        std::istringstream temp(line);
		        temp >> matrix[i];
		        ++i;
	        } 
	        return in; 
        }

	private:
		int rows, cols;
		Array<Array<T>> data;
};