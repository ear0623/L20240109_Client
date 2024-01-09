#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "iostream"
#include "WinSock2.h"

#pragma comment(lib,"ws2_32")// �߰����� �ҷ����� ���

using namespace std;

int main()
{
	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);//dll�� �ҷ���//����Ʈ������ �о �Ҽ������� ����
	if (Result != 0)
	{
		cout << "Windsock dll error" << GetLastError() << endl;//������ �ִ� ������ �ַ��ڵ� ǥ��
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

	char RecvBuffer[1024] = { 0, };//�ִ����ũ��//�ӽ�����
	int RecvByte = recv(ServerSocket, RecvBuffer, sizeof(RecvBuffer), 0);//�ִ���۱���//os�� ���������� ������

	cout << "serverSent" << RecvBuffer;

	RecvByte = send(ServerSocket, RecvBuffer, strlen(RecvBuffer), 0);//�ִ���۱���//os�� ���������� ������

	cout << "SendData" << RecvBuffer;

	WSACleanup();
	return 0;
}