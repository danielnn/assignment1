#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

int countWords(string textLine);


int main(int argc, char* argv[])
{
   //Check how many commandline arguments
   if(argc != 2)
   {
       cout << "Improper command line arguments entered" << endl;
       cout << "Include file name after the program being run." << endl;
       return 1;
   }

   
   
   string numberLine;
   int numLines;
   string* lines;
   
   //get number of lines from txt file
   ifstream inputFile;
   inputFile.open(argv[1]);
   if(inputFile.is_open())
   {
          getline(inputFile, numberLine);
          stringstream ss;
          ss << numberLine;
          ss >> numLines;
   }
   
   //Dynamically allocate string arrays for rest of file
   lines = new string[numLines];
   
   //Read rest of the lines
   if(inputFile.is_open())
   {
    int i = numLines - 1; //Minus 1 because index starts at 0
    string tempLine;

    while(getline(inputFile, tempLine))
    {
      lines[i] = tempLine;
      i--;
    }
   }

   //Count and Print number of words
   for(int i = 0; i < numLines; i++)
   {
      cout << countWords(lines[i]) << endl;
   }
   
   inputFile.close();
   delete [] lines;

   return 0;
}

int countWords(string textLine)
{
  bool isAWord = false;
  char wordArray[80];
  int wordCount = 0;

  const char* tempArray = textLine.c_str();
  strcpy(wordArray,tempArray);


  int arraySize = strlen(tempArray); //Plus 1 for null character

  /*
  Goes through the character array letter by letter
  isAWord, the search state initially starts as false
  if a letter is encountered while the search state is false, it adds 1 to the wordCount and changes the state to true
  if a space is encountered while the search state is true, isAWord changes to false
  */
  for(int i = 0; i < arraySize; i++)
  {
    if(isAWord == false && wordArray[i] != ' ')
    {
      wordCount++;
      isAWord = true;
    }
    else if(isAWord == true && wordArray[i] == ' ')
    {
      isAWord = false;
    }
  }
  return wordCount;
}