// tmat.h - simple STL matrix class
//
// © PliaTech Corp 2002-2010
// Author: MB Pliam
// Originated Oct 5, 2002
// Revised Nov 15, 2002
// Revised Aug 24, 2003
// Revised Sep 1, 2003
// Last Update Jan 19, 2010

#pragma warning (disable: 4786)

#ifndef _TMAT_
#define _TMAT_

#include <complex>

#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <exception>
using namespace std;

//#include <crtdbg.h>
//#ifdef _DEBUG
//#include "trace.h"
//#endif

#ifndef _TVEC_
#include "tvec.h"
#endif

//////////////////////////////////////////////////////////////////////
// tmat class

template <class T>
class tmat
{
	// constructors and destructor
public:

	tmat()
	{
		m_nrows = 0;
		m_ncols = 0;
		//m_vec.resize(0);
	}

	tmat(long row, long col)
	{
		m_nrows = row;
		m_ncols = col;
		m_vec.resize(row * col);

	}

	tmat(long row, long col, const tvec<T> &sv)
	{
		m_nrows = row;
		m_ncols = col;
		m_vec = sv;

	}

	tmat(long row, long col, T x)
	{
		m_nrows = row;
		m_ncols = col;
		tvec<T> nv(row*col, x);
		m_vec = nv;

	}


	tmat(long row, long col, T *x)
	{
		m_nrows = row;
		m_ncols = col;
		tvec<T> nv(row*col, x);
		m_vec = nv;

	}

	tmat(const tmat<T> &a)	// copy
	{
		m_nrows = a.m_nrows;
		m_ncols = a.m_ncols;
		m_vec = a.m_vec;
	}

	tmat &operator = (const tmat<T> &a)	// assignment
	{
		m_nrows = a.m_nrows;
		m_ncols = a.m_ncols;
		m_vec = a.m_vec;
		return *this;
	}

	tmat &operator = (const T &a)	// assignment
	{
		//m_nrows = 1;
		//m_ncols = 1;
		//m_vec.resize(1);
		//m_vec(1) = a;
		m_vec = a;
		return *this;
	}

	virtual ~tmat()
	{
		m_nrows = 0;
		m_ncols = 0;
		m_vec.resize(0);

	}

	// Attributes
protected:
	long m_nrows;				// number of rows
	long m_ncols;				// number of columns
	mutable tvec<T> m_vec;		// base vector container

								// Implementation
public:
	long nrows() { return m_nrows; }
	long ncols() { return m_ncols; }
	long num_rows() const { return m_nrows; }
	long num_cols() const { return m_ncols; }

	void resize(long rows, long cols)
	{
		m_nrows = rows;
		m_ncols = cols;
		m_vec.resize(rows * cols);
	}

	void show()
	{
		long i, j, k; k = 1;
		cout << m_nrows << "  " << m_ncols << endl;
		for (i = 1; i <= m_nrows; i++) {
			for (j = 1; j <= m_ncols; j++) {
				cout << m_vec(k) << "   "; k++;
			}cout << endl;
		}cout << endl;

	}

	//  error output
	void cerror(char *text)
	{
		//printf("%s\n", text);
		throw text;

	}

	// indexing operators
	T &operator() (long i)	const // 1d indexing
	{
		if (i < 1 || i > m_nrows * m_ncols)
			cerror("operator(): index out of range");

		return m_vec(i);
	}

	T &operator() (long i, long j) const // 2d indexing
	{
		if (i < 1 || i > m_nrows || j < 1 || j > m_ncols)
			//cerror("operator(): index out of range");
			printf("operator index range error\n");

		long li = i - 1;
		long lj = j - 1;
		long lc = m_ncols;
		return m_vec(li *lc + lj + 1);
	}

	T &operator() (long i, long j) // 2d indexing
	{
		if (i < 1 || i > m_nrows || j < 1 || j > m_ncols)
			cerror("operator(): index out of range");

		long li = i - 1;
		long lj = j - 1;
		long lc = m_ncols;
		return m_vec(li *lc + lj + 1);
	}

