

#include <stdio.h>
#include <iup.h>
#include <stdlib.h>
#include <string.h>
#include <MorseLib.h>
#include "MorseTool.h"


#define TXTMORSE_1 "txtMorse_1"
#define TXTBINARY_1 "txtBinary_1"
#define LBLMORSELEN_1 "lblMorseLen_1"
#define LBLBINARYLEN_1 "lblBinaryLen_1"

#define FRMT_MORSELEN_1 "Morse string length: %d"
#define FRMT_BINARYLEN_1 "Binary bit string length: %d"


static char *generalInfo = "This command decodes morse code\n"
					"to corresponding binary code.\n"
					"To enter morse code, use following\n"
					"keyboard buttons :\n\n"
					". for a DOT\n"
					"- for a DASH\n"
					"/ for a Letter separator\n"
					"| for a Word separator\n\n"
					"Any other character except these will be\n"
					"unnecessary and not allowed.";
					

static int cb_btnDecodeToBinary(Ihandle *btn);

static int cb_txtMorseAction(Ihandle *txt);
static int cb_txtBinaryAction(Ihandle *txt);

static int cb_btnCopyMorse(Ihandle *text);
static int cb_btnCopyBinary(Ihandle *text);

static int cb_btnClearMorse(Ihandle *btn);
static int cb_btnClearBinary(Ihandle *btn);

void textCopyClipboardFrom(Ihandle *textBox);







static int cb_btnDecodeToBinary(Ihandle *btn) {

	Ihandle *txtMorse, *txtBinary, *msgDialog;
	char *morseText, *binaryText;
	int morseLen, binaryLen;

	extern BSTTree morseToBinary;           	/* Might be declared in the driver file */

	txtMorse = IupGetHandle(TXTMORSE_1);
	txtBinary = IupGetHandle(TXTBINARY_1);

	morseText = IupGetAttribute(txtMorse, "VALUE");
	morseLen = strlen(morseText);
	binaryText = (char *) malloc(4 * morseLen * sizeof(char));

	if (morseLen == 0) {
		msgDialog = IupMessageDlg();
		IupSetAttribute(msgDialog, "DIALOGTYPE", "INFORMATION");
		IupSetAttribute(msgDialog, "TITLE", "Decoding Procedure");
		IupSetAttribute(msgDialog, "VALUE", generalInfo);
		IupSetAttribute(msgDialog, "BOTTONS", "OK");
		IupSetAttribute(msgDialog, "PARENTDIALOG", MAINDIALOG);
		IupPopup(msgDialog, IUP_CENTER, IUP_CENTER);
		IupDestroy(msgDialog);
//		IupSetAttribute(txtBinary, "VALUE", 0);
		goto END;
	}

	morse_convMorseToBinary(&morseToBinary, morseText, morseLen, binaryText, &binaryLen);
	*(binaryText + binaryLen) = '\0';

	/*printf("Decoded binary %s, len %d\n", binaryText, binaryLen);*/
	IupSetStrAttribute(txtBinary, "VALUE", binaryText);

	END:
	cb_txtBinaryAction(txtBinary);
	free(binaryText);

	return IUP_DEFAULT;
}


static int cb_txtMorseAction(Ihandle *txt) {

	Ihandle *lblMorseLen;
	int charCount;

	lblMorseLen = IupGetHandle(LBLMORSELEN_1);
	charCount = IupGetInt(txt, "COUNT");

	IupSetfAttribute(lblMorseLen, "TITLE", FRMT_MORSELEN_1, charCount);
	IupRefresh(lblMorseLen);

	return IUP_DEFAULT;
}


static int cb_txtBinaryAction(Ihandle *txt) {

	Ihandle *lblBinaryLen;
	int charCount;

	lblBinaryLen = IupGetHandle(LBLBINARYLEN_1);
	charCount = IupGetInt(txt, "COUNT");

	IupSetfAttribute(lblBinaryLen, "TITLE", FRMT_BINARYLEN_1, charCount);
	IupRefresh(lblBinaryLen);

	return IUP_DEFAULT;
}


static int cb_btnCopyMorse(Ihandle *text) {

	Ihandle *txtMorse;

	txtMorse = IupGetHandle(TXTMORSE_1);
	textCopyClipboardFrom(txtMorse);

	return IUP_DEFAULT;
}

static int cb_btnCopyBinary(Ihandle *text) {

	Ihandle *txtBinary;

	txtBinary = IupGetHandle(TXTBINARY_1);
	textCopyClipboardFrom(txtBinary);

	return IUP_DEFAULT;
}


static int cb_btnClearMorse(Ihandle *btn) {

	Ihandle *txtMorse, *lblMorse;

	txtMorse = IupGetHandle (TXTMORSE_1);
	lblMorse = IupGetHandle (LBLMORSELEN_1);

	IupSetAttribute(txtMorse, "VALUE", 0);
	IupSetfAttribute(lblMorse, "TITLE", FRMT_MORSELEN_1, 0);

	return IUP_DEFAULT;
}


static int cb_btnClearBinary(Ihandle *btn) {

	Ihandle *txtBinary, *lblBinary;

	txtBinary = IupGetHandle (TXTBINARY_1);
	lblBinary = IupGetHandle (LBLBINARYLEN_1);

	IupSetAttribute(txtBinary, "VALUE", 0);
	IupSetfAttribute(lblBinary, "TITLE", FRMT_BINARYLEN_1, 0);

	return IUP_DEFAULT;
}





