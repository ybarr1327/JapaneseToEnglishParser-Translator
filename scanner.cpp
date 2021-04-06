#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by:
//  Gabriel Ybarra
//  Ryan Lochrane
//  Hieu Nguyen
// Group Number: 9
//=====================================================

// --------- Two DFAs ---------------------------------

/**********************************************************************************
isVowel function
Parameters: 
 char c
   takes a character c as an input to test
Purpose
this function tests if the character is a vowel which includes aeiouIE characters
returns true if it is in these characters false if not
**********************************************************************************/
bool isVowel(char c)
{
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'I' || c == 'E');
}

/**********************************************************************************
is_bghkmpr function
Parameters: 
 char c
   takes a character c as an input to test
Purpose
this function tests if the character is one of the possible characters bghkmpr
returns true if it is in these characters false if not
**********************************************************************************/
bool is_bghkmpr(char c)
{
  return (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'p' || c == 'r');
}

/**********************************************************************************
is_dwzyj function
Parameters: 
 char c
   takes a character c as an input to test
Purpose
this function tests if the character is one of the possible characters dwzyj
returns true if it is in these characters false if not
**********************************************************************************/
bool is_dwzyj(char c)
{
  return (c == 'd' || c == 'w' || c == 'z' || c == 'y' || c == 'j');
}

// WORD DFA
// Done by: Gabriel Ybarra
// RE:   (vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+

bool word(string s)
{
  //defining the state and pos
  string state = "q0";
  int charpos = 0;
  // cout << "Trying the dfa1 machine" << endl;
  /* replace the following todo the word dfa  */
  while (s[charpos] != '\0') //while not at the last character
  {
    // cout << "current state: " << state << endl;
    // cout << "character: " << s[charpos] << endl;

    //Transitions from q0
    if (state == "q0" && is_dwzyj(s[charpos]))
      state = "qsa";
    else if (state == "q0" && (is_bghkmpr(s[charpos]) || s[charpos] == 'n'))
      state = "qy";
    else if (state == "q0" && isVowel(s[charpos]))
      state = "q0q1";
    else if (state == "q0" && (s[charpos] == 't'))
      state = "qt";
    else if (state == "q0" && (s[charpos] == 's'))
      state = "qs";
    else if (state == "q0" && (s[charpos] == 'c'))
      state = "qc";
    //transitions from qsa
    else if (state == "qsa" && isVowel(s[charpos]))
      state = "q0q1";
    //transitions from qy
    else if (state == "qy" && isVowel(s[charpos]))
      state = "q0q1";
    else if (state == "qy" && (s[charpos] == 'y'))
      state = "qsa";
    //transitions from qt
    else if (state == "qt" && isVowel(s[charpos]))
      state = "q0q1";
    else if (state == "qt" && (s[charpos] == 's'))
      state = "qsa";
    //transitions from qs
    else if (state == "qs" && isVowel(s[charpos]))
      state = "q0q1";
    else if (state == "qs" && (s[charpos] == 'h'))
      state = "qsa";
    //transitions from qc
    else if (state == "qc" && (s[charpos] == 'h'))
      state = "qsa";
    //transitions from q0q1
    else if (state == "q0q1" && isVowel(s[charpos]))
      state = "q0q1";
    else if (state == "q0q1" && s[charpos] == 'n')
      state = "q0qy";
    else if (state == "q0q1" && (s[charpos] == 't'))
      state = "qt";
    else if (state == "q0q1" && (s[charpos] == 's'))
      state = "qs";
    else if (state == "q0q1" && (s[charpos] == 'c'))
      state = "qc";
    else if (state == "q0q1" && is_bghkmpr(s[charpos]))
      state = "qy";
    else if (state == "q0q1" && is_dwzyj(s[charpos]))
      state = "qsa";
    //transitions from q0qy
    else if (state == "q0qy" && s[charpos] == 't')
      state = "qt";
    else if (state == "q0qy" && s[charpos] == 's')
      state = "qs";
    else if (state == "q0qy" && s[charpos] == 'c')
      state = "qc";
    else if (state == "q0qy" && isVowel(s[charpos]))
      state = "q0q1";
    else if (state == "q0qy" && (is_bghkmpr(s[charpos]) || s[charpos] == 'n'))
      state = "qy";
    else if (state == "q0qy" && is_dwzyj(s[charpos]))
      state = "qsa";
    //stuck transition
    else // if the character read is not an a or b then the dfa is stuck
    {
      // cout << "I am stuck in state " << state << endl;
      return (false);
    }
    charpos++; //move to the next character
  }            //end of while

  // where did I end up????
  if (state == "q0" || state == "q0q1" || state == "q0qy")
    return (true); // end in a final state
  else
    return (false);
}

