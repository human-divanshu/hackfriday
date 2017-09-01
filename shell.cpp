#include <iostream>
#include <string>
#include <algorithm>
#include "myfuns.h"
#include <map>
#include <cctype>
#include <ctime>
#include "cmd.h"

using namespace std;
enum state {NONE, ALPHA, DIGIT, OPERATOR, SPACE, STRING, BLOCK, NEWLINE};
map<string, string> m;
string token;

map<string, int> cmdMap;


void cmdMapinit()
{
	cmdMap["copy"]  = 2;
	cmdMap["dir"] = 0;
	cmdMap["pwd"] = 0;
	cmdMap["cd"] = 1;
	cmdMap["move"] = 2;
	cmdMap["find"] = 1;
	cmdMap["whoami"] = 0;
	cmdMap["exit"] = 0;
	cmdMap["echo"] = 1;
	cmdMap["history"] = 0;
	cmdMap["help"] = 0;
	cmdMap["cat"] = 1;
	cmdMap["wc"] = 1;
	cmdMap["date"] = 0;
	cmdMap["diff"] = 2;
	cmdMap["head"] = 1;
	cmdMap["tail"] = 1;
	cmdMap["man"] = 1;
	cmdMap["time"] = 0;
	cmdMap["del"] = 1;
	cmdMap["rename"] = 2;
	cmdMap["uniq"] = 1;
	cmdMap["sleep"] = 1;
	cmdMap["uptime"] = 0;	
}

class Token {
	public:
		string type;
		string val;
	Token(string t, string v)
	{
		this->type = t;
		this->val = v;
	}
	Token(){}
};

bool isoperator(char ch)
{
	vector<char> v = {'+', '-', '*', '/', '=', '!', '>', '<'};
	for(int i = 0; i < v.size(); i++) {
		if(v[i] == ch)
			return true;
	}
	return false;
}

void throw_error(string s)
{
	cout << s << endl;
	exit(-1);
}

bool iskeyword(string s)
{	
	if(cmdMap.find(s) != cmdMap.end())
		return true;
	
	return false;
}

Token gettoken(string s, int readstate)
{	
	string type;
	if(readstate == NEWLINE) {
		Token t("LINE-END", "");
		return t; 
	} else if(readstate == ALPHA) {
		if(iskeyword(s)) {
			Token t("CMD", s);
			return t;
		} else {
			Token t("ATTR", s);
			return t;
		}
	} else if(readstate == DIGIT) {
		if(s.find(".") != string::npos) {
			if(s[s.size() - 1] == '.')
				s = s + "0";
			type = "FLOAT";
		} else {
			type = "INT";
		}
		Token t(type, s);
		return t;
	} else if(readstate == OPERATOR) {	
		
		if(s.size() == 2) {
			if(s == "==")
				type = "OP-EQL";
			else if(s == "!=")
				type = "OP-NEQL";
			else if(s == ">=")
				type = "OP-GTEQ";
			else if(s == "<=")
				type = "OP-LTEQ";
		} else {
			if(s == "+")
				type = "OP-SUM";
			else if(s == "-")
				type = "OP-SUB";
			else if(s == "*")
				type = "OP-MUL";
			else if(s == "/")
				type = "OP-DIV";
			else if(s == ">")
				type = "OP-GT";
			else if(s == "<")
				type = "OP-LT";
			else if(s == "=")
				type = "OP-ASSIGN";
		}
		Token t(type, s);
		return t;
	
	} else if(readstate == STRING) {
		Token t("STRING", s);
		return t;
	} else if(readstate == BLOCK) {
		if(s == "(")
			type = "LEFTPAREN";
		else if(s == ")")
			type = "RIGHTPAREN";
		else if(s == "{")
			type = "LEFTCURLY";
		else if(s == "}")
			type = "RIGHTCURLY";
		Token t(type, s);
		return t;
	}
}



