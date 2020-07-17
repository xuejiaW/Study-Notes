#include <string>
#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

int GetMinDistance(int size, string* stringArray,string str1,string str2);
void TestGetMinDistance()
{
    int size=0;
    cin>>size;
    string str1,str2;
    cin>>str1>>str2;
    string strArr[size];
    for(int i=0;i!=size;++i)
    {
        cin>>strArr[i];
    }
    int result = GetMinDistance(size,strArr,str1,str2);
    cout<<result<<endl;
}

int GetMinDistance(int size, string* strArr,string str1,string str2)
{
    int lastStr1Index = -1, lastStr2Index=-1;
    int minDistance= INT_MAX;
    for(int i=0;i!=size;++i)
    {
        if(strArr[i] == str1)
        {
            lastStr1Index = i;
            if(lastStr2Index != -1)
                minDistance=min(minDistance,(lastStr1Index-lastStr2Index));
        }
        else if(strArr[i] == str2)
        {
            lastStr2Index = i;
            if(lastStr1Index != -1)
                minDistance=min(minDistance,(lastStr2Index-lastStr1Index));
        }
    }
    
    return minDistance==INT_MAX?-1:minDistance;
}