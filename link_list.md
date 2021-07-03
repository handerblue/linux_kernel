Linux kernel provides reusable link-list data structure. We don't need to create all of operations of link list from scratch.

Concepts:
- All the pointers in link-list is a member of structure
- Use offset of pointer member in the structure. And by subtracting this offset from the pointer, we get the address of structure

```
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
```

We can get rid of first line. But this will lead to lack of type checking of ptr.
```
const typeof( ((type *)0)->member ) *__mptr = (ptr);
```

offsetof(type, member): returns the offset value from start address of structure.

```
(type *)( (char *)__mptr - offsetof(type,member) );})
```
```
struct typeA{
  int a;
  int b;
  int c;
  int member1;
};

offsetof(typeA, member1) returns 12 
  a = 0, b = 0 + 4, c = 4 + 8, member1 = 8 + 12 (32bits arch)

gcc provides build in offsetof function:  __builtin_offsetof(a, b) which offsetoff() actually calls.

```
