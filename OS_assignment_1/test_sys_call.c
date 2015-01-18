#include <stdio.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <sys/syscall.h>

int main(){
	long int syscall_helloworld = syscall(318);
	printf("System call sys_hellworld returned %ld\n", syscall_helloworld);
	return 0;

}