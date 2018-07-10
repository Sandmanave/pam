#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "10";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2018";
	static const char UBUNTU_VERSION_STYLE[] =  "18.07";
	
	//Software Status
	static const char STATUS[] =  "Release";
	static const char STATUS_SHORT[] =  "r";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 21;
	static const long REVISION  = 128;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 22;
	#define RC_FILEVERSION 1,0,21,128
	#define RC_FILEVERSION_STRING "1, 0, 21, 128\0"
	static const char FULLVERSION_STRING [] = "1.0.21.128";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 0;
	

}
#endif //VERSION_H
