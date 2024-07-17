[ ] use "4class3.inc"
[ ] 
[ ] ////////////////////////////////////////////////////////////
[+] // expand for misc documentation                          //
	[ ] //
	[ ] // Image Director and Cookie Bounce Test Plan
	[ ] // Implemented 2001 by Akien MacIain
	[ ] //
	[+] // Assumptions about the person operating or modifying this code
		[ ] // 
		[ ] // It is assumed that the operator or programmer modifying this
		[ ] // code has basic familiarity with Silk, and understands the following:
		[ ] // 
		[ ] // * The SilkTest Agent, including setting network options, and 
		[ ] //   it's role in the Silk architecture.
		[ ] //
		[ ] // * The difference between the window and winclass keywords
		[ ] //
		[ ] // * TestCaseEnter, TestCaseExit, and realted function overrides.
		[ ] //
		[ ] // * The basic design philosophy of object oriented programming
		[ ] //
		[ ] // * The operator understands Silk "properites" (a peice of code
		[ ] //   that appears to be a data member, but it's data is arrived
		[ ] //   at by the execution of code).
		[ ] //
		[ ] // If any of these areas are unclear to you, you should consult
		[ ] // either a competant authority on Silk, the Silk manuals, or,
		[ ] // as a last resort, technical support.
		[ ] //
		[ ] // It is further assumed that the operator understands the layout
		[ ] // and use of INI files.
		[ ] //
	[ ] //
	[+] // Execution notes
		[ ] //
		[ ] // * You MUST have browser extensions enabled in Silk for the
		[ ] //   browser you will be using to perform the tests.
		[ ] //
		[ ] // * All servers, both image directors and E-Color back end 
		[ ] //   MUST be running, logged in as an administrator (qagod, most of the 
		[ ] //   QA engineers, a domain admin, etc)
		[ ] //
		[ ] // * That all servers be running the Silktest Agent
		[ ] //
		[ ] // * That the machine executing the test be running Silk, configured 
		[ ] //   to talk to the local agent by default
		[ ] //
		[ ] // * That "Enable browser-specific image names" be turned off:
		[ ] //   Extension dialog, Internet Explorer, extension options button -
		[ ] //   This is NOT the default setting.
		[ ] //
		[ ] // * IMPORTANT: E-Color servers having both an internal and an external 
		[ ] //   network interface MUST have their Agent configured to use
		[ ] //   NETBIOS and the machine's NETBIOS name in the Agent must
		[ ] //   be the same as the server's internal name, for instance:
		[ ] //   TICQASVR8
		[ ] //   For this reason, it is reccomended all Agents, and Silk IDEs
		[ ] //   be set to use NETBIOS (this is NOT he default setting)
		[ ] //
		[ ] // * Is is also required that all aspects of the server be configured,
		[ ] //   which is to say, if you're going to run Footprint tests, all
		[ ] //   footprint related properties must be set correctly, so that 
		[ ] //   this script mearly needs to turn the service on and off.
		[ ] //
	[ ] // 
	[+] // Limitations beyond those imposed by the manual test plan
		[ ] //
		[ ] // * This code does not attempt to implement support for
		[ ] //   Image Directors on platforms other than WinNT/Win2K.
		[ ] //   This shouldn't be hard to implement, but at the time
		[ ] //   of this writing the Agent software isn't available at
		[ ] //   E-Color to test this.
		[ ] //
		[ ] // * This code does not attempt to run a full browser
		[ ] //   gauntlet, as there is no support in Silk to switch
		[ ] //   browsers at execution time. Support code for this
		[ ] //   could probably be created, but it would be a lengthy 
		[ ] //   project unto itself.
		[ ] //
	[ ] //
	[+] // Test Parameters
		[ ] //
		[ ] // As much as is possible, this automated test plan operates
		[ ] // without hard coded parameters, but instead relies on 
		[ ] // information from the imagedirectortest.ini file.
		[ ] //
		[ ] // Test configuration information is stored in imagedirectortest.ini, 
		[ ] // represented by the class/instance cINIFILE/TestProps. To change 
		[ ] // test properties, such as E-Color back end server names, simply 
		[ ] // edit the INI file. In order to make additions, add the new section(s) 
		[ ] // or keyword(s) to the INI file, then add new Section and/or Key 
		[ ] // class instances to the TestProps object.
		[ ] // 
		[ ] // As is shown in the code, when you want to refer to the item in 
		[ ] // the INI file, like so:
		[ ] // 
		[ ] // [QALogon]
		[ ] // userid=qa\qagod
		[ ] // 
		[ ] // So the objet definition for TestProps looks something like this:
		[ ] // 
		[ ] // object cINIFILE TestProps
		[ ] //     STRING __sFileName = "C:\ecolor\Image Director\ImageDirectorTest.ini"
		[ ] //     Section QALogon
		[ ] //         Key userid
		[ ] // 
		[ ] // When you are getting data from the INI file, you will always get 
		[ ] // back strings. You can get this data like so:
		[ ] // 
		[ ] // foo = TestProps.QALogon.userid.sValue 
		[ ] // 
		[ ] // The .QALogon. refers to the [QALogon] section of 
		[ ] // the INI file. The instance of the Section class must be spelled 
		[ ] // the same as the section name in the INI file. The same is true 
		[ ] // for the Key class, which .userid. is an instance of.
		[ ] // 
		[ ] // The Key class has one property, .sValue which has both get and 
		[ ] // set methods, which means the test code can write to this property, 
		[ ] // and modify the INI file.
		[ ] // 
	[ ] //
	[+] // Primary Interfaces
		[ ] //
		[ ] //     This code attempts to reduce the operation of the test
		[ ] //     suite to a minimal number of extensible interfaces.
		[ ] //
		[ ] //     The main interfaces are
		[ ] //
		[ ] //         cIMAGEDIRECTOR (ImageDirector1 & ImageDirector2)
		[ ] //         EColorServers
		[ ] //         BrowserSupport
		[ ] //
		[ ] //     Some of the most commonly used secondary interfaces
		[ ] //     used by this code are:
		[ ] //
		[ ] //         Browser (provided with Silk)
		[ ] //		   TuneUp (does a default tune up)
		[ ] //         cCOOKIE (included in ImageDirector class)
		[ ] //         cSERVERINTERFACE (included in ImageDirector and EColorServers
		[ ] //         SecurityAlert (browser prompting for accept cookie)
		[ ] //
		[ ] //     Something the user will probably seldom use directly,
		[ ] //     but an interface that is used throughout the system is
		[ ] //     "TestProps", which is the abstraction that covers the
		[ ] //     test properties file. If you add fields to the 
		[ ] //     properties file, you'll have to add them to this instance.
		[ ] //
	[ ] //
	[+] // Implementation Notes
		[ ] //
		[ ] // * URLs for Tune Up are constructed in the TuneUp object.
		[ ] //
		[ ] // * Wherever possible, browser or OS specific code is isolated by 
		[ ] // function, rather than within a function. This kind of isolation 
		[ ] // is accomplished using the os type or browser type, like so:
		[ ] // 
		[ ] // mswnt foo(string bar)
		[ ] // // do NT/2K specific code here
		[ ] // 
		[ ] // msw98 foo(string bar)
		[ ] // // do 98 specific code here
		[ ] // 
		[ ] // void __fooSharedCode(string bar)	// might be present if foo had platform 
		[ ] //                                  // independent functionality
		[ ] // 
		[ ] // explorer5 ifoo(string bar)
		[ ] // // ie5 code
		[ ] // 
		[ ] // explorer4 ifoo(string bar)
		[ ] // // ie4 code
		[ ] // 
		[ ] // The only drawback to this kind of implementation is that you can't 
		[ ] // compound them directly, you can't, for instance, do this:
		[ ] // 
		[ ] // mswnt explorer5 foo()
		[ ] // 
		[ ] // Instead, you'd have to do this:
		[ ] // 
		[ ] // mswnt foo()
		[ ] //  	browser_specific_foo()
		[ ] // explorer5 browser_specific_foo()
		[ ] // 
		[ ] // explorer4 browser_specific_foo()
		[ ] // 
		[ ] // These 'types' can, however, be used on a single line of code, like so:
		[ ] //
		[ ] // foo()
		[ ] //		string a = ""
		[ ] //		netscape a = "hi"
		[ ] //		explorer a = "bye"
		[ ] //
		[ ] // These types can be found in the 4test.inc file that comes with Silk.
		[ ] //
	[ ] //
	[+] // Library notes
		[ ] //
		[ ] // * Libraries 4Code3.inc and 4class3.inc are 4Test Extension libraries written 
		[ ] //   and maintained by Akien MacIain, most recent code is always available at:
		[ ] //
		[ ] //   ftp://ftp.weirdness.org/pub/4TestLanguageExtentions/
		[ ] //
		[ ] //   As this code is updated, previous interfaces are strictly enforced,
		[ ] //   to insure compatibility with existing code. Akien can be contacted for
		[ ] //   bugs in these libraries at akienm@weirdness.org
		[ ] // 
		[ ] // * In the event of a major revision, 4class and 4code would become 4class4.inc and
		[ ] //   4code4.inc. No warrent is made that v4 will be compatible with v3, though differences
		[ ] //   would be noted in the documentation.
		[ ] //
		[ ] // * 4Code3.inc is a set of functions that are generic 4Test language extensions,
		[ ] //   independant of environment or company. The functions are documented in the
		[ ] //   code.
		[ ] //
		[ ] // * 4Class3.inc is a set of objects for abstracting timers, files, the system being
		[ ] //   tested on, and other, non-window based abstractions.
		[ ] //
		[ ] // * Defined in 4CODE3.INC:
		[ ] //     const ON = TRUE
		[ ] //     const OFF = FALSE
		[ ] //
	[ ] //
	[+] // Syntactic Conventions
		[ ] //
		[ ] // * It is important to note that Silk allows the addition of 
		[ ] //   properties to globally defined instances directly, rather 
		[ ] //   than by defining an "intervening class". This feature is 
		[ ] //   made use of in this code.
		[ ] //   
		[ ] // * In this code, and in the supporting class libraries, it is common to
		[ ] //   have data types defined as all caps.
		[ ] //
		[ ] // * Classes are defined with a lower case "c" at the beginning, and then 
		[ ] //   the class name all upper case, like so: cCOOKIE
		[ ] //
		[ ] // * Since Silk does not support class private properties,
		[ ] //   prefacing something with a double underscore indicates that the
		[ ] //   item in question should be treated as class private, and that
		[ ] //   in most cases using it directly should be avoided, as it may
		[ ] //   have unintended consiquences. There are two exceptions to this
		[ ] //   in the library 4CLASS3.INC, they are __sFileName for the class 
		[ ] //   cFILE and it's dirivatives (when instantiating a global instance,
		[ ] //   you must define STRING __sFileName = <whatever the filename is>)...
		[ ] //   And for cTEXTFILE, the property __lsData is the raw list of the
		[ ] //   contents of the text file. You can not directly write to a specified
		[ ] //   line in the list using the syntax lsData[3] = "Hi!", for this 
		[ ] //   particular action, you have to use __lsData directly, like 
		[ ] //   so: __lsData[3]="Hi!"
		[ ] //
	[ ] //
	[+] // WARNINGS
		[ ] // 
		[ ] // * Silk is a 2 pass compiler. for this reason, things are
		[ ] //   not required to be defined in the order used. However, even though 
		[ ] //   it's a two pass compiler, if the interdependancies become too great,
		[ ] //   the compiler can still become confused, and the result can be error
		[ ] //   messages that make no sense.
		[ ] //
		[ ] // * Silk does not support constructors and destructors. However, it is
		[ ] //   possible to force Silk to do comparable behavior to a constructor like 
		[ ] //   so:
		[ ] //
		[ ] //   window cBASE MyObject
		[ ] //      boolean __CostructorResult = __Constructor()
		[ ] //      boolean __Constructor()
		[ ] //        // do stuff here
		[ ] //        return true
		[ ] //
		[ ] //   While this is a powerful tool, if there are bugs in the code,
		[ ] //   Silk isn't very helpful about reporting these bugs. You'll get 
		[ ] //   error messages, they just may not make any sense.
	[ ] //
	[+] // Platform/Browser issues
		[ ] // 
		[ ] // Netscape and IE are very different beasts. IE, via the Windows OS, makes it's cookies
		[ ] // available as distinct files, where NS uses a single cookie file.
		[ ] //
	[ ] //
[ ] ////////////////////////////////////////////////////////////
[ ] 
[ ] ////////////////////////////////////////////////////////////
[+] // expand for global settings changes                     //
	[ ] 
	[ ] // this is populated from the INI file, and is used to
	[ ] // flag whether to print all the debug info or not.
	[ ] OPTION fDebug
	[ ] 
	[ ] // this next item is required to manipulate a setting in the
	[ ] // library that controls how file names are manipulated on 
	[ ] // the windows platofrm.
	[+] window cFILE ResetDefaultParameters
		[ ] boolean __cf = __c()
		[-] boolean __c()
			[ ] STATIC_Set("PFILECLASSES","USERAWFILENAMEFLAG",TRUE)
			[ ] return true
