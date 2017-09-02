#include "cmd.h"
#include <fstream>
#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <unistd.h>
using namespace std;

void dir(string s){
    vector<string> result;
    
    const char *path = s.c_str();
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

void history(vector<string> v){
    int j = 0;
    for(int i = 0; i < v.size(); i++){
        cout << "\e[1m" << j++ << "\e[0m  " << v[i] << endl;
    }
    return;
}

void whoami(){
    char *buf;
    buf=(char *)malloc(10*sizeof(char));
    cuserid(buf);
    cout << buf << endl;
}

void sleep(string seconds, string type){
    if(type == "INT" || type == "FLOAT")
        usleep(stof(seconds)*1000000);
    return;
}

void touch(string filename){
    ofstream f(filename);    
    f.close();
    return;
}

string getcwd() 
{
    char cwd[1024];    
    getcwd(cwd, sizeof(cwd));
    string str(cwd);
    return str;
}

void pwd()
{
    cout << getcwd() << endl;
}

string cd(string path){
    if(chdir(path.c_str()) == 0);
    else cout << "\033[1;31mInvalid path.. \033[0m\n";
    return getcwd();
}

void makedir(string path1){
    
}