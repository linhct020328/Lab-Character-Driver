## Install
- `$sudo apt install make`
- `$sudo apt install build-essential -y`
- `$sudo apt install linux-headers-$(uname -r)`
- `$sudo apt-get install manpages-dev`

## Lab(1-3)
- `Để biên dịch: $make`
- `Cài đặt module vào hệ thống (sử dụng lệnh insmod) : $ sudo insmod  file.ko (file này có được sau khi biên dịch). Gỡ kernel module dùng lệnh rmmod`
- `Để hiển thị nội dụng của kernel: $sudo dmesg`

## Đối với các bài Character Device Driver(4-6)
- `Làm các bước như trên lab(1-3)`
- `Xem major id của kernel module dùng lệnh: $ cat /proc/devices. Hoặc liệt kê các Driver file dùng câu lệnh: $ ls -l /dev`
- `Sau khi hiển thị nội dung kernel ta test bên phần user thì cần dịch: $gcc test.c -o test (test hoặc main)`
- `Chạy test: $ sudo ./test`

