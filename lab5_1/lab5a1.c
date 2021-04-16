#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include<linux/time.h>
#include<linux/jiffies.h>


#define DRIVER_AUTHOR "linh"
#define DRIVER_DESC "Dg driver"
#define VERSION "3.0"
#define MEM_SIZE 1024

static struct cdev *lab51_cdev;
unsigned open_cnt = 0;

int8_t *buf_tmp;
int32_t *kernel_buf2;
int32_t *kernel_buf8;
int8_t *kernel_buf16;


static int vchar_driver_open(struct inode *inode, struct file *flip);
static int vchar_driver_release(struct inode *inode, struct file *filp);
static ssize_t vchar_driver_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off);
static ssize_t vchar_driver_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off);

static void DecToBinary(int n);
static void DecToHex(int n);
static void DecToOct(int n);

static int select;
static int binNumber;
static int octNumber;
static int hexNumber;


static struct file_operations fops = 
{
    .owner      = THIS_MODULE,
    .read       = vchar_driver_read,
    .write      = vchar_driver_write,
    .open       = vchar_driver_open,
    .release    = vchar_driver_release,
};

struct vchar_drv{
	dev_t dev_num;				
	struct class *dev_class;	
	struct device *dev;
}vchar_drv;



static int vchar_driver_open(struct inode *inode, struct file *flip)
{
    open_cnt++;
    printk("Handle opened event %u times\n", open_cnt);
	return 0;
}


static int vchar_driver_release(struct inode *inode, struct file *filp)
{
    printk("Handle closed event %u times\n", open_cnt);
    return 0;
}
 

static ssize_t vchar_driver_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	if(select == 3) {
		copy_to_user(user_buf, kernel_buf2, MEM_SIZE);
		printk("Read\n");
		return binNumber;
	}
	if(select == 4) {
		copy_to_user(user_buf, kernel_buf8, MEM_SIZE);
		printk("Read\n");
		return octNumber;
	}
	if(select == 5) {
		copy_to_user(user_buf, kernel_buf16, MEM_SIZE);
		printk("Read\n");
		return hexNumber;
	}
	return MEM_SIZE;
}


static ssize_t vchar_driver_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "len = %ld\n", len);
	if(len == 4) {
		copy_from_user(kernel_buf2, user_buf, len);

		copy_from_user(kernel_buf8, user_buf, len);

		copy_from_user(kernel_buf16, user_buf, len);

		DecToBinary((int)*kernel_buf2);
		DecToOct((int)*kernel_buf8);
		DecToHex((int)*kernel_buf16);
	}
	else {
		copy_from_user(buf_tmp, user_buf, len);
		if(*buf_tmp == '3') {
			select = 3;
		}
		if(*buf_tmp == '4') {
			select = 4;
		}
		if(*buf_tmp == '5') {
			select = 5;
		}
	}
	printk(KERN_INFO "Write\n");
	return len;
}

// 10->2
void DecToBinary(int n)
{
	int arr[100];
	int i = 0;
	int j = 0;
	while(n > 0) {
		arr[i] = n%2;
		n = n/2;
		i++;
	}
	binNumber = 0;
	for(i = i-1; i >= 0; i--)
	{
		kernel_buf2[j] = arr[i];
		j++;
		binNumber++;
	}
}
// 10->16
void DecToHex(int n)
{
	int arr[100];
	int i = 0;
	int j = 0;
	int k = 0;
	while(n>0) {
		arr[i] = n%16;
		n = n/16;
		i++;
	}
	hexNumber = 0;
	for(j=i-1;j>=0;j--) {
		kernel_buf16[k] = arr[j];
		k++;
		hexNumber++;
	}
}

// 10->8
void DecToOct(int n)
{
	int arr[100];
	int i = 0;
	int j = 0;
	while(n>0)
	{
		arr[i] = n%8;
		n = n/8;
		i++;
	}
	octNumber = 0;
	for(i = i-1; i >= 0; i--)
	{
		kernel_buf8[j] = arr[i];
		j++;
		octNumber++;
	}
}

// Khoi tao driver
static int __init char_driver_init(void)
{
	int ret = 0;
	vchar_drv.dev_num = 0;

    
    ret = alloc_chrdev_region(&vchar_drv.dev_num, 0, 1, "Lab 51");
	if(ret < 0) {
		printk("Can't allocate character driver\n");
		goto failed_register_devnum;
	}
    printk("Insert character driver successfully. major(%d), minor(%d)\n", MAJOR(vchar_drv.dev_num), MINOR(vchar_drv.dev_num));

	
    vchar_drv.dev_class = class_create(THIS_MODULE, "Lab05");
	if(IS_ERR(vchar_drv.dev_class)) {
		printk("Can't create class\n");
		goto failed_create_class;
	}

	vchar_drv.dev = device_create(vchar_drv.dev_class, NULL, vchar_drv.dev_num, NULL,"lab51");
	if(IS_ERR(vchar_drv.dev)) {
		printk("Can't create device file\n");
		goto failed_create_device;
	}
    
	
	kernel_buf2 	= kmalloc(MEM_SIZE, GFP_KERNEL);
	kernel_buf8 	= kmalloc(MEM_SIZE, GFP_KERNEL);
	kernel_buf16 	= kmalloc(MEM_SIZE, GFP_KERNEL);
	buf_tmp			= kmalloc(MEM_SIZE, GFP_KERNEL);

    lab51_cdev = cdev_alloc();				
	cdev_init(lab51_cdev, &fops); 			
	cdev_add(lab51_cdev, vchar_drv.dev_num, 1); 	

    return 0;

failed_create_device:
	class_destroy(vchar_drv.dev_class);
failed_create_class:
	unregister_chrdev_region(vchar_drv.dev_num, 1);
failed_register_devnum:
	return ret;
}

static void __exit char_driver_exit(void) 
{
    cdev_del(lab51_cdev);
	kfree(kernel_buf2);
	kfree(kernel_buf8);
	kfree(kernel_buf16);
	kfree(buf_tmp);

	device_destroy(vchar_drv.dev_class, vchar_drv.dev_num);
	class_destroy(vchar_drv.dev_class);
	unregister_chrdev_region(vchar_drv.dev_num, 1);
	printk("Remove character driver successfully.\n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(VERSION);
