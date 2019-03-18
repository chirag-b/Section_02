#include "FBullCowGame.h"
#include <map>
#pragma once

// to make syntax more Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const {
	//return MyMaxTries; 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 10}, {5, 15}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset() // defult constructor
{
	const FString HIDDEN_WORD = "planes"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if guess isn't an isogram
	if (!IsIsogram(Guess)){
		return EGuessStatus::Not_Isogram;
	}

	// if the guess isn't all lowercase
	else if (!IsLowercase(Guess)){	
		return EGuessStatus::Not_Lowercase;
	}

	//if the guess length is wrong
	else if (Guess.length() != GetHiddenWordLength()){
		return EGuessStatus::Wrong_Length;
	}

	// otherwise
	else{
		return EGuessStatus::OK;
	}

	return EGuessStatus::OK;
}

// receives a VALID guess, increments the bulls and cows
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length(); // assuming guess is same length

	// loop through all letters in the hidden
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess word.
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if they're in the same position
				if (MHWChar == GChar)
				{
					// increment bulls ==> same position match
					BullCowCount.Bulls++;
				}
				// else
				else
				{
					// increment cows ==> letter exists but out of position
					BullCowCount.Cows++;
				}
			}

		}

	}

	if (BullCowCount.Bulls == WordLength){
		bGameWon = true;
	}else{
		bGameWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram (FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	  
	TMap<char, bool> LetterSeen;
	// loop through all characters in guess
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		// if the letter is already in the table
		if (LetterSeen[Letter] == true) { 
			return false; 
		} else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() <= 1) {
		return true;
	}

	for (auto Letter : Word)
	{
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
