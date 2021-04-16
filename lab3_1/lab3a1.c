#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

int mulTowVector(int *vect_1, int *vect_2, int n);
int chinhHop(int k, int n);
int gt(int n);
void printkMatr(int *matr, int hang, int cot); 
int *sumMatr(int *matr_1, int *matr_2, int hang, int cot);
int *subMatr(int *matr_1, int *matr_2, int hang, int cot);
int *mulMatr(int *matr_1, int *matr_2, int hang, int cot_1, int cot_2);

static int lab3_1_init(void)
{
	int n1 =2;
	int n2 = 9, k =3;
	int vect_1[2] = {3,4};
	int vect_2[2] = {7,9};
	
	int matr_1[9] = {1,2,3,4,5,6,7,8,9};
	int matr_2[9] = {11,12,13,14,15,16,17,18,19};
	printk(KERN_ALERT "Tich 2 vector la:%d \n", mulTowVector(vect_1, vect_2, n1));
	printk(KERN_ALERT "Chinh hop chap %d cua %d: %d\n",k,n2,chinhHop(k,n2));
	
	printk(KERN_ALERT "\nMa tran 1:");
	printkMatr(matr_1,3,3);
	
	printk(KERN_ALERT "\nMa tran 2:");
	printkMatr(matr_2,3,3);
	
	printk(KERN_ALERT "\ntong 2 ma tran :");
	printkMatr(sumMatr(matr_1, matr_2,3, 3),3,3);
	
	printk(KERN_ALERT "\nhieu 2 ma tran :");
	printkMatr(subMatr(matr_1, matr_2,3, 3),3,3);
	
	printk(KERN_ALERT "\ntich 2 ma tran :");
	printkMatr(mulMatr(matr_1, matr_2,3,3,3),3,3);
	
	return 0;
}

int mulTowVector(int *vect_1, int *vect_2, int n)
{
	int i, mul = 0;
	for(i = 0; i <n; i++)
	{
		mul += *(vect_1 +i)*(*(vect_2+i));//mul = vect_1[i] *vect_2[i]
	}
	return mul;
}

int gt(int n)
{
	int i, s = 1;
	for(i =0; i<n; i++)
	{
		s *=i;
	}
	return s;
}

int chinhHop(int k, int n)//su dung de quy de tinh chinh hop chap k cua n
{
	if(k == 0 || k ==n) return 1;
	if(k ==1) return n;
	return gt(n)/gt(n-k);
}

//in ra matran, tu ham nay de thuc hien pirnt ra cac matran sau khi tinh cong/tru/nhan matran
void printkMatr(int *matr, int hang, int cot)
{
	int i, j;
	for(i = 0; i< hang; i++)
	{
		for(j=0; j< cot; j++)
		{
			printk(KERN_ALERT "%d ",*(matr +(i*cot +j)));
		}
	printk(KERN_ALERT "");
	}
}

int *sumMatr(int *matr_1, int *matr_2, int hang, int cot)
{
	int i, j;
	int *sum ;
	sum = (int *)kmalloc(hang*cot*sizeof(int),GFP_KERNEL);
	for(i = 0; i<hang; i++)
		for(j = 0; j<cot ;j++)
		{
			*(sum +(i*cot +j)) = *(matr_1 +(i*cot +j))+*(matr_2 +(i*cot+j));
		}
	return sum;
}
	
int *subMatr(int *matr_1,int *matr_2, int hang, int cot)
{
	int i, j;
	int *sub;
	sub = (int *)kmalloc(hang*cot*sizeof(int),GFP_KERNEL);
	for(i = 0; i<hang; i++)
		for(j = 0; j<cot ;j++)
		{
			*(sub +(i*cot +j)) = *(matr_1 +(i*cot +j))-*(matr_2 +(i*cot+j));
		}
	return sub;
}

int *mulMatr(int *matr_1, int *matr_2, int hang, int cot_1, int cot_2)
{
	int i,j,k;
	int *mul;
	mul = (int *)kmalloc(hang*cot_2*sizeof(int),GFP_KERNEL);
	for( i = 0; i<hang ;i++)
	{
		for(j = 0; j<cot_2; j++)
		{
			for(k = 0; k < cot_1; k++)
			{
				*(mul+(i*cot_2+j)) += *(matr_1+(i*cot_1+k))*(*(matr_2+(k*cot_2+j)));
			}
		}
	}
	return mul;
}
	

static void lab3_1_exit(void)
{
	printk(KERN_ALERT "ket thuc \n");
}

module_init(lab3_1_init);
module_exit(lab3_1_exit);
