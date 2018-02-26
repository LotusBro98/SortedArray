all: libsarr.so Tests

CC=g++
CFLAGS=-g -Wall

LD=g++
LDFLAGS=-L. -Wl,-rpath,. 


### Objects ###

libsarr.so: sorted_array.cpp
	@printf "\033[32mCompiling Sorted Array shared library libsarr.so...\033[0m\n"
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $<

Tests.o: Tests.cpp
	@printf "\033[32mCompiling Unit Tests...\033[0m\n"
	$(CC) $(CFLAGS) -c -o $@ $<


### Executables ###

Tests: Tests.o
	@printf "\033[32mLinking Unit Tests...\033[0m\n"
	$(LD) $(LDFLAGS) -o $@ $< -lsarr


### Additional targets ###

clean:
	@printf "\033[32mRemoving all build files...\033[0m\n"
	rm -rf *.o *.so Tests doc/*/

doxygen:
	@printf "\033[32mGenerating documentation...\033[0m\n"
	doxygen doc/Doxyfile > /dev/null

### Dependencies on headers ###

libsarr.so: sorted_array.h
Tests: SortedArray.hpp sorted_array.h
