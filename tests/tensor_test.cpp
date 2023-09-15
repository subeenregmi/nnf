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
