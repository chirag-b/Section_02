#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planes";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if guess isn't an isogram
	if (!IsIsogram(Guess)){
		return EGuessStatus::Not_Isogram; // TODO: Write Function
	}

	// if the guess isn't all lowercase
	else if (!IsLowercase(Guess)){	
		return EGuessStatus::Not_Lowercase; // TODO: Write Function
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
