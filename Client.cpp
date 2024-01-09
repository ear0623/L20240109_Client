#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "iostream"
#include "WinSock2.h"
#include <string>

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
	ServerSocketAddr.sin_family = AF_INET;//�ּ�ü��
	ServerSocketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//4byte���·� low�ϰ� 
	ServerSocketAddr.sin_port = htons(40211);//��Ʈ��ȣ(//���� ������ �ִ�)


	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//tcp 0���νᵵ ���� �������.

	Result = connect(ServerSocket, (SOCKADDR*)&ServerSocketAddr, sizeof(ServerSocketAddr));//��ī��� �����̶� ����
	if (Result == SOCKET_ERROR)
	{
		cout << "Can't Connect : " << GetLastError() << endl;
		exit(-1);
	}
	while (true)
	{
		char RecvBuffer[1024] = { 0, };//�ִ����ũ��//�ӽ�����


		int RecvByte = recv(ServerSocket, RecvBuffer, sizeof(RecvBuffer), 0);//�ִ���۱���//os�� ���������� ������

		//char FirstNumber = RecvBuffer[0] - 48;
		//char SecondNumber = RecvBuffer[2] - 48;
		//char RecvResult = FirstNumber + SecondNumber;
		//RecvResult += 48;

		//char Answer[1024] = { 0, };
		//Answer[0] = RecvResult;
		//Answer[1] = '\n';

		cout<<"ServerSend" << RecvBuffer << endl;

		string Data = RecvBuffer;
		size_t OperatorPosition = Data.find('+');
		if (OperatorPosition == string::npos)
		{
			OperatorPosition = Data.find('*');
			if (OperatorPosition == string::npos)
			{
				OperatorPosition = Data.find('-');
				if (OperatorPosition == string::npos)
				{
					OperatorPosition = Data.find('/');
					if (OperatorPosition == string::npos)
					{
						OperatorPosition = Data.find('%');
					}
				}
			}
		}

		string FirstNumberString = Data.substr(0, OperatorPosition);
		string SecondNumberString = Data.substr(OperatorPosition + 1, Data.length() - OperatorPosition - 1);

		cout << FirstNumberString << endl;
		cout << SecondNumberString << endl;

		int FirstNumber = stoi(FirstNumberString);
		int SecondNumber = stoi(SecondNumberString);
		int ResultNumber=0
			;
		OperatorPosition = Data.find('+');
		if (OperatorPosition == string::npos)
		{
			OperatorPosition = Data.find('*');
			if (OperatorPosition == string::npos)
			{
				OperatorPosition = Data.find('-');
				if (OperatorPosition == string::npos)
				{
					OperatorPosition = Data.find('/');
					if (OperatorPosition == string::npos)
					{
						OperatorPosition = Data.find('%');
						ResultNumber = FirstNumber % SecondNumber;
					}
					else
					{
						ResultNumber = FirstNumber / SecondNumber;
					}
				}
				else
				{
					ResultNumber = FirstNumber - SecondNumber;
				}
			}
			else
			{
				ResultNumber = FirstNumber * SecondNumber;
			}
		}
		else
		{
			ResultNumber = FirstNumber + SecondNumber;
		}

		char Buffer[1024] = { 0, };
		sprintf_s(Buffer, 1024, "%d", ResultNumber);

		RecvByte = send(ServerSocket, Buffer, strlen(Buffer) + 1, 0);//�ִ���۱���//os�� ���������� ������

		cout << RecvBuffer << Buffer << endl;
	}
	

	closesocket(ServerSocket);

	WSACleanup();
	return 0;
}
//Ư¡- �ڷ�� ������ �ʾ�.//mmorpg���� ���¹��// ���� �и��� 




//computor->OS->NIC->
//App
//App->Socket->OS(bind)->NIC(->Port)
//client
//server
//os->TCP �������ִٰ� recv�� ����
//protocol �Ծ� ����//����������������� tcp;

//server -> Client;
//Socket	Scoket

//Bind		connect
//Listen
//Accept

//send / recv	recv/send
//�̹��� �ؽ�Ʈ ���� ���� ����������/
//��� �ڵ�->���ƾ� �Ϻκи� �������� ����.//