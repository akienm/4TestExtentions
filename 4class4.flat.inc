////////////////////////////////////////////////////////////////////////////
//
// Name:				4CLASS4.INC
//
// Purpose:				Library for extending 4Tst
//
// Requires:			BWCOMPAT.INC, MSW32.INC, REGISTRY.INC (Included with Silk)
//						
// Compatibility:		Tested on SilkTest v5.x thru 8.x
//						Running on MS Windows (most of this code
//						should work on other platforms) 
//
// Original Author: 	Akien MacIain
// Initial Date: 		05/1993 (v1.0)
// Last Edit: 			see the constant EXTENSION_LIBRARY_REVISION
//
// Copyright (c) 1992 thru 2006 Akien MacIain
// All Rights Reserved. This code is distributed as freeware, and may
// be distributed provided this notice is kept in tact.
//
// cDATASOURCE by Philip Boatwright, 8/2002
//
// NOTES (Expand outline for notes):
	//
	// COMPATIBILITY:
	//
	// This library has been tested primarially on Microsoft Windows.
	// A few of the features of this library are Windows specific, but not many.
	//
	// Please note that this is a complete rewrite from version 3 of these
	// libraries. Most of the interfaces have changed to create more
	// consistancy. 4CODEx.INC is no longer required, but is built in.
	//
	// A few things have been removed all together, such as DLG_Dismiss,
	// many things have been renamed, and several have been rewritten.
	// Details are in the Revision Information section below.
	//
	// GENERAL:
	//
	// Stylistic Note: As 4Test does not support private data members in a class,
	// items with two underscores at the beginning of their name are intended to
	// be private, and are subject to change. Methods marked private will also
	// follow this convention, even though there isn't a limitation on making
	// a member function private.
	//
	// In the documentation, property names are marked either rw ro wo
	// for read/write, read only, and write only.
	//
	// A NOTE TO DEVELOPERS:
	//
	// If you're changing this file, it should compile OK with no additional
	// files. The intent of this library is to be generic extensions to 4Test
	// unrelated to any specific company, platform or application. Having
	// said that, there are some features in this library that only work
	// under MS Windows, because that's where I've done all my development.
	//
	// REVISION NOTE:
	//
	// 5 of the functions in this library were originally written by other people.
	// Credit has been given where their code was left in tact, however it
	// was not given on code that has been completely rewritten because it
	// was unnecessarly complex. If even 1 line of code from the original
	// function or method were used (excepting the return statement), the
	// originator is noted.
	//
	// REVISION INFORMATION:
	//
	// 8/17/2001 Akien MacIain - Began rewrite to v4
		//
		// This list is as close to complete as I could manage, but I'm sure some things
		// were left out. -AM
		//
		// GENERAL-------------------------------------------------------------
		// Spliced 4CODE into 4CLASS
		// Grouped functions by type
		// Created outline structure for the whole file
		// Rewrote all documentation
		//
		// CONSTANTS & DATA TYPES----------------------------------------------
		// Renamed library error CONSTANTS
		// Renamed library version number constant names
		// Modified TEXT to be STRING, LIST, WINDOW
		// Added LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS
		//
		// REMOVED-------------------------------------------------------------
		// Removed FM_INIOPEN (now obsolete)
		// Removed STRINGorWINDOW, STRINGorLIST and all those other similar types
		// Removed DLG_Dismiss - I believe it was unused
		// Removed Tag_IsWindow - I believe it was unused
		// Removed WND_GetAppMainWindowTag(s), replaced by GetUltimateParent
		// Removed WND_Status() (the oldest function in this library) replaced with GetWindowStatus()
		//
		// RENAMED-------------------------------------------------------------
		// Renamed Data extraction functions to Get<something>
		// Renamed data type conversion functions to Make<type> including Parse, ParseWS, etc.
		// Renamed data typing function names to IsVar<type>
		// Fixed spelling errors of EXTENTION to EXTENSION
		//
		// ADDED---------------------------------------------------------------
		// Added MakeText(t) converts any TEXT type to list of string
		// Added GetLargest() and GetSecondLargest()
		// Added ListReverse()
		// Added GetUltimateParent(w) (replaces WND_GetAppMainWindowTag(s))
		// Added GetWindowStatus(w) (replaces WND_GetStatus(s))
		// Added MakeListFromRecord(r)
		//
		// CHANGED-------------------------------------------------------------
		// Modified GetWindowStatus() to take WNDTAG or WINDOW
		// Rewrote ParseWS (now MakeListOfWordsFromString) to make it MUCH simpler
		// Rewrote GetSmallest() and GetSecondSmallest() to make them MUCH simpler
		// Simplified Contains()
		// Rewrote lContains(), much more consistant behavior now
		// Rewrote rpContains()
		// Simplified TAG_StripAll()
		// Rewrote ListAdd() from scratch.
		// Modified ListReverse() and ListAdd() to return the modified list. Helps in testing.
		// Rewrote TAG_StripParentage()
		//
		// OTHER---------------------------------------------------------------
		// Created test suites for code
		// Fixed zillions of bugs
		//
		// GLOBAL INSTANCES----------------------------------------------------
		// Moved all cSYSTEM code into cSystem, and made it inherit from cBASE
		// Added machine switching to cSystem
		// Added color depth method and properties to cSystem
		//
		// WINDOW OBJECT LIBRARY CHANGES---------------------------------------
		// Added SmartMessageBox class. Uses a few code fragments from DLG_Dismiss()
		// Added DOS_ classes for manipulating character/command line based apps
		//
		// ABSTRACT OBJECT LIBRARY CHANGES-------------------------------------
		// Marked all private methods as private
		// Added cDATE
		// Added cDATASOURCE (by Phil Boatwright)
		// Added DOS_ window classes for operating DOS apps which function via forms
		// Added to cBASE IsOfClass so as to allow other code to determine if it can work with an object
		// Added to cBASE additional methods to make it more like AnyWin
		// Added to cBASE lsClassFieldList, GetFieldsOfObject() and AssignValues(a)
		// Added to cBASE a group of functions for enumerating the fields or properties of a class
		// Added to cBASE persistant storage
		// Added to cBASE DeepCopy()
		// Added to cBASE VerifyIsOfClass - raises exception if no match
		// Added to cBASE sRawPassedValue property, doesn't run the TAG_StripAll(). Always has leading '/'
		// Rewrote cFILE, much simpler interfaces, no duplication
		// Rewrote cFILE, no longer requires you to define __sFileName, now you define as sFileName
		// Rewrote cTEXTFILE, much smarter about how it determines if there are unsaved changes
		// Rewrote cOPENFILE - simplified - use APPEND() if logging
		// Added to cOPENFILE - ReadValue() and WriteValue() for saving data of any type
		// Added to cEXEFILE - now supports RunAndWait(), RunSafe(), and RunAndWaitSafe()
		// Removed cEXEANDWAIT
		// Removed cEXEANDWAITSAFE
		// Removed cSYSTEM, moved that functionality into cSystem global instance
		// Rewrote cINIFILE - simplified
		//
	// 6/14/2006 Akien MacIain - Updated for SilkTest 8 
	//                           (lost some of the GUI types previously supported 
	//                            by SilkTest)
	// Requires: 
	// blat.exe
	// wizmo
	// Properties.dll
	// restart.exe
//
////////////////////////////////////////////////////////////////////////////

use "bwcompat.inc";
use "msw32.inc";
use "registry.inc";

///////////////////////////////////////////////////////////////////////////

// Expand for CONSTANTS used in this code
{
	const EXTENSION_LIBRARY_VERSION = 4.0; 					// changed for v4
	const EXTENSION_LIBRARY_REVISION = 0.20060614;			// changed for v4
	
	const DATA_DIR 		= "c:\cvs_data";
	
	const EMPTYSTRING 	= "";
	const DoubleQuote 	= chr(34);
	const SingleQuote 	= chr(39);
	const LeftBrace 	= chr(123);
	const RightBrace 	= chr(125);
	const CRLF 			= chr (13) + chr (10);
	const crlf 			= CRLF;
	const CR 			= chr (13);
	const cr 			= CR;
	const LF 			= chr(10);
	const lf 			= LF;
	const Tab		 	= chr(9);
	const NBSP			= "&nbsp";
	
	const YES 			= TRUE;
	const ON  			= TRUE;
	const NO  			= FALSE;
	const OFF 			= FALSE;
	const PASS 			= FALSE;
	const FAIL  		= FALSE;
	
	const FM_CLOSED 	= 0; 	// Rounds out file mode flags	// in v3 there was yet another one. Now obsolete.
	
	const LIBERROR_CANT_CHANGE_STATIC_READ_ONLY = -30001;
	const LIBERROR_PROTECTION_FAULT_ON_STATIC	= -30002;
	const LIBERROR_TIMER_FAILURE				= -30003;
	const LIBERROR_FEATURE_NOT_YET_IMPLEMENTED 	= -30004;	// new for v4
	
	const LIBERROR_INVALID_DATA_TYPE			= -30101;
	const LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS	= -30102;	// new for v4
	const LIBERROR_WRONG_NUMBER_OF_ARGUMENTS	= -30104;	// new for v4
	const LIBERROR_FORMAT_INVALID				= -30105;	// new for v4
	const LIBERROR_WRONG_NUMBER_OF_ELEMENTS		= -30106;	// new for v4
	const LIBERROR_FIELD_NAME_MISSING			= -30107;	// new for v4
	
	const LIBERROR_CANT_PERFORM_ASSIGNMENT      = -30201;	// new for v4
	const LIBERROR_STACK_UNDERFLOW				= -30202;	// new for v4
	const LIBERROR_CANT_GET_OS_DATA				= -30203;	// new for v4
	
	const LIBERROR_FILE_DELETE_FAILED			= -30301;	// new for v4
	const LIBERROR_FILE_NOT_FOUND				= -30302;	// new for v4
	const LIBERROR_FILE_SHARING_VIOLATION		= -30303;	// new for v4
	
	const LIBERROR_CANT_CLOSE_WINDOW			= -30401;	// new for v4
	const LIBERROR_CANT_CLOSE_OBSCURING_WINDOW	= -30402;	// new for v4
	
	const LIBERROR_DOS_WINDOW_OBJECT_NOT_FOUND	= -30501;	// new for v4
	const LIBERROR_DOS_CONTROL_NOT_RESPONDING 	= -30502;	// new for v4
	
	// type EXCEPTION is enum  // from 4test.inc for reference
	{
		// // 4TEST
		// 
		// E_ABORT          = -10100
		// E_ACCESS         = -10200
		// E_AGENT          = -10300
		// E_ARRAY_SIZE     = -10400
		// E_ASSERT_FAILED  = -10500
		// E_ASSIGN         = -10600
		// E_BAD_ARG        = -10700
		// E_BAD_INDEX      = -10800
		// E_BUSY           = -10900
		// E_CLASS_MISMATCH = -11000
		// E_CONST          = -11100
		// E_DATABASE       = -11200
		// E_DEADLOCK       = -11300
		// E_DISABLED       = -11400
		// E_DIVIDE_BY_ZERO = -11500
		// E_FILE           = -11600
		// E_HALT_THREAD    = -11700
		// E_HANDLE         = -11800
		// E_INCOMPAT_TYPES = -11900
		// E_INTERNAL       = -12000
		// E_LIST_FULL      = -12100
		// E_NO_LIST_OPEN   = -12200
		// E_NO_RETVAL      = -12300
		// E_NULL           = -12400
		// E_NUM_ARGS       = -12500
		// E_OUT_OF_MEMORY  = -12600
		// E_SEMAPHORE      = -12700
		// E_STR_OVERFLOW   = -12800
		// E_SYNTAX         = -12900
		// E_SYSTEM         = -13000
		// E_TIMER          = -13100
		// E_TYPE_MISMATCH  = -13200
		// E_UNDEFINED      = -13300
		// E_UNSUPPORTED    = -13400
		// E_VAR_EXPECTED   = -13500
		// E_VAR_NOT_SET    = -13600
		// E_VERIFY         = -13700
		// E_WINDOW_TAG     = -13800
		// E_ZERO_STEP      = -13900
		// E_PARENT_HALTED  = -14000
		// E_SIBLING_HALTED = -14100
		// E_AGENT_GUI_MISMATCH = -14200
		// 
		// // 4TEST AGENT
		// E_APP_FAULT = -20000
		// E_APP_NOT_RESPONDING = -20100
		// E_APPID_INVALID = -20200
		// E_BITMAP_NOT_STABLE = -20300
		// E_BITMAP_REGION_INVALID = -20400
		// E_BITMAPS_ALMOST_MATCH = -20500
		// E_BITMAPS_DIFFERENT = -20600
		// E_BITMAPS_DIFF_COLORTABLE = -20700
		// E_BITMAPS_DIFF_DEPTH = -20800
		// E_BITMAPS_DIFF_EMPTY = -20900
		// E_BITMAPS_DIFF_HEIGHT = -21000
		// E_BITMAPS_DIFF_PLANES = -21100
		// E_BITMAPS_DIFF_SIZE = -21200
		// E_BITMAPS_DIFF_WIDTH = -21300
		// E_CANT_CAPTURE_BITMAP = -21400
		// E_CANT_CLEAR_SELECTION = -21500
		// E_CANT_CLOSE_WINDOW = -21600
		// E_CANT_CONVERT_RESOURCE = -21700
		// E_CANT_EXIT_APP = -21800
		// E_CANT_EXTEND_SELECTION = -21900
		// E_CANT_LOAD_DLL = -22000
		// E_CANT_MAXIMIZE_WINDOW = -22100
		// E_CANT_MINIMIZE_WINDOW = -22200
		// E_CANT_MOVE_WINDOW = -22300
		// E_CANT_RESTORE_WINDOW = -22400
		// E_CANT_SET_ACTIVE = -22500
		// E_CANT_SET_FOCUS = -22600
		// E_CANT_SIZE_WINDOW = -22700
		// E_CANT_START_APP = -22800
		// E_CANT_TRANSLATE_KEYS = -22900
		// E_CANT_TRANSLATE_TEXT = -23000
		// E_COL_COUNT_INVALID = -23100
		// E_COL_NUM_INVALID = -23200
		// E_COL_START_EXCEEDS_END = -23300
		// E_CONNECTION_REFUSED = -23400
		// E_CONTROL_NOT_RESPONDING = -23500
		// E_COORD_OFF_SCREEN = -23600
		// E_COORD_OUTSIDE_WINDOW = -23700
		// E_CURSOR_TIMEOUT = -23800
		// E_DELAY_INVALID = -23900
		// E_FUNCTION_NOT_FOUND = -24000
		// E_FUNCTION_NOT_REGISTERED = -24100
		// E_GUIFUNC_ID_INVALID = -24200
		// E_ITEM_NOT_FOUND = -24300
		// E_ITEM_NOT_VISIBLE = -24400
		// E_ITEM_INDEX_INVALID = -24500
		// E_INVALID_REQUEST = -24600
		// E_KEY_COUNT_INVALID = -24700
		// E_KEY_NAME_INVALID = -24800
		// E_KEY_SYNTAX_ERROR = -24900
		// E_LINE_COUNT_INVALID = -25000
		// E_LINE_NUM_INVALID = -25100
		// E_LINE_START_EXCEEDS_END = -25200
		// E_MOUSE_BUTTON_INVALID = -25300
		// E_NO_ACTIVE_WINDOW = -25400
		// E_NO_DEFAULT_PUSHBUTTON = -25500
		// E_NO_FOCUS_WINDOW = -25600
		// E_OPTION_CLASSMAP_INVALID = -25700
		// E_OPTION_EVTSTR_LENGTH = -25800
		// E_OPTION_NAME_INVALID = -25900
		// E_OPTION_TOO_MANY_TAGS = -26000
		// E_OPTION_TYPE_MISMATCH = -26100
		// E_OPTION_VALUE_INVALID = -26200
		// E_POS_INVALID = -26300
		// E_POS_NOT_REACHABLE = -26400
		// E_PROPERTY_INDEX_INVALID = -26500
		// E_PROPERTY_IS_NULL = -26600
		// E_PROPERTY_NOT_FOUND = -26700
		// E_PROPERTY_READ_ONLY = -26800
		// E_PROPERTY_TYPE_MISMATCH = -26900
		// E_RESOURCE_NOT_FOUND = -27000
		// E_SBAR_HAS_NO_THUMB = -27100
		// E_TAG_SYNTAX_ERROR = -27200
		// E_TRAP_NOT_SET = -27300
		// E_WINDOW_INDEX_INVALID = -27400
		// E_WINDOW_NOT_ACTIVE = -27500
		// E_WINDOW_NOT_ENABLED = -27600
		// E_WINDOW_NOT_EXPOSED = -27700
		// E_WINDOW_NOT_FOUND = -27800
		// E_WINDOW_NOT_UNIQUE = -27900
		// E_WINDOW_SIZE_INVALID = -28000
		// E_WINDOW_TYPE_MISMATCH = -28100
		// 
		// // NEW EXCEPTIONS SINCE 2.0.2 MUST GO BELOW THIS LINE ***/
		// 
		// E_COLUMN_INDEX_INVALID = -28200
		// E_COLUMN_NOT_FOUND = -28201
		// E_ITEM_CANT_COLLAPSE = -28300
		// E_ITEM_CANT_EXPAND = -28400
		// E_KEY_STRING_TOO_LONG = -28500
		// 
		// /*** THESE ARE FOR HANDLING OLE2/VB CALLS ***/
		// 
		// E_AXEXT_NOT_RESPONDING     = -28600
		// E_OBJ_CALL_FAILED          = -28700
		// E_OBJ_NOT_FOUND            = -28800
		// E_ARG_TYPE_MISMATCH        = -28900
		// E_BAD_ARG_COUNT            = -29000
		// E_ARG_VAL_OUT_OF_RANGE     = -29100
		// E_APP_NOT_READY            = -29200
		// E_CANT_SCROLL_INTO_VIEW    = -29300
		// E_ALREADY_DRAGGING         = -29400
		// E_NOT_DRAGGING             = -29500
		// 
		// E_DLL_EXCEPTION            = -29800
		// 
		// E_ROW_INDEX_INVALID        = -30000
		// E_TBL_HAS_NO_ROW_HDR       = -30100
		// E_TBL_HAS_NO_COL_HDR       = -30200
		// E_TBL_SINGLE_CELL_ONLY     = -30300
		// E_UD_HAS_NO_RANGE          = -30400
		// E_ROW_NOT_TOP              = -30500
		// E_COLUMN_NOT_LEFT          = -30600
		// 
		// E_VO_COLUMN_INVALID        = -50100
		// E_VO_COUNT_INVALID         = -50200
		// E_VO_ITEM_INDEX_INVALID    = -50300
		// E_VO_ITEM_NOT_FOUND        = -50400
		// E_VO_LINE_INVALID          = -50500
		// E_VO_PROPERTY_NOT_FOUND    = -50600
		// E_VO_REGION_INVALID        = -50700
		// E_VO_ROW_INVALID           = -50800
		// E_VO_STATUS_NOT_FOUND      = -50900
		// E_VO_TYPE_MISMATCH         = -51000
	

// Expand for type definitions used in this code
	}
	type TATEDATE is STRING;						// 
	type TATETIME is STRING;
	type TATEDATETIME is STRING;
	
	type object is WINDOW;						// Denotes classes not related to window elements
	type OBJECT is WINDOW;
	
	type OPTION is BOOLEAN;						// Can be used to make it clear that this is a script option
	
	type TEXT is STRING, LIST , WINDOW;			// Can be a string, cTEXTFILE, or a list of these two types. new for v4
	type FILEREF is STRING, WINDOW;				// Can be a STRING or cFILE/cDIR new for v4
	type WNDREF  is STRING, WINDOW;
	
	type CONTAINS is STRING, LIST, RECT, WINDOW;	// Used by Contains()
	type BOOLTYPES is BOOLEAN, INTEGER, STRING;	// Used by MakeBool()
	
	type WNDSTATUS is enum
	{
		WSTAT_ACTIVE,    // WINDOW IS ACTIVE
		WSTAT_OBSCURED,  // WINDOW IS OBSCURED BY ANOTHER WINDOW
		WSTAT_DISABLED,  // WINDOW IS DISABLED
		WSTAT_MISSING,   // WINDOW DOES NOT EXIST
		WSTAT_NOTUNIQUE // MULTIPLE WINDOWS MATCH THE PROVIDED TAG
		
	}
	type DISMISSTYPE is enum
	{
		ACCEPT,
		CANCEL,
		CUSTOM

///////////////////////////////////////////////////////////////////////////

// Expand for Function Library - Date string functions	 			(MakeSortableDate(), etc.)
	// Sortable dates are strings that you can use ListSort() to arrange in date or time order.
	// They are devoid of seperator characters, and are in the form yymmddhhmmss. You can also 
	// use > and < on these, tho there is no native support for adding or subtrating... that'll 
	// have to come later
	
	// these convert sortable dates and times to conventionally recognizable dates and times
	// again, more work is needed... conversion to silktest datetime types, add, subtract,
	// extract date, extract time, and the ability to distinguish between a date and a time.
	// if optional argument not supplied, then the date or time now is used
	}
	TATEDATE 		MakeSortableDate(STRING sDate NULL optional) 				// input in the form mm-dd-yy
	{
		if sDate==NULL
		{
			sDate=DateStr();
		}
		if sContains(sDate,"/") || sContains(sDate,"-")
		{
			sDate=SubStr(sDate,7,2)+SubStr(sDate,1,2)+SubStr(sDate,4,2);
		}
		return sDate;
	}
	STRING 			MakeStandardDate(TATEDATE sDate NULL optional) 				// input in the form yymmdd
	{
		if sDate==NULL
		{
			sDate=DateStr();
		}
		else
		{
			sDate=SubStr(sDate,3,2)+"/"+SubStr(sDate,5,2)+"/"+SubStr(sDate,1,2);
		}
		return sDate;
	}
	TATETIME 		MakeSortableTime(STRING sTime NULL optional) 				// input in the form hh:mm:ss
	{
		if sTime==NULL
		{
			sTime=TimeStr();
		}
		if sContains(sTime,":")
		{
			sTime=SubStr(sTime,1,2)+SubStr(sTime,4,2)+SubStr(sTime,7,2);
		}
		return sTime;
	}
	STRING 			MakeStandardTime(TATETIME sTime NULL optional) 				// input in the form hhmmss
	{
		if sTime==NULL
		{
			sTime=TimeStr();
		}
		else
		{
			if sTime != NBSP
			{
				sTime=SubStr(sTime,1,2)+":"+SubStr(sTime,3,2)+":"+SubStr(sTime,5,2);
			}
		}
		return sTime;
	}
	TATEDATETIME 	MakeSortableDateTime(STRING sDatetime NULL optional) 		// input in the form mm/dd/yy hh:mm:ss
	{
		if sDatetime == NULL
		{
			sDatetime=MakeStandardDate()+" "+MakeStandardTime();
		
		}
		STRING sDatePart = SubStr(sDatetime,1,8);
		STRING sTimePart = SubStr(sDatetime,10,255);
		return MakeSortableDate(sDatePart)+MakeSortableTime(sTimePart);
	}
	STRING 			MakeStandardDateTime(TATEDATETIME sDatetime NULL optional) 	// input in the form yymmddhhmmss
	{
		if sDatetime == NULL
		{
			sDatetime=MakeSortableDateTime();
		
		}
		STRING sDatePart = SubStr(sDatetime,1,6);
		STRING sTimePart = SubStr(sDatetime,7,255);
		return MakeStandardDate(sDatePart)+" "+MakeStandardTime(sTimePart);
	
	}
	STRING  		GetNewestStamp(LIST OF STRING lsStamps)
	{
		lsStamps=FilterStamps(lsStamps);
		ListSort(lsStamps);
		if lsStamps=={}
		{
			lsStamps={NBSP};
		}
		return lsStamps[ListCount(lsStamps)];
	}
	STRING  		GetOldestStamp(LIST OF STRING lsStamps)
	{
		lsStamps=FilterStamps(lsStamps);
		ListSort(lsStamps);
		if lsStamps=={}
		{
			lsStamps={NBSP};
		}
		return lsStamps[1];
	}
	LIST OF STRING 	FilterStamps(LIST OF STRING lsStamps)
	{
		INTEGER i;
		for i = ListCount(lsStamps) to 1 step -1
		{
			if lsStamps[i]==NBSP
			{
				ListDelete(lsStamps,i);
			}
		}
		return lsStamps;
	}
	STRING			MakeTwoLineStamp(STRING sStamp, BOOLEAN fAssumeDate optional)
	{
		
		STRING sResult;
		
		if sStamp != NBSP
		{
			// fAssumeDate is used only to select between date and time if the string passed in is 6 chars
			if fAssumeDate==NULL
			{
				fAssumeDate=FALSE;
			
			// sStamp=SuiteItem.sSuiteStart
			// sDoneTime=SuiteItem.sSuiteDone
			// if len of input is 6... could be date, could be time
			// if len of input is 8, is date w 4 digit year
			// if len of input is 12, date and time
			// if len of input is 14, date in 4 digit year and time
			
			}
			BOOLEAN fDate=FALSE;
			BOOLEAN fTime=TRUE;
			
			// if len of input is 6... could be date, could be time
			INTEGER iYPos=1,iMPos=3, iDPos=5, iYLen=2;
			INTEGER iHPos=1, iNPos=3, iSPos=5;
			
			// if len of input is 8, is date w 4 digit year
			if Len(sStamp) == 8
			{
				iYPos=1;
				iMPos=5;
				iDPos=7;
				iYLen=4;
				fDate=TRUE;
				fTime=FALSE;
			
			// if len of input is 12, date and time
			}
			if Len(sStamp) == 12
			{
				iYPos=1;
				iMPos=3;
				iDPos=5;
				iYLen=2;
				iHPos=7;
				iNPos=9;
				iSPos=11;
				fDate=TRUE;
				fTime=TRUE;
			
			// if len of input is 14, date in 4 digit year and time
			}
			if Len(sStamp) == 14
			{
				iYPos=1;
				iMPos=5;
				iDPos=7;
				iYLen=4;
				iHPos=9;
				iNPos=11;
				iSPos=13;
				fDate=TRUE;
				fTime=TRUE;
			
			}
			STRING sDate="", sTime="";
			STRING sYear="", sMonth="", sDay="", sHour="", sMinute="", sSecond="";
			STRING sNewLine="";
			
			
			if fDate && fTime
			{
				sNewLine="<BR>";
			}
			if fDate
			{
				sDate=SubStr(sStamp,iMPos,2)+"/"+SubStr(sStamp,iDPos,2)+"/"+SubStr(sStamp,iYPos,iYLen);
			}
			if fTime
			{
				sTime=SubStr(sStamp,iHPos,2)+":"+SubStr(sStamp,iNPos,2)+":"+SubStr(sStamp,iSPos,2);
			
			}
			sResult=sDate+sNewLine+sTime;
		}
		else
		{
			sResult=sStamp;
		
		//print(sResult)
		}
		return sResult;
		
	}
	STRING			GetDatePart(STRING sStamp)
	{
		return SubStr(sStamp,1,6);
	

// Expand for Function Library - Data Conversion Functions 			(Make into...)
	
	////////////////////////////////////////////////////////////////////////////
	// MakeInt(x)
	//
	// Recasts x as an integer.
	////////////////////////////////////////////////////////////////////////////
	}
	INTEGER MakeInt(ANYTYPE Incoming)
	{
		Incoming = "{MakeNumber(Incoming)}";
		return [INTEGER]Val("{Incoming}");
	
	////////////////////////////////////////////////////////////////////////////
	// MakeFloat(x)
	//
	// Recasts incoming number as a float.
	////////////////////////////////////////////////////////////////////////////
	}
	FLOAT   MakeFloat(ANYTYPE Incoming)
	{
		Incoming = "{MakeNumber(Incoming)}";
		return [FLOAT]Val("{Incoming}");
	
	////////////////////////////////////////////////////////////////////////////
	// Round(x, y)
	//
	// Performs rounding
	// Caller can specify to what level of percision - y is an optional argument
	// which specifies percision.
	////////////////////////////////////////////////////////////////////////////
	}
	REAL Round(ANYTYPE Incoming, INTEGER Percision optional)
	{
		if Percision == NULL
		{
			Percision = 0;
		}
		NUMBER Multiplier = 10**Percision;
		NUMBER Floater;
		Incoming = "{MakeNumber(Incoming)}";
		Incoming = Val("{Incoming}");
		Incoming = (Incoming * Multiplier ) + .5;
		Incoming = MakeInt(Incoming);
		Incoming = [REAL]Incoming;
		Incoming = (Incoming / Multiplier);
		return Incoming;
	////////////////////////////////////////////////////////////////////////////
	// IsEven(x)
	//
	// Returns if a number is odd or even
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN IsEven (INTEGER incoming)
	{
		return !MakeBool(incoming%2);
	
	////////////////////////////////////////////////////////////////////////////
	}
	Integer MakeHexIntoInt(string xinput)
	{
		const Allowed="0123456789ABCDEF";
		INTEGER i,iPos,xoutput=0;
		for i = len(xinput) to 1 step -1
		{
			iPos = StrPos(xinput[i],Allowed);
			xoutput = xoutput + (16 ** (i-1)) * (iPos-1);
		}
		return xoutput;
	
	
	////////////////////////////////////////////////////////////////////////////
	// MakeBool(x)
	//
	// Used to convert strings that have boolean meanings to a boolean value or
	// to express INTEGER values as a boolean. Useful for parsing INI files.
	//
	// values that come in as boolean are passed out unchanged
	// 1 becomes true, 0 false
	// "yes", "true", "on", "y", "t", and "1" all return true
	// all other STRING values return false
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN MakeBool (ANYTYPE incoming)
	{
		BOOLEAN result = FALSE;
		incoming = trim(lower("{incoming}"));
		if abs(val(incoming)) > 0
		{
			incoming='1';
		}
		if ListFind({"true","t","on","yes","y","1","ok","pass","passed"},incoming) > 0
		{
			result = true;
		}
		return result;
	
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataConversion_MakeBool()
	{
		__DoTest("MakeBool(TRUE)" ,MakeBool(TRUE) ,TRUE);
		__DoTest("MakeBool('TRUE')",MakeBool('TRUE'),TRUE);
		__DoTest("MakeBool('tRUE')",MakeBool('tRUE'),TRUE);
		__DoTest("MakeBool('True')",MakeBool('True'),TRUE);
		__DoTest("MakeBool('true')",MakeBool('true'),TRUE);
		__DoTest("MakeBool('T')"   ,MakeBool('T')   ,TRUE);
		__DoTest("MakeBool('t')"   ,MakeBool('t')   ,TRUE);
		__DoTest("MakeBool('yes')",MakeBool('yes'),TRUE);
		__DoTest("MakeBool('Yes')",MakeBool('Yes'),TRUE);
		__DoTest("MakeBool('YES')",MakeBool('YES'),TRUE);
		__DoTest("MakeBool('yES')",MakeBool('yES'),TRUE);
		__DoTest("MakeBool('Y')"  ,MakeBool('Y')  ,TRUE);
		__DoTest("MakeBool('y')"  ,MakeBool('y')  ,TRUE);
		__DoTest("MakeBool('1')"  ,MakeBool('1')  ,TRUE);
		__DoTest("MakeBool('ON')" ,MakeBool('ON') ,TRUE);
		__DoTest("MakeBool('on')" ,MakeBool('on') ,TRUE);
		__DoTest("MakeBool('On')" ,MakeBool('On') ,TRUE);
		__DoTest("MakeBool('oN')" ,MakeBool('oN') ,TRUE);
		__DoTest("MakeBool(1)"    ,MakeBool(1)    ,TRUE);
		__DoTest("MakeBool(14.1)" ,MakeBool(14.1) ,TRUE);
		__DoTest("MakeBool(-1)"   ,MakeBool(-1)   ,TRUE);
		__DoTest("MakeBool(-1.1)" ,MakeBool(-1.1) ,TRUE);
		__DoTest("MakeBool(FALSE)"  ,MakeBool(FALSE)  ,FALSE);
		__DoTest("MakeBool('FALSE')",MakeBool('FALSE'),FALSE);
		__DoTest("MakeBool('fALSE')",MakeBool('fALSE'),FALSE);
		__DoTest("MakeBool('False')",MakeBool('False'),FALSE);
		__DoTest("MakeBool('F')"    ,MakeBool('F')    ,FALSE);
		__DoTest("MakeBool('f')"    ,MakeBool('f')    ,FALSE);
		__DoTest("MakeBool('no')"   ,MakeBool('no')   ,FALSE);
		__DoTest("MakeBool('No')"   ,MakeBool('No')   ,FALSE);
		__DoTest("MakeBool('NO')"   ,MakeBool('NO')   ,FALSE);
		__DoTest("MakeBool('nO')"   ,MakeBool('nO')   ,FALSE);
		__DoTest("MakeBool('N')"    ,MakeBool('N')    ,FALSE);
		__DoTest("MakeBool('n')"    ,MakeBool('n')    ,FALSE);
		__DoTest("MakeBool('0')"    ,MakeBool('0')    ,FALSE);
		__DoTest("MakeBool('OFF')"  ,MakeBool('OFF')  ,FALSE);
		__DoTest("MakeBool('off')"  ,MakeBool('off')  ,FALSE);
		__DoTest("MakeBool('Off')"  ,MakeBool('Off')  ,FALSE);
		__DoTest("MakeBool('oFF')"  ,MakeBool('oFF')  ,FALSE);
		__DoTest("MakeBool(0)"      ,MakeBool(0)      ,FALSE);
		__DoTest("MakeBool(0.00)"   ,MakeBool(0.00)   ,FALSE);
		__DoTest("MakeBool(-0)"     ,MakeBool(-0)     ,FALSE);
		__DoTest("MakeBool(-0.0)"   ,MakeBool(-0.0)   ,FALSE);
	
	////////////////////////////////////////////////////////////////////////////
	// MakeNumber(s)
	//
	// Returns only numeric portions of a STRING as a number.
	//
	// For instance, "You Have $32,767.01 Dollars" returns 32767.01 But you
	// have to take care, "32-27-53" returns 322753, "-32,545" returns -32545
	// and "510.649.0247" returns 510.6490247
	////////////////////////////////////////////////////////////////////////////
	}
	NUMBER MakeNumber (ANYTYPE incoming)
	{
		STRING numbers = "0123456789";
		INTEGER counter = 0;
		STRING inprog = "";
		
		BOOLEAN fPeriod = FALSE;
		BOOLEAN fDash   = FALSE;
		BOOLEAN fNumber = FALSE;
		
		incoming = "{incoming}";
		
		for counter = 1 to len (incoming)
		{
			if sContains (numbers, incoming[counter])
			{
				inprog = "{inprog}{incoming[counter]}";
				fNumber = TRUE;
			}
			if ((! fDash) && (! fNumber) && incoming[counter] == "-")
			{
				inprog = "{inprog}-";
				fDash = TRUE;
			}
			if ((! fPeriod) && incoming[counter] == ".")
			{
				inprog = "{inprog}.";
				fPeriod = TRUE;
			}
		}
		return val (inprog);
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataConversion_MakeNumber()
	{
		__DoTest("MakeNumber('0')"							,MakeNumber('0')      						,0);
		__DoTest("MakeNumber('0A')"							,MakeNumber('0A')     						,0);
		__DoTest("MakeNumber('m1n3')"						,MakeNumber('m1n3')   						,13);
		__DoTest("MakeNumber('$123.45')"					,MakeNumber('$123.45')						,123.45);
		__DoTest("MakeNumber('-2.0')"						,MakeNumber('-2.0')   						,-2);
		__DoTest("MakeNumber('828-2882')"					,MakeNumber('828-2882')						,8282882);
		__DoTest("MakeNumber('IJ98y897si.eugh*(&y9sd7uho')"	,MakeNumber('IJ98y897si.eugh*(&y9sd7uho')	,98897.97);
		__DoTest("MakeNumber('h-.2')"						,MakeNumber('h-.2')   						,-.2);
		__DoTest("MakeNumber('You Have $32,767.01 Dollars')",MakeNumber('You Have $32,767.01 Dollars')  ,32767.01);
		__DoTest("MakeNumber('32-27-53')"					,MakeNumber('32-27-53')   					,322753);
		__DoTest("MakeNumber('510.649.0247')"				,MakeNumber('510.649.0247')   				,510.649025);
	
	////////////////////////////////////////////////////////////////////////////
	// MakeString(a)
	//
	// Returns a STRING from anytype
	////////////////////////////////////////////////////////////////////////////
	}
	STRING MakeString (ANYTYPE incoming)
	{
		return "{incoming}";
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataConversion_MakeString()
	{
		__DoTest("MakeString('hello!')"		,MakeString('Hello'),	"Hello");
		__DoTest("MakeString(1)"			,MakeString(1),			"1");
		__DoTest("MakeString(1.1)"			,MakeString(1.1),		"1.100000");
		__DoTest("MakeString(TRUE)"			,MakeString(TRUE),		"TRUE");
		__DoTest("MakeString(ANYTYPE)"		,MakeString(ANYTYPE),	"ANYTYPE");
		__DoTest("MakeString(TRUE)"			,MakeString(TRUE),		"TRUE");
		__DoTest("MakeString(OBJECT)"		,MakeString(OBJECT),	"OBJECT");
		__DoTest("MakeString(cBASE)"		,MakeString(cBASE),		"cBASE");
		__DoTest("MakeString(cBASE())"		,MakeString(cBASE()),	'cBASE("")');
		
	
	////////////////////////////////////////////////////////////////////////////
	// MakeListFromString(s,sd)
	//
	// Returns list of STRING from STRING and delimiter
	// (Formerly called Parse)
	////////////////////////////////////////////////////////////////////////////
	}
	LIST OF STRING MakeListFromString (STRING sIncoming, STRING sDelimiter)
	{
		LIST OF STRING lsResult = {};
		INTEGER iPosition = 0;
		STRING sCurrent;
		sIncoming = sIncoming + sDelimiter + ' ';
		
		if (sIncoming[1]==''{') && (sIncoming[Len(sIncoming)]=='}')
		{
			sIncoming=RemoveFirstAndLast(sIncoming);
		
		}
		while len (trim (sIncoming)) > 0 && Assign (iPosition, StrPos (sDelimiter, sIncoming)) > 0
		{
			ListAppend (lsResult, SubStr (sIncoming, 1, iPosition - 1));
			sIncoming = SubStr (sIncoming, iPosition + len (sDelimiter), 1000000);
			
		}
		return lsResult;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataConversion_MakeListFromString()
	{
		__DoTest("MakeListFromString('hello,this,fine,world',',')",	MakeListFromString('hello,this,fine,world',","), {"hello","this",'fine','world'});
		__DoTest("MakeListFromString('hello|this|fine|world','|')",	MakeListFromString('hello|this|fine|world','|'), {"hello","this",'fine','world'});
		
	
	////////////////////////////////////////////////////////////////////////////
	// MakeListFromCSV(s)
	//
	// Returns list of STRING from a STRING of CSV data.
	////////////////////////////////////////////////////////////////////////////
	}
	LIST OF STRING MakeListFromCSV (STRING csvData)
	{
		LIST OF STRING lsData = {};
		INTEGER i;
		STRING sCurrent="";
		BOOLEAN fInQuotes = FALSE;
		for i = 1 to len(csvData)
		{
			if csvData[i]=='"'
			{
				fInQuotes = ! fInQuotes;
			}
			else if csvData[i]==',' && ! fInQuotes
			{
				ListAppend(lsData,sCurrent);
				sCurrent="";
			}
			else 
			{
				sCurrent=sCurrent+csvData[i];
		
			}
		}
		if sCurrent != ""
		{
			ListAppend(lsData,sCurrent);
		
		//return MakeListFromString (csvData, ",")
		}
		return lsData;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataConversion_MakeListFromCSV()
	{
		__DoTest("MakeListFromCSV('hello,this,fine,world')",	MakeListFromCSV('hello,this,fine,world'), {"hello","this",'fine','world'});
	
	////////////////////////////////////////////////////////////////////////////
	// MakeListOfWordsFromString(s)
	//
	// Returns list of STRING for character collections seperated by the space
	// character.
	// (Formerly called ParseWS)
	////////////////////////////////////////////////////////////////////////////
	}
	LIST OF STRING MakeListOfWordsFromString (STRING sIncoming)
	{
		return MakeListFromString(sIncoming, " ");
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataConversion_MakeListOfWordsFromString()
	{
		__DoTest("MakeListOfWordsFromString('hello this fine world')",	MakeListOfWordsFromString('hello this fine world'), {"hello","this",'fine','world'});
	
	////////////////////////////////////////////////////////////////////////////
	// MakeText(TEXT)
	//
	// Accepts STRING, LIST of STRING, cTEXTFILE or LIST of cTEXTFILE
	// Returns LIST OF STRING
	////////////////////////////////////////////////////////////////////////////
	}
	TEXT MakeText(TEXT text, inout TEXT worklist optional)
	{
		if worklist == NULL
		{
			worklist = {};
		}
		select
		{
			case IsVarString(text):
				ListAppend(worklist,text);
			case IsVarList(text):
				ANYTYPE item;
				for each item in text
				{
					MakeText(item, worklist);
				}
			case IsVarWindow(text):
				if text.IsOfClass(cOPENFILE)
				{
					text.Close();
					text=cTEXTFILE(text.sFileName);
					text.Read();
					MakeText(text.lsData, worklist);
				}
				else
				{
					do
					{
						MakeText(text.d, worklist);
					}
					except
					{
						raise LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS, "*** Error: LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS on {text}";
					}
				}
			default:
			{
				raise LIBERROR_INVALID_DATA_TYPE, "*** Error: LIBERROR_INVALID_DATA_TYPE on {text}";
			}
		}
		return worklist;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataConversion_MakeText()
	{
		STRING b = ""{"+"}", lb = b[1], rb = b[2], s1 = 'hello this fine world';
		LIST OF STRING ls1 = {s1}, ls2 = {'hello','this','fine','world'};
		LIST lls1 = {ls1,ls2,s1};
		LIST OF STRING lls2 = {'hello this fine world', 'hello', 'this', 'fine', 'world', 'hello this fine world'};
		LIST OF STRING ls3 = {'a','b','c','d','e','f','g','h','i','j','k'};
		LIST OF STRING ls4 = {'a','b','c','d','e','f','g','h','i','j','k','a','b','c','d','e','f','g','h','i','j','k'};
		OBJECT ct1 = cTEXTFILE("temp.txt");
		ct1.lsData = ls3;
		OBJECT ct2 = cTEXTFILE("temp.txt");
		ct2.lsData = ls3;
		LIST lo1 = {ct1,ct2};
		LIST ohgod = {s1,ls1,ls2,lls1,{lls2,ct1},ct2};
		LIST finalanswer = {'hello this fine world','hello this fine world', 'hello', 'this', 'fine', 'world', 'hello this fine world', 'hello', 'this', 'fine', 'world', 'hello this fine world', 'hello this fine world', 'hello', 'this', 'fine', 'world', 'hello this fine world', 'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
		__DoTest("MakeText('{s1}')"				,MakeText(s1)	,ls1);
		__DoTest("MakeText({lb}'{s1}'{rb})"		,MakeText(ls1)	,ls1);
		__DoTest("MakeText({ls2})"				,MakeText(ls2)	,ls2);
		__DoTest("MakeText({lls1})"				,MakeText(lls1)	,lls2);
		__DoTest("MakeText(cTEXTFILE())"		,MakeText(ct1)	,ls3);
		__DoTest("MakeText("{cTEXTFILE(),cTEXTFILE()})"		,MakeText(lo1)	,ls4);
		__DoTest("MakeText({ohgod})"			,MakeText(ohgod)	,finalanswer);
		
	
	////////////////////////////////////////////////////////////////////////////
	// MakeList(a)
	//
	// Accepts LIST, TEXT, 
	// Returns LIST 
	////////////////////////////////////////////////////////////////////////////
	}
	LIST MakeList(ANYTYPE Incoming)
	{
		if IsVarObject(Incoming)
		{
			if Incoming.IsOfClass({cLIST, cTEXT, cTEXTFILE, cSEARCHABLELIST, cBATCHFILE})
			{
				Incoming=Incoming.d;
			}
			else
			{
				raise LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS,"Don't know how to extract list from that class type: {Incoming.Class}";
			}
			return Incoming;
	
	////////////////////////////////////////////////////////////////////////////
	// MakeListFromRecord(a)
	//
	// Takes a record, returns a list where each list item is one field from
	// the record.
	////////////////////////////////////////////////////////////////////////////
		}
	}
	LIST MakeListFromRecord(ANYTYPE incoming)
	{
		LIST OF STRING fieldlist = FieldsOfRecord(TypeOf(incoming));
		LIST result = {};
		ANYTYPE item;
		for each item in fieldlist
		{
			ListAppend(result,incoming.@(item));
		}
		return result;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataConversion_MakeListFromRecord()
	{
		FILEINFO donk = 
		{
			'Field sName',
			TRUE,  			// bIsDir
			23,				// iSize
			255,				// iAttributes
			[datetime]'2000-12-25 00:01:02.4',	//dtLastModifyTime
			[datetime]'2000-12-31 23:59:59.9'	//dtCreationTime
		};
		__DoTest('MakeListFromRecord({donk})','{MakeListFromRecord(donk)}',''{Field sName, TRUE, 23, 255, 2000-12-25 00.01.02.400000, 2000-12-31 23.59.59.900000}');
		
	
	////////////////////////////////////////////////////////////////////////////
	// MakeStringFromFILEREF(f)
	//
	// A FILEREF is either a cDISKENTITY or a STRING (where the STRING is either
	// a directory name or a file name). This function converts the ambiguous
	// state to a string.
	////////////////////////////////////////////////////////////////////////////
	}
	STRING MakeStringFromFILEREF(FILEREF Target)
	{
		if IsVarWindow(Target)
		{
			if Target.IsOfClass(cFILE)
			{
				Target = Target.sFileName;
			}
			else if Target.IsOfClass(cDIR)
			{
				Target = Target.sDirName;
			}
			else // it's an object, but not a cFILE or cDIR, raise exception
			{
				raise LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS, "*** Error: LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS, Should be a cDIR or cFILE, but got {Target.Class}";
			}
		}
		return Target;
		
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataConversion_MakeStringFromFILEREF() {}
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	OBJECT MakeObjectFromFILEREF(FILEREF Target, OBJECT oCaller optional)
	{
		if oCaller==NULL
		{
			oCaller=cFILE();
		}
		if IsVarString(Target)
		{
			Target=@(oCaller.sClass)(Target);
		}
		return Target;
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	}
	STRING MakeCSVFromList(LIST OF STRING lsData)
	{
		ANYTYPE item;
		STRING sResult="";
		for each item in lsData
		{
			sResult=sResult+","+item;
		}
		sResult[1]="";
		return sResult;
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	}
	STRING MakeYesNo(ANYTYPE item)
	{
		BOOLEAN fActual = MakeBool(item);
		return iff(fActual,"Yes","No");
	
	}
	STRING MakePassFail(ANYTYPE aIn)
	{
		aIn=MakeBool(aIn);
		return Iff(aIn,"PASS","FAIL");
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	}
	STRING NormalizeVersionString(STRING sIncoming)
	{
		STRING sResult = "";
		LIST OF STRING lsValues = MakeListFromString(sIncoming,".");
		ANYTYPE item;
		for each item in lsValues
		{
			sResult=sResult+Right(sResult+"000{val(item)}",3)+'.';
		}
		sResult[len(sResult)]='';	// chops off trailing .
		while Right(sResult,4)==".000"
		{
			sResult = GetLeftOf(sResult,".000");
		
		}
		return sResult;
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	}
	STRING MakeLower(inout ANYTYPE sIn)
	{
		do
		{
			sIn=lower("{sIn}");
		}
		except
		{
			raise LIBERROR_CANT_PERFORM_ASSIGNMENT,"MakeLower({sIn}) Assignment failed because {sIn} isn't STRING or a type that can be assigned a string";
		}
		return sIn;
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	}
	STRING MakeUpper(inout ANYTYPE sIn)
	{
		do
		{
			sIn=upper("{sIn}");
		}
		except
		{
			raise LIBERROR_CANT_PERFORM_ASSIGNMENT,"MakeLower({sIn}) Assignment failed because {sIn} isn't STRING or a type that can be assigned a string";
		}
		return sIn;
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	}
	STRING MakeWidth(ANYTYPE aData,INTEGER iWidth, STRING sPad optional)
	{
		if sPad==NULL
		{
			sPad=" ";
		
		}
		STRING sPadded = Replicate(sPad,iWidth)+"{aData}";
		
		return Right(sPadded,iWidth);
		
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	}
	STRING RemoveFirstAndLast(STRING sIn)
	{
		sIn[1]="";
		sIn[len(sIn)]="";
		return sIn;
	
	

// Expand for Function Library - Data Extraction Functions 			(Get from...)
	
	////////////////////////////////////////////////////////////////////////////
	// GetLastMember(la)
	//
	// Returns the Last member of a list (of anytype)
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE GetLastMember(LIST OF ANYTYPE laIncoming)
	{
		ANYTYPE result = {};
		if laIncoming != {}
		{
			INTEGER pos = ListCount(laIncoming);
			result = laIncoming[pos];
		}
		return result;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetLastMember()
	{
		__DoTest("GetLastMember("{'a','b'})" ,GetLastMember({'a','b'}) ,'b');
		__DoTest("GetLastMember("{'a'})" ,GetLastMember({'a'}) ,'a');
		
	
	////////////////////////////////////////////////////////////////////////////
	// GetLeftOf(s,ss)
	//
	// Returns everything to the left of the last occurance of a substring
	// Unless optional third argument is specified, then get from left of FIRST
	// instance of ss.
	////////////////////////////////////////////////////////////////////////////
	}
	STRING GetLeftOf(STRING sIncoming, STRING sFindMe, BOOLEAN fGetLeftOfFirst optional)
	{
		if fGetLeftOfFirst == NULL
		{
			fGetLeftOfFirst = FALSE;
		}
		STRING sResult = sIncoming;
		if sContains(sIncoming,sFindMe)
		{
			if ! fGetLeftOfFirst			// then we must want to get left of last
			{
				sResult = Left(sIncoming, FindLastPos(sIncoming, sFindMe)-1);
			}
			else
			{
				sResult = Left(sIncoming, StrPos(sFindMe, sIncoming)-1);
			}
		}
		return sResult;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetLeftOf()
	{
		__DoTest("GetLeftOf('abcdefg','d')" ,GetLeftOf('abcdefg','d') ,'abc');
		__DoTest("GetLeftOf('abcdefg','a')" ,GetLeftOf('abcdefg','a') ,'');
		__DoTest("GetLeftOf('abcdefg','g')" ,GetLeftOf('abcdefg','g') ,'abcdef');
	
	////////////////////////////////////////////////////////////////////////////
	// GetRightOf(s,ss)
	//
	// Returns everything to the right of the last occourance of a substring
	////////////////////////////////////////////////////////////////////////////
	}
	STRING GetRightOf(STRING sIncoming, STRING sFindMe,BOOLEAN fGetRightOfFirst optional)
	{
		if fGetRightOfFirst == NULL
		{
			fGetRightOfFirst = FALSE;
		}
		STRING sResult = sIncoming;
		if sContains(sIncoming,sFindMe)
		{
			if ! fGetRightOfFirst			// then we must want to get Right of last
			{
				sResult = SubStr(sIncoming, FindLastPos(sIncoming, sFindMe)+Len(sFindMe));
			}
			else
			{
				sResult = SubStr(sIncoming, StrPos(sFindMe, sIncoming)+Len(sFindMe));
			}
		}
		return sResult;
		//return SubStr(sIncoming, FindLastPos(sIncoming, sFindMe)+Len(sFindMe))
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetRightOf()
	{
		__DoTest("GetRightOf('abcdefg','d')" ,GetRightOf('abcdefg','d') ,'efg');
		__DoTest("GetRightOf('abcdefg','g')" ,GetRightOf('abcdefg','g') ,'');
		__DoTest("GetRightOf('abcdefg','a')" ,GetRightOf('abcdefg','a') ,'bcdefg');
	
	////////////////////////////////////////////////////////////////////////////
	// GetStringBetween(s1,sl,sr)
	//
	// Returns everything between two other characters. If the characters
	// occour more than once, the routine takes the first instances it encounters.
	////////////////////////////////////////////////////////////////////////////
	}
	STRING GetStringBetween(STRING sIncoming, STRING sLeft, STRING sRight)
	{
		STRING Result = sIncoming;
		Result = GetLeftOf(Result, sRight);
		Result = GetRightOf(Result, sLeft);
		return Result;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetStringBetween()
	{
		__DoTest("GetStringBetween('ab!cd$e','!','$')" ,GetStringBetween('ab!cd$e','!','$') ,'cd');
		__DoTest("GetStringBetween('ab!cd!e','!','!')" ,GetStringBetween('ab!cd$e','!','$') ,'cd');
		__DoTest("GetStringBetween('ab!cd!e!f','!','!')" ,GetStringBetween('ab!cd$e','!','$') ,'cd');
		__DoTest("GetStringBetween('ab,cd,e',',',',')" ,GetStringBetween('ab!cd$e','!','$') ,'cd');
	
	////////////////////////////////////////////////////////////////////////////
	// GetLastChar(s)
	//
	// Returns STRING of last character of a STRING or "" if STRING is empty or NULL
	////////////////////////////////////////////////////////////////////////////
	}
	STRING GetLastChar (STRING sIncoming NULL optional)
	{
		if sIncoming == NULL
		{
			sIncoming = "";
		}
		if Len (sIncoming) > 0
		{
			sIncoming = sIncoming[Len (sIncoming)];
		}
		return sIncoming;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetLastChar()
	{
		__DoTest("GetLastChar('abcd')" ,GetLastChar('abcd') ,'d');
		__DoTest("GetLastChar('')" ,GetLastChar('') ,'');
	
	////////////////////////////////////////////////////////////////////////////
	// GetAllButLast(s)
	//
	// Returns STRING of incoming minus the last character
	////////////////////////////////////////////////////////////////////////////
	}
	STRING GetAllButLast(STRING sIncoming NULL optional)
	{
		if sIncoming == NULL
		{
			sIncoming = "";
		}
		if Len (sIncoming) > 0
		{
			sIncoming = Left(sIncoming,Len(sIncoming) - 1);
		}
		return sIncoming;
		
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetAllButLast()
	{
		__DoTest("GetAllButLast('abcd')" ,GetAllButLast('abcd') ,'abc');
		__DoTest("GetAllButLast('')" ,GetAllButLast('') ,'');
	
	////////////////////////////////////////////////////////////////////////////
	// FindSelectionFromList(lSelectionList)
	//
	// Returns the item in the list selected with the use of brackets 
	// if given {[days],weeks,months} returns days
	////////////////////////////////////////////////////////////////////////////
	}
	STRING GetSelectionFromList(LIST OF STRING lsSelectionList)
	{
		STRING sItem;
		STRING sReturnSelection;
		STRING sSelection;
		for each sSelection in lsSelectionList
		{
			if MatchStr("[*]",sSelection)
			{
				sSelection = StrTran(sSelection,"[","");
				sReturnSelection = StrTran(sSelection,"]","");
				break;
			}
		}
		return sReturnSelection;
	
	////////////////////////////////////////////////////////////////////////////
	// GetFieldFromCSVList(s,i)
	//
	// Returns list of STRING of specified field number from a csv list
	////////////////////////////////////////////////////////////////////////////
	}
	LIST OF STRING GetFieldFromCSVList (LIST OF STRING csvData, INTEGER iFieldNum)
	{
		LIST OF STRING lsResult;
		ANYTYPE item;
		for each item in csvData
		{
			ListAppend (lsResult, MakeListFromCSV (item)[iFieldNum]);
			
		}
		return lsResult;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetFieldFromCSVList()
	{
		LIST data1 = { "a,b,c,d","e,f,g,h","i,j,k,l"};
		__DoTest("GetFieldFromCSVList({data1},2)"	,GetFieldFromCSVList(data1,2),{'b','f','j'});
		__DoTest("GetFieldFromCSVList({data1},1)"	,GetFieldFromCSVList(data1,1),{'a','e','i'});
		__DoTest("GetFieldFromCSVList({data1},4)"	,GetFieldFromCSVList(data1,4),{'d','h','l'});
	
	////////////////////////////////////////////////////////////////////////////
	// GetSmallest(l)
	//
	// Returns the smallest item from a list
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE GetSmallest(LIST OF ANYTYPE data)
	{
		ListSort(data);
		return data[1];
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetSmallest()
	{
		__DoTest("GetSmallest("{6,4,3,0,9,1,5,2,7,8})",GetSmallest({6,4,3,0,9,1,5,2,7,8}),0);
		__DoTest("GetSmallest("{'c','a','b'})",GetSmallest({'c','a','b'}),'a');
		__DoTest("GetSmallest("{"{'c'},"{'b'}})",GetSmallest({{'c'},{'b'}}),{'b'});
	
	////////////////////////////////////////////////////////////////////////////
	// GetSecondSmallest(l)
	//
	// Returns the second smallest item from a list
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE GetSecondSmallest(LIST OF ANYTYPE data)
	{
		ListSort(data);
		return data[2];
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetSecondSmallest()
	{
		__DoTest("GetSecondSmallest("{6,4,3,0,9,1,5,2,7,8})",GetSecondSmallest({6,4,3,0,9,1,5,2,7,8}),1);
		__DoTest("GetSecondSmallest("{'c','a','b'})",GetSecondSmallest({'c','a','b'}),'b');
		__DoTest("GetSecondSmallest("{"{'c'},"{'b'}})",GetSecondSmallest({{'c'},{'b'}}),{'c'});
		
	
	////////////////////////////////////////////////////////////////////////////
	// GetLargest(l)
	//
	// Returns the Largest item from a list
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE GetLargest(LIST OF ANYTYPE data)
	{
		ListSort(data);
		return data[ListCount(data)];
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetLargest()
	{
		__DoTest("GetLargest("{6,4,3,0,9,1,5,2,7,8})",GetLargest({6,4,3,0,9,1,5,2,7,8}),9);
		__DoTest("GetLargest("{'c','a','b'})",GetLargest({'c','a','b'}),'c');
		__DoTest("GetLargest("{"{'c'},"{'b'}})",GetLargest({{'c'},{'b'}}),{'c'});
	
	////////////////////////////////////////////////////////////////////////////
	// GetSecondLargest(l)
	//
	// Returns the second Largest item from a list
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE GetSecondLargest(LIST OF ANYTYPE data)
	{
		ListSort(data);
		return data[ListCount(data)-1];
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataExtraction_GetSecondLargest()
	{
		__DoTest("GetSecondLargest("{6,4,3,0,9,1,5,2,7,8})",GetSecondLargest({6,4,3,0,9,1,5,2,7,8}),8);
		__DoTest("GetSecondLargest("{'c','a','b'})",GetSecondLargest({'c','a','b'}),'b');
		__DoTest("GetSecondLargest("{"{'c'},"{'b'}})",GetSecondLargest({{'c'},{'b'}}),{'b'});
		
	
	////////////////////////////////////////////////////////////////////////////
	// SetMax(i,n)
	//
	// Returns and sets the max of the 2 numbers. Used typically like this:
	//
	// VOID Test()
	// 		INTEGER iMax = 0
	//		INTEGER i
	//		for i = 1 to ListCount(foo)
	//			SetMax(iMax,foo[i])
	//		print("Largest number in list was {iMax}")
	////////////////////////////////////////////////////////////////////////////
	}
	INTEGER SetMax(inout INTEGER iMax, INTEGER iTest)
	{
		if iTest>iMax
		{
			iMax=iTest;
		}
		return iMax;
	
	
	}
	STRING PopulateEnvVars(STRING sIncoming)
	{
		OBJECT li=cLIST().CreateWith(FindSubstrings(sIncoming,"%"));
		
		if li.iLength > 1
		{
			STRING sSuspect=SubStr(sIncoming,li.d[1]+1,li.d[2]-li.d[1]-1);
			STRING sNewValue=cSystem.GetEnv(sSuspect);
			sIncoming=StrTran(sIncoming,"%{sSuspect}%",sNewValue);
		
		}
		return sIncoming;
	

// Expand for Function Library - Data Location Functions 			(Find in...)
	
	////////////////////////////////////////////////////////////////////////////
	// CaseInsensitiveStringCompare(s1,s2)
	//
	// Returns true if the strings match when compared in a case
	// insensitive way (read: convert to uppercase, then compare)
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN CaseInsensitiveStringCompare(STRING sFirst,STRING sSecond)
	{
		if sFirst == NULL
		{
			return FALSE;
		}
		if sSecond == NULL
		{
			return FALSE;
		}
		return Upper(Trim(sFirst)) == Upper(Trim(sSecond));
	
	
	////////////////////////////////////////////////////////////////////////////
	// FindLastPos(sSuper,sSub)
	//
	// Returns the position where the last occurrence of a given subSTRING appears
	////////////////////////////////////////////////////////////////////////////
	}
	INTEGER FindLastPos(STRING sIncoming, STRING sFindMe)
	{
		INTEGER iResult = 0;
		INTEGER iTemp = 0;
		STRING sTemp = sIncoming;
		BOOLEAN bGoFlag = TRUE;
		while bGoFlag
		{
			iTemp = StrPos(sFindMe, sTemp);
			iResult = iResult + iTemp;
			sTemp = right(sTemp, Len(sTemp)-iTemp);
			if iTemp == 0
			{
				bGoFlag = FALSE;
			}
		}
		return iResult;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataLocation_FindLastPos()
	{
		__DoTest("FindLastPos('abcabcabc','a')",FindLastPos('abcabcabc','a'),7);
		__DoTest("FindLastPos('a','a')",FindLastPos('a','a'),1);
		__DoTest("FindLastPos('abcabcabc','!')",FindLastPos('abcabcabc','!'),0);
		__DoTest("FindLastPos('abcdefghi','a')",FindLastPos('abcdefghi','a'),1);
		__DoTest("FindLastPos('abcdefghi','i')",FindLastPos('abcdefghi','i'),9);
	
	////////////////////////////////////////////////////////////////////////////
	// Contains(super,sub)
	//
	// Returns bool true if arg1 (super) contains arg2 (sub)
	// used in a wide variety of places. Accepts string, list & rect args.
	//
	// NOTES:
	// * a RECT operation is performed on the absolute rects of the passed wndtags.
	//   Since wndtag is a different type of string, if either of the passed wndtags
	//   does not exist, then the compare happens on the string.
	// * When comparing two RECTs, make sure they have the same origin, or
	//   the result will be meaningless
	//
	// USES: lContains(), rContains(), sContains()
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN Contains (CONTAINS superitem, ANYTYPE subitem, DATATYPE comptype optional)
	{
		BOOLEAN result = FALSE;
		
		if comptype == NULL
		{
			comptype = TypeOf(superitem);
		}
		switch comptype
		{
			case RECT:
				result = rContains (superitem, subitem);
			case STRING:
				result = sContains (superitem, subitem);
			case LIST:
				result = lContains (superitem, subitem);
			case WINDOW:
				result = sContains (superitem.WndTag, subitem.WndTag);
			default:
			{
				raise LIBERROR_INVALID_DATA_TYPE, "*** Error: LIBERROR_INVALID_DATA_TYPE passed to Contains([{TypeOf(superitem)}]{superitem},[{TypeOf(subitem)}]{subitem})";
			}
		}
		return result;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataLocation_Contains()
	{
		// note: Most of Contains() functionality tested in sContains, lContains, rContains
		__DoTest("Contains('string','s',STRING)"			,Contains('string','s',STRING)		, TRUE);
		__DoTest("Contains('string','s')"					,Contains('string','s')		 		, TRUE);
		__DoTest("Contains("{1,1,100,100},"{2,2,4,4},RECT)"	,Contains([RECT]{1,1,100,100},[RECT]{2,2,4,4},RECT)	, TRUE);
		__DoTest("Contains("{1,1,100,100},"{2,2,4,4})"		,Contains([RECT]{1,1,100,100},[RECT]{2,2,4,4})		, TRUE);
		__DoTest("Contains("{2,3,4,5,6},3,LIST)"			,Contains({2,3,4,5,6},3,LIST)		, TRUE);
		__DoTest("Contains("{2,3,4,5,6},3)"					,Contains({2,3,4,5,6},3)			, TRUE);
		// NOTE: WE'RE NOT TESTING WINDOW, TOO MUCH STUFF TO DEFINE, AND IT PASSED THE ABOVE CASES
		// __DoTest("Contains(,,)",	Contains(,,), )
		// __DoTest("Contains(,,)",	Contains(,,), )
		
	
	////////////////////////////////////////////////////////////////////////////
	// lContains(laSuper, aSub)
	//
	// Returns bool true if arg1 (super) contains arg2 (sub) FOR list ONLY
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN lContains (LIST OF ANYTYPE superitem, ANYTYPE subitem)
	{
		BOOLEAN result = FALSE;
		
		if ! IsVarString(subitem)
		{
			if ListFind(superitem, subitem) > 0
			{
				result = TRUE;
			}
		}
		else
		{
			ANYTYPE item;
			for each item in superitem
			{
				result = scontains (item, subitem);
				if result
				{
					break;
		
				}
			}
		}
		return result;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataLocation_lContains()
	{
		__DoTest("lContains("{2,3,4,5,6},3)"				,lContains({2,3,4,5,6},3)			, TRUE);
		__DoTest("lContains("{2,3,4,5,6},"{3,4})"			,lContains({2,3,4,5,6},{3,4})		, FALSE);
		__DoTest("lContains("{'a','bat','c'},'t')"			,lContains({'a','bat','c'},'t')			, TRUE);
	
	////////////////////////////////////////////////////////////////////////////
	// rContains(rSuper, rSub)
	//
	// Returns bool true if arg1 (super) contains arg2 (sub) FOR RECT ONLY
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN rContains (RECT superitem, RECT subitem)
	{
		BOOLEAN result = FALSE;
		
		BOOLEAN x1res, y1res, x2res, y2res;
		
		x1res = subitem.xPos >= superitem.xPos;
		y1res = subitem.yPos >= superitem.yPos;
		x2res = (subitem.xPos + subitem.xSize) <= (superitem.xPos + superitem.xSize);
		y2res = (subitem.yPos + subitem.ySize) <= (superitem.yPos + superitem.ySize);
		
		if (x1res && y1res && x2res && y2res)
		{
			result = TRUE;
		
		}
		return result;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataLocation_rContains()
	{
		__DoTest("rContains("{1,1,100,100},"{2,2,4,4})"		,rContains([RECT]{1,1,100,100},[RECT]{2,2,4,4})		, TRUE);
		__DoTest("rContains("{1,1,100,100},"{1,1,101,101})"	,rContains([RECT]{1,1,100,100},[RECT]{1,1,101,101})	, FALSE);
		__DoTest("rContains("{1,1,100,100},"{1,1,101,99})"	,rContains([RECT]{1,1,100,100},[RECT]{1,1,101,99})	, FALSE);
		__DoTest("rContains("{1,1,100,100},"{1,1,99,101})"	,rContains([RECT]{1,1,100,100},[RECT]{1,1,99,101})	, FALSE);
	
	////////////////////////////////////////////////////////////////////////////
	// sContains(sSuper, sSub)
	//
	// Returns bool true if arg1 (super) contains arg2 (sub) FOR STRING ONLY
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN sContains (STRING superitem, STRING subitem)
	{
		BOOLEAN result = FALSE;
		if strpos (subitem, superitem) > 0
		{
			result = TRUE;
		}
		return result;
		
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataLocation_sContains()
	{
		__DoTest("sContains('hello new world','new')"		,sContains('hello new world','new')			,TRUE);
		__DoTest("sContains('hello new world','New')"		,sContains('hello new world','New')			,FALSE);
		__DoTest("sContains('hello new world','hello')"		,sContains('hello new world','hello')		,TRUE);
		__DoTest("sContains('hello new world','world')"		,sContains('hello new world','world')			,TRUE);
	
	////////////////////////////////////////////////////////////////////////////
	// rpContains(rSuper, i1, i2)
	//
	// Returns bool TRUE if rect contains point
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN rpContains (RECT superitem, int x, int y)
	{
		BOOLEAN result = FALSE;
		
		BOOLEAN x1res, y1res, x2res, y2res;
		
		x1res = x >= superitem.xPos;
		y1res = y >= superitem.yPos;
		x2res = x <= (superitem.xPos + superitem.xSize);
		y2res = y <= (superitem.yPos + superitem.ySize);
		
		if (x1res && y1res && x2res && y2res)
		{
			result = TRUE;
		
		}
		return result;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataLocation_rpContains()
	{
		__DoTest("rpContains("{10,10,100,100},50,50)"		,rpContains([RECT]{10,10,100,100},50,50)	, TRUE);
		__DoTest("rpContains("{10,10,100,100},1,1)"			,rpContains([RECT]{10,10,100,100},1,1)		, FALSE);
		__DoTest("rpContains("{10,10,100,100},200,200)"		,rpContains([RECT]{10,10,100,100},200,200)	, FALSE);
		__DoTest("rpContains("{10,10,100,100},50,200)"		,rpContains([RECT]{10,10,100,100},50,200)	, FALSE);
	
	////////////////////////////////////////////////////////////////////////////
	// IsEmpty(s)
	//
	// Returns true if specified STRING == ""
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN IsEmpty (STRING sPassed)
	{
		return iff (sPassed == "", TRUE, FALSE);
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataLocation_IsEmpty()
	{
		__DoTest("IsEmpty('')"		,IsEmpty('')	, TRUE);
		__DoTest("IsEmpty('a')"		,IsEmpty('a')	, FALSE);
	
	////////////////////////////////////////////////////////////////////////////
	// FindSubstrings(s,s)	
	//
	// Returns a list of integers 
	////////////////////////////////////////////////////////////////////////////
	}
	LIST OF INTEGER FindSubstrings(STRING sSuper, STRING sSub)
	{
		OBJECT Results=cLIST().CreateWith({});
		INTEGER i,m=0;
		BOOLEAN fKeepGoing=TRUE;
		while fKeepGoing
		{
			
			i=StrPos(sSub,sSuper);
			if i==0
			{
				fKeepGoing=FALSE;
			}
			else
			{
				Results.Append(i+m);
				sSuper=SubStr(sSuper,i+1,100000);
				m=m+i;
			
			
		
			}
		}
		return Results.d;
	
	}
	private LIST __SmartFindStack={};
	Push(ANYTYPE item)
	{
		ListInsert(__SmartFindStack,item,1);
	}
	ANYTYPE Pop()
	{
		ANYTYPE Result;
		do
		{
			Result=__SmartFindStack[1];
		}
		except
		{
			raise LIBERROR_STACK_UNDERFLOW,"Stack underflow";
		}
		ListDelete(__SmartFindStack,1);
		return Result;
		
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE SmartFind(ANYTYPE aSuperItem,ANYTYPE SubItem, boolean fCaseSensitive optional, inout LIST Results optional)
	{
		if fCaseSensitive==NULL
		{
			fCaseSensitive=FALSE;
		}
		if Results==NULL
		{
			Results={};
		}
		INTEGER i;
		
		// OK, environment set up. Now start checking types
		
		if TypeOf(aSuperItem)!=LIST
		{
			SubItem=Upper("{SubItem}");
			i=StrPos(SubItem,Upper("{aSuperItem}"));
			Push(i);
		}
		else
		{
			raise 1,"ARGH!";
		}
		return i;
	// LIST a={"a","abc","c",{"a","d",{"b"}}}
	// LIST b={0,2,0,{0,0,{1}}}
	
	

// Expand for Function Library - Data Typing Functions 				(Is this of type...)
	////////////////////////////////////////////////////////////////////////////
	// IsInRange(v,Max,Min)
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN IsInRange(ANYTYPE aData, ANYTYPE aMin, ANYTYPE aMax)
	{
		return (aData <= aMax) && (aData >= aMin);
	
	
	////////////////////////////////////////////////////////////////////////////
	// IsVarType(x, dt)
	//
	// Returns true if specified variable is initialized as type specified
	//
	// IsVarBool(x)			returns true if type is boolean
	// IsVarDataclass(x)	etc.
	// IsVarInteger(x)		etc.
	// IsVarString(x)		etc.
	// IsVarWindow(x)		etc.
	// IsVarList(x)			etc.
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN IsVarType 		(ANYTYPE testvar NULL, DATATYPE maybetype)
	{
		BOOLEAN retvalue = TRUE;
		
		if testvar == NULL
		{
			retvalue = FALSE;
		}
		else
		{
			retvalue = iff (typeof (testvar) == maybetype, TRUE, FALSE);
			
		}
		return retvalue;
		
	}
	BOOLEAN IsVarBool 		(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, BOOLEAN);
	}
	BOOLEAN IsVarDataclass	(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, DATACLASS);
	}
	BOOLEAN IsVarInteger	(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, INTEGER);
	}
	BOOLEAN IsVarNumber		(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, NUMBER);
	}
	BOOLEAN IsVarLong		(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, LONG);
	}
	BOOLEAN IsVarString		(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, STRING);
	}
	BOOLEAN IsVarWindow		(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, WINDOW);
	}
	BOOLEAN IsVarObject		(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, WINDOW);
	}
	BOOLEAN IsVarList		(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, LIST);
	}
	BOOLEAN IsVarDateTime	(ANYTYPE testvar NULL)
	{
		return IsVarType (testvar, DATETIME);
	
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataTyping_IsVarType()
	{
		__DoTest("IsVarList("{1,2})"		,IsVarList({1,2})		, TRUE);
		__DoTest("IsVarList('a')"			,IsVarList('a')			, FALSE);
		__DoTest("IsVarWindow(cBASE())"		,IsVarWindow(cBASE())	, TRUE);
		__DoTest("IsVarWindow('a')"			,IsVarWindow('a')		, FALSE);
		__DoTest("IsVarString('a')"			,IsVarString('a')		, TRUE);
		__DoTest("IsVarString(7)"			,IsVarString(7)			, FALSE);
		__DoTest("IsVarLong(1)"				,IsVarLong([LONG]1)		, TRUE);
		__DoTest("IsVarLong('a')"			,IsVarLong('a')			, FALSE);
		__DoTest("IsVarNumber(1)"			,IsVarNumber([NUMBER]1)	, TRUE);
		__DoTest("IsVarNumber('a')"			,IsVarNumber('a')		, FALSE);
		__DoTest("IsVarInteger(1)"			,IsVarInteger(1)		, TRUE);
		__DoTest("IsVarInteger('a')"		,IsVarInteger('a')		, FALSE);
		__DoTest("IsVarDataclass(cBASE)"	,IsVarDataclass(cBASE)	, TRUE);
		__DoTest("IsVarDataclass('a')"		,IsVarDataclass('a')	, FALSE);
		__DoTest("IsVarBool(TRUE)"			,IsVarBool(TRUE)		, TRUE);
		__DoTest("IsVarBool('a')"			,IsVarBool('a')			, FALSE);
		// We've tested IsVarType because all the rest of these call it.
		
	
	
	////////////////////////////////////////////////////////////////////////////
	// IsDefined(a)
	//
	// Returns TRUE if the passed item is defined. If you pass in a string,
	// it is dereferenced, and the named variable is checked.
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN IsDefined(inout ANYTYPE incoming NULL)
	{
		BOOLEAN result = TRUE;
		do
		{
			if IsVarString(incoming)
			{
				incoming = @(incoming);
			}
			TypeOf(incoming);
		}
		except
		{
			result = FALSE;
			ExceptClear();
		}
		return result;
	
	

// Expand for Function Library - Data Manipulation Functions 		(Other data stuff)
	
	
	////////////////////////////////////////////////////////////////////////////
	// ApplyIfNull(inoutarg,newdata)	
	//
	// Applies the new data to the inoutarg (which is in fact spec'd as inout)
	// ONLY IF the inout arg is null. Returns the inout arg
	//
	// Target use. Replaces:
	//
	//      VOID foo(ANYTYPE Arg1)
	//          if Arg1 == NULL
	//              Arg1="Foo!"
	//
	// With this:
	//
	//      VOID foo(ANYTYPE Arg1)
	//          ApplyIfNull(Arg1, "foo")
	// 
	//      
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE ApplyIfNull(inout ANYTYPE Incoming NULL, ANYTYPE NewValue NULL)
	{
		if Incoming==NULL
		{
			Incoming=NewValue;
		}
		return Incoming;
	
	////////////////////////////////////////////////////////////////////////////
	// Assign(a1,a2)
	//
	// Returns anytype a2, which it also assigns to a1
	//
	// Used in a situation where you want to assign a value to a variable and
	// also test the value (you can do this in C, but not in 4Test).
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE Assign (inout ANYTYPE aVar NULL, ANYTYPE aValue NULL)
	{
		
		// First, try the assignment. This might generate an exception in the
		// event that there's a type mismatch. First instance, the assignment
		// BOOLEAN A="Yes" will fail.
		do
		{
			aVar = aValue;
		}
		except
		{
			
			// Having gotten to this point, we can't do a simple assignment. We
			// now have to figure out the data types and try to recast the data.
			
			// First, make sure the incoming data element is set. We need this
			// in order to get the TypeOf() the variable.
			if ! IsSet(aVar)
			{
				aVar=NULL;
			
			// Now try to get the data type
			}
			do
			{
				DATATYPE InDataType = TypeOf(aVar);
			}
			except
			{
				
				// oops, that didn't work.
				Log.LogWarning("ERROR - Assign() passed a variable which was uninitialized, ");
				Log.print("initial attempt at assign failed, and Assign() couldn't determine ");
				Log.print("the data type for recasting.");
				Log.print("(initialize the variable before passing in to Assign()).");
				reraise;
			
			// Now that we have the data type, we'll want string 
			// and number versions of the data. This makes the assignment
			// part simpler
			}
			STRING sStr = "{aValue}";
			ANYTYPE aNum = Val(sStr);
			
			// Finally, based on the data type of the passed in argument, 
			// we'll perform the assignment again.
			switch InDataType
			{
				case STRING:
					aVar = sStr;
				case BOOLEAN:
					aVar = MakeBool(sStr);
				case INTEGER:
					aVar = [INTEGER]aNum;
				case LONG:
					aVar = [LONG]aNum;
				case REAL:
					aVar = [REAL]aNum;
				case NUMBER:
					aVar = [NUMBER]aNum;
				case HANDLE:
					aVar = [HANDLE]aNum;
				case LIST OF STRING:
					LIST OF STRING lsResult = {};
					sStr=RemoveFirstAndLast(sStr);
					lsResult=MakeListFromString(sStr,",");
					aVar=lsResult;
				default:
				{
					Log.print("ERROR - Assign() passed a variable of type {InDataType}, and data of {TypeOf(aValue)}, and couldn't figure out how to convert.");
					reraise;
			
				}
			}
			ExceptClear();
		
		}
		return aVar;
		
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataManipulation_Assign()
	{
		ANYTYPE a;
		__DoTest("Assign(a,1)",			Assign(a,1),			1);
		__DoTest("Assign(a,NULL)",		Assign(a,NULL),			NULL);
		
	
	////////////////////////////////////////////////////////////////////////////
	// ListAdd(l1,l2)
	//
	// Concatenates two lists. Was part of the library before ListMerge()
	// came along.
	////////////////////////////////////////////////////////////////////////////
	}
	LIST ListAdd (inout LIST OF ANYTYPE laListToAppendTo, ANYTYPE laListToAppendFrom)
	{
		if ! IsVarList(laListToAppendFrom)
		{
			laListToAppendFrom = {laListToAppendFrom};
		}
		ListMerge(laListToAppendTo,laListToAppendFrom);
		return laListToAppendTo;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataManipulation_ListAdd()
	{
		LIST l;
		l = {'a'};
		__DoTest("ListAdd("{'a'},"{'b'})",ListAdd(l,{'b'}),{'a','b'});
		l = {'a'};
		__DoTest("ListAdd("{'a'},'b')"   ,ListAdd(l,'b')  ,{'a','b'});
		
	
	////////////////////////////////////////////////////////////////////////////
	// ListReverse()
	//
	// Takes a list and reverses the order of the elements.
	////////////////////////////////////////////////////////////////////////////
	}
	LIST ListReverse(inout LIST OF ANYTYPE lIncoming)
	{
		if lIncoming != {}
		{
			LIST OF ANYTYPE lWorkFrom = lIncoming;
			lIncoming = {};
			INTEGER l;
			for l = ListCount(lWorkFrom) to 1 step -1
			{
				ListAppend(lIncoming,lWorkFrom[l]);
			}
		}
		return lIncoming;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataManipulation_ListReverse()
	{
		LIST l;
		l = {'c','b','a'};
		__DoTest("ListReverse("{'c','b','a'})"	, ListReverse(l)		, {'a','b','c'});
		l = {'a'};
		__DoTest("ListReverse("{'a'})"			, ListReverse(l)		, {'a'});
		l = {};
		__DoTest("ListReverse("{})"				, ListReverse(l)		, {});
		
	
	////////////////////////////////////////////////////////////////////////////
	// Iff(b,aTrue, aFalse)
	//
	// Returns aTrue if b evaluates to true, else aFalse.
	// (4Test didn't always have the C style conditional operator)
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE iff (BOOLEAN expression, ANYTYPE rtrue NULL, ANYTYPE rfalse NULL)
	{
		ANYTYPE result = rfalse;
		if (expression)
		{
			result = rtrue;
		}
		return result;
	}
	private VOID ExtensionLibrary_SelfTestSuite_DataManipulation_Iff()
	{
		__DoTest("iff(TRUE,1,2)",iff(TRUE,1,2),1);
		__DoTest("iff(FALSE,1,2)",iff(FALSE,1,2),2);
		__DoTest("iff(TRUE,NULL,2)",iff(TRUE,NULL,2),NULL);
		__DoTest("iff(FALSE,1,NULL)",iff(FALSE,1,NULL),NULL);
		
	

// Expand for Function Library - Program information functions...	(GetCallStack)
	
	////////////////////////////////////////////////////////////////////////////
	// GetCallStack()
	//
	// Returns the callstack at time of entry (including itself)
	////////////////////////////////////////////////////////////////////////////
	}
	ANYTYPE GetCallStack()
	{
		do
		{
			raise 1;
		}
		except
		{
			ANYTYPE aData=ExceptCalls();
			ExceptClear();
		}
		return aData;
	}
	private VOID ExtensionLibrary_SelfTestSuite_ProgramInformation_GetCallStack()
	{
		LIST l = GetCallStack();
		INTEGER i;
		for i = 1 to ListCount(l)
		{
			l[i].sModule=GetLastMember( MakeListFromString( l[i].sModule , cSystem.sDirSeparator ) );
			l[i].iLine=0;
		}
		ListDelete(l,ListCount(l));
		__DoTest("GetCallStack()","{l}",""{"{GetCallStack, 4class4.inc, 0}, "{ExtensionLibrary_SelfTestSuite_ProgramInformation_GetCallStack, 4class4.inc, 0}, "{ExtensionLibrary_SelfTestSuite_Object.RunAllTests, 4class4.inc, 0}}");
		
	
	}
	STRING 	GetCallerFull(INTEGER i optional) 	// Give me the name of a specific caller
	{
		if i == NULL
		{
			i = 2;
		}
		LIST of CALL lcCall = GetCallStack();
		STRING sMethod = lcCall[i].sFunction;
		return sMethod;
	}
	STRING 	GetCaller(INTEGER i optional)		// Give name of specific caller, if method strip off the parents
	{
		if i == NULL
		{
			i = 3;
		}
		STRING sTemp = GetCallerFull(i+1);
		if sContains(sTemp,".")
		{
			sTemp = GetRightOf(sTemp,'.');
		}
		return sTemp;
	
	}
	ANYTYPE GetCleanCallStack() 	// returns call stack excluding self
	{
		OBJECT foo=cLIST().CreateWith(GetCallStack());
		foo.Pop();
		foo.Pop();
		return foo.d;
	}
	STRING 	GetCleanSelf()			// basically returns name of self, from the POV of the caller
	{
		OBJECT foo=cLIST().CreateWith(GetCallStack());
		foo.Pop();
		foo.Pop();
		return foo.d[1].sFunction;
	}
	STRING 	GetCleanSelfsCaller()	// basically returns name of self's caller, from the POV of the caller
	{
		OBJECT foo=cLIST().CreateWith(GetCallStack());
		foo.Pop();
		foo.Pop();
		foo.Pop();
		return foo.d[1].sFunction;
	
	}
	LIST	GetCallerList()			// returns only caller names, excluding self
	{
		OBJECT Result = cLIST().CreateWith({});
		OBJECT Calls = cLIST().CreateWith(GetCallStack());
		Calls.Pop();
		Calls.Pop();
		ANYTYPE item;
		for each item in Calls.d
		{
			Result.Append(item.sFunction);
		
		}
		return Result.d;
		
	
	}
	LIST	ReturnCallStack(LIST OF CALL lcCall NULL optional, INTEGER iStart optional, INTEGER iEnd optional)	// formats output
	{
		if lcCall==NULL
		{
			do
			{
				raise 1;
			}
			except
			{
				lcCall=ExceptCalls();
				ExceptClear();
			
			}
		}
		if iStart==NULL
		{
			iStart=1;
		}
		if iEnd==NULL
		{
			iEnd=ListCount(lcCall);
		
		}
		CALL Call ;
		LIST lReturnCalls;
		STRING sCallString = "";
		for each Call in lcCall
		{
			sCallString = "Occurred in {Call.sFunction} at {Call.sModule}({Call.iLine})";
			ListAppend(lReturnCalls,sCallString);
		
		}
		LIST EndResult = {};
		INTEGER i;
		for i = iStart to iEnd
		{
			ListAppend(EndResult,lReturnCalls[i]);
		}
		return EndResult;
	
	}
	LIST	PrintLocation()			// prints line for caller in res file in the form that 
	{
		// return ReturnCallStack()
		return ReturnCallStack(NULL,3,3);
									// hot links to that location
	

// Expand for Function Library - Window Tag Manipulation Functions	(Do things with strings that are WndTags)
	
	////////////////////////////////////////////////////////////////////////////
	// THESE FUNCTIONS ARE USED BY THE CLASS LIBRARY!
	////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////
	// TAG_StripAll(wt)
	//
	// Strip all but lowermost portions of windowtag exceluding class.
	// /[MainWin]foo/[DialogBox]Phred/[PushButton]OK becomes simply OK
	////////////////////////////////////////////////////////////////////////////
	}
	WNDTAG TAG_StripAll (WNDTAG windowtostrip, BOOLEAN SkipBrackets optional)
	{
		if SkipBrackets == NULL
		{
			SkipBrackets = FALSE;
		}
		windowtostrip = TAG_StripParentage(windowtostrip);
		if ! SkipBrackets
		{
			while scontains (windowtostrip, "]")
			{
				windowtostrip = GetRightOf(windowtostrip,"]");
			}
		}
		return windowtostrip;
	}
	private VOID ExtensionLibrary_SelfTestSuite_WndTagManipulation_TAG_StripAll()
	{
		__DoTest("TAG_StripAll('/[This]is/[A]Test/[Now]Is')",TAG_StripAll('/[This]is/[A]Test/[Now]Is'),"Is");
		__DoTest("TAG_StripAll('')",TAG_StripAll(''),'');
		__DoTest("TAG_StripAll('/')",TAG_StripAll(''),'');
		__DoTest("TAG_StripAll(']')",TAG_StripAll(''),'');
		__DoTest("TAG_StripAll('/]/]/]/]/]/')",TAG_StripAll(''),'');
		
	
	////////////////////////////////////////////////////////////////////////////
	// TAG_StripParentage(wt)
	//
	// Strip all but lowermost portions of windowtag
	// /[MainWin]foo/[DialogBox]Phred/[PushButton]OK becomes [PushButton]OK
	////////////////////////////////////////////////////////////////////////////
	}
	WNDTAG TAG_StripParentage (WNDTAG windowtostrip)
	{
		while contains (windowtostrip, "/")
		{
			windowtostrip = GetRightOf(windowtostrip,"/");
		}
		return windowtostrip;
	}
	private VOID ExtensionLibrary_SelfTestSuite_WndTagManipulation_TAG_StripParentage()
	{
		__DoTest("TAG_StripParentage('/[This]is/[A]Test/[Now]Is')",TAG_StripParentage('/[This]is/[A]Test/[Now]Is'),"[Now]Is");
		__DoTest("TAG_StripParentage('')",TAG_StripParentage(''),'');
		__DoTest("TAG_StripParentage('/')",TAG_StripParentage(''),'');
		__DoTest("TAG_StripParentage(']')",TAG_StripParentage(''),'');
		__DoTest("TAG_StripParentage('/]/]/]/]/]/')",TAG_StripParentage(''),'');
	

// Expand for Function Library - Window Query Functions				(Get window information)
	
	////////////////////////////////////////////////////////////////////////////
	// VerifyExists(w [,i])
	//
	// If the specified window does not exist, raises E_WINDOW_NOT_FOUND.
	// Argument can be either a window or a wndtag. The second parameter is
	// optional, and refers to how long to wait until failing.
	////////////////////////////////////////////////////////////////////////////
	}
	VOID VerifyExists(WNDREF Incoming, INTEGER timeout optional)
	{
		
		if ! IsVarWindow(Incoming)                        // if not window
		{
			Incoming = MoveableWin (Incoming);           // Make it be one
		
		}
		if timeout == NULL
		{
			timeout = Agent.GetOption (OPT_WINDOW_TIMEOUT);
		}
		INTEGER i;
		BOOLEAN OK = false;
		for i = 1 to timeout
		{
			if Incoming.bExists
			{
				OK = TRUE;
				break;
			}
			else
			{
				sleep(1);
			}
		}
		if ! OK
		{
			raise E_WINDOW_NOT_FOUND, Incoming.GetTag();
	
	
	////////////////////////////////////////////////////////////////////////////
	// GetWindowStatus(w, optional n)
	//
	// Returns enum of
	// WSTAT_ACTIVE, WSTAT_OBSCURED, WSTAT_DISABLED, WSTAT_MISSING, WSTAT_NOTUNIQUE
	// for a quick and consistant check of the status of a window. If window
	// does not exist when WND_Status is called, the WND_Exists function will
	// wait the number of seconds specified in the optional argument timeout,
	// otherwise it waits whatever the current window timeout is.
	// (Replaced WND_GetStatus())
	////////////////////////////////////////////////////////////////////////////
		}
	}
	WNDSTATUS GetWindowStatus (WNDREF targetwindow, NUMBER timeout optional)
	{
		if ! IsVarWindow(targetwindow)                        // if not window
		{
			targetwindow = MoveableWin (targetwindow);           // Make it be one
		
		}
		if timeout == NULL                                    // if not passed a timeout
		{
			timeout = 0.0;                                       // assume zero seconds
		
		}
		ANYTYPE PreviousTimeout = GUI_SetWindowTimeout (timeout);	// save old timeout
		
		WNDSTATUS windowstate = WSTAT_MISSING;                 // assume missing
		do
		{
			if targetwindow.bExists                               // but if exists
			{
				do
				{
					targetwindow.VerifyActive();                       // then check if active
					windowstate = WSTAT_ACTIVE;                        // if OK then active
				}
				except                                              // if NOT focus
				{
					windowstate = WSTAT_OBSCURED;                    // so if exists, but not focused, maybe obscured
					do
					{
						targetwindow.VerifyEnabled();                  // check to see if enabled
					}
					except
					{
						windowstate = WSTAT_DISABLED;                  // if no, override obscured with disabled
						ExceptClear();
					}
					ExceptClear();
				}
			}
		}
		except                                              // if NOT focus
		{
			if ExceptNum () == E_WINDOW_NOT_UNIQUE            // was window unique?
			{
				windowstate = WSTAT_NOTUNIQUE;
				ExceptClear();
			}
			else
			{
				Log.LogError("GetWindowStatus({targetwindow}) failed with exception Number: {ExceptNum()}");
				reraise;
		
			}
		}
		GUI_SetWindowTimeout (PreviousTimeout);                 // return the timeout to what it was
		return windowstate;                                     // and pass back the state
	
	}
	private VOID ExtensionLibrary_SelfTestSuite_WindowQuery_GetWindowStatus()
	{
		ExtensionLibrary_SelfTestSuite_WindowQuery_GetWindowStatus_GUISpecific_DoTest();
	}
	private VOID ExtensionLibrary_SelfTestSuite_WindowQuery_GetWindowStatus_GUISpecific_DoTest()
	{
		
		ExtensionLibrary_SelfTestSuite_TextEd1.CloseAll();
		
		__DoTest("GetWindowStatus(TextEd) sb missing",GetWindowStatus(ExtensionLibrary_SelfTestSuite_TextEd1),WSTAT_MISSING);
		ExtensionLibrary_SelfTestSuite_TextEd1.Invoke();
		__DoTest("GetWindowStatus(TextEd) sb active",GetWindowStatus(ExtensionLibrary_SelfTestSuite_TextEd1),WSTAT_ACTIVE);
		ExtensionLibrary_SelfTestSuite_TextEd1.File.Open.Pick();
		__DoTest("GetWindowStatus(TextEd) sb disabled",GetWindowStatus(ExtensionLibrary_SelfTestSuite_TextEd1),WSTAT_DISABLED);
		ExtensionLibrary_SelfTestSuite_TextEd1.Open.Close();
		ExtensionLibrary_SelfTestSuite_TextEd2.Start(ExtensionLibrary_SelfTestSuite_TextEd.sCmdLine);
		__DoTest("GetWindowStatus(TextEd) sb notunique",GetWindowStatus(ExtensionLibrary_SelfTestSuite_TextEd),WSTAT_NOTUNIQUE);
		
		__DoTest("GetWindowStatus(TextEd) sb obscured",GetWindowStatus(ExtensionLibrary_SelfTestSuite_TextEd2),WSTAT_OBSCURED);
		
		ExtensionLibrary_SelfTestSuite_TextEd1.CloseAll();
	
	
	////////////////////////////////////////////////////////////////////////////
	// GetUltimateParent(w)
	//
	// Returns the top-most parent for the passed window.
	// (replaces WND_GetAppMainWindowTag())
	////////////////////////////////////////////////////////////////////////////
	}
	WINDOW GetUltimateParent(WINDOW wIncoming)
	{
		BOOLEAN fKeepGoing = TRUE;
		LIST OF WINDOW AllWindows = {wIncoming};
		WINDOW result = wIncoming;
		while fKeepGoing
		{
			do
			{
				result = WindowParent(result);
				if result != NULL
				{
					ListAppend(AllWindows,result);
				}
				else
				{
					fKeepGoing = FALSE;
				}
			}
			except
			{
				fKeepGoing = FALSE;
				ExceptClear();
			}
		}
		if ListCount(AllWindows) == 1
		{
			result = wIncoming;
		}
		else
		{
			result = GetLastMember(AllWindows);
		
		}
		return result;
	}
	private VOID ExtensionLibrary_SelfTestSuite_WindowQuery_GetUltimateParent()
	{
		
		ExtensionLibrary_SelfTestSuite_TextEd.Invoke();
		__DoTest("GetUltimateParent(TextEd)","{GetUltimateParent(ExtensionLibrary_SelfTestSuite_TextEd)}",'ExtensionLibrary_SelfTestSuite_TextEd');
		__DoTest("GetUltimateParent(TextEd.File.Open)","{GetUltimateParent(ExtensionLibrary_SelfTestSuite_TextEd.File.Open)}",'ExtensionLibrary_SelfTestSuite_TextEd');
		__DoTest("GetUltimateParent(DesktopWin)","{GetUltimateParent(DesktopWin())}",'DesktopWin("")');
		ExtensionLibrary_SelfTestSuite_TextEd.Close();
	
	////////////////////////////////////////////////////////////////////////////
	// WND_IsAllOnScreen(wt)
	//
	// Returns TRUE if specified window is all on the screen - that is if
	// "/" rContains() checkme.
	//
	// NOTE: RETURNS FALSE IF WINDOW DOES NOT EXIST! - DOES NOT RAISE EXCEPTION
	////////////////////////////////////////////////////////////////////////////
	}
	BOOLEAN WND_IsAllOnScreen (WNDTAG checkme)
	{
		return iff (WND_Exists (checkme, 0), Contains (DesktopWin().GetRect(), WND_GetRect(checkme)), FALSE);
	}
	private VOID ExtensionLibrary_SelfTestSuite_WindowQuery_WND_IsAllOnScreen()
	{
		ExtensionLibrary_SelfTestSuite_WindowQuery_WND_IsAllOnScreen_GUISpecific_DoTest();
	}
	msw private VOID ExtensionLibrary_SelfTestSuite_WindowQuery_WND_IsAllOnScreen_GUISpecific_DoTest()
	{
		
		ExtensionLibrary_SelfTestSuite_TextEd.Invoke();
		STRING nwt = ExtensionLibrary_SelfTestSuite_TextEd.WndTag;
		INTEGER x = [INTEGER](DesktopWin().Rect.xSize);
		INTEGER y = [INTEGER](DesktopWin().Rect.ySize);
		INTEGER x2 = (x-100)*.8;
		INTEGER y2 = (y-100)*.8;
		ExtensionLibrary_SelfTestSuite_TextEd.SetActive();
		ExtensionLibrary_SelfTestSuite_TextEd.Move(100,100);
		ExtensionLibrary_SelfTestSuite_TextEd.Size(x2,y2);
		__DoTest("WND_IsAllOnScreen(TextEd)",			WND_IsAllOnScreen(ExtensionLibrary_SelfTestSuite_TextEd.WndTag),			TRUE);
		ExtensionLibrary_SelfTestSuite_TextEd.Move(x/2,y/2);
		__DoTest("WND_IsAllOnScreen(TextEd)",			WND_IsAllOnScreen(ExtensionLibrary_SelfTestSuite_TextEd.WndTag),			FALSE);
		ExtensionLibrary_SelfTestSuite_TextEd.Move(100,100);
		ExtensionLibrary_SelfTestSuite_TextEd.Close();
		__DoTest("WND_IsAllOnScreen(DesktopWin)",		WND_IsAllOnScreen(DesktopWin().WndTag),		TRUE);
		
	
	

// Expand for Function Library - Static data manipulation functions (Used by class library)
	////////////////////////////////////////////////////////////////////////////
	// STATIC System
	//
	// Creates a pool of stored data, for exchange between members of a class,
	// which may not exist at the same instant in time. Sort of like an INI file
	// in memory.
	//
	// functions
	// 			STATIC_Set(owner,key,value,readonly optional)
	//					Sets a value in the table.
	//      			If item already exists and is read only, raise
	//					LIBERROR_CANT_CHANGE_STATIC_READ_ONLY
	//			STATIC_Get(owner,key)
	//					Get a value from the table. NULL if not found
	//			STATIC_Delete(owner,key)
	//					Remove an item from the table.
	//      			if item already exists and is read only, raise
	//					LIBERROR_CANT_CHANGE_STATIC_READ_ONLY
	//			STATIC_ChangeReadOnlyAttribute(owner, key)
	//					Change readonly attribute on an item in the table.
	//			STATIC_ReturnPoolForDebug()
	//					Returns the whole pool for debugging purposes
	//
	// consts  	LIBERROR_CANT_CHANGE_STATIC_READ_ONLY
	// types   	__STATIC_STORAGE_RECORD (record of lists)
	// private 	__STATIC_STORAGE_RECORD __STATIC_InternalPrivateList
	//
	////////////////////////////////////////////////////////////////////////////
	}
	private type __STATIC_STORAGE_RECORD is record
	{
		STRING key;
		ANYTYPE value;
		BOOLEAN attrib;
	}
	private window cBASE __STATIC_STORAGE 	// this is the engine
	{
		LIST OF STRING keys = {};
		LIST OF ANYTYPE values = {};
		LIST OF BOOLEAN attribs = {};
		
		INTEGER Count()
		{
			return ListCount(this.keys);
		}
		INTEGER FindIndex(STRING sOwner,STRING sKey)
		{
			return listfind (this.keys, "{sOwner}|{sKey}");
		
		}
		VOID	Set (STRING owner, STRING key, ANYTYPE value NULL, BOOLEAN readonly NULL optional)
		{
			if readonly == NULL // if not specified, default is false
			{
				readonly = FALSE;
				
			}
			INTEGER found = FindIndex(owner,key);
			if found == 0 // if it hasn't already been set,
			{
				listappend (keys, "{owner}|{key}"); // append it to the end
				listappend (values, value);
				listappend (attribs, readonly);
				// otherwise
			}
			else
			{
				if attribs[found] == TRUE // if read only, complain
				{
					raise LIBERROR_CANT_CHANGE_STATIC_READ_ONLY, "*** Error: LIBERROR_CANT_CHANGE_STATIC_READ_ONLY in STATIC_SET({owner},{key})";
				}
				else
				{
					attribs[found] = readonly; // set the new values.
					values[found] = value;
				}
			}
		}
		ANYTYPE	Get (STRING owner, STRING key)
		{
			ANYTYPE result = NULL; // will return as null if no find
			INTEGER found = FindIndex(owner,key); // try & find it
			
			if found != 0 // if it exists,
			{
				result = values[found];
				
			}
			return result;
			
		}
		VOID	Delete   (STRING owner, STRING key)
		{
			INTEGER found = FindIndex(owner,key); // try & find it
			if found != 0 // if it exists,
			{
				if attribs[found] == TRUE // if read only, complain
				{
					raise LIBERROR_CANT_CHANGE_STATIC_READ_ONLY, "*** Error: LIBERROR_CANT_CHANGE_STATIC_READ_ONLY in STATIC_SET({owner},{key})";
				}
				else
				{
					listdelete (keys, found); // delet 'em!
					listdelete (values, found);
					listdelete (attribs, found);
					
				}
			}
		}
		VOID	ChangeReadOnlyAttribute (STRING owner, STRING key)
		{
			INTEGER found = FindIndex(owner,key); // try & find it
			if found != 0 // if it exists,
			{
				attribs[found] = ! attribs[found];
				
		
			}
		}
		__STATIC_STORAGE_RECORD Find(STRING sOwner, STRING sKey)
		{
			INTEGER i=FindIndex(sOwner,sKey);
			return Retrieve(i);
		}
		__STATIC_STORAGE_RECORD Retrieve(INTEGER i)
		{
			__STATIC_STORAGE_RECORD founditem=NULL;
			if i > 0
			{
				founditem=[__STATIC_STORAGE_RECORD]{this.keys[i],this.values[i],this.attribs[i]};
			}
			return founditem;
		
		}
		ANYTYPE	ReturnPoolForDebug () 				// not tested in the cases below
		{
			LIST ReturnPool = {{"Readonly","Key","Value"}};
			LIST CurrentItem = {};
			INTEGER i;
			for i = 1 to this.Count()
			{
				CurrentItem = {attribs[i],keys[i],values[i]};
				ListAppend(ReturnPool,CurrentItem);
			}
			return ReturnPool;
			
		
	
		}
	}
	VOID	STATIC_Set 		(STRING owner, STRING key, ANYTYPE value NULL, BOOLEAN readonly optional)
	{
		__STATIC_STORAGE.Set(owner,key,value,readonly);
		
	}
	ANYTYPE	STATIC_Get 		(STRING owner, STRING key)
	{
		return __STATIC_STORAGE.Get(owner,key);
		
	}
	VOID	STATIC_Delete   (STRING owner, STRING key)
	{
		__STATIC_STORAGE.Delete(owner,key);
	}
	VOID	STATIC_ChangeReadOnlyAttribute (STRING owner, STRING key)
	{
		__STATIC_STORAGE.ChangeReadOnlyAttribute(owner,key);
	}
	ANYTYPE	STATIC_ReturnPoolForDebug () 				// not tested in the cases below
	{
		return __STATIC_STORAGE.ReturnPoolForDebug ();
	
	}
	private VOID ExtensionLibrary_SelfTestSuite_STATIC_All()
	{
		STATIC_Set('thisistheownerfield1','thisisthekeyfield1','OK!');
		INTEGER i = __STATIC_STORAGE.Count();
		__STATIC_STORAGE_RECORD FoundItem=__STATIC_STORAGE.Retrieve(i);
		__DoTest("STATIC_Set('thisistheownerfield1','thisisthekeyfield1','OK!')",FoundItem, [__STATIC_STORAGE_RECORD]{'thisistheownerfield1|thisisthekeyfield1', 'OK!', FALSE});
		__DoTest("STATIC_Get('thisistheownerfield1','thisisthekeyfield1')",STATIC_Get('thisistheownerfield1','thisisthekeyfield1'), 'OK!');
		__DoTest("STATIC_Get('thisistheownerfield2','thisisthekeyfield2') sb NULL", STATIC_Get('thisistheownerfield2','thisisthekeyfield2'), NULL);
		
		STATIC_Set('o','k','data');
		STATIC_Delete('o','k');
		__DoTest("STATIC_Delete('o','k')",__STATIC_STORAGE.Count()==i,TRUE);
		STATIC_Set('o','k','data',TRUE);
		ANYTYPE result;
		do
		{
			result = TRUE;
			STATIC_Set('o','k','FAIL');
		}
		except
		{
			result = FALSE;
			ExceptClear();
		}
		__DoTest("STATIC_Set() on a READONLY item",result,FALSE);
		STATIC_ChangeReadOnlyAttribute('o','k');
		i = __STATIC_STORAGE.Count();
		__DoTest("STATIC_ChangeReadOnlyAttribute()",__STATIC_STORAGE.Retrieve(i)==[__STATIC_STORAGE_RECORD]{'o|k','data',FALSE},TRUE);
		
	

// Expand for Function Library - Other								(Misc, incl Stack managment routines)
	
	}
	ANYTYPE StackPop(inout LIST l)
	{
		ANYTYPE Result=NULL;
		if ListCount(l)>0
		{
			Result=l[1];
			ListDelete(l,1);
		}
		else
		{
			raise 1, "User stack underflow";
		}
		return Result;
	
	}
	VOID StackPush(inout LIST l null, ANYTYPE aData)
	{
		if l==NULL
		{
			l={};
		}
		ListInsert(l,1,aData);
	
	}
	VOID ClickIfThere(WINDOW Passed)
	{
		ANYTYPE iStatus=GetWindowStatus(Passed);
		if iStatus==WSTAT_OBSCURED
		{
			do
			{
				Passed.SetActive();
			}
			except
			{
				// nada - might fail because passed window doesn't have setactive,
				// in which case it will have setfocus
				ExceptClear();
			}
			do
			{
				Passed.SetFocus();
			}
			except
			{
				// nada - see above comment
				ExceptClear();
			}
		}
		if Passed.bExists
		{
			Passed.Click();
	
		}
	}
	VOID SmartListPrint(ANYTYPE aIn NULL)
	{
		ANYTYPE item;
		if aIn==NULL
		{
			aIn=NULL;
		}
		if IsVarList(aIn)
		{
			ResOpenList("Click to open: {aIn}");
			for each item in aIn
			{
				SmartListPrint(item);
			}
			ResCloseList();
		}
		else
		{
			print(aIn);
	

///////////////////////////////////////////////////////////////////////////

// Expand for Window Class Library - General classes				(SmartMessageBox)
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass SmartMessageBox : MessageBoxClass
	{
		STRING sSearchKey;
		
		BOOLEAN Exists()
		{
			return sContains(this.StaticText("#1").sValue,this.sSearchKey);
		}
		property bExists
		{
			BOOLEAN Get()
			{
				return this.Exists();
		
			}
		}
		VOID Dismiss (ANYTYPE howto optional)
		{
			
			STRING killme_wndtag; 	// will hold the wndtag - once we have it
			STRING killme_class; 	// class of specifed wndtag
			ANYTYPE killme_window; 	// will hold the window - if applicable
			WNDTAG killme_override; 	// overriding control name
			WNDSTATUS killme_status; // what was our state at startup?
			
			// set the dismiss lists
			ANYTYPE controllist_OK = 
			{
				"OK",
				"Yes",
				"Done",
				"Close",
				"Exit" // accept version
			};
			ANYTYPE controllist_CANCEL = 
			{
				"Cancel",
				"No",
				"Abort",
				"Close",
				"OK",
				"Exit",
				"Yes",
				"Done"
			};
			
			// Now check the window status
			if ! this.bExists
			{
				return;
			}
			if this.bExists
			{
				if ! this.bEnabled
				{
					do
					{
						this.SetActive();
					}
					except
					{
						// do nothing - this exception doesn't need to be trapped, the next peice of code
						// checks the result of this action.
						ExceptClear();
					}
				}
				if ! this.bEnabled
				{
					CustomWin(".").TypeKeys("<Esc>");
				}
			}
			if this.bExists
			{
				if ! this.bEnabled
				{
					do
					{
						this.SetActive();
					}
					except
					{
						// do nothing - this exception doesn't need to be trapped, the next peice of code
						// checks the result of this action.
						ExceptClear();
					}
				}
				if ! this.bEnabled
				{
					raise LIBERROR_CANT_CLOSE_OBSCURING_WINDOW, "*** Error: LIBERROR_CANT_CLOSE_OBSCURING_WINDOW in {this}.Dismiss()";
			
			// Let's get our options right
				}
			}
			ANYTYPE controllist = controllist_CANCEL+controllist_OK;
			if howto == NULL // has hiwto been initialized?
			{
				howto = CANCEL; // default operation
			}
			if IsVarString(howto)
			{
				ListInsert(controllist,1,howto);
				howto = CUSTOM;
			}
			else
			{
				if howto == ACCEPT
				{
					controllist = controllist_OK+controllist_CANCEL;
			
				}
			}
			ANYTYPE currentcontrol; 	// used to process controllist
			for each currentcontrol in controllist
			{
				currentcontrol = this.PushButton(currentcontrol);
				if currentcontrol.bExists
				{
					currentcontrol.Click();
			
				}
			}
			if this.bExists // if still there, try smashing it.
			{
				WND_Close (this.WndTag);
			
			}
			if this.bExists
			{
				raise LIBERROR_CANT_CLOSE_WINDOW, "*** Error: LIBERROR_CANT_CLOSE_WINDOW in {this}.Dismiss()";
	

// Expand for Window Class Library - DOS window classes				(DOS_MainWin, DOS_AnyWIn, DOS_DialogBox, etc...)
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
			}
		}
	}
	WINDOW DialogBox DOS_Selector_Window
	{
		tag "Select Command Prompt";
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	}
	winclass DOS_MainWin    		: DialogBox
	{
		
		// NOTE: RECT is in CHARS not in PIXELS!!!
		TEXT GetTextfromScreen(RECT Region, BOOLEAN fForce optional)
		{
			if fForce==NULL
			{
				fForce=FALSE;
			}
			if fForce
			{
				fCachedScreenDirtyFlag=TRUE;
			
			}
			LIST OF STRING Result={};
			// extract the required strings
			SnapScreen();
			
			// use sub STRING functions and list index selectors to create LIST OF STRING for
			// the rect that was passed in as CharRect
			// return that LIST OF string
			
			INTEGER i;
			if Region.ySize > ListCount(lsScreenCapture)
			{
				Region.ySize = ListCount(lsScreenCapture);
			}
			for i=Region.yPos to Region.yPos+(Region.ySize-1)
			{
				ListAppend(Result,trim(Substr(lsScreenCapture[i],Region.xPos,Region.xSize)));
			
			//Log.ListPrint(Result)
			
			}
			return Result;
		}
		VOID SnapScreen(BOOLEAN fForce optional)
		{
			//capture the whole dos screen
			this.SetActive();
			if fForce==NULL
			{
				fForce=FALSE;
			}
			if fForce
			{
				fCachedScreenDirtyFlag=TRUE;
			}
			if fCachedScreenDirtyFlag || (MakeText(lsScreenCapture) == {})
			{
				if DOS_Selector_Window.bExists
				{
					this.TypeKeys("<Esc>");
				}
				this.SysMenu.MenuItem("Edit").MenuItem("Mark").Pick();
				this.TypeKeys("<Shift-Right 80><Shift-PgDn><Enter>");
				
				// gets the text off the clipboard
				lsScreenCapture = Clipboard.GetText();
				fCachedScreenDirtyFlag = FALSE;
			}
		}
		VOID __DumpScreen()
		{
			Log.ListPrint(this.GetTextFromScreen({1,1,80,50}));
		
		}
		BOOLEAN fCachedScreenDirtyFlag = TRUE;
		TEXT lsScreenCapture = {};
		
		property d
		{
			LIST Get()
			{
				return {fCachedScreenDirtyFlag,lsScreenCapture};
		
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
			}
		}
	}
	winclass DOS_AnyWin     		: AnyWin
	{
		
		property bCheckExists
		{
			BOOLEAN Get()
			{
				return this.__bCheckExists;
			}
		}
		property Application
		{
			WINDOW Get()
			{
				return GetUltimateParent(this);
			}
		}
		property rCaptionRect
		{
			RECT Get()
			{
				return this.__TakeTagApart()[1];
			}
		}
		property Rect
		{
			RECT Get()
			{
				return this.__TakeTagApart()[3];
			}
		}
		property iTabOrder
		{
			INTEGER Get()
			{
				return val(this.__TakeTagApart()[4]);
			}
		}
		property sCaption
		{
			STRING GET()
			{
				return this.__TakeTagApart()[2];
			}
		}
		property sHotKey
		{
			STRING Get()
			{
				return this.__TakeTagApart()[5];
			}
		}
		property wParent
		{
			WINDOW Get()
			{
				return WindowParent(this);
		
			}
		}
		TEXT GetTextFromScreen(RECT RectToUse)
		{
			WINDOW myapp = this.Application;
			return myapp.GetTextFromScreen(RectToUse);
		}
		TEXT GetCaptionFromScreen()
		{
			return this.GetTextFromScreen(this.rCaptionRect);
		}
		TEXT GetFieldValueFromScreen()
		{
			return this.GetTextFromScreen(this.Rect);
		}
		VOID TypeHotkey(STRING sOverride optional)
		{
			STRING sToUse = "";
			if sHotKey != ""
			{
				sToUse = sHotKey;
			}
			if sOverride != NULL
			{
				sToUse = sOverride;
			}
			if sToUse != ""
			{
				Agent.FlushEvents ( );
				Application.fCachedScreenDirtyFlag = TRUE;
				this.Application.ReleaseKeys("<Shift>");
				this.Application.TypeKeys(sToUse);
				Agent.FlushEvents ( );
			}
		}
		BOOLEAN Exists()
		{
			BOOLEAN result = FALSE;
			if this.Application.Exists()
			{
				result = ( this.GetCaptionFromScreen()[1] == this.sCaption );
			}
			return result;
		}
		property bExists
		{
			BOOLEAN Get()
			{
				return this.Exists();
		
			}
		}
		VOID VerifyExists()
		{
			if this.bCheckExists
			{
				INTEGER iCountSeconds = Agent.GetOption (OPT_WINDOW_TIMEOUT);
				INTEGER l;
				for l = 1 to iCountSeconds
				{
					
					if (! this.Exists())
					{
						Application.fCachedScreenDirtyFlag = TRUE;
						sleep(1);
					}
					else
					{
						l = iCountSeconds;
						break;
				
					}
				}
				if (! this.Exists())
				{
					Log.print("---------------------------------------------------------------");
					this.Application.__DumpScreen();
					Log.print("---------------------------------------------------------------");
					Log.print("Expected: |{this.sCaption}|");
					Log.print("At      : |{this.rCaptionRect}|");
					Log.print("Got     : |{this.GetCaptionFromScreen()[1]}|");
					Log.print("---------------------------------------------------------------");
					raise LIBERROR_DOS_WINDOW_OBJECT_NOT_FOUND,"*** Error: LIBERROR_DOS_WINDOW_OBJECT_NOT_FOUND on {this}";
			
		
				}
			}
		}
		BOOLEAN __bCheckExists = TRUE;
		
		// Takes a tag in the form "12,14,10,1|USERNAME|22,14,10,1|3|<Tab>"
		// and converts it into some RECTs, strings, and integers:
		// {{12,14,10,1},"USERNAME",{22,14,10,1},3,"<Tab>"}
		//  -RECT------   STRING--  -RECT------- I  STRING
		// Where I = INTEGER
		LIST __TakeTagApart()
		{
			{
				
				do
				{
					LIST OF ANYTYPE Result = {};
					
					// get the tag for a text field for (ex. "12,14,10,1|USERNAME|22,14,10,1|3|<Tab>")
					STRING sDataTextTag = TAG_StripAll(WindowTag(this));
					
					// make a STRING at each delimiter
					LIST OF STRING TagFields = MakeListFromString (sDataTextTag, "|");
					
					// make a list of STRING from csv form(STRING with "," in them as "12""14""10""1")--part1
					LIST OF ANYTYPE Rect1;
					Rect1 = MakeListFromCSV (TagFields[1]);
					
					// append the first rect
					ListAppend(Result, [RECT]{Val(Rect1[1]),Val(Rect1[2]),Val(Rect1[3]),Val(Rect1[4])});
					
					//append the caption, STRING "USERNAME" in result--part2
					ListAppend(Result,TagFields[2]);
					
					// append second rect
					LIST OF ANYTYPE Rect2;
					Rect2 = MakeListFromCSV (TagFields[3]);
					ListAppend(Result, [RECT]{Val(Rect2[1]),Val(Rect2[2]),Val(Rect2[3]),Val(Rect2[4])});
					
					// append the tab order to result--part4
					ListAppend(Result,TagFields[4]);
					
					// lastly append the command for tab--part4
					ListAppend(Result,TagFields[5]);
				}
				except
				{
					Log.print("Exception Data - tag:              {sDataTextTag}");
					Log.print("Exception Data - TagFields (sb 5): {TagFields}");
					Log.print("Exception Data - Result:           {Result}");
					reraise;
				}
				return Result;
			
		
		
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
			}
		}
	}
	winclass DOS_DialogBox  		: DOS_AnyWin {}
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	winclass DOS_PushButton 		: DOS_AnyWin
	{
		VOID Click()
		{
			this.VerifyExists();
			this.Application.fCachedScreenDirtyFlag = TRUE;
			this.TypeHotkey();
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass DOS_TextField  		: DOS_AnyWin
	{
		
		INTEGER iExtraCharacters = 0;
		
		VOID	SelectField()
		{
			if iTabOrder != 0
			{
				Application.fCachedScreenDirtyFlag = TRUE;
				STRING sTabOrder = (Right('00{iTabOrder}',2));
				Agent.FlushEvents();
				this.Application.TypeKeys("<F2>{sTabOrder}");
				Agent.FlushEvents();
				this.Application.TypeKeys("<F2>{sTabOrder}");
				Agent.FlushEvents();
				this.Application.TypeKeys("<F2>{sTabOrder}");
				Agent.FlushEvents();
				this.Application.TypeKeys("<F2>{sTabOrder}");
				Agent.FlushEvents();
				this.Application.TypeKeys("<F2>{sTabOrder}");
				Agent.FlushEvents();
				this.Application.TypeKeys("<F2>");
				Agent.FlushEvents();
				this.Application.TypeKeys("{sTabOrder}");
				Agent.FlushEvents();
			
			}
		}
		VOID 	ClearText()
		{
			this.Application.SetActive();
			Agent.FlushEvents();
			this.Application.TypeKeys("<Ctrl-Y>");
			Agent.FlushEvents();
			//sleep(1)
			// if this.Rect.xSize > 1
			{
				// SelectField()
				// //this.Application.TypeKeys("<Ctrl-D>")
				//
				// STRING sOnEntry = this.GetText()
				// WhitneySystem.fCachedScreenDirtyFlag = TRUE
				//
				// if sDeleteKey == 'UNSET'
				{
					// STRING firstchar = sOnEntry
					// if firstchar == '.'
					{
						// this.Application.TypeKeys('z')
					// this.Application.TypeKeys("<delete>")
					// WhitneySystem.fCachedScreenDirtyFlag = TRUE
					// firstchar = this.GetText()[1]
					// if firstchar == '.'
						// sDeleteKey = "<ctrl-g>"
						// sOnEntry = '.'+sOnEntry
						// this.Application.TypeKeys('<ctrl-h>')
					// else
						// sDeleteKey = "<delete>"
				//
				// INTEGER i
				// for i = 1 to this.Rect.xSize
					// this.Application.TypeKeys(sDeleteKey)
					// Agent.FlushEvents()
				// WhitneySystem.fCachedScreenDirtyFlag = TRUE
			
					}
				}
			}
		}
		VOID   	VerifyContents(STRING Incoming)
		{
			if iExtraCharacters == 0
			{
				STRING sValue = this.GetText();
				if lower(trim(Incoming)) != lower(trim(sValue))
				{
					Log.print("--------------------------------------------------------------");
					Log.print("FAILED IN {this.Class}.{this.sName}.SetText('{Incoming}')");
					Log.print("FOUND: '{sValue}'");
					raise LIBERROR_DOS_CONTROL_NOT_RESPONDING, "*** Error: LIBERROR_DOS_CONTROL_NOT_RESPONDING in {this.Class}.{this.sName}";
				}
			}
		}
		STRING 	GetText()
		{
			this.VerifyExists();
			return this.GetFieldValueFromScreen()[1];
		}
		VOID 	SetText(STRING Incoming, BOOLEAN fRawMode optional)
		{
			if fRawMode == NULL
			{
				fRawMode = FALSE;
			}
			this.VerifyExists();
			
			if ! fRawMode
			{
				Agent.FlushEvents();
				if len(trim(sHotKey)) != 0
				{
					this.TypeHotKey();
				}
				else
				{
					SelectField();
				}
				this.ClearText();
				// this.Application.TypeKeys ("<CTRL-D>")
			
			}
			Application.fCachedScreenDirtyFlag = TRUE;
			//Application.TypeKeys("<Delete>")
			Application.TypeKeys(Incoming);
			if len(Incoming) < (this.Rect.xSize+this.iExtraCharacters)
			{
				Application.TypeKeys('<Enter>');
			}
			if bExists && (! fRawMode)
			{
				VerifyContents(Incoming);
		
			}
		}
		property lsValue
		{
			TEXT Get()
			{
				return this.GetText();
			}
			VOID Set(TEXT Incoming)
			{
				this.SetText(Incoming);
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
			}
		}
	}
	winclass DOS_MenuGroup			: DOS_AnyWin {}
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	winclass DOS_Menu       		: DOS_AnyWin
	{
		VOID Pick()
		{
			VerifyExists();
			Application.fCachedScreenDirtyFlag = TRUE;
			this.TypeHotkey();
		
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass DOS_MenuItem   		: DOS_Menu
	{
		VOID Pick()
		{
			this.wParent.Pick();
			VerifyExists();
			Application.fCachedScreenDirtyFlag = TRUE;
			this.TypeHotkey();
			
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass DOS_ListBox    		: DOS_AnyWin
	{
		
		TEXT GetScreenContents()
		{
			this.VerifyExists();
			return this.GetFieldValueFromScreen();
		
		// TEXT GetContents()
			// // should scroll through the screen and get all the strings
			//
		}
		BOOLEAN IsValueDisplayed(STRING aSelector)
		{
			
			if (ListFind(GetScreenContents(),aSelector)==0)
			{
				Log.LogWarning("*** Warning: Item {aSelector} not found in {this}");
				return FALSE;
			}
			else
			{
				return TRUE;
			
		
			}
		}
		VOID Select(LISTITEM aSelector)
		{
			this.VerifyExists();
			this.__bCheckExists = FALSE;
			
			if IsVarString(aSelector)
			{
				LIST OF STRING lsListContents;
				this.Application.typekeys(aSelector);
				Application.fCachedScreenDirtyFlag = TRUE;
				if(IsValueDisplayed(aSelector)==TRUE)
				{
					//Log.print("ID {aSelector} is Found.")
					this.application.typekeys("<ENTER>");
				}
				else
				{
					//Log.print("ID {aSelector} is not Found.")
					raise E_ITEM_NOT_FOUND, "*** Error: E_ITEM_NOT_FOUND in {this} looking for {aSelector}";
					//need to click add if employee not found.
				}
			}
			else
			{
				this.application.typekeys("<HOME><HOME>");
				INTEGER i;
				for i = 1 to (aSelector - 1)
				{
					this.application.typekeys("<DOWN>");
			
				}
			}
			this.__bCheckExists = TRUE;
			Application.fCachedScreenDirtyFlag = TRUE;
			
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass DOS_PopupMenu			: DOS_DialogBox
	{
		VOID Pick()
		{
			VerifyExists();
			Application.fCachedScreenDirtyFlag = TRUE;
			this.TypeHotkey();
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass DOS_StaticText			: DOS_AnyWin
	{
		TEXT GetText()
		{
			this.VerifyExists();
			return this.GetFieldValueFromScreen();
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass DOS_Group				: DOS_AnyWin {}
	
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	winclass DOS_MessageBox			: DOS_AnyWin {}
	
	

///////////////////////////////////////////////////////////////////////////

// Expand for Abstract Object Library - General classes 			(cBASE, cTIMER)
	
	////////////////////////////////////////////////////////////////////////////
	// cBASE		Virtual base class for this object library
	//
	// Purpose:		Provides object ID services to other classes
	//
	// Expand this for documentation
	{
		//
		// inherits:	none
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		//		Class			ro: dataclass of this
		// 		sName			ro: STRING name of this
		// 		loChildren		ro: list of object children of this. In this
		//						case this means objects contained as data
		//						members of this.
		// 		oParent 		ro: object of parent to this. If there is
		// 						no parent for the object, returns NULL.
		//						In this case, Parent means an object which
		//						has this as one of it's data members.
		//		sClass			ro: String of the class name of this
		// 		sParent 		ro: STRING of name of parent window object
		// 						OR empty STRING if none.
		//		sParentClass	ro: Returns a STRING of the parent's class name
		// 		sPassedValue 	ro: STRING of value passed to object at
		// 						instantiation time
		//		sRawPassedValue	ro: Unaltered passed value. Usually the only
		//						difference between this and sPassedValue is that
		//						this one wwill have a leading slash.
		//		ldInheritsFrom	ro: Lists all the classes this inherits from
		//
		// PUBLIC MEMBERS - METHODS:
		//
		//		GetClass() 		returns dataclass of this
		//		GetName()		returns the name of this
		//		GetParent()		returns the parent (container object) of this
		//		GetChildren()	returns the objects contained by this
		//		GetPassedValue()returns the STRING passed at instantiation time
		//						or specified using the 'tag' keyword.
		//		IsDefined(s)	TRUE if item named exists within this
		//		IsOfClass(dc)	TRUE if this inherits from dc
		//		MakeDeepCopy()	Returns an object of the same class as this, with
		//						all data memebers copied from this.
		//						NOTE: While this recursivly copies contained objects,
		//						IT DOES NOT YET deep copy contained lists which
		//						contain objects.
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//		AssignValues(l)	Accepts list of anytype and assigns the values to
		//						any data member fields which are defined for this
		//						in the order they are specified in the constants
		//						lsClassFieldList and lsInstanceFieldList. See below
		//						for more information.
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//		SelectiveAssignValues(ls,la) Makes assignments as above, except
		//						rather than using the built in lists, this allows
		//						you to specify the field names. Can also be used
		//						to make assignments to rw properties. The first list
		//						is the list of fields, and the second list is the
		//						list of values to assign. Item 1 in the first list
		//						will get item 1 from the second list assigned to
		//						it, item 2 gets item 2... and so on.
		//		StorePersistant(F)	Stores this to disk. Will store all fields
		//						from this to a file.
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//		RetrievePersistant(F) Retrieves values stored with StorePersistant()
		//						These two calls can be used to reinitialize something
		//						if you have to end it, but want it to pick up where
		//						it left off.
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//		DebugPrint(F)	Prints all the fields and properties of this for
		//						debugging purposes. F is optional and is a reference
		//						to a log file. If F is specified, the DebugPrint will
		//						go to BOTH the res file and the file specified in F.
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//		GetAllClassesThisInheritsFrom() Returns a list of all the classes
		//						which this inherits from.
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//		GetFieldsOfObject() Returns fields defined for this object from the
		//						constants lsClassFieldList and lsInstanceFieldList
		//						BUT DOES NOT RETURN INHERETED FIELDS!
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//		GetAllFieldsOfObject() Returns fields defined for this object from the
		//						constants lsClassFieldList and lsInstanceFieldList
		//						BUT THIS ON DOES RETURN INHERETED FIELDS!
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//		GetPropertiesOfObject() Returns the names of the properties defined for
		//						for this object in lsClassPropertyList and lsInstancePropertyList
		//						BUT DOES NOT RETURN INHERETED FIELDS!
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//		GetAllPropertiesOfObject() Returns the names of the properties defined for
		//						for this object in lsClassPropertyList and lsInstancePropertyList
		//						BUT THIS ON DOES RETURN INHERETED FIELDS!
		//						DEPENDS ON THE CONSTANTS LISTED BELOW.
		//
		// PUBLIC MEMBERS - CONSTANTS:
		//
		//		dcInheritsFrom			dataclass which this inherits from. This is
		//								required for several of the methods provided by
		//								cBASE. You MUST override this in your class
		//								definitions with the correct inherited class
		//								of your new class. This kludge is required because
		//								Silk doesn't provide this functionality.
		//		lsClassFieldList		List of STRING for the names of any data members
		//								defined in the CURRENT class definition.
		//								As with the above, Silk doesn't provide this
		//								functionality, so you have to do it manually.
		//								EVEN IF YOU DON'T DEFINE ADDITIONAL ELEMENTS
		//								YOU MUST DEFINE THIS CONSTANT AS = {} TO PREVENT
		//								INHERETED ITEMS FROM BEING LISTED TWICE.
		//		lsClassPropertyList		List of STRING for the names of any properties
		//								defined in the CURRENT class definition.
		//								As with the above, Silk doesn't provide this
		//								functionality, so you have to do it manually.
		//								EVEN IF YOU DON'T DEFINE ADDITIONAL ELEMENTS
		//								YOU MUST DEFINE THIS CONSTANT AS = {} TO PREVENT
		//								INHERETED ITEMS FROM BEING LISTED TWICE.
		//		lsInstanceFieldList		Unlike the above, this is a list of data members
		//								that might be defined in a global instance.
		//								As with the above, Silk doesn't provide this
		//								functionality, so you have to do it manually.
		//								EVEN IF YOU DON'T DEFINE ADDITIONAL ELEMENTS
		//								YOU MUST DEFINE THIS CONSTANT AS = {} TO PREVENT
		//								INHERETED ITEMS FROM BEING LISTED TWICE.
		//		lsInstancePropertyList	As with the above, list properties here that
		//								you might define in a global instance.
		//								As with the above, Silk doesn't provide this
		//								functionality, so you have to do it manually.
		//								EVEN IF YOU DON'T DEFINE ADDITIONAL ELEMENTS
		//								YOU MUST DEFINE THIS CONSTANT AS = {} TO PREVENT
		//								INHERETED ITEMS FROM BEING LISTED TWICE.
		//
	//
	////////////////////////////////////////////////////////////////////////////
	}
	winclass cBASE
	{
		
		// ATTRIBUTES OF THIS
		property 			Class
		{
			DATACLASS Get ()
			{
				return this.GetClass();
			}
		}
		property 			sClass
		{
			STRING Get()
			{
				return "{this.Class}";
			}
		}
		property 			sRawName
		{
			STRING Get()
			{
				return WindowName(this);
			}
		}
		property 			sName
		{
			STRING Get ()
			{
				// get the raw name first
				OBJECT soResult=cSTRING(this.sRawName);
				
				if (soResult.Right(2)=="()") && (this.sPassedValue != "")
				{
					soResult.Insert(-2,this.sPassedValue);
				
				// now see if there's a user set name to override with 
				}
				if this.__sUserSpecifiedName != NULL
				{
					soResult.d=__sUserSpecifiedName;
				
				}
				return soResult.d;
				
			}
			VOID Set(STRING sIn)
			{
				this.__sUserSpecifiedName=sIn;
			}
		}
		property 			sPassedValue
		{
			STRING Get ()
			{
				STRING sTemp = WindowTag (this);
				sTemp[1] = EMPTYSTRING;
				return sTemp;
			}
		}
		property 			sRawPassedValue
		{
			STRING Get()
			{
				return WindowTag(this);
			}
		}
		property			sFullName
		{
			STRING Get()
			{
				LIST RawData=this.lwParents;
				ANYTYPE item;
				STRING sResult="";
				for each item in RawData
				{
					
					sResult=item.sRawName+"."+sResult;
					
				
				}
				sResult=GetAllButLast(sResult);
				
				return sResult;
				
		
		// ATTRIBUTES OF PARENT OR INHERETENCE
			}
		}
		property 			ldInheritsFrom
		{
			LIST OF DATACLASS Get()
			{
				return this.GetAllClassesThisInheritsFrom();
			}
		}
		property 			oParent
		{
			WINDOW Get ()
			{
				ANYTYPE result = NULL;
				do
				{
					result = WindowParent (this);
				}
				except
				{
					// oops. I guess we don't have a parent.
					ExceptClear();
				}
				return result;
			}
		}
		property 			sParent
		{
			STRING Get ()
			{
				ANYTYPE temp;
				do
				{
					temp = WindowParent (this);
					temp = temp.sName;
				}
				except
				{
					temp = EMPTYSTRING;
					ExceptClear();
				}
				return temp;
			}
		}
		property 			sParentClass
		{
			STRING Get ()
			{
				STRING sResult = "";
				STRING sMyParent = this.sParent;
				
				if sMyParent != ""
				{
					sResult = "{this.oParent.Class}";
				}
				return sResult;
				
			}
		}
		property 			wParent
		{
			WINDOW Get ()
			{
				ANYTYPE temp;
				do
				{
					temp = WindowParent (this);
				}
				except
				{
					temp = NULL;
					ExceptClear();
				}
				return temp;
			}
		}
		property 			lwParents
		{
			LIST Get()
			{
				LIST lResult={};
				WINDOW Current=this;
				while Current.wParent != NULL
				{
					ListAppend(lResult,Current);
					do
					{
						Current=Current.wParent;
					}
					except
					{
						Current=NULL;
					
				
					}
				}
				ListAppend(lResult,Current);
				return lResult;
				
			
		
		// ATTRIBUTES OF CHILDREN
			}
		}
		property 			loChildren
		{
			LIST OF WINDOW Get ()
			{
				return (WindowChildren (this));
			}
		}
		property 			lsChildrenNames
		{
			LIST OF STRING Get()
			{
				ANYTYPE item;
				LIST OF STRING result = {};
				for each item in loChildren
				{
					ListAppend(result, item.sName);
				}
				return result;
		
			}
		}
		LIST OF DATACLASS 	GetAllClassesThisInheritsFrom()
		{
			LIST OF DATACLASS ldResult = {this.Class};
			BOOLEAN fKeepGoing = TRUE;
			ANYTYPE temp;
			
			WINDOW Active = this;
			while fKeepGoing
			{
				if Active.dcInheritsFrom == NULL
				{
					fKeepGoing = FALSE;
				}
				else
				{
					temp = Active.dcInheritsFrom;
					Active = @('{temp}')();			// Create an instance
					ListAppend(ldResult,Active.Class);
			
				}
			}
			return ldResult;
			
		}
		LIST OF OBJECT 		GetChildren()
		{
			return (WindowChildren (this));
		}
		DATACLASS 			GetClass()
		{
			return (ClassOf (this));
		}
		STRING				GetExtName(varargs OF ANYTYPE laPassed)
		{
			
			// Class and instance part
			STRING sResult='{this.sName}={this.Class}({this.sPassedValue})';
			
			// Method part
			sResult='{sResult}.{GetCaller(4)}';
			
			// Args part
			sResult=sResult+'(';
			if laPassed == {}
			{
				sResult=sResult+"?";
			}
			else
			{
				ANYTYPE item;
				for each item in laPassed
				{
					sResult=sResult+'{item},';
				}
				sResult[Len(sResult)]='';
				
			}
			sResult=sResult+')';
			
			return sResult;
		}
		STRING				GetFullMethodName()
		{
			return this.sFullName+"."+GetCaller(4);
		}
		STRING				GetName()
		{
			return this.sName;
		}
		STRING				GetPassedValue()
		{
			STRING sTemp = WindowTag (this);
			sTemp[1] = EMPTYSTRING;
			return sTemp;
		}
		OBJECT				GetParent()
		{
			return WindowParent(this);
		}
		BOOLEAN				IsOfClass (ANYTYPE Incoming, BOOLEAN fExact optional)
		{
			BOOLEAN fResult=FALSE;
			BOOLEAN fTemp;
			if IsVarList(Incoming)
			{
				ANYTYPE item;
				for each item in Incoming
				{
					fTemp=WindowIsOfClass (this, item);
					fResult=(fResult && fTemp);
				}
			}
			else
			{
				fResult=WindowIsOfClass (this, Incoming, fExact);
			
			}
			return fResult;
		}
		BOOLEAN				IsDefined (STRING sName, out DATACLASS Class null optional, WINDOWDEFINEDHOW DefinedHow optional)
		{
			return (WindowIsDefined (this, sName, Class, NULL, DefinedHow));
		}
		OBJECT 				SetName(STRING sNewName)
		{
			this.__sUserSpecifiedName=sNewName;
			return this;
		}
		VOID				VerifyIsOfClass(DATACLASS NewClass, BOOLEAN fExact null optional)
		{
			if ! this.IsOfClass(NewClass, fExact)
			{
				raise LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS, "*** Error: LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS on {this} - Should be {NewClass} not {this.Class}";
		
			}
		}
		OBJECT				AssignValues(LIST OF ANYTYPE incoming)
		{
			INTEGER ileng = ListCount(incoming);
			LIST OF STRING lscompleteFieldList = this.lsClassFieldList+this.lsInstanceFieldList;
			INTEGER ifields = ListCount(lscompleteFieldList);
			if ileng < ifields
			{
				raise LIBERROR_WRONG_NUMBER_OF_ARGUMENTS,'*** Error: LIBERROR_WRONG_NUMBER_OF_ARGUMENTS - Too many fields passed (should have been less than {ifields} not {ileng}) to {this}.Assign({incoming})';
			}
			ANYTYPE i;
			for i = 1 to ileng
			{
				do
				{
					@(lscompleteFieldList[i]) = incoming[i];
				}
				except
				{
					// must have been a property or not exist
					raise LIBERROR_CANT_PERFORM_ASSIGNMENT,"*** Error: LIBERROR_CANT_PERFORM_ASSIGNMENT on {this}.{lscompleteFieldList[i]}";
				}
			}
			return this;
		}
		LIST OF STRING 		GetFieldsOfObject()
		{
			LIST OF STRING lsResult = this.lsClassFieldList+this.lsInstanceFieldList;
			return lsResult;
		}
		LIST OF STRING 		GetPropertiesOfObject()
		{
			LIST OF STRING lsResult = this.lsClassPropertyList+this.lsInstancePropertyList;
			return lsResult;
		}
		LIST OF STRING 		GetAllFieldsOfObject()
		{
			
			return this.__GatherInheretedLists({"lsClassFieldList","lsInstanceFieldList"});
			
		}
		LIST OF STRING 		GetAllPropertiesOfObject()
		{
			
			return this.__GatherInheretedLists({"lsClassPropertyList","lsInstancePropertyList"});
			
		
		}
		LIST OF ANYTYPE 	GetValues(LIST OF STRING lsPassedFieldList)  // AMM 20041110: returns list of anytype, of values from fields specified
		{
			ANYTYPE item;
			OBJECT Result=cLIST();
			for each item in lsPassedFieldList
			{
				Result.Append(this.@(item));
			}
			return Result.d;
		}
		OBJECT				MakeDeepCopy()
		{
			LIST OF STRING fullfieldlist = this.GetAllFieldsOfObject();
			OBJECT new = @(this.sClass)();
			ANYTYPE item;
			for each item in fullfieldlist
			{
				if IsVarObject(item)
				{
					new.@(item) = item.MakeDeepCopy();
				}
				else
				{
					new.@(item) = this.@(item);
				}
			}
			return new;
		}
		OBJECT				SelectiveAssignValues(LIST OF STRING lsFields, LIST OF ANYTYPE laValues, BOOLEAN fForceErrorChecking optional)
		{
			if fForceErrorChecking == NULL
			{
				fForceErrorChecking = FALSE;
			}
			if fForceErrorChecking
			{
				if ListCount(lsFields) != ListCount(laValues)
				{
					if ListCount(lsFields) > ListCount(laValues)
					{
						Log.LogWarning("There were more fields in {this} than there were data elements");
					}
					if ListCount(lsFields) < ListCount(laValues)
					{
						Log.LogWarning("There were more data elements in the passed data than there were fields in {this}");
					}
					Log.ResPrintList("lsFields = {ListCount(lsFields)}",lsFields);
					Log.ResPrintList("laValues = {ListCount(laValues)}",laValues);
					raise LIBERROR_WRONG_NUMBER_OF_ARGUMENTS,'*** Error: LIBERROR_WRONG_NUMBER_OF_ARGUMENTS - Lists passed to SelectiveAssignValues(x,y) were not the same length.';
			
				}
			}
			INTEGER counter;
			INTEGER iMax = Min(ListCount(lsFields),ListCount(laValues));
			for counter = 1 to iMax
			{
				do
				{
					if lsFields[counter] != ""
					{
						Assign(this.@(lsFields[counter]),laValues[counter]);
					}
				}
				except
				{
					
					Log.LogWarning("Unable to assign, {this.sName}.{lsFields[counter]}={laValues[counter]}");
					Log.print("Perhaps the variable name is misspelled? Here are the list of fields:");
					Log.print(lsFields);
					Log.print(laValues);
					Log.ExceptPrint();
					Log.print("------------------------------------");
					ExceptClear();
				}
			}
			return this;
		}
		OBJECT				SelectiveAssignValuesToClass(LIST OF ANYTYPE laValues)
		{
			return SelectiveAssignValues(lsClassFieldList,laValues);
		}
		VOID				RetrievePersistant(FILEREF FileToUse)
		{
			OBJECT TheFile = cOPENFILE();
			TheFile.AssignFileName(FileToUse);
			LIST OF ANYTYPE result = TheFile.ReadValue(FILEREF);
			this.Assign(result);
		}
		VOID				StorePersistant(FILEREF FileToUse)
		{
			LIST OF ANYTYPE FieldData = {};
			ANYTYPE item;
			LIST OF ANYTYPE result;
			LIST OF STRING allfields = GetAllFieldsOfObject();
			for each item in allfields
			{
				ListAppend(FieldData,this.@(item));
			}
			OBJECT TheFile = cOPENFILE();
			TheFile.AssignFileName(FileToUse);
			TheFile.WriteValue(result);
		
		}
		VOID				DebugPrint(BOOLEAN fOverride null optional)
		{
			LIST OF CALL lcCall = GetCallStack();
			ListDelete(lcCall,1);
			STRING sCallString = "Occurred in {lcCall[1].sFunction} at {lcCall[1].sModule}({lcCall[1].iLine})";
			this.__DebugPrintEntry(fOverride, sCallString);
		
		}
		property DebugPrint_Enable
		{
			BOOLEAN Get()
			{
				if __fDebugPrintEnable == NULL
				{
					__fDebugPrintEnable = cSTATIC('fDebugPrintEnable');
				}
				if __fDebugPrintEnable.Value == NULL
				{
					__fDebugPrintEnable.Value = TRUE;
				}
				return __fDebugPrintEnable.Value;
			}
			VOID Set(BOOLEAN fNewValue)
			{
				if __fDebugPrintEnable == NULL
				{
					__fDebugPrintEnable = cSTATIC('fDebugPrintEnable');
				}
				__fDebugPrintEnable.Value = fNewValue;
			}
		}
		property DebugPrint_PropertiesToPublish
		{
			LIST OF STRING Get()
			{
				if this.__DebugPrint_PropertiesToPublish==NULL
				{
					OBJECT Result = cLIST();
					
					Result.Merge(this.GetAllPropertiesOfObject());
					Result.Append(__GatherInheretedLists({"__lsPrivateClassPropertyList","__lsPrivateInstancePropertyList"}));
					
					this.__DebugPrint_PropertiesToPublish=Result.d;
				
				}
				return this.__DebugPrint_PropertiesToPublish;
				
			}
			VOID Set(LIST OF STRING lsNewFields)
			{
				this.__DebugPrint_FieldsToPublish=lsNewFields;
			}
		}
		property DebugPrint_FieldsToPublish
		{
			LIST OF STRING Get()
			{
				if this.__DebugPrint_FieldsToPublish==NULL
				{
					OBJECT Result = cLIST();
					
					Result.Merge(this.GetAllFieldsOfObject());
					Result.Append(__GatherInheretedLists({"__lsPrivateClassFieldList","__lsPrivateInstanceFieldList"}));
					
					this.__DebugPrint_FieldsToPublish=Result.d;
				
				}
				return this.__DebugPrint_FieldsToPublish;
				
			}
			VOID Set(LIST OF STRING lsNewFields)
			{
				this.__DebugPrint_FieldsToPublish=lsNewFields;
		
			}
		}
		INTEGER __kawaga=1;
		
		const dcInheritsFrom 	  = NULL;
		const lsClassFieldList    = 
		{
			'dcInheritsFrom',
			"lsClassFieldList",
			"lsClassPropertyList",
			"lsInstanceFieldList",
			"lsInstancePropertyList"
		};
		const lsClassPropertyList = 
		{
			'Class',
			'sRawName',
			'sName',
			'loChildren',
			'lsChildrenNames',
			'oParent',
			'sClass',
			'sParent',
			'wParent',
			'sParentClass',
			'sPassedValue',
			'sRawPassedValue',
			'ldInheritsFrom',
			'sID',
			'sLongID',
			'fDebugPrintEnable',
			'fPrivateDebugPrintEnable',
			'DebugPrintLogFile'
		};
		const lsInstanceFieldList    = {};
		const lsInstancePropertyList = {};
		
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const 		__lsPrivateClassFieldList    = 
			{
			};
			const 		__lsPrivateClassPropertyList = {};
			const 		__lsPrivateInstanceFieldList    = {};
			const 		__lsPrivateInstancePropertyList = {};
			
			const 		__lsListOfThingsToSkip = {'ldInheritsFrom','__fDebugPrintEnable','__DebugPrintLogFile'};
			ANYTYPE 	__fDebugPrintEnable = NULL;
			
			// This method is marked private, because it's intended for unit testing. Returns a 
			// blank object of this type.
			OBJECT		__UnitTest_ObjGen()
			{
				OBJECT Result=@(this.sClass)();
				return Result;
			
			}
			ANYTYPE 	__GatherInheretedLists(LIST OF STRING lsVarNames)
			{
				OBJECT Result = cTEXT();
				
				LIST OF DATACLASS InheritanceLine = this.GetAllClassesThisInheritsFrom();
				
				ANYTYPE CurrentClass, CurrentFieldList;
				
				for each CurrentClass in InheritanceLine
				{
					
					ANYTYPE a = @('{CurrentClass}')();
					
					for each CurrentFieldList in lsVarNames
					{
						
						LIST l = a.@(CurrentFieldList);
						
						if (l != {}) && (l != {''})
						{
							Result.Append(l);
				
						}
					}
				}
				Result.Append(this.lsInstanceFieldList);
				
				return Result.d;
				
			
			}
			STRING  	__sUserSpecifiedName = NULL;
			ANYTYPE 	__DebugPrint_FieldsToPublish = NULL;
			ANYTYPE 	__DebugPrint_PropertiesToPublish = NULL;
			
			VOID		__DebugPrint(ANYTYPE foo NULL optional)
			{
				OBJECT PropertyList=cLIST().CreateWith(this.DebugPrint_PropertiesToPublish);
				OBJECT FieldList=cLIST().CreateWith(this.DebugPrint_FieldsToPublish);
				
				ANYTYPE item, itemdata;
				
				Log.ResOpenList("DebugPrint of {this.sName}");
				
				Log.Print("PROPERTIES:");
				for each item in PropertyList.d
				{
					
					do 
					{
						itemdata="DebugPrint() could not get this value";
						itemdata=this.@(item);
					}
					except
					{
						// nada
						ExceptClear();
					
					}
					Log.Print("  {this.__FormatLogLine(item,itemdata)}");
					
				
				}
				Log.Print("FIELDS:");
				for each item in FieldList.d
				{
					
					do 
					{
						itemdata="DebugPrint() could not get this value";
						itemdata=this.@(item);
					}
					except
					{
						// nada
						ExceptClear();
					
					}
					Log.Print("  {this.__FormatLogLine(item,itemdata)}");
					
				
				}
			}
			STRING		__FormatLogLine(STRING sItem1, STRING sItem2 optional)
			{
				STRING sFormatted = sItem1;
				if sItem2 != NULL
				{
					sFormatted = substr(sItem1+space(30),1,30)+sItem2;
				}
				return sFormatted;
			
			// OLDER CODE
				// STRING 	__sSingular
				// STRING 	__sPlural
				// BOOLEAN	__LocalDebugPrintEnable = TRUE
				// ANYTYPE __DebugPrintLogFile = NULL
				// 
				// property __fPrivateDebugPrintEnable
				{
					// BOOLEAN Get()
					{
						// if __fDebugPrintEnable == NULL
						{
							// __fDebugPrintEnable = cSTATIC('fPrivateDebugPrintEnable')
						// if __fDebugPrintEnable.Value == NULL
							// __fDebugPrintEnable.Value = FALSE
						// return __fDebugPrintEnable.Value
					// VOID Set(BOOLEAN fNewValue)
						// if __fDebugPrintEnable == NULL
							// __fDebugPrintEnable = cSTATIC('fPrivateDebugPrintEnable')
						// __fDebugPrintEnable.Value = fNewValue
				// property __DebugGetAllFieldsOfObject
					// ANYTYPE Get()
						// return this.GetAllFieldsOfObject()
				// property __DebugGetAllPropertiesOfObject
					// ANYTYPE Get()
						// return this.GetAllPropertiesOfObject()
				// 
				// INTEGER __iScanDepth = 0
				// const __iMaxScanDepth = 20
				// 
				// 
				// private VOID	__DoPrintLine(STRING sFormattedLine null optional, STRING sForLog optional)
					// if sFormattedLine != NULL
						// Log.print(sFormattedLine)
					// //if DebugPrintLogFile != NULL
						// STRING temp
						// if sForLog != NULL
							// temp = sForLog
						// else
							// temp = sFormattedLine
						// //if DebugPrintLogFile != NULL
							// //DebugPrintLogFile.Append(temp)
				// 
				// 
				// private VOID	__DoPrintItem(STRING sLine, ANYTYPE AdditionalData optional)
					// if AdditionalData == NULL
						// __DoPrintLine(sLine)
					// else
						// if ! (Contains(this.__lsListOfThingsToSkip,sLine))
							// if __iScanDepth < __iMaxScanDepth
							{
								// ANYTYPE item
								// select
								{
									// case IsVarList(AdditionalData)
									{
										// //__DoPrintLine(sLine)
										// Log.ResOpenList(sLine)
										// __iScanDepth++
										// for each item in AdditionalData
										{
											// __DoPrintLine(item,__FormatLogLine('>','{item}'))
										// Log.ResCloseList()
										// __iScanDepth--
										// 
									// case IsVarObject(AdditionalData)
										// STRING ResFileLine = __FormatLogLine(sLine,'{this}')
										// STRING LogFileLine = __FormatLogLine(sLine,'SubItem {AdditionalData.Class}.{AdditionalData.sName}------------------------------------')
										// __DoPrintLine(NULL,LogFileLine)
										// 
										// Log.ResOpenList(ResFileLine)
										// __iScanDepth++	
										// 
										// AdditionalData.DebugPrint(__LocalDebugPrintEnable)
										// Log.ResCloseList()
										// __iScanDepth--
										// 
										// __DoPrintLine('SubItem {AdditionalData.Class}.{AdditionalData.sName} Complete---------------------------')
										// 
									// default
										// __DoPrintLine(__FormatLogLine(sLine,'{AdditionalData}'))
						// 
						// 
				// 
				// private VOID 	__DebugPrintPart(LIST OF STRING lsAccessList)
					// this.__DoPrintItem('Debug Print of all {this.__sPlural} in {this.Class}.{this.sName}')
					// this.__DoPrintItem(__FormatLogLine('Name','Value'))
					// //this.__DoPrintItem('>{lsAccessList}')
					// 
					// STRING item
					// for each item in lsAccessList
						// //Log.print('>{item}')
						// do
							// STRING  sCurrentThingyName = item
							// ANYTYPE aCurrentThingyContent = this.@(item)
							// 
							// // some exceptions which can cause the thing to loop endlessly if not intercepted
							// if sCurrentThingyName == 'oParent'
								// do
									// aCurrentThingyContent = oParent.sName
								// except
									// aCurrentThingyContent = "(This object has no discernable parent)"
							// if sCurrentThingyName == 'loChildren'
								// aCurrentThingyContent = lsChildrenNames
								// if aCurrentThingyContent == {}
									// aCurrentThingyContent = "(This object has no discernable children)"
							// if sCurrentThingyName == 'DebugPrintLogFile'
								// aCurrentThingyContent = 'DebugPrintLogFile (object)'
							// if sCurrentThingyName == ''
								// aCurrentThingyContent = 'NULL'
							// this.__DoPrintItem(__FormatLogLine(sCurrentThingyName),'{aCurrentThingyContent}')
						// except
							// this.__DoPrintItem(__FormatLogLine(sCurrentThingyName,">>>DEBUGPRINT FAILED TO GET VALUE: {ExceptData()}"))
				// 
				// private VOID	__DebugPrintEntry(BOOLEAN fOverride null optional, STRING sCallString optional)
					// __LocalDebugPrintEnable = this.fDebugPrintEnable
					// if fOverride != NULL
						// __LocalDebugPrintEnable = fOverride
					// if __LocalDebugPrintEnable
						// 
						// Log.ResOpenList('DebugPrint of {this.Class}.{this.sName}')
						// __iScanDepth++
						// if __iScanDepth < __iMaxScanDepth
							// if sCallString != NULL
								// LIST OF CALL lcCall = GetCallStack()
								// CALL Call
								// ListDelete(lcCall,1)
								// ListDelete(lcCall,1)
								// for each Call in lcCall
									// this.__DoPrintItem ("Occurred in {Call.sFunction} at {Call.sModule}({Call.iLine})")
								// 
							// this.__DoPrintItem('=======================================================================')
							// this.__sSingular = 'property'
							// this.__sPlural = 'properties'
							// this.__DebugPrintPart(this.GetAllPropertiesOfObject())
							// this.__DoPrintItem('=======================================================================')
							// this.__sSingular = 'field'
							// this.__sPlural = 'fields'
							// this.__DebugPrintPart(this.GetAllFieldsOfObject())
							// this.__DoPrintItem('=======================================================================')
						// Log.ResCloseList()
						// __iScanDepth--
						// 
				
				//INTEGER __iMyID = __iObjectIDCarrier++
				// INTEGER __iMyID = 0 // __AppendObjectToMasterList(this) // CONSTRCUTOR
				// STRING __MyIDVariable="sPassedValue"
				
				// property fPrivateDebugPrintEnable
					// ANYTYPE Get()
						// return this.__fPrivateDebugPrintEnable
					// SET(BOOLEAN f)
						// this.__fPrivateDebugPrintEnable = f
				// property 			sID
					// STRING Get()
						// return GetID()
				// property 			sLongID
					// STRING Get()
						// return GetLongID()
					// STRING Get()
						// return WindowName (this)
				// STRING 				GetID()
					// return "ID"+right('00000000{__iMyID}',8)
				// STRING 				GetLongID()
					// STRING sWorkingName = this.sRawName
					// if sContains(sRawName,'("')
						// sWorkingName=""
					// if __sUserSpecifiedName != ""
						// sWorkingName = __sUserSpecifiedName
					// STRING sResult='{GetID()}:{sWorkingName}:{Class}("{@(__MyIDVariable)}")'
					// return sResult
				// property DebugPrint_LogFile
					// OBJECT Get()
						// if __DebugPrintLogFile == NULL
							// __DebugPrintLogFile = cSTATIC('DebugPrintLogFile')
						// return __DebugPrintLogFile.Value
					// VOID Set(FILEREF NewFileRef null optional)
						// if __DebugPrintLogFile == NULL
							// __DebugPrintLogFile = cSTATIC('DebugPrintLogFile')
						// 
						// if NewFileRef != NULL
							// OBJECT TheFile = cOPENFILE()
							// TheFile.AssignFileName(NewFileRef)
							// 
							// if __DebugPrintLogFile.Value == NULL
								// __DebugPrintLogFile.Value = TheFile
							// 
							// // now check to see if we've been passed a file which is different from what's already stored
							// if __DebugPrintLogFile.Value.sFileName != TheFile.sFileName
								// __DebugPrintLogFile.Value.Close()
								// __DebugPrintLogFile.Value = TheFile
						// 
		////////////////////////////////////////////////////////////////////////////
		// INTERNAL UNIT TESTS
			
										}
									}
								}
							}
						}
					}
				}
			}
			STRING __TEST_GetFullMethodName() 
			{
				return this.GetFullMethodName();
		////////////////////////////////////////////////////////////////////////////
		
	
			}
		}
	}
	private WINDOW cBASE ExtensionLibrary_SelfTestSuite_Objects_cBASE_GlobalInstance
	{
		tag "global";
		cBASE item1
		{
			tag "woo hoo1";
		}
		cBASE item2
		{
			tag "woo hoo2";
		}
	}
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cBASE()
	{
		WINDOW GI = ExtensionLibrary_SelfTestSuite_Objects_cBASE_GlobalInstance;
		WINDOW LI = cBASE("local");
		__DoTest("global cBASE.Class",GI.Class,cBASE);
		__DoTest("global cBASE.sName",GI.sName,"{GI}");
		__DoTest("local  cBASE.sName",LI.sName,'cBASE ("local")');
		__DoTest("global cBASE.loChildren",GI.loChildren,{GI.item1, GI.item2});
		__DoTest("local  cBASE.loChildren",LI.loChildren,{});
		__DoTest("global cBASE.oParent",GI.oParent,NULL);
		__DoTest("global cBASE.subitem.oParent",GI.item1.oParent,GI);
		__DoTest("global cBASE.sClass",GI.sClass,'cBASE');
		__DoTest("global cBASE.sParent",GI.sParent,'');
		__DoTest("global cBASE.subitem.sParent",GI.item1.sParent,'{GI}');
		__DoTest("global cBASE.sParentClass",GI.sParentClass,'');
		__DoTest("global cBASE.subitem.sParentClass",GI.item1.sParentClass,'cBASE');
		__DoTest("global cBASE.sPassedValue",GI.sPassedValue,'global');
		__DoTest("local  cBASE.sPassedValue",LI.sPassedValue,'local');
		__DoTest("global cBASE.sRawPassedValue",GI.sRawPassedValue,'/global');
		__DoTest("local  cBASE.sRawPassedValue",LI.sRawPassedValue,'/local');
		
		__DoTest("global cBASE.GetName()",GI.GetName(),"{GI}");
		__DoTest("local  cBASE.GetName()",LI.GetName(),'cBASE ("local")');
		__DoTest("global cBASE.GetParent()",GI.GetParent(),NULL);
		__DoTest("global cBASE.subitem.GetParent()",GI.item1.GetParent(),GI);
		
		__DoTest("global cBASE.IsDefined('item1')",GI.IsDefined('item1'),TRUE);
		__DoTest("global cBASE.IsDefined('item3')",GI.IsDefined('item3'),FALSE);
		
		__DoTest("cBASE cFILE.IsOfClass(cBASE)",cFILE().IsOfClass(cBASE),TRUE);
		__DoTest("cBASE.IsOfClass(cFILE)",cBASE().IsOfClass(cFILE),FALSE);
		
		__DoTest("cBASE.GetAllClassesThisInheritsFrom()",cBASE().GetAllClassesThisInheritsFrom(),{cBASE});
		__DoTest("cBASE cFILE.GetAllClassesThisInheritsFrom()",cFILE().GetAllClassesThisInheritsFrom(),{cFILE, cDISKENTITY, cBASE});
		__DoTest("cBASE cFILE.ldInheritsFrom",cFILE().ldInheritsFrom,{cFILE, cDISKENTITY, cBASE});
		__DoTest("cBASE cFILE.GetAllPropertiesOfObject()","{cFILE().GetAllPropertiesOfObject()}",""{bExists, fUseRawName, sMungedName, sDrivePart, sDirectoryPart, sNamePart, sExtensionPart, bIsDir, iSize, dtCreated, dtModified, bReadOnly, bHidden, bSystem, bArchive, Class, sRawName, sName, loChildren, lsChildrenNames, oParent, sClass, sParent, wParent, sParentClass, sPassedValue, sRawPassedValue, ldInheritsFrom, sID, sLongID, fDebugPrintEnable, fPrivateDebugPrintEnable, DebugPrintLogFile}");
	
	
	////////////////////////////////////////////////////////////////////////////
	// cTIMER 			Timer object
	//
	// Purpose: 		Encapsulates Timer functionality
	//
	// Expand this for documentation
		//
		// inherits: 		cBASE
		//
		// PUBLIC MEMBERS - METHODS:
		//
		//		HotStart ()			Creates timer, starts it, and returns this.
		//							See notes for usage.
		// 		HotStop ()			Stops timer, returns real of elapsed time
		// 		Start ()			Starts timer
		// 		Stop ()				Stops timer (can't resume)
		// 		Pause ()			Pauses timer
		// 		Resume ()			Resume's timer
		// 		Reset ()			Reset timer (halts, resets values to zero)
		// 		Destroy ()			Destorys timer handle
		// 		PrintTime ()		Print's elapsed time to resfile
		// 		ObjectLatency ()	Returns amount of time spent starting and
		//							stopping timer. See notes.
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		// 		rElapsedTime		REAL of actual elapsed time
		// 		sElapsedTime		STRING of actual elapsed time
		// 		rObjectLatency		REAL of time spent starting and stopping
		//							the timer
		//
		//
		// PUBLIC MEMBERS - DATA:
		//
		// 		STRING sStartTime	When timer was started or "NOT STOPPED YET"
		// 		STRING sStopTime	When timer was stopped or "NOT STOPPED YET"
		//
		// NOTES: When timer is running, has been stopped or is paused, the
		// value in rElapsedTime and sElapsedTime reflects the time that
		// the timer was running for.
		//
		// rObjectLatency refers to the amount of time the timer object
		// will record if started and immediatly stopped. This value can then
		// be subtracted from reported results. WARNING! Running the ObjectLatency()
		// function causes the current timer to be destroyed. Run this FIRST before
		// timing an operation.
		//
		// All functions which return elapsed time return recorded time less latency
		//
		// Typical usage:
		//		OBJECT TheTimer = cTIMER().HotStart()
		//		// do things here
		//		print( TheTimer.HotStop() )
		//
	////////////////////////////////////////////////////////////////////////////
	}
	winclass cTIMER : cBASE
	{
		
		property rElapsedTime
		{
			REAL Get ()
			{
				return this.__rRawElapsedTime - this.rObjectLatency;
			}
		}
		property sElapsedTime
		{
			STRING Get ()
			{
				return "{this.rElapsedTime}";
				
			}
		}
		property rObjectLatency // THIS IS USED BY THE SYSTEM OBJECT
		{
			REAL Get ()
			{
				return this.ObjectLatency ();
			}
			VOID Set(NUMBER n)
			{
				__PersistantLatency.SetValueAtClass(n,cTIMER);
			}
		}
		property Status
		{
			STRING Get()
			{
				STRING sResult;
				
				switch this.__TimerState
				{
					case TS_STARTED:
						sResult="TS_STARTED";
					case TS_STOPPED:
						sResult="TS_STOPPED";
					case TS_PAUSED:
						sResult="TS_PAUSED";
					default:
					{
						sResult="TS_NOTSTARTED";
				
					}
				}
				return sResult;
		
			}
		}
		OBJECT 	HotStart ()
		{
			this.start ();
			return this;
			
		}
		REAL 	HotStop ()
		{
			REAL temp = this.rElapsedTime;
			this.Destroy ();
			return temp;
			
			// FUNCTIONS FOR OPERATING THE TIMER
		}
		VOID 	Start ()
		{
			this.__Start();
		}
		REAL 	Stop ()
		{
			this.__Stop();
			return this.rElapsedTime;
		}
		REAL 	Pause ()
		{
			this.__Pause();
			return this.rElapsedTime;
		}
		REAL 	Resume ()
		{
			this.__Resume();
			return this.rElapsedTime;
		}
		REAL 	Reset ()
		{
			return this.Destroy ();
			
			
			// VALUES MAINTAINED BY THE TIMER
		}
		REAL 	Destroy ()
		{
			REAL result = 0;
			
			if this._____InternalTimerHandle != NULL
			{
				
				if this.__TimerState != TS_STOPPED
				{
					this.Stop ();
				}
				TimerDestroy (this.__TimerHandle);
				this._____InternalTimerHandle = NULL;
				this.sStartTime = "NOT STARTED YET";
				this.sStopTime = "NOT STOPPED YET";
				result = rElapsedTime;
			
			}
			return result;
			
		}
		VOID	PrintTime ()
		{
			print ("{this.__sName}.sElapsedTime = {this.sElapsedTime}");
		}
		REAL 	ObjectLatency ()
		{
			REAL rResult = __PersistantLatency.Value;
			
			if ! __DoingInitialCalc
			{
				if rResult == NULL
				{
					
					LIST OF REAL lrResults;
					INTEGER l;
					ANYTYPE item;
					REAL total = 0, average;
					__DoingInitialCalc = TRUE;
					
					for l = 1 to 200
					{
						Reset ();
						Start ();
						Stop ();
						listappend (lrResults, this.__rRawElapsedTime);
						Destroy ();
						
					}
					for each item in lrResults
					{
						total = total + item;
						
					}
					average = total / listcount (lrResults);
					
					__PersistantLatency.SetValueAtClass(average,cTIMER);
					__DoingInitialCalc = FALSE;
					rResult = average;
				}
			}
			else
			{
				rResult = 0;
			}
			return rResult;
			
		}
		VOID	Flip()
		{
			if this.Status == "TS_STARTED"
			{
				this.Pause();
			}
			if this.Status == "TS_STOPPED"
			{
				this.Resume();
			}
			if this.Status == "TS_PAUSED"
			{
				this.Resume();
			}
			if this.Status == "TS_NOTSTARTED"
			{
				this.Resume();
			
		
		
			}
		}
		STRING sStartTime = "NOT STARTED YET";
		STRING sStopTime = "NOT STOPPED YET";
		
		const dcInheritsFrom = cBASE;
		const lsClassFieldList    = {'sStartTime','sStopTime'};
		const lsClassPropertyList = {'rElapsedTime','sElapsedTime','rObjectLatency'};
		
		////////////////////////////////////////////////////////////////////////////
		// = PRIVATE MEMBERS! DO NOT USE! PRIVATE MEMBERS! DO NOT USE! =
		{
			
			const lsPrivateClassFieldList    = {'__PersistantLatency','_____InternalTimerHandle','__DoingInitialCalc'};
			const lsPrivateClassPropertyList = {'__rRawElapsedTime','__TimerHandle','__TimerState'};
			
			builtin STRING GetID ();
			
			cSTATIC		__PersistantLatency {}
			HANDLE 		_____InternalTimerHandle = NULL;
			BOOLEAN 	__DoingInitialCalc = FALSE;
			
			private property 	__rRawElapsedTime
			{
				REAL Get ()
				{
					return TimerValue (this.__TimerHandle);
					
				}
			}
			private property 	__TimerHandle
			{
				HTIMER Get ()
				{
					if this._____InternalTimerHandle == NULL
					{
						this._____InternalTimerHandle = TimerCreate ();
					}
					return this._____InternalTimerHandle;
					
				}
			}
			private property 	__TimerState
			{
				INTEGER Get ()
				{
					INTEGER i = 0;
					if this._____InternalTimerHandle != NULL
					{
						i = TimerState (this.__TimerHandle);
					}
					return i;
			
				}
			}
			VOID __Start()
			{
				switch this.__TimerState
				{
					case TS_STARTED:
						// do nothing
					case TS_STOPPED:
						__DoStart();
					case TS_PAUSED:
						__DoResume();
					default:
					{
						__DoStart();
					}
				}
			}
			VOID __Stop()
			{
				switch this.__TimerState
				{
					case TS_STARTED:
						__DoStop();
					case TS_STOPPED:
						// do nothing
					case TS_PAUSED:
						__DoStop();
					default:
					{
						__DoStop();
					}
				}
			}
			VOID __Pause()
			{
				switch this.__TimerState
				{
					case TS_STARTED:
						__DoPause();
					case TS_STOPPED:
						Log.LogWarning("cTIMER asked to pause a timer that wasn't started");
					case TS_PAUSED:
						// do nothing
					default:
					{
						// default case is always not started
					}
				}
			}
			VOID __Resume()
			{
				switch this.__TimerState
				{
					case TS_STARTED:
						// do nothing, already running
					case TS_STOPPED:
						__DoStart();
					case TS_PAUSED:
						__DoResume();
					default:
					{
						__DoStart();
				
			
			
			// private REAL 		__DoAction (STRING sCaller, STRING sStart, STRING sStopped, STRING sPaused)
				// switch this.__TimerState
					// case TS_STARTED
						// if sStart[1] == "_"
						{
							// @(sStart) ()
						// else
							// this.__DoRaise (sCaller)
					// case TS_STOPPED
						// if sStopped[1] == "_"
							// @(sStopped) ()
						// else
							// this.__DoRaise (sCaller)
					// case TS_PAUSED
						// if sPaused[1] == "_"
							// @(sPaused) ()
						// else
							// this.__DoRaise (sCaller)
				// return rElapsedTime
				
						}
					}
				}
			}
			private VOID		__DoRaise (STRING sCaller)
			{
				raise LIBERROR_TIMER_FAILURE, "*** Error: LIBERROR_TIMER_FAILURE in {this.sName}.{sCaller}() state is {this.Status}";
				
			}
			private VOID		__DoSTart ()
			{
				if ! __DoingInitialCalc
				{
					ObjectLatency ();
				}
				sStartTime = TimeStr ();
				TimerStart (this.__TimerHandle);
			}
			private VOID		__DoStop ()
			{
				TimerStop (this.__TimerHandle);
				sStopTime = TimeStr ();
			}
			private VOID		__DoPause ()
			{
				TimerPause (this.__TimerHandle);
			}
			private VOID		__DoResume ()
			{
				TimerResume (this.__TimerHandle);
			
		////////////////////////////////////////////////////////////////////////////
		
			}
		}
	}
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cTIMER()
	{
		OBJECT timer = cTIMER().HotStart();
		OBJECT temp = cTEXTFILE('4class4.inc');
		timer.HotStop();
		__DoTest('cTIIMER Basic stop & start',TRUE,TRUE);
	
	

// Expand for Abstract Object Library - Data classes 				(cDATA, cSTATIC, cSTRING, cLIST, cSEARCHABLELIST, cTEXT, cDATE)
	
	
	////////////////////////////////////////////////////////////////////////////
	// cDATA			Base class for object representations of basic 
	//					data types, such as STRING, LIST
	////////////////////////////////////////////////////////////////////////////
	}
	winclass cDATA : cBASE
	{
		ANYTYPE d = NULL;
	
	
	////////////////////////////////////////////////////////////////////////////
	// cSTATIC		Static storage
	//
	// Purpose:		Manages persistant data (not file based data)
	// 				That is, data required to be shared between instances
	// 				of a class that may not coexist temporally.
	//
	// Expand this for documentation
		//
		// inherits: 	cBASE
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		// 		Value			rw: Stores and retrieves the value from the shared
		//						pool of data. When you instantiate the class, you must
		//						either do it dynamically, or specify a tag. The name
		//						provided at instantiation as the tag is the search key
		//						for the data. Returns NULL if value is unset.
		//		LocalValue		ro: Retrieves or stores a value at the level of the
		//						container class, instead of at whatever level it's
		//						defined. You can use this to override an inherited
		//						value that may no longer be relevent.
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		//		SetValueAtClass(a,dc)	Sets value at a specific class level.
		//
		// NOTES:
		//
		// This is intended to be used as a member inside another object. This is
		// because one of the keys it generates for locating it's data is based
		// on the class of container that the cSTATIC is within.
		//
		// winclass cFOO : cBASE
		//		cSTATIC SharedData
		//
		//		VOID foo()
		//			SharedData.Value = 'hi!'
		//		VOID foo2()
		//			print(SharedData.Value)
		//
	////////////////////////////////////////////////////////////////////////////
	}
	winclass cSTATIC : cDATA
	{
		
		tag "StaticClassDefault";
		
		property d
		{
			ANYTYPE Get()
			{
				return this.Value;
			}
		}
		property Value
		{
			ANYTYPE Get ()
			{
				return this.__GetValue(TRUE);
			}
			VOID Set (ANYTYPE aValue)
			{
				this.__SetValue(aValue);
			}
		}
		property LocalValue
		{
			ANYTYPE Get ()
			{
				return this.__GetValueAtThisLevel();
			}
			VOID Set (ANYTYPE aValue)
			{
				this.__SetValueAtThisLevel(aValue);
			
		
			}
		}
		ANYTYPE  SetValueAtClass(ANYTYPE NewValue, DATACLASS dcClassID)
		{
			return this.__SetValue(NewValue, dcClassID);
		
		}
		const dcInheritsFrom      = cDATA;
		const lsClassFieldList    = {};
		const lsClassPropertyList = {'Value','LocalValue'};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {'__LastFoundClass'};
			const lsPrivateClassPropertyList = {};
			
			DATACLASS 	__LastFoundClass = NULL;
			
			private LIST 		__GetKeys(BOOLEAN fSearch, DATACLASS dcClassID null optional)
			{
				STRING sKey = this.sRawName;						// name of the object
				if right(this.sPassedValue,18) != "StaticClassDefault"
				{
					sKey = this.sPassedValue;					  // Can be overridden by sPassedValue
				
				}
				DATACLASS ClassToKeyOffOf;
				do
				{
					ClassToKeyOffOf = this.oParent.Class;		// By default, use the current parent's class
				}
				except
				{
					ClassToKeyOffOf = NULL;
					ExceptClear();
				
				}
				do												// now, we search
				{
					if ClassToKeyOffOf != NULL
					{
						LIST OF DATACLASS ldInheritanceList = this.oParent.GetAllClassesThisInheritsFrom();
						ANYTYPE aTest;
						DATACLASS item;
						for each item in ldInheritanceList
						{
							aTest = STATIC_Get ('{item}', sKey);
							if aTest != NULL
							{
								this.__LastFoundClass = item;
								break;
							}
						}
					}
				}
				except
				{
					// do nothing - this exception doesn't need to be trapped, the next peice of code
					// checks the result of this action.
					ExceptClear();
				
				}
				do
				{
					if this.__LastFoundClass != NULL				// if __LastFoundClass is set, replace at that level
					{
						ClassToKeyOffOf = this.__LastFoundClass;
					}
				}
				except
				{
					this.__LastFoundClass = this.Class;
					ClassToKeyOffOf = this.Class;
					ExceptClear();
				
				}
				if dcClassID != NULL							// on the other hand, if a class was specified
				{
					ClassToKeyOffOf = dcClassID;					  // use THAT class
				
				}
				STRING sClassToUse;
				if ClassToKeyOffOf != NULL
				{
					if ! this.oParent.IsOfClass(ClassToKeyOffOf)	// now make sure we SHOULD have access
					{
						raise LIBERROR_PROTECTION_FAULT_ON_STATIC, "*** Error: LIBERROR_PROTECTION_FAULT_ON_STATIC Can't get STATIC for {ClassToKeyOffOf} as it's not an ancestor of {this.oParent.Class}";
					}
					sClassToUse = '{ClassToKeyOffOf}';
				}
				else
				{
					sClassToUse = 'UNKNOWN';
				
				}
				if Right(sKey,5)==' ("")'
				{
					sKey = GetLeftOf(sKey,' ("")');
				
				}
				return {sClassToUse,'{sKey}'};					// and hand back the keys
				
			}
			private ANYTYPE 	__GetValue(BOOLEAN fSearch)
			{
				ANYTYPE result = NULL;
				do
				{
					LIST Keys = this.__GetKeys(fSearch);
					result = STATIC_Get(Keys[1], Keys[2]);
				}
				except
				{
					// do nothing, return null
					ExceptClear();
				}
				return result;
			}
			private ANYTYPE 	__SetValue(ANYTYPE NewValue, DATACLASS dcClassID optional)
			{
				LIST Keys = this.__GetKeys(TRUE, dcClassID);
				STATIC_Set(Keys[1], Keys[2], NewValue);
				return this.__GetValue(TRUE);
			}
			private ANYTYPE 	__SetValueAtThisLevel(ANYTYPE NewValue)
			{
				return this.__SetValue(NewValue, this.oParent.Class);
			}
			private ANYTYPE		__GetValueAtThisLevel()
			{
				LIST Keys = this.__GetKeys(FALSE);
				return STATIC_Get(this.oParent.sClass, Keys[2]);
				
			
		////////////////////////////////////////////////////////////////////////////
		
			}
		}
	}
	INTEGER __iActionCounter=0;
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cSTATIC()
	{
		WINDOW phred = cSTATIC('hi');
		phred.Value = "good";
		__DoTest("cSTATIC",phred.Value,"good");
		OBJECT c1 = cDISKENTITY();
		OBJECT c2 = cFILE();
		__DoTest("cSTATIC 2",c1.fUseRawName,FALSE);
		BOOLEAN fUseRawNameTemp = c1.fUseRawName;
		c1.fUseRawName = TRUE;
		__DoTest("cSTATIC 3",c2.fUseRawName,TRUE);
		c1.fUseRawName = fUseRawNameTemp;
	
	}
	winclass cSTATICLIST : cSTATIC
	{
		
		VOID Register(OBJECT item)
		{
			ANYTYPE temp = this.Value;
			if temp == NULL
			{
				temp = {};
			}
			ListAppend(temp,item);
			this.Value = temp;
		
		}
		const dcInheritsFrom      = cSTATIC;
		const lsClassFieldList    = {};
		const lsClassPropertyList = {};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {};
			const lsPrivateClassPropertyList = {};
			
		////////////////////////////////////////////////////////////////////////////
		
	
	
	////////////////////////////////////////////////////////////////////////////
	// cSTRING			Basic string class
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass cSTRING : cDATA
	{
		STRING   	d = NULL;
		property 	iLength
		{
			INTEGER Get()
			{
				INTEGER iResult=0;
				if this.d != NULL
				{
					iResult=Len(this.d);
					
				}
				return iResult;
		
			}
		}
		INTEGER  	i; // index
		property 	c // char at [i]
		{
			STRING Get()
			{
				return this.Index(this.i);
			}
			VOID Set(STRING sIn)
			{
				this.d[this.GetRealIndex(this.i)]=sIn;
		
			}
		}
		STRING   	Index(INTEGER iNew)
		{
			return this.d[this.GetRealIndex(iNew)];
		}
		INTEGER  	GetRealIndex(INTEGER iNew)
		{
			if iNew < 0
			{
				iNew = (this.iLen + 1 + iNew);
			}
			return iNew;
		
		}
		VOID		Append(STRING sData)
		{
			this.d=this.d+sData;
		}
		STRING 		SubStr(INTEGER iNum, INTEGER iLen)
		{
			iNum=this.GetRealIndex(iNum);
			return ____SubStr(this.d,iNum,iLen);
		}
		STRING 		Right(INTEGER iNum)
		{
			return ____Right(this.d,iNum);
		}
		STRING 		Left(INTEGER iNum)
		{
			return ____Left(this.d, iNum);
		}
		INTEGER  	Find(STRING sSubStr)
		{
			return StrPos(this.d,sSubStr);
		}
		BOOLEAN  	Contains(STRING sSubStr)
		{
			return MakeBool(sContains(this.Upper(),____Upper(sSubStr)));
		}
		VOID		Insert(INTEGER iAt, STRING sIn)
		{
			this.d[iAt]=sIn+this.d[iAt];
		}
		STRING		StrTran(STRING sSearch, STRING sReplace)
		{
			 return ____StrTran(this.d,sSearch,sReplace);
		}
		STRING 		Lower()
		{
			return ____Lower(this.d);
		}
		STRING 		Upper()
		{
			return ____Upper(this.d);
		}
		STRING 		Trim()
		{
			return ____Trim(this.d);
		}
		STRING 		MakeLower()
		{
			this.d=this.Lower();
			return this.d;
		}
		STRING 		MakeUpper()
		{
			this.d=this.Upper();
			return this.d;
		}
		STRING 		MakeTrim()
		{
			this.d=this.Trim();
			return this.d;
		}
		STRING		MakeStrTran(STRING sSearch, STRING sReplace)
		{
			this.d=this.StrTran(sSearch, sReplace);
			return this.d;
		}
		OBJECT		CreateWith(STRING sValue)
		{
			this.d=sValue;
			return this;
		
		}
		BOOLEAN 	__ConstructorResult = this.__Constructor();
		BOOLEAN 	__Constructor()
		{
			if this.sPassedValue != ""
			{
				this.d=this.sPassedValue;
			}
			return (this.sPassedValue != "");
		
	
		}
	}
	STRING ____SubStr(STRING sIn, INTEGER iPos, INTEGER iLen)
	{
		return SubStr(sIn,iPos,iLen);
	}
	STRING ____Right(STRING sIn, INTEGER iLen)
	{
		return Right(sIn, iLen);
	}
	STRING ____Left(STRING sIn, INTEGER iLen)
	{
		return Left(sIn, iLen);
	}
	STRING ____StrTran(STRING sData, STRING sSearch, STRING sReplace)
	{
		return StrTran(sData,sSearch,sReplace);
	}
	STRING ____Lower(STRING d)
	{
		return Lower(d);
	}
	STRING ____Upper(STRING d)
	{
		return Upper(d);
	}
	STRING ____Trim(STRING d)
	{
		return Trim(d);
	
	////////////////////////////////////////////////////////////////////////////
	// cLIST			Basic list class
	//
	// Purpose:			Provides all list basics in one box
	//					And adds basic substring query
	//
	// Expand this for documentation
		//
		// inherits:		cBASE
		//
		// PUBLIC MEMBERS - DATA:
		//
		// 		LIST d				The data to use, in the form:
		//								foo.d = {...}
		//									{"Akien","WebFilter"},
		//									{"Igor","Server"},
		//									{"Jesun","API"},
		//									{"Phil","Install"}
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		// 		iSize				Number of records
		//
		// PUBLIC MEMBERS - METHODS:
		//
		//		Find(a)				Returns index of the item matching a
		//		Query(a)			Returns a list of indexes for all items containing a
		//		Append(a)			Appends a to the list
		//		Delete(i)			Deletes list entry i
		//		Insert(i,a)			Insert at position i the data of a
		//		Merge(a)			Merge the list a to this (list can be a list or a cLIST)
		//		Sort()				Sorts the list
		//		Push(a)				Inserts a into position 1
		//		Pop()				Returns and deletes the item in position 1
		//		Read(FILEREF)		Does a listread - FILEREF can be string or cFILE
		//		Write(FILEREF)		Does a listwrite
	//
	////////////////////////////////////////////////////////////////////////////
	}
	winclass cLIST : cDATA
	{
		
		LIST d = {}; // this is the raw data from the user
		
		property lData
		{
			ANYTYPE Get()
			{
				return this.d;
			}
			VOID Set(ANYTYPE incoming)
			{
				d=incoming;
			}
		}
		property iSize 
		{
			INTEGER Get()
			{
				INTEGER i=0;
				if d != NULL
				{
					i=ListCount(this.d);
				}
				return i;
			}
		}
		property iLength 
		{
			INTEGER Get()
			{
				INTEGER i=0;
				if d != NULL
				{
					i=ListCount(this.d);
				}
				return i;
		
			}
		}
		INTEGER Find(ANYTYPE incoming)
		{
			return ListFind(this.d,incoming);
		}
		LIST 	Query(ANYTYPE incoming)	// slow search
		{
			ANYTYPE i;
			OBJECT 	lResult=cLIST();
			for i=1 to this.iSize
			{
				if sContains("{this.d[i]}","{incoming}")
				{
					lResult.Append(i);
			
				}
			}
			return lResult.d;
		
		}
		VOID 	Append(ANYTYPE incoming NULL)
		{
			if this.d==NULL
			{
				this.d={};
			}
			ListAppend(this.d,incoming);
		}
		VOID	Prepend(ANYTYPE incoming NULL)
		{
			this.Insert(1,incoming);
		}
		ANYTYPE Delete(INTEGER i)
		{
			this.__FixIndex(i);
			ANYTYPE aFoundData = this.d[i];
			ListDelete(this.d,i);
			return aFoundData;
		}
		VOID 	Insert(INTEGER i, ANYTYPE incoming)
		{
			if this.d=={}
			{
				ListAppend(this.d,incoming);
			}
			else
			{
				ListInsert(this.d,i,incoming);
			
			}
		}
		VOID	Merge(ANYTYPE incoming, INTEGER iPos optional)
		{
			LIST lLocalData={};
			if IsVarObject(incoming)
			{
				lLocalData=incoming.d;
			}
			if IsVarList(incoming)
			{
				lLocalData=incoming;
			}
			if iPos==NULL
			{
				iPos=this.iSize;
			}
			if iPos==0
			{
				this.d=incoming;
			}
			else
			{
				ListMerge(this.d,incoming,iPos);
			}
		}
		VOID	Sort()
		{
			ListSort(this.d);
		
		}
		ANYTYPE Pop()
		{
			ANYTYPE Result=this.d[this.iLength];
			this.Delete(this.iLength);
			return Result;
		}
		VOID	Push(ANYTYPE incoming)
		{
			this.Append(incoming);
		
		}
		LIST	Read(FILEREF incoming)
		{
			incoming=MakeStringFromFILEREF(incoming);
			OBJECT Temp=cTEXTFILE(incoming);
			Temp.Read();
			this.d=Temp.lsData;
			return this.d;
		}
		VOID	Write(FILEREF incoming)
		{
			incoming=MakeStringFromFILEREF(incoming);
			OBJECT Temp=cTEXTFILE(incoming);
			Temp.lsData=this.d;
			Temp.Write();
		
		}
		OBJECT	CreateWith(LIST aData)
		{
			this.d=aData;
			return this;
		
		// Methods for cCELLSELECTOR
		}
		ANYTYPE cCS_GetData(OBJECT NewCellSelector) // returns INTEGER from Find() if row non integer, by row number if integer
		{
			ANYTYPE Result=NULL;
			if IsVarInteger(NewCellSelector.r)
			{
				Result=d[NewCellSelector.r];
			}
			else
			{
				Result=this.Find(NewCellSelector.r);
			}
			return Result;
		}
		VOID	cCS_SetData(OBJECT NewCellSelector, ANYTYPE aData)
		{
			INTEGER iLine=this.__ReturnLineFromUnknownData(NewCellSelector.r);
			this.d[iLine]=aData;
		}
		VOID	cCS_InsertRow(OBJECT NewCellSelector, ANYTYPE aData, INTEGER iNumericOverride optional)
		{
			INTEGER iLine=this.__ReturnLineFromUnknownData(NewCellSelector.r);
			if iNumericOverride != NULL
			{
				iLine=iNumericOverride;
			}
			if iLine < 0
			{
				this.Append(aData);
			}
			else
			{
				this.Insert(iLine,aData);
			}
		}
		VOID	cCS_DeleteRow(OBJECT NewCellSelector)
		{
			INTEGER iLine=this.__ReturnLineFromUnknownData(NewCellSelector.r);
			this.Delete(iLine);
		}
		INTEGER	__ReturnLineFromUnknownData(ANYTYPE aData)
		{
			INTEGER iLine=NULL;
			if ! IsVarInteger(aData)
			{
				iLine=this.Find(aData);
			}
			else
			{
				iLine=aData;
			}
			return iLine;
		}
		INTEGER __FixIndex(inout INTEGER i)
		{
			if i < 0
			{
				i = this.iLength + (i+1);
			}
			return i;
		
		}
		const dcInheritsFrom = cBASE;
		const lsClassFieldList={"d"};
		const lsClassPropertyList={"lData","iSize"};
		
		VOID 	__UnitTest()
		{
			
		
	
	////////////////////////////////////////////////////////////////////////////
	// cCELLSELECTOR	Used in conjunction with cLIST, cSEARCHABLELIST
	//
	// Purpose: 		Kind of a query object
	//
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass cCELLSELECTOR : cBASE
	{
		
		// Selectors. NOTE: Not all selectors are valid for all data objects
		// invlaid selectors will be ignored (e.g.: c&f are ignored in cLIST)
		ANYTYPE c=NULL;	// Column, used only in lists with columns
		ANYTYPE r=NULL;	// Row, used in all lists
		ANYTYPE f=NULL;	// Field, used for searchable lists
		
		// Attach is used to attach to a cLIST/cSEARCHABLELIST object. You can also specify
		// the c/r/f fields. If only 1 is provided, r is assumed. if 2 or more, then the
		// order of the fields is c,r,f. 
		// Attach returns this so it can be used like this: 
		// 		OBJECT foo=cCELLSELECTOR().Attach(MyList,"Name","Steve","Phone")
		OBJECT Attach(OBJECT Incoming, ANYTYPE aNew1 optional, ANYTYPE aNew2 optional, ANYTYPE aNew3 optional)
		{
			this.wParent=Incoming;
			if aNew1 != NULL
			{
				this.Select(aNew1,aNew2, aNew3);
			}
			return this;
		
		// Select applies the three arguments then returns the result from .d
		}
		ANYTYPE Select(ANYTYPE aNew1, ANYTYPE aNew2 NULL optional, ANYTYPE aNew3 NULL optional)
		{
			if aNew2 == NULL
			{
				this.r=aNew1;
			}
			else
			{
				this.c=aNew1;
				this.r=aNew2;
			}
			if aNew3 != NULL
			{
				this.f=aNew3;
			}
			return d;
		
		}
		property wParent
		{
			ANYTYPE Get()
			{
				ANYTYPE Try = NULL;
				if this.wParent != NULL
				{
					Try=this.wParent;
				}
				if this.__StoredParent != NULL
				{
					Try=this.__StoredParent;
				}
				return Try;
			}
			Set(WINDOW Incoming)
			{
				this.__StoredParent=Incoming;
			}
		}
		property d		// d returns row if f not specified
		{
			ANYTYPE Get()
			{
				return wParent.cCS_GetData(this);
			}
			VOID Set(ANYTYPE aData)
			{
				wParent.cCS_SetData(this,aData);
			}
		}
		property bFound
		{
			BOOLEAN Get()
			{
				return (this.d != NULL);
		
		// Row Actions
			}
		}
		Prepend(ANYTYPE aData)
		{
			wParent.cCS_InsertRow(this,aData,1);
		}
		Insert(ANYTYPE aData)
		{
			wParent.cCS_InsertRow(this,aData);
		}
		Append(ANYTYPE aData)
		{
			wParent.cCS_InsertRow(this,aData,-1);
		}
		Delete()
		{
			wParent.cCS_DeleteRow(this);
		
		}
		const dcInheritsFrom = cBASE;
		const lsClassFieldList={"c","r","f"};
		const lsClassPropertyList={"d","bFound","wParent"};
		
		/////////////////////////////////////////////////////////////////////////////
		{
			WINDOW __StoredParent = NULL;
		
	
	////////////////////////////////////////////////////////////////////////////
	// cTEXT		 	Encapsulates common actions for LIST OF STRING
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass cTEXT : cLIST
	{
		LIST OF ANYTYPE d = {};
		VOID Append(ANYTYPE Incoming NULL)
		{
			cLIST::Append(MakeText(Incoming));
	
	////////////////////////////////////////////////////////////////////////////
	// cSEARCHABLELIST	Searchable array class
	//
	// Purpose: 		Provides fast searching for data in a record type format
	//
	// Expand this for documentation
		//
		// inherits: 		cLIST
		//
		// PUBLIC MEMBERS - METHODS:
		//
		//		Find(a)				Returns the record where the first entry matches a
		//		GetNumFields()		Returns the number of fields in each record 
		//		FindIndex(a)		Returns the record number where the first field matches a
		//		GetData(i)			Returns the data for the record who's index is i
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		//		iFields				Number of fields
		//
		// NOTES: 
		//
		// Assumptions are: 	All rows have same number of items
		//
		// Typical use:			ColumnSelector can be a field name or column number
		//						RowSelector can be field contents of that column, or row number
		//							RowSelectors that are not numbers will be searched for using
		//							ListFind on the column specified in ColumnSelector
		//						CurrentRow returns a list of the row specified by ColumnSelector & RowSelector
		//						CurrentField returns the field specified by RowSelector & FieldSelector
		//							Because RowSelector may be non numeric, non numeric values cause a
		//							ListFind to be performed on the column specified in ColumnSelector in
		//							order to determine the RowNumber. From there, the field is extracted.
		// 
		// 						CellSelectors can be pushed onto and popped off of a stack, using PushCellSelector
		//							and PopCellSelector.  
		//
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass cSEARCHABLELIST : cLIST
	{
		
		LIST OF STRING lsFieldNames = NULL;
		
		LIST 		d = NULL;		// Master list in list of rows format
		
		OBJECT		CreateNewFromSelf(BOOLEAN fMakeBlankRecord optional) // returns a blank version of this, allows to use object as template
		{
			OBJECT foo=cSEARCHABLELIST();
			foo.lsFieldNames=this.lsFieldNames;
			
			INTEGER i;
			if fMakeBlankRecord==NULL
			{
				fMakeBlankRecord=FALSE;
			}
			if fMakeBlankRecord
			{
				LIST Result={};
				for i = 1 to ListCount(this.lsFieldNames)
				{
					ListAppend(Result,NULL);
				}
				foo.d={Result};
			
			}
			foo.ColumnSelector=1;
			foo.RowSelector=1;
			foo.FieldSelector=1;
			return foo;
		
		}
		property	bFound			// returns FALSE if current specifiers result in a "not found" 
		{
			BOOLEAN Get()
			{
				return this.CurrentCell!=NULL;
		
			}
		}
		ANYTYPE		GrabField(ANYTYPE aColID NULL, ANYTYPE aRowID NULL, ANYTYPE aFieldID NULL optional, BOOLEAN fForceSearch NULL optional)
		{
			// this is the most often called interface
			
			ApplyIfNull(aColID,NULL);
			ApplyIfNull(aRowID,NULL);
			ApplyIfNull(aFieldID,NULL);
			ApplyIfNull(fForceSearch,FALSE);
			oProfiler.Mark4(this.GetExtName({aColID,aRowID,aFieldID,fForceSearch})) ;
			
			LIST    lFieldPos=this.__GetFieldLoc(aColID,aRowID,aFieldID,fForceSearch);
			ANYTYPE Result=NULL;
			do
			{
				Result=this.d[lFieldPos[2]][lFieldPos[3]];
			}
			except
			{
				// nada
			
			}
			oProfiler.Mark4(this.GetExtName({aColID,aRowID,aFieldID,fForceSearch})) ;
			return Result;
		
		}
		ANYTYPE 	GrabColumn(ANYTYPE aColID NULL optional, ANYTYPE aRowID NULL optional)
		{
			PushCellSelector();
			if aColID != NULL
			{
				this.ColumnSelector=aColID;
			}
			if aRowID != NULL
			{
				this.RowSelector=aRowID;
			
			}
			ANYTYPE Result=this.CurrentColumn;
			PopCellSelector();
			return Result;
		}
		ANYTYPE		GrabRow(ANYTYPE aColID NULL optional, ANYTYPE aRowID NULL optional, BOOLEAN fForceSearch optional) 
		{
			PushCellSelector();
			if aColID != NULL
			{
				this.ColumnSelector=aColID;
			}
			if aRowID != NULL
			{
				this.RowSelector=aRowID;
			
			}
			if fForceSearch != NULL
			{
				this.RowContentSelector=aRowID;
			}
			ANYTYPE Result=this.CurrentRow;
			PopCellSelector();
			return Result;
		}
		VOID		PutField(ANYTYPE aColID NULL, ANYTYPE aRowID NULL, ANYTYPE aFieldID NULL, ANYTYPE aData, BOOLEAN fForceSearch optional)
		{
			PushCellSelector();
			
			if aColID != NULL
			{
				this.ColumnSelector=aColID;
			}
			if aRowID != NULL
			{
				this.RowSelector=aRowID;
			}
			if aFieldID != NULL
			{
				this.FieldSelector=aFieldID;
			
			}
			if fForceSearch != NULL
			{
				this.RowContentSelector=aRowID;
			
			}
			this.CurrentField=aData;
			
			PopCellSelector();
			
		
		}
		OBJECT 		CreateWith(ANYTYPE Incoming) // added for compatibility with cLIST interface, accepts LIST OF STRING, cLIST, cSEARCHABLELIST
		{
			if IsVarObject(Incoming)
			{
				Incoming=Incoming.d;
			}
			return this.AddRows(Incoming);
		
		// List manipulation stuff
		}
		INTEGER 	AddRow(LIST Incoming optional)
		{
			
			// check to see if we need to make a blank row
			if Incoming == NULL
			{
				OBJECT TempList = cLIST();
				
				INTEGER i;
				for i = 1 to iNumCols
				{
					TempList.Append(NULL);
				
				}
				Incoming=TempList.d;
				
			
			}
			if this.d != NULL
			{
				if ListCount(this.d)>0
				{
					if ListCount(Incoming) != this.iNumCols
					{
						print("Number of Columns={this.iNumCols} Number of incoming fields={ListCount(Incoming)}");
						raise 1, "ERROR: Invalid number of fields in data passed to cSEARCHABLELIST().AddRow({Incoming})";
			
					}
				}
			}
			if this.d == NULL
			{
				this.d={};
			}
			ListAppend(this.d,Incoming);
			this.__CheckCache();
			
			return this.iNumRows;
			
		}
		OBJECT		AddRows(LIST Incoming)
		{
			ANYTYPE item;
			for each item in Incoming
			{
				this.AddRow(item);
			}
			return this;
		}
		LIST		DeleteRow(ANYTYPE TargetRowID optional)
		{
			this.PushCellSelector();
			
			if TargetRowID==NULL
			{
				TargetRowID=this.iRowNumber;
			
			}
			this.RowSelector=TargetRowID;
			ANYTYPE Result=this.CurrentRow;
			ListDelete(d,iRowNumber);
			
			this.PopCellSelector();
			return Result;
		}
		VOID		AddColumn(LIST aData, STRING sNewFieldName optional)
		{
			OBJECT OldListOfColumns = cLIST().CreateWith(this.dx);
			OldListOfColumns.Append(aData);
			this.InsertColumnData(OldListOfColumns.d);
			
			if this.lsFieldNames != NULL	// if this is null, do nothing more
			{
				
				if sNewFieldName==NULL		  // if we do have field names, but none was specified for this, create one
				{
					sNewFieldName="Column{this.iNumCols+1}";
				
				}
				ListAppend(this.lsFieldNames,sNewFieldName);
				
			
			}
		}
		VOID		InsertColumn(ANYTYPE ColumnID, LIST lColumnData, STRING sNewFieldName optional) // inserts BEFORE specified col
		{
			
			if ListCount(lColumnData) != this.iNumRows
			{
				raise LIBERROR_WRONG_NUMBER_OF_ELEMENTS,"InsertColumn() failed, incoming list had {ListCount(lColumnData)} elements, rather than the {this.iNumRows} elements expected";
			}
			else if (this.lsFieldNames != NULL) && (sNewFieldName==NULL)
			{
				raise LIBERROR_FIELD_NAME_MISSING,"InsertColumn() failed, object had field names, but none specified for the new column";
			}
			else
			{
				
				if (this.lsFieldNames == NULL) && (sNewFieldName!=NULL)
				{
					Log.LogWarning("Warning: cSEARCHABLELIST().InsertColumn() you specified a field name, but there were no field names already in the object. Data was ignored");
					Log.PrintCallStack();
				
				}
				PushCellSelector();
				
				OBJECT foo=cSEARCHABLELIST();
				foo.d=this.__ColsToRows(this.d);
				INTEGER p=this.GetFieldNum(ColumnID);
				
				foo.Insert(p,lColumnData);
				this.d=this.__RowsToCols(foo.d);
				
				ListInsert(this.lsFieldNames,p,sNewFieldName);
				
				PopCellSelector();
			}
			__CheckCache() ;
		}
		VOID		InsertRow(ANYTYPE RowID, LIST lRowData)
		{
			if ListCount(lRowData) != this.iNumRows
			{
				raise LIBERROR_WRONG_NUMBER_OF_ELEMENTS,"InsertRow() failed, incoming list had {ListCount(lRowData)} elements, rather than the {this.iNumCols} elements expected";
			}
			else
			{
				PushCellSelector();
				
				this.RowSelector=RowID;
				ListInsert(this.d,this.iRowNumber,lRowData);
				
				PopCellSelector();
				
			}
			__CheckCache();
		}
		VOID		Append(LIST lRowData)	// FOR MAINTAINING INHERETED INTERFACE
		{
			if ListCount(lRowData) != this.iNumCols
			{
				raise LIBERROR_WRONG_NUMBER_OF_ELEMENTS,"InsertRow() failed, incoming list had {ListCount(lRowData)} elements, rather than the {this.iNumCols} elements expected";
			}
			else
			{
				PushCellSelector();
				derived::Append(lRowData);
				PopCellSelector();
				
			}
			__CheckCache();
			
		
		// Data selectors
		}
		property 	ColumnSelector	// R/W STRING/INTEGER can be string or number, string does lookup from lsFieldNames
		{
			ANYTYPE Get()
			{
				return this.__LastColumnSelectorSpecified;
			}
			VOID Set(ANYTYPE Incoming)
			{
				this.__LastColumnSelectorSpecified = Incoming;
			}
		}
		property 	RowSelector 	// R/W STRING/INTEGER can be string or number, string causes fast lookup of first field
		{
			ANYTYPE Get()
			{
				return this.__LastRowSelectorSpecified;
			}
			VOID Set(ANYTYPE Incoming)
			{
				this.__LastRowSelectorSpecified = Incoming;
			}
		}
		property	RowContentSelector // R/W can be any type, always does search
		{
			ANYTYPE Get()
			{
				return this.__LastRowSelectorSpecified;
			}
			VOID Set(ANYTYPE Incoming)
			{
				this.__CheckCache();
				INTEGER iResult=ListFind(this.CurrentColumn,Incoming);
				this.__LastRowSelectorSpecified = iResult;
			
			}
		}
		property 	CellSelector	// R/W LIST of {ColumnSelector,RowSelector}
		{
			LIST Get()
			{
				return {this.ColumnSelector, this.RowSelector, this.FieldSelector};
			}
			VOID Set(LIST Incoming)
			{
				INTEGER i=ListCount(Incoming);
				if i>0
				{
					this.ColumnSelector=Incoming[1];
				}
				if i>1
				{
					this.RowSelector=Incoming[2];
				}
				if i>2
				{
					this.FieldSelector=Incoming[3];
				}
			}
		}
		property 	FieldSelector	// R/W Similar to ColumnSelector, but selects for CurrentField
		{
			ANYTYPE Get()
			{
				return this.__LastFieldSelectorSpecified;
			}
			VOID Set(ANYTYPE Incoming)
			{
				this.__LastFieldSelectorSpecified = Incoming;
		
			}
		}
		property 	iColNumber		// R/O INTEFER Col specified by ColumnSelector
		{
			INTEGER Get()
			{
				INTEGER iResult=0, iTemp;
				if this.iNumCols > 0
				{
					iResult=1; // default answer
				}
				if IsVarString(this.ColumnSelector)
				{
					iResult=this.GetFieldNum(this.ColumnSelector);
				}
				else
				{
					iResult=this.ColumnSelector;
				}
				if (iResult==0) && (this.ColumnSelector == 0) && (this.iNumCols > 0)
				{
					iResult=1;
				
				}
				return iResult;
			}
		}
		property 	iRowNumber		// R/O INTEGER Row specified by RowSelector
		{
			INTEGER Get()
			{
				INTEGER iResult = 0;				   	// 0 is the default answer, means not found
				if IsVarInteger(this.RowSelector)   // is the current RowSelector a number?
				{
					iResult=this.RowSelector;		 // Yes, so just use the number
				}
				else
				{
					if this.iNumRows > 0					 // if it's a string, check that we actually HAVE some rows
					{
						if this.iColNumber > 0			   // and that we have a valid column to search in
						{
							iResult=ListFind(this.CurrentColumn, this.RowSelector);
						}
					}
				}
				return iResult;
			}
			VOID Set(INTEGER iNewNum)
			{
				this.RowSelector=this.CurrentColumn[iNewNum];
			}
		}
		property 	iFieldNumber	// R/O INTEGER Column specified by FieldSelector
		{
			INTEGER Get()
			{
				INTEGER iResult=0, iTemp;
				if this.iNumCols > 0
				{
					iResult=1; // default answer
				}
				if IsVarString(this.FieldSelector)
				{
					iResult=this.GetFieldNum(this.FieldSelector);
				}
				else
				{
					do
					{
						iResult=this.FieldSelector;
					}
					except
					{
						ExceptPrint();
					}
					if (iResult==0) && (this.FieldSelector == 0) && (this.iNumCols > 0)
					{
						iResult=1;
				
				
					}
				}
				return iResult;
		
		// Data presenters
			}
		}
		property 	CurrentColumn	// R/O LIST contents of column specified by FieldSelector
		{
			LIST Get()
			{
				this.__CheckCache();
				return this.__CachedColList[this.iColNumber];
				
			}
		}
		property 	CurrentRow		// R/W LIST contents of row specified by RowSelector
		{
			LIST Get()
			{
				this.__CheckCache();
				ANYTYPE Answer=NULL;
				if this.iRowNumber > 0
				{
					Answer=this.d[this.iRowNumber];
				}
				return Answer;
			}
			VOID Set(LIST lNewRowData)
			{
				this.d[this.iRowNumber]=lNewRowData;
				this.__CheckCache();
			}
		}
		property 	CurrentCell 	// R/W ANYTYPE contents of cell specified by RowSelector * ColumnSelector
		{
			ANYTYPE Get()
			{
				ANYTYPE Result=NULL;
				do
				{
					this.__CheckCache();
					Result=this.d[this.iRowNumber][this.iColNumber];
				}
				except
				{
					// nada
				}
				return Result;
			}
			VOID Set(ANYTYPE Incoming)
			{
				this.d[this.iRowNumber][this.iColNumber] = Incoming;
				this.__CheckCache();
			}
		}
		property 	CurrentField 	// R/W ANYTYPE contents of cell specified by RowSelector * FieldSelector
		{
			ANYTYPE Get()
			{
				oProfiler.Mark(this.GetExtName());
				this.__CheckCache();
				ANYTYPE Result=NULL;
				//this.__VerifyRanges()
				do
				{
					Result=this.d[this.iRowNumber][this.iFieldNumber];
				}
				except
				{
					// nothing, as the result will be null
				}
				oProfiler.Mark(this.GetExtName());
				return Result;
				
			}
			VOID Set(ANYTYPE Incoming NULL)
			{
				do
				{
					this.d[this.iRowNumber][this.iFieldNumber] = Incoming;
				}
				except
				{
					ANYTYPE item;
					OBJECT foo=cTEXTFILE("C:\TEMP.TXT");
					foo.Zap();
					for each item in this.d
					{
						foo.Append("{item}");
					}
					foo.Write();
					ExceptClear();
				}
				this.__CheckCache();
			}
		}
		property 	CurrentRowObject // R/O Returns current row as a cSEARCHABLELIST
		{
			ANYTYPE Get()
			{
				OBJECT temp=this.__UnitTest_ObjGen();
				temp.InsertColumnData({this.lsFieldNames,this.CurrentRow});
				return temp;
		
			}
		}
		property 	iNumRows		// R/O Number of rows
		{
			INTEGER Get()
			{
				INTEGER i=0;
				if this.d != NULL
				{
					i=ListCount(this.d);
				}
				return i;
			}
		}
		property 	iNumCols		// R/O Number of columns
		{
			INTEGER Get()
			{
				INTEGER i=0;
				if this.lsFieldNames != NULL
				{
					i=ListCount(this.lsFieldNames);
				}
				else
				{
					if (this.d != NULL)
					{
						if (this.d != {})
						{
							i=ListCount(this.d[1]);
						}
					}
				}
				return i;
		
			}
		}
		property 	iLength
		{
			INTEGER Get()
			{
				return this.iNumRows;
									// Query peforms a slow, case insensitive substring search 
			}
		}
		LIST 	 	Query(ANYTYPE sSlowSearchKey, ANYTYPE NewColumnSelector NULL optional)
		{
			this.PushCellSelector();
			OBJECT Result=cLIST();
			INTEGER i;
			
			if NewColumnSelector != NULL
			{
				this.ColumnSelector=NewColumnSelector;
			
			}
			for i=1 to iNumRows
			{
				this.RowSelector=i;
				if sContains(Upper("{this.CurrentCell}"),Upper("{sSlowSearchKey}"))
				{
					Result.Append(this.CurrentRow);
			
				}
			}
			this.PopCellSelector();
			
			return Result.d;
			
			
		}
		LIST 		Find(ANYTYPE aData)
		{
			if this.iColNumber==0
			{
				this.ColumnSelector=1;
			
			}
			this.RowSelector=aData;
			
			return this.CurrentRow;
		
		}
		ANYTYPE 	GetField(ANYTYPE aFieldID) // Gives a way to get a field without resetting the ColumnSelector
		{
			ANYTYPE Result=NULL;
			do
			{
				Result=this.CurrentRow[this.GetFieldNum(aFieldID)];
			}
			except
			{
				print("Couldn't GetField({aFieldID})");
				ExceptClear();
			
			}
			return Result;
		}
		VOID	 	SetField(ANYTYPE aFieldID, ANYTYPE NewData NULL, ANYTYPE NewRowSelector NULL optional, ANYTYPE NewColSelector NULL optional)
		{
			if NewColSelector != NULL
			{
				this.ColumnSelector=NewColSelector;
			}
			if NewRowSelector != NULL
			{
				this.RowSelector=NewRowSelector;
			}
			this.FieldSelector=aFieldID;
			this.CurrentField=NewData;
		
		}
		INTEGER 	GetFieldNum(ANYTYPE aFieldID)
		{
			if IsVarString(aFieldID)
			{
				aFieldID=ListFind(this.lsFieldNames, aFieldID);
			}
			return aFieldID;
		}
		ANYTYPE 	GetRow(ANYTYPE TempColSelector NULL optional, ANYTYPE TempRowSelector NULL optional)
		{
			ANYTYPE Answer=this.GetRowObject(TempColSelector,TempRowSelector);
			return Answer.dx[2];
			
		}
		ANYTYPE 	GetRowObject(ANYTYPE TempColSelector NULL optional, ANYTYPE TempRowSelector NULL optional)
		{
			this.PushCellSelector();
			
			if TempColSelector!=NULL
			{
				this.ColumnSelector = TempColSelector;
			}
			if TempRowSelector!=NULL
			{
				this.RowSelector = TempRowSelector;
			
			}
			ANYTYPE Answer=this.CurrentRowObject;
			this.PopCellSelector();
			return Answer;
		
		// Utility
		}
		VOID		PushCellSelector(ANYTYPE NewColumnSelector NULL optional, ANYTYPE NewRowSelector NULL optional, ANYTYPE NewFieldSelector NULL optional, BOOLEAN NewNumberSearchFlag optional)
		{
			ApplyIfNull(NewColumnSelector, NULL);
			ApplyIfNull(NewRowSelector, NULL);
			ApplyIfNull(NewFieldSelector, NULL);
			ApplyIfNull(NewNumberSearchFlag, NULL);
			oProfiler.Mark4(this.GetExtName({NewColumnSelector, NewRowSelector, NewFieldSelector, NewNumberSearchFlag})) ;
			
			this.__CellSelectorStack.Push(this.CellSelector);
			
			if NewColumnSelector != NULL
			{
				this.ColumnSelector = NewColumnSelector;
			}
			if NewRowSelector != NULL
			{
				this.RowSelector = NewRowSelector;
			}
			if NewFieldSelector != NULL
			{
				this.FieldSelector = NewFieldSelector;
			
			}
			oProfiler.Mark4(this.GetExtName({NewColumnSelector, NewRowSelector, NewFieldSelector, NewNumberSearchFlag})) ;
			
			
		}
		VOID		PopCellSelector()
		{
			oProfiler.Mark(this.GetExtName());
			this.CellSelector=this.__CellSelectorStack.Pop();
			oProfiler.Mark(this.GetExtName());
		
		}
		property 	dx				// R/w LIST OF LIST, all data in "list of columns" format
		{
			LIST Get()
			{
				this.__CheckCache();
				return this.__CachedColList;
			}
			VOID Set(LIST Incoming)
			{
				this.InsertColumnList(Incoming);
		
			}
		}
		property 	iFields 		// MAINTAIN OLD INTERFACE
		{
			INTEGER Get()
			{
				return this.iNumCols;
			}
		}
		INTEGER 	GetNumFields()	// MAINTAIN OLD INTERFACE
		{
			return this.iNumCols;
		}
		INTEGER 	FindIndex(ANYTYPE aData) // MAINTAIN OLD INTERFACE
		{
			if this.iColNumber==0
			{
				this.ColumnSelector=1;
			
			}
			this.RowSelector=aData;
			
			return this.iRowNumber;
			
		}
		LIST 		GetData(INTEGER iIndex)  // MAINTAIN OLD INTERFACE
		{
			if this.iColNumber==0
			{
				this.ColumnSelector=1;
			
			}
			this.RowSelector=iIndex;
			
			return this.CurrentRow2;
		}
		VOID		InsertColumnData(LIST incoming) // pass in a list of columns, instead of a list of rows. MAINTAIN OLD INTERFACE
		{
			this.d=this.__ColsToRows(incoming);
			this.__CachedRowList=this.d;
			this.__CachedColList=incoming;
		}
		VOID		Insert(ANYTYPE RowID, LIST lRowData)
		{
			this.InsertRow(RowID,lRowData);
		
		
		// Methods for cCELLSELECTOR
		}
		ANYTYPE cCS_GetData(OBJECT NewCellSelector) 
		{
			
			this.PushCellSelector();
			this.__ApplyCellSelector(NewCellSelector);
			ANYTYPE Result=NULL;
			if NewCellSelector.f != NULL
			{
				Result=this.CurrentField;
			}
			else
			{
				Result=this.CurrentRow;
			}
			this.PopCellSelector();
			
			return Result;
			
		}
		VOID	cCS_SetData(OBJECT NewCellSelector, ANYTYPE aData)
		{
			
			this.PushCellSelector();
			this.__ApplyCellSelector(NewCellSelector);
			if NewCellSelector.f != NULL
			{
				this.CurrentField=aData;
			}
			else
			{
				this.CurrentRow=aData;
			}
			this.PopCellSelector();
			
		}
		VOID	cCS_InsertRow(OBJECT NewCellSelector, ANYTYPE aData, INTEGER iNumericOverride optional)
		{
			this.PushCellSelector();
			this.__ApplyCellSelector(NewCellSelector);
			INTEGER iLine=this.RowNumber;
			if iNumericOverride != NULL
			{
				iLine=iNumericOverride;
			}
			if iLine < 0
			{
				this.Append(aData);
			}
			else
			{
				this.Insert(iLine,aData);
			}
			this.PopCellSelector();
			
		}
		VOID	cCS_DeleteRow(OBJECT NewCellSelector)
		{
			this.PushCellSelector();
			this.__ApplyCellSelector(NewCellSelector);
			this.Delete(this.iRowNumber);
			this.PopCellSelector();
			
		}
		VOID	__ApplyCellSelector(OBJECT NewCellSelector)
		{
			this.ColumnSelector=NewCellSelector.c;
			this.RowSelector=NewCellSelector.r;
			this.FieldSelector=NewCellSelector.f;
		  
		}
		const dcInheritsFrom 	  = cLIST;
		const lsClassFieldList    = {"lsFieldNames"};
		const lsClassPropertyList = 
		{
			"ColumnSelector",
			"RowSelector",
			"CellSelector",
			"CurrentColumn",
			"CurrentRow",
			"CurrentCell",
			"dx",
			"iNumRows",
			"iNumCols",
			"iColNumber",
			"iRowNumber"
		};
		const lsInstanceFieldList    = {};
		const lsInstancePropertyList = {};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS
		{
			
			// property 	__DerivedList	// Returns list specified in the class, may not wind up being used by the time I'm done
			{
				// LIST Get()
				{
					// return derived::d
				// VOID Set(LIST NewList)
					// derived::d=NewList
				}
			}
			LIST	 	__CachedRowList = NULL;	// Used for noting changes between queries
			LIST	 	__CachedColList = NULL;	// Used for noting changes between queries
			ANYTYPE		__LastColumnSelectorSpecified = 0;
			ANYTYPE		__LastRowSelectorSpecified = 0;
			ANYTYPE		__LastFieldSelectorSpecified = 0;
			
			cLIST 		__CellSelectorStack {}
			
			LIST 	 	__ColsToRows(LIST Incoming)	// convert column based data to row based data (LIST OF COLUMNS -> LIST OF ROWS)
			{
				OBJECT lResult = cLIST();
				OBJECT lRecord = cLIST();
				
				INTEGER i, j, iFields=ListCount(Incoming);
				
				if ListCount(Incoming[1]) > 0
				{
					for i = 1 to ListCount(Incoming[1])
					{
						
						lRecord.d={};
						
						for j = 1 to iFields
						{
							lRecord.Append(Incoming[j][i]);
						
						}
						lResult.Append(lRecord.d);
				
					}
				}
				return lResult.d;
				
			}
			LIST     	__RowsToCols(LIST Incoming)	// convert row based data to column based data (LIST OF ROWS -> LIST OF COLUMNS)
			{
				
				OBJECT lResult = cLIST();
				OBJECT lColumn = cLIST();
				
				INTEGER i, j, iColumns=0, iRows;
				
				iRows=ListCount(Incoming);
				
				if iRows > 0
				{
					
					iColumns=ListCount(Incoming[1]);
					for i = 1 to iColumns
					{
						
						lColumn.d={};
						
						for j = 1 to iRows
						{
							lColumn.Append(Incoming[j][i]);
						
						}
						lResult.Append(lColumn.d);
				
					}
				}
				return lResult.d;
				
			}
			VOID		__CheckCache()
			{
				if this.d != this.__CachedRowList
				{
					this.__CachedRowList = this.d;
					this.__CachedColList = this.__RowsToCols(this.d);
				}
				if this.lsFieldNames == NULL
				{
					if this.sPassedValue != ""
					{
						
						STRING sTemp=this.sPassedValue;
						
						if sTemp[1]==LeftBrace
						{
							if sTemp[Len(sTemp)]==RightBrace
							{
								
								sTemp[1]="";
								sTemp[Len(sTemp)]="";
						
							}
						}
						this.lsFieldNames=MakeListFromCSV(sTemp);
						
					}
				}
			}
			VOID 		__VerifyRanges()
			{
				if ! IsInRange(this.iRowNumber,1,this.iNumRows)
				{
					raise E_ARG_VAL_OUT_OF_RANGE,"RowSelector {this.RowSelector} (which results in iRowNumer={this.iRowNumber}) was out of range. (Max was {iNumRows})";
				}
				if ! IsInRange(this.iColNumber,1,this.iNumCols)
				{
					raise E_ARG_VAL_OUT_OF_RANGE,"ColumnSelector {this.ColumnSelector} (which results in iColNumer={this.iColNumber}) was out of range. (Max was {iNumCols})";
				}
				if ! IsInRange(this.iFieldNumber,1,this.iNumCols)
				{
					raise E_ARG_VAL_OUT_OF_RANGE,"FieldSelector {this.FieldSelector} (which results in iFieldNumer={this.iFieldNumber}) was out of range. (Max was {iNumCols})";
			
				}
			}
			INTEGER		__GetColNum(ANYTYPE aColID NULL)
			{
				ApplyIfNull(aColID,NULL);
				oProfiler.Mark4(this.GetExtName({aColID})) ;
				
				if aColID==NULL
				{
					aColID=this.ColunmSelector;
				}
				if ! IsVarInteger(aColID)
				{
					aColID=ListFind(this.lsFieldNames, aColID);
				
				}
				oProfiler.Mark4(this.GetExtName({aColID})) ;
				return aColID;
				
			}
			INTEGER		__GetRowNum(ANYTYPE aColID NULL, ANYTYPE aRowID NULL, BOOLEAN fForceSearch NULL optional)
			{
				aColID=this.__GetColNum(aColID);
				ApplyIfNull(fForceSearch,FALSE);
				
				if aRowID==NULL
				{
					aRowID=this.RowSelector;
				}
				if (! IsVarInteger(aRowID)) || fForceSearch
				{
					aRowID=ListFind(this.__CachedColList[aColID],aRowID);
				
				}
				return aRowID;
				
			}
			LIST		__GetFieldLoc(ANYTYPE aColID NULL, ANYTYPE aRowID NULL, ANYTYPE aFieldID NULL optional, BOOLEAN fForceSearch NULL optional)
			{
				aColID=this.__GetColNum(aColID);
				ApplyIfNull(fForceSearch,FALSE);
				aRowID=this.__GetRowNum(aColID,aRowID,fForceSearch);
				
				if aFieldID==NULL
				{
					aFieldID=this.FieldSelector;
				}
				if ! IsVarInteger(aFieldID)
				{
					aFieldID=ListFind(this.lsFieldNames, aFieldID);
				
				}
				return {aColID,aRowID,aFieldID};
				
			
			// OLD cSEARCHABLELIST
				// LIST d = {} // this is the raw data from the user
				// 
				// LIST Find(ANYTYPE aData)
				{
					// INTEGER p=this.FindIndex(aData)
					// aData=NULL
					// if p > 0
					{
						// aData=this.GetData(p)
					// return aData
				// 
				// property iFields 
					// INTEGER Get()
						// return GetNumFields()
				// 
				// INTEGER GetNumFields()
					// INTEGER iNumFields = 0
					// if ListCount(this.d) >0
						// iNumFields=ListCount(this.d[1])
					// return iNumFields
				// INTEGER FindIndex(ANYTYPE aData)
					// this.__ConditionalUpdate()
					// INTEGER iResult=0
					// if this.iSize > 0
						// iResult=ListFind(this.__lInvertedData[1],aData)
					// return iResult
					// 
				// LIST 	GetData(INTEGER iIndex)
					// this.__ConditionalUpdate()
					// INTEGER iSize = ListCount(this.d)
					// if iIndex > ListCount(this.d)
						// raise E_BAD_INDEX, "*** Error: Index value of {iIndex} exceeds list size of {this.iSize}"
					// 
					// LIST lResult={}
					// INTEGER i
					// for i = 1 to this.iFields
						// ListAppend(lResult,this.__lInvertedData[i][iIndex])
					// 
					// return lResult
				// 
				// VOID	InsertColumnData(LIST incoming) // pass in a list of columns
					// this.__Revert(incoming)
				// 
				// const dcInheritsFrom = cLIST
				// const lsClassFieldList={}
				// const lsClassPropertyList={"iFields"}
				// 
				// ////////////////////////////////////////
				// 
				// LIST __lCachedData = {} 	// this is what we had last time we inverted (saves inverting again)
				// LIST __lInvertedData = {} 	// this is the inverted data
				// 
				// VOID __ConditionalUpdate()
					// if this.d != this.__lCachedData
						// this.__Invert()
				// VOID __Invert()
					// 
					// ANYTYPE item
					// LIST lCurrent
					// INTEGER i // this is used for stepping thru fields
					// 
					// if this.iSize>0
						// 
						// this.__lCachedData = this.d // update the cache
						// this.__lInvertedData={}
						// 
						// // generate blank containers
						// for item=1 to this.iFields
						{
							// ListAppend(this.__lInvertedData,{})
						// 
						// // now blank container is ready for data
						// for item = 1 to ListCount(this.d)
							// 
							// for i = 1 to this.iFields
							{
								// ListAppend(this.__lInvertedData[i], this.d[item][i])
							// 
					// 
					// 
				// VOID __Revert(LIST incoming)
					// // { {col1-entry1,col1-entry2},{col2-entry1,col2-entry2} }
					// 
					// OBJECT lResult = cLIST()
					// OBJECT lRecord = cLIST()
					// 
					// INTEGER i, j, iFields=ListCount(incoming)
					// 
					// if ListCount(incoming[1]) > 0
						// for i = 1 to ListCount(incoming[1])
							// 
							// lRecord.d={}
							// 
							// for j = 1 to iFields
								// lRecord.Append(incoming[j][i])
							// 
							// lResult.Append(lRecord.d)
					// 
					// this.d=lResult.d
				// 
				// VOID __UnitTest()
					// LIST foo = {...}
						// {"Igor","Server"}
						// {"Phil","Install"}
						// {"Jesun","API"}
						// {"Akien","WebFilter"}
					// 
					// OBJECT me = cSEARCHABLELIST()
					// me.d=foo
					// 
					// me.__ConditionalUpdate()
					// print(me.d)
					// print(me.__lCachedData)
					// print(me.__lInvertedData)
					// print(me.iSize)
					// print(me.iFields)
					// print(me.FindIndex("Akien"))
					// 
		////////////////////////////////////////////////////////////////////////////
		// Unit tests
							}
						}
					}
				}
			}
			OBJECT		__UnitTest_PopulatedObj()
			{
				OBJECT foo=this.__UnitTest_ObjGen();
				foo.lsFieldNames={"First","Last","Addr","City","State","Zip"};
				foo.d=
				{
					{"Akien","MacIain","123 Main","Pleasantville","AK","12345"},
					{"Igor","Svidler","234 Fleet","Washington","DC","67890"},
					{"Jesun","Manuel","246 Splash","San Francisco","FL","99999"},
					{"Phil","Boatwright","111 Uplook","Seattle","TX","11111"}
				};
				return foo;
			}
			VOID UnitTests()
			{
				this.UnitTest_FieldNameLookup();
				this.UnitTest_BasicLookup();
				this.UnitTest_FieldNameRowLookup();
				this.UnitTest_NoColSelectorTest();
				this.UnitTest_FieldLookupTest();
				this.UnitTest_AddRow();
			
			}
			VOID UnitTest_FieldNameLookup()
			{
				OBJECT foo = this.__UnitTest_ObjGen();
				foo.lsFieldNames = {"One","Two","Three"};
				print("UnitTest_FieldNameLookup: {MakePassFail(foo.GetFieldNum("Two")==2)}");
				
				
			}
			VOID UnitTest_BasicLookup()
			{
				OBJECT foo = this.__UnitTest_PopulatedObj();
				
				foo.ColumnSelector=2;
				foo.RowSelector="Svidler";
				
				print("UnitTest_BasicLookup: {MakePassFail(foo.CurrentRow==foo.d[2])}");
			}
			VOID UnitTest_FieldNameRowLookup()
			{
				OBJECT foo = this.__UnitTest_PopulatedObj();
				
				foo.ColumnSelector="Last";
				foo.RowSelector="Svidler";
				
				print("UnitTest_FieldNameRowLookup: {MakePassFail(foo.CurrentRow==foo.d[2])}");
			}
			VOID UnitTest_NoColSelectorTest()
			{
				OBJECT foo = this.__UnitTest_PopulatedObj();
				
				foo.RowSelector="Igor";
				
				print("UnitTest_NoColSelectorTest: {MakePassFail(foo.CurrentRow==foo.d[2])}");
				
			}
			VOID UnitTest_FieldLookupTest()
			{
				OBJECT foo = this.__UnitTest_PopulatedObj();
				
				foo.ColumnSelector="First";
				foo.RowSelector="Igor";
				foo.FieldSelector="City";
				
				Print("UnitTest_FieldLookupTest: {MakePassFail(foo.CurrentField=="Washington")}");
				
				
			}
			VOID UnitTest_AddRow()
			{
				OBJECT foo = this.__UnitTest_PopulatedObj();
				foo.AddRow({"FirstName","LastName","Address","City","State","Zip"});
				SmartListPrint(foo.d);
				
				foo=cSEARCHABLELIST();
				foo.AddRow({"FirstName","LastName","Address","City","State","Zip"});
				SmartListPrint(foo.d);
				
				
			
			
		////////////////////////////////////////////////////////////////////////////
		
	
	
	////////////////////////////////////////////////////////////////////////////
	// cDATE			General purpose date object
	//
	// Purpose:			Collect all date functions under one roof
	//
	// Expand this for documentation
	////////////////////////////////////////////////////////////////////////////
			}
		}
	}
	winclass cDATE : cDATA
	{
		
		property 	d	// maintain compatibility with cDATA
		{
			ANYTYPE Get()
			{
				return this.dtDateTime;
			}
			VOID Set(ANYTYPE aNew)
			{
				this.dtDateTime=aNew;
		
			}
		}
		DATETIME 	dtDateTime;
		
		OBJECT		Subtract(OBJECT NewDateTime)	// subtract passed object's datetime from this.dtDateTime
		{
			if ! NewDateTime.IsOfClass(cDATE)
			{
				raise LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS,"Object {NewDateTime.sRawName} passed to {this.sRawName}.Subtract() was not a cDATE object";
			
			}
			OBJECT Result=cDATE();
			
			//DiffDateTime (DateTime1, DateTime2 [, iHours, iMinutes,  iSeconds, iMicrosecs])
			INTEGER iNewDays, iNewHours, iNewMinutes, iNewSeconds, iNewMicroseconds;
			iNewDays=DiffDateTime (this.dtDateTime, NewDateTime.dtDateTime,iNewHours,iNewMinutes,iNewSeconds,iNewMicroseconds);
			
			STRING z='0';
			STRING r="";
			r=r+"0000/00/";
			r=r+"{MakeWidth(iNewDays,2,z)} ";
			r=r+"{MakeWidth(iNewHours,2,z)}:";
			r=r+"{MakeWidth(iNewMinutes,2,z)}:";
			r=r+"{MakeWidth(iNewSeconds,2,z)}.";
			r=r+"{iNewMicroseconds}";
			
			Result.dtDateTime=[DATETIME]r;
			
			return Result;
		}
		OBJECT		Add(OBJECT NewDateTime)			// complements Subtract()
		{
			if ! NewDateTime.IsOfClass(cDATE)
			{
				raise LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS,"Object {NewDateTime.sRawName} passed to {this.sRawName}.Add() was not a cDATE object";
			
			}
			OBJECT Result=cDATE();
			
			Result.dtDateTime=AddDateTime (NewDateTime.dtDateTime,this.iDay,this.iHour,this.iMinute,this.iSecond,this.iMilliSecond);
			
			return Result;
			
		}
		VOID		Assign(ANYTYPE New)
		{
			if IsVarString(New)
			{
				this.dtDateTime=[DATETIME]New;
			}
			else if IsVarWindow(New)
			{
				if New.IsOfClass(cDATE)
				{
					this.dtDateTime=New.dtDateTime;
				}
				else
				{
					raise LIBERROR_OBJECT_NOT_OF_EXPECTED_CLASS,"Invalid class {New.Class} passed into cDATE.Assign()";
				}
			}
			else if IsVarDateTime(New)
			{
				
			}
			else
			{
				raise LIBERROR_INVALID_DATA_TYPE,"Invalid data type {TypeOf(New)} passed into cDATE.Assign()";
		
			}
		}
		property	dDate
		{
			DATE Get()
			{
				return [DATE] this.dtDateTime;
			}
		}
		property	sDate
		{
			STRING Get()
			{
				return "{this.dDate}";
			}
		}
		property	tTime
		{
			TIME Get()
			{
				return [TIME] this.dtDateTime;
			}
		}
		property	sTime
		{
			STRING Get()
			{
				return "{this.tTime}";
		
			}
		}
		property 	iHour
		{
			INTEGER Get()
			{
				return this.__GetPart(DTP_HOUR);
			}
		}
		property 	iMinute
		{
			INTEGER Get()
			{
				return this.__GetPart(DTP_MINUTE);
			}
		}
		property 	iSecond
		{
			INTEGER Get()
			{
				return this.__GetPart(DTP_SECOND);
			}
		}
		property 	iMilliSecond
		{
			INTEGER Get()
			{
				return this.__GetPart(DTP_MICROSEC)*1000000;
			}
		}
		property 	iYear
		{
			INTEGER Get()
			{
				return this.__GetPart(DTP_YEAR);
			}
		}
		property 	iMonth
		{
			INTEGER Get()
			{
				return this.__GetPart(DTP_MONTH);
			}
		}
		property 	iDay
		{
			INTEGER Get()
			{
				return this.__GetPart(DTP_DAY);
			}
		}
		property 	sSortableDate
		{
			STRING Get()
			{
				return "{this.iYear}{this.iMonth}{this.iDay}";
			}
		}
		property 	sSortableTime
		{
			STRING Get()
			{
				return "{this.iHour}{this.iMinute}{this.iSecond}";
			}
		}
		property 	sSortableDateTime
		{
			STRING Get()
			{
				return "{this.iYear}{this.iMonth}{this.iDay}{this.iHour}{this.iMinute}{this.iSecond}";
			}
		}
		property 	iDayOfWeek			
		{
			INTEGER Get()
			{
				return this.__GetPart(DTP_DAYOFWEEK)+1;
			}
		}
		property 	iDayOfYear
		{
			INTEGER Get()
			{
				return this.__GetPart(DTP_DAYOFYEAR);
			}
		}
		property 	sDayOfWeek
		{
			STRING Get()
			{
				return this.lsDaysOfTheWeek[this.iDayOfWeek];
		
			}
		}
		property	sSystemShortDateFormat
		{
			STRING Get()
			{
				return this.GetShortDateFormat();
			}
		}
		property 	sSystemLongDateFormat
		{
			STRING Get()
			{
				return this.GetLongDateFormat();
		
			}
		}
		OBJECT		MakeNow()
		{
			this.dtDateTime = GetDateTime();
			return this;
		}
		INTEGER 	GetDay ()
		{
			return this.__GetPart(DTP_DAY);
		}
		INTEGER 	GetMonth ()
		{
			return this.__GetPart(DTP_MONTH);
		}
		INTEGER 	GetYear ()
		{
			return this.__GetPart(DTP_YEAR);
		}
		STRING 		GetDate()
		{
			return FormatDateTime (this.dtDateTime, this.sSystemShortDateFormat);
		}
		STRING 		GetFormattedDate (STRING sDateFormat)
		{
			//returns full date as in Tuesday, May 22, 2001  or 5/22/01
			//STRING is of form     dddd, mmmm dd, yyyy   or mm/dd/yy
			
			// if (this.iDay <10) //test to see if day is one or two digits in length
			{
				// sDateFormat = " dddd, mmmm d, yyyy" //SINGLE day digit for date comparison!!!!
			//else, use " dddd, mmmm dd, yyyy" double digit int for day of month
			
			// format current date and time
			}
			STRING sDate = FormatDateTime (this.dtDateTime, sDateFormat);
			return sDate;
			
		}
		STRING 		IncrementDecrementCurrentDate (INTEGER iIncDec)
		{
			
			datetime dtCurrentDate = this.dtDateTime;
			STRING sCurrentDate = FormatDateTime ([DATETIME] dtCurrentDate, this.sSystemShortDateFormat);
			
			// Increment or decrement current date by iIncDec
			datetime dtNewDate = AddDateTime (dtCurrentDate, iIncDec);
			this.dtDateTime = dtNewDate;
			return (FormatDateTime ([DATETIME] dtNewDate, this.sSystemShortDateFormat));
			
		
		}
		STRING 		GetShortDateFormat ()
		{
			return this.__ExtractShortDateFormat();
			
		}
		STRING 		GetLongDateFormat ()
		{
			return this.__ExtractLongDateFormat();
		}
		VOID 		SetRegionLocale(STRING sLocale)
		{
			if sLocale != __ExtractPresentLocale()
			{
				__RegionalSettingsProperties.SelectLocale(sLocale);
			}
		}
		STRING 		GetPresentLocale ()
		{
			return this._ExtractPresentLocale();
		}
		STRING 		ConvertExcelDate (STRING sExcelDate)
		{
			// CT 09/12/01********************************************************************
			// *** Method moved from TIMEDATE class to DATE class***
			// This Method converts a Date STRING gotten from MS Excel to the current System
			// Date format.
			//********************************************************************************
			
			INTEGER iCharNum;
			STRING sMonth = "";
			STRING sDay = "";
			STRING sYear = "";
			STRING sCharToType;
			INTEGER iLenDateToType = Len(sExcelDate);
			EXCEL_YYYYMMDD_DATE_CURSOR_STATE eDateCursorPosition = EYEAR_POSITION_1;
			
			for (iCharNum=1; iCharNum <= iLenDateToType; iCharNum++)
			{
				// Step through each char in the string
				sCharToType = SubStr (sExcelDate, iCharNum, 1);
				switch eDateCursorPosition
				{
					// One state for each digit position in a MM/DD/YYYY date
					case EYEAR_POSITION_1:
						// In first (leftmost) year portion of the date
						select
						{
							case (IsDigit(sCharToType)):
								// If the char is a digit, save it and move to the next state
								sYear = sYear + sCharToType;
								eDateCursorPosition = EYEAR_POSITION_2;
							default:
							{
								// Log a warning that data may have some bogus chars in it.
								Print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
								Log.LogWarning ("*** Warning: {this} Bad Data? Attempting to convert non-numeric ""{sCharToType}"" day char into date string");
								
							}
						}
					case EYEAR_POSITION_2:
						// The first year digits has been found
						// Now in second year digit state.
						select
						{
							case (IsDigit(sCharToType)):
								sYear = sYear + sCharToType;
								eDateCursorPosition = EYEAR_POSITION_3;
							default:
							{
								// Log a warning that data may have some bogus chars in it.
								Print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
								Log.LogWarning ("*** Warning: {this} Bad Data? Attempting to convert non-numeric ""{sCharToType}"" day char into date string");
						
							}
						}
					case EYEAR_POSITION_3:
						// The first 2 year digits have been found
						// Now in third year digit state
						select
						{
							case (IsDigit(sCharToType)):
								sYear = sYear + sCharToType;
								eDateCursorPosition = EYEAR_POSITION_4;
							default:
							{
								// Log a warning that data may have some bogus chars in it.
								Print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
								Log.LogWarning ("*** Warning: {this} Bad Data? Attempting to convert non-numeric ""{sCharToType}"" day char into date string");
						
							}
						}
					case EYEAR_POSITION_4:
						// The first 3 year digits have been found.
						// Now in fourth year digit state.
						select
						{
							case (IsDigit(sCharToType)):
								sYear = sYear + sCharToType;
								eDateCursorPosition = EMONTH_POSITION_1;
							default:
							{
								// Log a warning that data may have some bogus chars in it.
								Print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
								Log.LogWarning ("*** Warning: {this} Bad Data? Attempting to convert non-numeric ""{sCharToType}"" day char into date string");
						
							}
						}
					case EMONTH_POSITION_1:
						select
						{
							case (IsDigit(sCharToType)):
								// If the char is a digit, save it and move to the next state
								sMonth = sMonth + sCharToType;
								eDateCursorPosition = EMONTH_POSITION_2;
							case (sCharToType == "-"):
								// If the
								// - is a "-" and
								// - we haven't entered any month digits
								// then stay in the first month digit state.
								eDateCursorPosition = EMONTH_POSITION_1;
							default:
							{
								// Log a warning that data may have some bogus chars in it.
								Print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
								Log.LogWarning ("*** Warning: {this} Bad Data? Attempting to convert non-numeric ""{sCharToType}"" day char into date string");
						
							}
						}
					case EMONTH_POSITION_2:
						// In second month digit portion of the date
						select
						{
							case (IsDigit(sCharToType)):
								// If the char is a digit, save it and move to the next state
								sMonth = sMonth + sCharToType;
								eDateCursorPosition = EDAY_POSITION_1;
							case (sCharToType == "-"):
								// If the char
								// - is a "-" and
								// - we've already found the first month char
								// then move to the next state (first day digit).
								eDateCursorPosition = EDAY_POSITION_1;
							default:
							{
								// Log a warning that data may have some bogus chars in it.
								Print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
								Log.LogWarning ("*** Warning: {this} Bad Data? Attempting to convert non-numeric ""{sCharToType}"" day char into MM/DD/YYYY date string");
								
							}
						}
					case EDAY_POSITION_1:
						select
						{
							case (IsDigit(sCharToType)):
								// If the char is a digit, save it and move to the next state
								sDay = sDay + sCharToType;
								eDateCursorPosition = EDAY_POSITION_2;
							case (sCharToType == "-"):
								// If the
								// - is a "-" and
								// - we haven't entered any day digits
								// then stay in the first day digit state.
								eDateCursorPosition = EDAY_POSITION_1;
							default:
							{
								// Log a warning that data may have some bogus chars in it.
								Print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
								Log.LogWarning ("*** Warning: {this} Bad Data? Attempting to convert non-numeric ""{sCharToType}"" day char into date string");
						
							}
						}
					case EDAY_POSITION_2:
						select
						{
							case (IsDigit(sCharToType)):
								// After the second day digit has been found, that should be the end of the date string
								sDay = sDay + sCharToType;
								eDateCursorPosition = EDAY_POSITION_EXTRA;
							default:
							{
								// Log a warning that data may have some bogus chars in it.
								Print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
								Log.LogWarning ("*** Warning: {this} Bad Data? Attempting to convert non-numeric ""{sCharToType}"" day char into MM/DD/YYYY date string");
						
							}
						}
					case EDAY_POSITION_EXTRA:
						// If the full date has been specified but there are
						// still more chars in the string, then don't save them.
						// Log a warning that data may have some bogus chars in it.
						Print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
						Log.LogWarning ("*** Warning: {this} Too many chars? Attempting to convert more than 2 day chars into date string");
						
					default:
					{
						// We should never reach the default case, so raise an erorr
						print ("Chars entered=""{SubStr(sExcelDate,1,iCharNum)}, Month=""{sMonth}"", Day=""{sDay}"", Year=""{sYear}"" ");
						print ("Abnormal execution of ConvertExcelDate(), should not be in default case (state={eDateCursorPosition})");
						raise LIBERROR_FORMAT_INVALID, "*** Error: LIBERROR_FORMAT_INVALID in {this}";
			
			// First, look and see if sDay, sMonth and sYear were populated..
			// If not, then just return ""
			
					}
				}
			}
			if (sDay == "" && sMonth == "" && sYear == "")
			{
				return "";
				
			
			}
			STRING sResult;
			switch (GetShortDateFormat())
			{
				case "dd/MM/yyyy":
					// If Regional Settings were set to English (Canada)
					// RegionalSettingsProperties.SetActive()
					// RegionalSettingsProperties.Cancel.Click()
					sResult = (sDay + "/" + sMonth + "/" + sYear);
				case "MM/dd/yyyy":
					// If Regional Settings were set to English (United States)
					// RegionalSettingsProperties.SetActive()
					// RegionalSettingsProperties.Cancel.Click()
					sResult = (sMonth + "/" + sDay + "/" + sYear);
				case "M/d/yyyy":
					// If Regional Settings were set to English (United States)
					// RegionalSettingsProperties.SetActive()
					// RegionalSettingsProperties.Cancel.Click()
					sResult = (sMonth + "/" + sDay + "/" + sYear);
					
				default:
				{
					raise LIBERROR_FORMAT_INVALID, "*** Error: LIBERROR_FORMAT_INVALID in {this}, Date format {GetShortDateFormat()} is unrecognized";
			
				}
			}
			return sResult;
			
		
		}
		LIST lsDaysOfTheWeek={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
		
		const dcInheritsFrom = cBASE;
		const lsClassFieldList    = {'dtDateTime'};
		const lsClassPropertyList = {'dDate','sDate','tTime','sTime','iHour','iMinute','iSecond','iYear','iMonth','iDay','sSortableDate','sSortableTime','sSortableDateTime','iDayOfWeek','iDayOfYear','sSystemShortDateFormat','sSystemLongDateFormat'};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {};
			const lsPrivateClassPropertyList = {};
			
			private ANYTYPE __GetPart(ANYTYPE aPart)
			{
				return GetDateTimePart(this.dtDateTime, aPart);
			// type DATETIMEPART is enum
				// DTP_YEAR
				// DTP_MONTH
				// DTP_DAY
				// DTP_DAYOFYEAR
				// DTP_DAYOFWEEK
				// DTP_HOUR
				// DTP_MINUTE
				// DTP_SECOND
				// DTP_MICROSEC
				//
			
			}
			private STRING __ExtractPresentLocaleData(STRING sItem)
			{
				INTEGER iKey = HKEY_CURRENT_USER; // defined in msw32.inc
				STRING sPath = "Control Panel\International";
				return SYS_GetRegistryValue (iKey, sPath, sItem);
			
			}
			private STRING __ExtractPresentLocale()
			{
				return __ExtractPresentLocaleData("sCountry");
			
			}
			private STRING __ExtractShortDateFormat()
			{
				STRING sResult="M/d/yyyy";
				do
				{
					sResult=__ExtractPresentLocaleData("sShortDate");
				}
				except
				{
					// do nothing, if the registry call fails, the value
					// left in sResult is exactly what's needed.
					ExceptClear();
				}
				return sResult;
				
			}
			private STRING __ExtractLongDateFormat()
			{
				return __ExtractPresentLocaleData("sLongDate");
				
			
		////////////////////////////////////////////////////////////////////////////
		
			}
		}
	}
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cDATE()
	{
		OBJECT today = cDATE();
		today.MakeNow();
		Log.print(today.iDay);
		STRING TodayDate = today.GetFormattedDate ("dd mm yyyy");
		print ("Today is {TodayDate}");
		
	
	
	// enum for date state driven code
	}
	type EXCEL_YYYYMMDD_DATE_CURSOR_STATE is enum
	{
		// Used by ConvertExcelDate() in the cTIMEDATE object to convert
		// dates received from an Excel spreadsheet to the System date format
		EYEAR_POSITION_1,
		EYEAR_POSITION_2,
		EYEAR_POSITION_3,
		EYEAR_POSITION_4,
		EMONTH_POSITION_1,
		EMONTH_POSITION_2,
		EDAY_POSITION_1,
		EDAY_POSITION_2,
		EDAY_POSITION_EXTRA
		
	}
	msw2000 private WINDOW DialogBox __RegionalSettingsProperties
	{
		
		//launch the windows "regional settings" window from the control panel
		STRING sWinCmd = "rundll32 shell32.dll,Control_RunDLL intl.cpl";
		
		VOID Invoke ()
		{
			if (!bExists)
			{
				APP_Start(sWinCmd);
			}
			SetActive ();
		
		}
		ANYTYPE SelectLocale (STRING sNewLocale)
		{
			//change locale
			Invoke ();
			STRING sPresentLocale =this.ExtractPresentLocale (TRUE);
			__RegionalSettingsProperties.PageList1.Select ("General");
			
			//check to see if new locale equals present setting, if so, "Apply" button is inactive!
			if (sPresentLocale != sNewLocale)
			{
				General.YourLocaleLocation.Select(sNewLocale);
			
			}
			LIST OF ANYTYPE result = {"",""};
			
			result[1] = ExtractShortDateFormat (TRUE);
			result[2] = ExtractLongDateFormat (TRUE);
			
			if bExists
			{
				OK.Click();
			
			}
			return result;
		
		}
		STRING ExtractPresentLocale (BOOLEAN fLeaveOpen optional)
		{
			if fLeaveOpen == NULL
			{
				fLeaveOpen = FALSE;
			//read present locale
			}
			Invoke ();
			__RegionalSettingsProperties.PageList1.Select ("General");
			//__RegionalSettingsProperties.RegionalSettings.SetActive ()
			STRING sPresentLocale = General.YourLocaleLocation.GetSelText ();
			if ! fLeaveOpen
			{
				OK.Click();
			}
			return sPresentLocale;
			
		}
		STRING ExtractShortDateFormat (BOOLEAN fLeaveOpen optional)
		{
			if fLeaveOpen == NULL
			{
				fLeaveOpen = FALSE;
			}
			Invoke ();
			__RegionalSettingsProperties.PageList1.Select ("Date");
			STRING sShortDateFormat = General.xDate.ShortDateStyle.GetSelText();
			if ! fLeaveOpen
			{
				OK.Click();
			//print ("sShortDateFormat = {sShortDateFormat}")
			}
			return sShortDateFormat;
			
		}
		STRING ExtractLongDateFormat (BOOLEAN fLeaveOpen optional)
		{
			if fLeaveOpen == NULL
			{
				fLeaveOpen = FALSE;
			}
			Invoke ();
			__RegionalSettingsProperties.PageList1.Select ("Date");
			STRING sLongDateFormat = General.xDate.LongDateStyle.GetSelText();
			if ! fLeaveOpen
			{
				OK.Click();
			//print ("sLongDateFormat = {sLongDateFormat}")
			}
			return sLongDateFormat;
		
		//expand for window declarations
			tag "Regional Options";
			DialogBox General
			{
				multitag "General"
				{
					"$0"
				}
				StaticText SettingsForTheCurrentUserT
				{
					tag "$65535[1]";
				}
				StaticText ManyProgramsSupportInternat
				{
					tag "$65535[2]";
				}
				StaticText YourLocaleLocationText
				{
					tag "$65535[3]";
				}
				PopupList YourLocaleLocation
				{
					tag "$1030";
				}
				StaticText LanguageSettingsForTheSyst
				{
					tag "$65535[4]";
				}
				StaticText YourSystemIsConfiguredToR1
				{
					tag "$65535[5]";
				}
				ListView YourSystemIsConfiguredToR2
				{
					tag "$1035";
					Header Header1
					{
						tag "$0";
					}
				}
				PushButton SetDefault
				{
					tag "$1036";
				}
				PushButton Advanced
				{
					tag "$1037";
				}
			}
			PushButton OK
			{
				tag "$1";
			}
			PushButton Cancel
			{
				tag "$2";
			}
			PushButton Apply
			{
				tag "$12321";
			}
			PageList PageList1
			{
				tag "$12320";
			}
			DialogBox xDate
			{
				multitag "Date"
				{
					"$0"
				}
				StaticText ShortDateSampleText
				{
					tag "Short date sample:";
				}
				TextField ShortDateSample
				{
					tag "Short date sample:";
				}
				StaticText ShortDateStyleText
				{
					tag "Short date style:";
				}
				ComboBox ShortDateStyle
				{
					tag "Short date*";
				}
				StaticText DateSeparatorText
				{
					tag "Date separator:";
				}
				ComboBox DateSeparator
				{
					tag "Date separator:";
				}
				StaticText CalendarTypeText
				{
					tag "Calendar type:";
				}
				PopupList CalendarType
				{
					tag "Calendar type:";
				}
				StaticText LongDateSampleText
				{
					tag "Long date sample:";
				}
				TextField LongDateSample
				{
					tag "Long date sample:";
				}
				StaticText LongDateStyleText
				{
					tag "Long date style:";
				}
				ComboBox LongDateStyle
				{
					tag "Long date*";
				}
				StaticText ShortDateText
				{
					tag "Short date";
				}
				StaticText LongDateText
				{
					tag "Long date";
			
		
		//additional tab declarations added
				}
			}
		}
		DialogBox RegionalSettingsCopyingF
		{
			tag "Regional Settings -- Copying Files...";
			//parent __RegionalSettingsProperties
			CustomWin SysAnimate321
			{
				tag "[SysAnimate32]#1";
			}
			StaticText DI386KbdtuqDll1Text
			{
				tag "D:\i386\kbdtuq.dll[1]";
			}
			StaticText DI386KbdtuqDll2Text
			{
				tag "D:\i386\kbdtuq.dll[2]";
			}
			CustomWin Msctls_progress321
			{
				tag "[msctls_progress32]#1";
			}
			PushButton Cancel
			{
				tag "Cancel";
			
			}
		}
		DialogBox FilesNeeded
		{
			STRING sLocation;
			VOID CheckAndDismiss()
			{
				if bExists
				{
					//STRING sLocation = AutomationINI.WindowsInstalls.@("{GetGuiType()}").sValue
					{
						//from system test .ini file which is TBD as of 8/6/01
					}
					CopyFilesFrom.SetText(sLocation);
					OK.Click();
			
				}
			}
			tag "Files Needed";
			//parent RegionalSettingsCopyingF
			PushButton OK
			{
				tag "OK";
			}
			PushButton Cancel
			{
				tag "Cancel";
			}
			StaticText CopyFilesFromText
			{
				tag "Copy files from:";
			}
			ComboBox CopyFilesFrom
			{
				tag "Copy files from:";
			}
			PushButton SkipFile
			{
				tag "Skip File";
			}
			PushButton Browse
			{
				tag "Browse";
			}
			CustomWin Icon1
			{
				tag "[Icon]#1";
			}
			StaticText TheFileKbdurDllOnWindow
			{
				tag "The file 'kbdur.dll' on Windows NT Workstation CD-ROM is needed.";
			}
			StaticText TypeThePathWhereTheFileI
			{
				tag "Type the path where the file is located, and then click OK.";
			
		
	// mswnt40 private WINDOW DialogBox __RegionalSettingsProperties
		// 
		// //launch the windows "regional settings" window from the control panel
		// STRING sWinCmd = "rundll32 shell32.dll,Control_RunDLL intl.cpl"
		// 
		// VOID Invoke ()
			// if (!bExists)
				// APP_Start(sWinCmd)
			// SetActive ()
		// 
		// ANYTYPE SelectLocale (STRING sNewLocale)
			// //change locale
			// Invoke ()
			// STRING sPresentLocale =this.ExtractPresentLocale (TRUE)
			// __RegionalSettingsProperties.PageList1.Select ("Regional Settings")
			// 
			// //check to see if new locale equals present setting, if so, "Apply" button is inactive!
			// if (sPresentLocale != sNewLocale)
				// RegionalSettings.ManyProgramsSupportInternat3.Select(sNewLocale)
			// 
			// LIST OF ANYTYPE result = {"",""}
			// 
			// result[1] = ExtractShortDateFormat (TRUE)
			// result[2] = ExtractLongDateFormat (TRUE)
			// 
			// if bExists
				// OK.Click()
			// 
			// return result
		// 
		// STRING ExtractPresentLocale (BOOLEAN fLeaveOpen optional)
			// if fLeaveOpen == NULL
				// fLeaveOpen = FALSE
			// //read present locale
			// Invoke ()
			// __RegionalSettingsProperties.PageList1.Select ("Regional Settings")
			// //__RegionalSettingsProperties.RegionalSettings.SetActive ()
			// STRING sPresentLocale = RegionalSettings.ManyProgramsSupportInternat3.GetSelText ()
			// if ! fLeaveOpen
				// OK.Click()
			// return sPresentLocale
			// 
		// STRING ExtractShortDateFormat (BOOLEAN fLeaveOpen optional)
			// if fLeaveOpen == NULL
				// fLeaveOpen = FALSE
			// Invoke ()
			// __RegionalSettingsProperties.PageList1.Select ("Date")
			// STRING sShortDateFormat = RegionalSettings.xDate.ShortDateStyle.GetSelText()
			// if ! fLeaveOpen
				// OK.Click()
			// //print ("sShortDateFormat = {sShortDateFormat}")
			// return sShortDateFormat
			// 
		// STRING ExtractLongDateFormat (BOOLEAN fLeaveOpen optional)
			// if fLeaveOpen == NULL
				// fLeaveOpen = FALSE
			// Invoke ()
			// __RegionalSettingsProperties.PageList1.Select ("Date")
			// STRING sLongDateFormat = RegionalSettings.xDate.LongDateStyle.GetSelText()
			// if ! fLeaveOpen
				// OK.Click()
			// //print ("sLongDateFormat = {sLongDateFormat}")
			// return sLongDateFormat
		// 
		// //expand for window declaration
			// tag "Regional Settings Properties"
			// DialogBox RegionalSettings
				// multitag "Regional Settings"
					// "$0"
				// CustomWin ManyProgramsSupportInternat1
					// tag "[CplWorldMapClass]Many programs support international settings. Changing the Regional Settings affects the way these programs display and sort d*"
				// StaticText ManyProgramsSupportInternat2
					// tag "Many programs support international settings. Changing the Regional Settings affects the way these programs display and sort d*"
				// PopupList ManyProgramsSupportInternat3
					// tag "Many programs support international settings. Changing the Regional Settings affects the way these programs display and sort d*"
				// CheckBox SetAsSystemDefaultLocale
					// tag "Set as system default locale"
			// PushButton OK
				// tag "OK"
			// PushButton Cancel
				// tag "Cancel"
			// PushButton Apply
				// tag "Apply"
			// PageList PageList1
				// tag "#1"
			// DialogBox xDate
				// multitag "Date"
					// "$0"
				// StaticText ShortDateSampleText
					// tag "Short date sample:"
				// TextField ShortDateSample
					// tag "Short date sample:"
				// StaticText ShortDateStyleText
					// tag "Short date style:"
				// ComboBox ShortDateStyle
					// tag "Short date style:"
				// StaticText DateSeparatorText
					// tag "Date separator:"
				// ComboBox DateSeparator
					// tag "Date separator:"
				// StaticText CalendarTypeText
					// tag "Calendar type:"
				// PopupList CalendarType
					// tag "Calendar type:"
				// StaticText LongDateSampleText
					// tag "Long date sample:"
				// TextField LongDateSample
					// tag "Long date sample:"
				// StaticText LongDateStyleText
					// tag "Long date style:"
				// ComboBox LongDateStyle
					// tag "Long date style:"
				// StaticText ShortDateText
					// tag "Short date"
				// StaticText LongDateText
					// tag "Long date"
			// 
		// // // WINDOW DialogBox RegionalOptions
			// // // tag "Regional Options"
			// // // DialogBox General
				// // // multitag "General"
					// // // "$0"
				// // // StaticText SettingsForTheCurrentUserT
					// // // multitag "#1"
						// // // "Settings for the current user"
						// // // "$65535[1]"
				// // // StaticText ManyProgramsSupportInternat
					// // // multitag "#2"
						// // // "Many programs support international settings for numbers, currencies, times, and dates. Set the locale in order to use the sta*"
						// // // "$65535[2]"
				// // // StaticText YourLocaleLocationText
					// // // multitag "#3"
						// // // "Your locale (location):"
						// // // "$65535[3]"
				// // // PopupList YourLocaleLocation
					// // // multitag "#1"
						// // // "Your locale (location):"
						// // // "$1030"
				// // // StaticText LanguageSettingsForTheSyst
					// // // multitag "#4"
						// // // "Language settings for the system"
						// // // "$65535[4]"
				// // // StaticText YourSystemIsConfiguredToR1
					// // // multitag "#5"
						// // // "Your system is configured to read and write documents in multiple languages."
						// // // "$65535[5]"
				// // // ListView YourSystemIsConfiguredToR2
					// // // multitag "#1"
						// // // "Your system is configured to read and write documents in multiple languages."
						// // // "$1035"
					// // // Header Header1
						// // // multitag "#1"
							// // // "$0"
				// // // PushButton SetDefault
					// // // multitag "#1"
						// // // "Set default"
						// // // "$1036"
				// // // PushButton Advanced
					// // // multitag "#2"
						// // // "Advanced"
						// // // "$1037"
			// // // PushButton OK
				// // // multitag "#1"
					// // // "OK"
					// // // "$1"
			// // // PushButton Cancel
				// // // multitag "#2"
					// // // "Cancel"
					// // // "$2"
			// // // PushButton Apply
				// // // multitag "#3"
					// // // "Apply"
					// // // "$12321"
			// // // PageList PageList1
				// // // multitag "#1"
					// // // "$12320"
		// 
		// //additional tab declarations added
		// DialogBox RegionalSettingsCopyingF
			// tag "Regional Settings -- Copying Files..."
			// //parent __RegionalSettingsProperties
			// CustomWin SysAnimate321
				// tag "[SysAnimate32]#1"
			// StaticText DI386KbdtuqDll1Text
				// tag "D:\i386\kbdtuq.dll[1]"
			// StaticText DI386KbdtuqDll2Text
				// tag "D:\i386\kbdtuq.dll[2]"
			// CustomWin Msctls_progress321
				// tag "[msctls_progress32]#1"
			// PushButton Cancel
				// tag "Cancel"
			// 
		// DialogBox FilesNeeded
			// STRING sLocation
			// VOID CheckAndDismiss()
				// if bExists
					// //STRING sLocation = AutomationINI.WindowsInstalls.@("{GetGuiType()}").sValue
						// //from system test .ini file which is TBD as of 8/6/01
					// CopyFilesFrom.SetText(sLocation)
					// OK.Click()
			// 
			// tag "Files Needed"
			// //parent RegionalSettingsCopyingF
			// PushButton OK
				// tag "OK"
			// PushButton Cancel
				// tag "Cancel"
			// StaticText CopyFilesFromText
				// tag "Copy files from:"
			// ComboBox CopyFilesFrom
				// tag "Copy files from:"
			// PushButton SkipFile
				// tag "Skip File"
			// PushButton Browse
				// tag "Browse"
			// CustomWin Icon1
				// tag "[Icon]#1"
			// StaticText TheFileKbdurDllOnWindow
				// tag "The file 'kbdur.dll' on Windows NT Workstation CD-ROM is needed."
			// StaticText TypeThePathWhereTheFileI
				// tag "Type the path where the file is located, and then click OK."
			// 
		// 
	// THESE TWO ARE PLACEHOLDERS!
			}
		}
	}
	msw9x private WINDOW DialogBox __RegionalSettingsProperties
	{
		
		//launch the windows "regional settings" window from the control panel
		STRING sWinCmd = "";
		
		VOID Invoke ()
		{
			raise LIBERROR_FEATURE_NOT_YET_IMPLEMENTED, "*** Error: LIBERROR_FEATURE_NOT_YET_IMPLEMENTED in {this}, cDATE support for Win9x not yet implemented. Contact the author.";
			if (!bExists)
			{
				APP_Start(sWinCmd);
			}
			SetActive ();
		
		}
		ANYTYPE SelectLocale (STRING sNewLocale)
		{
			//change locale
			Invoke ();
			STRING sPresentLocale =this.ExtractPresentLocale (TRUE);
			__RegionalSettingsProperties.PageList1.Select ("General");
			
			//check to see if new locale equals present setting, if so, "Apply" button is inactive!
			if (sPresentLocale != sNewLocale)
			{
				General.YourLocaleLocation.Select(sNewLocale);
			
			}
			LIST OF ANYTYPE result = {"",""};
			
			result[1] = ExtractShortDateFormat (TRUE);
			result[2] = ExtractLongDateFormat (TRUE);
			
			if bExists
			{
				OK.Click();
			
			}
			return result;
		
		}
		STRING ExtractPresentLocale (BOOLEAN fLeaveOpen optional)
		{
			if fLeaveOpen == NULL
			{
				fLeaveOpen = FALSE;
			//read present locale
			}
			Invoke ();
			__RegionalSettingsProperties.PageList1.Select ("General");
			//__RegionalSettingsProperties.RegionalSettings.SetActive ()
			STRING sPresentLocale = General.YourLocaleLocation.GetSelText ();
			if ! fLeaveOpen
			{
				OK.Click();
			}
			return sPresentLocale;
			
		}
		STRING ExtractShortDateFormat (BOOLEAN fLeaveOpen optional)
		{
			if fLeaveOpen == NULL
			{
				fLeaveOpen = FALSE;
			}
			Invoke ();
			__RegionalSettingsProperties.PageList1.Select ("Date");
			STRING sShortDateFormat = General.xDate.ShortDateStyle.GetSelText();
			if ! fLeaveOpen
			{
				OK.Click();
			//print ("sShortDateFormat = {sShortDateFormat}")
			}
			return sShortDateFormat;
			
		}
		STRING ExtractLongDateFormat (BOOLEAN fLeaveOpen optional)
		{
			if fLeaveOpen == NULL
			{
				fLeaveOpen = FALSE;
			}
			Invoke ();
			__RegionalSettingsProperties.PageList1.Select ("Date");
			STRING sLongDateFormat = General.xDate.LongDateStyle.GetSelText();
			if ! fLeaveOpen
			{
				OK.Click();
			//print ("sLongDateFormat = {sLongDateFormat}")
			}
			return sLongDateFormat;
		
		//expand for window declarations
			tag "Regional Options";
			DialogBox General
			{
				multitag "General"
				{
					"$0"
				}
				StaticText SettingsForTheCurrentUserT
				{
					tag "$65535[1]";
				}
				StaticText ManyProgramsSupportInternat
				{
					tag "$65535[2]";
				}
				StaticText YourLocaleLocationText
				{
					tag "$65535[3]";
				}
				PopupList YourLocaleLocation
				{
					tag "$1030";
				}
				StaticText LanguageSettingsForTheSyst
				{
					tag "$65535[4]";
				}
				StaticText YourSystemIsConfiguredToR1
				{
					tag "$65535[5]";
				}
				ListView YourSystemIsConfiguredToR2
				{
					tag "$1035";
					Header Header1
					{
						tag "$0";
					}
				}
				PushButton SetDefault
				{
					tag "$1036";
				}
				PushButton Advanced
				{
					tag "$1037";
				}
			}
			PushButton OK
			{
				tag "$1";
			}
			PushButton Cancel
			{
				tag "$2";
			}
			PushButton Apply
			{
				tag "$12321";
			}
			PageList PageList1
			{
				tag "$12320";
			}
			DialogBox xDate
			{
				multitag "Date"
				{
					"$0"
				}
				StaticText ShortDateSampleText
				{
					tag "Short date sample:";
				}
				TextField ShortDateSample
				{
					tag "Short date sample:";
				}
				StaticText ShortDateStyleText
				{
					tag "Short date style:";
				}
				ComboBox ShortDateStyle
				{
					tag "Short date*";
				}
				StaticText DateSeparatorText
				{
					tag "Date separator:";
				}
				ComboBox DateSeparator
				{
					tag "Date separator:";
				}
				StaticText CalendarTypeText
				{
					tag "Calendar type:";
				}
				PopupList CalendarType
				{
					tag "Calendar type:";
				}
				StaticText LongDateSampleText
				{
					tag "Long date sample:";
				}
				TextField LongDateSample
				{
					tag "Long date sample:";
				}
				StaticText LongDateStyleText
				{
					tag "Long date style:";
				}
				ComboBox LongDateStyle
				{
					tag "Long date*";
				}
				StaticText ShortDateText
				{
					tag "Short date";
				}
				StaticText LongDateText
				{
					tag "Long date";
			
		
		//additional tab declarations added
				}
			}
		}
		DialogBox RegionalSettingsCopyingF
		{
			tag "Regional Settings -- Copying Files...";
			//parent __RegionalSettingsProperties
			CustomWin SysAnimate321
			{
				tag "[SysAnimate32]#1";
			}
			StaticText DI386KbdtuqDll1Text
			{
				tag "D:\i386\kbdtuq.dll[1]";
			}
			StaticText DI386KbdtuqDll2Text
			{
				tag "D:\i386\kbdtuq.dll[2]";
			}
			CustomWin Msctls_progress321
			{
				tag "[msctls_progress32]#1";
			}
			PushButton Cancel
			{
				tag "Cancel";
			
			}
		}
		DialogBox FilesNeeded
		{
			STRING sLocation;
			VOID CheckAndDismiss()
			{
				if bExists
				{
					//STRING sLocation = AutomationINI.WindowsInstalls.@("{GetGuiType()}").sValue
					{
						//from system test .ini file which is TBD as of 8/6/01
					}
					CopyFilesFrom.SetText(sLocation);
					OK.Click();
			
				}
			}
			tag "Files Needed";
			//parent RegionalSettingsCopyingF
			PushButton OK
			{
				tag "OK";
			}
			PushButton Cancel
			{
				tag "Cancel";
			}
			StaticText CopyFilesFromText
			{
				tag "Copy files from:";
			}
			ComboBox CopyFilesFrom
			{
				tag "Copy files from:";
			}
			PushButton SkipFile
			{
				tag "Skip File";
			}
			PushButton Browse
			{
				tag "Browse";
			}
			CustomWin Icon1
			{
				tag "[Icon]#1";
			}
			StaticText TheFileKbdurDllOnWindow
			{
				tag "The file 'kbdur.dll' on Windows NT Workstation CD-ROM is needed.";
			}
			StaticText TypeThePathWhereTheFileI
			{
				tag "Type the path where the file is located, and then click OK.";
			
		
	// mswxp private WINDOW DialogBox __RegionalSettingsProperties
		// 
		// //launch the windows "regional settings" window from the control panel
		// STRING sWinCmd = "rundll32 shell32.dll,Control_RunDLL intl.cpl"
		// 
		// VOID Invoke ()
			// raise LIBERROR_FEATURE_NOT_YET_IMPLEMENTED, "*** Error: LIBERROR_FEATURE_NOT_YET_IMPLEMENTED in {this}, cDATE support for WinXP not yet implemented. Contact the author."
			// if (!bExists)
				// APP_Start(sWinCmd)
			// SetActive ()
		// 
		// ANYTYPE SelectLocale (STRING sNewLocale)
			// //change locale
			// Invoke ()
			// STRING sPresentLocale =this.ExtractPresentLocale (TRUE)
			// __RegionalSettingsProperties.PageList1.Select ("General")
			// 
			// //check to see if new locale equals present setting, if so, "Apply" button is inactive!
			// if (sPresentLocale != sNewLocale)
				// General.YourLocaleLocation.Select(sNewLocale)
			// 
			// LIST OF ANYTYPE result = {"",""}
			// 
			// result[1] = ExtractShortDateFormat (TRUE)
			// result[2] = ExtractLongDateFormat (TRUE)
			// 
			// if bExists
				// OK.Click()
			// 
			// return result
		// 
		// STRING ExtractPresentLocale (BOOLEAN fLeaveOpen optional)
			// if fLeaveOpen == NULL
				// fLeaveOpen = FALSE
			// //read present locale
			// Invoke ()
			// __RegionalSettingsProperties.PageList1.Select ("General")
			// //__RegionalSettingsProperties.RegionalSettings.SetActive ()
			// STRING sPresentLocale = General.YourLocaleLocation.GetSelText ()
			// if ! fLeaveOpen
				// OK.Click()
			// return sPresentLocale
			// 
		// STRING ExtractShortDateFormat (BOOLEAN fLeaveOpen optional)
			// if fLeaveOpen == NULL
				// fLeaveOpen = FALSE
			// Invoke ()
			// __RegionalSettingsProperties.PageList1.Select ("Date")
			// STRING sShortDateFormat = General.xDate.ShortDateStyle.GetSelText()
			// if ! fLeaveOpen
				// OK.Click()
			// //print ("sShortDateFormat = {sShortDateFormat}")
			// return sShortDateFormat
			// 
		// STRING ExtractLongDateFormat (BOOLEAN fLeaveOpen optional)
			// if fLeaveOpen == NULL
				// fLeaveOpen = FALSE
			// Invoke ()
			// __RegionalSettingsProperties.PageList1.Select ("Date")
			// STRING sLongDateFormat = General.xDate.LongDateStyle.GetSelText()
			// if ! fLeaveOpen
				// OK.Click()
			// //print ("sLongDateFormat = {sLongDateFormat}")
			// return sLongDateFormat
		// 
		// //expand for window declarations
			// tag "Regional Options"
			// DialogBox General
				// multitag "General"
					// "$0"
				// StaticText SettingsForTheCurrentUserT
					// tag "$65535[1]"
				// StaticText ManyProgramsSupportInternat
					// tag "$65535[2]"
				// StaticText YourLocaleLocationText
					// tag "$65535[3]"
				// PopupList YourLocaleLocation
					// tag "$1030"
				// StaticText LanguageSettingsForTheSyst
					// tag "$65535[4]"
				// StaticText YourSystemIsConfiguredToR1
					// tag "$65535[5]"
				// ListView YourSystemIsConfiguredToR2
					// tag "$1035"
					// Header Header1
						// tag "$0"
				// PushButton SetDefault
					// tag "$1036"
				// PushButton Advanced
					// tag "$1037"
			// PushButton OK
				// tag "$1"
			// PushButton Cancel
				// tag "$2"
			// PushButton Apply
				// tag "$12321"
			// PageList PageList1
				// tag "$12320"
			// DialogBox xDate
				// multitag "Date"
					// "$0"
				// StaticText ShortDateSampleText
					// tag "Short date sample:"
				// TextField ShortDateSample
					// tag "Short date sample:"
				// StaticText ShortDateStyleText
					// tag "Short date style:"
				// ComboBox ShortDateStyle
					// tag "Short date*"
				// StaticText DateSeparatorText
					// tag "Date separator:"
				// ComboBox DateSeparator
					// tag "Date separator:"
				// StaticText CalendarTypeText
					// tag "Calendar type:"
				// PopupList CalendarType
					// tag "Calendar type:"
				// StaticText LongDateSampleText
					// tag "Long date sample:"
				// TextField LongDateSample
					// tag "Long date sample:"
				// StaticText LongDateStyleText
					// tag "Long date style:"
				// ComboBox LongDateStyle
					// tag "Long date*"
				// StaticText ShortDateText
					// tag "Short date"
				// StaticText LongDateText
					// tag "Long date"
			// 
		// 
		// //additional tab declarations added
		// DialogBox RegionalSettingsCopyingF
			// tag "Regional Settings -- Copying Files..."
			// //parent __RegionalSettingsProperties
			// CustomWin SysAnimate321
				// tag "[SysAnimate32]#1"
			// StaticText DI386KbdtuqDll1Text
				// tag "D:\i386\kbdtuq.dll[1]"
			// StaticText DI386KbdtuqDll2Text
				// tag "D:\i386\kbdtuq.dll[2]"
			// CustomWin Msctls_progress321
				// tag "[msctls_progress32]#1"
			// PushButton Cancel
				// tag "Cancel"
			// 
		// DialogBox FilesNeeded
			// STRING sLocation
			// VOID CheckAndDismiss()
				// if bExists
					// //STRING sLocation = AutomationINI.WindowsInstalls.@("{GetGuiType()}").sValue
						// //from system test .ini file which is TBD as of 8/6/01
					// CopyFilesFrom.SetText(sLocation)
					// OK.Click()
			// 
			// tag "Files Needed"
			// //parent RegionalSettingsCopyingF
			// PushButton OK
				// tag "OK"
			// PushButton Cancel
				// tag "Cancel"
			// StaticText CopyFilesFromText
				// tag "Copy files from:"
			// ComboBox CopyFilesFrom
				// tag "Copy files from:"
			// PushButton SkipFile
				// tag "Skip File"
			// PushButton Browse
				// tag "Browse"
			// CustomWin Icon1
				// tag "[Icon]#1"
			// StaticText TheFileKbdurDllOnWindow
				// tag "The file 'kbdur.dll' on Windows NT Workstation CD-ROM is needed."
			// StaticText TypeThePathWhereTheFileI
				// tag "Type the path where the file is located, and then click OK."
			// 
		// 
	
	
	
	
	

// Expand for Abstract Object Library - Basic disk classes 			(cDISKENTITY, cDIR, cFILE, cTEXTFILE, cOPENFILE)
	
	////////////////////////////////////////////////////////////////////////////
	// cDISKENTITY	Virtual base class for cDIR and cFILE
	//
	// Purpose: 	Encapsulates functionality common to both files and directories
	//
	// Expand this for documentation
		//
		// inherits: 	cBASE
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		//		fUseRawName					rw: This flag is persistant across all
		//									instances of this class. When the flag
		//									is TRUE, the raw dir/file name as provided
		//									will be used. But if it's FALSE, and you're
		//									running on any version of MS Windows,
		//									illegal characters will be replaced with
		//									an underscore, and the STRING will be
		//									converted to all lowercase.
		//		sMungedName					ro: Returns the file or directory name
		//									based on the setting of the fUseRawName
		//		sDrivePart					ro: returns the drive letter of the
		//									sMungedName on MS Windows.
		//		sDirectoryPart				Attempts to return the directory part
		//									of the name.
		//		sNamePart					ro: the last segment of the directory
		//									structure, exceluing anything after a
		//									period.
		//		sExtensionPart				ro: this part is anything after the last
		//									period.
		//		bIsDir						ro: TRUE if this is a directory
		//		iSize						ro: Integer size in bytes of the file/dir
		//		dtCreated					ro: DATETIME of when the file/dir was
		//									created (on OS's that support this
		//									function).
		//		dtModified					ro: as above, except it's the DATETIME
		//									when the file was last modified.
		//		bReadOnly					ro: TRUE if the file/dir is marked READ ONLY
		//		bHidden						ro: TRUE if the file/dir is marked HIDDEN
		//		bSystem						ro: TRUE if the file/dir is marked SYSTEM
		//		bArchive					ro: TRUE if the file/dir ARCHIVE bit is set
		//
		// PUBLIC MEMBERS - METHODS:
		//
		//		MungedName(s)				For this, the s argument is optional. If it's
		//									NOT specified, this method returns the
		//									munged name of the file/dir specified for
		//									this object, and subject to the state of
		//									fUseRawName. If the optional argument IS
		//									specified, then it returns the munged form
		//									of the argument, again subject to fUseRawName.
		//		GetDrivePart()				Returns the drive letter of the sMungedName
		//									on MS Windows.
		//		GetDirectoryPart()			Attempts to return the directory part
		//									of the name.
		//		GetNamePart()				the last segment of the directory
		//									structure, exceluing anything after a
		//									period.
		//		GetExtensionPart()			this part is anything after the last
		//									period.
		//		GetSize()					Integer size in bytes of the file/dir
		//		GetAttributes()				Integer of the attributes byte from the
		//									FILEINFO record Silk can return on a file.
		//		GetCreationDateTime()		DATETIME of when the file/dir was
		//									created (on OS's that support this
		//									function).
		//		GetModificationDateTime()	As above, except it's the DATETIME
		//									when the file was last modified.
		//
		//
	////////////////////////////////////////////////////////////////////////////
			}
		}
	}
	winclass cDISKENTITY : cBASE
	{
		
		property 	fUseRawName			// static item, shared between all members of the class
		{
			BOOLEAN Get()
			{
				BOOLEAN result = TRUE;
				if this.__PersistantRawNameFlag.Value == NULL
				{
					this.__PersistantRawNameFlag.SetValueAtClass(FALSE,cDISKENTITY);
					result = FALSE;
				}
				else
				{
					result = this.__PersistantRawNameFlag.Value;
				}
				return result;
			}
			VOID	Set(BOOLEAN NewValue)
			{
				this.__PersistantRawNameFlag.SetValueAtClass(NewValue,cDISKENTITY);
			}
		}
		property 	sMungedName
		{
			STRING Get()
			{
				return this.MungedName();
			}
		}
		property	sDrivePart
		{
			STRING Get()
			{
				return this.GetDrivePart();
			}
		}
		property	sDirectoryPart
		{
			STRING Get()
			{
				return this.GetDirectoryPart();
			
			}
		}
		property	sNamePart
		{
			STRING Get()
			{
				return this.GetNamePart();
			}
		}
		property	sExtensionPart
		{
			STRING Get()
			{
				return this.GetExtensionPart();
			}
		}
		property	bIsDir
		{
			BOOLEAN Get()
			{
				this.__Populate();
				return this.__bIsDir;
			}
		}
		property	iSize
		{
			INTEGER Get()
			{
				return this.GetSize();
			}
		}
		property	dtCreated
		{
			DATETIME Get()
			{
				return this.GetCreationDateTime();
			}
		}
		property	dtModified
		{
			DATETIME Get()
			{
				return this.GetModificationDateTime();
		
			}
		}
		property	Sep
		{
			STRING Get()
			{
				return cSystem.sDirSeparator;
			}
		}
		property	sFullName
		{
			STRING Get()
			{
				__Populate();
				return this.sDrivePart+":"+Sep+this.sDirectoryPart+Sep+this.sNamePart+"."+this.sExtensionPart;
			}
		}
		property	sFullPath
		{
			STRING Get()
			{
				__Populate();
				return this.sDrivePart+":"+Sep+this.sDirectoryPart+Sep;
			}
		}
		property 	lsDirectoryList
		{
			LIST OF STRING Get()
			{
				__Populate();
				STRING sIn = sDrivePart+Sep+sDirectoryPart;
				LIST OF STRING lsResult = MakeListFromString(sIn,Sep);
				INTEGER i;
				for i=ListCount(lsResult) to 1 step -1
				{
					if trim(lsResult[i])==""
					{
						ListDelete(lsResult,i);
					}
				}
				return lsResult;
			}
		}
		property	sLastDirPart
		{
			STRING Get()
			{
				return GetLastMember(this.lsDirectoryList);
		
			}
		}
		property 	bReadOnly
		{
			BOOLEAN Get()
			{
				this.__Populate();
				return this.__bReadOnly;
			}
			Set(BOOLEAN fNew)
			{
				this.__SetAttribs(fNew,NULL,NULL,NULL);
			}
		}
		property 	bHidden
		{
			BOOLEAN Get()
			{
				this.__Populate();
				return this.__bHidden;
			}
			Set(BOOLEAN fNew)
			{
				this.__SetAttribs(NULL,fNew,NULL,NULL);
			}
		}
		property 	bSystem
		{
			BOOLEAN Get()
			{
				this.__Populate();
				return this.__bSystem;
			}
			Set(BOOLEAN fNew)
			{
				this.__SetAttribs(NULL,NULL,fNew,NULL);
			}
		}
		property 	bArchive
		{
			BOOLEAN Get()
			{
				this.__Populate();
				return this.__bArchive;
			}
			Set(BOOLEAN fNew)
			{
				this.__SetAttribs(NULL,NULL,NULL,fNew);
		
			}
		}
		STRING 		MungedName(STRING sIncoming optional)
		{
			if sIncoming!=NULL
			{
				this.@(this.__sObjectFileNamePointer)=sIncoming;
			}
			return this.__SafeName(FALSE);
		}
		STRING		GetDrivePart()
		{
			this.__Populate();
			return this.__sDrive;
		}
		STRING		GetDirectoryPart()
		{
			this.__Populate();
			return this.__sDir;
		}
		STRING		GetNamePart()
		{
			this.__Populate();
			return this.__sName;
		}
		STRING		GetExtensionPart()
		{
			this.__Populate();
			return this.__sExt;
		//Getting the subdirectory works backwards from the file name. Use negative numbers
		}
		STRING		GetSubDirectory(INTEGER iSection)
		{
			this.__Populate();
			LIST OF STRING lsSubDirs = this.lsDirectoryList;
			INTEGER iListCount = ListCount(this.lsDirectoryList) + 1;
			INTEGER iPart = 0;
			if iSection < 0
			{
				iSection = iListCount + iSection;
			}
			return lsSubDirs[iSection];
		}
		INTEGER		GetSize()
		{
			this.__Populate();
			return this.__iSize;
		}
		INTEGER		GetAttributes()
		{
			this.__Populate();
			return this.__iAttributes;
		}
		DATETIME	GetCreationDateTime()
		{
			this.__Populate();
			return this.__dtCreationTime;
		}
		DATETIME	GetModificationDateTime()
		{
			this.__Populate();
			return this.__dtLastModifyTime;
		
		}
		VOID		SetAttribs(BOOLEAN fInReadonly NULL, BOOLEAN fInHidden NULL, BOOLEAN fInSystem NULL, BOOLEAN fInArchive NULL)
		{
			this.__SetAttribs(fInReadonly,fInHidden,fInSystem,fInArchive);
		
		}
		const dcInheritsFrom = cBASE;
		const lsClassFieldList    = {};
		const lsClassPropertyList = 
		{
			'fUseRawName',
			'sMungedName',
			'sDrivePart',
			'sDirectoryPart',
			'sNamePart',
			'sExtensionPart',
			'bIsDir',
			'iSize',
			'dtCreated',
			'dtModified',
			'bReadOnly',
			'bHidden',
			'bSystem',
			'bArchive'
		};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			msw __SetAttribs(BOOLEAN fInReadonly NULL, BOOLEAN fInHidden NULL, BOOLEAN fInSystem NULL, BOOLEAN fInArchive NULL)
			{
				
				OBJECT Attrib = cEXEFILE("attrib.exe");
				
				STRING sPassArgs = this.sFileName;
				
				if fInReadonly != NULL
				{
					if (! this.bExists) || (this.bReadOnly != fInReadonly)
					{
						//sPassArgs="r{iff(fInReadonly,"+","-")} "+sPassArgs
						sPassArgs="{iff(fInReadonly,"+","-")}r "+ chr(34) + sPassArgs + chr(34);
				
					}
				}
				if fInHidden != NULL
				{
					if (! this.bExists) || (this.bHidden != fInHidden)
					{
						sPassArgs="h{iff(fInHidden,"+","-")} "+sPassArgs;
				
					}
				}
				if fInSystem != NULL
				{
					if (! this.bExists) || (this.bSystem != fInSystem)
					{
						sPassArgs="s{iff(fInSystem,"+","-")} "+sPassArgs;
				
					}
				}
				if fInArchive != NULL
				{
					if (! this.bExists) || (this.bArchive != fInArchive)
					{
						sPassArgs="a{iff(fInArchive,"+","-")} "+sPassArgs;
				
					}
				}
				if sPassArgs != this.__FullPathAndName
				{
					Attrib.RunAndWait(sPassArgs);
				
			
				}
			}
			const lsPrivateClassFieldList    = 
			{
				'__PersistantRawNameFlag',
				'__sDrive',
				'__sDir',
				'__sName',
				'__sExt',
				'__bIsDir',
				'__iSize',
				'__iSize',
				'__iAttributes',
				'__dtLastModifyTime',
				'__dtCreationTime',
				'__bArchive',
				'__bHidden',
				'__bReadOnly',
				'__bSystem',
				'__bTemporary',
				'__bNormal'
			};
			const lsPrivateClassPropertyList = {};
			
			cSTATIC		__PersistantRawNameFlag {}
			
			property __FullPathAndName
			{
				STRING Get()
				{
					this.__Populate();
					STRING sResult="";
					sResult=sResult+__sDrive;
					sResult=sResult+":"+Sep;
					sResult=sResult+__sDir;
					sResult=sResult+":"+Sep;
					sResult=sResult+__sName;
					sResult=sResult+".";
					sResult=sResult+__sExt;
					return sResult;
			
				}
			}
			STRING 		__sDrive;
			STRING 		__sDir;
			STRING 		__sName;
			STRING 		__sExt;
			BOOLEAN		__bIsDir;
			INTEGER		__iSize;
			INTEGER		__iAttributes;
			DATETIME	__dtLastModifyTime;
			DATETIME	__dtCreationTime;
			BOOLEAN		__bArchive;
			BOOLEAN		__bHidden;
			BOOLEAN		__bReadOnly;
			BOOLEAN		__bSystem;
			BOOLEAN		__bTemporary;
			BOOLEAN		__bNormal;
			
			STRING 		__sObjectFileNamePointer = "sFileName";
			
			private STRING 		__SafeName(BOOLEAN fRaw optional)
			{
				if fRaw==NULL
				{
					fRaw=this.fUseRawName;
				
				// first off, get the file name sorted out
				
				// Is the pointer set?
				}
				if ! IsSet(this.__sObjectFileNamePointer)
				{
					this.__sObjectFileNamePointer = "sFileName";
				
				// is the filename/dirname set?
				}
				do
				{
					if ! IsSet(this.@(this.__sObjectFileNamePointer))
					{
						@(this.__sObjectFileNamePointer)="";
					}
				}
				except
				{
					// this condition should occur ONLY if the sFileName/sDirName
					// is a property. In which case, we can ignore it. 
					// You can't IsSet on a property, but it may be,
					// depending on the user, that it's either a string
					// or a property. 
					ExceptClear();
				
				// ok, so now it's set, if it's empty and passedvalue isn't, populate it
				// is the filename/dirname set?
				}
				do
				{
					if (@(this.__sObjectFileNamePointer)=="") && (this.sPassedValue != "")
					{
						@(this.__sObjectFileNamePointer)=sPassedValue;
					}
				}
				except
				{
					// this condition should occur ONLY if the sFileName/sDirName
					// is a property. In which case, we can ignore it. 
					// You can't IsSet on a property, but it may be,
					// depending on the user, that it's either a string
					// or a property.
					ExceptClear()
					 ;
				
				}
				STRING sResult=@(this.__sObjectFileNamePointer);
				
				// next, sort out the munged name if appropriate
				if ! fRaw
				{
					STRING sName = sResult;
					
					if sContains("{GetGuiType()}","Microsoft Windows")
					{
						if ! this.fUseRawName
						{
							sName = lower(sName);
							STRING sBadCharList = '/*?<>|';
							INTEGER i;
							for i = 1 to len(sName)
							{
								if sContains(sBadCharList, sName[i])
								{
									sName[i]="_";
					
								}
							}
						}
					}
					if GetLastChar(sName) == cSystem.sDirSeparator
					{
						sName = GetAllButLast(sName);
					
					}
					if this.IsOfClass(cDIR)
					{
						sName=sName+cSystem.sDirSeparator;
					
					}
					INTEGER iPos;
					STRING s1 = sName[1];
					sName[1]="";
					while sContains(sName,"\\")
					{
						iPos=StrPos("\\",sName);
						sName[iPos]="";
					}
					sName=s1+sName;
					
					sResult=sName;
				
				}
				return sResult;
			}
			private VOID		__Populate()
			{
				// this is a speed optimization, sMungedName isn't all that quick
				STRING sLocalMungedName=this.sMungedName;
				
				this.__sDrive = "";
				this.__sDrive = "";
				this.__sDir = "";
				this.__sName = "";
				this.__sExt = "";
				
				// first the drive...
				if sContains("{GetGuiType()}","Microsoft Windows")
				{
					if sLocalMungedName[2] == ":"
					{
						this.__sDrive = sLocalMungedName[1];
					}
					else
					{
						this.__sDrive = SYS_GetDrive();
				
				// next the directory
					}
				}
				this.__sDir = SYS_GetDir();
				if sContains(sLocalMungedName, cSystem.sDirSeparator)
				{
					if this.IsOfClass(cDIR)
					{
						this.__sDir = sLocalMungedName;
					}
					else
					{
						this.__sDir = GetLeftOf(sLocalMungedName, cSystem.sDirSeparator)+cSystem.sDirSeparator;
					}
				}
				if this.__sDir[2]==':'
				{
					this.__sDir[1]='';
					this.__sDir[1]='';
				
				// now the file name
				}
				this.__sName = sLocalMungedName;
				if sContains(this.__sName, cSystem.sDirSeparator)
				{
					this.__sName = GetRightOf(this.__sName, cSystem.sDirSeparator);
				}
				if sContains(this.__sName, '.')
				{
					this.__sName = GetLeftOf(this.__sName, '.');
					// and the extention...
					this.__sExt = GetRightOf(sLocalMungedName, ".");
				
				// attributes as a record     FILEINFO = sName, bIsDir, iSize, iAttributes, dtLastModifyTime, dtCreationTime
				}
				FILEINFO fiResult = {"",FALSE,0,0,NULL,NULL};
				
				if this.bExists
				{
					STRING sDir = this.__sDir;
					msw sDir = iff(sContains(sLocalMungedName,':'),this.__sDrive+':'+sDir,sDir);
					STRING sJustTheFileName = this.__sName+iff(this.__sExt != '','.'+this.__sExt,'');
					LIST of FILEINFO lfData = SYS_GetDirContents(sDir);
					ANYTYPE item;
					for each item in lfData
					{
						if sContains("{GetGuiType()}","Microsoft Windows")
						{
							item.sName = Lower(item.sName);
							sJustTheFileName = Lower(sJustTheFileName);
						}
						if (item.sName == sJustTheFileName) && (! item.bIsDir)
						{
							fiResult = item;
							break;
					
						}
					}
					this.__bIsDir 			= fiResult.bIsDir;
					this.__iSize  			= fiResult.iSize;
					this.__dtLastModifyTime	= fiResult.dtLastModifyTime;
					this.__dtCreationTime	= fiResult.dtCreationTime;
					
					// now make that record into booleans...
					this.__bArchive 	= MakeBool(fiResult.iAttributes & FILE_ATTRIBUTE_ARCHIVE); 	// 1
					this.__bHidden 		= MakeBool(fiResult.iAttributes & FILE_ATTRIBUTE_HIDDEN);	// 3
					this.__bNormal 		= MakeBool(fiResult.iAttributes & FILE_ATTRIBUTE_NORMAL);	// 4
					this.__bReadOnly	= MakeBool(fiResult.iAttributes & FILE_ATTRIBUTE_READONLY);	// 5
					this.__bSystem 		= MakeBool(fiResult.iAttributes & FILE_ATTRIBUTE_SYSTEM);	// 6
					this.__bTemporary 	= MakeBool(fiResult.iAttributes & FILE_ATTRIBUTE_TEMPORARY);	// 7
					
					// and now, all the private data members are populated!
					
				
				
			
		////////////////////////////////////////////////////////////////////////////
		
		
	// cDISKENTITY is tested in the cFILE and cDIR suites
				}
			}
		}
	}
	INTEGER iFileInitCounter=0;
	
	
	////////////////////////////////////////////////////////////////////////////
	// cDIR 		Represents a directory
	//
	// Purpose: 	Represents a directory
	//
	// Expand this for documentation
		//
		// inherits: 	cDISKENTITY
		//
		// PUBLIC MEMBERS - DATA:
		//
		//		sDirName				String of the name of this directory.
		//								When doing dynamic instantiation, this
		//								will be set if you pass in a value, like
		//								so: OBJECT a = cDIR('C:\DOCS')
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		// 		bExists					ro: TRUE if the directory exists
		//		lsFileNames				ro: list of STRING of the names of the entries
		//								in the directory list in memory.
		//		loFiles					ro: List of cFILEs and cDIRs for all the
		//								entries in the directory list in memory.
		//
		// PUBLIC MEMBERS - METHODS:
		//
		//		Create()				Creates the directory if it doesn't already
		//								exist.
		//		Delete()				Deletes this directory and all it's contents.
		//		MakeWorkingDir()		Make this the current working directory for
		//								the script.
		//		CopyTo(f)				Takes a FILEREF. Copies the contents of this
		//								directory to the place specified in f.
		//		MoveTo(f)				Takes a FILEREF. Moves the contents of this
		//								directory to the place specified in f.
		//		CopyFrom(f)				Takes a FILEREF. Copies the contents of the
		//								remote directory specified in f to this.
		//		MoveFrom(f)				Takes a FILEREF. Moves the contents of the
		//								remote directory specified in f to this.
		//
		// NOTES:
		//
		// The way this object works is to maintain a list in memory of the entries
		// in the directory. In order to populate the list the first time, you would
		// call Read(). Subsiquently, you would use Update(). Update() returns a
		// list of new entries since the last read. You can use this to periodically
		// poll the directory for new entries.
		//
	////////////////////////////////////////////////////////////////////////////
	INTEGER __cDIR_DebugCycleCounter = 0;
	BOOLEAN DebugCheck(INTEGER iCycleCount, STRING sMessage optional)
	{
		if sMessage==NULL
		{
			sMessage="";
		}
		if __cDIR_DebugCycleCounter > iCycleCount
		{
			print("__cDIR_DebugCycleCounter = {__cDIR_DebugCycleCounter} {sMessage}");
		}
		__cDIR_DebugCycleCounter++;
		return (__cDIR_DebugCycleCounter > iCycleCount);
	
	}
	winclass cDIR : cDISKENTITY
	{
		
		//STRING sDirName=this.sPassedValue
		{
			// 2004.11.09 AMM: Replaced STRING sDirName with property that would 
			//                 perform assignments in order to try and work around
			// 				   a condition that appears to be a silk bug where the 
			//				   value of sDirName was being lost. 
			//
			//				   The user can still override the property with 
			//				   	STRING sDirName = "..."
		}
		property sDirName
		{
			STRING Get()
			{
				STRING sResult=this.sPassedValue;
				if this.__UserSpecifiedDirName != NULL
				{
					if this.__UserSpecifiedDirName != ""
					{
						sResult=this.__UserSpecifiedDirName;
					}
				}
				return sResult;
			}
			VOID Set(STRING sIn)
			{
				this.__UserSpecifiedDirName = sIn;
		
		// PROPERTIES
			}
		}
		property bExists 		// Read only
		{
			BOOLEAN Get()
			{
				return this.Exists();
			}
		}
		property lsFileNames 	// Read only
		{
			LIST OF STRING Get()
			{
				return this.__lsFileList;
			}
		}
		property loFiles 		// Read only
		{
			ANYTYPE Get()
			{
				return this.__lfoData;
			}
		}
		property lsPath			// read only
		{
			LIST OF STRING Get()
			{
				return MakeListFromString(this.sDirName,Sep);
			}
		}
		property sName			// Read only
		{
			STRING Get()
			{
				return this.sDirName;
			}
			VOID Set(FILEREF incoming)
			{
				incoming=MakeStringFromFILEREF(incoming);
				this.sDirName=incoming;
		
		// DO ACTIONS ON DIR
			}
		}
		OBJECT 	Create()
		{
			if ! this.bExists
			{
				ANYTYPE item;
				STRING sCurrent="";
				for each item in lsPath
				{
					sCurrent=sCurrent+item+cSystem.sDirSeparator;
					do
					{
						SYS_MakeDir(sCurrent);
					}
					except
					{
						//nada
						ExceptClear();
					}
				}
			}
			return this;
		}
		VOID 	Delete(REAL rTime null optional)						// DANGER: DELETES ALL CONTENTS AND THE DIRECTORY ITSELF
		{
			if this.bExists
			{
				this.DeleteContents(rTime);
				SYS_RemoveDir(this.sMungedName);
			}
		}
		VOID 	MakeWorkingDir()
		{
			SYS_SetDrive(this.sDrivePart);
			SYS_SetDir(this.sDirectoryPart);
		}
		VOID	CopyTo(FILEREF TargetDir)
		{
			this.__DoCopyOrMove(this,TargetDir,FALSE);
		}
		VOID	MoveTo(FILEREF TargetDir)
		{
			this.__DoCopyOrMove(this,TargetDir,TRUE);
		}
		VOID	CopyFrom(FILEREF TargetDir)
		{
			this.__DoCopyOrMove(TargetDir,this,FALSE);
		}
		VOID	MoveFrom(FILEREF TargetDir)
		{
			this.__DoCopyOrMove(TargetDir,this,TRUE);
		
		// ACTIONS ON CONTENTS
		}
		VOID 	DeleteFile(FILEREF File)
		{
			OBJECT MyFile;
			if IsVarString(File)
			{
				MyFile = cFILE(File);
			}
			else
			{
				MyFile = File;
			}
			if ListFind(this.__lfoData, MyFile) != 0
			{
				MyFile.DeleteMe();
			}
		}
		VOID 	DeleteContents(REAL rTime null optional)
		{
			this.Read();
			ANYTYPE item;
			for each item in this.__lfoData
			{
				item.Delete(rTime);
			}
			for each item in this.__ldoData
			{
				item.Delete(rTime);
		
		// STATE READINGS
			}
		}
		BOOLEAN Exists()
		{
			return SYS_DirExists(this.sMungedName);
		}
		BOOLEAN PathContainsName(STRING sLocalName) 	// check if the sMungedName contains sName
		{
			return sContains(this.sMungedName, sLocalName);
		}
		BOOLEAN IsWorkingDir() 					// works correctly only for MSWindows
		{
			STRING sCurrent = lower(this.MungedName(SYS_GetDir()));
			STRING sMine = lower(this.sMungedName);
			return sCurrent == sMine;
		
		// DO ACTIONS ON LIST
		}
		LIST OF OBJECT 	Read()
		{
			if this.bExists
			{
				this.__lfData = SYS_GetDirContents(this.sMungedName);
				this.__MakeFileNameList();
				this.__MakeObjects();
			}
			else
			{
				this.__lfoData = {};
			}
			return __lfoData;
		}
		LIST OF OBJECT 	Update() // returns list of new files since last read
		{
			// returns new files that have
			// appeared since last polled
			
			LIST OF STRING lsOldList = this.__lsFileList;
			this.Read();
			ANYTYPE item;
			LIST OF OBJECT results = {};
			INTEGER ListPos;
			
			for each item in this.__lsFileList
			{
				ListPos = ListFind(lsOldList, item);
				if ListPos == 0
				{
					// NEW ITEM!
					OBJECT NewFile = cTEXTFILE(this.sMungedName+item);
					ListAppend(results, NewFile);
			
				}
			}
			return results;
		}
		BOOLEAN 		FileExistsInList(TEXT File)
		{
			
			STRING sSearchKey;
			if IsVarString(File)
			{
				sSearchKey = File;
			}
			else
			{
				sSearchKey = File.GetNamePart()+'.'+File.GetFileExtensionPart();
			
			}
			INTEGER result = ListFind(this.__lsFileList, lower(sSearchKey));
			return (result > 0);
			
		
		// FindFiles()
		}
		LIST OF OBJECT 	GetAllFiles(STRING sFileExt optional)
		{
			LIST OF OBJECT lsAllFiles;
			LIST OF OBJECT lsAllDirs;
			GetAllContents(lsAllDirs, lsAllFiles);
			if sFileExt == NULL //Get all files
			{
				return lsAllFiles;
			}
			else
			{
				LIST OF OBJECT lsReturnFiles={};
				OBJECT aFile;
				for each aFile in lsAllFiles
				{
					if sContains(aFile.sFileName, sFileExt)
					{
						ListAppend(lsReturnFiles, aFile);
					}
				}
				return lsReturnFiles;
			}
		}
		LIST OF OBJECT	GetAllContents(out LIST OF OBJECT lsAllDirs, out LIST OF OBJECT lsAllFiles, STRING rootDir optional)
		{
			lsAllDirs = {}; // output value
			lsAllFiles = {}; // output value
			
			// Lets figure out the starting place
			LIST OF STRING lsGetDirs = { this.sMungedName };
			if rootDir != NULL
			{
				lsGetDirs = { rootDir };
			
			// Now loop through eveything in this dir
			}
			while ( lsGetDirs!={} )
			{
				STRING sep = cSystem.sDirSeparator;
				
				// Get the contents, and get ready to start looping through them
				FILEINFO aItem;
				STRING sTheDir = lsGetDirs[1];
				LIST OF FILEINFO lsContents = SYS_GetDirContents( sTheDir );
				ListDelete(lsGetDirs,1);
				
				// Do we have ANY entries?
				if lsContents!={}
				{
					
					// Yes! OK, loop through them
					for each aItem in lsContents
					{
						
						if (aItem.bIsDir) // if it's a directory
						{
							
							// verify that it DOES NOT have a trailing "\"
							sDir=sTheDir;
							if sDir != "\"
							{
								if sTheDir[len(sTheDir)]==sep
								{
									sTheDir[len(sTheDir)]="";
								}
								STRING sDir = sTheDir + sep + aItem.sName + sep;
								
								// make it an object, and save that off
								OBJECT aDir = cDIR(sDir);
								ListAppend( lsAllDirs, aDir );
								
								// and add it to the list of directories to scan
								ListAppend( lsGetDirs, sDir );
								
								
							}
						}
						else //is a file
						{
							OBJECT aFile = cFILE(this.MungedName(sTheDir) + sep + aItem.sName);
							ListAppend( lsAllFiles, aFile );
				
				
				
						}
					}
				}
			}
			LIST Result=lsAllDirs;
			ListMerge(Result,lsAllFiles);
			return Result;
		}
		LIST OF OBJECT 	GetAllObjects()
		{
			LIST List1={},List2={},Result={};
			Result=this.GetAllContents(List1,List2);
			return Result;
		}
		BOOLEAN 		IsTypeFileExists(STRING sFileExt, out LIST OF STRING lsFileName optional) //check the type of file exists by file Extension. If yes, will append to lsFileName
		{
			LIST OF FILEINFO lsFileInfo = SYS_GetDirContents(this.sMungedName);
			FILEINFO aFileInfo;
			BOOLEAN bReturn = FALSE;
			for each aFileInfo in lsFileInfo
			{
				if GetRightOf(aFileInfo.sName,".") == GetRightOf(sFileExt, ".")
				{
					ListAppend(lsFileName, aFileInfo.sName);
					bReturn = TRUE;
				}
			}
			return bReturn;
		
		}
		const dcInheritsFrom = cDISKENTITY;
		const lsClassFieldList    = {'sDirName'};
		const lsClassPropertyList = {'bExists','lsFileNames','loFiles','lsPath'}; 	// 'sMungedName' already exists in class inherited from
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {'__lfData','__lsLastEntry','__lsFileList','__lfoData','__lsDirList','__ldoData'};
			const lsPrivateClassPropertyList = {};
			
			LIST OF FILEINFO 	__lfData = {};
			LIST of STRING 		__lsLastEntry = {};
			LIST OF STRING 		__lsFileList = {};
			LIST OF OBJECT 		__lfoData = {};
			LIST OF STRING		__lsDirList = {};
			LIST OF OBJECT 		__ldoData = {};
			
			STRING 				__UserSpecifiedDirName = NULL;
			
			STRING 				__sObjectFileNamePointer = "sDirName";
			
			private VOID 		__MakeFileNameList()
			{
				ANYTYPE item;
				this.__lsFileList = {};
				for each item in this.__lfData
				{
					if ! item.bIsDir
					{
						ListAppend(this.__lsFileList, (item.sName));
					}
					else
					{
						ListAppend(this.__lsDirList, (item.sName));
			
					}
				}
			}
			private VOID 		__MakeObjects()
			{
				STRING item;
				STRING sTemp;
				List of OBJECT FileList = {};
				LIST OF OBJECT DirList = {};
				
				for each item in this.__lsFileList
				{
					sTemp = this.sMungedName + cSystem.sDirSeparator + item;
					OBJECT NewFile = cFILE(sTemp);
					ListAppend(FileList, NewFile);
				}
				this.__lfoData = FileList;
				
				for each item in this.__lsDirList
				{
					sTemp = this.sMungedName + cSystem.sDirSeparator + item;
					OBJECT NewDir = cDIR(sTemp);
					ListAppend(DirList, NewDir);
				}
				this.__ldoData = DirList;
				
			}
			private VOID		__DoCopyOrMove(FILEREF SourceDir, FILEREF TargetDir, BOOLEAN fDeleteSourceFiles)
			{
				if fDeleteSourceFiles == NULL
				{
					fDeleteSourceFiles = FALSE;
				
				}
				if IsVarString(TargetDir)
				{
					TargetDir = cDIR(TargetDir);
				
				}
				SourceDir.Read();
				ANYTYPE item;
				for each item in SourceDir.GetAllObjects()
				{
					if item.IsOfClass(cDIR)					// ARE WE COPYING A SUBDIR?
					{
						OBJECT NewLocalDir = cDIR(this.MungedName()+Sep+GetLastMember(item.lsPath));
						OBJECT NewTargetDir = cDIR(TargetDir.sDirName+Sep+item.sLastDirPart);
						NewTargetDir.Create();
						if fDeleteSourceFiles
						{
							NewLocalDir.MoveTo(NewTargetDir);
						}
						else
						{
							NewLocalDir.CopyTo(NewTargetDir);
						}
					}
					else							// WE ARE COPYING A FILE
					{
						if fDeleteSourceFiles
						{
							item.MoveTo(TargetDir);
						}
						else
						{
							OBJECT TargetFile = cFILE(TargetDir.__SafeName()+Sep+item.sNamePart+"."+item.sExtensionPart);
							item.CopyTo(TargetFile);
				
			
		////////////////////////////////////////////////////////////////////////////
		
		
	
	
	////////////////////////////////////////////////////////////////////////////
	// cFILE 		Virtual base class for file objects
	//
	// Purpose: 	Provides file services to caller
	//
	// Expand this for documentation
		//
		// inherits: 	cBASE
		//
		// PUBLIC MEMBERS - METHODS:
		//
		//		ConvertTo(C)			Returns an instance of the specified class
		//                              which has the same file name. 
		//
		// PUBLIC MEMBERS - SPECIAL:
		//
		// NOTES:
			//
			// If the code is running on any version of Windows, this class will, by
			// default, make the following modifications:
			//
			// 	1) Replace any characters from this list: /*?"<>| with _
			//	2) Convert file name to lower case
			//
			// This conversion, referred to in the documentation above as munging,
			// may not be desirable on Windows boxes interfacing with Java applications,
			// which are case sensitive.
			//
			// If you want the classes to use only the unadulterated file name, you
			// can change the value of the property fUseRawName. Doing this will
			// change all instances of all classes that inherit from cFILE.
			//
			// This change was made so that comparing file names directly could be done
			// rather than explicitly converting them to lower case for the compare.
			// This was done because Windows and most Windows applications are case
			// preserving, but case insensitive. This behavior is not true of Java,
			// because Windows is the only Java platform to behave this way. Java is
			// implemented in a consistant manner across platforms, and so is case
			// sensitive even though the OS isn't.
		//
	////////////////////////////////////////////////////////////////////////////
						}
					}
				}
			}
		}
	}
	winclass cFILE : cDISKENTITY
	{
		STRING sFileName = cBASE::sPassedValue;
		
		property 	bExists
		{
			BOOLEAN Get ()
			{
				return this.Exists();
			}
		}
		property 	Extension
		{
			STRING Get ()
			{
				STRING sExt = "";
				if sContains(sFileName,".")
				{
					sExt=GetRightOf(sFileName,".");
				
				}
				return sExt;
			}
		}
		property	sName
		{
			STRING Get()
			{
				return this.sFileName;
			}
			VOID Set(FILEREF incoming)
			{
				incoming=MakeStringFromFILEREF(incoming);
				this.sFileName=incoming;
		
			}
		}
		OBJECT		AssignFileName(FILEREF incoming)
		{
			this.sFileName = MakeStringFromFILEREF(incoming);
			return this;
		}
		OBJECT		ConvertTo(DATACLASS NewType)
		{
			OBJECT NewObject = @("{NewType}")(this.sFileName);
			NewObject.VerifyIsOfClass(cFILE);
			return NewObject;
		}
		BOOLEAN 	Exists()
		{
			return SYS_FileExists (this.sMungedName);
		}
		VOID 		Delete(REAL rTime optional)
		{
			this.__FileDelete(rTime);
		}
		VOID 		CopyTo (FILEREF Target, BOOLEAN fDeleteTarget optional)
		{
			if IsNull(fDeleteTarget)
			{
				fDeleteTarget = TRUE;
			}
			Target=MakeObjectFromFILEREF(Target);
			if this.bExists
			{
				if fDeleteTarget
				{
					Target.Delete();
				
				}
				cDIR(Target.sDirectoryPart).Create();
				
				do
				{
					SYS_CopyFile (this.sMungedName, Target.sMungedName);
				}
				except
				{
					Log.ExceptPrint();
					Log.LogWarning("CopyTo failed on {this.sRawName}.CopyTo({Target.sFileName})");
					Log.print("Copying from {this.sFileName}");
					reraise;
				}
			}
		}
		VOID		MoveTo (FILEREF Target)
		{
			Target=MakeObjectFromFILEREF(Target,this);
			this.CopyTo(Target,TRUE);
			this.Delete();
			this.sFileName = Target.sFileName;
			
		
		}
		VOID		MakeNameIntoDateStamp(STRING sDir optional, STRING sName optional, STRING sExt optional)
		{
			if sDir==NULL
			{
				sDir="";
			}
			else
			{
				if Right(sDir,1) != Sep
				{
					sDir=sDir+Sep;
				}
			}
			if sName==NULL
			{
				sName="";
			}
			if sExt==NULL
			{
				sExt="";
			}
			OBJECT Dater = cDATE();
			Dater.MakeNow();
			this.sFileName = "{sDir}{Dater.GetFormattedDate("yyyymmdd")}.{sExt}";
			
		
		}
		VOID 		ArchiveToOld()
		{
			OBJECT OldOne=cFILE(this.sFileName+".old");
			if this.bExists
			{
				OldOne.Delete();
				this.MoveTo(OldOne);
			
		
			}
		}
		const dcInheritsFrom = cDISKENTITY;
		const lsClassFieldList    = {'sFileName'};
		const lsClassPropertyList = {'bExists','Extension'};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {};
			const lsPrivateClassPropertyList = {};
			
			private VOID		__FileDelete(REAL rTime null optional)
			{
				STRING sException="";
				if rTime == NULL
				{
					rTime = 60*7;
				}
				if rTime == 0
				{
					rTime = 7;
				}
				rTime = rTime/7;
				do // first try
				{
					if this.Exists()
					{
						this.__FileDeleteQAP();
					}
				}
				except
				{
					Log.ExceptPrint();
					ExceptClear();
				// do // wait for a minute, then try again
					// if this.Exists ()
					{
						// this.__FileClearAttribsDOS()
						// if this.Exists ()
						{
							// this.__FileDeleteQAP()
				// except
					// Log.ExceptPrint()
					// ExceptClear()
				// do // wait for another minute, then try again
					// if this.Exists ()
						// sleep(rTime)
						// if this.Exists ()
							// this.__FileDeleteQAP()
				// except
					// Log.ExceptPrint()
					// ExceptClear()
				// do // wait for yet another minute (3 so far), then try again
					// if this.Exists ()
						// sleep(rTime)
						// if this.Exists ()
							// this.__FileDeleteQAP()
				// except
					// Log.ExceptPrint()
					// ExceptClear()
				// do // ok, lets try changing the attributes (4 minutes)
					// if this.Exists ()
						// sleep(rTime)
						// if this.Exists ()
							// this.__FileClearAttribsDOS()
							// this.__FileDeleteQAP()
				// except
					// Log.ExceptPrint()
					// ExceptClear()
				// do // maybe a DOS delete? (5 minutes)
					// if this.Exists ()
						// sleep(rTime)
						// if this.Exists ()
							// this.__FileDeleteDOS()
				// except
					// Log.ExceptPrint()
					// ExceptClear()
				// do // maybe we can rename it? (6 minutes)
					// if this.Exists ()
						// sleep(rTime)
						// if this.Exists ()
							// this.__FileRenameDOS(this.sMungedName+".bak")
				// except
					// Log.ExceptPrint()
					// ExceptClear()
				// do // last try. We'll try everything. (7 minutes)
					// if this.Exists ()
						// sleep(rTime)
						// if this.Exists ()
							// this.__FileClearAttribsDOS()
							// this.__FileRenameDOS(this.sMungedName+".bak")
							// this.__FileDeleteDOS()
							// this.__FileDeleteQAP()
				// except
					// Log.ExceptPrint()
					// ExceptClear()
				// // I give up
						}
					}
				}
				if this.Exists ()
				{
					raise LIBERROR_FILE_DELETE_FAILED, "*** Error: LIBERROR_FILE_DELETE_FAILED in {this.sMungedName} on file name {this.sFileName} (permissions issue?) {sException}";
				}
			}
			private VOID		__FileDeleteQAP()
			{
				do
				{
					SYS_RemoveFile (this.sMungedName);
				}
				except
				{
					if MatchStr("*Permission denied*",ExceptData())
					{
						Log.print("Permission denied when trying to delete file {this.sFileName}, retrying...");
						sleep(5);
						do
						{
							SYS_RemoveFile (this.sMungedName);
							Log.print("2nd attempt successful.");
						}
						except
						{
							reraise;
						
						}
					}
					ExceptClear();
				}
			}
			private VOID		__FileDeleteDOS()
			{
				if cSystem.IsWindows()
				{
					//Log.print(cSystem.sShell+" /c DEL {this.sMungedName}")
					Log.ListPrint(cEXEFILE(cSystem.sShell).RunAndWait("/c DEL {this.sMungedName}"));
					sleep(10);
				}
			}
			private VOID		__FileClearAttribsDOS()
			{
				if cSystem.IsWindows()
				{
					//Log.print('{cSystem.sShell} /c ATTRIB -S -H -R {this.sMungedName}")')
					SYS_Execute(cSystem.sShell+" /c ATTRIB -S -H -R {this.sMungedName}");
					sleep(30);
				}
			}
			private VOID		__FileRenameDOS(STRING NewName)
			{
				if cSystem.IsWindows()
				{
					//Log.print('APP_Start({cSystem.sShell} /c REN {this.sMungedName} {sMungedName}.bak")')
					APP_Start(cSystem.sShell+" /c REN {this.sMungedName} {sMungedName}.bak");
					sleep(10);
			
		////////////////////////////////////////////////////////////////////////////
		
				}
			}
		}
	}
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cFILE()
	{
		STRING sf = ExtensionLibrary_SelfTestSuite_Object.sTestFileName;
		STRING st = ExtensionLibrary_SelfTestSuite_Object.sTestFileTarget;
		WINDOW cf = cFILE(sf);
		WINDOW ct = cFILE(st);
		WINDOW cfbak = cFILE(sf);
		ExtensionLibrary_SelfTestSuite_Object.RemoveTargetFile();
		ExtensionLibrary_SelfTestSuite_Object.RemoveTestFile();
		__DoTest("cFILE.sFileName",cf.sFileName,sf);
		__DoTest('cFILE.bExists FALSE',cf.bExists,FALSE);
		ExtensionLibrary_SelfTestSuite_Object.MakeTestFile();
		__DoTest('cFILE.bExists TRUE',cf.bExists,TRUE);
		__DoTest('cFILE.sDrivePart',upper(cf.sDrivePart),'C');
		__DoTest('cFILE.sDirectoryPart',cf.sDirectoryPart,cSystem.sDirSeparator);
		__DoTest('cFILE.sNamePart',cf.sNamePart,'test');
		__DoTest('cFILE.sExtensionPart',cf.sExtensionPart,'txt');
		__DoTest('cFILE.iSize',cf.iSize == 28,TRUE);
		__DoTest('cFILE.dtCreated',(cf.dtCreated != NULL) && (TypeOf(cf.dtCreated)==DATETIME),TRUE);
		__DoTest('cFILE.dtModified',(cf.dtModified != NULL) && (TypeOf(cf.dtModified)==DATETIME),TRUE);
		__DoTest('cFILE.bReadOnly',cf.bReadOnly,FALSE);
		__DoTest('cFILE.bHidden',cf.bHidden,FALSE);
		__DoTest('cFILE.bSystem',cf.bSystem,FALSE);
		__DoTest('cFILE.bArchive',cf.bArchive,TRUE);
		WINDOW bf = cFILE('Hello/*?<>|World');
		__DoTest("cFILE.sMungedName 'Hello/*?<>|World",bf.sMungedName,'hello______world');
		__DoTest("cFILE.sFileName 'Hello/*?<>|World",bf.sFileName,'Hello/*?<>|World');
		BOOLEAN fUseRawNameTemp = cf.fUseRawName;
		cf.fUseRawName = TRUE;
		__DoTest("cFILE.sMungedName (overridden) 'Hello/*?<>|World",bf.sMungedName,"Hello/*?<>|World");
		cf.fUseRawName = fUseRawNameTemp;
		cf.Delete();
		__DoTest('cFILE.Delete()',cf.bExists,FALSE);
		ExtensionLibrary_SelfTestSuite_Object.MakeTestFile();
		cf.MoveTo(ct);
		__DoTest('cFILE.Move(x)',(cf.sFileName == ct.sFileName) && (! cfbak.bExists), TRUE);
		ExtensionLibrary_SelfTestSuite_Object.RemoveTargetFile();
		ExtensionLibrary_SelfTestSuite_Object.RemoveTestFile();
		
	
	
	////////////////////////////////////////////////////////////////////////////
	// cOPENFILE 		Openable File Object
	//
	// Purpose: 		Provides centralized file services to caller
	//
	// Expand this for documentation
		//
		// inherits: 		cTEXTFILE (See cFILE for important notes on file names)
		//
		// PUBLIC MEMBERS - METHODS:
		//
		// 		Append (x)			Appends x to the file. If x is a list, method
		//							is called recursivly to append each item. All
		//							other items are recast as strings, and appended
		// 		Close ()			Closes the file.
		// 		DeleteMe ()			Overrides cFILE::DeleteMe() Closes before delete
		// 		New ()				Closes and deletes the file
		// 		Read ()				Returns the next STRING from the file. If file
		//							hasn't been opened, opens it and returns first
		//							STRING from file. NULL is returned if at EOF
		// 		Write (x)			Overwrites the file, starting with x
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		// 		AtEOF 				YES if last read left us at end of file
		//
		// PUBLIC MEMBERS - DATA:
		//
		//		CloseAfterEachWrite	Boolean, closes the file after each write if
		//							true. TRUE is safer, FALSE is faster. Always
		//							use TRUE if using this as a log file.
		//
		// NOTES:
		//
		// You don't have to open the file, if it isn't open, using this class
		// will cause it to be opened as needed. If CloseAfterEachWrite is set to
		// TRUE (the default setting), you never have to close the file either,
		// as it will be closed after each write.
		//
		// Also, even tho this inherets from cTEXTFILE, it will not automatically
		// read in the data.
		//
	////////////////////////////////////////////////////////////////////////////
	}
	winclass cOPENFILE : cTEXTFILE
	{
		
		STRING sFileName = cBASE::sPassedValue;
		
		property CloseAfterEachWrite			// default is yes, shared 
		{
			BOOLEAN Get()
			{
				BOOLEAN fResult;
				
				// have we specified an override?
				if this.__fLocalOverrideCloseAfterEachWrite==NULL
				{
					
					// no, so get the value set for the class
					OBJECT Closer=__fCloseAfterEachWrite;
					// do we have an already set value?
					if Closer.Value==NULL
					{
						// nope, set to TRUE
						Closer.SetValueAtClass(TRUE,cOPENFILE);
					
					// whether we just set it or it was there before, get it
					}
					fResult=Closer.Value;
				}
				else
				{
					// an override is specified for this instance, use that
					fResult=this.__fLocalOverrideCloseAfterEachWrite;
				
				// and hand back!
				}
				return fResult;
				
			}
			VOID Set(BOOLEAN fNew)
			{
				OBJECT Closer=__fCloseAfterEachWrite;
				Closer.SetValueAtClass(fNew,cOPENFILE);
				
			}
		}
		property LocallyOverrideAutoClose		// set to NULL for no override
		{
			BOOLEAN Get()
			{
				return this.__fLocalOverrideCloseAfterEachWrite;
			}
			VOID Set(BOOLEAN fNew NULL)
			{
				this.__fLocalOverrideCloseAfterEachWrite=fNew;
		
			}
		}
		property 	AtEOF // YES if at end of file
		{
			BOOLEAN Get ()
			{
				return this.__AtEof;
		
			}
		}
		VOID 		Append (TEXT text)
		{
			this.__OpenAs (FM_APPEND);
			text = MakeText(text);
			STRING item;
			for each item in text
			{
				FileWriteLine (this.__CurrentFileHandle, item);
			}
			this.__ConditionalClose ();
			
		}
		VOID 		Close ()
		{
			this.__Close ();
			this.__HavePerformedOverwriteSinceExplicitClose_Flag = NO;
			
		}
		VOID 		Delete ()
		{
			this.Close ();
			cFILE::Delete ();
			
		}
		STRING 		Read ()
		{
			if ! this.bExists
			{
				raise LIBERROR_FILE_NOT_FOUND, "*** Error: LIBERROR_FILE_NOT_FOUND in {this} for '{this.sFileName}' Read operation failed";
				
			}
			this.__OpenAs (FM_READ);
			
			STRING sData;
			FileReadLine (this.__CurrentFileHandle, sData);
			
			do
			{
				if (sData == NULL)
				{
					this.__AtEof = YES;
					sData = NULL;
				}
			}
			except
			{
				this.__AtEof = YES;
				sData = NULL;
				ExceptClear();
			}
			return sData;
			
		}
		VOID 		Write (TEXT text)
		{
			if (this.__HavePerformedOverwriteSinceExplicitClose_Flag == NO)
			{
				this.Delete ();
				this.__HavePerformedOverwriteSinceExplicitClose_Flag = YES;
			}
			this.Append (text);
		
		}
		VOID		WriteValue(ANYTYPE Incoming)
		{
			this.__OpenAs (FM_WRITE);
			FileWriteValue(this.__CurrentFileHandle, Incoming);
			this.Close ();
		}
		ANYTYPE		ReadValue()
		{
			ANYTYPE result;
			this.__OpenAs (FM_READ);
			FileReadValue (this.__CurrentFileHandle, result);
			this.Close ();
			return result;
		
		}
		const dcInheritsFrom = cFILE;
		const lsClassFieldList    = {'CloseAfterEachWrite'};
		const lsClassPropertyList = {'AtEOF'};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			BOOLEAN			__fLocalOverrideCloseAfterEachWrite = NULL;
			cSTATIC			__fCloseAfterEachWrite {}
			
			const 			lsPrivateClassFieldList    = 
			{
				'__HavePerformedOverwriteSinceExplicitClose_Flag',
				'__CurrentOpenMode',
				'__CurrentFileHandle',
				'__AtEof',
				'__iConstructor'
			};
			const 			lsPrivateClassPropertyList = {};
			
			BOOLEAN 		__HavePerformedOverwriteSinceExplicitClose_Flag = NO;
			INTEGER 		__CurrentOpenMode = FM_CLOSED;
			HANDLE 			__CurrentFileHandle = NULL;
			BOOLEAN 		__AtEof = NO;
			
			private VOID	__Close ()
			{
				do
				{
					if (this.__CurrentOpenMode != FM_CLOSED)
					{
						FileClose (this.__CurrentFileHandle);
						this.__CurrentOpenMode = FM_CLOSED;
					}
				}
				except
				{
					// do nothing for now...
					ExceptClear();
				}
			}
			private VOID	__ConditionalClose ()
			{
				if (this.CloseAfterEachWrite == YES)
				{
					this.__Close ();
				}
			}
			private VOID	__OpenAs (INTEGER FileMode)
			{
				
				STRING sExcept="";
				INTEGER iSeconds = 120;
				
				if (this.__CurrentOpenMode != FileMode)
				{
					this.__Close ();
					sleep(0.2);
					
					// retry the open up to 120 times, with 1 second spacing - for managing collisions with other processes
					INTEGER iTries=iSeconds;
					STRING sOldStatus="";
					STRING sTemp;
					BOOLEAN fError;
					
					while iTries > 0
					{
						fError=FALSE;
						iTries--;
						do
						{
							this.__CurrentFileHandle = FileOpen (this.sMungedName, FileMode);
						}
						except
						{
							//ExceptPrint()
							sExcept=ExceptData();
							
							if sContains(sExcept,"Sharing violation")
							{
								sleep(1);
								fError=TRUE;
								sTemp=SetTestStatus("FileOpen failed, seconds left for retry {iTries}. File: {this.sFileName}");
							}
							else
							{
								reraise;
							}
							if sOldStatus==""
							{
								sOldStatus=sTemp;
							}
							ExceptClear();
						}
						if ! fError
						{
							iTries=0;
					
						}
					}
					if sOldStatus != ""
					{
						SetTestStatus(sOldStatus);
					
					}
					if this.__CurrentFileHandle == NULL
					{
						if sContains(sExcept,"Sharing violation")
						raise LIBERROR_FILE_SHARING_VIOLATION, "*** Error: Sharing violation, unable to open file after {iSeconds} seconds of trying on {this.sFileName}";
						
					
					}
					this.__CurrentOpenMode = FileMode;
					this.__AtEof = NO;
					
				//if this.__CurrentOpenMode != FM_CLOSED
			
				}
			}
			BOOLEAN 		__Init = FALSE;
			
		////////////////////////////////////////////////////////////////////////////
		
		}
	}
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cOPENFILE() {}
	
	
	////////////////////////////////////////////////////////////////////////////
	// cTEXTFILE 		Text File (Represented as a list of string) Object
	//
	// Purpose: 		Provides text file services to caller
	//
	// Expand this for documentation
	{
		//
		// inherits: 		cFILE (See cFILE for important notes on file names)
		//
		// PUBLIC MEMBERS - SPECIAL:
		//
		//		LIST OF STRING __lsData 	This is the element in which the file
		//									data is actually stored. This is made
		//								accessable because you can't modify a single
		//								line in the list by exposing it as a property.
		//								Use this if you need to make changes to
		//								specific lines. Otherwise, it's safer to use
		//								the lsData property, because the class stores
		//								information on whether the data in memory is
		//								'dirty' and therefore may need to be written.
		//		__bDirty				Boolean variable which stores the dirty state.
		//								If you modify __lsData, you should set this
		//								to TRUE.
		//
		// PUBLIC MEMBERS - METHODS:
		//
		//		Append (x)				Accepts LISTorSTRINGorWINDOW where WINDOW
		//								would be another cTEXTFILE or derivitive.
		//		AddTo(x)				Accepts LISTorSTRINGorWINDOW as above. Reads
		//								the file from disk, appends the data, and
		//								writes it back out. Useful for logging.
		// 		Create()				Writes the file
		// 		DeleteLine(i)			Deletes the specified item from the list
		//								in memory.
		// 		GetLength()				Returns the number of lines in the list
		//								in memory.
		// 		InsertLine (x,i)		Inserts the line(s) provided. x is a string
		//								or list of string, i is the line number to
		//								insert at.
		// 		InsertTop (x)			Inserts x (LISTorSTRING) at the top of the
		//								list in memory.
		// 		Find(s)					Returns INTEGER of line s was found in
		// 		Read ()					Reads the file from disk, if the file exists.
		// 		Replace (x)				Replaces the list in memory with x where x is
		//								LIST of STRING or another cTEXTFILE
		//		Write ()				Writes the file
		// 		ZapData ()				Deletes the contents of the list in memory
		// 		SetLine(s,i)			Replaces the contents of the line specified
		//								as i with the STRING s in the list in memory
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		// 		iLength					Number of lines in the list in memory
		// 		lsData					Property for __lsData, modification sets the
		//								dirty flag.
		// 		bRead					Has the instance ever been read from disk?
		// 		bWritten				Has the instance ever been saved to disk?
		//
		// PUBLIC MEMBERS - DATA:
		//
		// 		iIndex					Used by SetLine(s,i), stores last line written
		//								to.
		//
		// NOTES:
		//
		// At instantiation time, if the specified file exists, the
		// instance will read it into lsData automatically, without
		// the need for an explicit call to Read().
		//
		// object MyFile = cTEXTFILE("C:\TEST.TXT");
		// STRING Line1 = MyFile.lsData[1];
		//
		// As 4Test does not allow us to create a destructor, you must
		// write the data out to storage explicitly before the object
		// goes out of scope, or the data will be lost.
		//
	////////////////////////////////////////////////////////////////////////////
	}
	winclass cTEXTFILE : cFILE
	{
		
		STRING sFileName = cBASE::sPassedValue;
		
		LIST OF STRING lsData = {};
		property 	d	// data. a mirror of lsData. This is the new standard as of 10/04
		{
			LIST Get()
			{
				return this.lsData;
			}
			VOID Set(LIST incoming)
			{
				this.lsData = incoming;
		
			}
		}
		BOOLEAN 	fHasBeenRead = FALSE;
		BOOLEAN 	fUseFastWrite = FALSE;	// IF TRUE, uses ListWrite WHICH WILL NOT
											// WORK ON A REMOTE BOX! ONLY ON LOCAL BOX!
		property 	fIsDirty
		{
			BOOLEAN Get()
			{
				return ! (this.lsData == this.__LastFileOpImage);
			}
		}
		property	iLength
		{
			INTEGER Get()
			{
				return this.GetLength();
		
			}
		}
		VOID		Read()
		{
			this.fHasBeenRead = FALSE;
			this.lsData = {};
			if this.bExists
			{
				this.lsData = SYS_GetFileContents(this.sMungedName);
				this.__LastFileOpImage = this.lsData;
				this.fHasBeenRead = TRUE;
			}
		}
		VOID		Write()
		{
			if ! this.fUseFastWrite
			{
				OBJECT Writer = cOPENFILE(this.sFileName);
				Writer.CloseAfterEachWrite = NO;
				ANYTYPE item;
				for each item in this.lsData
				{
					Writer.Write(item);
				}
				Writer.Close();
				this.__LastFileOpImage = this.lsData;
			}
			else
			{
				ListWrite(this.lsData,this.sFileName);
		
			}
		}
		VOID		Append (TEXT text)
		{
			text = MakeText(text);
			this.lsData = this.lsData + text;
		}
		VOID		Clear()
		{
			this.lsData = {};
			this.fHasBeenRead = FALSE;
		}
		VOID		DeleteLine(INTEGER iIndex)
		{
			ListDelete(this.lsData, iIndex);
		}
		INTEGER		Find(STRING sToFind)
		{
			return ListFind(this.lsData, sToFind);
		}
		INTEGER		GetLength()
		{
			return ListCount(this.lsData);
		}
		VOID		InsertLine (TEXT text, INTEGER iIndex)
		{
			text = MakeText(text);
			if this.iLength == 0
			{
				this.lsData = text;
			}
			else
			{
				ListMerge(this.lsData, text, iIndex);
			}
		}
		VOID		InsertTop (TEXT text)
		{
			text = MakeText(text);
			if this.lsData == NULL
			{
				this.lsData = text;
			}
			else
			{
				this.InsertLine(text, 1);
			}
		}
		VOID		ReplaceLine(INTEGER iIndex,ANYTYPE aData)
		{
			this.lsData[iIndex]=aData;
		}
		VOID		Zap()
		{
			Clear();
			Delete();
			Write();
		
		}
		const dcInheritsFrom = cFILE;
		const lsClassFieldList    = {'fHasBeenRead','lsData'};
		const lsClassPropertyList = {'fIsDirty','iLength'};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {'__LastFileOpImage','__Init'};
			const lsPrivateClassPropertyList = {};
			
			LIST OF STRING __LastFileOpImage = {};
			BOOLEAN 	__Init = this.__Init();
			
			private BOOLEAN 	__Init()
			{
				BOOLEAN fInitialReadOK = FALSE;
				do
				{
					if this.sFileName != ""
					{
						if this.bExists
						{
							this.Read();
							fInitialReadOK = TRUE;
						}
					}
				}
				except
				{
					// this just prevents an unhandled exception in the event that the
					// object is a global instance, and that the file doesn't exist yet.
					ExceptClear();
				}
				return fInitialReadOK;
			
		////////////////////////////////////////////////////////////////////////////
		
		// Expand for Historical Information
			// VOID		Read()  // Old way, uses cOPENFILE
				// this.fHasBeenRead = FALSE
				// OBJECT Reader = cOPENFILE(this.sMungedName)
				// if Reader.bExists
				{
					// this.Clear()
					// while ! Reader.AtEOF
					{
						// ListAppend(this.lsData, Reader.Read())
					// Reader.Close()
					// this.__LastFileOpImage = this.lsData
					// this.fHasBeenRead = TRUE
			// VOID		Read()	// Older way, uses ListRead - Doesn't work on a remote agent
				// this.fHasBeenRead = FALSE
				// if this.bExists
					// ListRead(this.lsData,this.sMungedName)
					// this.__LastFileOpImage = this.lsData
					// this.fHasBeenRead = TRUE
			// VOID		Write()	// Old way, uses ListWrite - Doesn't work on a remote agent
				// ListWrite(this.lsData, this.sMungedName)
				// this.__LastFileOpImage = this.lsData
		
					}
				}
			}
		}
	}
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cTEXTFILE()
	{
		STRING sf = ExtensionLibrary_SelfTestSuite_Object.sTestFileName;
		STRING st = ExtensionLibrary_SelfTestSuite_Object.sTestFileTarget;
		
		ExtensionLibrary_SelfTestSuite_Object.RemoveTargetFile();
		ExtensionLibrary_SelfTestSuite_Object.RemoveTestFile();
		
		WINDOW cf1 = cTEXTFILE(sf);
		__DoTest('cTEXTFILE.lsData on no file',cf1.lsData,{});
		
		ExtensionLibrary_SelfTestSuite_Object.MakeTestFile();
		cf1.Read();
		__DoTest('cTEXTFILE.Read()',cf1.lsData,{'line1', 'line2', 'line3', 'line4'});
		
		WINDOW cf2 = cTEXTFILE(sf);
		__DoTest('cTEXTFILE Constructor',cf2.lsData,{'line1', 'line2', 'line3', 'line4'});
		
		ExtensionLibrary_SelfTestSuite_Object.RemoveTestFile();
		WINDOW cf3 = cTEXTFILE(sf);
		ExtensionLibrary_SelfTestSuite_Object.MakeTestFile();
		__DoTest('cTEXTFILE.fHasBeenRead FALSE',cf3.fHasBeenRead,FALSE);
		cf3.Read();
		__DoTest('cTEXTFILE.fHasBeenRead TRUE',cf3.fHasBeenRead,TRUE);
		
		__DoTest('cTEXTFILE.fIsDirty FALSE',cf3.fIsDirty,FALSE);
		cf3.lsData = {'monday','tuesday','wednesday'};
		__DoTest('cTEXTFILE.fIsDirty TRUE',cf3.fIsDirty,TRUE);
		WINDOW cf4 = cTEXTFILE('who are you and why are you looking at me');
		__DoTest('cTEXTFILE.iLength 0',cf4.iLength,0);
		__DoTest('cTEXTFILE.iLength 3',cf3.iLength,3);
		
		TEXT testdata = {'who','are','you','and','why','are','you','looking','at','me'};
		cf4.Delete();
		cf4.lsData = testdata;
		cf4.Write();
		WINDOW cf5 = cTEXTFILE(cf4.sFileName);
		__DoTest('cTEXTFILE.Write()',cf5.lsData,testdata);
		cf5.Delete();
		
		WINDOW cf6 = cTEXTFILE('hello world');
		cf6.lsData = {"bad program, no biscut!"};
		cf6.Delete();
		cf6.Read();
		__DoTest('cTEXTFILE.Read() on no file',cf6.lsData == {},TRUE);
		cf6.Append("line1");
		__DoTest('cTEXTFILE.Append()',cf6.lsData == {'line1'},TRUE);
		cf6.Clear();
		__DoTest('cTEXTFILE.Clear()',cf6.lsData == {},TRUE);
		cf6.lsData = {'line1','line3','line2'};
		cf6.DeleteLine(2);
		__DoTest('cTEXTFILE.DeleteLine()',cf6.lsData,{'line1','line2'});
		cf6.lsData = {'line1','line2','line3'};
		__DoTest('cTEXTFILE.Find()',cf6.Find('line2'),2);
		cf6.lsData = {'line1', 'line2', 'line3', 'line4'};
		__DoTest('cTEXTFILE.GetLength()',cf6.GetLength(),4);
		cf6.lsData = {'line1', 'line3', 'line4'};
		cf6.InsertLine( 'line2',2);
		__DoTest('cTEXTFILE.InsertLine()',cf6.lsData,{'line1', 'line2', 'line3', 'line4'});
		cf6.InsertTop( 'new1');
		__DoTest('cTEXTFILE.InsertTop()',cf6.lsData,{'new1','line1', 'line2', 'line3', 'line4'});
		
		ExtensionLibrary_SelfTestSuite_Object.RemoveTargetFile();
		ExtensionLibrary_SelfTestSuite_Object.RemoveTestFile();
		cf6.Delete();
		cf5.Delete();
		cf4.Delete();
		cf3.Delete();
		cf2.Delete();
		cf1.Delete();
		
	
	

// Expand for Abstract Object Library - Executable file classes 	(cEXEFILE, cBATCHFILE, cEXEFILEFROMREGKEY, etc...)
	
	////////////////////////////////////////////////////////////////////////////
	// cEXEFILE 		Executable File Object
	//
	// Purpose: 		Provides centralized file services to caller
	//
	// Expand this for documentation
		//
		// inherits: 		cFILE (See cFILE for important notes on file names)
		//
		// PUBLIC MEMBERS - METHODS:
		//
		//		Run(s)			Runs the sFileName command, s is an optional
		//						parameter which allows you to specify additional
		//						arguments. Asynchronously runs the command
		//		RunAndWait(s)	As above, with two exceptions: 1) Command is run
		//						Synchronously, Silk doesn't continue execution
		//						until the command completes. 2) Returns list of
		//						STRING of any text that was displayed on the console
		//						as the command was run.
		//
		// NOTES:
		//
		// When running under Windows, there are some goofy behaviors around
		// batch files, like which caracters are allowed to be passed on the command
		// line and which have special meanings in the batch file. If you get
		// unexpected results when running a batch file, add the following to the
		// top of the file:
		//
		// @echo off
		// echo %1 %2 %3 %4 %5 %6 %7 %8 %9
		// pause
		//
		// And observe what really got passed to the insides of the batch file.
		//
	////////////////////////////////////////////////////////////////////////////
	}
	winclass cEXEFILE : cFILE
	{
		
		STRING sFileName = cBASE::sPassedValue;
		
		VOID 			Run(STRING sIncoming NULL optional)
		{
			if sIncoming == NULL
			{
				sIncoming = "";
			}
			else
			{
				sIncoming = " " + sIncoming;
			}
			do
			{
				STRING sNameToUse=PopulateEnvVars(this.sMungedName);
				APP_Start('{sNameToUse} {sIncoming}');
			}
			except
			{
				if MatchStr("*Application cannot be started*", ExceptData())
				{
					raise 1, "*** Error: Application cannot be started -- {this.sMungedName} not found. Occurred in {this.sName}";
					ExceptClear();
				}
				else
				{
					reraise;
				}
			}
		}
		LIST OF STRING 	RunAndWait(STRING sIncoming NULL optional)
		{
			if sIncoming == NULL
			{
				sIncoming = '';
			}
			else
			{
				sIncoming = ' ' + sIncoming;
			}
			LIST OF STRING lsResult = {};
			STRING sNameToUse=PopulateEnvVars(this.sMungedName);
			SYS_Execute('{sNameToUse} {sIncoming}',lsResult);
			return lsResult;
		
		}
		msw VOID		RunSafe(STRING sIncoming NULL optional)
		{
			this.__RunSafe(FALSE, sIncoming);
		}
		msw TEXT		RunAndWaitSafe (STRING sIncoming NULL optional)
		{
			return this.__RunSafe(TRUE , sIncoming);
		
		}
		const dcInheritsFrom = cFILE;
		const lsClassFieldList    = {};
		const lsClassPropertyList = {};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {};
			const lsPrivateClassPropertyList = {};
			
			msw private TEXT		__RunSafe(BOOLEAN fWait, STRING sIncoming NULL optional)
			{
				
				TEXT Result={};
				if sIncoming == NULL
				{
					sIncoming = "";
				
				}
				STRING sDopeyMeFileSpec = cSystem.sTempDir + "DopeyMe.bat";
				OBJECT DopeyMeBAT = cEXEFILE(sDopeyMeFileSpec);
				OBJECT DopeyMeTXT = cTEXTFILE(sDopeyMeFileSpec);
				OBJECT DopeyMeFLG = cSTATIC ("DOPEYME");
				
				if DopeyMeFLG.Value == NULL
				{
					DopeyMeTXT.lsData = 
					{
						"@echo off",
						"echo ARGH! ARGH! ARGH! ARGH!",
						"echo ARGH! ARGH! ARGH! ARGH!",
						"echo ARGH! ARGH! ARGH! ARGH!",
						"echo ARGH! ARGH! ARGH! ARGH!",
						"echo ARGH! ARGH! ARGH! ARGH!",
						"echo ARGH! ARGH! ARGH! ARGH!"
					};
					DopeyMeTXT.write();
					DopeyMeFLG.Value = TRUE;
				
				}
				DopeyMeBAT.RunAndWait ();
				
				if fWait
				{
					Result=this.RunAndWait(sIncoming);
				}
				else
				{
					this.Run(sIncoming);
				
				}
				return Result;
			
		////////////////////////////////////////////////////////////////////////////
		
		
			}
		}
	}
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cEXEFILE() {}
	
	////////////////////////////////////////////////////////////////////////////
	// cCOMMANDLINE 	Executes any command line
	//
	// Purpose 			General command line execution utility
	//
	// Notes			While this class inherets from cEXEFILE, it deals with
	//					it's data a little differently. Before the run operations
	//					happen, any extra command line is added to sFileName,
	//					then replace sFileName with everything to the first space
	//					(with special logic to handle " characters in the file
	//					name). Move everything after that space into the 
	//					sArguments data element. Then call the run command.
	////////////////////////////////////////////////////////////////////////////
	winclass cCOMMANDLINE : cEXEFILE
	{
		
		STRING sFileName = cBASE::sPassedValue;
		STRING sArguments = "";
		
		VOID 			Run(STRING sIncoming NULL optional)
		{
			
			if sIncoming != NULL
			{
				sArguments = sIncoming;
			
			}
			this.__FixUpFileNames();
			cEXEFILE(this.sFileName).Run(this.sArguments);
			
		}
		LIST OF STRING 	RunAndWait(STRING sIncoming NULL optional)
		{
			
			if sIncoming != NULL
			{
				sArguments = sIncoming;
			
			}
			this.__FixUpFileNames();
			return cEXEFILE(this.sFileName).RunAndWait(this.sArguments);
			
		
		}
		msw VOID		RunSafe(STRING sIncoming NULL optional)
		{
			
			if sIncoming != NULL
			{
				sArguments = sIncoming;
			
			}
			this.__FixUpFileNames();
			cEXEFILE(this.sFileName).RunSafe(this.sArguments);
			
		}
		msw TEXT		RunAndWaitSafe (STRING sIncoming NULL optional)
		{
			
			if sIncoming != NULL
			{
				sArguments = sIncoming;
			
			}
			this.__FixUpFileNames();
			return cEXEFILE(this.sFileName).RunAndWaitSafe(this.sArguments);
			
		
		}
		const dcInheritsFrom = cEXEFILE;
		const lsClassFieldList    = {"sArguments"};
		const lsClassPropertyList = {};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {};
			const lsPrivateClassPropertyList = {};
			
			VOID __FixUpFileNames()
			{
				STRING sCommandLine = this.sFileName+" "+sArguments;
				STRING sTemp;
				INTEGER i;
				LIST l;
				
				// first see if the command line has a leading "
				// which indicates that the file name part is 
				// enclosed in quotes (which will happen when there's
				// a space in it)
				if this.sFileName[1]=='"'
				{
					
					l=FindSubstrings(sCommandLine,'"');
					this.sFileName=SubStr(sCommandLine,1,l[2]);
					this.sArguments=SubStr(sCommandLine,l[2]+1,100000);
					
				}
				else
				{
					
					// No? OK, then let's see if there are any spaces in the command line
					l=FindSubstrings(sCommandLine,' ');
					if l != {}
					{
						// Yes, there's a space! So there must be a command line
						// and some arguments
						this.sFileName=SubStr(sCommandLine,1,l[2]);
						this.sArguments=SubStr(sCommandLine,l[2]+1,100000);
						
					}
					else
					{
						// no quotes and no spaces, must be just a command file name
						this.sFileName=sCommandLine;
						this.sArguments="";
					
					
				
			
		////////////////////////////////////////////////////////////////////////////
		
		
	
	////////////////////////////////////////////////////////////////////////////
	// cBATCHFILE
	////////////////////////////////////////////////////////////////////////////
					}
				}
			}
		}
	}
	winclass cBATCHFILE : cEXEFILE
	{
		
		STRING sFileName = cBASE::sPassedValue;
		TEXT   d {}
		
		Run(STRING sIncoming NULL optional)
		{
			if sIncoming==NULL
			{
				sIncoming="";
			}
			this.Write();
			derived::Run(sIncoming);
		}
		TEXT RunAndWait(STRING sIncoming NULL optional)
		{
			if sIncoming==NULL
			{
				sIncoming="";
			}
			this.Write();
			return derived::RunAndWait(sIncoming);
		}
		SafeRun(STRING sIncoming NULL optional)
		{
			if sIncoming==NULL
			{
				sIncoming="";
			}
			this.Write();
			derived::RunSafe(sIncoming);
		}
		SafeRunAndWait(STRING sIncoming NULL optional)
		{
			if sIncoming==NULL
			{
				sIncoming="";
			}
			this.Write();
			derived::RunAndWaitSafe(sIncoming);
		}
		VOID Write()
		{
			OBJECT foo=cTEXTFILE(this.sFileName);
			foo.Zap();
			foo.lsData=this.d;
			foo.Write();
		
		
	
	////////////////////////////////////////////////////////////////////////////
	// cEXEFILEFROMREGKEY
	//
	// Used when you want to run something, such as TWEAKUI.INF which is not
	// an executable, and which requires something like RunDLL in order to 
	// run it. There will be a reg key for that file type, something like so:
	// 
	// HKEY_CLASSES_ROOT\inffile\shell\install\command\
	//
	// Once you know where the file is, and where the execution reg key is, you can
	// invoke it like this:
	//
	// STRING sTweakUIInstallerPath = "\\Auto01\automation\Software\TweakUI\tweakui.inf"
	// STRING sRegEntryForINFFiles  = "HKEY_CLASSES_ROOT\inffile\shell\install\command\"
	// OBJECT TweakUIInstaller = cEXEFILEFROMREGKEY(sTweakUIInstallerPath).CreateWith(sRegEntryForINFFiles)
	// TweakUIInstaller.Run()
	//
	// STRING sRegEntryForCPLFiles = "HKEY_CLASSES_ROOT\cplfile\shell\cplopen\command\"
	// OBJECT TweakUIPanel = cEXEFILEFROMREGKEY("TWEAKUI.CPL").CreateWith(sRegEntryForCPLFiles)
	// TweakUIPanel.Run()
	// 
	// I looked at trying to make it autodetermine how to handle the file if
	// the reg key was not provided... But that will take some time to see if there's
	// a default key assigned, and if not to enumerate the keys and grab the first one.
	// We'll try this later.
	//
	// In the mean time, you'll need to provide the key
	//
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass cEXEFILEFROMREGKEY : cEXEFILE
	{
		
		STRING sRegKey = "";
		STRING sRegData = "";
		STRING sFileName = cBASE::sPassedValue;
		STRING sExecutable = "";
		STRING sCmdLinePart = "";
		
		OBJECT 			CreateWith(STRING sNewRegKey)
		{
			this.sRegKey = sNewRegKey;
			return this;
		}
		VOID			RunFrom(STRING sNewRegKey)
		{
			this.sRegKey=sNewRegKey;
			Run();
		
		}
		VOID 			Run(STRING sIncoming NULL optional)
		{
			if sIncoming == NULL
			{
				sIncoming = "";
			}
			else
			{
				sIncoming = " " + sIncoming;
			
			}
			this.__Extract();
			STRING sNameToUse=PopulateEnvVars(this.sExecutable);
			APP_Start('{sNameToUse} {this.sCmdLinePart} {sIncoming}');
			
		}
		LIST OF STRING 	RunAndWait(STRING sIncoming NULL optional)
		{
			if sIncoming == NULL
			{
				sIncoming = '';
			}
			else
			{
				sIncoming = ' ' + sIncoming;
			}
			LIST OF STRING lsResult = {};
			this.__Extract();
			STRING sNameToUse=PopulateEnvVars(this.sExecutable);
			SYS_Execute('{this.sNameToUse} {this.sCmdLinePart} {this.sIncoming}',lsResult);
			
			return lsResult;
			
		
		}
		property lsClassValues 
		{
			LIST Get()
			{
				OBJECT Result=cLIST().CreateWith({});
				ANYTYPE item;
				for each item in this.lsClassFieldList
				{
					
					Result.Append(@item);
					
				
				}
				return Result.d;
				
			
			}
		}
		const lsClassFieldList = {"sRegKey","sRegData","sFileName","sExecutable","sCmdLinePart"};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {};
			const lsPrivateClassPropertyList = {};
			
			VOID			__Extract()
			{
				if this.sRegKey==""
				{
					raise 1, "{this.Class}({this.sPassedValue}) failed to get the registry data because the reg key was not provided. Use CreateWith(sRegKey).";
				}
				this.sRegData=cSystem.GetReg(this.sRegKey);
				this.sRegData=GetLeftOf(this.sRegData,"%1",TRUE)+this.sFileName;
				
				this.sRegData=PopulateEnvVars(this.sRegData);
				
				this.sExecutable=GetLeftOf(this.sRegData," ",TRUE) ;
				this.sCmdLinePart=GetRightOf(this.sRegData," ",TRUE);
				
				// %SystemRoot%
				
				
				
			
		////////////////////////////////////////////////////////////////////////////
		
	
	////////////////////////////////////////////////////////////////////////////
	// cINFFILE
	////////////////////////////////////////////////////////////////////////////
			}
		}
	}
	winclass cINFFILE : cEXEFILEFROMREGKEY
	{
		
		VOID Install()
		{
			this.RunFrom("HKEY_CLASSES_ROOT\inffile\shell\install\command\");
		
		
	
	////////////////////////////////////////////////////////////////////////////
	// cCPLFILE
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass cCPLFILE : cEXEFILEFROMREGKEY
	{
		VOID Run()
		{
			cEXEFILEFROMREGKEY::RunFrom("HKEY_CLASSES_ROOT\cplfile\shell\cplopen\command\");
	

// Expand for Abstract Object Library - Special text file classes 	(cINIFILE, cLOGFILE)
	
	////////////////////////////////////////////////////////////////////////////
	// cINIFILE 		INI File Object
	//
	// Purpose: 		Provides INI file services to caller
	//
	// Expand this for documentation
		//
		// inherits: 		cTEXTFILE
		//
		// SPECIAL NOTES:
		//
		// 1) This class can be used either on it's own, or in conjunction with the
		// Section and Key classes. Please see the notes section before using.
		//
		// 2) While this class inherets from cTEXTFILE, it DOES NOT automatically
		// read in the file at instantiation time. This is because INI files can 
		// be so dynamic. If you want to work with the whole file in memory, do
		// an explicit read() before using lsData.
		//
		// PUBLIC MEMBERS - METHODS:
		//
		// 		Store(s,s,s) 		store a value to ini file
		// 		Retrieve(s,s) 		retrieve a value from ini file
		//		Write()				Closes the file, writing any changes
		//
		// NOTES:
		//
		// Can be used on it's own, or works with the Section and Key classes,
		// allowing it to be used like so:
		//
		// //Global definition
		// WINDOW cINIFILE Phred
		// 		STRING sFileName = "phred.ini"
		//		Section LoginInfo
		//			Key Username
		//			Key Password
		//
		// Then you can access the data stored there like so:
		// 		Window.Textfield = Phred.LoginInfo.Username.sValue
		//
		// Alternativly, you can dynamically instantiate the classes in the same
		// sort of way, like so:
		//
		// 		Window.Textfield = cINIFILE("Phred.ini").Section("LoginInfo").Key("Username").sValue
		//
		// The Section class one public method:
		//      Dump()			Dump() returns a list of list of string,
		//						which contains the keys and values for that section.
		//                      Basically, it gives you this kind of thing:
		//						{ { 'key1','key2'} , {'value1','value2'} }
		//						You can search list[1] for a string, and based on
		//						the resultant index into that list, fetch the
		//						corrisponding value from list[2].
		//						Primarially useful when you're not sure what
		//						keys will exist in a section and want to be able
		//						to loop through them all.
		//
		// The Key class has the following:
		// Inherits:			cBASE
		// Public Methods:		GetValue()	Gets value from INI file
		//						SetValue(s)	Sets value in INI file
		// Public Properties:	sValue		rw: gets or sets value from INI file
		//
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass cINIFILE : cTEXTFILE
	{
		
		STRING sFileName = cBASE::sPassedValue;
		
		VOID	Store (STRING sSection, STRING sKeyword, STRING sValue)
		{
			do
			{
				this.__Open ();
				INIFileSetValue (this.__hInternalHandle, sSection, sKeyword, sValue);
				this.__Close ();
			}
			except
			{
				ExceptClear();
				do
				{
					this.__Close ();
				}
				except
				{
					ExceptClear();
					// do nothing - this exception doesn't need to be trapped, the next peice of code
					// checks the result of this action.
				}
				do
				{
					this.SetAttribs(FALSE,FALSE,FALSE,NULL);
				}
				except
				{
					Log.LogError(ExceptData());
					ExceptClear();
				}
				this.__Open ();
				INIFileSetValue (this.__hInternalHandle, sSection, sKeyword, sValue);
				this.__Close ();
			
			}
		}
		STRING	Retrieve (STRING sSection, STRING sKeyword)
		{
			STRING sReturnValue;
			
			this.__Open ();
			sReturnValue = INIFileGetValue (this.__hInternalHandle, sSection, sKeyword);
			this.__Close ();
			
			return sReturnValue;
			
		}
		VOID	Close()
		{
			__Close();
		
		}
		const dcInheritsFrom = cTEXTFILE;
		const lsClassFieldList    = {};
		const lsClassPropertyList = {};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {'__fInternalHandle'};
			const lsPrivateClassPropertyList = {};
			
			ANYTYPE __hInternalHandle = NULL; 	// INIT VALUE, CHECK AGAINST 0 LATER TO SEE IF OPENED
			
			private VOID __Open ()
			{
				this.__hInternalHandle = INIFileOpen (this.sMungedName);
				
			}
			private VOID __Close ()
			{
				do
				{
					__InnerClose();
				}
				except
				{
					sleep(.5);
					ExceptClear();
					do
					{
						__InnerClose();
					}
					except
					{
						Log.LogWarning("INIFileClose({this.sFileName}) failed.");
						reraise;
					}
				}
			}
			private VOID __InnerClose()
			{
				if this.__hInternalHandle != NULL
				{
					INIFileClose (this.__hInternalHandle);
					this.__hInternalHandle = NULL;
			
			// this method is here to override the autoread code
				}
			}
			private BOOLEAN 	__Init()
			{
				return TRUE;
			
		////////////////////////////////////////////////////////////////////////////
		
			}
		}
	}
	winclass Section : cBASE
	{
		tag ".";
		LIST OF LIST OF STRING Dump()
		{
			return this.__DumpRaw()[2];
		}
		LIST OF LIST OF STRING DumpPaired()
		{
			return this.__DumpRaw()[3];
		}
		LIST OF STRING DumpRaw()
		{
			return this.__DumpRaw()[1];
		
		}
		const dcInheritsFrom = cBASE;
		const lsClassFieldList    = {};
		const lsClassPropertyList = {};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {'__INIFile','__sSection'};
			const lsPrivateClassPropertyList = {};
			
			WINDOW	__INIFile;
			STRING  __sSection;
			
			STRING __GetSectionName()
			{
				this.__sSection = TAG_StripParentage(this.sPassedValue);
				if __sSection == "."
				{
					__sSection = this.sName;
				}
				return this.__sSection;
			
			}
			private VOID	__SetValues()
			{
				this.__INIFile = this.oParent;
				this.__INIFile.lsData = {};
				this.__INIFile.Read();
				this.__GetSectionName();
			
			}
			LIST __DumpRaw()
			{
				this.__SetValues();
				LIST OF STRING lsData=this.__INIFile.lsData;
				
				integer iSectionStart = 0;
				iSectionStart = ListFind(lsData,'[{this.__sSection}]');
				integer i;
				list of string lsKeys = {};
				LIST OF STRING lsValues = {};
				LIST OF STRING lsLines = {};
				LIST OF LIST OF STRING llsPairs = {};
				STRING sValueData, sKeyName;
				
				integer iListSize = ListCount(lsData);
				// iSectionStart = iSectionStart+1
				
				if iSectionStart < iListSize
				{
					for i = iSectionStart+1 to iListSize
					{
						
						STRING sCurrent = lsData[i];
						if trim(sCurrent)[1]=='['
						{
							break;
						
						}
						if len(trim(sCurrent)) > 0
						{
							sKeyName = GetLeftOf(sCurrent,'=');
							sValueData="";
							if MatchStr("*=*",sCurrent)
							{
								sValueData=GetRightOf(sCurrent,'=');
							
							}
							ListAppend(lsLines,sCurrent);
							ListAppend(lsValues,sValueData);
							ListAppend(lsKeys,sKeyName);
							ListAppend(llsPairs,{sKeyName,sValueData});
						
						}
					}
				}
				return {lsLines,{lsKeys,lsValues},llsPairs};
				
		////////////////////////////////////////////////////////////////////////////
		
			}
		}
	}
	winclass Key : cBASE
	{
		tag ".";
		property 	sValue
		{
			STRING Get()
			{
				return GetValue();
			}
			VOID Set(STRING sIncoming)
			{
				this.SetValue(sIncoming);
			}
		}
		property 	d
		{
			STRING Get()
			{
				return GetValue();
			}
			VOID Set(STRING sIncoming)
			{
				this.SetValue(sIncoming);
		
			}
		}
		STRING		GetValue()
		{
			this.__SetValues();
			return this.__INIFile.Retrieve(this.__sSection, this.__sKey);
		}
		VOID		SetValue(STRING sIncoming)
		{
			this.__SetValues();
			this.__INIFile.Store(this.__sSection, this.__sKey, sIncoming);
		
		}
		const dcInheritsFrom = cBASE;
		const lsClassFieldList    = {};
		const lsClassPropertyList = {'sValue'};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {'__sSection','__sKey','__sCachedValue','__INIFile'};
			const lsPrivateClassPropertyList = {};
			
			STRING	__sSection;
			STRING	__sKey;
			STRING  __sCachedValue;
			WINDOW	__INIFile;
			
			private VOID	__SetValues()
			{
				WINDOW Section = this.oParent;
				__INIFile = Section.oParent;
				__sSection = Section.__GetSectionName();
				__sKey = TAG_StripParentage(this.sPassedValue);
				if __sKey == "."
				{
					__sKey = this.sName;
				
			
			
		////////////////////////////////////////////////////////////////////////////
		
				}
			}
		}
	}
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cINIFILE() {}
	
	
	////////////////////////////////////////////////////////////////////////////
	// cLOGFILE			Generic log file system, which shares data between instances
	////////////////////////////////////////////////////////////////////////////
	
	winclass cLOGFILE : cOPENFILE
	{
		
		STRING sFileName = cBASE::sPassedValue;
		
		VOID Append(ANYTYPE aIncoming)
		{
			this.__CycleInstances("Append",aIncoming, NULL);
		}
		VOID Print(ANYTYPE aIncoming)
		{
			this.__CycleInstances("Print",aIncoming, NULL);
		}
		VOID print(ANYTYPE aIncoming)
		{
			this.__CycleInstances("Print",aIncoming, NULL);
		}
		VOID LogError(ANYTYPE aIncoming, BOOLEAN bPrintCallStack null optional)
		{
			if bPrintCallStack == NULL
			{
				bPrintCallStack=FALSE;
			}
			this.__CycleInstances("LogError",aIncoming, bPrintCallStack);
		}
		VOID LogPass(ANYTYPE aIncoming)
		{
			this.__CycleInstances("LogPass",aIncoming, NULL);
		}
		VOID LogResult(ANYTYPE aIncoming)
		{
			this.__CycleInstances("LogResult",aIncoming, NULL);
		}
		VOID LogWarning(ANYTYPE aIncoming)
		{
			this.__CycleInstances("LogWarning",aIncoming, NULL);
		}
		VOID listprint(ANYTYPE aIncoming)
		{
			this.__CycleInstances("listprint",aIncoming, NULL);
		}
		VOID ListPrint(ANYTYPE aIncoming)
		{
			this.__CycleInstances("ListPrint",aIncoming, NULL);
		}
		VOID ResOpenList(ANYTYPE aIncoming)
		{
			this.__CycleInstances("ResOpenList",aIncoming, NULL);
		}
		VOID ResCloseList()
		{
			this.__CycleInstances("ResCloseList",NULL, NULL);
		}
		VOID ResPrintList(STRING sName, LIST OF ANYTYPE laItems)
		{
			this.__CycleInstances("ResPrintList",sName, laItems);
		}
		VOID ResCloseAnyRemainingList()
		{
			while this.__iCurrentResIndent < 0
			{
				this.ResCloseList();
			}
		}
		VOID PrintCallStack()
		{
			this.__CycleInstances("PrintCallStack",NULL, NULL);
		
		}
		hidecalls VOID ExceptPrint()
		{
			this.__CycleInstances("ExceptPrint",NULL, NULL);
		}
		hidecalls VOID SmartExceptPrint()
		{
			LIST OF STRING lsData=MakeErrorData();
			this.ResOpenList(lsData[1]);
			StackPop(lsData);
			this.ResListPrint(lsData);
			this.ResCloseList();
		
		}
		VOID Reset()
		{
			this.__CycleInstances("Reset",NULL, NULL);
		}
		VOID WriteOutErrorLogBuffer()
		{
			ANYTYPE aError;
			for each aError in ErrorLogBuffer
			{
				this.LogError(aError);
			}
		}
		VOID ClearErrorLogBuffer()
		{
			this.__lsErrorLogBuffer = {};
		
		}
		property 	ErrorLogBuffer
		{
			LIST OF ANYTYPE Get()
			{
				{
					return  this.__lsErrorLogBuffer;
				}
			}
			VOID Set(ANYTYPE aIncoming)
			{
				if aIncoming == "{}"
				{
					this.__lsErrorLogBuffer = {};
				}
				else
				{
					ListAppend(this.__lsErrorLogBuffer,aIncoming);
					::LogError([STRING]aIncoming);
		
				}
			}
		}
		const dcInheritsFrom = cOPENFILE;
		const lsClassFieldList    = {'sCurrentFilter','lsCallsToHook'};
		const lsClassPropertyList = {'fTimeStampFiles','fReuse'};
		
		const lsCallsToHook = 
		{
			"Append",
			"Print",
			"print",
			"LogError",
			"LogPass",
			"LogResult",
			"LogWarning",
			"ListPrint",
			"listprint",
			"ResOpenList",
			"ResCloseList",
			"ResPrintList",
			"PrintCallStack",
			"Reset"
		};
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
		{
			
			const lsPrivateClassFieldList    = {'__iCurrentResIndent','__loAdditionalLogs','__Logging'};
			const lsPrivateClassPropertyList = {'__sCurrentIndent'};
			
			// driver methods - here's where the data gets passed around and filtered
			hidecalls VOID			__CycleInstances(STRING sMethod, ANYTYPE a1 null optional, ANYTYPE a2 null optional)
			{
				
				if a1 == NULL	// this is to turn unset NULLs into explicit NULLs
				{
					a1 = NULL;
				}
				if a2 == NULL
				{
					a2 = NULL;
				
				}
				ANYTYPE item;
				for each item in oLogFileHelperObject.SubscriberList
				{
					do
					{
						item.@("__"+sMethod)(this, sMethod, a1, a2);
					}
					except
					{
						ExceptPrint();
					}
				}
			}
			hidecalls BOOLEAN 		__FilterCheck(OBJECT oCaller, STRING sMethod)
			{
				BOOLEAN fResult=FALSE;
				if oCaller==this
				{
					fResult=TRUE;
				}
				else if Contains(lsCallsToHook, sMethod)
				{
					fResult=TRUE;
				}
				return fResult;
			
			// low level methods, these do the actual output work
			}
			hidecalls VOID	__JustPrint(ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				___print(aIncoming);
			}
			hidecalls VOID	__JustAppend(ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				if IsVarWindow(aIncoming)
				{
					cOPENFILE::Append(aIncoming);
				}
				else
				{
					cOPENFILE::Append(this.__sCurrentIndent+"{aIncoming}");
				}
			}
			hidecalls VOID	__JustCallStack()
			{
				
				LIST OF CALL lcCall = GetCallStack();
				CALL Call;
				INTEGER i,iTarget;
				
				// find the entry point into __CycleInstances
				for i = 1 to ListCount(lcCall)
				{
					if sContains(lcCall[i].sFunction,".__CycleInstances")
					{
						iTarget=i;
						break;
				
				// now remove all calls leading up to __CycleInstances... And one more, 
				// since usually that's the entry point into the cLOG object
					}
				}
				for i = 1 to (iTarget+1)
				{
					ListDelete(lcCall,1);
				
				// now we're ready to print the result
				}
				STRING sMessage="Occurred in";
				for each Call in lcCall
				{
					this.__JustAppend ("{sMessage} {Call.sFunction} at {Call.sModule}({Call.iLine})");
					if sMessage=="Occurred in"
					{
						sMessage="Called from";
					}
				}
			}
			hidecalls VOID	__JustListPrint(LIST Incoming)
			{
				ANYTYPE item;
				for each item in Incoming
				{
					this.__JustAppend(item);
			
			// Functional methods
				}
			}
			hidecalls VOID	__print(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustAppend(aIncoming);
				}
			}
			hidecalls VOID	__Print(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustAppend(aIncoming);
				}
			}
			hidecalls VOID	__Append(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustAppend(aIncoming);
				}
			}
			hidecalls VOID 	__PrintCallStack (OBJECT oCaller, STRING sMethod, ANYTYPE NotUsed1 null optional, ANYTYPE NotUsed2 null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustCallStack();
				}
			}
			hidecalls VOID 	__LogError(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, BOOLEAN bPrintCallStack null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					STRING sData = "{aIncoming}";
					if substr(sData,1,10)!="*** Error:"
					{
						sData="*** Error: "+sData;
					}
					this.__JustAppend(sData);
					if IsNull(bPrintCallStack)
					{
						bPrintCallStack = FALSE;
					}
					if bPrintCallStack
					{
						this.__JustCallStack();
					}
				}
			}
			hidecalls VOID 	__LogPass(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustAppend(aIncoming);
				}
			}
			hidecalls VOID 	__LogResult(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustAppend(aIncoming);
				}
			}
			hidecalls VOID 	__LogWarning(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustAppend("*** Warning: {aIncoming}");
				}
			}
			hidecalls VOID 	__listprint(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustListPrint(aIncoming);
				}
			}
			hidecalls VOID 	__ResOpenList(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustAppend(aIncoming);
					__iCurrentResIndent=__iCurrentResIndent+3;
				}
			}
			hidecalls VOID 	__ResCloseList(OBJECT oCaller, STRING sMethod, ANYTYPE NotUsed1 null, ANYTYPE NotUsed2 null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					__iCurrentResIndent=__iCurrentResIndent-3;
				}
			}
			hidecalls VOID 	__ResPrintList(OBJECT oCaller, STRING sMethod, STRING sName, LIST OF ANYTYPE laItems)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustAppend(sName);
					this.__iCurrentResIndent=this.__iCurrentResIndent+3;
					this.__JustListPrint(laItems);
					this.__iCurrentResIndent=this.__iCurrentResIndent-3;
				}
			}
			hidecalls VOID	__ExceptPrint(OBJECT oCaller, STRING sMethod, ANYTYPE NotUsed1 null, ANYTYPE NotUsed2 null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.__JustAppend("*** Error: {ExceptData()}");
					ANYTYPE item,laCallList=ExceptCalls();
					for each item in laCallList
					{
						if ! (sContains(item.sFunction,".__CycleInstances at ") || sContains(item.sFunction,".LogError at "))
						{
							this.__JustAppend("Called from {item.sFunction} at {item.sModule}({item.iLine}).");
					
			
						}
					}
				}
			}
			hidecalls VOID 	__Reset(OBJECT oCaller, STRING sMethod, ANYTYPE NotUsed1 null optional, ANYTYPE NotUsed2 null optional)
			{
				if this.__FilterCheck(oCaller, sMethod)
				{
					this.Delete();
			
			// Constructor related
				}
			}
			BOOLEAN			__Constructor()
			{
				oLogFileHelperObject.Register(this);
				return TRUE;
			}
			BOOLEAN 		__ConstructorValue = this.__Constructor();
			
			// Other
			INTEGER 		__iCurrentResIndent = 0;
			property		__sCurrentIndent
			{
				STRING Get()
				{
					STRING sResult = Space(__iCurrentResIndent);
					if this.__iCurrentResIndent == 0
					{
						sResult = "";
					}
					return sResult;
				}
			}
			LIST OF ANYTYPE __lsErrorLogBuffer;
			
			// debris from the old way of doing it
			{
				// VOID			__OpenIndent()
				{
					// this.__iCurrentResIndent = this.__iCurrentResIndent + 3
				// VOID			__CloseIndent()
					// this.__sCurrentIndent = this.__sCurrentIndent - 3
				// BOOLEAN		__PassesFilter(STRING sFilterForIncomingMessage)
					// BOOLEAN fResult = TRUE
					// if ! (this.sFilter == "")
					{
						// fResult = ( lower(this.sFilter) == lower(sFilterForIncomingMessage) )
					// return fResult
				// VOID			__ReEntry(STRING sOriginatingFilter, STRING sMethod, ANYTYPE a1 null optional, ANYTYPE a2 null optional)
					// if __PassesFilter(sOriginatingFilter)
						// this.@(sMethod)(a1,a2)
					//
				// VOID			__ResPrint(ANYTYPE aIncoming)
					// if __PassesFilter(aIncoming)
						// ___print(aIncoming)
				// VOID			__ResListPrint(ANYTYPE aIncoming)
					// if __PassesFilter(aIncoming)
					// ANYTYPE item
				// property sFilter
					// STRING Get()
						// return GetRightOf(this.sFileName,cSystem.sDirSeparator)
				// STRING			__MakeFileName()
					// STRING sProgDir = GetProgramDir()
					// STRING sSep = cSystem.sDirSeparator
					// STRING sTimeStamp = ""
					// STRING sFile = "Complete.log"
					// STRING sFinal = sProgDir + sSep + sTimeStamp + sFile
					// do
						// sFinal = cBASE::sPassedValue
					// except
						// // we must be a global instance...
						// ExceptClear()
					// return
			
			
		////////////////////////////////////////////////////////////////////////////
	
					}
				}
			}
		}
	}
	hidecalls LIST OF STRING MakeErrorData()
	{
		
		LIST OF STRING lsResult = {};
		
		ListAppend(lsResult,"*** Error: {ExceptData()}");
		
		ANYTYPE item,laCallList=ExceptCalls();
		
		for each item in laCallList
		{
			//if ! ((sContains(item.sFunction,".__CycleInstances at ") || sContains(item.sFunction,".LogError at ")))
			ListAppend(lsResult,"Called from {item.sFunction} at {item.sModule}({item.iLine}).");
		
		}
		return lsResult;
		
	}
	hidecalls SmartExceptPrint()
	{
		LIST OF STRING lsData=MakeErrorData();
		ResOpenList(lsData[1]);
		StackPop(lsData);
		ListPrint(lsData);
		ResCloseList();
		
	
	// Private helper code for cLOGFILE
		private VOID ___print(ANYTYPE aIncoming)
		{
			print(aIncoming);
		}
		private VOID ___ListPrint(ANYTYPE aIncoming)
		{
			ListPrint(aIncoming);
		}
		private VOID ___LogError(ANYTYPE aIncoming)
		{
			LogError(aIncoming);
		}
		private VOID ___LogWarning(ANYTYPE aIncoming)
		{
			LogWarning(aIncoming);
		}
		private VOID ___ResOpenList(ANYTYPE aIncoming)
		{
			ResOpenList(aIncoming);
		}
		private VOID ___ResCloseList()
		{
			ResCloseList();
		}
		private VOID ___ResPrintList(STRING sMessage, ANYTYPE aIncoming)
		{
			ResPrintList(sMessage, aIncoming);
		}
		private WINDOW cBASE oLogFileHelperObject
		{
			
			LIST OF OBJECT SubscriberList = {};
			
			VOID Register(OBJECT oIncoming)
			{
				if ListFind(SubscriberList,oIncoming) == 0
				{
					ListAppend(SubscriberList,oIncoming);
			
				}
			}
			BOOLEAN fPrinted = FALSE;
			
	
	// Built in instances
		}
	}
	WINDOW cLOGFILE ResFile
	{
		VOID			__JustPrint(ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
		{
			___print(aIncoming);
		}
		VOID			__JustAppend(ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
		{
			___print(aIncoming);
		}
		VOID			__JustListPrint(LIST Incoming)
		{
			___listprint(Incoming);
		
		}
		VOID 			__LogError(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, BOOLEAN bPrintCallStack null optional)
		{
			___LogError(aIncoming);
			if IsNull(bPrintCallStack)
			{
				bPrintCallStack = FALSE;
			}
			if bPrintCallStack
			{
				__JustCallStack();
			}
		}
		VOID 			__LogWarning(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
		{
			___LogWarning(aIncoming);
		}
		VOID 			__ResOpenList(OBJECT oCaller, STRING sMethod, ANYTYPE aIncoming, ANYTYPE NotUsed null optional)
		{
			___ResOpenList(aIncoming);
		}
		VOID 			__ResCloseList(OBJECT oCaller, STRING sMethod, ANYTYPE NotUsed1 null, ANYTYPE NotUsed2 null optional)
		{
			___ResCloseList();
		}
		VOID 			__ResPrintList(OBJECT oCaller, STRING sMethod, STRING sName, LIST OF ANYTYPE laItems)
		{
			___ResPrintList(sName,laItems);
		}
		VOID			__ExceptPrint(OBJECT oCaller, STRING sMethod, ANYTYPE NotUsed1 null, ANYTYPE NotUsed2 null optional)
		{
			___LogError("{ExceptData()}");
			ANYTYPE item,laCallList=ExceptCalls();
			//ListDelete(laCallList,1)
			//ListDelete(laCallList,1)
			for each item in laCallList
			{
				__JustAppend("Called from {item.sFunction} at {item.sModule}({item.iLine})");
		
			}
		}
		VOID 			__Reset(OBJECT oCaller, STRING sMethod, ANYTYPE NotUsed1 null optional, ANYTYPE NotUsed2 null optional)
		{
			// do nothing - yet.
		
		}
	}
	WINDOW cLOGFILE Log
	{
		STRING sFileName = "{GetProgramDir()}{cSystem.sDirSeparator}Complete.log";
	
	//unit test
		testcase atest()
		{
			Log.print("RESET AND POPULATE ResultLog");
			OBJECT LocalResultLog = cLOGFILE("{GetProgramDir()}{cSystem.sDirSeparator}Result.log");
			LocalResultLog.lsCallsToHook=
			{
				"LogError",
				"LogResult",
				"LogWarning",
				"Reset"
			};
			
			LocalResultLog.Reset();
			LocalResultLog.print('Hi!');
			LocalResultLog.print('scooby!');
			Log.print("How about a scooby snack?");
			Log.print(LocalResultLog.sFileName);
			LocalResultLog.ErrorLogBuffer = "Error1";
			LocalResultLog.ErrorLogBuffer = "Error2";
			LocalResultLog.ErrorLogBuffer = "Error3";
			LocalResultLog.ErrorLogBuffer = "Error4";
			LocalResultLog.ErrorLogBuffer = "Error5";
			LocalResultLog.ErrorLogBuffer = "Error6";
			LocalResultLog.ErrorLogBuffer = "Error7";
			LocalResultLog.WriteOutErrorLogBuffer();
			Log.print('------------------------------------');
			Log.print("RESULT LOG CONTENTS");
			OBJECT foo1 = cTEXTFILE(LocalResultLog.sFileName);
			Log.print(foo1.sFileName);
			Log.print(foo1.bExists);
			Log.listprint(foo1.lsData);
			Log.print("COMPLETE LOG CONTENTS");
			Log.print('------------------------------------');
			OBJECT foo2 = cTEXTFILE(Log.sFileName);
			Log.print(foo2.sFileName);
			Log.print(foo2.bExists);
			Log.listprint(foo2.lsData);
			
			
	

// Expand for Abstract Object Library - Data container file classes	(cDATASOURCE, cBAG, cVERIFYBAG)
	
	////////////////////////////////////////////////////////////////////////////
	// cDATASOURCE		Sources data from external files (Phil Boatwright)
	//
	// Purpose:			Connects to and returns rows from various data
	//                  stores: Comma Delimited (csv), Text (txt), XLS,
	// 					SQL Server, Visual Fox Pro (DBF)
	//
	// Expand this for documentation
		//
		//			 Data Setup:
		//				cDATASOURCE can retrieve all rows from a file/table. It
		//              only requires filename/path, data type and table name.
		//
		//				NOTE:Excel retrieval does not include the header
		//              information. A special RetrieveHeader method must be
		//              used to acquire this information.
		//
		// inherits:	cTEXTFILE
		//
		// PUBLIC MEMBERS - METHODS:
		//		RowCount:	 returns the number of rows of data in a specified table (Only XLS files currently supported)
		//		Retrieve: 	 returns the rows of data from a data store.
		//  				 Retrieves all rows unless using the following options:
		//						Index:  passing in the number from the "index" column within the datastore will return only
		//								the row specified. Requires the creation of a column called "Index" and a unique
		//								alpha/numeric for	each row in the spreadsheet.
		//						Qry:	passing in a custom query will return the results based on the query. The query needs
		//								to conform to the SQL syntax requirements of the data store that is being queried.
		//						UID:	Enterprise data stores,ie SQL Server requires a user name
		//						PWD:	Enterprise data stores,ie SQL Server requires a password
		//						DB:		Enterprise data stores,ie SQL Server requires the name of the database.
		//						SVR		Enterprise data stores,ie SQL Server requires the name of the server.
		//
		//						NOTE: SQL Server does not use the filename or table name however these are required.
		//
		//		RetrieveXLS: 	 returns the rows of data from an XLS Worksheet
		//  					 Retrieves all rows unless using the following options:
		//						 Index:  passing in the number from the "index" column within the spreadsheet will return only
		//								 the row specified. Requires the creation of a column called "Index" and a unique
		//								 alpha/numeric for	each row in the spreadsheet.
		//						  if passed an Index it returns a list of STRING as a list of anytype
		//						  if not passed an index it returns a list of list of STRING as a list of anytype
		//
		//		Data Cleanup:
		//						Data returned from Excel Spreadsheets (XLS) require some cleanup.
		//						Here's a list of what's cleaned up:
		//							Strings are returned with a single quote in the first character position. This is removed.
		//							Integers are returned with six zero's past the decimal point. The zeros and decimal point
		//							are removed.
		//
		//		RetrieveHeader:	returns the header (column names) information only. Only needed for Excel.
		//						Excel Data Setup:
		//							This requires the addition of a worksheet in the workbook called "TableData". The first
		//							column of the worksheet is called "nothing" and needs to be left empty. The first row of
		//							each column in this worksheet has to contain the name of each worksheet in the workbook.
		//							Under each table name all fields in each table has to be listed top to bottom
		//							as they appear left to right in their respective tables. This is where retrieve header
		//							retrieves the column names for each table.
		//
		//		Update:			 Update changes information in an existing Excel Spreadsheet. It requires at least two rows of data.
		//						 The first row needs to be the column names and the subsequent rows are the data to change.
		//		PopulateFields:  Populates the properties of an object with data from a data store. Requires the data
		//						 type, table name and specific row if not populating object with first row data. Currently
		//						 only for Excel Spreadsheets. Requires an additional LIST OF STRING attribute. This list
		//						 should contain the names of all of the object properties in the same order left to right
		//						 as the column names in the spreadsheet. Ex:
		//						 LIST OF STRING lsAttributes = {"sFirstName", "sLastName", "sAddress", "sCity", "sZip"}
		//						 NOTE: THIS ASSUMES YOU ARE POPULATING ALL FIELDS OF AN OBJECT
		//  	PopulateFromSheet(s,i) Populates this from an excel workbook which contains a worksheet called HeaderList
		//                       Which contains all the headers for the worksheets in the workbook. This assumes that the
		//                       column names are EXACTLY THE SAME as the field names of the object. The useful thing about
		//                       this method is it's tolerance of order... You can rearrange the columns and the data
		//                       will still be populated correctly. When you call this method, you specify sheet name and row
		//					     to populate from.
		// 		PopulateClassFromSheet(i) This method assumes that the worksheet name you wish to populate from is
		//						 exactly the same as the name of the class that's being populated. All you have to
		//						 specify is the row. The down side of this being that if you have a class such as cFILE,
		//						 and a sheet from which you're populating cFILE, and you inheret from cFILE to another class
		//						 such as cTEXTFILE, then this method will only populate from a worksheet named cTEXTFILE.
		//						 In such a case, PopulateFromSheet() is a better course.
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		//		none
	////////////////////////////////////////////////////////////////////////////
		}
	}
	winclass cDATASOURCE : cFILE	// 2002.11.11 AMM: Changed from cTEXTFILE to speed load time
	{
		
		// AMM 2004.11.05: I think these are the real public members
		STRING sFileName = cBASE::sPassedValue;
		
		STRING 				sTableName = "{ClassOf(this)}";
		STRING 				sIndex = "";
		LIST OF STRING      lsData = NULL;
		
		// AMM 2004.11.05: I'm unsure if this should be public
		LIST OF LIST OF STRING	lCSVList =
		{
		};
		
		// AMM 2004.11.05: These methods should clearly be public
		LIST OF ANYTYPE		RetrieveXLS(STRING sWorksheet, STRING sIndex optional,STRING sColumn optional,
		 						STRING sColumnValue optional)
		{
			__sPassedTableName=sWorksheet;
			// if passed an Index it returns a list of STRING as a list of anytype
			//if not passed an index it returns a list of list of STRING as a list of anytype
			LIST OF ANYTYPE lsAllRows = {};
			LIST OF STRING lsRow = {};
			LIST OF STRING rsRow = {};
			STRING sSQL = NULL;
			STRING sItem = NULL;
			STRING sField = NULL;
			lRow = 
			{
			};
			lsRow = 
			{
			};
			sItem = "";
			r=0;
			// STRING sConnect = "DRIVER=Microsoft Excel Driver (*.xls);ReadOnly=0;DBQ= {this.sFileName};"
			// hODBC=__DB_Connect(sConnect)
			select 
			{
				case sIndex != NULL:
					sSQL = 'SELECT * FROM  "{sWorksheet}$""{sWorksheet}$" WHERE "{sWorksheet}$".index=' + sIndex;
				case sColumn != NULL:
					sSQL = 'SELECT * FROM  "{sWorksheet}$""{sWorksheet}$" WHERE "{sWorksheet}$".{sColumn}=''{sColumnValue}''';
				default:
				{
					sSQL = 'SELECT * FROM  "{sWorksheet}$""{sWorksheet}$"';
				}
			}
			hRecord = GetDataSetHandle(sSQL);
			do
			{
				while (__DB_FetchNext (hRecord, id, rsRow) == TRUE)
				{
					//start a counter of rows
					lsRow = {};
					r++;
					//analyze each item and clean it up.
					for each sItem in rsRow
					{
						if sItem == NULL
						{
							sItem = "";
						}
						else
						{
							sItem = CleanData(sItem);
						//append each item to a new list
						}
						ListAppend(lsRow, sItem);
					//append the cleaned rows to another list
					}
					ListAppend(lsAllRows,lsRow);
				}
			}
			except
			{
				// printing exception and class data used to happen here, now it happens in the primitaves
				reraise;
			//if the query only returned one row then just send the new list
			}
			__DB_FinishSQL(hRecord);
			__DB_Disconnect(hODBC);
			if r ==1
			{
				return lsRow;
			//otherwise send the multiple list
			}
			else
			{
				return lsAllRows;
			
			}
		}
		LIST OF ANYTYPE		Retrieve(STRING sTableName, STRING sIndex optional,
								STRING sQry optional, STRING sUID optional, STRING sPWD  optional, STRING sDB optional,
								STRING sSVR optional)
		{
			__sPassedTableName=sTableName;
			//Row Retrieval
			LIST OF ANYTYPE lTableData;
			LIST OF ANYTYPE lsRow;
			LIST OF STRING lRow;
			STRING sRow;
			STRING sField;
			switch Upper(Extension)
			{
				STRING sSQL;
				case "CSV":
					lCSVList = 
					{
					};
					lRow = 
					{
					};
					do
					{
						this.lsData = SYS_GetFileContents(this.sFileName);
					}
					except
					{
						if MatchStr("*File not found*",ExceptData())
						{
							Log.LogError("{this.sFileName} could not be opened. File not found.");
						}
						else
						{
							Log.LogError(TRUE);
						}
						ExceptClear();
					}
					for each sRow in this.lsData
					{
						lRow = MakeListFromCSV(sRow);
						ListAppend(lCSVList, lRow);
					}
					return lCSVList;
				case "XLS":
					lTableData = 
					{
					};
					lRow = 
					{
					};
					lsRow = 
					{
					};
					sRow = "";
					if sIndex != NULL
					{
						sSQL = 'SELECT * FROM  "{sTableName}$""{sTableName}$" WHERE "{sTableName}$".index={sIndex}';
					}
					else if sQry != NULL
					{
						sSQL = sQry;
					}
					else
					{
						sSQL = 'SELECT * FROM  "{sTableName}$""{sTableName}$"';
					}
					hRecord = GetDataSetHandle(sSQL);
					while (__DB_FetchNext (hRecord, id, lRow) == TRUE)
					{
						for each sRow in lRow
						{
							if sRow == NULL
							{
								sRow = "";
							}
							else
							{
								sRow = CleanData(sRow);
							}
							ListAppend(lsRow, sRow);
						}
						ListAppend(lTableData, lsRow);
						// Log.print(lsRow)
						lsRow = 
						{
						};
						lRow = 
						{
						};
					}
					__DB_FinishSQL(hRecord);
					__DB_Disconnect(hODBC);
					return lTableData;
					// ListAppend(lTableData, sTableName)
				case "DBF":
					lCSVList = 
					{
					};
					lRow = 
					{
					};
					r = 0;
					DSConnect();
					if sQry == NULL
					{
						sSQL = 'SELECT * FROM {sTableName}';
					}
					else
					{
						sSQL = sQry;
					}
					hRecord = GetDataSetHandle(sSQL);
					while (__DB_FetchNext (hRecord, id, lRow) == TRUE)
					{
						ListAppend(lCSVList, lRow);
					}
				case "SQL":
					lTableData = 
					{
					};
					lRow = 
					{
					};
					lsRow = 
					{
					};
					sRow = "";
					INTEGER iASCII;
					DSConnect(sUID, sPWD, sDB, sSVR);
					if sQry == NULL
					{
						sSQL = 'SELECT * FROM {sTableName}';
					}
					else
					{
						sSQL = sQry;
						ListAppend(lTableData, sTableName);
					}
					hRecord = __DB_ExecuteSql (hODBC, sSQL);
					while (__DB_FetchNext (hRecord, id, lRow) == TRUE)
					{
						for each sRow in lRow
						{
							if sRow == NULL || Asc(sRow) == 32
							{
								sRow="";
								ListAppend(lsRow, sRow);
							}
							else
							{
								sRow = CleanData(sRow);
								ListAppend(lsRow, sRow);
							}
						}
						ListAppend(lTableData, lsRow);
						lsRow = 
						{
						};
						lRow = 
						{
						};
					}
					__DB_FinishSQL(hRecord);
					__DB_Disconnect(hODBC);
					return lTableData;
				default:
				{
					Log.LogError("{Extension} is not a supported file in the cDATASOURCE Retrieve method.");
				}
			}
		}
		LIST OF ANYTYPE		RetrieveHeader(STRING dtType, STRING sTableName, STRING sQry optional,
								STRING sUID optional, STRING sPWD  optional, STRING sDB optional, STRING sSVR optional)
		{
			__sPassedTableName=sTableName;
			LIST OF ANYTYPE lTableData = {};
			LIST OF STRING lRow;
			LIST OF ANYTYPE lsRow;
			STRING sRow;
			switch (Extension)
			{
				case "XLS":
					// header row on
					STRING sTBSQL;
					sTBSQL = 'SELECT "TableData$".Nothing, "TableData$".{sTableName}  FROM "TableData$""TableData$"';
					hRecord = GetDataSetHandle(sTBSQL);
					while (__DB_FetchNext (hRecord, id, lRow) == TRUE)
					{
						for each sRow in lRow
						{
							if sRow == NULL
							{
								sRow = "";
							}
							else
							{
								sRow = CleanData(sRow);
							}
							ListAppend(lsRow, sRow);
						}
						ListAppend(lTableData, lsRow);
						// Log.print(lsRow)
						lsRow = 
						{
						};
						lRow = 
						{
						};
					}
					__DB_FinishSQL(hRecord);
					__DB_Disconnect(hODBC);
				// ListAppend(lTableData, lCSVList)
				return lTableData;
			}
		}
		VOID 				Update(STRING sWorksheet optional,STRING sIndex optional, STRING sColumn optional, STRING sColumnValue optional,STRING sUpdateSQL optional)
		{
			__sPassedTableName=sWorksheet;
			// VOID	Update(STRING dtType,STRING sTableName, LIST OF ANYTYPE lData, STRING sUID optional ,STRING sPWD  optional, STRING sDB optional, STRING sSVR optional)
			sColumnValue = '''{sColumnValue}''';
			STRING sSQL;
			r=0;
			switch Upper(Extension)
			{
				case "XLS":
					// for r = 2 to listcount(lData)
						// sSQL = "update {sTableName} SET "
						// for c = 1 to listcount(lData[1])-1
							// sSQL = sSQL + " {lData[1][c]} = '{lData[r][c]}' , "
						// sSQL = sSQL + "WHERE {lData[1][c+1]} = '{lData[r][c+1]}'"
						// sSQL = StrTran (sSQL, ", WHERE", " WHERE")
						// Log.print(sSQL)
						c=0;
					if !IsNull(sUpdateSQL)
					{
						sSQL = sUpdateSQL;
					}
					else
					{
						sSQL = 'UPDATE "{sWorksheet}$" "{sWorksheet}$" SET  "{sWorksheet}$".{sColumn} = {sColumnValue} WHERE "{sWorksheet}$".index=' + sIndex;
					}
					hRecord = GetDataSetHandle(sSQL);
					__DB_FinishSQL(hRecord);
					__DB_Disconnect(hODBC);
				case "SQL":
		
		// AMM 2004.11.05: ObjectRow/ObjectField
			}
		}
		VOID 				CreateDataObjectRow(OBJECT oDataObject optional)
		{
			OBJECT oCreateDataObject;
			STRING sCreateIndex = "";
			sCreateIndex = Str(this.RowCount(this.sTableName)+1);
			STRING sCreateItems = "index";
			STRING sCreateValues = "{sCreateIndex}";
			INTEGER i;
			STRING sValue ="";
			STRING sItem = "";
			if IsNull(oDataObject)
			{
				oCreateDataObject = this;
			}
			else
			{
				oCreateDataObject = oDataObject;
			}
			INTEGER iListCount = ListCount(oCreateDataObject.lsClassFieldList);
			STRING sThisListItem;
			STRING sDataObjectListItem;
			BOOLEAN bFoundItem = FALSE;
			for each sThisListItem in  oCreateDataObject.lsClassFieldList
			{
				for each sDataObjectListItem in this.lsClassFieldList
				{
					if {sThisListItem} == {sDataObjectListItem}
					{
						if !IsSet(oCreateDataObject.@(sDataObjectListItem))
						{
							oCreateDataObject.@(sDataObjectListItem) = "";
						}
						if oCreateDataObject.@(sDataObjectListItem) != ""
						{
							bFoundItem = TRUE;
							sItem = sDataObjectListItem;
							sValue = oCreateDataObject.@(sDataObjectListItem);
							sCreateItems = '{sCreateItems},{sItem}';
							sCreateValues = '{sCreateValues},''{sValue}''';
						}
					}
				}
			}
			STRING sCreateSQL = 'INSERT INTO "{this.sTableName}$" ({sCreateItems}) VALUES ({sCreateValues})';
			if !bFoundItem
			{
				sCreateSQL = 'INSERT INTO "{this.sTableName}$"  (index) VALUES ({sCreateIndex})';
			}
			do
			{
				this.Update(NULL,NULL,NULL,NULL,sCreateSQL);
			}
			except
			{
				print("CreateSQL: {sCreateSQL}");
				reraise;
			}
			sCreateSQL = "";
			sCreateItems = "";
			sCreateItems= "";
			this.sIndex = sCreateIndex;
			this.ReadDataObjectRow();
		}
		VOID				ReadDataObjectRow(OBJECT oDataObject optional)
		{
			OBJECT oReadDataObject;
			if IsNull(oDataObject)
			{
				oReadDataObject = this;
			}
			else
			{
				oReadDataObject = oDataObject;
			}
			STRING sSQL = "";
			// if IsNull(sWhereAttribute)
				// this.PopulateFromSheet(oReadDataObject.sTableName,oReadDataObject.sIndex)
			// else
				// STRING sData = ""
				// LIST OF STRING rsRow
				// sSQL = 'SELECT "{this.sTableName}$".index FROM  "{this.sFileName}$""{this.sFileName}$" WHERE "{this.sTableName}$".{@(sWhereAttribute)}={sWhereAttributeValue}'
				// hRecord = GetDataSetHandle(sSQL)
				// do
					// while (__DB_FetchNext (hRecord, id, rsRow) == TRUE)
						// //start a counter of rows
						// lsRow = {}
						// r++
						// //analyze each item and clean it up.
						// for each sItem in rsRow
							// if sItem == NULL
								// sItem = ""
							// else
								// sItem = CleanData(sItem)
							// //append each item to a new list
							// ListAppend(lsRow, sItem)
						// //append the cleaned rows to another list
						// ListAppend(lsAllRows,lsRow)
				// except
					// // printing exception and class data used to happen here, now it happens in the primitaves
					// ExceptClear()
					// reraise
				// //if the query only returned one row then just send the new list
				// __DB_FinishSQL(hRecord)
				// __DB_Disconnect(hODBC)
				// if r ==1
					// return lsRow
				// //otherwise send the multiple list
				// else
					// return lsAllRows
				// 
				// 
			this.PopulateFromSheet(oReadDataObject.sTableName,oReadDataObject.sIndex);
		}
		VOID				UpdateDataObjectRow(OBJECT oDataObject optional, STRING sWhereAttribute optional, BOOLEAN bReadInRow optional)
		{
			if IsNull(bReadInRow)
			{
				bReadInRow = TRUE;
			}
			OBJECT oUpdateDataObject;
			STRING sWhereClause ="";
			STRING sThisListItem ="";
			STRING sDataObjectListItem ="";
			BOOLEAN bFoundItem = FALSE;
			STRING sUpdateNVPair = "";
			if IsNull(oDataObject)
			{
				oUpdateDataObject = this;
			}
			else
			{
				oUpdateDataObject = oDataObject;
			}
			if IsNull(sWhereAttribute)
			{
				sWhereClause = 'WHERE "{this.sTableName}$".index={this.sIndex}';
			}
			else
			{
				sWhereClause = 'WHERE "{this.sTableName}$".{sWhereAttribute}=''{this.@(sWhereAttribute)}''';
			}
			STRING sUpdateClause = 'UPDATE "{this.sTableName}$" "{this.sTableName}$" SET';
			// STRING sUpdateNVPair = '""{this.sTableName}$".RowKey ="{this.sIndex}"'
			// if this.sIndex != ""
				//  sUpdateNVPair ='""{this.sTableName}$".{this.lsClassFieldList[1]} = ''{this.sIndex}'''
			INTEGER i;
			INTEGER iListCount = ListCount(this.lsClassFieldList);
			STRING sValue ="";
			for each sDataObjectListItem in  oUpdateDataObject.lsClassFieldList
			{
				for each sThisListItem in this.lsClassFieldList
				{
					if {sThisListItem} == {sDataObjectListItem}
					{
						if !IsSet(oUpdateDataObject.@(sDataObjectListItem))
						{
							oUpdateDataObject.@(sDataObjectListItem) = "";
						}
						if oUpdateDataObject.@(sDataObjectListItem) != ""
						{
							sValue = '''{oUpdateDataObject.@(sDataObjectListItem)}''';
							sUpdateNVPair = '{sUpdateNVPair}, "{this.sTableName}$".{sDataObjectListItem} = {sValue}';
			// for i = 1 to iListCount
				// sValue = '''{oUpdateDataObject.@(oUpdateDataObject.lsClassFieldList[i])}'''
				// sUpdateNVPair = '{sUpdateNVPair}, "{this.sTableName}$".{oUpdateDataObject.lsClassFieldList[i]} = {sValue}'
						}
					}
				}
			}
			sUpdateNVPair = SubStr(sUpdateNVPair,2);
			STRING sUpdateSQL = '{sUpdateClause} {sUpdateNVPair} {sWhereClause}';
			// print(sUpdateSQL)
			this.Update(this.sTableName,NULL,NULL,NULL,sUpdateSQL);
			//using a different where clause indicates i'm not updating the row by index
			// therefore i don't know what the index is and cannot read back in the object data
			// so i skip reading the object back in after update.
			if IsNull(sWhereAttribute)
			{
				bReadInRow = FALSE;
			}
			if bReadInRow
			{
				this.ReadDataObjectRow();
			}
		}
		VOID				DeleteDataObjectRow(OBJECT oDataObject optional)
		{
			OBJECT oDeleteDataObject;
			
			if IsNull(oDataObject)
			{
				oDeleteDataObject = this;
			}
			else
			{
				oDeleteDataObject = oDataObject;
			}
			this.Update(this.sTableName,this.sIndex,"index","0");
		}
		VOID 				UpdateDataObjectField(STRING sDataObjectField, STRING sDataObjectFieldValue, BOOLEAN bReadInRow optional)
		{
			if IsNull(bReadInRow)
			{
				bReadInRow = TRUE;
			//two ways to build the sql statement.
			//this builds the statement by taking the value and using it as a pointer into the attribute 
			//that needs to be updated.
			}
			do
			{
				this.@(sDataObjectField) = sDataObjectFieldValue;
			}
			except
			{
				if MatchStr("*is not defined in window*",ExceptData())
				{
					// ignore
				}
				else
				{
					Log.print(ExceptData());
				}
				ExceptClear();
			//the other is to simply take what values are given and update using those values.
			}
			do
			{
				this.Update(this.sTableName, this.sIndex, sDataObjectField, sDataObjectFieldValue);
			}
			except
			{
				Log.ExceptPrint();
				ExceptClear();
			}
			if bReadInRow
			{
				this.ReadDataObjectRow();
			}
		}
		STRING				ReadDataObjectField(STRING sColumnName)
		{
			INTEGER iColumn = ListFind(this.lsClassFieldList,sColumnName);
			STRING sTableName = this.sTableName;
			STRING sWorksheet = this.sFileName;
			STRING sIndex = this.sIndex;
			STRING sSQL = 'SELECT "{this.sTableName}$".{sColumnName} FROM  "{this.sFileName}$""{this.sFileName}$" WHERE "{this.sTableName}$".index={this.sIndex}';
			return this.RetrieveXLS(this.sTableName,this.sIndex,sColumnName)[iColumn];
		
		// AMM 2004.11.05: Population methods
		}
		OBJECT				PopulateFields(STRING dType optional,STRING sTableName, STRING sIndex)
		{
			__sPassedTableName=sTableName;
			OBJECT PopObject;
			LIST OF ANYTYPE lData;
			lData = this.Retrieve(sTableName,sIndex);
			// print(this.lsClassFieldList)
			// print(lData[1])
			PopObject= this.SelectiveAssignValues(this.lsClassFieldList, lData[1]);
			this.sIndex = sIndex;
			this.sTableName = sTableName;
			return PopObject;
		}
		OBJECT 				PopulateFromSheet(STRING sSheet, ANYTYPE iRow)
		{
			LIST OF STRING lsHeaders=GetHeaders(sSheet);
			this.SelectiveAssignValues(lsHeaders,this.RetrieveXLS(sSheet,"{iRow}"));
			return this;
		}
		OBJECT 				PopulateClassFromSheet(ANYTYPE iRow)
		{
			return PopulateFromSheet("{this.sTableName}",iRow);
		}
		LIST OF OBJECT		CreateObjectListFromSheet(LIST OF ANYTYPE lsFilters optional)
		{
			// in this method, we gather all the data at once, and do the assignments to
			// the objects individually, rather than using PopulateFromSheet() The reason
			// is that it's more than 100x faster to do it this way, rather than making
			// repeated ODBC calls.
			
			ANYTYPE aData;
			STRING sSheet = "{this.sTableName}";
			LIST OF STRING lsHeaders = this.GetHeaders(sSheet);
			if IsNull(lsFilters)
			{
				aData = this.RetrieveXLS(sSheet);
			}
			else
			{
				STRING sFilterClause = "";
				LIST OF STRING sPair = {};
				STRING sValue = "";
				for each sPair in lsFilters
				{
					if IsDigit(sPair[2])
					{
						sValue = sPair[2];
					}
					else
					{
						sValue = "'{sPair[2]}'";
					}
					sFilterClause = '{sFilterClause}"{sSheet}$".{sPair[1]}={sValue} AND ';
				}
				sFilterClause=Left(sFilterClause,Len(sFilterClause)-5);
				// print(sFilterClause)
				STRING sSQL = 'SELECT * FROM  "{sSheet}$""{sSheet}$" WHERE {sFilterClause}';
				// print(sSQL)
				aData = this.Retrieve(sSheet,NULL,sSQL);
			}
			LIST OF OBJECT loResults = {};
			ANYTYPE item;
			for each item in aData
			{
				if ! IsVarList(item)
				{
					item={item};
				}
				OBJECT Current = @(this.sTableName)(this.sFileName).SelectiveAssignValues(lsHeaders,item);
				if IsDigit(item[1][1])
				{
					Current.sIndex = item[1];
				}
				ListAppend(loResults,Current);
			}
			return loResults;
		
		}
		OBJECT				CreateSearchableListObject()
		{
			OBJECT Result = cSEARCHABLELIST();
			Result.d=this.RetrieveXLS(this.sTableName);
			Result.lsFieldNames=this.GetHeaders(this.sTableName);
			return Result;
		}
		OBJECT				CreateSearchableListObjectWithObjects()  // returns searchable list with additional column on the end
		{
			OBJECT BulkData = this.CreateSearchableListObject();
			BulkData.AddColumn(CreateObjectListFromSheet(),"{this.Class}_Objects");
			return BulkData;
																	 // name of column will be "{this.Class}_Objects"
		
		// AMM 2004.11.05: Other support members
		}
		INTEGER				RowCount(STRING sTableName, STRING sFilter optional)
		{
			__sPassedTableName=sTableName;
			// Row Count
			INTEGER iRows;
			STRING sTBSQL;
			DSConnect();
			if sFilter == NULL
			{
				sTBSQL = 'SELECT count("{sTableName}$".index), count("{sTableName}$".index)  FROM "{sTableName}$""{sTableName}$"';
			}
			else
			{
				sTBSQL = 'SELECT count("{sTableName}$".index), count("{sTableName}$".index)  FROM "{sTableName}$""{sTableName}$" WHERE "{sTableName}$".{sFilter}';
			}
			hRecord = GetDataSetHandle(sTBSQL);
			while (__DB_FetchNext (hRecord, id, iRows) == TRUE)
			return iRows;
		}
		BOOLEAN 			TableExists(STRING sTableName)
		{
			__sPassedTableName=sTableName;
			BOOLEAN bResult;
			switch Upper(Extension)
			{
				STRING sSQL;
				case "CSV":
					bResult = TRUE;
				case "XLS":
					DSConnect();
					do
					{
						sSQL = 'SELECT * FROM  "{sTableName}$""{sTableName}$"';
						hRecord = __DB_ExecuteSql (hODBC, sSQL);
						bResult = TRUE;
					}
					except
					{
						if MatchStr("*is not a valid name*",ExceptData())
						else
						{
							Log.LogError(ExceptData(),TRUE );
						}
						bResult = FALSE;
						ExceptClear();
					}
					__DB_FinishSQL(hRecord);
					__DB_Disconnect(hODBC);
				default:
				{
					bResult = FALSE;
				}
			}
			return bResult;
		}
		LIST OF STRING		GetHeaders(STRING sSheet)
		{
			// Open this for the old, Buggy way we did this
			{
				// // find headers
				// LIST OF STRING lsQuickSheetList = {}
				// INTEGER i
				// LIST OF ANYTYPE lsResults = {}
				// for each item in lsHeaders
				{
					// if trim(item[1]) != ""
					{
						// for i = ListCount(item) to 1 step -1
						{
							// if trim(item[i]) == ""
							{
								// ListDelete(item,i)
							// else
								// i = 1
								// break
						// ListAppend(lsQuickSheetList,Upper(item[1]))
						// ListDelete(item,1) // Remove sheet name
						// ListDelete(item,1) // Remove index
						// ListAppend(lsResults,item)
						// //Log.print(item)
				//
				// // find sheet
				// // Log.ListPrint(lsQuickSheetList)
				// INTEGER iSheetPointer=ListFind(lsQuickSheetList,Upper(sSheet))
				// //Log.print(iSheetPointer)
				// //Log.print(lsResults[iSheetPointer])
				//
				// // Now call selective populate fields with the data!
				// //Log.print(lsResults[iSheetPointer])
				// //Log.print(this.RetrieveXLS(sSheet,"{iRow}"))
			
							}
						}
					}
				}
			}
			ANYTYPE lsHeaders = this.lsClassFieldList;
			do
			{
				lsHeaders=this.RetrieveXLS("HeaderLists");
				LIST OF STRING lsResult = {};
				INTEGER i,p=0;
				// print("Headers: {lsHeaders}")
				for i = 1 to ListCount(lsHeaders)
				{
					if lsHeaders[i][1]==sSheet
					{
						p=i;
						break;
				
					}
				}
				if p==0
				{
					raise 1,"*** Error: Header list not found for sheet named '{sSheet}' in Excel file '{this.sFileName}'";
				
				}
				lsResult=lsHeaders[p];
				ListDelete(lsResult,1); // Remove index
				ListDelete(lsResult,1); // Remove sheet name
				
				for i = ListCount(lsResult) to 1 step -1
				{
					if trim(lsResult[i])==""
					{
						ListDelete(lsResult,i);
					}
				}
			}
			except
			{
				// nada 
				ExceptClear();
			
			}
			return lsResult;
		
		// AMM 2004.11.05: Debugging tools?
		}
		VOID 				PrintAttributes()
		{
			STRING sAttribute;
			print(this.lsClassFieldList);
			for each sAttribute in this.lsClassFieldList
			{
				do
				{
					print("{sAttribute}: {this.@(sAttribute)}");
				}
				except
				{
					print("Bad Field: {sAttribute}");
					ExceptClear();
		
				}
			}
		}
		const dcInheritsFrom = cFILE;
		const lsClassFieldList    = {'lCSVList','hRecord','hODBC','lRow','r','c','id'};
		const lsClassPropertyList = {};
		
		// AMM 2004.11.05: Any reason these aren't private?
		HANDLE				hRecord = NULL;
		HANDLE				hODBC = NULL;
		LIST OF STRING		lRow = NULL;
		INTEGER 			r  = NULL;
		INTEGER				c = NULL;
		INTEGER				id = NULL;
		
		VOID				DSConnect(STRING sUID optional ,STRING sPWD  optional, STRING sDB optional,STRING sSVR optional)
		{
			//		DSConnect: Data Source Connection String: Returns the correct DSN file STRING parameters based on file type
			BOOLEAN bKeepTrying = TRUE;
			STRING sConnect;
			STRING sPath;
			INTEGER iCountdown = 120, i;
			
			switch Upper(Extension)
			{
				case "SQL":
					sConnect = "DRIVER=SQL Server;UID={sUID};PWD={sPWD};DATABASE={sDB};SERVER={sSVR}";
					if ! this.bExists
					{
						raise LIBERROR_FILE_NOT_FOUND,"File not found on cDATASOURCE({this.sFileName}).DSConnect()";
					}
				case "DBF":
					sConnect = "DRIVER=Microsoft Visual FoxPro Driver;SourceDB={this.sDirectoryPart};SourceType={this.sExtensionPart}";
					if ! this.bExists
					{
						raise LIBERROR_FILE_NOT_FOUND,"File not found on cDATASOURCE({this.sFileName}).DSConnect()";
					}
				case "XLS":
					sConnect = "DRIVER=Microsoft Excel Driver (*.xls);ReadOnly=0;DBQ= {this.sFileName};";
					if ! this.bExists
					{
						raise LIBERROR_FILE_NOT_FOUND,"File not found on cDATASOURCE({this.sFileName}).DSConnect()";
					}
				case "CSV","TXT":
					sConnect = "{this.sFileName}";
					if ! this.bExists
					{
						raise LIBERROR_FILE_NOT_FOUND,"File not found on cDATASOURCE({this.sFileName}).DSConnect()";
			
					}
			}
			for i=iCountdown to 1 step -1
			{
				if !IsNull(hODBC)
				{
					do
					{
						__DB_Disconnect(hODBC, TRUE);
					}
					except
					{
						//nada
						ExceptClear();
				
					}
				}
				do
				{
					hODBC = __DB_Connect(sConnect, TRUE);
					if hODBC != NULL
					{
						break;
					}
				}
				except
				{
					// nada
					print(ExceptData());
					ExceptClear();
				
				}
				if i == 1
				{
					DisplayErrorData();
					reraise;
				
				}
				sleep(1);
			}
		}
		STRING				CleanData(STRING sField)
		{
			INTEGER iPos;
			if StrPos("'", sField) == 1
			{
				sField=StrTran(sField, "'","");
			}
			sField=StrTran(sField, ".000000","");
			// sField=Upper(sField)
			sField=trim(sField);
			sField = this.__NormalizeString(sField);
			return sField;
		}
		HANDLE 				GetDataSetHandle(STRING sSQL)
		{
			DSConnect();
			hRecord = __DB_ExecuteSql (hODBC, sSQL);
			return hRecord;
		}
		OBJECT				CreateObjectFromString(STRING sDataObject, STRING sDataFile)
		{
			OBJECT oUserDataObject = NULL;
			const INTEGER OBJECTNAME = 1;
			const INTEGER OBJECTVALUE = 2;
			const INTEGER OBJECTPARAM = 3;
			LIST OF ANYTYPE laUserDataAsList = cSystem.ConvertStringToList(sDataObject);
			STRING sUserDataElement = "";
			oUserDataObject = @("{laUserDataAsList[1][OBJECTNAME]}")(sDataFile);
			oUserDataObject.PopulateFromSheet(laUserDataAsList[1][OBJECTNAME],laUserDataAsList[1][OBJECTVALUE]);
			return oUserDataObject;
			
		
		////////////////////////////////////////////////////////////////////////////
		// PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
			// helper method
			STRING __NormalizeString(ANYTYPE Incoming NULL)
			{
				if Incoming==NULL
				{
					Incoming="";
				}
				Incoming="{Incoming}";
				return Incoming;
			
			
			}
			const lsPrivateClassFieldList    = {};
			const lsPrivateClassPropertyList = {};
			
			VOID				DisplayErrorData()
			{
				Log.ResOpenList("ODBC Failure Data:");
				// show class level data
				Log.print("--class data--");
				Log.print("sFileName    :{sFileName}");
				Log.print("hODBC        :{hODBC}");
				Log.print("hRecord      :{hRecord}");
				Log.print("lsData       :{lsData}");
				Log.print("lCSVList     :{lCSVList}");
				Log.print("r            :{r}");
				Log.print("c            :{c}");
				Log.print("id           :{id}");
				// show local data
				Log.print("--local data--");
				Log.print("sConnect string      :{__sConnect}");
				Log.print("Last fetch result    :{__aLastFetchResult}");
				Log.print("SQL Code             :{__sSQL}");
				Log.print("Row to Retrieve      :{sIndex}");
				Log.print("worksheet/table name	:{__sPassedTableName}");
				Log.print("sIndex               :{sIndex}");
				
				//Log.print("Filter by columns:   				  			 :{sColumn}")
				//Log.print("Filter column value      						 :{sColumnValue}")
				//Log.print("Rows retrieved						  			 :{lsAllRows}")
				//Log.print("List of Rows being processed       	  			 :{lsRow}")
				//Log.print("Row being processed at time of error 			 :{rsRow}")
				//Log.print("Data item getting retrieved from recordset        :{sItem}")
				// debugprint
				//Log.print("--DebugPrint()--")
				//DebugPrint()
				Log.ResCloseList();
			
			}
			HANDLE				__DB_Connect(STRING sConnect, BOOLEAN fDontReport optional)
			{
				if fDontReport==NULL
				{
					fDontReport=FALSE;
				}
				__DB_CallName = "DB_Connect";
				ANYTYPE result;
				__sConnect=sConnect;
				do
				{
					hODBC = DB_Connect(sConnect);
				}
				except
				{
					if ! fDontReport
					{
						DisplayErrorData();
					}
					reraise;
				}
				return hODBC;
			}
			ANYTYPE 			__DB_FetchNext(HANDLE hRecord, out ANYTYPE arg2, out ANYTYPE arg3)
			{
				__DB_CallName = "DB_FetchNext";
				ANYTYPE result;
				do
				{
					result=DB_FetchNext (hRecord, id, arg3);
				}
				except
				{
					if MatchStr("*Numeric field overflow*",ExceptData())
					{
						Log.print("A column in the spreadsheet being accessed has inconsistent data. Numbers in one cell and text in cells above or below the text, or text in a cell and TRUE or FALSE in cells above or below the text. Columns must contain the same type of data.");
					}
					DisplayErrorData();
					reraise;
				}
				__aLastFetchResult=result;
				return result;
			}
			VOID 				__DB_FinishSQL(HANDLE hRecord)
			{
				__DB_CallName = "DB_FinishSQL";
				do 
				{
					DB_FinishSQL(hRecord);
				}
				except
				{
					DisplayErrorData();
					reraise;
				}
			}
			VOID 				__DB_Disconnect(HANDLE hODBC, BOOLEAN fDontReport optional)
			{
				if fDontReport==NULL
				{
					fDontReport=FALSE;
				}
				__DB_CallName = "DB_Disconnect";
				do
				{
					DB_Disconnect(hODBC);
				}
				except
				{
					if ! fDontReport
					{
						DisplayErrorData();
					}
					reraise;
				
				}
			}
			HANDLE				__DB_ExecuteSql(HANDLE hODBC, STRING sSQL)
			{
				__sSQL=sSQL;
				__DB_CallName = "DB_ExecuteSQL";
				do
				{
					hRecord = DB_ExecuteSql (hODBC, sSQL);
				}
				except
				{
					hRecord = NULL;
					select
					{
						case MatchStr("*Operation must use an updateable query*",ExceptData()):
							INTEGER i = 0;
							while IsNull(hRecord)
							{
								do
								{
									hRecord = DB_ExecuteSql (hODBC, sSQL);
								}
								except
								{
									i++;
									print("Trying to connect: {i}");
									ExceptClear();
									if i == 20
									{
										Log.LogError("Cannot connect to spreadsheet. Tried {i} times. Better luck next time.");
										break;
									}
								}
							}
						case MatchStr("*Too few parameters*",ExceptData()):
							Log.print(sSQL);
							Log.print("The SQL Query is incorrect. Be sure the column you are searching on exists in the table and that the where clause is correct.");
							reraise;
						default:
						{
							Log.print(sSQL);
							DisplayErrorData();
							reraise;
						}
					}
					ExceptClear();
				}
				return hRecord;
			
			}
			STRING  			__sConnect = NULL;
			ANYTYPE 			__aLastFetchResult = NULL;
			STRING  			__DB_CallName = NULL;
			STRING  			__sSQL = NULL;
			STRING  			__sPassedTableName = "{ClassOf(this)}";
			
			
		////////////////////////////////////////////////////////////////////////////
		// VOID 				CreateDataObjectRow(OBJECT oDataObject optional)
			// OBJECT oCreateDataObject
			// STRING sCreateIndex = ""
			// sCreateIndex = Str(this.RowCount(this.sTableName)+1)
			// STRING sCreateItems = "index"
			// STRING sCreateValues = "{sCreateIndex}"
			// INTEGER i
			// STRING sValue =""
			// if IsNull(oDataObject)
			{
				// oCreateDataObject = this
			// else
				// oCreateDataObject = oDataObject
			// INTEGER iListCount = ListCount(oCreateDataObject.lsClassFieldList)
			// for i = 1 to iListCount
				// if IsSet(oCreateDataObject.@(oCreateDataObject.lsClassFieldList[i]))
				{
					// sValue = oCreateDataObject.@(oCreateDataObject.lsClassFieldList[i])
				// // sValue = AddAposToColumnValue(sValue)
				// sCreateItems = '{sCreateItems},{oCreateDataObject.lsClassFieldList[i]}'
				// sCreateValues = '{sCreateValues},''{sValue}'''
			// STRING sCreateSQL = 'INSERT INTO "{this.sTableName}$" ({sCreateItems}) VALUES ({sCreateValues})'
			// print(sCreateSQL)
			// this.Update(NULL,NULL,NULL,NULL,sCreateSQL)
			// this.sIndex = sCreateIndex
			// this.ReadDataObjectRow()
		
		
	
	
	////////////////////////////////////////////////////////////////////////////
	// cBAG					Generic data carrier
	// cVERIFYBAG			Generic verify data carrier
	//
	////////////////////////////////////////////////////////////////////////////
	// bag is generic data container, so here’s a way to have generic data containers
				}
			}
		}
	}
	winclass cBAG : cDATASOURCE
	{
		
		property 	lsFieldNames
		{
			LIST OF STRING Get()
			{
				return this.__d.lsFieldNames;
			}
			VOID Set(LIST OF STRING lsNewFieldNames)
			{
				this.__d.lsFieldNames=lsNewFieldNames;
		
			}
		}
		property 	d
		{
			ANYTYPE Get()
			{
				return this.__d.d;
			}
			VOID Set(LIST newdata)
			{
				this.__d.d=newdata;
		
			}
		}
		property 	sKey
		{
			
			ANYTYPE Get()
			{
				return this.__d.GetField("sKey");
			
			}
			VOID Set(ANYTYPE sKeyIn NULL)
			{
				this.__d.RowSelector=sKeyIn;
			}
		}
		property 	aData
		{
			ANYTYPE Get()
			{
				return this.__d.GetField("aData");
			}
			VOID Set(ANYTYPE aInData)
			{
				this.__d.SetField("aData",aInData);
			
		
			}
		}
		property 	iNumItems 
		{
			INTEGER Get()
			{
				return this.__d.iNumRows;
		
		// returns all the items in this container as a list of rows
			}
		}
		ANYTYPE 	GetItems()
		{
			return this.__d.d;
		
		// updates an item (if item isn’t existent, adds it) 
		}
		INTEGER		AddItem(varargs lIncoming NULL) // ARG1 is always the key, other args MUST MATCH FIELD LIST ORDER!
		{
			//STRING sKeyIn, ANYTYPE aInData,...
			
			OBJECT lRow=this.__AddUpdateCommon(lIncoming);
			this.__d.AddRow(lRow.d);
			
			return this.__d.iLength;
			
		}
		VOID 		UpdateItem(varargs lIncoming NULL) // ARG1 is always the key, other args MUST MATCH FIELD LIST ORDER!
		{
			//STRING sKeyIn, ANYTYPE aInData,...
			
			OBJECT lRow=this.__AddUpdateCommon(lIncoming);
			
			// does the row already exist?
			if this.__d.CurrentRow==NULL
			{
				// no, create it
				this.__d.AddRow(lRow.d);
			}
			else
			{
				// yes, update it
				this.__d.CurrentRow=lRow.d;
			
		
		
			}
		}
		OBJECT 		PopulateFromSheet(STRING sSheet, ANYTYPE aRow) // reads sheet headers and populates based on MATCHING FIELD NAMES!
		{
			LIST OF STRING lsHeaders=GetHeaders(sSheet);
			ANYTYPE TheData = this.RetrieveXLS(sSheet,"{aRow}");
			ANYTYPE p,i,item;
			//i believe this is where cDATAOBJECTBAG is having trouble getting populated
			if this.__d.lsFieldNames == NULL
			{
				this.__d.lsFieldNames = lsHeaders;
			
			}
			if ! IsVarList(TheData[1])
			{
				TheData={TheData};
			
			}
			for each item in TheData
			{
				
				OBJECT lRow = cLIST().CreateWith({});
				if lsHeaders != {}
				{
					
					for p=1 to this.__d.iNumCols
					{
						
						i=ListFind(lsHeaders,lsHeaders[p]); // find the position of the current expected field in the data
						if i > 0
						{
							lRow.Append(item[i]);
						}
						else
						{
							lRow.Append(NULL);
						}
						if i == ListCount(lsHeaders)
						{
							break;
					// OK, now lRow should match the expected input for adding a row if it doesn't exist
						}
					}
					this.__d.AddRow(lRow.d);
				
				}
				else
				{
					
					// got no headers. Hope we have the right data!
					// field orders must match 
					
					while ListCount(item) < this.__d.iNumCols
					{
						ListAppend(item,NULL);
					
					// padded to length, now cross our fingers and commit
					}
					this.__d.AddRow(item);
					
					
				
			
				}
			}
			return this;
			
		}
		VOID		Zap() // resets the data
		{
			this.__d.d={};
		}
		INTEGER 	Field(STRING sFieldID)
		{
			return ListFind(this.lsFieldNames,sFieldID);
		
		}
		VOID		Merge(OBJECT oBag)
		{
			this.__d.Merge(oBag.__d.d);
			oBag.__d.d = {};
		
		////////////////////////////////////////////////////////////////////////////
		// Private members, do not use outside of class
			cSEARCHABLELIST __d	// d=data!
			{
				LIST OF STRING lsFieldNames = {"sKey","aData"};
			}
			OBJECT			__AddUpdateCommon(LIST lIncoming NULL) // ARG1 is always the key, other args MUST MATCH FIELD LIST ORDER!
			{
				//STRING sKeyIn, ANYTYPE aInData,...
				
				if (ListCount(lIncoming) == 1) && IsVarList(lIncoming[1])
				{
					lIncoming=lIncoming[1];
				
				}
				STRING sKeyIn=lIncoming[1];
				
				// Make Row
				ANYTYPE item ;
				OBJECT lRow=cLIST().CreateWith({});
				for each item in lIncoming
				{
					lRow.Append(item);
				}
				if lRow.iLength < this.__d.iNumCols
				{
					for item = 1 to (this.__d.iNumCols - lRow.iLength)
					{
						lRow.Append(NULL);
				
					}
				}
				this.__d.ColumnSelector=1;
				this.__d.RowSelector=sKeyIn;
				
				return lRow ;
				
		////////////////////////////////////////////////////////////////////////////
		
		
		// Obsolete ////////////////////////////////////////////////////////////////
			
			
			// VOID UpdateItem(STRING sKeyIn, ANYTYPE aInData NULL) 
				// this.__d.ColumnSelector=1
				// this.__d.RowSelector=sKeyIn
				// 
				// // does the row already exist?
				// if this.__d.CurrentRow==NULL
				{
					// // no, create it
					// this.__d.AddRow({sKeyIn,aInData})
				// else
					// // yes, update it
					// this.__d.CurrentRow={sKeyIn,aInData}
				// 
			// The old way of doing it
				// property sKey
					// 
					// STRING Get()
					{
						// return this.__sQuickKey
					// 
					// VOID Set(ANYTYPE sKeyIn NULL)
						// if IsVarNumber(sKeyIn)
						{
							// this.__iQuickPointer=sKeyIn
							// this.__sQuickKey=this.__lsKeys[this.__iQuickPointer]
							// 
						// else
							// this.__sQuickKey=sKeyIn
							// this.__iQuickPointer=NULL
							// if sKeyIn != NULL
							{
								// this.__iQuickPointer=this.__FindItem(sKeyIn)
								// if this.__iQuickPointer==0
								{
									// this.__iQuickPointer=NULL
									// this.__sQuickKey=NULL
				// property aData
					// 
					// ANYTYPE Get()
						// return this.__GetProperty(this.__laData)
					// 
					// VOID Set(ANYTYPE aInData)
						// this.__SetProperty(this.__laData, aInData)
				// 
				// property iNumItems 
					// INTEGER Get()
						// return ListCount(this.__lsKeys)
				// 
				// VOID AddItem(STRING sKeyIn, ANYTYPE aInData NULL)
					// this.UpdateItem(sKeyIn, aInData)
				// 
				// // updates an item (if item isn’t existent, adds it) 
				// VOID UpdateItem(STRING sKeyIn, ANYTYPE aInData NULL) 
					// 
					// INTEGER i = this.__FindItem(sKeyIn)
					// 
					// if i == 0
						// this.__AddItem(sKeyIn,aInData)
					// else
						// this.__laData[i]=aInData
					// 
				// 
				// // returns an item in the form {sItem, aInData, ...}
				// ANYTYPE GetItem(ANYTYPE sKeyIn) // returns NULL if item not found
					// return this.__GetEntry(sKeyIn)
				// 
				// // returns an item’s data as a list
				// ANYTYPE GetItemData(STRING sKeyIn) // returns NULL if item not found
					// return this.GetItem(sKeyIn)[2]
				// 
				// // returns all the items in this bean as a list of list
				// ANYTYPE GetItems()
					// ANYTYPE aResult=NULL
					// INTEGER i
					// if iNumItems > 0
						// aResult={}
						// for i = 1 to iNumItems
							// ListAppend(aResult,this.GetItem(i))
					// return aResult
				// 
				// // removes item if it exists
				// VOID RemoveItem(STRING sKeyIn)
					// this.__RemoveEntry(sKeyIn)
				// 
				// OBJECT PopulateFromSheet(STRING sSheet, ANYTYPE iRow)
					// LIST OF STRING lsHeaders=GetHeaders(sSheet)
					// ANYTYPE TheData = this.RetrieveXLS(sSheet,"{iRow}")
					// ANYTYPE p
					// for p=1 to ListCount(lsHeaders)
						// this.UpdateItem(lsHeaders[p],TheData[p])
					// return this
				// 
				// INTEGER Field(STRING sFieldID)
					// return ListFind(this.lsFieldHeaders,sFieldID)
				// ANYTYPE GetAField(STRING sKeyIn, STRING sFieldID)
					// this.sKey=sKeyIn
					// return this.GetItem(sKeyIn)[this.Field(sFieldID)]
				// 
				// const LIST OF STRING lsFieldHeaders={...}
					// "sKey"
					// "aData"
				// ///////////////////////////////////////////////////////////////////
					// 
					// // THESE MUST BE REDEFIED WHEN FIELDS ADDED
						// LIST OF STRING __lsVirtualFields = {...}
							// "__lsKeys"
							// "__laData"
						// LIST OF STRING __lsVirtualFields__Private = {...}
							// 
						// LIST OF STRING __lsPropertiesToPublish = {...}
							// 
						// 
					// ///////////////////////////////////////////
					// 
					// property __AllVirtualFields
						// LIST Get()
							// LIST one=this.__lsVirtualFields
							// ListMerge(one,this.__lsVirtualFields__Private)
							// return one
					// property __PublicVirtualFields
						// LIST Get()
							// LIST one=this.__lsVirtualFields
							// ListMerge(one,this.__lsPropertiesToPublish)
							// return one
					// 
					// ANYTYPE __GetEntry(ANYTYPE sKeyIn)
						// // first save off global sKey, since we might be cycling thru all the sKeys
						// ANYTYPE aLocal_sKey=NULL
						// do 
							// aLocal_sKey=this.sKey
						// except
							// aLocal_sKey=NULL
						// 
						// // now figure out what virtual row we're being asked for
						// INTEGER i = 0
						// 
						// if IsVarInteger(sKeyIn)
							// i=sKeyIn
							// sKeyIn=this.__lsKeys[sKeyIn]
						// else
							// i = this.__FindItem(sKeyIn)
						// 
						// ANYTYPE Result=NULL
						// 
						// // if we have a valid row pointer, now we have to loop thru the fields and
						// // build the record
						// if i>0
							// // because some of the properties might key off of sKey, we'll need to set
							// // it to the same row selector we're being asked for
							// this.sKey=this.__lsKeys[i]
							// 
							// // now assemble the record
							// ANYTYPE item
							// Result={}
							// for each item in this.__PublicVirtualFields
								// do
									// ListAppend(Result,this.@(item)[i])
								// except
									// if MatchStr("*Unexpected NULL*",ExceptData())
									{
										// ListAppend(Result,NULL)
									// else
										// reraise
						// 
						// // finally reset the global sKey back to what it was when we came in
						// this.sKey=aLocal_sKey
						// 
						// return Result
					// INTEGER __AddListEntry()
						// ANYTYPE item
						// for each item in this.__AllVirtualFields
							// ListAppend(this.@(item),NULL)
						// return this.iNumItems
					// VOID 	__RemoveEntry(STRING sKeyIn)
						// INTEGER i = this.__FindItem(sKeyIn)
						// ANYTYPE item
						// 
						// if i>0
							// for each item in this.__AllVirtualFields
								// ListDelete(this.@(item),i)
						// 
					// 
					// INTEGER __iQuickPointer = NULL
					// STRING  __sQuickKey = NULL
					// 
					// INTEGER	__AddItem(STRING sKeyIn, ANYTYPE aInData NULL)
						// INTEGER i = this.__FindItem(sKeyIn)
						// if i==0
							// i=this.__AddListEntry()
						// if i>0
							// this.__lsKeys[i]=sKeyIn
							// this.__laData[i]=aInData
						// return i
					// ANYTYPE	__GetProperty(inout LIST ListToUse)
						// 
						// ANYTYPE aResult=NULL
						// 
						// if this.__sQuickKey != NULL
							// aResult=ListToUse[this.__iQuickPointer]
						// 
						// return aResult
					// VOID 	__SetProperty(inout LIST ListToUse, ANYTYPE aInData NULL)
						// if this.__sQuickKey != NULL
							// ListToUse[this.__iQuickPointer] = aInData
					// 
					// // finds an item in the list
					// INTEGER __FindItem(STRING sKeyIn) // returns 0 if not found
						// return ListFind(this.__lsKeys, sKeyIn)
					// 
					// LIST OF STRING 	__lsKeys = {} // list of items
					// LIST OF ANYTYPE __laData = {} // list of data
				// // removes item if it exists
				// VOID RemoveItem(ANYTYPE sKeyIn)
					// this.__d.DeleteRow(sKeyIn)
				// // returns an item in the form {sItem, aInData, ...}
				// ANYTYPE GetItem(ANYTYPE sKeyIn) // returns NULL if item not found
					// this.__d.ColumnSelector=1
					// this.__d.RowSelector=sKeyIn
					// return this.__d.CurrentRow
				// // returns an item’s data as a list
				// ANYTYPE GetItemData(ANYTYPE sKeyIn) // returns NULL if item not found
					// return this.GetItem(sKeyIn)[2]
				// ANYTYPE GetAField(STRING sKeyIn, STRING sFieldID)
					// this.sKey=sKeyIn
					// return this.GetItem(sKeyIn)[this.Field(sFieldID)]
				// VOID AddItem(STRING sKeyIn, ANYTYPE aInData NULL)
					// this.__d.AddRow({sKeyIn,aInData})
			
			
		
	
	
	////////////////////////////////////////////////////////////////////////////
	// cVERIFYBAG is used for the verifies, and adds the pass/fail result to the data. 
	// Also adds PostResult to update the result of the verify.
	//
	// Theory goes like this:
	//
	// cVERIFYBAG is a generic container for things to verify. The item has
	// a name and an expected value. If the verify routine finds a name
	// for something it checks for (such as FeatureSoAndSoEnabled), then
	// it verifies the data. The result get's posted using PostResult.
	// You can also send additional messages along with the result,
	// for instance "Button was not found", by using the PostMessage method.
	////////////////////////////////////////////////////////////////////////////
									}
								}
							}
						}
					}
				}
			}
		}
	}
	winclass cVERIFYBAG : cBAG
	{
		
		cSEARCHABLELIST __d	// d=data!
		{
			const lsFieldNames = 
			{
				"sKey",
				"aData",
				"fExpectedResult",
				"fVerifyResult",
				"tMessage",
				"aMessage",
				"HashTable",
				"HashKey",
				"HashAnswer",
				"sQATestCase",
				"lCallStack"
				
			};
		}
		BOOLEAN __ConstructorResult = FALSE;
		
		property fExpectedResult
		{
			ANYTYPE Get()
			{
				return this.__d.GetField("fExpectedResult");
			}
			VOID Set(ANYTYPE aInData)
			{
				this.__d.SetField("fExpectedResult",aInData);
			}
		}
		property fVerifyResult
		{
			ANYTYPE Get()
			{
				return this.__d.GetField("fVerifyResult");
			}
			VOID Set(ANYTYPE aInData)
			{
				this.__d.SetField("fVerifyResult",aInData);
			}
		}
		property tMessage
		{
			ANYTYPE Get()
			{
				return MakeText(this.__d.GetField("tMessage"));
			}
			VOID Set(ANYTYPE aInData)
			{
				OBJECT Before = cTEXT();
				
				do
				{
					Before.Append(this.__d.GetField("tMessage"));
				}
				except
				{
					// nada
					ExceptClear();
				}
				if Before.d == NULL
				{
					Before.d={};
				}
				Before.Append(aInData);
				
				this.__d.SetField("tMessage",Before.d);
				
			}
		}
		property aMessage
		{
			ANYTYPE Get()
			{
				return MakeText(this.__d.GetField("aMessage"));
			}
			VOID Set(ANYTYPE aInData)
			{
				OBJECT Before = cLIST();
				Before.Append(this.__d.GetField("aMessage"));
				if Before.d == NULL
				{
					Before.d={};
				}
				Before.Append(aInData);
				this.__d.SetField("aMessage",Before.d);
				
		
			}
		}
		property HashTable
		{
			ANYTYPE Get()
			{
				OBJECT Temp=this.__d.GetField("HashTable");
				return Temp;
			}
			VOID Set(ANYTYPE aInData)
			{
				ANYTYPE Temp=aInData;
				if IsVarList(aInData)
				{
					Temp=cSEARCHABLELIST();
					Temp.d=aInData;
				}
				this.__d.SetField("HashTable",Temp);
				
			}
		}
		property HashKey
		{
			ANYTYPE Get()
			{
				return this.__d.GetField("HashKey");
			}
			VOID Set(ANYTYPE aInData)
			{
				this.__d.SetField("HashKey",aInData);
				OBJECT temp=this.HashTable;
				temp.RowSelector=aInData;
				temp.FieldSelector=2;
				this.__d.SetField("HashAnswer",temp.CurrentRow);
			
			}
		}
		property HashAnswer
		{
			ANYTYPE Get()
			{
				return this.__d.GetField("HashAnswer");
		
			}
		}
		property lCallStack
		{
			ANYTYPE Get()
			{
				return this.__d.GetField("lCallStack");
			}
			VOID Set(ANYTYPE aInData)
			{
				this.__d.SetField("lCallStack",aInData);
			
			}
		}
		property sQATestCase
		{
			ANYTYPE Get()
			{
				return this.__d.GetField("sQATestCase");
			}
			VOID Set(ANYTYPE aInData)
			{
				this.__d.SetField("sQATestCase",aInData);
			
		
			}
		}
		LIST OF ANYTYPE laVerifyList;
		
		VOID	SetKey(STRING sKey)
		{
			this.__d.PushCellSelector();
			this.__d.ColumnSelector=1;
			this.__d.FieldSelector=1;
			this.__d.RowSelector=sKey;
			if this.__d.CurrentField==NULL
			{
				this.__d.AddRow();
				this.__d.RowSelector=this.__d.iNumRows;
			}
			this.__d.CurrentField=sKey;
			this.__d.PopCellSelector();
			this.__d.RowSelector=sKey;
			
		}
		VOID	SetCallStack(STRING sKey optional)
		{
			
			if sKey != NULL
			{
				this.SetKey(sKey);
			
			}
			OBJECT Calls=cLIST().CreateWith(GetCleanCallStack());
			Calls.Pop(); // pop self off stack
			lCallStack=Calls.d;
			
			
			
		}
		VOID 	MasterDispatcher()
		{
			INTEGER i;
			
			for i = 1 to this.__d.iNumRows
			{
				this.Dispatch(i);
			}
		}
		VOID	SetAll(ANYTYPE sKeyIn, BOOLEAN fNewExpectedResult, ANYTYPE aInData NULL optional)
		{
			if aInData==NULL
			{
				aInData=NULL;
			
			}
			this.__d.RowSelector=sKeyIn;
			
			if this.__d.CurrentRow==NULL
			{
				this.__d.AddRow({sKeyIn,aInData,fNewExpectedResult,NULL,NULL,NULL,NULL,NULL,NULL});
			}
			else
			{
				this.fExpectedResult=fNewExpectedResult;
				this.aData=aInData;
			
			}
		}
		STRING 	ConvertData(STRING sData)
		{
			DATACLASS Class;
			STRING sConvertedData = "";
			if sData == ""
			else
			{
				LIST OF STRING lsRegInfo = cSystem.ConvertStringToList(sData)[1];
				if ListCount(lsRegInfo)> 1
				{
					STRING sConvertedList = "";
					STRING sPartialList;
					INTEGER i = 0;
					for i = 1 to ListCount(lsRegInfo)
					{
						if MatchStr("*.*",lsRegInfo[i])
						{
							do
							{
								Class = @(GetField(lsRegInfo[i],".",1)).GetClass ();
								sPartialList = @(GetField(lsRegInfo[i],".",1)).@(GetField(lsRegInfo[i],".",2));
								switch i
								{
									case 1:
										sConvertedList = sPartialList;
									case ListCount(lsRegInfo):
										sConvertedList = ""{{sConvertedList},{sPartialList}}";
									default:
									{
										sConvertedList = "{sConvertedList},{sPartialList}";
								// print("Here it is: {sConvertedList}")
									}
								}
							}
							except
							{
								select
								{
									case MatchStr("*is not defined*",ExceptData()) || MatchStr("*is NULL*",ExceptData()):
										sConvertedData = sData;
										break;
									case MatchStr("*is not set*",ExceptData()) || MatchStr("*is NULL*",ExceptData()):
										Log.print("{aData} has no data. VerifyBag.ConvertData failed.");
									default:
									{
										Log.ExceptPrint();
									}
								}
								ExceptClear();
							}
						}
						else
						{
							sConvertedData = sData;
						}
					}
				}
				else
				{
					if MatchStr("*.*",sData)
					{
						do
						{
							Class = @(GetField(sData,".",1)).GetClass ();
							sConvertedData = @(GetField(sData,".",1)).@(GetField(sData,".",2));
							// print("Here it is: {sConvertedData}")
						}
						except
						{
							select
							{
								case MatchStr("*is not defined*",ExceptData()) || MatchStr("*is NULL*",ExceptData()):
									sConvertedData = sData;
								case MatchStr("*is not set*",ExceptData()) || MatchStr("*is NULL*",ExceptData()):
									Log.print("{aData} has no data.");
								default:
								{
									Log.ExceptPrint();
								}
							}
							ExceptClear();
						}
					}
					else
					{
						sConvertedData = sData;
					}
				}
			}
			return sConvertedData;
		
		// AMM 2005 MAR 10: DO NOT COMMENT THIS BACK IN
		// VOID 	PopulateFromSheet(STRING sTableName, STRING sRow)
			// 
			// // these refer to column position in the incoming data
			// const KEY =1
			// const EXPECTEDRESULT = 2
			// const DATA = 3
			// INTEGER i = 0
			// 
			// // now get the data
			// this.laVerifyList = this.RetrieveXLS(sTableName,sRow)
			// 
			// if TypeOf(this.laVerifyList)!=LIST OF LIST OF STRING
			{
				// this.laVerifyList = {this.laVerifyList}
			// 
			// for i = 1 to ListCount(this.laVerifyList)
				// this.laVerifyList[i][DATA] = ConvertData(this.laVerifyList[i][DATA])
				// this.SetAll(this.laVerifyList[i][KEY],MakeBool("{this.laVerifyList[i][EXPECTEDRESULT]}"),this.laVerifyList[i][DATA])
			// 
			// 
			// 
			// 
		// VOID 	PopulateFromSheet(STRING sTableName, STRING sRow)
			// const KEY =1
			// const EXPECTEDRESULT = 2
			// const DATA = 3
			// INTEGER i = 0
			// this.laVerifyList = this.RetrieveXLS(sTableName,sRow)
			// //condition added by Ramasamy to handle single input row
			// if TypeOf(this.laVerifyList)==LIST OF LIST OF STRING
				// for i = 1 to ListCount(this.laVerifyList)
				{
					// this.laVerifyList[i][DATA] = ConvertData(this.laVerifyList[i][DATA])
					// this.SetAll(this.laVerifyList[i][KEY],MakeBool(this.laVerifyList[i][EXPECTEDRESULT]),this.laVerifyList[i][DATA])
			// else
				// this.laVerifyList[DATA] = ConvertData(this.laVerifyList[DATA])
				// this.SetAll(this.laVerifyList[1],MakeBool(this.laVerifyList[2]),this.laVerifyList[3])
		
		// Dispatch takes an argument like Application.Dialog.Control.VerifyBag(x)
		// and makes the call to that method, 
				}
			}
		}
		VOID 	Dispatch(ANYTYPE i)
		{
			do
			{
				this.__d.ColumnSelector=1;
				this.__d.RowSelector=i;
				
				this.sKey=i;
				
				LIST OF STRING lsData = MakeListFromString(this.__d.GrabField(1,i,"sKey"),".");
				INTEGER iListCount=ListCount(lsData);
				if sContains(lsData[iListCount],"(")
				{
					lsData[iListCount]=GetLeftOf(lsData[iListCount],"(");
				
				
				}
				switch iListCount
				{
					case 1:
						@(lsData[1])(this);
					case 2:
						@(lsData[1]).@(lsData[2])(this);
					case 3:
						@(lsData[1]).@(lsData[2]).@(lsData[3])(this);
					case 4:
						@(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4])(this);
					case 5:
						@(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5])(this);
					case 6:
						@(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6])(this);
					case 7:
						@(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7])(this);
					case 8:
						@(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8])(this);
					case 9:
						@(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8]).@(lsData[9])(this);
					case 10:
						@(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8]).@(lsData[9]).@(lsData[10])(this);
					case 11:
						@(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8]).@(lsData[9]).@(lsData[10]).@(lsData[11])(this);
					case 12:
						@(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8]).@(lsData[9]).@(lsData[10]).@(lsData[11]).@(lsData[12])(this);
				
				//this.sKey=NULL
				
				}
			}
			except
			{
				this.tMessage = ExceptData();
				Log.ExceptPrint();
				ExceptClear();
		
			}
		}
		VOID 	UnitTest()
		{
			
			// test one
			LIST TestData=
			{
				{"ACT_ZoneClient.Panel.Overview.Preferences.VerifyAbleToCheckForUpdates"	, "", TRUE},
				{"ACT_ZoneClient.Panel.Overview.Preferences.VerifyAbleToShareSettings"		, "", TRUE},
				{"ACT_ZoneClient.Panel.Overview.ProductInfo.VerifyAbleToBuyNow"				, "", FALSE},
				{"ACT_ZoneClient.Panel.Overview.ProductInfo.VerifyAbleToChangeLicenseInformation", "", TRUE},
				{"ACT_ZoneClient.Panel.Overview.ProductInfo.VerifyAbleToChangeRegistration"	, "", TRUE},
				{"ACT_ZoneClient.Panel.Overview.ProductInfo.VerifyAbleToRenewSubscription"	, "", TRUE},
				{"ACT_ZoneClient.Panel.Overview.ProductInfo.VerifyInTrialMode"				, "", FALSE},
				{"ACT_ZoneClient.Panel.Overview.ProductInfo.VerifyLicenseNumber"			, "jq5aj-xrq7w-k4fee-axw5vi-xn90g0", TRUE},
				{"ACT_ZoneClient.Panel.Overview.ProductInfo.VerifyLicenseType"				, "Trial", TRUE}
				
			};
			OBJECT foo=this.__UnitTest_ObjGen();
			foo.d=TestData;
			
			// test two
			foo=cVERIFYBAG();
			foo.SetKey("snark");
			SmartListPrint(foo.__d.d);
			
		
		
	
		}
	}
	window cBASE UnitTestfoo1
	{
		STRING sKey="UnitTestfoo1.foo2.foo3";
		cBASE foo2
		{
			VOID foo3(OBJECT oBag)
			{
				
				// verify step - ASSUMES call was made thru cVERIFYBAG::Dispatcher()
				// because that sets sKey before the call is made, and sKey is used 
				// as the pointer into the list
				
				print(oBag.aData);
				
				oBag.fVerifyResult = ( oBag.fExpectedResult == ( oBag.aData == "Hello World!" ) );
				
				if oBag.fVerifyResult
				{
					oBag.tMessage = "PASSED!";
				}
				else
				{
					oBag.tMessage = "FAILED!";
				
				}
			}
		}
	}
	private VOID ExtensionLibrary_SelfTestSuite_Objects_cVERIFYBAG()
	{
		
		OBJECT Bag=cVERIFYBAG();
		
		Bag.SetAll(UnitTestfoo1.sKey, TRUE, "Hello World!") ;
		
		Bag.MasterDispatcher();
		
		print(Bag.GetItem(UnitTestfoo1.sKey));
	// winclass cVERIFYBAG : cBAG
		// 
		// // Virtual Fields: 
		// // 		sKey	 		= Name for the item (Inhereted)
		// //  	aData			= Value to use for verification (ie: expected text)(Inhereted)
		// //		fExpectedResult	= BOOLEAN of Do You Expect the verify to match or not?
		// //		fVerifyResult 	= BOOLEAN of Did The Verify Pass
		// //		tMessage		= Text messages to be passed back up about the failure
		// //		aMessage		= Any other data to pass back up
		// // 
		// // can update all the fields in the data
		// 
		// // property sKey defined in cBAG
		// // property aData defined in cBAG
		// 
		// property fExpectedResult
		{
			// ANYTYPE Get()
			{
				// return this.__GetProperty(this.__lfExpectedResult)
			// VOID Set(ANYTYPE aInData)
				// this.__SetProperty(this.__lfExpectedResult, aInData)
		// property fVerifyResult
			// ANYTYPE Get()
				// return this.__GetProperty(this.__lfVerifyResult)
			// VOID Set(ANYTYPE aInData)
				// this.__SetProperty(this.__lfVerifyResult, aInData)
		// property tMessage
			// ANYTYPE Get()
				// return this.__GetProperty(this.__ltResultMessages)
			// VOID Set(ANYTYPE aInData)
				// this.PostMessage(this.sKey, aInData)
		// property aMessage
			// ANYTYPE Get()
				// return this.__GetProperty(this.__laAdditionalData)
			// VOID Set(ANYTYPE aInData)
				// this.PostData(this.sKey, aInData)
		// 
		// property HashTable
			// ANYTYPE Get()
				// return this.__GetProperty(this.__laHashTables)
			// VOID Set(ANYTYPE aInData)
				// this.__SetProperty(this.__laHashTables, aInData)
				// 
		// property HashKey
			// ANYTYPE Get()
				// return this.__GetProperty(this.__laHashKeys)
			// VOID Set(ANYTYPE aInData)
				// 
				// // store hash key
				// this.__SetProperty(this.__laHashKeys, aInData)
				// 
				// ANYTYPE Result=NULL
				// OBJECT LookupTable=cSEARCHABLELIST()
				// 
				// INTEGER i = this.__FindItem(this.sKey)
				// 
				// if i > 0
				{
					// // item found! Now, is there already a searchable list?
					// if this.__laSearchableTables[i] != NULL
					{
						// LookupTable=this.__laSearchableTables[i]
					// else
						// this.__laSearchableTables[i] = ""
					// 
					// LookupTable.d=this.HashTable
					// this.__laSearchableTables[i]=LookupTable
					// 
					// Result=LookupTable.Find(aInData)
					// 
					// this.__SetProperty(this.__laHashAnswers, Result)
					// 
					// 
				// 
			// 
		// property HashAnswer
			// ANYTYPE Get()
				// return this.__GetProperty(this.__laHashAnswers)
		// 
		// LIST OF ANYTYPE laVerifyList
		// VOID PopulateFromSheet(STRING sTableName, STRING sRow)
			// const KEY =1
			// const EXPECTEDRESULT = 2
			// const DATA = 3
			// INTEGER i = 0
			// this.laVerifyList = this.RetrieveXLS(sTableName,sRow)
			// //condition added by Ramasamy to handle single input row
			// if TypeOf(this.laVerifyList)==LIST OF LIST OF STRING
				// for i = 1 to ListCount(this.laVerifyList)
					// this.laVerifyList[i][DATA] = ConvertData(this.laVerifyList[i][DATA])
					// this.SetAll(this.laVerifyList[i][KEY],MakeBool(this.laVerifyList[i][EXPECTEDRESULT]),this.laVerifyList[i][DATA])
			// else
				// this.laVerifyList[DATA] = ConvertData(this.laVerifyList[DATA])
				// this.SetAll(this.laVerifyList[1],MakeBool(this.laVerifyList[2]),this.laVerifyList[3])
		// STRING ConvertData(STRING sData)
			// DATACLASS Class
			// STRING sConvertedData = ""
			// if sData == ""
			// else
				// LIST OF STRING lsRegInfo = cSystem.ConvertStringToList(sData)[1]
				// if ListCount(lsRegInfo)> 1
					// STRING sConvertedList = ""
					// STRING sPartialList
					// INTEGER i = 0
					// for i = 1 to ListCount(lsRegInfo)
						// if MatchStr("*.*",lsRegInfo[i])
						{
							// do
							{
								// Class = @(GetField(lsRegInfo[i],".",1)).GetClass ()
								// sPartialList = @(GetField(lsRegInfo[i],".",1)).@(GetField(lsRegInfo[i],".",2))
								// switch i
								{
									// case 1
									{
										// sConvertedList = sPartialList
									// case ListCount(lsRegInfo)
										// sConvertedList = ""{{sConvertedList},{sPartialList}}"
									// default
										// sConvertedList = "{sConvertedList},{sPartialList}"
								// // print("Here it is: {sConvertedList}")
							// except
								// select
									// case MatchStr("*is not defined*",ExceptData()) || MatchStr("*is NULL*",ExceptData())
										// sConvertedData = sData
										// break
									// case MatchStr("*is not set*",ExceptData()) || MatchStr("*is NULL*",ExceptData())
										// Log.print("{aData} has no data. VerifyBag.ConvertData failed.")
									// default
										// Log.print(ExceptData())
						// else
							// sConvertedData = sData
				// else
					// if MatchStr("*.*",sData)
						// do
							// Class = @(GetField(sData,".",1)).GetClass ()
							// sConvertedData = @(GetField(sData,".",1)).@(GetField(sData,".",2))
							// // print("Here it is: {sConvertedData}")
						// except
							// select
								// case MatchStr("*is not defined*",ExceptData()) || MatchStr("*is NULL*",ExceptData())
									// sConvertedData = sData
								// case MatchStr("*is not set*",ExceptData()) || MatchStr("*is NULL*",ExceptData())
									// Log.print("{aData} has no data.")
								// default
									// Log.print(ExceptData())
					// else
						// sConvertedData = sData
			// return sConvertedData
		// SetExpected(STRING sKeyIn, BOOLEAN fExpectedResult)
			// this.SetAll(sKeyIn, fExpectedResult)
		// 
		// SetAll(STRING sKeyIn, BOOLEAN fExpectedResult, ANYTYPE aInData NULL optional)
			// if aInData==NULL
				// aInData=NULL
			// INTEGER i = this.__FindItem(sKeyIn)
			// if i==0
				// i=this.__AddItem(sKeyIn, aInData)
			// if i > 0
				// this.__lfExpectedResult[i]=fExpectedResult
		// 
		// PostAll(STRING sKeyIn, BOOLEAN fVerifyResult NULL, TEXT tData NULL optional, ANYTYPE aInData NULL optional)
			// if fVerifyResult != NULL
				// this.PostResult(sKeyIn, fVerifyResult)
			// if tData != NULL
				// this.PostMessage(sKeyIn,tData)
			// if aInData != NULL
				// this.PostData(sKeyIn, aInData)
		// 
		// // updates the boolean pass/fail value on the verify
		// PostResult(STRING sKeyIn, BOOLEAN fVerifyResult)
			// INTEGER i = this.__FindItem(sKeyIn)
			// if i==0
				// Log.LogWarning("Tried to post verify result on a key which was not found. sKeyIn={sKeyIn}")
			// else
				// this.__lfVerifyResult[i]=fVerifyResult
		// 
		// // APPENDS the message
		// PostMessage(STRING sKeyIn, TEXT tData)
			// INTEGER i = this.__FindItem(sKeyIn)
			// if i==0
				// Log.LogWarning("Tried to post verify message on a key which was not found. sKeyIn={sKeyIn}")
			// else
				// 
				// if this.__ltResultMessages[i] == NULL
					// this.__ltResultMessages[i] = {}
				// 
				// ListAppend(this.__ltResultMessages[i],MakeText(tData))
		// 
		// // updates the Additional Data field
		// PostData(STRING sKeyIn, ANYTYPE aInData NULL)
			// INTEGER i = this.__FindItem(sKeyIn)
			// if i==0
				// Log.LogWarning("Tried to post verify message on a key which was not found. sKeyIn={sKeyIn}")
			// else
				// if this.__laAdditionalData[i] == NULL
					// this.__laAdditionalData[i] = {}
				// ListAppend(this.__laAdditionalData[i],aInData)
			// 
		// 
		// BOOLEAN AreThereFailures()
			// BOOLEAN fResult = FALSE
			// ANYTYPE i
			// for i = 1 to ListCount(this.__lsKeys)
				// if IsNull(this.__lfVerifyResult[i])
					// this.__lfVerifyResult[i] = FALSE
				// if !this.__lfVerifyResult[i]
					// return TRUE
			// return fResult
		// 
		// ANYTYPE GetFailedItems()
			// ANYTYPE aResult=NULL, CheckMe
			// INTEGER i,iMax
			// iMax = ListCount(this.__lsKeys)
			// if iMax > 0
				// aResult={}
				// for i = 1 to iMax
					// if IsNull(this.__lfVerifyResult[i])
						// this.__lfVerifyResult[i] = FALSE
					// if !this.__lfVerifyResult[i]
						// CheckMe=this.GetItem(i)
						// ListAppend(aResult,CheckMe)
			// return aResult
			// 
		// 
		// VOID MasterDispatcher()
			// INTEGER iMax = ListCount(__lfExpectedResult) // how many items in the bag?
			// INTEGER i
			// 
			// for i = 1 to iMax
				// this.Dispatch(i)
		// 
		// // Dispatch takes an argument like Application.Dialog.Control.VerifyBag(x)
		// // and makes the call to that method, 
		// VOID Dispatch(INTEGER i)
			// do
				// //this.__lsKeys[i]
				// LIST OF STRING lsData = MakeListFromString(this.__lsKeys[i],".")
				// INTEGER iListCount=ListCount(lsData)
				// if sContains(lsData[iListCount],"(")
					// lsData[iListCount]=GetLeftOf(lsData[iListCount],"(")
				// 
				// this.sKey=i
				// 
				// switch iListCount
					// case 1
						// @(lsData[1])(this)
					// case 2
						// @(lsData[1]).@(lsData[2])(this)
					// case 3
						// @(lsData[1]).@(lsData[2]).@(lsData[3])(this)
					// case 4
						// @(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4])(this)
					// case 5
						// @(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5])(this)
					// case 6
						// @(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6])(this)
					// case 7
						// @(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7])(this)
					// case 8
						// @(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8])(this)
					// case 9
						// @(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8]).@(lsData[9])(this)
					// case 10
						// @(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8]).@(lsData[9]).@(lsData[10])(this)
					// case 11
						// @(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8]).@(lsData[9]).@(lsData[10]).@(lsData[11])(this)
					// case 12
						// @(lsData[1]).@(lsData[2]).@(lsData[3]).@(lsData[4]).@(lsData[5]).@(lsData[6]).@(lsData[7]).@(lsData[8]).@(lsData[9]).@(lsData[10]).@(lsData[11]).@(lsData[12])(this)
				// 
				// this.sKey=NULL
				// 
			// except
				// this.tMessage = ExceptData()
				// ExceptPrint()
		// 
		// const LIST OF STRING lsFieldHeaders={...}
			// "sKey"
			// "aData"
			// "fExpectedResult"
			// "fVerifyResult"
			// "tMessage"
			// "aMessage"
			// "HashTable"
			// "HashKey"
			// "HashAnswer"
		// ///////////////////////////////////////////////////////////////////
			// 
			// // THESE MUST BE REDEFIED WHEN FIELDS ADDED
				// LIST OF STRING __lsVirtualFields = {...}
					// "__lsKeys"
					// "__laData"
					// "__lfExpectedResult"
					// "__lfVerifyResult"
					// "__ltResultMessages"
					// "__laAdditionalData"
					// "__laHashTables"
					// "__laHashKeys"
					// "__laHashAnswers"
				// LIST OF STRING __lsVirtualFields__Private = {...}
					// "__laSearchableTables"
				// LIST OF STRING __lsPropertiesToPublish = {...}
			// 
			// // cVERIFYBAG properties
			// LIST OF BOOLEAN 		__lfExpectedResult 	= {}
			// LIST OF BOOLEAN 		__lfVerifyResult 	= {} 
			// LIST OF TEXT 			__ltResultMessages 	= {}
			// LIST OF ANYTYPE 		__laAdditionalData 	= {}
			// 
			// // Additional properties for hash table support
			// LIST OF LIST OF ANYTYPE __laHashTables = {}
			// ANYTYPE					__laHashKeys   = {}
			// LIST OF ANYTYPE			__laHashAnswers = {}
			// LIST OF ANYTYPE			__laSearchableTables = {}
		// 
	
	

// Expand for Abstract Object Library - Other special file classes 	(cBOOTLOADER, cSENDMAIL)
	
	////////////////////////////////////////////////////////////////////////////
	// cBOOTLOADER 			OS Loading object
	//
	//
	// Purpose: 			For cycling through multiple OS's per machine. Each machine to use cBOOTLOADER needs to
	//						have some additional sections added to the boot.ini file:
	//							OSComputer:		Computer name as stated within the operating systems network id.
	//							OSName:		 	User readable OS Names for reporting purposes
	//							OSPartition:	OS path info as recognized within the [operating systems] section of the boot.ini file.
	//					   Each of these sections may have the following keys depending on which OS's are installed::
	// 						Win98
	// 						WinME
	// 						WinNT4
	// 						Win98SE
	// 						Win2KPro
	// 						WinXPPro
	//						WinXPHome
	//
	//
	////////////////////////////////////////////////////////////////////////////
	// Expand this for documentation
		//
		// inherits: 		cINIFILE
		//
		//
		// PUBLIC MEMBERS - METHODS:
		//
		// 		SetMachineToNextOS		Advances the OS to the next OS based on  a machine's list of OS's
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		//
		//		IsWriteable				Checks/Sets the read-only file property of boot.ini
		//
		//		IsNotEndOfOS			Checks if __iWinOS = 0 if it is, then it returns FALSE otherwise it returns
		//								TRUE. 0 indicates that there are no more OS's to process in the list.
		//
		//		DefaultOS				Gets/Sets the default operating system in boot.ini.
		//
		//		Timeout					Gets/Sets the timout value within boot.ini. This value is used to count down in seconds the
		//								display of the boot menu before the default OS is executed.
		//
		//		OSComputerName			Gets the computer OS name for the operating system in boot.ini. Dependent on
		//								a section being created within the boot.ini file.
		//
		//		OSFullName				Gets the full name of the OS for the operating system in boot.ini. Dependent on
		//								a section being created within the boot.ini file.
		//
		//		NextOSStartupPath			Gets the startup path for the next OS to process
		// PRIVATE MEMBERS - VARS:
		//
		// 		__iWinOS				This controls all processing within cBOOTLOADER. The number is manipulated to change which key
		//								within the OSPartition section should be processed. Setting this number to 0 indicates that processing is
		//								to be stopped.
									}
								}
							}
						}
					}
				}
			}
		}
	}
	winclass cBOOTLOADER : cINIFILE
	{
		STRING sFileName ="c:\boot.ini";
		INTEGER __iWinOS = ListFind(this.OSPartition.Dump()[2],this.BootLoader.Default.sValue);
		//Returns the network name of the OS that is set within the default key in the boot loader section of boot.ini.
		//manipulates the read-only property of the boot.ini file
		property IsWriteable
		{
			BOOLEAN Get()
			{
				// Excute attrib and capture the result to analyze the writeable attribute of the file.
				LIST OF STRING sResult = cEXEFILE("attrib").RunAndWait("c:\boot.ini");
				//An R indicate that the file is read-only.
				if MatchStr("*R*",sResult[1])
				{
					return FALSE;
				}
				else
				{
					return TRUE;
				}
			}
			VOID Set(BOOLEAN bIncoming)
			{
				//execute attive on the boot.ini file to set it to read-only or not read-only
				if bIncoming
				{
					cEXEFILE("attrib").RunAndWait("c:\boot.ini -r");
				}
				else
				{
					cEXEFILE("attrib").RunAndWait("c:\boot.ini +r");
		//Checks if all OS's have finished. __iWinOS is set to 0 when all OS's have finished processing.
		//To continue processing __iWinOS must be set to a number corresponding to where the OS is in a list
		//returned by the Dump() method.
				}
			}
		}
		property IsNotEndOfOS
		{
			BOOLEAN Get()
			{
				if __iWinOS == 0
				{
					return FALSE;
				}
				else
				{
					return TRUE;
		//manipulates the value of the default key in the boot loader section of boot.ini. This is the OS that will execute
		// at the next start up. To start processing, this needs to be set to the first OS in the list that requires
		//processing.
				}
			}
		}
		property DefaultOS
		{
			STRING Get()
			{
				return this.BootLoader.Default.sValue;
		//Returns the name of the OS that is set within the default key in the boot loader section of boot.ini.
			}
		}
		property OSComputerName
		{
			STRING Get()
			{
				if __iWinOS == 0
				{
					Log.LogError("No Operating System has been set.");
					return "";
				}
				else
				{
					return this.OSComputer.Dump()[2][__iWinOS];
		//Returns the name of the OS that is set within the default key in the boot loader section of boot.ini.
				}
			}
		}
		property OSFullName
		{
			STRING Get()
			{
				if __iWinOS == 0
				{
					Log.LogError("No Operating System has been set.");
					return "";
				}
				else
				{
					return this.OSFull.Dump()[2][__iWinOS];
				}
			}
		}
		property OSShortName
		{
			STRING Get()
			{
				if __iWinOS == 0
				{
					Log.LogError("No Operating System has been set.");
					return "";
				}
				else
				{
					return this.OSShort.Dump()[2][__iWinOS];
				}
			}
		}
		property OSList
		{
			LIST OF STRING Get()
			{
				return GetMachineOSList();
		//Returns the startup path of the OS that is set within the default key in the boot loader section of boot.ini.
			}
		}
		property OSStartupPath
		{
			STRING Get()
			{
				if __iWinOS == 0
				{
					Log.LogError("No Operating System has been set.");
					return "";
				}
				else
				{
					return this.OSStartupDir.Dump()[2][__iWinOS];
		//Returns the starup path of the OS that is set within the default key in the boot loader section of boot.ini.
		//manipulates the value of the timeout key in the boot loader section of boot.ini. Timeout specifies how long
		//the boot menu displays before the menu automatically selects the default menu.
				}
			}
		}
		property Timeout
		{
			STRING Get()
			{
				return this.BootLoader.Timeout.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				this.BootLoader.Timeout.sValue = sIncoming;
		//public methods
		//these sections are for changing the two keys in boot.ini, needed for rebooting a machine to different OS's.
			}
		}
		Section BootLoader
		{
			tag "boot loader";
			//timeout in boot.ini specifies how long the boot menu should appear before the default OS is executed.
			Key Timeout
			{
				tag "timeout";
			//Default specifies which OS is to be executed as a default OS while the OS menu is displayed.
			}
			Key Default
			{
				tag "default";
			}
			Key Home
			{
				tag "home";
		//The value of these keys represent the Operating system to execute. They are used to set the default key value for
		//boot.ini
			}
		}
		Section OSPartition
		{
			Key Win98 {}
			Key WinME {}
			Key WinNT4 {}
			Key Win98SE {}
			Key Win2KPro {}
			Key WinXPPro {}
			Key WinXPHome {}
		//The value of these keys represent the Operating full name used for reporting.
		}
		Section OSFull
		{
			Key Win98 {}
			Key WinME {}
			Key WinNT4 {}
			Key Win98SE {}
			Key Win2KPro {}
			Key WinXPPro {}
			Key WinXPHome {}
		//The value of these keys represent the Operating full name used for reporting.
		}
		Section OSShort
		{
			Key Win98 {}
			Key WinME {}
			Key WinNT4 {}
			Key Win98SE {}
			Key Win2KPro {}
			Key WinXPPro {}
			Key WinXPHome {}
		//The value of these keys represent the network name for the computer's operating system.
		}
		Section OSComputer
		{
			Key Win98 {}
			Key WinME {}
			Key WinNT4 {}
			Key Win98SE {}
			Key Win2KPro {}
			Key WinXPPro {}
			Key WinXPHome {}
		//The value of these keys represent the startup folder for the computer's operating system.
		}
		Section OSStartupDir
		{
			Key Win98 {}
			Key WinME {}
			Key WinNT4 {}
			Key Win98SE {}
			Key Win2KPro {}
			Key WinXPPro {}
			Key WinXPHome {}
		//The value of these keys represent the machine identification for the computer's operating system.
		}
		Section Machine
		{
			Key MachineNumber {}
			Key MachineName {}
		//properties
		}
		property MachineNum
		{
			STRING Get()
			{
				if this.Machine.MachineNumber.sValue == ""
				{
					Log.LogError("Machine Number has not been set.");
					return "";
				}
				else
				{
					return this.Machine.MachineNumber.sValue;
				}
			}
		}
		property MachineName
		{
			STRING Get()
			{
				if this.Machine.MachineName.sValue == ""
				{
					Log.LogError("Machine Name has not been set.");
					return "";
				}
				else
				{
					return this.Machine.MachineName.sValue;
				}
			}
		}
		STRING GetNextOSStartupPath(LIST OF STRING laRunOS)
		{
			INTEGER iNextPath;
			BOOLEAN bSelectPath = TRUE;
			// {, , Auto1_nt4, Auto-1_win98se, Auto1_win2kpro, auto1_xppro, }
			//find where the default OS is in the list of OS's. Set __iRunOS to a number representing
			//the next OS in the list
			iNextPath =  ListFind(this.OSPartition.Dump()[2],this.BootLoader.Default.sValue) + 1;
			while bSelectPath
			{
				//An item in the list could be blank, I (Ignore) or R (Run). Only if its R do you set it to
				//the next OS
				//pass the number into the private method to set the machine to the next OS to be executed.
				if [STRING]laRunOS[iNextPath] == "R"
				{
					// Log.print(laRunOS)
					return this.OSStartupDir.Dump()[2][iNextPath];
					//break out of the while loop
					bSelectPath=FALSE;
				}
				else
				{
					//if it's not an R then increment iNextPath to evaluate the next item in the list.
					iNextPath = iNextPath + 1;
					//check to be sure your not at the end of the list
					if iNextPath > ListCount(this.OSPartition.Dump()[2])
					{
						//if you're at the end of the list then set the machine to stop and break the loop
						return "";
						bSelectPath=FALSE;
					}
				}
			}
		}
		VOID SetMachineToOS(LIST OF STRING laRunOS optional,BOOLEAN bFirst optional)
		{
			BOOLEAN bRunOS = TRUE;
			INTEGER iRunOS;
			INTEGER iCount;
			// {, , Auto1_nt4, Auto-1_win98se, Auto1_win2kpro, auto1_xppro, }
			//find where the default OS is in the list of OS's. Set __iRunOS to a number representing
			//the next OS in the list
			if IsNull(bFirst)
			{
				bFirst = FALSE;
			//there are two "first" OS's. The first OS that needs running and the first OS in the list of OS's.
			}
			if bFirst
			{
				//if laRunOS comes in blank, then set the OS to the "home" OS. The first OS in the OS list.
				if IsNull(laRunOS)
				{
					iRunOS = ListFind(this.OSShort.Dump()[2],this.BootLoader.Home.sValue);
					//Find the first item with data in the list, this is the first OS in the system
					__SetMachineOS(iRunOS);
					bRunOS= FALSE;
				//otherwise set the machine to the first OS that needs testing.
				}
				else
				{
					//Find the first R in the list, this is the first OS to run.
					for iCount = 1 to ListCount (laRunOS)
					{
						if laRunOS[iCount] == "R"
						{
							iRunOS = iCount;
							break;
						}
					}
				}
			}
			else
			{
				iRunOS =  ListFind(this.OSPartition.Dump()[2],this.BootLoader.Default.sValue) + 1;
			//set up an evaluation of lsRunOS, Only run OS's when there is a corresponding R in the list.
			//Example:
			// {, , R, I, R, R, , Machine1}
			}
			while bRunOS
			{
				//An item in the list could be set to R. If it's an R, set it to the next OS
				//pass the number into the private method to set the machine to the next OS to be executed.
				if [STRING]laRunOS[iRunOS] == "R"
				{
					// Log.print(this.OSList)
					__SetMachineOS(iRunOS);
					//break out of the while loop
					bRunOS=FALSE;
				}
				else
				{
					//if it's not an R then increment iRunOS to evaluate the next item in the list.
					iRunOS = iRunOS + 1;
					//check to be sure your not at the end of the list
					if iRunOS > ListCount(this.OSPartition.Dump()[2])
					{
						//if you're at the end of the list then set the machine to stop and break the loop
						__SetMachineOS(0);
						bRunOS=FALSE;
					}
				}
			}
		}
		LIST OF STRING GetMachineOSList()
		{
			//Get the list from the ShortName section
			LIST OF STRING lsList = this.OSShort.Dump()[2];
			LIST OF STRING lsReturn;
			STRING sOS;
			//since lsList contains empty items i need to eliminate them
			for each sOS in lsList
			{
				if sOS !=""
				{
					ListAppend(lsReturn,sOS);
				}
			}
			return lsReturn;
		//private members
			//__iWinOS controls what list member in each list is to be used. If this is set to 0 then processing
			// is halted.
			VOID __SetMachineOS(INTEGER iIncoming)
			{
				// Get the total number of items in the list of OS's.
				INTEGER __iOSCount = ListCount(this.OSPartition.Dump()[2]);
				//Check if the number representing the next OS in the list is greater than  or less than the total count of OS's
				// If it is greater than that indicates the default OS is at the end of the list and therefore the process should
				// be stopped. If it is less than the number, that indicates an incorrect number which would crash execution.
				//In either case __iWinOS should be set to 0 so that processing would stop.
				if iIncoming > __iOSCount || iIncoming <= 0
				{
					__iWinOS = 0;
				}
				else
				{
					//set __iWinOS to the next OS and set the bootloader "default" selection to the
					//OS represented by __iWinOS
					__iWinOS = iIncoming;
					this.BootLoader.Default.sValue = this.OSPartition.Dump()[2][__iWinOS];
		
	
	
	////////////////////////////////////////////////////////////////////////////
	// cEMAIL
	////////////////////////////////////////////////////////////////////////////
				}
			}
		}
	}
	winclass cSENDEMAIL : cFILE
	{
		STRING sFileName = "";
		
		property 	SetTemplate
		{
			STRING Get()
			{
				return __DataStore.sFileName;
			}
			VOID Set(STRING sIncoming)
			{
				__DataStore.sFileName = sIncoming;
			}
		}
		property 	Host
		{
			STRING Get()
			{
				return __DataStore.Address.Host.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__DataStore.Address.Host.sValue = sIncoming;
			}
		}
		property 	From
		{
			STRING Get()
			{
				return __DataStore.Address.From.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__DataStore.Address.From.sValue = sIncoming;
			}
		}
		property 	To
		{
			STRING Get()
			{
				return __DataStore.Address.To.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__DataStore.Address.To.sValue = sIncoming;
			}
		}
		property 	ReplyTo
		{
			STRING Get()
			{
				return __DataStore.Address.ReplyTo.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__DataStore.Address.ReplyTo.sValue = sIncoming;
			}
		}
		property 	Subject
		{
			STRING Get()
			{
				return __DataStore.Message.Subject.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__DataStore.Message.Subject.sValue = sIncoming;
			}
		}
		property 	AddFileToBody
		{
			STRING Get()
			{
				return __DataStore.Message.AddFileToBody.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__DataStore.Message.AddFileToBody.sValue = sIncoming;
			}
		}
		property 	Body
		{
			TEXT Get()
			{
				return this.d;
			}
			VOID Set(TEXT lsIncoming)
			{
				this.d=lsIncoming;
			}
		}
		VOID 		SendMail()
		{
			if this.Host == ""
			{
				this.Host = "exgate1.zonelabs.com";
			}
			if From == ""
			{
				From = cSystem.sHostName;
			}
			if ReplyTo == ""
			{
				this.ReplyTo = this.From;
			
			}
			OBJECT temp=cTEXTFILE("C:\blat.temp.file.txt");
			temp.Delete();
			if d != NULL
			{
				temp.lsData=this.d;
				temp.Write();
				this.AddFileToBody = temp.sFileName;
				
			
			}
			cEXEFILE("blat.exe").RunAndWait('-install {Host} {From}');
			sleep(3);
			cEXEFILE("blat.exe").RunAndWait('{AddFileToBody} -to {To} -replyto {ReplyTo} -s "{Subject}"');
			// print(cEXEFILE("blat.exe").RunAndWait('{AddFileToBody} -to {To} -replyto {ReplyTo} -s "{Subject}"'))
			Log.print('blat.exe {AddFileToBody} -to {To} -replyto {ReplyTo} -s "{Subject}"');
			temp.Delete();
		
		}
		OBJECT 		Send(STRING sHost null optional, STRING sFrom null optional, STRING sTo null optional, STRING sSubject null optional, TEXT lsBody null optional)
		{
			OBJECT Temp = cTEXTFILE("temp.txt");
			
			if sHost != NULL
			{
				Host=sHost;
			}
			if sFrom != NULL
			{
				From=sFrom;
			}
			if sTo != NULL
			{
				To=sTo;
			}
			if sSubject != NULL
			{
				Subject=sSubject;
			}
			if lsBody != NULL
			{
				Temp.Zap();
				Temp.lsData = MakeText(lsBody);
				Temp.Write();
				AddFileToBody=Temp.sFileName;
			
			}
			SendMail();
			
			return this;
		
		}
		property __DataStore
		{
			OBJECT Get()
			{
				return this.__GetCorrectObject();
			}
		}
		OBJECT   __GetCorrectObject()
		{
			OBJECT Result = this.__LocalData;
			if this.sFileName != ""
			{
				Result=this.__EmailTemplate;
				this.__EmailTemplate.sFileName=this.sFileName;
			}
			return Result;
		}
		cINIFILE __EmailTemplate
		{
			Section Address
			{
				Key Host {}
				Key To {}
				Key From {}
				Key ReplyTo {}
			}
			Section Message
			{
				Key Subject {}
				Key AddFileToBody {}
				Key Body {}
			}
		}
		cBASE    __LocalData
		{
			cBASE Address
			{
				cBASE Host
				{
					STRING sValue = "";
				}
				cBASE To
				{
					STRING sValue = "";
				}
				cBASE From
				{
					STRING sValue = "";
				}
				cBASE ReplyTo
				{
					STRING sValue = "";
				}
			}
			cBASE Message
			{
				cBASE Subject
				{
					STRING sValue = "";
				}
				cBASE Body
				{
					LIST OF STRING sValue = {""};
				}
				cBASE AddFileToBody
				{
					STRING sValue = "";
				
				}
			}
		}
		TEXT d = NULL;
		
	
	
	

///////////////////////////////////////////////////////////////////////////

// Expand for other global instances
	////////////////////////////////////////////////////////////////////////////
	// cSystem 			System object - represents system running test
	//
	// Purpose: 		Encapsulates system activities
	//
	//
	// Expand this for documentation
		//AutoLogon documentation
		{
			////////////////////////////////////////////////////////////////////////////
			// AutoLogon
			//
			// Purpose: 		Sets registry keys to allow the system to automatically login after a restart.
			//
			//
			// class:     cSYSTEM
			{
				//
				// method:    window.UserName = "your username"
				// notes:     Used within a testcase to set the username registry key required for automatically logging a user into windows
				
				// method:    window.UserName = "your passord
				// notes:     Used within a testcase to set the password registry key required for automatically logging a user into windows
				
				// method:    window.UserName = "your domain
				// notes:     Used within a testcase to set the domain registry key required for automatically logging a user into windows
				
				// method:    window.AutoLogon(bLogon)
				// parameter: bLogon: TRUE: Verifies that the username and logon have been set, if so, sets the AutoLogon key to "1". 1 autologs in the user.
				// parameter: bLogon: FALSE: Sets the AutoLogon key to "0".(0 forces user to logon manually) And initializes the password to "".
				// notes:     A method which controls whether a system, at restart, automatically logs in the user based on pre-set registry keys.
				
				// method:    window.__Constructor = __InitDomain ()
				// notes:     A private member constructor which calls the __InitDomain() method at Run time.
				//
				// method:    window.__InitDomain()
				// notes:     Initializes the DefaultDomainName Registry key to the current ZL domain.
				//
				// method:    window.__WINLOGON_REG_KEY = "Software\Microsoft\Windows NT\CurrentVersion\Winlogon"
				// notes:     Private member that sets the registry key to all of the windows logon registry values.
				
				// method:    window.__sUserName = ""
				// notes:     Initializing the rivate member to sPassword.
				
				// method:    window.__sPassword = ""
				// notes:     Initializing the rivate member to sPassword.
				
				// method:    window.__sDomain = ""
				// notes:     Initializing the rivate member to sPassword.
		//TestCaseTracker documentation
			////////////////////////////////////////////////////////////////////////////
			// TestCaseTracker
			//
			// Purpose: 		Tracks TestCase Execution through an ini file
			//
			//
			// class:     cSYSTEM
				//
				// method:    window.ResetBookMark ()
				// notes:     Resets the bookmark to "Start". "Start" should containe the first series of testcases to run.
				//
				// method:    window.BookMark = "your bookmark"
				// notes:     Used within a testcase to set the bookmark for the series of testcase that should be run next..
				//
				// method:    switch window.BookMark
				// notes:     Used within a main statement to retrieve the current book mark. A case statement in the switch should contain the method names of the testcases to run.
			// Testcase tracker works in conjunction with a main in your testcase file.
			// The main in your testcase file requires a switch statement. As follows:
			// main()
				// switch TestCaseTracker.BookMark
				{
					// case "Start"
					{
						// ExecuteTestcase1()
						// ExecuteTestcase2()
						// ExecuteTestcase3()
					// case "Finish"
						// ExecuteTestcase4()
			// It it used to track which test cases should be run next after restarting windows.
			// It works in conjunction with an ini file called TestCaseTracker.ini.
			// TestCaseTracker.ini stores a "bookmark" that you read and write to, depending on which case of a
			// switch statement you'd like to run.
			// This requires an external ini file called TestCaseTracker.ini. This file
			// must be stored in the same directory as the t file being executed.
		//StartUpBat documentation
			////////////////////////////////////////////////////////////////////////////
			// StartUpBat
			//
			// Purpose: 		Allows you to edit a batch file (silk_library.bat) to put
			//					in specific test case info and then put the bat file in or delete it
			//					from the startup folder. This then can allow the execution of silk partner
			//					after restart without assistance.
			//					This requires an external batch file called silk_startup.bat. This file
			//					must be stored in the same directory as the t file being executed.
			// class:     cSYSTEM
				//
				// method:    window.SilkTestCaseFile = "the name and location of the test file"
				// notes:     Used to set the name and location of the test file executed by the batch file
				
				// method:    window.SilkExecParams = "the partner.exe executable plus any parameters
				// notes:     Used to set the parameters for executing silk partner from a batch file.
				
				// method:    window.SilkExecPath = "the location of partner.exe
				// notes:     Used to set the location of the silk partner installation.
				
				// method:    window.SetBatchCode()
				// notes:     A method used to write out to the batch file the SilkTestCaseFile, SilkExecParams,
				//			  and SilkExecPath properies.If the file is already in the folder, the
				//			  existing file is deleted and recopied.
				// method:    window.PutBatInStartup()
				// notes:     A method that copies a batch file to the windows startup folder. It uses the window
				//			 tag location set by the user from a constant.
				
				// method:    window.DelBatFromStartup()
				// notes:     A method that deletes a batch file from the windows startup folder. It uses the window
				//			  tag location set by the user from a constant.
				//
				// method:    window.__GetStartUpPath()
				// notes:     returns the startup path of the os based on the value of the startup registry key.
				//
				// method:    window.__sSilkTestCaseFile = ""
				// notes:     Initializing the private member to sSilkTestCaseFile.
				
				// method:    window.__sSilkExecParams = ""
				// notes:     Initializing the rivate member to sSilkExecParams.
				
				// method:    window.__sSilkExecPath = ""
				// notes:     Initializing the rivate member to sSilkExecPath.
			
			
		//
		// inherits: 		cINIFILE
		//
		// PUBLIC MEMBERS - CONSTANTS:
		//
		// 		sDirSeparator			Set to "\" for MS Windoze
		//
		// PUBLIC MEMBERS - METHODS:
		//
		// 		TimeStamp()				Returns a STRING of the current date and time
		// 		GetEnv(s)				Returns the STRING stored in the environment
		//								variable specified in s
		// 		CurrentDir()			Returns current working dir for the Silk process
		// 		IsWindows()				Returns true if running on any version of MS Windows
		// 		rPerformanceIndexOfThisCPU ()	Returns an amount of time 10000 list searches
		//								took. Not a valid test with today's caching CPUs.
		//
		// PUBLIC MEMBERS - PROPERTIES:
		//
		// 		sShell					Returns shell name, only works on MS Windows
		// 		sTempDir				Returns the temp dir for any OS with a TEMP
		//								environment variable (Windows only?)
		// 		oTempDir				Returns TEMP dir as a cDIR
		//		rDeskTop				Returns the RECT of the desktop. Written before there
		//								was a Desktop object included in Silk.
		//
		// 		rTimerLatencyOnThisMachine	Returns a REAL of the timer latency on this
		//								machine.
		// 		rHalfTimerLatencyOnThisMachine	Returns timer latency of this machine/2
		//
		// 		iHour					Returns the current hour of the day
		// 		iMinute					Returns the current minute
		// 		iSecond					Do I really have to spell this out?
		// 		iYear					I think you get the point.
		//  	iMonth					Etc.
		// 		iDay					Etc.
		// 		sSortableDate			Returns STRING in the form YYYYMMDD
		// 		sSortableTime			Returns STRING in the form HHMMSS
		// 		sSortableDateTime		Returns STRING in the form YYYYMMDDHHMMSS
		// 		iDayOfWeek				Integer of day of the week
		// 		iDayOfYear				And how many days we are into the year
		//
	// AgentInterface is an instance rather than a class,
	// because there's only one Agent. This object's job is
	// to abstract the machine switching mechanism. There's only
	// one call, SwitchMachine(sName optional) If you specify
	// sName, control will switch to that machine. If you
	// don't, control will switch back to the current machine.
	////////////////////////////////////////////////////////////////////////////
					}
				}
			}
		}
	}
	WINDOW cBASE cSystem
	{
		
		const lsInstanceFieldList    = {'DateTimeNow'};
		const lsInstancePropertyList = 
		{
			"sDirSeparator",
			"sWinSysDrive",
			"sWinSysDir",
			"sSystemDir",
			'sShell',
			'sTempDir',
			'oTempDir',
			'rTimerLatencyOnThisMachine',
			'iColorDepth',
			'SystemDate',
			'sHostName',
			'UserName',
			'Password',
			'Domain'
		};
		
		cDATE		DateTimeNow
		{
			property dtDateTime		// overriding the class member
			{
				DATETIME Get()
				{
					return GetDateTime();
		
				}
			}
		}
		property 	sDirSeparator
		{
			STRING Get()
			{
				STRING sResult = "\";
				switch (GetGUIType ())
				{
					case msw:
						sResult = "\";
					// case mac
						// sResult = "|"
					// case mswdos
						// sResult = "\"
					case motif:
						sResult = "/";
					// case pm
						// sResult = "\"
				}
				return sResult;
			}
		}
		property 	sShell
		{
			STRING Get()
			{
				STRING sResult;
				if ! this.IsWindows()
				{
					raise LIBERROR_CANT_GET_OS_DATA,"*** Error: LIBERROR_CANT_GET_OS_DATA - cSystem.sShell was unable to get platform shell";
				}
				else
				{
					sResult = GetEnv("COMSPEC");
				}
				return sResult;
			}
		}
		property 	rTimerLatencyOnThisMachine
		{
			REAL Get ()
			{
				return cTIMER ().rObjectLatency;
			}
		}
		property	sHostName
		{
			STRING Get()
			{
				STRING sData = "UNABLE TO DETERMINE MACHINE NAME - Please add COMPUTERNAME environment variable.";
				STRING sValue = GetEnv("COMPUTERNAME");
				if sValue != ""
				{
					sData=sValue;
				}
				return sData;
		
			}
		}
		property 	sWinSysDrive
		{
			STRING Get()
			{
				STRING sResult = "";
				msw32 sResult = Left(this.ReplaceEnvVar("%windir%\system"),3);
				mswnt sResult = Left(this.ReplaceEnvVar("%windir%\system32"),3);
				return sResult;
			}
		}
		property 	sWinSysDir
		{
			STRING Get()
			{
				STRING sResult = "";
				msw32 sResult = this.ReplaceEnvVar("%windir%\system");
				mswnt sResult = this.ReplaceEnvVar("%windir%\system32");
				return sResult;
			}
		}
		property	sProgramsDir
		{
			STRING Get()
			{
				return cSystem.GetReg("HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\ProgramFilesDir");
			}
		}
		property 	sSystemDir
		{
			STRING Get()
			{
				STRING sResult = "";
				msw32 sResult = this.ReplaceEnvVar("%windir%");
				mswnt sResult = this.ReplaceEnvVar("%windir%");
				return sResult;
			}
		}
		property 	sTempDir
		{
			STRING Get()
			{
				return GetEnv("TEMP")+sDirSeparator;
			}
		}
		property 	oTempDir
		{
			OBJECT Get()
			{
				OBJECT result = cDIR(this.sTempDir);
				return result;
			}
		}
		property	iColorDepth
		{
			INTEGER Get()
			{
				return this.getColorDepth();
		
			}
		}
		STRING 		CurrentDir()
		{
			return SYS_GetDir();
		}
		INTEGER		GetColorDepth()
		{
			
			LONG PLANES=14;
			LONG BITSPIXEL=12;
			
			LONG hdc = GetDC(Desktop.GetHandle());
			//Print (hdc)
			INT dBitsInAPixel = GetDeviceCaps(hdc, PLANES) * GetDeviceCaps(hdc, BITSPIXEL);
			return dBitsInAPixel;
			
			
		}
		BOOLEAN		EnvVarExists(STRING sVar)
		{
			STRING sValue = SYS_GetEnv(sVar);
			if sValue == ""
			{
				return FALSE;
			}
			else
			{
				return TRUE;
			}
		}
		STRING 		GetEnv(STRING sVar)
		{
			return SYS_GetEnv(sVar);
		}
		VOID 		SetEnv(STRING sName, STRING sValue)
		{
			if !EnvVarExists(sName)
			{
				Log.LogWarning("Reg Name '{sName}' was not an existing environmental variable. Creating now with a value of '{sValue}'");
				Reg_CreateValue(HKEY_LOCAL_MACHINE,"SYSTEM\CurrentControlSet\Control\Session Manager\Environment", sName, sValue);
			}
			else
			{
				SYS_SetRegistryValue(HKEY_LOCAL_MACHINE,"SYSTEM\CurrentControlSet\Control\Session Manager\Environment", sName, sValue);
			}
		}
		ANYTYPE		GetReg(STRING sFullKey)
		{
			STRING sKey=GetLeftOf(sFullKey,"\",TRUE);
			STRING sPath=GetLeftOf(GetRightOf(sFullKey,"\",TRUE),"\");
			STRING sItem=GetRightOf(sFullKey,"\");
			return SYS_GetRegistryValue(@sKey,sPath,sItem);
			
		}
		BOOLEAN 	RegKeyExists(INTEGER iKey, STRING sPath, STRING sItem)
		{
			STRING sValue;
			BOOLEAN bReturn = FALSE;
			do
			{
				sValue = SYS_GetRegistryValue(iKey,sPath,sItem);
				bReturn = TRUE;
			}
			except
			{
				bReturn = FALSE;
				ExceptClear();
			}
			return bReturn;
		}
		BOOLEAN 	IsWindows()
		{
			return sContains("{GetGuiType()}","Microsoft Windows");
		}
		STRING 		ReplaceEnvVar(STRING sEnvVarText)
		{
			STRING sEnvVar;
			STRING sEnvValText = sEnvVarText;
			if sContains(sEnvVarText,"%")
			{
				//retrieve the environmental variable from the string
				sEnvVar = GetField(sEnvVarText, '%',2);
				//Retrieve value of environmental variable and replace the variable with the actual value within the text
				sEnvValText =StrTran(sEnvVarText,"%{sEnvVar}%",SYS_GetEnv(sEnvVar));
			}
			if sContains(sEnvValText,"%")
			{
				sEnvValText = this.ReplaceEnvVar(sEnvValText);
			}
			return sEnvValText;
		}
		REAL 		rPerformanceIndexOfThisCPU ()
		{
			OBJECT tPerformanceTimer = cTIMER ().HotStart ();
			
			ANYTYPE a = 0.0, item, x, l = {"A", "B", "C", "D", "E"}, s = "One two three four five six";
			
			// TESTS
			for x = 1 to 10000
			{
				for each item in l
				{
					x = listfind (l, item);
				}
				x = listfind (l, "Z");
				a = a + 1.1;
				s[1] = "";
				s[1] = "O";
				// END TESTS
				
			}
			return tPerformanceTimer.HotStop ();
			
			
		}
		VOID		SwitchMachine(STRING name optional)
		{
			if name != NULL
			{
				// name was specified
				// DebugPrint("AgentInterface.SwitchMachine({name})")
				// swicth to remote machine
				// First, save off local name
				__hLocalMachine = GetMachine ();
				
				// Now get the handle for the other box
				// And connect to it
				do
				{
					__hCurrentMachine = Connect(name);
					SetMachine(__hCurrentMachine);
				}
				except
				{
					do
					{
						__hCurrentMachine = Connect(name);
						SetMachine(__hCurrentMachine);
					}
					except
					{
						do
						{
							__hCurrentMachine = Connect(name);
							SetMachine(__hCurrentMachine);
						}
						except
						{
							Log.LogError(" Failure on connecting to maching {name} (3 tries)");
							reraise;
						}
					}
					ExceptClear();
					ExceptClear();
				}
			}
			else
			{
				// return to local machine
				if ! IsSet(__hLocalMachine)
				{
					__hLocalMachine = GetMachine ();
				}
				else
				{
					SetMachine(__hLocalMachine);
					Disconnect(__hCurrentMachine);
				}
				__hCurrentMachine = __hLocalMachine;
			
			// Example Code From Segue
				// HMACHINE target_machine     // target computer
				// HMACHINE host_machine       // host computer
				// STRING sTarget = "sunfish"  // target's network name
				// STRING sHost = "moonray"    // host's network name
				// // save host’s handle
				// host_machine = GetMachine ()
				// // save target's handle
				// target_machine = Connect (sTarget)
				// // what is currently active on the target machine?
				// Print ("Active window on Target: ", Desktop.GetActive ())
				// // switch to host machine
				// SetMachine (host_machine)
				// // what is currently active on host machine?
				// Print ("Active window on Host: ", Desktop.GetActive ())
				// Disconnect (target_machine)  // disconnect from target
		
			}
		}
		STRING 		TimeStamp()
		{
			return "{DateStr()} {TimeStr()}";
		}
		property	SystemDate
		{
			STRING Get()
			{
				return DateStr();
			}
			VOID Set(STRING sIncoming)
			{
				if sIncoming == cSystem.CurrentDate
				{
					cSystem.IsCurrentDate = "TRUE";
				}
				else
				{
					cSystem.IsCurrentDate = "FALSE";
				}
				__SetDateBat.lsData = {'date {sIncoming}','time timestr()','exit'};
				__SetDateBat.Write();
				cEXEFILE().RunAndWait("{DATA_DIR}\setdate.bat");
			}
		}
		STRING 		AddDaysToCurrentDate(INTEGER iDays)
		{
			DATETIME dtDate = AddDateTime(GetDateTime ( ),iDays);
			STRING sNewDate = FormatDateTime (dtDate, "mm/dd/yy");
			return sNewDate;
		}
		property 	CurrentDate
		{
			STRING Get()
			{
				return  __TestTracker.Test.CurrentDate.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.CurrentDate.sValue =sIncoming;
			}
		}
		property 	IsCurrentDate
		{
			STRING Get()
			{
				return  __TestTracker.Test.IsCurrentDate.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.IsCurrentDate.sValue =sIncoming;
			}
		}
		VOID 		ResetSystemDateToCurrent()
		{
			if MakeBool(this.IsCurrentDate)
			else
			{
				this.SystemDate = this.CurrentDate;
				
		
		// AUTOLOGON AND RESTART INTERFACES
		//autologon properties
			}
		}
		property 	UserName
		{
			STRING Get()
			{
				return GetRegValue("HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Winlogon\DefaultUserName");
			}
			VOID Set(STRING sUserName)
			{
				CreateRegValue("HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Winlogon\DefaultUserName",sUserName);
			}
		}
		property 	Password
		{
			STRING Get()
			{
				STRING sPassword;
				do
				{
					sPassword = GetRegValue("HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Winlogon\DefaultPassword");
				}
				except
				{
					CreateRegValue("HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Winlogon\DefaultPassword","");
					ExceptClear();
				}
				return GetRegValue("HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Winlogon\DefaultPassword");
			}
			VOID Set(STRING sPassword)
			{
				CreateRegValue("HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\WinlogonefaultPassword",sPassword);
			}
		}
		mswnt property Domain
		{
			STRING Get()
			{
				return GetRegValue("HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Winlogon\DefaultDomainName");
			}
			VOID Set(STRING sDomain)
			{
				CreateRegValue("HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Winlogon\DefaultDomainName",sDomain);
		
		//simple reboot interface
			}
		}
		VOID		SimpleRestart()
		{
			this.SetBatchCode();
			this.PutBatInStartUp();
			Restart();
		}
		VOID		CleanUpFromSimpleRestart()
		{
			this.DelBatFromStartUp();
		
		//autologon methods
		}
		VOID 		SetUserNamePassword(STRING sUserName, STRING sPassword)
		{
			// if this.Password !=""
			{
				// Log.LogWarning("***Warning: Login Credentials Exist. UserName and Password Unchanged.")
			// else
				this.UserName = sUserName;
				this.Password = sPassword;
			}
		}
		VOID 		AutoLogon(BOOLEAN bLogon)
		{
			if bLogon
			{
				if this.UserName =="" || this.Password ==""
				{
					CleanUpTestFile();
					raise LIBERROR_WRONG_NUMBER_OF_ARGUMENTS, "*** Error: LIBERROR_WRONG_NUMBER_OF_ARGUMENTS in cSystem.AutoLogon() - UserName or Password are blank.: UserName: {this.UserName}, Password: {this.Password}";
				}
				else
				{
					CreateRegValue("AutoAdminLogon","1");
				}
			}
			else
			{
				CreateRegValue("AutoAdminLogon","0");
		
		// if bSkipAutoLogon == TRUE, skip AutoLogon ()
			}
		}
		VOID 		PreRestart(BOOLEAN bRestart, BOOLEAN bSkipAutoLogon optional, INTEGER iDelay optional, STRING sDomain optional)
		{
			//	Put the startup batch file in the startup folder
			this.SetBatchCode(iDelay);
			this.PutBatInStartUp();
			//	Set the system to automatically logon
			// //AutoLogon Information
			{
				// this.UserName = "xxxxx"
				// this.Password = "xxxxx"
			}
			if IsNull (bSkipAutoLogon)
			{
				bSkipAutoLogon = FALSE;
			}
			if ! bSkipAutoLogon
			{
				this.AutoLogon(TRUE);
			}
			if !IsNull(sDomain)
			{
				mswnt cSystem.Domain = sDomain;
			//set for system restart
			}
			if bRestart
			{
				Restart();
				exit;
			}
		}
		VOID 		PostRestart(BOOLEAN bSkipAutoLogon optional, STRING sDomain optional)
		{
			//	Turnoff Autologon, delete password from registry
			if IsNull (bSkipAutoLogon)
			{
				bSkipAutoLogon = FALSE;
			}
			if !IsNull (sDomain)
			{
				mswnt cSystem.Domain = sDomain;
			}
			if ! bSkipAutoLogon
			{
				this.AutoLogon(FALSE);
			// Delete the batch file from StartUp
			}
			this.DelBatFromStartUp();
		
		//Start Up Batch Filder methods
		}
		VOID 		ClearBatchCode()
		{
			__StartUpBat.Zap();
		}
		VOID 		AddBatchCode(STRING sBatchCode, INTEGER iDelay optional)
		{
			if IsNull(iDelay)
			else
			{
				__StartUpBat.Append('ping 127.0.0.1 -n {iDelay}');
			}
			__StartUpBat.Append(sBatchCode);
			__StartUpBat.Write();
		}
		VOID 		SetBatchCode(INTEGER iDelay optional)
		{
			if IsNull(iDelay)
			{
				__StartUpBat.lsData = {'start {__StartUpBat.__sSilkExecPath}{__StartUpBat.__GetExecParams()} "{__StartUpBat.__sSilkTestCaseFile}"'};
			}
			else
			{
				__StartUpBat.lsData = {'@echo off','ping 127.0.0.1 -n {iDelay}','start {__StartUpBat.__sSilkExecPath}{__StartUpBat.__GetExecParams()} "{__StartUpBat.__sSilkTestCaseFile}"'};
			}
			__StartUpBat.Write();
		}
		VOID 		PutBatInStartUp(STRING sStartUpPath optional)
		{
			if IsNull(sStartUpPath)
			{
				do
				{
					__StartUpBat.CopyTo("{__StartUpBat.__GetStartupPath()}\silk_startup.bat");
				}
				except
				{
					if (ExceptNum() == -13000)
					{
						this.DelBatFromStartUp();
						this.PutBatInStartUp();
						ExceptClear();
					}
					else
					{
						reraise;
					}
				}
			}
			else
			{
				do
				{
					__StartUpBat.CopyTo("{sStartUpPath}\silk_startup.bat");
				}
				except
				{
					if (ExceptNum() == -13000)
					{
						this.DelBatFromStartUp(sStartUpPath);
						this.PutBatInStartUp(sStartUpPath);
						ExceptClear();
					}
					else
					{
						reraise;
					}
				}
			}
		}
		VOID 		DelBatFromStartUp(STRING sStartUpPath optional)
		{
			if IsNull(sStartUpPath)
			{
				do
				{
					cTEXTFILE("{__StartUpBat.__GetStartupPath()}\silk_startup.bat").Delete();
				}
				except
				{
					if (ExceptNum() == -13000)
					{
						ExceptClear();
					}
					else
					{
						reraise;
					}
				}
			}
			else
			{
				do
				{
					cTEXTFILE("{sStartUpPath}\silk_startup.bat").Delete();
				}
				except
				{
					if (ExceptNum() == -13000)
					{
						ExceptClear();
					}
					else
					{
						reraise;
					}
				}
			}
		}
		VOID 		LaunchBatchFile()
		{
			cEXEFILE(__StartUpBat.sFileName).Run();
		
		// MAY ALSO BELONG HERE
		//Startup Folder Batch File
		}
		property 	SilkTestCaseFile
		{
			STRING Get()
			{
				return __StartUpBat.__sSilkTestCaseFile;
			}
			VOID Set(STRING sSilkTestCaseFile)
			{
				__StartUpBat.__sSilkTestCaseFile = sSilkTestCaseFile;
			}
		}
		property 	SilkExecPath
		{
			STRING Get()
			{
				return __StartUpBat.__sSilkExecPath;
			}
		}
		property 	SilkExecParams
		{
			STRING Get()
			{
				return __StartUpBat.__GetExecParams();
			}
		}
		property 	SilkProgramPath
		{
			STRING Get()
			{
				do
				{
					STRING sResult=SYS_GetRegistryValue(HKEY_LOCAL_MACHINE,"SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\partner.exe", "Path");
				}
				except
				{
					sResult="B:\Akien\Portable Programs\SilkTest\Partner.exe";
				}
				return sResult;
			}
		}
		property 	OverrideManifest
		{
			STRING Get()
			{
				return  __TestTracker.Test.OverrideManifest.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.OverrideManifest.sValue =sIncoming;
		
		// GENERALIZED FUCNTIONS
		// These appear to be generalized functions and likely belong 
		// in other parts of the library
			}
		}
		VOID 		Restart (BOOLEAN bNoExit optional)
		{
			if IsNull(bNoExit)
			{
				bNoExit = FALSE;
			}
			__WindowsShutDown.Restart();
			if bNoExit
			else
			{
				exit;
			}
		}
		VOID 		Shutdown ()
		{
			cSystem.ClearBatchCode();
			cSystem.AddBatchCode('start wizmo shutdown',10);
			cSystem.LaunchBatchFile();
			exit;
		}
		STRING 		GetFile (STRING sFileNamePath)
		{
			STRING sFile = SubStr(sFileNamePath,StrPos("\",sFileNamePath,TRUE)+1);
			return sFile;
		}
		STRING 		GetFileVersion(STRING sFullPathAndFileName, BOOLEAN bFileNotExistNoError optional)
		{
			if IsNull(bFileNotExistNoError)
			{
				bFileNotExistNoError = FALSE;
			}
			INTEGER i = 1;
			STRING sResult = "";
			STRING sFinalResult = "";
			STRING sItem = "";
			STRING sChangedItem = "";
			if !SYS_FileExists("{sFullPathAndFileName}")
			{
				sFinalResult="";
			}
			else
			{
				if !SYS_FileExists("{cSystem.sWinSysDir}\Properties.dll")
				{
					do
					{
						SYS_CopyFile("Properties.dll","{cSystem.sWinSysDir}\Properties.dll");
					}
					except
					{
						Log.print(ExceptData());
						ExceptClear();
					}
				}
				if GetVersion(sFullPathAndFileName,sResult) == 0
				{
					sFinalResult = sResult;
					// while GetField (sResult, ".", i) !=""
					{
						// if i < 4
						{
							// sFinalResult = sFinalResult + GetField (sResult, ".", i) + "."
						// else
							// sItem = GetField (sResult, ".", i)
							// sChangedItem = NormalizeVersionString(sItem)
							// sFinalResult = sFinalResult + sChangedItem
							//
						// i++
						}
					}
				}
				else
				{
					if bFileNotExistNoError
					else
					{
						raise 1, "ERROR: Could not retrieve version number for {sFullPathAndFileName}. Full file name and path may be incorrect or file may not exist.";
				
				
					}
				}
			}
			return sFinalResult;
		}
		STRING 		ChopVersion(STRING sVersion)
		{
			INTEGER iCharNum = 0;
			INTEGER iStringLen = Len(sVersion);
			STRING sChar = "";
			INTEGER iDotCount = 0;
			for (iCharNum=1; iCharNum <= iStringLen; iCharNum++)
			{
				sChar = SubStr (sVersion, iCharNum, 1);
				if MatchStr(".",sChar)
				{
					iDotCount++;
				}
			}
			if iDotCount == 3
			{
				sVersion = Left(sVersion,StrPos(".",sVersion,TRUE)-1);
			}
			STRING sTriadNum = GetField (sVersion,".", 3);
			if StrPos("0",sTriadNum) == 1
			{
				STRING sChoppedTriadNum = Right(sTriadNum,2);
				sVersion= StrTran (sVersion, sTriadNum, sChoppedTriadNum );
			}
			return sVersion;
		}
		STRING 		GetLocalMachineName ()
		{
			const STRING REG_PATH_COMPUTERNAME = "SYSTEM\CurrentControlSet\Control\ComputerName\ComputerName";	// reg key
			const STRING COMPUTER_NAME = "COMPUTERNAME";															// keg key name
			return SYS_GetRegistryValue (HKEY_LOCAL_MACHINE, REG_PATH_COMPUTERNAME, COMPUTER_NAME);				//return the value for the key name
		}
		STRING		GetLocalIPAddress()
		{
			LIST OF STRING lsResults;
			STRING sIPAddress="0.0.0.0";
			INTEGER i;
			SYS_SetDir(GetProgramDir());
			OBJECT Pinger = cTEXTFILE("{GetProgramDir ()}\DoPing.bat");
			Pinger.lsData = {'ipconfig'};
			Pinger.Write();
			lsResults = cEXEFILE(Pinger.sFileName).RunAndWait();
			for (i=1; i<=listcount(lsResults);i++)
			{
				if matchstr("*IP Address*",lsResults[i])
				{
					sIPAddress=substr(lsResults[i],strpos(" ",lsResults[i],TRUE)+1,strpos(chr(13),lsResults[i],TRUE)-strpos(" ",lsResults[i],TRUE)-1);
					break;
				}
			}
			return sIPAddress;
		}
		LIST OF ANYTYPE ConvertStringToList(STRING sList)
		{
			if MatchStr("*},*",sList)
			{
				sList = StrTran(sList,"},","}");
			}
			INTEGER i;
			LIST OF STRING lsTestList;
			LIST OF ANYTYPE laList;
			STRING sTempValue = "";			//strip off the braces
			i=1;
			INTEGER b = 1;
			if !Contains(sList,"}")
			{
				while GetField (sList, ",", i) !=""
				{
					ListAppend(lsTestList,Trim(GetField (sList, ",", i)));
					ListAppend(laList,lsTestList);
					lsTestList={};
					i++;
				}
			}
			else
			{
				while GetField (sList, "}", b) !=""
				{
					sTempValue = GetField(sList,"}",b);
					sTempValue = StrTran(sTempValue, ""{", "");			//strip off the front brace
					while GetField (sTempValue, ",", i) !=""
					{
						ListAppend(lsTestList,Trim(GetField (sTempValue, ",", i)));
						i++;
					}
					ListAppend(laList,lsTestList);
					lsTestList = {};
					b++;
					i=1;
				}
			}
			return laList;
		
		}
		STRING		ConvertListToString(LIST OF ANYTYPE lsList)
		{
			STRING sList = "";
			STRING sMessage = "";
			for each sList in lsList
			{
				sMessage = sMessage + sList;
			}
			return sMessage;
		}
		VOID 		SetBrowserOptions (INTEGER iTimeout optional)
		{
			do
			{
				const DOM_BROWSER = __PartnerIni.Runtime.DefaultBrowser.sValue;
				// SetDefaultBrowserType ([BROWSERTYPE]DOM_BROWSER)
				// SetBrowserType ([BROWSERTYPE]DOM_BROWSER)
				if ! IsNull (iTimeout)
				{
					Agent.SetOption (OPT_APPREADY_TIMEOUT, iTimeout);
				}
			}
			except
			{
				Log.Print("This is probably caused by not having a default browser set in the Runtime Options dialog.");
				Log.Print("Fix this and run the test again.");
				reraise;
		//Retrieves file name from any folder,optional searchcritera
			}
		}
		STRING GetFileFromFolder(STRING sFolder, STRING sSearchCriteria optional,BOOLEAN bDir optional,LIST OF STRING lsExcludeFiles optional)
		{
			if IsNull(bDir)
			{
				bDir = FALSE;
			}
			LIST OF FILEINFO lfFiles;
			INTEGER iCount;
			STRING sFileFound = "";
			sFolder=Trim(sFolder);
			do
			{
				lfFiles = SYS_GetDirContents (sFolder);
			}
			except
			{
				if MatchStr("* already exists",ExceptData())
				else if MatchStr("* does not exist",ExceptData())
				else
				{
					Log.LogError("Accessing {sFolder} caused the following error: ");
					Log.LogError(ExceptData(),TRUE );
					
				}
				ExceptClear();
			}
			for iCount = 1 to ListCount (lfFiles)
			{
				if bDir
				{
					if IsNull(sSearchCriteria)
					{
						if SYS_DirExists("{sFolder}\{lfFiles[iCount].sName}")
						{
							sFileFound=lfFiles[iCount].sName;
							break;
						}
					}
					else
					{
						if MatchStr(sSearchCriteria,lfFiles[iCount].sName)
						{
							if SYS_DirExists("{sFolder}\{lfFiles[iCount].sName}")
							{
								sFileFound=lfFiles[iCount].sName;
								break;
							}
						}
					}
				}
				else
				{
					if IsNull(sSearchCriteria)
					{
						if SYS_FileExists("{sFolder}\{lfFiles[iCount].sName}")
						{
							sFileFound=lfFiles[iCount].sName;
							if ListFind(lsExcludeFiles,sFileFound) == 0
							{
								break;
							}
						}
					}
					else
					{
						if MatchStr(sSearchCriteria,lfFiles[iCount].sName)
						{
							sFileFound=lfFiles[iCount].sName;
							break;
						}
					}
				}
			}
			return sFileFound;
		
		// SHOULD BE MOVED TO AN EMAIL OBJECT
		//Email Parameters for "blat.exe"
		}
		property 	SetTemplate
		{
			STRING Get()
			{
				return __EmailTemplate.sFileName;
			}
			VOID Set(STRING sIncoming)
			{
				__EmailTemplate.sFileName = sIncoming;
			}
		}
		property 	Host
		{
			STRING Get()
			{
				return __EmailTemplate.Address.Host.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__EmailTemplate.Address.Host.sValue = sIncoming;
			}
		}
		property 	From
		{
			STRING Get()
			{
				return __EmailTemplate.Address.From.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__EmailTemplate.Address.From.sValue = sIncoming;
			}
		}
		property 	To
		{
			STRING Get()
			{
				return __EmailTemplate.Address.To.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__EmailTemplate.Address.To.sValue = sIncoming;
			}
		}
		property 	ReplyTo
		{
			STRING Get()
			{
				return __EmailTemplate.Address.ReplyTo.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__EmailTemplate.Address.ReplyTo.sValue = sIncoming;
			}
		}
		property 	Subject
		{
			STRING Get()
			{
				return __EmailTemplate.Message.Subject.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__EmailTemplate.Message.Subject.sValue = sIncoming;
			}
		}
		property 	AddFileToBody
		{
			STRING Get()
			{
				return __EmailTemplate.Message.AddFileToBody.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__EmailTemplate.Message.AddFileToBody.sValue = sIncoming;
			}
		}
		property 	Body
		{
			STRING Get()
			{
				return __EmailTemplate.Message.Body.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__EmailTemplate.Message.Body.sValue = sIncoming;
			}
		}
		VOID 		QuickSend(STRING sHost null optional, STRING sFrom null optional, STRING sReplyTo null optional, STRING sTo null optional, STRING sSubject null optional, STRING sBody null optional)
		{
			if IsNull(sHost)
			{
				sHost=__EmailTemplate.Address.Host.sValue;
			}
			if IsNull(sFrom)
			{
				sFrom=__EmailTemplate.Address.From.sValue;
			}
			if IsNull(sReplyTo)
			{
				sReplyTo=__EmailTemplate.Address.ReplyTo.sValue;
			}
			if IsNull(sTo)
			{
				 sTo=__EmailTemplate.Address.To.sValue;
			}
			if IsNull(sSubject)
			{
				sSubject=__EmailTemplate.Message.Subject.sValue;
			}
			if IsNull(sBody)
			{
				sBody=__EmailTemplate.Message.Body.sValue;
			
			}
			APP_Start('blat.exe -install {sHost} {sFrom}');
			print('blat.exe -install {sHost} {sFrom}');
			sleep(3);
			// cEXEFILE("blat.exe").Run(' C:\CVS_Data\send.txt -to {sTo} -replyto {sReplyTo} -s "{sSubject}" -body {sBody}')
			APP_Start('blat.exe C:\CVS_Data\send.txt -to {sTo} -replyto {sReplyTo} -s "{sSubject}" -body "{sBody}"');
			Log.print('blat.exe C:\CVS_Data\send.txt -to {sTo} -replyto {sReplyTo} -s "{sSubject}" -body "{sBody}"');
		}
		VOID 		SendMail()
		{
			cEXEFILE("blat.exe").Run('-install {Host} {From}');
			sleep(3);
			cEXEFILE("blat.exe").Run('{AddFileToBody} -to {To} -replyto {ReplyTo} -s "{Subject}"');
			// print(cEXEFILE("blat.exe").RunAndWait('{AddFileToBody} -to {To} -replyto {ReplyTo} -s "{Subject}"'))
			Log.print('blat.exe {AddFileToBody} -to {To} -replyto {ReplyTo} -s "{Subject}"');
		
		// THIS NEEDS TO BE MOVED TO TATE.INC --- cTESTCASETRACKER?
		//testcase tracker properties
		}
		property 	TestStartNum
		{
			STRING Get()
			{
				if __TestTracker.Test.TestStartNum.sValue==""
				{
					Log.LogError("Test Starting Number has no value. Must Initialize Tests before using this property.");
					Log.ExceptPrint();
					return "";
				}
				else
				{
					return  __TestTracker.Test.TestStartNum.sValue;
				}
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.TestStartNum.sValue = sIncoming;
			}
		}
		property 	TestList
		{
			LIST OF STRING Get()
			{
				if __TestTracker.Test.TestList.sValue==""
				{
					Log.LogError("Test List has no value. Must Initialize Tests before using this property.");
					Log.ExceptPrint();
					return {};
				}
				else
				{
					return ConvertStringToList(__TestTracker.Test.TestList.sValue)[1];
				}
			}
			VOID Set(LIST OF STRING lsIncoming)
			{
				__TestTracker.Test.TestList.sValue = [STRING]lsIncoming;
			}
		}
		property 	TestMarker
		{
			STRING Get()
			{
				if __TestTracker.Test.TestMarker.sValue==""
				{
					Log.LogError("Marker has no value. Must Initialize Tests before using this property.");
					Log.ExceptPrint();
					return "";
				}
				else
				{
					return  __TestTracker.Test.TestMarker.sValue;
				}
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.TestMarker.sValue = sIncoming;
			}
		}
		property 	PassedTests
		{
			STRING Get()
			{
				return  __TestTracker.Test.PassedTests.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.PassedTests.sValue =sIncoming;
			}
		}
		property 	FailedTests
		{
			STRING Get()
			{
				return  __TestTracker.Test.FailedTests.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.FailedTests.sValue =sIncoming;
			}
		}
		property 	BlockedTests
		{
			STRING Get()
			{
				return  __TestTracker.Test.BlockedTests.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.BlockedTests.sValue =sIncoming;
			}
		}
		property 	TotalTests
		{
			STRING Get()
			{
				if __TestTracker.Test.TotalTests.sValue==""
				{
					Log.LogError("Total Tests is empty. Must Initialize Tests before using this property.");
					Log.ExceptPrint();
					return "";
				}
				else
				{
					return  __TestTracker.Test.TotalTests.sValue;
				}
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.TotalTests.sValue =sIncoming;
			}
		}
		property 	AbortAllTests
		{
			STRING Get()
			{
				return  __TestTracker.Test.AbortAllTests.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.AbortAllTests.sValue =sIncoming;
			}
		}
		property 	TestResult
		{
			STRING Get()
			{
				return  __TestTracker.Test.TestResult.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.TestResult.sValue =sIncoming;
			}
		}
		property 	SkipTest
		{
			STRING Get()
			{
				return  __TestTracker.Test.SkipTest.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.SkipTest.sValue =sIncoming;
			}
		}
		property 	CaseMarker
		{
			STRING Get()
			{
				return  __TestTracker.Test.TestMarker.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.TestMarker.sValue = sIncoming;
			}
		}
		property 	RestartMachine
		{
			STRING Get()
			{
				STRING sResult = __TestTracker.Test.RestartMachine.sValue;
				return sResult;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.RestartMachine.sValue = sIncoming;
			}
		}
		property 	ShutdownMachine
		{
			STRING Get()
			{
				STRING sResult = __TestTracker.Test.ShutdownMachine.sValue;
				return sResult;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.ShutdownMachine.sValue = sIncoming;
		// property 	LoopTestSuite
			// STRING Get()
				// STRING sResult = __TestTracker.Test.LoopTestSuite.sValue
				// return sResult
			// VOID Set(STRING sIncoming)
				// if  IsDigit (sIncoming)
				{
					// __TestTracker.Test.LoopTestSuite.sValue = sIncoming
				// else
					// Log.LogError("{sIncoming} is not a number.")
		// property 	TestSuiteLoops
			// STRING Get()
				// STRING sResult = __TestTracker.Test.TestSuiteLoops.sValue
				// return sResult
			// VOID Set(STRING sIncoming)
				// if  IsDigit (sIncoming)
					// __TestTracker.Test.TestSuiteLoops.sValue = sIncoming
				// else
					// Log.LogError("{sIncoming} is not a number.")
				}
			}
		}
		property 	ExitSilk
		{
			STRING Get()
			{
				STRING sResult = __TestTracker.Test.ExitSilk.sValue;
				return sResult;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.ExitSilk.sValue = sIncoming;
			}
		}
		property 	BreakTCLoop
		{
			STRING Get()
			{
				STRING sResult = __TestTracker.Test.BreakTCLoop.sValue;
				return sResult;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.BreakTCLoop.sValue = sIncoming;
			}
		}
		property 	IntraTestMarker
		{
			STRING Get()
			{
				STRING sResult = __TestTracker.Test.IntraTestMarker.sValue;
				return sResult;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.IntraTestMarker.sValue = sIncoming;
			}
		}
		property 	LogIndicator
		{
			STRING Get()
			{
				STRING sResult = __TestTracker.Test.LogIndicator.sValue;
				return sResult;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.LogIndicator.sValue = sIncoming;
			}
		}
		property 	VMHostID
		{
			STRING Get()
			{
				return  __TestTracker.ProductState.VMHostID.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.VMHostID.sValue = sIncoming;
			}
		}
		property 	ProductVersion
		{
			STRING Get()
			{
				return  __TestTracker.ProductState.Version.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.Version.sValue = sIncoming;
			}
		}
		property 	RequiredTestsStatus
		{
			STRING Get()
			{
				return  __TestTracker.Test.RequiredTestsStatus.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.RequiredTestsStatus.sValue =sIncoming;
			}
		}
		property 	OptionalTestsStatus
		{
			STRING Get()
			{
				return  __TestTracker.Test.OptionalTestsStatus.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.OptionalTestsStatus.sValue =sIncoming;
			}
		}
		property 	TestSuiteName
		{
			STRING Get()
			{
				return  __TestTracker.Test.TestSuiteName.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.TestSuiteName.sValue =sIncoming;
			}
		}
		property 	SchedID
		{
			STRING Get()
			{
				return  __TestTracker.Test.SchedID.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.SchedID.sValue =sIncoming;
			}
		}
		property 	SchedHistID
		{
			STRING Get()
			{
				return  __TestTracker.Test.SchedHistID.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.SchedHistID.sValue =sIncoming;
			}
		}
		property 	SummaryLogName
		{
			STRING Get()
			{
				return  __TestTracker.Test.SummaryLogName.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.SummaryLogName.sValue =sIncoming;
			}
		}
		property 	MasterExecution
		{
			STRING Get()
			{
				return  __TestTracker.Test.MasterExecution.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.MasterExecution.sValue =sIncoming;
			}
		}
		property 	RunEnvironment
		{
			STRING Get()
			{
				if __TestTracker.Test.RunEnvironment.sValue == ""
				{
					__TestTracker.Test.RunEnvironment.sValue = "DEV";
				}
				return  __TestTracker.Test.RunEnvironment.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.RunEnvironment.sValue =sIncoming;
			}
		}
		property 	StartTateRegression
		{
			STRING Get()
			{
				if __TestTracker.Test.StartTateRegression.sValue == ""
				{
					__TestTracker.Test.StartTateRegression.sValue = "FALSE";
				}
				return  __TestTracker.Test.StartTateRegression.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.StartTateRegression.sValue =sIncoming;
		
		//For tracking builds being processed
			}
		}
		property 	TATEInitialized
		{
			STRING Get()
			{
				return __TestTracker.ProductState.TATEInitialized.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.TATEInitialized.sValue = sIncoming;
			}
		}
		property 	TestsInitialized
		{
			STRING Get()
			{
				return __TestTracker.Test.TestsInitialized.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.Test.TestsInitialized.sValue = sIncoming;
			}
		}
		property 	MessageInitialized
		{
			STRING Get()
			{
				return __TestTracker.ProductState.MessageInitialized.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.MessageInitialized.sValue = sIncoming;
			}
		}
		property 	TestsChanged
		{
			STRING Get()
			{
				return __TestTracker.ProductState.TestsChanged.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.TestsChanged.sValue = sIncoming;
			}
		}
		property 	SchedInitialized
		{
			STRING Get()
			{
				return __TestTracker.ProductState.SchedInitialized.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.SchedInitialized.sValue = sIncoming;
			}
		}
		property 	BuildInitialized
		{
			STRING Get()
			{
				return __TestTracker.ProductState.TATEInitialized.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.TATEInitialized.sValue = sIncoming;
			}
		}
		property 	MessageFileName
		{
			STRING Get()
			{
				return  __TestTracker.ProductState.MessageFileName.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.MessageFileName.sValue = sIncoming;
			}
		}
		property 	ExcelFile
		{
			STRING Get()
			{
				return  __TestTracker.ProductState.ExcelFile.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.ExcelFile.sValue =sIncoming;
			}
		}
		property 	MessagePath
		{
			STRING Get()
			{
				return  __TestTracker.ProductState.MessagePath.sValue;
			}
			VOID Set(STRING sMessagePath)
			{
				//set the path for retrieving the build files
				__TestTracker.ProductState.MessagePath.sValue = sMessagePath;
				if sMessagePath!=""
				{
					//set the file name that contains the build path needed to retrieve the installer files
					__TestTracker.ProductState.MessageFileName.sValue = __SetMessageFileName();
				}
			}
		}
		property 	BuildPath
		{
			STRING Get()
			{
				return  __TestTracker.ProductState.BuildPath.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.BuildPath.sValue =sIncoming;
				//once the build path is set, then get the sub build path where the installer files are found.
				__TestTracker.ProductState.SubBuildPath.sValue = __SetSubBuildPath();
			}
		}
		property 	SubBuildPath
		{
			STRING Get()
			{
				return  __TestTracker.ProductState.SubBuildPath.sValue;
			}
		}
		property 	LocalInstallerPath
		{
			STRING Get()
			{
				return __TestTracker.ProductState.LocalInstallerPath.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				//sIncoming is a unique identifier for the logs being created
				__TestTracker.ProductState.LocalInstallerPath.sValue = "{GetProgramDir()}\installs\{sIncoming}";
				do
				{
					SYS_MakeDir("{GetProgramDir()}\installs\");
				}
				except
				{
					if MatchStr("* already exists",ExceptData())
					else
					{
						Log.LogError(ExceptData(),TRUE );
					}
					ExceptClear();
				}
				do
				{
					SYS_MakeDir("{GetProgramDir()}\installs\{sIncoming}");
				}
				except
				{
					if MatchStr("* already exists",ExceptData())
					else
					{
						Log.LogError(ExceptData(),TRUE );
					}
					ExceptClear();
				}
			}
		}
		property 	ResultsPath
		{
			STRING Get()
			{
				return __TestTracker.ProductState.ResultsPath.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				//sIncoming is a unique identifier for the logs being created
				__TestTracker.ProductState.ResultsPath.sValue = sIncoming;
				// do
				{
					// SYS_MakeDir(__TestTracker.ProductState.ResultsPath.sValue)
				// except
					// if MatchStr("* already exists",ExceptData())
					// else
					{
						// CleanUpTestFile()
						// Log.LogError(ExceptData(),TRUE )
					}
				}
			}
		}
		property 	ManifestFileAndPath
		{
			STRING Get()
			{
				do
				{
					return __TestTracker.ProductState.ManifestFileAndPath.sValue;
				}
				except
				{
					if MatchStr("* has not been set*",ExceptData())
					{
						return "";
					}
					else
					{
						Log.LogError(ExceptData(),TRUE );
						return "";
					}
					ExceptClear();
				}
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.ManifestFileAndPath.sValue = sIncoming;
		
		//for tracking the OS being processed
			}
		}
		property 	OSInitialized
		{
			STRING Get()
			{
				return __TestTracker.ProductState.OSInitialized.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.OSInitialized.sValue = sIncoming;
			}
		}
		property 	CurrentOS
		{
			STRING Get()
			{
				return __TestTracker.ProductState.CurrentOS.sValue;
			}
			VOID Set(STRING sIncoming)
			{
				__TestTracker.ProductState.CurrentOS.sValue = sIncoming;
		
		//testcase tracker methods
			}
		}
		VOID ResetTestMarker()
		{
			{
				__TestTracker.Test.TestMarker.sValue = "1";
			}
		}
		VOID ResetIntraCaseMarker()
		{
			{
				__TestTracker.Test.IntraTestMarker.sValue = "TRUE";
			}
		}
		VOID InitializeTestFile(STRING sFilePath optional,STRING sTableName optional, STRING sFilter optional)
		{
			{
				__TestTracker.Test.TestMarker.sValue = "1";
				__TestTracker.Test.ExitSilk.sValue = "FALSE";
				__TestTracker.Test.RestartMachine.sValue = "FALSE";
				__TestTracker.Test.IntraTestMarker.sValue = "TRUE";
				__TestTracker.Test.IsCurrentDate.sValue = "TRUE";
				__TestTracker.Test.CurrentDate.sValue = DateStr();
				if !IsNull(sFilePath)
				{
					__TestTracker.Test.TotalTests.sValue = Str(cDATASOURCE(sFilePath).RowCount(sTableName,sFilter));
				}
				__TestTracker.Test.RequiredTestsStatus.sValue = "PASSED";
				__TestTracker.Test.OptionalTestsStatus.sValue = "PASSED";
				__TestTracker.Test.TestsInitialized.sValue = "TRUE";
				__TestTracker.ProductState.Version.sValue = "";
				__TestTracker.Test.TestResult.sValue = "";
				__TestTracker.Test.PassedTests.sValue = "0";
				__TestTracker.Test.FailedTests.sValue = "0";
				__TestTracker.Test.BlockedTests.sValue = "0";
			}
		}
		VOID ResetIntraTestMarker()
		{
			{
				__TestTracker.Test.IntraTestMarker.sValue = "TRUE";
			}
		}
		VOID CleanUpTestFile ()
		{
			__TestTracker.Test.SkipTest.sValue = "FALSE";
			__TestTracker.Test.OptionalTestsStatus.sValue = "PASSED";
			__TestTracker.Test.RequiredTestsStatus.sValue = "PASSED";
			__TestTracker.Test.TestMarker.sValue = "";
			__TestTracker.Test.IntraTestMarker.sValue = "TRUE";
			__TestTracker.Test.TotalTests.sValue = "";
			__TestTracker.Test.TestList.sValue = "";
			__TestTracker.Test.TestSuiteName.sValue = "";
			__TestTracker.Test.SchedID.sValue = "";
			__TestTracker.Test.SummaryLogName.sValue = "";
			__TestTracker.Test.ShutdownMachine.sValue = "FALSE";
			// do not remove, igor uses this!!!
			__TestTracker.Test.TestsInitialized.sValue = "FALSE";
		}
		VOID IncrementTestMarker()
		{
			__TestTracker.Test.TestMarker.sValue = Str(Val(__TestTracker.Test.TestMarker.sValue) +1);
		}
		VOID DecrementTestMarker()
		{
			__TestTracker.Test.TestMarker.sValue = Str(Val(__TestTracker.Test.TestMarker.sValue) -1);
		//build methods
		}
		VOID ArchiveMessage()
		{
			{
				if SYS_FileExists ("{cSystem.MessagePath}\{cSystem.MessageFileName}")
				{
					do
					{
						SYS_MoveFile ("{cSystem.MessagePath}\{cSystem.MessageFileName}",
						"{cSystem.MessagePath}\archivedmessages\{cSystem.MessageFileName}");
					}
					except
					{
						Log.ExceptPrint();
						ExceptClear();
					}
				}
				else
				{
					Log.LogError("No build message to archive.");
				}
			}
		}
		VOID SkipTest(STRING sTestType)
		{
			switch sTestType
			{
				case "R":
					__TestTracker.Test.SkipTest.sValue = "TRUE";
				case "O":
					__TestTracker.Test.SkipTest.sValue = "FALSE";
				default:
				{
					Log.LogError("Test Type Invalid. Cannot set SkipTest property.");
		
		/////////////////////////////////////////////////////////////////////
		// 	STARTUP BATCH FOLDER PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
				}
			}
			cTEXTFILE __StartUpBat
			{
				tag "{DATA_DIR}\silk_startup.bat";
				STRING __sSilkTestCaseFile = "{GetProgramDir()}\{GetProgramName()}";
				STRING __sSilkExecPath = GetExecutableDir();
				STRING __GetExecParams()
				{
					STRING sValue="";
					STRING sExec;
					STRING sExecParams = "";
					LIST OF STRING lsExecs = 
					{
						"{GetExecutableDir()}runtime.exe",
						"{GetExecutableDir()}partner.exe"
					};
					for each sExec in lsExecs
					{
						if SYS_FileExists(sExec)
						{
							sExecParams = "{this.GetFile(sExec)} -r -resexport -q ";
							break;
						}
					}
					return sExecParams;
					
				}
				STRING __GetStartupPath()
				{
					//reg value for the os systems startup path
					STRING RegVal = "Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders";
					//get the value from the startup key
					STRING sStartupFolder = SYS_GetRegistryValue(HKEY_CURRENT_USER,RegVal,"Startup");
					STRING sStartUpPath = cSystem.ReplaceEnvVar(sStartupFolder);
					return sStartUpPath;
				}
			}
			cTEXTFILE __SetDateBat
			{
				tag "{DATA_DIR}\setdate.bat";
		//
		//DATE BAT FILE PRIVATE MEMBER
		// 	EMAIL TEMPLATE PRIVATE MEMBERS
			}
			cINIFILE __EmailTemplate
			{
				STRING sFileName = "{DATA_DIR}\email_template.ini";
				Section Address
				{
					Key Host {}
					Key To {}
					Key From {}
					Key ReplyTo {}
				}
				Section Message
				{
					Key Subject {}
					Key AddFileToBody {}
					Key Body {}
		//
		//	TEST CASE TRACKER PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
				}
			}
			cINIFILE __TestTracker
			{
				STRING sFileName = "{DATA_DIR}\TestCaseTracker.ini";
				BOOLEAN bConsruct = Construct();
				Section Test
				{
					Key TestList {}
					Key TestStartNum {}
					Key PassedTests {}
					Key FailedTests {}
					Key BlockedTests {}
					Key TotalTests {}
					Key TestsInitialized {}
					Key TestResult {}
					Key SkipTest {}
					Key AbortAllTests {}
					Key TestMarker {}
					Key IntraTestMarker {}
					Key RowCount {}
					Key LogIndicator {}
					Key RequiredTestsStatus {}
					Key OptionalTestsStatus {}
					Key TestSuiteName {}
					Key SchedID {}
					Key SchedHistID {}
					Key SummaryLogName {}
					Key MasterExecution {}
					Key RestartMachine {}
					Key ShutdownMachine {}
					Key LoopTestSuite {}
					Key TestSuiteLoops {}
					Key ExitSilk {}
					Key BreakTCLoop {}
					Key RunEnvironment {}
					Key StartTateRegression {}
					Key CurrentDate {}
					Key IsCurrentDate {}
					Key OverrideManifest {}
				}
				Section ProductState
				{
					Key TATEInitialized {}
					Key MessageInitialized {}
					Key SchedInitialized {}
					Key OSInitialized {}
					Key CurrentOS {}
					Key MessagePath {}
					Key MessageFileName {}
					Key ExcelFile {}
					Key BuildPath {}
					Key SubBuildPath {}
					Key LocalInstallerPath {}
					Key ResultsPath {}
					Key ManifestFileAndPath {}
					Key Version {}
					Key TestsChanged {}
					Key VMHostID {}
			
				}
			}
			VOID __SetTestCaseFile(STRING sPathAndFileName)
			{
				STRING sFileName = sPathAndFileName;
			}
			STRING __SetSubBuildPath()
			{
				STRING sDir;
				LIST OF FILEINFO lfFiles;
				INTEGER iCount;
				if cSystem.BuildPath== ""
				{
					Log.LogWarning( "Build Path has not been set.");
					sDir ="";
				}
				else
				{
					do
					{
						lfFiles = SYS_GetDirContents (BuildPath);
					}
					except
					{
						// Log.LogError(ExceptData(),TRUE )
						sDir="";
						ExceptClear();
					}
					for iCount = 1 to ListCount (lfFiles)
					{
						if MatchStr("*build*",lfFiles[iCount].sName)
						{
							sDir = lfFiles[iCount].sName;
						}
					}
				}
				return sDir;
			}
			STRING __SetMessageFileName()
			{
				STRING sFileName = "";
				LIST OF FILEINFO lfFiles;
				INTEGER iCount;
				// Put all directory contents in the FILEINFO records
				lfFiles = SYS_GetDirContents (MessagePath);
				//loop through the list of files
				BOOLEAN bFoundMessage = FALSE;
				for iCount = 1 to ListCount (lfFiles)
				{
					//Find a file
					if SYS_FileExists("{MessagePath}\{lfFiles[iCount].sName}")
					{
						sFileName = lfFiles[iCount].sName;
						bFoundMessage= TRUE;
						break;
					}
				}
				if !bFoundMessage
				{
					Log.print("No requests in the message folder.");
					this.CleanUpTestFile();
					sFileName ="";
					
				}
				return sFileName;
			}
			BOOLEAN Construct()
			{
				WINDOW __TestTracker = cINIFILE("{GetProgramDir()}\TestCaseTracker.ini");
				return TRUE;
		//
		// 	AUTOLOGON PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
			}
			mswnt const  __WINLOGON_REG_KEY = "Software\Microsoft\Windows NT\CurrentVersion\Winlogon";
			msw9x const __WINLOGON_REG_KEY = "Software\Microsoft\Windows\CurrentVersion\Winlogon";
			mswnt ANYTYPE __Constructor = __InitDomain();
			
			mswnt ANYTYPE __InitDomain()
			{
				STRING __WINLOGON_REG_KEY = "Software\Microsoft\Windows NT\CurrentVersion\Winlogon";
				CreateRegValue("DefaultDomainName","SLANT");
				return 1;
			}
			CreateRegValue(STRING sRegKey, STRING sRegValue optional)
			{
				Reg_CreateValue(HKEY_LOCAL_MACHINE,__WINLOGON_REG_KEY,sRegKey,sRegValue);
			}
			STRING GetRegValue(STRING sRegKey)
			{
				STRING __sRegValue = SYS_GetRegistryValue(HKEY_LOCAL_MACHINE,__WINLOGON_REG_KEY,sRegKey);
				return __sRegValue;
		//
		// 	RESTART PRIVATE MEMBERS - NOT FOR USE OUTSIDE THE CLASS
			}
			DialogBox __WindowsShutDown
			{
				tag "#1/[DialogBox]Shut Down Windows";
				
				PushButton OK
				{
					tag "OK";
				}
				PushButton Yes			// nt
				{
					tag "Yes";
				}
				PushButton No			// nt
				{
					tag "No";
				}
				RadioList Options		// w95, w98, nt
				{
					tag "#1";
				}
				PopupList Options2		// w2k, xp
				{
					tag "#1";
				}
				Invoke ()
				{
					Taskbar.SetActive ();
					Taskbar.Start.Click ();
					Desktop.Typekeys ("<Alt-F4>");
				}
				Restart ()
				{
					this.Invoke ();
					//msw95, msw98 this.Options.Select ("*Restart*")
					msw98 this.Options.Select ("*Restart*");
					msw2000 this.Options2.Select ("*Restart*");
					//mswxp this.Options2.Select ("*Restart*")
					if OK.bExists
					{
						this.OK.Click ();
					}
					else if Yes.bExists
					{
						Yes.Click ();
					}
					else
					{
						Log.LogError ("ERROR: Dialog ""Shut Down Windows"" has neither button OK nor button Yes.",TRUE );
					}
				}
				Shutdown ()
				{
					this.Invoke ();
					//msw95, msw98 this.Options.Select ("*Shut Down*")
					msw98 this.Options.Select ("*Shut Down*");
					// mswxp this.Options2.Select ("*Shut Down*")
					msw2000 this.Options2.Select ("*Shut Down*");
					if OK.bExists
					{
						this.OK.Click ();
					}
					else if Yes.bExists
					{
						Yes.Click ();
					}
					else
					{
						Log.LogError ("ERROR: Dialog ""Shut Down Windows"" has neither button OK nor button Yes.",TRUE );
				//mswxp, msw2000, mswnt40 Restart()
					}
				}
				msw2000 Restart()
				{
					cEXEFILE("restart.exe").Run();
				// mswxp Restart()
					// cEXEFILE("restart.exe").Run()
		// Partner .ini Object
				}
			}
			 cINIFILE __PartnerIni
			{
				STRING sFileName = "{cSystem.SilkProgramPath}\partner.ini";
				Section Runtime
				{
					Key DefaultBrowser {}
				
		
		
		// Class Private
			
				}
			}
			const lsPrivateInstanceFieldList    = {'__hLocalMachine','__hCurrentMachine'};
			const lsPrivateInstancePropertyList = {'__WINLOGON_REG_KEY','__sUserName','__sPassword','__sDomain','__Constructor'};
			
			HMACHINE __hLocalMachine {}
			HMACHINE __hCurrentMachine {}
		
		/////////////////////////////////////////////////////////////////////
		
		
	
		}
	}
	use "Registry.inc";
	dll "vsutil.dll"
	{
		BOOL PostDelayedMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT dwDealyMS);
	}
	dll "properties.dll"
	{
		DWORD GetVersion (LPCSTR lpFile, out LPCSTR lpVersion_output) alias "GetFileVersion";
	}
	dll "user32.dll"
	{
		LONG GetDC(LONG hdc);
	}
	dll "Gdi32.dll"
	{
		LONG GetDeviceCaps(LONG hdc, LONG dtype);
	}
	private VOID ExtensionLibrary_SelfTestSuite_GlobalInstances_cSystem() {}
	
	
	////////////////////////////////////////////////////////////////////////////
	// oProfiler		Allows programmer to profile code
	////////////////////////////////////////////////////////////////////////////
	window cBASE oProfiler
	{
		
		BOOLEAN fEnable=FALSE;
		BOOLEAN f4Class4Profiling=FALSE;
		
		Mark(STRING sCaller optional)
		{
			if this.fEnable
			{
				this.__foo.Resume();
				this.__Calls++;
				
				if IsNull(sCaller)
				{
					sCaller=GetCaller(iCallerDepth);
				
				}
				INTEGER iRow=ListFind(this.__lsCallers,sCaller);
				if iRow==0
				{
					ListAppend(this.__lsCallers,sCaller);
					ListAppend(this.__lfStates,FALSE);
					ListAppend(this.__liCounts,0);
					ListAppend(this.__loTimers,cTIMER());
					iRow=ListCount(this.__lsCallers);
				
				}
				if this.__lfStates[iRow] // if true, timer is running now
				{
					
					this.__lfStates[iRow]=FALSE;
					this.__loTimers[iRow].Pause();
					
				}
				else
				{
					
					this.__lfStates[iRow]=TRUE;
					this.__liCounts[iRow]++;
					this.__loTimers[iRow].Resume();
					
				}
				this.__foo.Pause();
			
			}
		}
		Mark4(STRING sCaller optional)
		{
			if oProfiler.f4Class4Profiling
			{
				if this.fEnable
				{
					this.__foo.Resume();
					this.__Calls++;
					
					if IsNull(sCaller)
					{
						sCaller=GetCaller(iCallerDepth);
					
					}
					INTEGER iRow=ListFind(this.__lsCallers,sCaller);
					if iRow==0
					{
						ListAppend(this.__lsCallers,sCaller);
						ListAppend(this.__lfStates,FALSE);
						ListAppend(this.__liCounts,0);
						ListAppend(this.__loTimers,cTIMER());
						iRow=ListCount(this.__lsCallers);
					
					}
					if this.__lfStates[iRow] // if true, timer is running now
					{
						
						this.__lfStates[iRow]=FALSE;
						this.__loTimers[iRow].Pause();
						
					}
					else
					{
						
						this.__lfStates[iRow]=TRUE;
						this.__liCounts[iRow]++;
						this.__loTimers[iRow].Resume();
						
					}
					this.__foo.Pause();
				
			
				}
			}
		}
		Report()
		{
			if this.fEnable
			{
				
				LIST lsCallers={'Caller','Profiler'};
				LIST lsCounts={'Count','{this.__Calls}'};
				LIST lsTimerValues={'Time','{this.__foo.rElapsedTime}'};
				INTEGER i1=Len(lsCallers[1]), i2=Len(lsCounts[1]), i3=Len(lsTimerValues[1]), l1,l2,l3;
				INTEGER iRow;
				
				for iRow = 1 to ListCount(this.__lsCallers)
				{
					
					ListAppend(lsCallers,this.__lsCallers[iRow]);
					ListAppend(lsCounts ,"{this.__liCounts[iRow]}");
					ListAppend(lsTimerValues,"{this.__loTimers[iRow].rElapsedTime}");
					l1=Len(lsCallers[iRow+1]);
					l2=Len(lsCounts[iRow+1]);
					l3=Len(lsTimerValues[iRow+1]);
					if l1>i1
					{
						i1=l1;
					}
					if l2>i2
					{
						i2=l2;
					}
					if l3>i3
					{
						i3=l3;
					
				
				
					}
				}
				STRING sDots=Replicate(".",255);
				STRING sSpaces=Replicate(" ",255);
				Log.ResOpenList("Profiling Report -----------------------------------------------------------------------");
				Log.Print('');
				for iRow = 1 to ListCount(lsCallers)
				{
					Log.print("{Left('{lsCallers[iRow]}'+sDots,i1+3)}: {Right(sSpaces+'{lsCounts[iRow]}',i2+3)} {Right(sSpaces+'{lsTimerValues[iRow]}',i3+3)}");
				}
				Log.Print('');
				Log.Print("End Profiling Report -------------------------------------------------------------------");
				Log.ResCloseList();
				
				
			
			}
		}
		ClearData()
		{
			this.__lsCallers={};
			this.__lfStates={};
			this.__liCounts={};
			this.__loTimers={};
			
			__foo.Destroy();
			this.__Calls=0;
			
		
		// INTERNALS
			INTEGER iCallerDepth=4;
			
			LIST __lsCallers={};
			LIST __lfStates={};
			LIST __liCounts={};
			LIST __loTimers={};
			
			cTIMER __foo {}
			INTEGER __Calls=0;
			
			BOOLEAN __ConstructorResult = this.__Constructor();
			BOOLEAN __Constructor()
			{
				
				this.__foo.rObjectLatency=0;
				return TRUE;
				
		
		
		
	
	
	
	

///////////////////////////////////////////////////////////////////////////

// Expand for Self Test Harness
			}
		}
	}
	testcase zzz_4ClassUnitTests() appstate none
	{
		ExtensionLibrary_SelfTestSuite_Object.RunAllTests();
	}
	WINDOW cBASE ExtensionLibrary_SelfTestSuite_Object
	{
		VOID RunAllTests()
		{
			SYS_SetDir(GetProgramDir());
			Log.print("Case                                               Actual Value                    Pass/Fail");
			ExtensionLibrary_SelfTestSuite_DataConversion_MakeBool();
			ExtensionLibrary_SelfTestSuite_DataConversion_MakeNumber();
			ExtensionLibrary_SelfTestSuite_DataConversion_MakeString();
			ExtensionLibrary_SelfTestSuite_DataConversion_MakeListFromString();
			ExtensionLibrary_SelfTestSuite_DataConversion_MakeListFromCSV();
			ExtensionLibrary_SelfTestSuite_DataConversion_MakeListOfWordsFromString();
			ExtensionLibrary_SelfTestSuite_DataConversion_MakeText();
			ExtensionLibrary_SelfTestSuite_DataConversion_MakeListFromRecord();
			
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetLastMember();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetLeftOf();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetRightOf();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetStringBetween();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetLastChar();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetAllButLast();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetFieldFromCSVList();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetSmallest();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetSecondSmallest();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetLargest();
			ExtensionLibrary_SelfTestSuite_DataExtraction_GetSecondLargest();
			
			ExtensionLibrary_SelfTestSuite_DataLocation_FindLastPos();
			ExtensionLibrary_SelfTestSuite_DataLocation_Contains();
			ExtensionLibrary_SelfTestSuite_DataLocation_lContains();
			ExtensionLibrary_SelfTestSuite_DataLocation_rContains();
			ExtensionLibrary_SelfTestSuite_DataLocation_sContains();
			ExtensionLibrary_SelfTestSuite_DataLocation_rpContains();
			ExtensionLibrary_SelfTestSuite_DataLocation_IsEmpty();
			
			ExtensionLibrary_SelfTestSuite_DataTyping_IsVarType();
			
			ExtensionLibrary_SelfTestSuite_DataManipulation_ListAdd();
			ExtensionLibrary_SelfTestSuite_DataManipulation_ListReverse();
			ExtensionLibrary_SelfTestSuite_DataManipulation_Assign();
			ExtensionLibrary_SelfTestSuite_DataManipulation_Iff();
			
			ExtensionLibrary_SelfTestSuite_ProgramInformation_GetCallStack();
			
			ExtensionLibrary_SelfTestSuite_WndTagManipulation_TAG_StripAll();
			ExtensionLibrary_SelfTestSuite_WndTagManipulation_TAG_StripParentage();
			
			ExtensionLibrary_SelfTestSuite_WindowQuery_GetWindowStatus();
			ExtensionLibrary_SelfTestSuite_WindowQuery_GetUltimateParent();
			ExtensionLibrary_SelfTestSuite_WindowQuery_WND_IsAllOnScreen();
			
			ExtensionLibrary_SelfTestSuite_STATIC_All();
			
			ExtensionLibrary_SelfTestSuite_Objects_cBASE();
			ExtensionLibrary_SelfTestSuite_Objects_cSTATIC();
			ExtensionLibrary_SelfTestSuite_Objects_cFILE();
			ExtensionLibrary_SelfTestSuite_Objects_cTEXTFILE();
			ExtensionLibrary_SelfTestSuite_Objects_cOPENFILE();
			ExtensionLibrary_SelfTestSuite_Objects_cEXEFILE();
			ExtensionLibrary_SelfTestSuite_Objects_cINIFILE();
			ExtensionLibrary_SelfTestSuite_Objects_cTIMER();
			ExtensionLibrary_SelfTestSuite_Objects_cDATE();
			
			ExtensionLibrary_SelfTestSuite_GlobalInstances_cSystem();
			
			Log.print("");
			Log.print("----------------------------------------------------------------------------------------------");
			Log.print("Total tests executed: {this.__TestCount}");
			Log.print("");
			Log.print("");
			
		}
		INTEGER __TestCount = 0;
		VOID RunSpecificTest(STRING sTestName)
		{
			SYS_SetDir(GetProgramDir());
			@(sTestName)();
		}
		msw STRING sTestFileName = "C:\test.txt";
		msw STRING sTestFileTarget = "C:\tested.txt";
		VOID MakeTestFile()
		{
			this.RemoveTestFile();
			LIST OF STRING data = {"line1",'line2','line3','line4'};
			ListWrite(data,this.sTestFileName);
		}
		VOID RemoveTestFile()
		{
			if SYS_FileExists(this.sTestFileName)
			{
				SYS_RemoveFile(this.sTestFileName);
			}
		}
		VOID RemoveTargetFile()
		{
			if SYS_FileExists(this.sTestFileTarget)
			{
				SYS_RemoveFile(this.sTestFileTarget);
		
			}
		}
		cSTATIC StaticGlobalTestVariable {}
		
	}
	private VOID __DoTest(STRING sLeadText,ANYTYPE returnedvalue NULL,ANYTYPE passingvalue NULL) // appstate none
	{
		ExtensionLibrary_SelfTestSuite_Object.__TestCount = ExtensionLibrary_SelfTestSuite_Object.__TestCount+1;
		STRING sResult = SubStr(sLeadText+space(200),1,50);
		sResult=sResult+" ("+SubStr("{returnedvalue})"+space(200),1,30)+" : ";
		do
		{
			if (returnedvalue==passingvalue)
			{
				sResult=sResult+"OK";
				Log.print(sResult);
			}
			else
			{
				sResult=sResult+"FAIL!!";
				Log.LogError(sResult);
				Log.print("Got      : {returnedvalue}");
				Log.print("Expected : {passingvalue}");
			}
		}
		except
		{
			sResult=sResult+"FAIL!!";
			Log.LogError(sResult);
			Log.print("Got      : {returnedvalue}");
			Log.print("Expected : {passingvalue}");
			Log.ExceptPrint();
			ExceptClear();
		
		
		}
	}
	private winclass ExtensionLibrary_SelfTestSuite_TextEdClass : MainWin
	{
		STRING sCmdLine="{GetStartupDir()}textedit.exe";
		tag "[MainWin]Text Editor*";
		VOID Invoke()
		{
			if ! bExists
			{
				MainWin::Invoke();
			}
		}
		VOID Close()
		{
			if bExists
			{
				do
				{
					SetActive();
				}
				except
				{
					// do nothing - this exception doesn't need to be trapped, the next peice of code
					// checks the result of this action.
					ExceptClear();
				}
			}
			if bExists
			{
				TypeKeys("<Esc>");
				File.Exit.Pick();
			}
			if bExists
			{
				MainWin::Close();
			}
		}
		VOID CloseAll()
		{
			while this.bExists
			{
				this.Close();
		//tag "Text Editor"
			}
		}
		Menu File
		{
			tag "File";
			MenuItem New
			{
				tag "New";
			}
			MenuItem Open
			{
				tag "Open";
			}
			MenuItem Close
			{
				tag "Close";
			}
			MenuItem Save
			{
				tag "Save";
			}
			MenuItem SaveAs
			{
				tag "Save As";
			}
			MenuItem Print
			{
				tag "Print";
			}
			MenuItem PrinterSetup
			{
				tag "Printer Setup";
			}
			MenuItem Exit
			{
				tag "Exit";
			}
		}
		Menu Edit
		{
			tag "Edit";
			MenuItem Undo
			{
				tag "Undo";
			}
			MenuItem Cut
			{
				tag "Cut";
			}
			MenuItem Copy
			{
				tag "Copy";
			}
			MenuItem Paste
			{
				tag "Paste";
			}
			MenuItem Delete
			{
				tag "Delete";
			}
		}
		Menu Search
		{
			tag "Search";
			MenuItem Find
			{
				tag "Find";
			}
			MenuItem FindNext
			{
				tag "Find Next";
			}
			MenuItem Replace
			{
				tag "Replace";
			}
			MenuItem GotoLine
			{
				tag "Goto Line";
			}
		}
		Menu Options
		{
			tag "Options";
			MenuItem Font
			{
				tag "Font";
			}
			MenuItem Tabs
			{
				tag "Tabs";
			}
			MenuItem AutomaticIndent
			{
				tag "Automatic indent";
			}
			MenuItem CreateBackups
			{
				tag "Create backups";
			}
		}
		Menu xWindow
		{
			tag "Window";
			MenuItem TileVertically
			{
				tag "Tile Vertically";
			}
			MenuItem TileHorizontally
			{
				tag "Tile Horizontally";
			}
			MenuItem Cascade
			{
				tag "Cascade";
			}
			MenuItem ArrangeIcons
			{
				tag "Arrange Icons";
			}
			MenuItem CloseAll
			{
				tag "Close All";
			}
			MenuItem Next
			{
				tag "Next";
			}
		}
		Menu Help
		{
			tag "Help";
			MenuItem About
			{
				tag "About";
		
			}
		}
		DialogBox Open
		{
			tag "Open";
			
			StaticText LookInText
			{
				tag "Look in:";
			}
			PopupList LookIn
			{
				tag "Look in:";
			}
			ToolBar LookIn2
			{
				tag "Look in:[2]";
				PushButton History
				{
					tag "History";
				}
				PushButton Desktop
				{
					tag "Desktop";
				}
				PushButton Local
				{
					tag "Local";
				}
				PushButton Network
				{
					tag "Network";
				}
			}
			ListView ListView1
			{
				tag "#1";
			}
			StaticText FileNameText
			{
				tag "File name:";
			}
			ComboBox FileName
			{
				tag "File name:";
			}
			StaticText FilesOfTypeText
			{
				tag "Files of type:";
			}
			PopupList FilesOfType1
			{
				tag "Files of type:";
			}
			PushButton Open
			{
				tag "Open";
			}
			PushButton Cancel
			{
				tag "Cancel";
			}
			ToolBar LookIn1
			{
				tag "Look in:[1]";
				PushButton PushButton1
				{
					tag "#1";
				}
				PushButton PushButton2
				{
					tag "#2";
				}
				PushButton PushButton3
				{
					tag "#3";
				}
				PushButton PushButton4
				{
					tag "#4";
				}
			}
			ScrollBar FilesOfType2
			{
				tag "Files of type:";
		
			}
		}
	}
	private WINDOW ExtensionLibrary_SelfTestSuite_TextEdClass ExtensionLibrary_SelfTestSuite_TextEd {}
	private WINDOW ExtensionLibrary_SelfTestSuite_TextEdClass ExtensionLibrary_SelfTestSuite_TextEd1
	{
		tag "Text Editor*[1]";
	}
	private WINDOW ExtensionLibrary_SelfTestSuite_TextEdClass ExtensionLibrary_SelfTestSuite_TextEd2
	{
		tag "Text Editor*[2]";
	
	
	}
	VOID ExtensionLibrary_SelfTestSuite_main()
	{
		INTEGER a = 1;
		ExtensionLibrary_SelfTestSuite_Object.RunAllTests();
		
		//STRING sObject = 'cFILE'
		//ExtensionLibrary_SelfTestSuite_Object.RunSpecificTest('ExtensionLibrary_SelfTestSuite_Objects_{sObject}')
		





	}
}
