#include <fstream>
#include <iomanip>
#include <iostream>


#include "view.h"


void View::createView(std::string viewName, std::string commands){
    std::ofstream viewWriter("view", std::ios::app);
    viewWriter << viewName << " :" << commands << std::endl;
    viewWriter.close();
    return ;

}



void View::showView(){
    std::ifstream viewReader("view", std::ios::in | std::ios::out);
    std::string s;
    std::cout << "+-------------------------------------------------------------------------+" << std::endl;
    std::getline(viewReader, s);
    while(std::getline(viewReader, s)){

        std::cout << "+" << std::left << std::setw(73) << s << "+" << std::endl;
        std::cout << "+-------------------------------------------------------------------------+" << std::endl;
    }
//    std::cout << "+-------------------------------------------------------------------------+" << std::endl;
    viewReader.close();

}


void View::helpView(std::string viewName){
    std::ifstream viewReader("view", std::ios::in | std::ios::out);

    std::string s;
    std::getline(viewReader, s);
    while(std::getline(viewReader, s)){
        std::string name = s.substr(0, s.find_first_of(" "));

        if(name == viewName){
            std::string command = s.substr(s.find_first_of(":"));
            std::cout << command << std::endl;
            break;
        }
    }
    return ;

}
