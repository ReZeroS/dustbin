#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node
{
    public:
        Node();
        Node(string _type, string _value);
        virtual ~Node();

        void setType(string type);
        string getType();
        void setValue(string value);
        string getValue();

        int getStartPos();
        int getEndPos();
        void setPos(int _x, int _y);


    protected:

    private:
        string type;
        string value;
        int startPos;
        int endPos;
};

#endif // NODE_H
