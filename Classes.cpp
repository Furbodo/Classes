// Classes.cpp : Defines the entry point for the console application.
// Justin Balogh

#include "stdafx.h"
#include <string>
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

class Horse 
{
private:
	// Fields for Horse
	string name;
	int age;
	int numRaces;
	int finishes[5];
	int finishesIndex;
	float average;

public:
	// Member Methods
	Horse() // default constructor
	{
		this->name = "";
		this->age = 0;
		this->numRaces = 0;
		this->average = 0;
		this->finishesIndex = 0;
	}

	Horse(string name, int age) // parameter based constructor
	{
		this->name = name;
		this->age = age;
		this->numRaces = 0;
		this->average = 0;
	}

	void setAge(int age) // sets age
	{
		this->age = age;
	}

	void setName(string name) // sets name
	{
		this->name = name;
	}

	void InitHorse() // intializes a horse
	{
		string name;
		string age;
		int ageInt = 0;

		cout << "What is the name of the horse?" << endl;
		getline(cin, name); cout << endl;
		
		cout << "What is the age of the horse?" << endl;
		getline(cin, age); cout << endl;
		
		string::size_type size; // using getline needs a method of not using cin because the buffer has to be flushed, easier to just use getline for the rest of the program
		ageInt = stoi(age, &size); // parses age string and assigns the numerical value to age

		setAge(ageInt); 
		setName(name);
	}

	int AddFinish(int raceFinish) 
	{
		if (finishesIndex <= 5) // keeps track of array size
		{
			finishes[finishesIndex] = raceFinish; // assigns finish place to current element
			finishesIndex++; 
			numRaces++;

			UpdateAverage(); // updates average place after another place is entered

			cout << "Race data entered successfully" << endl; 
			return 1;
		}

		else // error text
		{
			cout << "Could not add finish. Data full." << endl;
			return 0;
		}
	}

	int HighFinish() // finds max finish place, then returns it. variation of func from monkey assignment
	{
		if (finishesIndex != 0)
		{
			int highestFinish = finishes[0];
			
			for (int i = 0; i < finishesIndex; i++) 
			{
				if (finishes[i] > highestFinish) 
				{
					highestFinish = finishes[i];
				}
			}
			return highestFinish;
		}

		else 
		{
			cout << "Error no races have been run." << endl;
			return -1;
		}
	}

	int LowFinish() // reverse of max, finds min 
	{
		if (finishesIndex != 0) 
		{
			int lowestFinish = finishes[0];

			for (int i = 0; i < finishesIndex; i++) 
			{
				if (finishes[i] < lowestFinish)
				{
					lowestFinish = finishes[i];
				}
			}
			return lowestFinish;
		}

		else 
		{
			cout << "Error no races have been run." << endl;
			return -1;
		}
	}

	void PrintFinishes() // prints each horse and the data
	{
		cout << fixed << setprecision(1);
		
		cout << "----------------------------- Horse Details ---------------------------------------" << endl;
		cout << "Name: " << name << "  Age: " << age << "  Number of Races: " << numRaces << "  \n";
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << "Finish Places: ";

		for ( int i = 0; i < finishesIndex; i++) // cycles through array
		{
			cout << finishes[i] << ", " << endl;
		}

		cout << "The lowest finish was: " << LowFinish() << endl; // prints low, high, and average
		cout << "The highest finish was: " << HighFinish() << endl;
		cout << "The average finish was: " << average << endl;
		
	}

	void UpdateAverage() // updates the average
	{
		if (finishesIndex != 0) 
		{
			for (int i = 0; i < finishesIndex; i++)
			{
				average += finishes[i];
			}
			average /= finishesIndex;
		}
		else 
		{
			// No average to calc
		}
	}

	~Horse() // deconstructor 
	{
		// no clean up needed
	}


};
// Prototypes
void setupRace(Horse[]);
void readOutContestants(Horse[]);
void enterRaceData(Horse[]);

int main()
{
	Horse contestants[5];
	
	setupRace(contestants);
	readOutContestants(contestants);
	enterRaceData(contestants);
	readOutContestants(contestants);

	system("PAUSE");
}

void setupRace(Horse constestants[]) // sets up the five horses and fills the contestant array
{
	Horse *playerOne = new Horse();
	playerOne->InitHorse();
	constestants[0] = *playerOne;

	Horse *playerTwo = new Horse();
	playerTwo->InitHorse();
	constestants[1] = *playerTwo;

	Horse *playerThree = new Horse();
	playerThree->InitHorse();
	constestants[2] = *playerThree;

	Horse *playerFour = new Horse();
	playerFour->InitHorse();
	constestants[3] = *playerFour;

	Horse *playerFive = new Horse();
	playerFive->InitHorse();
	constestants[4] = *playerFive;
}

void readOutContestants(Horse contestants[]) // prints out each array element using the member function from Horse
{
	for (int i = 0; i < 5; i++) 
	{
		contestants[i].PrintFinishes();
		cout << endl;
	}
}

void enterRaceData(Horse contestants[]) // Entering race data
{
	cout << "Please enter horse finish data." << endl;

	char enterDataFlag = 'y';
	int input = 0;
	int place = 0;
	while (enterDataFlag == 'y') 
	{	// cin is fine here because only primitives are being used (no strings)
		cout << "What horse do you want to enter data for?(1-5)" << endl;
		cin >>  input; // sets array element or object to add a place to 
		input -= 1;

		cout << "What place did the horse make?" << endl;
		cin >> place;
		contestants[input].AddFinish(place); // adds a place to the finishes array in the horse obj
		
		cout << "Do you want to continue adding places?(y/n)" << endl;
		cin >> enterDataFlag; // continue flag
		tolower(enterDataFlag);
	}
}