#include <stdio.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <sys/syscall.h>

int main(){
	int *result;
	long int sys_simple_add = syscall(319,1,2,&result);
	printf("System call sys_simple_add returned %ld\n",sys_simple_add);
	return 0;
}