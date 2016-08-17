#include<cctype>
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main()
{
	//init
	int c; //character pointer
	int p; //previous character
	int i; //for loop iterator
	int flag=0; //flag
	bool comm;
	string s; //temp string
	string key[] =  {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
	string op[] = {"=", "||", "&&", "==", "!=", "<", ">", "<=", ">=", "+", "-", "*", "/", "%", "&", "!", "++", "--", ".", "->", "(", ")", "[", "]", "{", "}", ";", ":",","};

	//Get first character
	c=cin.get();	

	while(c!=EOF)
	{
		//Number
		if(isdigit(c))
		{
			s="";
			do
			{	
				s+=c;
				c=cin.get();
			}
			while(isdigit(c));
			cout << "number:" << s << endl;
		}
		//Identifier or Keyword
		else if(c=='_' || (isalpha(c)))
		{
			s="";
			flag=0;
			do
			{
				s+=c;
				c=cin.get();
			}
			while(c=='_' || isalpha(c) || isdigit(c));

			//Check if Keyword
			for(i=0;i<=31;i++)
			{
				if(s == key[i])
				{
					cout << "keyword:" << s << endl;
					flag=1;
					break;
				}	
			}
			//Check if not Keyword
			if(flag == 0)
			{
				cout << "identifier:" << s << endl;
			}
		}
		//String
		else if(c=='"')
		{
			s="";
			//c=cin.get();
			do
			{	
				//New line
				if(c=='\n')
				{
					break;
				}
				//Backslash
				if(c=='\\')
				{
					s+=c;
					c=cin.get();
				}
				s+=c;
				c=cin.get();
			}while(c!='"');
			s+=c;
			cout << "string:" << s << endl;
			c=cin.get();
		}
		//Character
		else if(c=='\'')
		{
			s="";
			do
			{
				s+=c;
				c=cin.get();
				if(c=='\\')
				{
					s+=c;
					c=cin.get();
					s+=c;
					c=cin.get();
				}
			}while(c!='\'');
			s+=c;
			cout << "character:" << s << endl;
			c=cin.get();
		}
		//Operators and Comments
		else if(ispunct(c))
		{
			s=c;
			flag=0;
			if(c=='/')
			{
				c=cin.get();
				//Comment
				if(c!='*')
				{
					flag=1;
					cin.putback(c);
				}
				else
				{	
					s.clear();
					do
					{
						c=cin.get();
						if(c == '*')
						{
							c=cin.get();
							if(c == '/')
							{
								c=cin.get();
								break;
							}
							else
								cin.putback(c);
						}
					}while(1);
				}
			}
			else if (c == '*' || c == '/' || c == '%' || c == '.' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ':' || c == ';' || c == ',' ) 
			{
				flag=1;
				c=cin.get();
			}
			else if(c == '=' || c == '|' || c == '&' || c == '!' || c == '<' || c == '>' || c == '+' || c == '-')
			{
				c=cin.get();
				if(c == '|'|| c == '&'|| c == '='|| c == '+'|| c == '-'|| c == '>')
				{
					s+=c;
					c=cin.get();
				}
				flag=1;
			}
			if(flag==1)
				cout << "operator:" << s << endl;
		}
		else
			c=cin.get();
		
	}

	return 0;
}
