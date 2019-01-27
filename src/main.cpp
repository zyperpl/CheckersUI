#include <chrono>

#include "window.hpp"
#include "view.hpp"

#define SCREEN_WIDTH 1900
#define SCREEN_HEIGHT 1000

int main()
{
  Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
  View view;

  double dt = 1.0;
    
  static auto time = std::chrono::high_resolution_clock::now();        

  while (window.isOpen())
  {
    auto timeNow = std::chrono::high_resolution_clock::now();        
    auto nanoSec = timeNow.time_since_epoch() - time.time_since_epoch();
    time = timeNow;

    double dt = nanoSec.count()/1e+6;
    //printf("Delta time: %4.2fms\n", dt);

    window.update(dt, view);
    window.render(view);
  }

  return 0;
};
