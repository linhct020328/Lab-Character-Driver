#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/ctype.h>

int i,n;
static void ChuyenVi(char *XauRo,char *XauMa,int k){//En(x) = (x+n) mod 26
	i=0;
	n = strlen(XauRo);
	for(i = 0; i < n; i++)
	{
		if(isalpha(XauRo[i]))
		{
			if(isupper(XauRo[i]))// la chu hoa
			{
				XauMa[i] = ((((XauRo[i] - 65) + k) % 26) + 65);
			}
			else if (islower(XauRo[i]))//la chu thuong
			{
				XauMa[i] = ((((XauRo[i] - 97) + k) % 26) + 97);
			}
		}
		else 
		{
			XauMa[i] = XauRo[i];
		}
	}
}

static void ThayThe(char *XauRo,char *XauMa,char *k){
	i=0;
	n = strlen(XauRo);
	for(i = 0; i < n; i++)
	{
		if(isalpha(XauRo[i]))
		{
			if(isupper(XauRo[i]))// la chu hoa
			{
				XauMa[i] = *(k + (XauRo[i] - 65));
			}
			else if (islower(XauRo[i]))//la chu thuong
			{
				XauMa[i] = *(k + (XauRo[i] - 97));
			}
		}
		else 
		{
			XauMa[i] = XauRo[i];
		}
	}
}



//kmalloc: phan bo bo nho cho cac doi tuong nho hon kich thuoc page trong kernel
//GFP_KERNEL: phan bo RAM binh thuong

static int __init init_lab(void){
	char XauRo[15] = "Thuy Linh";

	char *XauMaChuyenVi = (char *)kmalloc(15*sizeof(char),GFP_KERNEL);
	int k1 = 1;
	
	char *XauMaThayThe = (char *)kmalloc(15*sizeof(char),GFP_KERNEL);
	char *k2 = "phqgiumeaylnofdxjkrcvstzwb";
	
    	printk("\nXau Ro : %s",XauRo);
	printk(KERN_ALERT "\nThuc hien ma hoa chuyen vi:");
	ChuyenVi(XauRo,XauMaChuyenVi,k1);	
	printk("Xau Ma chuyen vi: %s\n",XauMaChuyenVi);

	printk(KERN_ALERT "\nThuc hien ma hoa thay the");
	ThayThe(XauRo,XauMaThayThe,k2);
	printk("Xau Ma thay the: %s\n",XauMaThayThe);
	return 0;
}

static void __exit exit_lab(void){
	printk("Exit module");
	printk("\n");
}

module_init(init_lab);
module_exit(exit_lab);
