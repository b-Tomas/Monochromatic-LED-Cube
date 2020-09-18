/*
 * Snake functions
 * 
 * TODO:
 * - check collissions
 */


int sign(int x) {
  return x < 0 ? -1 : (x > 0 ? 1 : 0);
}

// Type to represent a 3d coordinate
struct Coord {
  int x;
  int y;
  int z;
  // turn led on/off on this coordinate
  void led(bool state) {
     LED(x, y, z, state);
  }
  // converts this point into a unit "vector", randomly choosing one
  // of the non-zero coordinates. It ends up with two zeros, and the
  // other value either 1 or -1.
  // If the point is already (0,0,0), it returns false. 
  bool randomFlatten() {
    int r2 = random(0,2);
    int r3 = random(0,3);
    x = sign(x);
    y = sign(y);
    z = sign(z);
    if (x) {
      if (y) {
        if (z) { // x, y, z
          if (r3 == 0) {
            // pick x
            y = z = 0;          
          } else if (r3 == 1) {
            // pick y
            x = z = 0; 
          } else {
            // pick z
            x = y = 0;
          }
        } else { // x, y
          if (r2) { x = 0; } else { y = 0; }
        }
      } else { // no y
        if (z) { // x, z
          if (r2) { x = 0; } else { z = 0; }            
        } else { // x
          // only x, ok
        }
      }
    } else { // no x
      if (y) {
        if (z) { // y, z
          if (r2) { y = 0; } else { z = 0; }
        } else {
          // only y, ok
        }
      } else { // no y
        if (z) {
          // only z, ok
        } else {
          // no coords!!
          return false;            
        }         
      }
    }
    return true;
  }
  // Randomizes the coordinate to a coordinate (within the cube)
  void randomize() {
    x = random(0, CUBE_SIZE);
    y = random(0, CUBE_SIZE);
    z = random(0, CUBE_SIZE);  
  }
};

// Adds two coordinates p1 and p2 storing result in r
void addCoord(const struct Coord *p1, const struct Coord *p2, struct Coord *r) {
   r->x = p1->x + p2->x;
   r->y = p1->y + p2->y;
   r->z = p1->z + p2->z;
}
// Subtracts two coordinates p1 and p2 storing result in r
void subtractCoord(const struct Coord *p1, const struct Coord *p2, struct Coord *r) {
   r->x = p1->x - p2->x;
   r->y = p1->y - p2->y;
   r->z = p1->z - p2->z;
}




#define MAX_LEN 10
// THE apple. There is only one
struct Coord apple;
// THE snake.
struct {
  // List of coordinates
  struct Coord coords[MAX_LEN];
  // Index of the most recent element, the head
  int head = 0;
  // Index of the last element, the tail. There is always at least 
  // one element in the snake!
  int tail = 0;
  // Adds one point to the snake, becoming its head. It also draws it
  // in the board.
  bool push(struct Coord *p) {
    int h = (head + 1) % MAX_LEN;
    if (h == tail) {
      return false;
    }
    coords[h] = *p;
    coords[h].led(HIGH);
    head = h;
    return true;
  }
  // Removes the last element (tail) from the snake, and turns LED off
  void pop() {
    coords[tail].led(LOW);
    tail = (tail + 1) % MAX_LEN;
  }
  // Resets snake length to 1 and randomizes its position
  int reset() {
    head = tail = 0;
    coords[head].randomize();
    coords[head].led(1);
  }
} snake;



void Snake() {
  // Main timer. One tick every N millis
  int TICK_MS = 50;
  // How many ticks to wait for updating the apple and the snake 
  int APPLE_TICKS = 3;
  int SNAKE_TICKS = 8;
  // Counters to update apple and snake
  int appleClock = 0;
  int snakeClock = 0;
  // Current apple color
  int appleColor = HIGH;
  // Start with random positions the apple and the snake
  apple.randomize();
  snake.reset();

  // Main loop: while not at the maximum length (it stops earlier anyway)
  int len = 0;
  while (len < MAX_LEN) {
    // Show/Hide apple
    appleClock++;
    if (++appleClock >= APPLE_TICKS) {
      // Change apple color, and redraw it
      appleColor = 1 - appleColor;
      apple.led(appleColor);
      appleClock = 0;
    } 
    // Move snake
    if (++snakeClock >= SNAKE_TICKS) {
      // Calculate the direction towards the apple
      struct Coord delta;
      subtractCoord(&apple, &snake.coords[snake.head], &delta);
      // Turn the direction into a unit, cartesian vector (and check if it is zero)
      bool eat = !delta.randomFlatten();
      Coord next;
      // Calculate the next coordinate position, just adding the unit
      // vector "delta" to snake's head
      addCoord(&snake.coords[snake.head], &delta, &next);
      // Attempt to grow (unless max length is reached)
      if (!snake.push(&next)) {
        // cannot grow snake, max size. restart!!
        return;
      }
      if (eat) { 
        // When eating the apple, create a new one
        apple.randomize();        
      } else {
        // If not eating, advance the tail (remove it)
        snake.pop();
      }        
      snakeClock = 0;
    }
    // Wait.
    delay(TICK_MS);
  }
}