	// friends
	friend ostream &operator << (ostream &s, tmat<T> &m)
	{
		s << m.nrows() << "  " << m.ncols() << endl;
		for (int i = 1; i <= m.nrows(); i++) {
			for (int j = 1; j <= m.ncols(); j++) {
				s << m(i, j) << "  ";
			} s << endl;
		}s << endl;

		return s;
	}

	friend  tmat<T> operator + (const tmat<T> &a, const tmat<T> &b)
	{
		if (a.num_rows() != b.num_rows() || a.num_cols() != b.num_cols()) {
			printf("matrices do not conform in addition\n");
			return a;
		}
		tmat<T> c(a.num_rows(), a.num_cols());
		for (long i = 1; i <= c.nrows(); i++)
			for (long j = 1; j <= c.ncols(); j++)
				c(i, j) = a(i, j) + b(i, j);
		return c;
	}

	friend tmat<T> operator - (const tmat<T> &a, const tmat<T> &b)
	{
		if (a.num_rows() != b.num_rows() || a.num_cols() != b.num_cols()) {
			printf("matrices do not conform in addition\n");
			return a;
		}
		tmat<T> c(a.num_rows(), a.num_cols());
		for (long i = 1; i <= c.nrows(); i++)
			for (long j = 1; j <= c.ncols(); j++)
				c(i, j) = a(i, j) - b(i, j);
		return c;
	}

	friend tmat<T> operator * (const tmat<T> &a, const tmat<T> &b)
	{
		if (a.num_rows() != b.num_cols()) {
			printf("matrices do not conform for multiplication\n");
			return a;
		}

		T sum;
		tmat<T> c(a.num_rows(), b.num_cols());
		for (long i = 1; i <= a.num_rows(); i++) {
			for (long j = 1; j <= b.num_cols(); j++) {
				sum = 0;
				for (long k = 1; k <= a.num_cols(); k++)
					sum += a(i, k) * b(k, j);
				c(i, j) = sum;
			}
		}

		return c;
	}

	friend tmat<T> operator / (const tmat<T> &a, const tmat<T> &b)
	{
		if (a.num_rows() != b.num_cols()) {
			printf("matrices do not conform for matrix division\n");
			return a;
		}

		tmat<T> c(a.num_rows(), b.num_cols());

		tmat<T> tmp = b;
		double fdet = det(tmp);  cout << "fdet(b) = " << fdet << endl;
		if (fabs(fdet) < 1.0e-32)
		{
			printf("divisor matrix is singular\n");
			return a;
		}

		tmp = inv(tmp);
		c = a * tmp;

		return c;
	}

};

// *******************[ basic matrix operations ]***************************

template <class T>
tmat<T> transpose(tmat<T> m)
{
	tmat<T> c(m.ncols(), m.nrows());
	for (long i = 1; i <= m.ncols(); i++) {
		for (long j = 1; j <= m.nrows(); j++) {
			c(i, j) = m(j, i);
		}
	}
	return c;

}// transpose(tmat<T> m)

template <class T>
tmat<T> add(tmat<T> a, tmat<T> b)
{
	if (a.ncols() != b.ncols() || a.nrows() != b.nrows()) {
		printf("matrices do not conform for addition\n");
		return a;
	}

	tmat<T> c(a.nrows(), a.ncols());
	for (long i = 1; i <= a.nrows(); i++) {
		for (long j = 1; j <= a.ncols(); j++) {
			c(i, j) = a(i, j) + b(i, j);
		}
	}
	return c;

}// add(tmat<T> a, tmat<T> b)

template <class T>
tmat<T> subtract(tmat<T> a, tmat<T> b)
{
	if (a.ncols() != b.ncols() || a.nrows() != b.nrows()) {
		printf("matrices do not conform for subtractionn\n");
		return a;
	}

	tmat<T> c(a.nrows(), a.ncols());
	for (long i = 1; i <= a.nrows(); i++) {
		for (long j = 1; j <= a.ncols(); j++) {
			c(i, j) = a(i, j) - b(i, j);
		}
	}
	return c;

}// subtract(tmat<T> a, tmat<T> b)

