#include <algorithm>
#include <cmath>
#include <string>

#define interface struct

interface StringMatcher {
	virtual ~StringMatcher() = default;
	virtual int CalculateScore(const std::string& a, const std::string& b) const = 0;
};

class LengthSimilarityChecker : public StringMatcher {
public:
	int CalculateScore(const std::string& a, const std::string& b) const override {
		size_t longLength = std::max(a.length(), b.length());
		size_t shortLength = std::min(a.length(), b.length());

		if (longLength == 0) {
			return 60;
		}
		if (longLength >= shortLength * 2) {
			return 0;
		}

		double gap = static_cast<double>(longLength - shortLength);
		double score = (1.0 - gap / longLength) * 60.0;
		return static_cast<int>(std::round(score));
	};
};