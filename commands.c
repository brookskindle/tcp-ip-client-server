/*
   Brooks Kindle
   brooks.kindle@wsu.edu

   commands.c  -   source file for prelab commands
 */

#include "commands.h"

/* makes a directory */
void mymkdir(const char *dname) {
    mkdir(dname, 0775);
}//end mymkdir


/* removes a directory */
void myrmdir(const char *dname) {
    rmdir(dname);
}//end myrmdir


/* removes a file */
void rm(const char *fname) {
    unlink(fname);
}//end rm


/* prints file contents */
void cat(const char *fname) {
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
void ls(const char *path) {
    int i = 0;
    struct stat file;
    if(path) { //ls the (non-null) path
        i = stat(path, &file);
        if(!i) { //success statting path
            if((file.st_mode & 0100000) == 0100000) { //reg file(1000) or lnk(1010)
                lsFile(file, path);
            }
            else if((file.st_mode & 0040000) == 0040000) { //dir(0100)
                lsDir(path);
            }
        }
        else { //unable to stat path
        }
    }//end else
}//end ls


/* ls a file in long format (can be directory, lkn, file, or etc...) */
void lsFile(struct stat file, const char *fname) {
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
    printf(" %2d ", file.st_nlink); //number of hard links
    printf("%d %d", file.st_uid, file.st_gid); //uid and gid
    printf(" %ld ", file.st_size); //size on disk
    printf("%s", ctime(&file.st_mtime)); //time of last modification
    printf("%s\n", basename(tmpname)); //filename
}//end lsFile


/* ls on a directory, which prints all directory contents in long format. If
   the given string is not a directory, nothing will happen */
void lsDir(const char *dname) {
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
            lsFile(fstat, filename);
        }
        ep = readdir(dp); //read next file
    }//end while
}//end lsDir
