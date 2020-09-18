#include <iostream>
#include <sstream>  //to convert string to int.
#include <fstream>  //to read files
#include <string>   

using namespace std;


int search(string rank[],string x, int lower, int upper)      // Function to find word using binary search
{
      int mid = (lower + upper) / 2;
      
      if (lower > upper)
      {
          return 0; //returns 0 to "temp" (Temp gets changed to '1001' if it was previously '0')
      }
      else if (rank[mid] == x)
      {
          return mid;
      }
      else if (rank[mid] > x)
      {
          return search(rank,x,lower, mid-1); //recursive case 1
      }
      else if (rank[mid] < x)
      {
          return search(rank,x,mid + 1, upper); //recursive case 2
      }
}

float getDifficulty(float total, float count) // Function to calculate difficulty
{
    float math = 0;
    math = total / count; // average
}

int main()
{
    ifstream wordsFile; //takes is words.txt
    wordsFile.open ("words.txt");
    if (!wordsFile.is_open()) 
    {
        return 0;
    }
    string word[1000]; //contains array of words
    string wordRank[1000]; //contains the rank for each word respectively
    
    for (int j = 1; j < 1000; j++) //loads array (I used 'j' because I aleady used 'i' below (i did that before))
    {
        wordsFile >> wordRank[j];
        wordsFile >> word[j];
        
        //cout << wordRank[j] << endl;
        //cout << word[j] << endl;
    }
    wordsFile.close(); //closes file, done editing arrays.
    
    string filename = " "; 
    cout << "Welcome to the reading level evaluator" << endl << "Enter name of input file (please include file extension): " ;
    cin >> filename; //gets filename
    
    ifstream input;
    input.open (filename); //remember to close when done!!
    if (!input.is_open()) 
    {
        cout << "Error, couldn't read file. " << endl;
        return 0;
    }

    string inputWord = " ";
    float difficulty = 0.0;
    float wordCount = 0.0;

    while (input >> inputWord) // this loop reads one word at a time as long as there are words to read
    {
        for (int i = 0; i < inputWord.length(); i++) //imbedded loop to read words one letter at a time
        {
            inputWord[i] = tolower(inputWord[i]);     // turns all letters to lower case
            
            if ((inputWord[i] == '.') || (inputWord[i] == ',') || (inputWord[i] == ')') || (inputWord[i] == '(') || (inputWord[i] == '!') || (inputWord[i] == '?'))
            {                                                               // removes unnessary charaters
                //cout << inputWord[i] << endl;
                inputWord.erase (inputWord.begin()+i);//tells program where to erase the charater if it finds a invalid one           
                                                      //happens i spaces after the beginning, because that is where the loop is currently looking
            }
        }
        int upper = 1000; //highest rank
        int lower = 0;    //lowest rank
        int temp = 0;     //extra variable to keep me from getting confused
        
        string wordValue = wordRank[search(word,inputWord, lower, upper)]; //sets a new variable equal to the difficutly level of the current word
                                                                           //had to be a string because you cant mix strings and ints    
        stringstream string_2_int(wordValue); //convert string to int
        string_2_int >> temp; //save result in temp
        
        if (temp == 0) //if the word wasn't found in the library, it therefor is too rare and equals '1001'
        {
            temp = 1001;
        }
        
        difficulty = difficulty + temp; //adds the difficulty of the current word to the difficulty of the other words.
        wordCount += 1;                 //increments the wordCount 
                                        //(These are to calculate the average later)
        //*trouble shooting code*\\
        //cout << temp << endl;
        //cout << difficulty << endl;
        //cout << temp << endl;
        //cout << wordValue.length() << endl;
        //cout << wordCount << endl;
        //cout << inputWord << endl;
        
    }
    input.close(); //closes file to prevent leaks or something
    
    float result = getDifficulty(difficulty, wordCount); //gets average difficulty across all words 
    
    cout << "The reading level of " << filename << " is: " << result << "." << endl; //outputs result to user
}