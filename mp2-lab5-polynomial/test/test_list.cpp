#include <gtest.h>
#include "list.h"
#include "polynomial.h"


TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int> list);
}

TEST(List, can_create_copied_list)
{
	List<int> list;
	list.Insert(5);
	List<int> copy(list);

	EXPECT_EQ(list.GetFirst()->GetData(), copy.GetFirst()->GetData());
}

TEST(List, can_insert_node_in_list)
{
	List<int> list;
	const int c = 9;

	list.Insert(c);

	EXPECT_EQ(c, (list.GetFirst())->GetData());
}

TEST(List, can_delete_node)
{
	const int c = -2;
	List<int> list;

	list.Insert(c);
	list.Insert(-2);
	list.Insert(9);

	list.Delete(list.GetFirst()->GetNext());

	EXPECT_EQ(c, (list.GetFirst()->GetNext())->GetData());
}

TEST(List, check_length_of_list_after_join) //проверили длину списка после слияния
{
	List<int> list1, list2;
	const int res = 3;

	list1.Insert(1); 
	list1.Insert(2); 
	list2.Insert(3); 

	list1.Join(list2);

	EXPECT_EQ(res, list1.GetLength());
}

TEST(List, check_list_is_sorted_after_join)
{
	List<int> list1, list2;
	const bool res = true;

	list1.Insert(5); list1.Insert(0);
	list2.Insert(3);

	list1.Join(list2);

	EXPECT_EQ(res, list1.IsSort());
}




TEST(Monom, can_create_monom)
{
	ASSERT_NO_THROW(Monom m(9.0, 123));
}

TEST(Monom, cant_create_monom_with_degree_greater_than_nine)
{
	ASSERT_ANY_THROW(Monom m(1.0, 2312));
}

TEST(Monom, can_add_monoms_with_equal_index)
{
	const int index = 123;
	const double c1 = 1.0, c2 = 2.0, c3 = c1 + c2;
	Monom a(c1, index), b(c2, index), res(c3, index);

	EXPECT_EQ(res, a + b);
}

TEST(Monom, throw_when_add_monoms_with_different_index)
{
	Monom a(1.0, 123), b(1.0, 321);

	ASSERT_ANY_THROW(a + b);
}

TEST(Monom, can_multiply_scalar_by_monom)
{
	const int index = 111;
	const double coeff = 9.0, d = 3.9;
	Monom a(coeff, index), expVal(coeff * d, index);

	EXPECT_EQ(expVal, a * d);
}

TEST(Monom, can_multiply_monoms)
{
	int index1 = 123, index2 = 321, index3 = index1 + index2;
	double coeff1 = 1.0, coeff2 = 1.02, coeff3 = coeff1 * coeff2;
	Monom m1(coeff1, index1), m2(coeff2, index2), res(coeff3, index3);

	EXPECT_EQ(res, m1 * m2);
}

TEST(Monom, throw_when_result_of_mupltiply_has_incorrect_degree)
{
	int index1 = 109, index2 = 203;
	Monom a(1.0, index1), b(2.0, index2);

	ASSERT_ANY_THROW(a * b);
}

TEST(Polinom, can_create_polinom)
{
	const int km = 3;
	Monom* monoms = new Monom[3];
	Monom m1(1.0, 123), m2(2.0, 321), m3(3.1, 423);
	monoms[0] = m1; monoms[1] = m2; monoms[2] = m3;
	ASSERT_NO_THROW(Polinom p(monoms, km));
}

TEST(Polinom, can_reduce_a_polinom_to_standart_view)
{
	Monom m0(5.3, 123);
	Monom m1(4.3, 123), m2(1.0, 123);

	Monom* monoms = new Monom[2];
	Monom* resMon = new Monom(m0);

	monoms[0] = m1; monoms[1] = m2;
	Polinom a(monoms, 2), resPolinom(resMon, 1);

	a.SimilarTerms();

	EXPECT_EQ(resPolinom, a);
}

TEST(Polinom, polinom_is_reduced_after_insert)
{
	Polinom a, resPolinom;
	Monom m1(1.0, 123), m2(2.0, 123), resMon(3.0, 123);

	a.Insert(m1); a.Insert(m2);
	resPolinom.Insert(resMon);

	EXPECT_EQ(resPolinom, a);
}

TEST(Polinom, can_add_polinoms)
{
	Monom a1(1.0, 123), a2(2.0, 321);
	Monom b1(3.1, 456), b2(4.0, 461), b3(9.3, 346);
	Polinom a, b, resPolinom;

	a.Insert(a1); a.Insert(a2);
	b.Insert(b1); b.Insert(b2); b.Insert(b3);

	resPolinom.Insert(a1); resPolinom.Insert(a2);
	resPolinom.Insert(b1); resPolinom.Insert(b2);
	resPolinom.Insert(b3);

	EXPECT_EQ(resPolinom, a + b);
}


TEST(Polinom, can_multiply_scalar_by_polinom)
{
	const double scalar = 2.0;
	Monom a1(1.0, 123), a2(-2.0, 321);
	Monom b1(2.0, 123), b2(-4.0, 321);

	Polinom a, resPolinom;

	a.Insert(a1); a.Insert(a2);
	resPolinom.Insert(b1); resPolinom.Insert(b2);

	EXPECT_EQ(resPolinom, a * scalar);
}


TEST(Polinom, can_multiply_monom_by_polinom)
{
	Monom m(2, 123);
	Monom a1(3.5, 123), a2(-1.5, 321);
	Monom c1(7.0, 246), c2(-3.0, 444);

	Polinom a, resPolinom;
	a.Insert(a1); a.Insert(a2);
	resPolinom.Insert(c1); resPolinom.Insert(c2);

	EXPECT_EQ(resPolinom, a * m);
}

TEST(Polinom, can_multiply_polinoms)
{
	Polinom p1;
	Monom a1(2.1, 321), a2(1.5, 123), a3(3.5, 123);
	p1.Insert(a1); p1.Insert(a2); p1.Insert(a3);

	Polinom p2;
	Monom b1(2.0, 210), b2(0.0, 789);
	p2.Insert(b1); p2.Insert(b2);

	Polinom resPolinom;
	Monom c1(4.2, 531), c2(10.0, 333);
	resPolinom.Insert(c1); resPolinom.Insert(c2);

	EXPECT_EQ(resPolinom, p1 * p2);
}


TEST(Polinom, result_of_addition_polinoms_does_not_contain_zero_monoms)
{
	Monom a1(1.0, 123), a2(2.0, 102);
	Monom b1(-1.0, 123), b2(4.0, 000), b3(9.9, 159);

	Polinom a, b, expPolinom;

	a.Insert(a1); a.Insert(a2);
	b.Insert(b1); b.Insert(b2); b.Insert(b3);
	expPolinom.Insert(a2); expPolinom.Insert(b2); expPolinom.Insert(b3);

	EXPECT_EQ(expPolinom, a + b);
}

TEST(Polinom, result_of_addition_polinoms_is_reduced)
{
	Monom a1(1.0, 123), a2(2.0, 102);
	Monom b1(8.9, 123), b2(4.0, 102), b3(8.4, 354);
	Monom c1(9.9, 123), c2(6.0, 102);

	Polinom a, b, resPolinom;

	a.Insert(a1); a.Insert(a2);
	b.Insert(b1); b.Insert(b2); b.Insert(b3);
	resPolinom.Insert(c1); resPolinom.Insert(c2);
	resPolinom.Insert(b3);

	EXPECT_EQ(resPolinom, a + b);
}