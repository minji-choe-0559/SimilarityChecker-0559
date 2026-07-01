#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#define interface struct

class InvalidStringException : public std::invalid_argument {
public:
	explicit InvalidStringException(const std::string& message) : std::invalid_argument(message) {}
};

interface StringMatcher {
	virtual ~StringMatcher() = default;
	virtual int CalculateScore(const std::string& a, const std::string& b) const = 0;

protected:
	// Similarity rules are only defined for uppercase A-Z input.
	static void ValidateUppercaseAlphabet(const std::string& s) {
		for (char c : s) {
			if (c < 'A' || c > 'Z') {
				throw InvalidStringException("Input must contain only uppercase alphabet characters");
			}
		}
	}
};

class LengthSimilarityChecker : public StringMatcher {
public:
	int CalculateScore(const std::string& a, const std::string& b) const override {
		ValidateUppercaseAlphabet(a);
		ValidateUppercaseAlphabet(b);

		size_t longLength = std::max(a.length(), b.length());
		size_t shortLength = std::min(a.length(), b.length());

		if (longLength == 0) {
			throw InvalidStringException("Both strings are empty");
		}
		if (longLength >= shortLength * 2) {
			return 0;
		}

		double gap = static_cast<double>(longLength - shortLength);
		double score = (1.0 - gap / longLength) * 60.0;
		return static_cast<int>(std::round(score));
	};
};