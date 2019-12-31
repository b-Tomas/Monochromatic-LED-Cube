/*

*/

// Turns on all the LEDs
void AllOn() {
  for (int x = 0; x < CUBE_SIZE; x++) {
    for (int y = 0; y < CUBE_SIZE; y++) {
      for (int z = 0; z < CUBE_SIZE; z++) {
        LED(x, y, z, HIGH);
      }
    }
  }
}

// Turns off all the LEDs
void Clear() {
  for (int x = 0; x < CUBE_SIZE; x++) {
    for (int y = 0; y < CUBE_SIZE; y++) {
      for (int z = 0; z < CUBE_SIZE; z++) {
        LED(x, y, z, LOW);
      }
    }
  }
}

// Turn on only the edges
void EdgesOn(int speed) {
  for (int i = 0; i < CUBE_SIZE; i++) {
    // From 0, 0, 0
    LED(i, 0, 0, HIGH);
    LED(0, i, 0, HIGH);
    LED(0, 0, i, HIGH);
    delay(speed);
  }
  for (int i = 1; i < CUBE_SIZE; i++) {
    // From 0, 0, CUBE_SIZE-1
    LED(i, 0, CUBE_SIZE-1, HIGH);
    LED(0, i, CUBE_SIZE-1, HIGH);
    // From CUBE_SIZE-1, 0, 0
    LED(CUBE_SIZE-1, 0, i, HIGH);
    LED(CUBE_SIZE-1, i, 0, HIGH);
    // From 0, CUBE_SIZE-1, 0
    LED(0, CUBE_SIZE-1, i, HIGH);
    LED(i, CUBE_SIZE-1, 0, HIGH);
    delay(speed);
  }
  for (int i = 1; i < CUBE_SIZE; i++) {
    // From CUBE_SIZE-1, 0, CUBE_SIZE-1
    LED(CUBE_SIZE-1, i, CUBE_SIZE-1, HIGH);
    // From CUBE_SIZE-1, CUBE_SIZE-1, 0
    LED(CUBE_SIZE-1, CUBE_SIZE-1, i, HIGH);
    // From 0, CUBE_SIZE-1, CUBE_SIZE-1
    LED(i, CUBE_SIZE-1, CUBE_SIZE-1, HIGH);
    delay(speed);
  }
}

// Turn on only the edges reversely
void EdgesOnReverse(int speed) {
  for (int i = CUBE_SIZE-1; i >= 0; i--) {
    // From CUBE_SIZE-1, CUBE_SIZE-1, CUBE_SIZE-1
    LED(i, CUBE_SIZE-1, CUBE_SIZE-1, HIGH);
    LED(CUBE_SIZE-1, i, CUBE_SIZE-1, HIGH);
    LED(CUBE_SIZE-1, CUBE_SIZE-1, i, HIGH);
    delay(speed);
  }
  for (int i = CUBE_SIZE-2; i >= 0; i--) {
    // From CUBE_SIZE-1, 0, CUBE_SIZE-1
    LED(CUBE_SIZE-1, 0, i, HIGH);
    LED(i, 0, CUBE_SIZE-1, HIGH);
    // From CUBE_SIZE-1, CUBE_SIZE-1, 0
    LED(CUBE_SIZE-1, i, 0, HIGH);
    LED(i, CUBE_SIZE-1, 0, HIGH);
    // From 0, CUBE_SIZE-1, CUBE_SIZE-1
    LED(0, CUBE_SIZE-1, i, HIGH);
    LED(0, i, CUBE_SIZE-1, HIGH);
    delay(speed);
  }
  for (int i = CUBE_SIZE-2; i >= 0; i--) {
    // From 0, CUBE_SIZE-1, 0
    LED(i, 0, 0, HIGH);
    // From 0, CUBE_SIZE-1, 0
    LED(0, i, 0, HIGH);
    // From 0, 0, CUBE_SIZE-1
    LED(0, 0, i, HIGH);
    delay(speed);
  }
}

