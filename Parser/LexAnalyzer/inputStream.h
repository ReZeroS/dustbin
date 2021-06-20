#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <node.h>

#include <vector>
#include <string>
#include <iostream>

#define KEYWORDCOUNT 10
#define OPERATORCOUNT 7
#define SEPARATORCOUNT 6


using namespace std;


static const string KEYWORDS[] = {
    "if", "int", "for", "while", "do", "return", "break", "continue", "double", "string"
};

static const char OPERATORS[] = {
    '+', '-', '*', '/', '=', '>', '<'
};

static const char SEPARATORS[] = {
    ',', ';', '(', ')', '{', '}'
};

class InputStream
{
    public:
        InputStream();
        InputStream(string _line);
        virtual ~InputStream();


        bool isSpace(char ch);
        bool isDigit(char ch);
        bool isOperator(char ch);
        bool isSeparator(char ch);
        bool isIdentifier(char ch);

        bool isKeyword(string word);
        bool isPrequote(char ch);


        bool readSeparator();
        bool readOperator();
        bool readNumber();
        bool readString();
        bool readIdentifier();
        void readWhileSpace();
        bool readToken();


        void logPos();
        void testOut();

    protected:

    private:
        int pos;
        int length;
        string line;
        vector<Node> binaryArray;


};

#endif // INPUTSTREAM_H
