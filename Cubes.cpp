#include "Cubes.h"

#include <algorithm>
#include <map>

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
		//GetSetsRecursive(0, n);
		SortCubes();

		std::map<unsigned int, std::vector<uint32_t>> remainderClasses;

		for (size_t i = 0; i < n; i++)
		{
			remainderClasses.emplace(i, FindWithRemainder(i));
		}

		// Add exact cases
		int exactPairSize = remainderClasses[0].size();
		int exactRemainder = (n - exactPairSize) % 4;

		int exactCounter = 0;
		for (auto& exactPairValue : remainderClasses[0])
		{
			if (exactCounter + exactRemainder == exactPairSize)
			{
				break;
			}

			combination.emplace_back(exactPairValue);

			exactCounter++;
		}

		// Add pairs of pairs while combination size is not equal to n
		unsigned int RemainderClassCounter = 1;
		while (combination.size() != n)
		{
			if (RemainderClassCounter == n)
			{
				break;
			}
			int plusPairSize = remainderClasses[RemainderClassCounter].size();
			int minusPairSize = remainderClasses[n - RemainderClassCounter].size();

			// Least common multiple (lcm)
			int lcm = plusPairSize < minusPairSize ? plusPairSize : minusPairSize;

			unsigned int amountNeeded = n - combination.size();
			int amountToAdd = amountNeeded < lcm ? amountNeeded : lcm;

			for (size_t i = 0; i < amountToAdd; i++)
			{
				combination.emplace_back(remainderClasses[RemainderClassCounter][i]);
				combination.emplace_back(remainderClasses[n - RemainderClassCounter][i]);
			}

			RemainderClassCounter++;
		}
		
		// Set to true if enough combinations found
		if (combination.size() == 60)
		{
			validCombinationFound = true;
		}

		#ifdef _DEBUG
		CheckCombination();
		#endif // _DEBUG


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

	void Cubes::SortCubes()
	{
		std::sort(cubeValues.begin(), cubeValues.end());
	}

	std::vector<uint32_t> Cubes::FindWithRemainder(int remainder)
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
