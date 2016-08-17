# include <cstdio>
# include <cctype>
# include <string>
# include <iostream>
# include "lexer.h"
# include "lexer.cpp"

using namespace std;

int _token;
int lookahead;
static string lexbuf;
bool peekFlag = false;

/*
	office hours:
	W 12:00-1:00
	Th 12:00-1:00
*/

void match(int t)
{
	if(peekFlag == true){
		_token = lookahead;
		peekFlag = false;
	}
	else{
		if (_token == t)
			_token = lexan(lexbuf);
		else
			cout << "error on token:" << _token << "try to match " << t << endl;
	}	
}

int peek()
{
	lookahead = lexan(lexbuf);
	peekFlag = true;
	return lookahead;
}

void matchEXPRLIST()
{
	matchEXPR();

	if(_token == COMMA){
		match(COMMA);
		matchEXPRLIST();
	}
}

void matchID()
{
	if(_token == ID){
		match(ID);
		if(_token == LPAREN){
			match(LPAREN);
			if(_token != RPAREN)
				matchEXPRLIST();
			match(RPAREN);
		}
	}
	else if(_token == NUMBER)
		match(NUMBER);
	else if(_token == STRING)
		match(STRING);
	else if(_token == CHARACTER)
		match(CHARACTER);
	else{
		match(LPAREN);
		matchEXPR();
		match(RPAREN);
	}
}

void matchINDEX()
{
	matchID();

	while(_token == LBRACK || _token == DOT || _token == ARROW){
		if(_token == LBRACK){
			match(LBRACK);
			matchEXPR();
			match(RBRACK);
			cout << "index" << endl;
		}
		else if(_token == DOT){
			match(DOT);
			matchID();
			cout << "dot" << endl;
		}
		else{
			match(ARROW);
			matchID();
			cout << "arrow" << endl;
		}
	}
}

void matchUNARY()
{
	if(_token == ADDR){
		match(ADDR);
		matchUNARY();
		cout << "addr" << endl;
	}
	else if(_token == STAR){
		match(STAR);
		matchUNARY();
		cout << "deref" << endl;
	}
	else if(_token == NOT){
		match(NOT);
		matchUNARY();
		cout << "not" << endl;
	}
	else if(_token == SUB){
		match(SUB);
		matchUNARY();
		cout << "neg" << endl;
	}
	else if(_token == SIZEOF){
		match(SIZEOF);
		if(_token == LPAREN){
			match(LPAREN);
			matchSPECIFIER();
			matchPOINTERS();
			match(RPAREN);
		}
		else
			matchUNARY();
		cout << "sizeof" << endl;
	}
	else
		matchINDEX();
}

void matchCAST()
{
	int temp = peek();
	if(_token == LPAREN && (temp == INT || temp == CHAR || temp == STRUCT)){
		match(LPAREN);
		matchSPECIFIER();
		matchPOINTERS();
		match(RPAREN);
		matchCAST();
		cout << "cast" << endl;
	}
	else
		matchUNARY();
}

void matchMUL()
{
	matchCAST();

	while(_token == STAR || _token == DIV || _token == REM){
		if(_token == STAR){
			match(STAR);
			matchCAST();
			cout << "mul" << endl;
		}
		else if(_token == DIV){
			match(DIV);
			matchCAST();
			cout << "div" << endl;
		}
		else{
			match(REM);
			matchCAST();
			cout << "rem" << endl;
		}
	}
}

void matchADD()
{
	matchMUL();

	while(1){
		if (_token == ADD){
			match(ADD);
			matchMUL();
			cout << "add" << endl;
		}
		else if (_token == SUB){
			match(SUB);
			matchMUL();
			cout << "sub" << endl;
		}
		else
			break;
	}
}

void matchLTN()
{
	matchADD();

	while(_token == LTN || _token == GTN || _token == LEQ || _token == GEQ){
		if(_token == LTN){
			match(LTN);
			matchADD();
			cout << "ltn" << endl;
		}
		else if(_token == GTN){
			match(GTN);
			matchADD();
			cout << "gtn" << endl;
		}
		else if(_token == LEQ){
			match(LEQ);
			matchADD();
			cout << "leq" << endl;
		}
		else{
			match(GEQ);
			matchADD();
			cout << "geq" << endl;
		}
	}
}

void matchEQL()
{
	matchLTN();

	while(_token == EQLEQL || _token == NOTEQL){
		if(_token == EQLEQL){
			match(EQLEQL);
			matchLTN();
			cout << "eql" << endl;
		}
		else{
			match(NOTEQL);
			matchLTN();
			cout << "neq" << endl;
		}
	}
}

