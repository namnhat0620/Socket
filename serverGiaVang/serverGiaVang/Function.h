#ifndef Function_h
#define Function_h
#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>

using namespace std;
using namespace nlohmann;

void response(int choice, char ServerMsg[], int& n);

void readFile(const char* fileName, json& j);

void writeFile(const char* fileName, json j);

bool login(char* username, char* password, json j);

bool Register(char* username, json j);

bool login_register(CSocket& connector, char* username, char* password, json j, int check);

DWORD WINAPI function_cal(LPVOID arg);


#endif // !Function_h

