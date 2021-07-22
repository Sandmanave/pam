#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "22";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2021";
	static const char UBUNTU_VERSION_STYLE[] =  "21.07";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 103;
	static const long REVISION  = 547;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 158;
	#define RC_FILEVERSION 1,0,103,547
	#define RC_FILEVERSION_STRING "1, 0, 103, 547\0"
	static const char FULLVERSION_STRING [] = "1.0.103.547";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 0;
	

}
#endif //VERSION_H
