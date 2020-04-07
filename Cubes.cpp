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
		
		SortCubes();

		std::vector<uint32_t>::iterator bIt= cubeValues.begin();
		std::vector<uint32_t>::iterator eIt = cubeValues.end();
		int sum = 0;
		for (size_t i = 0; i < n; i++)
		{
			if (i < n - 1)
			{
				std::advance(bIt, 1);
				combination.emplace_back(*bIt._Ptr);
				sum += *bIt._Ptr;

				std::advance(eIt, -1);
				combination.emplace_back(*eIt._Ptr);
				sum += *eIt._Ptr;
			}
			else
			{
				do 
				{
					std::advance(bIt, 1);
				} while ((sum + *bIt._Ptr) % n != 0);
				combination.emplace_back(*bIt._Ptr);
				sum += *bIt._Ptr;
			}
		}

		CheckCombination();

		return;
	}

	void Cubes::SortCubes()
	{
		std::sort(cubeValues.begin(), cubeValues.end());
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
