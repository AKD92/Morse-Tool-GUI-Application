


/************************************************************************************
	Implementation code for main() function and global variables
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
*************************************************************************************/




#include <iup.h>					/* Header file for GUI toolkit */
#include <stdio.h>					/* Header file for Standard IO */
#include <BSTTree.h>				/* Header file for Dictionary ADT */
#include <MorseLib.h>				/* Header file for Morse Library */
#include "MorseTool.h"				/* Header file for Global declarations */



/* Function prototype for main() function */
int main(void);




/* Dictionary data structure variables for code conversions */
BSTTree morseToBinary;
BSTTree binaryToMorse;
BSTTree morseToText;
BSTTree textToMorse;


/* Error message to show if something goes wrong */
static const char *errorMessage_1 = "Could not initialize Dictionary data structures\n"
							"which are needed for this application to perform\n"
							"necessary operations.\n\n"
							"Reason : Memory allocation failure.\n\n"
							"This application will now terminate.";
							
							
char *error_decode = "Decoding operation failed\n"
						"The specified decoding command could not be executed.\n\n"
						"Function returned abnormally, return value: %d.\n"
						"Possible reason: unsupported input combination.";





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
	/* We perform a simple Bitwise OR between four return values to determine this factor */
	isInitialized = (unsigned int) (init1 | init2 | init3 | init4);


	/* Initialize our GUI toolkit only for the first time */
	/* Parameters are argc and argv, not necessary, can be NULL (0) */
	IupOpen(0, 0);


		/* Check if our Dictionaries are initialized properly */
		/* If initialized, show main window and start Event Processing Loop */
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
			IupSetAttribute(mainDialog, "VALUE", errorMessage_1);
			
			/* Show this error message dialog on the screen */
			IupPopup(mainDialog, IUP_CENTER, IUP_CENTER);
			
			/* Explicit destruction is necessary (for popup dialogs) */
			IupDestroy(mainDialog);
		}


	/* Shuts down GUI toolkit, releases occupied system resources (if any) */
	IupClose();


	/* Destroy (releases memory of) all four Dictionary data structures */
	bst_destroy(&morseToBinary);
	bst_destroy(&binaryToMorse);
	bst_destroy(&morseToText);
	bst_destroy(&textToMorse);


	/* Return to the operating system */
	return 0;
}

