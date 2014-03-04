// This is the echo SERVER server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netdb.h>

#define  MAX 256

// Define variables:
struct sockaddr_in  server_addr, client_addr, name_addr;
struct hostent *hp;

int  sock, newsock;                  // socket descriptors
int  serverPort;                     // server port number
int  r, length, n;                   // help variables

// Server initialization code:

int server_init(char *name)
{
   printf("==================== server init ======================\n");   
   // get DOT name and IP address of this host

   printf("1 : get and show server host info\n");
   hp = gethostbyname(name);
   if (hp == 0){
      printf("unknown host\n");
      exit(1);
   }
   printf("    hostname=%s  IP=%s\n",
               hp->h_name,  inet_ntoa(*(long *)hp->h_addr));
  
   //  create a TCP socket by socket() syscall
   printf("2 : create a socket\n");
   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock < 0){
      printf("socket call failed\n");
      exit(2);
   }

   printf("3 : fill server_addr with host IP and PORT# info\n");
   // initialize the server_addr structure
   server_addr.sin_family = AF_INET;                  // for TCP/IP
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // THIS HOST IP address  
   server_addr.sin_port = 0;   // let kernel assign port

   printf("4 : bind socket to host info\n");
   // bind syscall: bind the socket to server_addr info
   r = bind(sock,(struct sockaddr *)&server_addr, sizeof(server_addr));
   if (r < 0){
       printf("bind failed\n");
       exit(3);
   }

   printf("5 : find out Kernel assigned PORT# and show it\n");
   // find out socket port number (assigned by kernel)
   length = sizeof(name_addr);
   r = getsockname(sock, (struct sockaddr *)&name_addr, &length);
   if (r < 0){
      printf("get socketname error\n");
      exit(4);
   }

   // show port number
   serverPort = ntohs(name_addr.sin_port);   // convert to host ushort
   printf("    Port=%d\n", serverPort);

   // listen at port with a max. queue of 5 (waiting clients) 
   printf("5 : server is listening ....\n");
   listen(sock, 5);
   printf("===================== init done =======================\n");
}


main(int argc, char *argv[])
{
   char *hostname;
   char line[MAX];

   if (argc < 2)
      hostname = "localhost";
   else
      hostname = argv[1];
 
   server_init(hostname); 

   // Try to accept a client request
   while(1){
     printf("server: accepting new connection ....\n"); 

     // Try to accept a client connection as descriptor newsock
     length = sizeof(client_addr);
     newsock = accept(sock, (struct sockaddr *)&client_addr, &length);
     if (newsock < 0){
        printf("server: accept error\n");
        exit(1);
     }
     printf("server: accepted a client connection from\n");
     printf("-----------------------------------------------\n");
     printf("        IP=%s  port=%d\n", inet_ntoa(client_addr.sin_addr.s_addr),
                                        ntohs(client_addr.sin_port));
     printf("-----------------------------------------------\n");

     // Processing loop
     while(1){
     
     
     //This is where the server begins to read in the message from Client
       n = read(newsock, line, MAX);
       if (n==0){
           printf("server: client died, server loops\n");
           close(newsock);
           break;
      }
      
      // show the line string
      printf("server: read  n=%d bytes; line=[%s]\n", n, line);
  
/*    
	  //Lines 122 - 125 should be replaced with the actual execution of command segment, then writing to the appropriate socket. 
      strcat(line, " ECHO");
      // send the echo line to client 
      n = write(newsock, line, MAX);
*/

	char * cmd  = strok(line, " ");
	
	if(cmd == NULL)
		printf("invalid command");

      printf("server: wrote n=%d bytes; ECHO=[%s]\n", n, line);
      printf("server: ready for next request\n");
    }
 }
}


/*
	example of server side 'get'
	
	//cmd should contain 'get' if here
	
	char *filename = strtok(NULL," ");
	
	if (filename == NULL)
	{
		printf("invalid file name");
	}else
	{
		struct stat info;
		int c = stat(filename, &info);
		if(c == -1)
		{
			printf("file does not exist");
			n = write(newsock, "file does not exist", MAX); 
			//return or break??
		}else
		{
			// this might cause an error since info.st_size is not a char *????
			n = write(newsock, info.st_size, MAX);
			
			
			// start to write the file to the buffer
			int fid = open(filename, O_RONLY);
			if(fid != -1)
			{
				// I wonder if 'n' should be changed to a local variable for this segement
				char buf[MAX];
				while(n=read(fd, buf, MAX))
				{
					n = write(newsock, buf, MAX); 
				}
				
				close(fid);
			}else
				printf("error opening file");
		}
		
	}
	
			


*/


/*
	example of 'put' server side
	//cmd be put 
	
	char *filename = strtok(NULL," ");
	
	if (filename == NULL)
	{
		printf("invalid file name");
	}else
	{
		
		char * cSIZE = (strtok(NULL, " ");
		
		if(cSize == NULL)
			printf("invalid size");
		else
		{
			int size =  atoi(cSize);
			int fid = open(filename, O_WRONLY | O_CREAT, 0644);
			
			int count = 0;
	 		while( count < size) 
	 		{
	 			n = read(socket,buf, MAX);
	 			count += n;
	 			write(fid, n, MAX);
	 		}
	 		close(fid);
		}
		
	}
*/

			
