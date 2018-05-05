// compile with golf.h and golf.cpp
#include <iostream>
#include "golf.h"

const int ARRAY_SIZE = 4;

int main()
{
	std::cout << "Enter information for up to " << ARRAY_SIZE << " players in the following format:" << std::endl;

	Golf examplePlayer("Tony Stark", 35);
	examplePlayer.ShowGolf();


	Golf golfArray[ARRAY_SIZE];
	int golfArrayCount = 0;


	while (golfArrayCount < ARRAY_SIZE)
	{
		std::cout << "\nENTRY #" << (golfArrayCount + 1) << std::endl;
		if (golfArray[golfArrayCount].SetGolf())
			golfArrayCount++;
		else
			break;
	}

	if (golfArrayCount)
	{
		std::cout << "\n\nHere are your entries:" << std::endl;
		for (int i = 0; i < golfArrayCount; i++)
		{
			std::cout << "\nENTRY #" << (i + 1) << std::endl;
			golfArray[i].ShowGolf();
		}

		std::cout << "\nWould you like to change the handicap of an entry? <y/n> ";
		char ch;
		while (std::cin >> ch)
		{
			if (ch == 'y' || ch == 'Y')
			{
				std::cout << "Enter the number of the entry you want to change: ";
				int inputIndex;
				std::cin >> inputIndex;

				inputIndex--;

				while (std::cin.fail() || inputIndex < 0 || inputIndex > golfArrayCount)
				{
					std::cin.clear();
					std::cin.get();
					std::cout << "\aInvalid entry number. Please enter a valid entry number: ";
					std::cin >> inputIndex;
				}

				std::cout << "Enter the new handicap for " << golfArray[inputIndex].GetName() << ": ";
				int inputHandicap;
				std::cin >> inputHandicap;
				while (std::cin.fail())
				{
					std::cin.clear();
					std::cin.get();
					std::cout << "\aInvalid handicap. Please enter a valid handicap for " << golfArray[inputIndex].GetName() << ": ";
					std::cin >> inputIndex;
				}

				golfArray[inputIndex].Handicap(inputHandicap);

				std::cout << "\nHere's the updated info:" << std::endl;
				golfArray[inputIndex].ShowGolf();

				std::cin.get();

				std::cout << "\nWould you like to change the handicap of another entry? <y/n> ";
			}
			else
				break;
		}
		std::cin.get();
	}
	else
		std::cout << "No information was entered." << std::endl;

	std::cout << "\nBye!" << std::endl;

	std::cin.get();

	return 0;
}