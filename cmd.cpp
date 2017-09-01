#include "cmd.h"

Command temp[24];

cmdVector.push_back(temp[0]("copy", 2));
cmdVector.push_back(temp[1]("dir", 0));
cmdVector.push_back(temp[2]("pwd", 0));
cmdVector.push_back(temp[3]("cd", 1));
cmdVector.push_back(temp[4]("move", 2));
cmdVector.push_back(temp[5]("find", 1));
cmdVector.push_back(temp[6]("whoami", 0));
cmdVector.push_back(temp[7]("exit", 0));
cmdVector.push_back(temp[8]("echo", 0));
cmdVector.push_back(temp[9]("history", 0));
cmdVector.push_back(temp[10]("help", 0));
cmdVector.push_back(temp[11]("cat", 1));
cmdVector.push_back(temp[12]("wc", 1));
cmdVector.push_back(temp[13]("date", 0));
cmdVector.push_back(temp[14]("diff", 2));
cmdVector.push_back(temp[15]("head", 1));
cmdVector.push_back(temp[16]("tail", 1));
cmdVector.push_back(temp[17]("man", 1));
cmdVector.push_back(temp[18]("time", 0));
cmdVector.push_back(temp[19]("delete", 1));
cmdVector.push_back(temp[20]("rename", 2));
cmdVector.push_back(temp[21]("uniq", 1));
cmdVector.push_back(temp[22]("sleep", 1));
cmdVector.push_back(temp[23]("uptime", 0));