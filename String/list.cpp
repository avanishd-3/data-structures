#include <iostream>
#include "list.hpp"

// Return a linked list from a c-string s

list::Node* list::from_string(const char *s) {

	return *s == 0 ? nullptr : new Node{*s, list::from_string(s+1)};
	// Infinite recursion if original pointer is advanced
	// Give next memory address instead -> ensure substring of s
}

// Delete all nodes of a linked list

void list::free(Node *head) {
	for(Node *p = head; p!= nullptr;) {
		Node *temp = p;
		p = p->next;
		delete temp;
	}
}

// Print linked list to ostream out

void list::print(std::ostream& out, Node *head) {
	for(Node *p = head; p!= nullptr; p = p->next) {
		out << p->data;
	}
}

// Return duplicate of linked list starting at head

list::Node* list::copy(Node *head) {
	return (head == nullptr) ? nullptr : new Node{head->data, list::copy(head->next)};
}

// Strcmp for lists

int list::compare(list::Node *lhs, list::Node *rhs) {
	int left_length = list::length(lhs);
	
	Node *left = lhs;
	Node *right = rhs;

	if (lhs == nullptr && rhs != nullptr) {
		return -1;
	}

	if (lhs != nullptr && rhs == nullptr) {
		return 1;
	}

	for(int i = 0; i < left_length && lhs != nullptr && rhs != nullptr; ++i, left=left->next, right=right->next) {

		if(left->data != right->data) {	
			return left->data - right->data;
		}

		if (left->next == nullptr && right->next != nullptr) {
			return '\0' - right->data;
		}

		if (right->next == nullptr && left->next != nullptr) {
			return left->data - '\0';
		}

		if(left->next == nullptr && right->next == nullptr) {
			return 0;
		}


	}
	return 0;
}

// Strncmp for lists

int list::compare(list::Node *lhs, list::Node *rhs, int n) {

	Node *left = lhs;
	Node *right = rhs;

	if (lhs == nullptr && rhs != nullptr && n > 0) {
		return -1;
	}

	if (lhs != nullptr && rhs == nullptr && n > 0) {
		return 1;
	}


	for(int i = 0; i < n && lhs != nullptr && rhs != nullptr; ++i, left=left->next, right=right->next) {

		if(left->data != right->data) {	
			return left->data - right->data;
		}

		if (left->next == nullptr && right->next != nullptr) {
			if (++i >= n) {
				return left->data - right->data;
			}

			else {
				return '\0' - right->data;
			}
		}

		if (right->next == nullptr && left->next != nullptr) {
			if (++i >= n) {
				return left->data - right->data;
			}

			else {
				return left->data - '\0';
			}
		}

		if(left->next == nullptr && right->next == nullptr) {
			return 0;
		}
	}
	return 0;
}



// Counts number of nodes in linked list

int list::length(Node *head) {
	int len{0};

	for(Node *p = head; p!= nullptr; p=p->next) {
		++len;
	}

	return len;
}

// Return reverse copy of linked list

list::Node* list::reverse(Node *head) {
	Node *p = head; // Pointer to traverse original list
	
	Node *reverse_head = nullptr; // Return this
	
	for(; p!= nullptr; p=p->next) {
		reverse_head = new Node{p->data, reverse_head};
	}

	return reverse_head;
}

// Return new list containing all nodes of lhs followed by all nodes of rhs

list::Node* list::append(Node *lhs, Node *rhs) {

	Node *right_hand_side = list::copy(rhs);

	if(lhs == nullptr) {
		return right_hand_side;
	}

	Node *p = lhs;

	Node *new_list_head = new Node{p->data, p->next}; // Do not move
	p=p->next; // Already put in 1st time
	
	Node *new_list = new_list_head;
	
	for (; p!= nullptr; p=p->next) {
		new_list->next = new Node{p->data, p->next};
		new_list = new_list->next;
	}

	new_list->next = right_hand_side;

	return new_list_head;
}

// Get last node of linked list

list::Node* list::last(Node *head) {
	for(Node *p = head; p!= nullptr; p=p->next) {
		if(p->next == nullptr) {
			return p;
		}	
	}

	return head;
}

// Return index of node in list starting at head

int list::index(Node *head, Node *node) {
	int count{0};

	if (node == nullptr) {
		return -1;
	}

	for (Node *p = head; p!= nullptr; p=p->next) {
		if (p->data == node->data && p->next == node->next) {
			return count;
		}

		else {
			++count;
		}
	}

	return -1;
}

// Strchr for a linked list

list::Node* list::find_char(Node *head, char c) {
	
	for(Node *p = head; p!= nullptr; p=p->next) {
		if (p->data == c) {
			return p;
		}
	}

	return nullptr;
}

// Strstr for linked list

list::Node* list::find_list(Node *haystack, Node *needle) {
	int len = list::length(needle);

	Node *p = haystack;

	if (len == 0)  {
		return p;
	}

	for(; (p = find_char(p, needle->data)) && p!= nullptr; p=p->next) {
		if(list::compare(p, needle, len) == 0) {
			return p;
		}
	}

	return nullptr;	
}

// Get nth node of linked list

list::Node* list::nth(Node *head, int n) {

	int i{0};
	Node *p = head;
	
	for(; p!= nullptr && i < n; p=p->next) {
		++i;
	}

	return p;
}