#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>

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
    int x{0};
    int y{0};
    map<pair<int, int>, unsigned> houses{{{0, 0}, 1}};
    while(f.good())
    {
        f.get(c);
        if(f.eof())
        {
            break;
        }
        switch (c)
        {
        case '^'://N
            ++y;
            break;
        case '>'://E
            ++x;
            break;
        case '<'://W
            --x;
            break;
        case 'v'://S
            --y;
            break;
        }
        houses[{x, y}] += 1;
    }
    f.close();
    cout << "Number of houses visited: " << houses.size() << endl;
}