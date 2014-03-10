// Frequently used utilities

#ifndef UTILZ_H_
#define UTILZ_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

typedef std::string string;
typedef std::vector<string> vector_string;
typedef std::vector<float> vector_float;
typedef std::vector<int> vector_int;

/*************** String manipulation ****************/

// Split string into tokens by the given delimit char                          
vector_string split(const string &s, char delim);

// Overload: Split string into tokens by the given delimit char                    
vector_string &split(const string &s, char delim, std::vector<string> &elems);

// Replace all instances of "from" to "to" in the string str
void replace_all(string& str, string from, string to);

/*************** File I/O ****************/

// For a standard filename with ".xxx" extension, remove the extension
string remove_extension(const string filename);

// Read a delimited text file into a map; the first element in the line becomes the key
void read_delimited_file_to_map(std::map<string, vector_string> &content, const string filename, const char delimit, bool to_skip_header);

// Read a delimited text file into a vector; each line becomes an element of vector<string> in the vector
void read_delimited_file_to_vector(std::vector<vector_string> &content, const string filename, const char delimit, bool to_skip_header);


/*************** Conversion ****************/

// Convert a string into float
float convert_string_to_float(const string number_string);

// Convert a string into int
int convert_string_to_int(const string number_string);

// Convert a number into string
string convert_number_to_string(const int number);
string convert_number_to_string(const float number);


/************* Date related **************/

// Parse the date string (YYYY-MM-DD) into a vector of int [YYYY, MM, DD]
vector_int parse_date(const string date);

// Convert a date in string (YYYY-MM-DD) into the Julian Date Number and vice versa
// Refer to http://en.wikipedia.org/wiki/Julian_day
long convert_date_to_jdn(const string date);
string convert_jdn_to_date(const long jdn);

// Return the date (YYYY-MM-DD) that is days_diff ahead (-) of or after (+) today (YYYY-MM-DD)
string get_diff_date(const string today, int days_diff);

#endif // End of define UTILZ_H_