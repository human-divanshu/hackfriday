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
