[ ] //	*********************
[ ] //	*	REGISTRY.INC	*
[ ] //	*********************************************************************************************************
[ ] //	*																										*
[ ] //	*	Registry functions for creating and deleting keys													*
[ ] //	*																										*
[ ] //	*	Reg_CreateKey		-	Creates a new subkey off of an existing path.								*
[ ] //	*	Reg_CreateValue		-	Creates a value in a key with the specified data.							*
[ ] //	*							Also creates the key if necessary.											*
[ ] //	*	Reg_DeleteKey		-	Deletes a registry key.														*
[ ] //	*	Reg_DeleteKeysAll	-	Deletes a registry key, including all keys and values below that key.		*
[ ] //	*	Reg_DeleteValue		-	Deletes a value in a key.													*
[ ] //	*	Reg_EnumKeys		-	Returns the list of subkeys directly beneath the specified key.				*
[ ] //  *   							The paths of the subkeys are relative to sPath.							*
[ ] //	*	Reg_EnumKeysAll		-	Returns the list of all layers of subkeys beneath the specified key.		*
[ ] //  *   							The paths of the subkeys are relative to sPath.							*
[ ] //	*	Reg_EnumValues		-	Returns the list of values belonging to the specified key.					*
[ ] //	*	Reg_EnumValuesAll	-	Returns a list of values and all layers of subkey values. The names of the	*
[ ] //  *   							values include the path of the containing subkey relative to sPath.		*
[ ] //	*	Author: Sharon Rozines																				*
[ ] //	*	Copyright ©2001-2003 by Segue Software, Inc.																*
[ ] //	*																										*
[ ] //	*********************************************************************************************************
[ ] 
[ ] use "mswconst.inc"			// includes definitions for root keys
[ ] 
[+] // Records (Structures)
	[+] type FILETIME is record
		[ ] LONG dwLowDateTime
		[ ] LONG dwHighDateTime
	[+] type REGVALUE is record
		[ ] STRING sValueName
		[ ] STRING sValueData
[ ] 
[+] // Constants and enumerated types
	[ ] const READ_CONTROL = 0x20000
	[ ] const SYNCHRONIZE = 0x100000
	[ ] const STANDARD_RIGHTS_READ = (READ_CONTROL)
	[ ] const STANDARD_RIGHTS_WRITE = (READ_CONTROL) 
	[ ] const KEY_QUERY_VALUE = 0x1
	[ ] const KEY_SET_VALUE = 0x2 
	[ ] const KEY_CREATE_SUB_KEY = 0x4
	[ ] const KEY_ENUMERATE_SUB_KEYS = 0x8
	[ ] const KEY_NOTIFY = 0x10
	[ ] const KEY_READ =  ((STANDARD_RIGHTS_READ  | KEY_QUERY_VALUE |KEY_ENUMERATE_SUB_KEYS | KEY_NOTIFY) & (~SYNCHRONIZE))
	[ ] const KEY_WRITE = ((STANDARD_RIGHTS_WRITE | KEY_SET_VALUE |KEY_CREATE_SUB_KEY) & (~ SYNCHRONIZE))
	[ ] const LONG MAX_CHARS_NAME = 256	 // added by SRozines
	[ ] const LONG MAX_CHARS_DATA = 1024 // added by SRozines
	[ ] 
	[+] type REG_ERROR is enum
		[ ] ERROR_SUCCESS = 0
		[ ] ERROR_FILE_NOT_FOUND = 2
		[ ] ERROR_INVALID_HANDLE = 6
		[ ] ERROR_MORE_DATA = 234
		[ ] ERROR_NO_MORE_ITEMS = 259
		[ ] ERROR_BADKEY = 1010
		[ ] ERROR_CANTOPEN = 1011
		[ ] ERROR_CANTREAD = 1012
		[ ] ERROR_CANTWRITE = 1013
		[ ] ERROR_OTHER = 9999	 // added by SRozines
		[ ] 
	[+] type REG_DATA is enum
		[ ] REG_NONE   = 0
		[ ] REG_SZ     = 1
		[ ] REG_BINARY = 3
		[ ] REG_DWORD  = 4
