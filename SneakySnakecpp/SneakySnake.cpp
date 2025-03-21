#include <iostream>
#include <vector>
#include <string>
#include <cassert>


int MainHRT(const std::string& query , const std::string& reference , int checkpoint) {
  
  int longest_es = 0;
  
  for (unsigned int i = checkpoint ; i < query.size() ; i++) {
    
    if (query.at(i) != reference.at(i)) {
      return longest_es;
    }
    
    else longest_es++;
  }
  
  return longest_es;
}

int UpperHRT(const std::string& query , const std::string& reference , int checkpoint , int E) {
  
  int longest_es = 0;
  
  for (unsigned int r = E ; r >= 1 ; r--) {
    
    int count = 0;
    
    for (unsigned int n = checkpoint ; n < query.size() ; n++) {
      
      if (n < r) {
        break;
      }
      else if (query.at(n - r) != reference.at(n)) {
        break;
      }
      else if (query.at(n - r) == reference.at(n)) {
        count++;
      }
      
      if (count > longest_es) {
        longest_es = count;
      }
    }
  }
  
  return longest_es;
}

int LowerHRT(const std::string&query , const std::string&reference , int checkpoint , int E) {
  
  int longest_es = 0;
  unsigned long m = query.size();
  
  for (unsigned int r = 1 ; r <= E ; r++) {
    
    int count = 0;
    
    for (unsigned int n = checkpoint ; n < query.size() ; n++) {
      
      if (n > m - r - 1) {
        break;
      }
      else if (query.at(n + r) != reference.at(n)) {
        break;
      }
      else if (query.at(n + r) == reference.at(n)) {
        count++;
      }
      
      if (count > longest_es) {
        longest_es = count;
      }
    }
  }
  
  return longest_es;
}


int SneakySnake(const std::string& query , const std::string& reference , const int& E) {
  
  int checkpoint = 0; //as soon as checkpoint reaches query.size() the function outputs its value
  int PropagationDelay = 0; //this is going to be the output of the function
  
  unsigned long m = query.size();
  
  while (checkpoint < m) {
    
    
    int count = MainHRT(query , reference , checkpoint); //this function compares the two strings
                                                         //without any shift
    if (count == m) return PropagationDelay;
    
    
    int longest_es = std::max(UpperHRT(query , reference , checkpoint , E) ,
                              LowerHRT(query , reference , checkpoint , E));
    
    //UpperHRT compares the strings with a positive shift, LowerHRT compare the string with a
    //negative shift
    
    
    if (count > longest_es) longest_es = count;
    
    checkpoint += longest_es;
    
    if (checkpoint < m) {
      PropagationDelay++;
      checkpoint++;
    }
    
  }
  
return PropagationDelay;
}

