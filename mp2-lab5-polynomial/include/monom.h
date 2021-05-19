#pragma once

#include <string>


class Monom
{
private:
	double coeff_;    //коэффициент монома
	int index_;       //набор степеней
	int sum_;         //свёртка степеней
public:
	Monom(double coeff = 0.0, int index = -1);
	Monom(const Monom& q);

	double GetCoeff();
	int GetIndex();
	int GetSum();

	void SetCoeff(double coeff);
	void SetIndex(int index);

	bool operator != (const Monom& q) const;
	bool operator == (const Monom& q) const;
	bool operator < (const Monom& q) const;
	bool operator > (const Monom& q) const;
	bool operator > (int c);

	const Monom& operator = (const Monom& q);
	Monom& operator += (const Monom& q);
	const Monom operator + (const Monom& q) const;
	Monom operator * (double d) const;
	Monom operator * (int i) const;
	Monom& operator -= (const Monom& q);
	const Monom operator - (const Monom& q) const;
	Monom& operator *= (const Monom& q);
	const Monom operator * (const Monom& q) const;

	friend ostream& operator << (ostream& os, const Monom& m);
	friend istream& operator >> (istream& is, Monom& m);

};



Monom::Monom(double coeff, int index)
{
	if ((index > 999) || (index < -1)) {
		throw "big degree";
	}
	coeff_ = coeff;
	index_ = index;
	sum_ = 0;
	while (index) {
		sum_ += index % 10;
		index /= 10;
	}
}

Monom::Monom(const Monom& q)
{
	coeff_ = q.coeff_;
	index_ = q.index_;
	sum_ = q.sum_;
}

double Monom::GetCoeff()
{
	return coeff_;
}

int Monom::GetIndex()
{
	return index_;
}

int Monom::GetSum()
{
	return sum_;
}

void Monom::SetCoeff(double coeff)
{
	coeff_ = coeff;
}

void Monom::SetIndex(int index)
{
	Monom tmp(coeff_, index);
	index_ = tmp.index_;
	sum_ = tmp.sum_;
}

bool Monom::operator == (const Monom& q) const
{
	return ((coeff_ == q.coeff_) && (index_ == q.index_) && (sum_ == q.sum_)); 
}

bool Monom::operator != (const Monom & q) const
{
	return !((*this) == q);
}

bool Monom::operator < (const Monom & q) const
{
	return index_ < q.index_;
}

bool Monom::operator > (const Monom & q) const
{
	return index_ > q.index_;
}

bool Monom::operator > (int c) 
{
	return coeff_ > c;
}

const Monom& Monom::operator = (const Monom & q)
{
	if (this != &q) {
		coeff_ = q.coeff_;
		index_ = q.index_;
		sum_ = q.sum_;
	}
	return *this;
}

Monom& Monom::operator += (const Monom & q)
{
	if (index_ != q.index_) {
		throw "different index in adding";
	}

	coeff_ += q.coeff_;
	return *this;
}

const Monom Monom::operator + (const Monom & q) const
{
	Monom res(*this);
	res += q;
	return res;
}

Monom Monom::operator * (double d) const
{
	Monom res(*this);
	res.coeff_ *= d;
	return res;
}

Monom Monom::operator * (int i) const
{
	Monom res(*this);
	res.coeff_ *= i;
	return res;
}

Monom& Monom::operator -= (const Monom & q)
{
	(*this) += q * (-1);

	return *this;
}

const Monom Monom::operator - (const Monom & q) const
{
	Monom res(*this);
	res -= q;
	return res;
}

Monom& Monom::operator *= (const Monom & q)
{
	*this = (*this) * q;
	return *this;
}

const Monom Monom::operator * (const Monom & q) const
{
	Monom res(coeff_ * q.coeff_, (index_ + q.index_));

	if (res.sum_ != (sum_ + q.sum_) && (res.coeff_ != 0)) {
		throw "big degree";         //превышение максимальной степени
	}
	return res;
}

istream& operator >> (istream & is, Monom & m)
{
	string s_coeff;
	is >> s_coeff;
	string s_index;
	is >> s_index;

	size_t pos = 0;
	double coeff = stod(s_coeff, &pos);
	int index = stoi(s_index, &pos);

	Monom s(coeff, index);
	m = s;

	return is;
}

ostream& operator << (ostream & os, const Monom & m)
{
	os << m.coeff_ ;
	int degree = m.index_;
	int z = degree % 10;
	degree /= 10;
	int y = degree % 10;
	degree /= 10;
	int x = degree;
	os << "x^" << x << "y^" << y << "z^" << z;
	return os;
} 

//ostream& operator << (ostream& os, const Monom& m)
//{
//	os << "(" << m.coeff_ << "," << m.index_ << ")";
//	return os;
//}