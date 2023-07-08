#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define maxchar 100
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
int main(){
	char username[100];
    char password[100];
	
	int client_sock;
	char buff[BUFF_SIZE + 1];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_received;
	int choice;
	
	//Step 1: Construct socket
	client_sock = socket(AF_INET,SOCK_STREAM,0);
	
	//Step 2: Specify server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	
	//Step 3: Request to connect server
	if(connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0){
		printf("\nError!Can not connect to sever! Client exit imediately! ");
		return 0;
	}
		
	//Step 4: Communicate with server			
	int islogin=0;
	//send message
	do{
		printf("\n1.loging\n2.logout\n3.receive question\nyour choice:");
		scanf("%d",&choice);
		if(islogin==0&&choice==1|| islogin==1&&(choice ==2||choice==3)||choice==4){
		if (send(client_sock, &choice, sizeof(choice), 0) == -1) {
			perror("send() failed");
		}}
		switch (choice) {
            case 1:
					if(islogin==1){
						printf("\n you are logged in\n");
						break;
					}
					while(1){		
					printf("Enter your username: ");
					scanf("%s", username);
					printf("Enter your password: ");
					scanf("%s", password);

					// Send username and password to server
					sprintf(buff, "%s %s", username, password);
					msg_len = strlen(buff);
					bytes_sent = send(client_sock, buff, msg_len, 0);
					if(bytes_sent < 0)
					perror("\nError: ");
					int k; 			//number received from server to know  login results
					bytes_received = recv(client_sock, &k, BUFF_SIZE, 0);
					if (bytes_received < 0)
							perror("\nError: ");
					else if (bytes_received == 0)
							printf("Connection closed.\n");
						


					printf("\nReply from server: ");			//printf the result
					if (k==1){
						printf("OK\n");
						islogin=1;
						break;

						}else if(k==0)
						{
							printf("Account not ready\n");
						}
						else if(k==2){
								printf("not OK\n");
						}
					}
					break;
			case 2:
					if(islogin==0){
						printf("\n you are not logged in\n");
						break;
					}else{
						islogin=0;
						printf("\nlogged out\n");break;
					}
			case 3:
					if(islogin==0){
						printf("\n you are not logged in\n");
						break;
					}else{
					
						
					bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
					if (bytes_received == -1) {
						perror("Error: ");
						break;
					} else if (bytes_received == 0) {
						printf("Server closed the connection.\n");
						break;
					}

					buff[bytes_received] = '\0';
					printf("%s", buff);

				break;}
			case 4:
				while (1) {
					printf("Enter your username: ");
                    scanf("%s", username);
                    printf("Enter your password: ");
                    scanf("%s", password);

                    // Send username and password to server
                    sprintf(buff, "%s %s", username, password);
                    msg_len = strlen(buff);
                    bytes_sent = send(client_sock, buff, msg_len, 0);
                    if (bytes_sent < 0)
                        perror("\nError: ");
                    int k; //number received from server to know  login results
                    bytes_received = recv(client_sock, &k, sizeof(k), 0);
                    if (bytes_received < 0)
                        perror("\nError: ");
                    else if (bytes_received == 0)
                        printf("Connection closed.\n");

						//printf("\n%d\n",k);

                    printf("\nReply from server: "); //printf the result
                    if (k==1){
						printf("singup OK\n");
						islogin=0;
						break;

						}else if(k==0)
						{
							printf("Account existed\n");
						}
				}
				break;
			default: break;
		}
	}while (choice >= 1 && choice <= 4);
		



	//Step 4: Close socket
	close(client_sock);
	return 0;
}
