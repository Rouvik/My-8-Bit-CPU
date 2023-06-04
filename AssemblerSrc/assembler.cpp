#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <locale>
#include <algorithm>
#include <vector>

// the actual line number the code is at
int lineNumber = 0;

// number of opcode
int opNumber = 0;

// container to store labels
struct Label {
	std::string name;
	int lbpos;
};

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

// trim from end
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

// stores the label to indivitual code pieces
std::vector <Label> labels;

// processes labels and returns an appropriate address
int processLabel(std::string lb) {
	if(std::isalpha(lb[0])) { // labeled address
		int offsetPos = lb.find("+");
		if(offsetPos != -1) { // uses offset label
			std::string lbname = lb.substr(0, offsetPos);
			rtrim(lbname);

			std::vector<Label>::iterator it = std::find_if(labels.begin(),
								       labels.end(),
					     			       [lbname](Label x) {
				return !(x.name.compare(lbname));	
			});

			if(it == labels.end()) { // no match
				std::cerr << "No such label name: " << lbname << " at " << lineNumber << "\n";
				return 0;
			}

			int offset = std::atoi((lb.substr(offsetPos + 1)).c_str());
			return (*it).lbpos + offset;
		} else {
			std::vector<Label>::iterator it = std::find_if(labels.begin(),
								       labels.end(),
								       [lb](Label x) {
				return !(x.name.compare(lb));
			});

			if(it == labels.end()) { // no match
                                std::cerr << "No such label name: " << lb << " at " << lineNumber << "\n";
                                return 0;
                         }

			return (*it).lbpos;
		}
	} else { // it is nothing but raw address
		return atoi(lb.c_str());
	}
}

// copys everything from a stream
std::string gulp(std::istream &in, short bufSize = 255)
{
    std::string ret;
    char buffer[bufSize];
    while (in.read(buffer, sizeof(buffer)))
        ret.append(buffer, sizeof(buffer));
    ret.append(buffer, in.gcount());
    return ret;
}

struct Operation {
	std::string name;
	int code;
	bool hasOperand;
	bool usesLabels = false;
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
	{"JMP", 10, true, true}, // this op uses labels
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
	{"CMP", 31, false},
	{"JNE", 32, true, true}, // this op uses labels
	{"JZE", 33, true, true}, // this op uses labels
	{"JOV", 34, true, true}, // this op uses labels
	{"JPE", 35, true, true}, // this op uses labels
	{"GDRAW", 36, false},
	{"GRESET", 37, false},
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

void pickLabels(std::ifstream& in) {
	while(!in.eof()) {
		std::string line = "";
		getline(in, line);

		line = line.substr(0, line.find(";")); // delete trailing comment
	
		int colpos = line.find(":");
		if(colpos != -1) {
			std::string lb = line.substr(0, colpos);
			trim(lb);

			if(lb.find(" ") != -1) {
				std::cerr << "Bad label: " << lb << "\n";
			}

			labels.push_back({lb, opNumber});
			continue;
		}

		// check for blank line
		bool not_blank = false;
		for(int i = 0; i < line.length(); i++) {
			if(!std::isspace(line[i])) {
				not_blank = true;
				break;
			}
		}
		
		// update op number of valid opcode line
		if(not_blank) opNumber++;
	}
	
	in.clear(); // erase fail bit
	in.seekg(0); // seek back to start of stream
}

std::string processLine(std::string line) {
	++lineNumber; // process line number

	line = line.substr(0, line.find(";")); // delete trailing comment
	
	int colpos = line.find(":");
	if(colpos != -1) return ""; // labels already picked ignore

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

	std::string data = gulp(buf); // store the operand or data in it (if required)
	trim(data);

	// process opcode
	bool found = false;
	for(auto& operation : oplist) {
		if((operation.name).compare(opcode) == 0) {
			found = true;
			int value = operation.code << 8; // shift by 8 bit to opcode section
			if(operation.usesLabels) {
				std::cout << "Operation: " << opcode
					  << " at " << lineNumber
					  << " uses labels\n";

				value |= processLabel(data);
			} else if(operation.hasOperand) {
				value |= std::atoi(data.c_str());
			}

			return getHexStr<int>(value) + " ";
		}
	}

	// check if opcode found
	if(!found) {
		std::cerr << "Unknown opcode: "
			  << opcode << " at " << lineNumber
			  << " setting NOP\n";
		return "0000 "; // return 0 if unknown
	}

	return ""; // just a case for failure
		
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
	
	pickLabels(in);
	
	std::string output = "";
	while(!in.eof()) {
		std::string line = "";
		getline(in, line); // copy a single line to process
		output += processLine(line); // add binary to output buffer
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

	for(struct Label x : labels) {
		std::cout << x.name << " " << x.lbpos << "\n";
	}
	return 0;
}
