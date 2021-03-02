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
    array<pair<int, int>, 2> positions;
    int step{0};
    map<pair<int, int>, unsigned> houses{{{0, 0}, 2}};
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
            positions[step % 2].second += 1;
            // ++y;
            break;
        case '>'://E
            positions[step % 2].first += 1;
            break;
        case '<'://W
            positions[step % 2].first -= 1;
            break;
        case 'v'://S
            positions[step % 2].second -= 1;
            break;
        }
        houses[positions[step % 2]] += 1;
        ++step;
    }
    f.close();
    cout << "Number of houses visited: " << houses.size() << endl;
}