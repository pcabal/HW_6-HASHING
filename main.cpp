#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

///I DIDN'T WORK WITH ALL STRINGS BECAUSE THE COMPILER WOULDN'T WORK WITH THE CODE I HAD
///SINCE I WORKED WITH INTS, NUMBERS LIKE 0003 WOULD BE CONSIDERED AS 3 INSTEAD, BUT I FIXED THIS WHILE WRITING TO FILE

///************************************************///
///ALSO, IF THERE IS AN EMPTY SLOT IN THE HASHED ARRAY, I DIDN'T KNOW HOW TO DISTINGUISH
///0000 FROM "EMPTY" SINCE I DIDN'T WORK WITH STRINGS
int Hash (int queueContents)  //hash function to get position
{
    //I don't really need this since I worked with ints
    return queueContents%65000;                    //key = 4 numbers from SSN -> I extracted it in Main
}

//Quad Probe
int quadratic_probe(int Hashtable[], int key, int MAX)
{
    int pos, i;
    for (i=1; i<(MAX-1)/2; i++)
    {
        pos = (Hash(key)+(i*i))%MAX;        //MAX is the user input
        if (Hashtable[pos] == 0) //empty slot
        {
            Hashtable[pos] = key;       //Hashtable spot becomes key
            return pos;
        }
    }
    return -1;  //Table overflow

}


int main()
{

queue <int> myQueue;                //Put all the contents from the file in here
queue <int> hashedQueue;            //Put the hashed SSN in here to write out to file
ifstream inFile;                       //Create a file inFile that will read in from a file
ofstream outFile;                      //Create a file outFile that will be written to
string fileName, fileContents;
int parseFileContents, userInput;
fileName = "/Users/Perseus/Documents/C++/HW_6/test.txt";
//fileName ="test.txt"
inFile.open(fileName);                  //Open file called fileName

while (!inFile.eof())                           //while the file is not at the end
{
    ///I DID MY EXTRACTION WHILE GETTING THE FILECONTENTS
    if (getline(inFile, fileContents, ','))     //Makes 1 string from the whole file and separates the string by the delimiter ","...
    {
        fileContents.erase(0,2);  //123456789 1 & 2 are taken out
        fileContents.erase(1,1);  //356789      4 is taken out
        fileContents.erase(2,1);  //35789;      6 is taken out
        fileContents.erase(4,1);            //  9 is taken out
        parseFileContents = stoi(fileContents);  //Parse the string into an int
        myQueue.push(parseFileContents);  //3578 is pushed in
       // cout << fileContents << endl; testing
    }
}
inFile.close();

    int array_of_numbers [75000];

    for (int i = 0; i<65000; i++)                     //Add file values into array
    {
        array_of_numbers[i] = myQueue.front();
        myQueue.pop();
    }
    //Size is 65000 because that's how many SSN's there are
    ///If 450000000 is inputted, it works fine, but if 1 is inputted, not all the numbers show because of the size
    ///Couldn't Dynamically Allocate Array
    int hash_table [65000];                         //Set all the values in the hash = to zero
    for (int i = 0; i<65000; i++)
    {
        hash_table[i] =0;
    }
    int index;
   cout << "Enter a number between 1 and 450 million: ";        ///IS IT SUPPOSED TO HASH BETTER THE HIGHER THE NUMBER?
   cin >> userInput;
   for(int i=0;i<65000;i++)    //hash the elements in array_of_numbers into the hash_table
    {
        index=Hash(array_of_numbers[i]);
        if(hash_table[index]==0)                                    //If the spot is empty, insert the value
            hash_table[index]=array_of_numbers[i];
        else
        {
            quadratic_probe(hash_table, array_of_numbers[i], userInput);        //probe the value if the index is taken
        }
    }

    for (int i = 0; i<65000; i++)  ///This is for a high user input, if the input is low, the array is too small to show everything
    {
        //cout << array_of_numbers[i] << endl; //testing
        cout << hash_table[i] << endl;       //testing
        hashedQueue.push(hash_table[i]);                    //Pushes the elements in the array into a queue
    }


outFile.open("hashed_socials.txt");                 //Open a new file to write to

while (hashedQueue.size() != 1)                     //Adds a comma after every element except the last one, next element is accessed by popping the front
    {
        if (hashedQueue.front() < 10)                   //If the value is less than 10 add 3 zeros to the front
        {                                               //i.e. 3 becomes 0003, 6 becomes 0006
            outFile << "000";
            outFile << hashedQueue.front() << ',';
            hashedQueue.pop();
        }
        else if (hashedQueue.front() < 100)             //If the value is less than 100, add 2 zeros to the front
        {                                               //i.e. 40 becomes 0040,  99 becomes 0099
            outFile << "00";
            outFile << hashedQueue.front() << ',';
            hashedQueue.pop();
        }
        else if (hashedQueue.front() < 1000)            //If the value is less than 1000, add 1 zero to the front
        {                                               //999 become 0999, 432 becomes 0432
            outFile << "0";
            outFile << hashedQueue.front() << ',';
            hashedQueue.pop();
        }
        else                                            //Normal hashed code, no need to add zeros
        {
        outFile << hashedQueue.front() << ',';
        hashedQueue.pop();
        }
    }
    outFile << hashedQueue.back() << endl;
    hashedQueue.pop();

    outFile.close();                                //Close the file
//cout << myQueue.size();
return 1;

}