void matchAND()
{
	matchEQL();

	while(_token == AND){
		match(AND);
		matchEQL();
		cout << "and" << endl;
	}
}

void matchEXPR()
{
	matchAND();

	while(_token == OR){
		match(OR);
		matchAND();
		cout << "or" << endl;
	}
}

void matchSTATEMENT()
{
	if(_token == LBRACE){
		match(LBRACE);
		matchDECLARATIONS();
		while(_token != RBRACE)
			matchSTATEMENTS();
		match(RBRACE);
	}
	else if(_token == RETURN){
		match(RETURN);
		matchEXPR();
		match(SCOLON);
	}
	else if(_token == WHILE){
		match(WHILE);
		match(LPAREN);
		matchEXPR();
		match(RPAREN);
		matchSTATEMENT();
	}
	else if(_token == IF){
		match(IF);
		match(LPAREN);
		matchEXPR();
		match(RPAREN);
		matchSTATEMENT();
		if(_token == ELSE){
			match(ELSE);
			matchSTATEMENT();
		}
	}
	else{
		matchEXPR();
		if(_token == EQL){
			match(EQL);
			matchEXPR();
		}
		match(SCOLON);
	}
}

void matchSTATEMENTS()
{
	while(_token != RBRACE){
		matchSTATEMENT();
	}
}

void matchDECLARATOR()
{
	matchPOINTERS();
	match(ID);
	if(_token == LBRACK){
		match(LBRACK);
		match(NUMBER);
		match(RBRACK);
	}
}

void matchDEC()
{
	matchSPECIFIER();
	matchDECLARATOR();
	while(_token == COMMA){
		match(COMMA);
		matchDECLARATOR();
	}
	match(SCOLON);
}

void matchDECLARATIONS()
{
	while(_token == INT || _token == CHAR || _token == STRUCT)
		matchDEC();
}

void matchPARAM()
{
	matchSPECIFIER();
	matchPOINTERS();
	match(ID);
}

void matchPARAMLIST()
{
	matchPARAM();

	if(_token == COMMA){
		match(COMMA);
		matchPARAMLIST();
	}
}

void matchPARAMS()
{
	if(_token == VOID)
		match(VOID);
	else
		matchPARAMLIST();
}

void matchSPECIFIER()
{
	if(_token == INT)
		match(INT);
	else if(_token == CHAR)
		match(CHAR);
	else{
		match(STRUCT);
		match(ID);
	}
}

void matchPOINTERS()
{
	while(_token == STAR){
		match(STAR);
	}
}

void matchGDEC()
{
	matchPOINTERS();
	match(ID);
	if(_token == LBRACE){
		match(LBRACE);
		match(NUMBER);
		match(RBRACE);
	}
	else if(_token == LPAREN){
		match(LPAREN);
		match(RPAREN);
	}
}

void matchGDECLIST()
{
	while(_token == COMMA){
		match(COMMA);
		matchGDEC();
	}
	match(SCOLON);
}

void matchTranslation()
{
	matchSPECIFIER();

	if(_token == LBRACE){ //type-def case
		match(LBRACE);
		matchDECLARATIONS();
		match(RBRACE);
		match(SCOLON);
	}
	else{
		matchPOINTERS();
		match(ID);
		if(_token == LPAREN){ //pointers id() || funct-def case
			match(LPAREN);
			if(_token == RPAREN){ //pointers id()
				match(RPAREN);
			}
			else{				//funct-def case
				matchPARAMS();
				match(RPAREN);
				match(LBRACE);
				matchDECLARATIONS();
				matchSTATEMENTS();
				match(RBRACE);
			}
		}
		else if(_token == LBRACK){ //pointers id [num]
			match(LBRACK);
			match(NUMBER);
			match(RBRACK);
		}
		if(_token == COMMA || _token == SCOLON){
			matchGDECLIST();
		}
	}
}

int main()
{
	_token = lexan(lexbuf);

	while(_token != DONE){
		matchTranslation();
	}
	return 1;
};

/*

EXAMPLE PARSER MODIFICATIONS

int matchPOINTERS()
{
	int count = 0;

	while(_token == STAR){
		count++;
		match(STAR);
	}
	return count;
}

string matchSPECIFIER()
{
	if(_token == CHAR){
		match(CHAR);
		return "char";
	}
	if(_token == INT){
		match(INT);
		return "int";
	}
	match(STRUCT);
	string s = lexbuf;
	match(ID);
	return s;
}

void matchDEC()
{
	string s = matchSPECIFIER();
	matchDECLARATOR(s);

	while(_token == COMMA){
		match(COMMA);
		matchDECLARATOR(s);
	}
	match(SCOLON);
}

*/








