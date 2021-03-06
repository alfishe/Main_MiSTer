#ifndef _FAT16_H_INCLUDED
#define _FAT16_H_INCLUDED

#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	int       fd;
	int       mode;
	int       type;
	__off64_t size;
	__off64_t offset;
	char      name[261];
}  fileTYPE;

extern int nDirEntries;
extern struct dirent DirItem[1000];
extern int iSelectedEntry;
extern int iFirstEntry;

// scanning flags
#define SCAN_INIT        0 // start search from beginning of directory
#define SCAN_NEXT        1 // find next file in directory
#define SCAN_PREV       -1 // find previous file in directory
#define SCAN_NEXT_PAGE   2 // find next 8 files in directory
#define SCAN_PREV_PAGE  -2 // find previous 8 files in directory
#define SCAN_SET_ITEM    3 // find exact item

// options flags
#define SCAN_DIR    1 // include subdirectories
#define SCAN_UMOUNT 2 // include subdirectories
#define SCAN_SDIR   4 // include subdirectories

void FindStorage();
int  getStorage(int from_setting);
void setStorage(int dev);
int  isUSBMounted();

int  FileOpenEx(fileTYPE *file, const char *name, int mode);
int  FileOpen(fileTYPE *file, const char *name);
void FileClose(fileTYPE *file);

int FileSeek(fileTYPE *file, __off64_t offset, int origin);
int FileSeekLBA(fileTYPE *file, uint32_t offset);

//MiST compatible functions. Avoid to use them.
int FileRead(fileTYPE *file, void *pBuffer);
int FileReadEx(fileTYPE *file, void *pBuffer, int nSize);
int FileWrite(fileTYPE *file, void *pBuffer);
int FileNextSector(fileTYPE *file);

//New functions.
int FileReadAdv(fileTYPE *file, void *pBuffer, int length);
int FileReadSec(fileTYPE *file, void *pBuffer);
int FileWriteAdv(fileTYPE *file, void *pBuffer, int length);
int FileWriteSec(fileTYPE *file, void *pBuffer);

int FileCanWrite(char *name);

int FileSave(char *name, void *pBuffer, int size);
int FileLoad(char *name, void *pBuffer, int size); // supply pBuffer = 0 to get the file size without loading

//save/load from config dir
#define CONFIG_DIR "config"
int FileSaveConfig(char *name, void *pBuffer, int size);
int FileLoadConfig(char *name, void *pBuffer, int size); // supply pBuffer = 0 to get the file size without loading

void AdjustDirectory(char *path);
int ScanDirectory(char* path, int mode, char *extension, int options);

char *getRootDir();
char *getFullPath(char *name);

#ifdef __cplusplus
}
#endif

#endif
