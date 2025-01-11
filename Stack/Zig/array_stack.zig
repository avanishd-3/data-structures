const std = @import("std");
const ArrayList = std.ArrayList;
const expect = std.testing.expect;

fn ArrayStack(comptime T: type) type {
    return struct {
        stack: ArrayList(T),
        size: usize = 0,
        const Self = @This();

        pub fn init(allocator: std.mem.Allocator) Self {
            const stack = ArrayList(T).init(allocator);
            return Self{ .stack = stack };
        }

        pub fn deinit(self: *Self) void {
            self.stack.deinit();
        }

        pub fn empty(self: *Self) bool {
            return self.size == 0;
        }

        pub fn push(self: *Self, value: T) !void {
            try self.stack.append(value);
            self.size += 1;
        }

        pub fn top(self: *Self) !T {
            if (self.size == 0) {
                return error.StackEmptyException;
            }
            return self.stack.items[self.size - 1];
        }

        pub fn pop(self: *Self) !void {
            if (self.size == 0) {
                return error.StackEmptyException;
            }
            _ = self.stack.pop();
            self.size -= 1;
        }
    };
}

test "Length of empty stack is 0" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const IntStack = ArrayStack(i64);

    var stack = IntStack.init(gpa.allocator());
    defer stack.deinit();

    try expect(stack.size == 0);
}

test "Empty stack is empty" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const IntStack = ArrayStack(i64);

    var stack = IntStack.init(gpa.allocator());
    defer stack.deinit();

    try expect(stack.empty());
}

test "Top equals element after 1 insertion" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const IntStack = ArrayStack(i64);

    var stack = IntStack.init(gpa.allocator());
    defer stack.deinit();

    try stack.push(5);
    try expect(try stack.top() == 5);
}

test "Length of stack after 1 insertion is 1" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const IntStack = ArrayStack(i64);

    var stack = IntStack.init(gpa.allocator());
    defer stack.deinit();

    try stack.push(5);
    try expect(stack.size == 1);
}

test "Stack is not empty after 1 insertion" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const IntStack = ArrayStack(i64);

    var stack = IntStack.init(gpa.allocator());
    defer stack.deinit();

    try stack.push(5);
    try expect(!stack.empty());
}

test "Top equals 2nd element after 2 insertions" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const IntStack = ArrayStack(i64);

    var stack = IntStack.init(gpa.allocator());
    defer stack.deinit();

    try stack.push(5);
    try stack.push(3);
    try expect(try stack.top() == 3);
}

test "Top equals 1st element after 2 insertions and 1 pop" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const IntStack = ArrayStack(i64);

    var stack = IntStack.init(gpa.allocator());
    defer stack.deinit();

    try stack.push(5);
    try stack.push(3);
    _ = try stack.pop();
    try expect(try stack.top() == 5);
}

test "Calling top when stack is empty should return stack empty exception" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const IntStack = ArrayStack(i64);

    var stack = IntStack.init(gpa.allocator());
    defer stack.deinit();

    try expect(stack.top() == error.StackEmptyException);
}

test "Calling pop when stack is empty should return stack empty exception" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const IntStack = ArrayStack(i64);

    var stack = IntStack.init(gpa.allocator());
    defer stack.deinit();

    try expect(stack.pop() == error.StackEmptyException);
}
