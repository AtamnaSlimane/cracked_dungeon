#include "input.h"
#include <iostream>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

static termios oldSettings, newSettings;

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &oldSettings);
  newSettings = oldSettings;
  newSettings.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
}

void disableRawMode() { tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings); }

char getInput() {
  char c;
  std::cin.get(c);
  return c;
}

bool isKeyPressed() {
  timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);
  return select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv) > 0;
}
