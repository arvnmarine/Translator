#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;

ifstream fin;
ofstream fout;
//string saved_E_word;
//string s = "";

//=================================================
// File parser.cpp written by Group Number: 18
//=================================================

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)

// ** Need the updated match and next_token (with 2 global vars)
 
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function

bool vowel(char c) { //check for a e i o u and I E
	return ((c=='a')||(c=='e')||(c=='i')||(c=='o')||(c=='u')||(c=='I')||(c=='E'));
}

bool br(char c) {// check for consonant b   g h   k m n  p r    
	return ((c=='b')||(c=='g')||(c=='h')||(c=='k')||(c=='m')||(c=='n')||(c=='p')||(c=='r'));
}

bool dz(char c) {// check for the start of consonant pair d j w y z  
	return ((c=='d')||(c=='j')||(c=='w')||(c=='y')||(c=='z'));
}

enum IR { CONNECT, ACTOR, OBJ, TO, ACTION, TENSE};

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
  
  
  if (!(fin>>w)) {a = EOFM; return 0;}
  

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
	if ((w == "eofm") ||(w == "EOFM")) {a = EOFM;} else
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
		cout << "Lexical error: " << w << " is not a valid token" << endl;
		
	}
  
  return 1;
  

}//the end

string typeName[16] = {"WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"};
 
bool match(tokentype& a,tokentype b){
	return (a==b);
}


string theEword[6] = {"CONNECTOR","ACTOR","OBJECT", "TO", "ACTION", "TENSE"};
string printWords[6] = {"CONNECTOR","ACTOR","OBJECT", "TO", "ACTION", "TENSE"};
void gen( string s, IR w)
{
	///cout << "GEN" << endl;
	theEword[w] = s;	
}
string getEword( string w )
{
	string wordToReturn = w;
	///cout << "getEWORD" << endl;
	
	if(w == "dakara") //The series of if else statements will find english translation.
	{
		wordToReturn = "Therefore";
		return wordToReturn;
	}
	else if( w == "shikashi")
	{
		wordToReturn = "However";

		return wordToReturn;
	}
	else if( w == "soshite")
	{
		wordToReturn = "Then";
		return wordToReturn;
	}
	else if( w == "mata")
	{
		wordToReturn = "Also";
		return wordToReturn;
	}
	else if( w == "watashi")
	{
		wordToReturn = "I/me";
		return wordToReturn;
	}
	else if( w == "anata")
	{
		wordToReturn = "you";
		return wordToReturn;
	}
	else if( w == "kare")
	{
		wordToReturn = "he/him";
		return wordToReturn;
	}
	else if( w == "kanojo")
	{
		wordToReturn = "she/her";
		return wordToReturn;
	}
	else if( w == "sore")
	{
		wordToReturn = "it";
		return wordToReturn;
	}
	else if( w == "ni")
	{
		wordToReturn = "DESTINATION";
		return wordToReturn;
	}
	else if( w == "deshita")
	{
		wordToReturn = "WAS";
		return wordToReturn;
	}
	else if( w == "desu")
	{
		wordToReturn = "IS";
		return wordToReturn;
	}
	else if( w == "masendeshita")
	{
		wordToReturn = "VERBPASTNEG";
		return wordToReturn;
	}
	else if( w == "mashita")
	{
		wordToReturn = "VERBPAST";
		return wordToReturn;
	}
	else if( w == "masen")
	{
		wordToReturn = "VERBNEG";
		return wordToReturn;
	}
	else if( w == "masu")
	{
		wordToReturn = "VERB";
		return wordToReturn;
	}	
	else //If you cant find the translation to english return the original word
	{
		return wordToReturn;
	}
}


