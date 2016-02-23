


/************************************************************************************
	Implementation code of Morse To ASCII panel box + necessary callback functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
*************************************************************************************/





#include <stdio.h>
#include <iup.h>
#include <stdlib.h>
#include <string.h>
#include <MorseLib.h>
#include "MorseTool.h"


#define TXTMORSE_3 "txtMorse_3"
#define TXTASCII_1 "txtAscii_1"
#define LBLMORSELEN_3 "lblMorseLen_3"
#define LBLASCIILEN_1 "lblAsciiLen_1"

#define FRMT_MORSELEN_3 "Morse string length: %d"
#define FRMT_ASCIILEN_1 "ASCII Text length: %d"


static char *generalInfo = "This command decodes morse code\n"
					"to ASCII text string.\n"
					"To enter morse code, use following\n"
					"keyboard buttons :\n\n"
					". for a DOT\n"
					"- for a DASH\n"
					"/ for a Letter separator\n"
					"| for a Word separator\n\n"
					"Any other character except these will be\n"
					"unnecessary and not allowed.";
					
//static char *errorMsg = "Decoding operation failed\n"
//						"The specific library command could not be executed\n"
//						"And returned abnormally\n\n"
//						"Function return value: %d";


static int cb_btnDecodeToAscii(Ihandle *btn);

static int cb_txtMorseAction(Ihandle *txt);
static int cb_txtAsciiAction(Ihandle *txt);

static int cb_btnCopyMorse(Ihandle *text);
static int cb_btnCopyAscii(Ihandle *text);

static int cb_btnClearMorse(Ihandle *btn);
static int cb_btnClearAscii(Ihandle *btn);

void textCopyClipboardFrom(Ihandle *textBox);







static int cb_btnDecodeToAscii(Ihandle *btn) {

	Ihandle *txtMorse, *txtAscii, *msgDialog;
	char *morseText, *asciiText;
	int morseLen, asciiLen;

	Ihandle *errorDialog;
	char *errorText;
	int opReturnCode;

	extern char *error_decode;
	extern BSTTree morseToText;           	/* Might be declared in the driver file */

	txtMorse = IupGetHandle(TXTMORSE_3);
	txtAscii = IupGetHandle(TXTASCII_1);

	morseText = IupGetAttribute(txtMorse, "VALUE");
	morseLen = strlen(morseText);
	asciiText = (char *) malloc(morseLen * sizeof(char));

	if (morseLen == 0) {
		msgDialog = IupMessageDlg();
		IupSetAttribute(msgDialog, "DIALOGTYPE", "INFORMATION");
		IupSetAttribute(msgDialog, "TITLE", "Decoding Procedure");
		IupSetAttribute(msgDialog, "VALUE", generalInfo);
		IupSetAttribute(msgDialog, "BOTTONS", "OK");
		IupSetAttribute(msgDialog, "PARENTDIALOG", MAINDIALOG);
		IupPopup(msgDialog, IUP_CENTER, IUP_CENTER);
		IupDestroy(msgDialog);
//		IupSetAttribute(txtAscii, "VALUE", 0);
		goto END;
	}

	opReturnCode = morse_convMorseToAscii(
							&morseToText, morseText, morseLen, asciiText, &asciiLen);
							
	/* Check to see if decoding operation is successful or not */
	if (opReturnCode != 0) {

		errorText = (char *) malloc(strlen(error_decode) + 10);
		sprintf(errorText, error_decode, opReturnCode);

		errorDialog = IupMessageDlg();
		IupSetAttribute(errorDialog, "DIALOGTYPE", "ERROR");
		IupSetAttribute(errorDialog, "BUTTONS", "OK");
		IupSetAttribute(errorDialog, "TITLE", "Error");
		IupSetAttribute(errorDialog, "PARENTDIALOG", MAINDIALOG);
		IupSetAttribute(errorDialog, "VALUE", errorText);

		IupPopup(errorDialog, IUP_CENTER, IUP_CENTER);
		IupDestroy(errorDialog);
		free(errorText);
		goto END;
	}

	/* Add a nul terminator at the end of the output buffer */
	*(asciiText + asciiLen) = '\0';

	/*printf("Decoded ascii %s, len %d\n", asciiText, asciiLen);*/
	IupSetStrAttribute(txtAscii, "VALUE", asciiText);

	END:
	cb_txtAsciiAction(txtAscii);
	free(asciiText);

	return IUP_DEFAULT;
}


