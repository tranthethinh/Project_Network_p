#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

#include <mysql/mysql.h>

// Define the MySQL server connection parameters
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "123456"
#define DB_NAME "thinhtestdatabase"


#define BACKLOG 20   /* Number of allowed connections */
#define BUFF_SIZE 1024


// Define the maximum length of username and password
#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
//#define PORT 5550  /* Port that will be opened */ 
#define BUFF_SIZE 1024

// Define a structure to store account information
typedef struct Account {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int status;
    int num_signin_wrong;//know the number of times user entered the wrong password
    int is_logged_in;//=0 not logged_in
    struct Account* next;
}Account;
// Define a linked list to store all accounts6
Account *head=NULL;
Account *tail=NULL;

int sign_in(char username[MAX_USERNAME_LENGTH], char password[MAX_PASSWORD_LENGTH]);// return login result
Account *find_account();//find account in the list
void load_accounts();// Load account information from the file into the linked list
void freeList(Account* head); //free list
void update_status();// update status
void save_account();
int register_account(char username[MAX_USERNAME_LENGTH], char password[MAX_PASSWORD_LENGTH]);
/* Receive and echo message to client */
void *echo(void *);

int main(int argc, char *argv[])
{
    
	int PORT;
	int listenfd, *connfd;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in *client; /* client's address information */
	int sin_size;
	pthread_t tid;

	// Step 0: Get data from command
    if (argc != 2)
    {
        printf("Wrong command!./server PORT\n");
    }
    else
    {
        PORT = atoi(argv[1]);
    }
    load_accounts();

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		perror("\nError: ");
		return 0;
	}
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT); 
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   

	if(bind(listenfd,(struct sockaddr*)&server, sizeof(server))==-1){ 
		perror("\nError: ");
		return 0;
	}     

	if(listen(listenfd, BACKLOG) == -1){  
		perror("\nError: ");
		return 0;
	}
	
	sin_size=sizeof(struct sockaddr_in);
	client = malloc(sin_size);
	while(1){		
		connfd = malloc(sizeof(int));
		if ((*connfd = accept(listenfd, (struct sockaddr *)client, &sin_size)) ==- 1)
			perror("\nError: ");
				
		printf("You got a connection from %s\n", inet_ntoa(client->sin_addr) ); /* prints client's IP */
		
		/* For each client, spawns a thread, and the thread handles the new client */
		pthread_create(&tid, NULL, &echo, connfd);	
	}
	
	close(listenfd);
	return 0;
}

void *echo(void *arg){
    int connfd;
    int bytes_sent, bytes_received;
    char buff[BUFF_SIZE + 1];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    connfd = *((int *) arg);
    free(arg);
    pthread_detach(pthread_self());
    while(1){

        int choice;
			if (recv(connfd,  &choice, sizeof(choice), 0) == -1) {
				   perror("recv() failed");
				   break;
			}

        if( choice==1){
            //while(1){
            bytes_received = recv(connfd, buff, BUFF_SIZE, 0);
            if (bytes_received < 0)
            {
                perror("\nError: ");
                break;
            }
            else if (bytes_received == 0)
            {
                printf("Connection closed.\n");
                break;
            }

            buff[bytes_received]='\0';
            sscanf(buff,"%s %s", username, password);

            printf("Received username: %s, password: %s\n",username ,password);

            int k=sign_in(username,password);

            bytes_sent = send(connfd, &k, sizeof(k), 0); /* send the login result to the client  */
            if (bytes_sent < 0){
                perror("\nError: ");
                break;
            }
            // if(k==1){
            //     break;
            //     }
        //}
        choice=-1;
        }else if(choice==2){
            printf("\n%s logged out\n",username);
            buff[0]='\0';
            choice=-1;
        } else if (choice == 3) {
            // Read random questions functionality
            MYSQL *conn;
            MYSQL_RES *res;
            MYSQL_ROW row;

            conn = mysql_init(NULL);
            if (conn == NULL) {
                printf("Error: cannot initialize MySQL connection.\n");
                break;
            }

            if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
                printf("Error: cannot connect to MySQL database.\n");
                mysql_close(conn);
                break;
            }

            if (mysql_query(conn, "SELECT * FROM questions ORDER BY RAND() LIMIT 2")) {
                printf("Error: cannot execute MySQL query.\n");
                mysql_close(conn);
                break;
            }

            res = mysql_use_result(conn);
            if (res == NULL) {
                printf("Error: cannot retrieve MySQL result set.\n");
                mysql_close(conn);
                break;
            }

            // Send the questions to the client
            while ((row = mysql_fetch_row(res)) != NULL) {
                // Prepare the question string
                char question[BUFF_SIZE];
                snprintf(question, sizeof(question), "Question: %s\na. %s\nb. %s\nc. %s\nd. %s\n",
                         row[2], row[3], row[4], row[5], row[6]);

                // Send the question to the client
                bytes_sent = send(connfd, question, strlen(question), 0);
                if (bytes_sent < 0) {
                    perror("\nError: ");
                    break;
                }
            }

            // Free the MySQL result and close the connection
            mysql_free_result(res);
            mysql_close(conn);

            // Set choice to -1 to indicate that the operation is completed
            choice = -1;
        }else if( choice==4){
                            //while (1) {
                                int bytes_received = recv(connfd, buff, BUFF_SIZE, 0);
                                if (bytes_received < 0) {
                                    perror("\nError: ");
                                    break;
                                } else if (bytes_received == 0) {
                                    //printf("Connection closed.\n");
                                    break;
                                }

                                buff[bytes_received] = '\0';
                                sscanf(buff, "%s %s", username, password);

                                printf("Received username: %s, password: %s\n", username, password);
                                int k=register_account(username,password);
                                int bytes_sent = send(connfd, &k, sizeof(k), 0);
                                    if (bytes_sent == -1) {
                                        perror("\nError: ");
                                        break;
                                    }
                                    //if(k==1)break;
                                //}
                                choice =-1;
                        }

        
    }
    printf("\nthinh close\n");
    close(connfd);   
}

