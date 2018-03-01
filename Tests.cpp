#include "SortedArray.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int testNumber;
std::ofstream log;

int cmp_int(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

void testStart()
{
	testNumber++;
	log.open("Tests.log");
}

void testEnd(bool success)
{
	log.close();
	if (success)
	{
		printf("\033[1m\033[32mTest %d passed.\033[0m\n", testNumber);
	}
	else
	{
		printf("\033[1m\033[31mTest %d failed. Test output is written to Tests.log.\033[0m\n", testNumber);
		system("cat Tests.log");
		exit(EXIT_FAILURE);
	}

}

int main()
{
	SortedArray<int> sa(20, cmp_int);	
	testNumber = 0;
	bool success;

	try 
	{
	// ---- Test 1 ----
		testStart();

		int IN[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 3, 6, 2, 1, 8, 7, 9, 0, 4, 5, 6};
		try
		{
			for (int a : IN)
			{
				sa.put(a);
				log << sa;
			}
			testEnd(false);
		} catch (int) { errno = 0; }
	
		int T1[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
		testEnd(sa == T1);
	
	// ---- Test 2 ----
		testStart();

		success = true;
		for (int i = 0; i < 20; i++)
		{
			if (sa[i] != T1[i])
			{
				success = false;
				break;
			}
		}

		try { 
			sa[20]; 
			testEnd(false); 
		} catch (int) { errno = 0; }

		testEnd(success);

	// ---- Test 3 ----
		testStart();

		int index;
		success = true;

		log << sa;

		success &= 8 == (index = sa.find(4));	log << index << '\n';
		success &= 0 == (index = sa.find(0));	log << index << '\n';
		success &= 18 == (index = sa.find(9));	log << index << '\n';

		try { 
			sa.find(10);
			testEnd(false);
		} catch (int) { errno = 0; }

		testEnd(success);

	// ---- Test 4 ----
		testStart();

		sa.removeAll(3); log << sa;
		sa.removeAll(6); log << sa;
		sa.removeAll(0); log << sa;
		sa.removeAll(9); log << sa;
		sa.removeAll(10); log << sa;
	
		int T2[] = {1, 1, 2, 2, 4, 4, 5, 5, 7, 7, 8, 8};
		testEnd(sa == T2);

	// ---- Test 5 ----	
		testStart();

		sa.remove(0); log << sa;
		sa.remove(1); log << sa;
		sa.remove(2); log << sa;

		int T3[] = {1, 2, 4, 5, 5, 7, 7, 8, 8};
		testEnd(sa == T3);

	
	} 
	catch (int err) 
	{
		std::cerr << 
			"\033[1m\033[35m" << 
			"The program has crashed on test " << 
			testNumber << 
			". Output is written to Tests.log\n" << 
			"\033[0m";
		log << "Caught error " << err << ": " << strerror(err) << ".\n";
		log.close();

		system("cat Tests.log");
		exit(EXIT_FAILURE);
	}

	return 0;
}
