#include "SortedArray.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Context
{
	int i;
	bool success;
	int* T3;
};

int testNumber;
std::ofstream log;

int cmp_int(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

void each1(void * p)
{
	*(int*)p ^= 0xAAAAAAAA;
}

void each2(void* p, void * context)
{
	log << *(int*) p << ' ';
	struct Context * ctx = (struct Context*) context;
	if (*(int*)p != ctx->T3[ctx->i])
		ctx->success = false;
	ctx->i++;
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
		printf("\033[1m\033[31mTest %d failed. Test output has been written to Tests.log\033[0m\n", testNumber);
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

		sa.removeAll(3); log << sa;
		sa.removeAll(6); log << sa;
		sa.removeAll(0); log << sa;
		sa.removeAll(9); log << sa;
		sa.removeAll(10); log << sa;
		sa.removeAll(0); log << sa;
	
		int T2[] = {1, 1, 2, 2, 4, 4, 5, 5, 7, 7, 8, 8};
		testEnd(sa == T2);
	
	// ---- Test 4 ----
		testStart();

		int index;
		success = true;

		log << sa;

		success &= 4 == (index = sa.find(4));	log << index << '\n';
		success &= 0 == (index = sa.find(1));	log << index << '\n';
		success &= 10 == (index = sa.find(8));	log << index << '\n';

		try { 
			sa.find(10);
			testEnd(false);
		} catch (int) { errno = 0; }
	
		try { 
			sa.find(6);
			testEnd(false);
		} catch (int) { errno = 0; }


		testEnd(success);

	// ---- Test 5 ----	
		testStart();

		sa.remove(0); log << sa;
		sa.remove(1); log << sa;
		sa.remove(2); log << sa;

		int T3[] = {1, 2, 4, 5, 5, 7, 7, 8, 8};
		testEnd(sa == T3);

	// ---- Test 6 ----
		testStart();

		sa.foreach(each1);
		log << sa;
	
		int T4[] = {-1431655765, -1431655768, -1431655762, -1431655761, -1431655761, -1431655763, -1431655763, -1431655774, -1431655774};
		if (sa != T4)
			testEnd(false);

		sa.resort();
		log << sa;

		int T5[] = {-1431655774, -1431655774, -1431655768, -1431655765, -1431655763, -1431655763, -1431655762, -1431655761, -1431655761};
		if (sa != T5)
			testEnd(false);

		sa.foreach(each1);
		log << sa;

		int T6[] = {8, 8, 2, 1, 7, 7, 4, 5, 5};
		if (sa != T6)
			testEnd(false);

		sa.resort();
		log << sa;

		if (sa != T3)
			testEnd(false);

		try {
			sa.foreach(NULL);
			testEnd(false);
		} catch (int) {errno = 0;}
		log << "NULL\n";

		try {
			sa.foreach(NULL, NULL);
			testEnd(false);
		} catch (int) {errno = 0;}
		log << "NULL NULL\n";

		testEnd(true);

	// ---- Test 7 ----
		testStart();

		struct Context ctx = {
			.i = 0,
			.success = true,
			.T3 = T3
		};

		log << sa;
		sa.foreach(&ctx, each2);
		log << '\n';

		if (ctx.success == false)
			testEnd(false);

		int i = 0;
		success = true;
		SortedArray<int>::Iterator it(sa);
		for (; !it.isEnd(); it.next())
		{
			log << it.get() << ' ';
			if (it.get() != T3[i]) {
				success = false;
				break;
			}
			i++;
		}
		log << '\n';

		try { 
			it.next(); 
			testEnd(false);
		} catch (int) {errno = 0;}

		try { 
			it.get(); 
			testEnd(false);
		} catch (int) {errno = 0;}

		testEnd(success);

	// ---- Test 8 ----
		testStart();

		#define CHECK if (errno == 0) {log << "\033[1m\033[33m" << i << "\033[0m\n"; testEnd(false);} errno = 0; log << i++ << ' ';

		i = 1;

		sanew(-1, -1, NULL);				CHECK //1
		sadelete(NULL);						CHECK //2
		saget(NULL, 1);						CHECK //3
		saput(NULL, NULL);					CHECK //4
		sarm(NULL, 0);						CHECK //5
		sarmall(NULL, NULL);				CHECK //6
		salen(NULL);						CHECK //7
		safind(NULL, NULL);					CHECK //8
		sacmp(NULL, 0, NULL);				CHECK //9
		saresort(NULL);						CHECK //10
		sainew(NULL);						CHECK //11
		saidelete(NULL);					CHECK //12
		saiend(NULL);						CHECK //13
		sainext(NULL);						CHECK //14
		saiget(NULL);						CHECK //15

		try { 
			SortedArray<int> san(100500800900, cmp_int); 
			CHECK //16
		} catch (int) { errno = 0; log << i++ << ' '; }

		try {
			sa[1000];
			CHECK //17
		} catch (int) { errno = 0; log << i++ << ' '; }

		try {
			sa.remove(1000);
			CHECK //18
		} catch (int) { errno = 0; log << i++ << ' '; }

		try {
			sa.cmp(1000, 1);
			CHECK //19
		} catch (int) { errno = 0; log << i++ << ' '; }

		struct sorted_array* sarr = sanew(4, 0, cmp_int);
		int one = 1;

		safind(sarr, &one);					CHECK //20

		sarmall(sarr, &one);

		if (sa == T1 || sa == T6)
			testEnd(false);

		testEnd(true);
	} 
	catch (int err) 
	{
		std::cerr << 
			"\033[1m\033[35m" << 
			"The program had crashed on test " << 
			testNumber << 
			". Output has been written to Tests.log\n" << 
			"\033[0m";
		log << "Caught error " << err << ": " << strerror(err) << ".\n";
		log.close();

		system("cat Tests.log");
		exit(EXIT_FAILURE);
	}

	return 0;
}
