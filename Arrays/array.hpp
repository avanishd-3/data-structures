#include <iostream>
#include <iomanip>
#include <sstream>
#include <utility>


template<typename T>
class StaticArray { // Fixed size array
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
        StaticArray() // Zero size array
            : buf{nullptr}
            , max_len{0}
            , current_len{0}
        {
        }
        
        StaticArray(int len)
            : buf(new T[max_len])
            , max_len{len}
            , current_len{0}
        {
        }

        ~StaticArray() {
            delete[] buf;
        }

        int current_length() const {
            return current_len;
        }

        friend std::ostream& operator<<(std::ostream &out, const StaticArray<T> &array) {
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

template <typename T>
class Array {
	public:
		// Construct zero-length array
		Array()
			: len{0}
			, buf{nullptr}
		{
		}

		// Construct array of given length
		explicit Array(int len)
			: len{len}
			, buf{new T[len]}
		{
		}

		// Copy and move constructors
		Array(const Array &other) 
			: len{0}
			, buf{nullptr}
		{
			int other_len = other.length();
			Array temp_array = Array(other_len);

			for (int i = 0; i < other_len; ++i) {
				temp_array.buf[i] = other.buf[i];
			}

			swap(*this, temp_array);
		}

		Array(Array &&other) noexcept
			: len{other.len}
			, buf{other.buf}
		{
			other.len = 0;
			other.buf = nullptr;
		}

		// Swap 2 arrays without allocations
		friend void swap(Array &lhs, Array &rhs) noexcept {
			std::swap(lhs.len, rhs.len);
			std::swap(lhs.buf, rhs.buf);
		}

		// Copy and move assignment
		Array& operator=(const Array &other) {
			Array temp_array(other);
			swap(*this, temp_array);

			return *this;
		}

		Array& operator=(Array &&other) noexcept {

			if(this == &other) {
				return *this; // Handle self-assignment
			}

			delete[] buf;

			swap(*this, other);

			other.len = 0;
			other.buf = nullptr;

			return *this;
		}

		// Destructor
		~Array() {
			delete[] buf;
		}

		// Get length of array
		int length() const {
			return len;
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

		// Set every element of the array to val
		void fill (T val) {
			for (int i = 0; i < len; ++i) {
				buf[i] = val;
			}
		}

		// TODO: Fill array by setting every entry i to fn(i)
		template <typename Fn>
		void fill_with_fn(Fn fn) {
			for (int i = 0; i < len; ++i) {
				buf[i] = fn(i);
			}	
		}

        friend std::ostream& operator<<(std::ostream &out, const Array<T> &array) {
            std::stringstream temp;
	        temp << std::setprecision(2) << std::fixed << std::right;
            
            for (int i = 0; i < array.length(); ++i) {
		        temp << std::setw(8) << array[i];
	        }

	        out << temp.str();
	        return out;
        }

        // Read array from in separated by whitespace
        friend std::istream& operator>>(std::istream &in, Array<T> &array) {
            for (int i = 0; i < array.length(); ++i) {
                in >> array[i];
	        }
	        return in;
        }
		
	private:
		int len;
		T *buf;

		bool in_bounds(int index) const {
			return index >= 0 && index < len;
		}
};