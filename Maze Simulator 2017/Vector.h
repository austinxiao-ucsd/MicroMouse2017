//#ifndef __VECTOR_H__
//#define __VECTOR_H__
#include "Cell.h"
class Vector
{
    public:
        
        int index = 0;
        
        int arr_size = 0;
        
        Cell ** stack_arr;
        
        Vector();
        
        ~Vector();
         
        void push_back (Cell * cell);
        
        Cell * pop_back();
        
        Cell * back();
        
        bool empty();
        
        int size();
        
        void clear();
        
        Cell * get_curr_cell(int idx);
};
