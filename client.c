//**************************** ECHO CLIENT CODE **************************
// The echo client client.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "commands.h"

// Define variables
struct hostent *hp;              
struct sockaddr_in  server_addr; 

int sock, r;
int SERVER_IP, SERVER_PORT; 

/* Command table for easy user command lookup. For example, if the user inputs
   mkdir folderName
   then when the input gets split up into the command and argument, command
   will be
   mkdir
   and in order to determine what function to call, you simply loop through
   inputTable until you find an index that matches mkdir, then you call
   the corresponding function in functTable at that same index */
typedef void (*funct)(int, char *);

funct localTable[] = {cat, pwd, ls, cd, mymkdir, myrmdir, rm, quit};
const char *const localInputs[] = {"lcat", "lpwd", "lls", "lcd", "lmkdir", "lrmdir",
    "lrm", "quit"};
const char *const remoteInputs[] = {"pwd", "cd", "mkdir", "rmdir", "rm", "get",
    "put", "ls"};

// clinet initialization code

int client_init(char *argv[])
{
    printf("======= clinet init ==========\n");

    printf("1 : get server info\n");
    hp = gethostbyname(argv[1]);
    if (hp==0){
        printf("unknown host %s\n", argv[1]);
        exit(1);
    }

    SERVER_IP   = *(long *)hp->h_addr_list[0];
    SERVER_PORT = atoi(argv[2]);

    printf("2 : create a TCP socket\n");
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock<0){
        printf("socket call failed\n");
        exit(2);
    }

    printf("3 : fill server_addr with server's IP and PORT#\n");
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = SERVER_IP;
    server_addr.sin_port = htons(SERVER_PORT);

    // Connect to server
    printf("4 : connecting to server ....\n");
    r = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (r < 0){
        printf("connect failed\n");
        exit(1);
    }

    printf("5 : connected OK to \007\n"); 
    printf("---------------------------------------------------------\n");
    printf("hostname=%s  IP=%s  PORT=%d\n", 
            hp->h_name, inet_ntoa(*(struct in_addr *)&SERVER_IP), SERVER_PORT);
    printf("---------------------------------------------------------\n");

    printf("========= init done ==========\n");
    return 0;
}


//main -- program start point
int main(int argc, char *argv[ ])
{
    int n, i, found = 0;
    char line[MAX], ans[MAX];
    char *someTok = NULL;

    if (argc < 3){
        printf("Usage : client ServerName SeverPort\n");
        exit(1);
    }

    client_init(argv);

    printf("********  processing loop  *********\n");
    while (1){
        printf("input a line : ");
        bzero(line, MAX);                // zero out line[ ]
        fgets(line, MAX, stdin);         // get a line (end with \n) from stdin

        line[strlen(line)-1] = 0;        // kill \n at end
        if (line[0]==0)                  // exit if NULL line
            exit(0);

        someTok = strtok(line, " "); //split line and get user command
        /*
           Check to see if the inputted command is a local or remote command
         */
        found = 0;

        //check for local command
        for(i = 0; i < sizeof(localTable) / sizeof(funct); i++) {
            if(!strcmp(someTok, localInputs[i])) { //local command
                printf("Running local command %s\n", someTok);
                //call local command with stdout as the destination file descriptor
                localTable[i](1, line + strlen(someTok) + 1); 
                found = 1; //command found
                break;
            }
        }//end for

        //check for remote command
        if(!found) { 
            for(i = 0; i < 8; i++) {
                if(!strcmp(someTok, remoteInputs[i])) { //remote command
                    line[strlen(someTok)] = ' ';
                    printf("Running remote command %s\n", someTok);
                    execRemote(sock, line);
                    found = 1; //command found
                    break;
                }
            }//end for
        }//end if

        //command neither local nor remote
        if(!found) { 
            printf("%s is not a command!\n", someTok);
        }
    }
    return 0;
}//end main

/*
   example of GET on client side

   if( strcmp(someTok, get))
   {
   n = write(sock, line, MAX);
   printf("client: wrote n=%d bytes; line=(%s)\n", n, line);

   n = read(sock, ans, MAX);
   printf("client: read  n=%d bytes; echo=(%s)\n",n, ans);

// look into ans for reply of server
if( ans == -1) 
{
//do nothing, maybe break

}else
{
//command is good
// this means 'ans' should contain the size of the file to be read in

count = 0 ;
char* filename = strtok(NULL, " ");
if( filename == NULL)
{
printf(" invalid file name");
}else
{
int fid = open(filename, O_WRONLY | O_CREAT);
while( count < ans) 
{
n = read(socket,buf, MAX);
count += n;
write(fid, n, MAX);
}
close(fid);
}
}

}   

 */


/*
   example of 'put' 
 */

