#include <iostream>
#include <string>
#include <algorithm>
#include "myfuns.h"

using namespace std;

int main(void)
{
	string s;
	do {
		cout << ">>> ";
		getline(cin, s);
		cout << trim(s) << endl;
	} while(trim(s) != "exit");
	
	return 0;
}