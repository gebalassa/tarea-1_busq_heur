/*
Ejemplo Singleton desde:
https://refactoring.guru/es/design-patterns/singleton/cpp/example#example-0
*/
#ifndef STATISTICS
#define STATISTICS
#include <memory>
#include <chrono>

using namespace std;

class Statistics
{
protected:
    Statistics() {}
    Statistics(Statistics& other) {}
    void operator=(const Statistics&) {}
public:
    // Instancia singleton
    static unique_ptr<Statistics> instance;
    // Estadísticas
    int negamax_visited_nodes = 0;
    long long move_time_micro = 0;

    void reset() {
        negamax_visited_nodes = 0;
        long long move_time_micro = 0;
    }
};

#endif STATISTICS