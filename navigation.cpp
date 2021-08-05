#ifndef SERVICECLASSCECLASS_H
#define SERVICECLASSCECLASS_H

#include <iostream>
#include <stdlib.h>
#include <vector>

class Navigation
{
public:
    Navigation(float x, float y);
    virtual ~Navigation();

public:
    int x;
    int y;
public:
    void navi();
};

#endif // SERVICECLASSCECLASS_H

    Navigation::Navigation(float a = 0, float b = 0)
    {
        x = a;
        y = b;
        
        navi();

    }
    Navigation::~Navigation()
    {

    }

    void Navigation::navi()
    {

        system("rostopic pub /move_base_simple/goal geometry_msgs/PoseStamped '[0,[0,0],'map']' '[[x,y,0],[0,0,0,1]]'");
    }

    int main()
    {
        Navigation na(1,2);
        



    }



