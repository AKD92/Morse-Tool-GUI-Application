


/************************************************************************************
	Implementation code of About Window with necessary callback functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/





#include <iup.h>
#include <stdlib.h>
#include "MorseTool.h"


#define BTN_CLOSE "btnClose"




static const char *strProjName = "Morse Tool (libmorse.a)";
static const char *strProjDesc = "This tool is a byproduct of my DSD project\n"
							"Secret message transmitter && receiver\n"
							"via Morse Code";
static const char *strProjSource = "Implemented in Arduino Microcontrollers";
static const char *strProjCompiler = "Compiled using: gcc 4.8.1 (32 bit)";
static const char *strProjProgrammer = "Programmed by : Ashis Kumar Das";
static const char *strProjDept = "Department of Engineering && Computer Science\n"
							"BRAC University";
static const char *strProjEmail = "mailto:akd.bracu@gmail.com";
static const char *strProjSrcLink = "https://github.com/AKD92"
										"/Morse-Tool-GUI-Application.git";



static int cb_btnClose(Ihandle *btn);



Ihandle *createAboutDialog(void) {
	
	Ihandle *lblProjName, *lblDesc, *lblArduino, *lblCompiler;
	Ihandle *lblAuthor, *lblDepartment, *lblEmail, *lblProjSource;
	Ihandle *lblSeparator;
	Ihandle *vbox1, *vbox2;
	Ihandle *vboxContainer, *bottomHbox;
	Ihandle *vboxWhole;
	Ihandle *btnClose, *dlgAbout;
	
	lblProjName = IupLabel(strProjName);
	lblDesc = IupLabel(strProjDesc);
	lblArduino = IupLabel(strProjSource);
	lblCompiler = IupLabel(strProjCompiler);
	lblAuthor = IupLabel(strProjProgrammer);
	lblDepartment = IupLabel(strProjDept);
	lblEmail = IupLink(strProjEmail, "akd.bracu@gmail.com");
	lblProjSource = IupLink(strProjSrcLink, "Source code on my GitHub account");
	lblSeparator = IupLabel(0);
	IupSetAttribute(lblSeparator, "SEPARATOR", "HORIZONTAL");
	IupSetAttribute(lblProjName, "ALIGNMENT", "ACENTER");
	IupSetAttribute(lblDesc, "ALIGNMENT", "ACENTER");
	IupSetAttribute(lblArduino, "ALIGNMENT", "ACENTER");
	IupSetAttribute(lblCompiler, "ALIGNMENT", "ACENTER");
	IupSetAttribute(lblAuthor, "ALIGNMENT", "ACENTER");
	IupSetAttribute(lblDepartment, "ALIGNMENT", "ACENTER");
	IupSetAttribute(lblEmail, "ALIGNMENT", "ACENTER");
	IupSetAttribute(lblProjSource, "ALIGNMENT", "ACENTER");
	
	vbox1 = IupVbox(lblProjName, lblDesc, lblArduino, lblCompiler, 0);
	IupSetAttribute(vbox1, "EXPANDCHILDREN", "YES");
	IupSetAttribute(vbox1, "NGAP", "7");
	IupSetAttribute(vbox1, "NMARGIN", "0x0");
	
	vbox2 = IupVbox(lblAuthor, lblDepartment, lblEmail, lblProjSource, 0);
	IupSetAttribute(vbox2, "EXPANDCHILDREN", "YES");
	IupSetAttribute(vbox2, "NGAP", "5");
	IupSetAttribute(vbox2, "NMARGIN", "0x0");
	
	vboxContainer = IupVbox(IupFill(), vbox1, lblSeparator, vbox2, IupFill(), 0);
	IupSetAttribute(vboxContainer, "NGAP", "10");
	IupSetAttribute(vboxContainer, "NMARGIN", "20x20");
	
	btnClose = IupButton("Close (Esc)", 0);
	IupSetAttribute(btnClose, "RASTERSIZE", "90x30");
	IupSetCallback(btnClose, "ACTION", (Icallback) cb_btnClose);
	
	bottomHbox = IupHbox(IupFill(), btnClose, 0);
	vboxWhole = IupVbox(vboxContainer, bottomHbox, 0);
	IupSetAttribute(vboxWhole, "NGAP", "10");
	IupSetAttribute(vboxWhole, "NMARGIN", "10x10");
	
	IupSetHandle(BTN_CLOSE, btnClose);
	
	dlgAbout = IupDialog(vboxWhole);
	IupSetAttribute(dlgAbout, "SHRINK", "YES");
	IupSetAttribute(dlgAbout, "PARENTDIALOG", MAINDIALOG);
	IupSetAttribute(dlgAbout, "TITLE", "About this tool");
	IupSetAttribute(dlgAbout, "DEFAULTESC", BTN_CLOSE);
	
	return dlgAbout;
}


static int cb_btnClose(Ihandle *btn) {
	
	return IUP_CLOSE;
}
