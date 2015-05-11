//
// Control the motor's actions using SPI comms - not yet implemented.
//
// SPI bits borrowed from http://mitchtech.net/raspberry-pi-arduino-spi/

#include <SPI.h>
 
char buf [100];
volatile byte pos;
volatile boolean process_it;
 
void setup_spi(void)
{
#ifdef SPI_NOT_YET_IMPLEMENTED

  // have to send on master in, *slave out*
  pinMode(spi_miso, OUTPUT);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;
 
  // now turn on interrupts
  SPI.attachInterrupt();

#endif
}  // end of setup
 
 
// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;  // grab byte from SPI Data Register
  
  // add to buffer if room
  if (pos < sizeof buf)
    {
    buf [pos++] = c;
    
    // example: newline means time to process buffer
    if (c == '\n')
      process_it = true;
      
    }  // end of room available
}  // end of interrupt routine SPI_STC_vect

int read_spi(void)
{
 
  //TODO: Read from other input sources (serial, network, SPI, ...)
#ifdef SPI_INCOMPLETE
  if (process_it)
  {
    // Read the SPI buffer
    buf[pos] = 0;

    pos = 0;
    process_it = false;
  }
#endif

  return 0;
}
