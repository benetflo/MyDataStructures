#include <iostream>

template <class T> class B_dynamic_arr{

    private:
        unsigned int b_size = 1;
        unsigned int b_elements = 0;
        T *main_arr;
    
    public:

        B_dynamic_arr() {
            main_arr = new T[b_size];
        }
        B_dynamic_arr(unsigned int in_size){
            b_size = in_size;
            main_arr = new T[b_size];
        }
        ~B_dynamic_arr(){
            delete[] main_arr;
            main_arr = nullptr;
        }

        /**
         * @brief A method that adds an element to the end of the array. Array is resized if needed. New_size = current_size * 2.
         * 
         * @param element element to add to the back of the array.
         * 
         * @return no return value.
         */
        void add_back(T element){
            
            if(b_size >= b_elements){
                T *temp_arr = new T[b_size * 2];
                for(int i = 0; i < b_size; i++){
                    temp_arr[i] = main_arr[i];
                }
                b_size *= 2;
                temp_arr[b_elements] = element;
                b_elements++;
                delete [] main_arr;
                main_arr = temp_arr;
                temp_arr = nullptr;
            }
            else{
                main_arr[b_elements] = element;
                b_elements++;
            }
        }

        /**
         * @brief A method that adds an element to the beginning of the array. Array is resized if needed. New_size = current_size * 2.
         * 
         * Note: This method involves copying the entire array, making it inefficient for frequent use. 
         * Consider alternative data structures (e.g., linked lists) for scenarios requiring frequent 
         * insertions at the beginning.
         * 
         * @param element element to add to the beginning of the array.
         * 
         * @return no return value.
         */
        void add_front(T element){   
            
            if(b_size >= b_elements){
                T *temp_arr = new T[b_size * 2];
                for(int i = 0; i < b_size; i++){
                    temp_arr[i + 1] = main_arr[i];
                }
                b_size *= 2;
                temp_arr[0] = element;
                b_elements++;
                delete [] main_arr;
                main_arr = temp_arr;
                temp_arr = nullptr;            
            }
            else{
                T *temp_arr = new T[b_size];
                for(int i = 0; i < b_size; i++){
                    temp_arr[i + 1] = main_arr[i];
                }
                temp_arr[0] = element;
                b_elements++;
                delete [] main_arr;
                main_arr = temp_arr;
                temp_arr = nullptr;
            }
        }

        /**
         * @brief A method that checks if given element is present in the dynamic array.
         * 
         * @param element element to look for.
         * 
         * @return true(1) if element was found, else false(0).
         */
        bool is_present(T element){
            for(int i = 0; i < b_elements; i++){
                if(main_arr[i] == element){
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief A method that prints the dynamic array to the terminal, each element is seperated by spaces.
         * std::endl is included at the end.
         */
        void print(){
            for(int i = 0; i < b_elements; i++){
                std::cout << main_arr[i] << " ";
            }
            std::cout << std::endl;
        }

        /**
         * @brief A method that counts how many of the given element that are present in the array.
         *
         * @param element element to count.
         * 
         * @return count as int. 
         */
        int how_many_of(T element){
            int count = 0;
            for(int i = 0; i < b_elements; i++){
                if(main_arr[i] == element)
                    count++;
                else
                    continue;
            }
            return count;
        }

        /**
         * @brief A method that "removes" all existing elements in dynamic array that are equal to a given parameter. The remaining elements are shifted to fill the gaps, reducing the amount of elements present in the array. 
         * 
         * @param element element to remove all instances of.
         * 
         * Note: The method does not reset or clear the "removed" elements.
         * 
         * @return no return value.
         */
        void remove_all_of(T element){
            
            
            for(int i = 0; i < b_elements; i++){
                if(element == main_arr[i]){
                    for(int j = i; j < b_elements - 1; j++){
                        main_arr[j] = main_arr[j+1];
                    }
                    b_elements--;
                    i--;
                }
                else
                    continue;
            }

        }    

        /**
         * @brief A method that checks if the dynamic array is empty.
         * 
         * @return returns a boolean. true if empty, else false.
         */
        bool is_empty(){
            if(b_elements == 0)
                return true;
            else
                false;
        }


};