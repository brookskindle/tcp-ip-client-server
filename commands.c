/*
   Brooks Kindle
   brooks.kindle@wsu.edu

   commands.c  -   source file for prelab commands
 */


/*
	Looking over the list and possible implementations of this commands, the server and clients may need there own versions of the commands.
	
*/


#include "commands.h"
#include <stdlib.h>


/* sends a string command to a socket */
void execRemote(int sock, char line[MAX]) {
    char ans[MAX] = {0};
    // Send ENTIRE line to server
    int n = write(sock, line, MAX);
    printf("client: wrote n=%d bytes; line=(%s)\n", n, line);
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


/* Prints the directory or file in long format. If an invalid path is inputted,
   NULL or just a path that does not exist), nothing will happen */
void ls(int fd, char *path) {
    int i = 0;
    struct stat file;
    if(path) { //ls the (non-null) path
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
    }//end else
}//end ls


/* prints the current working directory to the file descriptor */
void pwd(int fd, char *path) {
    //TODO: Finish this function
}//end pwd


/* changes directory to the given directory and writes any output to the given 
file descriptor */
void cd(int fd, char *path) {
    //TODO: cd
}//end cd


/* gets a file from a remote server */
void get(int fd, char *path) {
    //TODO: get
}//end get


/* uploads a file to the server */
void put(int fd, char *path) {
    //TODO: put
}//end put


/* quits the program */
void quit(int fd, char *path) {
    exit(0);
}//end quit


/* ls a file in long format (can be directory, lkn, file, or etc...) */
void lsFile(int fd, struct stat file, const char *fname) {
    int i;
    char tmpname[strlen(fname) + 1];
    strcpy(tmpname, fname);
    if((file.st_mode & 0100000) == 0100000) { //reg file
        printf("-");
    }
    else if((file.st_mode & 0040000) == 0040000) { //directory
        printf("d");
    }
    else { //symbolic link
        printf("l");
    }
    for(i = 8; i >= 0; i--) { //print file permissions
        if(file.st_mode & (1 << i)) { //has permission
            switch(i % 3) { //determine read, write, or execute
                case 2: //read
                    printf("r");
                    break;
                case 1: //write
                    printf("w");
                    break;
                case 0: //execute
                    printf("x");
                    break;
            }//end switch
        }
        else { //doesn't have permission
            printf("-");
        }
    }//end for
    printf(" %2d ", (int) file.st_nlink); //number of hard links
    printf("%d %d", file.st_uid, file.st_gid); //uid and gid
    printf(" %ld ", file.st_size); //size on disk
    printf("%s", ctime(&file.st_mtime)); //time of last modification
    printf("%s\n", basename(tmpname)); //filename
}//end lsFile


/* ls on a directory, which prints all directory contents in long format. If
   the given string is not a directory, nothing will happen */
void lsDir(int fd, const char *dname) {
    char filename[256] = {'\0'};
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






