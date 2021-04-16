#include<linux/init.h>
#include<linux/module.h>

int Tong(int arr[20][20], int n, int m);
int Am(int arr[20][20], int n, int m);
int Duong(int arr[20][20], int n, int m);
int MAXDCC(int arr[20][20], int n, int m);
int MINDCC(int arr[20][20], int n, int m);
int MAXDCP(int arr[20][20], int n, int m);
int MINDCP(int arr[20][20], int n, int m);
int TongLe(int arr[20][20], int m, int n);
int TongChan(int arr[20][20], int m, int n);

static int lab1_3_init(void)
{
    int n = 3, m=3;
    int arr[20][20] = {{1,2,3},{5,6,7},{12,13,14}};
	
	printk(KERN_ALERT "\nTong = %d\n", Tong(arr, n, m));
	printk(KERN_ALERT "\nSo phan tu am = %d\n", Am(arr, n, m));
	printk(KERN_ALERT "\nSo phan tu duong = %d\n", Duong(arr, n, m));
	printk(KERN_ALERT "\nGTLN tren duong cheo chinh = %d\n", MAXDCC(arr, n, m));
	printk(KERN_ALERT "\nGTNN tren duong cheo chinh = %d\n", MINDCC(arr, n, m));
	printk(KERN_ALERT "\nGTLN tren duong cheo phu = %d\n", MAXDCP(arr, n, m));
	printk(KERN_ALERT "\nGTNN tren duong cheo phu = %d\n", MINDCP(arr, n, m));
	printk(KERN_ALERT "\nTong chan = %d\n", TongChan(arr, n, m));
	printk(KERN_ALERT"\nTong le = %d\n", TongLe(arr, n, m));

	return 0;
}

int Tong(int arr[20][20], int n, int m)
{
    int i,j, sum = 0;
	for(i=0;i<n;i++) {
		for( j=0;j<m;j++) {
			sum += arr[i][j];
		}
	}
	return sum;
}

int Am(int arr[20][20], int n, int m)
{
    int i, j, dem = 0;
	for(i=0;i<n;i++) {
		for( j=0;j<m;j++) {
			if(arr[i][j] < 0) 
            dem++; 
		}
	}
	return dem;

}

int Duong(int arr[20][20], int n, int m)
{
    int i, j, dem = 0;
	for(i=0;i<n;i++) {
		for( j=0;j<m;j++) {
			if(arr[i][j] > 0) 
            dem++; 
		}
	}
	return dem;
}

int MAXDCC(int arr[20][20], int n, int m)
{
    int max = arr[0][0];
	int i = 0;
	for(i=1;i<n;i++) {
		if(arr[i][i] > max) max = arr[i][i];
	}
	return max;

}

int MINDCC(int arr[20][20], int n, int m)
{
    int min = arr[0][0];
	int i = 0;
	for(i=1;i<n;i++) {
		if(arr[i][i] < min) min = arr[i][i];
	}
	return min;

}

int MAXDCP(int arr[20][20], int n, int m)
{
    int i, j, max = arr[0][n-1];
	for( i=0; i<n; i++) {
		for( j=0;j<m;j++) {
			if(i+j == n-1 && arr[i][j] > max) {
				max = arr[i][j];
				break;
			}
		}
	}
	return max;
}

int MINDCP(int arr[20][20], int n, int m)
{
    int i, j,min = arr[0][n-1];
	for( i=0;i<n;i++) {
		for( j=0;j<m;j++) {
			if(i+j == n-1 && arr[i][j] < min) {
				min = arr[i][j];
				break;
			}
		}
	}
	return min;
}

int TongChan(int arr[20][20], int n, int m)
{
	int i,j, sum = 0;
	for( i=0;i<n;i++) {
		for(j=0;j<m;j++) {
			if(arr[i][j] %2 ==  0) sum+=arr[i][j];
		}
	}
	return sum;
}

int TongLe(int arr[20][20], int n, int m)
{
	int i,j, suml = 0;
	for( i=0;i<n;i++) {
		for( j=0;j<m;j++) {
			if(arr[i][j]%2 !=  0) suml += arr[i][j];
		}
	}
	return suml;
}

static void lab1_3_exit(void)
{
    printk(KERN_ALERT "KET THUC \n");
}

module_init(lab1_3_init);
module_exit(lab1_3_exit);
