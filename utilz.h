// Frequently used utilities

#ifndef UTILZ_H_
#define UTILZ_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

typedef std::string String;
typedef std::vector<String> VectorOfString;
typedef std::vector<float> VectorOfFloat;
typedef std::vector<int> VectorOfInt;

using namespace std;

/*************** String manipulation ****************/

// Split string into tokens by the given delimit char                          
VectorOfString Split(const String &s, char delim);

// Overload: Split string into tokens by the given delimit char                    
VectorOfString &Split(const String &s, char delim, std::vector<String> &elems);

// Replace all instances of "from" to "to" in the string str
void ReplaceAll(String& str, String from, String to);

/*************** File I/O ****************/

// For a standard filename with ".xxx" extension, remove the extension
String RemoveExtension(const String filename);

// Read a delimited text file into a map; the first element in the line becomes the key
void ReadDelimitedFileToMap(map<String, VectorOfString> &content, const String filename, const char delimit, bool to_skip_header);

// Read a delimited text file into a vector; each line becomes an element of vector<string> in the vector
void ReadDelimitedFileToVector(vector<VectorOfString> &content, const String filename, const char delimit, bool to_skip_header);

/*************** Conversion ****************/

// Convert a string into float
float ConvertStringToFloat(const String number_string);

// Convert a string into double
double ConvertStringToDouble(const String number_string);

// Convert a string into int
int ConvertStringToInt(const String number_string);

// Convert a number into string
String ConvertNumberToString(const int number);
String ConvertNumberToString(const float number);

/************* Date related **************/

// Parse the date string (YYYY-MM-DD) into a vector of int [YYYY, MM, DD]
VectorOfInt ParseDate(const String date);

// Convert a date in string (YYYY-MM-DD) into the Julian Date Number and vice versa
// Refer to http://en.wikipedia.org/wiki/Julian_day
long ConvertDateToJDN(const String date);
String ConvertJDNToDate(const long jdn);

// Return the date (YYYY-MM-DD) that is days_diff ahead (-) of or after (+) today (YYYY-MM-DD)
String GetDiffDate(const String today, int days_diff);

#endif // End of define UTILZ_H_