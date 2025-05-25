#pragma once

#define BLOCK_PROPS_BASE   0b00000000  // Base (basically a block)
#define BLOCK_PROPS_SOLID  0b00000001  // Solid
#define BLOCK_PROPS_INVIS  0b00000010  // Invisible
#define BLOCK_PROPS_PSPAWN 0b00000100  // Player Spawn
#define BLOCK_PROPS_KILL   0b00001000  // Killbrick
#define BLOCK_PROPS_STICKY 0b00010000  // Sticky
#define BLOCK_PROPS_JUMP   0b00100000  // Jump pad
#define BLOCK_PROPS_BREAK  0b01000000  // Breakable
#define BLOCK_PROPS_LVLSWP 0b10000000  // Level Swap