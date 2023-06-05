[ ] //**************************************************************************
[ ] 
[ ] // 4CLASS3.INC
[ ] 
[ ] // Peak Object Library for extending 4Test
[ ] 
[ ] // REQUIRES QA PARTNER v2.0+
[ ] 
[ ] // Original Author: Mark Hemsley
[ ] // Initial Date:  5/12/94
[ ] // Last Edit:   10/5/98 sjf
[ ] 
[ ] // Copyright (c) 1993, 1994, 1995, 1998 Peak Enterprises, Inc.
[ ] // All Rights Reserved
[ ] // This code is distributed as freeware.
[ ] 
[ ] // NOTES:
[ ] 
[ ] // This code requires 4CODE3.INC
[ ] 
[ ] // Stylistic Note: As 4Test does not support private members in a class,
[ ] // items with two underscores at the beginning of their name are intended to
[ ] // be private, and are subject to change.
[ ] 
[ ] // Items with three underscores are properties that indicate version
[ ] // information. Their names will not be changed, but thier values may.
[ ] 
[ ] // Items listed as Published Private Memebers are intended only for
[ ] // use within a sub-class, and should not be called from outside.
[ ] 
[ ] // WARNING:
[ ] 
[ ] // This version of the class library has had several class' and methods
[ ] // names changed to be more consistant.
[ ] 
[ ] // FINAL NOTE TO DEVELOPERS:
[ ] // 
[ ] // If you're changing this file, it should compile OK with only the addition
[ ] // of 4CODEx.INC No other files should be required to compile this. If there
[ ] // are, your changes aren't generic enough. This is intended to be a general 
[ ] // purpose set of extentions to 4Test.
[ ] 
[ ] //**************************************************************************
[ ] 
[ ] use "4code3.inc"
[ ] 
[ ] type object is WINDOW
[ ] type OBJECT is WINDOW
[ ] type OPTION is BOOLEAN
[ ] 
[ ] type STRINGorWINDOW is STRING, WINDOW
[ ] type LISTorWINDOW is LIST OF ANYTYPE, WINDOW
[ ] type LISTorSTRINGorWINDOW is LIST, STRING, WINDOW
[ ] type LISTorSTRING is LIST, STRING
[ ] 
[ ] const EMPTYSTRING = ""
[ ] const FM_CLOSED = 0 // Rounds out file mode flags
[ ] const FM_INIOPEN = 100
[ ] const YES = TRUE
[ ] const ON = TRUE
[ ] const NO = FALSE
[ ] const OFF = FALSE
[ ] 
[ ] //==========================================================================
[ ] // cBASE   Virtual base class for POL (Peak Object Library)
[ ] 
[ ] // Purpose:  Provides object ID services to other classes
[ ] 
[ ] // inherits:  none
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] // functions:  Class()   returns dataclass of this
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:
[ ] 
[ ] // properties:  __Class   dataclass of this
[ ] //     __sName   string name of this
[ ] //     __wParent  window of parent to this NOTE: If there is
[ ] //         no parent for the object, an exception will
[ ] //         be raised.
[ ] //     __lwChildren list of window children of this
[ ] //     __sParent  string of name of parent window object
[ ] //         OR null string if none. (does not raise
[ ] //         an exception if no parent exists)
[ ] //     __sPassedValue string of value passed to object at
[ ] //         instantiation time
[ ] 
[ ] //     ___sPVersion Peak Object Library Version
[ ] //     ___sPRevision Peak Object Library Build #
[ ] 
[ ] // functions:  __IsDefined(s) TRUE if object named exists within this
[ ] 
[ ] // NOTES:
[ ] 
[ ] //==========================================================================
[+] winclass cBASE
	[+] property    Class
		[+] DATACLASS Get ()
			[ ] return this.__Class
	[+] property    ___sPVersion
		[+] STRING Get ()
			[ ] return "3.00.01"
	[+] property    ___sPRevision
		[+] STRING Get ()
			[ ] return ".19981012"
	[+] property    __Class
		[+] DATACLASS Get ()
			[ ] return (ClassOf (this))
	[+] property    __sName
		[+] STRING Get ()
			[ ] return (WindowName (this))
	[+] property    __wParent
		[+] WINDOW Get ()
			[ ] return (WindowParent (this))
	[+] property    __lwChildren
		[+] LIST OF WINDOW Get ()
			[ ] return (WindowChildren (this))
			[ ] 
	[+] hidecalls BOOLEAN  __IsDefined (STRING sName)
		[ ] return (WindowIsDefined (this, sName))
		[ ] 
	[+] property    __sParent
		[+] STRINGorWINDOW Get ()
			[ ] STRINGorWINDOW wReturnValue
			[ ] 
			[+] do
				[ ] wReturnValue = WindowParent (this)
				[ ] wReturnValue = wReturnValue.sName
			[+] except
				[ ] wReturnValue = EMPTYSTRING
				[ ] 
			[ ] return wReturnValue
			[ ] 
	[+] property    __sParentClass
		[+] STRING Get ()
			[ ] STRING sResult = "UNKNOWN CLASS"
			[ ] STRING sMyParent = this.__sParent
			[ ] 
			[+] if sMyParent != ""
				[ ] sResult = this.__wParent.Class
			[ ] return sResult
			[ ] 
	[+] property    __sPassedValue
		[+] STRING Get ()
			[ ] STRING sTemp = WindowTag (this)
			[ ] sTemp[1] = EMPTYSTRING
			[ ] return sTemp
