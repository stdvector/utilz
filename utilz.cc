#include "utilz.h"

using namespace std;

/*************** String manipulation ****************/

// Split string into tokens by the given delimit char                          
VectorOfString Split(const String &s, char delim)
{
  vector<String> elems;

  split(s, delim, elems);

  return elems;
}

// Overload: Split string into tokens by the given delimit char                    
VectorOfString &Split(const String &s, char delim, VectorOfString &elems)
{
  stringstream ss(s);
  String item;

  while (getline(ss, item, delim))
  {
    elems.push_back(item);
  }

  return elems;
}

// Replace all instances of "from" to "to" in the string str
void ReplaceAll(String& str, String from, String to) 
{  
    if (from.empty())
        return;

    size_t start_pos = 0;

    while ((start_pos = str.find(from, start_pos)) != String::npos) 
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

/*************** File I/O ****************/

// For a standard filename with ".xxx" extension, remove the extension
String RemoveExtension(const String filename)
{
  String filename_no_extension = filename.substr(0, filename.rfind("."));

  return filename_no_extension;
}

// Read a delimited text file into a map; the first element in the line becomes the key
void ReadDelimitedFileToMap(map<String, VectorOfString> &content, const String filename, const char delimit, bool to_skip_header)
{
  ifstream input_file;

  input_file.open(filename);

  if (!input_file.is_open())
  {    
    cout << "Cannot open delimited input file: " << filename << endl;
    exit(EXIT_FAILURE);
  }

  String line;

  getline(input_file, line);
  
  // Does NOT skip the file header
  if (!to_skip_header)
  {
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);

    content["_header"] = split(line, delimit);
  }

  getline(input_file, line);

  while (input_file.good())
  {
    VectorOfString fields = split(line, delimit);
    VectorOfString values;

    for (int i = 1; i < fields.size(); i++)
    {
      values.push_back(fields[i]);
    }

    content[fields[0]] = values;

    getline(input_file, line);

  } 

  input_file.close();
}

// Read a delimited text file into a vector; each line becomes an element of vector<string> in the vector
void ReadDelimitedFileToVector(vector<vector<String> > &content, const String filename, const char delimit, bool to_skip_header)
{
  ifstream input_file;

  input_file.open(filename);

  if (!input_file.is_open())
  {    
    cout << "Cannot open delimited input file: " << filename << endl;
    exit(EXIT_FAILURE);
  }

  String line;
  
  // Skip the file header
  if (to_skip_header)
  {
    getline(input_file, line);
  }

  getline(input_file, line);

  while (input_file.good())
  {
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    VectorOfString fields = split(line, delimit);
    content.push_back(fields);
    getline(input_file, line);
  } 

  input_file.close();
}


/*************** Conversion ****************/


// Convert a string into float
float ConvertStringToFloat(const String number_string)
{
  return atof(number_string.c_str());
}

// Convert a string into int
int ConvertStringToInt(const String number_string)
{
  return atoi(number_string.c_str());
}

// Convert a number into string
String ConvertNumberToString(const int number)
{
  stringstream ss;
  ss << number;
  return ss.str();
}

String ConvertNumberToString(const float number)
{
  stringstream ss;
  ss << number;
  return ss.str();
}

/*************** Date and Time ****************/

// Parse the date string (YYYY-MM-DD) into a vector of int [YYYY, MM, DD]
vector<int> ParseDate(const String date)
{
  VectorOfString yyyy_mm_dd = split(date, '-');

  if (yyyy_mm_dd.size() != 3)
  {
    cout << "Error parsing date " << date << ". Terminating program." << endl;
    exit(EXIT_FAILURE);
  }

  vector<int> y_m_d;
  y_m_d.push_back(convert_string_to_int(yyyy_mm_dd[0]));
  y_m_d.push_back(convert_string_to_int(yyyy_mm_dd[1]));
  y_m_d.push_back(convert_string_to_int(yyyy_mm_dd[2]));

  return (y_m_d);
}

// Convert a date in string (YYYY-MM-DD) into the Julian Date Number
// Refer to http://en.wikipedia.org/wiki/Julian_day
long ConvertDateToJDN(const String date)
{
  vector<int> y_m_d = parse_date(date);
 
  int a = (14 - y_m_d[1]) / 12; 
  int y = y_m_d[0] + 4800 - a; 
  int m = y_m_d[1] + 12 * a - 3; 
  
  if (y_m_d[0] > 1582 || (y_m_d[0] == 1582 && y_m_d[1] > 10) || (y_m_d[0] == 1582 && y_m_d[1] == 10 && y_m_d[2] >= 15)) 
    return y_m_d[2] + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045; 
  else 
    return y_m_d[2] + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083; 
}

// Convert a Julian Date Number into a date string (YYYY-MM-DD)
// Refer to http://en.wikipedia.org/wiki/Julian_day
String ConvertJDNToDate(const long jdn)
{

  long long j = static_cast<long long>(jdn + 0.5) + 32044;
  long long g = j / 146097;
  long long dg = j % 146097;
  long long c = (dg / 36524 + 1) * 3 / 4;
  long long dc = dg - c * 36524;
  long long b = dc / 1461;
  long long db = dc % 1461;
  long long a = (db / 365 + 1) *3 / 4;
  long long da = db - a * 365;
  long long y = g * 400 + c * 100 + b * 4 + a;
  long long m = (da * 5 + 308) / 153 - 2;
  long long d = da - (m+4) * 153 / 5 + 122;
    
  int year = y - 4800 + (m + 2) / 12;
  int month = (m + 2) % 12 + 1;
  int day = d + 1;

  String year_str = convert_number_to_string(year);
  String month_str = convert_number_to_string(month);
  String day_str = convert_number_to_string(day);

  // Pad the month and day string with leading 0s
  month_str.insert(month_str.begin(), 2 - month_str.size(), '0');
  day_str.insert(day_str.begin(), 2 - day_str.size(), '0');

  return (year_str + "-" + month_str + "-" + day_str);
}

// Return the date (YYYY-MM-DD) that is days_diff ahead (-) of or after (+) today (YYYY-MM-DD)
String GetDiffDate(const String today, int days_diff)
{
  long jdn = convert_date_to_jdn(today);

  return (convert_jdn_to_date(jdn + days_diff));
}

//////////////////////// TEST ////////////////

// int main()
// {
//   string date;
//   cin >> date;

//   int days_diff;
//   cin >> days_diff;

//   cout << compute_diff_date(date, days_diff) << endl;


// }
