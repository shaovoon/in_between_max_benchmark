#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

class timer
{
public:
	timer() = default;
	void start(const std::string& text_)
	{
		text = text_;
		begin = std::chrono::high_resolution_clock::now();
	}
	void stop()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - begin;
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		std::cout << std::setw(50) << text << " timing:" << std::setw(5) << ms << "ms" << std::endl;
	}

private:
	std::string text;
	std::chrono::high_resolution_clock::time_point begin;
};

class RandomNumGen
{
public:
	RandomNumGen(int min_value, int max_value)
		: gen(rd())
		, dis(min_value, max_value)
	{
	}
	static double GetRand()
	{
		static std::unique_ptr<RandomNumGen> randomNumGen;
		if (!randomNumGen)
			randomNumGen = std::unique_ptr<RandomNumGen>(new RandomNumGen(1, 1000));
		return randomNumGen->dis(randomNumGen->gen);
	}

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis;

};

struct Fraction
{
	Fraction(int numerator_, int denominator_) : numerator(numerator_), denominator(denominator_) {}
	int numerator;
	int denominator;
};

void InitVector(std::vector<Fraction>& vec, size_t total)
{
	vec.clear();
	for (size_t i = 0; i < total; ++i)
	{
		vec.push_back(Fraction(RandomNumGen::GetRand(), 1000));
	}
}


int main()
{
	const size_t MAX_LOOP = 1000000;
	std::vector<Fraction> vec;
	InitVector(vec, 1000);
	int max_value = 280;
	int sum1 = 0;
	int sum2 = 0;
	int sum3 = 0;

	timer stopwatch;
	stopwatch.start("With float conversion");
	for (size_t i = 0; i < MAX_LOOP; ++i)
	{
		sum1 = 0;
		for (size_t j = 0; j < vec.size(); ++j)
		{
			const Fraction& frac = vec[j];
			int value = (int)(((float)frac.numerator / frac.denominator) * max_value);
			sum1 += value;
		}
	}
	stopwatch.stop();

	stopwatch.start("Without float conversion");
	for (size_t i = 0; i < MAX_LOOP; ++i)
	{
		sum2 = 0;
		for (size_t j = 0; j < vec.size(); ++j)
		{
			const Fraction& frac = vec[j];
			int value = max_value * frac.numerator / frac.denominator;
			sum2 += value;
		}
	}
	stopwatch.stop();

	stopwatch.start("Without float conversion with constant divisor");
	for (size_t i = 0; i < MAX_LOOP; ++i)
	{
		sum3 = 0;
		for (size_t j = 0; j < vec.size(); ++j)
		{
			const Fraction& frac = vec[j];
			int value = max_value * frac.numerator / 1000;
			sum3 += value;
		}
	}
	stopwatch.stop();

	std::cout << "sum: " << sum1 << ", " << sum2 << ", " << sum3 << std::endl;

    std::cout << "Done!\n";
}

