#include <gtest/gtest.h>
#include "activations.hpp"

TEST(Activations, Linear){
	ASSERT_EQ(tnsrf_act::linear(4), 4);
	ASSERT_EQ(tnsrf_act::linear(0), 0);
	ASSERT_EQ(tnsrf_act::linear(-1.2), -1.2);
	ASSERT_EQ(tnsrf_act::linear(333), 333);
	ASSERT_EQ(tnsrf_act::linear(0.004), 0.004);
}

TEST(Activations, LinearD){
	ASSERT_EQ(tnsrf_act::linearD(4), 1);
	ASSERT_EQ(tnsrf_act::linearD(2), 1);
	ASSERT_EQ(tnsrf_act::linearD(-1.5),1);
	ASSERT_EQ(tnsrf_act::linearD(33300321), 1);
	ASSERT_EQ(tnsrf_act::linearD(0.2324), 1);
}

TEST(Activations, Sigmoid){
	ASSERT_EQ(tnsrf_act::sigmoid(0), 0.5);
	ASSERT_EQ(tnsrf_act::sigmoid(1), 1/(1+exp(-1)));
}
