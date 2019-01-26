#pragma once

#include <iostream>

template<typename C, typename size_type, typename value_type>
void find_and_insert(C& array, size_type insert_idx, value_type value, size_type offset)
{
    while(insert_idx > (offset - 1) && array[insert_idx-offset] > value){
        array[insert_idx] = array[insert_idx-offset];
        insert_idx -= offset;
    }

    array[insert_idx] = value;
}

template<typename C>
void insertion_sort(C& array)
{
    using size_type = typename C::size_type;
    
    for (size_type next_idx = 1; next_idx < array.size(); ++next_idx) {
        find_and_insert(array, next_idx, array[next_idx], static_cast<size_type>(1));
    }
}

template<typename C, typename G>
void shell_sort(C& array, G gaps)
{
    for (auto interval : gaps) {
        for (auto next_idx = interval; next_idx < array.size(); ++next_idx) {
            find_and_insert(array, next_idx, array[next_idx], interval);
        }
    }
}