// Turn off only the edges
void EdgesOff(int speed) {
  for (int i = 0; i < CUBE_SIZE; i++) {
    // From 0, 0, 0
    LED(i, 0, 0, LOW);
    LED(0, i, 0, LOW);
    LED(0, 0, i, LOW);
    delay(speed);
  }
  for (int i = 1; i < CUBE_SIZE; i++) {
    // From 0, 0, CUBE_SIZE-1
    LED(i, 0, CUBE_SIZE-1, LOW);
    LED(0, i, CUBE_SIZE-1, LOW);
    // From CUBE_SIZE-1, 0, 0
    LED(CUBE_SIZE-1, 0, i, LOW);
    LED(CUBE_SIZE-1, i, 0, LOW);
    // From 0, CUBE_SIZE-1, 0
    LED(0, CUBE_SIZE-1, i, LOW);
    LED(i, CUBE_SIZE-1, 0, LOW);
    delay(speed);
  }
  for (int i = 1; i < CUBE_SIZE; i++) {
    // From CUBE_SIZE-1, 0, CUBE_SIZE-1
    LED(CUBE_SIZE-1, i, CUBE_SIZE-1, LOW);
    // From CUBE_SIZE-1, CUBE_SIZE-1, 0
    LED(CUBE_SIZE-1, CUBE_SIZE-1, i, LOW);
    // From 0, CUBE_SIZE-1, CUBE_SIZE-1
    LED(i, CUBE_SIZE-1, CUBE_SIZE-1, LOW);
    delay(speed);
  }
}

// Turn off only the edges reversely
void EdgesOffReverse(int speed) {
  for (int i = CUBE_SIZE-1; i >= 0; i--) {
    // From CUBE_SIZE-1, CUBE_SIZE-1, CUBE_SIZE-1
    LED(i, CUBE_SIZE-1, CUBE_SIZE-1, LOW);
    LED(CUBE_SIZE-1, i, CUBE_SIZE-1, LOW);
    LED(CUBE_SIZE-1, CUBE_SIZE-1, i, LOW);
    delay(speed);
  }
  for (int i = CUBE_SIZE-2; i >= 0; i--) {
    // From CUBE_SIZE-1, 0, CUBE_SIZE-1
    LED(CUBE_SIZE-1, 0, i, LOW);
    LED(i, 0, CUBE_SIZE-1, LOW);
    // From CUBE_SIZE-1, CUBE_SIZE-1, 0
    LED(CUBE_SIZE-1, i, 0, LOW);
    LED(i, CUBE_SIZE-1, 0, LOW);
    // From 0, CUBE_SIZE-1, CUBE_SIZE-1
    LED(0, CUBE_SIZE-1, i, LOW);
    LED(0, i, CUBE_SIZE-1, LOW);
    delay(speed);
  }
  for (int i = CUBE_SIZE-2; i >= 0; i--) {
    // From 0, CUBE_SIZE-1, 0
    LED(i, 0, 0, LOW);
    // From 0, CUBE_SIZE-1, 0
    LED(0, i, 0, LOW);
    // From 0, 0, CUBE_SIZE-1
    LED(0, 0, i, LOW);
    delay(speed);
  }
}

// "Scan" on the X axis
void ScanX(int speed) {
  for (int x = 0; x < CUBE_SIZE; x ++){
    for (int y = 0; y < CUBE_SIZE; y ++){
      for (int z = 0; z < CUBE_SIZE; z ++){
        LED(CUBE_SIZE-1-x, y, z, HIGH);
      }
    }
    delay(speed);
    for (int y = 0; y < CUBE_SIZE; y ++){
      for (int z = 0; z < CUBE_SIZE; z ++){
        LED(CUBE_SIZE-1-x, y, z, LOW);
      }
    }
  }
}

// "Scan" on the Y axis
void ScanY(int speed) {
  for (int y = 0; y < CUBE_SIZE; y ++){
    for (int x = 0; x < CUBE_SIZE; x ++){
      for (int z = 0; z < CUBE_SIZE; z ++){
        LED(x, CUBE_SIZE-1-y, z, HIGH);
      }
    }
    delay(speed);
    for (int x = 0; x < CUBE_SIZE; x ++){
      for (int z = 0; z < CUBE_SIZE; z ++){
        LED(x, CUBE_SIZE-1-y, z, LOW);
      }
    }
  }
}

// "Scan" on the Z axis
void ScanZ(int speed) {
  for (int z = 0; z < CUBE_SIZE; z ++){
    for (int x = 0; x < CUBE_SIZE; x ++){
      for (int y = 0; y < CUBE_SIZE; y ++){
        LED(x, y, z, HIGH);
      }
    }
    delay(speed);
    for (int x = 0; x < CUBE_SIZE; x ++){
      for (int y = 0; y < CUBE_SIZE; y ++){
        LED(x, y, z, LOW);
      }
    }
  }
}