Ihandle *panel_createMorseToBinary(void) {
	
	/*
		Declare all the GUI objects to be constructed
		Ihandle are gui objects (actually pointers to GUI objects)
	*/

	Ihandle *txtMorse, *txtBinary;
	Ihandle *lblMorseLen, *lblBinaryLen;
	Ihandle *btnClearMorse, *btnClearBinary, *btnDecodeToBinary;
	Ihandle *btnCopyMorse, *btnCopyBinary;
	Ihandle *frmMorse, *frmBinary;

	Ihandle *frmMorseHbox, *frmBinaryHbox;
	Ihandle *frmMorseVbox, *frmBinaryVbox;
	Ihandle *frmContainerVbox;

	txtMorse = IupText(0);
	txtBinary = IupText(0);

	IupSetAttribute(txtMorse, "BORDER", "YES");
	IupSetAttribute(txtBinary, "BORDER", "YES");
	IupSetAttribute(txtMorse, "EXPAND", "HORIZONTAL");
	IupSetAttribute(txtBinary, "EXPAND", "HORIZONTAL");
	IupSetAttribute(txtMorse, "CUEBANNER", "Type-in morse code here");
	IupSetAttribute(txtMorse, "MULTILINE", "NO");
	IupSetAttribute(txtBinary, "MULTILINE", "NO");
	IupSetAttribute(txtMorse, "PADDING", "5x");
	IupSetAttribute(txtBinary, "PADDING", "5x");
	IupSetAttribute(txtBinary, "READONLY", "YES");
	IupSetAttribute(txtBinary, "ALIGNMENT", "ARIGHT");
	IupSetAttribute(txtMorse, "FONTSIZE", "12");
	IupSetAttribute(txtBinary, "FONTSIZE", "12");
	IupSetAttribute(txtMorse, "SIZE", "x14");
	IupSetAttribute(txtBinary, "SIZE", "x14");
	IupSetAttribute(txtMorse, "MASK", "[./-///|]*");        /* Permit only <. - / ' '> */

	IupSetCallback(txtMorse, "VALUECHANGED_CB", (Icallback) cb_txtMorseAction);

	lblMorseLen = IupLabel(0);
	lblBinaryLen = IupLabel(0);

	IupSetfAttribute(lblMorseLen, "TITLE", FRMT_MORSELEN_1, 0);
	IupSetfAttribute(lblBinaryLen, "TITLE", FRMT_BINARYLEN_1, 0);

	btnClearMorse = IupButton("Clear", 0);
	btnClearBinary = IupButton("Clear", 0);
	btnDecodeToBinary = IupButton("Decode", 0);
	
	btnCopyMorse = IupButton("Copy", 0);
	btnCopyBinary = IupButton("Copy", 0);

	IupSetAttribute(btnClearMorse, "RASTERSIZE", "55x30");
	IupSetAttribute(btnClearBinary, "RASTERSIZE", "55x30");
	IupSetAttribute(btnDecodeToBinary, "RASTERSIZE", "70x30");
	IupSetAttribute(btnCopyMorse, "RASTERSIZE", "55x30");
	IupSetAttribute(btnCopyBinary, "RASTERSIZE", "55x30");
	
	IupSetCallback(btnDecodeToBinary, "ACTION", (Icallback) cb_btnDecodeToBinary);
	IupSetCallback(btnCopyMorse, "ACTION", (Icallback) cb_btnCopyMorse);
	IupSetCallback(btnCopyBinary, "ACTION", (Icallback) cb_btnCopyBinary);
	IupSetCallback(btnClearMorse, "ACTION", (Icallback) cb_btnClearMorse);
	IupSetCallback(btnClearBinary, "ACTION", (Icallback) cb_btnClearBinary);

	frmMorseHbox = IupHbox(lblMorseLen, IupFill(), btnCopyMorse, btnClearMorse, btnDecodeToBinary, 0);
	frmBinaryHbox = IupHbox(lblBinaryLen, IupFill(), btnCopyBinary, btnClearBinary, 0);

	IupSetAttribute(frmMorseHbox, "NGAP", "5");
	IupSetAttribute(frmBinaryHbox, "NGAP", "5");
	IupSetAttribute(frmMorseHbox, "NMARGIN", "0x0");
	IupSetAttribute(frmBinaryHbox, "NAMRGIN", "0x0");
	
	frmMorseVbox = IupVbox(frmMorseHbox, txtMorse, 0);
	frmBinaryVbox = IupVbox(frmBinaryHbox, txtBinary, 0);

	IupSetAttribute(frmMorseVbox, "NGAP", "10");
	IupSetAttribute(frmBinaryVbox, "NGAP", "10");
	IupSetAttribute(frmMorseVbox, "NMARGIN", "10x10");
	IupSetAttribute(frmBinaryVbox, "NMARGIN", "10x10");

	frmMorse = IupFrame(frmMorseVbox);
	frmBinary = IupFrame(frmBinaryVbox);

	IupSetAttribute(frmMorse, "SUNKEN", "NO");
	IupSetAttribute(frmBinary, "SUNKEN", "NO");
	IupSetAttribute(frmMorse, "TITLE", "Morse Code");
	IupSetAttribute(frmBinary, "TITLE", "Binary Code");

	frmContainerVbox = IupVbox(frmMorse, IupFill(), frmBinary, 0);
	
	IupSetAttribute(frmContainerVbox, "NGAP", "15");
	IupSetAttribute(frmContainerVbox, "NMARGIN", "0x0");
	

	/*
		Register all necessary handlers globally
		So that they can be retrieved by other functions manipulate them
	*/

	IupSetHandle(TXTMORSE_1, txtMorse);
	IupSetHandle(TXTBINARY_1, txtBinary);
	IupSetHandle(LBLMORSELEN_1, lblMorseLen);
	IupSetHandle(LBLBINARYLEN_1, lblBinaryLen);
	IupSetHandle(PANEL_MORSETOBINARY, frmContainerVbox);
	
	return frmContainerVbox;
	
}




