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

TEST(Activations, Relu){
	ASSERT_EQ(tnsrf_act::relu(4.5), 4.5);
	ASSERT_EQ(tnsrf_act::relu(0), 0);
	ASSERT_EQ(tnsrf_act::relu(-1.2), 0);
	ASSERT_EQ(tnsrf_act::relu(23.490), 23.490);
	ASSERT_EQ(tnsrf_act::relu(0.002), 0.002);
}

TEST(Activations, ReluD){
	ASSERT_EQ(tnsrf_act::reluD(5.3), 1);
	ASSERT_EQ(tnsrf_act::reluD(0), 0);
	ASSERT_EQ(tnsrf_act::reluD(-1.2), 0);
	ASSERT_EQ(tnsrf_act::reluD(94.5), 1);
	ASSERT_EQ(tnsrf_act::reluD(0.5), 1);
}

TEST(Activations, Tanh){
	ASSERT_EQ(round(tnsrf_act::Ntanh(5)), 0.999);
	ASSERT_EQ(round(tnsrf_act::Ntanh(1)), 0.761);
	ASSERT_EQ(round(tnsrf_act::Ntanh(-0.2)), -0.198);
	ASSERT_EQ(round(tnsrf_act::Ntanh(0.1)), 0.099);
	ASSERT_EQ(round(tnsrf_act::Ntanh(-6)), -1);
}

TEST(Activations, TanhD){
	ASSERT_EQ(round(tnsrf_act::NtanhD(1)), 0.419);
	ASSERT_EQ(round(tnsrf_act::NtanhD(0)), 1);
	ASSERT_EQ(round(tnsrf_act::NtanhD(0.2)), 0.961);
	ASSERT_EQ(round(tnsrf_act::NtanhD(0.1)), 0.990);
	ASSERT_EQ(round(tnsrf_act::NtanhD(-2.3)), 0.039);
}

TEST(Activations, LeakyRelu){
	ASSERT_EQ(tnsrf_act::leakyrelu(1), 1);
	ASSERT_EQ(tnsrf_act::leakyrelu(0), 0);
	ASSERT_EQ(tnsrf_act::leakyrelu(743), 743);
	ASSERT_EQ(tnsrf_act::leakyrelu(0.33), 0.33);
	ASSERT_EQ(tnsrf_act::leakyrelu(-5), -0.5);
}

TEST(Activations, LeakyReluD){
	ASSERT_EQ(tnsrf_act::leakyreluD(1), 1);
	ASSERT_EQ(tnsrf_act::leakyreluD(0), 0.1);
	ASSERT_EQ(tnsrf_act::leakyreluD(743), 1);
	ASSERT_EQ(tnsrf_act::leakyreluD(-0.33), 0.1);
	ASSERT_EQ(tnsrf_act::leakyreluD(-2.6), 0.1);
}

TEST(Activations, Elu){
	ASSERT_EQ(tnsrf_act::elu(1), 1);
	ASSERT_EQ(tnsrf_act::elu(0), 0);
	ASSERT_EQ(tnsrf_act::elu(42), 42);
	ASSERT_EQ(round(tnsrf_act::elu(-3.9)), -0.98);
	ASSERT_EQ(round(tnsrf_act::elu(-0.432)), -0.351);
}

TEST(Activations, EluD){
	ASSERT_EQ(tnsrf_act::eluD(1), 1);
	ASSERT_EQ(tnsrf_act::eluD(0), 0);
	ASSERT_EQ(tnsrf_act::eluD(42), 1);
	ASSERT_EQ(round(tnsrf_act::eluD(-0.55)), -0.424);
	ASSERT_EQ(round(tnsrf_act::eluD(-0.81)), -0.556);
}
