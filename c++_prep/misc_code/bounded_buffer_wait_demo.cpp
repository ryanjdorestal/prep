#include <array>
#include <atomic>
#include <iostream>
#include <string>

// Take one available permit, or immediately report that none was available.
bool try_reserve(std::atomic<int>& permits) {
    int seen = permits.load();
    while (seen > 0) {
        if (permits.compare_exchange_strong(seen, seen - 1)) {
            return true;
        }
        // On failure, seen now contains the current count. Try again if positive.
    }
    return false;
}

int main() {
    std::array<std::string, 2> fridge{"groceries", ""};
    std::atomic<int> empty{1};
    int full = 1;
    auto show = [&](const char* event) {
        std::cout << event << " | empty=" << empty.load() << " full=" << full
                  << " slot[1]=" << (fridge[1].empty() ? "(vacant)" : fridge[1]) << '\n';
    };

    show("Start");
    bool pizza_has_slot = try_reserve(empty);
    show("Back in main after pizza call");
    bool cake_has_slot = try_reserve(empty);
    std::cout << std::boolalpha << "Pizza reserved: " << pizza_has_slot
              << ", cake reserved: " << cake_has_slot << '\n';
    if (pizza_has_slot) {
        fridge[1] = "pizza"; // Assume exclusive buffer access for this step.
        show("Pizza placed");
        ++full;             // Models signal(full) with no waiting consumer.
        show("Item announced");
    }

    // Replay two producers that both read 1 before either attempted a claim.
    std::atomic<int> last_slot{1};
    int pizza_saw = last_slot.load();
    int cake_saw = last_slot.load();
    bool pizza_won = last_slot.compare_exchange_strong(pizza_saw, 0);
    bool cake_won = last_slot.compare_exchange_strong(cake_saw, 0);
    std::cout << "Both saw 1 earlier. Pizza claim: " << pizza_won
              << ", cake claim: " << cake_won << ", empty=" << last_slot.load() << '\n';
}
