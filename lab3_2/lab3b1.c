#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/ctype.h>

static void ChuyenVi(char *XauRo,char *XauMa,int k){//En(x) = (x+n) mod 26
	int i,j,ii=0,length,code[100][100],column;
	length = strlen(XauRo); //Sử dụng thư viện <linux/string.h>
	for(i=0;i<length;){
		for(j=0;j<k;j++) {
			code[ii][j]=0;
			i++;
		}
		ii++;
	}

	ii=0;

	for(i=0;i<length;){
		if(XauRo[i]!= ' ') {
			for(j=0;j<k;) {
				if(i<=length) {
						code[ii][j]=(int)XauRo[i];
						i++;
						j++;
				} else {
					break;
				}
			}
			ii++;
		} else {
			i++;
		}
	}
	column = ii;
	ii=0;
	for(i=0;i<k;i++){
		for(j=0;j< column; j++) {
			if(code[j][i]!=0){
				XauMa[ii]=(char)code[j][i];
				ii++;			
			}
		}
	}
	XauMa[ii]='\0';
}

static void ThayThe(char *XauRo,char *XauMa,char *k){
	k = k%26;
    	int i,j=0,temp;
    	for (i=0;XauRo[i]!=NULL;i++)
	  	XauRo[i]=tolower(XauRo[i]);
	for (i=0;XauRo[i]!=NULL;i++) {
		if(XauRo[i]==' ')
		    XauMa[j++]=XauRo[i]; else {
			if(XauRo[i]>=48 && XauRo[i]<=57) {
				temp=XauRo[i]+k;
				if(temp>57)
				         XauMa[j++]=48+(temp-58); else
				         XauMa[j++]=temp;
			} else {
				if(XauRo[i]>=97 && XauRo[i]<=123) {
					temp=XauRo[i]+k;
					if(temp>122)
					             XauMa[j++]=97+(temp-123); else
					             XauMa[j++]=temp;
				} else
				              XauMa[j++]=XauRo[i];
			}
		}
	}
	XauMa[j]='\0';
}

//mã hóa hoán vị toàn cục
static int findMin(char *temp) {
	int i,j,min,index;
	min=temp[0];
	index=0;
	for (j=0;temp[j]!=NULL;j++) {
		if(temp[j]<min) {
			min=temp[j];
			index=j;
		}
	}
	temp[index]=123;
	return index;
}

static int cipher(int i,int r,int l,char arr[22][22], char *XauMa) {
	int j;
	for (j=0;j<r;j++) { {
			XauMa[l++]=arr[j][i];
		}
	}
	return l;
	//XauMa[k]='\0';
}

static void HoanViToanCuc(char *XauRo, char *XauMa, char *k){
	char arr[22][22];
	char temp[55];
	int index;
	strcpy(temp,k);
	int l=0,flag=0,klen,i,j,row,column;
	klen = strlen(k);
	for (i=0; ;i++) {
		if(flag==1) 
		    break;
		for (j=0;k[j]!=NULL;j++) {
			if(XauRo[l]==NULL) {
				flag=1;
				arr[i][j]='-';
			} else {
				arr[i][j]=XauRo[l++];
			}
		}
	}
	row = i;
	column = j;
	
	l=0;
	for (i=0;i<klen;i++) {
		index=findMin(temp);
		l = cipher(index,row,l,arr,XauMa);
	}
	XauMa[l]='\0';
}

//kmalloc: phan bo bo nho cho cac doi tuong nho hon kich thuoc page trong kernel
//GFP_KERNEL: phan bo RAM binh thuong

static int __init init_lab(void){
	char XauRo[15] = "Thuy Linh";

	char *XauMaChuyenVi = (char *)kmalloc(15*sizeof(char),GFP_KERNEL);
	int k1 = 1;
	
	char *XauMaThayThe = (char *)kmalloc(15*sizeof(char),GFP_KERNEL);
	char *k2 = "phqgiumeaylnofdxjkrcvstzwb";
	
	char *XauMaHoanViToanCuc = (char *)kmalloc(15*sizeof(char),GFP_KERNEL);
	char *k3 = "CT2C";
	
    	printk("\nXau Ro : %s",XauRo);
	printk(KERN_ALERT "\nThuc hien ma hoa chuyen vi:");
	ChuyenVi(XauRo,XauMaChuyenVi,k1);	
	printk("Xau Ma chuyen vi: %s\n",XauMaChuyenVi);

	printk(KERN_ALERT "\nThuc hien ma hoa thay the");
	ThayThe(XauRo,XauMaThayThe,k2);
	printk("Xau Ma thay the: %s\n",XauMaThayThe);
	
	printk(KERN_ALERT "\nThuc hien ma hoa hoan vi toan cuc");
	ThayThe(XauRo,XauMaHoanViToanCuc,k3);
	printk("Xau Ma hoan vi toan cuc: %s\n",XauMaHoanViToanCuc);
	return 0;
}

static void __exit exit_lab(void){
	printk("Exit module");
	printk("\n");
}

module_init(init_lab);
module_exit(exit_lab);
