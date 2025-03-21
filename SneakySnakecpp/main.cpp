#include <iostream>
#include <vector>
#include <fstream>
#include "SneakySnake.cpp"
#include "SneakySnakeMat.cpp"
#include "utils.hpp"
#include "MurmurHash.cpp"

using matrix = std::vector<std::vector<bool> >;

void print_vector(std::vector<int> vec , std::ostream& out) {
    for (unsigned int i = 0 ; i < vec.size() ; i++) {
        out << vec.at(i) << std::endl;
    }
}

void print_matrix(matrix a , std::ostream& out) {
    for (unsigned int i = 0 ; i < a.size() ; i++) {
        for (unsigned int k = 0 ; k < a.at(0).size() ; k++) {
            out << a.at(i).at(k) << " ";
        }
        out << std::endl;
    }
}


matrix string_table(std::string a , std::string b , unsigned int e) {
    
    matrix table(2 * e + 1 , std::vector<bool>(a.size()));
    
    int r = e;
    
    for (unsigned int i = 0 ; i < table.size() ; i++) {
        for (unsigned int k = 0 ; k < table.at(0).size() ; k++) {
            if (k - r >= 0 && k - r < table.at(0).size()) {
                if (a.at(k - r) == b.at(k)) {
                    table.at(i).at(k) = true;
                }
            }
        }
        r--;
    }
    
    return table;
}


matrix string_table_murmur(std::string a , std::string b , unsigned int e , unsigned int c ,
                           unsigned int murmur2) {
    
    matrix table(2 * e + 1 , std::vector<bool>(a.size() / c));
    
    unsigned int r = e;
    
    for (unsigned int i = 0 ; i < a.size() ; i += c) {
        for (unsigned int j = 0 ; j < table.size() ; j++) {
            
            if (i + c <= a.size() && i + c + r <= a.size() && i + r >= 0 && i + r < a.size()) {
                std::string a_little;
                std::string b_little;
                
                for (unsigned int k = 0 ; k < c ; k++) {
                    b_little.push_back(b.at(i + k));
                    a_little.push_back(a.at(i + k + r));
                }
                
                uint32_t hash_1 = murmur3_32((uint8_t *)a_little.c_str() , c , murmur2);
                uint32_t hash_2 = murmur3_32((uint8_t *)b_little.c_str() , c , murmur2);
                    
                if (hash_1 == hash_2) {
                    table.at(j).at(i / c) = true;
                }
            }
            r--;
        }
        r = e;
    }
    
    return table;
}

int main() {
    
    //reading the file and preparing the matrices
    
    std::ifstream in("sourcefile.txt");
    
    std::vector<matrix> matrices_succession;
    
    //std::vector<std::string> a1;
    //std::vector<std::string> b1;
    
    std::string a;
    std::string b;
    
    while (in >> a && in >> b) {
        matrices_succession.push_back(string_table_murmur(a , b , 20 , 20 , 0));
        //matrices_succession.push_back(string_table(a , b , 5));
        //a1.push_back(a);
        //b1.push_back(b);
    }
    
    
    //preparing the output vector
    
    std::vector<int> edit_distances;
    
    std::ofstream out("outputfile.txt");
    
    
    //starting the computation and the timer
    
    Timer timer;
    
    timer.tick();
    
    for (unsigned int i = 0 ; i < matrices_succession.size() ; i++) {
        int a = SneakySnakeMat(matrices_succession.at(i));
        edit_distances.push_back(a);
    }
    
    timer.tock();
    
    //printing the results
    
    print_vector(edit_distances , out);
    
    out << "Time needed: " << timer.elapsed() << " ms";
    
}
