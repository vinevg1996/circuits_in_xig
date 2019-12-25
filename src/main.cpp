#include <iostream>
#include <cmath>
#include <map>

#include "aig.h"

int main(int argc, char **argv) {
    std::ifstream data_base_file("../database_dump_AIG.txt");
    std::vector<std::vector<int>> xorStructures;
    std::map<int, int> xor_structure_map;
    int sum;
    for (int i = 0; i < 616125; ++i) {
        MyAIG curr_aig(data_base_file);
        curr_aig.CountXorStructures(sum, xorStructures);
        //std::cout << "i = " << i << std::endl;  
        xor_structure_map[sum] = xor_structure_map[sum] + 1;
        /*
        if (sum > 0) {
            std::cout << curr_aig.GetMincode() << std::endl;
            std::cout << curr_aig.GetComplexity() << std::endl;
            std::cout << "sum = " << sum << std::endl;
        }
        */
        sum = 0;
        xorStructures.clear();
    }
    for (const auto &elem: xor_structure_map) {
        std::cout << elem.first << ": " << elem.second << std::endl;
    }
    return 0;
}
