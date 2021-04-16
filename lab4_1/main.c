#include<stdio.h>
#include<stdlib.h>// Thư viện sử dụng định nghĩa 1 số biến....
#include<unistd.h>/*read()/write() dùng để đọc dữ liệu từ file vật lý hoặc ghi dữ liệu ra file vật lý.*/
#include<sys/ioctl.h>
#include<sys/types.h>// thư viện : kiểu dữ liệu
#include<sys/stat.h>// trong thư viện C POSIX cho ngôn ngữ lập trình C có cấu trúc tạo điều kiện nhận thông tin về các thuộc tính tệp.
#include<fcntl.h>// xác định tùy chọn file control
#include<sys/select.h>
#include<sys/time.h>
#include<errno.h>

int main(int argc, char **argv){
	int f ;
	int wt, rd;
	f = open("/dev/device_lab4_1", O_RDWR);//f là file descriptor (đặc tả file),
	if(f < 0) {
		printf("Can not open the device file\n");
		exit(1);
	}
    	printf("Open the device file success\n");

	wt = write(f, &write, sizeof(write));
	printf("kq tra ve tu ham write = %d\n", wt);
	rd = read(f, &write, sizeof(write));
	printf("kq tra ve tu ham read = %d\n", rd);
	
	close(f);

}