static int cb_txtMorseAction(Ihandle *txt) {

	Ihandle *lblMorseLen;
	int charCount;

	lblMorseLen = IupGetHandle(LBLMORSELEN_3);
	charCount = IupGetInt(txt, "COUNT");

	IupSetfAttribute(lblMorseLen, "TITLE", FRMT_MORSELEN_3, charCount);
	IupRefresh(lblMorseLen);

	return IUP_DEFAULT;
}


static int cb_txtAsciiAction(Ihandle *txt) {

	Ihandle *lblAsciiLen;
	int charCount;

	lblAsciiLen = IupGetHandle(LBLASCIILEN_1);
	charCount = IupGetInt(txt, "COUNT");

	IupSetfAttribute(lblAsciiLen, "TITLE", FRMT_ASCIILEN_1, charCount);
	IupRefresh(lblAsciiLen);

	return IUP_DEFAULT;
}


static int cb_btnCopyMorse(Ihandle *text) {

	Ihandle *txtMorse;

	txtMorse = IupGetHandle(TXTMORSE_3);
	textCopyClipboardFrom(txtMorse);

	return IUP_DEFAULT;
}

static int cb_btnCopyAscii(Ihandle *text) {

	Ihandle *txtAscii;

	txtAscii = IupGetHandle(TXTASCII_1);
	textCopyClipboardFrom(txtAscii);

	return IUP_DEFAULT;
}


static int cb_btnClearMorse(Ihandle *btn) {

	Ihandle *txtMorse, *lblMorse;

	txtMorse = IupGetHandle (TXTMORSE_3);
	lblMorse = IupGetHandle (LBLMORSELEN_3);

	IupSetAttribute(txtMorse, "VALUE", 0);
	IupSetfAttribute(lblMorse, "TITLE", FRMT_MORSELEN_3, 0);

	return IUP_DEFAULT;
}


static int cb_btnClearAscii(Ihandle *btn) {

	Ihandle *txtAscii, *lblAscii;

	txtAscii = IupGetHandle (TXTASCII_1);
	lblAscii = IupGetHandle (LBLASCIILEN_1);

	IupSetAttribute(txtAscii, "VALUE", 0);
	IupSetfAttribute(lblAscii, "TITLE", FRMT_ASCIILEN_1, 0);

	return IUP_DEFAULT;
}





