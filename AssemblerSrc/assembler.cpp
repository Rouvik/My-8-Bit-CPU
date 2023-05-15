#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>

struct Operation {
	std::string name;
	int code;
	bool hasOperand;
};

std::vector <Operation> oplist {
	{"NOP", 0, false},
	{"LDX", 1, true},
	{"XOUT", 2, false},
	{"LDY", 3, true},
	{"YOUT", 4, false},
	{"LDR", 5, true},
	{"ROUT", 6, false},
	{"SWP", 7, false},
	{"AOUT", 8, false},
	{"SOUT", 9, false},
	{"JMP", 10, true},
	{"ATX", 11, false},
	{"ATY", 12, false},
	{"STX", 13, false},
	{"STY", 14, false},
	{"XTR", 15, false},
	{"YTR", 16, false},
	{"RTX", 17, false},
	{"RTY", 18, false},
	{"ATR", 19, false},
	{"STR", 20, false},
	{"SAD", 21, true},
	{"XLM", 22, false},
	{"XTM", 23, false},
	{"RLM", 24, false},
	{"RTM", 25, false},
	{"YLM", 26, false},
	{"YTM", 27, false},
	{"SADR", 28, false},
	{"SADX", 29, false},
	{"SADY", 30, false},
	{"HLT", 128, false}
};

template <typename I> std::string getHexStr(I w) {
	static const char* digits = "0123456789abcdef";
	std::string rc = "";

	while(w > 15) {
		rc = digits[w & 0xf] + rc; // put hex code for last 4 bit
		w = w >> 4; // delete the 4 bits
	}

	rc = digits[w] + rc; // add last bit if left

	return rc;
}

std::string processLine(int lno, std::string line) {
	line = line.substr(0, line.find(";")); // delete trailing comment

	std::stringstream buf(line);
	std::string opcode; // store the opcode in here
	buf >> opcode;

	if(opcode.compare("") == 0) { // no opcode found (ignore line)
		return (std::string) "";
	}

	// convert opcode to uppercase
	std::transform(opcode.begin(), opcode.end(),
		       opcode.begin(), 
		       [](unsigned char c)
		       {
			 return std::toupper(c);	
		       });

	std::string data; // store the operand or data in it (if required)
	buf >> data;

	// process opcode
	bool found = false;
	for(auto& operation : oplist) {
		if((operation.name).compare(opcode) == 0) {
			found = true;
			int value = operation.code << 8; // shift by 8 bit to opcode section
			if(operation.hasOperand) {
				value |= std::atoi(data.c_str());
			}
			return getHexStr<int>(value);
		}
	}

	// check if opcode found
	if(!found) {
		std::cerr << "Unknown opcode: "
			  << opcode << " at " << lno
			  << " setting NOP\n";
	}

	return "0000"; // return 0 if unknown
		
}

int main(int argc, char** argv) {
	// check for args
	if (argc < 2) {
		std::cout << "Please provide file to assemble...\n";
		return 1;
	}

	std::string filename = argv[1]; // store the file name to assemble
	std::string outname = "out.hex"; // default output file name
	
	// check for additional args (output file name)
	if (argc > 2) {
		outname = argv[2];
	}

	// conversion begins here
	std::ifstream in(filename);

	if(!in) {
		std::cout << "Error, failed to open " << filename << "\n";
		in.close();
		return 1;
	}

	std::string output = "";
	int lno = 0;
	while(!in.eof()) {
		std::string line = "";
		getline(in, line); // copy a single line to process
		output += processLine(++lno, line) + " "; // add binary to output buffer
	}
	
	// close the reading file
	in.close();

	std::ofstream out(outname);

	if(!out) {
		std::cout << "Error, failed to open file to write!";
		out.close();
		return 1;
	}
	
	// write header
	char head[] = "v3.0 hex words auto\n";
	out.write(head, std::strlen(head));
	// write the compiled hexcode
	out.write(output.c_str(), output.size());
	out.close();	
	return 0;
}
