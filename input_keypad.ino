//
// Control the motor's actions using a keypad connected to the Arduino digital I/O pins.
//
void setup_keypad(void)
{
  pinMode(btnBaseA,     INPUT);
  pinMode(btnBaseB,     INPUT);
  pinMode(btnElbowA,    INPUT);
  pinMode(btnElbowB,    INPUT);
  pinMode(btnShoulderA, INPUT);
  pinMode(btnShoulderB, INPUT);
  pinMode(btnLwristA,   INPUT);
  pinMode(btnLwristB,   INPUT);
  pinMode(btnRwristA,   INPUT);
  pinMode(btnRwristB,   INPUT);
  pinMode(btnGripperA,  INPUT);
  pinMode(btnGripperB,  INPUT);
}

int read_keypad(void)
{
  int moveCommand = 0;
  
  // Read the button states.
  // Each motor is controlled by one of 2 buttons (one for each direction), which are obviously exclusive of each other.
  if (digitalRead(btnBaseA))     { moveCommand |= base_l; }     else if (digitalRead(btnBaseB))     { moveCommand |= base_r; };
  if (digitalRead(btnElbowA))    { moveCommand |= elbow_l; }    else if (digitalRead(btnElbowB))    { moveCommand |= elbow_r; };
  if (digitalRead(btnShoulderA)) { moveCommand |= shoulder_l; } else if (digitalRead(btnShoulderB)) { moveCommand |= shoulder_r; };
  if (digitalRead(btnLwristA))   { moveCommand |= lwrist_l; }   else if (digitalRead(btnLwristB))   { moveCommand |= lwrist_r; };
  if (digitalRead(btnRwristA))   { moveCommand |= rwrist_l; }   else if (digitalRead(btnRwristB))   { moveCommand |= rwrist_r; };
  if (digitalRead(btnGripperA))  { moveCommand |= gripper_l; }  else if (digitalRead(btnGripperB))  { moveCommand |= gripper_r; };
  
  return moveCommand;
}
