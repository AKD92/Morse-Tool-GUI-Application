


#include <iup.h>
#include <stdio.h>
#include <BSTTree.h>
#include <MorseLib.h>
#include "MorseTool.h"



/* Function prototype for main() function */
int main(void);




/* Dictionary data structure variables for code conversions */
BSTTree morseToBinary;
BSTTree binaryToMorse;
BSTTree morseToText;
BSTTree textToMorse;


/* Error message to show if something goes wrong */
static const char *errorMessage = "Could not initialize Dictionary data structures\n"
							"needed for this application to perform necessary\n"
							"operations.\n\n"
							"Reason : Memory allocation failure.\n\n"
							"This application will now terminate.";





/* Program entry point, main() function */
int main(void) {
	
	
	/* Starts executing */
	/* First, declare necessary variables */
	Ihandle *mainDialog;
	int init1, init2, init3, init4;
	unsigned int isInitialized;
	
	
	/* Initialize all four Dictionary data structures (optional) */
	bst_init(&morseToBinary);
	bst_init(&binaryToMorse);
	bst_init(&morseToText);
	bst_init(&textToMorse);
	
	
	/* Feed all four Dictionaries the data (key:value) they need to contain */
	init1 = morse_createMorseToBinaryMapping(&morseToBinary);
	init2 = morse_createBinaryToMorseMapping(&binaryToMorse);
	init3 = morse_createMorseToAsciiMapping(&morseToText);
	init4 = morse_createAsciiToMorseMapping(&textToMorse);
	
	
	/* Determine of our Dictionary data structures are properly initialized or not */
	/* If all four (4) Dictionaries are initialized successfully, isInitialized = 0 */
	/* For any dictionary not having properly initialized, isInitialized != 0 */
	/* We perform a simple Bitwise OR of four return values to determine this factor */
	isInitialized = init1 | init2 | init3 | init4;


	/* Initialize our GUI toolkit only for the first time */
	/* Parameters are argc and argv, not necessary, can be NULL (0) */
	IupOpen(0, 0);


		/* Check if our Dictionaries are initialized properly */
		if (isInitialized == 0) {
			mainDialog = createMainWindow();
			IupSetAttribute(mainDialog, "RASTERSIZE", "420x510");
			IupShowXY(mainDialog, IUP_CENTER, IUP_CENTER);
			IupMainLoop();
		}
		/* If not initialized, show an error message and exit */
		else {
			mainDialog = IupMessageDlg();
			IupSetAttribute(mainDialog, "DIALOGTYPE", "ERROR");
			IupSetAttribute(mainDialog, "BUTTONS", "OK");
			IupSetAttribute(mainDialog, "TITLE", "Initialization Problem");
			IupSetAttribute(mainDialog, "VALUE", errorMessage);
			
			/* Show this error message dialog on the screen */
			IupPopup(mainDialog, IUP_CENTER, IUP_CENTER);
			
			/* Explicit destruction is necessary (for popup dialogs) */
			IupDestroy(mainDialog);
		}


	/* Shuts down GUI toolkit, releases occupied system resources (if any) */
	IupClose();


	/* Destroy (releases memory) all four Dictionary data structures */
	bst_destroy(&morseToBinary);
	bst_destroy(&binaryToMorse);
	bst_destroy(&morseToText);
	bst_destroy(&textToMorse);


	/* Return to the operating system */
	return 0;
}

