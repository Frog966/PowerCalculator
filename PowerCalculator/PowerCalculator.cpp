#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "Optimizations.h";

// Define the maximum length of the number.
#define MAX_LENGTH 500

int main() {
	using namespace std;
	using namespace chrono;
	using hrclock = high_resolution_clock;

	int base = 2;

	// Prompt the user for a power of two.
	int power = 0;
	std::cout << "Power of " << base << " to calculate: ";
	cin >> power;

	// Use this array to store the number.
	// Initialize the number with a value of 1.
	//int digits[MAX_LENGTH] = { 1 };
	vector<int> digits = { 1 };
	hrclock::time_point start = hrclock::now(); // Remember the start time.

	int carryOver = 0;

	//== Mid-Level Stuff? ==/
	// Iterate for each power of base specified.
	//for (int p = 0; p < power; ++p) {
	//	// Go through entire array to get sum
	//	for (int q = 0; q < digits.size(); ++q) {
	//		int temp1 = digits[q] * base + carryOver;

	//		digits[q] = temp1 % 10;
	//		carryOver = temp1 / 10; // Pass any number greater than 10 to next element. If temp1 < 10, returns 0 which resets carryOver

	//		if (temp1 > 10) {
	//			digits.push_back(0); // Add a new element after current if temp 1 > 10
	//		}
	//	}
	//}

	//== Senior-Level Stuff? ==/
	// Convert power to string for array functions
	std::string powerStr = to_string(power);

	// This loop should be doing this:
	// eg: power = 321 -> base^3 -> base^3^10 -> base^30 -> base^30 * base^2 -> base^32 -> base^320 -> base^320 * base^1
	// It uses the rules below:
	// 2^3^4 == 2^(3*4)
	// 2^3 * 2^4 == 2^(3+4)
	//! You can reduce the number of calculations by exponentially increasing the power (2^10 (^10) -> 2^10^10 (^100) -> 2^10^10^10 (^1000) ->  2^10^10^10^10 (^10000))
	//! Try not to exceed power 10 as you would need to rewrite the loop algorithm. 
	//! 9 is the highest number possible currently therefore ((element = 9) * 10) + (carryOver = 9) would only reach 99 maximum
	for (int i = 0; i < powerStr.size(); ++i) {
		int currPowerNum = (int)powerStr[i] - 48; // Convert powerStr char to int. I don't know how to convert

		// Performing calculations based on current power if currPowerNum > 0
		// eg. power = 321 -> power[0] = currPowerNum = 3 -> base^3
		if (currPowerNum > 0) {
			// Stores the answer for first for loop
			// Start with base^0
			vector<int> tempDigits = { 1 }; 

			for (int j = 0; j < currPowerNum; ++j) {
				for (int k = 0; k < tempDigits.size(); ++k) {
					int temp = tempDigits[k] * base + carryOver;

					tempDigits[k] = temp % 10;
					carryOver = temp / 10; // Pass any number greater than 10 to next element. If temp < 10, returns 0 which resets carryOver

					if (temp > 10) {
						tempDigits.push_back(0); // Add a new element after current if temp > 10
					}
				}
			}

			// Folowing the math rule: 2^3 * 2^4 == 2^(3+4)
			// Digits must start at base^0
			digits = multiplyDigits(digits, tempDigits);
		}

		// If not the last number of powerStr, do digits^10
		// Folowing the math rule: 2^3^4 == 2^(3*4)
		// eg. power = 321 -> power[0] = currPowerNum = 3 -> base^3 -> base^3^10 -> base^30
		if (i < powerStr.size() - 1) {
			digits = power10Digits(digits);
		}
	}

	// Take the end time and compute the time elapsed.
	hrclock::time_point stop = hrclock::now();
	auto elapsed = duration_cast<duration<double>>(stop - start);

	// Convert the digits to a string.
	string result;
	for (const auto digit : digits)
		result += char(digit + '0');

	// Reverse the resulting string and trim leading zeros.
	std::reverse(result.begin(), result.end());
	result = result.substr(result.find_first_not_of('0'));

	// Print the result and stats.
	std::cout << base << "^" << power << " is " << result << endl;
	std::cout << "The result is " << result.length() << " digits long." << endl;
	std::cout << "Time elapsed: " << fixed << elapsed.count() << " seconds." << endl;
}