/*
   Brooks Kindle
   brooks.kindle@wsu.edu

   commands.c  -   source file for prelab commands
 */

#include "commands.h"
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>

//global env variables
char home[MAX],
     cwd[MAX];


/* parses the command line environments of main */
void parseEnv(char *env[]) {
    char *cur;
    int i = 0;
    for(i = 0, cur = env[i]; env[i]; i++) { //loop through env
        if(strstr(env[i], "HOME=") == env[i]) { //home path found
            sprintf(home, "%s", strstr(env[i], "=") + 1);
        }
        else if(strstr(env[i], "PWD=") == env[i]) { //cwd found
            sprintf(cwd, "%s", strstr(env[i], "=") + 1);
        }
    }//end for
}//end parseEnv


/* sends a string command to a socket */
void execRemote(int sock, char line[MAX]) {
    char ans[MAX] = {0};
    // Send ENTIRE line to server
    int n = write(sock, line, MAX);
    printf("client: wrote n=%d bytes; line=(%s)\n", n, line);


    // the client then should read from socket to get results of the remote command if it returns anything. 
	char *cmd = strtok(line, " ");
	char *filename = strtok(NULL, " ");
	char buf[MAX];
	
, 	if( !strcmp(cmd, "get"){
		get(socket, filename);
	}else if( !strcmp(cmd, "put"){
		put(socket, filename);
	}else{
		//read from buffer until check is met
		char check[MAX] =  "END OF ";
		check = strcat(check, cmd);
		n = 0;
		
		while (true)
		{
			n = read(socket, buf, MAX);
			write(socket, buf, MAX);
			if(strstr(check,  buf))
			{
				printf("reached end\n");
				break;
			}//end if
		}//end while
		
	}//end if else chain
	
	

}//end execRemote


/* makes a directory */
void mymkdir(int fd, char *dname) {
    if(!mkdir(dname, 0775)) { //success
        sprintf(buf, "mkdir okay\nEND OF mkdir");
    }
    else { //failure
        sprintf(buf, "mkdir failed\nEND OF mkdir");
    }
    write(fd, buf, MAX); //write line to file descriptor
}//end mymkdir


/* removes a directory */
void myrmdir(int fd, char *dname) {
    if(!rmdir(dname)) { //success
        sprintf(buf, "rmdir okay\n");
    }
    else { //failure
        sprintf(buf, "rmdir failed\n");
    }
    strcat(buf, "END OF rmdir");
    write(fd, buf, MAX); //write line to file descriptor
}//end myrmdir


/* removes a file */
void rm(int fd, char *fname) {
    if(!unlink(fname)) { //success
        sprintf(buf, "rm okay\n");
    }
    else { //failure
        sprintf(buf, "rm failed\n");
    }
    strcat(buf, "END OF rm");
    write(fd, buf, MAX); //write line to file descriptor
}//end rm


/* prints file contents */
void cat(int fd, char *fname) {
    FILE *f = fopen(fname, "r");
    char ch;
    if(f) { //file opened
        ch = fgetc(f);
        while(!feof(f)) {
            putchar(ch); //write char
            ch = fgetc(f); //get next char
        }//end while
        fclose(f);
    }//end if
}//end cat


/* Prints the directory or file in long format. If an invalid path is inputted
   (NULL or just a path that does not exist), nothing will happen */
void ls(int fd, char *path) {
    int i = 0, n = 0;
    struct stat file;
    path = strtok(NULL, " ");
    if(!path) { //no argument to ls, print cwd
        path = cwd;
    }
    while(path) { //get all arguments for ls
        i = stat(path, &file);
        if(!i) { //success statting path
            if((file.st_mode & 0100000) == 0100000) { //reg file(1000) or lnk(1010)
                lsFile(fd, file, path);
            }
            else if((file.st_mode & 0040000) == 0040000) { //dir(0100)
                lsDir(fd, path);
            }
        }
        else { //unable to stat path
        }
        path = strtok(NULL, " ");
    }//end while
    bzero(buf, MAX);
    sprintf(buf, "END OF ls");
    write(fd, buf, MAX);
}//end ls


/* prints the current working directory to the file descriptor */
void pwd(int fd, char *path) {
    sprintf(buf, "%s\nEND OF pwd", cwd);
    write(fd, buf, MAX);
}//end pwd


/* changes directory to the given directory and writes any output to the given 
   file descriptor */
void cd(int fd, char *path) {
    path = strtok(NULL, " "); //get cd arg
    if(!path) { //no argument to cd, cd to home directory
        path = home;
    }
    if(chdir(path) != -1) { //success changing directory
        getcwd(cwd, MAX);
        sprintf(buf, "cd okay\nEND OF cd");
    }
    else { //unsuccessful changing directories
        sprintf(buf, "cd failed\nEND OF cd");
    }
    write(fd, buf, MAX); //write line to file descriptor
}//end cd


/* gets a file from a remote server */
void get(int socket, char *filename) {
    //TODO: get

    
       char ans[MAX];
       char buf[MAX];
		int n;

       n = read(socket, ans, MAX);
       int size = atoi(ans);

       if( size == -1) 
       {
       		printf("An error has occured\n");
       		return;

       }else
       {
		 int count = 0 ;
		if( filename == NULL)
		{
			printf(" invalid file name");
		}else
		{
			int fid = open(filename, O_WRONLY | O_CREAT| O_TRUNC);
			int count = 0;
			while( count < size) 
			{
				n = read(socket,buf, MAX);
				count += n;
				write(fid, buf, MAX);
			}//end while
			close(fid);

		}//end if else
    }//end if else

    
}//end get


/* uploads a file to the server */
void put(int socket, char *filename) {
    //TODO: put *assuming this is the client side of put
	char buf[MAX];
	int n;
    
    int fid =  open(filename, O_RDONLY);
    if( fid == -1)
    {
    	printf("error opening file");
    	sprintf(buf,"%d", fid);
    	n = write(socket, buf, MAX);
    	
    }else
    {
    	//send size
		struct stat info;
		int x = stat(filename, &info);
		int size = info.st_size;
		sprintf(buf, "%d", size);
		n = write(socket, buf, MAX);
		 
		//then send file 
		while((n=read(fid, buf, MAX)))
		{
			n = write(socket, buf, MAX); 
		}//end while
    }//end if else


     
}//end put



/* quits the program */
void quit(int fd, char *path) {
    exit(0);
}//end quit


/* ls a file in long format (can be directory, lkn, file, or etc...) */
void lsFile(int fd, struct stat file, const char *fname) {
    int i;
    char tmpname[strlen(fname) + 1];
    char *time = 0;
    strcpy(tmpname, fname);

    bzero(buf, MAX); //zero out buf so we don't get previous results
    if((file.st_mode & 0100000) == 0100000) { //reg file
        sprintf(buf, "-");
    }
    else if((file.st_mode & 0040000) == 0040000) { //directory
        sprintf(buf, "d");
    }
    else { //symbolic link
        sprintf(buf, "l");
    }
    for(i = 8; i >= 0; i--) { //print file permissions
        if(file.st_mode & (1 << i)) { //has permission
            switch(i % 3) { //determine read, write, or execute
                case 2: //read
                    strcat(buf, "r");
                    break;
                case 1: //write
                    strcat(buf, "w");
                    break;
                case 0: //execute
                    strcat(buf, "x");
                    break;
            }//end switch
        }
        else { //doesn't have permission
            strcat(buf, "-");
        }
    }//end for
    sprintf(buf+strlen(buf), " %2d ", (int) file.st_nlink); //number of hard links
    sprintf(buf+strlen(buf), "%d %d", file.st_uid, file.st_gid); //uid and gid
    sprintf(buf+strlen(buf), " %ld ", file.st_size); //size on disk
    time = ctime(&file.st_mtime);
    time[strlen(time)-1] = '\0'; //remove newline
    sprintf(buf+strlen(buf), "%s ", time); //time of last modification
    sprintf(buf+strlen(buf), "%s\n", basename(tmpname)); //filename

    write(fd, buf, MAX);
}//end lsFile


/* ls on a directory, which prints all directory contents in long format. If
   the given string is not a directory, nothing will happen */
void lsDir(int fd, const char *dname) {
    char filename[MAX] = {'\0'};
    struct stat fstat;
    DIR *dp = opendir(dname); //open directory
    struct dirent *ep = readdir(dp); //get next file in directory
    while(ep) {
        if(strcmp(ep->d_name, ".") == 0 || //special directory
                strcmp(ep->d_name, "..") == 0) {//don't print
        }
        else { //okay to print the file
            strcpy(filename, dname);
            strcat(filename, "/");
            strcat(filename, ep->d_name);
            stat(filename, &fstat);
            lsFile(fd, fstat, filename);
        }
        ep = readdir(dp); //read next file
    }//end while
}//end lsDir