bool parsing_noun(tokentype thetype, string theword){
	//tokentype thetype;
	//string theword; 
	///cout << "Processing <noun>" <<endl;
	//scanner(thetype, theword);
	if (match(thetype,PRONOUN)){
		///cout << "Matched PRONOUN" <<endl;
	} else if (match(thetype,WORD1)) {
		
	/// "Matched WORD1" << endl;
	} else {
		cout << "Unexpected "<< theword << " found in noun."<<endl;
		//return false;
		exit(1);
	}
	
	return true;
}
bool parsing_verb(tokentype thetype, string theword){
	
	//tokentype thetype;
	//string theword;
	///cout << "Processing <verb> " << endl;
	
	//scanner(thetype, theword);
	if (!(match(thetype,WORD2))){
		//cout << "SYNTAX ERROR: expected "<<typeName[VERB]<<" but found "<< theword <<endl;
		return false;
	} else {
		
	///	cout << "Matched WORD2\n";
		return true;
	
	}
}
bool parsing_tense(string& saved_E_word){
	tokentype thetype;
	string theword;
	///cout << "Processing <tense> " << endl;
	
	scanner(thetype, theword);
	saved_E_word = theword;
	
	if ( (match(thetype,VERBPAST) )){
		
	///	cout << "Matched VERBPAST" << endl;
		
	} else if( (match(thetype,VERB) )){
		
	///	cout << "Matched VERB" << endl;
	} else if( (match(thetype,VERBPASTNEG) )){
		
	///	cout << "Matched VERBPASTN" << endl;
	} else if( (match(thetype,VERBNEG) )){
		
	///	cout << "Matched VERBN" << endl;
	} else{
		cout << "Unexpected "<< theword << " found in tense."<<endl;
		exit(1);
	} 
	
	return true;
}


bool parsing_s4(string s)
{
	///cout << "Processing <s4>" <<endl;
	tokentype thetype;
	string theword; 
	string saved_E_word = s;
	
	gen( saved_E_word, ACTION);
	if( parsing_tense(saved_E_word) ){
		saved_E_word = getEword(saved_E_word);
		gen(saved_E_word, TENSE);
		
	}
	
	scanner(thetype,theword);

	if(match(thetype,PERIOD))
	{
		return true;
	}
	else
	{
		cout << "Did not match period. Exiting.." << endl;
		exit(1);
	}
}

bool parsing_be(tokentype thetype,string theword)
{

	//tokentype thetype;
	//string theword;
	///cout << "Processing <be> " << endl;
	
	//scanner(thetype, theword);
	if ((match(thetype,IS))){
	///	cout << "Matched IS" <<endl;
	} else if ((match(thetype,WAS))){
		
		///cout << "Matched WAS" <<endl;
	}  else{
	//	cout << "SYNTAX ERROR: expected IS|WAS but found "<< theword <<endl;
		
		return false;
		
	}
	return true;
}
bool parsing_s3() {
	///cout << "Processing <s3>" <<endl;
	tokentype thetype;
	string theword; 
	string saved_E_word;
	scanner(thetype,theword);
	if (parsing_verb(thetype,theword)) {
		
		saved_E_word = getEword(theword);
		return parsing_s4(saved_E_word);		
	} 
	else if  (parsing_noun(thetype,theword)) {
		
		saved_E_word = getEword(theword);
		scanner(thetype, theword);
		if(match(thetype,DESTINATION))
		{ 
			gen(saved_E_word, TO);
			//cout << "Matched DESTINATION" <<endl;
		} else {
			 cout << "SYNTAX ERROR: expected DESTINATION but found "<< theword <<endl;
			exit(1);
			
		}		  
		scanner(thetype,theword);
		if(parsing_verb(thetype,theword)){
			saved_E_word = getEword(theword);
			return parsing_s4(saved_E_word);
		}

	} else {
		cout << "Unexpected "<< theword << " found in" << endl;
		exit(1);
	}
	return true;
}

