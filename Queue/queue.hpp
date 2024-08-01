#include <utility> // For std::swap
#include <vector>

template<typename T>
class Queue { // Circular queue to re-use empty spaces from deletion
    private:
        T *buf;
        int size;
        int front;
        int rear;

    public:
        Queue(int i)
            : buf(new T[i])
            , size(i)
            , front(0)
            , rear(0)
        {
        }
        ~Queue() {
            delete[] buf;
        }

        bool isEmpty() {
            return front == rear;
        }

        bool isFull() {
            return (rear + 1) % size == front;
        }

        void enqueue(T data) {
            if (isFull()) {
                throw std::out_of_range("Queue is full");
            }
            else {
                rear = (rear + 1) % size;
                buf[rear] = data;
            }
        }

        void dequeue() {
            if (isEmpty()) {
                throw std::invalid_argument("Stack is empty");
            }
            else {
                front = (front + 1) % size;
            }
        }

        T first() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                return buf[front];
            }
        }

        T last() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                return buf[rear];
            }
        }

        T peek(int index) {
            if (index < 0 || index > top) {
                throw std::invalid_argument("Invalid index");
            }
            else {
                return buf[front + index - 1];
            }
        }
};


template <typename T>
class LLQueue {
    private:
        struct Node {
            T data;
            Node *next;
        };

    Node *front;
    Node *rear;
    int len;

    public:
        LLQueue()
            : front(nullptr)
            , rear(nullptr)
            , len(0)
        {
        }

        ~LLQueue() {
            for (Node *p = front; p != nullptr;) {
                Node *temp = p;
                p=p->next;
                delete temp;
            }
        }

        int size() {
            return len;
        }

        bool isEmpty() {
            return front == nullptr;
        }

        void enqueue(T data) {
            if (front == nullptr) {
                front = rear = new Node(data, nullptr);
            }
            else {
                rear->next = new Node(data, nullptr);
                rear = rear->next;
            }
            ++len;
        }

        void dequeue() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                Node *temp = front;
                front = front->next;
                delete temp;
                --len;
            }
        }

        T first() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                return front->data;
            }
        }

        T last() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                return rear->data;
            }
        }
};

template<typename T>
class Deque { // Circular queue to re-use empty spaces from deletion
    private:
        T *buf;
        int size;
        int front;
        int rear;

    public:
        Deque(int i)
            : buf(new T[i])
            , size(i)
            , front(-1)
            , rear(-1)
        {
        }
        ~Deque() {
            delete[] buf;
        }

        bool isEmpty() {
            return front == rear;
        }

        bool isFull() {
            return (rear + 1) % size == front;
        }

        void push_front(T data) {
            if (isFull()) {
                throw std::out_of_range("Queue is full");
            }
            else {
                front = (front + 1) % size;
                buf[front] = data;
            }

        }

        void push_back(T data) {
            if (isFull()) {
                throw std::out_of_range("Queue is full");
            }
            else {
                rear = (rear + 1) % size;
                buf[rear] = data;
            }
        }

        void pop_front() {
            if (isEmpty()) {
                throw std::invalid_argument("Stack is empty");
            }
            else {
                front = (front + 1) % size;
            }
        }

        void pop_back() {
            if (isEmpty()) {
                throw std::invalid_argument("Stack is empty");
            }
            else {
                rear = (rear + 1) % size;
            }
        }

        T first() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                return buf[front];
            }
        }

        T last() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                return buf[rear];
            }
        }

        T peek(int index) {
            if (index < 0 || index > top) {
                throw std::invalid_argument("Invalid index");
            }
            else {
                return buf[front + index - 1];
            }
        }
};

template <typename T>
class LLDeque {
    private:
        struct Node {
            T data;
            Node *prev;
            Node *next;
        };

    Node *front;
    Node *rear;
    int len;

    public:
        LLDeque()
            : front(nullptr, nullptr)
            , rear(nullptr, nullptr)
            , len(0)
        {
        }

        ~LLDeque() {
            for (Node *p = front; p != nullptr;) {
                Node *temp = p;
                p=p->next;
                delete temp;
            }
        }

        int size() {
            return len;
        }

        bool isEmpty() {
            return front == nullptr;
        }

        void push_back(T data) {
            if (front == nullptr) {
                front = rear = new Node(data, nullptr, nullptr);
            }
            else {
                rear->next = new Node(data, rear, nullptr);
                rear = rear->next;
            }
            ++len;
        }

         void push_front(T data) {
            if (front == nullptr) {
                front = rear = new Node(data, nullptr, nullptr);
            }
            else {
                if (front->next) {
                    front->next = new Node(data, front, front->next->next);
                }
                else {
                    front->next = new Ndoe(data, front, nullptr);
                }
            }
            ++len;
        }

        void pop_front() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                Node *temp = front;
                front = front->next;
                delete temp;
                --len;
            }
        }

        void pop_back() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                Node *temp = rear;
                rear = rear->prev;
                delete temp;
                --len;
            }
        }

        T first() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                return front->data;
            }
        }

        T last() {
            if (isEmpty()) {
                throw std::invalid_argument("Queue is empty");
            }
            else {
                return rear->data;
            }
        }
};

template <typename T>
class PriorityQueue { // Smaller value is higher priority
    private:
        std::vector<T> data;

    public:
        PriorityQueue()
            : len{0}
        {
        }

        bool isEmpty() {
            return data.size() == 0;
        }

        T top() {
            return data[0];
        }

        int len() {
            return data.size();
        }

        void insert(T elem) {
            data.push_back(elem);
            std::sort(data.begin(), data.end(), greater<int>()); // Sort in descending order
        }

        void pop() {
            data.pop_back();
        }
};