#ifndef SET_HPP
#define SET_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

template <typename T>
class Set {
	struct ListNode {
		T data;
		std::shared_ptr<ListNode> next;
	};

	public:
		class ListIterator {
			public:
				using iterator_category = std::forward_iterator_tag;
				using value_type = T;
				using difference_type = std::ptrdiff_t;
				using pointer = T*;
				using reference = T&;

				explicit ListIterator(std::shared_ptr<ListNode> ptr = nullptr)
					: ptr{ptr}
				{	
				}

				ListIterator& operator++() {
					if (ptr) { // No nullptr
						ptr = ptr->next;
					}
					return *this;
				}

				ListIterator operator++(int) {
					ListIterator temp = *this;
					++temp;
					return temp;
				}

				T& operator*() const {
					return ptr->data;
				}

				T* operator->() const {
					return &(ptr->data);
				}
				bool operator==(const ListIterator &other) const = default;

			private:
				std::shared_ptr<ListNode> ptr;
		};

		using value_type = T;
		using iterator = ListIterator;
		// Normally there would be a const iterator too

		Set() = default;

		template<std::ranges::input_range Rng>
		explicit Set(Rng &&rng) {
			std::ranges::for_each(std::forward<Rng>(rng),std::bind_front(&Set::insert, this));
		}

		ListIterator begin() {
			return ListIterator(head);
		}
		ListIterator end() {
			return ListIterator();
		}
		bool contains(const T& value) {
			for (ListIterator val = begin(); val != end(); ++val) {
				if (value == *val) {
					return true;
				}
			}
			return false;
		}
		ListIterator insert(T value) {
			if (head) { // If not nullptr

				if (!contains(std::move(value))) { // No duplicates allowed
					head = std::make_shared<ListNode>(std::move(value), head);
				}
				

				return ListIterator(head);
			}

			else { // Head is nullptr
				head = std::make_shared<ListNode>(std::move(value), nullptr);
				return ListIterator(head);
				
			}
		}

	private:
		std::shared_ptr<ListNode> head = nullptr;	
};

#endif