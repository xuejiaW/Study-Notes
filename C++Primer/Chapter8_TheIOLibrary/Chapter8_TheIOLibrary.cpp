#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

void TestIOCopyOrAssign();
void TestManagingConditionState();
void TestTyingStreams();
void TryFileStream();
void TestIstringstream();
void TestOstringStream();

struct PersonInfo
{
    string name;
    vector<string> phones;
};

int main()
{
    std::cout << "This is Chapter 8" << std::endl;
    // TestIOCopyOrAssign();
    // TestManagingConditionState();
    // TestTyingStreams();
    // TryFileStream();
    // TestIstringstream();
    TestOstringStream();
}

void TestOstringStream()
{
    ostringstream ssf;
    ssf << "123"
        << " 456";
    cout << ssf.str() << endl;

    /*
    123 456
    */
}

void TestIstringstream()
{
    string line, word;
    vector<PersonInfo> people;
    //morgan 2015 86255
    while (getline(cin, line))
    {
        PersonInfo info;
        istringstream record(line); //Bind line to record
        record >> info.name;        //Read one word,in this case, it's name

        // Read one word,in this case, it's phone,
        //If condition is false, means that there is no content
        while (record >> word)
        {
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
}

void TryFileStream()
{
    string content = "123\n456";
    ofstream out("./Test.txt");
    out << content;

    //Clear content
    content = "";
    //Must close file in order for other fstream to use this file
    out.close();

    ifstream in("./Test.txt");
    while (in.good())
    {
        in >> content;
        cout << "Read Content with good is " << content << endl;
    }

    in.close();
    in.open("./Test.txt");
    cout << endl;

    //IO type as condition is equal to !io.fail()
    //fail does not check eofbit
    while (in)
    {
        in >> content;
        cout << "Read Content with condition is " << content << endl;
    }

    /*
    Read Content with good is 123
    Read Content with good is 456

    Read Content with condition is 123
    Read Content with condition is 456
    Read Content with condition is 456
    */

    in.close();
    cout << endl;

    ofstream out1("./Test.txt", ostream::app);
    out1 << "\n789";
    out1.close();
    in.open("./Test.txt");
    while (in.good())
    {
        in >> content;
        cout << "Read Content with good is " << content << endl;
    }

    in.close();
    cout << endl;

    out1.open("./Test.txt");
    out1 << "\n666";
    out1.close();
    in.open("./Test.txt");
    while (in.good())
    {
        in >> content;
        cout << "Read Content with good is " << content << endl;
    }

    /*
    Read Content with good is 123
    Read Content with good is 456
    Read Content with good is 789

    Read Content with good is 666
    */
}

void TestIOCopyOrAssign()
{
    ofstream out1, out2;
    // out1 = out2; //error, cannot assign stream objects
}

void TestManagingConditionState()
{
    cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);
}

void TestTyingStreams()
{
    cin.tie(&cout); //System already do

    ostream *old_tie = cin.tie(nullptr);
    //old_tie is pointer to cout
    //Now cin is tied to nothing

    cin.tie(&cerr);
    cin.tie(old_tie);
    //cin is tied to cout
}