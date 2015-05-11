// Motors.
enum Motor
{
  elbow      = 0, // U1 & U2
  shoulder,       // U3 & U4
  rwrist,         // U5 & U6
                  // U7 & U8     (spare)
  base,           // U9 & U10
  gripper,        // U11 & U12   (unused)
  lwrist          // U13 & U14
};

// Bitmask for motor commands.
enum Command
{
  elbow_l    = 0x001,
  elbow_r    = 0x002,
  shoulder_l = 0x004,
  shoulder_r = 0x008,
  rwrist_l   = 0x010,
  rwrist_r   = 0x020,
  base_l     = 0x040,
  base_r     = 0x080,
  gripper_l  = 0x100,
  gripper_r  = 0x200,
  lwrist_l   = 0x400,
  lwrist_r   = 0x800
};

