#include <iostream>
#include <string>
#include <algorithm>
#include "myfuns.h"
#include <map>
#include <cctype>

using namespace std;
enum state {NONE, ALPHA, DIGIT, OPERATOR, SPACE, STRING, BLOCK, NEWLINE};
map<string, string> m;
string token;

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
	vector<string> v = {"print", "input", "if", "else", "while"};
	for(int i = 0; i < v.size(); i++) {
		if(v[i] == s)
			return true;
	}
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
			Token t("KEYWORD", s);
			return t;
		} else {
			Token t("ID", s);
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

	do {
		cout << ">>> ";
		getline(cin, s);
		s = trim(s);
		cout << s << endl;

		v = lexer(s);

		for(int i = 0; i < v.size(); i++) {
			cout << "<" << v[i].type << " , " << v[i].val <<  ">"<< endl;	
		}

	} while(trim(s) != "exit");
	
	return 0;
}