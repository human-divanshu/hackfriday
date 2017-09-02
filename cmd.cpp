#include "cmd.h"
#include <fstream>

void copy(string path1, string path2)
{

	
	ifstream in(path2);
	if(in.good()){
		// OUTPUT ALREADY EXISTS
		// ABORT
		in.close();
		cout<< "\e[1;31m OUTPUT FILENAME ALREADY EXISTS \e[0m"<<endl;
	}

	else{		
		
		ifstream in(path1);
		
		if(in.good()){

			ofstream out(path2);
			string str;
			while(getline(in, str)){
				out<<str<<endl;
			}

			in.close();
			out.close();
		}		

		else{

			// INPUT DOES NOT EXISTS
			// ABORT
			in.close();
			cout<< "\e[1;31m INPUT FILENAME DOES NOT EXISTS \e[0m"<<endl;
		}
	}

}

void cat(string str)
{


	ifstream in(str);
	if(in.good()){

		string str;
		while(getline(in, str)){
			cout<<str<<endl;
		}

		in.close();
	}

	else{

		cout<< "\e[1;31m INPUT FILENAME DOES NOT EXISTS \e[0m"<<endl;	
	}
}

void head(string str)
{

	ifstream in(str);
	if(in.good()){
		int count = 0;
		string str;
		while(getline(in, str)){
			
			if(count == 10)
				break;
			cout<<str<<endl;
			count++;
		}

		in.close();
	}

	else{

		cout<< "\e[1;31m INPUT FILENAME DOES NOT EXISTS \e[0m"<<endl;	
	}

}

void help(){
	cout << "KocharTech Shell version 1.0 (for unix only)" << endl;
	cout << "These shell commands are defined internally" << endl;
	cout << "* copy [src] [dest]\t\t\tcopies a source file to some destination address" << endl;
	cout << "* dir\t\t\t shows the list of files in current directory" << endl;
	cout << "* pwd\t\t\tshows the present working directory" << endl;
	cout << "* cd [path]\t\t\tchanges the current working directory to the given path" << endl;
	cout << "* move [src] [dest]\t\t\tmoves the source file to some destination address" << endl;
	cout << "* find [keyword] [path]\t\t\tfinds occurances of a keyword in the given file" << endl;
	cout << "* whoami\t\t\treturns the active current user" << endl;
	cout << "* echo [something]\t\t\tprints the argument to the terminal as is" << endl;
	cout << "* history\t\t\tdisplays the previously executed commands in the current session" << endl;
	cout << "* help\t\t\tshows help menu (this one)" << endl;
	cout << "* cat [file]\t\t\tdisplays the content of the file" << endl;
	cout << "* wc [file]\t\t\tshows the number of words, characters and lines in a file" << endl;
	cout << "* date\t\t\tshows the current date" << endl;
	cout << "* diff [file1] [file2]\t\t\tshows the difference between 2 files" << endl;
	cout << "* head [file]\t\t\tshows first 10 lines of a file" << endl;
	cout << "* tail [file]\t\t\tshows last 10 lines of a file" << endl;
	cout << "* del [file]\t\t\tdeleted the file" << endl;
	cout << "* rname [oldname] [new]\t\t\trenames a file from old to new" << endl;
	cout << "* sort [file]\t\t\tsorts and displays content of the file" << endl;
	cout << "* unique [file]\t\t\tshows distince words of a file" << endl;
	cout << "* sleep [time]\t\t\tsleeps for given time" << endl;
	cout << "* uptime\t\t\tshows uptime of the terminal" << endl;
	cout << "* printlogo\t\t\tprints KocharTech logo" << endl;
	cout << "* touch [filename]\t\t\tcreates new file" << endl;
	cout << "* mkdir [name]\t\t\tcreates a directory with given name" << endl;
	cout << "* rmdir [name]\t\t\tremoves the directory" << endl;
}

void tail(string str)
{

	ifstream in(str);
	vector<string> vec;
	if(in.good()){
		
		while(getline(in, str)){
			vec.push_back(str);
		}

		int size = vec.size();
		int count = 0;
		for(string s : vec){
			count++;
			if(count >= size - 9)
				cout<<s<<endl;
			
		}

	}

	else{

		cout<< "\e[1;31m INPUT FILENAME DOES NOT EXISTS \e[0m"<<endl;	
	}
}

void del(string file)
{
	if( remove(file.c_str()) != 0 )
    	cout<< "\e[1;31m INPUT FILENAME DOES NOT EXISTS \e[0m"<<endl;
}

void rname(string old_name, string new_name)
{

	if(rename(old_name.c_str(), new_name.c_str()) != 0)
		cout<< "\e[1;31m INPUT FILENAME DOES NOT EXISTS \e[0m"<<endl;	
}
