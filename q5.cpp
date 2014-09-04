#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

int numBuckets = 0;
int numCommands = 0;

int main(int argc, char* argv[])
{
	if( argc != 2)
	{
		cout<<"Incorrect command line input" << endl;
		cout<<"Input file name after program name" << endl;
	}

	ifstream iFile;
	iFile.open(argv[1]);
	if(iFile.fail())
	{
		cout << "Improper file name inputted, please try again" << endl;
		return 1;
	}

	iFile >> numBuckets;
	iFile >> numCommands;

	cout<< numBuckets << endl;
	cout << numCommands << endl;
	
	iFile.close();
	return 0;
}