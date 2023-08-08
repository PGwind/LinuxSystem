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
    Student stu;
    Student *p;

    fd = open("test_map.txt", O_RDONLY); 
    if (fd == -1) {
        perror("open error");
        exit(1);
    }

    p = mmap(NULL, sizeof(stu), PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    
    close(fd);
    
    while (1) {
        printf("id = %d, name = %s, age = %d\n", p->id, p->name, p->age);
        sleep(1);
    }

    munmap(p, sizeof(stu));

    return 0;
}

