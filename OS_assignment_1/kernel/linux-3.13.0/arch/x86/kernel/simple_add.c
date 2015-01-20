#include <linux/kernel.h>
#include <linux/linkage.h>
asmlinkage long sys_simple_add(int number1, int number2, int *result){
	printk(KERN_ALERT "numbers to be added are %d and %d\n", number1,number2);
	*result = number1 + number2;
	printk(KERN_ALERT "result is %d\n",*result);
	return 0;
}
