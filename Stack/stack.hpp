#include <utility> // For std::swap

template<typename T>
class Stack {
    private:
        T *buf;
        int size;
        int top;

    public:
        Stack(int i)
            : buf(new T[i])
            , size(i)
            , top(0)
        {
        }
        ~Stack() {
            delete[] buf;
        }

        bool isEmpty() {
            return top <= 0;
        }

        bool isFull() {
            return top == size;
        }

        void push(T data) {
            if (isFull()) {
                throw std::out_of_range("Stack is full");
            }
            else {
                buf[top++] = data;
            }
        }

        void pop() {
            if (isEmpty()) {
                throw std::invalid_argument("Stack is empty");
            }
            else {
                --top;
            }
        }

        T peek(int index) {
            if (index < 0 || index > top) {
                throw std::invalid_argument("Invalid index");
            }
            else {
                int buf_index = top - index - 1;
                return buf[buf_index];
            }
        }

        T stackTop() {
            return buf[top - 1];
        }
};

template<typename T>
class LLStack {
    private:

        struct Node {
            T data;
            Node *next;
        };

        class StackEmptyException : public std::exception {
            public:
                char* what() {
                    retur "Stack is empty";
                }

        };

        Node *head;
        std::size_t len;

    public:
        LLStack()
            : head(nullptr)
            , len(0)
        {
        }

        LLStack(const LLStack & st) { // Copy constructor
            if (st.head == nullptr) {
                head = nullptr;
                len = 0;
            }

            else {
                head = new Node(head->data, nullptr);
                for (Node *p = head->next; p != nullptr; p=p->next) {
                    head->next = new Node(p->data, nullptr);
                }
                len = st.len;
            }
        }

        LLStack& operator=(const LLStack &st) { // Copy assignment
            LLStack<T> temp(st);

            std::swap(head, st.head);
            std::swap(len, st.len);

            // Destructor for st automatically called
            
            return *this;
        }

        ~LLStack() { // Destructor
            for (Node *p = head; p != nullptr;) {
                Node *temp = p;
                p=p->next;
                delete temp;
            }
        }

        std::size_t size() const noexcept {
            return len;
        }

        bool isEmpty() const noexcept {
            return head == nullptr;
        }

        T& top() {
            return head->data;
        }

        const T& top() const {
            return head->data;
        }

        void push(const T &elem) noexcept {
            if (head == nullptr) {
                head = new Node(elem, nullptr);
                ++len;
            }
            else {
               Node *t = new Node(elem, head);
               head = t;
               ++len;
            }
        }

        void pop() {
            if (isEmpty()) {
                throw StackEmptyException;
            }
            else {
                Node *temp = head;
                head = head->next;
                delete temp;
                --len;
            }
        }
};

