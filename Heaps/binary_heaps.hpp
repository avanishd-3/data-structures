#include <vector>
#include <utility> // For std::swap

template <typename T>
class MaxHeap {
    private:
        std::vector<T> heap;

    public:
        MaxHeap()
        {
            heap.push_back(T());
        }

        MaxHeap(std::vector<T> &v) { 
            for (T val : v) {
                insert(val);
            }

        }

        const int size() const noexcept{
            return heap.size() - 1;

        }

        T& operator[](int val) {
            return heap[val + 1];
        }

        const T& operator[](int val) const {
            return heap[val + 1];
        }

        void insert(int key) {
            heap.push_back(key);
            int i = heap.size();

            while (i > 1 && heap[i/2] < key) {
                heap[i] = heap[i/2];
                i = i/2;
            }
            heap[i] = key;
        }

        void max_heapify(std::vector<T> &A, i) { // In-place & runs in O(n) time
            int left = 2*i;
            int right = 2*i + 1;

            int size = A.size();

            int largest = (left <= size && A[left] > A[i] ? left : i);

            if (right <= size && A[right] > A[largest]) {
                largest = right;
            }

            if (largest != i) {
                std::swap(A[i], A[largest]);
                max_heapify(A, largest);
            }
        }

        void remove() { // Can only delete the top element from the max heap
            int size = heap.size();

            heap[1] = heap[size - 1];

            int i = 1;

            while (i < size && heap[i] < (heap[2*i] > heap[2*i+1] ? heap[2*i] : heap[2*i+1])) {
                std::swap(heap[i], (heap[2*i] > heap[2*i+1] ? heap[2*i] : heap[2*i+1]));
                
                i = heap[2*i] > heap[2*i+1] ? 2*i : 2*i + 1;
            }

	    heap.resize(size-1);
	
        }

        friend std::ostream& operator<<(std::ostream &out, const MaxHeap<T> &max_heap) {
            int size = max_heap.size();
	        for (int i = 1; i < size; ++i) {
		        out << max_heap[i] << ' ';
	        }
            	out << std::endl;

	        return out;
        }
};

template <typename T>
class MinHeap {
    private:
        std::vector<T> heap;

    public:
        MinHeap()
        {
            heap.push_back(T());
        }

        MinHeap(std::vector<T> &v) {
            for (T val : v) {
                insert(val);
            }

        }

        const int size() const noexcept{
            return heap.size() - 1;

        }

        T& operator[](int val) {
            return heap[val + 1];
        }

        const T& operator[](int val) const {
            return heap[val + 1];
        }

        void insert(int key) {
            heap.push_back(key);
            int i = heap.size();

            while (i > 1 && heap[i/2] > key) {
                heap[i] = heap[i/2];
                i = i/2;
            }
            heap[i] = key;
        }

        void min_heapify(std::vector<T> &A, i) {  // In-place & runs in O(n) time
            int left = 2*i;
            int right = 2*i + 1;

            int size = A.size();

            int smallest = (left <= size && A[left] < A[i] ? left : i);

            if (right <= size && A[right] < A[largest]) {
                smallest = right;
            }

            if (smallest != i) {
                std::swap(A[i], A[smallest]);
                min_heapify(A, smallest);
            }
        }

        void remove() { // Can only delete the top element from the max heap
            int size = heap.size();

            heap[1] = heap[size - 1];

            int i = 1;

            while (i < size && heap[i] > (heap[2*i] < heap[2*i+1] ? heap[2*i] : heap[2*i+1])) {
                std::swap(heap[i], (heap[2*i] > heap[2*i+1] ? heap[2*i] : heap[2*i+1]));
                
                i = heap[2*i] < heap[2*i+1] ? 2*i : 2*i + 1;
            }

	    heap.resize(size-1);
        }

        friend std::ostream& operator<<(std::ostream &out, const MinHeap<T> &min_heap) {
            int size = min_heap.size();
	        for (int i = 1; i < size; ++i) {
		        out << min_heap[i] << ' ';
	        }
            out << std::endl;

	        return out;
        }
};
