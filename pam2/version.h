#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "01";
	static const char MONTH[] = "04";
	static const char YEAR[] = "2019";
	static const char UBUNTU_VERSION_STYLE[] =  "19.04";
	
	//Software Status
	static const char STATUS[] =  "Release";
	static const char STATUS_SHORT[] =  "r";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 1216;
	static const long REVISION  = 6781;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3009;
	#define RC_FILEVERSION 1,0,1216,6781
	#define RC_FILEVERSION_STRING "1, 0, 1216, 6781\0"
	static const char FULLVERSION_STRING [] = "1.0.1216.6781";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 0;
	

}
#endif //VERSION_H