Ihandle *panel_createMorseToText(void) {

	/*
		Declare all the GUI objects to be constructed
		Ihandle are gui objects (actually pointers to GUI objects)
	*/

	Ihandle *txtMorse, *txtAscii;
	Ihandle *lblMorseLen, *lblAsciiLen;
	Ihandle *btnClearMorse, *btnClearAscii, *btnDecodeToAscii;
	Ihandle *btnCopyMorse, *btnCopyAscii;
	Ihandle *frmMorse, *frmAscii;

	Ihandle *frmMorseHbox, *frmAsciiHbox;
	Ihandle *frmMorseVbox, *frmAsciiVbox;
	Ihandle *frmContainerVbox;

	txtMorse = IupText(0);
	txtAscii = IupText(0);

	IupSetAttribute(txtMorse, "BORDER", "YES");
	IupSetAttribute(txtAscii, "BORDER", "YES");
	IupSetAttribute(txtMorse, "EXPAND", "HORIZONTAL");
	IupSetAttribute(txtAscii, "EXPAND", "HORIZONTAL");
	IupSetAttribute(txtMorse, "CUEBANNER", "Type-in morse code here");
	IupSetAttribute(txtMorse, "MULTILINE", "NO");
	IupSetAttribute(txtAscii, "MULTILINE", "NO");
	IupSetAttribute(txtMorse, "PADDING", "5x");
	IupSetAttribute(txtAscii, "PADDING", "5x");
	IupSetAttribute(txtAscii, "READONLY", "YES");
	IupSetAttribute(txtAscii, "ALIGNMENT", "ARIGHT");
	IupSetAttribute(txtMorse, "FONTSIZE", "12");
	IupSetAttribute(txtAscii, "FONTSIZE", "12");
	IupSetAttribute(txtMorse, "SIZE", "x14");
	IupSetAttribute(txtAscii, "SIZE", "x14");
	IupSetAttribute(txtMorse, "MASK", "[./-///|]*");        /* Permit only <. - / ' '> */

	IupSetCallback(txtMorse, "VALUECHANGED_CB", (Icallback) cb_txtMorseAction);

	lblMorseLen = IupLabel(0);
	lblAsciiLen = IupLabel(0);

	IupSetfAttribute(lblMorseLen, "TITLE", FRMT_MORSELEN_3, 0);
	IupSetfAttribute(lblAsciiLen, "TITLE", FRMT_ASCIILEN_1, 0);

	btnClearMorse = IupButton("Clear", 0);
	btnClearAscii = IupButton("Clear", 0);
	btnDecodeToAscii = IupButton("Decode", 0);

	btnCopyMorse = IupButton("Copy", 0);
	btnCopyAscii = IupButton("Copy", 0);

	IupSetAttribute(btnClearMorse, "RASTERSIZE", "55x30");
	IupSetAttribute(btnClearAscii, "RASTERSIZE", "55x30");
	IupSetAttribute(btnDecodeToAscii, "RASTERSIZE", "70x30");
	IupSetAttribute(btnCopyMorse, "RASTERSIZE", "55x30");
	IupSetAttribute(btnCopyAscii, "RASTERSIZE", "55x30");

	IupSetCallback(btnDecodeToAscii, "ACTION", (Icallback) cb_btnDecodeToAscii);
	IupSetCallback(btnCopyMorse, "ACTION", (Icallback) cb_btnCopyMorse);
	IupSetCallback(btnCopyAscii, "ACTION", (Icallback) cb_btnCopyAscii);
	IupSetCallback(btnClearMorse, "ACTION", (Icallback) cb_btnClearMorse);
	IupSetCallback(btnClearAscii, "ACTION", (Icallback) cb_btnClearAscii);

	frmMorseHbox = IupHbox(lblMorseLen, IupFill(), btnCopyMorse, btnClearMorse, btnDecodeToAscii, 0);
	frmAsciiHbox = IupHbox(lblAsciiLen, IupFill(), btnCopyAscii, btnClearAscii, 0);

	IupSetAttribute(frmMorseHbox, "NGAP", "5");
	IupSetAttribute(frmAsciiHbox, "NGAP", "5");
	IupSetAttribute(frmMorseHbox, "NMARGIN", "0x0");
	IupSetAttribute(frmAsciiHbox, "NAMRGIN", "0x0");

	frmMorseVbox = IupVbox(frmMorseHbox, txtMorse, 0);
	frmAsciiVbox = IupVbox(frmAsciiHbox, txtAscii, 0);

	IupSetAttribute(frmMorseVbox, "NGAP", "10");
	IupSetAttribute(frmAsciiVbox, "NGAP", "10");
	IupSetAttribute(frmMorseVbox, "NMARGIN", "10x10");
	IupSetAttribute(frmAsciiVbox, "NMARGIN", "10x10");

	frmMorse = IupFrame(frmMorseVbox);
	frmAscii = IupFrame(frmAsciiVbox);

	IupSetAttribute(frmMorse, "SUNKEN", "NO");
	IupSetAttribute(frmAscii, "SUNKEN", "NO");
	IupSetAttribute(frmMorse, "TITLE", "Morse Code");
	IupSetAttribute(frmAscii, "TITLE", "ASCII Text");

	frmContainerVbox = IupVbox(frmMorse, IupFill(), frmAscii, 0);

	IupSetAttribute(frmContainerVbox, "NGAP", "15");
	IupSetAttribute(frmContainerVbox, "NMARGIN", "0x0");


	/*
		Register all necessary handlers globally
		So that they can be retrieved by other functions manipulate them
	*/

	IupSetHandle(TXTMORSE_3, txtMorse);
	IupSetHandle(TXTASCII_1, txtAscii);
	IupSetHandle(LBLMORSELEN_3, lblMorseLen);
	IupSetHandle(LBLASCIILEN_1, lblAsciiLen);
	IupSetHandle(PANEL_MORSETOTEXT, frmContainerVbox);

	return frmContainerVbox;

}


