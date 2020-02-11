// Chapter2_VariablesAndBasicTypes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Chapter2Const.h"
using namespace std;

// //Declarations and Definitions
// extern int i;			   // Declares but does not define i
// int j;					   //declare and defines j
// extern double pi = 3.1416; // declare and defines pi

void TestTypeConvert();
void TestSignedAndUnsigned();
void TestInitialization();
void TestReference();
void TestPoints();
void TestCompoundType();
void TestConstInitialization();
void TestConstMultipleFiles();
void TestConstReference();
void TestConstReferenceInitialization();
void TestReferenceToNonConstObject();
void TestConstPointer();
void TestTopLowLevelConst();
void TestTypeAliases();
void TestTypePointerAliases();
void TestAutoSpecifier();
void TestCompoundAutpSpecifier();
void TestDeclType();

// struct Sales_data
// {
// 	std::string bookNo;
// 	unsigned units_sold = 0;
// 	double revenue = 0.0;
// } accum, trans, *salesptr;

// struct Sales_data
// {
// 	std::string bookNo;
// 	unsigned units_sold = 0;
// 	double revenue = 0.0;
// };

// Sales_data accum, trans, *salesptr;

main()
{
	TestTypeAliases();
}

void TestDeclType()
{
	decltype(getSize_Literal()) size;
	decltype(getSize_Int()) ss;

	const int ci = 0, &cj = ci;
	decltype(ci) x = 0; // x is const int
	auto xx = ci;		//xx is int
	decltype(cj) y = x; //y is int reference
	// decltype(cj) yy; //yy is int reference, must be initialized

	int i = 42, *p = &i, &r = i;
	decltype(r) b = i;  //b is int reference
	decltype(r + 0) bb; //bb is int,because r + 0 is a expression and result is literal
	decltype(p) c;		// c is int pointer
	// decltype(*p) cc;//error,*p is a expression and *p can be the left hand side of assignment,cc is int&

	decltype(i) d; // d is uninitialized int
				   // decltype((i)) dd;//error,(i) is expression and i can be left hand side, so dd is int&
}

void TestCompoundAutpSpecifier()
{
	int i = 0, &r = i;
	auto a = r; //a is int not int reference because r is alias for i

	const int ci = i, &cr = i; //ci is const int,cr is const int reference
	auto b = ci;			   //b is int
	auto d = &i;			   //d is int*
	auto e = &ci;			   //e is const int *
	auto &g = ci;			   // g is const int reference
	// auto &h=42;//error
	const auto &h = 42; //can bind const reference to literal

	auto &m = i, k = ci; //although i is int while ci is const int,but the top-level const is ignored
						 // auto &n = i, *p2 = &ci; //error,while using reference, top-level const is not ignored
}

void TestAutoSpecifier()
{
	auto i = 0, *p = &i; //i is int, p is int*
						 // auto sz = 0, pi = 3.14; //error, sz is int but pi is double
}

void TestTypePointerAliases()
{
	int value1 = 15, value2 = 20;
	typedef int *pInt;
	typedef const int *cpInt;
	const pInt p = &value1; //equals to int *const p=&value1;
	cpInt cp = &value1;		//equals to const int *cp=&value1;
	// *cp = 20; //error, cp is pointer to const int
	*p = 20; // p is int* const
		// p = &value2; //error,p is int * const
}

void TestTypeAliases()
{
	typedef double wages; //wages is a synonym for double
	using base = wages;   //base is a synonym for wages(double)
	base b = 3.14;
	wages w = b;
	cout << b << "  " << w << endl; //3.14  3.14
									// typedef wages base, *p; //base is a synonym for wages(double), p for double*
}

