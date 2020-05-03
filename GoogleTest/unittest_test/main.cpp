#include "unittest_test.h"
#include "gtest/gtest.h"
#include "stdafx.h"

TEST(testMath, mathtest){
	EXPECT_EQ(1, 1); 
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv); 
	RUN_ALL_TESTS(); 
}