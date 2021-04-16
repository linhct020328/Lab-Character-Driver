#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/select.h>
#include<sys/time.h>
#include<errno.h>

int8_t w = 'w';
int8_t r;

int main(int argc, char **argv){
	int f ;
	int wt, rd;
	f = open("/dev/device_lab4_1", O_RDWR);
	wt = write(f, &write, sizeof(write));
	printf("kq tra ve tu ham write = %d\n", wt);
	rd = read(f, &write, sizeof(write));
	printf("kq tra ve tu ham read = %d\n", wt);
	
	close(f);

}
