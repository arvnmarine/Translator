#include<iostream>
#include<fstream>
#include<string>
using namespace std;

ifstream fin;


//=====================================================
// File scanner.cpp written by: Group Number: 18** 
//=====================================================


bool vowel(char c) { //check for a e i o u and I E
	return ((c=='a')||(c=='e')||(c=='i')||(c=='o')||(c=='u')||(c=='I')||(c=='E'));
}

bool br(char c) {// check for consonant b   g h   k m n  p r    
	return ((c=='b')||(c=='g')||(c=='h')||(c=='k')||(c=='m')||(c=='n')||(c=='p')||(c=='r'));
}

bool dz(char c) {// check for the start of consonant pair d j w y z  
	return ((c=='d')||(c=='j')||(c=='w')||(c=='y')||(c=='z'));
}


// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by:Nam Ho
// ** RE: (vowel | vowel n | br vowel | br vowel n | br y vowel | br y vowel n | dz vowel | dz vowel n | s vowel | s vowel n| sh vowel | sh vowel n | ch vowel | ch vowel n | ts vowel | ts vowel n)^+




bool mytoken(string s)
{
  int state = 0;
  int charpos = 0;
  //cout << "dsada " <<s<< " " <<s.length()<<endl;

  while (charpos < s.length()) 
    {
		//cout << state<< " " <<s[charpos] <<endl;
      if (state == 0 && vowel(s[charpos])){
      state = 2;}
      else
      if (state == 0 && br(s[charpos])){
      state = 1;}
      else
      if (state == 0 && dz(s[charpos])){
      state = 3;}
      else
		if (state == 0 && (s[charpos]=='s')){
		state = 4;}
      else
		  if (state == 0 && (s[charpos]=='c')){
      state = 5;}
      else
		  if (state == 0 && (s[charpos] == 't')){
      state = 6;}
      else
		  if (state == 1 && vowel(s[charpos])){
      state = 2;}
      else
		  if (state == 1 && (s[charpos]=='y')){
      state = 3;}
      else
		  if (state == 2 && (s[charpos]=='n')){
      state = 0;}
      else
		  if (state == 2 && vowel(s[charpos])){
      state = 2;}
      else
		  if (state == 2 && br(s[charpos])){
      state = 1;}
      else 
		  if (state == 2 && dz(s[charpos])){
      state = 3;}
      else
		  if (state == 2 && (s[charpos]=='s')){
		state = 4;}
      else
		  if (state == 2 && (s[charpos]=='c')){
      state = 5;}
      else
		  if (state == 2 && (s[charpos] == 't')){
      state = 6;}
      else
		  if (state == 3 && vowel(s[charpos])){
      state = 2;}
      else
		  if (state == 4 && vowel(s[charpos])){
      state = 2;}
      else
		  if (state == 4 && (s[charpos]=='h')){
      state = 3;}
      else
		  if (state == 5 && (s[charpos]=='h')){
      state = 3;}
      else
		  if (state == 6 && (s[charpos]=='s')){
      state = 3;}
      else
		  if (state == 6 && vowel(s[charpos])){
      state = 2;}
      else
	  return(false);
      charpos++;
    }//end of while

  // where did I end up????
  //cout <<state<<endl;
  if ((state == 0)||(state == 2)) return(true);  // end in a final state
   else return(false);
}

// ** Add the PERIOD DFA here
// ** Done by:Nam Ho

bool periodToken(string s) {
	return(s==".");
}


// ** Update the tokentype to be WORD1, WORD2, PERIOD and ERROR.
enum tokentype {WORD1, WORD2, PERIOD, ERROR, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};

// ** Need the lexicon to be set up here (to be used in Part C)
// ** Need the reservedwords list to be set up here
// ** Do not require any file input for these.
// ** a.out should work without any additional files.



// Scanner processes only one word each time it is called
// ** Done by: Nam Ho
int scanner(tokentype& a, string& w)
{

  // ** Grab the next word from the file
  if (!(fin>>w)) {return 0;}
  

  /* 
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error if both DFAs failed.
     Let the token_type be ERROR in that case.
  3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.
  4. Return the token type & string  (pass by reference)
  */
	if (w == "gakkou") {a = WORD1;} else
	if (w == "masu") {a = VERB;} else
	if (w == "masen") {a = VERBNEG;} else
	if (w == "mashita") {a = VERBPAST;} else
	if (w == "masendeshita") {a = VERBPASTNEG;} else
	if (w == "desu") {a = IS;} else
	if (w == "deshita") {a = WAS;} else
	if (w == "o") {a = OBJECT;} else
	if (w == "wa") {a = SUBJECT;} else
	if (w == "ni") {a = DESTINATION;} else
	if ((w == "watashi") || (w == "anata") || (w == "kare")|| (w == "kanojo") || (w == "sore")) {a = PRONOUN;} else
	if ((w == "mata") || (w == "soshite") || (w == "shikashi")|| (w == "dakara")) {a = CONNECTOR;} else
	if (w == "eofm") {a = EOFM;} else
	if (mytoken(w)) {
	  a = WORD1;
	  if ((w[w.length()-1] == 'I') || (w[w.length()-1] == 'E')) {
		  a = WORD2;
	  }
	  
	} else 
	if (periodToken(w)) {
	  a = PERIOD;
	} else {
		a= ERROR;
		cout << "Lexical error: " << w << "is not a valid token" << endl;
		
	}
  
  return 1;
  

}//the end



// The test driver to call the scanner repeatedly  
// ** Done by: Nam Ho **




int main()
{
  tokentype thetype;
  string theword; 

  /*
1. get the input file name from the user
2. open the input file which contains a story written in Japanese (fin.open).
3. call Scanner repeatedly until the EOF marker is read, and
     each time cout the returned results
     e.g. STRING TOKEN-TYPE
          =====  ===========
          watashi PRONOUN  (from the first call)
          wa      SUBJECT  (from the second call)
          gakkou  WORD1
          etc.
  */
  
  string inName;
  cout << "Input file? "; cin >> inName;
  
  fin.open(inName.c_str());
  
  
	
	string typeName[16] = {"WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"};
  while (true)
    {
      if ((scanner(thetype, theword) == 0) || (thetype == EOFM)) {break;}  // call the scanner
       cout << "Type is:" << typeName[thetype] << endl;
       cout << "Word is:" << theword << endl <<endl;   

       // ** display the actual type instead of a number
	   

    }

  // ** close the input file
  fin.close();

}// end



