#include "cmd.h"

#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

void dir(string s){
    vector<string> result;
    
    char* path = new char[s.length()];
    for(int i = 0; i < s.length(); i++){
        path[i] = s[i];
    }
    DIR *pdir = NULL;
    pdir = opendir (path); 
    struct dirent *pent = NULL;
    if (pdir == NULL){         
        return;
    } 
    while (pent = readdir (pdir)){
        if (pent == NULL){            
            return;
        }
        if((pent->d_name)[0] == '.') continue;
        result.push_back(pent->d_name);
    }
    closedir(pdir);
    
    sort(result.begin(), result.end());
    for(int i = 0; i < result.size(); i++){
        cout << result[i] << "  ";
    }
    cout << endl;
    
    return;
}

void time(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "\e[1;34m" << ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << ltm->tm_sec << " \e[0m" << endl;    
    return;
}

void date(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "\e[1;34m" << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << " \e[0m" << endl;
    return;
}

