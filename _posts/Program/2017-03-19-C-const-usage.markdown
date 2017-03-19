---
layout: post
title:  "C++ const"
date:   2017-01-05
categories: Program
tags: [C & C++]
---

### Summary

"const" declaration is one of the most messy features of C++. It is simple in conecpt: variables declared with 'const' added become constants and cannot be altered by the program. However it is also used to bodge in a substitute for one of the missing features of C++ and there it gets horridly complicated and sometimes frustratingly restictive. 

1. 'const' used on variables;
2. 'const' used on reference;
3. 'const' used on pointers;
4. 'const' used on parameter passing and functions;
___

### Part 1. 'const' used on variables

a) 'const' is a compile time constraint that an object cannot be modified;

b) 'const' declaration must be initialized.

```
const std::string hi = "hello"; // ok
const int i, j = 0; // error: i is not initialized
```
c) A non-const global variable is an 'extern' variable by defaults, while a const global variable has to be declared explicitly as 'extern'.

```
// file_1.cc
extern const int bufSize = fcn();
// file_2.cc
extern const int bufSize; // use bufSize from file_1
```

### Part 2. 'const' used on reference

a) A reference is an alias to a certain object and a reference has to be initialized and cannot redefined;

b)  const reference is a reference to const variable and non-const reference cannot be initialized by a const variable;

```
const int ival = 1024;
const int &refVal = ival; // ok: a const reference
refVal += 2; // error: a const reference
int &ref2 = ival; // error: non-const reference to a const object
```

c) A const reference can be initialized as a right value or a different type.

```
int i = 42;
// legal for const references only
const int &r = 42;
const int &r2 = r+i;

double dval = 3.14; 
const int &ri = dval;
// which is equal to the following
int temp = dval; // a force transform
const int &ri = temp; // bind ri to that temp
```
___

### Part 3. 'const' used on pointers

a) If 'const' is on the left of \*, data is const, we call it 'const data pointer', and if 'const' is on the right of \*, pointer is const, we call it 'const pointer';

```
const int i = 9;
const int *p1 = &i; // data is const, pointer is not
int const *p2 = &i; // data is const, pointer is not
int* const p2 = &i; // data is not, pointer is const
```

b) A const data cannot be bind with a normal pointer, while a const data pointer can be bind with a normal data, but cannot modify the value through the pointer;

```
const double *cptr;
*cptr = 42; // error: a const data pointer
const double pi = 3.14;
double *ptr = &pi; // error: const data cannot be binded with normal pointer
void *pv = &pi; // error: const data cannot be binded with normal pointer
double dval = 3.14;
cptr = &dval; //ok: but cannot change dval though cptr
```
c) A const pointer points to a fixed object and cannot be re-pointed to other objects.

```
int errNumb = 0;
int* const curErr = &errNumb; // curErr is a const pointer
curErr = curErr; // error: const pointer cannot be redefined

typedef string *pstring;
const pstring cstr;

// wrong interpretation of the const pstring cstr
const string *cstr;
// correct interpretation
string* const cstr;
```
___
### Part 4. 'const' used on parameter passing

a) const parameters by reference avoid parameters being modified in the function calls;

b) const return value by reference avoid the result being modified;

c) const member functions reject modification of any member variables, except those with 'mutable' declarations, and const functions can only call other const functions;

```
class Dog{
	int age;
	string name;

public: 
	Dog() {age = 3; name = "dummy";}

	void setAge (const int& a) // const parameters by reference
	{
		age = a; 
		a++; // error: cannot be modified
	}

	const string& getName() {return name;} // const return value by reference

	void printDogName() const // const functions
	{
		cout << name << "const" << endl; // prints "dummyconst"
		age++; // error: in const functions cannot change any member variable
		cout << getName() << endl; // error: non-const functions called in const functions
	}

	void printDogName() // non-const function overload
	{
		cout << getName() << "nonconst" << endl; // prints "dummynonconst"
	}
}

int main() {
	Dog d;

	int i = 9;
	d.setAge(i) // ok: age has been set to 9

	const string& n = d.getName(); // n cannot be changed

	d.printDogName(); // invoke non-const functions

	const Dog d2;
	d2.printDogName(); // invoke const version
}

```
___
