// CMP201 AX1.8 The dog adoption problem.
// Author: William Kavanagh
// Partial Framework

#include <map>
#include <vector>
#include <iostream>

// helper function
// takes a vector of vectors, a person to index the row and then two dogs 1 and 2 to index the column.
// if the value of dog 1 comes BEFORE dog 2 in the person row of their preference, return true, else, return false.
// Hint: Use find(iterator, iterator, value).
bool personPrefersNewDog(std::vector<std::vector<int>> personPref, int person, int dog1, int dog2)
{
	// Assessed, 1 mark.
	for (int i = 0; i<personPref.size();i++)
	{
		if (personPref[person][i] == dog2)
		{
			return true;
		}
		else {
			return false;
		}
	}

	return false;
}

// helper function
// takes a map of matches and returns the dog (i.e. the key) of the pair with the passed person as the value.
int dogMatchedToPerson(int person, std::map<int,int> matches)
{
	// Assessed, 1 mark.
	return 0;
}

std::map<int, int> stableMarriage(std::vector<std::vector<int>> dogPref, std::vector<std::vector<int>> personPref)
{
	// Assessed, 3 marks.
	
	// Initialise all dogs and people to be free.
	// create counts of how many proposals each dog has made.
	std::vector<bool> dogFree;
	std::vector<bool> personFree;
	std::vector<int> personMatch;
	std::vector<int> dogProps;
//	std::map<int, int> matching;
	//
	int size = dogPref.size();

	for (int i=0; i<=size;i++)
	{
		dogFree.push_back(true);
		personFree.push_back(true);
		personMatch.push_back(-1);
		dogProps.push_back(size);
		//matching.insert(i,-1);
	}

	int freeDogAmount = size;


	
	// while a dog is free and hasn't proposed to everyone yet.

	while (freeDogAmount > 0)
	{
			// find the next free dog who still has a person to propose to
		int currentDog;
		for (currentDog = 0; currentDog < size; currentDog++)
		{
			if (dogFree[currentDog] == true)
			{
				break;
			}
		}

		for (int i = 0; i < size; i++)//for every dog
		{

			// find the next person they haven't proposed to.
			if(dogFree[currentDog] == true)
			{
				int matchedPerson = dogPref[currentDog][i];
				// if the person is free..
				if (personMatch[matchedPerson] == -1)// person is not matched, match dog and person
				{
					// Dog proposes to person -- increment proposal.
					personMatch[matchedPerson] = currentDog;
					//dogFree[currentDog] = false;
					freeDogAmount--;
				}
				else {// Either form new match, or compare with current match.
					// person is already matched to dog2.
					int currentMatch = personMatch[matchedPerson];

					if (personPrefersNewDog(personPref, matchedPerson, currentDog, currentMatch) == false)
					{
						// person prefers new dog, dog2 is unmatched, dog1 and person make new match.
						personMatch[matchedPerson] = currentDog;
						dogFree[currentDog] = false;
						dogFree[currentMatch] = true;
					}
				}
			}
		}
	}

	std::map<int, int> matches;

	for (int i = 0; i < size; i++)
	{
		matches[i] = personMatch[i];
	}
				
	return matches;
}

int main()
{
	// Test 1, from lecture 13A
	std::vector<std::vector<int>> dogPref = {
		{1, 2, 3, 4, 0},
		{2, 3, 4, 1, 0},
		{2, 3, 1, 0, 4},
		{3, 2, 1, 0, 4},
		{2, 3, 0, 1, 4}
	};

	std::vector<std::vector<int>> peoplePref = {
		{1, 3, 2, 4, 0},
		{2, 3, 1, 4, 0},
		{2, 4, 1, 0, 3},
		{1, 2, 3, 0, 4},
		{2, 3, 0, 1, 4}
	};

	std::map<int, int> matches = stableMarriage(dogPref, peoplePref);

	std::cout << "Correct result should see matches of D0-P4, D1-P3, D2-P2, D3-P1 and D4-P0.\n";
	
	for (auto d : matches)
	{
		std::cout << d.first << " was matched with " << d.second << ", ";
	}
	std::cout << "\n";

	// Test 2
	dogPref = {
		{0, 2, 4, 6, 7, 1, 3, 5},
		{1, 3, 2, 0, 4, 5, 6, 7},
		{1, 2, 0, 4, 3, 6, 5, 7},
		{3, 1, 2, 4, 5, 6, 7, 0},
		{2, 0, 3, 1, 5, 7, 6, 4},
		{2, 1, 3, 0, 6, 7, 4, 5},
		{0, 2, 1, 4, 3, 7, 5, 6},
		{2, 3, 0, 1, 5, 7, 6, 4}
	};

	peoplePref = {
		{6, 7, 3, 1, 2, 4, 5, 0},
		{2, 0, 3, 1, 5, 7, 6, 4},
		{2, 1, 3, 4, 5, 0, 6, 7},
		{6, 0, 4, 2, 7, 1, 3, 5},
		{1, 0, 2, 3, 4, 5, 6, 7},
		{0, 4, 3, 5, 6, 7, 1, 2},
		{0, 3, 7, 5, 2, 1, 4, 6},
		{2, 3, 0, 1, 5, 7, 6, 4} 
	};

	matches = stableMarriage(dogPref, peoplePref);

	std::cout << "we are expecting: D0-P4, D1-P2, D2-P1, D3-P5, D4-P3, D5-P6, D6-P0, D7-P7:\n";

	for (auto d : matches)
	{
		std::cout << d.first << " was matched with " << d.second << ", ";
	}

	return 0;
}