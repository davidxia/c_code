#define NAME_MAX 14             /* longest filename component */
#include <dirent.h>


/* Using system dirent.h so no need to
 * use structs provided by book.
 */
//typedef struct {                /* portable directory entry */
//    long ino;                   /* inode number */
//    char name[NAME_MAX + 1 ];   /* name + '\0' terminator */
//} Dirent;

//typedef struct {                /* minimal DIR: no buffering, etc. */
//    int fd;                     /* file descriptor for the directory */
//    Dirent d;                   /* the directory entry */
//} DIR;


//DIR *opendir(char *dirname);
//Dirent *readdir(DIR *dfd);
//void closedir(DIR *dfd);


#ifndef DIRSIZ
#define DIRSIZ 14
#endif

struct direct {                 /* directory entry */
    ino_t d_ino;                /* inode number */
    char d_name[DIRSIZ];        /* long name does not have '\0' */
};

