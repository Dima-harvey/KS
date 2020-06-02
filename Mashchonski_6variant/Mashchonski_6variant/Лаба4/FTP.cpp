#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <winsock2.h> 
#include <WS2tcpip.h> 
#include <iostream> 
#include <ctime> 
#include <math.h> 
#include <fstream> 
#include <windows.h> 
#include <vector> 
#include <sstream> 
#include <cstring> 
#include <sstream> 
#include <string> 
#pragma comment(lib,"WS2_32.lib") 

using namespace std;
char* readServ(int S)
{
	int rc;
	fd_set fdr;
	FD_ZERO(&fdr);
	FD_SET(S, &fdr);
	timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	char* buff = new char[100];
	int test = recv(S, buff, INT_MAX, 0);
	buff[test] = '\0';
	rc = select(S, &fdr, NULL, NULL, &timeout);
	return buff;
}
char* steep = new char[512];
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	int port = 21;
	cout << "IP :" <<" 127.0.0.1 "<< endl;
	cout << endl;
	cout << "Port:" <<" 21 "<< endl;
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 0), &WSAData) != 0)
	{
		cout << "WSA ERROR";
		system("pause");
		return -1;
	}
	sockaddr_in address;
	SOCKET S = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(port);

	int len;
	int result;
	len = sizeof(address);
	result = connect(S, (sockaddr*)&address, len);
	if (result == -1)
	{
		cout << "CONNECT ERROR";
		system("pause");
		return -1;
	}
	readServ(S);
	char name[512] = "USER stud01\r\n";
	send(S, name, strlen(name), 0);
	readServ(S);

	char pass[512] = "PASS stud\r\n";
	send(S, pass, strlen(pass), 0);
	readServ(S);
	char pasv[512] = "PASV\r\n";
	char* arr;
	char* arr1;
	send(S, pasv, strlen(pasv), 0);
	arr = readServ(S);
	arr1 = readServ(S);
	string str = string(arr);
	string str1 = string(arr1);

	int index1 = str1.find_last_of(')');
	int index2 = str1.find_last_of(',');
	int index3 = str1.find_last_of(',', index2 - 1);

	string highStr = str1.substr(index3 + 1, index2 - index3 - 1);
	string lowStr = str1.substr(index2 + 1, index1 - index2 - 1);

	int high = atoi(highStr.c_str()) * 256;
	int low = atoi(lowStr.c_str());
	cout << "New Port: " << high + low << endl;
	sockaddr_in address2;
	SOCKET S2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	address2.sin_family = AF_INET;
	address2.sin_addr.s_addr = inet_addr("127.0.0.1");
	address2.sin_port = htons(high + low);

	int len2;
	int result2;
	len2 = sizeof(address2);
	result2 = connect(S2, (sockaddr*)&address2, len2);
	if (result2 == -1)
	{
		cout << "CONNECT ERROR" << endl;
		cout << WSAGetLastError() << endl;
		system("pause");
		return -1;
	}
	char list[512] = "LIST\r\n";
	send(S, list, strlen(list), 0);
	readServ(S2);
	closesocket(S2);
	cout << endl;
	cout << "Enter directory: " << endl;
	char* dir = new char[512];
	cin >> dir;
	char cdw[512] = "CWD ";
	strcat_s(cdw, dir);
	strcat_s(cdw, "\r\n");
	send(S, cdw, strlen(cdw), 0);
	readServ(S);
	S2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	address2.sin_family = AF_INET;
	address2.sin_addr.s_addr = inet_addr("127.0.0.1");
	address2.sin_port = htons(high + low);
	len2 = sizeof(address2);
	result2 = connect(S2, (sockaddr*)&address2, len2);
	if (result2 == -1)
	{
		cout << "CONNECT ERROR" << endl;
		system("pause");
		return -1;
	}
	send(S, list, strlen(list), 0);
	char message[30];
	int sizeMessage = 0;
	bool end = false;
	int i = 0;
	std::vector<std::string> VecStr1;
	std::vector<std::string> VecStr2;
	string* test = new string[100];
	do {
		ZeroMemory(message, sizeof(message));
		sizeMessage = recv(S2, message, sizeof(message), NULL);
		if (sizeMessage < sizeof(message)) {
			VecStr1.push_back( message);
			cout << message;

		}
		else
			for (i = 0; i < sizeMessage; i++)
			VecStr1.push_back(message);

		cout << message;
	} while (sizeMessage == sizeof(message));
	
	int b = 1;
	for (;;) {
		Sleep(5000);
		cout << "-------------------------------------------------------" << endl;
		S2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		address2.sin_family = AF_INET;
		address2.sin_addr.s_addr = inet_addr("127.0.0.1");
		address2.sin_port = htons(high + low);
		len2 = sizeof(address2);
		result2 = connect(S2, (sockaddr*)&address2, len2);
		if (result2 == -1)
		{
			cout << "CONNECT ERROR" << endl;
			system("pause");
			return -1;
		}
		send(S, list, strlen(list), 0);
		do {
			ZeroMemory(message, sizeof(message));
			sizeMessage = recv(S2, message, sizeof(message), NULL);
			if (sizeMessage < sizeof(message)) {
				VecStr2.push_back(message);
				cout << message;

			}
			else
				for (i = 0; i < sizeMessage; i++)
					VecStr2.push_back(message);

			cout << message;
		} while (sizeMessage == sizeof(message));
		if (b == 1) {
			if (VecStr1.size() > VecStr2.size()) {
				cout << " В данном каталоге был удалён файл" << endl;
			}
			if (VecStr1.size() < VecStr2.size()) {
				cout << " В данном каталоге был добавлен файл" << endl;
				
			}
			if (VecStr1.size() == VecStr2.size()) {
				cout << " В данном каталоге ничего не произошло" << endl;
			}
			VecStr2.clear();
		}
		Sleep(5000);
	
	}
	cout << "End of program" << endl;
	system("pause");
	return 0;
}