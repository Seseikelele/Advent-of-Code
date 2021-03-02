#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv, char** env)
{
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " inputfile" << endl;
        exit(1);
    }
    fs::path inputfile(argv[1]);
    if(!fs::exists(inputfile))
    {
        cout << "File does not exist." << endl;
        exit(2);
    }
    if(!fs::is_regular_file(inputfile))
    {
        cout << "Invalid input file." << endl;
        exit(3);
    }
    ifstream f(inputfile);
    char c{0};
    int floor{0};
    int position{1};
    bool flag = false;
    while(f.good())
    {
        f.get(c);
        if(f.eof())
        {
            break;
        }
        switch(c)
        {
        case '(':
            ++floor;
            break;
        case ')':
            --floor;
            break;
        }
        if(!flag && floor == -1)
        {
            cout << "Basement reached on position " << position << endl;
            flag = true;
        }
        ++position;
    }
    f.close();
    cout << "Final floor = " << floor << endl;
}