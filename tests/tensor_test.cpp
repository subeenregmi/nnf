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

}
