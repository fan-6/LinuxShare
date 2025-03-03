    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>

    int main(int argc, char **argv)
    {
        int fd_old; //老文件描述符
        int fd_new; //新文件描述符
        char buf[1024];
        int len;

        /* 1.判断参数 */
        if (argc != 3) {
            printf("This app is used to copy file. Usage: %s <old file> <new file>\n",argv[0]);
            printf("Like this: %s 1.txt 2.txt\n", argv[0]);
            return -1;
        }

        /* 2.打开老文件 */
        fd_old = open(argv[1], O_RDONLY);   //只读方式打开老文件
        if (fd_old == -1) {
            printf("Can't open file <%s>\n", argv[1]);
            return -1;
        }

        /* 3.创建新文件 */
        fd_new = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

        if (fd_new == -1) {
            printf("Create file <%s> fail!", argv[2]);
            return -1;
        }

        /* 4.循环: 读老文件->写新文件 */
        while ((len =read(fd_old, buf, 1024)) > 0) {
            if (write(fd_new, buf, len) != len) {
                printf("Can't write <%s>\n", argv[2]);
                return -1;
            }
        }

        close(fd_old);
        close(fd_new);

        return 0;
    }
