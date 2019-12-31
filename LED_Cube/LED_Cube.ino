//********************************************************************//
//  Name    : Monochromatic LED cube                                  //
//  Author  :                                                         //
//  Date    :                                                         //
//  Version :                                                         //
//  Notes   :   Code for controlling any monochromatic LED cube       //
//          :   This uses direct port register manipulation to make   //
//          : the code much faster. Take care if you change the       //
//          : pins. If you change the port you will need to change    //
//          : the lines where that port appears and replace it        //
//          :   This uses the TCNT1 register, so the servo functions  //
//          : and pins 9 and 10 for PWM are disabled                  //
//********************************************************************//

/*
TODO:
.OPTIMIZE THE ISR
.check for TODOs
.more animations
*/

// Libraries
#include <SPI.h>

// Pins -> If you change this section, the direct port register manipulation may not work (if you change the port register), and you will need to change every line where this is used
#define LATCH_PIN PD2 // Digital I/O 2 for ATmega328p. Connect to RCLK pin of the ICs. Is the storage register, the slave selector for SPI communication

// Other data
#define CUBE_SIZE 5.0f // Size of the side of the LED cube. HAS to be float, but type integers please
#define LATENCY 10 // Frecuency of the cube cycle in Hz
#define NUMBER_OF_REGISTERS (int) ceil((sq(CUBE_SIZE) + CUBE_SIZE)/8.0f) // Number of shift registers needed to control the cube
#define USELESS_BITS (int) (NUMBER_OF_REGISTERS*8 - (sq(CUBE_SIZE) + CUBE_SIZE)) // Number of bits of the last IC that are not used

#define SET(x, y) (x |= (1 << y)) // Equivalent to bitSet()
#define CLR(x, y) (x &= ~(1 << y)) // Equivalent to bitClear()

//                        X                Y                Z
bool cubeMatrix[(int) CUBE_SIZE][(int) CUBE_SIZE][(int) CUBE_SIZE] = {0}; // Every item is a led. 1 means on and 0 off

byte data[NUMBER_OF_REGISTERS]; // Data to send. Every element goes to its shift register. The shift registers are odered form the first, wich contains the firs column, to the last, that controls some of the layers

byte currentLayer = 0; // Actual layer

void setup() { 
  
  // Set digital output pins
  pinMode(LATCH_PIN, OUTPUT); // Slave selector pin for the SPI communication

  // Configure SPI communication
  SPI.setBitOrder(MSBFIRST); // Data sending order, most significant bit first
  SPI.setDataMode(SPI_MODE0); // Clock is normally low, sends the data on the transition form low to high on the clock
  SPI.setClockDivider(SPI_CLOCK_DIV2); // Data sending frequency. The Arduino UNO clock works at 16Mhz, too much for the shift registers. SPI_CLOCK_DIV2 divides it by 2, so it goes at 8Mhz  
  SPI.begin(); // Enable the communication
  
  // Configure the timer 1 (TCNT1 register) of the arduino
  noInterrupts(); // Disable the interrups while configuring
  TCCR1A = 0; // Reset timer 1 control register A
  CLR(TCCR1B, CS12); // Sets the prescaler to 64 (250Khz timing count for a 16Mhz board). If you change this lines change the OCR1A line
  SET(TCCR1B, CS11); //  _| |
  SET(TCCR1B, CS10); //  ___|
  OCR1A = (pow((LATENCY*CUBE_SIZE/1000000), -1)*16)/64; // Match value to compare to the timer value that generates the compare match interrupt (TIMER1_COMPA). Is stored in the Output Compare Registers. 16 is the CPU clock frequency (in Mhz) and 64 the prescaler
  TIMSK1 = (1 << OCIE1A); // Counter interrupt mask register. Sets the interrupt to enable compare A mach interrupt.
  TCNT1 = 0; // Starts counting form cero
  interrupts(); // Enable interrupts
}

void loop() {
  EdgesOn(30);
  delay(200);
  EdgesOff(30);
  delay(200);
  EdgesOnReverse(30);
  delay(200);
  EdgesOffReverse(30);
  delay(200);
  ScanX(50);
  ScanY(50);
  ScanZ(65);
  delay(200);
  AllOn();
  delay(500);
  EdgesOffReverse(30);
  delay(100);
  Clear();
  delay(30);
}

// Turns On or Off the specified LED
void LED(int X, int Y, int Z, bool state) {
  
  // If the given coordinates are out of the cube, bring it to the limit
  if (X >= CUBE_SIZE) {
    X = CUBE_SIZE-1;
  }
  if (Y >= CUBE_SIZE) {
    Y = CUBE_SIZE-1;
  }
  if (Z >= CUBE_SIZE) {
    Z = CUBE_SIZE-1;
  }
  
  // Saves the state of the given LED
  cubeMatrix[X][Y][Z] = state;
}


// Interrupt service routine. Handles the interrupt of the timer 1. Changes to the next layer
ISR(TIMER1_COMPA_vect) {
  
  TCNT1 = 0; // Reset the timer count
  
  // If in the layer to turn on is a LED to turn on, turn it on. If not, off
  int columnOfThisLed = 0; // The number of column where this LED is located
  for (int y = 0; y < CUBE_SIZE; y++) {
    for (int x = 0; x < CUBE_SIZE; x++, columnOfThisLed++) {
        int registerOfThisColumn = columnOfThisLed >> 3; // In wich register is stored the state of this column
        int bitOfTheColumn = columnOfThisLed - (registerOfThisColumn << 3); // Wich bit on the register represents the state of the column
        bitWrite(data[registerOfThisColumn], bitOfTheColumn, int(cubeMatrix[x][y][currentLayer])); // Writes to the bit where is the led in the current layer to turn on a 1, or a 0 to turn off
    }
  }
  
  // Turns on the current layer and off the others  
  int bitOfTheLayerInTheTotal = ((NUMBER_OF_REGISTERS*8)-(USELESS_BITS+CUBE_SIZE)); // The number of bit (output) within all the outputs
  for (int z = 0; z < CUBE_SIZE; z++, bitOfTheLayerInTheTotal++) {
    int registerOfThisLayer = bitOfTheLayerInTheTotal >> 3; // Register where this bit is located
    int bitOfTheLayer = bitOfTheLayerInTheTotal-(registerOfThisLayer << 3); // Bit of this layer in its register
    
    // Turn the layer on if it is the current layer, turn it off if not
    if (z == currentLayer) {
      SET(data[registerOfThisLayer], bitOfTheLayer);
    } else {      
      CLR(data[registerOfThisLayer], bitOfTheLayer);
    }
  }  
  
  // Starts data transfer
  CLR(PORTD, LATCH_PIN); // digitalWrite(LATCH_PIN, LOW);
  // Sends the data to the registers
  for (int i = NUMBER_OF_REGISTERS-1; i >= 0; i--) {
    SPI.transfer(data[i]);
  }
  SET(PORTD, LATCH_PIN); // digitalWrite(LATCH_PIN, HIGH);
  // End of data transfer
  
  // Updates the layer for the next iteration
  currentLayer++;
  if (currentLayer == CUBE_SIZE) {
    currentLayer = 0;
  }
}
