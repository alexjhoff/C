/*
 * File:	lexer.h
 *
 * Description:	This file contains the public function and variable
 *		declarations for the lexical analyzer for Simple C.
 */

# ifndef LEXER_H
# define LEXER_H

extern int lineno, numerrors;

int lexan(std::string &lexbuf);
void report(const std::string &str, const std::string &arg = "");
void matchEXPR();
void matchEXPRLIST();
void matchSPECIFIER();
void matchPOINTERS();
void matchDECLARATIONS();
void matchPOINTERS();
void matchDECLARATION();
void matchSTATEMENTS();

# endif /* LEXER_H */
