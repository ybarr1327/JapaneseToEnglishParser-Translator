#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream fin; // global stream for reading from the input file

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//scanner.cpp file here------------------------------------------------------------------------------------------

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

string tokentypeStrings(tokentype val)
{
  if(val == 0) return "ERROR";
  if(val == 1) return "WORD1";
  if(val == 2) return "WORD2";
  if(val == 3) return "PERIOD";
  if(val == 4) return "EOFM";
  if(val == 5) return "VERB";
  if(val == 6) return "VERBNEG";
  if(val == 7) return "VERBPAST";
  if(val == 8) return "VERBPASTNEG";
  if(val == 9) return "IS";
  if(val == 10) return "WAS";
  if(val == 11) return "SUBJECT";
  if(val == 12) return "OBJECT";
  if(val == 13) return "DESTINATION";
  if(val == 14) return "PRONOUN";
  if(val == 15) return "CONNECTOR";
}

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

  cout<<"Scanner called using word: " << w <<endl;
  // if w == "eofm"
  if (w == "eofm")
  {
    tt = EOFM; // returns the token type EOFM
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
        } //else if reserved word at i == watashi, anata, sore, kanojo, or kare. Token type is PRONOUN
        else if (reservedWords[i] == "watashi" || reservedWords[i] == "anata" || reservedWords[i] == "sore" || reservedWords[i] == "kanojo" || reservedWords[i] == "kare")
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


//end of scanner.cpp ------------------------------------------------------------------------------------------

//=================================================
// File parser.cpp written by Group Number: Group 9
//  Gabriel Ybarra
//  Ryan Lochrane
//  Hieu Nguyen
//=================================================

tokentype saved_token; // global buffer for the token the scanner returned.
string saved_lexeme; //this is the string being read by the parser
bool token_available; // global flag indicating whether

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

