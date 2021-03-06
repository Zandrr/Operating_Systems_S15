

#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<asm/uaccess.h>
#define BUFFER_SIZE 1024

static char device_buffer[BUFFER_SIZE];

int open_counter = 0;
int close_counter = 0;

ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/*  length is the length of the userspace buffer*/
	/*  current position of the opened file*/
	/* copy_to_user function. source is device_buffer (the buffer defined at the start of the code) and destination is the userspace 		buffer *buffer */
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);

	if(length > BUFFER_SIZE - *offset){ length = BUFFER_SIZE-*offset;} // make sure user buffer is less than or equal to BUFFER SIZE

	copy_to_user(buffer,device_buffer,length);
	printk(KERN_ALERT "You have read %zd bytes!\n", length );

	*offset +=length;
	return length;


	
}



ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/*  length is the length of the userspace buffer*/
	/*  current position of the opened file*/
	/* copy_from_user function. destination is device_buffer (the buffer defined at the start of the code) and source is the userspace 		buffer *buffer */
	if(length > BUFFER_SIZE - *offset){ length = BUFFER_SIZE-*offset;}

	copy_from_user(device_buffer,buffer,length);
	printk(KERN_ALERT "You have written %zd bytes!\n", length );
	
	*offset +=length;
	return length;
}


int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	open_counter++;
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	printk(KERN_ALERT "DEVICE HAS BEEN OPENED.  It has been opened %d times", open_counter);
	return 0;
}


int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	close_counter++;
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	printk(KERN_ALERT "DEVICE HAS BEEN CLOSED.  It has been closed %d times", close_counter);

	return 0;
}

struct file_operations simple_char_driver_file_operations = {

	.owner   = THIS_MODULE,
	.open    = simple_char_driver_open,
	.release   = simple_char_driver_close,
	.write   = simple_char_driver_write,
	.read    = simple_char_driver_read

	/* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
};

static int simple_char_driver_init(void)
{
	/* print to the log file that the init function is called.*/
	/* register the device */
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	register_chrdev(511, "simple_character_driver", &simple_char_driver_file_operations);
	return 0;
}

static void simple_char_driver_exit(void)
{
	/* print to the log file that the exit function is called.*/
	/* unregister  the device using the register_chrdev() function. */
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	unregister_chrdev(511, "simple_character_driver");
}


module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);
/* add module_init and module_exit to point to the corresponding init and exit function*/
//make -C /lib/modules/$(uname -r)/build M=$PWD modules
//sudo mknod -m 777 /dev/simple_character_device c 511 0