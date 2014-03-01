/*
   Brooks Kindle
   brooks.kindle@wsu.edu

   localCommands.h    -   header file for client side local commands
 */

#ifndef LOCALCOMMANDS_H
#define LOCALCOMMANDS_H

//Note: like system call functions, these return -1 on failure or 0 on success
int lcat(char *arg);
int lpwd(char *arg);
int lls(char *arg);
int lcd(char *arg);
int lmkdir(char *arg);
int lrmdir(char *arg);
int lrm(char *arg);
int quit(char *arg);

#endif
