#ifndef SERVICECLASSCECLASS_H
#define SERVICECLASSCECLASS_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <stdio.h>
using namespace std;

class Navigation
{
public:
    Navigation();
    virtual ~Navigation();

public:
    int x;
    int y;

public:
    void navi(float a, float b);
};

#endif // SERVICECLASSCECLASS_H

    //Navigation::Navigation(float a, float b)
    //{
       // x = a;
        //y = b;
       // navi(a,b);
   // }
    Navigation::Navigation() {}
    Navigation::~Navigation()
    {

    }

    void Navigation::navi(float a, float b)
    {
        char buf[200];
	//s==>int
        sprintf(buf, "rostopic pub /move_base_simple/goal geometry_msgs/PoseStamped '[0,[0,0],'map']' '[[%f,%f,0],[0,0,0,1]]'",a,b);
	system(buf);
    }

    int main()
    {
        Navigation na = Navigation();
        na.navi(-1.2, -1.2);
    }



