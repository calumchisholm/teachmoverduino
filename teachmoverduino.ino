/*
 * Arduino interface for the Microbot Teachmover II / Alpha II robot arm.
 *
 * Copyright (C) 2015 Calum Chisholm and released under the ISC license.
 *
 *
 * CONFIG:
 * - Pin mappings and delays are defined in config.h
 *
 * TODO:
 * - Improve debugging - serial debug calls have a significant performance impact when made during a motor movement
 *   and should be made only when strictly necessary.
 * - Implement other input sources (serial, network, SPI, ...)
 * - Implement separate timers for each motor, allowing them to run simultaneously at different speeds.
 * - Robot apocalypse.
 *
 */

#include "config.h"
#include "enums.h"

long previousMillis = 0; // Stores the time (ms) since a motor was last moved.

#ifdef TODO

// Stores the time (ms) since the last movement of the individual motors.
long previousElbow = 0;
long previousShoulder = 0;
long previousRwrist = 0;
long previousBase = 0;
long previousGripper = 0;
long previousLwrist = 0;

#endif

//Initialize variables, pin modes etc.
void setup()
{
#ifdef DEBUG
  Serial.begin (19200); // debugging
#endif

  // Set up the motor pins.
  setup_motor();
  
  // Set up our input sources.
  setup_spi();
  setup_keypad();
}

// Main program loop.
void loop()
{
  int commands = 0;

  // Read from our input sources.
  commands |= read_keypad();      // Read from the keypad();
  commands |= read_spi();         // Read from SPI (not yet implemented)

  if (commands > 0)
  {
    unsigned long currentMillis = millis();

    //TODO: Create separate timers for each motors, to allowing them to be run simultaneously at different speeds.
    if(currentMillis - previousMillis > stepDelay)
    {
      previousMillis = currentMillis;

      // I like to move it move it.
      MoveMotors(commands);
    }
  }
}
