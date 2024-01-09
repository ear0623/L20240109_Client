#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "iostream"
#include "WinSock2.h"

#pragma comment(lib,"ws2_32")// 추가없이 불러오는 방법

using namespace std;

int main()
{
	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);//dll을 불러옴//바이트단위로 밀어서 소수점으로 만듬
	if (Result != 0)
	{
		cout << "Windsock dll error" << GetLastError() << endl;//가지고 있는 마지막 애러코드 표시
		exit(-1);
	}

	struct sockaddr_in ServerSocketAddr;
	memset(&ServerSocketAddr, 0, sizeof(ServerSocketAddr));
	ServerSocketAddr.sin_family = AF_INET;//
	ServerSocketAddr.sin_addr.s_addr = inet_addr("192.168.3.118");
	ServerSocketAddr.sin_port = htons(40211);


	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	Result = connect(ServerSocket, (SOCKADDR*)&ServerSocketAddr, sizeof(ServerSocketAddr));
	if (Result == SOCKET_ERROR)
	{
		cout << "Can't Connect : " << GetLastError() << endl;
		exit(-1);
	}

	char RecvBuffer[1024] = { 0, };//최대버퍼크기//임시저장
	int RecvByte = recv(ServerSocket, RecvBuffer, sizeof(RecvBuffer), 0);//최대버퍼길이//os로 싸짊어저서 보내줌

	cout << "serverSent" << RecvBuffer;

	RecvByte = send(ServerSocket, RecvBuffer, strlen(RecvBuffer), 0);//최대버퍼길이//os로 싸짊어저서 보내줌

	cout << "SendData" << RecvBuffer;

	WSACleanup();
	return 0;
}