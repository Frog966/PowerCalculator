#include <chrono>
#include <iostream>
#include <string>

// Define the maximum length of the number.
#define MAX_LENGTH 500

int main() {
	using namespace std;
	using namespace chrono;
	using hrclock = high_resolution_clock;

	// Prompt the user for a power of two.
	int power = 0;
	cout << "Power of two to calculate: ";
	cin >> power;

	// Use this array to store the number.
	// Initialize the number with a value of 1.
	int digits[MAX_LENGTH] = { 1 };// Remember the start time.
	hrclock::time_point start = hrclock::now();

	int base = 3;
	int carryOver = 0;

	// Iterate for each power of two specified.
	for (int p = 0; p < power; p++) {
		// Go through entire array to get sum
		for (int q = 0; q < MAX_LENGTH; q++) {
			int temp1 = digits[q] * base + carryOver;

			digits[q] = temp1 % 10;
			carryOver = temp1 / 10; // Pass any number greater than 10 to next element
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
	reverse(result.begin(), result.end());
	result = result.substr(result.find_first_not_of('0'));

	// Print the result and stats.
	cout << base << "^" << power << " is " << result << endl;
	cout << "The result is " << result.length() << " digits long." << endl;
	cout << "Time elapsed: " << fixed << elapsed.count() << " seconds." << endl;
}