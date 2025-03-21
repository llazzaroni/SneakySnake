#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using matrix = std::vector<std::vector<bool> >;


unsigned int longest_path(const matrix& table , const int checkpoint) {
    
    unsigned int longest = 0;
    
    for (unsigned int i = 0 ; i < table.size() ; i++) {
        
        unsigned int ith_longest = 0;
        
        while (checkpoint + ith_longest < table.at(0).size() && table.at(i).at(checkpoint + ith_longest)) {
            ith_longest++;
        }
        
        if (ith_longest > longest) {
            longest = ith_longest;
        }
    }
    
    return longest;
}


int SneakySnakeMat(const matrix& table) {
  
  int checkpoint = 0;
  int PropagationDelay = 0;
  
  unsigned long m = table.at(0).size();
  
  while (checkpoint < m) {
    
      checkpoint += longest_path(table , checkpoint);
      //longest_path is a function which outputs the longest matching subsequence
      //starting from the checkpoint.
      
      if (checkpoint < m) {
          checkpoint++;
          PropagationDelay++;
      }
  }
  
return PropagationDelay;
}


