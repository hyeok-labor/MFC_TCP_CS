// TCPClt_01.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "TCPClt_01.h"

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
            if (!sock.Create())
                MessageBox(NULL, _T("소켓생성에러"), _T("소켓생성에러"), MB_ICONERROR);
            if (!sock.Connect(_T("127.0.0.1"), 44000))
                MessageBox(NULL, _T("서버연결에러"), _T("서버연결에러"), MB_ICONERROR);

            TCHAR buf[256 + 1];
            int nbytes;

           // 서버에 데이터 10회만 전송
            for (int i = 0; i < 10; i++) {
                wsprintf(buf, _T("%d번째 테스트 메시지 \r\n"), i);
                nbytes = sock.Send(buf, 256);
                if(nbytes == SOCKET_ERROR)
                    MessageBox(NULL, _T("데이터송신에러"), _T("데이터송신에러"), MB_ICONERROR);
                else
                {
                    _tprintf(_T("<%d> %d 바이트 전송 \n"), i, nbytes);
                    Sleep(1000);
                }
            }
            sock.Close();
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
