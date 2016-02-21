


#include <iup.h>
#include <stdio.h>
#include <BSTTree.h>
#include <MorseLib.h>
#include "MorseTool.h"





int main(void);

BSTTree morseToBinary;
BSTTree binaryToMorse;
BSTTree morseToText;
BSTTree textToMorse;





int main(void) {
	
	Ihandle *mainDialog;
	
	bst_init(&morseToBinary);
	bst_init(&binaryToMorse);
	bst_init(&morseToText);
	bst_init(&textToMorse);
	
	morse_createMorseToBinaryMapping(&morseToBinary);
	morse_createBinaryToMorseMapping(&binaryToMorse);
	morse_createMorseToAsciiMapping(&morseToText);
	morse_createAsciiToMorseMapping(&textToMorse);

	IupOpen(0, 0);

		mainDialog = createMainWindow();
		IupSetAttribute(mainDialog, "RASTERSIZE", "420x510");
		IupShowXY(mainDialog, IUP_CENTER, IUP_CENTER);
		IupMainLoop();

	IupClose();

	bst_destroy(&morseToBinary);
	bst_destroy(&binaryToMorse);
	bst_destroy(&morseToText);
	bst_destroy(&textToMorse);

	return 0;
}
