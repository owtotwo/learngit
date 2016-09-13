// hex_viewer - a program for viewing any files in hex.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iterator>

using namespace std;

int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		cout << "Usage: hex_viewer [file]" << endl;
		exit(1);
	}


	const string file_addr = argv[1];
	ifstream fin(file_addr, ifstream::in | ifstream::binary);
	
	if (!fin.is_open()) {
		cout << "Cannot open file \"" << file_addr << "\"" << endl;
		exit(1);
	}


	istream_iterator<unsigned char> in_it(fin >> noskipws), eos;

	for (int i = 0; in_it != eos; ++i, ++in_it) {
		if (i % 16 == 0)
			cout << setw(8) << setfill('0') << i << "| ";

		cout << setw(2) << setfill('0') << hex // padding zero for hex
		     << static_cast<unsigned int>(*in_it) << " ";

		if (i % 16 == 15) cout << endl;
	}

	cout << endl;


	fin.close();
	
	return 0;
}
