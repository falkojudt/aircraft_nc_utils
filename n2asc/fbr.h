/*
 * Resource file for n2asc.
 */

static String fallback_resources[] =
  {
  "*defaultFontList:		-adobe-courier-bold-r-*-*-14-140-75-75-*-*-*-*",
  "*XmPushButton.height:		32",
  "*XmTextField.background:		Burlywood",
  "*XmTextField.foreground:		black",
  "*XmForm.horizontalSpacing:		8",
  "*XmForm.verticalSpacing:		8",

  "*buttonFrame.shadowType:		SHADOW_IN",
  "*buttonRC.XmPushButton.recomputeSize:False",
  "*buttonRC.XmPushButton.width:	130",
  "*buttonRC.entryAlignment:		ALIGNMENT_CENTER",
  "*buttonRC.orientation:		HORIZONTAL",
/*
 *	Dismiss/Reset buttons",
 */
  "*resetButton.labelString:		Reset",
  "*dismissButton.labelString:		Dismiss",
/*
 *	Defaults for First window to appear.
 */
  "*topLevelShell.x:			75",
  "*topLevelShell.y:			75",
  "*topLevelShell.title:		netCDF to ASCII 2.0.1",
  "*topLevelShell.iconName:		n2asc",
  "*topLevelForm.resizePolicy:		RESIZE_GROW",
  "*topLevelForm*buttonRC.spacing:	244",
  "*quitButton.labelString:		Quit",
  "*quitButton.traversalOn:		False",
  "*proceedButton.labelString:		Proceed",
  "*proceedButton.traversalOn:		False",
  "*fileNameRC*XmTextField.columns:	40",
  "*fileNameRC*XmTextField.maxLength:	256",
  "*fnRC.orientation:			HORIZONTAL",
  "*fnRC*XmLabel.alignment:		ALIGNMENT_END",
  "*fnRC*XmLabel.recomputeSize:		False",
  "*fnRC*XmLabel.width:			115",
  "*FNlabel0.labelString:		Input file:",
  "*FNlabel1.labelString:		Output file:",
  "*inputFileText.value:		/jnet/data/",
  "*outputFileText.value:		/jnet/data/",
/*
 *	Setup Window resources (2nd window to appear).
 */
  "*setupShell.x:			240",
  "*setupShell.y:			100",
  "*setupForm.horizontalSpacing:	8",
  "*setupForm.verticalSpacing:		8",
  "*setupForm.resizePolicy:		RESIZE_GROW",
  "*menuBar*setupPD_CB.labelString:	Setup",
  "*menuBar*setupPD_CB.mnemonic:	S",
  "*menuBar*editPD_CB.labelString:	Edit",
  "*menuBar*editPD_CB.mnemonic:		E",
  "*menuBar*cancelSetupButton.labelString:	Cancel",
  "*menuBar*cancelSetupButton.mnemonic:	C",
  "*menuBar*cancelSetupButton.accelerator:	Ctrl<Key>Q",
  "*menuBar*cancelSetupButton.acceleratorText:Ctrl-Q",
  "*menuBar*editTimeSlices.labelString:	Time Slices",
  "*menuBar*editTimeSlices.mnemonic:	T",
  "*menuBar*editTimeSlices.accelerator:	Ctrl<Key>T",
  "*menuBar*editTimeSlices.acceleratorText:Ctrl-T",
  "*menuBar*toggleOutput.labelString:	Toggle Output",
  "*menuBar*toggleOutput.mnemonic:	O",
  "*menuBar*toggleOutput.accelerator:	Ctrl<Key>O",
  "*menuBar*toggleOutput.acceleratorText:	Ctrl-O",
  "*goButton.height:			37",
  "*goButton.labelString:		Go",
  "*goButton.recomputeSize:		False",
  "*goButton.width:			120",
  "*timeDisplayText.background:		black",
  "*timeDisplayText.columns:		9",
  "*timeDisplayText.cursorPositionVisible:	False",
  "*timeDisplayText.editable:		False",
  "*timeDisplayText.foreground:		red",
  "*timeDisplayText.maxLength:		10",
  "*timeDisplayText.value:		00:00:00",
  "*timeDisplayText.x:			550",
  "*timeDisplayText.y:			10",
  "*listRC.resizeWidth:			False",
  "*listRC.width:			350",
  "*listTitle.alignment:		ALIGNMENT_BEGINNING",
  "*varList.background:			black",
  "*varList.foreground:			green",
  "*varList.listSizePolicy:		CONSTANT",
  "*varList.selectionPolicy:		EXTENDED_SELECT",
  "*varList.scrollBarDisplayPolicy:	STATIC",
  "*varList.visibleItemCount:		25",
  "*logText.background:			Gray",
  "*logText.editable:			FALSE",
  "*logText.editMode:			MULTI_LINE_EDIT",
  "*logText.rows:			3",
  "*logText.scrollHorizontal:		TRUE",
  "*logText.scrollVertical:		TRUE",
/*
 *	Time Slice Window
 */
  "*timeSliceShell.x:			75",
  "*timeSliceShell.y:			300",
  "*timeSliceRC.numColumns:		2",
  "*timeSliceRC.packing:		PACK_COLUMN",
  "*timeSliceRC.XmTextField.columns:	9",
  "*timeSliceRC.XmTextField.maxLength:	8",
  "*timeSliceRC.XmTextField.traversalOn:True",
  "*tsRC.entryAlignment:		ALIGNMENT_CENTER",
  "*tsRC.XmPushButton.recomputeSize:	False",
  "*tsRC.XmPushButton.width:		106",
  "*tsRC.orientation:			HORIZONTAL",
/*
 *	Pause Window
 */
  "*pauseForm.defaultPosition:		FALSE",
  "*pauseForm.x:			525",
  "*pauseForm.y:			225",
  "*pauseForm.horizontalSpacing:	8",
  "*pauseForm.verticalSpacing:		8",
  "*pauseForm.resizePolicy:		RESIZE_GROW",
  "*pauseForm.XmPushButton.width:	130",
  "*pauseForm*pauseStop.labelString:	Stop",
  "*pauseForm*pauseCont.labelString:	Continue",
/*
 *	Dialog Boxes
 */
  "*fileBox.defaultPosition:		FALSE",
  "*fileBox.x:				130",
  "*fileBox.y:				200",
  "*fileBox*textColumns:		50",
  "*fileBox*dialogTitle:		Select a File",
  "*errorBox.defaultPosition:		FALSE",
  "*errorBox.x:				450",
  "*errorBox.y:				100",
  "*errorBox*background:		DarkSlateGray",
  "*errorBox*dialogTitle:		Error Message",
  "*errorBox*foreground:		Red",
  "*errorBox*XmLabel.alignment:		ALIGNMENT_CENTER",
  "*queryBox*dialogTitle:		Need input",
  "*queryBox*alignment:			ALIGNMENT_CENTER",
  "*warnBox.defaultPosition:		FALSE",
  "*warnBox.x:				450",
  "*warnBox.y:				100",
  "*warnBox*background:			DarkSlateGray",
  "*warnBox*dialogTitle:		Warning Message",
  "*warnBox*foreground:			Yellow",
  "*warnBox*XmLabel.alignment:		ALIGNMENT_CENTER",
  NULL
  };
