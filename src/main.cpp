#include "app.h"

int main() {
  if(!app_init()) {
    return -1;
  }
  
  app_run();
  app_shutdown();
  
  return 0;
}
