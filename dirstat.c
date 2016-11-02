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


long sumsize(char * dir){
  DIR *d;
  d = opendir(dir);
  struct dirent* curr;
  curr = readdir(d);
  long size = 0;
  while(curr){
    if (curr->d_type == DT_DIR && strcmp(curr->d_name,".") != 0 && strcmp(curr->d_name,"..")!=0){
      // printf("\ncurrdir: %s",curr->d_name);
      char subdir[256];
      strcpy(subdir, dir);
      strcat(subdir, curr->d_name);
      strcat(subdir, "/");
      // printf("\ndir: %s\n",subdir);
      size += sumsize(subdir);
    }
    if (curr->d_type == DT_REG){
      struct stat st;
      char fildir[256];
      strcpy(fildir,dir);
      strcat(fildir,curr->d_name);
      stat(fildir, &st);
      size += st.st_size;
    }
    curr = readdir(d);
  }
  return size;
}


void dirstat(char * dir){
  long size = 0;
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
      // printf("size:%d\n", st.st_size);
      strcat(regs, curr->d_name);
      strcat(regs, "\n");
    }
    curr = readdir(d);
  }
  printf("Statistics for directory: %s\n", dir);
  printf("Size of Regular Files:");
  long b = size;
  long kb = b/1024;
  long mb = kb/1024;
  long gb = mb/1024;
  char p = 0;
  if (gb>1 && !p){
    printf("%li GB\n",gb);
    p=1;
  }
  if (mb>1 && !p){
    printf("%li MB\n",mb);
    p=1;
  }
  if (kb>1 && !p){
    printf("%li KB\n",kb);
    p = 1;
  }
  if (p){
    printf("%li B\n", b);
    p = 1;
  }

  printf("Size of Directory(including subdir):");
  size = sumsize(dir);
  b = size;
  kb = b/1024;
  mb = kb/1024;
  gb = mb/1024;
  p = 0;
  if (gb>1 && !p){
    printf("%li GB\n",gb);
    p=1;
  }
  if (mb>1 && !p){
    printf("%li MB\n",mb);
    p=1;
  }
  if (kb>1 && !p){
    printf("%li KB\n",kb);
    p = 1;
  }
  if (p){
    printf("%li B\n", b);
    p = 1;
  }
  printf("%s",dirs);
  printf("%s",regs);
}


int main(){
  dirstat("./");
  return 0;
}
