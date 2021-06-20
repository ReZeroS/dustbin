#include "test.h"
#include "inputstream.h"

#include <bits/stdc++.h>

using namespace std;


Test::Test()
{
    //ctor
}

Test::~Test()
{
    //dtor
}


int main(){
    string line = "", lines = "";
    while(getline(cin, line)){
        lines.append(line);
    }
    InputStream testCase(lines);
    while(testCase.readToken());
//    testCase.logPos();
    testCase.testOut();

}


//
//int main(){
//	int a = 2;
//	int b = 2.222;
//	string c = "name";
//	printf("hello, world!");
//}
//
