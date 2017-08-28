# Bulls vs Cows - Notes

* How much planning should we do?
* Define the emotional **problem** the game solves*
* Chose concept, rules & **requirements**
* Start to think about the architecture
* Copy as much as possible into the code
* Document now what may change later

*McConnell, Steve. Code Comlete. Microsoft Press 2004. Chapter 3.3

## The Problem

* I want a mental challenge
* I want to feel smart / prove myself
* I miss word puzzles
* I want to prove myself
* I want to challenge (feel superior to) someone

## Concept & Rules

* This is a "guess the isogram" game
* An isogram is a word with no repeating letters
* The user has a limited number of guesses.
* After each guess the computer outpurs...
    * Bull = right letter in the right place
    * Cow = right letter in the wrong place
* You win by guessing the word within max tries

## Write up the requirements

* What will the **inputs** be? In what format?
* What will the **outputs** be?
* What **tasks** will the user be asked to do?
* Any **performances** limits worth mentioning?
* What **assets** (art, sound, story text) do we need?

### TODO: Requirements (Dalton-student's  version)

* input: A single letter (char)
* output: "cow" or "bull" or a "complete miss"
Since this is a "terminal-console" game all the inputs and outputs will be in plain text via keyboard
* Assets:
    * some ASCII art for the "Main Menu"
    * maybe some texts for the formatted questions, answers and general messages
* No perfomance limitations here, since this is a console game

### Requirements (teacher's version)

* Plain text instructions for all interactions
* Code to deal with the player, helping make a valid guess (e.g. all lowercase, an isogram, right lenght)
* Code to check the number of Bulls and Cows in the guess, compared the hidden word
* Code to keep track of the number of valid guesses

### Possible Future Ideas (The NO list)

* Give feedback on every press
* Have a large dictionary of hidden words
* User selectable word lenght, and difficulty
* Checking the user's guess is a dictionary isogram
* Providing a time limit for the guesses
* A hint system, spend a turn for a hint

## Types in Unreal

IN Unreal we use

'''CSharp
using FText = std::string;  // when 
using FString = std::string;
'''