#include "pch.h"
#include "Function.h"
#include <iostream>
using namespace std;

bool DangNhap(CSocket& client)
{
    do
    {
        int choice = 0;
        //1 la dang nhap , 0 la dang ky, cac so con lai la ket thuc chuong trinh
        cout << "Nhap lua chon (1 la dang nhap , 0 la dang ky): ";
        cin >> choice;
        cin.ignore();

        client.Send(&choice, 4);
        if (choice != 0 && choice != 1)
            break;

        char username[30];
        char password[30];

        cout << "username: ";
        cin.getline(username, 30);
        int use_length = strlen(username);

        cout << "password: ";
        cin.getline(password, 30);
        int pass_length = strlen(password);

        client.Send(&use_length, 4);
        client.Send(username, use_length);
        client.Send(&pass_length, 4);
        client.Send(password, pass_length);

        char* ans = nullptr;
        int size = 0;
        client.Receive((char*)&size, 4);
        ans = new char[size + 1];
        ans[size] = '\0';
        client.Receive(ans, size);
        cout << ans;
        if (strcmp(ans, "Dang nhap thanh cong! Bat dau thuc hien tra cuu!!!\n") == 0)
        {
            return true;
        }
    } while (1);
    return false;
}
