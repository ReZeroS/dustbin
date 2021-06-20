#include "inputstream.h"

InputStream::InputStream()
{
    //ctor

}

InputStream::~InputStream()
{
    //dtor
}



InputStream::InputStream(string _line){
    line = _line;
    length = line.size();
    cout << "The line's length is " << length << endl;
}

void InputStream::logPos(){
    cout << "#Stop at " << line[pos] << " and pos is " << pos << endl;
}


bool InputStream::isSpace(char ch){
    if(ch == ' ' || ch == '\t' || ch == '\n'){
        return true;
    }
    return false;
}

bool InputStream::isDigit(char ch){
    if( ch <= '9' && ch >= '0'){
        return true;
    }
    return false;
}

bool InputStream::isOperator(char ch){
    for(int i = 0; i < OPERATORCOUNT; ++i){
        if(OPERATORS[i] == ch){
            return true;
        }
    }
    return false;

}

bool InputStream::isPrequote(char ch){
    if(ch == '"'){
        return true;
    }
    return false;
}


bool InputStream::isSeparator(char ch){
    for(int i = 0; i < SEPARATORCOUNT; ++i){
        if(SEPARATORS[i] == ch){
            return true;
        }
    }
    return false;
}


bool InputStream::isIdentifier(char ch){
    if(ch == '_' || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
        return true;
    }
    return false;
}


//pending: Add to token class
bool InputStream::isKeyword(string word){
    for(int i = 0; i < KEYWORDCOUNT; ++i){
        if(KEYWORDS[i] == word){
            return true;
        }
    }
    return false;
}



bool InputStream::readSeparator(){
    string temp = "";
    for(int i = 0; i < SEPARATORCOUNT; ++i){
        if(SEPARATORS[i] == line[pos]){
            temp.push_back(line[pos++]);
            Node node("Separator", temp);
            node.setPos(pos - 1, pos - 1);
            binaryArray.push_back(node);
            return true;
        }
    }
    return false;
}

bool InputStream::readOperator(){
    string temp = "";
    for(int i = 0; i < OPERATORCOUNT; ++i){
        if(OPERATORS[i] == line[pos]){
            temp.push_back(line[pos++]);
            Node node("Operator", temp);
            node.setPos(pos - 1, pos - 1);
            binaryArray.push_back(node);
            return true;
        }
    }
    return false;
}

bool InputStream::readNumber(){
    string num = "";
    int startPos = pos;
    while(isDigit(line[pos])){
        num += line[pos++];
    }
    if(line[pos] == '.'){
        num += line[pos++];
        while(isDigit(line[pos])){
            num += line[pos++];
        }
    }
    if(line[pos] == '.'){
        cout << "Got a number error." << endl;
        return false;
    }
    Node node("Number", num);
    node.setPos(startPos, pos - 1);
    binaryArray.push_back(node);
    return true;
}

bool InputStream::readString(){
    string temp = "";
    int startPos = pos++;
    while(line[pos] != '"' && pos < length){
        temp += line[pos++];
    }
    pos++;
    if(pos >= length){
        cout << "Got a string error." << endl;
        return false;
    }
    Node node("String", '"' + temp + '"');
    node.setPos(startPos, pos - 1);
    binaryArray.push_back(node);
    return true;

}


bool InputStream::readIdentifier(){
    string temp = "";
    int startPos = pos;
    while(isIdentifier(line[pos])){
        temp += line[pos++];
    }
    Node node("?", temp);
    if(isKeyword(temp)){
        node.setType("Keyword");
    }
    else {
       node.setType("Identifier");
    }
    node.setPos(startPos, pos - 1);
    binaryArray.push_back(node);
    return true;
}

void InputStream::readWhileSpace(){
    while(isSpace(line[pos])){
        pos++;
    }
}

bool InputStream::readToken(){
    readWhileSpace();
    if(isSeparator(line[pos])){
        readSeparator();
        return true;
    }
    if(isOperator(line[pos])){
        readOperator();
        return true;
    }
    if(isDigit(line[pos])){
        readNumber();
        return true;
    }
    if(isIdentifier(line[pos])){
        readIdentifier();
        return true;
    }
    if(isPrequote(line[pos])){
        readString();
        return true;
    }
    logPos();
    return false;
}

void InputStream::testOut(){
    int arraySize = binaryArray.size();
    for(int i = 0; i < arraySize; ++i){
        string type = binaryArray[i].getType();
        string value = binaryArray[i].getValue();
        int startPos = binaryArray[i].getStartPos();
        int endPos = binaryArray[i].getEndPos();
        cout << "{ " << type << " : " << value << " }  " << "Start position: " << startPos << " , End position: " << endPos << endl;

    }

}
