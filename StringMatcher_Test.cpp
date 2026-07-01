#include "gmock/gmock.h"
#include "StringMatcher.cpp"

class LengthSimilarityCheckerTest : public testing::Test {
protected:
	LengthSimilarityChecker checker;

	void ExpectScore(const std::string& a, const std::string& b, int expectedScore) {
		EXPECT_EQ(expectedScore, checker.CalculateScore(a, b));
	}

	void ExpectInvalidStringException(const std::string& a, const std::string& b) {
		EXPECT_THROW(checker.CalculateScore(a, b), InvalidStringException);
	}
};

TEST_F(LengthSimilarityCheckerTest, SameLength_ReturnsFullScore) {
	ExpectScore("ASD", "DSA", 60);
}

TEST_F(LengthSimilarityCheckerTest, LengthDoublesOrMore_ReturnsZero) {
	ExpectScore("A", "BB", 0);
}

TEST_F(LengthSimilarityCheckerTest, PartialGap_ReturnsPartialScore) {
	ExpectScore("AAABB", "BAA", 36);
}

TEST_F(LengthSimilarityCheckerTest, SmallPartialGap_ReturnsPartialScore) {
	ExpectScore("AA", "AAE", 40);
}

TEST_F(LengthSimilarityCheckerTest, BothEmpty_ThrowsInvalidStringException) {
	ExpectInvalidStringException("", "");
}

TEST_F(LengthSimilarityCheckerTest, NonUppercaseInput_ThrowsInvalidStringException) {
	ExpectInvalidStringException("asd", "DSA");
	ExpectInvalidStringException("A1D", "DSA");
}
