#include "Optimizations.h"

struct vectorComparer {
	std::vector<int> larger;
	std::vector<int> smaller;
};

vectorComparer compareIntVectorSizes(std::vector<int>& a, std::vector<int>& b) {
	vectorComparer temp;

	if (b.size() > a.size()) {
		temp.larger = b;
		temp.smaller = a;
	}
	else {
		temp.larger = a;
		temp.smaller = b;
	}

	return temp;
}

void resizeSmallerIntVectorToLargerIntVector(std::vector<int>& a, std::vector<int>& b) {
	if (a.size() > b.size()) {
		b.resize(a.size());
	}
	else if (a.size() < b.size()) {
		a.resize(b.size());
	}
}

std::vector<int> addDigits(std::vector<int> a, std::vector<int> b) {
	std::vector<int> sum;
	vectorComparer comparer = compareIntVectorSizes(a, b);

	sum.resize(comparer.larger.size()); // Redefine sum's size to larger vector's size

	int carryOver = 0;

	for (int i = 0; i < sum.size(); ++i) {
		sum[i] = carryOver;

		// If we're still within range of larger vector's size, add current larger vector's element into current sum element
		if (i < comparer.larger.size()) sum[i] += comparer.larger[i];

		// If we're still within range of smaller vector's size, add current smaller vector's element into current sum element
		if (i < comparer.smaller.size()) sum[i] += comparer.smaller[i];

		carryOver = sum[i] / 10; // Pass any number greater than 10 to next element
		sum[i] %= 10; // Current sum element only keeps the remainder of 10

		// If there is still carryOver and we've reached the end of sum vector, add a new element to sum
		if (carryOver > 0 && i == sum.size() - 1) {
			sum.push_back(0);
		}
	}

	return sum;
}

std::vector<int> multiplyDigits(std::vector<int> a, std::vector<int> b) {
	std::vector<int> product = { 0 };
	vectorComparer comparer = compareIntVectorSizes(a, b);

	product.resize(comparer.larger.size()); // Redefine product's size to larger vector's size

	// We cannot use regular multiplication as the "int" datatype will eventually run out of memory
	// Currently performing the ye olde "add a number to a number X number of time where X is the multiplier"
	for (int i = 0; i < comparer.smaller.size(); ++i) {
		std::vector<int> sum;
		int currMultiplier = comparer.smaller[i];

		if (currMultiplier > 0) {
			for (int j = 0; j < currMultiplier; ++j) {
				sum = addDigits(sum, comparer.larger);
			}

			sum.insert(sum.begin(), i, 0); // Add 0s to the start of sum to mimic multiplying by a factor of 10. (12*12 == 12*2 + 12*10)
			product = addDigits(sum, product);
		}
	}

	return product;
}

std::vector<int> power10Digits(std::vector<int> base) {
	std::vector<int> total = { 1 }; // Always start with 1 which is base^0

	for (int i = 0; i < 10; ++i) {
		total = multiplyDigits(base, total);
	}

	return total;
}