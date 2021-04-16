#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/device.h> 
#include <linux/slab.h> 
#include <linux/cdev.h>
#include <linux/uaccess.h> 
#include <linux/kernel.h> 

#define AUTHOR "linh"
#define DESC "LAB4_2"
#define VERSION "01"

static struct cdev *cdev_lab4; 

static int lab4_open(struct inode *inode, struct file *filp);
static int lab4_release(struct inode *inode, struct file *filp);
static ssize_t lab4_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off);
static ssize_t lab4_write(struct file *filp, const char *user_buf, size_t len, loff_t *off);

struct vchrdev{
	dev_t dev_num;
	struct class *dev_class;
	struct device *dev; 

}vchrdev;

static struct file_operations fops = {
	.owner 	= THIS_MODULE,
	.open 		= lab4_open,
	.release 	= lab4_release,
	.read 		= lab4_read,
	.write 	= lab4_write,
	 
};

static int lab4_open(struct inode *inode, struct file *filp)
{
  	printk( "Driver: open()\n");
  	return 0;
}

static int lab4_release(struct inode *inode, struct file *filp)
{
  	printk( "Driver: close()\n");
  	return 0;
}

static ssize_t lab4_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	printk( "Driver: read()\n");
  	return len;
}

static ssize_t lab4_write(struct file *f, const char *user_buf, size_t len, loff_t *off)
{	
	
  	printk( "Driver: write()\n");
  	return len;
}

static int __init init_chrdev(void){
	int ret = 0;
	vchrdev.dev_num = MKDEV(242, 0);
	ret = register_chrdev_region(vchrdev.dev_num, 1, "lab4_2");
	if(ret < 0){
		printk("Cap phat khong thanh cong");
		goto failed_register_devnum;
	}
	printk("Cap phat thanh cong device number (%d, %d)", MAJOR(vchrdev.dev_num), MINOR(vchrdev.dev_num));
	
	vchrdev.dev_class = class_create(THIS_MODULE, "class_dev_lab4_2");
	if(IS_ERR(vchrdev.dev_class)){
		printk("Tao lop cac thiet bi that bai");
		goto failed_create_class;
	}
	
	vchrdev.dev = device_create(vchrdev.dev_class, NULL, vchrdev.dev_num, NULL, "device_lab4_2");
	if(IS_ERR(vchrdev.dev)){
		printk("Tao file thiet bi that bai");
		goto failed_create_dev;
	}
	cdev_lab4 = cdev_alloc(); 
	cdev_init(cdev_lab4, &fops);
	cdev_add(cdev_lab4, vchrdev.dev_num, 1);
	
	printk("Khoi tao thiet bi thanh cong");
	printk("Hello!!!");
	return 0;
	
failed_create_dev:
	class_destroy(vchrdev.dev_class);
failed_create_class:
	unregister_chrdev_region(vchrdev.dev_num, 1);
failed_register_devnum:
	return ret;
}


static void __exit exit_chrdev(void){
	cdev_del(cdev_lab4);
	device_destroy(vchrdev.dev_class, vchrdev.dev_num);
	class_destroy(vchrdev.dev_class);
	unregister_chrdev_region(vchrdev.dev_num, 1);
	
	printk("Bye!!!");
}

module_init(init_chrdev);
module_exit(exit_chrdev);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_VERSION(VERSION);