template <class T>
tmat<T> mul(tmat<T> a, tmat<T> b)
{
	if (a.ncols() != b.nrows()) {
		printf("matrices do not conform for multiplication\n");
		return a;
		//throw "matrices do not conform for multiplication";
	}

	T sum;
	tmat<T> c(a.nrows(), b.ncols());
	for (long i = 1; i <= a.nrows(); i++) {
		for (long j = 1; j <= b.ncols(); j++) {
			sum = 0;
			for (long k = 1; k <= a.ncols(); k++)
				sum += a(i, k) * b(k, j);
			c(i, j) = sum;
		}
	}
	return c;
}// mul(tmat<T> a, tmat<T> b)




//////////////////////////////////////////////////
//////////////////////////////////////////////////////
template <class T>
tmat<T> mul(tmat<T> a, T b)
{
	tmat<T> c(a.nrows(), a.ncols());

	for (long i = 1; i <= a.nrows(); i++) 
	{
		for (long j = 1; j <= a.ncols(); j++) 
		{
			c(i, j) = a(i, j) * b; 											////!!!!!
			//cout <<">>>>" <<c(i, j)<<"   "<< b <<"<<<<<<"<< endl;
		}
	}
	//cout << endl;
	return c;
}// mul(tmat<T> a, tmat<T> b)

////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////




template <class T>
tmat<T> sweep(long k1, long k2, tmat<T> &a)
{
	//double eps = 1.0e-8;
	T eps = 1.0e-8;
	T d;
	long i, j, k, n, it;

	if (a.ncols() != a.nrows())
		printf("sweep: matrix a not square\n");

	n = a.nrows();
	if (k2 < k1) { k = k1; k1 = k2; k2 = k; }

	for (k = k1; k <= k2; k++) {
		if (fabs(a(k, k)) < eps)
			for (it = 1; it <= n; it++)
				a(it, k) = a(k, it) = 0.0;
		else {
			d = 1.0 / a(k, k);
			a(k, k) = d;
			for (i = 1; i <= n; i++)
				if (i != k)
					a(i, k) *= (T)-d;
			for (j = 1; j <= n; j++)
				if (j != k)
					a(k, j) *= (T)d;
			for (i = 1; i <= n; i++) {
				if (i != k) {
					for (j = 1; j <= n; j++) {
						if (j != k)
							a(i, j) += a(i, k) *a(k, j) / d;
					} // end for j
				} // end for i != k
			} // end for i
		} // end else
	} // end for k
	return a;

}// sweep(long k1, long k2, tmat<T> &a)

template <class T>
tmat<T> inv(tmat<T> &a)
{
	printf("typeid(a(1,1)).name() == %s\n", typeid(a(1, 1)).name());
//	if (strcmp(typeid(a(1, 1)).name(), "int") == 0)
//	{
//		printf("not available for integer matrices. recast to double\n");
//		return a;
//	}

//	if (strcmp(typeid(a(1, 1)).name(), "double") != 0 &&
//		strcmp(typeid(a(1, 1)).name(), "float") != 0) {
//		printf("not a floating point type\n");
//		return a;
//	}

	if (a.ncols() != a.nrows())
		printf("INVERSE: matrix a not square\n");

	tmat<T> b = a;
	sweep(1, b.nrows(), b);
	return b;

}   // inverse 

template <class T>
tmat<T> submatrix(tmat<T> a, long lr, long r, long lc, long c)
// returns a designated submatrix, sa, of matrix a
{
	long m = a.nrows(); long n = a.ncols();
	if ((r > m) || (c > n)) {
		printf("index out of range\n");
		return a;
	}

	long r2 = r - lr + 1; long c2 = c - lc + 1;
	tmat <T> b(r2, c2);
	long lrm1 = lr - 1; long lcm1 = lc - 1;
	for (long i = 1; i <= r2; i++)
		for (long j = 1; j <= c2; j++)
			b(i, j) = a(lrm1 + i, lcm1 + j);
	return b;

}// submatrix(tmat<T> a, long lr, long r, long lc, long c)


 /////////////////////////////////////////////////////////////////////
 // determinant algorithms and definitions

#define VERY_SMALL	1.0e-12
#define VERY_LARGE	1.0E+12

 // mine

#define zeroc complex<double>(0,0)
 //#define zeroc 0.0;

 //#define ZERO 1.0E-8
