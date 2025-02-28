#include <utility>
#include <iostream>
#include <string>

// Template class for PriorityQueue
template <class T> 
class PriorityQueue {

    private:
        unsigned int queue_size = 1;                             // Initial size of the queue
        unsigned int elements_in_queue = 0;                      // Current number of elements in the queue
        std::pair<int, T> *queue_arr;                             // Pointer to the array holding queue elements (priority, element)

    public:
        
        // Default constructor
        PriorityQueue() {                                         
            queue_arr = new std::pair<int, T>[queue_size];        // Initialize queue with the default size
        }

        // Constructor with custom size
        PriorityQueue(unsigned int in_size) {                    
            queue_size = in_size;                                 
            queue_arr = new std::pair<int, T>[queue_size];        // Initialize queue with the given size
        }

        // Destructor to clean up dynamically allocated memory
        ~PriorityQueue() {                                      
            delete[] queue_arr;
            queue_arr = nullptr;
        }

        // Function to double the size of the queue when it is full
        void make_queue_grow(std::pair<int, T>* &queue) {
            // Create a temporary array with double the size of the current queue
            std::pair<int, T> *temp_arr = new std::pair<int,T>[queue_size * 2];

            // Copy current elements into the new array
            for(int i = 0; i < elements_in_queue; i++) {
                temp_arr[i] = queue[i];
            }

            queue_size *= 2;  // Double the size of the queue

            // Delete the old queue and point to the new array
            delete[] queue;
            queue = temp_arr;
            temp_arr = nullptr;
        }

        // Function to enqueue an element with a priority
        void enqueueWithPriority(int priority, T element) {
            int index = 0;  

            // If the queue is full, grow the queue
            if(elements_in_queue == queue_size) {
                make_queue_grow(queue_arr);
            }

            // If the priority is 1, insert at the correct position to maintain priority
            if(priority == 1) {
                std::pair<int, T> *temp_arr = new std::pair<int, T>[queue_size];  

                // Shift elements with priority 1 to the right to make room for the new element
                while(queue_arr[index].first == 1 && index < elements_in_queue) {
                    temp_arr[index] = queue_arr[index];
                    index++;
                }

                // Insert the new element with priority 1
                temp_arr[index] = std::make_pair(priority, element);    
                elements_in_queue++;
                index++;

                // Move the rest of the elements after the new element
                while(index < elements_in_queue) {
                    temp_arr[index] = queue_arr[index - 1];
                    index++;
                }

                // Delete old array and point to the newly created array
                delete[] queue_arr;
                queue_arr = temp_arr;               
                temp_arr = nullptr;                 
            }
            // If the priority is 0, just add the element at the end
            else if(priority == 0) {
                queue_arr[elements_in_queue] = std::make_pair(priority, element);     
                elements_in_queue++;
            }
            // If the priority is invalid, display an error
            else {
                std::cerr << "Invalid priority. Entered priority: " << priority << ". Acceptable priorities are 0 and 1. Element was not added to the queue.\n";
            }
        }           

        // Function to dequeue (remove) the highest priority element
        void dequeue() {
            if (isEmpty()) {
                throw std::runtime_error("Cannot dequeue from an empty queue."); // Error if the queue is empty
            }

            std::pair<int, T> *temp_arr = new std::pair<int, T>[queue_size];
            
            elements_in_queue--;  // Decrease the number of elements in the queue

            // Shift elements left to fill the removed spot
            for(int i = 0; i < elements_in_queue; i++) {
                temp_arr[i] = queue_arr[i + 1];
            }

            // Delete old array and point to the new array
            delete[] queue_arr;
            queue_arr = temp_arr;
            temp_arr = nullptr;  
        }

        // Function to print all the elements in the queue
        void print() {  
            if(elements_in_queue == 0)
                std::cout << "Queue is empty!\n";
            else {
                for(int i = 0; i < elements_in_queue; i++) {
                    std::cout << queue_arr[i].second << "\n";  // Print each element
                }
                std::cout << std::endl;
            }
        }
 
        // Function to peek at the most prioritized element (without removing it)
        void peek() {          
            if (isEmpty()) {
                throw std::runtime_error("Cannot peek at an empty queue."); // Error if the queue is empty
            }
            else {
                T most_prioritized = queue_arr[0].second;
                std::cout << "Most prioritized: " << most_prioritized << "\n";  // Display the highest priority element
            }
        }
    
        // Function to get the current size of the queue
        unsigned int get_size() {
            return elements_in_queue;
        }
        
        // Function to check if the queue is empty
        bool isEmpty() {
            if(elements_in_queue == 0)                    
                return true;
            else
                return false;
        }
};
