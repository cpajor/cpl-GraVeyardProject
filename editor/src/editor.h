#ifndef EDITOR_H
#define EDITOR_H
// GENERIC INPUT - keyboard

#define CKEY_NONE 0 

#define CKEY_LEFT 1 
#define CKEY_RIGHT 2
#define CKEY_UP 3
#define CKEY_DOWN 4
// SPACEBAR key
#define CKEY_JUMP 5
// LEFT CTRL key
#define CKEY_ATTACK 6 
// LEFT SHIFT key
#define CKEY_ATTACK2 7 
// LEFT ALT key
#define CKEY_ALT 8
// ESC key
#define CKEY_ESC 9 
// ENTER key
#define CKEY_ENTER 10 

// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
void keyboard_extended(unsigned int key, char state);

void cpl_updateView();

void cworld_save();
void cworld_load();
void cworld_new();

#endif // !EDITOR_H