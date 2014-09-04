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

void empty(bucket &item, int bucketNumber)
{
	if(bucketCheck(bucketNumber))
	{
		item.contentSize = 0;
		delete [] item.contents;
		item.contents = NULL;	
	}
	else
	{
		cout<< "Error - bucket " << bucketNumber <<" does not exist." << endl;
	}
}

void put(bucket &item, int bucketNumber, int numContents,int* numberLine)
{
	if(bucketCheck(bucketNumber))
	{
		if(item.contentSize != 0)
		{
			cout << "Error - bucket " << bucketNumber <<" is not empty." << endl;
		}
		else
		{
			item.contentSize = numContents;
			item.contents = new int[numContents - 1]; // to adjust for indexing

			for(int i = 0; i < numContents; i++)
			{
				item.contents[i] = numberLine[i];
			}
		}	

	}
	else
	{
		cout<< "Error - bucket " << bucketNumber <<" does not exist." << endl;
	}
	
}

void output(bucket &item, int bucketNumber)
{
	if(bucketCheck(bucketNumber))
	{
		if(item.contentSize == 0)
		{
			cout << "empty" << endl;
		}
		else
		{
			for(int i = 0; i < item.contentSize; i++)
			{
				cout << item.contents[i] <<" ";
			}
			cout <<endl;
		}

	}
	else
	{
		cout<< "Error - bucket " << bucketNumber <<" does not exist." << endl;
	}
}

void runCommands(ifstream &commandFile, bucket* &item)
{
	string command;
	int bucketNumber;
	int numContents;
	int* numberLine = NULL;
	string inputLine;

	for(int i = 0; i < numCommands; i++)
	{

		commandFile >> command >> bucketNumber;

		if(command == "PUT")
		{
			commandFile >> numContents;
			getline(commandFile, inputLine);
			numberLine = new int[numContents -1];
			stringstream ss;
			for(int i = 0; i < numContents; i++)
			{
				ss << inputLine;
				ss >> numberLine[i];
			}

			put(item[bucketNumber-1], bucketNumber, numContents, numberLine);

			delete [] numberLine;

		}
		else if(command == "OUTPUT")
		{
			output(item[bucketNumber-1],bucketNumber);
		}
		else if(command == "EMPTY")
		{
			empty(item[bucketNumber-1],bucketNumber);
		}
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
	runCommands(iFile,buckets);
	iFile.close();

	for(int i = 0; i < numBuckets; i++)
	{
		if(buckets[i].contentSize != 0)
		{
			delete [] buckets[i].contents;
		}
	}

	delete [] buckets;
	delete [] commandList;


	return 0;
}


