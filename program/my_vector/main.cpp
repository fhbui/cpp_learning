#include <iostream>
#include "my_vector.h"
#include <vector>

int main(void){
    // my_vector<int> vec{3};

    // std::vector<int> test{1,2,3,4,5,6};
    // std::cout << test[3];

    my_vector<int> v(5, 1);
    v.push_back(3);
    v.insert(&v[1], 2);

    for(int i=0; i<v.size(); i++){
        std::cout << v[i] << " ";
    }
    return 0;
}