// PERIOD DFA
// Done by: Gabriel Ybarra
// RE: .
bool period(string s)
{ // complete this **
  //defining the state and pos
  string state = "q0";
  int charpos = 0;
  // cout << "Trying the dfa2 machine" << endl;

  while (s[charpos] != '\0') //while not at the last character
  {
    // cout << "current state: " << state << endl;
    // cout << "character: " << s[charpos] << endl;

    //Transitions from q0
    if (state == "q0" && s[charpos] == '.')
      state = "q1";
    //stuck transition
    else // if the character read is not an a or b then the dfa is stuck
    {
      // cout << "I am stuck in state " << state << endl;
      return (false);
    }
    charpos++; //move to the next character
  }            //end of while

  // where did I end up????
  if (state == "q1")
    return (true); // end in a final state
  else
    return (false);
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Hieu, Ryan

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
// tokentype is an enumerated list of the token types
enum tokentype
{
  ERROR,
  WORD1,
  WORD2,
  PERIOD,
  EOFM,
  VERB,
  VERBNEG,
  VERBPAST,
  VERBPASTNEG,
  IS,
  WAS,
  SUBJECT,
  OBJECT,
  DESTINATION,
  PRONOUN,
  CONNECTOR
};

// ** For the display names of tokens - must be in the same order as the tokentype.

// tokenName is a string array that contains the display names of the tokens.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "SUBJECT", "OBJECT", "DESTINATION", "PRONOUN", "CONNECTOR"};

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.

//ReservedWords is a string array that contains a set of reserved words
string reservedWords[19] = {
    //taken from reservedwords.txt
    //words: tokentype:

    "masu",         // VERB
    "masen",        // VERBNEG
    "mashita",      //VERBPAST
    "masendeshita", // "ERBPASTNEG
    "desu",         // IS
    "deshita",      // WAS
    "o",            //OBJECT
    "wa",           // SUBJECT
    "ni",           //ESTINATION
    "watashi",      //PRONOUN
    "anata",        //PRONOUN
    "sore",         //PRONOUN
    "kanojo",       //PRONOUN
    "kare",         //PRONOUN
    "mata",         // CONNECTOR
    "soshite",      //CONNECTOR
    "shikashi",     //"ONNECTOR
    "dakara",       //CONNECTOR
    "eofm",         //EOFM
};

// ------------ Scaner and Driver -----------------------

ifstream fin; // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Hieu, Ryan
int scanner(tokentype &tt, string &w)
{

  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.

  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */

  fin >> w;
  // if w == "eofm"
  if (w == "eofm")
  {
    return EOFM; // returns the token type EOFM
  }
  //else if word(w) returns true
  else if (word(w))
  {
    // bool variable rWords set to false
    bool rWords = false;
    //for loop to loop through the list of reserved words and if the word
    //is a reserved word, the tokenType is updated and we break from the loop.
    //if the word is not a reserved word, we check if the last letter in the word is either an I or and E
    // which then wetermines if its token type is either word1 or word2.
    //We then check is the function period(w) is true and if so, we update the token type to PERIOD.
    //if none of the above conditions are true then we conclude the it is a lexical error and the token type is
    //set to ERROR.
    for (int i = 0; i < 19; i++)
    {

      if (w == reservedWords[i])
      { //if reserved word at i == masu token type is VERB
        if (reservedWords[i] == "masu")
        {
          tt = VERB;
        } //else if reserved word at i == masen token type is VERBNEG
        else if (reservedWords[i] == "masen")
        {
          tt = VERBNEG;
        } //else if reserved word at i == mashita token type is VERBPAST
        else if (reservedWords[i] == "mashita")
        {
          tt = VERBPAST;
        } //else if reserved word at i == masendeshita token type is VERBPASTNEG
        else if (reservedWords[i] == "masendeshita")
        {
          tt = VERBPASTNEG;
        } //else if reserved word at i == desu token type is IS
        else if (reservedWords[i] == "desu")
        {
          tt = IS;
        } //else if reserved word at i == o token type is OBJECT
        else if (reservedWords[i] == "o")
        {
          tt = OBJECT;
        } //else if reserved word at i == wa token type is SUBJECT
        else if (reservedWords[i] == "wa")
        {
          tt = SUBJECT;
        } //else if reserved word at i == ni token type is DESTINATION
        else if (reservedWords[i] == "ni")
        {
          tt = DESTINATION;
        } //else if reserved word at i == deshita, token type is WAS
        else if (reservedWords[i] == "deshita")
        {
          tt = WAS;
        }//else if reserved word at i == watashi, anata, sore, kanojo, or kare. Token type is PRONOUN
        else if (reservedWords[i] == "watashi" || reservedWords[i] ==  "anata" || reservedWords[i] == "sore" || reservedWords[i] == "kanojo" || reservedWords[i] == "kare")
        {
          tt = PRONOUN;
        } //else if reserved word at i == mata, soshite, shikashi, or dakara. Token type is CONNECTOR
        else if (reservedWords[i] == "mata" || reservedWords[i] == "soshite" || reservedWords[i] == "shikashi" || reservedWords[i] == "dakara")
        {
          tt = CONNECTOR;
        }
        //set the bool variable rWords to true because w is a reserved word
        rWords = true;
        //break form the loop
        break;
      }
    }
    //If the bool variable rWords is currently set to false,meaning that the word is not a reserved word, then look at the last letter of the word
    //and determine if it is an I or an E
    if (!rWords)
    {
      //If the last letter of the word is either an I or an E the tokentype is WORD2
      if (w.back() == 'I' || w.back() == 'E')
      {
        tt = WORD2;
      }
      //If not an I or and E, the tokentype is WORD1
      else /*if (w.back() == 'a'||w.back() == 'e'||w.back() == 'i'||w.back() == 'o'||w.back() == 'u')*/
      {
        tt = WORD1;
      }
      // else
      // {
      //   cout << "Lexical error: " << w << " is not a valid token" << endl;
      //   tt = ERROR;
      // }
    }
  }
  //Call the period() to check if there is a period after the word. If so token type is PERIOD
  else if (period(w))
  {
    tt = PERIOD;
  }
  //None of the above tokentypes have been found therefore a lexical error has occured and the tokenType ERROR is assigned
  else
  {
    cout << "Lexical error: " << w << " is not a valid token" << endl;
    tt = ERROR;
  }

  return 0;

} //the end of scanner

// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword;
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
  while (true)
  {
    scanner(thetype, theword); // call the scanner which sets
                               // the arguments
    if (theword == "eofm")
      break; // stop now

    cout << "Type is:" << tokenName[thetype] << endl;
    cout << "Word is:" << theword << endl;
    cout << endl;
  }

  cout << "End of file is encountered." << endl;
  fin.close();

} // end
