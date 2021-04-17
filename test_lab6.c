#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char write_buf[1024];
char read_buf[1024];
int8_t w_buf[27];
int8_t khv[26];
int k,i,j;
char x,ktt[26];
int main()
{
        int fd;
        char option;
        printf("**************************************************\n");
        printf("*******user application to test char driver*******\n");
 
        fd = open("/dev/lab6_device", O_RDWR);//mo de doc va ghi
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
 
        while(1) {
                printf("        ****Please Enter the Option******        \n");
                printf("        1. Nhap vao mot xau.\n");
                printf("        2. Ma hoa va luu xau dung ma dich chuyen.\n");
                printf("        3. Ma hoa va luu xau dung ma thay the.\n");
                printf("        4. Ma hoa va luu xau dung ma hoan vi.\n");
       
		printf("        5. Doc va giai ma xau ma dung ma dich chuyen.\n");
		printf("        6. Doc va giai ma xau ma dung ma dung ma thay the.\n");
		printf("        7. Doc va giai ma xau ma dung ma dung ma hoan vi.\n");
                printf("        8. Exit.\n");
                printf("*************************************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
				*write_buf = 1;
                                printf("Nhap vao xau: ");
                                scanf(" %s", write_buf+1);
                                write(fd, write_buf, strlen(write_buf)+1);
                                printf("Done!\n");
                                break;
                        case '2':
				*write_buf = 2;
                                printf("Nhap khoa K: ");
                                scanf(" %s", write_buf+1);
 				write(fd, write_buf, strlen(write_buf)+1);
				read(fd, read_buf, 1024);
				printf("Du lieu sau khi duoc ma hoa la: %s\n",read_buf);
				printf(".	Done!\n");
                                break;
                        case '3':
                        	*write_buf = 3;
                                printf("Nhap vao day ki tu dung lam ma thay the: ");
                                scanf(" %s", write_buf+1);
 				write(fd, write_buf, strlen(write_buf)+1);
 				read(fd, read_buf, 1024);
				printf("Du lieu sau khi duoc ma hoa la: %s\n",read_buf);
				
				printf(".	Done!\n");
                                break;
			case '4':
				*w_buf = 4;
				w_buf;
                                printf("Nhap vao day so dung lam ma hoan vi: ");
                                //1 25 16 12 2 24 11 3 23 17 22 4 21 13 5 20 6 19 7 14 8 18 15 9 26 10
                                for(int i = 1; i <= 26; i++){
                                	scanf(" %hhd", w_buf + i);
                                }
 				write(fd, w_buf, sizeof(int8_t)*27);
				read(fd, read_buf, 1024);
				printf("Du lieu sau khi duoc ma hoa la: %s\n",read_buf);
				
				printf(".	Done!\n");
                                break;
                      
                        case '5':
				*write_buf = 5;
				write(fd, write_buf, strlen(write_buf)+1);
				read(fd, read_buf, 1024);
                                printf("Nhap khoa K de giai ma: ");
				scanf(" %d", &k);
				printf("Du lieu sau khi duoc giai ma la: ");
				i = 0;
				while(read_buf[i] != '\0'){
					x = read_buf[i];
					x -= 71;//-97+26
					x -= k;
					x = x%26;
					x += 97;
					printf("%c",x);
					i++;
				}
				printf(".	Done!\n");
                                break;
                        case '6':
				*write_buf = 6;
				write(fd, write_buf, strlen(write_buf)+1);
				read(fd, read_buf, 1024);
				printf("GIAI MA DU LIEU, nhap khoa de giai ma: ");
				scanf(" %s", ktt);
				printf("DU LIEU sau khi GIAI MA la: ");
				i=0;
				while(read_buf[i] != '\0'){
					x = read_buf[i];
					for(j = 0; j< 26; j++){
						if(ktt[j] == x){
							x = j + 97;
							printf("%c",x);
							break;
						}
					}
					i++;
				}
				printf(".	Done!\n");
                                break;
                        case '7':
				*write_buf = 7;
				write(fd, write_buf, strlen(write_buf)+1);
				read(fd, read_buf, 1024);
				printf("GIAI MA DU LIEU, nhap khoa de giai ma: ");
				for(int i = 0; i < 26; i++){
                                	scanf(" %hhd", &khv[i]);
                                }
				printf("DU LIEU sau khi GIAI MA la: ");
				i = 0;
				while(read_buf[i] != '\0'){
					x = read_buf[i];
					x -= 96;
					for(j = 0; j < 26; j++){
						if(khv[j] == x){
							x = j + 97;
							printf("%c",x);
							break;
						}
					}
					i++;
				}
                                break;
                       
                        case '8':
                                close(fd);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
}


