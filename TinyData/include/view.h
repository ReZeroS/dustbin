#ifndef VIEW_H
#define VIEW_H


#include <string>

class View
{
    public:


        static void createView(std::string viewName, std::string command);

        static void showView();

        static void helpView(std::string viewName);

    protected:

    private:
};

#endif // VIEW_H
