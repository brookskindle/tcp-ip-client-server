/*
   Brooks Kindle
   brooks.kindle@wsu.edu

   commands.c  -   source file for prelab commands
 */

#include "commands.h"
#include <stdlib.h>
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


}//end execRemote


/* makes a directory */
void mymkdir(int fd, char *dname) {
    mkdir(dname, 0775);
}//end mymkdir


/* removes a directory */
void myrmdir(int fd, char *dname) {
    rmdir(dname);
}//end myrmdir


/* removes a file */
void rm(int fd, char *fname) {
    unlink(fname);
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
}//end ls


/* prints the current working directory to the file descriptor */
void pwd(int fd, char *path) {
    sprintf(buf, "%s\n", cwd);
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
    }
}//end cd


/* gets a file from a remote server */
void get(int fd, char *path) {
    //TODO: get

    /*
       I assume this is the client version of 'get' while, for it is difficult not to keep both version seperate
     */
    /*
       char ans[MAX];
       char buf[MAX];
       n = write(sock, path, MAX);
       printf("client: wrote n=%d bytes; line=(%s)\n", n, line);


       n = read(socket, ans, MAX);
       printf("client: read  n=%d bytes; echo=(%s)\n",n, ans);

       if( ans == -1) 
       {
       printf("Server has returned an error\n");
       return;

       }else
       {
    //command is good
    // this means 'ans' should contain the size of the file to be read in

    count = 0 ;
    char* filename = strtok(path, " ");
    if( filename == NULL)
    {
    printf(" invalid file name");
    }else
    {
    int fid = open(filename, O_WRONLY | O_CREAT);
    int count = 0;
    while( count < ans) 
    {

    //Socket may need to be globalized
    n = read(socket,buf, MAX);
    count += n;
    write(fid, n, MAX);
    }//end while
    close(fid);

    }//end if else
    }//end if else

     */
}//end get


/* uploads a file to the server */
void put(int fd, char *path) {
    //TODO: put *assuming this is the client side of put

    /*
       n = write(socket, path, MAX);
       printf("client: wrote n=%d bytes; line=(%s)\n", n, line);

    //do not need to check if command is good, just write info  to socket??

    char* filename =  strtok(path, " "); 
    if(filename == NULL)
    printf("invalid file name");
    else
    {
    fid =  open(filename, O_RONLY);
    if( fid == -1)
    {
    printf("error opening file");
    }else
    {

    char buf[MAX];
    while(n=read(fd, buf, MAX))
    {
    n = write(socket, buf, MAX); 
    }//end while
    }//end if else
    }//end if else


     */
}//end put


void putS(int fd, char *path) {
    /*
       char *filename = strtok(path," ");
       int n = 0;

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
       n = write(socket, "file does not exist", MAX); 
    //return or break??
    }else
    {
    // this might cause an error since info.st_size is not a char *????
    n = write(socket, info.st_size, MAX);


    // start to write the file to the buffer
    int fid = open(filename, O_RDONLY);
    if(fid != -1)
    {
    // I wonder if 'n' should be changed to a local variable for this segement
    char buf[MAX];
    while(n=read(fd, buf, MAX))
    {
    n = write(newsock, buf, MAX); 
    }//end while

    close(fid);
    }else
    printf("error opening file");
    }//end if else

    }//end if else
     */
}//end putS


void getS(int fd, char *path){

}//end getS


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
