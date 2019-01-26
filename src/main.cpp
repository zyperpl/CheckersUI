#include "window.hpp"
#include "view.hpp"

#define SCREEN_WIDTH 1900
#define SCREEN_HEIGHT 1000

int main()
{
  Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
  View view;

  double dt = 0.0;

  while (window.isOpen())
  {
    window.update(dt, view);
    window.render(view);
  }

  return 0;
};
