#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;

ifstream fin;

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
		cout << "Lexical error: " << w << " is not a valid token" << endl;
		
	}
  
  return 1;
  

}//the end

string typeName[16] = {"WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"};
 

bool match(tokentype& a,tokentype b){
	return (a==b);
}
//Error msgs done by JuanM
void syntaxerror(string s, string s2)
{
	cout << "Syntax error: expected " << s <<  " but found " << s2 << endl;
	exit(1);
}

void syntaxerror2(string s, string s2)
{
	cout << "Syntax Error: unexpected " << s << " found in " << s2 << endl;
	exit(1);
}
//Parses the noun into word word 1 or pronoun
//JuanM
bool parsing_noun(tokentype thetype, string theword){
	//tokentype thetype;
	//string theword; 
	cout << "Processing <noun>" <<endl;
	//scanner(thetype, theword);
	if (match(thetype,PRONOUN)){
		cout << "Matched PRONOUN" <<endl;
	} else if (match(thetype,WORD1)) {
		
		cout << "Matched WORD1" << endl;
	} else {
		//cout << "Unexpected "<< theword << " found in noun."<<endl;
		//return false;
	//	exit(1);
	syntaxerror2(theword,"noun");
	}
	
	return true;
}
//Will parse the verb into word2
//JuanM
bool parsing_verb(tokentype thetype, string theword){
	
	//tokentype thetype;
	//string theword;
	cout << "Processing <verb> " << endl;
	
	//scanner(thetype, theword);
	if (!(match(thetype,WORD2))){
		//cout << "SYNTAX ERROR: expected "<<typeName[VERB]<<" but found "<< theword <<endl;
		return false;
	} else {
		
		cout << "Matched WORD2\n";
	return true;
	
	
}
}
//matches the tense into either verbpast,verb,verbpastn, or verbn
//JuanM
bool parsing_tense(){
	tokentype thetype;
	string theword;
	cout << "Processing <tense> " << endl;
	
	scanner(thetype, theword);
	if ( (match(thetype,VERBPAST) )){
		
		cout << "Matched VERBPAST" << endl;
		
	} else if( (match(thetype,VERB) )){
		
		cout << "Matched VERB" << endl;
	} else if( (match(thetype,VERBPASTNEG) )){
		
		cout << "Matched VERBPASTN" << endl;
	} else if( (match(thetype,VERBNEG) )){
		
		cout << "Matched VERBN" << endl;
	} else{//else none of them are correct.
		//cout << "Unexpected "<< theword << " found in tense."<<endl;
		//exit(1);
		syntaxerror2(theword,"tense");
	}
	return true;
}
//JuanM
//This will parse be according to the left factoring rules is||was.
bool parsing_be(tokentype thetype,string theword)
{

	//tokentype thetype;
	//string theword;
	cout << "Processing <be> " << endl;
	
	//scanner(thetype, theword);//Need to match the type is or was or else invalid
	if ((match(thetype,IS))){
		cout << "Matched IS" <<endl;
	} else if ((match(thetype,WAS))){
		
		cout << "Matched WAS" <<endl;
	}  else{
	//	cout << "SYNTAX ERROR: expected IS|WAS but found "<< theword <<endl;
		
		return false;
		
	}
	return true;
}
//NamH
//This will parse the s3 according to the left factoring rules.
bool parsing_s3() {
	cout << "Processing <s3>" <<endl;
	tokentype thetype;
	string theword; 
	scanner(thetype,theword);
	//Need to match be verb or noun initially
	if (parsing_verb(thetype,theword)) {
		
		parsing_tense();
		scanner(thetype, theword);
		
		if(match(thetype,PERIOD) )
		{
			cout << "Matched PERIOD " <<endl;
			return true;
		} else{
		//	cout << "SYNTAX ERROR: expected PERIOD but found "<< theword <<endl;
		syntaxerror("PerioD", theword);
		}
		
				
	} else if  (parsing_noun(thetype,theword)) {
		scanner(thetype, theword);
		if(match(thetype,DESTINATION))
		{ 
			cout << "Matched DESTINATION" <<endl;
		} else {
		//	 cout << "SYNTAX ERROR: expected DESTINATION but found "<< theword <<endl;
		//	exit(1);
		syntaxerror("DESTINATION", theword);
			
		}		  
		scanner(thetype,theword);
		if(!parsing_verb(thetype,theword)){
			
		//	cout << "SYNTAX ERROR: expected VERB but found "<< theword <<endl;
			//exit(1);
			syntaxerror("Verb", theword);
		}
		parsing_tense();
		scanner(thetype,theword);
		if(match(thetype,PERIOD)) { 
			cout << "Matched PERIOD " <<endl;
			return true;
		} else{
			 cout << "SYNTAX ERROR: expected "<<typeName[PERIOD]<<" but found "<< theword <<endl;
			exit(1);
		}		  
		
	} else {
		cout << "Unexpected "<< theword << " found in" << endl;
		exit(1);
	}
	return true;
}
//This is the function parsing s2 meant to represent the s2 in left factoring rules.
//NamH
bool parsing_s2(){
	cout << "Processing <s2>" <<endl;
	tokentype thetype;
	string theword; 
	scanner(thetype,theword);//Scan to get the word. Has to match be destination||be||object or else there is an error.
	if (parsing_be(thetype,theword)) {
		scanner(thetype, theword);
		//If match be scan again and match period
		if (!match(thetype,PERIOD)){
			//cout << "SYNTAX ERROR: expected "<<typeName[PERIOD]<<" but found "<< theword <<endl;
			//exit(1);
			syntaxerror("Period", theword);
		}
		else{
			cout << "Matched PERIOD " <<endl;
			return true;
		}
		
				//else match destination and then verb period
	} else if (match(thetype,DESTINATION)) {
		cout<<"Matched DESTINATION" << endl;
		scanner(thetype,theword);
		 if(!parsing_verb(thetype,theword)){
			// cout << "SYNTAX ERROR: expected WORD2 but found "<< theword <<endl;
			// exit(1);
			syntaxerror("WORD2",theword );
		 }
		 parsing_tense();
		 scanner(thetype, theword);
		 if(match(thetype,PERIOD))
		 { 
			cout << "Matched PERIOD " <<endl;
			 return true;
		 }
		 else{//else not valid
		//	 cout << "SYNTAX ERROR: expected "<<typeName[PERIOD]<<" but found "<< theword <<endl;
		//	exit(1);
		syntaxerror("Period", theword);
			
		  
		 }
		
	} else if ( match(thetype,OBJECT)){
		
		cout << "Matched OBJECT " <<endl;
		return parsing_s3();//call s3 to go on to next rule
	}else {
		cout << "Unexpected "<< theword << " found in s2" << endl;
		exit(1);
		
	}
	
	return true;
}
//Done by NamH
//Parsing s1 according to the LF rules. Inital has to be verb tense period or noun. 
bool parsing_s1(){
	cout << "Processing <s1>" <<endl;
	tokentype thetype;
	string theword; 
	scanner(thetype, theword);
	if (parsing_verb(thetype,theword)) {
		parsing_tense();
		
		scanner(thetype, theword);
		if (!match(thetype,PERIOD)){
		//	cout << "SYNTAX ERROR: expected "<<typeName[PERIOD]<<" but found "<< theword <<endl;
			//exit(1);
			syntaxerror("Period", theword);
			
		}else{
			cout << "Matched PERIOD" <<endl;
			return true;
		}
		
				
	} else if (parsing_noun(thetype,theword)) {
		return parsing_s2();		
		
	} else {//if not either then does not belong here.
	//	cout << "Unexpected "<< theword << " in s1" << endl;
		//exit(1);	
		syntaxerror(theword, "s1");
	}
}
// This is the s .initial has to be connector or noun.
//Done by NamH
bool s(){
	tokentype thetype;
	string theword; 
	cout << "\n====== Processing <s> ======" <<endl;
	if ((scanner(thetype, theword) == 0) || (thetype == EOFM)){
		return false;
	} else {
		if (match(thetype, CONNECTOR)){	//match connector if there is one.
			cout << "Matched CONNECTOR " << endl;
			scanner(thetype, theword);
		}	
		parsing_noun(thetype,theword);//call the parse noun
		
		
		scanner(thetype, theword);
		if (!match(thetype, SUBJECT)){
			cout << "SYNTAX ERROR: expected "<<typeName[SUBJECT]<<" but found "<< theword <<endl;
			exit(1);
			
		} else {
			cout << "Matched SUBJECT " << endl;
		}		
		return (parsing_s1());
	}
}


//JuanM
//This will be the function to process the story .
void story(){
	int i=0;
	cout << "Processing story. " <<endl ;
	 
	while( true ){cout<<++i;
		if (!s()){
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


