#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>

void dirstat(char * dir){
  int size;
  DIR * d;
  d = opendir(dir);
  struct dirent* curr;
  curr = readdir(d);
  char dirs[256] = "Directories:\n";
  char regs[256] = "Regular Files:\n";
  while(curr){
    if (curr->d_type == DT_DIR){
      strcat(dirs, curr->d_name);
      strcat(dirs, "\n");
    }
    if (curr->d_type == DT_REG){
      struct stat st;
      char fildir[256];
      strcpy(fildir,dir);
      strcat(fildir,curr->d_name);
      stat(fildir, &st);
      size += st.st_size;
      strcat(regs, curr->d_name);
      strcat(regs, "\n");
    }
    curr = readdir(d);
  }
  printf("Statistics for directory: %s\n", dir);
  printf("Size of Regular Files: %d\n", size);
  printf("%s",dirs);
  printf("%s",regs);
}


int main(){
  dirstat("../");

  return 0;
}
