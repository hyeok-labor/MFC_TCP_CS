// TCPServ01.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "TCPServ01.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 애플리케이션 개체입니다.

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 여기에 애플리케이션 동작을 코딩합니다.
            wprintf(L"심각한 오류: MFC 초기화 실패\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 여기에 애플리케이션 동작을 코딩합니다.
            _tsetlocale(LC_ALL, _T(""));
            AfxSocketInit();    // 소켓 초기화

            CSocket sock;
            if (!sock.Create(44000))
                MessageBox(NULL, _T("소켓생성에러"), _T("소켓생성에러"), MB_ICONERROR);
            if(!sock.Listen())
                MessageBox(NULL, _T("소켓대기에러"), _T("소켓대기에러"), MB_ICONERROR);

            TCHAR buf[256 + 1];
            int nbytes;

            while (1) {  // 클라이언트 접속 허가
                CSocket newsock;
                if( !sock.Accept(newsock))
                    MessageBox(NULL, _T("클라이언트소켓생성에러"), _T("클라이언트소켓생성에러"), MB_ICONERROR);

                CString PeerAddr;
                UINT PeerPort;
                newsock.GetPeerName(PeerAddr, PeerPort);
                // _tprintf(_T("####IP주소 : %s, 포트번호 : %s ### \n"), (LPCTSTR)PeerAddr, PeerPort);
                cout << "ip==> " << (LPCTSTR)PeerAddr << ";" << "PORT--> " << PeerPort << endl;

                // 클라이언트에서 전송된 데이터 수신
                while (1) {
                    nbytes = newsock.Receive(buf, 256);
                    if (nbytes == 0 || nbytes == SOCKET_ERROR) {
                        MessageBox(NULL, _T("클라이언트수신완료 또는 에러"), _T("클라이언트수신완료 또는 에러"), MB_ICONERROR);
                        break;
                    }
                    else {
                        buf[nbytes] = _T('\0');
                        _tprintf(_T("%s, %d \n"), buf, nbytes);
                    }
                }
                newsock.Close();
            }
        }
    }
    else
    {
        // TODO: 오류 코드를 필요에 따라 수정합니다.
        wprintf(L"심각한 오류: GetModuleHandle 실패\n");
        nRetCode = 1;
    }

    return nRetCode;
}
