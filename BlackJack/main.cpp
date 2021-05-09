#include <cstdlib>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using namespace std;

bool cardTest();
bool cardDeckTest();
bool blackJackTest();

int main(int argc, char* argv[]) {
	int testNum = 3;
	if (argc > 1) {
		testNum = atoi(argv[1]);
	}
	switch (testNum) {
		case 1:
			cardTest();
			break;
		case 2:
			cardDeckTest();
			break;
		case 3:
			blackJackTest();
			break;
	}
	return 0;
}
