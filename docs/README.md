# C++ Programming

**Sequence Containers:**
Sequence containers in C++ are a type of container that organize elements in a strict linear sequence, where each element is positioned at a specific point. The standard template library (STL) provides several types of sequence containers, each with its own unique characteristics and uses. Here are the primary sequence containers in C++:

| Container         | Description                                                  | Best Use Case                                                |
| ----------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| std::array        | Fixed-size container that stores elements contiguously with a size known at compile time. | When the size of the array is known at compile time and fixed. |
| std::vector       | Dynamic array that can resize automatically, providing fast access to elements and efficient addition/removal. | For dynamic arrays where size may change frequently and random access is required. |
| std::deque        | Double-ended queue that allows fast insertion and deletion at both the beginning and the end. | When insertion and deletion at both ends of the container is needed. |
| std::forward_list | Singly linked list that supports fast insertion and deletion from the front, optimized for memory efficiency. | When memory efficiency is a concern and only forward traversal is needed. |
| std::list         | Doubly linked list that allows fast insertion and deletion from anywhere in the container. | When frequent insertion and deletion at any position is required. |



**Associative Containers:**
Associative containers in C++ store elements formed by a combination of a key value and a mapped value, and are typically implemented as balanced binary trees. Here are the primary associative containers in C++:

| Container     | Description                                                  | Best Use Case                                                |
| ------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| std::set      | Container that stores unique elements in a specific order.   | When you need a sorted set of unique keys.                   |
| std::multiset | Similar to std::set but allows duplicate elements.           | When you need a sorted set of keys that may contain duplicates. |
| std::map      | Associates unique keys with corresponding values, stored in a specific order. | For storing key-value pairs with sorted keys and efficient lookup. |
| std::multimap | Similar to std::map but allows multiple elements with the same key. | When you need a sorted set of key-value pairs that may contain duplicates. |



**Unordered Associative Containers:**
Unordered associative containers in C++ use hash tables to store elements, providing fast access regardless of the order. Here are the primary unordered associative containers in C++:

| Container               | Description                                                  | Best Use Case                                                |
| ----------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| std::unordered_set      | Container that stores unique elements in an unordered manner, using hash tables for fast access. | When you need an unordered set of unique keys.               |
| std::unordered_multiset | Similar to std::unordered_set but allows duplicate elements. | When you need an unordered set of keys that may contain duplicates. |
| std::unordered_map      | Associates unique keys with corresponding values in an unordered manner, using hash tables for fast access. | For storing key-value pairs with unordered keys and efficient lookup. |
| std::unordered_multimap | Similar to std::unordered_map but allows multiple elements with the same key. | When you need an unordered set of key-value pairs that may contain duplicates. |



**Container Adaptors:**
Container adaptors provide a different interface for sequential containers, modifying their behavior. Here are the primary container adaptors in C++:

| Container           | Description                                                  | Best Use Case                                                |
| ------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| std::stack          | LIFO (Last-In-First-Out) stack, typically implemented as an adapter over other containers like `std::deque`. | When you need Last-In-First-Out (LIFO) behavior, such as in a depth-first search algorithm. |
| std::queue          | FIFO (First-In-First-Out) queue, typically implemented as an adapter over other containers like `std::deque`. | For First-In-First-Out (FIFO) behavior, like in breadth-first search algorithms or job scheduling. |
| std::priority_queue | A priority queue that maintains elements in a heap, ensuring that the highest priority element is always accessible. | When elements need to be processed in order of priority, such as in Dijkstra's algorithm. |



**Tuple:**
Tuples provide a way to store a fixed-size collection of heterogeneous values. Here is the primary tuple container in C++:

| Container  | Description                                                  | Best Use Case                                                |
| ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| std::tuple | Fixed-size collection of heterogeneous values, allowing multiple values to be returned from a function. | When you need to store a fixed-size collection of heterogeneous values, such as in returning multiple values from a function. |



**Span:**
Span provides a view over a contiguous sequence of elements, such as arrays or other containers. Here is the primary span container in C++:

| Container | Description                                                  | Best Use Case                                                |
| --------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| std::span | A view over a contiguous sequence of objects, providing a safe and efficient way to work with subranges. | When you need a view over a contiguous sequence of objects, providing a safe and efficient way to work with subranges of arrays or other containers. |