#pragma once

struct Controls {
  char up;
  char down;
  char left;
  char right;
  char fire;
};

extern Controls controls;

extern const Controls VimControls;
extern const Controls WasdControls;
extern const Controls ZqsdControls;

void chooseControls();
void saveControls();
bool loadControls();
