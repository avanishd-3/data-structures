#include <iostream>
#include <utility> // For std::swap
#include <sstream>  // For std::stringstream

#include "string.hpp"
#include "list.hpp"

// Copy construction from a C string

String::String(const char *s) // Default is empty string
	: head{list::from_string(s)}
{
}

// Copy construction from a String

String::String(const String &s)
	: head{list::copy(s.head)}
{
}

// Move construction from a String

String::String(String &&s)
	: head{s.head}
{
	s.head = nullptr;
}

// Private constructor for reverse() and +

String::String(list::Node* head)
	: head{head}
{
}
// Swap pointers

void String::swap(String &s) {
	std::swap(head, s.head);
}

// Copy assignment

String& String::operator=(const String &s) {
	String temp_str(s);
	String::swap(temp_str);

	// Destructor for temp_str automatically called after function ends
	
	return *this;
}

// Move assignment

String& String::operator=(String &&s) {
	list::free(head);
	String::swap(s);

	s.head = nullptr;

	// Destructor for s automatically called after function ends
	
	return *this;
}


// Destructor

String::~String() {
	list::free(head);
}

// Printing

void String::print(std::ostream &out) const {
	list::print(out, head);
}

std::ostream &operator<<(std::ostream &out, const String &s) {
	s.print(out);
	return out;
}

// Reading

void String::read(std::istream &in) {
	// Initial set-up	
	char c;
	in.get(c);

	if (!std::isspace(static_cast<unsigned char>(c))) {
		list::free(head);
		head = new list::Node{c, nullptr}; // Do not move
		list::Node *input_str = head;

		while (in.get(c) && !std::isspace(static_cast<unsigned char>(c))) { //Make sure isspace is defined for all c
			input_str->next = new list::Node{c, nullptr};
			input_str = input_str->next;
		}
	}
}

std::istream& operator>>(std::istream &in, String &s) {
	s.read(in);
	return in;
}

// Size
int String::size() const {
	return list::length(head); 
}

// Reverse

String String::reverse() const {
	return String(list::reverse(head));
}

// Const Indexing

bool String::in_bounds(int index) const {
	return index >= 0 && index < list::length(head);
}

char String::operator[](int index) const {
	if (in_bounds(index)) {
		return list::nth(head, index)->data;
	}

	else {
		std::cout << "ERROR: Index Out Of Bounds" << std::endl;
		char return_char = '\0';

		return return_char;
	}
}

// Index of sub-chars and substrs

int String::indexOf(const char c) const {
	list::Node *node = list::find_char(head, c);
	return list::index(head, node);
}

int String::indexOf(const String &s) const {
	if (s.head == nullptr) {
		return 0;
	}

	list::Node *node = list::find_list(head, s.head);
	return list::index(head, node);	
}

// Concatenation

String String::operator+(const String &s) const {
	return String(list::append(head, s.head));
}

String& String::operator+=(const String &s) {	
	list::Node *left_tail = list::last(head);
	list::Node *rhs = list::copy(s.head);

	if (left_tail != nullptr) {
		left_tail->next = rhs;
	}

	else {
		std::swap(head, rhs);
	}

	return *this;
}

// Relational operators

bool String::operator==(const String &s) const {
	return (list::compare(head, s.head) == 0);
}

std::strong_ordering String::operator<=>(const String &s) const {
	return list::compare(head, s.head) <=> 0;
}