#include "Vector.h"
int index = 0;
int arr_size = 0;
Cell ** stack_arr;

void Vector::push_back (Cell * cell) {
    // if at full capacity, expand size
    if (index == arr_size) { 
        Cell * resize_arr [arr_size + 10];
        for (int i = 0; i < arr_size; i++) {
            resize_arr[i] = stack_arr[i];
        }
        if (stack_arr != 0) {
            delete [] stack_arr;
        }
        stack_arr = resize_arr;
        arr_size = arr_size + 10;
    }
    // append the cell to the back of the array
    stack_arr[index] = cell;
    index ++;
}

void Vector::clear(){
    index = 0;
}

Cell * Vector::get_curr_cell(int idx){
        return stack_arr[idx];
}

Cell * Vector::pop_back() {
    Cell * res = stack_arr[index];
    index --;
    return res;
}

Cell * Vector::back() {
    return stack_arr[index];
}

bool Vector::empty() {
    return index == 0;
}

int Vector::size() {
    return index;    
}