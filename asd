#ifndef SERVICECLASSCECLASS_H
#define SERVICECLASSCECLASS_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


class Navigation
{
public:
    Navigation(string a);
    virtual ~Navigation();
    string x;
    string s;
    char s1;
    void print()
    {
        cout << s << endl;



    }
    void navi()
    {


        s = "rostopic pub /move_base_simple/goal geometry_msgs/PoseStamped '[0,[0,0],'map']' '[[x,y,0],[0,0,0,1]]'";
        s.replace(s.find("x,y"), 3, x);
        

    }
    void command()
    {
        char temp[1000];
        sprintf(temp, "", 1000);
        system(temp);



    }

};

#endif // SERVICECLASSCECLASS_H

Navigation::Navigation(string a = " ")
{
    x = a;


}
Navigation::~Navigation()
{

}



int main()
{
    Navigation na("1,2");
    na.navi();
    na.print();



}

