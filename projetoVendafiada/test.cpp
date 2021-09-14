
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

int main()
{

    time_t result = time(NULL);
    printf("%s", ctime(&result));
    return 0;
}