void TestTopLowLevelConst()
{
	int i = 0;
	int *const pi = &i;  //pi is top level const
	const int ci = 42;   //top level const
	const int *p2 = &ci; //low level const
	// int *p3 = p2;	//error,differnt low level const,and const can't convert to nonconst
	const int *const p4 = p2; //both top and low level const
	const int &r1 = ci;		  //low level const
	// int &r2 = ci;	//error,differnt low level const,and const can't convert to nonconst
	i = ci;			   //i is low level const, high level const of ci is ignored
	p2 = p4;		   //high level of p4 is ignored
	p2 = &i;		   //although different low level const,but nonconst can convert to const
	const int &r3 = i; //although different low level const,but nonconst can convert to const
}

void TestConstPointer()
{
	int errorNum = 0, warningNum = 0;
	// int *const curErr;//error, must be initialized.
	int *const curErr = &errorNum;
	// curErr = &warningNum; // can not change pointer value
	*curErr = 1;

	const double pi = 3.14;
	double p = 3.1415;
	const double *const pip = &pi;
	// pip = &p; //error,can not change pointer value
	// *pip = 2.0; //error,can not const variable value
}

void TestPointerToConst()
{
	const double pi = 3.14;
	// double *ptr = &pi;//error,pointer must be pointer to const
	const double *cptr = &pi;
	// *cptr = 42; //error,can't modify const value
	double dval = 3.14;
	cptr = &dval; //can pointer to different variable
				  // const int *iptr = &dval;//error,can't point to differnet type
}

void TestReferenceToNonConstObject()
{
	int i = 42;
	int &r1 = i;
	const int &r2 = i;
	cout << "value is " << r2 << endl; //value is 42
	r1 = 0;
	// r2=0;//error,can't change const reference
	cout << "value is " << r2 << endl; //value is 0
}

void TestConstReference()
{
	const int ci = 1024;
	const int &r1 = ci;
	// r1 = 42;	  //error,ri is reference to a const variable
	// int &r2 = ci; //error, reference to a const variable must be const
}

void TestConstReferenceInitialization()
{
	int i = 42;
	double dval = 3.14;
	const int &r1 = i;
	const int &r2 = 42;
	const int &r3 = r1 * 2;
	const int &r4 = dval;
	// int &r5 = i * 2;//error, plain,nonconst reference must match type
}

void TestConstMultipleFiles()
{
	extern const int bufSize;
	cout << "value is: " << bufSize; //value is: 42
}

void TestConstInitialization()
{
	const int kk = getSize_Literal();
	// const int k; //error, const value must be initialized
	int i = 42;
	const int ci = i;
	int j = ci;
}

void TestTypeConvert()
{
	//Type convert
	bool b = 42;
	cout << "value is " << b << endl;
	int i = b;
	cout << "value is " << i << endl;
	i = 3.14;
	cout << "value is " << i << endl;
	if (i)
		cout << "result is true" << endl;
	double pi = i;
	cout << "value is " << pi << endl;
	unsigned char c = -1;
	cout << "value is " << (int)c << endl;
	signed char c2 = 256; //cause warning
	cout << "value is " << (int)c2 << endl;
}

void TestSignedAndUnsigned()
{
	// signed and unsigned implicitly convert
	unsigned u1 = 10, u2 = 42;
	int i = -42;
	cout << i + i << endl;
	cout << i + u1 << endl;
	cout << u2 - u1 << endl;
	cout << u1 - u2 << endl;

	// signed and unsigned implicitly convert cause endless loop
	for (unsigned i = 10; i >= 0; i--)
	{
		cout << "i is " << i << endl;
	}
}

void TestLiteral()
{
	//literal
	int i_decimal = 20, i_octal = 024, i_hexadecimal = 0x14;
	// int month = 09;//error, 09 is treated as octal
	cout << "i decimal is " << i_decimal << endl;
	cout << "i octal is " << i_octal << endl;
	cout << "i hexadecimal is " << i_hexadecimal << endl;
	cout << 9223372036854775807 << endl;
	// cout << 9223372036854775808 << endl;
	// cout << -9223372036854775808 << endl;
	cout << 3.14159 << endl;   //3.14159
	cout << 3.14159E0 << endl; //3.14159
	cout << 3.14159E1 << endl; //31.14159
	cout << 0. << endl;		   //0
	cout << 0e0 << endl;	   //0
	cout << .001 << endl;	  //0.001
	cout << 1E-3 << endl;	  //0.001
	cout << 'a' << endl;	   //a
	cout << "Hello" << endl;   //Hello
	cout << "This is first string literal"
			"This is second string literal"
		 << endl;	  //This is first string literalThis is second string literal
	cout << "M\n";	 //M
	cout << "\115\12"; //M
	cout << "\x4d\xA"; //M

	cout << 9223372036854775808ULL << endl;
	cout << L'a' << endl;
	cout << u8"hi" << endl;
	cout << 1E-3F << endl;
	cout << 0.001F << endl;
	cout << 3.14159L << endl;
}

