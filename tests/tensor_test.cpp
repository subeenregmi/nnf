#include <gtest/gtest.h>
#include "tensor.hpp"

// Demonstrate some basic assertions.
TEST(Tensor, Instantiation) {
	int p[3] = {1, 2, 3};
	Tensor t(p, 3);
	ASSERT_EQ(t.items, 6);
}

TEST(Tensor, Items){
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

