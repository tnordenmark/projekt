// ProjStruct.cpp
// Egendefinierade datatyper till programmet för att hantera en personlista
// double används istället för float då double är "standardflyttalet" i C++
// och prestandan inte är något hinder i ett program av den här kalibern
// Thomas Nordenmark 2014-01-14
// Ver 0.1
//------------------------------------------------------------------------------
#ifndef PROJSTRUCT_H
#define PROJSTRUCT_H
#include <string>

// Struct för att lagra personers attribut
struct Person
{
    std::string first_name;
    std::string last_name;
    std::string signature;
    double height;
};

// Enum för sorteringsalternativen
enum Sort
{
    NAME = 1,
    SIGN = 2,
    HEIGHT = 3
};

#endif // PROJSTRUCT_H
