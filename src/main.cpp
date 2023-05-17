#include <checkmate_in_n_sequential.hpp>
#include <checkmate_in_n_concurrent_bfs.hpp>
#include <checkmate_in_n_concurrent_dfs.hpp>
#include <checkmate_in_n_concurrent_dfs_atomic.hpp>
#include <checkmate_in_n_concurrent_dfs_atomic_hashmap.hpp>
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
    // 2 moves
    // 3qr2k/pbpp2pp/1p5N/3Q2b1/2P1P3/P7/1PP2PPP/R4RK1 w - - 0 1
    // 9 moves
    // 6q1/3r1p2/2N1nk1K/3rp3/8/5PP1/8/1Q1N4 w - - 0 1
    string fen = "6q1/3r1p2/2N1nk1K/3rp3/8/5PP1/8/1Q1N4 w - - 0 1";
    timer stopwatch;
    auto pos = libchess::Position(fen, true);
    auto checkmate = checkmate_in_n(pos);
    auto modified = checkmate_in_n_modified(pos);
    auto checkmate_concurrent = checkmate_in_n_concurrent_bfs(pos);
    unsigned int numThreads = std::thread::hardware_concurrency();
    auto checkmate_concurrent_1 = checkmate_in_n_concurrent_dfs(pos, 8);
    auto checkmate_concurrent_hashmap = checkmate_in_n_concurrent_dfs_atomic_hashmap(pos, 8);
    stopwatch.elapsed();
    bool answer = checkmate.findAnswer(5);
    cout << "Checkmate-In-N Sequential Returned " << answer << " with an execution time: " << stopwatch.elapsed() << endl;
    // bool answer_modified = modified.findAnswer(7);
    // cout << "Checkmate-In-N Modified Returned " << answer_modified << " with an execution time: " << stopwatch.elapsed() << endl;
    // bool answer_concurrent = checkmate_concurrent.findAnswer(5);
    // cout << "Checkmate-In-N Concurrent Returned " << answer_concurrent << " with an execution time: " << stopwatch.elapsed() << endl;
    // printf("Running the concurrent version with %d threads\n", numThreads);
    bool answer_concurrent_1 = checkmate_concurrent_1.findAnswer(5);
    cout << "Checkmate-In-N Concurrent_1 Returned " << answer_concurrent_1 << " with an execution time: " << stopwatch.elapsed() << endl;

    auto checkmate_concurrent_2 = checkmate_in_n_concurrent_dfs_atomic(pos, 8);
    stopwatch.elapsed();
    bool answer_concurrent_2 = checkmate_concurrent_2.findAnswer(5);
    cout << "Checkmate-In-N Concurrent_2 Returned " << answer_concurrent_2 << " with an execution time: " << stopwatch.elapsed() << endl;
    bool answer_hashmap = checkmate_concurrent_hashmap.findAnswer(5);
    cout << "Checkmate-In-N Concurrent_hashmap Returned " << answer_concurrent_2 << " with an execution time: " << stopwatch.elapsed() << endl;
    return 0;
}