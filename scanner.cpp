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
  cout << "Trying the dfa1 machine" << endl;
  /* replace the following todo the word dfa  */
  while (s[charpos] != '\0')//while not at the last character
  {
    cout << "current state: " << state << endl;
    cout << "character: " << s[charpos] << endl;

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
      cout << "I am stuck in state " << state << endl;
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
  cout << "Trying the dfa2 machine" << endl;

  while (s[charpos] != '\0')//while not at the last character
  {
    cout << "current state: " << state << endl;
    cout << "character: " << s[charpos] << endl;

    //Transitions from q0
    if (state == "q0" && s[charpos] == '.')
      state = "q1";
    //stuck transition
    else // if the character read is not an a or b then the dfa is stuck
    {
      cout << "I am stuck in state " << state << endl;
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
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "SUBJECT", "OBJECT", "DESTINATION", "PRONOUN", "CONNECTOR"};

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.

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
// ** Done by: Hieu Ryan
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

  if (w == "eofm")
  {
    return EOFM;
  }
  else if (word(w))
  {
    bool rWords = false;
    for (int i = 0; i < 19; i++)
    {
      if (w == reservedWords[i])
      {
        if (reservedWords[i] == "masu")
        {
          tt = VERB;
        }
        else if (reservedWords[i] == "masen")
        {
          tt = VERBNEG;
        }
        else if (reservedWords[i] == "mashita")
        {
          tt = VERBPAST;
        }
        else if (reservedWords[i] == "masendeshita")
        {
          tt = VERBPASTNEG;
        }
        else if (reservedWords[i] == "desu")
        {
          tt = IS;
        }
        else if (reservedWords[i] == "o")
        {
          tt = OBJECT;
        }
        else if (reservedWords[i] == "wa")
        {
          tt = SUBJECT;
        }
        else if (reservedWords[i] == "ni")
        {
          tt = DESTINATION;
        }
        else if (reservedWords[i] == "watashi" || "anata" || "sore" || "kanojo" || "kare")
        {
          tt = PRONOUN;
        }
        else if (reservedWords[i] == "mata" || "soshite" || "shikashi" || "dakara")
        {
          tt = CONNECTOR;
        }
        rWords = true;
        break;
      }
    }
    if (!rWords)
    {
      if (w[w.length() - 1] == 'I' || w[w.length() - 1] == 'E')
      {
        tt = WORD2;
      }
      else
      {
        tt = WORD1;
      }
    }
  }
  else if (period(w))
  {
    tt = PERIOD;
  }
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
