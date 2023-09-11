#include <gtest/gtest.h>
#include "tensor.hpp"

// Demonstrate some basic assertions.
TEST(TensorTesting, Instantiation) {
	int p[3] = {1, 2, 3};
	Tensor t(p, 3);

	ASSERT_EQ(t.items, 6);
}
