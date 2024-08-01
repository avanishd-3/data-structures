#include <iostream>
#include <iomanip>
#include <sstream>


template<typename T>
class Array { // Fixed size array
    private:
        T *buf;
        int max_len; // Physical size
        int current_len; // Logical length

        bool in_bounds(int index) const {
            return index >= 0 && index < max_len;
        }

        bool insertable(int index) const { // Cannot insert more than 1 index past logical length
            return index >=0 && index < current_len;
        }

    public:
        Array() // Zero size array
            : buf{nullptr}
            , max_len{0}
            , current_len{0}
        {
        }
        
        Array(int len)
            : buf(new T[max_len])
            , max_len{len}
            , current_len{0}
        {
        }

        ~Array() {
            delete[] buf;
        }

        int current_length() const {
            return current_len;
        }

        friend std::ostream& operator<<(std::ostream &out, const Array<T> &array) {
	        std::stringstream temp;
	        temp << std::setprecision(2) << std::fixed << std::right;

	        for (int i = 0; i < array.current_length(); ++i) {
		        temp << std::setw(8) << array[i];
	        }

	        out << temp.str();
	        return out;
}

        void append(int n) { // O(1) operation
            if (current_len < max_len) {
                buf[current_len++] = n;
            }

            else {
               throw std::length_error("Array is full"); 
            }
        }

        void insert(int index, T element) {
            if (!insertable(index)) {
				throw std::out_of_range("Index is out of range to be insertable");
			}

            if (current_len <= max_len - 1) {
                for (int i = current_len; i > index; --i) {
                    buf[i] = buf[i - 1]; // Worst case -> O(n)
                }

                buf[index] = element; // Best case -> O(1)
                ++current_len;
            }

            else {
                throw std::length_error("Array is full");
            }
        }

        void remove(int index) {
            if (!insertable(index)) {
				throw std::out_of_range("Index is out of range to be deleted");
			}
            for (int i = index; i < current_len - 1; ++i) {
                    buf[i] = buf[i + 1];  // Worst case -> O(n)
                }
            --current_len; // Best case -> O(1)
        }

        void reverse() {
            for (int i = 0, int j = current_len - 1; i < j; ++i, --j) {
                int temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }

        int find(T key) const { // Linear search
            for (int i = 0; i < current_len; ++i) { // Best case -> O(1) (key is at 0th element)
                if (buf[i] == key) {
                    return i; // Average case -> O(n)
                }
            }
            return -1; // Element not found // Worst case -> O(n)
        }

        T max() const {
            T max = buf[0];
            for (int i = 1; i < current_len; ++i) {
                if (buf[i] > max) {
                    max = buf[i];
                }
            }
            return max;
        }

        T min() const {
            T min = buf[0];
            for (int i = 1; i < current_len; ++i) {
                if (buf[i] < min) {
                    max = buf[i];
                }
            }
            return min;
        }

        // Get length of array
		int length() const {
			return current_len;
		}

		// Get a particular element of the array
		T& operator[](int index) {
			if (!in_bounds(index)) {
				throw std::out_of_range("Index is out of range");
			}
			return buf[index]; // Shuts up compiler
		}

		const T& operator[](int index) const {
			if (!in_bounds(index)) {
				throw std::out_of_range("Index is out of range");
			}
			return buf[index]; // Shuts up compiler
		}

};