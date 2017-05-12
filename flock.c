#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "apue.h"
// #define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
// #define read_lock(fd,offset,whence,len) lock_reg (fd, F_SETLK, F_RDLCK, offset, whence, len)
// #define readw_lock(fd,offset,whence,len) lock_reg (fd, F_SETLKW, F_RDLCK, offset, whence, len)
// #define write_lock(fd,offset,whence,len) lock_reg (fd, F_SETLK, F_WRLCK, offset, whence, len)
// #define writew_lock(fd,offset,whence,len) lock_reg (fd, F_SETLKW, F_WRLCK, offset, whence, len)
// #define un_lock(fd,offset,whence,len) lock_reg (fd, F_SETLK, F_UNLCK, offset, whence, len)

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;        // F_RDLCK, F_WRLCK, F_UNLCK
    lock.l_type = type;         // byte offset, relative to l_whence
    lock.l_start = offset;      // SEEK_SET, SEEK_CUR, SEEK_END
    lock.l_whence = whence;     // bytes (0 means to EOF)
    lock.l_len = len;
    
    return (fcntl(fd, cmd, &lock));
}

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;
    lock.l_type = type;     //  F_RDLCK or F_WRLCK
    lock.l_start = offset;  // byte offset, relative to l_whence
    lock.l_whence = whence; //  SEEK_SET, SEEK_CUR, SEEK_END
    lock.l_len = len;
    
    if (fcntl(fd, F_GETLK, &lock) < 0) {
        perror("fcntl error");
        exit(-1);
    }
    
    if (lock.l_type == F_UNLCK)
        return 0;             
    return (lock.l_pid);
}

static void lockabyte(const char *name, int fd, off_t offset) {
    if (writew_lock(fd, offset, SEEK_SET, 1) < 0) {
        err_sys("%s: writew_lock error", name);
    }
    printf("%s: got the lock, byte %ld\n", name, offset);
}

int main (void) 
{
    int fd;
    pid_t pid;
    
    if ((fd = creat("templock", FILE_MODE)) < 0) {
        perror("create error"); exit(-1);
    }
    if (write(fd, "ab", 2) != 2) {
        perror("write error"); exit(-1);
    }
    TELL_WAIT();
    if ((pid = fork()) < 0) {
        perror("frok error"); exit(-1);
    } else if (pid == 0) {
        lockabyte("child", fd, 0);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lockabyte("child", fd, 1);
    } else {
        lockabyte("parent", fd, 1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockabyte("parent", fd, 0);
    }
    exit(0);
}