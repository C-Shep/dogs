// CMP201 AX1.8 The dog adoption problem.
// Author: William Kavanagh
// Partial Framework

#include <map>
#include <vector>
#include <queue>
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
	if (matches.find(person) == matches.end())
	{
		return true;
	}
	else {
		return false;
	}

	return 0;
}

std::map<int, int> stableMarriage(std::vector<std::vector<int>> dogPref, std::vector<std::vector<int>> personPref)
{
	// Assessed, 3 marks.
	typedef std::vector<int> wantList;
	typedef std::map<int, int> pairs;

	int size = dogPref.size();

	std::queue<int> freeDogs;

	for (int i = 0; i < size; i++)
	{
		freeDogs.push(dogPref[i][0]);
	}

	int freeDogAmount = size;

	pairs matched;

	while (!freeDogs.empty())
	{
		const int& currentDawg = freeDogs.front();
		const wantList& wantlist = dogPref[currentDawg];

		for (wantList::const_iterator it = wantlist.begin(); it != wantlist.end(); ++it)
		{
			const int& wantedPerson = *it;
			
			if (dogMatchedToPerson(wantedPerson, matched))
			{
				matched[wantedPerson] = currentDawg;
				break;
			}

			const int& wantedDog = matched[wantedPerson];

			if (personPrefersNewDog(personPref, wantedPerson, currentDawg, wantedDog))
			{
				freeDogs.push(wantedDog);
				matched[wantedPerson] = currentDawg;
				break;
			}
		}

		freeDogs.pop();
	}
	return matched;
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