#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;


struct bucket{

	int* contents = NULL;
	int contentSize = 0;
	int bucketNumber = 0;
};

int numBuckets = 0;
int numCommands = 0;

bool bucketCheck(int bucketNumber)
{
	if(bucketNumber < 1 || bucketNumber > numBuckets)
	{
		return false; 
	}
	else
	{
		return true;
	}
}

void assignBucketNumbers(bucket* &item)
{
	for(int i = 0; i < numBuckets; i++)
	{
		item[i].bucketNumber = i + 1;
	}

}

void emptyBucket(bucket &item, int bucketNumber)
{
	if(bucketCheck(bucketNumber))
	{
		item.contentSize = 0;
	}
	else
	{
		cout<< "Error - bucket " << bucketNumber <<" does not exist." << endl;
	}
}

int main(int argc, char* argv[])
{

	bucket* buckets = NULL;
	string* commandList = NULL;

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
// get data for number of buckets and commands
	iFile >> numBuckets;
	iFile >> numCommands;
// dynamically allocate number of buckets and commands

	buckets = new bucket [numBuckets];
	commandList = new string [numCommands];

	assignBucketNumbers(buckets);

	iFile.close();

	delete [] buckets;
	delete [] commandList;

	return 0;
}


