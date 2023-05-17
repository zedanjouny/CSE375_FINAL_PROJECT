#include <libchess/position.hpp>
#include <iostream>
#include <thread>
#include <tbb/tbb.h>
#include <tbb/concurrent_hash_map.h>

using namespace std;
using namespace libchess;
using namespace tbb;

struct MyHashCompare {
    static size_t hash( const string& fen ) {
        size_t h = 0;
        for( const char* s = fen.c_str(); *s; ++s )
            h = (h*17)^*s;
        return h;
    }
    //! True if strings are equal
    static bool equal( const string& fen, const string& y ) {
        return fen==y;
    }
};

struct boardOutcome {
    bool checkmate;
    int greatestDepth;
};

typedef concurrent_hash_map<string, boardOutcome, MyHashCompare> BoardMap;

class checkmate_in_n_concurrent_dfs_atomic_hashmap {
    Position pos;
    int threads_size;
    atomic<bool> checkmate_found;
    int maxdepth;
    BoardMap boardMap;

public:
    // Constructor initializing position, thread size, and checkmate-related variables
    checkmate_in_n_concurrent_dfs_atomic_hashmap(Position pos, int threads_size)
        : pos(pos), threads_size(threads_size), checkmate_found(false), maxdepth(-1), boardMap(threads_size) {}

    // Main function to find the answer
    bool findAnswer(int depth) {
        auto moves = this->pos.legal_moves();
        maxdepth = depth;
        vector<Position> ps(moves.size());

        // Create temporary positions
        for (int i = 0; i < moves.size(); i++) {
            Position t(this->pos.get_fen());
            t.makemove(moves[i]);
            ps[i] = t;
        }

        vector<thread> threads(threads_size);

        // Spawn multiple threads to perform the work concurrently
        for (int i = 0; i < threads.size(); i++) {
            int ending_index = (i + 1) * (ps.size() / threads_size);
            if (i == threads.size() - 1) {
                ending_index = ps.size();
            }
            threads[i] = thread(&checkmate_in_n_concurrent_dfs_atomic_hashmap::do_work, this, i * (ps.size() / threads_size), ending_index, ps, depth, i);
        }

        // Wait for all threads to finish
        for (int i = 0; i < threads.size(); i++) {
            threads[i].join();
        }

        // Return the value of checkmate_found
        return checkmate_found.load(memory_order_acquire);
    }

    // Worker function for each thread
    void do_work(int starting_index, int ending_index, vector<Position> ps, int depth, int thread_index) {
        for (int i = starting_index; i < ending_index; i++) {
            _opponentMove(depth, ps[i]);
        }
    }

    bool _answerMove(int depth, Position p) {
        if (checkmate_found.load(memory_order_relaxed)) {
            return true;
        }
        auto moves = p.legal_moves();

        for (const auto &move : moves) {
            Position temp(p.get_fen());
            temp.makemove(move);
            
            // Check if the board has already been processed
            BoardMap::const_accessor result;
            if (boardMap.find(result, temp.get_fen())) {
                if (depth <= result->second.greatestDepth) {
                    return result->second.checkmate;
                }
            }
            result.release();
            
            bool found = _opponentMove(depth, temp);

            // Store the board outcome in the concurrent_hash_map
            if (found) {
                BoardMap::accessor a;
                boardMap.insert(a, temp.get_fen());
                a->second.checkmate = true;
                a->second.greatestDepth = depth;
                a.release();
                return true;
            }
        }
        return false;
    }

    bool _opponentMove(int depth, Position p) {
        if (checkmate_found.load(memory_order_relaxed)) {
            return true;
        }
        auto moves = p.legal_moves();

        if (moves.size() == 0) {
            return p.is_checkmate();
        } else if (depth == 1) {
            return false;
        }

        for (const auto &move : moves) {
            Position temp(p.get_fen());
            temp.makemove(move);

            // Check if the board has already been processed
            BoardMap::const_accessor result;
            if (boardMap.find(result, temp.get_fen())) {
                if (depth <= result->second.greatestDepth) {
                    if (!result->second.checkmate) {
                        return false;
                    }
                }
            }
            result.release();

            bool found = _answerMove(depth - 1, temp);

            // Store the board outcome in the concurrent_hash_map
            if (!found) {
                BoardMap::accessor a;
                boardMap.insert(a, temp.get_fen());
                a->second.checkmate = false;
                a->second.greatestDepth = depth;
                a.release();
                return false;
            }
        }

        if (depth == maxdepth) {
            checkmate_found.store(true, memory_order_relaxed);
        }
        return true;
    }
};
