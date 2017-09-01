#include "cmd.h"

vector<Command> cmdVector;

cmdVector.push_back(Command("copy", 2));
cmdVector.push_back(Command("dir", 0));
cmdVector.push_back(Command("pwd", 0));
cmdVector.push_back(Command("cd", 1));
cmdVector.push_back(Command("move", 2));
cmdVector.push_back(Command("find", 1));
cmdVector.push_back(Command("whoami", 0));
cmdVector.push_back(Command("exit", 0));
cmdVector.push_back(Command("echo", 0));
cmdVector.push_back(Command("history", 0));
cmdVector.push_back(Command("help", 0));
cmdVector.push_back(Command("cat", 1));
cmdVector.push_back(Command("wc", 1));
cmdVector.push_back(Command("date", 0));
cmdVector.push_back(Command("diff", 2));
cmdVector.push_back(Command("head", 1));
cmdVector.push_back(Command("tail", 1));
cmdVector.push_back(Command("man", 1));
cmdVector.push_back(Command("time", 0));
cmdVector.push_back(Command("delete", 1));
cmdVector.push_back(Command("rename", 2));
cmdVector.push_back(Command("uniq", 1));
cmdVector.push_back(Command("sleep", 1));
cmdVector.push_back(Command("uptime", 0));