// Delay (ms) between motor steps.
long stepDelay = 5;

/* Pin mapping.
 *
 * 4 pins are required per degree of freedom, so a 6-dof arm will require a board with >24 available I/O pins,
 * This means you're restricted to using an Arduino Mega or similar if you want to support the full functionality of the Teachmover II.
 */
typedef enum Pins_t
{
  // Avoid pins 0 and 1 - used for serial comms, debugging.

  // Button inputs
  btnBaseA = 2,
  btnBaseB,
  btnElbowA,
  btnElbowB,
  btnShoulderA,
  btnShoulderB,
  btnLwristA,
  btnLwristB,
  btnRwristA,
  btnRwristB,
  btnGripperA,
  btnGripperB, //13

  // Stepper pins
  u1PhasePin =  22,
  u2PhasePin,
  u1Input0Pin,
  u2Input0Pin,
  
  u3PhasePin = 26,
  u4PhasePin,
  u3Input0Pin,
  u4Input0Pin,
  
  u5PhasePin = 30,
  u6PhasePin,
  u5Input0Pin,
  u6Input0Pin,
  
  u7PhasePin = 34,  // Currently unused
  u8PhasePin,       // Currently unused
  u7Input0Pin,      // Currently unused
  u8Input0Pin,      // Currently unused
  
  u9PhasePin = 38,
  u10PhasePin,
  u9Input0Pin,
  u10Input0Pin,
  
  u11PhasePin = 42, // Currently unused
  u12PhasePin,      // Currently unused
  u11Input0Pin,     // Currently unused
  u12Input0Pin,     // Currently unused
  
  u13PhasePin = 46,
  u14PhasePin,
  u13Input0Pin,
  u14Input0Pin,

  // SPI pins
  spi_miso = 50,
  spi_mosi = 51,
  spi_sck = 52,
  spi_ss = 54
};

#ifdef TODO

//TODO: Create a separate timers for each motors, to allowing them to run simultaneously at different speeds.
int delayElbow = 1;
int delayShoulder = 1;
int delayRwist = 1;
int delayBase = 1;
int delayGripper = 1;
int delayLwrist = 1;

#endif

