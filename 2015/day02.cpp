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
    regex dimensions("(\\d+)x(\\d+)x(\\d+)");
    string line;
    int a{0}, b{0}, c{0};
    int area1{0}, area2{0}, area3{0};
    int total_paper{0};
    int total_ribbon{0};
    while(f >> line)
    {
        smatch match;
        if(!regex_match(line, match, dimensions))
        {
            continue;
        }
        a = stoi(match[1].str());
        b = stoi(match[2].str());
        c = stoi(match[3].str());
        area1 = a * b;
        area2 = b * c;
        area3 = c * a;
        total_paper += 2 * (area1 + area2 + area3) + min({area1, area2, area3});
        vector arr{a, b, c};
        sort(arr.begin(), arr.end());
        total_ribbon += 2 * (arr[0] + arr[1]) + a * b * c;
    }
    cout << "Required paper area: " << total_paper << endl;
    cout << "Required ribbon length: " << total_ribbon << endl;
    f.close();
}