#define ZERO VERY_SMALL


template <class T>
void Pivot(tmat<T> &Data, long RefRow, T &Determ, bool &DetEqualsZero)
{
	DetEqualsZero = true;
	long NewRow = RefRow;
	while (DetEqualsZero && (NewRow < Data.nrows())) {
		NewRow++;
		if (fabs(Data(NewRow, RefRow)) > ZERO) {
			for (long i = 1; i <= Data.nrows(); i++) {
				T temp = Data(NewRow, i);
				Data(NewRow, i) = Data(RefRow, i);
				Data(RefRow, i) = temp;
			}
			DetEqualsZero = false;
			Determ = -Determ;   // row swap adjustment to det
		}
	}

}// Pivot(Matrix<T> &Data, long RefRow, T &Determ, bool &DetEqualsZero)

template <class T>
T det(tmat<T> &Datain)
{
	//Datain.Garbage("Det");

	T Determ;
	Determ = 1.0;
	if (Datain.nrows() == Datain.ncols()) {

		long Dimen = Datain.nrows();
		tmat<T> Data(Dimen, Dimen);

		Data = Datain;
		T Coef;
		long Row, RefRow = 0;
		//enum bboolean DetEqualsZero = false;
		bool DetEqualsZero = false;

		while (!(DetEqualsZero) && (RefRow < Dimen - 1)) {
			RefRow++;
			if (fabs(Data(RefRow, RefRow)) < ZERO)
				Pivot(Data, RefRow, Determ, DetEqualsZero);
			if (!(DetEqualsZero))
				for (Row = RefRow + 1; Row <= Dimen; Row++)
					if (fabs(Data(Row, RefRow)) > ZERO) {
						Coef = -((T)Data(Row, RefRow)) /
							((T)Data(RefRow, RefRow));
						for (int i = 1; i <= Dimen; i++)
							Data(Row, i) = Data(Row, i) +
							(T)(Coef*((T)Data(RefRow, i)));
					}
			Determ *= Data(RefRow, RefRow);
		}
		//Determ = (DetEqualsZero) ? zeroc : Determ * Data(Dimen, Dimen);
		//if(DetEqualsZero) return zeroc.real();
		//else return Determ * Data(Dimen, Dimen);
		Determ = (DetEqualsZero) ? zeroc.real() : Determ * Data(Dimen, Dimen);
	}
	//else Datain.Nrerror("Det: Matrix is not square\n");
	else printf("Matrix is not square\n");
	return Determ;

}
#undef ZERO

// end determinant algorithms
/////////////////////////////////////////////////////////////////////

template<class T>
tmat<T> hconcat(tmat<T> a, tmat<T> b)
// horizontally concatenate matrix a with matrix b
{
	long ar = a.nrows(); long ac = a.ncols();
	long br = b.nrows(); long bc = b.ncols();

	if (ar != br) {
		cout << "hconcat: matrices have differing row numbers" << endl;
		return a;
	}
	long i, j;
	tmat<T> c(ar, ac + bc, (T)0);
	for (i = 1; i <= ar; i++) {
		for (j = 1; j <= ac + bc; j++) {
			if (j <= ac) c(i, j) = a(i, j);
			if (j > ac) c(i, j) = b(i, j - ac);
		}
	}
	return c;

}// hconcat(tmat<T> a, tmat<T> b)

template<class T>
tmat<T> hconcat(tvec<T> a, tvec<T> b)
// horizontally concatenate vector a with vector b
{
	long ar = a.nsize();
	long br = b.nsize();
	tmat<T> c(ar, 2, (T)0);

	if (ar != br) {
		cout << "hconcat: vectors have differing row numbers" << endl;
		return c;
	}
	long i, j;
	//tmat<T> c(ar, ac+bc, (T)0);
	for (i = 1; i <= ar; i++) {
		//for(j=1;j<=ac+bc;j++) {
		for (j = 1; j <= 2; j++) {
			if (j <= 1) c(i, j) = a(i);
			if (j > 1) c(i, j) = b(i);
		}
	}
	return c;

}// hconcat(tvec<T> a, tvec<T> b)