[ ] 
[+] // DLL declarations
	[+] dll "advapi32.dll"
		[ ] LONG RegCloseKey (LONG hKey)
		[ ] LONG RegCreateKeyEx (LONG hKey, STRING lpSubKey, LONG Reserved, STRING lpClass, LONG dwOptions, LONG samDesired, LONG lpSecurityAttributes, out LONG phkResult, out LONG lpdwDisposition) alias "RegCreateKeyExA"
		[ ] LONG RegDeleteKey (LONG hKey, STRING lpSubKey) alias "RegDeleteKeyA" 
		[ ] LONG RegDeleteValue (LONG hKey, STRING lpValueName) alias "RegDeleteValueA"
		[ ] LONG RegEnumKeyEx (LONG hKey, LONG dwIndex, out STRING lpName, inout LONG lpcName, LONG Reserved, inout STRING lpClass null, inout LONG lpcClass, out FILETIME lpftLastWriteTime) alias "RegEnumKeyExA"
		[ ] LONG RegEnumValue (LONG hKey, LONG dwIndex, out STRING lpValueName, inout LONG lpcValueName, LONG Reserved, out STRING lpType null, out STRING lpData null, inout LONG lpcbData) alias "RegEnumValueA"
		[ ] LONG RegOpenKeyEx (LONG hKey, STRING lpSubKey, LONG ulOptions, LONG samDesired, out LONG phkResult) alias "RegOpenKeyExA"
		[ ] LONG RegQueryValueEx (LONG hKey, STRING lpValueName, LONG lpReserved, inout LONG lpType, inout STRING lpData, inout LONG lpcbData) alias "RegQueryValueExA"
		[ ] LONG RegSetValueEx( LONG hKey, STRING lpValueName, LONG Reserved, LONG dwType, STRING lpData, LONG cbData ) alias "RegSetValueExA" 
