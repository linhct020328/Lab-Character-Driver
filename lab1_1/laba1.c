#include<linux/init.h>
#include<linux/module.h>

int sum(int arr[100], int n);
int ucln(int a, int b);

static int lab1_1_init(void)
{
    int arr[5] = {1,3,5,6,8};
    int n = 5;
    int a = 4;
    int b = 18;

    printk(KERN_ALERT "\n tong cac so: sum = %d", sum(arr, n));
    printk(KERN_ALERT "\n ucln( %d, %d): %d \n", a, b, ucln(a,b));
    return 0;
}

int sum(int arr[100], int n)
{
    int i, s = 0;
    for(i = 0; i< n; i++)
    {
        s += arr[i];
    }
    return s;
}

int ucln(int a, int b)
{
    if(b == 0) return a;
    return ucln(b, a %b);
}

static void lab1_1_exit(void)
{
    printk(KERN_ALERT "ket thuc \n");
}

module_init(lab1_1_init);
module_exit(lab1_1_exit);