[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cSTATIC   Static storage
[ ] 
[ ] // Purpose:   Manages persistant data (not file based data)
[ ] //     That is, data required to be shared between instances
[ ] //     of a class that may not coexist temporally.
[ ] 
[ ] // inherits:  cBASE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:
[ ] 
[ ] //==========================================================================
[+] winclass cSTATIC : cBASE
	[+] property Value
		[+] ANYTYPE Get ()
			[ ] return STATIC_Get (cBASE::__sParentClass, cBASE::__sPassedValue)
		[+] Set (ANYTYPE aValue)
			[ ] STATIC_Set (cBASE::__sParentClass, cBASE::__sPassedValue, aValue)
			[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cDIR    Represents a directory
[ ] 
[ ] // Purpose:   Represents a directory
[ ] 
[ ] // inherits:  cBASE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] //     Read()   Read current contents of directory
[ ] //     Create()  Makes the directory
[ ] //     Destroy()  Removes the directory
[ ] //     Exists()  Returns boolean of if directory exists
[ ] //     AmWorkingDir() Returns true if this is the current 
[ ] //         working directory
[ ] //     FileExists(x) returns true if file x exists
[ ] //         x can be a string or an object
[ ] //     FileDelete(x) deletes file x from directory
[ ] //         x can be string or object /*by steph*/
[ ] //     PollForNewFiles() returns list of file objects
[ ] //          for files that have been created
[ ] //          since the last time dir was read
[ ] //          updates all internal variables to 
[ ] //          reflect new directory contents
[ ] //
[ ] //     GetAllContents From the rootDir(if passed) or from __sDirPath
[ ] //         abstract all the subdirectories(mult-level)
[ ] //         into the parameter lsAllDirs,
[ ] //         abstract all the files(mult-level) into
[ ] //         the parameter lsAllFiles. /*by Diana*/
[ ] //
[ ] //     DeleteAllContents Delete all the files subdirectories and 
[ ] //         subdirectories files. /*by Diana*/
[ ] //
[ ] //     CopyAllContents Copy all the files, subdirectories and 
[ ] //         subdirectoies files from cDIR fromDir. /*by Diana*/
[ ] //
[ ] //     IsTypeFileExists Return true if type of extension - "sFileExt"
[ ] //         files exists, Meanwhile will abstact the file 
[ ] //         names(without path) into list lsFileName. /*by Diana*/
[ ] //
[ ] //     GetAllFiles  Return all the files and subdirctories files
[ ] //         with the extension "sFileExt"./*by Diana*/
[ ] //  
[ ] // PROPERTIES:
[ ] //     sDirPath  Pathspec for specified directory (RW)
[ ] //     bExists   same as Exists() (RO)
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:
[ ] //   There is currently no setdir function, as this function needs to
[ ] //   be very different for Windows systems vs other systems, as
[ ] //   Windows systems have a drive specifier that must be selected
[ ] //   selected first and that might or might not be specified in the
[ ] //   directory path specifier.
[ ] 
[ ] //   Operations that read, create and destroy all check to see if
[ ] //   directory exists before performing their operation. They will
[ ] //   NOT raise an exception if attempted inappropriatly, it is
[ ] //   assumed that the programmer will have either verified existance,
[ ] //   or doesn't really care and, for instance, just wants the 
[ ] //   directory to exist or not to exist.
[ ] 
[ ] //==========================================================================
[+] winclass cDIR : cBASE
	[ ] // represents a directory
	[ ] 
	[ ] // ACTIONS
	[+] VOID Read()
		[-] if this.bExists
			[ ] this.__lfData = SYS_GetDirContents(this.sDirPath)
			[ ] this.__MakeFileNameList()
			[ ] this.__MakeObjects()
	[+] VOID Create()
		[+] if ! this.bExists
			[ ] SYS_MakeDir(this.sDirPath)
	[+] VOID Destroy()
		[+] if this.bExists
			[ ] SYS_RemoveDir(this.sDirPath)
	[+] VOID DeleteAllFiles()
		[ ] this.Read()
		[ ] ANYTYPE item
		[+] for each item in this.__lfoData
			[ ] item.Erase()
	[ ] 
	[ ] // STATE READINGS
	[+] BOOLEAN Exists()
		[ ] return SYS_DirExists(this.sDirPath)
	[+] BOOLEAN AmWorkingDir()  // works correctly only for MSWindows
		[ ] STRING sCurrent = lower(SYS_GetDir())
		[ ] STRING sMine = lower(this.sDirPath)
		[ ] __MakeNormal(sCurrent)
		[ ] return sCurrent == sMine
	[+] boolean HasIniFile(out object cIniFile)
		[ ] list of FILEINFO lsInfo = SYS_GetDirContents(this.sDirPath)
		[ ] FILEINFO aInfo
		[ ] list of string lsIniName={}
		[+] for each aInfo in lsInfo
			[+] if sContains(aInfo.sName, ".ini")
				[ ] ListAppend(lsIniName, aInfo.sName)
		[+] if ListCount(lsIniName)!=1
			[ ] LogError("Not only one ini file in the {this.sDirPath} directory")
			[ ] cIniFile = NULL
			[ ] return FALSE
		[+] else
			[ ] cIniFile = cINIFILE(this.sDirPath+lsIniName[1])
			[ ] return TRUE
		[ ] 
	[+] boolean IsName(string sDirName) //check if the sDirPath contains sDirName
		[ ] return sContains(this.sDirPath, sDirName)
	[ ] 
	[ ] // ACTIONS ON FILES
	[+] BOOLEAN FileExists(STRINGorWINDOW File)
		[ ] // stubbed
		[ ] STRING sSearchKey
		[+] if IsString(File)
			[ ] sSearchKey = File
		[-] else
			[ ] sSearchKey = File.GetFileName()
		[ ] //Read()
		[ ] INTEGER result = ListFind(this.__lsFileList, lower(sSearchKey))
		[ ] return (result > 0)
		[ ] 
	[+] VOID  FileDelete(STRINGorWINDOW File)
		[ ] OBJECT MyFile
		[+] if IsString(File)
			[ ] MyFile = cFILE(File)
		[+] else 
			[ ] MyFile = File
		[+] if ListFind(this.__lfoData, MyFile) != 0
			[ ] MyFile.DeleteMe()
	[ ] 
	[ ] // ACTIONS ON LIST
	[+] LIST OF OBJECT PollForNewFiles()
		[ ] // returns new files that have 
		[ ] // appeared since last polled
		[ ] 
		[ ] LIST OF STRING lsOldList = this.__lsFileList
		[ ] this.Read()
		[ ] ANYTYPE item
		[ ] LIST OF OBJECT results = {}
		[ ] INTEGER ListPos
		[ ] 
		[+] for each item in this.__lsFileList
			[ ] ListPos = ListFind(lsOldList, item)
			[+] if ListPos == 0
				[ ] // NEW ITEM!
				[ ] OBJECT NewFile = cTEXTFILE(this.sDirPath+item)
				[ ] ListAppend(results, NewFile)
		[ ]  
		[ ] return results
	[+] void    GetAllContents(out list of object lsAllDirs, out list of object lsAllFiles, string rootDir optional) 
		[ ] lsAllDirs = {}
		[ ] lsAllFiles = {}
		[ ] list of string lsGetDirs
		[+] if rootDir == NULL
			[ ] lsGetDirs = { this.sDirPath }
		[-] else
			[ ] lsGetDirs = { rootDir }
		[-] while ( lsGetDirs!={} )
			[ ] list of FILEINFO lsContents = {} 
			[ ] lsContents = SYS_GetDirContents( lsGetDirs[1] )
			[ ] string sTheDir = lsGetDirs[1]
			[ ] ListDelete(lsGetDirs,1)
			[ ] FILEINFO aItem
			[-] for each aItem in lsContents
				[-] if (aItem.bIsDir)
					[ ] string sDir = this.__MakeNormal(sTheDir) + sep + aItem.sName + sep
					[ ] object aDir = cDIR(sDir)
					[ ] ListAppend( lsGetDirs, sDir )
					[ ] ListAppend( lsAllDirs, aDir )
				[-] else //is a file
					[ ] object aFile = cFILE(__MakeNormal(sTheDir) + sep + aItem.sName)
					[ ] ListAppend( lsAllFiles, aFile )
		[ ] 
	[+] boolean   IsTypeFileExists(string sFileExt, out list of string lsFileName optional) //check the type of file exists by file extention. If yes, will append to lsFileName
		[ ] list of FILEINFO lsFileInfo = SYS_GetDirContents(this.sDirPath)
		[ ] FILEINFO aFileInfo
		[ ] boolean bReturn = FALSE
		[+] for each aFileInfo in lsFileInfo
			[+] if RightOf(aFileInfo.sName,".") == RightOf(sFileExt, ".")
				[ ] ListAppend(lsFileName, aFileInfo.sName)
				[ ] bReturn = TRUE
		[ ] return bReturn
	[+] list of object  GetAllFiles(string sFileExt optional)
		[ ] list of object lsAllFiles
		[ ] list of object lsAllDirs
		[ ] GetAllContents(lsAllDirs, lsAllFiles)
		[+] if sFileExt == NULL //Get all files
			[ ] return lsAllFiles
		[+] else
			[ ] list of object lsReturnFiles={}
			[ ] object aFile
			[+] for each aFile in lsAllFiles
				[+] if sContains(aFile.sFileName, sFileExt)
					[ ] ListAppend(lsReturnFiles, aFile)
			[ ] return lsReturnFiles
	[ ] 
	[ ] // WELCOME TO THE DANGER ZONE
	[+] void  DeleteAllContents() //delete all the files, subdirectories and subdirectory files, by Diana
		[ ] list of object lsAllDirs 
		[ ] list of object lsAllFiles 
		[ ] GetAllContents(lsAllDirs, lsAllFiles)
		[ ] object aObj
		[+] for each aObj in lsAllFiles
			[ ] aObj.Destroy()
		[ ] //has to delete directories in lsAllDirs in reverse order
		[ ] int iCount = ListCount(lsAllDirs)
		[ ] int i
		[+] for (i=iCount; i>0; i--)
			[ ] lsAllDirs[i].Destroy()
	[+] void  CopyAllContents(object fromDir) //copy all the files, subdirectories and subdirectory files, by Diana
		[ ] list of object lsFromDirs
		[ ] list of object lsFromFiles
		[ ] fromDir.GetAllContents(lsFromDirs, lsFromFiles)
		[ ] //this.GetAllContents(lsFromDirs, lsFromFiles, fromDir.sDirPath)
		[ ] string sFrom = Lower(fromDir.sDirPath)
		[ ] string sTo = Lower(this.sDirPath)
		[ ] object aObj
		[-] for each aObj in lsFromDirs
			[ ] string sObjDirPath = Lower(aObj.sDirPath)
			[ ] string sNewDirPath = StrTran ( sObjDirPath, sFrom, sTo ) //no checking for duplicated sFrom
			[ ] object newDir = cDIR(sNewDirPath)
			[ ] newDir.Create()
		[-] for each aObj in lsFromFiles
			[ ] string sObjFilePath = Lower(aObj.sFileName)
			[ ] string sNewFilePath = StrTran ( sObjFilePath, sFrom, sTo)
			[-] if SYS_FileExists(sNewFilePath)
				[ ] LogError("CopyAllContents: {sNewFilePath} already exists, original being deleted")
				[ ] SYS_RemoveFile(sNewFilePath)
			[-] if SYS_FileExists(sNewFilePath)
				[ ] LogError("CopyAllContents: {sNewFilePath} STILL exists, COPY ABORTED")
			[-] else
				[ ] SYS_CopyFile(sObjFilePath, sNewFilePath)
	[ ] 
	[ ] 
	[ ] // PROPERTIES
	[+] property sDirPath    // Read/Write
		[-] STRING Get()
			[ ] this.__MakeNormal(this.__sDirPath)
			[ ] return this.__sDirPath+cSystem.sDirSeperator
		[+] VOID Set(STRING sIncoming)
			[ ] this.__sDirPath = sIncoming
			[ ] this.__MakeNormal(this.__sDirPath)
	[+] property bExists   // Read only
		[+] BOOLEAN Get()
			[ ] return this.Exists()
	[+] property lsFileNames  // Read only
		[+] LIST OF STRING Get()
			[ ] return this.__lsFileList
	[+] property loFiles   // Read only
		[-] ANYTYPE Get()
			[ ] return this.__lfoData
	[+] property sep
		[+] STRING Get()
			[ ] return cSystem.sDirSeperator
	[ ] 
	[ ] // INTERNAL USE ONLY
	[ ] STRING __sDirPath = cBASE::__sPassedValue
	[+] STRING  __MakeNormal(inout STRING sPath )
		[ ] STRING sLastChar = LastChar(sPath)
		[-] if sLastChar == cSystem.sDirSeperator
			[ ] sPath = StripLast(sPath)
		[ ] return sPath
	[+] VOID  __MakeFileNameList()
		[ ] ANYTYPE item
		[ ] this.__lsFileList = {}
		[-] for each item in this.__lfData
			[-] if ! item.bIsDir
				[ ] //ListAppend(this.__lsFileList, lower(item.sName))
				[ ] ListAppend(this.__lsFileList, (item.sName))  //CHANGED 3/17sjf
	[+] VOID  __MakeObjects()
		[ ] STRING item
		[ ] STRING sTemp
		[ ] List of OBJECT FileList = {}
		[+] for each item in this.__lsFileList
			[ ] sTemp = this.sDirPath + cSystem.sDirSeperator + item
			[ ] OBJECT NewFile = cFILE(sTemp)
			[ ] ListAppend(FileList, NewFile)
		[ ] this.__lfoData = FileList
	[ ] 
	[ ] LIST OF FILEINFO  __lfData = {}
	[ ] LIST of STRING   __lsLastEntry = {}
	[ ] LIST OF STRING  __lsFileList = {}
	[ ] LIST OF OBJECT  __lfoData = {}
	[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cFILE   Virtual base class for file objects
[ ] 
[ ] // Purpose:   Provides file services to caller
[ ] 
[ ] // inherits:  cBASE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // properties:  bExists   boolean indicating whether the file exists
[ ] //         in mass storage.
[ ] //     sFileName  string of file name (can be passed at 
[ ] //         instantiation)
[ ] 
[ ] // functions:  DeleteMe()  delete the file from storage (if it exists)
[ ] //     CopyTo(s)  Copy file to specified location
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:
[ ] 
[ ] //==========================================================================
[+] winclass cFILE : cBASE
	[ ] STRING   __sFileName = cBASE::__sPassedValue
	[ ] 
	[+] VOID  Delete()
		[ ] this.__FileDelete()
	[+] VOID  Destroy()
		[ ] this.__FileDelete()
	[+] VOID  Erase()
		[ ] this.__FileDelete()
	[+] VOID   DeleteMe()
		[ ] this.__FileDelete()
	[+] BOOLEAN  Exists ()
		[ ] return this.__FileExists()
	[+] property  bExists
		[+] BOOLEAN Get ()
			[ ] return this.__FileExists ()
	[ ] 
	[+] STRING  GetFileName()
		[ ] return __FileExtractName()
	[ ] 
	[+] void   CopyTo (STRINGorWINDOW Target)
		[+] if IsString(Target)
			[ ] Target = cFILE(Target)
		[+] if Target.Exists()
			[ ] Target.Delete()
		[ ] SYS_CopyFile (this.__sFixedFileName, Target.__sFixedFileName)
	[+] INTEGER  SizeOf ()
		[ ] return this.__GetFileInfoRecord().iSize
	[+] // OBJECT MoveTo (object cTargetDir)
		[+] // if bExists
			[ ] // string sName = RightOf(this.__sFixedFileName, cSystem.sDirSeperator)
			[ ] // SYS_MoveFile(this.__sFixedFileName, cTargetDir.sDirPath+sName )
			[ ] // return cFILE(cTargetDir.sDirPath+sName)
	[ ] 
	[+] FILEINFO __GetFileInfoRecord()
		[ ] FILEINFO result
		[+] if this.bExists
			[+] if ! sContains(this.sFileName, cSystem.sDirSeperator)
				[ ] this.sFileName = "."+cSystem.sDirSeperator+this.sFileName
			[ ] STRING sDir = LeftOf(this.sFileName, cSystem.sDirSeperator)
			[ ] STRING sJustTheFileName = RightOf(this.sFileName, cSystem.sDirSeperator)
			[ ] LIST of FILEINFO lfData
			[ ] ANYTYPE item
			[+] for each item in lfData
				[+] if (item.sName == sJustTheFileName) && (! item.bIsDir)
					[ ] result = item
					[ ] break
			[ ] return result
	[+] BOOLEAN  __FileExists ()
		[ ] return SYS_FileExists (this.sFileName)
	[+] STRING  __FileExtractName()
		[ ] STRING sResult = this.sFileName
		[-] if sContains(this.sFileName, cSystem.sDirSeperator)
			[ ] sResult = RightOf(this.sFileName, cSystem.sDirSeperator)
		[ ] return sResult
	[-] VOID   __FileDelete()
		[-] do       // first try
			[-] if this.__FileExists ()
				[ ] this.___FileDeleteQAP()
		[+] except
			[ ] // do nothing...
		[-] do       // wait for a minute, then try again
			[-] if this.__FileExists ()
				[ ] sleep(60)
				[-] if this.__FileExists ()
					[ ] this.___FileDeleteQAP()
		[+] except
			[ ] // do nothing...
		[-] do       // wait for another minute, then try again
			[-] if this.__FileExists ()
				[ ] sleep(60)
				[-] if this.__FileExists ()
					[ ] this.___FileDeleteQAP()
		[+] except
			[ ] // do nothing...
		[-] do       // wait for yet another minute (3 so far), then try again
			[-] if this.__FileExists ()
				[ ] sleep(60)
				[-] if this.__FileExists ()
					[ ] this.___FileDeleteQAP()
		[+] except
			[ ] // do nothing...
		[-] do       // ok, lets try changing the attributes (4 minutes)
			[-] if this.__FileExists ()
				[ ] sleep(60)
				[-] if this.__FileExists ()
					[ ] this.___FileClearAttribsDOS()
					[ ] this.___FileDeleteQAP()
		[+] except
			[ ] // do nothing...
		[-] do       // maybe a DOS delete? (5 minutes)
			[-] if this.__FileExists ()
				[ ] sleep(60)
				[-] if this.__FileExists ()
					[ ] this.___FileDeleteDOS()
		[+] except
			[ ] // do nothing...
		[-] do       // maybe we can rename it? (6 minutes)
			[-] if this.__FileExists ()
				[ ] sleep(60)
				[-] if this.__FileExists ()
					[ ] this.___FileRenameDOS(this.sFileName+".bak")
		[+] except
			[ ] // do nothing...
		[-] do       // last try. We'll try everything. (7 minutes)
			[-] if this.__FileExists ()
				[ ] sleep(60)
				[-] if this.__FileExists ()
					[ ] this.___FileClearAttribsDOS()
					[ ] this.___FileRenameDOS(this.sFileName+".bak")
					[ ] this.___FileDeleteDOS()
					[ ] this.___FileDeleteQAP()
		[+] except
			[ ] // do nothing...
		[ ]        // I give up
		[-] if this.__FileExists ()
			[ ] print("Oh, wise master, the world has come to an end.")
			[ ] print("The file {sFileName} has been asked to")
			[ ] print("delete itself, and despite several tries, has been")
			[ ] print("unable to do so.")
			[ ] print("")
			[ ] print("I submit myself to your mercy.")
			[ ] print("(Perhaps it's write protected?)")
			[ ] raise 1, "File delete failure in {this}"
	[ ] 
	[+] VOID   ___FileDeleteQAP()
		[ ] SYS_RemoveFile (this.sFileName)
	[+] VOID   ___FileDeleteDOS()
		[-] if cSystem.IsWindows()
			[ ] print('APP_Start({cSystem.sShell} /c DEL {this.__sFixedFileName}")')
			[ ] APP_Start(cSystem.sShell+" /c DEL {this.__sFixedFileName}")
			[ ] sleep(10)
	[+] VOID   ___FileClearAttribsDOS()
		[-] if cSystem.IsWindows()
			[ ] print('{cSystem.sShell} /c ATTRIB -S -H -R {this.__sFixedFileName}")')
			[ ] APP_Start(cSystem.sShell+" /c ATTRIB -S -H -R {this.__sFixedFileName}")
			[ ] sleep(30)
	[+] VOID  ___FileRenameDOS(STRING NewName)
		[-] if cSystem.IsWindows()
			[ ] print('APP_Start({cSystem.sShell} /c REN {this.__sFixedFileName} {__sFixedFileName}.bak")')
			[ ] APP_Start(cSystem.sShell+" /c REN {this.__sFixedFileName} {__sFixedFileName}.bak")
			[ ] sleep(10)
	[ ] 
	[+] property sRawFileName
		[+] STRING Get()
			[ ] return this.__sFixedFileName
		[+] VOID Set(STRING sName)
			[ ] this.__sFixedFileName = sName
	[ ] 
	[-] property sFileName
		[-] STRING Get()
			[ ] STRING sName = this.__sFixedFileName
			[-] if sContains("{GetGuiType()}","Microsoft Windows")
				[ ] sName = lower(sName)
			[ ] return sName
		[+] VOID Set(STRING sName)
			[ ] this.__sFixedFileName = sName
	[ ] 
	[+] property __sFixedFileName
		[+] STRING Get()
			[ ] STRING sRetValue = this.__sFileName
			[ ] 
			[+] if sContains("{GetGuiType()}","Microsoft Windows")
				[ ] STRING sBadCharList = '/*?"<>|'
				[ ] INTEGER i
				[+] for i = 1 to len(sRetValue)
					[+] if sContains(sBadCharList, sRetValue[i])
						[ ] sRetValue[i]="_"
			[ ] return sRetValue
		[+] Set(STRING sName)
			[ ] this.__sFileName = sName
	[ ] 
[ ] // FILEINFO = {sName, bIsDir, iSize}
[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cTEXTFILE  Text File (Represented as a list of string) Object
[ ] 
[ ] // Purpose:   Provides text file services to caller
[ ] 
[ ] // inherits:  cFILE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // properties:  sFileName  string of name of file (inherited)
[ ] //     lsData   list of string, contents of the file
[ ] //     bExists   boolean indicating whether the file exists
[ ] //         in mass storage. (inherited)
[ ] //     iLength   integer of number of lines in text file
[ ] 
[ ] // functions:  Read()   if bExists, zap lsData and reread it from file
[ ] //     Write()   write file to storage. If file already exists
[ ] //         in storage, original is overwritten.
[ ] //     AddLine(s)  adds new line of s to end of lsData
[ ] //     InsertLine(s,i) Inserts new line of s into lsData at line i
[ ] //     Replace(l/w/s) zaps lsData and replaces it with either
[ ] //         the passed list, or if the passed item was
[ ] //         another loaded file object, it's lsData.
[ ] //     Append(l/w)  adds either the passed list of string to the
[ ] //         end of lsData, or if the passed item was
[ ] //         another loaded file object, it's lsData.
[ ] //     ZapData()  sets lsData = {}
[ ] //     AddTo(l/w/s) Read(), Append(), Write() 
[ ] //         Adds to version on disk. WARNING: Read is
[ ] //         performed before append. If there are 
[ ] //         unsaved changes in memory, they will be
[ ] //         lost.
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:   At instantiation time, if the specified file exists, the
[ ] //     instance will read it into lsData automatically, without
[ ] //     the need for an explicit call to Read().
[ ] 
[ ] //     object MyFile = cTEXTFILE("C:\TEST.TXT");
[ ] //     string Line1 = MyFile.lsData[1];
[ ] 
[ ] //     As 4Test does not allow us to create a destructor, you must
[ ] //     write the data out to storage explicitly before the object
[ ] //     goes out of scope, or the data will be lost.
[ ] 
[ ] //==========================================================================
[+] winclass cTEXTFILE : cFILE
	[ ] STRING   __sFileName = cBASE::__sPassedValue
	[+] VOID  Delete()
		[ ] cFILE::__FileDelete()
	[+] VOID  Destroy()
		[ ] cFILE::__FileDelete()
	[+] VOID  Erase()
		[ ] cFILE::__FileDelete()
	[+] VOID   DeleteMe()
		[ ] cFILE::__FileDelete()
	[+] BOOLEAN  Exists ()
		[ ] return cFILE::__FileExists()
	[+] property  bExists
		[+] BOOLEAN Get ()
			[ ] return cFILE::__FileExists ()
	[ ] 
	[+] property  iLength
		[-] INTEGER Get ()
			[ ] return ListCount (this.__lsData)
	[+] property lsData
		[+] LIST OF STRING Get()
			[ ] return this.__lsData
		[+] VOID Set(LIST OF STRING lsIncoming)
			[ ] this.__lsData = lsIncoming
			[ ] this.__bDirty = TRUE
	[+] property bRead
		[+] BOOLEAN Get()
			[ ] return this.__bRead
	[+] property bWritten
		[+] BOOLEAN Get()
			[ ] return this.__bWritten
	[ ] 
	[+] void   Append (LISTorSTRINGorWINDOW lswNewData)
		[+] if IsWindow (lswNewData)
			[ ] this.__lsData = this.__lsData + lswNewData.lsData
		[+] if IsString (lswNewData)
			[ ] listappend(this.__lsData, lswNewData)
		[+] if IsList (lswNewData)
			[ ] this.__lsData = this.__lsData + lswNewData
		[ ] 
	[+] VOID  AddTo(LISTorSTRINGorWINDOW lswNewData)
		[ ] this.Read()
		[ ] this.Append(lswNewData)
		[ ] this.Write()
	[+] VOID  DeleteLine(INTEGER iIndex)
		[ ] ListDelete(this.__lsData, iIndex)
	[+] INTEGER  GetLength()
		[ ] return ListCount(this.__lsData)
	[+] void   InsertLine (LISTorSTRING sItem, INTEGER iIndex)
		[+] if IsString(sItem)
			[+] if this.__lsData == {}
				[ ] this.__lsData = {sItem}
			[+] else
				[+] if iIndex > iLength
					[ ] Append(sItem)
				[+] else
					[+] if iIndex > iLength
						[ ] ListAppend(this.__lsData, sItem)
					[+] else
						[ ] ListInsert (this.__lsData, iIndex, sItem)
		[-] else
			[-] if iLength == 0
				[ ] this.__lsData = sItem
			[+] else
				[ ] ListMerge(this.__lsData, sItem, iIndex)
	[+] void  InsertTop (LISTorSTRING slItem)
		[+] if this.__lsData == NULL
			[ ] this.__lsData = {}
			[ ] Append(slItem)
		[+] else
			[ ] this.InsertLine(slItem, 1)
	[+] INTEGER  Find(STRING sToFind)
		[ ] return ListFind(this.__lsData, sToFind)
	[+] void   Read ()
		[-] if this.bExists
			[ ] this.__ZapData ()
			[ ] ListRead (this.__lsData, this.sFileName)
			[ ] this.__bRead = TRUE
			[ ] 
	[+] void   Replace (LISTorWINDOW lwNewData)
		[ ] this.__ZapData ()
		[ ] Append (lwNewData)
		[ ] 
	[-] void   Write ()
		[-] if this.__lsData == NULL
			[ ] this.__lsData = {}
		[-] if this.bExists
			[ ] this.DeleteMe ()
			[ ] sleep(1)
		[ ] ListWrite (this.__lsData, this.sFileName)
		[ ] this.__bWritten = TRUE
		[ ] this.__bDirty = FALSE
		[ ] 
	[+] void  ZapData ()
		[ ] this.__ZapData ()
		[ ] 
	[+] void  Zap()
		[ ] this.ZapData()
		[ ] this.DeleteMe()
	[ ] 
	[+] void  Create()
		[ ] this.write()
	[ ] 
	[ ] // These two items work together.
	[+] void  SetLine(STRING sData, INTEGER iNewIndex optional)
		[+] if iNewIndex == NULL
			[ ] iNewIndex = 0
		[+] if iIndex == NULL 
			[ ] iIndex = 0
		[+] if iIndex == 0
			[ ] iIndex = iNewIndex
		[+] if iNewIndex != 0
			[ ] iIndex = iNewIndex
		[ ] this.__lsData[iIndex] = sData
	[ ] INTEGER  iIndex
	[ ] // The above, SetLine(...) and iIndex are designed to overcome the
	[ ] // inability to set a specific member of the __lsData through the
	[ ] // lsData property. If iNewIndex is specified, it replaces iIndex.
	[ ] // If neither iIndex or iNewIndex are specified, an exception will
	[ ] // be raised.
	[ ] 
	[ ] // =============================================================
	[ ] // = PRIVATE MEMBERS! DO NOT USE! PRIVATE MEMBERS! DO NOT USE! =
	[ ] // =============================================================
	[ ] LIST OF STRING  __lsData = {}
	[ ] BOOLEAN   __bRead = FALSE
	[ ] BOOLEAN   __bWritten = FALSE
	[ ] BOOLEAN   __bDirty = FALSE
	[ ] 
	[+] void    __ZapData ()
		[ ] this.__lsData = {}
		[ ] 
	[+] boolean   __Init()
		[ ] boolean fIsSet = NO
		[+] do
			[+] if this.sFileName != NULL
				[ ] fIsSet = YES
		[+] except
			[ ] // bugger off.
		[+] if ! fIsSet
			[ ] this.sFileName = cBASE::__sPassedValue
		[+] if this.bExists
			[ ] this.Read()
		[ ] return true
	[ ] BOOLEAN   __InitFlag = this.__Init()
	[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cOPENFILE  Openable File Object
[ ] 
[ ] // Purpose:   Provides centralized file services to caller
[ ] 
[ ] // inherits:  cFILE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // properties:  bExists   boolean indicating whether the file exists
[ ] //         in mass storage. (Inherited)
[ ] //     sFileName  string of file name (can be passed at instantiation)
[ ] //         (Inherited)
[ ] 
[ ] // functions:  DeleteMe()  delete the file from storage (if it exists) (Inherited)
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:
[ ] 
[ ] //==========================================================================
[+] winclass cOPENFILE : cFILE
	[ ] OPTION CloseAfterEachWrite = YES // NO is faster, YES is safer
	[ ] 
	[+] VOID  Delete()
		[ ] cFILE::__FileDelete()
	[+] VOID  Destroy()
		[ ] cFILE::__FileDelete()
	[+] VOID  Erase()
		[ ] cFILE::__FileDelete()
	[+] //VOID   DeleteMe()
		[ ] //cFILE::__FileDelete()
	[+] BOOLEAN  Exists ()
		[ ] return cFILE::__FileExists()
	[+] property  bExists
		[+] BOOLEAN Get ()
			[ ] return cFILE::__FileExists ()
	[ ] STRING   __sFileName = cBASE::__sPassedValue
	[ ] 
	[+] property  AtEOF // YES if at end of file
		[+] BOOLEAN Get ()
			[ ] return this.__AtEof
	[ ] 
	[+] void   Append (ANYTYPE PassedItem)
		[ ] ANYTYPE item
		[ ] 
		[ ] this.__OpenAs (FM_APPEND)
		[ ] 
		[+] if (TypeOf (PassedItem) == LIST)
			[+] for each item in PassedItem
				[ ] this.Append (item)
		[+] else
			[ ] FileWriteLine (this.__CurrentFileHandle, "{PassedItem}")
			[ ] this.__ConditionalClose ()
			[ ] 
	[+] void   Close ()
		[ ] this.__Close ()
		[ ] this.__HavePerformedOverwriteSinceExplicitClose_Flag = NO
		[ ] 
	[+] void   DeleteMe ()
		[ ] this.Close ()
		[ ] this.Delete ()
		[ ] 
	[+] void   New ()
		[ ] this.Close()
		[ ] this.Delete ()
		[ ] 
	[+] STRING   Read ()
		[+] if ! this.bExists
			[ ] raise 1, "FILE {this.sFileName} DOES NOT EXIST, READ OPERATION FAILED."
			[ ] 
		[ ] this.__OpenAs (FM_READ)
		[ ] 
		[ ] STRING sData
		[ ] FileReadLine (this.__CurrentFileHandle, sData)
		[ ] 
		[+] do
			[+] if (sData == NULL)
				[ ] this.__AtEof = YES
				[ ] sData = NULL
		[+] except
			[ ] this.__AtEof = YES
			[ ] sData = NULL
			[ ] 
		[ ] return sData
		[ ] 
	[+] void   Write (ANYTYPE PassedItem)
		[+] if (this.__HavePerformedOverwriteSinceExplicitClose_Flag == NO)
			[ ] this.Delete ()
			[ ] this.__HavePerformedOverwriteSinceExplicitClose_Flag = YES
		[ ] this.Append (PassedItem)
	[ ] 
	[ ] // =============================================================
	[ ] // = PRIVATE MEMBERS! DO NOT USE! PRIVATE MEMBERS! DO NOT USE! =
	[ ] // =============================================================
	[ ] 
	[+] property  __Drive_Path_And_Name
		[+] STRING Get ()
			[ ] return SubStr (this.sFileName, 1, StrPos (".", this.sFileName) - 1)
			[ ] 
	[+] property  __bLocked
		[+] BOOLEAN Get ()
			[ ] return this.__LokFile.Exists ()
			[ ] 
	[ ] STRING   __sCurrentFileName = ""
	[ ] BOOLEAN  __HavePerformedOverwriteSinceExplicitClose_Flag = NO
	[ ] INTEGER  __CurrentOpenMode = FM_CLOSED
	[ ] HANDLE  __CurrentFileHandle
	[ ] BOOLEAN  __AtEof = NO
	[ ] OBJECT  __LokFile
	[+] INTEGER  __Init ()
		[ ] this.__sCurrentFileName = cBASE::__sPassedValue
		[ ] return 0
		[ ] 
	[ ] INTEGER  __iConstructor = __Init ()
	[+] INTEGER  __LocalInit ()
		[ ] this.__LokFile = cTEXTFILE (this.__Drive_Path_And_Name + ".LOK")
		[ ] return 1
		[ ] 
	[ ] INTEGER  __iLocalConstructor = this.__LocalInit ()
	[+] void   __Close ()
		[+] if (this.__CurrentOpenMode != FM_CLOSED)
			[ ] FileClose (this.__CurrentFileHandle)
			[ ] this.__CurrentOpenMode = FM_CLOSED
			[ ] this.__LokFile.DeleteMe ()
			[ ] 
	[+] void   __ConditionalClose ()
		[+] if (this.CloseAfterEachWrite == YES)
			[ ] this.__Close ()
			[ ] 
	[+] void   __OpenAs (INTEGER FileMode)
		[+] while (this.__CurrentOpenMode == FM_CLOSED && this.__bLocked)
			[ ] sleep (1) // DO NOTHING, WAIT
			[ ] 
		[+] if (this.__CurrentOpenMode != FileMode)
			[ ] this.__Close ()
			[ ] this.__CurrentFileHandle = FileOpen (this.__sFixedFileName, FileMode)
			[ ] this.__CurrentOpenMode = FileMode
			[ ] this.__AtEof = NO
			[ ] 
		[+] if this.__CurrentOpenMode != FM_CLOSED
			[ ] this.__LokFile.Write ()
[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cEXEFILE   Executable File Object
[ ] 
[ ] // Purpose:   Provides centralized file services to caller
[ ] 
[ ] // inherits:  cFILE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // Methods:   Run()   Executes the file
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:
[ ] 
[ ] //==========================================================================
[+] winclass cEXEFILE : cFILE
	[+] VOID  Delete()
		[ ] this.__FileDelete()
	[+] VOID  Destroy()
		[ ] this.__FileDelete()
	[+] VOID  Erase()
		[ ] this.__FileDelete()
	[+] VOID   DeleteMe()
		[ ] this.__FileDelete()
	[+] BOOLEAN  Exists ()
		[ ] return this.__FileExists()
	[+] property  bExists
		[+] BOOLEAN Get ()
			[ ] return this.__FileExists ()
	[ ] STRING   __sFileName = cBASE::__sPassedValue
	[ ] 
	[-] VOID Run(STRING sIncoming NULL optional)
		[-] if sIncoming == NULL
			[ ] sIncoming = ""
		[-] else
			[ ] sIncoming = " " + sIncoming
		[ ] //print("Executing {this} {this.sFileName} {sIncoming}")
		[ ] APP_Start("{this.sFileName} {sIncoming}")
[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cEXEANDWAIT  Executable File Object, waits for program completion
[ ] 
[ ] // Purpose:   Runs file, and waits for completion
[ ] 
[ ] // inherits:  cEXEFILE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // Methods:   RunAndWait() Runs and waits till completion
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:
[ ] 
[ ] //==========================================================================
[-] winclass cEXEANDWAIT : cEXEFILE
	[-] RunAndWait (STRING sIncoming NULL optional)
		[ ] 
		[ ] // sIncoming is additional command line arguments
		[ ] 
		[+] if sIncoming == NULL
			[ ] sIncoming = ""
		[ ] 
		[ ] OBJECT CompletionMessage = cFILE(cSystem.oTempDir.sDirPath + "finished.bc")
		[ ] CompletionMessage.Delete ()
		[ ] 
		[ ] OBJECT StoredFile = cTEXTFILE(cSystem.oTempDir.sDirPath+"ExecAndSendCompletionMessage.bat")
		[ ] OBJECT StoredFileFlag = cSTATIC ("STOREDFILE")
		[-] if (StoredFileFlag.Value == NULL) || ( ! StoredFile.bExists)
			[+] StoredFile.__lsData = {...}
				[ ] "@echo off"
				[ ] ""
				[ ] "if exist {CompletionMessage.sFileName} del {CompletionMessage.sFileName}"
				[ ] ""
				[ ] "call %1 %2 %3 %4 %5 %6 %7 %8 %9"
				[ ] ""
				[ ] "date /t > {CompletionMessage.sFileName}"
				[ ] "time /t >> {CompletionMessage.sFileName}"
			[ ] 
			[ ] StoredFile.write()
			[ ] StoredFileFlag.Value = TRUE
		[ ] 
		[ ] CompletionMessage.Delete ()
		[ ] 
		[ ] OBJECT ExeFile = cEXEFILE(StoredFile.sFileName)
		[ ] 
		[ ] print("Executing "+ExeFile.sFileName+" "+this.sFileName+" "+sIncoming)
		[ ] 
		[ ] ExeFile.Run(this.sFileName+" "+sIncoming)
		[ ] 
		[ ] 
		[ ] BOOLEAN WaitFlag = TRUE
		[+] while WaitFlag
			[ ] //print("Waiting... State is CompletionMessage.bExists = {CompletionMessage.bExists}")
			[-] if CompletionMessage.bExists
				[ ] WaitFlag = FALSE
				[ ] CompletionMessage.Delete ()
			[-] else
				[ ] sleep (10)
		[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cEXEANDWAIT_SAFE Executable File Object, waits for program completion
[ ] 
[ ] // Purpose:   There's a bug in Windoze where, for some reason,
[ ] //     batch files under QAP don't always start when they're
[ ] //     supposed to. This seems to only occur when working
[ ] //     with very complex scripts.
[ ] //
[ ] //     This code attempts to correct the problem by writing
[ ] //     a batch file to execute BEFORE the desired batch is
[ ] //     called. For some reason, the second batch will always
[ ] //     get run.
[ ] 
[ ] // inherits:  cEXEANDWAIT
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // Methods:   RunAndWait() OVERRIDE FROM INHERETED CLASS
[ ] //         Runs a batch file called 'DopeyMe'
[ ] //         Then runs the called batch. 
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:
[ ] 
[ ] //==========================================================================
[+] winclass cEXEANDWAIT_SAFE : cEXEANDWAIT
	[-] RunAndWait (STRING sIncoming NULL optional)
		[ ] 
		[-] if sIncoming == NULL
			[ ] sIncoming = ""
		[ ] 
		[ ] STRING sDopeyMeFileSpec = cSystem.oTempDir.sDirPath + "DopeyMe.bat"
		[ ] OBJECT DopeyMeBAT = cEXEANDWAIT(sDopeyMeFileSpec)
		[ ] OBJECT DopeyMeTXT = cTEXTFILE(sDopeyMeFileSpec)
		[ ] OBJECT DopeyMeFLG = cSTATIC ("DOPEYME")
		[ ] 
		[-] if DopeyMeFLG.Value == NULL
			[-] DopeyMeTXT.__lsData = {...}
				[ ] "@echo off"
				[ ] "echo ARGH! ARGH! ARGH! ARGH!"
				[ ] "echo ARGH! ARGH! ARGH! ARGH!"
				[ ] "echo ARGH! ARGH! ARGH! ARGH!"
				[ ] "echo ARGH! ARGH! ARGH! ARGH!"
				[ ] "echo ARGH! ARGH! ARGH! ARGH!"
				[ ] "echo ARGH! ARGH! ARGH! ARGH!"
			[ ] DopeyMeTXT.write()
			[ ] DopeyMeFLG.Value = TRUE
		[ ] 
		[ ] DopeyMeBAT.RunAndWait ()
		[ ] 
		[ ] cEXEANDWAIT::RunAndWait(sIncoming)
[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cINIFILE   INI File Object
[ ] 
[ ] // Purpose:   Provides INI file services to caller
[ ] 
[ ] // inherits:  cFILE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // properties:  bExists   boolean indicating whether the file exists
[ ] //         in mass storage. (Inherited)
[ ] //     sFileName  string of file name (can be passed at instantiation)
[ ] //         (Inherited)
[ ] 
[ ] // functions:  DeleteMe()  delete the file from storage (if it exists) (Inherited)
[ ] //     Store(s,s,s) store a value to ini file
[ ] //     Retrieve(s,s) retrieve a value from ini file
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:
[ ] 
[ ] //==========================================================================
[+] winclass cINIFILE : cFILE
	[+] VOID  Delete()
		[ ] this.__FileDelete()
	[+] VOID  Destroy()
		[ ] this.__FileDelete()
	[+] VOID  Erase()
		[ ] this.__FileDelete()
	[+] VOID   DeleteMe()
		[ ] this.__FileDelete()
	[+] BOOLEAN  Exists ()
		[ ] return this.__FileExists()
	[+] property  bExists
		[+] BOOLEAN Get ()
			[ ] return this.__FileExists ()
	[ ] STRING   __sFileName = cBASE::__sPassedValue
	[ ] 
	[+] Store (STRING sSection, STRING sKeyword, STRING sValue)
		[ ] this.__Open ()
		[ ] INIFileSetValue (this.__hInternalHandle, sSection, sKeyword, sValue)
		[ ] this.__ConditionalClose ()
		[ ] 
	[+] STRING Retrieve (STRING sSection, STRING sKeyword)
		[ ] STRING sReturnValue
		[ ] 
		[ ] this.__Open ()
		[ ] sReturnValue = INIFileGetValue (this.__hInternalHandle, sSection, sKeyword)
		[ ] this.__ConditionalClose ()
		[ ] 
		[ ] return sReturnValue
		[ ] 
	[+] Write ()
		[ ] this.__Close ()
	[ ] 
	[ ] // =============================================================
	[ ] // = PRIVATE MEMBERS! DO NOT USE! PRIVATE MEMBERS! DO NOT USE! =
	[ ] // =============================================================
	[ ] 
	[ ] ANYTYPE __hInternalHandle = 0 // INIT VALUE, CHECK AGAINST 0 LATER TO SEE IF OPENED
	[ ] BOOLEAN __fMode = TRUE // TRUE = CLOSE EACH TIME A STORE IS EXECUTED
	[ ] ANYTYPE __fStatus = FM_CLOSED // FM_CLOSED or FM_INIOPEN
	[ ] 
	[+] VOID __Open ()
		[+] if this.__fStatus == FM_CLOSED
			[ ] this.__hInternalHandle = INIFileOpen (this.__sFixedFileName)
			[ ] this.__fStatus = FM_INIOPEN
			[ ] 
	[+] VOID __Close ()
		[+] if this.__fStatus == FM_INIOPEN
			[ ] INIFileClose (this.__hInternalHandle)
			[ ] this.__fStatus = FM_CLOSED
			[ ] this.__hInternalHandle = 0
			[ ] 
	[+] VOID __ConditionalClose ()
		[+] if this.__fMode
			[ ] this.__Close ()
			[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cTIMER   Timer object
[ ] 
[ ] // Purpose:   Encapsulates Timer functionality
[ ] 
[ ] // inherits:  cBASE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // properties:  rElapsedTime real of time elapsed since Start() called
[ ] //     sElapsedTime string of time elapsed since Start() called
[ ] //     sStartTime  string of time timer was started or "NOT STARTED YET"
[ ] //     sStopTime  string of time timer was stopped or "NOT STOPPED YET"
[ ] //     rObjectLatency real of average time spent within timer object
[ ] 
[ ] // functions:  Start()   starts a stopped or paused timer
[ ] //     Stop()   stops a started timer
[ ] //     Pause()   pauses a started timer
[ ] //     Resume()  resumes a paused timer
[ ] //     Reset()   stops timer and resets it to 0
[ ] //     Destroy()  cleans up after a timer (so does reset)
[ ] //     PrintTime()  prints the current elapsed time
[ ] //     ObjectLatency() determines average time spent within object - see notes
[ ] 
[ ] //     HotStart()  returns the object of the started timer
[ ] //     HotStop()  returns the real of the destroyed timer
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:   When timer is running, has been stopped or is paused, the
[ ] //     value in rElapsedTime and sElapsedTime reflects the time that
[ ] //     the timer was running for.
[ ] 
[ ] //     rObjectLatency refers to the amount of time the timer object
[ ] //     will record if started and immediatly stopped. This value can then
[ ] //     be subtracted from reported results. WARNING! Running the ObjectLatency()
[ ] //     function causes the current timer to be destroyed. Run this FIRST before
[ ] //     timing an operation.
[ ] 
[ ] //==========================================================================
[+] winclass cTIMER : cBASE
	[ ] // FUNCTIONS FOR HOT START AND STOP
	[+] object HotStart ()
		[ ] this.start ()
		[ ] return this
		[ ] 
	[+] REAL HotStop ()
		[ ] REAL temp = this.rElapsedTime
		[ ] this.Destroy ()
		[ ] return temp
		[ ] 
		[ ] // FUNCTIONS FOR OPERATING THE TIMER
	[+] void Start ()
		[ ] this.__DoAction ("Start", "Start", "__DoStart", "__DoStart")
	[+] REAL Stop ()
		[ ] return this.__DoAction ("Stop", "__DoStop", "Stop", "__DoStop")
	[+] REAL Pause ()
		[ ] return this.__DoAction ("Pause", "__DoPause", "Pause", "Pause")
	[+] REAL Resume ()
		[ ] return this.__DoAction ("Resume", "Resume", "Resume", "__DoResume")
	[+] REAL Reset ()
		[ ] return this.Destroy ()
		[ ] 
		[ ] 
		[ ] // VALUES MAINTAINED BY THE TIMER
	[ ] 
	[+] property rElapsedTime
		[+] REAL Get ()
			[ ] return this.__rRawElapsedTime - this.__rCalculatedObjectLatency
	[+] property sElapsedTime
		[+] STRING Get ()
			[ ] return "{this.rElapsedTime}"
			[ ] 
	[ ] 
	[ ] STRING sStartTime = "NOT STARTED YET"
	[ ] STRING sStopTime = "NOT STOPPED YET"
	[ ] 
	[ ] 
	[ ] 
	[ ] // TIMER "UTILITY" FUNCTIONS
	[+] REAL Destroy ()
		[ ] REAL result = 0
		[+] if (typeof(this._____InternalTimerHandle) == HANDLE)
			[+] if this.__TimerState != TS_STOPPED
				[ ] this.Stop ()
			[ ] TimerDestroy (this.__TimerHandle)
			[ ] this._____InternalTimerHandle = 0
			[ ] this.sStartTime = "NOT STARTED YET"
			[ ] this.sStopTime = "NOT STOPPED YET"
			[ ] result = rElapsedTime
		[ ] return result
		[ ] 
	[+] PrintTime ()
		[ ] print ("{this.__sName}.sElapsedTime = {this.sElapsedTime}")
	[ ] 
	[ ] // THINGS TO DO WITH TIMER LATENCY
	[+] property rObjectLatency // THIS IS USED BY THE SYSTEM OBJECT
		[-] REAL Get ()
			[-] if this.__rCalculatedObjectLatency == 100000
				[ ] this.ObjectLatency ()
			[ ] return this.__rCalculatedObjectLatency
			[ ] 
	[+] REAL ObjectLatency ()
		[ ] REAL rResult = 0
		[ ] 
		[-] if this.__rCalculatedObjectLatency == 100000
			[ ] object GlobalTimerLatency = cSTATIC ("TIMERLATENCY")
			[-] if GlobalTimerLatency.Value == NULL
				[ ] this.__rCalculatedObjectLatency = 0
				[ ] 
				[ ] LIST OF REAL lrResults
				[ ] INTEGER l
				[ ] REAL total = 0, average
				[ ] ANYTYPE item
				[ ] 
				[-] for l = 1 to 20
					[ ] Reset ()
					[ ] Start ()
					[ ] Stop ()
					[ ] listappend (lrResults, this.__rRawElapsedTime)
					[ ] Destroy ()
					[ ] 
				[-] for each item in lrResults
					[ ] total = total + item
					[ ] 
				[ ] average = total / listcount (lrResults)
				[ ] this.__rCalculatedObjectLatency = average
				[ ] 
				[ ] GlobalTimerLatency.Value = average
				[ ] 
				[ ] rResult = average
			[+] else
				[ ] this.__rCalculatedObjectLatency = GlobalTimerLatency.Value
		[ ] return rResult
		[ ] 
	[ ] 
	[ ] // =============================================================
	[ ] // = PRIVATE MEMBERS! DO NOT USE! PRIVATE MEMBERS! DO NOT USE! =
	[ ] // =              SUBJECT TO UNEXPECTED REVISION!              =
	[ ] // =============================================================
	[ ] 
	[ ] builtin STRING GetID ()
	[ ] 
	[ ] REAL __rCalculatedObjectLatency = 100000
	[ ] 
	[+] property __rRawElapsedTime
		[+] REAL Get ()
			[ ] return TimerValue (this.__TimerHandle)
			[ ] 
	[+] property __TimerHandle
		[+] HTIMER Get ()
			[+] if IsInteger (this._____InternalTimerHandle)
				[ ] this._____InternalTimerHandle = TimerCreate ()
			[ ] return this._____InternalTimerHandle
			[ ] 
	[ ] 
	[ ] ANYTYPE _____InternalTimerHandle = 0
	[ ] 
	[+] property __TimerState
		[+] TIMERSTATE Get ()
			[ ] return TimerState (this.__TimerHandle)
			[ ] 
	[ ] 
	[+] REAL __DoAction (STRING sCaller, STRING sStart, STRING sStopped, STRING sPaused)
		[+] switch this.__TimerState
			[+] case TS_STARTED
				[+] if sStart[1] == "_"
					[ ] @(sStart) ()
				[+] else
					[ ] this.__DoRaise (sCaller)
			[+] case TS_STOPPED
				[+] if sStopped[1] == "_"
					[ ] @(sStopped) ()
				[+] else
					[ ] this.__DoRaise (sCaller)
			[+] case TS_PAUSED
				[+] if sPaused[1] == "_"
					[ ] @(sPaused) ()
				[+] else
					[ ] this.__DoRaise (sCaller)
		[ ] return rElapsedTime
		[ ] 
	[+] __DoRaise (STRING sCaller)
		[ ] raise 100000, "cTIMER {this.__sName}.{sCaller}() *** Error: Timer is {SubStr("{this.__TimerState}",3,3000)}"
		[ ] 
	[+] __DoSTart ()
		[ ] this.ObjectLatency ()
		[ ] sStartTime = TimeStr ()
		[ ] TimerStart (this.__TimerHandle)
		[ ] 
	[+] __DoStop ()
		[ ] TimerStop (this.__TimerHandle)
		[ ] sStopTime = TimeStr ()
		[ ] 
	[+] __DoPause ()
		[ ] TimerPause (this.__TimerHandle)
	[+] __DoResume ()
		[ ] TimerResume (this.__TimerHandle)
[ ] 
[ ] 
[ ] 
[ ] 
[ ] //==========================================================================
[ ] // cSYSTEM   System object - represents system running test
[ ] 
[ ] // Purpose:   Encapsulates system activities
[ ] 
[ ] // inherits:  cBASE
[ ] 
[ ] // PUBLIC MEMBERS:
[ ] 
[ ] // PUBLISHED PRIVATE MEMBERS:  none
[ ] 
[ ] // NOTES:   desktop size
[ ] 
[ ] //     Used to calculate timer latency on startup
[ ] //     Performance of CPU
[ ] //     Creates time stamp
[ ] 
[ ] //==========================================================================
[+] winclass cSYSTEM : cBASE
	[ ] 
	[ ] 
	[ ] const sDirSeperator = "\"
	[ ] 
	[+] property sShell
		[-] STRING Get()
			[ ] STRING sResult
			[-] if ! this.IsWindows()
				[ ] raise 1,"Unable to get appropraite platform shell"
			[-] else
				[ ] sResult = GetEnv("COMSPEC")
			[ ] return sResult
	[+] property sTempDir
		[-] STRING Get()
			[ ] return GetEnv("TEMP")+sDirSeperator
	[ ] 
	[+] property oTempDir
		[-] OBJECT Get()
			[ ] OBJECT result = cDIR(this.sTempDir)
			[ ] return result
	[ ] 
	[+] property  rDeskTop
		[+] RECT Get ()
			[ ] return CustomWin ("/").GetRect ()
			[ ] 
	[+] property  rTimerLatencyOnThisMachine
		[+] REAL Get ()
			[ ] return cTIMER ().rObjectLatency
	[+] property  rHalfTimerLatencyOnThisMachine
		[+] REAL Get ()
			[ ] return rTimerLatencyOnThisMachine / 2
			[ ] 
			[ ] // The lower the better
	[ ] 
	[+] REAL   rPerformanceIndexOfThisCPU ()
		[ ] object tPerformanceTimer = cTIMER ().HotStart ()
		[ ] 
		[ ] ANYTYPE a = 0.0, item, x, l = {"A", "B", "C", "D", "E"}, s = "One two three four five six"
		[ ] 
		[ ] // TESTS
		[+] for x = 1 to 10000
			[+] for each item in l
				[ ] x = listfind (l, item)
			[ ] x = listfind (l, "Z")
			[ ] a = a + 1.1
			[ ] s[1] = ""
			[ ] s[1] = "O"
			[ ] // END TESTS
			[ ] 
		[ ] return tPerformanceTimer.HotStop ()
		[ ] 
		[ ] 
	[+] STRING  TimeStamp()
		[ ] return "{DateStr()} {TimeStr()}"
	[+] STRING  GetEnv(STRING sVar)
		[ ] return SYS_GetEnv(sVar)
	[+] STRING  CurrentDir()
		[ ] return SYS_GetDir()
	[ ] 
	[+] property iHour
		[+] INTEGER Get()
			[ ] return this.__GetPart(DTP_HOUR)
	[+] property iMinute
		[+] INTEGER Get()
			[ ] return this.__GetPart(DTP_MINUTE)
	[+] property  iSecond
		[+] INTEGER Get()
			[ ] return this.__GetPart(DTP_SECOND)
	[+] property iYear
		[+] INTEGER Get()
			[ ] return this.__GetPart(DTP_YEAR)
	[+] property iMonth
		[+] INTEGER Get()
			[ ] return this.__GetPart(DTP_MONTH)
	[+] property iDay
		[+] INTEGER Get()
			[ ] return this.__GetPart(DTP_DAY)
	[+] property sSortableDate
		[+] STRING Get()
			[ ] return "{this.iYear}{this.iMonth}{this.iDay}"
	[+] property sSortableTime
		[+] STRING Get()
			[ ] return "{this.iHour}{this.iMinute}{this.iSecond}"
	[+] property sSortableDateTime
		[+] STRING Get()
			[ ] return "{this.iYear}{this.iMonth}{this.iDay}{this.iHour}{this.iMinute}{this.iSecond}"
	[+] property iDayOfWeek
		[+] INTEGER Get()
			[ ] return this.__GetPart(DTP_DAYOFWEEK)
	[+] property iDayOfYear
		[+] INTEGER Get()
			[ ] return this.__GetPart(DTP_DAYOFYEAR)
	[ ] 
	[+] ANYTYPE __GetPart(ANYTYPE aPart)
		[ ] return GetDateTimePart(GetDateTime(), aPart)
	[ ] 
	[+] // type DATETIMEPART is enum
		[ ] // DTP_YEAR
		[ ] // DTP_MONTH
		[ ] // DTP_DAY
		[ ] // DTP_DAYOFYEAR
		[ ] // DTP_DAYOFWEEK
		[ ] // DTP_HOUR
		[ ] // DTP_MINUTE
		[ ] // DTP_SECOND
		[ ] // DTP_MICROSEC
		[ ] // 
	[ ] 
	[+] BOOLEAN  IsWindows()
		[ ] return sContains("{GetGuiType()}","Microsoft Windows")
[ ] 
[ ] 
[ ] window cSYSTEM cSystem
[ ] 
