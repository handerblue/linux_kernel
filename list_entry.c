#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define offsetof(a, b)  __builtin_offsetof(a, b) 

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define list_entry(struct_type, list_ptr, list_name)  (struct_type *)((char *)list_ptr - __builtin_offsetof(struct_type, list_name))
struct list_head{
    struct list_head *prev, *next;
};
struct car{
    char name[13];
    int year;
    char* owner;
    struct list_head list;
};

struct man{
    char first_name[10];
    int birth;
    struct list_head list;
};

struct car* get_new_car(char* name, int year, char* owner){
    struct car* new_car = malloc(sizeof(struct car));
    printf("allocate mem for car, size:%lu, car_struct size:%lu\n", sizeof(new_car), sizeof(struct car));
    strcpy(new_car->name, name);
    new_car->year = year;
    new_car->owner = malloc(strlen(owner));
    strcpy(new_car->owner, owner);
    new_car->list.prev = & new_car->list;
    new_car->list.next = & new_car->list;

    return new_car;
}
int main(){
    struct car* car1 = get_new_car("Lexus", 2018, "Hander");
    struct list_head *clist1;
    struct car *cpt1;
    int i, j, k; 
    unsigned long list_offset;

    /* 1. "Simply use offest to calculate struct address */
    clist1 = &car1->list;
    list_offset =  __builtin_offsetof(struct car, list); 
    cpt1 = (struct car*)((unsigned long)clist1 - list_offset);
    printf("offset:%lu\n", list_offset);
    
    /* 2. "We can see type check can be done by compiler \n"); */
    i = 0;
    cpt1 = container_of(i, struct car, list); 
    /* !!! Compiler Warninng Here !!!*/

    /* 3. "Using 1. & 2. combined which is popular used in linux kernel*/
    cpt1 = container_of(clist1, struct car, list); 
    printf("car1: 0x%x, cpt1:0x%x(diff:%lu), clist:0x%x, offset:%lu\n", (unsigned int)car1, (unsigned int)cpt1, (unsigned long)clist1 - (unsigned long)cpt1, (unsigned int)clist1, list_offset);
    printf("After list operation, compare car1 and cpt1:\n");
    printf("car1:%s, %d, %s\n", car1->name, car1->year, car1->owner);
    printf("cpt1:%s, %d, %s\n", cpt1->name, cpt1->year, cpt1->owner);
    
    return 0;
}
