//////////////////////////////////////////////////////////////////////
// tvec.h - simple STL vector class
//
// © PliaTech Corp 2002-2010
// Author: MB Pliam
// Originated Oct 5, 2002
// Last Update Jan 10, 2010

#pragma warning (disable: 4786)

#ifndef _TVEC_
#define _TVEC_

#include <string>
#include <deque>
#include <vector>
#include <iostream>
using namespace std;

template <class T>
class tvec
{
	// Attributes
private:
	//vector<T> vt;			// vector of T
	mutable deque<T> vt;	// deque of T
	long nn;				// number of elements

public:
	// Construction / Destruction
	tvec() { nn = 0; vt.resize(0); }
	tvec(long n) { nn = n; vt.resize(n); }
	tvec(vector<T> v) { nn = v.size(); vt = v; };
	tvec(long n, vector<T> v) { nn = n; vt = v; }
	tvec(long n, T x) {
		nn = n;
		for (long i = 1; i <= n; i++)
			vt.push_back(x);
	}
	tvec(long n, T *x) {
		nn = n;
		for (long i = 1; i <= n; i++)
			vt.push_back(x[i - 1]);
	}
	~tvec() { nn = 0; vt.resize(0); }

	tvec(const tvec<T> &a)	// copy
	{
		nn = a.nn;
		vt = a.vt;
	}

	tvec<T> &operator = (const tvec<T> &a) // assign a vector
	{
		nn = a.nn;
		vt = a.vt;
		if (this == &a) return *this;
		return *this;
	}

	tvec<T> &operator = (const T &a) // assign a constant
	{
		nn = nn;
		for (long i = 0; i<nn; i++) vt[i] = a;
		return *this;
	}

	long nsize() { return nn; }
	long size() const { return nn; }

	long resize(long n) { nn = n; vt.resize(n); return n; }

	//long rows() const { return nn; }

	T &operator() (long i) const
	{
		return vt[i - 1];

	}

	friend ostream &operator << (ostream &s, tvec<T> &v)
	{
		cout << v.nsize() << endl;
		for (int i = 1; i <= v.nsize(); i++)
			s << v(i) << endl;

		return s;

	}

	// friends
	friend tvec<T> operator + (const tvec<T> &a, const tvec<T> &b)
	{
		if (a.nsize() != b.nsize()) {
			printf("vectors do not conform for addition\n");
			return a;
		}

		tvec<T> c(a.nsize());
		for (long i = 1; i <= c.nsize(); i++)
			c(i) = a(i) + b(i);
		return c;

	}// operator +

	friend tvec<T> operator - (const tvec<T> &a, const tvec<T> &b)
	{
		if (a.nsize() != b.nsize()) {
			printf("vectors do not conform for subtraction\n");
			return a;
		}

		tvec<T> c(a.nsize());
		for (long i = 1; i <= c.nsize(); i++)
			c(i) = a(i) - b(i);
		return c;

	}// operator -

	friend tvec<T> operator * (const tvec<T> &a, T b)
	{
		tvec<T> c(a.nsize());
		for (long i = 1; i <= c.nsize(); i++)
			c(i) = a(i) * b;
		return c;

	}// operator *

	friend tvec<T> operator * (T b, const tvec<T> &a)
	{
		tvec<T> c(a.nsize());
		for (long i = 1; i <= c.nsize(); i++)
			c(i) = a(i) * b;
		return c;

	}// operator *

	 // vector elementwise product
	friend tvec<T> operator * (const tvec<T> &a, const tvec<T> &b)
	{
		if (a.size() != b.size()) {
			printf("vectors do not conform for multiplication\n");
			return a;
		}

		tvec<T> c(a.size());
		for (long i = 1; i <= c.size(); i++)
			c(i) = a(i) * b(i);
		return c;

	}// operator *

};

#endif // _TVEC_

//////////////////////////////////////////////////////////////////////
// PliaTech 2002-2010


// Copyright © 2002-2010 by M.B. Pliam.  ALL RIGHTS RESERVED. 
// Consult your license regarding permissions and restrictions.
//

//
// This file is derived from software bearing the following
// restrictions:
//
// Copyright © 2002-2010
// PliaTech International
//
// Permission to use, copy, modify, distribute and sell this
// software and its documentation for any purpose is hereby
// granted without fee, provided that the above copyright notice
// appear in all copies and that both that copyright notice and
// this permission notice appear in supporting documentation.
// PliaTech International makes no representations about the
// suitability of this software for any purpose. It is provided
// "as is" without express or implied warranty.
//

