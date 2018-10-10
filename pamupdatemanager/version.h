#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "10";
	static const char MONTH[] = "10";
	static const char YEAR[] = "2018";
	static const char UBUNTU_VERSION_STYLE[] =  "18.10";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 29;
	static const long REVISION  = 148;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 43;
	#define RC_FILEVERSION 1,0,29,148
	#define RC_FILEVERSION_STRING "1, 0, 29, 148\0"
	static const char FULLVERSION_STRING [] = "1.0.29.148";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 0;
	

}
#endif //VERSION_H
