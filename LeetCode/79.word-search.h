// Tags: 
// array | backtracking

// 给定一个二维网格和一个单词，找出该单词是否存在于网格中。

// 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

 

// 示例:

// board =
// [
//   ['A','B','C','E'],
//   ['S','F','C','S'],
//   ['A','D','E','E']
// ]

// 给定 word = "ABCCED", 返回 true
// 给定 word = "SEE", 返回 true
// 给定 word = "ABCB", 返回 false
 

// 提示：

// board 和 word 中只包含大写和小写英文字母。
// 1 <= board.length <= 200
// 1 <= board[i].length <= 200
// 1 <= word.length <= 10^3

#include <vector>
#include <iostream>
#include <string>

using namespace std;

bool exist(vector<vector<char>> &board, string word);
void TestWordSearch()
{
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}};

    bool result = exist(board, "ABCD");
    cout << result << endl;
}

bool searchChar(vector<vector<char>> &board, const string &word, int charIndex, int i, int j);
bool exist(vector<vector<char>> &board, string word)
{
    for (int i = 0; i != board.size(); ++i)
    {
        for (int j = 0; j != board[i].size(); ++j)
        {
            if (searchChar(board, word, 0, i, j)) //Start search from every point
                return true;
        }
    }

    return false;
}

bool searchChar(vector<vector<char>> &board, const string &word, int charIndex, int i, int j)
{
    if (charIndex >= word.size())
        return true;

    if (board[i][j] != word[charIndex])
        return false;

    if (word.size() == 1)
        return true;

    int rowNum = board.size();
    int colNum = board[0].size();

    char temp = board[i][j];
    // To ensure the back operation failed, so make the current char to be a impossible char
    board[i][j] = '0';

    bool result = ((i - 1) >= 0 && searchChar(board, word, charIndex + 1, i - 1, j)) ||     // Up
                  ((j + 1) < colNum && searchChar(board, word, charIndex + 1, i, j + 1)) || // Right
                  ((i + 1) < rowNum && searchChar(board, word, charIndex + 1, i + 1, j)) || // Left
                  ((j - 1) >= 0 && searchChar(board, word, charIndex + 1, i, j - 1));       // Down

    board[i][j] = temp;

    return result;
}
