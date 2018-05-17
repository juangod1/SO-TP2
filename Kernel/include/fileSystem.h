#ifndef SO_TP2_FILESYSTEM_H
#define SO_TP2_FILESYSTEM_H
#endif //SO_TP2_FILESYSTEM_H

typedef struct file * file_CDT;
struct file_CDT
{
    int isFile;
    int isOpen;
    char fileName [20];
};
