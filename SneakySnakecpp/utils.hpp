#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>


struct Timer {
  using timepoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
  
  timepoint start;
  timepoint end;
  
  void tick() {
    start = std::chrono::high_resolution_clock::now();
  }
  
  void tock() {
    end = std::chrono::high_resolution_clock::now();
  }
  
  unsigned long elapsed() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  }
};