template<class T>
tmat<T> flop(tmat<T> a)
// flop matrix top to bottom
{
	long i, j;
	long m = a.nrows(); long n = a.ncols();
	tmat<T> t1; t1 = a; tmat<T> t2(m, n);
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++)
			t2(m - i + 1, j) = t1(i, j);
	}
	return t2;

}// flop(tmat<T> a)

template<class T>
tmat<T> tfill(long r, long c, T val)
// construct a r x c matrix filled with val
{
	tmat<T> a(r, c, val);
	return a;

}// tfill_(long r, long c, T val)

template<class T>
tmat<T> ident(long r, T dum)
// construct a r x r identity matrix
{
	tmat<T> a(r, r, (T)0);
	for (long i = 1; i <= r; i++) a(i, i) = (T)1;
	return a;

}// ident(long r, T dum)

template<class T>
T diagprod(tmat<T> a)
// returns the diagonal product of matrix a
{
	T dp = 1;
	for (long i = 1; i <= a.nrows(); i++)   // wasteful algo !!
		for (long j = 1; j <= a.ncols(); j++)
			if (i == j) dp *= a(i, j);
	return dp;

}// diagprod(tmat<T> a)

template<class T>
void delcol(tmat<T> &a, long c)
// delete by reference a selected matrix column
{
	long ar = a.nrows(); long ac = a.ncols();
	if (c <= 0 || c > ac) return; // invalid col index
	tmat<T> s, s1, s2;
	if (c == 1) { s = submatrix(a, 1, ar, 2, ac); goto quit; }
	if (c == ac) { s = submatrix(a, 1, ar, 1, ac - 1); goto quit; }
	s1 = submatrix(a, 1, ar, 1, c - 1);
	s2 = submatrix(a, 1, ar, c + 1, ac);
	s = hconcat(s1, s2);
quit: a = s;

}// delcol(tmat<T> a, long n)a

template <class T>
T perm(tmat<T> a)
// Pliam's algorithm for calculating the permanent of a 
// real square matrix
{
	long i, n;
	T prm = 0;
	n = a.ncols();		// ?? rows might be better
	tmat<T> s, o;
	o = hconcat(a, a);	// concat for n easy diagonal products
	s = flop(o);			// save flopped version 

	for (i = 1; i <= n; i++) {
		prm += diagprod(o);
		delcol(o, 1);
		prm += diagprod(s);
		delcol(s, 1);
	}

	return prm;

}// Perm(tmat<T> a)

 // recast matrix type a type b
template <class T1, class T2>
tmat<T2> recast(tmat<T1> a, tmat<T2> b)
{
	b.resize(a.nrows(), a.ncols());
	for (long i = 1; i <= a.nrows(); i++) {
		for (long j = 1; j <= a.ncols(); j++) {
			b(i, j) = (T2)a(i, j);
		}
	}

	return b;

}// recast(tmat<T1>)

 // vector outer (cross) product
template <class T>
tmat<T> outprod(const tvec<T> &a, const tvec<T> &b)
{
	const int na = a.size();
	const int nb = b.size();
	tmat<T> c(na, nb); c = 0.0;
	if (na != nb) {
		printf("vectors do not conform for outer-product multiplication\n");
		return c;
	}
	tmat<T> cv(na, 1); for (int i = 1; i <= na; i++) { cv(i, 1) = a(i); }
	tmat<T> cc(1, na); for (int i = 1; i <= na; i++) { cc(1, i) = b(i); }
	c = cv * cc;
	return c;
}

// vector inner (dot) product
template <class T>
tmat<T> inprod(const tvec<T> &a, const tvec<T> &b)
{
	const int na = a.size();
	const int nb = b.size();
	tmat<T> c(na, nb); c = 0.0;
	if (na != nb) {
		printf("vectors do not conform for inner-product multiplication\n");
		return c;
	}
	tmat<T> cv(1, na); for (int i = 1; i <= na; i++) { cv(1, i) = a(i); }
	tmat<T> cc(na, 1); for (int i = 1; i <= na; i++) { cc(i, 1) = b(i); }
	c = cv * cc;
	return c;
}

#endif // _TMAT_

//////////////////////////////////////////////////////////////////////
// PliaTech 2010


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

