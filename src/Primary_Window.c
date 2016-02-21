



#include <stdio.h>
#include <iup.h>
#include <stdlib.h>
#include <string.h>
#include <MorseLib.h>
#include "MorseTool.h"


int dlgAboutPosX, dlgAboutPosY;


static int cb_btnAbout(Ihandle *btn);
static int cb_btnExit(Ihandle *btn);
static int cb_keyPress(Ihandle *hnd, int key);

static int cb_flatButton1(Ihandle *btn);
static int cb_flatButton2(Ihandle *btn);
static int cb_flatButton3(Ihandle *btn);
static int cb_flatButton4(Ihandle *btn);



void textCopyClipboardFrom(Ihandle *textBox);









static int cb_keyPress(Ihandle *hnd, int key) {
	
	Ihandle *panel_z;
	Ihandle *controlRadio;
	Ihandle *toggle1, *toggle2, *toggle3, *toggle4;
	
	panel_z = IupGetHandle(PANEL_Z);
	controlRadio = IupGetHandle(CONTROL_RADIO);
	toggle1 = IupGetHandle(TOGGLE_MORSETOBINARY);
	toggle2 = IupGetHandle(TOGGLE_BINARYTOMORSE);
	toggle3 = IupGetHandle(TOGGLE_MORSETOTEXT);
	toggle4 = IupGetHandle(TOGGLE_TEXTTOMORSE);
	
	switch (key) {
		case K_F1 :
			IupSetAttribute(controlRadio, "VALUE", TOGGLE_MORSETOBINARY);
			IupSetAttribute(panel_z, "VALUE", PANEL_MORSETOBINARY);
			IupSetFocus(toggle1);
//			printf("Pressed F1\n");
			break;
		case K_F2 :
			IupSetAttribute(controlRadio, "VALUE", TOGGLE_BINARYTOMORSE);
			IupSetAttribute(panel_z, "VALUE", PANEL_BINARYTOMORSE);
			IupSetFocus(toggle2);
//			printf("Pressed F2\n");
			break;
		case K_F3 :
			IupSetAttribute(controlRadio, "VALUE", TOGGLE_MORSETOTEXT);
			IupSetAttribute(panel_z, "VALUE", PANEL_MORSETOTEXT);
			IupSetFocus(toggle3);
//			printf("Pressed F3\n");
			break;
		case K_F4 :
			IupSetAttribute(controlRadio, "VALUE", TOGGLE_TEXTTOMORSE);
			IupSetAttribute(panel_z, "VALUE", PANEL_TEXTTOMORSE);
			IupSetFocus(toggle4);
//			printf("Pressed F4\n");
			break;
	}
	
	return IUP_CONTINUE;
}


static int cb_btnExit(Ihandle *btn) {

	return IUP_CLOSE;
}


void textCopyClipboardFrom(Ihandle *textBox) {

	char *text, *msgText, *msgFormat, *dlgType;
	int length;
	Ihandle *clipboard, *msgDialog;

	msgText = 0;
	msgFormat = 0;
	dlgType = 0;

	text = IupGetAttribute(textBox, "VALUE");
	length = strlen(text);

	if (length == 0) {

		msgFormat = "Nothing to copy. Text is empty.";
		msgText = (char *) malloc(strlen(msgFormat) + 1);

		if (msgText == 0) return;

		strcpy(msgText, msgFormat);
		dlgType = "WARNING";
	}
	else {

		clipboard = IupClipboard();
		IupSetAttribute(clipboard, "TEXT", 0);
		IupSetAttribute(clipboard, "TEXT", text);
		IupDestroy(clipboard);

		msgFormat = "Text copied to clipboard, length: %d";
		msgText = (char *) malloc(strlen(msgFormat) + 1);

		if (msgText == 0) return;

		sprintf(msgText, msgFormat, length);
		dlgType = "INFORMATION";
	}

	msgDialog = IupMessageDlg();

	IupSetAttribute(msgDialog, "DIALOGTYPE", dlgType);
	IupSetAttribute(msgDialog, "BUTTONS", "OK");
	IupSetAttribute(msgDialog, "TITLE", "Copy text");
	IupSetAttribute(msgDialog, "PARENTDIALOG", MAINDIALOG);
	IupSetAttribute(msgDialog, "VALUE", msgText);

	IupPopup(msgDialog, IUP_CENTER, IUP_CENTER);

	IupDestroy(msgDialog);
	free(msgText);

	return;
}


static int cb_btnAbout(Ihandle *btn) {

	Ihandle *dlgAbout;

	dlgAbout = createAboutDialog();
	IupSetAttribute(dlgAbout, "RASTERSIZE", "350x380");
	IupPopup(dlgAbout, dlgAboutPosX, dlgAboutPosY);
	IupGetIntInt(dlgAbout, "SCREENPOSITION", &dlgAboutPosX, &dlgAboutPosY);
	IupDestroy(dlgAbout);

	return IUP_DEFAULT;
}


static int cb_flatButton1(Ihandle *btn) {

	Ihandle *panel_z;

	panel_z = IupGetHandle(PANEL_Z);
	IupSetAttribute(panel_z, "VALUE", PANEL_MORSETOBINARY);

	return IUP_DEFAULT;
}

static int cb_flatButton2(Ihandle *btn) {

	Ihandle *panel_z;

	panel_z = IupGetHandle(PANEL_Z);
	IupSetAttribute(panel_z, "VALUE", PANEL_BINARYTOMORSE);

	return IUP_DEFAULT;
}

