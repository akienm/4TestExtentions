	[ ] 
	[ ] LONG PLANES=14
	[ ] LONG BITSPIXEL=12
	[ ] 
[-] dll "user32.dll"
	[ ] LONG GetDC(LONG hdc)
	[ ] 
[-] dll "Gdi32.dll"
	[ ] LONG GetDeviceCaps(LONG hdc, LONG dtype)
	[ ] //use "msw32.inc"
	[ ] 
[-] integer GetColorDepth()
	[ ] 
	[ ] LONG hdc = GetDC(Desktop.GetHandle())
	[ ] //Print (hdc)
	[ ] INT dBitsInAPixel = GetDeviceCaps(hdc, PLANES) * GetDeviceCaps(hdc, BITSPIXEL) 
	[ ] return dBitsInAPixel
	[ ] 
	[ ] 
	[ ] 
[-] main ()
	[ ] 
	[ ] Print (GetColorDepth())
	[ ] 
	[ ] 
