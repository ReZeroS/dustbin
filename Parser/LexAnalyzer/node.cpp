#include "node.h"

Node::Node()
{
    //ctor
}

Node::~Node()
{
    //dtor
}

Node::Node(string _type, string _value){
    type = _type;
    value = _value;

}


void Node::setType(string _type){
    type = _type;
}

string Node::getType(){
    return type;
}


void Node::setValue(string _value){
    value = _value;
}

string Node::getValue(){
    return value;
}


void Node::setPos(int _x, int _y){
    startPos = _x;
    endPos = _y;
}

int Node::getStartPos(){
    return startPos;
}

int Node::getEndPos(){
    return endPos;
}


