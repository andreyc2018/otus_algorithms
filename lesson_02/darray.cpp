#include "DArray.h"
#include "stopwatch.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    int size = (argc > 1)? std::stoi(argv[1]) : 10;

    DArray<int> a;

    stop_watch_t t;
    t.start();
    for (int i = 0; i<size; i++)
	    a.add(i, i*i);
    auto l = t.stop();
    std::cout << "Add " << size << " elements took " << l << " " << t.period() << "\n";
    
    return 0;
}
