#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main () {
	int n;
	char buf[1024];
	while((n=read(STDIN_FILENO, buf, 1024)) > 0) {
		if (write(STDOUT_FILENO, buf, n) != n) {
			perror("write error!");	
		}
	}
	
	if (n < 0) {
		perror("write error");
	}
	return 0;
}
