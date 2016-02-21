

#include <stdio.h>
#include <iup.h>
#include <stdlib.h>
#include <string.h>
#include <MorseLib.h>
#include "MorseTool.h"


#define TXTMORSE_2 "txtMorse_2"
#define TXTBINARY_2 "txtBinary_2"
#define LBLMORSELEN_2 "lblMorseLen_2"
#define LBLBINARYLEN_2 "lblBinaryLen_2"

#define FRMT_MORSELEN_2 "Morse string length: %d"
#define FRMT_BINARYLEN_2 "Binary bit string length: %d"


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


static int cb_btnDecodeToMorse(Ihandle *btn);

static int cb_txtMorseAction(Ihandle *txt);
static int cb_txtBinaryAction(Ihandle *txt);

static int cb_btnCopyMorse(Ihandle *text);
static int cb_btnCopyBinary(Ihandle *text);

static int cb_btnClearMorse(Ihandle *btn);
static int cb_btnClearBinary(Ihandle *btn);

void textCopyClipboardFrom(Ihandle *textBox);







static int cb_btnDecodeToMorse(Ihandle *btn) {

	Ihandle *txtMorse, *txtBinary, *msgDialog;
	char *morseText, *binaryText;
	int morseLen, binaryLen;

	extern BSTTree binaryToMorse;           	/* Might be declared in the driver file */

	txtMorse = IupGetHandle(TXTMORSE_2);
	txtBinary = IupGetHandle(TXTBINARY_2);

	binaryText = IupGetAttribute(txtBinary, "VALUE");
	binaryLen = strlen(binaryText);
	morseText = (char *) malloc(binaryLen * sizeof(char));

	if (binaryLen == 0) {
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

	morse_convBinaryToMorse(&binaryToMorse, binaryText, binaryLen, morseText, &morseLen);
	*(morseText + morseLen) = '\0';

	/*printf("Decoded morse %s, len %d\n", morseText, morseLen);*/
	IupSetStrAttribute(txtMorse, "VALUE", morseText);

	END:
	cb_txtMorseAction(txtMorse);
	free(morseText);

	return IUP_DEFAULT;
}


static int cb_txtMorseAction(Ihandle *txt) {

	Ihandle *lblMorseLen;
	int charCount;

	lblMorseLen = IupGetHandle(LBLMORSELEN_2);
	charCount = IupGetInt(txt, "COUNT");

	IupSetfAttribute(lblMorseLen, "TITLE", FRMT_MORSELEN_2, charCount);
	IupRefresh(lblMorseLen);

	return IUP_DEFAULT;
}


static int cb_txtBinaryAction(Ihandle *txt) {

	Ihandle *lblBinaryLen;
	int charCount;

	lblBinaryLen = IupGetHandle(LBLBINARYLEN_2);
	charCount = IupGetInt(txt, "COUNT");

	IupSetfAttribute(lblBinaryLen, "TITLE", FRMT_BINARYLEN_2, charCount);
	IupRefresh(lblBinaryLen);

	return IUP_DEFAULT;
}


static int cb_btnCopyMorse(Ihandle *text) {

	Ihandle *txtMorse;

	txtMorse = IupGetHandle(TXTMORSE_2);
	textCopyClipboardFrom(txtMorse);

	return IUP_DEFAULT;
}

static int cb_btnCopyBinary(Ihandle *text) {

	Ihandle *txtBinary;

	txtBinary = IupGetHandle(TXTBINARY_2);
	textCopyClipboardFrom(txtBinary);

	return IUP_DEFAULT;
}


static int cb_btnClearMorse(Ihandle *btn) {

	Ihandle *txtMorse, *lblMorse;

	txtMorse = IupGetHandle (TXTMORSE_2);
	lblMorse = IupGetHandle (LBLMORSELEN_2);

	IupSetAttribute(txtMorse, "VALUE", 0);
	IupSetfAttribute(lblMorse, "TITLE", FRMT_MORSELEN_2, 0);

	return IUP_DEFAULT;
}


static int cb_btnClearBinary(Ihandle *btn) {

	Ihandle *txtBinary, *lblBinary;

	txtBinary = IupGetHandle (TXTBINARY_2);
	lblBinary = IupGetHandle (LBLBINARYLEN_2);

	IupSetAttribute(txtBinary, "VALUE", 0);
	IupSetfAttribute(lblBinary, "TITLE", FRMT_BINARYLEN_2, 0);

	return IUP_DEFAULT;
}





Ihandle *panel_createBinaryToMorse(void) {

	/*
		Declare all the GUI objects to be constructed
		Ihandle are gui objects (actually pointers to GUI objects)
	*/

	Ihandle *txtMorse, *txtBinary;
	Ihandle *lblMorseLen, *lblBinaryLen;
	Ihandle *btnClearMorse, *btnClearBinary, *btnDecodeToMorse;
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
	IupSetAttribute(txtBinary, "CUEBANNER", "Type-in binary code here");
	IupSetAttribute(txtMorse, "MULTILINE", "NO");
	IupSetAttribute(txtBinary, "MULTILINE", "NO");
	IupSetAttribute(txtMorse, "PADDING", "5x");
	IupSetAttribute(txtBinary, "PADDING", "5x");
	IupSetAttribute(txtMorse, "READONLY", "YES");
	IupSetAttribute(txtMorse, "ALIGNMENT", "ARIGHT");
	IupSetAttribute(txtMorse, "FONTSIZE", "12");
	IupSetAttribute(txtBinary, "FONTSIZE", "12");
	IupSetAttribute(txtMorse, "SIZE", "x14");
	IupSetAttribute(txtBinary, "SIZE", "x14");
	IupSetAttribute(txtBinary, "MASK", "[0/1]*");        /* Permit only <. - / ' '> */

	IupSetCallback(txtBinary, "VALUECHANGED_CB", (Icallback) cb_txtBinaryAction);

	lblMorseLen = IupLabel(0);
	lblBinaryLen = IupLabel(0);

	IupSetfAttribute(lblMorseLen, "TITLE", FRMT_MORSELEN_2, 0);
	IupSetfAttribute(lblBinaryLen, "TITLE", FRMT_BINARYLEN_2, 0);

	btnClearMorse = IupButton("Clear", 0);
	btnClearBinary = IupButton("Clear", 0);
	btnDecodeToMorse = IupButton("Decode", 0);

	btnCopyMorse = IupButton("Copy", 0);
	btnCopyBinary = IupButton("Copy", 0);

	IupSetAttribute(btnClearMorse, "RASTERSIZE", "55x30");
	IupSetAttribute(btnClearBinary, "RASTERSIZE", "55x30");
	IupSetAttribute(btnDecodeToMorse, "RASTERSIZE", "70x30");
	IupSetAttribute(btnCopyMorse, "RASTERSIZE", "55x30");
	IupSetAttribute(btnCopyBinary, "RASTERSIZE", "55x30");

	IupSetCallback(btnDecodeToMorse, "ACTION", (Icallback) cb_btnDecodeToMorse);
	IupSetCallback(btnCopyMorse, "ACTION", (Icallback) cb_btnCopyMorse);
	IupSetCallback(btnCopyBinary, "ACTION", (Icallback) cb_btnCopyBinary);
	IupSetCallback(btnClearMorse, "ACTION", (Icallback) cb_btnClearMorse);
	IupSetCallback(btnClearBinary, "ACTION", (Icallback) cb_btnClearBinary);

	frmMorseHbox = IupHbox(lblMorseLen, IupFill(), btnCopyMorse, btnClearMorse, 0);
	frmBinaryHbox = IupHbox(lblBinaryLen, IupFill(), btnCopyBinary, btnClearBinary, btnDecodeToMorse, 0);

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

	frmContainerVbox = IupVbox(frmBinary, IupFill(), frmMorse, 0);

	IupSetAttribute(frmContainerVbox, "NGAP", "15");
	IupSetAttribute(frmContainerVbox, "NMARGIN", "0x0");


	/*
		Register all necessary handlers globally
		So that they can be retrieved by other functions manipulate them
	*/

	IupSetHandle(TXTMORSE_2, txtMorse);
	IupSetHandle(TXTBINARY_2, txtBinary);
	IupSetHandle(LBLMORSELEN_2, lblMorseLen);
	IupSetHandle(LBLBINARYLEN_2, lblBinaryLen);
	IupSetHandle(PANEL_BINARYTOMORSE, frmContainerVbox);

	return frmContainerVbox;

}




