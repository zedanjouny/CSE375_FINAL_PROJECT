#include <string>
#include <chrono>
#include <iostream>
#include <checkmate_in_n_sequential.hpp>
#include <checkmate_in_n_modified.hpp>
#include <checkmate_in_n_concurrent_bfs.hpp>
#include <checkmate_in_n_concurrent_dfs.hpp>
#include <checkmate_in_n_concurrent_dfs_atomic.hpp>
#include <checkmate_in_n_concurrent_dfs_atomic_hashmap.hpp>

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
    timer stopwatch;
    string nine_moves = "6q1/3r1p2/2N1nk1K/3rp3/8/5PP1/8/1Q1N4 w - - 0 1";
    string two_moves = "3qr2k/pbpp2pp/1p5N/3Q2b1/2P1P3/P7/1PP2PPP/R4RK1 w - - 0 1";
    auto nine_pos = libchess::Position(nine_moves, true);
    auto two_pos = libchess::Position(two_moves, true);
    auto checkmate = checkmate_in_n(nine_pos);
    auto modified = checkmate_in_n_modified(nine_pos);
    auto checkmate_concurrent_bfs = checkmate_in_n_concurrent_bfs(nine_pos);
    auto checkmate_concurrent_dfs = checkmate_in_n_concurrent_dfs(nine_pos, 8);
    auto checkmate_concurrent_dfs_atomic = checkmate_in_n_concurrent_dfs_atomic(nine_pos, 8);
    auto checkmate_concurrent_dfs_atomic_hashmap = checkmate_in_n_concurrent_dfs_atomic_hashmap(nine_pos, 8);
    // Test 1
    stopwatch.elapsed();
    cout << "Checkmate-In-N Sequential Returned " << checkmate.findAnswer(1) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N Modified Returned " << modified.findAnswer(1) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N BFS Returned " << checkmate_concurrent_bfs.findAnswer(1) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs.findAnswer(1) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic.findAnswer(1) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap.findAnswer(1) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    stopwatch.elapsed();
    cout << "Checkmate-In-N Sequential Returned " << checkmate.findAnswer(2) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N Modified Returned " << modified.findAnswer(2) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N BFS Returned " << checkmate_concurrent_bfs.findAnswer(2) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs.findAnswer(2) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic.findAnswer(2) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap.findAnswer(2) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    stopwatch.elapsed();
    cout << "Checkmate-In-N Sequential Returned " << checkmate.findAnswer(3) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N Modified Returned " << modified.findAnswer(3) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N BFS Returned " << checkmate_concurrent_bfs.findAnswer(3) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs.findAnswer(3) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic.findAnswer(3) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap.findAnswer(3) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    stopwatch.elapsed();
    cout << "Checkmate-In-N Sequential Returned " << checkmate.findAnswer(4) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N Modified Returned " << modified.findAnswer(4) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N BFS Returned " << checkmate_concurrent_bfs.findAnswer(4) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs.findAnswer(4) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic.findAnswer(4) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap.findAnswer(4) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    stopwatch.elapsed();
    cout << "Checkmate-In-N Sequential Returned " << checkmate.findAnswer(5) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N Modified Returned " << modified.findAnswer(5) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N BFS Returned " << checkmate_concurrent_bfs.findAnswer(5) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs.findAnswer(5) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic.findAnswer(5) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap.findAnswer(5) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    stopwatch.elapsed();
    cout << "Checkmate-In-N Sequential Returned " << checkmate.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N Modified Returned " << modified.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N BFS Returned " << checkmate_concurrent_bfs.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    stopwatch.elapsed();
    cout << "Checkmate-In-N Sequential Returned " << checkmate.findAnswer(7) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N Modified Returned " << modified.findAnswer(7) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N BFS Returned " << checkmate_concurrent_bfs.findAnswer(7) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs.findAnswer(7) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic.findAnswer(7) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap.findAnswer(7) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    // Test 2 
    auto checkmate_concurrent_dfs_t2 = checkmate_in_n_concurrent_dfs(two_pos, 2);
    auto checkmate_concurrent_dfs_atomic_t2 = checkmate_in_n_concurrent_dfs_atomic(two_pos, 2);
    auto checkmate_concurrent_dfs_atomic_hashmap_t2 = checkmate_in_n_concurrent_dfs_atomic_hashmap(two_pos, 2);
    stopwatch.elapsed();
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs_t2.findAnswer(5) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic_t2.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap_t2.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    auto checkmate_concurrent_dfs_t4 = checkmate_in_n_concurrent_dfs(nine_pos, 4);
    auto checkmate_concurrent_dfs_atomic_t4 = checkmate_in_n_concurrent_dfs_atomic(nine_pos, 4);
    auto checkmate_concurrent_dfs_atomic_hashmap_t4 = checkmate_in_n_concurrent_dfs_atomic_hashmap(nine_pos, 4);
    stopwatch.elapsed();
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs_t4.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic_t4.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap_t4.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    auto checkmate_concurrent_dfs_t8 = checkmate_in_n_concurrent_dfs(nine_pos, 8);
    auto checkmate_concurrent_dfs_atomic_t8 = checkmate_in_n_concurrent_dfs_atomic(nine_pos, 8);
    auto checkmate_concurrent_dfs_atomic_hashmap_t8 = checkmate_in_n_concurrent_dfs_atomic_hashmap(nine_pos, 8);
    stopwatch.elapsed();
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs_t8.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic_t8.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap_t8.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    auto checkmate_concurrent_dfs_t16 = checkmate_in_n_concurrent_dfs(nine_pos, 16);
    auto checkmate_concurrent_dfs_atomic_t16 = checkmate_in_n_concurrent_dfs_atomic(nine_pos, 16);
    auto checkmate_concurrent_dfs_atomic_hashmap_t16 = checkmate_in_n_concurrent_dfs_atomic_hashmap(nine_pos, 16);
    stopwatch.elapsed();
    cout << "Checkmate-In-N DFS Returned " << checkmate_concurrent_dfs_t16.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic Returned " << checkmate_concurrent_dfs_atomic_t16.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "Checkmate-In-N DFS Atomic HashMap Returned " << checkmate_concurrent_dfs_atomic_hashmap_t16.findAnswer(6) << " with an execution time: " << stopwatch.elapsed() << endl;
    cout << "-------------------------------------" << endl;
    return 0;
}