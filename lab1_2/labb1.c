#include<linux/init.h>
#include<linux/module.h>

int Max(int arr[100],int n);
int Min(int arr[100], int n);
int Tbc(int arr[100], int n);

static int lab1_init(void)
{
    int arr[10] = {1,2,3,5,7,4,11,9,8,10};
    int n = 10;

    printk(KERN_ALERT "max: %d \n", Max(arr, n));
    printk(KERN_ALERT "min: %d\n", Min(arr, n));
    
    printk(KERN_ALERT "tbc: %d\n", Tbc(arr, n));
    
    return 0;
}

int Max(int arr[100],int n)
{
    int i, max = arr[0];
    for (i = 0; i < n; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

int Min(int arr[100], int n)
{
    int i, min = arr[0];
    for (i = 0; i < n; i++)
    {
        if (min > arr[i])
        {
            min = arr[i];
        }
    }
    return min;
}

int Tbc(int arr[100], int n)
{
    int i ,s = 0;
    for (i = 0; i < n; i++)
    {
       s += arr[i];
    }
    return s/n;
}

static void lab1_exit(void)
{
    printk(KERN_ALERT "KET THUC \n");
}

module_init(lab1_init);
module_exit(lab1_exit);
