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

//function prototypes
void mymkdir(const char *dname);
void myrmdir(const char *dname);
void rm(const char *fname);
void cat(const char *fname);
void ls(const char *path);
void lsFile(struct stat file, const char *fname);
void lsDir(const char *dname);

#endif
