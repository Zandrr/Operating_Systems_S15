### Operating Systems Assignment 1: Adding a system call to the kernel.


#### Alex Campbell
#### Alca5676
#### Student ID: 101182285


##### arch/x86/kernel/simple_add.c
simple_add.c is a C file that has an asmlinkage reference from linux/linkage.h.  It contains a function that takes in 3 parameters: *number1*, *number2*, and *\*result*.  The function will add *number1* and *number2* and store the result in *\*result*.  It will then print the result with the KERN\_ALERT macro.

---

##### arch/x86/kernel/Makefile
In this file we add the line:

 ```bash obj-y += simple_add.o```
 so that when we compile the kernel, it will see the object file simple_add.c and link it.

---

##### arch/x86/syscalls/syscall_64.tbl
The syscall_64.tbl is used to map our new syscall to a number, in our case 319.  This is done so that we can access the syscall from a syscall(<\some number>).

---

##### include/linux/syscalls.h
We add our function definition to link it to the system call.

---

##### /var/log/syslog
The system will log all outputs (including our printk(KERN_ALERT)) to a text file.

---
##### test\_sys_call.c

We will use this function to call the new syscall function.  It is saved at 319, so we can print it using:
```bash syscall(319)```
To run/compile:
  * ```bash gcc test\_sys_call.c``` while in the kernel folder.
  * ```bash ./test\_sys_call.c && dmesg ``` to show the output in the terminal.


---


