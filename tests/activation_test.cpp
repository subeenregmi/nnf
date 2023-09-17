#include <gtest/gtest.h>
#include "activations.hpp"

dataT round(dataT val){
	return floor(val*1000) / 1000.0d;
}	

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
	ASSERT_EQ(round(tnsrf_act::sigmoid(0)), 0.5);
	ASSERT_EQ(round(tnsrf_act::sigmoid(1)), 0.731);
	ASSERT_EQ(round(tnsrf_act::sigmoid(0.22)), 0.554);
	ASSERT_EQ(round(tnsrf_act::sigmoid(-2)), 0.119);
	ASSERT_EQ(round(tnsrf_act::sigmoid(-0.449)), 0.389);
}

TEST(Activations, SigmoidD){
	ASSERT_EQ(round(tnsrf_act::sigmoidD(0)), 0.25);
	ASSERT_EQ(round(tnsrf_act::sigmoidD(1)), 0.196);
	ASSERT_EQ(round(tnsrf_act::sigmoidD(0.22)), 0.246);
	ASSERT_EQ(round(tnsrf_act::sigmoidD(-2)), 0.104);
	ASSERT_EQ(round(tnsrf_act::sigmoidD(-0.449)), 0.237);
}
