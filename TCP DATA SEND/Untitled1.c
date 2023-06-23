#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <string.h>

int main()
{
    char recvBuff[380000]={0};
    struct sockaddr_in server; /*sockadder_in otomatik varolan bir struck*/
    unsigned int s; /*socketler unsigned int t�r�ndedir */
    WSADATA wsa;   /*WSADATA STRUCK T�R�NDE YAPI*/
    printf("\nInitializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {             /*WSAStartup ve MAKEWORD TAM ANLAMADIM */

        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return 1;

    }

    printf("Initialized\n");
    s = socket(AF_INET , SOCK_STREAM , 0 );        /*AF_INET iNTERNET PROTOKULU SOCK_STREAM TCP TURU 0 PROTOKOL NUMARASI */ /*SOCKETLER UNSIGNED_INT T�R�NDE OLUR */
    if(s == INVALID_SOCKET)                                                 /*INVALID_SOCKET GE�ERS�Z SOKET UNSiGNED INT T�R�NDE*/
	{
		printf("Soket Olu�turulmad� : %d" , WSAGetLastError());
	}

	printf("Soket Olustu.\n");


	server.sin_addr.s_addr=inet_addr("127.0.0.1");      /*Server�n ip adresi*/
	server.sin_family=AF_INET;                          /*servera ba�lant� �ekli*/
	server.sin_port=htons(1470);                        /*port adresini little �eklinden big endiana �evirir*/
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)   /*Ba�lant� kurar sockadrr �zel bir struck sor !!! */
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");

   FILE *fp;
    fp = fopen("a.jpg", "rb");
    if(fp==NULL)
    {
        printf("Error opening file");
        return 1;
    }

    fread(recvBuff,1,380000,fp);
    if(send(s,recvBuff,sizeof(recvBuff),0)<0){
        printf("error");
        return 1;}
    printf("Data Send");
    getch();
    closesocket(s);fclose(fp);
    return 0;
}