[ ] ////////////////////////////////////////////////////////////
[ ] 
[ ] ////////////////////////////////////////////////////////////
[+] // expand for support code (framework)                    //
	[ ] 
	[-] //primary and secondary interfaces
		[ ] // interfaces listed in reverse order because of compile 
		[ ] // requirments:
		[-] // secondary
			[ ] 
			[ ] // NetCommand is used to issue commands to do functions provided 
			[ ] // through that interface. So, drive mapping, service start and
			[ ] // stop, authenticating with a remote machine, that sort of thing
			[ ] // is done via command line calls to this gizmo. Typical usage
			[ ] // looks like this:
			[ ] // NetCommand.RunAndWait('Start "World Wide Web Publishing Service"')
			[+] window cEXEFILE NetCommand
				[ ] string __sFileName = "net"
			[ ] 
			[ ] // AgentInterface is an instance rather than a class, 
			[ ] // because there's only one Agent. This object's job is
			[ ] // to abstract the machine switching mechanism. There's only
			[ ] // one call, SwitchMachine(sName optional) If you specify
			[ ] // sName, control will switch to that machine. If you 
			[ ] // don't, control will switch back to the current machine.
			[+] window cBASE AgentInterface
				[ ] // Not specifying the optional parameter will cause the
				[ ] // local machine to be selected
				[-] SwitchMachine(string name optional)
					[-] if name != NULL
						[ ] // name was specified
						[ ] DebugPrint("AgentInterface.SwitchMachine({name})")
						[ ] // swicth to remote machine
						[ ] // First, save off local name
						[ ] __hLocalMachine = GetMachine ()
						[ ] 
						[ ] // Now get the handle for the other box
						[ ] // And connect to it
						[-] do
							[ ] __hCurrentMachine = Connect(name)
							[ ] SetMachine(__hCurrentMachine)
						[-] except
							[-] do
								[ ] __hCurrentMachine = Connect(name)
								[ ] SetMachine(__hCurrentMachine)
							[-] except
								[-] do
									[ ] __hCurrentMachine = Connect(name)
									[ ] SetMachine(__hCurrentMachine)
								[-] except
									[ ] LogError("*** Error: Failure on connecting to maching {name} (3 tries)")
									[ ] reraise
					[-] else
						[ ] // return to local machine
						[-] if ! IsSet(__hLocalMachine)
							[ ] __hLocalMachine = GetMachine ()
						[-] else
							[ ] SetMachine(__hLocalMachine)
							[ ] Disconnect(__hCurrentMachine)
						[ ] __hCurrentMachine = __hLocalMachine
					[ ] 
					[+] // Example Code From Segue
						[ ] // HMACHINE target_machine     // target computer
						[ ] // HMACHINE host_machine       // host computer
						[ ] // STRING sTarget = "sunfish"  // target's network name
						[ ] // STRING sHost = "moonray"    // host's network name
						[ ] // // save host’s handle
						[ ] // host_machine = GetMachine ()
						[ ] // // save target's handle
						[ ] // target_machine = Connect (sTarget) 
						[ ] // // what is currently active on the target machine?
						[ ] // Print ("Active window on Target: ", Desktop.GetActive ())
						[ ] // // switch to host machine
						[ ] // SetMachine (host_machine)
						[ ] // // what is currently active on host machine?
						[ ] // Print ("Active window on Host: ", Desktop.GetActive ())
						[ ] // Disconnect (target_machine)  // disconnect from target 
				[ ] /////////////////////////////////////////////////////////////////////
				[+] // Class Private
					[ ] HMACHINE __hLocalMachine
					[ ] HMACHINE __hCurrentMachine
				[ ] 
			[ ] 
			[ ] // cSERVERINTERFACE manages starting, stopping and 
			[ ] // changing properties files for servers. The servers
			[ ] // MUST be logged in, and MUST be running the Silk Agent.
			[+] winclass cSERVERINTERFACE : cBASE
				[+] property 	inifile
					[-] window Get()
						[ ] return TestProps.@(this.__sName)
				[ ] 
				[+] void		ServerOff()
					[-] if __fServerRunning
						[ ] __RemoteServiceOperate(false)
						[ ] __fServerRunning = FALSE
				[+] void		ServerOn()
					[-] if ! __fServerRunning
						[ ] __RemoteServiceOperate(true)
						[ ] __fServerRunning = TRUE
				[ ] 
				[+] property 	fServerRunning
					[-] boolean Get()
						[ ] return __fServerRunning
				[+] string 		GetPropertyValue(string parameter)
					[ ] return __GetPropertyValue(parameter)
				[ ] 
				[ ] /////////////////////////////////////////////////////////////////////
				[-] // Class Private
					[ ] // data
					[ ] boolean  	__fServerRunning = TRUE
					[ ] boolean 	__Authenticated = FALSE
					[ ] 
					[ ] // code
					[+] property 	__sPropertiesFileName
						[-] string Get()
							[ ] DebugPrint(this)
							[ ] string sResult = ""
							[ ] sResult = sResult + '\\' +inifile.InternalName.sValue
							[ ] sResult = sResult + '\'  +inifile.ShareName.sValue
							[ ] sResult = sResult + '\'  +inifile.PropertiesFile.sValue
							[ ] return sResult
					[ ] 
					[+] void		__DoConditionalAuth()
						[-] if ! __Authenticated
							[ ] DebugPrint("Attempting to authenticate {inifile.InternalName.sValue}")
							[ ] DebugPrint(NetCommand.RunAndWait("use \\{inifile.InternalName.sValue}\{inifile.ShareName.sValue} {TestProps.QALogon.password.sValue} /user:{TestProps.QALogon.userid.sValue}"))
					[+] integer 	__FindProperty(string parameter)
						[ ] integer result = 0
						[ ] 
						[ ] __DoConditionalAuth()
						[ ] object f = cTEXTFILE(__sPropertiesFileName)
						[ ] f.Read()
						[ ] 
						[ ] string item
						[ ] integer index
						[-] for index = 1 to f.iLength
							[ ] item = trim(f.lsData[index])
							[-] if sContains(item,parameter)
								[-] if ! sContains(item,"#{parameter}")
									[-] if ! (item[1] == "#")
										[ ] result = index
						[ ] 
						[ ] return result
						[ ] 
					[+] string		__GetPropertyValue(string parameter)
						[ ] string result = ""
						[ ] object f = cTEXTFILE(__sPropertiesFileName)
						[ ] f.Read()
						[ ] 
						[ ] integer location = __FindProperty(parameter)
						[-] if location > 0
							[ ] result = f.lsData[location]
							[ ] result = Rightof(result,"=")
						[ ] return trim(result)
					[ ] // WARNING! __ParameterChange will ALTER boolean variables to 
					[ ] // be strings - On or Off
					[+] void		__ParameterChange(string parameter, anytype newvalue)
						[ ] __DoConditionalAuth()
						[ ] object f = cTEXTFILE(__sPropertiesFileName)
						[ ] f.Read()
						[-] if f.iLength == 0
							[ ] f.Read()
						[-] if f.iLength == 0
							[ ] f.Read()
						[-] if f.iLength == 0
							[ ] f.Read()
						[-] if f.iLength == 0
							[ ] raise 1, "ERROR: Unable to read properties from file {f.sFileName}"
						[ ] 
						[ ] anytype newvaluebefore = newvalue
						[ ] 
						[-] if IsBool(newvalue)
							[-] if newvalue
								[ ] newvalue = "On"
							[-] else
								[ ] newvalue = "Off"
						[ ] 
						[ ] integer location = __FindProperty(parameter)
						[ ] 
						[ ] DebugPrint("------------------------------------------")
						[ ] DebugPrint("DEBUG: {newvaluebefore}/{newvalue}")
						[ ] DebugPrint("DEBUG: {location}")
						[ ] DebugPrint("DEBUG: f.sFileName = {f.sFileName}")
						[ ] DebugPrint("DEBUG: f.lsData    = {f.lsData}")
						[ ] DebugPrint("------------------------------------------")
						[ ] 
						[-] if ! IsString(newvalue)
							[ ] raise 1,"ERROR: newvalue wasn't reset to string!"
						[ ] 
						[-] if location < 1
							[ ] raise 1, "ERROR: Parameter in {__sPropertiesFileName} called {parameter} was not found"
						[-] else
							[ ] DebugPrint("Parameter change: {__sPropertiesFileName}/{parameter} = {newvalue}")
							[ ] f.__lsData[location] = "{parameter} = {newvalue}"
							[ ] f.Write()
						[ ] 
					[+] void		__RemoteServiceOperate(boolean newstate)
						[ ] // Remember, EColor backend servers are always NT/2K!
						[ ] string sCommand = "stop"
						[-] if newstate
							[ ] sCommand = "start"
						[ ] 
						[ ] string sJavaEngineServiceName = ""
						[-] do 
							[ ] sJavaEngineServiceName = inifile.JavaEngineServiceName.sValue
						[-] except
							[ ] // bite me.
						[ ] 
						[-] if inifile.InternalName.sValue == ""
							[ ] raise 1,"ERROR: No value from INI file on machine name for {this}"
						[ ] 
						[ ] AgentInterface.SwitchMachine(inifile.InternalName.sValue)
						[ ] 
						[-] if sJavaEngineServiceName != ""
							[ ] string sJavaCommandLine = '{sCommand} "{sJavaEngineServiceName}"'
							[ ] list of string result
							[ ] DebugPrint(NetCommand.RunAndWait(sJavaCommandLine))
						[ ] string sWebCommandLine = '{sCommand} "{inifile.WebServerServiceName.sValue}"'
						[ ] DebugPrint(NetCommand.RunAndWait(sWebCommandLine))
						[ ] 
						[ ] AgentInterface.SwitchMachine()
						[ ] 
					[ ] 
				[ ] 
			[ ] 
			[ ] // cCOOKIE encapsulates cookie manipulation functionality
			[ ] // including cookie contents, cookie exisance, and copying
			[+] winclass cCOOKIE : cTEXTFILE
				[ ] string __sFileName
				[+] //Data
					[ ] string Domain		// populated at instantiation time
					[ ] 
					[ ] int upv				//01 user profile version
					[ ] int uid				//02 user ID
					[ ] string timeStamp	//03 Fresh/Stale Timeout
					[ ] int isCalibrated	//04 Caliration Flag
					[ ] int vpv				//05 Viewing Profile Version
					[ ] int disptype		//06 Display Type
					[ ] string calp1		//07 First Calibration parameter
					[ ] string calp2		//08 Second Calibration parameter
					[ ] string calp3		//09 Third Calibration parameter
					[ ] int bandwidth		//10 Bandwidth	Type
					[ ] string ip			//11 Server Name or IP Address
					[ ] string name			//12 ?????
					[ ] string timeout		// this data is EXTERNAL to the cookie!
				[ ] 
				[+] void  			VerifyCookieExists()
					[ ] __FindCookie()
					[-] if ! bExists
						[ ] raise 1, "Failed: Cookie {__sName} does not exist"
				[+] void  			VerifyCookieNotExists()
					[ ] 
					[ ] boolean bFound = FALSE
					[-] do
						[ ] __FindCookie()
						[-] if bExists
							[ ] bFound = TRUE
					[-] except
						[ ] // bite me...
					[-] if bFound
						[ ] raise 1, "Failed: Cookie {__sName} exists"
				[ ] 
				[+] boolean 		Exists()
					[ ] boolean result
					[+] do
						[ ] this.__FindCookie()
					[+] except
						[-] if ExceptNum() == 1
							[ ] result = false
					[+] if IsSet(this.__sFileName)
						[ ] result = cFILE::Exists()
					[+] else
						[ ] result = false
					[ ] return result
				[+] property 		bExists
					[-] boolean Get()
						[ ] return Exists()
				[-] void			ReadFields()
					[ ] __ReadFields()
				[+] void			DeepCopyFrom(window cookie)
					[ ] //this.ReadFields()
					[ ] cookie.ReadFields()
					[ ] 
					[ ] Domain = cookie.Domain
					[ ] upv = cookie.upv
					[ ] uid = cookie.uid
					[ ] timeStamp = cookie.timeStamp
					[ ] isCalibrated = cookie.isCalibrated
					[ ] vpv = cookie.vpv
					[ ] disptype = cookie.disptype
					[ ] calp1 = cookie.calp1
					[ ] calp2 = cookie.calp2
					[ ] calp3 = cookie.calp3
					[ ] bandwidth = cookie.bandwidth
					[ ] ip = cookie.ip
					[-] if IsSet(cookie.name)
						[ ] name = cookie.name
					[ ] timeout = cookie.timeout
					[ ] __sFileName = cookie.__sFileName
					[ ] 
				[ ] 
				[ ] /////////////////////////////////////////////////////////////////////
				[+] // Class Private
					[+] void 			_DebugPrint()
						[ ] __FindCookie()
						[ ] __ReadFields()
						[ ] print("Name         {this.__sName}")
						[ ] print("Parent       {this.__sParent}")
						[ ] print("upv          {upv}")
						[ ] print("uid          {uid}")
						[ ] print("timeStamp    {timeStamp}")
						[ ] print("isCalibrated {isCalibrated}")
						[ ] print("vpv          {vpv}")
						[ ] print("disptype     {disptype}")
						[ ] print("calp1        {calp1}")
						[ ] print("calp2        {calp2}")
						[ ] print("calp3        {calp3}")
						[ ] print("bandwidth    {bandwidth}")
						[ ] print("ip           {ip}")
						[-] if ! IsSet(name)
							[ ] print("name         NULL")
						[-] else
							[ ] print("name         {name}")
					[ ] 
					[+] // __FindCookie() assumes the following (expand for details)
						[ ] // (these are the observed behaviors as of this writing)
						[ ] //
						[ ] // 1) that IE makes cookies visable in a shell folder that we can look at
						[ ] // 2) that the cookies are named in the form user@domain[x]
						[ ] // 3) that the number x won't exceed 9 (we've actually only seen it as 1 and 2)
						[ ] // 4) that IE4 and IE5 use different markers around the number field
						[ ] //
					[-] explorer void 	__FindCookie()
						[ ] string sUserName = TestSystem.UserName()
						[ ] string sPath = BrowserSupport.GetCookieDir()
						[ ] integer i
						[ ] window Result
						[ ] window CookieFile
						[ ] 
						[-] for i = 9 to 1 step -1
							[ ] string sFileSpec
							[ ] sFileSpec = BrowserSupport.GetCookieDir()+TestSystem.UserName()+"@"
							[ ] sFileSpec = sFileSpec+Domain
							[ ] sFileSpec = sFileSpec+BrowserSupport.CookieMarkers[1]+"{i}"+BrowserSupport.CookieMarkers[2]+".txt"
							[ ] CookieFile = cTEXTFILE(sFileSpec)
							[-] if CookieFile.bExists
								[ ] Result = CookieFile
						[ ] 
						[-] if ! IsSet(Result)
							[ ] print("--------------------------------------------------------")
							[ ] explorer listprint(cEXEFILE(cSystem.GetEnv("comspec")).RunAndWait('/c dir /b "{BrowserSupport.GetCookieDir()}\*.txt"'))
							[ ] raise 1,"ERROR: Couldn't find cookie that looked like {CookieFile.sFileName}"
						[ ] this.__sFileName = Result.sFileName
						[ ] 
					[+] netscape void	__FindCookie()
						[ ] 
					[ ] 
					[+] explorer void   __ReadFields()
						[ ] __FindCookie()
						[-] if ! bExists
							[ ] raise 1, "CAN'T READ COOKIE {this.sFileName}, FILE DOES NOT EXIST"
						[ ] Read()
						[ ] __os_GetCookieExternalData()
						[ ] ip = this.lsData[3]
						[ ] upv = Val (GetField(this.lsData[2], "_", 1))
						[ ] uid = Val(GetField(this.lsData[2],"_", 2))
						[ ] timeStamp = GetField(this.lsData[2],"_", 3)
						[ ] isCalibrated = Val(GetField(this.lsData[2],"_", 4))
						[ ] vpv = Val (GetField(this.lsData[2], "_", 5))
						[ ] disptype = Val(GetField(this.lsData[2], "_", 6))
						[ ] calp1 = GetField(this.lsData[2], "_", 7)
						[ ] calp2 = GetField(this.lsData[2], "_", 8)
						[ ] calp3 = GetField(this.lsData[2], "_", 9)
						[ ] bandwidth = Val (GetField(this.lsData[2], "_", 10))
					[+] mswnt    void   __os_GetCookieExternalData()
						[ ] __browser_GetCookieExternalData()
					[+] explorer void   __browser_GetCookieExternalData()
						[ ] TemporaryInternetFiles.Invoke()
						[ ] integer index = TemporaryInternetFiles.FileList.FindItem("Cookie:{TestSystem.UserName()}@{this.Domain}*")
						[ ] anytype data = TemporaryInternetFiles.FileList.GetItemText(index)
						[ ] anytype data2 = parse(data,";")
						[ ] timeout = data2[5]
						[ ] TemporaryInternetFiles.Close()
					[ ] 
					[ ] 
				[ ] 
			[ ] 
			[ ] // TuneUp does only a default tune up. It does this by making 
			[ ] // two URL loads, rather than using the actual tune up 
			[ ] // interface. The first URL load drops the uncalibrated cookie,
			[ ] // and the second one drops the calibrated cookie. One method:
			[ ] // TuneUp.DoDefaultTuneUp(OBJECT ImageDirector)
			[+] window cBASE TuneUp
				[-] DoDefaultTuneUp(OBJECT ImageDirector)
					[ ] BrowserSupport.OpenPage("http://{EColorServers.CalibrationServer.inifile.CalibrationURL.sValue}/CalibrationServer?Protocol=CSP,100&Method=GetTuneupPage&Customer={ImageDirector.sCustomerID}")
					[ ] BrowserSupport.OpenPage("http://{EColorServers.CalibrationServer.inifile.CalibrationURL.sValue}/CalibrationServer?Protocol=CSP%2C100&Method=SetTuneupResponse&Customer={ImageDirector.sCustomerID}&composite=100_22_22_22_10_10_10_22_22_22&elanguage=english&display=0")
					[ ] BrowserSupport.Close()
					[ ] fCurrentlyTunedUp = TRUE
				[ ] boolean fCurrentlyTunedUp = FALSE
			[ ] 
			[ ] // TestProps is the test properties file, INI file format.
			[ ] // There is more documentation about this in the "Misc Documentation"
			[ ] // section above.
			[+] window cINIFILE TestProps
				[ ] string __sFileName = "C:\ecolor\Image Director\ImageDirectorTest.ini"
				[-] Section TestFlags
					[ ] Key PrintDebugInfo
					[ ] Key KExecuteTestsWhichUseID2
					[ ] Key KExecuteTestsWhichUseFootprint
					[ ] Key KExecuteTestsWhichUseAkamai
					[+] property ExecuteTestsWhichUseID2
						[-] boolean Get()
							[ ] return MakeBool(KExecuteTestsWhichUseID2.sValue)
					[+] property ExecuteTestsWhichUseFootprint
						[-] boolean Get()
							[ ] return MakeBool(KExecuteTestsWhichUseFootprint.sValue)
					[+] property ExecuteTestsWhichUseAkamai
						[-] boolean Get()
							[ ] return MakeBool(KExecuteTestsWhichUseAkamai.sValue)
				[-] Section QALogon
					[ ] Key userid
					[ ] Key password
				[-] Section TestParameters
					[ ] Key Browser
					[ ] Key TuneUpToUse
					[ ] Key StaleTimeout
				[-] Section ImageDirector1
					[ ] Key InternalName
					[ ] Key DomainName
					[ ] Key TestPageURL
					[ ] Key ShareName
					[ ] Key PropertiesFile
					[ ] Key JavaEngineServiceName
					[ ] Key WebServerServiceName
				[-] Section ImageDirector2
					[ ] Key InternalName
					[ ] Key DomainName
					[ ] Key TestPageURL
					[ ] Key ShareName
					[ ] Key PropertiesFile
					[ ] Key JavaEngineServiceName
					[ ] Key WebServerServiceName
				[-] Section ProfileServer
					[ ] Key DomainName
					[ ] Key InternalName
					[ ] Key ShareName
					[ ] Key PropertiesFile
					[ ] Key JavaEngineServiceName
					[ ] Key WebServerServiceName
				[-] Section CalibrationServer
					[ ] Key CalibrationURL
					[ ] Key InternalName
					[ ] Key ShareName
					[ ] Key PropertiesFile
					[ ] Key JavaEngineServiceName
					[ ] Key WebServerServiceName
				[-] Section ImageServer
					[ ] Key DomainName
					[ ] Key InternalName
					[ ] Key ShareName
					[ ] Key PropertiesFile
					[ ] Key JavaEngineServiceName
					[ ] Key WebServerServiceName
				[ ] 
			[ ] 
		[+] // primary
			[ ] 
			[+] // BrowserSupport is intended to be the interface into the broswer. 
				[ ] // Silk provides a browser class, but it doesn't have all the methods we need.
				[ ] //
				[ ] // Invoke()			Launches the browser if it's not running. Sets it active if it is running.
				[ ] // ClearCache()		Clears the cache
				[ ] // ClearCacheAndCookies()	clears the cache and removes the cookies
				[ ] // Close()			Closes all the browser windows
				[ ] // OpenPage()		Types the page number into the location field and presses enter
				[ ] // StartPage()		Launches a browser from the command line with the specified URL 
				[ ] //
				[ ] // SetCookieMode()	Sets cookie security mode - CM_ACCEPT, ,CM_PROMPT, CM_REJECT
				[ ] //					(this code is browser specific, but required. Must be implemented for
				[ ] //					all browsers)
				[ ] //
				[ ] // There are additional interfaces, but they are intended for use within the frameowrk.
				[ ] // Platform specific interfaces:
				[ ] // GetCookieDir() 	Explorer only - returns the cookie dir user shell folder
				[ ] // ZapCookiesAtFileSystem() 	Deletes cookes from the user shell folder for cookies.
				[ ] //
			[ ] // We add functions here that would have been handy to have in the
			[ ] // Browser class that comes with Silk. We could modify Silk's 
			[ ] // Browser class directly, but then when we upgrade to a new version
			[ ] // of Silk we could have complications.
			[+] window 		cBASE BrowserSupport
				[ ] //MOST COMMON FUNCTIONS
				[+] void Invoke()
					[ ] // if browser not open, open it. 
					[-] if ! Browser.bExists
						[ ] BrowserSupport.StartPage("about:blank")
					[ ] // now set it active, and maximize it
					[ ] Browser.SetActive()
					[ ] Browser.Maximize()
				[+] void ClearCache(boolean fReturnState optional)
					[ ] // clear cache, and return browser to state we found it in
					[ ] // (leave open if was open, close if was closed)
					[ ] boolean fOpenOnEntry = Browser.bExists
					[ ] Invoke()
					[ ] Browser.ClearCache()
					[-] if ! fReturnState == NULL
						[-] if ! fOpenOnEntry
							[ ] Browser.Close()
				[+] void ClearCacheAndCookies()
					[ ] 
					[ ] __ClearCacheAndCookies()
					[ ] ZapCookiesAtFileSystem()
					[ ] TuneUp.fCurrentlyTunedUp = FALSE
				[+] void Close()
					[ ] integer i 
					[-] for i = 1 to 20
						[ ] __Close()
				[+] void OpenPage(STRING sURL)
					[ ] Invoke()
					[ ] Browser.Location.TypeKeys ("{sURL}<Enter>")
					[ ] Browser.WaitForReady()
					[ ] Sleep (1)
				[+] void StartPage(STRING sAdditionalCmdLine)
					[ ] APP_Start(Browser.sCmdLine+" "+sAdditionalCmdLine)
					[ ] Browser.WaitForReady()
					[ ] sleep(1)
				[ ] 
				[ ] //PLATFORM SPECIFIC CODE
				[+] mswnt string GetCookieDir()
					[ ] return __GetCookieDir()
				[+] mswnt void   ZapCookiesAtFileSystem()
					[ ] __ZapCookiesAtFileSystem()
				[ ] 
				[ ] //BROWSER SPECIFIC CODE
				[+] explorer5 SetCookieMode(COOKIE_MODE_TYPE NewCookieMode)
					[-] if __CurrentCookieMode != NewCookieMode
						[+] //Make Dialog Up and Active
							[-] if ! IE_Options.DialogBox("Security Settings").bExists
								[-] if ! IE_Options.bExists
									[ ] BrowserSupport.Invoke()
									[ ] Browser.TypeKeys("<Alt-T>O")
								[ ] IE_Options.SetActive ()
								[ ] IE_Options.PageList.Select ("Security")
								[ ] IE_Options.Security.CustomLevel.Click ()
							[ ] IE_Options.DialogBox("Security Settings").SetActive ()
						[-] //expand for code that rolls down to the cookies entry
							[ ] boolean fKeepChecking = TRUE
							[-] while fKeepChecking
								[-] do
									[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Prompt")
									[ ] fKeepChecking = FALSE
								[-] except
									[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").TypeKeys("<down>")
							[ ] 
						[+] switch NewCookieMode
							[-] case CM_REJECT
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Enable")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Prompt")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Disable")
							[-] case CM_ACCEPT
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Disable")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Prompt")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Enable")
							[-] case CM_PROMPT
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Enable")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Disable")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Prompt")
						[ ] IE_Options.DialogBox("Security Settings").PushButton("OK").Click ()
						[ ] BrowserMessage.SetActive ()
						[ ] BrowserMessage.Yes.Click ()
						[ ] IE_Options.SetActive ()
						[ ] IE_Options.OK.Click ()
						[ ] Browser.WaitForReady()
						[ ] Browser.Reload.Click()
						[ ] 
						[+] //Make Dialog Up and Active
							[-] if ! IE_Options.DialogBox("Security Settings").bExists
								[-] if ! IE_Options.bExists
									[ ] BrowserSupport.Invoke()
									[ ] Browser.TypeKeys("<Alt-T>O")
								[ ] IE_Options.SetActive ()
								[ ] IE_Options.PageList.Select ("Security")
								[ ] IE_Options.Security.CustomLevel.Click ()
							[ ] IE_Options.DialogBox("Security Settings").SetActive ()
						[-] //expand for code that rolls down to the cookies entry
							[ ] fKeepChecking = TRUE
							[-] while fKeepChecking
								[-] do
									[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Prompt")
									[ ] fKeepChecking = FALSE
								[-] except
									[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").TypeKeys("<down>")
							[ ] 
						[+] switch NewCookieMode
							[-] case CM_REJECT
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Enable")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Prompt")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Disable")
							[-] case CM_ACCEPT
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Disable")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Prompt")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Enable")
							[-] case CM_PROMPT
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Enable")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Disable")
								[ ] IE_Options.DialogBox("Security Settings").TreeView("Settings:").Select ("/Cookies/Allow cookies that are stored on your computer/Prompt")
						[ ] IE_Options.DialogBox("Security Settings").PushButton("OK").Click ()
						[ ] BrowserMessage.SetActive ()
						[ ] BrowserMessage.Yes.Click ()
						[ ] IE_Options.SetActive ()
						[ ] IE_Options.OK.Click ()
						[ ] Browser.WaitForReady()
						[ ] Browser.Reload.Click()
						[ ] Browser.Close()
						[ ] 
					[ ] __CurrentCookieMode = NewCookieMode
				[ ] explorer5 string CookieMarkers = "[]"
				[ ] explorer4 string CookieMarkers = "()"
				[ ] 
				[ ] /////////////////////////////////////////////////////////////////////
				[+] // Class Private
					[ ] 
					[ ] //BROWSER SPECIFIC CLASS PRIVATE CODE
					[-] explorer  void   __ClearCacheAndCookies()
						[ ] TemporaryInternetFiles.ClearContents()
					[+] explorer  STRING __GetCookieDir()
						[ ] return TestSystem.PreCookieDir()+"\Cookies\"
					[+] explorer  void   __ZapCookiesAtFileSystem()
						[ ] TuneUp.fCurrentlyTunedUp = FALSE
						[ ] cEXEFILE("cmd").RunAndWait(' /c echo Y | del "{GetCookieDir()}*.txt"')
					[+] netscape  void	 __ZapCookiesAtFileSystem()
						[ ] __NSCookieFile.Delete()
					[+] netscape  property __NSCookieFile
						[-] object Get()
							[ ] return cTEXTFILE("C:\Program Files\Netscape\{TestSystem.UserName}\cookies.txt")
					[ ] 
					[ ] // OTHER CLASS SPECIFIC PRIVATE CODE
					[+] void __Close()
						[-] do
							[-] if Browser.bExists
								[ ] Browser.Close()
						[-] except
							[-] switch ExceptNum()
								[-] case E_WINDOW_NOT_ACTIVE
									[ ] APP_Start("notepad.exe")
									[ ] sleep(1)
									[ ] MainWin("Notepad*").SetActive()
									[ ] MainWin("Notepad*").Close()
								[-] default
									[ ] reraise
					[ ] COOKIE_MODE_TYPE __CurrentCookieMode = CM_UNSET
					[ ] 
					[ ] 
				[ ] 
			[ ] 
			[+] // cIMAGEDIRECTOR is the class definition for the image director abstraction.
				[ ] // This is the most heavilly used item in this automated test plan.
				[ ] // 
				[ ] // Server			Is an interface into the server at the back end. This class is
				[ ] //					defined above in Secondary Interfaces.
				[ ] // inifile			Is a pointer into the TestProps object - used for fetching the 
				[ ] //					values from the INI file that relate to an instance of this class.
				[ ] // cookie			Container for contents of, and data related to, the customer
				[ ] //					cookie (see Secondary Interfaces)
				[ ] // GetPropertyValue()	Given a string, this method fetches the data from the 
				[ ] //					server properties file that corrisponds to that key.
				[ ] // sCustomerID		This property fetches the customer number from the
				[ ] //					preoprties file.
				[ ] //
				[ ] // MakeUncalibratedCookie()	Opens the hello world page, which causes a cookie
				[ ] //					to be dropped. THIS METHOD CLEARS THE CACHE BEFORE THE PAGE
				[ ] //					IS OPENED.
				[ ] // MakeCalibratedCookie()	Does a tune up, and then makes the cookie object read
				[ ] //					the field data. Does NOT CLEAR THE CACHE.
				[ ] // OpenTestPage()	Opens the test page specified in the INI file. Usually
				[ ] //					james.html
				[ ] // OpenHelloWorldPage() 	Opens the test page, then clicks on Hello World link.
				[ ] // DoDefaultTuneUp()		Calls the TuneUp object's Default Tune Up.
				[ ] // 
				[ ] // SetECNState()	Stops the server, sets the ECN state property, then restarts the
				[ ] //					server. The new state is saved in memory, so that if we're asked
				[ ] //					to reset the state again to the same setting (which might happen
				[ ] //					in the TestCaseEnter function), the code will be smart enough to
				[ ] //					know that it has already set that state, and not stop and restart
				[ ] //					the server unnecessarly.
				[ ] // SetImageWatchdogState()			As with SetECNState, stops server, sets property, restarts.
				[ ] // SetProfileServerWatchdogState()	As above for ProfileServerWatchdog property
				[ ] // SetGeoCacheState()				Are we seeing a pattern here? 
				[ ] // SetGeoCacheAllImgSrcState()		As above, see test plan for discussion of this property
				[ ] // SetGeoCacheProvider()			Switches between Footprint (GP_FOOTPRINT) and Akamai (GP_AKAMAI)
				[ ] // SetGeoCacheStateToDefault()		Special function. By default, when a test script starts,
				[ ] //									the GeoCaching function is set to Off. But since once we 
				[ ] // 									start the GeoCache group, we want to start and stop the
				[ ] //									servers as little as possible, this allows us to redefine 
				[ ] //									the default.
			[ ] // Anything you would do with a browser that is specific to one image
			[ ] // director or the other is contained here... Like open test pages,
			[ ] // verify images and cookies, etc.
			[+] winclass 	cIMAGEDIRECTOR : cBASE
				[ ] // Support
				[+] cSERVERINTERFACE Server	// defined with the other secondary interfaces
					[-] property inifile
						[-] window Get()
							[ ] return TestProps.@(this.__wParent.__sName)
					[ ] 
				[ ] OBJECT inifile 			// pointer into the TestProps file, the section for this ID
				[ ] cCOOKIE cookie			// interfaces to the "current" cookie
				[ ] 
				[ ] // get data about image director
				[+] string 		GetPropertyValue(string parameter)	// gets values from property file
					[ ] return Server.GetPropertyValue(parameter)
				[+] property	sCustomerID							// gets cust ID from property file
					[-] string Get()
						[ ] return GetPropertyValue("TicDispatcher.CustomerId")
				[ ] 
				[ ] // Page Operators - Indirect
				[ ] // these two methods leave browser open
				[+] void		MakeUncalibratedCookie()	// clear cookies, open hello world page
					[ ] BrowserSupport.ClearCacheAndCookies()
					[ ] OpenHelloWorldPage()
					[ ] Browser.WaitForReady()
					[ ] cookie.ReadFields()
				[-] void		MakeCalibratedCookie()		// clear cookies, tune up
					[ ] DoDefaultTuneUp()
					[-] if Browser.bExists
						[ ] Browser.WaitForReady()
					[ ] cookie.ReadFields()
				[ ] 
				[ ] // Page Operators - Direct
				[+] void		OpenTestPage()				// opens test page, usually james.html
					[-] if ! JamesTestPage.bExists
						[ ] BrowserSupport.Close()
						[ ] BrowserSupport.OpenPage("about:blank")
						[ ] BrowserSupport.OpenPage(inifile.TestPageURL.sValue)
				[+] void		OpenHelloWorldPage()		// opens test page and clicks on Hello World link
					[-] do
						[ ] OpenTestPage()
						[ ] Browser.WaitForReady()
						[ ] Browser.SetActive()
						[ ] Agent.FlushEvents()
						[ ] BrowserPage.HtmlLink("Get Hello World Page").Click ()
						[ ] Agent.FlushEvents()
						[ ] SecurityAlert.CheckForAndDismissWindow()
						[ ] Agent.FlushEvents()
					[-] except
						[ ] print(BrowserPage.HtmlLink("Get Hello World Page").WndTag)
						[ ] print(BrowserPage.HtmlLink("Get Hello World Page").bExists)
						[ ] print(WND_GetActive())
						[ ] print(Browser.Exists())
						[ ] print("-----------------------------------------------------")
						[ ] listprint(Browser.GetContents())
						[ ] print("-----------------------------------------------------")
						[ ] listprint(BrowserPage.GetContents())
						[ ] print("-----------------------------------------------------")
						[ ] reraise
				[ ] 
				[ ] // Tune Up Operators
				[+] void		DoDefaultTuneUp()			// does a default tune up
					[ ] TuneUp.DoDefaultTuneUp(this)
				[ ] 
				[ ] // Parameter Set Operators
				[+] SetECNState(boolean fNewState)
					[-] if ! IsSet(__LastSetECNState)
						[ ] __LastSetECNState=FALSE
					[-] if fNewState != __LastSetECNState
						[ ] __SetPropertyAndRestart("TicDispatcher.ECN.Status",fNewState)
						[ ] __LastSetECNState = fNewState
				[+] SetImageServerWatchdogState(boolean fNewState)
					[-] if __ImageServerWatchdogState != fNewState
						[ ] __SetPropertyAndRestart("TicDispatcher.ImageServerWatchdog.Status",fNewState)
						[ ] __ImageServerWatchdogState = fNewState
				[+] SetProfileServerWatchdogState(boolean fNewState)
					[-] if __ProfileServerWatchdogState != fNewState
						[ ] __SetPropertyAndRestart("TicDispatcher.ProfileServerWatchdog.Status",fNewState)
						[ ] __ProfileServerWatchdogState = fNewState
						[ ] 
				[+] SetGeoCacheState(boolean fNewState)
					[-] if fNewState != __CurrentGeoCacheState
						[ ] __SetPropertyAndRestart("GeoCache.EnableTranslation",fNewState)
						[ ] __CurrentGeoCacheState = fNewState
					[ ] 
				[+] SetGeoCacheAllImgSrcState(boolean fNewState)
					[-] if fNewState != __GeoCacheAllImgSrcState
						[ ] __SetPropertyAndRestart("GeoCache.EnableTranslation",fNewState)
						[ ] __GeoCacheAllImgSrcState = fNewState
					[ ] 
				[+] SetGeoCacheProvider(GEOCACHE_PROVIDER_TYPE NewProvider)
					[-] if NewProvider != __CurrentGeoCacheProvider
						[ ] __CurrentGeoCacheProvider = NewProvider
						[-] switch NewProvider
							[-] case GP_AKAMAI
								[ ] __SetPropertyAndRestart("GeoCache.Manager.Class","com.cs.GeoCache.AkamaiGeoCache") 
							[-] case GP_FOOTPRINT
								[ ] __SetPropertyAndRestart("GeoCache.Manager.Class","com.cs.GeoCache.FootprintGeoCache") 
							[-] default
								[ ] raise 1,"ERROR: Invalid Argument to SetGeoCacheProvider: {NewProvider}"
				[ ] 
				[ ] // SetGeoCacheStateToDefault() returns the GeoCache setting to 
				[ ] // whatever it's current default state is. But specifying an argument
				[ ] // will allow you to change what the default is on the fly. This is done
				[ ] // because it takes some time to stop and start the services, so if we 
				[ ] // have GeoCaching off until we're ready to test it, and then change the 
				[ ] // default, it can remain on for the GeoCache block of tests without
				[ ] // having to stop and restart services over and over. TestCaseEnter
				[ ] // calls this function, and initially the default state will be
				[ ] // off. The first of the Akamai tests will change the default state 
				[ ] // to on.
				[+] SetGeoCacheStateToDefault(boolean fNewState optional)
					[-] if fNewState == NULL
						[ ] fNewState = __DefaultGeoCacheState
					[ ] __DefaultGeoCacheState = fNewState
					[ ] SetGeoCacheState(__DefaultGeoCacheState)
				[ ] 
				[ ] // Cookie Update Methods and data
				[ ] // To use this group of methods, you need two sets of data. Cookie before
				[ ] // some action, and cookie after the action. MatchCookie is storage for 
				[ ] // the state before the action, since the cookie property is always the
				[ ] // current cookie data. StoreCurrentCookieData() copies all the values 
				[ ] // from the current cookie to the MatchCookie.
				[ ] cCOOKIE MatchCookie
				[+] StoreCurrentCookieData()
					[ ] MatchCookie.DeepCopyFrom(cookie)
				[+] VerifyCookieTimeoutUpdated()
					[ ] VerifyCookieIDUnchanged()
					[-] if MatchCookie.timeout == this.cookie.timeout
						[ ] print("Cookie timeout before page reload was {MatchCookie.timeout}")
						[ ] print("Cookie timeout after  page reload was {cookie.timeout}")
						[ ] raise 1,"Cookie wasn't updated"
				[+] VerifyCookieTimeoutNotUpdated()
					[ ] VerifyCookieIDUnchanged()
					[-] if MatchCookie.timeout != this.cookie.timeout
						[ ] print("Cookie timeout before page reload was {MatchCookie.timeout}")
						[ ] print("Cookie timeout after  page reload was {cookie.timeout}")
						[ ] raise 1,"Cookie wasn't updated"
				[+] VerifyCookieIDUnchanged()
					[-] if MatchCookie.uid != cookie.uid
						[ ] raise 1,"Cookie user IDs didn't match after stale timeout"
				[ ] 
				[ ] // Cookie Verify Methods
				[+] VerifyCookieExists()
					[ ] cookie.ReadFields()
					[ ] cookie.VerifyCookieExists()
				[+] VerifyCookieDoesNotExist()
					[-] if cookie.bExists
						[ ] raise 1,"ERROR: Cookie exists when not supposed to"
				[+] VerifyCookieIsUncalibrated()
					[ ] VerifyCookieMatchToMaster()
					[-] do
						[-] if cookie.isCalibrated != 0
							[ ] raise 1, "Fail: Customer cookie isCalibrated == {cookie.isCalibrated}"
						[-] if ((val(cookie.calp1) != 0) && (val(cookie.calp2) != 0) && (val(cookie.calp3) != 0))
							[ ] raise 1, "Fail: Customer cookie was calibrated"
					[-] except
						[ ] print("Master Cookie:")
						[ ] EColorServers.cookie._DebugPrint()
						[ ] print("Customer Cookie:")
						[ ] cookie._DebugPrint()
						[ ] reraise
					[ ] VerifyCookieMatchToMaster()
				[+] VerifyCookieIsCalibrated()
					[ ] VerifyCookieMatchToMaster()
					[+] do
						[-] if cookie.isCalibrated == 0 
							[ ] raise 1, "Fail: Customer cookie isCalibrated == {cookie.isCalibrated}"
						[-] if ((cookie.calp1 == "0.0") && (cookie.calp2 == "0.0") && (cookie.calp3 == "0.0"))
							[ ] raise 1, "Fail: Customer cookie was uncalibrated"
					[-] except
						[ ] print("Master Cookie:")
						[ ] EColorServers.cookie._DebugPrint()
						[ ] print("Customer Cookie:")
						[ ] cookie._DebugPrint()
						[ ] reraise
					[ ] VerifyCookieMatchToMaster()
				[+] VerifyCookieMatchToMaster()
					[ ] VerifyCookieExists()
					[ ] EColorServers.VerifyCookieExists()
					[+] do
						[-] if cookie.upv != EColorServers.cookie.upv
							[ ] raise 1, "Fail: Customer cookie profile version does not match Master cookie"
						[-] if cookie.uid != EColorServers.cookie.uid
							[ ] raise 1, "Fail: Customer cookie user id does not match Master cookie"
						[-] if cookie.uid == 0
							[ ] raise 1, "Fail: Customer cookie user id is 0"
						[-] if cookie.isCalibrated != EColorServers.cookie.isCalibrated
							[ ] raise 1, "Fail: Customer cookie isCalibrated does not match Master cookie"
						[-] if cookie.vpv != EColorServers.cookie.vpv
							[ ] raise 1, "Fail: Customer cookie Viewing Profile Version does not match Master cookie"
						[-] if cookie.disptype != EColorServers.cookie.disptype
							[ ] raise 1, "Fail: Customer cookie display type does not match Master cookie"
						[-] if val(cookie.calp1) != val(EColorServers.cookie.calp1)
							[ ] raise 1, "Fail: Customer cookie calibration parameter 1 does not match Master cookie"
						[-] if val(cookie.calp2) != val(EColorServers.cookie.calp2)
							[ ] raise 1, "Fail: Customer cookie calibration parameter 2 does not match Master cookie"
						[-] if val(cookie.calp3) != val(EColorServers.cookie.calp3)
							[ ] raise 1, "Fail: Customer cookie calibration parameter 3 does not match Master cookie"
						[-] if cookie.bandwidth != EColorServers.cookie.bandwidth
							[ ] raise 1, "Fail: Customer cookie profile version does not match Master cookie"
					[-] except
						[ ] print("Master Cookie:")
						[ ] EColorServers.cookie._DebugPrint()
						[ ] print("Customer Cookie:")
						[ ] cookie._DebugPrint()
						[ ] reraise
				[+] VerifyCookieRefreshed()
					[ ] VerifyCookieIDUnchanged()
					[ ] VerifyCookieTimeoutUpdated()
				[+] VerifyCookieNotRefreshed()
					[ ] VerifyCookieIDUnchanged()
					[ ] VerifyCookieTimeoutNotUpdated()
				[ ] 
				[ ] // Other verify Methods NOT related to images
				[+] VerifyTICTitle()
					[-] if ! sContains(Browser.sCaption,"True Internet Color(r)")
						[ ] raise 1,"ERROR: Title bar did not contain 'True Internet Color(r)'"
				[+] VerifyNotTICTitle()
					[-] if sContains(Browser.sCaption,"True Internet Color(r)")
						[ ] raise 1,"ERROR: Title bar contains 'True Internet Color(r)'"
				[ ] 
				[ ] // Image Verify Methods
				[ ] // VerifyImage() is the most common verify function to call. This
				[ ] // method calls the other verify methods based on what the current 
				[ ] // state of all the other variables are. For instance, if GeoCaching
				[ ] // is on, and the image URL indicates that the image is NOT coming
				[ ] // from a GeoCache provider, then we raise an exception. When we do
				[ ] // a tune up, a flag is set that says we're tuned up. When we clear
				[ ] // cache, that flag is cleared. If we do a VerifyImage while tuned
				[ ] // up, and the image URL comes back as not corrected, or average
				[ ] // corrected, then we raise an exception. VerifyImage calls the
				[ ] // other VeryImage...() methods based on the state of the settings
				[ ] // flags.
				[+] VerifyImage()
					[+] if ! HelloWorldPage.bExists		// make sure browser is up
						[ ] raise 1,"ERROR: ImageDirector.VerifyImage() called without browser open to Hello World page"
					[ ] 
					[ ] URL_DATA_TYPE ImageOriginData = ParseURL()
					[ ] 
					[+] if __DefaultGeoCacheState		// if caching on, verify origin
						[-] switch __CurrentGeoCacheProvider
							[-] case GP_AKAMAI
								[ ] VerifyImageFromAkamai(ImageOriginData)
							[-] case GP_FOOTPRINT
								[ ] VerifyImageFromFootprint(ImageOriginData)
							[-] default
								[ ] raise 1,"ERROR: Unknown GeoCache Provider: {__CurrentGeoCacheProvider}"
					[ ] 							
					[+] if TuneUp.fCurrentlyTunedUp
						[ ] // if we're tuned up...
						[ ] // is Image Server running?
						[-] if EColorServers.ImageServer.fServerRunning
							[ ] // verify for full correction
							[ ] VerifyImageFullCorrection()
						[-] else // image server not running
							[ ] // verify for no correction
							[ ] VerifyImageNoCorrection()
					[+] else 						 	// not tuned up
						[ ] // we're not calibrated
						[ ] // are we ECN?
						[-] if __LastSetECNState
							[ ] // verify average correction
							[ ] VerifyImageAverageCorrection()
						[-] else 					   // ECN off
							[ ] // verify no correction
							[ ] VerifyImageNoCorrection()
					[ ] 
					[ ] DebugPrint("Image Verified OK")
				[ ]  
				[+] VerifyImageAverageCorrection (URL_DATA_TYPE ImageData optional)
					[-] if ImageData == NULL
						[ ] ImageData = ParseURL()
					[-] if ! ImageData.fAvgCorr
						[ ] IDebugPrint(ImageData)
						[ ] raise 1, "ERROR: Image was NOT Average Corrected"
				[+] VerifyImageNoCorrection      (URL_DATA_TYPE ImageData optional)
					[-] if ImageData == NULL
						[ ] ImageData = ParseURL()
					[-] if ImageData.fCorrected
						[ ] IDebugPrint(ImageData)
						[ ] raise 1, "ERROR: Image was corrected"
				[+] VerifyImageFullCorrection    (URL_DATA_TYPE ImageData optional)
					[-] if ImageData == NULL
						[ ] ImageData = ParseURL()
					[-] if ! ImageData.fCorrected 
						[ ] IDebugPrint(ImageData)
						[ ] raise 1, "ERROR: Image was not corrected"
					[-] if ImageData.fAvgCorr
						[ ] IDebugPrint(ImageData)
						[ ] raise 1, "ERROR: Image had average correction"
				[+] VerifyImageFromCustomer      (URL_DATA_TYPE ImageData optional)
					[-] if ImageData == NULL
						[ ] ImageData = ParseURL()
					[-] if ! ImageData.fFromCustomer
						[ ] IDebugPrint(ImageData)
						[ ] raise 1, "ERROR: Image was from E-Color"
				[+] VerifyImageFromEColor        (URL_DATA_TYPE ImageData optional)
					[-] if ImageData == NULL
						[ ] ImageData = ParseURL()
					[-] if ImageData.fFromCustomer
						[ ] IDebugPrint(ImageData)
						[ ] raise 1, "ERROR: Image was from Customer"
				[+] VerifyImageFromAkamai        (URL_DATA_TYPE ImageData optional)
					[-] if ImageData == NULL
						[ ] ImageData = ParseURL()
					[-] if ! (ImageData.GeoCacheProvider == GP_AKAMAI)
						[ ] IDebugPrint(ImageData)
						[ ] raise 1, "ERROR: Image was NOT delivered from Akamai"
				[+] VerifyImageFromFootprint     (URL_DATA_TYPE ImageData optional)
					[-] if ImageData == NULL
						[ ] ImageData = ParseURL()
					[-] if ! (ImageData.GeoCacheProvider == GP_FOOTPRINT)
						[ ] IDebugPrint(ImageData)
						[ ] raise 1, "ERROR: Image was NOT delivered from Digital Island"
				[ ] 
				[ ] // Methods to support verification methods
				[+] void 			IDebugPrint(URL_DATA_TYPE ParseResult)
					[ ] print("-------------------------------------------------------")
					[ ] print("Recovered Image Data:")
					[ ] print("fFromCustomer    {ParseResult.fFromCustomer}")
					[ ] print("fFromEColor      {ParseResult.fFromEColor}")
					[ ] print("fGeoCached       {ParseResult.fGeoCached}")
					[ ] print("fCorrected       {ParseResult.fCorrected}")
					[ ] print("fAvgCorr         {ParseResult.fAvgCorr}")
					[ ] print("GeoCacheProvider {ParseResult.GeoCacheProvider}")
					[ ] print("sDomain          {ParseResult.sDomain}")
					[ ] print("")
					[ ] print("Partial URL      {__sLastURL}")
					[ ] print("Full URL         {__sLastFullURL}")
					[ ] 
				[+] string 			GetActualURLForVerify()
					[-] if ! HelloWorldPage.bExists		// make sure browser is up
						[ ] raise 1,"ERROR: ImageDirector.GetActualURLForVerify() called without browser open to Hello World page"
					[ ] 
					[ ] string result = HelloWorldPage.Mandrill2.GetLocation()
					[ ] __sLastURL = result
					[ ] BrowserSupport.OpenPage(result)
					[ ] result = Browser.Location.sValue
					[ ] result = Browser.Location.sValue
					[ ] result = Browser.Location.sValue
					[ ] result = Browser.Location.sValue
					[ ] result = Browser.Location.sValue
					[ ] result = Browser.Location.sValue
					[ ] __sLastFullURL = result
					[ ] Browser.Back.Click()
					[ ] 
					[ ] return result
					[ ] 
					[ ] // from
					[ ] // http://www1.perfectinternetcolor.com/TicImage/public/Mandrill.jpg
					[ ] // Result will look like this...
					[ ] // Full:
					[ ] // http://perfectinternetcolor.imager.trueinternetcolor.com/ImageServer/Protocol_3dCSP_2c100_26Method_3dGetCorrectedImage_26Customer_3d888_26ViewingProfile_3d100_5f1_5f_2d0.282_5f1.645_5f0.0_5f0_26Image_3dhttp_3a_2f_2fwww1.perfectinternetcolor.com_2fpublic_2fMandrill.jpg
					[ ] // Average:
					[ ] // http://perfectinternetcolor.imager.trueinternetcolor.com/ImageServer/Protocol_3dCSP_2c100_26Method_3dGetCorrectedImage_26Customer_3d888_26ViewingProfile_3d100_5f0_5f0.0_5f0.0_5f0.0_5f0_26Image_3dhttp_3a_2f_2fwww1.perfectinternetcolor.com_2fpublic_2fMandrill.jpg
					[ ] 
				[+] URL_DATA_TYPE	ParseURL()
					[-] if ! HelloWorldPage.bExists		// make sure browser is up
						[ ] raise 1,"ERROR: ImageDirector.ParseURL() called without browser open to Hello World page"
					[ ] string sURL = GetActualURLForVerify()
					[ ] URL_DATA_TYPE ParseResult
					[ ] 
					[ ] // defaults
					[ ] ParseResult.fFromCustomer 	= TRUE
					[ ] ParseResult.fFromEColor		= FALSE
					[ ] ParseResult.fGeoCached		= FALSE
					[ ] ParseResult.fCorrected		= FALSE
					[ ] ParseResult.fAvgCorr		= FALSE
					[ ] ParseResult.GeoCacheProvider= GP_NONE
					[ ] ParseResult.sDomain			= "ERROR"
					[ ] string sTemp
					[ ] 
					[ ] sTemp = substr(sURL, 8, 10000)
					[ ] sTemp = substr(sTemp,1,strpos("/",sTemp)-1)
					[ ] ParseResult.sDomain = sTemp
					[ ] 
					[ ] string sFootprintDomain = this.GetPropertyValue("Footprint.Supername.Address")
					[ ] string sAkamaiDomain = "http://"+this.GetPropertyValue("Akamai.Domain")
					[ ] 
					[-] if sContains(sURL, sFootprintDomain) 		// Check for GeoCaching FOOTPRINT
						[ ] ParseResult.GeoCacheProvider = GP_FOOTPRINT
						[ ] ParseResult.fGeoCached = TRUE
					[-] if sContains(sURL, sAkamaiDomain)	// Check for GeoCaching AKAMAI
						[ ] ParseResult.GeoCacheProvider = GP_AKAMAI
						[ ] ParseResult.fGeoCached = TRUE
					[ ] 
					[ ] // From customer? Or E-Color?
					[-] if sContains(sURL, "Protocol_3dCSP")
						[ ] ParseResult.fFromCustomer 	= FALSE
						[ ] ParseResult.fFromEColor		= TRUE
					[ ] 
					[ ] // what kind of correction?
					[ ] // There's a weird thing here where I've seen the Image Server come back with 
					[ ] // two DIFFERENT possible URLs, with different percision. There may need to be
					[ ] // more ORs in this conditional if yet more possible URLs come up. *Sigh*
					[-] if sContains(sURL, "ViewingProfile_3d100_5f0_5f0.0_5f0.0_5f0.0_5f0_26") || sContains(sURL,"ViewingProfile_3d100_5f0_5f0.000_5f0.000_5f0.000_5f0_26")
						[ ] ParseResult.fCorrected		= TRUE
						[ ] ParseResult.fAvgCorr		= TRUE
					[ ] 
					[-] if ! ParseResult.fCorrected				// we know we're not average corrected...
						[ ] // so see if we're fully corrected...
						[-] if sContains(sURL, "Protocol_3dCSP_2c100_26Method_3dGetCorrectedImage_26Customer_3d")
							[ ] ParseResult.fCorrected		= TRUE
					[ ] 
					[+] // sample URLs
						[ ] // from
						[ ] // http://www1.perfectinternetcolor.com/TicImage/public/Mandrill.jpg
						[ ] // Result will look like this...
						[ ] // Full:
						[ ] // http://perfectinternetcolor.imager.trueinternetcolor.com/ImageServer/Protocol_3dCSP_2c100_26Method_3dGetCorrectedImage_26Customer_3d888_26ViewingProfile_3d100_5f1_5f_2d0.282_5f1.645_5f0.0_5f0_26Image_3dhttp_3a_2f_2fwww1.perfectinternetcolor.com_2fpublic_2fMandrill.jpg
						[ ] // Average:
						[ ] // http://perfectinternetcolor.imager.trueinternetcolor.com/ImageServer/Protocol_3dCSP_2c100_26Method_3dGetCorrectedImage_26Customer_3d888_26ViewingProfile_3d100_5f0_5f0.0_5f0.0_5f0.0_5f0_26Image_3dhttp_3a_2f_2fwww1.perfectinternetcolor.com_2fpublic_2fMandrill.jpg
						[ ] // Footprint:
						[ ] // http://perfectinternetcolor.footprint.trueinternetcolor.com/ImageServer/Protocol_3dCSP_2c100_26Method_3dGetCorrectedImage_26Customer_3d888_26ViewingProfile_3d100_5f0_5f0.0_5f0.0_5f0.0_5f0_26Image_3dhttp_3a_2f_2fwww1.perfectinternetcolor.com_2fpublic_2fMandrill.jpg
						[ ] // Akamai:
						[ ] // http://a776.g.akamai.net/7/776/404/10080267/perfectinternetcolor.imager.trueinternetcolor.com/ImageServer/Protocol_3dCSP_2c100_26Method_3dGetCorrectedImage_26Customer_3d888_26ViewingProfile_3d100_5f0_5f
					[ ] 
					[ ] return ParseResult
					[ ] 
				[ ] 
				[ ] /////////////////////////////////////////////////////////////////////
				[+] // Class Private
					[ ] string 	__sLastURL
					[ ] string	__sLastFullURL
					[ ] 
					[ ] boolean __GeoCacheAllImgSrcState = TRUE
					[ ] boolean __CurrentGeoCacheState = FALSE
					[ ] boolean __DefaultGeoCacheState = FALSE
					[ ] INTEGER __CurrentGeoCacheProvider = GP_AKAMAI
					[ ] boolean __ImageServerWatchdogState = TRUE
					[ ] boolean __ProfileServerWatchdogState = TRUE
					[ ] boolean __LastSetECNState
					[-] __SetPropertyAndRestart(string sProperty, anytype NewState)
						[ ] Server.ServerOff()
						[ ] Server.__ParameterChange(sProperty,NewState)
						[ ] Server.ServerOn()
				[ ] 
			[+] window 		cIMAGEDIRECTOR ImageDirector1
				[ ] // the things defined here tell the system where to look in the
				[ ] // TestProps INI file
				[ ] window inifile = TestProps.ImageDirector1
				[+] cCOOKIE cookie
					[ ] string Domain = this.inifile.DomainName.sValue
			[+] window 		cIMAGEDIRECTOR ImageDirector2
				[ ] window inifile = TestProps.ImageDirector2
				[+] cCOOKIE cookie
					[ ] string Domain = this.inifile.DomainName.sValue
			[ ] 
			[ ] // EColorServers represents the entire backend. There are verify methods here
			[ ] // for the cookies generated by the backend, and a WaitForStale method that
			[ ] // sleeps the amount of time specified in the INI file for cookies to go stale.
			[ ] // There are also cSERVERINTERFACE's for the ProfileServer, ImageServer,
			[ ] // AdminServer, and CalibrationServer. I believe that, as of this writing
			[ ] // (5/25/2001), only ImageServer and ProfileServer are used by the test
			[ ] // cases. 
			[+] window 		cBASE EColorServers
				[+] WaitForStale()
					[+] if __iStaleTimeoutInSeconds == 0
						[ ] __iStaleTimeoutInSeconds = val(TestProps.TestParameters.StaleTimeout.sValue)
					[ ] sleep(__iStaleTimeoutInSeconds)
				[ ] 
				[ ] // Cookie managment
				[+] cCOOKIE cookie
					[ ] string Domain =  TestProps.ProfileServer.DomainName.sValue
				[ ] cCOOKIE MatchCookie
				[+] StoreCurrentCookieData()
					[ ] MatchCookie.DeepCopyFrom(cookie)
				[+] VerifyCookieExists()
					[ ] cookie.ReadFields()
					[ ] cookie.VerifyCookieExists()
				[+] VerifyCookieDoesNotExist()
					[-] if cookie.bExists
						[ ] raise 1,"ERROR: Cookie exists when not supposed to"
				[+] VerifyCookieRefreshed()
					[ ] VerifyCookieIDUnchanged()
					[ ] VerifyCookieTimeoutUpdated()
				[+] VerifyCookieNotRefreshed()
					[ ] VerifyCookieIDUnchanged()
					[ ] VerifyCookieTimeoutNotUpdated()
					[ ] 
				[+] VerifyCookieTimeoutUpdated()
					[ ] VerifyCookieIDUnchanged()
					[-] if MatchCookie.timeout == this.cookie.timeout
						[ ] print("Cookie timeout before page reload was {MatchCookie.timeout}")
						[ ] print("Cookie timeout after  page reload was {cookie.timeout}")
						[ ] raise 1,"Cookie wasn't updated"
				[+] VerifyCookieTimeoutNotUpdated()
					[ ] VerifyCookieIDUnchanged()
					[-] if MatchCookie.timeout != this.cookie.timeout
						[ ] print("Cookie timeout before page reload was {MatchCookie.timeout}")
						[ ] print("Cookie timeout after  page reload was {cookie.timeout}")
						[ ] raise 1,"Cookie wasn't updated"
				[+] VerifyCookieIDUnchanged()
					[-] if MatchCookie.uid != cookie.uid
						[ ] raise 1,"Cookie user IDs didn't match after stale timeout"
				[ ] 
				[ ] // EColor Servers
				[ ] cSERVERINTERFACE ProfileServer
				[ ] cSERVERINTERFACE ImageServer
				[ ] cSERVERINTERFACE AdminServer
				[ ] cSERVERINTERFACE CalibrationServer
				[ ] 
				[ ] integer __iStaleTimeoutInSeconds = 0
	[ ] 
	[+] //other window definitions
		[+] window BrowserChild JamesTestPage
			[ ] tag "James' Test Page"
			[ ] parent Browser
			[+] HtmlHeading JamesTestPage
				[ ] tag "James' Test Page"
			[+] HtmlLink GetHelloWorldPage
				[ ] tag "Get Hello World Page"
			[+] HtmlLink CalibrationTuneUp1
				[ ] tag "Calibration TuneUp 1"
			[+] HtmlLink CalibrationTuneUp2
				[ ] tag "Calibration TuneUp 2"
			[+] HtmlLink ImageAdminOnTicqasvr5Qacol
				[ ] tag "Image Admin on ticqasvr5.qacolor.com"
		[-] mswnt window DialogBox TemporaryInternetFiles
			[+] Invoke()
				[ ] STRING sUserProfileDir = cSystem.GetEnv("userprofile")
				[ ] STRING sTempINetFilesDir = sUserProfileDir+"\Local Settings\Temporary Internet Files\"
				[+] if ! bExists
					[ ] APP_Start('explorer.exe "{sTempINetFilesDir}"')
					[ ] sleep(3)
				[+] if ! bExists
					[ ] APP_Start('explorer.exe "{sTempINetFilesDir}"')
					[ ] sleep(3)
				[+] if ! IsActive()
					[ ] SetActive()
					[ ] sleep(1)
				[+] if ! IsActive()
					[ ] SetActive()
					[ ] sleep(1)
				[ ] 
			[+] ClearContents()
				[ ] //raise 1		// this is here to disable cookie cleanup, for debugging
				[ ] Invoke()
				[ ] sleep(1)
				[ ] this.TypeKeys("<F5>")
				[ ] sleep(1)
				[ ] this.TypeKeys("<F5>")
				[ ] sleep(1)
				[ ] this.TypeKeys("<Ctrl-a>")
				[ ] sleep(1)
				[ ] this.typeKeys("<Delete>")
				[ ] sleep(1)
				[-] if DELETE_WARNING.bExists
					[-] do
						[ ] DELETE_WARNING.Yes.Click()
					[-] except
						[ ] print(WND_GetActive())
						[ ] reraise
				[ ] Close()
				[ ] TuneUp.fCurrentlyTunedUp = FALSE
				[ ] 
			[ ] 
			[+] DialogBox DELETE_WARNING
				[ ] tag "WARNING"
				[+] PushButton Yes
					[ ] tag "Yes"
				[+] PushButton No
					[ ] tag "No"
				[-] CustomWin Icon1
					[ ] tag "[Icon]#1"
				[+] StaticText AreYouSureYouWantToDelet
					[ ] tag "Are you sure you want to delete the selected Cookie(s) ?"
				[-] CustomWin NativeFontCtl1
					[ ] tag "[NativeFontCtl]#1"
			[ ] 
			[ ] tag "Temporary Internet Files"
			[+] CustomWin MenuBarPane
				[ ] tag "Temporary Internet Files"
				[-] CustomWin MenuBars
					[ ] tag "Temporary Internet Files"
					[+] ComboBox ComboBox1
						[ ] tag "Temporary Internet Files"
					[-] CustomWin WorkerW1
						[ ] tag "Temporary Internet Files"
					[+] ToolBar ToolBar1
						[ ] tag "Temporary Internet Files"
						[+] PushButton Back
							[ ] tag "Temporary Internet Files"
						[+] PushButton Forward
							[ ] tag "Temporary Internet Files"
						[+] PushButton Up
							[ ] tag "Temporary Internet Files"
						[+] PushButton Refresh
							[ ] tag "Temporary Internet Files"
						[+] PushButton Folders
							[ ] tag "Temporary Internet Files"
						[+] PushButton Undo
							[ ] tag "Temporary Internet Files"
						[+] PushButton Views
							[ ] tag "Temporary Internet Files"
					[-] ToolBar MenuBar
						[ ] tag "Temporary Internet Files"
						[+] PushButton File
							[ ] tag "Temporary Internet Files"
						[+] PushButton Edit
							[ ] tag "Temporary Internet Files"
						[+] PushButton View
							[ ] tag "Temporary Internet Files"
						[+] PushButton Favorites
							[ ] tag "Temporary Internet Files"
						[+] PushButton Tools
							[ ] tag "Temporary Internet Files"
						[+] PushButton Help
							[ ] tag "Temporary Internet Files"
			[+] StatusBar StatusBar1
				[ ] tag "Temporary Internet Files"
				[+] DynamicText DynamicText1
					[ ] tag "Temporary Internet Files"
				[+] DynamicText DynamicText2
					[ ] tag "Temporary Internet Files"
			[+] ListView FileList
				[ ] tag "#1"
				[+] Header Header1
					[ ] tag "Temporary Internet Files"
					[+] PushButton Name
						[ ] tag "Temporary Internet Files"
					[+] PushButton InternetAddress
						[ ] tag "Temporary Internet Files"
					[+] PushButton Type
						[ ] tag "Temporary Internet Files"
					[+] PushButton Size
						[ ] tag "Temporary Internet Files"
					[+] PushButton Expires
						[ ] tag "Temporary Internet Files"
					[+] PushButton LastModified
						[ ] tag "Temporary Internet Files"
					[+] PushButton LastAccessed
						[ ] tag "Temporary Internet Files"
					[+] PushButton LastChecked
						[ ] tag "Temporary Internet Files"
			[ ] 
		[+] mswnt window DialogBox CookieProperties
			[ ] tag "Cookie:* Properties"
			[ ] parent TemporaryInternetFiles
			[+] DialogBox General
				[ ] tag "General"
				[+] CustomWin Icon1
					[ ] tag "[Icon]#1"
				[+] CustomWin EtchedHorz1
					[ ] tag "[EtchedHorz]#1"
				[+] StaticText TypeText
					[ ] tag "Type:"
				[+] StaticText TXTFileText
					[ ] tag "TXT File"
				[+] StaticText SizeText
					[ ] tag "Size:"
				[+] StaticText N110BytesText
					[ ] tag "110 bytes"
				[+] CustomWin Size
					[ ] tag "[EtchedHorz]Size:"
				[+] StaticText CacheNameText
					[ ] tag "Cache name:"
				[+] StaticText AmaciainQacolor2TxtText
					[ ] tag "amaciain@qacolor?2?.txt"
				[+] StaticText ExpiresText
					[ ] tag "Expires:"
				[+] StaticText N442021311PMText
					[ ] tag "4?4?2021 3:11 PM"
				[+] StaticText LastModifiedText
					[ ] tag "Last Modified:"
				[+] StaticText N492001311PM1Text
					[ ] tag "4?9?2001 3:11 PM[1]"
				[+] StaticText LastAccessedText
					[ ] tag "Last Accessed:"
				[+] StaticText N492001311PM2Text
					[ ] tag "4?9?2001 3:11 PM[2]"
				[+] TextField TextField1
					[ ] tag "#1"
				[+] CustomWin NativeFontCtl1
					[ ] tag "[NativeFontCtl]#1"
			[+] PushButton OK
				[ ] tag "OK"
			[+] PushButton Cancel
				[ ] tag "Cancel"
			[+] PageList PageList1
				[ ] tag "#1"
		[+] window DialogBox SecurityAlert
			[+] void VerifyDidAppear()
				[-] if ! SecurityAlert.fDidAppear
					[ ] raise 1,"ERROR: Security Alert Dialog did not appear when it was supposed to!"
			[+] void VerifyDidNotAppear()
				[-] if SecurityAlert.fDidAppear
					[ ] raise 1,"ERROR: Security Alert Dialog appeared when it was not supposed to!"
			[ ] 
			[ ] boolean fDidAppear = FALSE
			[+] void CheckForAndDismissWindow()
				[ ] fDidAppear = FALSE
				[-] do 
					[-] if bExists
						[ ] Yes.Click()
						[ ] fDidAppear = TRUE
					[-] else
						[ ] sleep(5)
						[-] if bExists
							[ ] Yes.Click()
							[ ] fDidAppear = TRUE
					[-] if bExists
						[ ] Yes.Click()
						[ ] fDidAppear = TRUE
					[-] else
						[ ] sleep(5)
						[+] if bExists
							[ ] Yes.Click()
							[ ] fDidAppear = TRUE
					[-] if bExists
						[ ] Yes.Click()
						[ ] fDidAppear = TRUE
					[-] else
						[ ] sleep(5)
						[+] if bExists
							[ ] Yes.Click()
							[ ] fDidAppear = TRUE
				[-] except
					[ ] //bite me.
			[ ] 
			[ ] tag "Security Alert"
			[ ] parent Browser
			[+] PushButton Yes
				[ ] tag "Yes"
			[+] PushButton No
				[ ] tag "No"
			[+] CustomWin Icon1
				[ ] msw tag "[Icon]#1"
			[+] StaticText ToProvideAMorePersonalized
				[ ] tag "To provide a more personalized browsing experience, will you allow this Web site to save a small file (called a cookie) on you*"
			[+] CheckBox InTheFutureDoNotShowThi
				[ ] tag "In the future, do not show this warning"
			[+] PushButton MoreInfo
				[ ] tag "More Info"
			[+] StaticText CookieInformationText
				[ ] tag "Cookie Information"
			[+] TextField Secure2
				[ ] tag "Secure[2]"
			[+] StaticText NameText
				[ ] tag "Name"
			[+] TextField CookieInformation
				[ ] tag "Cookie Information"
			[+] StaticText DomainText
				[ ] tag "Domain"
			[+] StaticText PathText
				[ ] tag "Path"
			[+] StaticText DataText
				[ ] tag "Data"
			[+] StaticText ExpiresText
				[ ] tag "Expires"
			[+] TextField Domain
				[ ] tag "Domain"
			[+] TextField Path
				[ ] tag "Path"
			[+] TextField Expires
				[ ] tag "Expires"
			[+] StaticText SecureText
				[ ] tag "Secure"
			[+] TextField Secure1
				[ ] tag "Secure[1]"
		[+] window BrowserChild HelloWorldPage
			[ ] 
			[ ] tag "Hello World Page*"
			[ ] parent Browser
			[+] HtmlText HelloWorld
				[ ] tag "Hello World"
			[+] HtmlText GreenSweatshirt1
				[ ] tag "Green Sweatshirt"
			[+] HtmlImage GreenSweatshirt2
				[ ] tag "Green Sweatshirt"
			[+] HtmlText Mandrill1
				[ ] tag "Mandrill"
			[+] HtmlImage Mandrill2
				[ ] tag "Mandrill"
			[+] HtmlText ECNEColorButton1
				[ ] tag "ECN E-Color button"
			[+] HtmlImage ECNEColorButton2
				[ ] tag "ECN E-Color button"
			[+] HtmlText OldEColorButton1
				[ ] tag "Old E-Color button"
			[+] HtmlImage OldEColorButton2
				[ ] tag "Old E-Color button"
	[ ] 
	[+] //enumerations used herein
		[+] type URL_DATA_TYPE is record
			[ ] boolean						fFromCustomer
			[ ] boolean						fFromEColor
			[ ] boolean						fGeoCached
			[ ] boolean						fCorrected
			[ ] boolean						fAvgCorr
			[ ] GEOCACHE_PROVIDER_TYPE		GeoCacheProvider
			[ ] string 						sDomain
		[+] type COOKIE_MODE_TYPE is enum
			[ ] CM_ACCEPT
			[ ] CM_PROMPT
			[ ] CM_REJECT
			[ ] // unset should always be the last one
			[ ] CM_UNSET
		[+] type GEOCACHE_PROVIDER_TYPE is enum
			[ ] GP_AKAMAI
			[ ] GP_FOOTPRINT
			[ ] // unset should always be the last one
			[ ] GP_NONE
			[ ] GP_UNSET
	[ ] 
	[+] //Other stuff
		[+] window cBASE TestSystem
			[+] string PreCookieDir()
				[ ] return UserProfileDir()
			[+] string UserProfileDir()
				[ ] return cSystem.GetEnv("userprofile")
			[+] string UserName()
				[ ] return cSystem.GetEnv("username")
			[+] property UserName 
				[-] string Get()
					[ ] return UserName()
		[+] void	DebugPrint(anytype thingie)
			[-] if ! IsSet(fDebug)
				[ ] fDebug = MakeBool(TestProps.TestFlags.PrintDebugInfo.sValue)
			[-] if fDebug
				[-] if IsList(thingie)
					[ ] listprint(thingie)
				[-] else
					[ ] print(thingie)
	[ ] 
	[+] //Obsolete code
		[+] //tune up
			[+] window cBASE OldTuneUp
				[+] DoDefaultTuneUp(OBJECT ImageDirector)
					[ ] BrowserSupport.OpenPage("http://{EColorServers.CalibrationServer.inifile.CalibrationURL.sValue}/CalibrationServer?Protocol=CSP,100&Method=GetTuneupPage&Customer={ImageDirector.sCustomerID}")
					[ ] BrowserSupport.OpenPage("http://{EColorServers.CalibrationServer.inifile.CalibrationURL.sValue}/CalibrationServer?Protocol=CSP%2C100&Method=SetTuneupResponse&Customer={ImageDirector.sCustomerID}&composite=100_22_22_22_10_10_10_22_22_22&elanguage=english&display=0")
					[ ] BrowserSupport.Close()
					[ ] fCurrentlyTunedUp = TRUE
				[+] OldDoDefaultTuneUp(OBJECT ImageDirector)
					[-] select
						[-] case TestProps.TestParameters.TuneUpToUse.sValue == "1"
							[ ] DoTuneUp(ImageDirector, {12,12,12},{6,6,6},{12,12,12})
						[-] case TestProps.TestParameters.TuneUpToUse.sValue == "2"
							[ ] DoTuneUp(ImageDirector, {12,12,12},{12,12,12},6)
						[-] default
							[ ] raise 1,"TUNE UP TYPE NOT SPECIFIED CORRECTLY IN INI FILE"
					[ ] 
				[+] void DoTuneUp(OBJECT ImageDirector, list of integer a, list of integer b, anytype c)
					[-] select
						[-] case TestProps.TestParameters.TuneUpToUse.sValue == "1"
							[ ] TuneUp1.DoTuneUp(ImageDirector, a, b, c)
						[-] case TestProps.TestParameters.TuneUpToUse.sValue == "2"
							[ ] TuneUp2.DoTuneUp(ImageDirector, a, b, c)
						[ ] // put additional tune ups here
						[-] default
							[ ] raise 1,"TUNE UP TYPE NOT SPECIFIED CORRECTLY IN INI FILE"
					[ ] this.fCurrentlyTunedUp = TRUE
					[ ] 
				[ ] 
				[ ] boolean fCurrentlyTunedUp = FALSE
			[+] //Tune Up 1
				[ ] //NON WINDOW RELATED CODE FOR TUNE UP 1
				[+] window cBASE TuneUp1
					[+] DoTuneUp(OBJECT ImageDirector, list of integer shad, list of integer black, list of integer high)
						[ ] OpenPage1(ImageDirector)
						[ ] TuneUp1Page1.Next()
						[ ] TuneUp1Page2.DoPage(shad[1],shad[2],shad[3])
						[ ] TuneUp1Page3.DoPage(black[1],black[2],black[3])
						[ ] TuneUp1Page4.DoPage(high[1],high[2],high[3])
						[ ] TuneUp1Page5.Close()
					[+] OpenPage1(OBJECT PassedImageDirector)
						[ ] PassedImageDirector.OpenTestPage()
						[ ] Browser.WaitForReady()
						[ ] BrowserPage.SetActive ()
						[ ] BrowserPage.HtmlLink("Calibration TuneUp 1").Click ()
					[ ] 
					[ ] 
					[ ] 
				[ ] //WHEN RERECORDING, THIS WINDOW MUST REMAIN AN ANYWIN!
				[+] window AnyWin TrueInternetColorRSetup
					[ ] tag "True Internet Color(r) - Setup*" // (r) - Setup - Microsoft Internet Explorer
					[+] StatusBar StatusBar1
						[ ] tag "#1"
						[-] DynamicText DynamicText1
							[ ] tag "#1"
						[-] DynamicText DynamicText2
							[ ] tag "#2"
						[-] DynamicText DynamicText3
							[ ] tag "#3"
						[-] DynamicText DynamicText4
							[ ] tag "#4"
						[-] DynamicText DynamicText5
							[ ] tag "#5"
				[+] window BrowserChild TuneUp1Page1 // Adjust bright
					[+] void Next()
						[ ] __NextButton.Click()
					[ ] window __NextButton = BrowserChild1.JavascriptGoToNextPage 
					[ ] //RECORDED WINDOW DECLARATION
					[ ] tag "#1"
					[ ] parent TrueInternetColorRSetup
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] HtmlImage HtmlImage1
							[ ] tag "#1"
						[+] HtmlImage HtmlImage2
							[ ] tag "#2"
						[+] HtmlImage HtmlImage3
							[ ] tag "#3"
						[+] HtmlImage HtmlImage4
							[ ] tag "#4"
						[+] HtmlText SetYourBrightnessControlO1
							[ ] tag "Set your Brightness control  on your"
						[+] HtmlImage SetYourBrightnessControlO2
							[ ] tag "Set your Brightness control  on your"
						[+] HtmlText ThenReduceTheBrightnessCon
							[ ] tag "Then reduce the Brightness control set"
						[+] HtmlImage HtmlImage6
							[ ] tag "#6"
						[+] HtmlText UntilTheFurthest
							[ ] tag "until the furthest"
						[+] HtmlImage JavascriptCancel
							[ ] tag "javascript:Cancel();"
						[+] HtmlImage JavascriptGoToNextPage
							[ ] tag "javascript:GoToNextPage();"
						[+] HtmlText IfYouHaveALaptopOr
							[ ] tag "If you have a laptop or"
						[+] HtmlLink Register
							[ ] tag "register"
						[+] HtmlLink Cancel
							[ ] tag "cancel"
						[+] HtmlImage CalibrationServer
							[ ] tag "CalibrationServer"
					[ ] 
				[+] window BrowserChild TuneUp1Page2 // Shadows - values 1 thru 23
					[+] void DoPage(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.SelectBRG(iBlue, iRed, iGreen)
						[ ] this.Next()
					[+] void SelectBRG(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.Blue(iBlue)
						[ ] this.Red(iRed)
						[ ] this.Green(iGreen)
					[+] void Blue(integer Index)	// INDEX 1 thru 23
						[ ] __DoClick(__BlueBar,Index)
					[+] void Red(integer Index)
						[ ] __DoClick(__RedBar,Index)
					[+] void Green(integer Index)
						[ ] __DoClick(__GreenBar,Index)
					[+] void Next()
						[ ] __NextButton.Click()
					[+] //EXPAND FOR INTERNALS
						[+] void __DoClick(window ItemToClick, integer index)
							[-] if index == 0 || index > __MaxIndexValue 
								[ ] raise 1, "Parameter out of bounds"
							[ ] index = index-1
							[ ] integer iVLoc = __VStart + (__VInterval*index)
							[ ] ItemToClick.Click(1,__HLocation, iVLoc)
						[ ] INTEGER __MaxIndexValue = 23 
						[ ] INTEGER __VStart    = 15
						[ ] INTEGER __VInterval = 18
						[ ] INTEGER __HLocation = 58
						[ ] window __NextButton = BrowserChild1.BrowserChild5.JavascriptGoToNextPage
						[ ] window __BlueBar = BrowserChild1.BrowserChild2.HtmlImage1
						[ ] window __RedBar = BrowserChild1.BrowserChild3.HtmlImage1
						[ ] window __GreenBar = BrowserChild1.BrowserChild4.HtmlImage1
					[ ] //RECORDED WINDOW DECLARATION
					[ ] tag "#1"
					[ ] parent TrueInternetColorRSetup
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] BrowserChild BrowserChild1
							[ ] tag "#1"
						[+] BrowserChild BrowserChild2	// blue
							[ ] tag "#2"
							[+] HtmlImage HtmlImage1
								[ ] tag "#1"
							[+] // Toolbar style co-ordinates - didn't work. Wrote support 3/29/01
								[+] // HtmlImage Blue1
									[ ] // tag "#1/(1:1, 1:26)"
								[+] // HtmlImage Blue2
									[ ] // tag "#1/(1:1, 2:26)"
								[+] // HtmlImage Blue3
									[ ] // tag "#1/(1:1, 3:26)"
								[+] // HtmlImage Blue4
									[ ] // tag "#1/(1:1, 4:26)"
								[+] // HtmlImage Blue5
									[ ] // tag "#1/(1:1, 5:26)"
								[+] // HtmlImage Blue6
									[ ] // tag "#1/(1:1, 6:26)"
								[+] // HtmlImage Blue7
									[ ] // tag "#1/(1:1, 7:26)"
								[+] // HtmlImage Blue8
									[ ] // tag "#1/(1:1, 8:26)"
								[+] // HtmlImage Blue9
									[ ] // tag "#1/(1:1, 9:26)"
								[+] // HtmlImage Blue10
									[ ] // tag "#1/(1:1, 10:26)"
								[+] // HtmlImage Blue11
									[ ] // tag "#1/(1:1, 11:26)"
								[+] // HtmlImage Blue12
									[ ] // tag "#1/(1:1, 12:26)"
								[+] // HtmlImage Blue13
									[ ] // tag "#1/(1:1, 13:26)"
								[+] // HtmlImage Blue14
									[ ] // tag "#1/(1:1, 14:26)"
								[+] // HtmlImage Blue15
									[ ] // tag "#1/(1:1, 15:26)"
								[+] // HtmlImage Blue16
									[ ] // tag "#1/(1:1, 16:26)"
								[+] // HtmlImage Blue17
									[ ] // tag "#1/(1:1, 17:26)"
								[+] // HtmlImage Blue18
									[ ] // tag "#1/(1:1, 18:26)"
								[+] // HtmlImage Blue19
									[ ] // tag "#1/(1:1, 19:26)"
								[+] // HtmlImage Blue20
									[ ] // tag "#1/(1:1, 20:26)"
								[+] // HtmlImage Blue21
									[ ] // tag "#1/(1:1, 21:26)"
								[+] // HtmlImage Blue22
									[ ] // tag "#1/(1:1, 22:26)"
								[+] // HtmlImage Blue23
									[ ] // tag "#1/(1:1, 23:26)"
								[+] // HtmlImage Blue24
									[ ] // tag "#1/(1:1, 24:26)"
								[+] // HtmlImage Blue25
									[ ] // tag "#1/(1:1, 25:26)"
								[+] // HtmlImage Blue26
									[ ] // tag "#1/(1:1, 26:26)"
						[+] BrowserChild BrowserChild3
							[ ] tag "#3"
							[-] HtmlImage HtmlImage1
								[ ] tag "#1"
						[+] BrowserChild BrowserChild4
							[ ] tag "#4"
							[-] HtmlImage HtmlImage1
								[ ] tag "#1"
						[+] BrowserChild BrowserChild5
							[ ] tag "#5"
							[+] HtmlImage HtmlImage1
								[ ] tag "#1"
							[+] HtmlImage HtmlImage2
								[ ] tag "#2"
							[+] HtmlImage HtmlImage3
								[ ] tag "#3"
							[+] HtmlText ForEachColorClickOnThe
								[ ] tag "For each color, click on the"
							[+] HtmlImage JavascriptGoToPreviousPage
								[ ] tag "javascript:GoToPreviousPage();"
							[+] HtmlImage JavascriptGoToNextPage
								[ ] tag "javascript:GoToNextPage();"
							[+] HtmlHeading TIP
								[ ] tag "TIP:"
							[+] HtmlText SquintingMakesItEasy
								[ ] tag "Squinting makes it easy!"
							[+] HtmlImage Panel33
								[ ] tag "panel33#"
						[+] BrowserChild BrowserChild6
							[ ] tag "#6"
						[+] BrowserChild BrowserChild7
							[ ] tag "#7"
				[+] window BrowserChild TuneUp1Page3 // Blackpoint - values 1 thru 12
					[+] void DoPage(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.SelectBRG(iBlue, iRed, iGreen)
						[ ] this.Next()
					[+] void SelectBRG(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.Blue(iBlue)
						[ ] this.Red(iRed)
						[ ] this.Green(iGreen)
					[+] void Blue(integer Index)	// INDEX 1 thru 12
						[ ] __DoClick(__BlueBar,Index)
					[+] void Red(integer Index)
						[ ] __DoClick(__RedBar,Index)
					[+] void Green(integer Index)
						[ ] __DoClick(__GreenBar,Index)
					[+] void Next()
						[ ] __NextButton.Click()
					[+] //EXPAND FOR INTERNALS
						[+] void __DoClick(window ItemToClick, integer index)
							[+] if index == 0 || index > __MaxIndexValue
								[ ] raise 1, "Parameter out of bounds"
							[ ] index = index-1
							[ ] integer iVLoc = __VStart + (__VInterval*index)
							[ ] ItemToClick.Click(1,__HLocation, iVLoc)
						[ ] INTEGER __MaxIndexValue = 12
						[ ] INTEGER __VStart    = 15
						[ ] INTEGER __VInterval = 36
						[ ] INTEGER __HLocation = 58
						[ ] window __NextButton = BrowserChild1.BrowserChild5.JavascriptGoToNextPage
						[ ] window __BlueBar = BrowserChild1.BrowserChild2.HtmlImage1
						[ ] window __RedBar = BrowserChild1.BrowserChild3.HtmlImage1
						[ ] window __GreenBar = BrowserChild1.BrowserChild4.HtmlImage1
					[ ] //RECORDED WINDOW DECLARATION
					[ ] tag "#1"
					[ ] parent TrueInternetColorRSetup
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] BrowserChild BrowserChild1
							[ ] tag "#1"
						[-] BrowserChild BrowserChild2
							[ ] tag "#2"
							[-] HtmlImage HtmlImage1
								[ ] tag "#1"
						[+] BrowserChild BrowserChild3
							[ ] tag "#3"
							[+] HtmlImage HtmlImage1
								[ ] tag "#1"
						[+] BrowserChild BrowserChild4
							[ ] tag "#4"
							[+] HtmlImage HtmlImage1
								[ ] tag "#1"
						[+] BrowserChild BrowserChild5
							[ ] tag "#5"
							[+] HtmlImage HtmlImage1
								[ ] tag "#1"
							[+] HtmlImage HtmlImage2
								[ ] tag "#2"
							[+] HtmlImage HtmlImage3
								[ ] tag "#3"
							[+] HtmlText ClickOnTheBlueRedAnd
								[ ] tag "Click on the blue, red and"
							[+] HtmlImage JavascriptGoToPreviousPage
								[ ] tag "javascript:GoToPreviousPage();"
							[+] HtmlImage JavascriptGoToNextPage
								[ ] tag "javascript:GoToNextPage();"
							[+] HtmlHeading TIP
								[ ] tag "TIP:"
							[+] HtmlText TheBlueRedAndGreenColumn
								[ ] tag "The blue, red and green columns"
							[+] HtmlImage Bppanel
								[ ] tag "bppanel#"
						[+] BrowserChild BrowserChild6
							[ ] tag "#6"
						[+] BrowserChild BrowserChild7
							[ ] tag "#7"
				[+] window BrowserChild TuneUp1Page4 // Highlights - values 1 thru 23
					[+] void DoPage(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.SelectBRG(iBlue, iRed, iGreen)
						[ ] this.Next()
					[+] void SelectBRG(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.Blue(iBlue)
						[ ] this.Red(iRed)
						[ ] this.Green(iGreen)
					[+] void Blue(integer Index)	// INDEX 1 thru 23
						[ ] __DoClick(__BlueBar,Index)
					[+] void Red(integer Index)
						[ ] __DoClick(__RedBar,Index)
					[+] void Green(integer Index)
						[ ] __DoClick(__GreenBar,Index)
					[+] void Next()
						[ ] __NextButton.Click()
					[+] //EXPAND FOR INTERNALS
						[+] void __DoClick(window ItemToClick, integer index)
							[+] if index == 0 || index > __MaxIndexValue 
								[ ] raise 1, "Parameter out of bounds"
							[ ] index = index-1
							[ ] integer iVLoc = __VStart + (__VInterval*index)
							[ ] ItemToClick.Click(1,__HLocation, iVLoc)
						[ ] INTEGER __MaxIndexValue = 23 
						[ ] INTEGER __VStart    = 15
						[ ] INTEGER __VInterval = 18
						[ ] INTEGER __HLocation = 58
						[ ] window __NextButton = BrowserChild1.BrowserChild5.JavascriptGoToNextPage
						[ ] window __BlueBar = BrowserChild1.BrowserChild2.HtmlImage1
						[ ] window __RedBar = BrowserChild1.BrowserChild3.HtmlImage1
						[ ] window __GreenBar = BrowserChild1.BrowserChild4.HtmlImage1
					[ ] //RECORDED WINDOW DECLARATION
					[ ] tag "#1"
					[ ] parent TrueInternetColorRSetup
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] BrowserChild BrowserChild1
							[ ] tag "#1"
						[+] BrowserChild BrowserChild2
							[ ] tag "#2"
							[+] HtmlImage HtmlImage1
								[ ] tag "#1"
						[+] BrowserChild BrowserChild3
							[ ] tag "#3"
							[+] HtmlImage HtmlImage1
								[ ] tag "#1"
						[+] BrowserChild BrowserChild4
							[ ] tag "#4"
							[+] HtmlImage HtmlImage1
								[ ] tag "#1"
						[+] BrowserChild BrowserChild5
							[ ] tag "#5"
							[+] HtmlImage HtmlImage1
								[ ] tag "#1"
							[+] HtmlImage HtmlImage2
								[ ] tag "#2"
							[+] HtmlImage HtmlImage3
								[ ] tag "#3"
							[+] HtmlText ForEachColorClickOnThe
								[ ] tag "For each color, click on the"
							[+] HtmlImage JavascriptGoToPreviousPage
								[ ] tag "javascript:GoToPreviousPage();"
							[+] HtmlImage JavascriptGoToNextPage
								[ ] tag "javascript:GoToNextPage();"
							[+] HtmlHeading TIP
								[ ] tag "TIP:"
							[+] HtmlText ThisIsTheLastStepDonT
								[ ] tag "This is the last step. Don't"
							[+] HtmlText Squint
								[ ] tag "squint."
							[+] HtmlImage Panel66
								[ ] tag "panel66#"
						[+] BrowserChild BrowserChild6
							[ ] tag "#6"
						[+] BrowserChild BrowserChild7
							[ ] tag "#7"
				[+] window AnyWin CongratulationsTrueInternet
					[ ] //RECORDED WINDOW DECLARATION
					[ ] tag "Congratulations! True Internet Color(r) - Complete - Microsoft Internet Explorer"
				[+] window BrowserChild TuneUp1Page5 // Closing Page
					[+] void Close()
						[ ] Finish.Click()
						[ ] sleep(1)
						[-] if HTTP404NotFoundMicrosoft.bExists
							[ ] HTTP404NotFoundMicrosoft.Close()
					[ ] //RECORDED WINDOW DECLARATION
					[ ] tag "#1"
					[ ] parent CongratulationsTrueInternet
					[+] HtmlImage FREETrueInternetColorIcon1
						[ ] tag "FREE True Internet Color Icon (optional)"
					[+] HtmlText FREETrueInternetColorIcon2
						[ ] tag "FREE True Internet Color Icon (optional)"
					[+] HtmlText DownloadTheTrueInternetCol1
						[ ] tag "Download the True Internet Color Indicator"
					[+] HtmlImage HtmlImage2
						[ ] tag "#2"
					[+] HtmlImage DownloadTheTrueInternetCol2
						[ ] tag "Download the True Internet Color Indicator"
					[+] HtmlText WhenYouSeeThisSymbolYou
						[ ] tag "When you see this symbol:  you"
					[+] HtmlImage HtmlImage4
						[ ] tag "#4"
					[+] HtmlText CongratulationsYouReNowS
						[ ] tag "Congratulations - you're now set up"
					[+] HtmlText SymbolTheColorOnYour
						[ ] tag "symbol:  , the color on your"
					[+] HtmlText ByRegisteringYouWillRecei
						[ ] tag "By registering, you will receive valuable"
					[+] HtmlRadioList HtmlRadioList1
						[ ] tag "#1"
					[+] HtmlText RegistrationOptional
						[ ] tag "Registration (optional)"
					[+] HtmlImage Finish
						[ ] tag "finish"
					[+] HtmlText TellUsMoreAndWeWill
						[ ] tag "Tell us more and we will"
					[+] HtmlText Bandwidth1
						[ ] tag "Bandwidth:"
					[+] HtmlPopupList Bandwidth2
						[ ] tag "Bandwidth:"
					[+] HtmlTextField Email1
						[ ] tag "Email:"
					[+] HtmlText Email2
						[ ] tag "Email:"
					[+] HtmlText Gender1
						[ ] tag "Gender:"
					[+] HtmlRadioList Gender2
						[ ] tag "Gender:"
					[+] HtmlTextField Age1
						[ ] tag "Age:"
					[+] HtmlText Age2
						[ ] tag "Age:"
					[+] HtmlTextField ZipPostalCode1
						[ ] tag "Zip ? Postal Code:"
					[+] HtmlText ZipPostalCode2
						[ ] tag "Zip ? Postal Code:"
				[+] window AnyWin HTTP404NotFoundMicrosoft
					[+] Close()
						[-] if bExists
							[ ] WND_SetActive(this.WndTag)
							[ ] TypeKeys("<Alt-F4>")
					[ ] //RECORDED WINDOW DECLARATION
					[ ] tag "HTTP 404 Not Found - *"
				[ ] 
			[+] //Tune Up 2
				[+] Window cBASE TuneUp2
					[+] DoTuneUp(OBJECT ImageDirector, list of integer blend1, list of integer blend2, integer dark)
						[ ] OpenPage1(ImageDirector)
						[ ] TuneUp2Page1.CRT()
						[ ] TuneUp2Page2.Next()
						[ ] TuneUp2Page3.Next()
						[ ] TuneUp2Page4.DoPage(blend1[1],blend1[2],blend1[3])
						[ ] TuneUp2Page5.DoPage(blend2[1],blend2[2],blend2[3])
						[ ] TuneUp2Page6.DoPage(dark)
						[ ] TuneUp2Page7.Close()
					[+] OpenPage1(OBJECT PassedImageDirector)
						[ ] PassedImageDirector.OpenTestPage()
						[ ] Browser.WaitForReady()
						[ ] BrowserPage.SetActive ()
						[ ] BrowserPage.HtmlLink("Calibration TuneUp 2").Click ()
				[+] window AnyWin EColorMicrosoftInternetE
					[ ] tag "E-Color - Microsoft Internet Explorer"
				[+] window BrowserChild TuneUp2Page1			// page1	CRT/LCD
					[+] void CRT() 
						[ ] BrowserChild1.Ecolor1e1.Click()
					[+] void Next()
						[ ] CRT()
					[ ] tag "#1"
					[ ] parent EColorMicrosoftInternetE
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] HtmlImage HtmlImage1
							[ ] tag "#1"
						[+] HtmlImage HtmlImage2
							[ ] tag "#2"
						[+] HtmlImage HtmlImage3
							[ ] tag "#3"
						[+] HtmlImage HtmlImage4
							[ ] tag "#4"
						[+] HtmlHeading IsYourColorCorrect
							[ ] tag "Is your color correct?"
						[+] HtmlImage HtmlImage5
							[ ] tag "#5"
						[+] HtmlImage HtmlImage6
							[ ] tag "#6"
						[+] HtmlImage HtmlImage7
							[ ] tag "#7"
						[+] HtmlText MakeSureProductsOnThisWeb
							[ ] tag "Make sure products on this website"
						[+] HtmlText TakesOneMinuteNoDownload
							[ ] tag "Takes one minute, no download, doesn't"
						[+] HtmlTable HtmlTable1
							[ ] tag "#1"
							[+] HtmlColumn HtmlColumn1
								[ ] tag "#1"
								[+] HtmlImage HtmlImage1
									[ ] tag "#1"
							[+] HtmlColumn HtmlColumn2
								[ ] tag "#2"
								[+] HtmlImage HtmlImage1
									[ ] tag "#1"
						[+] HtmlImage HtmlImage8
							[ ] tag "#8"
						[+] HtmlImage HtmlImage9
							[ ] tag "#9"
						[+] HtmlText ClickOnThePictureThatRepr
							[ ] tag "Click on the picture that represents"
						[+] HtmlImage Ecolor1e1
							[ ] tag "ecolor1e#[1]"
						[+] HtmlImage Ecolor1e2
							[ ] tag "ecolor1e#[2]"
						[+] HtmlImage HtmlImage12
							[ ] tag "#12"
						[+] HtmlText OnceYouVeCompletedThisOne
							[ ] tag "Once you've completed this one-time Tune-up,"
						[+] HtmlText CRT
							[ ] tag "CRT"
						[+] HtmlText ClickForLaptopOrFlatPanel
							[ ] tag "Click for laptop or flat panel"
						[+] HtmlImage Ecolor1e3
							[ ] tag "ecolor1e#[3]"
						[+] HtmlImage HtmlImage14
							[ ] tag "#14"
						[+] HtmlImage Ecolor1e4
							[ ] tag "ecolor1e#[4]"
						[+] HtmlImage Ecolor1e5
							[ ] tag "ecolor1e#[5]"
						[+] HtmlImage Ecolor1e6
							[ ] tag "ecolor1e#[6]"
				[+] window BrowserChild TuneUp2Page2			// CRTPage2	Brightness
					[+] void Next()
						[ ] BrowserChild1.Ecolor2_english3.Click()
					[ ] tag "#1"
					[ ] parent EColorMicrosoftInternetE
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] HtmlImage HtmlImage1
							[ ] tag "#1"
						[+] HtmlImage HtmlImage2
							[ ] tag "#2"
						[+] HtmlImage HtmlImage3
							[ ] tag "#3"
						[+] HtmlHeading MaximumBrightness
							[ ] tag "Maximum Brightness"
						[+] HtmlImage HtmlImage4
							[ ] tag "#4"
						[+] HtmlText Step1Of5
							[ ] tag "step 1 of 5"
						[+] HtmlImage SomeMonitorsHaveOnScreen1
							[ ] tag "Some monitors have on-screen"
						[+] HtmlText AdjustTheBrightnessControl
							[ ] tag "Adjust the brightness control on your"
						[+] HtmlText SomeMonitorsHaveOnScreen2
							[ ] tag "Some monitors have on-screen"
						[+] HtmlText MenusActivatedByButtons
							[ ] tag "menus activated by buttons"
						[+] HtmlText OnTheFaceOrOnA
							[ ] tag "on the face, or on a"
						[+] HtmlText ConsoleThatAdjustBrightnes1
							[ ] tag "console, that adjust brightness."
						[+] HtmlImage HtmlImage6
							[ ] tag "#6"
						[+] HtmlText IndicatesBrightness
							[ ] tag "Indicates brightness"
						[+] HtmlImage ConsoleThatAdjustBrightnes2
							[ ] tag "console, that adjust brightness."
						[+] HtmlText SeeTheInstructionsToTheRi
							[ ] tag "See the instructions to the right"
						[+] HtmlText AdjustToMaximum1
							[ ] tag "Adjust to maximum[1]"
						[+] HtmlImage SomeMonitorsHaveKnobsOr1
							[ ] tag "Some monitors have knobs or"
						[+] HtmlText SomeMonitorsHaveKnobsOr2
							[ ] tag "Some monitors have knobs or"
						[+] HtmlText ButtonsOnTheFaceThat
							[ ] tag "buttons on the face that"
						[+] HtmlText ClickNextToContinue
							[ ] tag "Click next to continue."
						[+] HtmlText DirectlyAdjustBrightness1
							[ ] tag "directly adjust brightness."
						[+] HtmlImage DirectlyAdjustBrightness2
							[ ] tag "directly adjust brightness."
						[+] HtmlText AdjustToMaximum2
							[ ] tag "Adjust to maximum[2]"
						[+] HtmlImage Ecolor2_english1
							[ ] tag "ecolor2_english#[1]"
						[+] HtmlImage HtmlImage11
							[ ] tag "#11"
						[+] HtmlImage Ecolor2_english2
							[ ] tag "ecolor2_english#[2]"
						[+] HtmlImage Ecolor2_english3
							[ ] tag "ecolor2_english#[3]"
						[+] HtmlImage HtmlImage14
							[ ] tag "#14"
				[+] window BrowserChild TuneUp2Page3			// CRTPage3	Adjust Brightness
					[+] void Next()
						[ ] BrowserChild1.Ecolor312.Click()
					[ ] tag "#1"
					[ ] parent EColorMicrosoftInternetE
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] HtmlImage HtmlImage1
							[ ] tag "#1"
						[+] HtmlImage HtmlImage2
							[ ] tag "#2"
						[+] HtmlImage HtmlImage3
							[ ] tag "#3"
						[+] HtmlHeading AdjustBrightness
							[ ] tag "Adjust Brightness"
						[+] HtmlImage HtmlImage4
							[ ] tag "#4"
						[+] HtmlImage AdjustBrightness1
							[ ] tag "Adjust Brightness[1]"
						[+] HtmlImage Ecolor31
							[ ] tag "ecolor3#[1]"
						[+] HtmlImage AdjustBrightness2
							[ ] tag "Adjust Brightness[2]"
						[+] HtmlText Step2Of5
							[ ] tag "step 2 of 5"
						[+] HtmlText LocateTheDarkestBarThatIs
							[ ] tag "Locate the darkest bar that is"
						[+] HtmlImage HtmlImage8
							[ ] tag "#8"
						[+] HtmlImage Ecolor32
							[ ] tag "ecolor3#[2]"
						[+] HtmlImage HtmlImage10
							[ ] tag "#10"
						[+] HtmlImage HtmlImage11
							[ ] tag "#11"
						[+] HtmlImage Ecolor33
							[ ] tag "ecolor3#[3]"
						[+] HtmlImage HtmlImage13
							[ ] tag "#13"
						[+] HtmlText ReduceTheBrightnessControl
							[ ] tag "Reduce the brightness control until the"
						[+] HtmlImage HtmlImage14
							[ ] tag "#14"
						[+] HtmlImage Ecolor34
							[ ] tag "ecolor3#[4]"
						[+] HtmlImage HtmlImage16
							[ ] tag "#16"
						[+] HtmlImage HtmlImage17
							[ ] tag "#17"
						[+] HtmlImage HtmlImage18
							[ ] tag "#18"
						[+] HtmlImage Ecolor35
							[ ] tag "ecolor3#[5]"
						[+] HtmlImage HtmlImage20
							[ ] tag "#20"
						[+] HtmlText Or
							[ ] tag "or"
						[+] HtmlImage Or1
							[ ] tag "or[1]"
						[+] HtmlImage Or2
							[ ] tag "or[2]"
						[+] HtmlImage Ecolor36
							[ ] tag "ecolor3#[6]"
						[+] HtmlImage Or3
							[ ] tag "or[3]"
						[+] HtmlImage HtmlImage25
							[ ] tag "#25"
						[+] HtmlImage Ecolor37
							[ ] tag "ecolor3#[7]"
						[+] HtmlImage HtmlImage27
							[ ] tag "#27"
						[+] HtmlImage HtmlImage28
							[ ] tag "#28"
						[+] HtmlImage Ecolor38
							[ ] tag "ecolor3#[8]"
						[+] HtmlImage HtmlImage30
							[ ] tag "#30"
						[+] HtmlText ClickNextToContinue
							[ ] tag "Click next to continue."
						[+] HtmlImage HtmlImage31
							[ ] tag "#31"
						[+] HtmlImage Ecolor39
							[ ] tag "ecolor3#[9]"
						[+] HtmlImage HtmlImage33
							[ ] tag "#33"
						[+] HtmlImage Ecolor310
							[ ] tag "ecolor3#[10]"
						[+] HtmlImage ClickNextToContinue1
							[ ] tag "Click next to continue.[1]"
						[+] HtmlImage Ecolor311
							[ ] tag "ecolor3#[11]"
						[+] HtmlImage Ecolor312
							[ ] tag "ecolor3#[12]"
						[+] HtmlImage ClickNextToContinue2
							[ ] tag "Click next to continue.[2]"
				[+] window BrowserChild TuneUp2Page4			// CRTPage4	Color Blend Part 1
					[+] void DoPage(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.SelectBRG(iBlue, iRed, iGreen)
						[ ] this.Next()
					[+] void SelectBRG(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.Blue(iBlue)
						[ ] this.Red(iRed)
						[ ] this.Green(iGreen)
					[+] void Blue(integer Index)	// INDEX 1 thru 23
						[ ] __DoClick(__BlueBar, Index)
					[+] void Red(integer Index)
						[ ] __DoClick(__RedBar, Index)
					[+] void Green(integer Index)
						[ ] __DoClick(__GreenBar, Index)
					[+] void Next()
						[ ] __NextButton.Click()
					[-] //INTERNALS
						[+] void __DoClick(window WindowToClick, INTEGER Index)
							[+] if Index == 0 || Index > __MaxIndex 
								[ ] raise 1, "Parameter out of bounds"
							[ ] Index = Index-1
							[ ] integer iVLoc = __VStart + (__VInterval*Index)
							[ ] WindowToClick.Click(1,__HLocation, iVLoc)
						[ ] window  __BlueBar  = BrowserChild1.HtmlImage7
						[ ] window  __RedBar   = BrowserChild1.HtmlImage4
						[ ] window  __GreenBar = BrowserChild1.HtmlImage5
						[ ] window  __NextButton = BrowserChild1.Ecolor4a3
						[ ] INTEGER __MaxIndex = 23
						[ ] INTEGER __VStart    = 9
						[ ] INTEGER __VInterval = 18
						[ ] INTEGER __HLocation = 48
						[ ] 
					[ ] //WINDOW DECLARATION AS RECORDED
					[ ] tag "#1"
					[-] parent EColorMicrosoftInternetE
						[ ] 
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] HtmlImage HtmlImage1
							[ ] tag "#1"
						[+] HtmlImage HtmlImage2
							[ ] tag "#2"
						[+] HtmlImage HtmlImage3
							[ ] tag "#3"
						[+] HtmlImage HtmlImage4
							[ ] tag "#4"
						[+] HtmlImage HtmlImage5
							[ ] tag "#5"
						[+] HtmlImage HtmlImage6
							[ ] tag "#6"
						[+] HtmlImage HtmlImage7
							[ ] tag "#7"
						[+] HtmlImage HtmlImage8
							[ ] tag "#8"
						[+] HtmlImage HtmlImage9
							[ ] tag "#9"
						[+] HtmlImage HtmlImage10
							[ ] tag "#10"
						[+] HtmlImage HtmlImage11
							[ ] tag "#11"
						[+] HtmlImage HtmlImage12
							[ ] tag "#12"
						[+] HtmlImage HtmlImage13
							[ ] tag "#13"
						[+] HtmlImage HtmlImage14
							[ ] tag "#14"
						[+] HtmlImage HtmlImage15
							[ ] tag "#15"
						[+] HtmlImage HtmlImage16
							[ ] tag "#16"
						[+] HtmlImage HtmlImage17
							[ ] tag "#17"
						[+] HtmlImage HtmlImage18
							[ ] tag "#18"
						[+] HtmlImage HtmlImage19
							[ ] tag "#19"
						[+] HtmlTable HtmlTable1
							[ ] tag "#1"
							[+] HtmlColumn HtmlColumn1
								[ ] tag "#1"
							[+] HtmlColumn HtmlColumn2
								[ ] tag "#2"
								[+] HtmlImage HtmlImage1
									[ ] tag "#1"
								[+] HtmlImage HtmlImage2
									[ ] tag "#2"
						[+] HtmlImage HtmlImage20
							[ ] tag "#20"
						[+] HtmlImage HtmlImage21
							[ ] tag "#21"
						[+] HtmlImage HtmlImage22
							[ ] tag "#22"
						[+] HtmlImage HtmlImage23
							[ ] tag "#23"
						[+] HtmlImage HtmlImage24
							[ ] tag "#24"
						[+] HtmlImage HtmlImage25
							[ ] tag "#25"
						[+] HtmlImage HtmlImage26
							[ ] tag "#26"
						[+] HtmlImage HtmlImage27
							[ ] tag "#27"
						[+] HtmlImage HtmlImage28
							[ ] tag "#28"
						[+] HtmlImage HtmlImage29
							[ ] tag "#29"
						[+] HtmlImage HtmlImage30
							[ ] tag "#30"
						[+] HtmlImage HtmlImage31
							[ ] tag "#31"
						[+] HtmlImage HtmlImage32
							[ ] tag "#32"
						[+] HtmlImage HtmlImage33
							[ ] tag "#33"
						[+] HtmlImage HtmlImage34
							[ ] tag "#34"
						[+] HtmlImage HtmlImage35
							[ ] tag "#35"
						[+] HtmlImage HtmlImage36
							[ ] tag "#36"
						[+] HtmlText ClickOnTheSquareInEach
							[ ] tag "Click on the square in each"
						[+] HtmlImage HtmlImage37
							[ ] tag "#37"
						[+] HtmlImage HtmlImage38
							[ ] tag "#38"
						[+] HtmlImage HtmlImage39
							[ ] tag "#39"
						[+] HtmlImage HtmlImage40
							[ ] tag "#40"
						[+] HtmlImage HtmlImage41
							[ ] tag "#41"
						[+] HtmlImage HtmlImage42
							[ ] tag "#42"
						[+] HtmlImage HtmlImage43
							[ ] tag "#43"
						[+] HtmlImage HtmlImage44
							[ ] tag "#44"
						[+] HtmlImage HtmlImage45
							[ ] tag "#45"
						[+] HtmlImage HtmlImage46
							[ ] tag "#46"
						[+] HtmlImage HtmlImage47
							[ ] tag "#47"
						[+] HtmlImage HtmlImage48
							[ ] tag "#48"
						[+] HtmlImage HtmlImage49
							[ ] tag "#49"
						[+] HtmlImage HtmlImage50
							[ ] tag "#50"
						[+] HtmlImage HtmlImage51
							[ ] tag "#51"
						[+] HtmlImage HtmlImage52
							[ ] tag "#52"
						[+] HtmlImage HtmlImage53
							[ ] tag "#53"
						[+] HtmlImage HtmlImage54
							[ ] tag "#54"
						[+] HtmlImage HtmlImage55
							[ ] tag "#55"
						[+] HtmlImage HtmlImage56
							[ ] tag "#56"
						[+] HtmlImage HtmlImage57
							[ ] tag "#57"
						[+] HtmlImage HtmlImage58
							[ ] tag "#58"
						[+] HtmlImage HtmlImage59
							[ ] tag "#59"
						[+] HtmlImage HtmlImage60
							[ ] tag "#60"
						[+] HtmlText ClickTheSquareInTheGreen
							[ ] tag "Click the square in the green"
						[+] HtmlText SquintYourEyesToMakeBlend
							[ ] tag "Squint your eyes to make blending"
						[+] HtmlImage HtmlImage61
							[ ] tag "#61"
						[+] HtmlImage HtmlImage62
							[ ] tag "#62"
						[+] HtmlImage HtmlImage63
							[ ] tag "#63"
						[+] HtmlImage HtmlImage64
							[ ] tag "#64"
						[+] HtmlImage HtmlImage65
							[ ] tag "#65"
						[+] HtmlImage HtmlImage66
							[ ] tag "#66"
						[+] HtmlImage HtmlImage67
							[ ] tag "#67"
						[+] HtmlImage HtmlImage68
							[ ] tag "#68"
						[+] HtmlImage HtmlImage69
							[ ] tag "#69"
						[+] HtmlImage HtmlImage70
							[ ] tag "#70"
						[+] HtmlImage HtmlImage71
							[ ] tag "#71"
						[+] HtmlImage HtmlImage72
							[ ] tag "#72"
						[+] HtmlImage HtmlImage73
							[ ] tag "#73"
						[+] HtmlImage HtmlImage74
							[ ] tag "#74"
						[+] HtmlImage HtmlImage75
							[ ] tag "#75"
						[+] HtmlImage HtmlImage76
							[ ] tag "#76"
						[+] HtmlImage HtmlImage77
							[ ] tag "#77"
						[+] HtmlImage HtmlImage78
							[ ] tag "#78"
						[+] HtmlText Example1
							[ ] tag "Example:"
						[+] HtmlImage HtmlImage79
							[ ] tag "#79"
						[+] HtmlImage HtmlImage80
							[ ] tag "#80"
						[+] HtmlImage HtmlImage81
							[ ] tag "#81"
						[+] HtmlImage HtmlImage82
							[ ] tag "#82"
						[+] HtmlImage HtmlImage83
							[ ] tag "#83"
						[+] HtmlImage HtmlImage84
							[ ] tag "#84"
						[+] HtmlImage Example2
							[ ] tag "Example:"
						[+] HtmlImage HtmlImage86
							[ ] tag "#86"
						[+] HtmlImage HtmlImage87
							[ ] tag "#87"
						[+] HtmlImage HtmlImage88
							[ ] tag "#88"
						[+] HtmlImage HtmlImage89
							[ ] tag "#89"
						[+] HtmlImage HtmlImage90
							[ ] tag "#90"
						[+] HtmlImage HtmlImage91
							[ ] tag "#91"
						[+] HtmlImage HtmlImage92
							[ ] tag "#92"
						[+] HtmlImage HtmlImage93
							[ ] tag "#93"
						[+] HtmlImage HtmlImage94
							[ ] tag "#94"
						[+] HtmlImage HtmlImage95
							[ ] tag "#95"
						[+] HtmlImage HtmlImage96
							[ ] tag "#96"
						[+] HtmlImage HtmlImage97
							[ ] tag "#97"
						[+] HtmlImage HtmlImage98
							[ ] tag "#98"
						[+] HtmlImage HtmlImage99
							[ ] tag "#99"
						[+] HtmlImage HtmlImage100
							[ ] tag "#100"
						[+] HtmlImage HtmlImage101
							[ ] tag "#101"
						[+] HtmlImage HtmlImage102
							[ ] tag "#102"
						[+] HtmlImage HtmlImage103
							[ ] tag "#103"
						[+] HtmlImage HtmlImage104
							[ ] tag "#104"
						[+] HtmlImage HtmlImage105
							[ ] tag "#105"
						[+] HtmlImage HtmlImage106
							[ ] tag "#106"
						[+] HtmlImage HtmlImage107
							[ ] tag "#107"
						[+] HtmlImage HtmlImage108
							[ ] tag "#108"
						[+] HtmlImage HtmlImage109
							[ ] tag "#109"
						[+] HtmlImage HtmlImage110
							[ ] tag "#110"
						[+] HtmlImage HtmlImage111
							[ ] tag "#111"
						[+] HtmlImage HtmlImage112
							[ ] tag "#112"
						[+] HtmlImage HtmlImage113
							[ ] tag "#113"
						[+] HtmlImage HtmlImage114
							[ ] tag "#114"
						[+] HtmlImage HtmlImage115
							[ ] tag "#115"
						[+] HtmlImage HtmlImage116
							[ ] tag "#116"
						[+] HtmlImage HtmlImage117
							[ ] tag "#117"
						[+] HtmlImage HtmlImage118
							[ ] tag "#118"
						[+] HtmlImage HtmlImage119
							[ ] tag "#119"
						[+] HtmlImage HtmlImage120
							[ ] tag "#120"
						[+] HtmlImage HtmlImage121
							[ ] tag "#121"
						[+] HtmlImage HtmlImage122
							[ ] tag "#122"
						[+] HtmlImage HtmlImage123
							[ ] tag "#123"
						[+] HtmlImage HtmlImage124
							[ ] tag "#124"
						[+] HtmlImage HtmlImage125
							[ ] tag "#125"
						[+] HtmlImage HtmlImage126
							[ ] tag "#126"
						[+] HtmlImage HtmlImage127
							[ ] tag "#127"
						[+] HtmlImage HtmlImage128
							[ ] tag "#128"
						[+] HtmlImage HtmlImage129
							[ ] tag "#129"
						[+] HtmlImage HtmlImage130
							[ ] tag "#130"
						[+] HtmlImage HtmlImage131
							[ ] tag "#131"
						[+] HtmlImage HtmlImage132
							[ ] tag "#132"
						[+] HtmlImage HtmlImage133
							[ ] tag "#133"
						[+] HtmlText ClickNextToContinue
							[ ] tag "Click next to continue."
						[+] HtmlImage HtmlImage134
							[ ] tag "#134"
						[+] HtmlImage HtmlImage135
							[ ] tag "#135"
						[+] HtmlImage HtmlImage136
							[ ] tag "#136"
						[+] HtmlImage HtmlImage137
							[ ] tag "#137"
						[+] HtmlImage HtmlImage138
							[ ] tag "#138"
						[+] HtmlImage HtmlImage139
							[ ] tag "#139"
						[+] HtmlImage HtmlImage140
							[ ] tag "#140"
						[+] HtmlImage HtmlImage141
							[ ] tag "#141"
						[+] HtmlImage HtmlImage142
							[ ] tag "#142"
						[+] HtmlImage HtmlImage143
							[ ] tag "#143"
						[+] HtmlImage HtmlImage144
							[ ] tag "#144"
						[+] HtmlImage HtmlImage145
							[ ] tag "#145"
						[+] HtmlImage Ecolor4a1
							[ ] tag "ecolor4a#[1]"
						[+] HtmlImage ClickNextToContinue1
							[ ] tag "Click next to continue.[1]"
						[+] HtmlImage ClickNextToContinue2
							[ ] tag "Click next to continue.[2]"
						[+] HtmlImage ClickNextToContinue3
							[ ] tag "Click next to continue.[3]"
						[+] HtmlImage ClickNextToContinue4
							[ ] tag "Click next to continue.[4]"
						[+] HtmlImage Ecolor4a2
							[ ] tag "ecolor4a#[2]"
						[+] HtmlImage Ecolor4a3
							[ ] tag "ecolor4a#[3]"
						[+] HtmlImage ClickNextToContinue5
							[ ] tag "Click next to continue.[5]"
					[+] // BrowserChild BrowserChild1  // tuneup 2.1
						[ ] // tag "#1"
						[+] // HtmlImage HtmlImage1
							[ ] // tag "#1"
						[+] // HtmlImage HtmlImage2
							[ ] // tag "#2"
						[+] // HtmlImage HtmlImage3
							[ ] // tag "#3"
						[+] // HtmlImage HtmlImage4
							[ ] // tag "#4"
						[+] // HtmlImage HtmlImage5
							[ ] // tag "#5"
						[+] // HtmlImage HtmlImage6
							[ ] // tag "#6"
						[+] // HtmlImage Ecolor4a1
							[ ] // tag "ecolor4a#[1]"
						[+] // HtmlImage Ecolor4a2
							[ ] // tag "ecolor4a#[2]"
						[+] // HtmlImage Ecolor4a3
							[ ] // tag "ecolor4a#[3]"
						[+] // HtmlImage HtmlImage10
							[ ] // tag "#10"
						[+] // HtmlImage HtmlImage11
							[ ] // tag "#11"
						[+] // HtmlImage HtmlImage12
							[ ] // tag "#12"
						[+] // HtmlImage HtmlImage13
							[ ] // tag "#13"
						[+] // HtmlImage HtmlImage14
							[ ] // tag "#14"
						[+] // HtmlImage HtmlImage15
							[ ] // tag "#15"
						[+] // HtmlImage HtmlImage16
							[ ] // tag "#16"
						[+] // HtmlImage HtmlImage17
							[ ] // tag "#17"
						[+] // HtmlImage HtmlImage18
							[ ] // tag "#18"
						[+] // HtmlImage HtmlImage19
							[ ] // tag "#19"
						[+] // HtmlImage HtmlImage20
							[ ] // tag "#20"
						[+] // HtmlImage HtmlImage21
							[ ] // tag "#21"
						[+] // HtmlTable HtmlTable1
							[ ] // tag "#1"
							[+] // HtmlColumn HtmlColumn1
								[ ] // tag "#1"
							[+] // HtmlColumn HtmlColumn2
								[ ] // tag "#2"
								[+] // HtmlImage HtmlImage1
									[ ] // tag "#1"
								[+] // HtmlImage HtmlImage2
									[ ] // tag "#2"
						[+] // HtmlImage HtmlImage22
							[ ] // tag "#22"
						[+] // HtmlImage HtmlImage23
							[ ] // tag "#23"
						[+] // HtmlImage HtmlImage24
							[ ] // tag "#24"
						[+] // HtmlImage HtmlImage25
							[ ] // tag "#25"
						[+] // HtmlImage HtmlImage26
							[ ] // tag "#26"
						[+] // HtmlImage HtmlImage27
							[ ] // tag "#27"
						[+] // HtmlImage HtmlImage28
							[ ] // tag "#28"
						[+] // HtmlImage HtmlImage29
							[ ] // tag "#29"
						[+] // HtmlImage HtmlImage30
							[ ] // tag "#30"
						[+] // HtmlImage HtmlImage31
							[ ] // tag "#31"
						[+] // HtmlImage HtmlImage32
							[ ] // tag "#32"
						[+] // HtmlImage HtmlImage33
							[ ] // tag "#33"
						[+] // HtmlImage HtmlImage34
							[ ] // tag "#34"
						[+] // HtmlImage HtmlImage35
							[ ] // tag "#35"
						[+] // HtmlImage HtmlImage36
							[ ] // tag "#36"
						[+] // HtmlImage HtmlImage37
							[ ] // tag "#37"
						[+] // HtmlImage HtmlImage38
							[ ] // tag "#38"
						[+] // HtmlText ClickOnTheSquareInEach
							[ ] // tag "Click on the square in each"
						[+] // HtmlImage HtmlImage39
							[ ] // tag "#39"
						[+] // HtmlImage HtmlImage40
							[ ] // tag "#40"
						[+] // HtmlImage HtmlImage41
							[ ] // tag "#41"
						[+] // HtmlImage HtmlImage42
							[ ] // tag "#42"
						[+] // HtmlImage HtmlImage43
							[ ] // tag "#43"
						[+] // HtmlImage HtmlImage44
							[ ] // tag "#44"
						[+] // HtmlImage HtmlImage45
							[ ] // tag "#45"
						[+] // HtmlImage HtmlImage46
							[ ] // tag "#46"
						[+] // HtmlImage HtmlImage47
							[ ] // tag "#47"
						[+] // HtmlImage HtmlImage48
							[ ] // tag "#48"
						[+] // HtmlImage HtmlImage49
							[ ] // tag "#49"
						[+] // HtmlImage HtmlImage50
							[ ] // tag "#50"
						[+] // HtmlImage HtmlImage51
							[ ] // tag "#51"
						[+] // HtmlImage HtmlImage52
							[ ] // tag "#52"
						[+] // HtmlImage HtmlImage53
							[ ] // tag "#53"
						[+] // HtmlImage HtmlImage54
							[ ] // tag "#54"
						[+] // HtmlImage HtmlImage55
							[ ] // tag "#55"
						[+] // HtmlImage HtmlImage56
							[ ] // tag "#56"
						[+] // HtmlImage HtmlImage57
							[ ] // tag "#57"
						[+] // HtmlImage HtmlImage58
							[ ] // tag "#58"
						[+] // HtmlImage HtmlImage59
							[ ] // tag "#59"
						[+] // HtmlImage HtmlImage60
							[ ] // tag "#60"
						[+] // HtmlImage HtmlImage61
							[ ] // tag "#61"
						[+] // HtmlImage HtmlImage62
							[ ] // tag "#62"
						[+] // HtmlText SquintYourEyesToMakeBlend1
							[ ] // tag "Squint your eyes to make blending"
						[+] // HtmlImage SquintYourEyesToMakeBlend2
							[ ] // tag "Squint your eyes to make blending[1]"
						[+] // HtmlImage SquintYourEyesToMakeBlend3
							[ ] // tag "Squint your eyes to make blending[2]"
						[+] // HtmlImage SquintYourEyesToMakeBlend4
							[ ] // tag "Squint your eyes to make blending[3]"
						[+] // HtmlImage SquintYourEyesToMakeBlend5
							[ ] // tag "Squint your eyes to make blending[4]"
						[+] // HtmlImage SquintYourEyesToMakeBlend6
							[ ] // tag "Squint your eyes to make blending[5]"
						[+] // HtmlImage SquintYourEyesToMakeBlend7
							[ ] // tag "Squint your eyes to make blending[6]"
						[+] // HtmlImage HtmlImage69
							[ ] // tag "#69"
						[+] // HtmlImage HtmlImage70
							[ ] // tag "#70"
						[+] // HtmlImage HtmlImage71
							[ ] // tag "#71"
						[+] // HtmlImage HtmlImage72
							[ ] // tag "#72"
						[+] // HtmlImage HtmlImage73
							[ ] // tag "#73"
						[+] // HtmlImage HtmlImage74
							[ ] // tag "#74"
						[+] // HtmlImage HtmlImage75
							[ ] // tag "#75"
						[+] // HtmlImage HtmlImage76
							[ ] // tag "#76"
						[+] // HtmlImage HtmlImage77
							[ ] // tag "#77"
						[+] // HtmlImage HtmlImage78
							[ ] // tag "#78"
						[+] // HtmlImage HtmlImage79
							[ ] // tag "#79"
						[+] // HtmlImage HtmlImage80
							[ ] // tag "#80"
						[+] // HtmlText Example1
							[ ] // tag "Example:"
						[+] // HtmlImage HtmlImage81
							[ ] // tag "#81"
						[+] // HtmlImage HtmlImage82
							[ ] // tag "#82"
						[+] // HtmlImage HtmlImage83
							[ ] // tag "#83"
						[+] // HtmlImage HtmlImage84
							[ ] // tag "#84"
						[+] // HtmlImage HtmlImage85
							[ ] // tag "#85"
						[+] // HtmlImage HtmlImage86
							[ ] // tag "#86"
						[+] // HtmlImage Example2
							[ ] // tag "Example:"
						[+] // HtmlImage HtmlImage88
							[ ] // tag "#88"
						[+] // HtmlImage HtmlImage89
							[ ] // tag "#89"
						[+] // HtmlImage HtmlImage90
							[ ] // tag "#90"
						[+] // HtmlImage HtmlImage91
							[ ] // tag "#91"
						[+] // HtmlImage HtmlImage92
							[ ] // tag "#92"
						[+] // HtmlImage HtmlImage93
							[ ] // tag "#93"
						[+] // HtmlImage HtmlImage94
							[ ] // tag "#94"
						[+] // HtmlImage HtmlImage95
							[ ] // tag "#95"
						[+] // HtmlImage HtmlImage96
							[ ] // tag "#96"
						[+] // HtmlImage HtmlImage97
							[ ] // tag "#97"
						[+] // HtmlImage HtmlImage98
							[ ] // tag "#98"
						[+] // HtmlImage HtmlImage99
							[ ] // tag "#99"
						[+] // HtmlImage HtmlImage100
							[ ] // tag "#100"
						[+] // HtmlImage HtmlImage101
							[ ] // tag "#101"
						[+] // HtmlImage HtmlImage102
							[ ] // tag "#102"
						[+] // HtmlImage HtmlImage103
							[ ] // tag "#103"
						[+] // HtmlImage HtmlImage104
							[ ] // tag "#104"
						[+] // HtmlImage HtmlImage105
							[ ] // tag "#105"
						[+] // HtmlImage HtmlImage106
							[ ] // tag "#106"
						[+] // HtmlImage HtmlImage107
							[ ] // tag "#107"
						[+] // HtmlImage HtmlImage108
							[ ] // tag "#108"
						[+] // HtmlImage HtmlImage109
							[ ] // tag "#109"
						[+] // HtmlImage HtmlImage110
							[ ] // tag "#110"
						[+] // HtmlImage HtmlImage111
							[ ] // tag "#111"
						[+] // HtmlImage HtmlImage112
							[ ] // tag "#112"
						[+] // HtmlImage HtmlImage113
							[ ] // tag "#113"
						[+] // HtmlImage HtmlImage114
							[ ] // tag "#114"
						[+] // HtmlImage HtmlImage115
							[ ] // tag "#115"
						[+] // HtmlImage HtmlImage116
							[ ] // tag "#116"
						[+] // HtmlImage HtmlImage117
							[ ] // tag "#117"
						[+] // HtmlImage HtmlImage118
							[ ] // tag "#118"
						[+] // HtmlImage HtmlImage119
							[ ] // tag "#119"
						[+] // HtmlImage HtmlImage120
							[ ] // tag "#120"
						[+] // HtmlImage HtmlImage121
							[ ] // tag "#121"
						[+] // HtmlImage HtmlImage122
							[ ] // tag "#122"
						[+] // HtmlImage HtmlImage123
							[ ] // tag "#123"
						[+] // HtmlImage HtmlImage124
							[ ] // tag "#124"
						[+] // HtmlImage HtmlImage125
							[ ] // tag "#125"
						[+] // HtmlImage HtmlImage126
							[ ] // tag "#126"
						[+] // HtmlImage HtmlImage127
							[ ] // tag "#127"
						[+] // HtmlImage HtmlImage128
							[ ] // tag "#128"
						[+] // HtmlImage HtmlImage129
							[ ] // tag "#129"
						[+] // HtmlImage HtmlImage130
							[ ] // tag "#130"
						[+] // HtmlImage HtmlImage131
							[ ] // tag "#131"
						[+] // HtmlImage HtmlImage132
							[ ] // tag "#132"
						[+] // HtmlImage HtmlImage133
							[ ] // tag "#133"
						[+] // HtmlImage HtmlImage134
							[ ] // tag "#134"
						[+] // HtmlImage HtmlImage135
							[ ] // tag "#135"
						[+] // HtmlText ClickNextToContinue
							[ ] // tag "Click next to continue."
						[+] // HtmlImage HtmlImage136
							[ ] // tag "#136"
						[+] // HtmlImage HtmlImage137
							[ ] // tag "#137"
						[+] // HtmlImage HtmlImage138
							[ ] // tag "#138"
						[+] // HtmlImage HtmlImage139
							[ ] // tag "#139"
						[+] // HtmlImage HtmlImage140
							[ ] // tag "#140"
						[+] // HtmlImage HtmlImage141
							[ ] // tag "#141"
						[+] // HtmlImage HtmlImage142
							[ ] // tag "#142"
						[+] // HtmlImage HtmlImage143
							[ ] // tag "#143"
						[+] // HtmlImage HtmlImage144
							[ ] // tag "#144"
						[+] // HtmlImage HtmlImage145
							[ ] // tag "#145"
						[+] // HtmlImage HtmlImage146
							[ ] // tag "#146"
						[+] // HtmlImage HtmlImage147
							[ ] // tag "#147"
						[+] // HtmlImage Ecolor4a4
							[ ] // tag "ecolor4a#[4]"
						[+] // HtmlImage ClickNextToContinue1
							[ ] // tag "Click next to continue.[1]"
						[+] // HtmlImage ClickNextToContinue2
							[ ] // tag "Click next to continue.[2]"
						[+] // HtmlImage ClickNextToContinue3
							[ ] // tag "Click next to continue.[3]"
						[+] // HtmlImage ClickNextToContinue4
							[ ] // tag "Click next to continue.[4]"
						[+] // HtmlImage Ecolor4a5
							[ ] // tag "ecolor4a#[5]"
						[+] // HtmlImage Ecolor4a6
							[ ] // tag "ecolor4a#[6]"
						[+] // HtmlImage ClickNextToContinue5
							[ ] // tag "Click next to continue.[5]"
				[+] window BrowserChild TuneUp2Page5			// CRTPage5 Color Blend Part 2
					[+] void DoPage(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.SelectBRG(iBlue, iRed, iGreen)
						[ ] this.Next()
					[+] void SelectBRG(Integer iBlue, Integer iRed, Integer iGreen)
						[ ] this.Blue(iBlue)
						[ ] this.Red(iRed)
						[ ] this.Green(iGreen)
					[+] void Blue(integer Index)	// INDEX 1 thru 23
						[ ] __DoClick(__BlueBar, Index)
					[+] void Red(integer Index)
						[ ] __DoClick(__RedBar, Index)
					[+] void Green(integer Index)
						[ ] __DoClick(__GreenBar, Index)
					[-] void Next()
						[ ] __NextButton.Click()
					[+] //INTERNALS
						[+] void __DoClick(window WindowToClick, INTEGER Index)
							[+] if Index == 0 || Index > __MaxIndex 
								[ ] raise 1, "Parameter out of bounds"
							[ ] Index = Index-1
							[ ] integer iVLoc = __VStart + (__VInterval*Index)
							[ ] WindowToClick.Click(1,__HLocation, iVLoc)
						[ ] window  __BlueBar  = BrowserChild1.HtmlImage7
						[ ] window  __RedBar   = BrowserChild1.HtmlImage4
						[ ] window  __GreenBar = BrowserChild1.HtmlImage5
						[ ] window  __NextButton = BrowserChild1.Ecolor4b3
						[ ] INTEGER __MaxIndex = 23
						[ ] INTEGER __VStart    = 9
						[ ] INTEGER __VInterval = 18
						[ ] INTEGER __HLocation = 48
						[ ] 
					[ ] //WINDOW DECLARATION AS RECORDED
					[ ] tag "#1"
					[ ] parent EColorMicrosoftInternetE
					[ ] 
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] HtmlImage HtmlImage1
							[ ] tag "#1"
						[+] HtmlImage HtmlImage2
							[ ] tag "#2"
						[+] HtmlImage HtmlImage3
							[ ] tag "#3"
						[+] HtmlImage HtmlImage4
							[ ] tag "#4"
						[+] HtmlImage HtmlImage5
							[ ] tag "#5"
						[+] HtmlImage HtmlImage6
							[ ] tag "#6"
						[+] HtmlImage HtmlImage7
							[ ] tag "#7"
						[+] HtmlImage HtmlImage8
							[ ] tag "#8"
						[+] HtmlImage HtmlImage9
							[ ] tag "#9"
						[+] HtmlImage HtmlImage10
							[ ] tag "#10"
						[+] HtmlImage HtmlImage11
							[ ] tag "#11"
						[+] HtmlImage HtmlImage12
							[ ] tag "#12"
						[+] HtmlImage HtmlImage13
							[ ] tag "#13"
						[+] HtmlImage HtmlImage14
							[ ] tag "#14"
						[+] HtmlImage HtmlImage15
							[ ] tag "#15"
						[+] HtmlImage HtmlImage16
							[ ] tag "#16"
						[+] HtmlImage HtmlImage17
							[ ] tag "#17"
						[+] HtmlImage HtmlImage18
							[ ] tag "#18"
						[+] HtmlImage HtmlImage19
							[ ] tag "#19"
						[+] HtmlTable HtmlTable1
							[ ] tag "#1"
							[+] HtmlColumn HtmlColumn1
								[ ] tag "#1"
							[+] HtmlColumn HtmlColumn2
								[ ] tag "#2"
								[+] HtmlImage HtmlImage1
									[ ] tag "#1"
								[+] HtmlImage HtmlImage2
									[ ] tag "#2"
								[+] HtmlImage HtmlImage3
									[ ] tag "#3"
						[+] HtmlImage HtmlImage20
							[ ] tag "#20"
						[+] HtmlImage HtmlImage21
							[ ] tag "#21"
						[+] HtmlImage HtmlImage22
							[ ] tag "#22"
						[+] HtmlImage HtmlImage23
							[ ] tag "#23"
						[+] HtmlImage HtmlImage24
							[ ] tag "#24"
						[+] HtmlImage HtmlImage25
							[ ] tag "#25"
						[+] HtmlImage HtmlImage26
							[ ] tag "#26"
						[+] HtmlImage HtmlImage27
							[ ] tag "#27"
						[+] HtmlImage HtmlImage28
							[ ] tag "#28"
						[+] HtmlImage HtmlImage29
							[ ] tag "#29"
						[+] HtmlImage HtmlImage30
							[ ] tag "#30"
						[+] HtmlImage HtmlImage31
							[ ] tag "#31"
						[+] HtmlImage HtmlImage32
							[ ] tag "#32"
						[+] HtmlImage HtmlImage33
							[ ] tag "#33"
						[+] HtmlImage HtmlImage34
							[ ] tag "#34"
						[+] HtmlImage HtmlImage35
							[ ] tag "#35"
						[+] HtmlText ClickOnTheSquareInEach
							[ ] tag "Click on the square in each"
						[+] HtmlImage HtmlImage36
							[ ] tag "#36"
						[+] HtmlImage HtmlImage37
							[ ] tag "#37"
						[+] HtmlImage HtmlImage38
							[ ] tag "#38"
						[+] HtmlImage HtmlImage39
							[ ] tag "#39"
						[+] HtmlImage HtmlImage40
							[ ] tag "#40"
						[+] HtmlImage HtmlImage41
							[ ] tag "#41"
						[+] HtmlImage HtmlImage42
							[ ] tag "#42"
						[+] HtmlImage HtmlImage43
							[ ] tag "#43"
						[+] HtmlImage HtmlImage44
							[ ] tag "#44"
						[+] HtmlImage HtmlImage45
							[ ] tag "#45"
						[+] HtmlImage HtmlImage46
							[ ] tag "#46"
						[+] HtmlImage HtmlImage47
							[ ] tag "#47"
						[+] HtmlImage HtmlImage48
							[ ] tag "#48"
						[+] HtmlImage HtmlImage49
							[ ] tag "#49"
						[+] HtmlImage HtmlImage50
							[ ] tag "#50"
						[+] HtmlImage HtmlImage51
							[ ] tag "#51"
						[+] HtmlImage HtmlImage52
							[ ] tag "#52"
						[+] HtmlImage HtmlImage53
							[ ] tag "#53"
						[+] HtmlImage HtmlImage54
							[ ] tag "#54"
						[+] HtmlImage HtmlImage55
							[ ] tag "#55"
						[+] HtmlImage HtmlImage56
							[ ] tag "#56"
						[+] HtmlImage HtmlImage57
							[ ] tag "#57"
						[+] HtmlImage HtmlImage58
							[ ] tag "#58"
						[+] HtmlImage HtmlImage59
							[ ] tag "#59"
						[+] HtmlImage SquintYourEyesToMakeBlend1
							[ ] tag "Squint your eyes to make blending[1]"
						[+] HtmlImage SquintYourEyesToMakeBlend2
							[ ] tag "Squint your eyes to make blending[2]"
						[+] HtmlImage SquintYourEyesToMakeBlend3
							[ ] tag "Squint your eyes to make blending[3]"
						[+] HtmlImage SquintYourEyesToMakeBlend4
							[ ] tag "Squint your eyes to make blending[4]"
						[+] HtmlImage SquintYourEyesToMakeBlend5
							[ ] tag "Squint your eyes to make blending[5]"
						[+] HtmlImage SquintYourEyesToMakeBlend6
							[ ] tag "Squint your eyes to make blending[6]"
						[+] HtmlText SquintYourEyesToMakeBlend7
							[ ] tag "Squint your eyes to make blending"
						[+] HtmlImage SquintYourEyesToMakeBlend8
							[ ] tag "Squint your eyes to make blending[7]"
						[+] HtmlImage SquintYourEyesToMakeBlend9
							[ ] tag "Squint your eyes to make blending[8]"
						[+] HtmlImage SquintYourEyesToMakeBlend10
							[ ] tag "Squint your eyes to make blending[9]"
						[+] HtmlImage SquintYourEyesToMakeBlend11
							[ ] tag "Squint your eyes to make blending[10]"
						[+] HtmlImage SquintYourEyesToMakeBlend12
							[ ] tag "Squint your eyes to make blending[11]"
						[+] HtmlImage SquintYourEyesToMakeBlend13
							[ ] tag "Squint your eyes to make blending[12]"
						[+] HtmlImage HtmlImage72
							[ ] tag "#72"
						[+] HtmlImage HtmlImage73
							[ ] tag "#73"
						[+] HtmlImage HtmlImage74
							[ ] tag "#74"
						[+] HtmlImage HtmlImage75
							[ ] tag "#75"
						[+] HtmlImage HtmlImage76
							[ ] tag "#76"
						[+] HtmlImage HtmlImage77
							[ ] tag "#77"
						[+] HtmlText Example
							[ ] tag "Example:"
						[+] HtmlImage HtmlImage78
							[ ] tag "#78"
						[+] HtmlImage HtmlImage79
							[ ] tag "#79"
						[+] HtmlImage HtmlImage80
							[ ] tag "#80"
						[+] HtmlImage HtmlImage81
							[ ] tag "#81"
						[+] HtmlImage HtmlImage82
							[ ] tag "#82"
						[+] HtmlImage HtmlImage83
							[ ] tag "#83"
						[+] HtmlImage Example1
							[ ] tag "Example:[1]"
						[+] HtmlImage Example2
							[ ] tag "Example:[2]"
						[+] HtmlImage Example3
							[ ] tag "Example:[3]"
						[+] HtmlImage Example4
							[ ] tag "Example:[4]"
						[+] HtmlImage Example5
							[ ] tag "Example:[5]"
						[+] HtmlImage Example6
							[ ] tag "Example:[6]"
						[+] HtmlImage Example7
							[ ] tag "Example:[7]"
						[+] HtmlImage HtmlImage91
							[ ] tag "#91"
						[+] HtmlImage HtmlImage92
							[ ] tag "#92"
						[+] HtmlImage HtmlImage93
							[ ] tag "#93"
						[+] HtmlImage HtmlImage94
							[ ] tag "#94"
						[+] HtmlImage HtmlImage95
							[ ] tag "#95"
						[+] HtmlImage HtmlImage96
							[ ] tag "#96"
						[+] HtmlImage HtmlImage97
							[ ] tag "#97"
						[+] HtmlImage HtmlImage98
							[ ] tag "#98"
						[+] HtmlImage HtmlImage99
							[ ] tag "#99"
						[+] HtmlImage HtmlImage100
							[ ] tag "#100"
						[+] HtmlImage HtmlImage101
							[ ] tag "#101"
						[+] HtmlImage HtmlImage102
							[ ] tag "#102"
						[+] HtmlImage HtmlImage103
							[ ] tag "#103"
						[+] HtmlImage HtmlImage104
							[ ] tag "#104"
						[+] HtmlImage HtmlImage105
							[ ] tag "#105"
						[+] HtmlImage HtmlImage106
							[ ] tag "#106"
						[+] HtmlImage HtmlImage107
							[ ] tag "#107"
						[+] HtmlImage HtmlImage108
							[ ] tag "#108"
						[+] HtmlImage HtmlImage109
							[ ] tag "#109"
						[+] HtmlImage HtmlImage110
							[ ] tag "#110"
						[+] HtmlImage HtmlImage111
							[ ] tag "#111"
						[+] HtmlImage HtmlImage112
							[ ] tag "#112"
						[+] HtmlImage HtmlImage113
							[ ] tag "#113"
						[+] HtmlImage HtmlImage114
							[ ] tag "#114"
						[+] HtmlImage HtmlImage115
							[ ] tag "#115"
						[+] HtmlImage HtmlImage116
							[ ] tag "#116"
						[+] HtmlImage HtmlImage117
							[ ] tag "#117"
						[+] HtmlImage HtmlImage118
							[ ] tag "#118"
						[+] HtmlImage HtmlImage119
							[ ] tag "#119"
						[+] HtmlImage HtmlImage120
							[ ] tag "#120"
						[+] HtmlImage HtmlImage121
							[ ] tag "#121"
						[+] HtmlImage HtmlImage122
							[ ] tag "#122"
						[+] HtmlImage HtmlImage123
							[ ] tag "#123"
						[+] HtmlImage HtmlImage124
							[ ] tag "#124"
						[+] HtmlImage HtmlImage125
							[ ] tag "#125"
						[+] HtmlImage HtmlImage126
							[ ] tag "#126"
						[+] HtmlImage HtmlImage127
							[ ] tag "#127"
						[+] HtmlImage HtmlImage128
							[ ] tag "#128"
						[+] HtmlImage HtmlImage129
							[ ] tag "#129"
						[+] HtmlImage HtmlImage130
							[ ] tag "#130"
						[+] HtmlImage HtmlImage131
							[ ] tag "#131"
						[+] HtmlImage HtmlImage132
							[ ] tag "#132"
						[+] HtmlText ClickNextToContinue
							[ ] tag "Click next to continue."
						[+] HtmlImage HtmlImage133
							[ ] tag "#133"
						[+] HtmlImage HtmlImage134
							[ ] tag "#134"
						[+] HtmlImage HtmlImage135
							[ ] tag "#135"
						[+] HtmlImage HtmlImage136
							[ ] tag "#136"
						[+] HtmlImage HtmlImage137
							[ ] tag "#137"
						[+] HtmlImage HtmlImage138
							[ ] tag "#138"
						[+] HtmlImage HtmlImage139
							[ ] tag "#139"
						[+] HtmlImage HtmlImage140
							[ ] tag "#140"
						[+] HtmlImage HtmlImage141
							[ ] tag "#141"
						[+] HtmlImage HtmlImage142
							[ ] tag "#142"
						[+] HtmlImage HtmlImage143
							[ ] tag "#143"
						[+] HtmlImage HtmlImage144
							[ ] tag "#144"
						[+] HtmlImage Ecolor4b1
							[ ] tag "ecolor4b#[1]"
						[+] HtmlImage HtmlImage146
							[ ] tag "#146"
						[+] HtmlImage HtmlImage147
							[ ] tag "#147"
						[+] HtmlImage HtmlImage148
							[ ] tag "#148"
						[+] HtmlImage ClickNextToContinue1
							[ ] tag "Click next to continue.[1]"
						[+] HtmlImage Ecolor4b2
							[ ] tag "ecolor4b#[2]"
						[+] HtmlImage Ecolor4b3
							[ ] tag "ecolor4b#[3]"
						[+] HtmlImage ClickNextToContinue2
							[ ] tag "Click next to continue.[2]"
					[+] // BrowserChild BrowserChild1  //tuneup 2.1
						[ ] // tag "#1"
						[+] // HtmlImage HtmlImage1
							[ ] // tag "#1"
						[+] // HtmlImage HtmlImage2
							[ ] // tag "#2"
						[+] // HtmlImage HtmlImage3
							[ ] // tag "#3"
						[+] // HtmlImage HtmlImage4
							[ ] // tag "#4"
						[+] // HtmlImage HtmlImage5
							[ ] // tag "#5"
						[+] // HtmlImage HtmlImage6
							[ ] // tag "#6"
						[+] // HtmlImage Ecolor4b1
							[ ] // tag "ecolor4b#[1]"
						[+] // HtmlImage Ecolor4b2
							[ ] // tag "ecolor4b#[2]"
						[+] // HtmlImage Ecolor4b3
							[ ] // tag "ecolor4b#[3]"
						[+] // HtmlImage HtmlImage10
							[ ] // tag "#10"
						[+] // HtmlImage HtmlImage11
							[ ] // tag "#11"
						[+] // HtmlImage HtmlImage12
							[ ] // tag "#12"
						[+] // HtmlImage HtmlImage13
							[ ] // tag "#13"
						[+] // HtmlImage HtmlImage14
							[ ] // tag "#14"
						[+] // HtmlImage HtmlImage15
							[ ] // tag "#15"
						[+] // HtmlImage HtmlImage16
							[ ] // tag "#16"
						[+] // HtmlImage HtmlImage17
							[ ] // tag "#17"
						[+] // HtmlImage HtmlImage18
							[ ] // tag "#18"
						[+] // HtmlImage HtmlImage19
							[ ] // tag "#19"
						[+] // HtmlImage HtmlImage20
							[ ] // tag "#20"
						[+] // HtmlImage HtmlImage21
							[ ] // tag "#21"
						[+] // HtmlTable HtmlTable1
							[ ] // tag "#1"
							[+] // HtmlColumn HtmlColumn1
								[ ] // tag "#1"
							[+] // HtmlColumn HtmlColumn2
								[ ] // tag "#2"
								[+] // HtmlImage HtmlImage1
									[ ] // tag "#1"
								[+] // HtmlImage HtmlImage2
									[ ] // tag "#2"
								[+] // HtmlImage HtmlImage3
									[ ] // tag "#3"
						[+] // HtmlImage HtmlImage22
							[ ] // tag "#22"
						[+] // HtmlImage HtmlImage23
							[ ] // tag "#23"
						[+] // HtmlImage HtmlImage24
							[ ] // tag "#24"
						[+] // HtmlImage HtmlImage25
							[ ] // tag "#25"
						[+] // HtmlImage HtmlImage26
							[ ] // tag "#26"
						[+] // HtmlImage HtmlImage27
							[ ] // tag "#27"
						[+] // HtmlImage HtmlImage28
							[ ] // tag "#28"
						[+] // HtmlImage HtmlImage29
							[ ] // tag "#29"
						[+] // HtmlImage HtmlImage30
							[ ] // tag "#30"
						[+] // HtmlImage HtmlImage31
							[ ] // tag "#31"
						[+] // HtmlImage HtmlImage32
							[ ] // tag "#32"
						[+] // HtmlImage HtmlImage33
							[ ] // tag "#33"
						[+] // HtmlImage HtmlImage34
							[ ] // tag "#34"
						[+] // HtmlImage HtmlImage35
							[ ] // tag "#35"
						[+] // HtmlImage HtmlImage36
							[ ] // tag "#36"
						[+] // HtmlImage HtmlImage37
							[ ] // tag "#37"
						[+] // HtmlText ClickOnTheSquareInEach
							[ ] // tag "Click on the square in each"
						[+] // HtmlImage HtmlImage38
							[ ] // tag "#38"
						[+] // HtmlImage HtmlImage39
							[ ] // tag "#39"
						[+] // HtmlImage HtmlImage40
							[ ] // tag "#40"
						[+] // HtmlImage HtmlImage41
							[ ] // tag "#41"
						[+] // HtmlImage HtmlImage42
							[ ] // tag "#42"
						[+] // HtmlImage HtmlImage43
							[ ] // tag "#43"
						[+] // HtmlImage HtmlImage44
							[ ] // tag "#44"
						[+] // HtmlImage HtmlImage45
							[ ] // tag "#45"
						[+] // HtmlImage HtmlImage46
							[ ] // tag "#46"
						[+] // HtmlImage HtmlImage47
							[ ] // tag "#47"
						[+] // HtmlImage HtmlImage48
							[ ] // tag "#48"
						[+] // HtmlImage HtmlImage49
							[ ] // tag "#49"
						[+] // HtmlImage HtmlImage50
							[ ] // tag "#50"
						[+] // HtmlImage HtmlImage51
							[ ] // tag "#51"
						[+] // HtmlImage HtmlImage52
							[ ] // tag "#52"
						[+] // HtmlImage HtmlImage53
							[ ] // tag "#53"
						[+] // HtmlImage HtmlImage54
							[ ] // tag "#54"
						[+] // HtmlImage HtmlImage55
							[ ] // tag "#55"
						[+] // HtmlImage HtmlImage56
							[ ] // tag "#56"
						[+] // HtmlImage HtmlImage57
							[ ] // tag "#57"
						[+] // HtmlImage HtmlImage58
							[ ] // tag "#58"
						[+] // HtmlImage HtmlImage59
							[ ] // tag "#59"
						[+] // HtmlImage HtmlImage60
							[ ] // tag "#60"
						[+] // HtmlImage HtmlImage61
							[ ] // tag "#61"
						[+] // HtmlImage SquintYourEyesToMakeBlend1
							[ ] // tag "Squint your eyes to make blending[1]"
						[+] // HtmlImage SquintYourEyesToMakeBlend2
							[ ] // tag "Squint your eyes to make blending[2]"
						[+] // HtmlImage SquintYourEyesToMakeBlend3
							[ ] // tag "Squint your eyes to make blending[3]"
						[+] // HtmlImage SquintYourEyesToMakeBlend4
							[ ] // tag "Squint your eyes to make blending[4]"
						[+] // HtmlImage SquintYourEyesToMakeBlend5
							[ ] // tag "Squint your eyes to make blending[5]"
						[+] // HtmlImage SquintYourEyesToMakeBlend6
							[ ] // tag "Squint your eyes to make blending[6]"
						[+] // HtmlText SquintYourEyesToMakeBlend7
							[ ] // tag "Squint your eyes to make blending"
						[+] // HtmlImage SquintYourEyesToMakeBlend8
							[ ] // tag "Squint your eyes to make blending[7]"
						[+] // HtmlImage SquintYourEyesToMakeBlend9
							[ ] // tag "Squint your eyes to make blending[8]"
						[+] // HtmlImage SquintYourEyesToMakeBlend10
							[ ] // tag "Squint your eyes to make blending[9]"
						[+] // HtmlImage SquintYourEyesToMakeBlend11
							[ ] // tag "Squint your eyes to make blending[10]"
						[+] // HtmlImage SquintYourEyesToMakeBlend12
							[ ] // tag "Squint your eyes to make blending[11]"
						[+] // HtmlImage SquintYourEyesToMakeBlend13
							[ ] // tag "Squint your eyes to make blending[12]"
						[+] // HtmlImage HtmlImage74
							[ ] // tag "#74"
						[+] // HtmlImage HtmlImage75
							[ ] // tag "#75"
						[+] // HtmlImage HtmlImage76
							[ ] // tag "#76"
						[+] // HtmlImage HtmlImage77
							[ ] // tag "#77"
						[+] // HtmlImage HtmlImage78
							[ ] // tag "#78"
						[+] // HtmlImage HtmlImage79
							[ ] // tag "#79"
						[+] // HtmlText Example
							[ ] // tag "Example:"
						[+] // HtmlImage HtmlImage80
							[ ] // tag "#80"
						[+] // HtmlImage HtmlImage81
							[ ] // tag "#81"
						[+] // HtmlImage HtmlImage82
							[ ] // tag "#82"
						[+] // HtmlImage HtmlImage83
							[ ] // tag "#83"
						[+] // HtmlImage HtmlImage84
							[ ] // tag "#84"
						[+] // HtmlImage HtmlImage85
							[ ] // tag "#85"
						[+] // HtmlImage Example1
							[ ] // tag "Example:[1]"
						[+] // HtmlImage Example2
							[ ] // tag "Example:[2]"
						[+] // HtmlImage Example3
							[ ] // tag "Example:[3]"
						[+] // HtmlImage Example4
							[ ] // tag "Example:[4]"
						[+] // HtmlImage Example5
							[ ] // tag "Example:[5]"
						[+] // HtmlImage Example6
							[ ] // tag "Example:[6]"
						[+] // HtmlImage Example7
							[ ] // tag "Example:[7]"
						[+] // HtmlImage HtmlImage93
							[ ] // tag "#93"
						[+] // HtmlImage HtmlImage94
							[ ] // tag "#94"
						[+] // HtmlImage HtmlImage95
							[ ] // tag "#95"
						[+] // HtmlImage HtmlImage96
							[ ] // tag "#96"
						[+] // HtmlImage HtmlImage97
							[ ] // tag "#97"
						[+] // HtmlImage HtmlImage98
							[ ] // tag "#98"
						[+] // HtmlImage HtmlImage99
							[ ] // tag "#99"
						[+] // HtmlImage HtmlImage100
							[ ] // tag "#100"
						[+] // HtmlImage HtmlImage101
							[ ] // tag "#101"
						[+] // HtmlImage HtmlImage102
							[ ] // tag "#102"
						[+] // HtmlImage HtmlImage103
							[ ] // tag "#103"
						[+] // HtmlImage HtmlImage104
							[ ] // tag "#104"
						[+] // HtmlImage HtmlImage105
							[ ] // tag "#105"
						[+] // HtmlImage HtmlImage106
							[ ] // tag "#106"
						[+] // HtmlImage HtmlImage107
							[ ] // tag "#107"
						[+] // HtmlImage HtmlImage108
							[ ] // tag "#108"
						[+] // HtmlImage HtmlImage109
							[ ] // tag "#109"
						[+] // HtmlImage HtmlImage110
							[ ] // tag "#110"
						[+] // HtmlImage HtmlImage111
							[ ] // tag "#111"
						[+] // HtmlImage HtmlImage112
							[ ] // tag "#112"
						[+] // HtmlImage HtmlImage113
							[ ] // tag "#113"
						[+] // HtmlImage HtmlImage114
							[ ] // tag "#114"
						[+] // HtmlImage HtmlImage115
							[ ] // tag "#115"
						[+] // HtmlImage HtmlImage116
							[ ] // tag "#116"
						[+] // HtmlImage HtmlImage117
							[ ] // tag "#117"
						[+] // HtmlImage HtmlImage118
							[ ] // tag "#118"
						[+] // HtmlImage HtmlImage119
							[ ] // tag "#119"
						[+] // HtmlImage HtmlImage120
							[ ] // tag "#120"
						[+] // HtmlImage HtmlImage121
							[ ] // tag "#121"
						[+] // HtmlImage HtmlImage122
							[ ] // tag "#122"
						[+] // HtmlImage HtmlImage123
							[ ] // tag "#123"
						[+] // HtmlImage HtmlImage124
							[ ] // tag "#124"
						[+] // HtmlImage HtmlImage125
							[ ] // tag "#125"
						[+] // HtmlImage HtmlImage126
							[ ] // tag "#126"
						[+] // HtmlImage HtmlImage127
							[ ] // tag "#127"
						[+] // HtmlImage HtmlImage128
							[ ] // tag "#128"
						[+] // HtmlImage HtmlImage129
							[ ] // tag "#129"
						[+] // HtmlImage HtmlImage130
							[ ] // tag "#130"
						[+] // HtmlImage HtmlImage131
							[ ] // tag "#131"
						[+] // HtmlImage HtmlImage132
							[ ] // tag "#132"
						[+] // HtmlImage HtmlImage133
							[ ] // tag "#133"
						[+] // HtmlImage HtmlImage134
							[ ] // tag "#134"
						[+] // HtmlText ClickNextToContinue
							[ ] // tag "Click next to continue."
						[+] // HtmlImage HtmlImage135
							[ ] // tag "#135"
						[+] // HtmlImage HtmlImage136
							[ ] // tag "#136"
						[+] // HtmlImage HtmlImage137
							[ ] // tag "#137"
						[+] // HtmlImage HtmlImage138
							[ ] // tag "#138"
						[+] // HtmlImage HtmlImage139
							[ ] // tag "#139"
						[+] // HtmlImage HtmlImage140
							[ ] // tag "#140"
						[+] // HtmlImage HtmlImage141
							[ ] // tag "#141"
						[+] // HtmlImage HtmlImage142
							[ ] // tag "#142"
						[+] // HtmlImage HtmlImage143
							[ ] // tag "#143"
						[+] // HtmlImage HtmlImage144
							[ ] // tag "#144"
						[+] // HtmlImage HtmlImage145
							[ ] // tag "#145"
						[+] // HtmlImage HtmlImage146
							[ ] // tag "#146"
						[+] // HtmlImage Ecolor4b4
							[ ] // tag "ecolor4b#[4]"
						[+] // HtmlImage HtmlImage148
							[ ] // tag "#148"
						[+] // HtmlImage HtmlImage149
							[ ] // tag "#149"
						[+] // HtmlImage HtmlImage150
							[ ] // tag "#150"
						[+] // HtmlImage ClickNextToContinue1
							[ ] // tag "Click next to continue.[1]"
						[+] // HtmlImage Ecolor4b5
							[ ] // tag "ecolor4b#[5]"
						[+] // HtmlImage Ecolor4b6
							[ ] // tag "ecolor4b#[6]"
						[+] // HtmlImage ClickNextToContinue2
							[ ] // tag "Click next to continue.[2]"
				[+] window BrowserChild TuneUp2Page6			// CRTPage6 Darkest Bar
					[+] void DoPage(Integer index)
						[ ] Bar(index)
						[ ] Next()
					[+] void Bar(integer index)
						[-] if index > 11
							[ ] raise 1, "Tune Up 2 page 6 - parameter out of range" 
						[ ] string Locator = "Ecolor5{index}"
						[ ] BrowserChild1.@(Locator).Click()
					[+] void Next()
						[ ] __NextButton.Click()
					[+] //INTERNALS
						[ ] window __NextButton = BrowserChild1.Ecolor514
					[ ] //WINDOW DECLARATION AS RECORDED
					[ ] tag "#1"
					[ ] parent EColorMicrosoftInternetE
					[+] BrowserChild BrowserChild1
						[ ] tag "#1"
						[+] HtmlImage HtmlImage1
							[ ] tag "#1"
						[+] HtmlImage HtmlImage2
							[ ] tag "#2"
						[+] HtmlImage HtmlImage3
							[ ] tag "#3"
						[+] HtmlImage HtmlImage4
							[ ] tag "#4"
						[+] HtmlImage HtmlImage5
							[ ] tag "#5"
						[+] HtmlImage HtmlImage6
							[ ] tag "#6"
						[+] HtmlImage DarkestBar1
							[ ] tag "Darkest Bar[1]"
						[+] HtmlImage Ecolor51
							[ ] tag "ecolor5#[1]"
						[+] HtmlImage DarkestBar2
							[ ] tag "Darkest Bar[2]"
						[+] HtmlImage HtmlImage10
							[ ] tag "#10"
						[+] HtmlHeading DarkestBar
							[ ] tag "Darkest Bar"
						[+] HtmlImage DarkestBar3
							[ ] tag "Darkest Bar[3]"
						[+] HtmlImage Step5Of51
							[ ] tag "step 5 of 5[1]"
						[+] HtmlImage Ecolor52
							[ ] tag "ecolor5#[2]"
						[+] HtmlImage Step5Of52
							[ ] tag "step 5 of 5[2]"
						[+] HtmlText Step5Of5
							[ ] tag "step 5 of 5"
						[+] HtmlText ClickOnTheDarkestBarThat
							[ ] tag "Click on the darkest bar that"
						[+] HtmlImage Step5Of53
							[ ] tag "step 5 of 5[3]"
						[+] HtmlImage HtmlImage16
							[ ] tag "#16"
						[+] HtmlImage Ecolor53
							[ ] tag "ecolor5#[3]"
						[+] HtmlImage HtmlImage18
							[ ] tag "#18"
						[+] HtmlImage HtmlImage19
							[ ] tag "#19"
						[+] HtmlImage HtmlImage20
							[ ] tag "#20"
						[+] HtmlImage Ecolor54
							[ ] tag "ecolor5#[4]"
						[+] HtmlImage HtmlImage22
							[ ] tag "#22"
						[+] HtmlText Example
							[ ] tag "Example:"
						[+] HtmlImage Example1
							[ ] tag "Example:[1]"
						[+] HtmlImage Example2
							[ ] tag "Example:[2]"
						[+] HtmlImage HtmlImage25
							[ ] tag "#25"
						[+] HtmlImage Ecolor55
							[ ] tag "ecolor5#[5]"
						[+] HtmlImage HtmlImage27
							[ ] tag "#27"
						[+] HtmlImage HtmlImage28
							[ ] tag "#28"
						[+] HtmlImage HtmlImage29
							[ ] tag "#29"
						[+] HtmlImage Ecolor56
							[ ] tag "ecolor5#[6]"
						[+] HtmlImage HtmlImage31
							[ ] tag "#31"
						[+] HtmlImage HtmlImage32
							[ ] tag "#32"
						[+] HtmlImage HtmlImage33
							[ ] tag "#33"
						[+] HtmlImage Ecolor57
							[ ] tag "ecolor5#[7]"
						[+] HtmlImage HtmlImage35
							[ ] tag "#35"
						[+] HtmlImage HtmlImage36
							[ ] tag "#36"
						[+] HtmlImage HtmlImage37
							[ ] tag "#37"
						[+] HtmlImage ClickNextToContinue1
							[ ] tag "Click next to continue.[1]"
						[+] HtmlImage Ecolor58
							[ ] tag "ecolor5#[8]"
						[+] HtmlImage ClickNextToContinue2
							[ ] tag "Click next to continue.[2]"
						[+] HtmlText ClickNextToContinue
							[ ] tag "Click next to continue."
						[+] HtmlImage ClickNextToContinue3
							[ ] tag "Click next to continue.[3]"
						[+] HtmlImage HtmlImage42
							[ ] tag "#42"
						[+] HtmlImage Ecolor59
							[ ] tag "ecolor5#[9]"
						[+] HtmlImage HtmlImage44
							[ ] tag "#44"
						[+] HtmlImage HtmlImage45
							[ ] tag "#45"
						[+] HtmlImage HtmlImage46
							[ ] tag "#46"
						[+] HtmlImage Ecolor510
							[ ] tag "ecolor5#[10]"
						[+] HtmlImage HtmlImage48
							[ ] tag "#48"
						[+] HtmlImage HtmlImage49
							[ ] tag "#49"
						[+] HtmlImage HtmlImage50
							[ ] tag "#50"
						[+] HtmlImage Ecolor511
							[ ] tag "ecolor5#[11]"
						[+] HtmlImage HtmlImage52
							[ ] tag "#52"
						[+] HtmlImage HtmlImage53
							[ ] tag "#53"
						[+] HtmlImage Ecolor512
							[ ] tag "ecolor5#[12]"
						[+] HtmlImage HtmlImage55
							[ ] tag "#55"
						[+] HtmlImage Ecolor513
							[ ] tag "ecolor5#[13]"
						[+] HtmlImage Ecolor514
							[ ] tag "ecolor5#[14]"
				[+] window BrowserChild TuneUp2Page7			// Finish
					[+] Close()
						[ ] __FinishButton.Click()
					[ ] window __FinishButton = YouAreNowTunedUpToReceiv.Ecolor6_english 
					[ ] //WINDOW DECLARATION AS RECORDED
					[ ] tag "#1"
					[ ] parent EColorMicrosoftInternetE
					[+] BrowserChild YouAreNowTunedUpToReceiv
						[ ] tag "You are now tuned-up to receive"
						[+] HtmlImage HtmlImage1
							[ ] tag "#1"
						[+] HtmlImage HtmlImage2
							[ ] tag "#2"
						[+] HtmlImage HtmlImage3
							[ ] tag "#3"
						[+] HtmlImage HtmlImage4
							[ ] tag "#4"
						[+] HtmlImage HtmlImage5
							[ ] tag "#5"
						[+] HtmlImage HtmlImage6
							[ ] tag "#6"
						[+] HtmlText YouAreNowTunedUpToReceiv
							[ ] tag "You are now tuned-up to receive"
						[+] HtmlImage HtmlImage7
							[ ] tag "#7"
						[+] HtmlText Images
							[ ] tag "images"
						[+] HtmlImage HtmlImage8
							[ ] tag "#8"
						[+] HtmlHeading BeforeEColor1
							[ ] tag "Before E-Color"
						[+] HtmlImage HtmlImage9
							[ ] tag "#9"
						[+] HtmlImage BeforeEColor2
							[ ] tag "Before E-Color"
						[+] HtmlText YouCanTrustTheColorYouRe
							[ ] tag "You can trust the color you're"
						[+] HtmlHeading ActualColor1
							[ ] tag "Actual color"
						[+] HtmlImage HtmlImage11
							[ ] tag "#11"
						[+] HtmlImage HtmlImage12
							[ ] tag "#12"
						[+] HtmlImage ActualColor2
							[ ] tag "Actual color"
						[+] HtmlText ClickFinishToReturnToThe1
							[ ] tag "Click finish to return to the"
						[+] HtmlText WantAFreeIndicatorThatTel
							[ ] tag "Want a free indicator that tells"
						[+] HtmlHeading AfterEColor1
							[ ] tag "After E-Color"
						[+] HtmlImage HtmlImage14
							[ ] tag "#14"
						[+] HtmlImage ClickFinishToReturnToThe2
							[ ] tag "Click finish to return to the"
						[+] HtmlText ClickHere1
							[ ] tag "? Click here"
						[+] HtmlLink ClickHere2
							[ ] tag "Click here"
						[+] HtmlImage AfterEColor2
							[ ] tag "After E-Color"
						[+] HtmlText Copyright©2000EColorIncor
							[ ] tag "Copyright © 2000 E-Color Incorporated. The"
						[+] HtmlText HtmlText8
							[ ] tag ","
						[+] HtmlText EColorAreAll1
							[ ] tag ", E-Color are all"
						[+] HtmlImage EColorAreAll2
							[ ] tag ", E-Color are all"
						[+] HtmlImage HtmlImage18
							[ ] tag "#18"
						[+] HtmlImage Ecolor6_english
							[ ] tag "ecolor6_english#"
		[+] //attempt to get color depth
			[ ] // LONG PLANES=14
			[ ] // LONG BITSPIXEL=12
			[ ] // 
			[-] // dll "user32.dll"
				[ ] // LONG GetDC()
			[-] // dll "Gdi32.dll"
				[ ] // LONG GetDeviceCaps(LONG hdc, LONG dtype)
			[ ] // //use "msw32.inc"
			[-] // integer GetColorDepth()
				[ ] // LONG hdc = GetDC()
				[ ] // INT dBitsInAPixel = GetDeviceCaps(hdc, PLANES) * GetDeviceCaps(hdc, BITSPIXEL) 
				[ ] // return dBitsInAPixel
	[ ] 
	[+] void TestCaseEnter()
		[ ] ImageDirector1.SetECNState(ON)
		[ ] ImageDirector1.SetImageServerWatchdogState(ON)
		[ ] ImageDirector1.SetGeoCacheStateToDefault()
		[ ] 
		[ ] ImageDirector2.SetECNState(ON)
		[ ] ImageDirector2.SetImageServerWatchdogState(ON)
		[ ] ImageDirector2.SetGeoCacheStateToDefault()
		[ ] 
		[ ] EColorServers.ImageServer.ServerOn()
		[ ] EColorServers.ProfileServer.ServerOn()
		[ ] 
		[ ] BrowserSupport.SetCookieMode(CM_ACCEPT)
		[ ] BrowserSupport.Close()
		[ ] BrowserSupport.ClearCacheAndCookies()
		[ ] 
		[ ] 
[ ] ////////////////////////////////////////////////////////////
[ ] 
[ ] ////////////////////////////////////////////////////////////
[+] // expand for test space (code used to test framework)    //
	[ ] 
	[-] maina()
		[ ] string sURL =         "ViewingProfile_3d100_5f0_5f0.000_5f0.000_5f0.000_5f0_26"
		[ ] print(sContains(sURL, "ViewingProfile_3d100_5f0_5f0.0_5f0.0_5f0.0_5f0_26"))
		[ ] 
	[ ] 
	[ ] 
[ ] ////////////////////////////////////////////////////////////
[ ] 
[ ] ////////////////////////////////////////////////////////////
[+] // expand for test cases                                  //
	[ ] 
	[+] // group 1 - general tests (cases 1 thru 10)
		[ ] // Test Case (A) = New Users with unknown user ID
		[ ] // 
		[ ] // Clean up your cookie, you should not have any cookie on your hard 
		[ ] // drive from our sites.
		[ ] // Open your browser
		[ ] // Open the Test Page #1 (May be http://207.171.220.212/james.html)
		[ ] // Click on the Get Hello World Page Link (receive a TIC filtered page)
		[ ] // OK both Message Boxes requesting permission to write the cookies to your hard drive (only if you receive a cookie prompt).
		[ ] // Close browser
		[ ] // Go to cookie location.
		[ ] // Verify the Id number is present
		[ ] // Verify the Id is identical to all cookies present
		[ ] // Verify the calibration information should be 0 (meaning un-calibrated)
		[ ] // Verify that two cookies have been written to your hard drive, one should be written from the web server and the other will be 
		[ ] // an e-color cookie.
		[ ] // (a2) Repeat test case (A) above while End-User cookie has set up prompt for cookie
		[ ] // Verify same as above
		[ ] // (a3) Repeat test case (A) above while End-User has cookie disable (or hit button "NO" or "Cancel" on prompt for cookie) on his system 
		[ ] // and verify that:
		[ ] // 1 - Images are displayed without any errors
		[ ] // 2 - Cookie has not been created
		[ ] // 3 - Friendly message should notified End-User that his cookie are disabled.
		[-] testcase a1() appstate none
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //execute
			[ ] ImageDirector1.MakeUncalibratedCookie()
			[ ] //verify
			[ ] SecurityAlert.VerifyDidNotAppear()
			[ ] ImageDirector1.VerifyCookieIsUncalibrated()
			[ ] ImageDirector1.VerifyImage()
		[ ] 
		[-] testcase a2() appstate none
			[ ] raise 1, "TEST SIDELINED, leaves system in unusable state"
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] BrowserSupport.SetCookieMode(CM_PROMPT)
			[ ] //execute
			[ ] // there's a bug in IE, we have to do this one differently, can't use the
			[ ] // library functions that work for other cases...
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] sleep(120)
			[ ] explorer Browser.TypeKeys("<F5>")
			[ ] Browser.WaitForReady()
			[ ] //verify
			[ ] SecurityAlert.VerifyDidAppear()
			[ ] ImageDirector1.VerifyCookieIsUncalibrated()
			[ ] ImageDirector1.VerifyImage()
		[ ]  
		[-] testcase a3() appstate none
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] BrowserSupport.SetCookieMode(CM_REJECT)
			[ ] //execute
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] EColorServers.VerifyCookieDoesNotExist()
			[ ] ImageDirector1.VerifyCookieDoesNotExist()
			[ ] ImageDirector1.VerifyImage()
		[ ] 
		[ ] // Test Case (B) = Existing Users with valid Id's
		[ ] // After you have made your complete cookie bounce and have a cookie on your hard drive
		[ ] // Go to the cookie and write down the cookie ID number and timeout information (time out information only for the e-color cookie)
		[ ] // Open the Test Page #1
		[ ] // Click on the Get Hello World Page Link (receive a TIC filtered page)
		[ ] // You should go through a back channel  
		[ ] // Close all your browsers
		[ ] // Go to The cookie location 
		[ ] // Verify that the ID number in your cookie remains the same
		[ ] // Verify that the Calibration information remains in the un-calibrated (0) state
		[ ] // Verify timeout has changed
		[-] testcase b() appstate none
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //execute
			[ ] ImageDirector1.MakeUncalibratedCookie()
			[ ] ImageDirector1.VerifyCookieIsUncalibrated()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.WaitForStale()
			[ ] 
			[ ] ImageDirector1.StoreCurrentCookieData()
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] ImageDirector1.VerifyCookieIsUnCalibrated()
			[ ] ImageDirector1.VerifyCookieRefreshed()
			[ ] ImageDirector1.VerifyImage()
			[ ] 
		[ ] 
		[ ] // Test Case (C) = Existing Users with valid Id on new site
		[ ] // After you have cookies with valid Id's from the ticqasvr1 site:
		[ ] // Open your browser
		[ ] // Go To Test Page #2 
		[ ] // Click on the Get Hello World Page Link (receive a TIC filtered page)
		[ ] // You should go through a bounce to write the customers cookie
		[ ] // Close all your browsers
		[ ] // Go to The cookie location 
		[ ] // Verify that the new site cookie has been written to your hard drive
		[ ] // Verify that only three cookies are written to your hard drive file, one from the first site, one from the current site and one from e-color.
		[ ] // Verify the Id number is present
		[ ] // Verify the Id is identical in all the cookies present
		[ ] // Verify the calibration information should be 0 (meaning un-calibrated)
		[-] testcase c() appstate none
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] BrowserSupport.Close()
				[ ] SecurityAlert.VerifyDidNotAppear()
				[ ] ImageDirector1.VerifyCookieIsUncalibrated()
				[ ] 
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] Browser.WaitForReady()
				[ ] 
				[ ] //verify
				[ ] SecurityAlert.VerifyDidNotAppear()
				[ ] ImageDirector2.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyCookieMatchToMaster()
				[ ] ImageDirector1.VerifyCookieMatchToMaster()
				[ ] ImageDirector2.VerifyImage()
				[ ] 
		[ ] 
		[ ] // Test Case (D) = Calibrated user onto a new site
		[ ] // After you have cookies with valid Id's from the Test Page #1 and you have calibrated on that site:
		[ ] // Open Your browser
		[ ] // Go To Test Page #2 
		[ ] // Click on the Get Hello World Page Link (receive a TIC filtered page)
		[ ] // You should go through a bounce to write the customers cookie
		[ ] // Close all your browsers
		[ ] // Go to The cookie location 
		[ ] // Verify that the new site cookie has been written to your hard drive with the current calibration information.
		[ ] // Verify the Id number is present
		[ ] // Verify the Id is identical in all the cookies present
		[ ] // Verify the calibration information should be 1 (meaning calibrated)
		[-] testcase d() appstate none
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //execute
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] ImageDirector1.VerifyCookieIsCalibrated()
				[ ] 
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] 
				[ ] //verify
				[ ] ImageDirector2.VerifyCookieMatchToMaster()
				[ ] ImageDirector1.VerifyCookieMatchToMaster()
				[ ] ImageDirector2.VerifyCookieIsCalibrated()
				[ ] ImageDirector2.VerifyImage()
		[ ] 
		[ ] // Test Case (E) = Back channel Tic Filter request   
		[ ] // Delete all Cookies.
		[ ] // Open Your browser
		[ ] // Go to the Test Page #1
		[ ] // Click on the Get Hello World Page Link and get uncalibrated cookies
		[ ] // Go to the Test Page #2
		[ ] // Click Calibration link, calibrate user and get the calibrated cookies with same user ID.
		[ ] // Go again to the Test Page #1
		[ ] // Wait 2 minutes (time can be changed in TIC Image Director property file) and click link Get Hello World Page.
		[ ] // Go to The cookie location 
		[ ] // Verify the cookie Id is identical in all the cookies present
		[ ] // Verify the calibration information should be 1 (calibrated) and it should have fresh calibration information on it. (Calibration parameters will be exactly the same in all cookies)
		[ ] // Note: By Default All Watchdogs status  = "On" in TicImageDirector.properties file.
		[-] testcase e() appstate none
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] ImageDirector2.DoDefaultTuneUp()
				[ ] BrowserSupport.Close()
				[ ] sleep(120)
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] //verify
				[ ] ImageDirector1.VerifyCookieIsCalibrated()
				[ ] ImageDirector1.VerifyCookieMatchToMaster()
				[ ] ImageDirector2.VerifyCookieMatchToMaster()
				[ ] ImageDirector1.VerifyImage()
		[ ] 
		[ ] // Test Case (F) = HTML fix ups/Title and any TIC Images for Dynamo Filter
		[ ] // Make sure you calibrate on the chromasvr4 site
		[ ] // 
		[ ] // Enable Image Watchdog
		[ ] // Chromasvr4 
		[ ] // TIC filter/ TicImageDirector.Properties
		[ ] // TIC Filter watchdog status = on/off change it to { on } Save and exit.
		[ ] // Open PC anywhere
		[ ] // Click on Chromasvr4 / login
		[ ] // Click CAD at the top of the page 
		[ ] // Click on Dynamo Administration UI / enter Admin / Admin
		[ ] // Click restart Dynamo button
		[ ] // 
		[ ] // Open Browser and go to the tic color corrected page, make sure it has TIC ® Microsoft Title at the top of the page.
		[ ] // 
		[ ] // Turn off Image Server
		[ ] // Open a new PC anywhere
		[ ] // Open Chromasvr1
		[ ] // Click on CAD button on the top, log in
		[ ] // Click on Sprocket
		[ ] // Stop / wait 4 minutes
		[ ] // Make sure the filter recognizes the Image Server is down and will not distribute TIC corrected images in the title
		[ ] // 
		[ ] // 5) Turn on the Image Server
		[ ] // Start\programs\JRun\Start JRun (NT Service mode)
		[ ] // Wait two minutes
		[ ] // Make Sure Title and Image Correction returns!
		[ ] // 
		[ ] // 6) Log Off
		[ ] // On the Server Page Go to the Start Menu
		[ ] // Select Log Off QA god
		[ ] // Wait until the Cntrl-Alt-Del message box comes up
		[ ] // Click on the Unplug button
		[-] testcase f() appstate none
			[ ] // NOT IMPLEMENTED - FOR DYNAMO FILTER
			[ ] raise 1,"ERROR: Dynamo Filter Test Case Not Implemented"
		[ ] 
		[ ] // Test Case (G) = HTML fix ups/Title and any TIC Images for JRUN Filter
		[ ] // Make sure you calibrate on the ticqasvr1 site
		[ ] // Open pcAnyWhere
		[ ] // 
		[ ] // Enable Image Watchdog
		[ ] // Go to ticqasvr1
		[ ] // Open Pc anywhere / win explorer
		[ ] // Chromaserve / TIC Filter.Properties
		[ ] // TIC Filter watchdog status = on/off change it to { on } Save and exit.
		[ ] // Click on Sprocket
		[ ] // Hit restart and minimize
		[ ] // Open win explorer and go to Java\Jrun\jsm-default\logs
		[ ] // Look at all the three files and make sure there are no errors.
		[ ] // Go to Java\Jrun\jsm-default\Services\jse\logs
		[ ] // Look at all the two files and make sure there are no errors.
		[ ] // 
		[ ] // 
		[ ] // Open Browser on your own PC and go to the tic color corrected page, make sure it has TIC ® Microsoft Title at the top of the page.
		[ ] // 
		[ ] // Turn off Image Server
		[ ] // Open a new PC anywhere
		[ ] // Open Chromasvr1
		[ ] // Click on Sprocket
		[ ] // Stop / wait 4 minutes
		[ ] // Repeat step4 to make sure the filter recognizes the Image Server is down and will not distribute TIC corrected images in the title
		[ ] // Turn on the Image Server
		[ ] // Start\programs\Jrun\Start JRun (NT Service mode)
		[ ] // Wait two minutes
		[ ] // Make Sure Title and Image Correction returns!
		[ ] // 
		[ ] // Log Off (two times)
		[ ] // On the Server Page Go to the Start Menu
		[ ] // Select Log Off QA god
		[ ] // Dismiss log off message box
		[ ] // Wait until the Cntrl-Alt-Del message box comes up
		[ ] // Click on the Unplug button
		[-] testcase g() appstate none
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup 
			[ ] ImageDirector1.DoDefaultTuneUp()
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] // verify part 1
			[ ] ImageDirector1.VerifyTICTitle()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] 
			[ ] sleep(60*4)		// 4 minutes? for what?
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] 
			[ ] // have to turn the server back on BEFORE verifying, since verify might raise exception
			[ ] EColorServers.ImageServer.ServerOn()
			[ ] 
			[ ] ImageDirector1.VerifyNotTICTitle()
			[ ] BrowserSupport.Close()
			[ ] 
			[ ] sleep(2*60)
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify part 2
			[ ] ImageDirector1.VerifyTICTitle()
			[ ] ImageDirector1.VerifyImage()
			[ ] 
		[ ] 
		[ ] // Test Case (H) = Profile Server Shutdown test
		[-] testcase h() appstate none
			[ ] raise 1,"ERROR: test not defined in test plan"
	[ ] 
	[-] // group 2 - ECN tests (cases 11 thru 41)
		[ ] // 1.	New user visiting Existing TIC or opted-out Limited ECN customer site
		[ ] // Result: Regular cookie bounce and correctable images are served from original customer 
		[ ] // web site
		[-] testcase ECN1() appstate none // 11
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] //execute
			[ ] ImageDirector1.MakeUncalibratedCookie()
			[ ] 
			[ ] //verify
			[ ] ImageDirector1.VerifyCookieIsUncalibrated()
			[ ] ImageDirector1.VerifyImage()
		[ ] 
		[ ] // 2.	New user visiting opted-in Limited ECN customer site
		[ ] // Result: Regular cookie bounce and correctable images are served from E-Color Image 
		[ ] // server with average viewing profile
		[-] testcase ECN2() appstate none  // 12
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(ON)
			[ ] //execute
			[ ] ImageDirector1.MakeUncalibratedCookie()
			[ ] Browser.WaitForReady()
			[ ] //verify
			[ ] ImageDirector1.VerifyCookieIsUncalibrated()
			[ ] ImageDirector1.VerifyImage()
		[ ] 
		[ ] // 3.	An un-calibrated Fresh/Stale User first visiting opted-in Limited ECN 
		[ ] // customer after having visited an existing TIC or opted-out Limited ECN customer
		[ ] // Result: Regular cookie bounce and update, and correctable images are served 
		[ ] // from E-Color Image server with average viewing profile
		[-] testcase ECN3() appstate none		//fresh (13)
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //setup
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] ImageDirector2.SetECNState(ON)
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] //verify
				[ ] ImageDirector2.VerifyImage()
				[ ] ImageDirector1.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyCookieIsUncalibrated()
		[-] testcase ECN3_1() appstate none		//stale (14)
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //setup
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] ImageDirector2.SetECNState(ON)
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] ImageDirector1.VerifyImage()
				[ ] EColorServers.WaitForStale()
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] //verify
				[ ] ImageDirector1.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyImage()
		[ ]  
		[ ] // 4.	An un-calibrated Fresh/Stale User first visiting existing TIC or 
		[ ] // opted-out ECN customer after having visited an ECN customer.
		[ ] // Result: Regular cookie bounce and update, and correctable images are served 
		[ ] // from original customer web site
		[-] testcase ECN4() appstate none		//fresh (15)
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //setup
				[ ] ImageDirector1.SetECNState(ON)
				[ ] ImageDirector2.SetECNState(OFF)
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] 
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] //verify
				[ ] ImageDirector2.VerifyImage()
				[ ] ImageDirector1.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyCookieIsUncalibrated()
		[-] testcase ECN4_1() appstate none		//stale (16)
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //setup
				[ ] ImageDirector1.SetECNState(ON)
				[ ] ImageDirector2.SetECNState(OFF)
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] EColorServers.WaitForStale()
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] //verify
				[ ] ImageDirector2.VerifyImage()
				[ ] ImageDirector1.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyCookieIsUncalibrated()
		[ ]  
		[ ] // 5.	A calibrated Fresh/Stale User first visiting an ECN customer after having 
		[ ] // visited an existing TIC or opted-out ECN customer.
		[ ] // Result: Regular cookie bounce and update, and correctable images are served 
		[ ] // from E-Color Image server with custom end user viewing profile
		[-] testcase ECN5() appstate none		//fresh (17)
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //setup
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] ImageDirector2.SetECNState(ON)
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] //verify
				[ ] ImageDirector2.VerifyImage()
				[ ] ImageDirector1.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyCookieIsUncalibrated()
		[-] testcase ECN5_1() appstate none		//stale (18)
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //setup
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] ImageDirector2.SetECNState(ON)
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] EColorServers.WaitForStale()
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] //verify
				[ ] ImageDirector2.VerifyImage()
				[ ] ImageDirector1.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyCookieIsUncalibrated()
		[ ] 
		[ ] // 6.	A calibrated Fresh/Stale User first visiting existing TIC or opted-out 
		[ ] // ECN customer after having visited an ECN customer.
		[ ] // Result: Regular cookie bounce and update, and correctable images are served 
		[ ] // from E-Color Image server with custom end user viewing profile
		[-] testcase ECN6() appstate none		//fresh (19)
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //setup
				[ ] ImageDirector1.SetECNState(ON)
				[ ] ImageDirector2.SetECNState(OFF)
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] //verify
				[ ] ImageDirector2.VerifyImage()
				[ ] ImageDirector1.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyCookieIsUncalibrated()
		[-] testcase ECN6_1() appstate none		//stale (20)
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //setup
				[ ] ImageDirector1.SetECNState(ON)
				[ ] ImageDirector2.SetECNState(OFF)
				[ ] //execute
				[ ] ImageDirector1.MakeUncalibratedCookie()
				[ ] EColorServers.WaitForStale()
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] //verify
				[ ] ImageDirector2.VerifyImage()
				[ ] ImageDirector1.VerifyCookieIsUncalibrated()
				[ ] ImageDirector2.VerifyCookieIsUncalibrated()
		[ ]  
		[ ] // 7.	Fresh/Stale an un-calibrated User visiting Existing TIC or opted-out Limited ECN
		[ ] // Result: Regular cookie update for stale user and no changes for cookie for Fresh user, 
		[ ] // and correctable images are served from original customer web site
		[-] testcase ECN7() appstate none		//fresh (21)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] //execute
			[ ] ImageDirector1.MakeUncalibratedCookie()
			[ ] BrowserSupport.Close()
			[ ] 
			[ ] ImageDirector1.StoreCurrentCookieData()
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] ImageDirector1.VerifyImage()
			[ ] ImageDirector1.VerifyCookieNotRefreshed()
			[ ] 
		[-] testcase ECN7_1() appstate none		//stale (22)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] //execute
			[ ] ImageDirector1.MakeUncalibratedCookie()
			[ ] BrowserSupport.Close()
			[ ] 
			[ ] ImageDirector1.StoreCurrentCookieData()
			[ ] 
			[ ] EColorServers.WaitForStale()
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] ImageDirector1.VerifyImage()
			[ ] ImageDirector1.VerifyCookieRefreshed()
		[ ] 
		[ ] // 8.	Fresh/Stale a calibrated User visiting Existing TIC or opted-out Limited ECN
		[ ] // Result: Regular cookie update for stale user and no changes for cookie for Fresh user, 
		[ ] // and correctable images are served from E-Color Image server with custom end user 
		[ ] // viewing profile
		[-] testcase ECN8() appstate none		//fresh (23)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] //execute
			[ ] ImageDirector1.MakeCalibratedCookie()
			[ ] BrowserSupport.Close()
			[ ] 
			[ ] ImageDirector1.StoreCurrentCookieData()
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] ImageDirector1.VerifyImage()
			[ ] ImageDirector1.VerifyCookieNotRefreshed()
			[ ] 
		[-] testcase ECN8_1() appstate none		//stale (24)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] //execute
			[ ] ImageDirector1.MakeCalibratedCookie()
			[ ] BrowserSupport.Close()
			[ ] 
			[ ] ImageDirector1.StoreCurrentCookieData()
			[ ] 
			[ ] EColorServers.WaitForStale()
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] ImageDirector1.VerifyImage()
			[ ] ImageDirector1.VerifyCookieRefreshed()
			[ ] 
		[ ] 
		[ ] // 9.	Fresh/Stale an un-calibrated User visiting opted-in Limited ECN
		[ ] // Result: Regular cookie update for stale user and no changes for cookie for Fresh user, 
		[ ] // and correctable images are served from E-Color Image server with average viewing profile
		[-] testcase ECN9() appstate none		//fresh (25)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(ON)
			[ ] //execute
			[ ] ImageDirector1.MakeCalibratedCookie()
			[ ] BrowserSupport.Close()
			[ ] 
			[ ] ImageDirector1.StoreCurrentCookieData()
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] ImageDirector1.VerifyImage()
			[ ] ImageDirector1.VerifyCookieNotRefreshed()
			[ ] 
		[-] testcase ECN9_1() appstate none		//stale (26)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(ON)
			[ ] //execute
			[ ] ImageDirector1.MakeCalibratedCookie()
			[ ] BrowserSupport.Close()
			[ ] 
			[ ] ImageDirector1.StoreCurrentCookieData()
			[ ] 
			[ ] EColorServers.WaitForStale()
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] ImageDirector1.VerifyImage()
			[ ] ImageDirector1.VerifyCookieRefreshed()
			[ ] 
		[ ] 
		[ ] // 10.	Fresh/Stale a calibrated User visiting opted-in Limited ECN
		[ ] // Result: Regular cookie update for stale user and no changes for cookie for Fresh user, 
		[ ] // and correctable images are served from E-Color Image server with custom end user 
		[ ] // viewing profile
		[-] testcase ECN10() appstate none		//fresh (27)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(ON)
			[ ] //execute
			[ ] ImageDirector1.MakeCalibratedCookie()
			[ ] BrowserSupport.Close()
			[ ] 
			[ ] ImageDirector1.StoreCurrentCookieData()
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] ImageDirector1.VerifyImage()
			[ ] ImageDirector1.VerifyCookieNotRefreshed()
			[ ] 
		[-] testcase ECN10_1() appstate none	//stale (28)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(ON)
			[ ] //execute
			[ ] ImageDirector1.MakeCalibratedCookie()
			[ ] BrowserSupport.Close()
			[ ] 
			[ ] ImageDirector1.StoreCurrentCookieData()
			[ ] 
			[ ] EColorServers.WaitForStale()
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] //verify
			[ ] ImageDirector1.VerifyImage()
			[ ] ImageDirector1.VerifyCookieRefreshed()
			[ ] 
		[ ] 
		[ ] // Disabled cookie function on Internet Browser
		[ ] // 11.	New User with disabled cookie function on their Internet Browser visiting 
		[ ] // opted-in Limited ECN or opted-out Limited ECN or Existing TIC
		[ ] // Result: No cookie bounce, and all correctable images are served from original customer 
		[ ] // web site
		[-] testcase ECN11() appstate none //  (29)
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseID2
				[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
				[ ] //setup
				[ ] BrowserSupport.SetCookieMode(CM_REJECT)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] ImageDirector2.SetECNState(OFF)
				[ ] 
				[ ] //execute
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] BrowserSupport.Close()
				[ ] ImageDirector2.OpenHelloWorldPage()
				[ ] 
				[ ] //verify
				[ ] ImageDirector2.VerifyImage()
				[ ] EColorServers.VerifyCookieDoesNotExist()
				[ ] ImageDirector1.VerifyCookieDoesNotExist()
				[ ] ImageDirector2.VerifyCookieDoesNotExist()
		[ ] 
		[ ] // 11.1 Existing User with (uncalibrated/calibrated) cookie, changed browser setting to 
		[ ] // disable cookie function on their Internet Browser visiting opted-in Limited ECN or 
		[ ] // opted-out Limited ECN or Existing TIC
		[ ] // Result: No cookie bounce, and all correctable images are served from original customer 
		[ ] // web site
		[-] testcase ECN11_1() appstate none	// uncalibrated, opt-in (30)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(ON)
			[ ] 
			[ ] BrowserSupport.SetCookieMode(CM_REJECT)
			[ ] 
			[ ] //execute
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] 
			[ ] //verify
			[ ] ImageDirector1.VerifyImageNoCorrection()
			[ ] EColorServers.VerifyCookieDoesNotExist()
			[ ] ImageDirector1.VerifyCookieDoesNotExist()
			[ ] 
		[-] testcase ECN11_2() appstate none	//   calibrated, opt-in (31)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(ON)
			[ ] 
			[ ] ImageDirector1.DoDefaultTuneUp()
			[ ] BrowserSupport.SetCookieMode(CM_REJECT)
			[ ] 
			[ ] //execute
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] 
			[ ] //verify
			[ ] ImageDirector1.VerifyImageNoCorrection()
			[ ] EColorServers.VerifyCookieDoesNotExist()
			[ ] ImageDirector1.VerifyCookieDoesNotExist()
			[ ] 
		[-] testcase ECN11_3() appstate none	// uncalibrated, opt-out (32)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] 
			[ ] BrowserSupport.SetCookieMode(CM_REJECT)
			[ ] 
			[ ] //execute
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] 
			[ ] //verify
			[ ] ImageDirector1.VerifyImageNoCorrection()
			[ ] EColorServers.VerifyCookieDoesNotExist()
			[ ] ImageDirector1.VerifyCookieDoesNotExist()
			[ ] 
		[-] testcase ECN11_4() appstate none	//   calibrated, opt-in (33)
			[ ] //testcaseenter does close browser, clear cache, set cookie mode to accept
			[ ] //setup
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] 
			[ ] ImageDirector1.DoDefaultTuneUp()
			[ ] BrowserSupport.SetCookieMode(CM_REJECT)
			[ ] 
			[ ] //execute
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] 
			[ ] //verify
			[ ] ImageDirector1.VerifyImageNoCorrection()
			[ ] EColorServers.VerifyCookieDoesNotExist()
			[ ] ImageDirector1.VerifyCookieDoesNotExist()
			[ ] 
		[ ] 
		[ ] 
		[ ] 
		[ ] // ·	Image Server is down and ImageServerWatchDog  = On
		[ ] // 12.	New or Fresh (calibrated or not) or Stale (calibrated or not) User visiting 
		[ ] // opted-in Limited ECN or opted-out Limited ECN or Existing TIC while Image Server is 
		[ ] // down and ImageServerWatchDog  = On
		[ ] // Result: No cookie bounce, and all correctable images are served from original customer 
		[ ] // web site
		[-] testcase ECN12_1() appstate none // Image Server Down, Watchdog on, fresh, uncalibrated, opt in (34)
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] ImageDirector1.VerifyImageNoCorrection()
		[-] testcase ECN12_2() appstate none // Image Server Down, Watchdog on, fresh, uncalibrated, opt out (35)
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] ImageDirector1.VerifyImageNoCorrection()
		[-] testcase ECN12_3() appstate none // Image server down, watchdog on, fresh, calibrated, opt in (36)
			[ ] ImageDirector1.DoDefaultTuneUp()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] ImageDirector1.VerifyImageNoCorrection()
		[-] testcase ECN12_4() appstate none // Image server down, watchdog on, fresh, calibrated, opt out (37)
			[ ] ImageDirector1.DoDefaultTuneUp()
			[ ] BrowserSupport.Close()
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] ImageDirector1.VerifyImageNoCorrection()
			[ ] 
		[-] testcase ECN12_5() appstate none // Image Server Down, Watchdog on, stale, uncalibrated, opt in (38)
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.WaitForStale()
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] ImageDirector1.VerifyImageNoCorrection()
		[-] testcase ECN12_6() appstate none // Image Server Down, Watchdog on, stale, uncalibrated, opt out (39)
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.WaitForStale()
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] ImageDirector1.VerifyImageNoCorrection()
		[-] testcase ECN12_7() appstate none // Image server down, watchdog on, stale, calibrated, opt in (40)
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.WaitForStale()
			[ ] ImageDirector1.DoDefaultTuneUp()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] ImageDirector1.VerifyImageNoCorrection()
		[-] testcase ECN12_8() appstate none // Image server down, watchdog on, stale, calibrated, opt out (41)
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.WaitForStale()
			[ ] ImageDirector1.DoDefaultTuneUp()
			[ ] BrowserSupport.Close()
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] ImageDirector1.VerifyImageNoCorrection()
			[ ]  
	[ ] 
	[-] // group 3 - Misc (cases 42 thru 42)
		[ ] // 25.	All possible variations of browser and OS as listed in the 
		[ ] // browser gauntlet
		[ ] 
		[-] testcase Misc1() appstate none
			[ ] raise 1, "Browser gauntlet not implemented"
		[ ] 
	[ ] 
	[+] // group 4 - GeoCaching1 (cases 42 thru 54)
		[ ] 
		[ ] // ·	Image Server is down and ImageServerWatchDog  = On
		[ ] // 13.	Image Server is down and both entries in TicImageDirector.properties file for Akamai are "ON"
		[ ] // 
		[ ] // GeoCache.EnableTranslation  = ON
		[ ] // GeoCache.TranslateAllImgSrc = ON
		[ ] // Verify that images are served from Akamai.
		[-] testcase GC1() appstate none  				// 43
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(OFF)
				[ ] ImageDirector1.SetGeoCacheStateToDefault(TRUE)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] BrowserSupport.Close()
				[ ] EColorServers.ImageServer.ServerOff()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] 
		[ ] // ECN opted On/Off	GeoCache.EnableTranslation  On/Off	GeoCache.TranslateAllImgSrc On/Off
		[ ] // Off	Off	Off
		[ ] // 14.	New or Fresh (calibrated or not) or Stale (calibrated or not) User while Image Server 
		[ ] // is down and ImageServerWatchDog = On
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable, nonAkamaised 
		[ ] // images are served from original customer web site.
		[ ] // ECN:off GC:off TAIS:off
		[-] testcase GC2() appstate none		//44
			[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
			[ ] ImageDirector1.SetGeoCacheAllImgSrcState(OFF)
			[ ] ImageDirector1.SetGeoCacheState(OFF)
			[ ] ImageDirector1.SetECNState(OFF)
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] 
			[ ] ImageDirector1.VerifyImage()
			[ ] 
		[ ] 
		[ ] // ECN:Off	GC:On	TAIS:Off
		[ ] // 15.	New or Fresh (calibrated or not) or Stale (calibrated or not) User while Image Server is down 
		[ ] // and ImageServerWatchDog  = OnResult: Regular cookie bounce or regular cookie update, and all 
		[ ] // correctable, nonAkamaised images are served from original customer web site.
		[-] testcase GC3() appstate none		//45
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(OFF)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] BrowserSupport.Close()
				[ ] EColorServers.ImageServer.ServerOff()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // ECN:Off	GC:On	TAIS:On
		[ ] // 16.	New or Fresh (calibrated or not) or Stale (calibrated or not) User while Image Server is down 
		[ ] // and ImageServerWatchDog  = On 
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable, Akamaised 
		[ ] // images are served from original customer web site.                                                                                                                                                                        
		[ ] // ECN opted On/Off	GeoCache.EnableTranslation  On/Off	GeoCache.TranslateAllImgSrc On/Off
		[-] testcase GC4() appstate none		//46
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] BrowserSupport.Close()
				[ ] EColorServers.ImageServer.ServerOff()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
				[ ] 
				[ ] // ECN:On	GC:Off	TAIS:Off
				[ ] // 17.	New or Fresh (calibrated or not) or Stale (calibrated or not) User while Image Server is down 
				[ ] // and ImageServerWatchDog  = On
				[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable, Akamaised 
				[ ] // images are served from original customer web site.
		[-] testcase GC5() appstate none		//47
			[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
			[ ] ImageDirector1.SetGeoCacheAllImgSrcState(OFF)
			[ ] ImageDirector1.SetGeoCacheState(OFF)
			[ ] ImageDirector1.SetECNState(ON)
			[ ] 
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] BrowserSupport.Close()
			[ ] EColorServers.ImageServer.ServerOff()
			[ ] ImageDirector1.OpenHelloWorldPage()
			[ ] 
			[ ] ImageDirector1.VerifyImage()
			[ ] 
		[ ] 
		[ ] // ECN:On	GC:On	TAIS:Off
		[ ] // 18.	New or Fresh (calibrated or not) or Stale (calibrated or not) User while Image Server is down 
		[ ] // and ImageServerWatchDog  = On
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable, Akamaised 
		[ ] // images are served from original customer web site.
		[-] testcase GC6() appstate none		//48
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] BrowserSupport.Close()
				[ ] EColorServers.ImageServer.ServerOff()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // ECN:On	GC:On	TAIS:On
		[ ] // 19.	New or Fresh (calibrated or not) or Stale (calibrated or not) User while Image Server is 
		[ ] // down and ImageServerWatchDog  = On
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable, Akamaised images 
		[ ] // are served from original customer web site. Cookie Fresh/Stale Timeout has been updated.
		[-] testcase GC7() appstate none		//49
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] BrowserSupport.Close()
				[ ] EColorServers.ImageServer.ServerOff()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // Profile Server is down and ProfileServerWatchDog  = On
		[ ] // 20.	New User visiting opted-out Limited ECN or Existing TIC while Profile 
		[ ] // Server is down and ProfileServerWatchDog  = On
		[ ] // Result: No cookie bounce, and all correctable images are served from 
		[ ] // original customer web site
		[-] testcase GC8() appstate none		//50
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] ImageDirector1.SetProfileServerWatchdogState(ON)
				[ ] 
				[ ] EColorServers.StoreCurrentCookieData()
				[ ] EColorServers.ProfileServer.ServerOff()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImageNoCorrection()
				[ ] ImageDirector1.VerifyCookieDoesNotExist()
				[ ] EColorServers.VerifyCookieNotRefreshed()
				[ ] 
		[ ] 
		[ ] // 21.	Fresh (uncalibrated) or Stale (uncalibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Profile Server is down and 
		[ ] // ProfileServerWatchDog  = On
		[ ] // Result: No cookie bounce (Fresh/Stale timestamp for cookie may be updated), 
		[ ] // and all correctable images are served from original customer web site
		[-] testcase GC9() appstate none		//51
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] ImageDirector1.SetProfileServerWatchdogState(ON)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] EColorServers.StoreCurrentCookieData()
				[ ] EColorServers.ProfileServer.ServerOff()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImageNoCorrection()
				[ ] EColorServers.VerifyCookieNotRefreshed()
				[ ] 
		[ ] 
		[ ] // 22.	Fresh (calibrated) or Stale (calibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Profile Server is down and 
		[ ] // ProfileServerWatchDog  = On
		[ ] // Result: No cookie bounce (Fresh/Stale timestamp for cookie may be updated), 
		[ ] // and all correctable images are served from E-Color Image server with custom 
		[ ] // end user viewing profile
		[-] testcase GC10() appstate none		//52
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] ImageDirector1.SetProfileServerWatchdogState(ON)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] EColorServers.StoreCurrentCookieData()
				[ ] EColorServers.ProfileServer.ServerOff()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] EColorServers.VerifyCookieNotRefreshed()
				[ ] 
		[ ]  
		[ ] // 23.	New or Fresh (uncalibrated) or Stale (uncalibrated) User visiting 
		[ ] // opted-in Limited ECN while Profile Server is down and 
		[ ] // ProfileServerWatchDog  = On
		[ ] // Result: No cookie bounce (Fresh, Stale timestamp for cookie may be 
		[ ] // updated), and all correctable images are served from E-Color Image server 
		[ ] // with average viewing profile
		[-] testcase GC11() appstate none		//53
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] ImageDirector1.SetProfileServerWatchdogState(ON)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] EColorServers.StoreCurrentCookieData()
				[ ] EColorServers.ProfileServer.ServerOff()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImageNoCorrection()
				[ ] EColorServers.VerifyCookieNotRefreshed()
				[ ] 
		[ ] 
		[ ] // 24.	Fresh (calibrated) or Stale (calibrated) User visiting opted-in 
		[ ] // Limited ECN while Profile Server is down and 
		[ ] // ProfileServerWatchDog  = On
		[ ] // Result: No cookie bounce (Fresh/Stale timestamp for cookie may be 
		[ ] // updated), and all correctable images are served from E-Color Image 
		[ ] // server with custom end user viewing profile
		[-] testcase CG12() appstate none		//54
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] ImageDirector1.SetProfileServerWatchdogState(ON)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] EColorServers.StoreCurrentCookieData()
				[ ] EColorServers.ProfileServer.ServerOff()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] EColorServers.VerifyCookieNotRefreshed()
				[ ]  
	[ ] 
	[+] // group 5 - GeoCaching2 -> Akamai with ECN (cases 55 thru 64)
		[ ] 
		[ ] // Test Cases for Limited ECN Dispatcher with Geographical Caching enable
		[ ] // 
		[ ] // Note: For more information $/Documents/QA/Test Plans/ChromaServe/Akamai - 
		[ ] // Functional Test Plan.doc in VSS.
		[ ] // 
		[ ] // Note: ECN Button - since Akamai checks fingerprints for the image, 
		[ ] // "average" and "full" images must exist on the customer website under 
		[ ] // same root as they were published (/public).
		[ ] // ECN Button has the same behavior as images.
		[ ] // 
		[ ] // Geographical Caching functionality for Any TIC Dispatcher can be 
		[ ] // enabling in property file for TIC Dispatcher (TicImageDirector.properties). 
		[ ] // Geographical Caching can be enable only for correctable images.
		[ ] // There are two lines in property file:
		[ ] // GeoCache.EnableTranslation  = Off - if "ON" - enable Geographical Caching 
		[ ] // only for correctable images for Calibrated User
		[ ] // GeoCache.TranslateAllImgSrc = Off - if "ON" - enable Geographical Caching 
		[ ] // for correctable images for Uncalibrated User
		[ ] // 
		[ ] // ·	Akamai:
		[ ] // Line: GeoCache.Manager.Class = com.cs.GeoCache.AkamaiGeoCache for TIC Dispatcher 
		[ ] // property file should exist
		[ ] // 
		[ ] // ·	Geographical Caching enabled for Correctable Images for Calibrated User
		[ ]  
		[ ] 
		[ ] // 26.	New User visiting opted-out Limited ECN or Existing TIC while 
		[ ] // Geographical Caching enabled for Correctable Images for Calibrated User
		[ ] // Result: Regular cookie bounce, and all correctable images are served from 
		[ ] // original customer web site
		[-] testcase GCECNA_1() appstate none		//55
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImageNoCorrection()
				[ ] 
		[ ] 
		[ ] // 27.	Fresh (uncalibrated) or Stale (uncalibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated User
		[ ] // Result: Regular cookie update, and all correctable images are served from 
		[ ] // original customer web site
		[-] testcase GCECNA_2() appstate none		//56
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] EColorServers.WaitForStale()
				[ ] BrowserSupport.Close()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ]  
		[ ] // 28.	Fresh (calibrated) or Stale (calibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated User
		[ ] // Result: Regular cookie update, and all correctable images are served from 
		[ ] // Akamai with custom end user viewing profile
		[-] testcase GCECNA_3() appstate none		//57
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] BrowserSupport.Close()
				[ ] EColorServers.StoreCurrentCookieData()
				[ ] EColorServers.WaitForStale()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] EColorServers.VerifyCookieRefreshed()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 29.	New or Fresh (uncalibrated) or Stale (uncalibrated) User visiting 
		[ ] // opted-in Limited ECN while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated User
		[ ] // Result: Regular cookie update, and all correctable images are served from 
		[ ] // Akamai with average viewing profile
		[-] testcase GCECNA_4() appstate none		//58
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 30.	Fresh (calibrated) or Stale (calibrated) User visiting opted-in 
		[ ] // Limited ECN while Geographical Caching enabled for Correctable Images 
		[ ] // for Calibrated User
		[ ] // Result: Regular cookie update, and all correctable images are served 
		[ ] // from Akamai with custom end user viewing profile
		[-] testcase GCECNA_5() appstate none		//59
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] BrowserSupport.Close()
				[ ] EColorServers.WaitForStale()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // ·	Geographical Caching enabled for Correctable Images for Calibrated 
		[ ] // and Uncalibrated User
		[ ] // Both line for TIC Dispatcher property file should be  = ON
		[ ] // 
		[ ] // GeoCache.EnableTranslation  = On - if "ON" - enable Geographical Caching 
		[ ] // only for correctable images, while End User Calibrated
		[ ] // GeoCache.TranslateAllImgSrc = On - if "ON" - enable Geographical Caching 
		[ ] // for correctable images while End User uncalibrated
		[ ] // 
		[ ] // 31.	New User visiting opted-out Limited ECN or Existing TIC while 
		[ ] // Geographical Caching enabled for Correctable Images for Calibrated and 
		[ ] // Uncalibrated User
		[ ] // Result: Regular cookie bounce, and all correctable (uncalibrated) images 
		[ ] // are served from Akamai
		[-] testcase GCECNA_6() appstate none		//60
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 32.	Fresh (uncalibrated) or Stale (uncalibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated and Uncalibrated User
		[ ] // Result: Regular cookie update, and all correctable (uncalibrated) images are 
		[ ] // served from Akamai
		[-] testcase GCECNA_7() appstate none		//61
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] EColorServers.WaitForStale()
				[ ] BrowserSupport.Close()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 33.	Fresh (calibrated) or Stale (calibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated and Uncalibrated User
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable 
		[ ] // images are served from Akamai with custom end user viewing profile
		[-] testcase GCENCA_8() appstate none		//62
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] EColorServers.WaitForStale()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 34.	New or Fresh (uncalibrated) or Stale (uncalibrated) User visiting 
		[ ] // opted-in Limited ECN while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated and Uncalibrated User
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable 
		[ ] // images are served from Akamai with average viewing profile
		[-] testcase GCECNA_9() appstate none		//63
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 35.	Fresh (calibrated) or Stale (calibrated) User visiting opted-in Limited 
		[ ] // ECN while Geographical Caching enabled for Correctable Images for Calibrated 
		[ ] // and Uncalibrated User
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable 
		[ ] // images are served from Akamai with custom end user viewing profile
		[-] testcase GCECNA_10() appstate none		//64
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseAkamai
				[ ] ImageDirector1.SetGeoCacheProvider(GP_AKAMAI)
				[ ] ImageDirector1.SetGeoCacheAllImgSrcState(ON)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] EColorServers.WaitForStale()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
	[ ] 
	[+] // group 6 - GeoCaching3 -> Footprint with ECN (cases 65 thru 74)
		[ ] 
		[ ] // ·	FootPrint
		[ ] // 
		[ ] // Line: GeoCache.Manager.Class = com.cs.GeoCache.FootprintGeoCache for TIC 
		[ ] // Dispatcher property file should exist
		[ ] // 
		[ ] // Same behaviors as listed above for Akamai, only different Geographical 
		[ ] // Caching server provider. Also FootPrint cannot support 
		[ ] // GeoCache.TranslateAllImgSrc option.
		[ ] //  See test cases for Akamai above.
		[ ] //
		[ ] // 26.	New User visiting opted-out Limited ECN or Existing TIC while 
		[ ] // Geographical Caching enabled for Correctable Images for Calibrated User
		[ ] // Result: Regular cookie bounce, and all correctable images are served from 
		[ ] // original customer web site
		[ ] 
		[-] testcase GCECNF_1() appstate none		//65
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImageNoCorrection()
				[ ] 
		[ ] 
		[ ] // 27.	Fresh (uncalibrated) or Stale (uncalibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated User
		[ ] // Result: Regular cookie update, and all correctable images are served from 
		[ ] // original customer web site
		[-] testcase GCECNF_2() appstate none		//66
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] EColorServers.WaitForStale()
				[ ] BrowserSupport.Close()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ]  
		[ ] // 28.	Fresh (calibrated) or Stale (calibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated User
		[ ] // Result: Regular cookie update, and all correctable images are served from 
		[ ] // Akamai with custom end user viewing profile
		[-] testcase GCECNF_3() appstate none		//67
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] BrowserSupport.Close()
				[ ] EColorServers.StoreCurrentCookieData()
				[ ] EColorServers.WaitForStale()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] EColorServers.VerifyCookieRefreshed()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 29.	New or Fresh (uncalibrated) or Stale (uncalibrated) User visiting 
		[ ] // opted-in Limited ECN while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated User
		[ ] // Result: Regular cookie update, and all correctable images are served from 
		[ ] // Akamai with average viewing profile
		[-] testcase GCECNF_4() appstate none		//68
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 30.	Fresh (calibrated) or Stale (calibrated) User visiting opted-in 
		[ ] // Limited ECN while Geographical Caching enabled for Correctable Images 
		[ ] // for Calibrated User
		[ ] // Result: Regular cookie update, and all correctable images are served 
		[ ] // from Akamai with custom end user viewing profile
		[-] testcase GCECNF_5() appstate none		//69
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] BrowserSupport.Close()
				[ ] EColorServers.WaitForStale()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // ·	Geographical Caching enabled for Correctable Images for Calibrated 
		[ ] // and Uncalibrated User
		[ ] // Both line for TIC Dispatcher property file should be  = ON
		[ ] // 
		[ ] // GeoCache.EnableTranslation  = On - if "ON" - enable Geographical Caching 
		[ ] // only for correctable images, while End User Calibrated
		[ ] // GeoCache.TranslateAllImgSrc = On - if "ON" - enable Geographical Caching 
		[ ] // for correctable images while End User uncalibrated
		[ ] // 
		[ ] // 31.	New User visiting opted-out Limited ECN or Existing TIC while 
		[ ] // Geographical Caching enabled for Correctable Images for Calibrated and 
		[ ] // Uncalibrated User
		[ ] // Result: Regular cookie bounce, and all correctable (uncalibrated) images 
		[ ] // are served from Akamai
		[-] testcase GCECNF_6() appstate none		//70
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] 
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 32.	Fresh (uncalibrated) or Stale (uncalibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated and Uncalibrated User
		[ ] // Result: Regular cookie update, and all correctable (uncalibrated) images are 
		[ ] // served from Akamai
		[-] testcase GCECNF_7() appstate none		//71
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] EColorServers.WaitForStale()
				[ ] BrowserSupport.Close()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 33.	Fresh (calibrated) or Stale (calibrated) User visiting opted-out 
		[ ] // Limited ECN or Existing TIC while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated and Uncalibrated User
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable 
		[ ] // images are served from Akamai with custom end user viewing profile
		[-] testcase GCENCF_8() appstate none		//72
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(OFF)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] EColorServers.WaitForStale()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 34.	New or Fresh (uncalibrated) or Stale (uncalibrated) User visiting 
		[ ] // opted-in Limited ECN while Geographical Caching enabled for Correctable 
		[ ] // Images for Calibrated and Uncalibrated User
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable 
		[ ] // images are served from Akamai with average viewing profile
		[-] testcase GCECNF_9() appstate none		//73
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ] 
		[ ] // 35.	Fresh (calibrated) or Stale (calibrated) User visiting opted-in Limited 
		[ ] // ECN while Geographical Caching enabled for Correctable Images for Calibrated 
		[ ] // and Uncalibrated User
		[ ] // Result: Regular cookie bounce or regular cookie update, and all correctable 
		[ ] // images are served from Akamai with custom end user viewing profile
		[-] testcase GCECNF_10() appstate none		//74
			[-] if TestProps.TestFlags.ExecuteTestsWhichUseFootprint
				[ ] ImageDirector1.SetGeoCacheProvider(GP_FOOTPRINT)
				[ ] ImageDirector1.SetGeoCacheState(ON)
				[ ] ImageDirector1.SetECNState(ON)
				[ ] 
				[ ] ImageDirector1.DoDefaultTuneUp()
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] EColorServers.WaitForStale()
				[ ] BrowserSupport.Close()
				[ ] 
				[ ] ImageDirector1.OpenHelloWorldPage()
				[ ] ImageDirector1.VerifyImage()
				[ ] 
		[ ]  
		[ ] 
	[ ] 
[ ] ////////////////////////////////////////////////////////////
[ ] 
