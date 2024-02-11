#ifndef CLASS_H
#define CLASS_H
#include "person.h"
struct SchoolClass{
    struct Person strudents[26];
    char paralelka;
    int class_number;
    struct Person teacher;
};
#endif