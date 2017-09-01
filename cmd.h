#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Command {
	public:
		string cmdName;
		int cmdArg;

	Command(string s, int i) {
		cmdName = s;
		cmdArg = i;		
	}
};

vector<Command> cmdVector;
void cmdinit();