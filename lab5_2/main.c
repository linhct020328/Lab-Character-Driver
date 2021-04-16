#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
#define BUFFER_LENGTH 256

long read_buf[1024]; 
int8_t write_buf[1024];

int open_chardev() {
	int fd = open("/dev/lab52", O_RDWR);
	if(fd < 0) {
		printf("Can not open the device file\n");
		exit(1);
	}
    printf("Open the device file success\n");
	return fd;
}

void close_chardev(int fd) {
	close(fd);
}

int main(int argc, char** argv)
{
    int ret, fd;
    char select;
    int i;
    fd = open_chardev(); 
    while (1)
    {
        printf("-----------------------SELECT-----------------------\n");
        printf("1. Lay thoi gian tuyet doi chinh xac den micro giay\n");
        printf("2. Lay thoi gian tuyet doi chinh xac den nano giay\n");
        printf("3. Lay thoi gian tuong doi\n");
        printf("4. Ket thuc chuong trinh\n");
        printf("\nNhap lua chon: ");
        scanf(" %c", &select);

        switch (select)
        {  
            case '1':
                read(fd, read_buf, sizeof(long)*3); 
                printf("Thoi gian tuyet doi: %ld,%ld (chinh xac den micro giay)\n",read_buf[1], read_buf[2]/1000);
                break;
            case '2':
                read(fd, read_buf, sizeof(long)*3);
                printf("Thoi gian tuyet doi: %ld,%ld (chinh xac den nano giay)\n",read_buf[1], read_buf[2]);
                break;
            case '3': 
                read(fd, read_buf, sizeof(long)*4);
				printf("Thoi gian tuong doi: %ld s\n",read_buf[3]);
                break;
            case '4': 
                close(fd); 
                exit(1);
                break;
            default:
                printf("Nhap lai lua cho = %c\n", select);
                break;    
        }
    }
    printf("End of the program\n");
    return 0;
}    

