/*
   Brooks Kindle
   brooks.kindle@wsu.edu

   commands.h  -   header file for prelab commands
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include <sys/stat.h> //for stat, mkdir
#include <string.h>
#include <dirent.h> //opendir, readdir
#include <libgen.h> //for basename
#include <unistd.h> //for rmdir, unlink
#include <time.h> //for ctime
#include <stdio.h> //for fopen

#define MAX 256 //max line length


/* Command table for easy user command lookup. For example, if the user inputs
   mkdir folderName
   then when the input gets split up into the command and argument, command
   will be
   mkdir
   and in order to determine what function to call, you simply loop through
   inputTable until you find an index that matches mkdir, then you call
   the corresponding function in functTable at that same index */
typedef void (*funct)(int, char *);

char buf[MAX];

//function prototypes
void parseEnv(char *env[]);
void execRemote(int sock, char line[MAX]);

void mymkdir(int fd, char *dname);
void myrmdir(int fd, char *dname);
void rm(int fd, char *fname);
void cat(int fd, char *fname);
void ls(int fd, char *path);
void pwd(int fd, char *path);
void cd(int fd, char *path);
void get(int fd, char *path);
void put(int fd, char *path);
void quit(int fd, char *path);


void putC(int size, char *filename);
void getC(int size, char *filename);


void putS(int size, char *filename);
void getS(int size, char *filename);


//helpers
void lsFile(int fd, struct stat file, const char *fname);
void lsDir(int fd, const char *dname);

#endif
