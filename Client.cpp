#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "iostream"
#include "WinSock2.h"
#include <string>

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
	ServerSocketAddr.sin_family = AF_INET;//주소체계
	ServerSocketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//4byte형태로 low하게 
	ServerSocketAddr.sin_port = htons(40211);//포트번호(//예가 가지고 있는)


	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//tcp 0으로써도 요즘엔 상관없음.

	Result = connect(ServerSocket, (SOCKADDR*)&ServerSocketAddr, sizeof(ServerSocketAddr));//랜카드랑 소켓이랑 연결
	if (Result == SOCKET_ERROR)
	{
		cout << "Can't Connect : " << GetLastError() << endl;
		exit(-1);
	}
	while (true)
	{
		char RecvBuffer[1024] = { 0, };//최대버퍼크기//임시저장


		int RecvByte = recv(ServerSocket, RecvBuffer, sizeof(RecvBuffer), 0);//최대버퍼길이//os로 싸짊어저서 보내줌

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

		RecvByte = send(ServerSocket, Buffer, strlen(Buffer) + 1, 0);//최대버퍼길이//os로 싸짊어저서 보내줌

		cout << RecvBuffer << Buffer << endl;
	}
	

	closesocket(ServerSocket);

	WSACleanup();
	return 0;
}
//특징- 자료는 날라가지 않어.//mmorpg에서 쓰는방법// 단점 밀리면 




//computor->OS->NIC->
//App
//App->Socket->OS(bind)->NIC(->Port)
//client
//server
//os->TCP 싸짊머있다가 recv시 구현
//protocol 규약 약정//연결지향형방법으로 tcp;

//server -> Client;
//Socket	Scoket

//Bind		connect
//Listen
//Accept

//send / recv	recv/send
//이미지 텍스트 압축 전송 동영상파일/
//고급 코덱->좋아야 일부분만 변동값만 같이.//