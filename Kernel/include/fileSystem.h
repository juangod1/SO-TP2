#ifndef SO_TP2_FILESYSTEM_H
#define SO_TP2_FILESYSTEM_H

#define MAX_FILENAME 20

typedef struct file_CDT * file;
struct file_CDT
{
    int isFile;
    int isOpen;
    char fileName [MAX_FILENAME];
};

void initializeFS();
void f_open(char* path, int mode);
void f_close();
void f_read(file f);
void f_seek(file f);
void f_mkdir(char* name);
void f_chdir(char* name);
void f_create(file fd, char * path, int mode);

#endif SO_TP2_FILESYSTEM_H