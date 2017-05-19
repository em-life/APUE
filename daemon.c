#include "apue.h"
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h> 


#define PIDFILE "daemon.pid"


int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;        // F_RDLCK, F_WRLCK, F_UNLCK
    lock.l_type = type;         // byte offset, relative to l_whence./.a
    lock.l_start = offset;      // SEEK_SET, SEEK_CUR, SEEK_END
    lock.l_whence = whence;     // bytes (0 means to EOF)
    lock.l_len = len;
    
    return (fcntl(fd, cmd, &lock));
}

int main(void)
{
	int fd, val;
	char buf[10];
	if ((fd=open(PIDFILE, O_WRONLY|O_CREAT, FILE_MODE)) < 0)
		err_sys("open error");  
    printf("fd = %d\n", fd);
	if (write_lock(fd, 0, SEEK_SET, 0) < 0)
		if (errno == EACCES || errno == EAGAIN)
			exit(0);	//gracefully exit, daemon is already running
		else
			err_sys("write_lock error");

	if (ftruncate(fd, 0) < 0)
		err_sys("ftruncate error");
	sprintf(buf, "%d\n", getpid());
	if (write(fd, buf, strlen(buf)) != strlen(buf))
		err_sys("write error");
	if ((val = fcntl(fd, F_GETFD, 0)) < 0)
		err_sys("fcntl F_GETFD error");
    printf("before val = %d\n", val);
	val |= FD_CLOEXEC;
    printf("before val = %d\n", val);
	if (fcntl(fd, F_SETFD, val) < 0)
		err_sys("fcntl F_SETFD error");
	exit(0);
}