[ ] 
[+] // Functions
	[+] private STRING GetRegRetCode (LONG lRet)
		[ ] STRING sRegRetCode = ""
		[ ] 
		[+] do
			[ ] sRegRetCode = "{[REG_ERROR]lRet}"
		[+] except
			[+] if ExceptNum () == E_INCOMPAT_TYPES
				[ ] sRegRetCode = "{lRet}"
			[+] else
				[ ] reraise
		[ ] 
		[ ] return sRegRetCode
	[ ] 
	[+] void Reg_CreateKey (LONG hRootKey, STRING sKeyPath)
		[+] //	***	LIBRARY BROWSER 'CODE'	***
			[ ] //	function:  Reg_CreateKey (hRootKey, sKeyPath)
			[ ] //	parameter: hRootKey: the constant (from mswconst.inc; e.g., HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE) for the root key (LONG)
			[ ] //	parameter: sKeyPath: the path to the key to be created (STRING)
			[ ] //	notes:     Creates a new key, including any ancestors that do not already exist.
			[ ] //  notes:     Example: Reg_CreateKey (HKEY_LOCAL_MACHINE, "Software\Company\Product\Version"))
		[ ] 
		[ ] LONG hNewKey, lDisposition, lRet
		[ ] 
		[ ] lRet = RegCreateKeyEx (hRootKey, sKeyPath, 0, "", 0, KEY_WRITE, 0, hNewKey, lDisposition)
		[+] do
			[ ] RegCloseKey (hNewKey)
		[+] except
			[ ] // Key probably was never created, but the next error will alert the user of this
		[ ] 
		[+] if (lRet != ERROR_SUCCESS)
			[ ] RaiseError (1, "Could not create key '{sKeyPath}' (return code {GetRegRetCode (lRet)}.")
		[ ] 
	[+] void Reg_CreateValue (LONG hRootKey, STRING sPath, STRING sValueName, STRING sValueData)
		[+] //	***	LIBRARY BROWSER 'CODE'	***
			[ ] //	function:  Reg_CreateValue (hRootKey, sPath, sValueName, sValueData)
			[ ] //	parameter: hRootKey: the constant (from mswconst.inc; e.g., HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE) for the root key (LONG)
			[ ] //	parameter: sPath: the full path of the key containing the value to be deleted (STRING)
			[ ] //  parameter: sValueName: the name of the value to be deleted (STRING)
			[ ] //  parameter: sValueData: the data for the value; supports string, binary and DWORD values, using the format used by SYS_SetRegistryValue() (STRING)
			[ ] //	notes:     Creates a value in a key with the specified data.
			[ ] //  notes:     Example: Reg_CreateValue (HKEY_LOCAL_MACHINE, "Software\Company\Product", "Directory", "C:\TEMP"))
		[ ] 
		[ ] LONG hKey, lDisposition, lRet
		[ ] REG_DATA rdType
		[ ] STRING sType
		[ ] 
		[ ] // Create the value and set its data in two separate steps, since SYS_SetRegistryValue()
		[ ] // cannot be used to create a new value.
		[ ] 
		[ ] // Create an empty value (no data).
		[ ] // Find the data type of the value. If there is no prefix, assume it is a string.
		[+] if (MatchStr ("REG_*:*", sValueData))
			[ ] sType = Upper (Trim (GetField (sValueData, ":", 1)))
			[+] switch sType
				[+] case "REG_SZ"
					[ ] rdType = REG_SZ
				[+] case "REG_BINARY"
					[ ] rdType = REG_BINARY
				[+] case "REG_DWORD"
					[ ] rdType = REG_DWORD
				[+] default
					[ ] RaiseError (E_TYPE_MISMATCH, "Unknown data type prefix: {sType}")
		[+] else
			[ ] rdType = REG_SZ
		[ ] 
		[ ] // Use RegCreateKeyEx() to open the key containing the value, since RegOpenKeyEx() will not
		[ ] // create the key if it does not exist.
		[ ] RegCreateKeyEx (hRootKey, sPath, 0, "", 0, KEY_WRITE, 0, hKey, lDisposition)
		[ ] lRet = RegSetValueEx (hKey, sValueName, 0, [LONG]rdType, "", 0)
		[ ] RegCloseKey (hKey)
		[ ] 
		[+] if (lRet != ERROR_SUCCESS)
			[+] switch lRet
				[+] case ERROR_BADKEY
					[ ] RaiseError (ERROR_BADKEY, "Could not create value '{sValueName}' of key '{sPath}': key did not exist.")
				[+] default
					[ ] RaiseError (ERROR_OTHER, "Could not create value '{sValueName}' of key '{sPath}' (return code {GetRegRetCode (lRet)}).")
		[ ] 
		[ ] // Set the data for the value using the built-in 4Test function.
		[ ] SYS_SetRegistryValue (hRootKey, sPath, sValueName, sValueData)
		[ ] 
	[ ] 
	[+] void Reg_DeleteKey (LONG hRootKey, STRING sPath)
		[+] //	***	LIBRARY BROWSER 'CODE'	***
			[ ] //	function:  Reg_DeleteKey (hRootKey, sPath)
			[ ] //	parameter: hRootKey: the constant (from mswconst.inc; e.g., HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE) for the root key (LONG)
			[ ] //	parameter: sPath: the full path of the key to be deleted (STRING)
			[ ] //	notes:     Deletes a registry key.
			[ ] //  notes:     Example: Reg_DeleteKey (HKEY_LOCAL_MACHINE, "Software\Company\Product"))
		[ ] 
		[ ] LONG lRet
		[ ] 
		[ ] lRet = RegDeleteKey (hRootKey, sPath)
		[ ] 
		[+] if (lRet != ERROR_SUCCESS)
			[+] switch lRet
				[+] case ERROR_FILE_NOT_FOUND
					[ ] RaiseError (2, "Could not delete key '{sPath}': key did not exist.")
				[+] default
					[ ] RaiseError (ERROR_OTHER, "Could not delete key '{sPath}' (return code {GetRegRetCode (lRet)}).")
		[ ] 
	[+] void Reg_DeleteKeysAll (LONG hRootKey, STRING sPath)
		[+] //	***	LIBRARY BROWSER 'CODE'	***
			[ ] //	function:  Reg_DeleteKeysAll (hRootKey, sPath)
			[ ] //	parameter: hRootKey: the constant (from mswconst.inc; e.g., HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE) for the root key (LONG)
			[ ] //	parameter: sPath: the full path of the key to be deleted (STRING)
			[ ] //	notes:     Deletes a registry key, including all keys and values below that key.
			[ ] //  notes:     Example: Reg_DeleteKeysAll (HKEY_LOCAL_MACHINE, "Software\Company\Product"))
		[ ] 
		[ ] LIST OF REGVALUE lrValues = Reg_EnumValuesAll (hRootKey, sPath)
		[ ] REGVALUE rValue
		[ ] STRING sValPath, sValName, sTmpValName
		[ ] INTEGER iPos
		[ ] 
		[ ] // Delete all values
		[+] for each rValue in lrValues
			[ ] iPos = -1
			[ ] sTmpValName = rValue.sValueName
			[+] while iPos < 0
				[ ] // Make sure that the '\' is not part of '\\', which is used for values that contain internal backslashes.
				[ ] iPos = StrPos ("\", sTmpValName, TRUE)
				[+] if sTmpValName[iPos - 1] == "\"
					[ ] sTmpValName = Left (sTmpValName, iPos - 2)
					[ ] iPos = -1
			[ ] 
			[ ] sValPath = Left (rValue.sValueName, iPos - 1)
			[ ] sValName = SubStr (rValue.sValueName, iPos + 1)
			[ ] Reg_DeleteValue (hRootKey, sPath + sValPath, sValName)
		[ ] 
		[ ] // Delete all keys, from the bottom to the top, including the specified key
		[ ] LIST OF STRING lsKeys = Reg_EnumKeysAll (hRootKey, sPath)
		[ ] INTEGER i
		[+] for i = ListCount (lsKeys) to 1 step -1
			[ ] Reg_DeleteKey (hRootKey, sPath + lsKeys[i])
		[ ] Reg_DeleteKey (hRootKey, sPath)
		[ ] 
	[+] void Reg_DeleteValue (LONG hRootKey, STRING sPath, STRING sValueName)
		[+] //	***	LIBRARY BROWSER 'CODE'	***
			[ ] //	function:  Reg_DeleteValue (hRootKey, sPath, sValueName)
			[ ] //	parameter: hRootKey: the constant (from mswconst.inc; e.g., HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE) for the root key (LONG)
			[ ] //	parameter: sPath: the full path of the key containing the value to be deleted (STRING)
			[ ] //  parameter: sValueName: the name of the value to be deleted (STRING)
			[ ] //	notes:     Deletes a value in a key.
			[ ] //  notes:     Example: Reg_DeleteValue (HKEY_LOCAL_MACHINE, "Software\Company\Product\1.0", "Directory"))
		[ ] 
		[ ] LONG hKey, lRet
		[ ] 
		[ ] RegOpenKeyEx (hRootKey, sPath, 0, KEY_WRITE, hKey )
		[ ] lRet = RegDeleteValue (hKey, sValueName)
		[ ] RegCloseKey (hKey)
		[ ] 
		[+] if (lRet != ERROR_SUCCESS)
			[+] switch lRet
				[+] case ERROR_FILE_NOT_FOUND
					[ ] RaiseError (ERROR_FILE_NOT_FOUND, "Could not delete value '{sValueName}' of key '{sPath}': value did not exist.")
				[+] case ERROR_BADKEY
					[ ] RaiseError (ERROR_BADKEY, "Could not delete value '{sValueName}' of key '{sPath}': key did not exist.")
				[+] default
					[ ] RaiseError (ERROR_OTHER, "Could not delete value '{sValueName}' of key '{sPath}' (return code {GetRegRetCode (lRet)}).")
		[ ] 
	[ ] 
	[+] private void RecurseEnumKeys (LONG hRootKey, STRING sTopKeyPath, STRING sPath, inout LIST OF STRING lsSubKeys, BOOLEAN bDoNotRecurse optional)
		[ ] LONG hKey, lRet, dwIndex, lpcName
		[ ] LONG lpcClass = 0
		[ ] STRING lpName
		[ ] STRING lpClass = NULL
		[ ] FILETIME lpftLastWriteTime
		[ ] BOOLEAN bContinue = TRUE
		[ ] 
		[+] if bDoNotRecurse == NULL
			[ ] bDoNotRecurse = FALSE
		[ ] 
		[ ] RegOpenKeyEx (hRootKey, sTopKeyPath + sPath, 0, KEY_READ, hKey )
		[ ] dwIndex = -1
		[ ] lRet = -1
		[+] while bContinue
			[ ] lpcName = MAX_CHARS_NAME
			[ ] dwIndex++
			[ ] lRet = RegEnumKeyEx (hKey, dwIndex, lpName, lpcName, 0, lpClass, lpcClass, lpftLastWriteTime)
			[+] switch lRet
				[+] case ERROR_SUCCESS, ERROR_MORE_DATA
					[ ] ListAppend (lsSubKeys, sPath + "\" + lpName)
					[+] if !bDoNotRecurse
						[ ] RecurseEnumKeys (hRootKey, sTopKeyPath, sPath + "\" + lpName, lsSubKeys)
				[+] case ERROR_NO_MORE_ITEMS
					[ ] bContinue = FALSE
				[+] default
					[ ] RaiseError (ERROR_OTHER, "Could not enumerate subkeys of key '{sTopKeyPath + sPath}' (return code {GetRegRetCode (lRet)}).")
		[ ] 
		[ ] RegCloseKey (hKey)
	[+] LIST OF STRING Reg_EnumKeys (LONG hRootKey, STRING sPath)
		[+] //	***	LIBRARY BROWSER 'CODE'	***
			[ ] //	function:  lsSubKeyPaths = Reg_EnumKeys (hRootKey, sPath)
			[ ] //  returns:   lsSubKeyPaths: the paths of the subkeys directly beneath sPath (LIST OF STRING)
			[ ] //	parameter: hRootKey: the constant (from mswconst.inc; e.g., HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE) for the root key (LONG)
			[ ] //	parameter: sPath: the full path of the key for which to enumerate the subkeys (STRING)
			[ ] //	notes:     Returns the list of subkeys directly beneath the specified key. The paths of the subkeys are relative to sPath.
			[ ] //  notes:     Example: Reg_EnumKeys (HKEY_CURRENT_USER, "Software\Microsoft\Windows\CurrentVersion\Explorer\MenuOrder\StartMenu\Programs")
		[ ] 
		[ ] LIST OF STRING lsSubKeyPaths = {}
		[ ] 
		[ ] RecurseEnumKeys (hRootKey, sPath, "", lsSubKeyPaths, TRUE)
		[ ] 
		[ ] return lsSubKeyPaths
		[ ] 
	[+] LIST OF STRING Reg_EnumKeysAll (LONG hRootKey, STRING sPath)
		[+] //	***	LIBRARY BROWSER 'CODE'	***
			[ ] //	function:  lsSubKeyPaths = Reg_EnumKeysAll (hRootKey, sPath)
			[ ] //  returns:   lsSubKeyPaths: the paths of all of the subkeys within sPath (LIST OF STRING)
			[ ] //	parameter: hRootKey: the constant (from mswconst.inc; e.g., HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE) for the root key (LONG)
			[ ] //	parameter: sPath: the full path of the key for which to enumerate the subkeys (STRING)
			[ ] //	notes:     Returns the list of all layers of subkeys beneath the specified key. The paths of the subkeys are relative to sPath.
			[ ] //  notes:     Example: Reg_EnumKeysAll (HKEY_CURRENT_USER, "Software\Microsoft\Windows\CurrentVersion\Explorer\MenuOrder\StartMenu\Programs")
		[ ] 
		[ ] LIST OF STRING lsSubKeyPaths = {}
		[ ] 
		[ ] RecurseEnumKeys (hRootKey, sPath, "", lsSubKeyPaths)
		[ ] 
		[ ] return lsSubKeyPaths
		[ ] 
	[+] private LIST OF REGVALUE EnumValues (LONG hRootKey, STRING sPath, STRING sPrefix)
		[+] if Len (sPrefix) > 0
			[ ] sPrefix = sPrefix + "\"
		[ ] 
		[ ] LIST OF REGVALUE lrValues = {}
		[ ] REGVALUE rValue = {}
		[ ] LONG hKey, lRet, dwIndex, lpcValueName, lpcbData
		[ ] LONG lpcClass = 0
		[ ] STRING lpValueName, lpType, lpData
		[ ] BOOLEAN bContinue = TRUE
		[ ] 
		[ ] RegOpenKeyEx (hRootKey, sPath, 0, KEY_READ, hKey )
		[ ] 
		[ ] dwIndex = -1
		[ ] lRet = -1
		[+] while bContinue
			[ ] lpcValueName = MAX_CHARS_NAME
			[ ] lpcbData = MAX_CHARS_DATA
			[ ] dwIndex++
			[ ] lRet = RegEnumValue (hKey, dwIndex, lpValueName, lpcValueName, 0, lpType, lpData, lpcbData)
			[+] switch lRet
				[+] case ERROR_SUCCESS, ERROR_MORE_DATA
					[ ] rValue.sValueName = sPrefix + lpValueName
					[ ] rValue.sValueData = lpData
					[+] switch Asc (lpType)
						[+] case REG_SZ
							[ ] // No prefix necessary
						[+] case REG_BINARY, REG_DWORD
							[ ] // rValue.sValueData = "{[REG_DATA](Asc (lpType))}:{rValue.sValueData}"
							[ ] rValue.sValueData = SYS_GetRegistryValue (hRootKey, sPath, lpValueName)
						[+] default
							[ ] RaiseError (E_TYPE_MISMATCH, "Unknown data type: {Asc (lpType)}")
					[ ] 
					[ ] ListAppend (lrValues, rValue)
					[ ] 
				[+] case ERROR_NO_MORE_ITEMS
					[ ] bContinue = FALSE
				[+] default
					[ ] RaiseError (ERROR_OTHER, "Could not enumerate values of key '{sPath}' (return code {GetRegRetCode (lRet)}).")
		[ ] 
		[ ] RegCloseKey (hKey)
		[ ] 
		[ ] return lrValues
		[ ] 
	[+] LIST OF REGVALUE Reg_EnumValues (LONG hRootKey, STRING sPath)
		[+] //	***	LIBRARY BROWSER 'CODE'	***
			[ ] //	function:  lrValues = Reg_EnumValues (hRootKey, sPath)
			[ ] //  returns:   lrValues: the values of the key specified by sPath. The data for the values can be string, binary or DWORD values, using the format used by SYS_SetRegistryValue(). (LIST OF REGVALUE)
			[ ] //	parameter: hRootKey: the constant (from mswconst.inc; e.g., HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE) for the root key (LONG)
			[ ] //	parameter: sPath: the full path of the key for which to enumerate the values (STRING)
			[ ] //	notes:     Returns the list of values belonging to the specified key.
			[ ] //  notes:     Example: Reg_EnumValues (HKEY_LOCAL_MACHINE, "Software\Company\Product\1.0")
		[ ] 
		[ ] LIST OF REGVALUE lrValues = {}
		[ ] 
		[ ] lrValues = EnumValues (hRootKey, sPath, "")			// no subpath
		[ ] 
		[ ] return lrValues
		[ ] 
	[+] LIST OF REGVALUE Reg_EnumValuesAll (LONG hRootKey, STRING sPath)
		[+] //	***	LIBRARY BROWSER 'CODE'	***
			[ ] //	function:  lrValues = Reg_EnumValues (hRootKey, sPath)
			[ ] //  returns:   lrValues: the values of the key and of all subkeys within sPath. The data for the values can be string, binary or DWORD values, using the format used by SYS_SetRegistryValue(). (LIST OF REGVALUE)
			[ ] //	parameter: hRootKey: the constant (from mswconst.inc; e.g., HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE) for the root key (LONG)
			[ ] //	parameter: sPath: the full path of the key for which to enumerate the values, including subkey values (STRING)
			[ ] //	notes:     Returns a list of values and all layers of subkey values. The names of the values include the path of the containing subkey relative to sPath.
			[ ] //  notes:     Example: Reg_EnumValuesAll (HKEY_LOCAL_MACHINE, "Software\Company\Product")
		[ ] 
		[ ] LIST OF REGVALUE lrValues = {}
		[ ] LIST OF STRING lsKeys = Reg_EnumKeysAll (hRootKey, sPath)
		[ ] STRING sKey
		[ ] 
		[ ] lrValues = EnumValues (hRootKey, sPath, "")			// no subpath
		[+] for each sKey in lsKeys
			[ ] ListMerge (lrValues, EnumValues (hRootKey, sPath + sKey, sKey))
		[ ] 
		[ ] return lrValues
		[ ] 
[ ] 
