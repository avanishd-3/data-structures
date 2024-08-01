#include <iostream>
#include <iomanip>
#include <sstream>

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