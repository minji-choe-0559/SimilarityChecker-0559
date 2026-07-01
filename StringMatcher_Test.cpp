#include "gmock/gmock.h"
#include "StringMatcher.cpp"

TEST(LengthSimilarityChecker, SameLength_ReturnsFullScore) {
	LengthSimilarityChecker checker;
	EXPECT_EQ(60, checker.CalculateScore("ASD", "DSA"));
}

TEST(LengthSimilarityChecker, LengthDoublesOrMore_ReturnsZero) {
	LengthSimilarityChecker checker;
	EXPECT_EQ(0, checker.CalculateScore("A", "BB"));
}

TEST(LengthSimilarityChecker, PartialGap_ReturnsPartialScore) {
	LengthSimilarityChecker checker;
	EXPECT_EQ(36, checker.CalculateScore("AAABB", "BAA"));
}

TEST(LengthSimilarityChecker, SmallPartialGap_ReturnsPartialScore) {
	LengthSimilarityChecker checker;
	EXPECT_EQ(40, checker.CalculateScore("AA", "AAE"));
}

TEST(LengthSimilarityChecker, BothEmpty_ThrowsInvalidStringException) {
	LengthSimilarityChecker checker;
	EXPECT_THROW(checker.CalculateScore("", ""), InvalidStringException);
}

TEST(LengthSimilarityChecker, NonUppercaseInput_ThrowsInvalidStringException) {
	LengthSimilarityChecker checker;
	EXPECT_THROW(checker.CalculateScore("asd", "DSA"), InvalidStringException);
	EXPECT_THROW(checker.CalculateScore("A1D", "DSA"), InvalidStringException);
}
