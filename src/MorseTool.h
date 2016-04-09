


/************************************************************************************
	Global header file for Morse Tool Application
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef MORSE_WINDOW_H
#define MORSE_WINDOW_H




#include <iup.h>





#define MAINDIALOG "Primary_Window"
#define BTNEXIT "btnExit"

#define TOGGLE_MORSETOBINARY "toggle_morseToBinary"
#define TOGGLE_BINARYTOMORSE "toggle_binaryToMorse"
#define TOGGLE_MORSETOTEXT "toggle_morseToText"
#define TOGGLE_TEXTTOMORSE "toggle_textToMorse"

#define PANEL_MORSETOBINARY "panel_morseToBinary"
#define PANEL_BINARYTOMORSE "panel_binaryToMorse"
#define PANEL_MORSETOTEXT "panel_morseToText"
#define PANEL_TEXTTOMORSE "panel_textToMorse"

#define PANEL_Z "panel_ZBOX"
#define CONTROL_RADIO "control_radioSelect"



Ihandle *createMainWindow(void);

Ihandle *panel_createMorseToBinary(void);

Ihandle *panel_createBinaryToMorse(void);

Ihandle *panel_createMorseToText(void);

Ihandle *panel_createTextToMorse(void);

Ihandle *panel_createControl(void);


Ihandle *createAboutDialog(void);



#endif

