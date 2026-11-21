// CSCI 375 Project #3: 3 sim readers and 2 sim writers.
#include <cstdlib>
#include <iostream>

const char* const name[] = {"R1", "R2", "R3", "W1", "W2"};

int programCounter[5] = {}; // index of next instruction(switch case) per process.

struct Simulation {
    bool inside[5] = {};     // tracking which processes use the buffer 
    int completed[5] = {};
    int turn = 0;
};

void panic() {
    std::cerr << "PANIC: there is an illegal critical-section occupancy\n";
    std::exit(EXIT_FAILURE);
}

void event(const Simulation& s, int id, const char* action) {
    std::cout << "Turn " << s.turn << ": " << name[id] << ' ' << action;
    bool occupied = false;
    for (int i = 0; i < 5; ++i) {
        if (s.inside[i]) {
            std::cout << (occupied ? ", " : " | ") << name[i]
                      << (i < 3 ? " is reading" : " is writing");
            occupied = true;
        }
    }
    if (occupied) std::cout << " in the critical section.";
    else std::cout << " | The critical section is empty.";
    std::cout << '\n';
}

void enter(Simulation& s, int id) {
    if (s.inside[id]) panic();
    int readers = 0, writers = 0;
    int otherReader = -1;
   
    //integer is indentifiing readers and writer in crit section
    for (int i = 0; i < 5; ++i) {
        if (!s.inside[i]) continue;
        if (i < 3) {
    ++readers;
    otherReader = i;
    } else {
    ++writers;
}
    }
    if (writers > 0 || (id < 3 && readers >= 2) || (id >= 3 && readers > 0))
        panic();
   std::cout << "Turn " << s.turn << ": " << name[id];
if (otherReader == -1) {
    std::cout << " enters the empty critical section.\n";
} else {
    std::cout << " enters the critical section while " << name[otherReader] << " is reading.\n";
}
s.inside[id] = true;
}

void leave(Simulation& s, int id) {
    if (!s.inside[id]) panic();
    s.inside[id] = false;
    event(s, id, "leaves the critical section.");
}

// Subproject 1: Reader-Writer w/2 reader permits
struct Semaphores {
    int slots = 2;
    int mutex = 1;
    int rw_mutex = 1;
    int read_count = 0;
};

// Successful check and decrement merging one wait instruction (atomic wait)
bool wait(int& permits) {
    if (permits == 0) return false;
    --permits;
    return true;
}

void signal(int& permits) {
    ++permits;
}

void semaphoreReader(Simulation& s, Semaphores& sem, int id) {
    int& pc = programCounter[id];
    switch (pc) {
        case 0:
            if (wait(sem.slots)) {
                event(s, id, "reserves one of the two reader permits.");
                ++pc;
            } else {
                event(s, id, "waits to enter: both reader permits are reserved.");
            }
            break;
        case 1: if (wait(sem.mutex)) ++pc; break;
        case 2: ++sem.read_count; ++pc; break;
        // The first reader takes the rw mutex for the whole group on next turn
        case 3: 
            if (sem.read_count == 1) pc += 1;
            else pc += 2;
            break;
        case 4: 
            // Failed wait keeps the keeps the reader here until it gets rw mutex
            if (wait(sem.rw_mutex)) {
                event(s, id, "acquires rw_mutex before entry.");
                ++pc;
            } else {
                event(s, id, "waits to enter: rw_mutex is held.");
            }
            break;
        case 5: signal(sem.mutex); ++pc; break;
        case 6: enter(s, id); ++pc; break;
        case 7: leave(s, id); ++pc; break;
        case 8: if (wait(sem.mutex)) ++pc; break;
        case 9: --sem.read_count; ++pc; break;
        // The last reader releases the rw mutex (for group)
        case 10: 
            if (sem.read_count == 0) pc += 1;
            else pc += 2;
            break;
        case 11: signal(sem.rw_mutex);
            event(s, id, "signals rw_mutex; another process can now claim it.");
            ++pc; break;
        case 12: signal(sem.mutex); ++pc; break;
        case 13: signal(sem.slots);
            event(s, id, "returns one reader permit.");
            ++s.completed[id]; pc = 0; break;
    }
}

