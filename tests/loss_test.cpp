#include <gtest/gtest.h>
#include "loss.hpp"

TEST(LossFunctions, MeanSquaredError){
	ASSERT_EQ(mse(34, 37), 9);
	ASSERT_EQ(mse(1, 1), 0);
	ASSERT_EQ(mse(5, 4), 1);
	ASSERT_EQ(mse(0.3, 2.145), 3.404025);
	ASSERT_EQ(mse(5000, 5001), 1);
}

TEST(LossFunctions, MeanSquaredErrorGrad){
	ASSERT_EQ(mseD(34, 37), -6);
	ASSERT_EQ(mseD(1, 1), 0);
	ASSERT_EQ(mseD(5, 4), 2);
	ASSERT_EQ(mseD(0.3, 2.145), -3.69);
	ASSERT_EQ(mseD(5000, 5001), -2);
}