// Type of error: Syntax
// Done by: Ryan Lochrane
//syntaxerror1() takes a string and a token_type parameter and outputs an error message telling the user what the program expected and
//what it found instead.
void syntaxerror1(tokentype expected)
{
  cout << "SYNTAX ERROR: expected " << expected << " but found " << saved_lexeme << "\n";
}
// Type of error: Syntax
// Done by: Ryan Lochrane
//syntaxerror2() takes a string parameter and outputs an error message telling the user that the program
// found an unexpected saved_lexeme in the expected string.
void syntaxerror2(string expected)
{
  cout << "SYNTAX ERROR: unexpected " << saved_lexeme << " found in " << expected << "\n";
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: the next_token function's purpose is to call the scanner to figure out what the token type of the string to be read next is.
// Done by: Gabriel Ybarra.


// we have saved a token to eat up or not

// next_token(void)
// Looks ahead to see what token comes next from the scanner.
// HOW: checks first to see if the token_available flag is false.
// If so, saved_token gets scanner() result.
// and the flag is set true.
// A token is grabbed but is not eaten up.
// Returns the saved_token
//
// A lexeme is a sequence of characters in the source program that matches the pattern for a token
// and is identified by the lexical analyzer as an instance of that token.
tokentype next_token()
{

  if (!token_available) // if there is no saved token yet
  {
    
    scanner(saved_token, saved_lexeme); // call scanner to grab a new token
    
    token_available = true;             // mark that fact that you have saved it
    
  }
  return saved_token; // return the saved token
}

// Purpose: the purpose of the match function is to match the token that was read with the one expected
// Done by: Gabriel Ybarra
//match(expected)
// Checks and eats up the expected token.
// HOW: checks to see if expected is different from next_token()
// and if so, generates a syntax error and handles the error
// else token_available becomes false (eat up) and returns true.
bool match(tokentype expected)
{
  if (next_token() != expected) // mismatch has occurred with the next token
  {
    syntaxerror1(expected);
  }
  else // match has occurred
  {
    token_available = false; // eat up the token
    cout<<"Matched "<< tokentypeStrings(expected) <<endl;
    return true;             // say there was a match
  }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

//prototypes for the RDP functions
void story();
void s();
void after_subject();
void after_noun();
void after_object();
void noun();
void verb();
void be();
void tense();

// Grammar: <s> { <s> }  
// Done by: Gabriel Ybarra
void story()
{
  cout<<"Processing <"<<"story"<<">"<<endl;
  s();
  while (true)
  {
    if (next_token() == EOFM)
    {
      cout << "Sucessfully parsed <story>." << endl;
      break;
    }
    s();
  }
}

// Grammar:<s> ::= [CONNECTOR] <noun> SUBJECT <after_subject>
// Done by: Gabriel Ybarra
void s()
{
  cout<<"Processing <"<<"s"<<">"<<endl;
  switch (next_token())
  {
  case CONNECTOR:
    match(CONNECTOR);
    noun();
    match(SUBJECT);
    after_subject();
    break;
  default:
    noun();
    match(SUBJECT);
    after_subject();
    break;
  }
}

// Grammar: <after_subject> ::= <verb> <tense> PERIOD | <noun> <after_noun>
// Done by: Gabriel Ybarra
void after_subject()
{
  cout<<"Processing <"<<"after_subject"<<">"<<endl;
  switch (next_token())
  {
  case WORD2:
    verb();
    tense();
    match(PERIOD);
    break;

  case WORD1:
  case PRONOUN:
    noun();
    after_noun();
    break;

  default:
    syntaxerror2("after_subject");
    break;
  }
}

// Grammar: <after_noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterObject>
// Done by: Hieu Nguyen

void after_noun() {
  cout<<"Processing <"<<"after_noun"<<">"<<endl;
    switch (next_token()) {
        case IS: case WAS:
            be();
            match(PERIOD);
            break;
        case DESTINATION:
            match(DESTINATION);
            verb();
            tense();
            match(PERIOD);
            break;
        case OBJECT:
            match(OBJECT);
            after_object();
            break;
        default:
            syntaxerror2("after_noun");
    }

}

// Grammar: <after_object> ::= <noun> DESTINATION <verb> <tense> PERIOD | <verb> <tense> PERIOD
// Done by: Hieu Nguyen

void after_object() {
  cout<<"Processing <"<<"after_object"<<">"<<endl;
    switch (next_token()) {
        case WORD1: case PRONOUN:
            noun();
            match(DESTINATION);
            verb();
            tense();
            match(PERIOD);
            break;
        case WORD2:
            verb();
            tense();
            match(PERIOD);
            break;
        default:
            syntaxerror2("after_object");
    }

}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Hieu Nguyen


void noun(){
  cout<<"Processing <"<<"noun"<<">"<<endl;
    switch (next_token()) {
        case WORD1:
            match(WORD1);
            break;
        case PRONOUN:
            match(PRONOUN);
            break;
        default:
            syntaxerror2("noun");
    }

}

// Grammar: <verb> ::= WORD2
// Done by: Ryan Lochrane
void verb()
{
  cout<<"Processing <"<<"verb"<<">"<<endl;
  //switch statement that calls next_token() and looks for the case where WORD2 is found
  switch (next_token())
  {
    //case WORD2 looks calls match() to look for WORD2
  case WORD2:
    match(WORD2);
    //break from the switch
    break;
  // default case where syntaxerror2() is called to display error message
  default:
    syntaxerror2("verb");
    //break form the switch
    break;
  }
}

// Grammar: <be> ::= IS | WAS
// Done by: Ryan Lochrane
void be()
{
  cout<<"Processing <"<<"be"<<">"<<endl;
  //switch statement that calls next_token() and looks for the below cases
  switch (next_token())
  {
    //case IS looks calls match() to look for IS
  case IS:
    match(IS);
    //break form the switch
    break;
    //case WAS looks calls match() to look for WAS
  case WAS:
    match(WAS);
    //break form the switch
    break;
    // default case where syntaxerror2() is called to display error message
  default:
    syntaxerror2("be");
    //break form the switch
    break;
  }
}

// Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Ryan Lochrane
void tense()
{
  cout<<"Processing <"<<"tense"<<">"<<endl;
  //switch statement that calls next_token() and looks for the below cases
  switch (next_token())
  {
    //case VERBPAST looks calls match() to look for VERBPAST
  case VERBPAST:
    match(VERBPAST);
    //break form the switch
    break;
  //case VERBPASTNEG looks calls match() to look for VERBPASTNEG
  case VERBPASTNEG:
    match(VERBPASTNEG);
    //break form the switch
    break;
  //case VERB looks calls match() to look for VERB
  case VERB:
    match(VERB);
    //break form the switch
    break;
  //case VERBNEG looks calls match() to look for VERBNEG
  case VERBNEG:
    match(VERBNEG);
    //break form the switch
    break;

  default:
    syntaxerror2("tense");
    //break form the switch
    break;
  }
}


string filename; // this is the name of the file that will be read from

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Hieu Nguyen
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  story();     //** calls the <story> to start parsing
  fin.close(); //** closes the input file

} // end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
