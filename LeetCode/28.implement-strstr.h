#include "parser.h"
#include "debug.h"

int strStr(string haystack, string needle);

void TestStrStr()
{
    int result = strStr("mississippi", "issip");
    cout << "result is " << result << endl;
}

int strStr(string haystack, string needle)
{
    if (needle.empty())
        return 0;
    if (haystack.empty())
        return -1;
    if (needle.size() > haystack.size())
        return -1;

    for (int i = 0; i != haystack.size(); ++i)
    {
        if (haystack[i] == needle[0])
        {
            bool match = true;
            if (i + needle.size() - 1 >= haystack.size())
                continue;
            for (int j = 1; j != needle.size(); ++j)
            {
                if (i + j >= haystack.size() || haystack[i + j] != needle[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
                return i;
        }
    }
    return -1;
}
