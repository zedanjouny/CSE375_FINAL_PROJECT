#include <checkmate_in_n_sequential.hpp>
#include <checkmate_in_n_concurrent.hpp>
#include <checkmate_in_n_modified.hpp>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

class timer {
public:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    timer() : lastTime(std::chrono::high_resolution_clock::now()) {}
    inline double elapsed() {
        std::chrono::time_point<std::chrono::high_resolution_clock> thisTime=std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double>(thisTime-lastTime).count();
        lastTime = thisTime;
        return deltaTime;
    }
};

// Test the solution
int main() {
    string fen = "r1bq2k1/ppp2r1p/2np1pNQ/2bNpp2/2B1P3/3P4/PPP2PPP/R3K2R w KQ - 0 1";
    timer stopwatch;
    auto pos = libchess::Position(fen, true);
    auto checkmate = checkmate_in_n(pos);
    auto modified = checkmate_in_n_modified(pos);
    auto checkmate_concurrent = checkmate_in_n_concurrent(pos);
    stopwatch.elapsed();
    bool answer = checkmate.findAnswer(5);
    cout << "Checkmate-In-N Sequential Returned " << answer << " with an execution time: " << stopwatch.elapsed() << endl;
    bool answer_modified = modified.findAnswer(5);
    cout << "Checkmate-In-N Modified Returned " << answer_modified << " with an execution time: " << stopwatch.elapsed() << endl;
    bool answer_concurrent = checkmate_concurrent.findAnswer(5);
    cout << "Checkmate-In-N Concurrent Returned " << answer_concurrent << " with an execution time: " << stopwatch.elapsed() << endl;
    return 0;
}