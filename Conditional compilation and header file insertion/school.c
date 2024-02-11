#include <stdio.h>
#include "schoolclass.h"
#include "schoolroom.h"
struct School{
    struct SchoolClass school_classes[20];
    struct SchoolRoom school_rooms[10];
};
int main(){
    struct School school;
    return 0;
}