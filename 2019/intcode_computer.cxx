#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class Computer
{
	vector<int> memory;

	size_t ip = 0;
	int arg1;
	int arg2;
	int arg3;

	istream& input;
	ostream& output;

public:
	Computer(vector<int>& memory, istream& in, ostream& out) : input(in), output(out)
	{
		if(memory.size() <= 0)
		{
			throw invalid_argument("zero size memory");
		}
		this->memory = move(memory);
	}

	void Run()
	{
		while(ip < memory.size())
		{
			ProcessOpcode();
		}
	}

	int& DMA(size_t address)
	{
		return memory[address];
	}

	void MemoryDump()
	{
		copy(memory.begin(), prev(memory.end()), ostream_iterator<int>(output, ","));
		cout << memory.back() << endl;
	}

private:
	void ProcessOpcode()
	{
		unsigned opcode = memory[ip] % 100;
		switch (opcode)
		{
		case 1://Addition
			Add();
			break;
		case 2://Multiplication
			Multiply();
			break;
		case 3://Get Input
			Input();
			break;
		case 4://Print Output
			Output();
			break;
		case 99://Exit
			Halt();
			break;
		default:
			break;
		}
	}

	void Add()
	{
		arg1 = memory[memory[++ip]];
		arg2 = memory[memory[++ip]];
		arg3 = memory[++ip];
		memory[arg3] = arg1 + arg2;
		++ip;
	}

	void Multiply()
	{
		arg1 = memory[memory[++ip]];
		arg2 = memory[memory[++ip]];
		arg3 = memory[++ip];
		memory[arg3] = arg1 * arg2;
		++ip;
	}

	void Input()
	{
		throw exception();
	}

	void Output()
	{
		throw exception();
	}

	void Halt()
	{
		ip = memory.size();
	}
};

void throwIfOpeningFailed(ifstream& stream)
{
	if(!stream)
	{
		throw invalid_argument("failed to open file");
	}
}

int try_main(int argc, char** argv)
{
	// Day 2 samples
	// {vector<int> v = {1, 0, 0, 0, 99};              Computer c(v, cin, cout); c.Run(); c.MemoryDump();}
	// {vector<int> v = {2, 3, 0, 3, 99};              Computer c(v, cin, cout); c.Run(); c.MemoryDump();}
	// {vector<int> v = {2, 4, 4, 5, 99, 0};           Computer c(v, cin, cout); c.Run(); c.MemoryDump();}
	// {vector<int> v = {1, 1, 1, 4, 99, 5, 6, 0, 99}; Computer c(v, cin, cout); c.Run(); c.MemoryDump();}

	// Day 2, part 1
	{
		ifstream in("aoc2.txt");
		vector<int> v;
		for(int word = 0; in >> word; in.ignore(1))
		{
			v.push_back(word);
		}
		in.close();
		Computer c(v, cin, cout);
		c.DMA(1) = 12;
		c.DMA(2) = 2;
		c.Run();
		cout << "Day 2, part 1: " << c.DMA(0) << endl;
	}

	// Day 2, part 2
	{
		ifstream in("aoc2.txt");
		vector<int> v;
		for(int word = 0; in >> word; in.ignore(1))
		{
			v.push_back(word);
		}
		in.close();

		bool l00p = true;
		for(int noun = 0; l00p && noun < 100; ++noun)
		{
			for(int verb = 0; l00p && verb < 100; ++verb)
			{
				vector<int> tmp;
				tmp.reserve(v.size());
				copy(v.begin(), v.end(), back_inserter(tmp));
				Computer c(tmp, cin, cout);
				c.DMA(1) = noun;
				c.DMA(2) = verb;
				c.Run();
				if(c.DMA(0) == 19690720)
				{
					cout << "Day 2, part 2: " << 100 * noun + verb << endl;
					l00p = false;
				}
			}
		}
	}
	return 0;
}

int main(int argc, char** argv)
{
	try
	{
		return try_main(argc, argv);
	}
	catch(const exception& e)
	{
		cerr << e.what() << '\n';
	}
}