vector<Token> lexer(string s)
{
	vector<Token> m;
	
	char ch;
	string token = "";
	
	int readstate = NONE; 
	int charcount = 0;
	int linecount = 1;
	
	int i = 0;
	while(i < s.size()) {
		ch = s[i++];
		charcount++;
		
		if(isalpha(ch)) {

			if(readstate == ALPHA) {
				token = token + ch;
			} else if(readstate == DIGIT) {
				throw_error(to_string(linecount) + ":" + to_string(charcount) + " Expecting digit here");
			} else if(readstate == STRING) {
				token = token + ch;
			} else if(readstate == NONE) {
				token = "";
				readstate = ALPHA;
				token = token + ch;
			} else if(readstate == OPERATOR) {
				m.push_back(gettoken(token, readstate));
				token = ch;
				readstate = ALPHA;
			}
			
		} else if(isdigit(ch) || (readstate == DIGIT && ch == '.')) {
		
			if(readstate == ALPHA) {
				token = token + ch;
			} else if(readstate == DIGIT) {
				token = token + ch;
			} else if(readstate == OPERATOR) {
				m.push_back(gettoken(token, readstate));
				//cout << "Token : " << token << endl;
				token = ch;
				readstate = DIGIT;
			} else if(readstate == NONE) {
				token = ch;
				readstate = DIGIT;
			} else if(readstate == STRING) {
				token = token + ch;
			}
			
		} else if(isoperator(ch)) {
			if(readstate == ALPHA) {
				m.push_back(gettoken(token, readstate));
				//cout << "Token : " << token << endl;
				readstate = OPERATOR;
				token = ch;
			} else if(readstate == DIGIT) {
				m.push_back(gettoken(token, readstate));
				//cout << "Token : " << token << endl;
				readstate = OPERATOR;
				token = ch;
			} else if(readstate == NONE) {
				token = ch;
				readstate = OPERATOR;
			} else if(readstate == OPERATOR) {
				m.push_back(gettoken(token, readstate));
				//cout << "Token : " << token << endl;
				token = ch;
				readstate = DIGIT;
			} else if(readstate == STRING) {
				token = token + ch;
			}
				
		} else if(isspace(ch)) {
			if(ch == '\n') {
				linecount++;
				charcount = 0;				
			}
				
			if(readstate == STRING) {
				token = token + ch;
			} else if(readstate == ALPHA) {
				m.push_back(gettoken(token, readstate));
				readstate = NONE;
			} else if(readstate == OPERATOR) {
				m.push_back(gettoken(token, readstate));
				readstate = NONE;
			} else if(readstate == DIGIT) {
				m.push_back(gettoken(token, readstate));
				readstate = NONE;
			}
			if(ch == '\n' && readstate != STRING)
				m.push_back(gettoken("\n", NEWLINE));
			
		} else if(ch == '"') {
			if(readstate == STRING) {				
				m.push_back(gettoken(token, readstate));
				//cout << "Token : " << token << endl;
				readstate = NONE;
			} else if(readstate == NONE) {
				token = "";
				readstate = STRING;
			}
		} else if(ch == '(' || ch == ')' || ch == '{' || ch == '}') {
			if(readstate != NONE)
				m.push_back(gettoken(token, readstate));
			token = ch;
			readstate = BLOCK;
			m.push_back(gettoken(token, readstate));
			readstate = NONE;
		} else if(ch == ',') {
			if(readstate != STRING) {
				m.push_back(gettoken(token, readstate));
				readstate = NONE;				
				token = "";
			}
		} else {
			if(readstate == STRING) {
				token = token + ch;
			}
		}
	}
	return m;
}

int main(void)
{
	string s;
	vector<Token> v;
	vector<string> historyVec;
	time_t now = time(0);

	// initialize the command structure
	cmdMapinit();

	printlogo();

	do {
		cout << ">>> ";
		getline(cin, s);
		s = trim(s);

		// cout << "size is : " << s.size() << endl;
		// cout << "vecot size : " << v.size() << endl;

		if(s.size() == 0) {
			continue;
		}

		historyVec.push_back(s);

		v = lexer(s+"\n");

		// print the lexer output here
		// for(int i = 0; i < v.size() - 1; i++) {
		// 	cout << "<" << v[i].type << " , " << v[i].val <<  ">"<< endl;	
		// }

		// cout << "vecot size : " << v.size() << endl;

		// do command processing here
		if(v.size() > 1) {

			if(v[0].type != "CMD") {
				cout << "\033[1;31m Invalid. Command not found \033[0m\n";
			} else {
				// check number of arguments
				if(v.size() - 2 != cmdMap[v[0].val]) {
					cout << "\033[1;31m Invalid number of arguments for command " << v[0].val  << "\033[0m \n";
				} else {
					// process the command here
					if(v[0].val == "dir") {
						dir(".");
					} else if(v[0].val == "date") {
						date();
					} else if(v[0].val == "time") {
						time();
					} else if(v[0].val == "history") {
						history(historyVec);
					}
				}
			}
		}

		// reset vector holding tokens
		v.clear();

	} while(trim(s) != "exit");
	
	return 0;
}