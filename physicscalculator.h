#ifndef PHYSICSCALCULATOR_H
#define PHYSICSCALCULATOR_H

#include <vector>
#include <algorithm>
#include "mybubble.h"
using namespace std;
class PhysicsCalculator
{
public:

    PhysicsCalculator();
    ~PhysicsCalculator();
    void calculate(vector<MyBubble*>& );
 private:

};

#endif // PHYSICSCALCULATOR_H
