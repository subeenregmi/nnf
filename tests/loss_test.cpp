#include <gtest/gtest.h>
#include "loss.hpp"

dataT round(dataT val){
	return floor(val*1000) / 1000.0d;
}

TEST(LossFunctions, MeanSquaredError){
	ASSERT_EQ(tnsrf_loss::mse(34, 37), 9);
	ASSERT_EQ(tnsrf_loss::mse(1, 1), 0);
	ASSERT_EQ(tnsrf_loss::mse(5, 4), 1);
	ASSERT_EQ(tnsrf_loss::mse(0.3, 2.145), 3.404025);
	ASSERT_EQ(tnsrf_loss::mse(5000, 5001), 1);
}

TEST(LossFunctions, MeanSquaredErrorGrad){
	ASSERT_EQ(tnsrf_loss::mseD(34, 37), -6);
	ASSERT_EQ(tnsrf_loss::mseD(1, 1), 0);
	ASSERT_EQ(tnsrf_loss::mseD(5, 4), 2);
	ASSERT_EQ(tnsrf_loss::mseD(0.3, 2.145), -3.69);
	ASSERT_EQ(tnsrf_loss::mseD(5000, 5001), -2);
}

TEST(LossFunctions, CategoricalLoss){
	ASSERT_EQ(round(tnsrf_loss::cel(0.4, 0.6)), 0.754);
	ASSERT_EQ(round(tnsrf_loss::cel(0.5, 0.5)), 0.693);
	ASSERT_EQ(round(tnsrf_loss::cel(0.231, 0.3145)), 0.640);
	ASSERT_EQ(round(tnsrf_loss::cel(0.74, 0.39)), 0.939);
	ASSERT_EQ(round(tnsrf_loss::cel(0.1, 0.1)), 0.325);
}

TEST(LossFunction, CategoricalLossGrad){
	ASSERT_EQ(round(tnsrf_loss::celD(0.4, 0.6)), -0.834);
	ASSERT_EQ(round(tnsrf_loss::celD(0.5, 0.5)), 0.000);
	ASSERT_EQ(round(tnsrf_loss::celD(0.231, 0.3145)), -0.471);
	ASSERT_EQ(round(tnsrf_loss::celD(0.74, 0.39)), 1.819);
	ASSERT_EQ(round(tnsrf_loss::celD(0.1, 0.1)), 0);
}
