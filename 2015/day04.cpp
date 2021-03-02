#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

#include <openssl/md5.h> // -lcrypto

using namespace std;
namespace fs = std::filesystem;

ostream& print_digest(ostream& stream, array<unsigned char, MD5_DIGEST_LENGTH>& digest)
{
    auto flags = stream.flags();
    for(auto c : digest)
    {
        stream << setfill('0') << setw(2) << uppercase << hex << (int)c;
    }
    stream.flags(flags);
    return stream;
}

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
    string key;
    f >> key;
    f.close();
    unsigned num{1};
    string in;
    bool fiveZerosHashFound{false};
    bool sixZerosHashFound{false};
    while(!fiveZerosHashFound || !sixZerosHashFound)
    {
        in = key + to_string(num);
        array<unsigned char, MD5_DIGEST_LENGTH> digest;
        unsigned char* d = reinterpret_cast<unsigned char*>(in.data());
        MD5(d, in.size(), digest.data());

        // first five characters of hex string -> two bytes and a nibble
        if(!fiveZerosHashFound && digest[0] == 0 && digest[1] == 0 && (digest[2] & 0xF0) == 0)
        {
            fiveZerosHashFound = true;
            cout << "Five zeros hash for " << in << ": ";
            print_digest(cout, digest);
            cout << endl;
        }

        // first six characters of hex string -> three bytes
        if(fiveZerosHashFound && count(digest.begin(), digest.begin() + 3, 0) == 3)
        {
            sixZerosHashFound = true;
            cout << "Six zeros hash for " << in << ": ";
            print_digest(cout, digest);
            cout << endl;
        }
        ++num;
    }
}