int reused = 42; //global scope

void TestInitialization()
{
	// Variables
	int sum = 0, value, sold = 0;
	double price = 109.99, discount = price * 0.16;

	//Initialization
	int units_sold = 0;
	// int units_sold(0);
	// int units_sold = {0};
	// int units_sold{0};

	// long double id = 3.1415926536; //cause warning
	// float ifloat{id};			   //cause warning
	// int a{id}, b = {id};		   //cause warning

	int unique = 0;							   //block scope
	cout << reused << " " << unique << endl;   //42 0
	int reused = 0;							   //local named reused hides global reused
	cout << reused << " " << unique << endl;   // 0 0
	cout << ::reused << " " << unique << endl; // 42 0
}

void TestReference()
{
	//Reference
	int ival = 1024;
	int &refVal = ival;
	// int &refVal2; //error,must be initialized
	// &refVal = reused; //error,can not be rebinded
	refVal = reused; //Not rebingding, is to change ival's value

	int ii = refVal;	   //Bound to ival
	int &refVal3 = refVal; //the same value as ival

	int i = 1024, i2 = 2048;
	int &r = i, r2 = i2; //r is int refernece, r2 is int
	// int &refVal4 = 10; //error, can't be bound to literal
	double dval = 3.14;
	// int &refVal5 = dval; //error, types not match
}

void TestPoints()
{
	//Points
	int *ip1, *ip2; //define int pointer without initializer
	double dp, dp2; //dp is double, dp2 is double pointer
	int ival = 42;
	int *p = &ival; //p hold the address of ival
	double dval;
	double *pd = &dval; //Initializer is the address of a double
	double *pd2 = pd;   //Initializer is a pointer to double
	// int *pi = pd;		//error,pointer types not match
	// int *pi2 = &dval;   // error,pointer types and object type not match

	int *ip = &ival;	 //Pointer to ival
	int *ipEnd = ip + 1; //Pointer to end of ival
	int *ipNull = NULL;
	cout << (*ip) << "  " << (*ipEnd) << endl; // 42 0

	int i = 42;
	int &r = i;							 //reference
	int *pp;							 //pointer
	pp = &r;							 //address-of operator
	*pp = i;							 //dereference
	int &r2 = *pp;						 // reference and dereference
	cout << (r2) << "" << (*pp) << endl; //4242

	int *p1 = nullptr; // c++ 11
	int *p2 = 0;
	int *p3 = NULL;
	int zero = 0;
	// p3 = zero; //error, can't assign an int to pointer

	double obj = 3.14, *pdd = &obj;
	void *pv = &obj; //pv can hold a pointer to any type
	pv = pdd;
	// cout << (*pv) << endl;//error,can't operate in the object void* addresses
}

void TestCompoundType()
{
	// Understanding Compound Type Declarations
	//// int i = 1024, *p = &i, &r = i;

	int ival = 1024;
	int *pi = &ival;
	int **ppi = &pi;
	cout << "Direct value is " << ival << endl;			  //Direct value is 1024
	cout << "Indirect value is " << *pi << endl;		  //Indirect value is 1024
	cout << "Double indirect value is " << **ppi << endl; //Double indirect value is 1024

	int i = 42;
	int *p;
	int *&r = p;
	r = &i; //make p point to i
	*r = 0; //make i's value to 0
}