static int cb_flatButton3(Ihandle *btn) {

	Ihandle *panel_z;

	panel_z = IupGetHandle(PANEL_Z);
	IupSetAttribute(panel_z, "VALUE", PANEL_MORSETOTEXT);

	return IUP_DEFAULT;
}

static int cb_flatButton4(Ihandle *btn) {

	Ihandle *panel_z;

	panel_z = IupGetHandle(PANEL_Z);
	IupSetAttribute(panel_z, "VALUE", PANEL_TEXTTOMORSE);

	return IUP_DEFAULT;
}




Ihandle *panel_createControl(void) {

	Ihandle *radioControl;
	Ihandle *hbox;
	Ihandle *fbtn1, *fbtn2, *fbtn3, *fbtn4;

	fbtn1 = IupFlatButton("Morse To Binary");
	fbtn2 = IupFlatButton("Binary To Morse");
	fbtn3 = IupFlatButton("Morse To Text");
	fbtn4 = IupFlatButton("Text To Morse");

	IupSetAttribute(fbtn1, "TOGGLE", "YES");
	IupSetAttribute(fbtn2, "TOGGLE", "YES");
	IupSetAttribute(fbtn3, "TOGGLE", "YES");
	IupSetAttribute(fbtn4, "TOGGLE", "YES");
	IupSetAttribute(fbtn1, "RASTERSIZE", "x33");
	IupSetAttribute(fbtn2, "RASTERSIZE", "x33");
	IupSetAttribute(fbtn3, "RASTERSIZE", "x33");
	IupSetAttribute(fbtn4, "RASTERSIZE", "x33");
	IupSetAttribute(fbtn1, "TIP", "Press F1");
	IupSetAttribute(fbtn2, "TIP", "Press F2");
	IupSetAttribute(fbtn3, "TIP", "Press F3");
	IupSetAttribute(fbtn4, "TIP", "Press F4");

	IupSetCallback(fbtn1, "VALUECHANGED_CB", (Icallback) cb_flatButton1);
	IupSetCallback(fbtn2, "VALUECHANGED_CB", (Icallback) cb_flatButton2);
	IupSetCallback(fbtn3, "VALUECHANGED_CB", (Icallback) cb_flatButton3);
	IupSetCallback(fbtn4, "VALUECHANGED_CB", (Icallback) cb_flatButton4);

	IupSetHandle(TOGGLE_MORSETOBINARY, fbtn1);
	IupSetHandle(TOGGLE_BINARYTOMORSE, fbtn2);
	IupSetHandle(TOGGLE_MORSETOTEXT, fbtn3);
	IupSetHandle(TOGGLE_TEXTTOMORSE, fbtn4);

	hbox = IupHbox(IupFill(), fbtn1, fbtn2, fbtn3, fbtn4, IupFill(), 0);
	IupSetAttribute(hbox, "NGAP", "5");
	IupSetAttribute(hbox, "NMARGIN", "0x10");

	radioControl = IupRadio(hbox);
	IupSetHandle(CONTROL_RADIO, radioControl);

	return radioControl;
}





Ihandle *createMainWindow(void) {

	Ihandle *panel1, *panel2, *panel3, *panel4;
	Ihandle *panel_control, *frm_control;
	Ihandle *panel_z;
	Ihandle *wholeVbox, *bottomHbox;
	Ihandle *btnAbout, *btnExit;
	Ihandle *dlgMain;
	
	dlgAboutPosX = IUP_CENTER;
	dlgAboutPosY = IUP_CENTER;
	
	panel1 = panel_createMorseToBinary();
	panel2 = panel_createBinaryToMorse();
	panel3 = panel_createMorseToText();
	panel4 = panel_createTextToMorse();
	
	panel_z = IupZbox(panel1, panel2, panel3, panel4, 0);
	IupSetAttribute(panel_z, "NMARGIN", "0x0");
	IupSetAttribute(panel_z, "EXPAND", "YES");
	IupSetHandle(PANEL_Z, panel_z);
	
	panel_control = panel_createControl();
	frm_control = IupFrame(panel_control);
	IupSetAttribute(frm_control, "SUNKEN", "NO");
	IupSetAttribute(frm_control, "TITLE", "Control Panel");
	
	btnAbout = IupButton("About", 0);
	btnExit = IupButton("Exit Program", 0);
	IupSetAttribute(btnAbout, "RASTERSIZE", "65x30");
	IupSetAttribute(btnExit, "RASTERSIZE", "95x30");
	IupSetCallback(btnAbout, "ACTION", (Icallback) cb_btnAbout);
	IupSetCallback(btnExit, "ACTION", (Icallback) cb_btnExit);
	IupSetHandle(BTNEXIT, btnExit);
	
	bottomHbox = IupHbox(IupFill(), btnAbout, btnExit, 0);
	IupSetAttribute(bottomHbox, "NGAP", "7");
	IupSetAttribute(bottomHbox, "NMARGIN", "0x0");
	
	wholeVbox = IupVbox(frm_control, IupFill(), panel_z, IupFill(), bottomHbox, 0);
	IupSetAttribute(wholeVbox, "NGAP", "7.5");
	IupSetAttribute(wholeVbox, "NMARGIN", "15x15");

	dlgMain = IupDialog(wholeVbox);
	IupSetAttribute(dlgMain, "SHRINK", "YES");
	IupSetAttribute(dlgMain, "TITLE", "Morse Tool (libmorse.a)");
	IupSetAttribute(dlgMain, "DEFAULTESC", BTNEXIT);
	IupSetCallback(dlgMain, "K_ANY", (Icallback) cb_keyPress);
	
	IupSetHandle(MAINDIALOG, dlgMain);

	return dlgMain;
}