void freeList(Account* head) {
    Account* current = head;
    Account* temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    free(head);
}

Account* find_account(char username[MAX_USERNAME_LENGTH]){
	Account* acc = head;
	while (acc != NULL) {
        if(strcmp(acc->username,username) == 0){
			return acc;
		}
			acc = acc->next;
			
    }
    	printf("Cannot find Account.\n");
    	return NULL;
}

// Load account information from the file into the linked list
void load_accounts() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error: cannot initialize MySQL connection.\n");
        return;
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        printf("Error: cannot connect to MySQL database.\n");
        mysql_close(conn);
        return;
    }

    if (mysql_query(conn, "SELECT username, password, status FROM users")) {
        printf("Error: cannot execute MySQL query.\n");
        mysql_close(conn);
        return;
    }

    res = mysql_use_result(conn);
    if (res == NULL) {
        printf("Error: cannot retrieve MySQL result set.\n");
        mysql_close(conn);
        return;
    }

    while ((row = mysql_fetch_row(res)) != NULL) {
        Account* account = malloc(sizeof(Account));

        strcpy(account->username, row[0]);
        strcpy(account->password, row[1]);
        account->status = atoi(row[2]);
        account->num_signin_wrong=0;
        account->is_logged_in=0;
        account->next = NULL;

        if (head == NULL) {
            head = account;
        } else {
            tail->next = account;
        }
        tail = account;
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int sign_in(char username[MAX_USERNAME_LENGTH], char password[MAX_PASSWORD_LENGTH]){
    int status;
	
	Account* current = find_account(username);
    if(current != NULL) {
    	//check blocked
		if(current->status==0){
			printf("Account is blocked.\n");
            return 0;
		}else if(current->status==1){

			if(strcmp(current->password,password) == 0){
				printf("Hello %s\n",current->username);
				current->num_signin_wrong=0;
				current->is_logged_in=1;
                return 1;
			}else{
				current->num_signin_wrong=current->num_signin_wrong+1;
				printf("Password is incorrect.\n");
                
				if(current->num_signin_wrong>=3){
					printf("Account is Blocked.\n");
					current->status=0;
					update_status();
				}
                return 2;
			}
		}
	}	
}

void update_status() {
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error: cannot initialize MySQL connection.\n");
        return;
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        printf("Error: cannot connect to MySQL database.\n");
        mysql_close(conn);
        return;
    }

    Account* current = head;
    while (current != NULL) {
        char query[1024];
        snprintf(query, sizeof(query), "UPDATE users SET status=%d WHERE username='%s'", current->status, current->username);

        if (mysql_query(conn, query)) {
            printf("Error: cannot execute MySQL query for user %s.\n", current->username);
        }
        
        current = current->next;
    }

    mysql_close(conn);
}
int register_account(char username[MAX_USERNAME_LENGTH], char password[MAX_PASSWORD_LENGTH]){
	Account* account = head;
	while (account != NULL) {
        if(strcmp(account->username,username) == 0){
        	printf("Account existed.\n");
        	return 0;
		}
			account = account->next;
    }
	if(account==NULL){
		printf("\nSuccessful registration.\n");
	 	Account* account = malloc(sizeof(Account));
        strcpy(account->username, username);
        strcpy(account->password, password);
        account->status = 1;
        account->num_signin_wrong=0;
        account->is_logged_in=0;
    	account->next = NULL;
        if (head == NULL) {
                head = account;
            } else {
                tail->next = account;
            }
            tail = account;
	save_account(username,password);
    return 1;
	}
}
void save_account(char username[MAX_USERNAME_LENGTH], char password[MAX_PASSWORD_LENGTH]) {
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error: cannot initialize MySQL connection.\n");
        return;
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        printf("Error: cannot connect to MySQL database.\n");
        mysql_close(conn);
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, status) VALUES ('%s', '%s', 1)",
             username, password);

    if (mysql_query(conn, query)) {
        printf("Error: cannot execute MySQL query for user %s.\n", username);
    }

    mysql_close(conn);
}
