#include <bits/stdc++.h>
#include <regex>



#define KEYWORDCOUNT 8
#define OPERATORCOUNT 7
#define SEPARATORCOUNT 6

using namespace std;





// keywords, identifier, number, operator, separator
const regex IDENTIFIER = regex("[a-zA-Z_]\\w*", std::regex::icase);
const regex NUMBER = regex("[+-]?[0-9]+", std::regex::icase);


static const string KEYWORDS[] = {
    "if", "int", "for", "while", "do", "return", "break", "continue"
};

static const string OPERATORS[] = {
    "+", "-", "*", "/", "=", ">", "<"
};

static const string SEPARATORS[] = {
    ",", ";", "(", ")", "{", "}"
};



bool isDigit(char c){
    if(c >= '0' && c <= '9'){
        return true;
    }
    return false;
}

bool isAlpha(char c){
    if(c >= 'a' && c <= 'z'){
        return true;
    }
    if(c >= 'A' && c <= 'Z'){
        return true;
    }
    return false;
}

bool isKeyword(string word){
    for(int i = 0; i < KEYWORDCOUNT; ++i){
        if(KEYWORDS[i] == word){
            return true;
        }
    }
    return false;
}

bool isIdentifier(string word){
    if(regex_match(word, IDENTIFIER)){
        return true;
    }
    return false;
}

bool isNumber(string word){
    if(regex_match(word, NUMBER)){
        return true;
    }
    return false;
}

bool isOperator(string word){
    for(int i = 0; i < OPERATORCOUNT; ++i){
        if(OPERATORS[i] == word){
            return true;
        }
    }
    return false;
}

bool isSeparator(string word){
    for(int i = 0; i < SEPARATORCOUNT; ++i){
        if(SEPARATORS[i] == word){
            return true;
        }
    }
    return false;
}



string& trim(string &s){
    if (s.empty()){
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    s.erase(0, s.find_first_not_of(" \r\n\t"));
    s.erase(s.find_last_not_of(" \r\n\t") + 1);

    return s;
}

void SplitString(const string& s, vector<string>& v, const string& c){
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}










int main(){
    string line;
    vector<string> binaryArrayIndex;
    vector<string> binaryArrayValue;
    while(getline(cin, line)){
//        cout << "OS " << line << " SO" << endl;
        trim(line);
        vector<string> wordList;
        SplitString(line, wordList, " ");
        int wordSize = wordList.size();
        for(int i = 0; i < wordSize; ++i){

            if(isKeyword(wordList[i])){
                binaryArrayIndex.push_back("keywords");
                binaryArrayValue.push_back(wordList[i]);
                continue;
            }
            if(isIdentifier(wordList[i])){
                binaryArrayIndex.push_back("identifier");
                binaryArrayValue.push_back(wordList[i]);
                continue;
            }
            if(isNumber(wordList[i])){
                binaryArrayIndex.push_back("number");
                binaryArrayValue.push_back(wordList[i]);
                continue;
            }
            if(isOperator(wordList[i])){
                binaryArrayIndex.push_back("operator");
                binaryArrayValue.push_back(wordList[i]);
                continue;
            }
            if(isSeparator(wordList[i])){
                binaryArrayIndex.push_back("separator");
                binaryArrayValue.push_back(wordList[i]);
                continue;
            }
        }

    }
    cout << "Ready: " << endl;
    int binaryArraySize = binaryArrayIndex.size();
    for(auto index = 0; index < binaryArraySize; ++index){
        cout << "{ " << binaryArrayIndex[index] << " : " << binaryArrayValue[index] << " }" << endl;
    }

}
