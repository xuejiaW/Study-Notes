#include "parser.h"
#include "debug.h"

bool isInterleave(string s1, string s2, string s3);

void TestIsInterleave()
{
    bool result = isInterleave("aabcc", "dbbca", "aadbbcbcac");
    cout << result << endl;
}

bool isInterleave(string s1, string s2, string s3)
{
    int s3Size = s3.size(), s2Size = s2.size(), s1Size = s1.size();
    if (s3Size != s1Size + s2Size)
        return false;

    vector<vector<int>> dp(s1Size + 1, vector<int>(s2Size + 1, false));
    dp[0][0] = 1;

    for (int i = 0; i <= s1Size; ++i)
    {
        for (int j = 0; j <= s2Size; ++j)
        {
            int p = i + j - 1;
            if (i > 0)
                dp[i][j] |= (dp[i - 1][j] && s1[i - 1] == s3[p]);
            if (j > 0)
                dp[i][j] |= (dp[i][j - 1] && s2[j - 1] == s3[p]);
        }
    }

    return dp[s1Size][s2Size];
}
