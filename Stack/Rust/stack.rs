use std::fmt;

// Errors for Stack

struct StackEmptyError;

impl fmt::Display for StackEmptyError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Stack is empty")
    }
}

impl fmt::Debug for StackEmptyError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{{ file: {}, line: {} }}", file!(), line!())
    }
}


struct Stack<T> {
    stack: Vec<T>,
    size: usize,
}


impl<T> Stack<T> {
    fn new() -> Self {
        return Stack { stack: Vec::new(), size: 0 };
    }

    fn top (&self) -> Option<&T> {
        return self.stack.last();
    }

    fn empty(&self) -> bool {
        return self.size == 0;
    }

    fn push(&mut self, element: T) {
        self.stack.push(element);
        self.size += 1;
    }

    fn pop(&mut self) -> Result<Option<T>, StackEmptyError>{
        if self.size == 0 {
            return Err(StackEmptyError);
        }
        else {
            self.size -= 1;
            return Ok(self.stack.pop());

        }
    }

}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn length_of_empty_stack_is_zero() {
        let stack: Stack<isize> = Stack::new();
        assert_eq!(stack.size, 0);
    }

    #[test]
    fn new_stack_is_empty() {
        let stack: Stack<isize> = Stack::new();
        assert_eq!(stack.empty(), true);
    }

    #[test]
    fn top_equals_element_after_one_insertion() {
        let mut stack: Stack<isize> = Stack::new();
        stack.push(5);
        assert_eq!(stack.top(), Some(&5));
    }

    #[test]
    fn stack_is_not_empty_after_one_insertion() {
        let mut stack: Stack<isize> = Stack::new();
        stack.push(5);
        assert_eq!(stack.empty(), false);
    }

    #[test]
    fn stack_has_size_one_after_one_insertion() {
        let mut stack: Stack<isize> = Stack::new();
        stack.push(5);
        assert_eq!(stack.size, 1);
    }

    #[test]
    fn top_equals_second_element_after_two_insertions() {
        let mut stack: Stack<isize> = Stack::new();
        stack.push(5);
        stack.push(3);
        assert_eq!(stack.top(), Some(&3));
    }

    #[test]
    fn top_equals_first_element_after_two_insertions_and_one_pop() {
        let mut stack: Stack<isize> = Stack::new();
        stack.push(5);
        stack.push(3);
        let _ = stack.pop();
        assert_eq!(stack.top(), Some(&5));
    }

    #[test]
    fn stack_has_size_one_after_two_insertions_and_one_pop() {
        let mut stack: Stack<isize> = Stack::new();
        stack.push(5);
        stack.push(3);
        let _ = stack.pop();
        assert_eq!(stack.size, 1);
    }

    #[test]
    fn empty_call_to_pop_returns_error() {
        let mut stack: Stack<isize> = Stack::new();
        let result = stack.pop();
        assert_eq!(result.is_err(), true);
    }

    #[test]
    fn top_on_empty_stack_returns_none() {
        let stack: Stack<isize> = Stack::new();
        assert_eq!(stack.top(), None);
    }
}
