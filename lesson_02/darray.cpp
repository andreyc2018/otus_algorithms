#include "DArray.h"
#include "BArray.h"
#include "DBArray.h"
#include "stopwatch.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    int size = (argc > 1)? std::stoi(argv[1]) : 10;

    stop_watch_t t;

    if (size <= 10000) {
        DArray<int> a;
        t.start();
        for (int i = 0; i<size; i++)
            a.add(i, i*i);
        auto l = t.stop();
        std::cout << "DArray: add " << size << " elements took " << l << " " << t.period() << "\n";
    }
    
    DBArray<int> b(100);
    t.start();
    for (int i = 0; i<size; i++)
	    b.add(i, i*i);
    auto l = t.stop();
    std::cout << "DBArray: add " << size << " elements took " << l << " " << t.period() << "\n";

    BArray<int> sb;
    t.start();
    for (int i = 0; i<size; i++)
	    sb.add(i, i*i);
    l = t.stop();
    std::cout << "BArray: add " << size << " elements took " << l << " " << t.period() << "\n";

    return 0;
}
