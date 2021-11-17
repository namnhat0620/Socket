#include "pch.h"
#include "framework.h"
#include "serverGiaVang.h"
#include "afxsock.h"
#include "Function.h"

void response(int choice, char ServerMsg[], int& n)
{
	switch (choice) {
	case 1:
		ServerMsg[0] = '1';
		n++;
		break;
	case 2:
		ServerMsg[0] = '2';
		n++;
		break;
	default:
		break;
	}
}

void readFile(const char* fileName, json& j)
{
    ifstream fin(fileName);
    if (fin.fail())
        return;
    fin >> j;
    fin.close();
}

void writeFile(const char* fileName, json j)
{
    ofstream fout(fileName);
    if (fout.fail())
        return;
    fout << setw(4) << j << "\n\n";
    fout.close();
}

bool login(char* username, char* password, json j)
{
    int j_size = j["user"].size();
    for (int i = 0; i < j_size; i++)
    {
        string str_1 = j["user"][i]["username"];
        const char* s_1 = str_1.c_str();
        if (strcmp(s_1, username) == 0)
        {
            string str_2 = j["user"][i]["password"];
            const char* s_2 = str_2.c_str();
            if (strcmp(s_2, password) == 0)
                return true;
        }
    }
    return false;
}

bool Register(char* username, json j)
{
    int j_size = j["user"].size();
    for (int i = 0; i < j_size; i++)
    {
    string str = j["user"][i]["username"];
    const char* s = str.c_str();
    if (strcmp(s, username) == 0)
        return false;
    }
    return true;
}

bool login_register(CSocket& connector, char* username, char* password, json j, int check)
{
    if (check == 0)
    {
        if (Register(username, j))
        {
            int j_size = j["user"].size();
            char mes[] = "Dang ky thanh cong\n";
            int mes_length = strlen(mes);
            connector.Send(&mes_length, 4);
            connector.Send(mes, mes_length);
            j["user"][j_size]["username"] = string(username);
            j["user"][j_size]["password"] = string(password);
            writeFile("user.json", j);
            return true;
        }
        else
        {
            char mes[] = "Tai khoan da ton tai\n";
            int mes_length = strlen(mes);
            connector.Send(&mes_length, 4);
            connector.Send(mes, mes_length);
            return false;
        }

    }
    else
    {
        if (login(username, password, j))
        {
            char mes[] = "Dang nhap thanh cong! Bat dau thuc hien tra cuu!!!\n";
            int mes_length = strlen(mes);
            connector.Send(&mes_length, 4);
            connector.Send(mes, mes_length);
            return true;
        }
        else
        {
            char mes[] = "Tai khoan hoac mat khau khong dung\n";
            int mes_length = strlen(mes);
            connector.Send(&mes_length, 4);
            connector.Send(mes, mes_length);
            return false;
        }
    }
    return false;
}

DWORD WINAPI function_cal(LPVOID arg)
{
    SOCKET* hConnected = (SOCKET*)arg;
    CSocket mysock;
    //Chuyen ve lai CSocket
    mysock.Attach(*hConnected);

    do{
        //PHAN DANG NHAP
        int check = 0;
        mysock.Receive((char*)&check, 4);
        //Check 0 la dang ky, check 1 la dang nhap

        char* username = nullptr;
        char* password = nullptr;

    
        //Nhan tai khoan
        int use_size = 0;
        mysock.Receive((char*)&use_size, 4);
        username = new char[use_size + 1];
        username[use_size] = '\0';
        mysock.Receive(username, use_size);
        

         //Nhan mat khau
        int pass_size = 0;
        mysock.Receive((char*)&pass_size, 4);
        password = new char[pass_size + 1];
        password[pass_size] = '\0';
        mysock.Receive(password, pass_size);

        json j;
        readFile("user.json", j);

    
        if (check == 0)
        {
            if (login_register(mysock, username, password, j, check) == true)
                cout << "Client dang ky thanh cong\n";

            else
                cout << "Client dang ky that bai\n";
        }
        else if (check == 1)
        {
            if (login_register(mysock, username, password, j, check) == true)
            {
                cout << "Client dang nhap thanh cong\n";
                break;
                /// Tien hanh tra cuu
            }
            else
                cout << "Client dang nhap that bai\n";
        }
        else
            break;
     
        delete[] username;
        delete[] password;
    } while (1);

    /*int choice = 0;
    while (choice >= 0) {
        int MsgSize;
        char* temp;
        //Nhan thong diep tu Client
        mysock.Receive((char*)&MsgSize, sizeof(int), 0); // Neu nhan loi thi tra ve la SOCKET_ERROR.		
        temp = new char[MsgSize + 1];
        mysock.Receive((char*)temp, MsgSize, 0);
        choice = temp[0] - 48;
        char ServerMsg[100];
        int n = 0;
        //Xoa thong diep cua Client
        delete temp;
        MsgSize = 0;
        //Tao response
        response(choice, ServerMsg, n);
        MsgSize = n;
        // Gui di do dai thong diep de client biet duoc do dai nay
        mysock.Send(&MsgSize, sizeof(MsgSize), 0);

        // Gui di thong diep voi do dai la MsgSize
        mysock.Send(ServerMsg, MsgSize, 0);

    }*/
    delete hConnected;
    return 0;
    //return 0;
}