bool parsing_s2(string s){
	///cout << "Processing <s2>" <<endl;
	tokentype thetype;
	string theword; 
	string saved_E_word;
	scanner(thetype,theword);
	saved_E_word = s;	
	if (match(thetype,DESTINATION)) {
		
		gen(saved_E_word,TO);
		///cout<<"Matched DESTINATION" << endl;
		scanner(thetype,theword);
		 if(parsing_verb(thetype,theword)){
			saved_E_word = getEword(theword);
			 return parsing_s4(saved_E_word);
		 }
		 /*
		 parsing_tense();
		 scanner(thetype, theword);
		 if(match(thetype,PERIOD))
		 { 
			cout << "Matched PERIOD " <<endl;
			 return true;
		 }*/
	
	} else if ( match(thetype,OBJECT)){
		
		///cout << "Matched OBJECT " <<endl;
		gen(saved_E_word,OBJ);
		return parsing_s3();
	}else if ((match(thetype,IS)) || (match,thetype,WAS)){
		saved_E_word = "#" + saved_E_word;
		gen(saved_E_word,ACTION);	
		saved_E_word = getEword(theword);
		gen(saved_E_word,TENSE);
		scanner(thetype,theword);
		if(match(thetype,PERIOD))
		{
			return true;
		}
		else
		{
			cout << "Error invalid" << endl;
			exit(1);
		
		}
	}
	else {
		cout << "Unexpected "<< theword << " found in s2" << endl;
		exit(1);
		
	}
	return true;
}

bool parsing_s1(){
	///cout << "Processing <s1>" <<endl;
	tokentype thetype;
	string theword; 
	string saved_E_word;
	
	scanner(thetype, theword);
	if (parsing_verb(thetype,theword)) {
		saved_E_word = getEword(theword);
		
		return parsing_s4(saved_E_word);
				
	} else if (parsing_noun(thetype,theword)) {
		saved_E_word = getEword(theword);
		return parsing_s2(saved_E_word);		
		
	} else {
		cout << "Unexpected "<< theword << " in s1" << endl;
		exit(1);	
	}
}

bool s(){
	tokentype thetype;
	string theword; 
	string saved_E_word;
	
	
	///cout << "\n====== Processing <s> ======" <<endl;
	//Initialize array to empty
	for(int i = 0; i < 6; i++)
	{
		theEword[i] = "";
	}	
	if (((scanner(thetype, theword) == 0) || (thetype == EOFM)) || (theword.find("EOFM") == 0 ) ){
		return false;
	} else {
		if (match(thetype, CONNECTOR)){	
			///cout << "Matched CONNECTOR " << endl;
			///scanner(thetype, theword);		
			saved_E_word = getEword(theword);
			gen(saved_E_word,CONNECT);
			scanner(thetype,theword);
		}	
		bool a = parsing_noun(thetype,theword);
		
		if(a)
		{
			 saved_E_word = getEword(theword);
		}else {
			cout << "Not a noun, exiting" << endl;
			exit(1);
		}
		scanner(thetype, theword);
		if (!match(thetype, SUBJECT)){
			cout << "SYNTAX ERROR: expected "<<typeName[SUBJECT]<<" but found "<< theword <<endl;
			exit(1);
			
		} else {
			///cout << "Matched SUBJECT " << endl;
			gen(saved_E_word, ACTOR);
			
		}		
		
		if (parsing_s1())
		{
			for(int j = 0; j < 6; j++)
			{
				if(theEword[j] != "")
				{
					if(theEword[j][0] == '#')
					{
						cout << "DESCRIPTION: " << theEword[j].substr(1) << endl;
						fout << "DESCRIPTION: " << theEword[j].substr(1) << endl;
					}
					else
					{

						cout << printWords[j] << ": " << theEword[j] << endl;
						fout << printWords[j] << ": " << theEword[j] << endl;
					}
				}
			}	
			fout << endl;
			cout << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
}

//JuanM
void story(){
	int i=0;
	///cout << "Processing story. " <<endl ;
	fout.open("translated.txt");
	 
	while( true ){
		if (!s()){
			fout.close();
			return;
		}
	}
}

// The test driver to start the parser
// Done by:  Nam Ho
int main()
{

  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file 

  string inName;
  cout << "Input file? "; cin >> inName;
  fin.open(inName.c_str());
  
  story();
	
	//string typeName[16] = {"WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"};
 

  // ** close the input file
  fin.close();
}// end
//** should require no other input files!


