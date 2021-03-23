#include <iostream>
#include <vector>

#include "Spring.h"
#include "Vector2D.h"

#define Print(x) std::cout << x;

int main()
{
    Print("Begin program\n");
    Vector2D r = Vector2D(0,0);
    r = Vector2D(-2,5) + Vector2D(1,2);
    Print(r);
    r += Vector2D(10,10);
    Print(r);

    
    return 0;
}