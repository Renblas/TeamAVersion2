
#include <string>

using std::string;

string boolToString(bool input)
{
    string a;
    if (input)
    {
        a = "TRUE";
    }
    else
    {
        a = "FALSE";
    }
    return a;
}
