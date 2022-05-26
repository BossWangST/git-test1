#include <stdio.h>
void B();
int main()
{
    //Here is a new line.
    printf("Added a line!");

    B();
    return 0;
}

void B(){
    printf("New func B!");
}

