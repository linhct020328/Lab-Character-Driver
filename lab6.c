#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define MEM_SIZE 1024
char *kernel_buffer; 
char xauro[1024], xauma1[1024], matt[1024], xauma2[1024], xauma3[1024], mahv[1024];
int k, choice;

struct c_driver {
	dev_t dev_num;
	struct class *dev_class;
	struct device *dev;
	struct cdev *vcdev;
} lab6;

static int my_open(struct inode *inode, struct file *filp);
static int my_release(struct inode *inode, struct file *filp);
static ssize_t my_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off);

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_release,
};

int my_open(struct inode *inode, struct file *filp) {
	pr_info("Mo device file thanh cong!!!");
	return 0;
}

int my_release(struct inode *inode, struct file *filp) {
	pr_info("Dong device file thanh cong!!!");
	return 0;
}

ssize_t my_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off) {
	if(choice == 2) {
		copy_to_user(user_buf, xauma1, 1024);
	}
	if(choice == 3) {
		copy_to_user(user_buf, xauma2, 1024);
	}
	if(choice == 4) {
		copy_to_user(user_buf, xauma3, 1024);
	}
	if(choice == 5) {
		copy_to_user(user_buf, xauma1, 1024);
	}
	if(choice == 6) {
		copy_to_user(user_buf, xauma2, 1024);
	}
	if(choice == 7) {
		copy_to_user(user_buf, xauma3, 1024);
	}
	return MEM_SIZE;
}

ssize_t my_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off) {
	int i, y;
	char x;
	copy_from_user(kernel_buffer, user_buf, len);
	choice = *kernel_buffer;
	if(choice == 1) {
		i = 0;
		kernel_buffer++;
		while(*kernel_buffer != '\0') {
			xauro[i++] = *kernel_buffer;
			kernel_buffer++;
		}
		xauro[i] = '\0';//có cần k nhỉ??
	}
	if(choice == 2) {//ma hoa dich chuyen
		kernel_buffer++;
		k = *kernel_buffer;
		k = k-48;
		i = 0;
		while(xauro[i] != '\0') {
			x = xauro[i];
			x -= 97;
			x += k;
			x = x%26;
			x += 97;
			xauma1[i++] = x;
		}
	}
	if(choice == 3) {//ma hoa thay the
		kernel_buffer++;
		for(i = 0; i < 26; i++) {
			matt[i] = *kernel_buffer;
			kernel_buffer++;
		}
		i = 0;
		while(xauro[i] != '\0'){
			y = xauro[i] - 97;
			y = matt[y];
			xauma2[i++] = y;
		}
	}
	if(choice == 4){//ma hoa hoan vi
		kernel_buffer++;
		for(i = 0; i < 26; i++) {
			mahv[i] = *kernel_buffer;
			kernel_buffer++;
		}
		i = 0;
		while(xauro[i] != '\0') {
			y = xauro[i] - 97;
			y = mahv[y];
			xauma3[i++] = y + 96;
		}
	}
	return len;
}

static int __init lab6_init(void) {
	pr_info("Hello lab 6\n");
	alloc_chrdev_region(&lab6.dev_num, 0, 1, "lab6_PhungThiThuy");
	lab6.dev_class = class_create(THIS_MODULE, "lab6_class");
	lab6.dev = device_create(lab6.dev_class, NULL, lab6.dev_num, NULL, "lab6_device");
	kernel_buffer = kmalloc(MEM_SIZE,GFP_KERNEL);
	lab6.vcdev = cdev_alloc();
	cdev_init(lab6.vcdev, &fops);
	cdev_add(lab6.vcdev, lab6.dev_num, 1);
	return 0;
}

static void __exit lab6_exit(void) {
	cdev_del(lab6.vcdev);
	kfree(kernel_buffer);
	device_destroy(lab6.dev_class, lab6.dev_num);
	class_destroy(lab6.dev_class);
	pr_info("Bye lab 6!!!\n");
}

module_init(lab6_init);
module_exit(lab6_exit);

MODULE_AUTHOR("Phung Thi Thuy");
MODULE_DESCRIPTION("lab6");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
