// serverGiaVang.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "serverGiaVang.h"
#include "afxsock.h"
#include "Function.h"

using namespace std;

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
            CSocket server;
            unsigned int port = 1234;
            int i;
            AfxSocketInit(NULL);

            server.Create(port);
            server.Listen(5);

            //Nhap so luong client
            cout << "Nhap so luong Client: ";
            int num_client = 0;
            cin >> num_client;
            fflush(stdin);
            cout << "Dang lang nghe ket noi tu Client..." << endl;
            //Tao mang chua cac socket client
            CSocket* sockClients = new CSocket[num_client];
            //Khoi tao con tro Socket
            SOCKET* hConnected = new SOCKET();

            //Tao mang thread
            DWORD* threadID = new DWORD[num_client];
            HANDLE* threadStatus = new HANDLE[num_client];
            for (i = 0; i < num_client; i++) {
                server.Accept(sockClients[i]);
                cout << "Da tiep nhan client " << i + 1 << "/" << num_client << endl;

                //Bao cho client biet minh la client thu may
                sockClients[i].Send((char*)&i, sizeof(int), 0);

                //Chuyen doi CSocket thanh Socket
                *hConnected = sockClients[i].Detach();
                //Tao thread xu ly tung client
                threadStatus[i] = CreateThread(NULL, 0, function_cal, hConnected, 0, &threadID[i]);
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
