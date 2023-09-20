#include <gtest/gtest.h>
#include "tensor.hpp"

TEST(Tensor, Instantiation) {
	int p[3] = {1, 2, 3};
	Tensor t(p, 3);
	ASSERT_EQ(t.items, 6);
}

TEST(Tensor, getItems){
	int p[3] = {1, 2, 3};
	Tensor t(p, 3);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 0, 0}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 1, 0}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 0, 1}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 1, 1}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 0, 2}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 1, 2}), 0);

	tnsrf::randomize(&t);

	ASSERT_NE(tnsrf::getItem(&t, {0, 0, 0}), 0);

	Tensor c(p, 3);

	tnsrf::copy(&c, &t);

	ASSERT_EQ(tnsrf::getItem(&t, {0, 0, 0}), tnsrf::getItem(&c, {0, 0, 0}));
	ASSERT_EQ(tnsrf::getItem(&t, {0, 1, 0}), tnsrf::getItem(&c, {0, 1, 0}));
	ASSERT_EQ(tnsrf::getItem(&t, {0, 0, 1}), tnsrf::getItem(&c, {0, 0, 1}));
	ASSERT_EQ(tnsrf::getItem(&t, {0, 1, 1}), tnsrf::getItem(&c, {0, 1, 1}));
	ASSERT_EQ(tnsrf::getItem(&t, {0, 0, 2}), tnsrf::getItem(&c, {0, 0, 2}));
	ASSERT_EQ(tnsrf::getItem(&t, {0, 1, 2}), tnsrf::getItem(&c, {0, 1, 2}));

	tnsrf::clear(&t);

	ASSERT_EQ(tnsrf::getItem(&t, {0, 0, 0}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 1, 0}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 0, 1}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 1, 1}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 0, 2}), 0);
	ASSERT_EQ(tnsrf::getItem(&t, {0, 1, 2}), 0);
}

TEST(Tensor, setItem){
	int ad[2] = {2, 2};
	Tensor a(ad, 2);


	tnsrf::setItem(&a, {0, 0}, 1);
	tnsrf::setItem(&a, {0, 1}, 1);
	tnsrf::setItem(&a, {1, 0}, 1);
	tnsrf::setItem(&a, {1, 1}, 1);

	EXPECT_EQ(tnsrf::total(&a), 4);

	int bd[1] = {6};
	Tensor b(bd, 1);

	tnsrf::setItem(&b, {0}, 1);
	tnsrf::setItem(&b, {1}, 1);
	tnsrf::setItem(&b, {2}, 1);
	tnsrf::setItem(&b, {3}, 1);

	EXPECT_EQ(tnsrf::total(&b), 4);

}

TEST(Tensor, Equality){
	int bd[6] = {1, 5, 2, 7, 2, 3};
	int ad[5] = {5, 2, 5, 2, 1};
	Tensor b(bd, 6);
	Tensor a(ad, 5);
	Tensor bcopy(bd, 6);	

	tnsrf::randomize(&b);
	tnsrf::copy(&bcopy, &b);

	EXPECT_FALSE(tnsrf::tensorEqual(&a, &b));
	EXPECT_TRUE(tnsrf::tensorEqual(&bcopy, &b));
}

TEST(Tensor, Reshape){
	int ad[3] = {1, 2, 3};
	Tensor a(ad, 3);
	
	int nd[3] = {3, 3, 3};
	tnsrf::reshape(&a, nd, 3);

	EXPECT_EQ(a.items, 27);

	tnsrf::setItem(&a, {2, 2, 2}, 10);
	EXPECT_EQ(tnsrf::getItem(&a, {2, 2, 2}), 10);
}

TEST(Tensor, Addition){
	int p[4] = {3, 3, 3, 3};
	Tensor a(p, 4);
	Tensor b(p, 4);
	Tensor d(p, 4);
	tnsrf::randomize(&a);
	tnsrf::add(&d, &a, &b);
	ASSERT_TRUE(tnsrf::tensorEqual(&d, &a));

	tnsrf::randomize(&b);
	tnsrf::add(&d, &a, &b);
	for(int i=0; i<a.items; i++){
		ASSERT_EQ((d.start)[i], (a.start)[i] + (b.start)[i]);
	}
}

TEST(Tensor, Subtraction){
	int p[4] = {3, 3, 3, 3};
	Tensor a(p, 4);
	Tensor b(p, 4);
	Tensor d(p, 4);

	tnsrf::randomize(&a);
	tnsrf::subtract(&d, &a, &b);

	EXPECT_TRUE(tnsrf::tensorEqual(&a, &d));

	tnsrf::randomize(&b);
	tnsrf::subtract(&d, &a, &b);

	for(int i=0; i<a.items; i++){
		ASSERT_EQ((d.start)[i], (a.start)[i] - (b.start)[i]);
	}
}

TEST(Tensor, Scaling){

	int ad[4] = {23, 4, 66, 2};
	Tensor a(ad, 4);
	Tensor b(ad, 4);

	tnsrf::randomize(&a);
	tnsrf::copy(&b, &a);
	tnsrf::scale(&b, 2.0);

	for(int i=0; i<b.items; i++){
		ASSERT_EQ((b.start)[i], 2 * (a.start)[i]);
	}
	
}

TEST(Tensor, Hproduct){

	int ad[4] = {23, 4, 66, 2};
	Tensor a(ad, 4);
	Tensor b(ad, 4);
	Tensor d(ad, 4);
	

	tnsrf::randomize(&a);
	tnsrf::randomize(&b);
	tnsrf::hproduct(&d, &a, &b);

	for(int i=0; i<b.items; i++){
		ASSERT_EQ((d.start)[i], (b.start)[i] * (a.start)[i]);
	}
}

TEST(Tensor, Total){
	int ad[5] = {1, 4, 2, 6, 4};
	Tensor a(ad, 5);

	ASSERT_EQ(tnsrf::total(&a), 0);
	
	tnsrf::randomize(&a);
	dataT to = tnsrf::total(&a);
	dataT top = 0;
	for(int i=0; i<a.items; i++){
		top += (a.start)[i];	
	}
	ASSERT_EQ(to, top);
}

TEST(Tensor, DotProduct){
	
	int ad[2] = {2, 2};
	Tensor a(ad, 2);
	Tensor b(ad, 2);
	Tensor c(ad, 2);

	tnsrf::randomize(&a);
	
	tnsrf::dot2d(&c, &a, &b);

	ASSERT_EQ(tnsrf::total(&c), 0);
	tnsrf::setItem(&b, {0, 0}, 1);
	tnsrf::setItem(&b, {1, 1}, 1);
	tnsrf::dot2d(&c, &a, &b);
	ASSERT_TRUE(tnsrf::tensorEqual(&c, &a));
}

TEST(Tensor, Tranpose){

	int ad[2] = {2, 4};
	int bd[2] = {4, 2};
	int cd[2] = {2, 4};

	Tensor a(ad, 2);
	Tensor b(bd, 2);
	Tensor c(cd, 2);

	tnsrf::randomize(&a);
	tnsrf::transpose2d(&b, &a);
	ASSERT_EQ(tnsrf::total(&a), tnsrf::total(&b));

	tnsrf::transpose2d(&c, &b);
	ASSERT_TRUE(tnsrf::tensorEqual(&c, &a));
}


