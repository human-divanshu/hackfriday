#include "myfuns.h"

string trim(string s){        
    int i, j;
    for(i = 0; s[i]==' '; i++);
    for(j = s.length()-1; s[j]==' '; j--);
    return s.substr(i, j-i+1);
}

string lower(string s){
	for(int i = 0; i < s.length(); i++){
        s[i] = s[i] + 32;
    }
    return s;
}

