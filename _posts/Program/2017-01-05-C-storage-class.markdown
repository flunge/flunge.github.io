---
layout: post
title:  "C storage class"
date:   2017-01-05
categories: Program
tags: [C & C++]
---

### Summary

In C language, each variable has a storage class which decides scope, visibility and lifetime of that variable. The following storage class are most ofenly used in C programming.

1. Automatic variables
2. External variables
3. Static variables
4. Register variables

___

### Part 1. Automatic variables

1. A variable declared inside a function without any storage class specification, is by default an automatic variable. 
2. They are created when a function is called and are destroyed automatically when the function exits. 
3. By default they are assigned garbage value by the compiler.

```
void main()
{
int detail; 
auto int detail;	// Both are same
}
```

___

### Part 2. External or Global variable

1. Global variable: A variable that is declared outside any function is a Global variable, which remain available throughout the entire program. Its value can be changed by any function in the program.
2. "extern" keyword: The extern keyword is used before a variable to inform the compiler that this variable is declared somewhere else, which does not allocate storage for variables.

```
main()
{
	extern int x; // Tells the compiler that it is defined somewhere else
	x = 10;
	printf("%d", x);
}
```
___

### Part 3. Static variable

1. A static variable tells the compiler to persist the variable until the end of program.
2. static is initialized only once and assigned 0 (zero) as default value by the compiler.
3. When static specifier is applied to a local variable inside a function or block, the compiler creates permanent storage for it, but static local variable remains visible only to the function or block in which it is defined.

```
#include <stdio.h>

void staticDemo()
{
  static int i;
  {
    static int i = 1;
    printf("%d ", i);
    i++;
  }
  printf("%d\n", i);
  i++;
}
 
int main()
{
  staticDemo();
  staticDemo();
}
OUTPUT
======
1 0
2 1
```

4. When static specifier is applied to a global variable or a function then compiler makes that variable or function known only to the file in which it is defined. These variables cannot be used in other files.

```
#include <stdio.h>

static int gInt = 1;
static void staticDemo()
{
  static int i;
  printf("%d ", i);
  i++;
  printf("%d\n", gInt);
  gInt++;
}
 
int main()
{
  staticDemo();
  staticDemo();
}
OUTPUT
======
0 1
1 2
```

___

### Part 4. Register variable

1. Register variable inform the compiler to store the variable in register instead of memory.
2. Register variable has faster access than normal variable. Frequently used variables are kept in register. 
3. We can never get the address of such variables.