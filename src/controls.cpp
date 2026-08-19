#include "controls.h"
#include "input.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

const Controls VimControls{'k', 'j', 'h', 'l', 'f'};

const Controls WasdControls{'w', 's', 'a', 'd', 'j'};

const Controls ZqsdControls{'z', 's', 'q', 'd', 'j'};

Controls controls = VimControls;

void saveControls(int choice) {
  std::ofstream file("controls.cfg");

  if (file) {
    file << choice;
  }
}
bool loadControls() {
  std::ifstream file("controls.cfg");

  int choice;

  if (!(file >> choice)) {
    return false;
  }

  switch (choice) {
  case 1:
    controls = VimControls;
    return true;

  case 2:
    controls = WasdControls;
    return true;

  case 3:
    controls = ZqsdControls;
    return true;

  default:
    return false;
  }
}
void chooseControls() {
  while (true) {
    std::cout << "\033[2J\033[H";

    std::cout << "=== CRACKED DUNGEON ===\n\n";
    std::cout << "Choose Controls\n\n";
    std::cout << "1) Vim (h j k l)\n";
    std::cout << "2) WASD for qwerty\n";
    std::cout << "3) ZQSD for azerty\n";

    if (isKeyPressed()) {
      switch (getInput()) {
      case '1':
        controls = VimControls;
        saveControls(1);
        return;

      case '2':
        controls = WasdControls;

        saveControls(2);
        return;

      case '3':
        controls = ZqsdControls;
        saveControls(3);
        return;
      }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