void semaphoreWriter(Simulation& s, Semaphores& sem, int id) {
    int& pc = programCounter[id];
    switch (pc) {
        case 0: 
            // If failed wait the writer tries again on next turn
            if (wait(sem.rw_mutex)) {
                event(s, id, "acquires rw_mutex before entry.");
                ++pc;
            } else {
                event(s, id, "waits to enter: rw_mutex is held.");
            }
            break;
        case 1: enter(s, id); ++pc; break;
        case 2: leave(s, id); ++pc; break;
        case 3: signal(sem.rw_mutex);
            event(s, id, "signals rw_mutex; another process can now claim it.");
            ++s.completed[id]; pc = 0; break;
    }
}

// Subproject 2: TestAndSet
bool TestAndSet(bool& target) {
    bool previous = target;
    target = true;
    return previous;
}

struct Locks {
    bool slot[2] = {};
    int readerSlot[3] = {};  // readers start at lock index 0 and keeping after sucessful claim
};

void tasReader(Simulation& s, Locks& locks, int id) {
    int& pc = programCounter[id];
    int& slot = locks.readerSlot[id];
    switch (pc) {
        case 0:
            if (!TestAndSet(locks.slot[slot])) pc = 2;
            else {
                event(s, id, "waits to enter: the attempted lock is held.");
                pc = 1;
            }
            break;
        case 1:
            slot = 1 - slot; // switching betwen index 0 and 1 for lock
            pc = 0;
            break;
        case 2: enter(s, id); ++pc; break;
        case 3: leave(s, id); ++pc; break;
        case 4: locks.slot[slot] = false;
            event(s, id, "releases its reader lock.");
            ++s.completed[id]; pc = 0; break;
    }
}

void tasWriter(Simulation& s, Locks& locks, int id) {
    int& pc = programCounter[id];
    // writer has to claim lock 1 before it can attempt lock 2
    switch (pc) {
        case 0: 
            if (!TestAndSet(locks.slot[0])) {
                event(s, id, "claims lock 1 before writing.");
                ++pc;
            } else {
                event(s, id, "waits to enter: lock 1 is held.");
            }
            break;
        case 1: 
            if (!TestAndSet(locks.slot[1])) {
                event(s, id, "claims lock 2 before writing.");
                ++pc;
            } else {
                event(s, id, "waits to enter: lock 2 is held.");
            }
            break;
        case 2: enter(s, id); ++pc; break;
        case 3: leave(s, id); ++pc; break;
        case 4: locks.slot[1] = false;
            event(s, id, "releases lock 2.");
            ++pc; break;
        case 5: locks.slot[0] = false;
            event(s, id, "releases lock 1.");
            ++s.completed[id]; pc = 0; break;
    }
}

int main() {
    for (int version = 1; version <= 2; ++version) {
        for (int& pc : programCounter) pc = 0;
        Simulation s;
        Semaphores sem;
        Locks locks;
        std::srand(375); //The srand func makes for repeatable random selections
        std::cout << "\nSubproject " << version
                  << (version == 1 ? " - Semaphores\n" : " - TestAndSet\n");
        for (s.turn = 1; s.turn <= 3000; ++s.turn) {
            int id = std::rand() % 5;
            // after an instruction is done, main picks a process again
            if (version == 1) {
                if (id < 3) semaphoreReader(s, sem, id);
                else semaphoreWriter(s, sem, id);
            } else {
                if (id < 3) tasReader(s, locks, id);
                else tasWriter(s, locks, id);
            }
        }
        std::cout << "Completed visits after 3000 turns:";
        for (int i = 0; i < 5; ++i)
            std::cout << ' ' << name[i] << '=' << s.completed[i];
        std::cout << '\n';
    }
}