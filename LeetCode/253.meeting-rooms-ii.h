// 会议室 II

// 难度：中等

// Tags:
// stack | sorting 

// 给定一个会议时间安排的数组，每个会议时间都会包括开始和结束的时间 [[s1,e1],[s2,e2],...] (si < ei)，为避免会议冲突，同时要考虑充分利用会议室资源，请你计算至少需要多少间会议室，才能满足这些会议安排。

// 示例 1:
// 输入: [[0, 30],[5, 10],[15, 20]]
// 输出: 2

// 示例 2:
// 输入: [[7,10],[2,4]]
// 输出: 1

#include "parser.h"
#include "debug.h"

int minMeetingRooms(vector<vector<int>> &intervals);
void TestMeetingRoom()
{
    vector<vector<int>> interval = parser2VectorArray_int("[[0,30],[5,10],[15,20]]");
    // vector<vector<int>> interval = parser2VectorArray_int("[[7,10],[2,4]]");
    cout << minMeetingRooms(interval);
}

// // Version: violent
int minMeetingRooms(vector<vector<int>> &intervals)
{
    if (intervals.empty())
        return 0;

    sort(intervals.begin(), intervals.end());

    vector<int> meetingRoom;
    meetingRoom.push_back(intervals[0][1]);

    for (int i = 1; i != intervals.size(); ++i)
    {
        bool foundARoom = false;
        for (int j = 0; j != meetingRoom.size(); ++j)
        {
            if (intervals[i][0] >= meetingRoom[j])
            {
                meetingRoom[j] = intervals[i][1];
                foundARoom = true;
                break;
            }
        }

        if (!foundARoom)
            meetingRoom.push_back(intervals[i][1]);
    }

    return meetingRoom.size();
}

// Version: priority_queue
int minMeetingRooms(vector<vector<int>> &intervals)
{
    if (intervals.empty())
        return 0;

    sort(intervals.begin(), intervals.end());
    priority_queue<int, vector<int>, greater<int>> meetingRooms;
    meetingRooms.push(intervals[0][1]);

    for (int i = 1; i != intervals.size(); ++i)
    {
        if (intervals[i][0] >= meetingRooms.top())
            meetingRooms.pop();

        meetingRooms.push(intervals[i][1]);
    }

    return meetingRooms.size();
}