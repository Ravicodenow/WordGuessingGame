// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Hiddenwordlist.h"
//#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    Isograma = GetValidWords(Words);
    SetUpGame();   
    
    // PrintLine(TEXT("%i"), FMath::RandRange(0, 10));
    // PrintLine(TEXT("The Number of Possible words is %i."),Words.num());
    // PrintLine(TEXT("The Number of valid words is %1."),GetValidWords(Words).Num());
    // PrintLine(TEXT("ValidWord -1 is =%i."),GetValidWords(Words).Num()- 1);
    //for loop for print 5 words from words list                                        
}

void UBullCowCartridge::OnInput(const FString& PlayerInput)    // When the player hits enter
{
    
  // If the Game is Over then clear the  screen and setupGaame() the guess
       
  if(bGameOver)
   {
    ClearScreen();
    SetUpGame();
   }
    else
   {
    ProcessGuess(PlayerInput);
   }
}      

void UBullCowCartridge::SetUpGame()
{
     //Welcoming the Players
        PrintLine(TEXT("Welcome to Bull Cow!"));
        HiddenWord=Isograms[FMath::RandRange(0,Isograms.Num() - 1)];//first element in the heddenwords show 
        Lives = HiddenWord.Len()*2;

        bGameOver =false;  
        PrintLine(TEXT("Guess the %i letter word!"),HiddenWord.len());    //Magic words
        PrintLine(TEXT("You have %i live"),Lives);
        PrintLine(TEXT("Type in your guess and Press enter to continue..."));  
        
       // PrintLine((TEXT("The Hidden Word is: %s."),*HiddenWord));//debug Line
        //promt player for guess
        // const TCHAR HW[6] = TEXT("cakes");
        // PrintLine(TEXT("Characture 1 of the hidden word is: %c"),HiddenWord[0]);//print 'c'
        // PrintLine(TEXT("The 4th characture of HW is: %c"),WH[3]);//print'm'
      

}
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    
    PrintLine(TEXT("\nPress enter to play again."));

}
void UBullCowCartridge:: ProcessGuess(const FString& Guess)
{
  if(Guess == HiddenWord)
  {
    PrintLine(TEXT("You have Won!"));
    EndGame();  
    return;    
  }
           
           
            if(Guess.Len() != HiddenWord.Len())
          {
            PrintLine(TEXT("Sorry,try guessing again! \n You have %i lives remaining"),Lives);
            PrintLine(TEXT("The HiddenWord is %i letter long"),HiddenWord.Len());
            return;
          }
           //If is an isogram
            //Promt to guess  again 
            //check right number of characture
           if(!IsIsogram(Guess))
            {
              PrintLine(TEXT("No Repeating letters, guess again"));
              return;
            }
            // Remove life
            PrintLine(TEXT("Lost a life!"));
            PrintLine(TEXT("%i"),--Lives);
          if(Lives > 0)
             {
            ClearScreen();
            PrintLine(TEXT("You have no lives left!"));
            PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
            EndGame();
            return;
             }
        }
            //Show player the Bulls and COWS
           FBullCowCount Score =  GetBullCows(Guess);
            PrintLine(TEXT("You Have %i Bull and Cows"),Score.Bulls,Score.Cows);
        PrintLine(TEXT("Guess again,you have %i lives left"),Lives);
}


bool UBullCowCatridge::IsIsogram(const FSring& Word) const
{
  for(int32 index = =0;Index < Word.Len(); Index++)
  {
    for(int32 Comparison = Index +1; Comparison < Word.Len();Comparison++)
    {
      if(Word[Index] ==Word[Comparison])
      {
        return false;
      }
    }
  }
   return true;


  TArray<FString>UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
  {
    TArray<FString> ValidWords;
    for(FString Word : WordList )//new Way of writing for loop
    { 
      
      if(Word.Len() >=4 && Word.Len() <=8 && IsIsogram(Word))
      {
        
           ValidWords.Emplace(Word);       
      }
    }  
    return ValidWords;      
  }
}
FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
   FBullCowCount Count;
  for(int32 GuessIndex=0; GuessIndex <Guess.Len();GuessIndex++)
  {
    if(Guess[GuessIndex] == HiddenWord[GuessIndex])
    {
      Count.Bull++;
      continue;
    }
    for(int32 HiddenIndex = 0 ;HiddenIndex < HiddenWord.Len();HiddenIndex++)
    {
      if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
      {
        Count.Cows++;
        break;
      }
    }
  }
  return Count;
}