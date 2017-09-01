#include <iostream>
#include <string>
#include <vector>

using namespace std;

void copy(string path1, string path2);
void dir();
void pwd();
void cd(string path);
void move(string file1, string des);
void find(string filename);
void whoami();
void echo(string s);
void history();
void help();
void cat(string filename);
void wc(string filename);
void date();
void date();
void diff(string file1, string file2);
void head(string filename);
void tail(string filename);
void man(string cmd);
void time();
void del(string filename);
void rename(string filename, string newname);
void sort(string filename); // sort contents
void unique(string filename); // arrage content 
void sleep(int timesec);
void uptime();
void redirect(string content, string filename); // write content to file
