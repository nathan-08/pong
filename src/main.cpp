#include <iostream>

#include "app.h"

int main()
{
  try
  {
    App *app = new App("try this");
    app->mainloop();
    delete app;
  }
  catch (std::exception& e)
  {
    std::cout << "caught exception: " << e.what() << std::endl;
  }
}
