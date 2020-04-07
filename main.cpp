#include <iostream> // Print
#include <time.h>	// Needed for time()


#include "Cubes.h" // Most of the code lies here



/* SETTINGS */
// Comment out this line if time measurement not needed
#define PROFILE_TIME


// Include chrono if we are profiling for time
#ifdef PROFILE_TIME
#include <chrono>
#endif // PROFILE_TIME


void PopulateCubesWithRandomValues(NagyB::Cubes& cubes)
{
	// Create seed from time
	srand(time(NULL));

	// Populate cubes with random values
	for (unsigned int i = 0; i < (2 * cubes.GetA() * cubes.GetB() * cubes.GetC()); i++)
	{
		cubes.AddCubeValue(rand() % 1000);
	}
}

int main()
{
	/*
	Program runs in 3 steps :
	1 : get initial values (a, b, c)
	2 : generate cubes
	3 : calculate task
	*/

	/* ************************************************************************* */
	// 1 : get initial values (a, b, c)
	/* ************************************************************************* */

	// NOTE : itt olvasod be cin rol vagy akarhonnan a, b, c erteket
	int a = 10;
	int b = 12;
	int c = 17;

	/* ************************************************************************* */
	// 2 : generate cubes (handled by constructor)
	/* ************************************************************************* */

	NagyB::Cubes cubes(a, b, c);			// Create container of the cubes	
	// Somewhere cubes failed if false
	if (cubes.GetSuccess() == false)
	{
		std::cout << cubes.GetErrorMessage() << std::endl;
		return -1;
	}
	PopulateCubesWithRandomValues(cubes);	// Populate cubes with values
	
	// Print new cobe values
	// NOTE : Csak debug verzioban irjuk ki a generalt kockakat
	#ifdef _DEBUG
	std::cout << "Generated cube values : " << std::endl;
	cubes.PrintGeneratedCubeValues();
	#endif // _DEBUG


	/* ************************************************************************* */
	// 3 : generate cubes (calculate task)
	/* ************************************************************************* */

	// Start measuring time if PROFILE_TIME is defined
	#ifdef PROFILE_TIME
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	#endif // PROFILE_TIME

	cubes.CalculateTask();

	/* ************************************************************************* */
	// 4 : print results
	/* ************************************************************************* */

	if (cubes.GetCombinationFound() == false)	// No valid combination found
	{
		std::cout << "****" << std::endl;
	}
	else
	{
		cubes.PrintCombination();
	}

	// Get end point in time and print time it took between begin & end
	#ifdef PROFILE_TIME
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time it took to find result = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
	#endif // PROFILE_TIME

	return 0;
}