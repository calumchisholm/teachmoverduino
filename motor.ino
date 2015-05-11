// Current step sequence for each motor.
int stepElbow = 0;
int stepShoulder = 0;
int stepRwrist = 0;
int stepBase = 0;
int stepGripper = 0;
int stepLwrist = 0;

void setup_motor(void)
{
  pinMode(u1PhasePin,   OUTPUT);      
  pinMode(u2PhasePin,   OUTPUT);      
  pinMode(u1Input0Pin,  OUTPUT);      
  pinMode(u2Input0Pin,  OUTPUT);      

  pinMode(u3PhasePin,   OUTPUT);      
  pinMode(u4PhasePin,   OUTPUT);      
  pinMode(u3Input0Pin,  OUTPUT);      
  pinMode(u4Input0Pin,  OUTPUT);      

  pinMode(u5PhasePin,   OUTPUT);      
  pinMode(u6PhasePin,   OUTPUT);      
  pinMode(u5Input0Pin,  OUTPUT);      
  pinMode(u6Input0Pin,  OUTPUT);      

  pinMode(u7PhasePin,   OUTPUT);      
  pinMode(u8PhasePin,   OUTPUT);      
  pinMode(u7Input0Pin,  OUTPUT);      
  pinMode(u8Input0Pin,  OUTPUT);      
   
  pinMode(u9PhasePin,   OUTPUT);      
  pinMode(u10PhasePin,  OUTPUT);      
  pinMode(u9Input0Pin,  OUTPUT);      
  pinMode(u10Input0Pin, OUTPUT);      
   
  pinMode(u11PhasePin,  OUTPUT);      
  pinMode(u12PhasePin,  OUTPUT);      
  pinMode(u11Input0Pin, OUTPUT);      
  pinMode(u12Input0Pin, OUTPUT);
}

