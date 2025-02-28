#include <utility>
#include <iostream>
#include <string>

/**
 * @brief Template class for a Priority Queue.
 * A priority queue stores elements with associated priorities and ensures that elements
 * with higher priority are dequeued first.
 * 
 * @tparam T The type of elements stored in the queue.
 */
template <class T> 
class PriorityQueue {

    private:
        unsigned int queue_size = 1;                             ///< The initial size of the queue.
        unsigned int elements_in_queue = 0;                      ///< The number of elements currently in the queue.
        std::pair<int, T> *queue_arr;                             ///< Pointer to the array holding elements, stored as pairs (priority, element).

    public:

        /**
         * @brief Default constructor that initializes the priority queue with default size.
         * Initializes an empty queue with a size of 1.
         */
        PriorityQueue() {                                         
            queue_arr = new std::pair<int, T>[queue_size];        ///< Initializes queue with default size of 1.
        }

        /**
         * @brief Constructor that allows specifying the initial size of the queue.
         * 
         * @param in_size The initial size of the queue.
         */
        PriorityQueue(unsigned int in_size) {                    
            queue_size = in_size;                                 
            queue_arr = new std::pair<int, T>[queue_size];        ///< Initializes queue with the provided size.
        }

        /**
         * @brief Destructor that cleans up the dynamically allocated memory.
         * Frees the memory used by the queue.
         */
        ~PriorityQueue() {                                      
            delete[] queue_arr;                                  ///< Frees the allocated memory for the queue array.
            queue_arr = nullptr;
        }

        /**
         * @brief Resizes the queue array when it is full.
         * Doubles the size of the queue when it reaches full capacity.
         * 
         * @param queue Reference to the queue array to resize.
         */
        void make_queue_grow(std::pair<int, T>* &queue) {
            std::pair<int, T> *temp_arr = new std::pair<int,T>[queue_size * 2];  ///< Creates a new array with double the size.

            for(int i = 0; i < elements_in_queue; i++) {
                temp_arr[i] = queue[i];  ///< Copies existing elements to the new array.
            }

            queue_size *= 2;  ///< Doubles the size of the queue.

            delete[] queue;   ///< Deletes the old queue.
            queue = temp_arr; ///< Points to the new array.
            temp_arr = nullptr;
        }

        /**
         * @brief Adds an element with a specified priority to the queue.
         * The element is inserted in such a way that elements with higher priority are dequeued first.
         * If the queue is full, it is resized.
         * 
         * @param priority The priority of the element (0 or 1).
         * @param element The element to add to the queue.
         */
        void enqueueWithPriority(int priority, T element) {
            int index = 0;  

            if(elements_in_queue == queue_size) {  ///< Checks if the queue is full and needs resizing.
                make_queue_grow(queue_arr);
            }

            if(priority == 1) {  ///< If the priority is 1, we insert the element before other priority 1 elements.
                std::pair<int, T> *temp_arr = new std::pair<int, T>[queue_size];  

                while(queue_arr[index].first == 1 && index < elements_in_queue) { 
                    temp_arr[index] = queue_arr[index];
                    index++;
                }

                temp_arr[index] = std::make_pair(priority, element);    
                elements_in_queue++;
                index++;

                while(index < elements_in_queue) {
                    temp_arr[index] = queue_arr[index - 1];
                    index++;
                }

                delete[] queue_arr;                
                queue_arr = temp_arr;               
                temp_arr = nullptr;                 
            }
            else if(priority == 0) {  ///< If the priority is 0, we simply append the element to the end.
                queue_arr[elements_in_queue] = std::make_pair(priority, element);     
                elements_in_queue++;
            }
            else {
                std::cerr << "Invalid priority. Entered priority: " << priority << ". Acceptable priorities are 0 and 1. Element was not added to the queue.\n";
            }
        }

        /**
         * @brief Removes the highest priority element from the queue.
         * Shifts the remaining elements to fill the empty spot.
         * Throws an error if the queue is empty.
         */
        void dequeue() {
            if (isEmpty()) {  ///< Checks if the queue is empty before dequeuing.
                throw std::runtime_error("Cannot dequeue from an empty queue."); 
            }

            std::pair<int, T> *temp_arr = new std::pair<int, T>[queue_size];

            elements_in_queue--;  ///< Decreases the number of elements in the queue.

            for(int i = 0; i < elements_in_queue; i++) {
                temp_arr[i] = queue_arr[i + 1];  ///< Shifts the elements to fill the gap left by the removed element.
            }

            delete[] queue_arr;
            queue_arr = temp_arr;  ///< Points to the new array.
            temp_arr = nullptr;  
        }

        /**
         * @brief Prints all the elements currently in the queue.
         * If the queue is empty, it prints a message indicating so.
         */
        void print() {  
            if(elements_in_queue == 0) {
                std::cout << "Queue is empty!\n";  ///< Prints message if the queue is empty.
            } else {
                for(int i = 0; i < elements_in_queue; i++) {
                    std::cout << queue_arr[i].second << "\n";  ///< Prints each element in the queue.
                }
                std::cout << std::endl;
            }
        }

        /**
         * @brief Displays the highest priority element in the queue without removing it.
         * Throws an error if the queue is empty.
         */
        void peek() {          
            if (isEmpty()) {  ///< Checks if the queue is empty before peeking.
                throw std::runtime_error("Cannot peek at an empty queue.");
            } else {
                T most_prioritized = queue_arr[0].second;
                std::cout << "Most prioritized: " << most_prioritized << "\n";  ///< Prints the highest priority element.
            }
        }

        /**
         * @brief Returns the current number of elements in the queue.
         * 
         * @return The number of elements in the queue.
         */
        unsigned int get_size() {
            return elements_in_queue;  ///< Returns the current size of the queue.
        }

        /**
         * @brief Checks if the queue is empty.
         * 
         * @return True if the queue is empty, otherwise false.
         */
        bool isEmpty() {
            return elements_in_queue == 0;  ///< Returns true if there are no elements in the queue.
        }
};
