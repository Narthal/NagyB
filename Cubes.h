#ifndef CUBES_H
#define CUBES_H

#include <stdint.h>	// Needed for uint32_t (unsigned int can be any bit size as the compiler optimizes the code. uint32_t ensures 32 bit length)
#include <vector>	// Vector
#include <string>	// String
#include <iostream>	// cout






namespace NagyB
{
	class Cubes
	{
	public: // Ctors / Dtors
		// Ctor
		Cubes(uint32_t a, uint32_t b, uint32_t c);

	public:	// Interface with this class through these methods
		// Add new value to vector
		void AddCubeValue(uint32_t value)
		{
			cubeValues.emplace_back(value);	// Pu new values to the back of the list
		}

		// Calculates the task
		void CalculateTask();

	public: // Get / Set
		inline const bool GetSuccess() const { return success; }
		inline const std::string GetErrorMessage() const { return errorMsg; }
		inline const uint32_t GetA() const { return a; }
		inline const uint32_t GetB() const { return b; }
		inline const uint32_t GetC() const { return c; }
		inline const bool GetCombinationFound() const { return validCombinationFound; }

	public: // Printing helper methods
		inline void PrintCombination() const
		{
			static int count = 0;

			#ifdef _DEBUG
			std::cout << "Combination : " << (++count) << " : ";
			#endif // _DEBUG
			for (int i = 0; i < combination.size(); ++i) { std::cout << combination[i] << " "; }
			std::cout << std::endl;
		}

		#ifdef _DEBUG	// NOTE : _DEBUG chack akkor letzik, ha Debug konfiguracioban buildelsz (a legvegen Release mode-ban buildelj optimalis sebessegert)
		
		inline void PrintGeneratedCubeValues() const { for (auto& cubeValue : cubeValues) std::cout << cubeValue << std::endl; }
	
		#endif // !_DEBUG


	private: // Vars
		uint32_t a, b, c;
		uint32_t n;
		std::vector<uint32_t> cubeValues;
		std::vector<uint32_t> combination;
		bool validCombinationFound = false;

	private: // Error handler variables
		bool success = true;
		std::string errorMsg = "";

	private: // Private helper methods
		void GetSets(int offset, int k);

		void CheckCombination();
	};
}


#endif // !CUBES_H
