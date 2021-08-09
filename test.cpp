#ifndef SERVICECLASSCECLASS_H
#define SERVICECLASSCECLASS_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <unistd.h>
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
    void navi(double a, double b);
    void navi2(double a, double b);
    void navi3(double a, double b);
};

#endif // SERVICECLASSCECLASS_H


Navigation::Navigation() {}
Navigation::~Navigation()
{

}

void Navigation::navi(double a, double b) // 1번->2번 방향
{
    char buf[200];
    sprintf(buf, "rostopic pub /move_base_simple/goal geometry_msgs/PoseStamped '[0,[0,0],'map']' '[[%lf,%lf,0],[0,0,1,-0.5]]'", a, b);
    system(buf);
}

void Navigation::navi2(double a, double b) // 2번->3번 방향
{
    char buf[200];
    sprintf(buf, "rostopic pub /move_base_simple/goal geometry_msgs/PoseStamped '[0,[0,0],'map']' '[[%lf,%lf,0],[0,0,1,0.35]]'", a, b);
    system(buf);
}

void Navigation::navi3(double a, double b) // 2번->4번 방향
{
    char buf[200];
    sprintf(buf, "rostopic pub /move_base_simple/goal geometry_msgs/PoseStamped '[0,[0,0],'map']' '[[%lf,%lf,0],[0,0,1,2]]'", a, b);
    system(buf);
}

int main()
{
    double x = -0.0179, y = 0.1403; // 터틀 초기좌표(lower_left)
    int i = 0;
    bool fin = true;
    Navigation na = Navigation();

    while (1)
    {    
            for (i = 0; i < 4; i++) //4번으로 쪼갬
            {
                if (fin == true)
                {
                    if (x >= -1.2065 && y >= -1.2435) // 아래->위로 올라갈 때
                    {
                        x = x - 0.2758;
                        y = y - 0.29715;
                        na.navi(x, y);
                        sleep(10);

                        if (x == -1.2065 && y == -1.2435)
                        {
                            na.navi2(x, y);
                            sleep(10);
                            x = x + 0.1;
                            y = y + 0.1;                           
                            na.navi3(x, y);
                            fin = false;
                            break; //for에 대한 break
                        }                        
                    }
                }                         
                if (fin == false)
                {            
                    if (x <= -0.0179 && y <= 0.1403) // 위->아래로 내려갈 때
                    {
                        x = x + 0.2758;
                        y = y + 0.29715;
                        na.navi3(x, y);
                        sleep(10);
                        if (x == -0.0179 && y == 0.1403)
                        {
                            na.navi2(x, y);
                            sleep(10);
                            x = x + 0.1;
                            y = y + 0.1;                            
                            na.navi(x, y);
                            fin = true;
                            break; //for에 대한 break
                        }                   
                    }
                }
            }
            if (x == -3.6636 && y == 0.1594) // upper_right
            {
                break;
            }
            else
                continue;           
    }
    sleep(60);
}





