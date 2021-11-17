// clientGiaVang.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "clientGiaVang.h"
#include "afxsock.h"
#include <string>
#include "Function.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: code your application's behavior here.
            CSocket client;
            char sAdd[1000];
            unsigned int port = 1234; //Cung port voi server
            AfxSocketInit(NULL);

            //1. Tao socket
            client.Create();

            // Nhap dic chi IP cua server
            cout << "Nhap dia chi IP cua server: ";
            cin.getline(sAdd, 1000);


            if (client.Connect(CA2W(sAdd), port))
            {
                cout << "Client da ket noi toi server" << endl;
                //Nhan tu server, cho biet day la client thu may
                int id;
                client.Receive((char*)&id, sizeof(id), 0);
                cout << "Day la client thu " << id + 1 << endl;
           
                //DANG NHAP
                DangNhap(client);
            }
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
