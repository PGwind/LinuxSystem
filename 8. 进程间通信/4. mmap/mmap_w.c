#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

typedef struct {
    int id;
    char name[256];
    int age;
} Student;

int main()
{
    int fd;
    Student stu = {1, "xiaoming", 18};
    Student *p;

    fd = open("test_map.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }

    ftruncate(fd, sizeof(stu));

    p = mmap(NULL, sizeof(stu), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    
    close(fd);
    
    while (1) {
        memcpy(p, &stu, sizeof(stu));
        stu.id ++;
        sleep(1);
    }

    munmap(p, sizeof(stu));

    return 0;
}

