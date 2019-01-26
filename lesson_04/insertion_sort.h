#pragma once

template<typename C>
void insertion_sort(C& array)
{
    using value_type = typename C::value_type;
    using size_type = typename C::size_type;
    
    for (size_type next_idx = 1; next_idx < array.size(); ++next_idx) {

        value_type insert_value = array[next_idx];
        auto insert_idx = next_idx;

        while(insert_idx > 0 && array[insert_idx-1] > insert_value){
            array[insert_idx] = array[insert_idx-1];
            --insert_idx;
        }

        array[insert_idx] = insert_value;
    }
}
