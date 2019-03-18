/*
	This is the console executable, that makes use of the BullCow Class
	This acts as the view in the MVC pattern, and is responsible for all
	user interaction. For game logic see the FBullCowGame class.
*/

// TODO: Read and understand MVC

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary(bool);


FBullCowGame BCGame; // instantiate a new game

// entry into the game
int main()
{
	bool bPlayAgain = false;

	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		
	} while (bPlayAgain);
 

	return 0;
}

 
// introduce the game
void PrintIntro()
{
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	// TODO ASCII ART
	std::cout << std::endl;
	std::cout << "    /|   BULLS   |\\	         COWS       " << std::endl;
	std::cout << "  _(_|___________|_)_      _/|___________|\\ _     " << std::endl;
	std::cout << " /__\\ ( O ) ( O ) /__\\   /__\\ ( O ) ( O ) /__\\     " << std::endl;
	std::cout << "     \\           /           \\           /     " << std::endl;
	std::cout << "      \\ _______ /      AND    \\ _______ /        " << std::endl;
	std::cout << "       ( O   O )               ( O   O )          " << std::endl;
	std::cout << "       | _____ |               ( _____ )          " << std::endl;
	std::cout << "       (_______)                        "<< std::endl << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of m8?" << std::endl;
	std::cout << std::endl;

	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl;
 		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}

	PrintGameSummary(BCGame.IsGameWon());

	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{ 
	EGuessStatus Status = EGuessStatus::Invalid_State;
	FText Guess = "";
	
	do {
		// Get current try
		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout <<". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
	
		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a "
					<< BCGame.GetHiddenWordLength()
					<< " letter word.\n\n";
				break;

			case EGuessStatus::Not_Lowercase:
				std::cout << "Some or all letters aren't lowercase! Please enter only lower case letters.\n\n";
				break;

			case EGuessStatus::Not_Isogram:
				std::cout << "This isn't an isogram! Please enter words without repeating letters.\n\n";
				break;

			default:
				break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n) ? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

void PrintGameSummary(bool bGameWon)
{
	// check for the status of GameWon
	// if game is won
	if (bGameWon)
	{
		// print +ve message
		std::cout << "THAT'S IT!! YOU DID IT!!" << std::endl;
	}

	// else
	else
	{
		std::cout << "Sorry, Better Luck Next Time.\n" << std::endl;

	}

}