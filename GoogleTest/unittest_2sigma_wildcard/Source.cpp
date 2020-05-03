// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(testMath, myCubeTest)
{
	EXPECT_EQ(1000, 1);
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS(); 
}