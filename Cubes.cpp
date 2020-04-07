#include "Cubes.h"

#include <algorithm>
#include <map>
#include <chrono>

namespace NagyB
{
	Cubes::Cubes(uint32_t a, uint32_t b, uint32_t c) : a(a), b(b), c(c)
	{
		// Check a, b, c values as they must be 1 <= a,b,c <= 50
		if (a < 1 || a > 50) { errorMsg += "A value invalid : " + a; success = false; }
		if (b < 1 || b > 50) { errorMsg += "B value invalid : " + b; success = false; }
		if (c < 1 || c > 50) { errorMsg += "C value invalid : " + c; success = false; }

		n = a * b * c / 2;

		#ifdef _DEBUG
		std::cout << "A : " << a << std::endl;
		std::cout << "B : " << b << std::endl;
		std::cout << "C : " << c << std::endl;
		std::cout << "N : " << n << std::endl;
		#endif // _DEBUG
	}

	void Cubes::CalculateTask()
	{
		cubeValuesSize = cubeValues.size();
		// Create seed from time
		srand(time(NULL));

		unsigned int leaveX;
		if (a*b*c > 1000)
		{
			leaveX = 2;
		}
		else
		{
			leaveX = 2;
		}

		success = false;
		unsigned int maxTryNumber = 50;
		unsigned int tryCount = 0;
		std::pair<uint32_t, uint32_t> lastPair;
		while (success == false)
		{
			blackList.clear();
			uint32_t sum = 0;
			for (size_t i = 0; i < n - leaveX; i++)
			{
				uint32_t newRandValue = GetRandomIndexWithBlacklist();

				combination.emplace_back(cubeValues[newRandValue]);
				blackList.emplace_back(newRandValue);
				sum += cubeValues[newRandValue];
			}

			int remainder = sum % n;

			if (leaveX == 2)
			{
				lastPair = FindLastPair(remainder);
			}
			else if (leaveX == 1)
			{
				lastPair = FindLast(remainder);
			}
			else
			{
				// nono
			}


			tryCount++;
			if (tryCount == maxTryNumber) break;
		}
		combination.emplace_back(lastPair.first);
		if (leaveX == 2) combination.emplace_back(lastPair.second);

		CheckCombination();

		return;
	}

	void Cubes::GetSetsRecursive(int offset, int k)
	{
		if (k == 0)
		{
			#ifdef _DEBUG
			PrintCombination();
			#endif // _DEBUG

			CheckCombination();

			return;
		}
		for (int i = offset; i <= cubeValues.size() - k; ++i)
		{
			combination.push_back(cubeValues[i]);
			GetSetsRecursive(i + 1, k - 1);

			if (validCombinationFound)
			{
				return;
			}

			combination.pop_back();
		}

	}

	uint32_t Cubes::GetRandomIndexWithBlacklist()
	{
		uint32_t value = rand() % cubeValuesSize;
		if (std::find_if(blackList.begin(), blackList.end(), [=](uint32_t item) -> bool { return value == item; }) != blackList.end())
		{
			value = GetRandomIndexWithBlacklist();
		}

		return value;
	}

	void Cubes::SortCubes()
	{
		std::sort(cubeValues.begin(), cubeValues.end());
	}

	std::pair<uint32_t, uint32_t> Cubes::FindLastPair(unsigned int remainder)
	{
		for (size_t i = 0; i < cubeValuesSize; i++)
		{
			for (size_t j = 0; j < cubeValuesSize; j++)
			{

				if (std::find_if(blackList.begin(), blackList.end(), [=](auto& item) -> bool { return item == i || item == j; }) == blackList.end())
				{
					if ((cubeValues[i] + cubeValues[j] + remainder) % n == 0)
					{
						success = true;
						return std::pair<uint32_t, uint32_t>(cubeValues[i], cubeValues[j]);
					}
				}
			}
		}
		success = false;
		return std::pair<uint32_t, uint32_t>();
	}

	std::pair<uint32_t, uint32_t> Cubes::FindLast(unsigned int remainder)
	{
		for (size_t i = 0; i < cubeValuesSize; i++)
		{
			if (std::find_if(blackList.begin(), blackList.end(), [=](auto& item) -> bool { return item == i; }) == blackList.end())
			{
				if ((cubeValues[i] + remainder) % n == 0)
				{
					success = true;
					return std::pair<uint32_t, uint32_t>(cubeValues[i], 0);
				}
			}
		}
		success = false;
		return std::pair<uint32_t, uint32_t>();
	}

	std::vector<uint32_t> Cubes::FindAllWithRemainder(int remainder)
	{
		std::vector<uint32_t> values;

		std::for_each
		(
			cubeValues.begin(),
			cubeValues.end(),
			[&](auto& item) -> void { if (item % this->GetN() == remainder) { values.emplace_back(item); } });

		return values;
	}

	void Cubes::CheckCombination()
	{
		uint32_t sum = 0;
		for (int i = 0; i < combination.size(); ++i)
		{
			sum += combination[i];
		}

		// Remainder calculation (combination valid if remainder == 0)
		int remainder = sum % n;

		#ifdef _DEBUG
		std::cout << "Combination sum : " << sum << std::endl;
		std::cout << "Combination remainder : " << remainder << std::endl;
		#endif // !_DEBUG

		if (remainder == 0)
		{
			#ifdef _DEBUG
			std::cout << "Combination found!" << std::endl;
			#endif // !_DEBUG

			validCombinationFound = true;
		}
	}
}
