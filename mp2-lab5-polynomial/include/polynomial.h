#pragma once

#include <iostream>
#include <cmath>

using namespace std;

#include "list.h"
#include "monom.h"

class Polinom : public List<Monom>
{
public:
	Polinom(Monom* monoms = nullptr, int km = 0);  //monoms - массив мономов
										           // km - количество мономов в полиноме

	void SimilarTerms();           //приведение подобных
	void Insert(const Monom& q);   //вставка и приведение подобных

	bool operator == (const Polinom& q) const;

	const Polinom& operator = (const Polinom& q);
	const Polinom operator + (const Polinom& q) const;
	const Polinom operator - (const Polinom& q) const;
	Polinom& operator += (const Polinom& q); 
	Polinom& operator *= (const Polinom& q); 
	Polinom operator * (double d) const; 
	Polinom operator * (const Monom& m) const; 
	Polinom operator * (const Polinom& q) const;
	double ValueinPoint(double val1, double val2, double val3);

	friend istream& operator >> (istream& in, Polinom& p);
	friend ostream& operator << (ostream& os, const Polinom& p);

};


Polinom::Polinom(Monom* monoms, int km) : List<Monom>()
{
	Node<Monom>* curr = pHead;
	for (int i = 0; i < km; i++) {
		if (monoms[i].GetCoeff() != 0) {  
			List<Monom>::Insert(monoms[i]);
		}
	}
}

void Polinom::SimilarTerms()
{
	Node<Monom>* prev = pHead->pNext;
	Node<Monom>* curr = prev->pNext;

	while (curr != pHead) {

		if (prev->data.GetCoeff() == 0) {   
			Delete(prev);
			prev = prev->pNext;
			curr = curr->pNext;
		}
		else if ((prev->data).GetIndex() == (curr->data).GetIndex()) {
			prev->data += curr->data;
			prev->pNext = curr->pNext;
			curr = prev->pNext;
		}
		else {
			prev = prev->pNext;
			curr = curr->pNext;
		}

	}

	// проверяем на равенство нулю последний моном
	if (prev->data.GetCoeff() == 0) { 
		Delete(prev);
	}
}

void Polinom::Insert(const Monom& q)
{
	(*this).List<Monom>::Insert(q);
	(*this).SimilarTerms();
}

bool Polinom::operator == (const Polinom& q) const
{
	if (GetLength() != q.GetLength()) {
		return false;
	}

	Node<Monom>* curr1 = pHead->pNext;
	Node<Monom>* curr2 = (q.pHead)->pNext;

	while (curr1 != pHead) {
		if (curr1->data != curr2->data) {
			return false;
		}
		curr1 = curr1->pNext;
		curr2 = curr2->pNext;
	}

	return true;
}

const Polinom& Polinom::operator = (const Polinom& q)
{
	if (this != &q) {
		Node<Monom>* pCurr = pHead;        
		Node<Monom>* walk = q.GetFirst();  // указатель, которым идём по полиному q
		while (walk != q.GetHead()) {
			Node<Monom>* tlink = new Node<Monom>(walk->data);
			pCurr->pNext = tlink;
			pCurr = tlink;
			walk = walk->pNext;
		}
		pCurr->pNext = pHead;
	}
	return *this;
}

const Polinom Polinom::operator + (const Polinom& q) const
{
	Polinom res = (*this);
	res.Join(q);
	res.SimilarTerms();
	return res;
}

Polinom& Polinom::operator += (const Polinom& q)
{
	(*this) = (*this) + q;
	return (*this);
}

Polinom Polinom::operator * (double d) const
{
	Polinom res(*this);
	Node<Monom>* curr = res.pHead->pNext;
	while (curr != res.pHead) {
		curr->data = curr->data * d;
		curr = curr->pNext;
	}
	res.SimilarTerms();
	return res;
}

const Polinom Polinom::operator - (const Polinom& q) const
{
	Polinom res;
	res = (*this) + ((q) * (-1.0));
	return res;
}

Polinom Polinom::operator * (const Monom & m) const
{
	Polinom res(*this);
	Node<Monom>* curr = (res.pHead)->pNext;
	while (curr != res.pHead) {
		curr->data = (curr->data) * m;
		curr = curr->pNext;
	}
	res.SimilarTerms();
	return res;
}

Polinom& Polinom::operator *= (const Polinom & q)
{
	Polinom temp;
	Node<Monom>* curr2 = (q.pHead)->pNext;
	while (curr2 != q.pHead) {
		temp += (*this) * curr2->data;
		curr2 = curr2->pNext;
	}
	(*this) = temp;
	SimilarTerms();
	return *this;
}

Polinom Polinom::operator * (const Polinom & q) const
{
	Polinom res(*this);
	res *= q;
	res.SimilarTerms();
	return res;
}

double Polinom::ValueinPoint(double val1, double val2, double val3)
{
	Node<Monom>* act = pHead->pNext;
	double res = 0.0;

	while (act != pHead) {
		double curr = 1.0;
		int degree = (act->data).GetIndex();
		int z = degree % 10;
		degree /= 10;
		int y = degree % 10;
		degree /= 10;
		int x = degree;
		curr *= (act->data).GetCoeff();
		curr *= pow(val1, x);
		curr *= pow(val2, y);
		curr *= pow(val3, z);
		res += curr;
		act = act->pNext;
	}
	return res;
}

istream& operator >> (istream & is, Polinom & p)
{
	int km;
	is >> km;
	for (int i = 0; i < km; i++) {
		Monom m;
		is >> m;
		p.Insert(m);
	}
	p.SimilarTerms();
	return is;
}

//ostream& operator << (ostream & os, const Polinom & p)
//{
//	if (p.IsEmpty()) {
//		os << "0";
//		return os;
//	}
//	int length = p.GetLength();
//	Node<Monom>* curr = p.GetFirst();
//	os << curr->GetData();
//	curr = curr->GetNext();
//	for (int i = 1; i < length; i++) {
//		if (curr->GetData() > 0)
//			cout << "+";
//		os << curr->GetData()<< endl;
//		curr = curr->GetNext();
//	}
//	return os;
//}

ostream& operator << (ostream& os, const Polinom& p)
{
	if (p.IsEmpty()) {
		os << "0";
		return os;
	}
	int length = p.GetLength();
	Node<Monom>* curr = p.GetFirst();
	for (int i = 0; i < length; i++) {
		os << curr->GetData() << endl;
		curr = curr->GetNext();
	}
	return os;
}