// This is where we determine which pins to update for a given motor and which values to set for the next
// stepper phase.
//
// The invert parameter is set when we're running the motor (and hence the stepper sequence) in reverse.
void NextStepperState(Motor motor, boolean invert)
{
  Pins_t phase_a_pin;
  Pins_t phase_b_pin;
  Pins_t input_a_pin;
  Pins_t input_b_pin;
  
  boolean phase_a_value;
  boolean phase_b_value;
  boolean input_a_value;
  boolean input_b_value;

  int* stepperState;

  Serial.println();
  switch(motor)
  {
    case elbow:
    {
      Serial.println("ELBOW");
      phase_a_pin = u1PhasePin; 
      phase_b_pin = u2PhasePin; 
      input_a_pin = u1Input0Pin; 
      input_b_pin = u2Input0Pin;
      stepperState = &stepElbow;
      break;
    }
    case shoulder:
    {
      Serial.println("SHOULDER");
      phase_a_pin = u3PhasePin; 
      phase_b_pin = u4PhasePin; 
      input_a_pin = u3Input0Pin; 
      input_b_pin = u4Input0Pin;
      stepperState = &stepShoulder;
      break;
    }
    case rwrist:
    {
      Serial.println("R-WRIST");
      phase_a_pin = u5PhasePin; 
      phase_b_pin = u6PhasePin; 
      input_a_pin = u5Input0Pin; 
      input_b_pin = u6Input0Pin;
      stepperState = &stepRwrist;
      break;
    }
    case base:
    {
      Serial.println("BASE");
      phase_a_pin = u9PhasePin; 
      phase_b_pin = u10PhasePin; 
      input_a_pin = u9Input0Pin; 
      input_b_pin = u10Input0Pin;
      stepperState = &stepBase;
      break;
    }
    case gripper:
    {
      Serial.println("[ERROR] - GRIPPER");
      phase_a_pin = u11PhasePin;
      phase_b_pin = u12PhasePin;
      input_a_pin = u11Input0Pin;
      input_b_pin = u12Input0Pin;
      stepperState = &stepGripper;
      break;
    }
    case lwrist:
    {
      Serial.println("L-WRIST");
      phase_a_pin = u13PhasePin; 
      phase_b_pin = u14PhasePin; 
      input_a_pin = u13Input0Pin; 
      input_b_pin = u14Input0Pin;
      stepperState = &stepLwrist;
      break;
    }
    default:
    {
      Serial.println("[ERROR] Unknown motor");
    }
  }

#ifdef DEBUG
  Serial.print("Stepper state: " );
  Serial.println(*stepperState);
#endif

  /* Stepper sequence used by the 3717 stepper controllers.
   * Currently set to use half-step,as described in Figure 5:
   * http://pdf.datasheetcatalog.com/datasheet/stmicroelectronics/1430.pdf
   * 
   * Modified sequence for faster current decay described in Figure 8:
   * http://pdf.datasheetcatalog.com/datasheet2/3/0781ylult7czhriharfiww4t3fwy.pdf
   */
  switch (*stepperState)
  {
    case 1:
    {
      phase_a_value = true; 
      phase_b_value = true; 
      input_a_value = true; 
      input_b_value = false;
      break;
    } 
    case 2:
    {
      phase_a_value = true; 
      phase_b_value = true; 
      input_a_value = false; 
      input_b_value = false;
      break;
    } 
    case 3:
    {
      phase_a_value = !invert;
      phase_b_value = invert;
      input_a_value = false; 
      input_b_value = true;
      break;
    } 
    case 4:
    {
      phase_a_value = !invert;
      phase_b_value = invert;
      input_a_value = false; 
      input_b_value = false;
      break;
    } 
    case 5:
    {
      phase_a_value = false; 
      phase_b_value = false; 
      input_a_value = true; 
      input_b_value = false;
      break;
    } 
    case 6:
    {
      phase_a_value = false; 
      phase_b_value = false; 
      input_a_value = false; 
      input_b_value = false;
      break;
    } 
    case 7:
    {
      phase_a_value = invert;
      phase_b_value = !invert;
      input_a_value = false; 
      input_b_value = true;
      break;
    }
    case 8:
    {
      phase_a_value = invert;
      phase_b_value = !invert;
      input_a_value = false; 
      input_b_value = false;
      *stepperState = 0;
      break;
    } 
    default:
    {
      //wtf? 
    }
  }

  (*stepperState)++;

#ifdef DEBUG
  Serial.print(phase_a_pin);
  Serial.print("  ");
  Serial.println(phase_a_value ? "HI" : "LO");
  Serial.print(phase_b_pin);
  Serial.print("  ");
  Serial.println(phase_b_value ? "HI" : "LO");
  Serial.print(input_a_pin);
  Serial.print("  ");
  Serial.println(input_a_value ? "HI" : "LO");
  Serial.print(input_b_pin);
  Serial.print("  ");
  Serial.println(input_b_value ? "HI" : "LO");
#endif

  // Push the sequence values to the motor pins.
  digitalWrite(phase_a_pin, phase_a_value);
  digitalWrite(phase_b_pin, phase_b_value);
  digitalWrite(input_a_pin, input_a_value);
  digitalWrite(input_b_pin, input_b_value);

  // We're functioning automatic and we are dancing mechanic!
}

// Move the motors according to the bitmask set in the commands variable.
void MoveMotors(int commands)
{
  if (commands & base_l)     { NextStepperState(base,     false); } else if (commands & base_r)     { NextStepperState(base,     true); }
  if (commands & elbow_l)    { NextStepperState(elbow,    false); } else if (commands & elbow_r)    { NextStepperState(elbow,    true); }
  if (commands & shoulder_l) { NextStepperState(shoulder, false); } else if (commands & shoulder_r) { NextStepperState(shoulder, true); }
  if (commands & lwrist_l)   { NextStepperState(lwrist,   false); } else if (commands & lwrist_r)   { NextStepperState(lwrist,   true); }
  if (commands & rwrist_l)   { NextStepperState(rwrist,   false); } else if (commands & rwrist_r)   { NextStepperState(rwrist,   true); }
  if (commands & gripper_l)  { NextStepperState(gripper,  false); } else if (commands & gripper_r)  { NextStepperState(gripper,  true); }
}
