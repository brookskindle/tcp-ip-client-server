/*
   Brooks Kindle
   brooks.kindle@wsu.edu

   remoteCommands.h    -   header file for client side remote commands
 */

#ifndef REMOTECOMMANDS_H
#define REMOTECOMMANDS_H

//Note: like system call functions, these return -1 on failure or 0 on success
int get(char *arg);
int put(char *arg);
int rpwd(char *arg);
int rls(char *arg);
int rcd(char *arg);
int rmkdir(char *arg);
int rrmdir(char *arg);
int rrm(char *arg);

#endif
