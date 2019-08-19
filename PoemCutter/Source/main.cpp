#include <string>
#include <array>

#include "choppingboard.h"

#include "honey.h"

using namespace std;
using namespace Honey;

int main(int argc, char* args[]) {
  StartHoney("ChoppingBoard");

  string file_pattern(args[1]);
  ChoppingBoard* choppingboard = new ChoppingBoard(file_pattern); 
  choppingboard->initialize();

  // Loop
  while (!screenmanager.getQuit()) {
    input.processInput();

    choppingboard->logic();
    choppingboard->render();

    graphics.updateDisplay();
  }

  delete choppingboard;
}

