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
	cout << "* copy [src] [dest]     | copies a source file to some destination address" << endl;
	cout << "* dir					 | shows the list of files in current directory" << endl;
	cout << "* pwd					 | shows the present working directory" << endl;
	cout << "* cd [path]             | changes the current working directory to the given path" << endl;
	cout << "* move [src] [dest]	 | moves the source file to some destination address" << endl;
	cout << "* find [keyword] [path] | finds occurances of a keyword in the given file" << endl;
	cout << "* whoami				 | returns the active current user" << endl;
	cout << "* echo [something]		 | prints the argument to the terminal as is" << endl;
	cout << "* history				 | displays the previously executed commands in the current session" << endl;
	cout << "* help					 | shows help menu (this one)" << endl;
	cout << "* cat [file]			 | displays the content of the file" << endl;
	cout << "* wc [file]			 | shows the number of words, characters and lines in a file" << endl;
	cout << "* date                  | shows the current date" << endl;
	cout << "* diff [file1] [file2]  | shows the difference between 2 files" << endl;
	cout << "* head [file]           | shows first 10 lines of a file" << endl;
	cout << "* tail [file]           | shows last 10 lines of a file" << endl;
	cout << "* del [file]            | deleted the file" << endl;
	cout << "* rname [oldname] [new] | renames a file from old to new" << endl;
	cout << "* sort [file]			 | sorts and displays content of the file" << endl;
	cout << "* unique [file]		 | shows distince words of a file" << endl;
	cout << "* sleep [time]          | sleeps for given time" << endl;
	cout << "* uptime				 | shows uptime of the terminal" << endl;
	cout << "* printlogo			 | prints KocharTech logo" << endl;
	cout << "* touch	[filename]	 | creates new file" << endl;
	cout << "* mkdir [name]			 | creates a directory with given name" << endl;
	cout << "* rmdir [name]			 | removes the directory" << endl;
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
