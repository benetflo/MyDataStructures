# Data Structures in C++

# 1. Dynamic Array (B_dynamic_arr)
A dynamic array that automatically resizes when full. You can add elements to the front or back, check for element presence, and remove specific elements.
Limitation:

Adding to the front is inefficient as it requires shifting all existing elements, which can make this operation slow.
The array doubles in size each time it's full, which can cause memory overhead if many elements are added.

# 2. Priority Queue
A priority queue that stores elements with priorities, where higher priorities are dequeued first.
Limitation:

The queue currently only supports two priority levels (0 and 1), which limits its flexibility for more complex use cases.
When the queue is full, resizing it requires copying all elements, which can be costly for large queues.
Inserting elements with priority 1 can lead to inefficient shifting of elements in the queue.
