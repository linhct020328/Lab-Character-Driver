#include <linux/module.h> /* tat ca cac module deu can thu vien nay */
#include <linux/init.h> /* thu vien nay dinh nghia cac macro nhu module_init va module_exit */
#include<linux/fs.h> /* thu vien nay chua cac ham cap phat/giai phong device number */
#include<linux/device.h> /* thu vien nay chua cac ham phuc vu tao device file */
#include<linux/cdev.h> /* thu vien cho cau truc cdev */
#include<linux/slab.h> /* thu vien chua ham kmalloc */
#include<linux/uaccess.h> /* thu vien chua cac ham trao doi du lieu giua user va kernel */
#include <linux/kernel.h>

#define AUTHOR "Thuy Linh"
#define DESC "LAB4_1"
#define VERSION "01"

static struct cdev *cdev_lab4; 

//nguyen mau cac ham theo format cua con tro ham trong file_operations
static int lab4_open(struct inode *inode, struct file *filp);
static int lab4_release(struct inode *inode, struct file *filp);
static ssize_t lab4_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off);
static ssize_t lab4_write(struct file *filp, const char *user_buf, size_t len, loff_t *off);


struct vchrdev{
	//Một biến kiểu dev_t để lưu giữ device number mà device được cấp phát, /* Chứa device number; */
	dev_t dev_num;
	struct class *dev_class;
	/* cdev là cấu trúc biểu diễn char devices; */
	struct device *dev; 

}vchrdev;

//Gan cac entry point voi cac ham xu ly tuong ung
//<=> gan con tro ham = ten ham 
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
	
	/* cap phat device number */
	vchrdev.dev_num = 0;
	ret = alloc_chrdev_region(&vchrdev.dev_num, 0, 1, "lab4_1");
	if(ret < 0){
		printk("Cap phat khong thanh cong");
		goto failed_register_devnum;
	}
	printk("Cap phat thanh cong device number (%d, %d)", MAJOR(vchrdev.dev_num), MINOR(vchrdev.dev_num));
	
	/* tao device file */
	vchrdev.dev_class = class_create(THIS_MODULE, "class_dev_lab4_1");
	if(IS_ERR(vchrdev.dev_class)){
		printk("Tao lop cac thiet bi that bai");
		goto failed_create_class;
	}
	
	//device_create(class, parent, dev_num, dev_data, dev_name)
	vchrdev.dev = device_create(vchrdev.dev_class, NULL, vchrdev.dev_num, NULL, "device_lab4_1");
	if(IS_ERR(vchrdev.dev)){
		printk("Tao file thiet bi that bai");
		goto failed_create_dev;
	}
	cdev_lab4 = cdev_alloc(); // cap phat bo nho cho cdev
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
	cdev_del(cdev_lab4);	/* huy dang ky entry point voi kernel */
		
	/* xoa bo device file */
	device_destroy(vchrdev.dev_class, vchrdev.dev_num);
	class_destroy(vchrdev.dev_class);
	
	/* giai phong device number */
	unregister_chrdev_region(vchrdev.dev_num, 1);
	
	printk("Bye!!!");
}

module_init(init_chrdev);
module_exit(exit_chrdev);

MODULE_LICENSE("GPL");/* giay phep su dung cua module */
MODULE_AUTHOR(AUTHOR); /* tac gia cua module */
MODULE_DESCRIPTION(DESC);/* mo ta chuc nang cua module */
MODULE_VERSION(VERSION); /* mo ta phien ban cuar module */
