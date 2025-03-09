#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <string>

class DiningPhilosophers {
private:
    int thinkTime; 
    int eatTime;
    std::vector<std::mutex> forks; 
    std::vector<std::thread> philosophers;
    std::vector<std::string> states;
    std::vector<std::string> fork_states;
    std::mutex console_mutex;
    int numPhilosophers;
    bool running;

    //displays the state of each fork and philosopher
    void displayStates() {
        std::lock_guard<std::mutex> console_lock(console_mutex);
        system("cls");
        system("clear");

        std::cout << "\033[H";
        for (int i = 0; i < numPhilosophers; i++) {
            std::cout << "Philosopher " << i << ": " << states[i] << std::endl;
            std::cout << "Fork " << i << ": " << fork_states[i] << std::endl;
        }
        std::cout << "\nPress Enter to stop the simulation..." << std::endl;
    }

    void updateForkState(int forkId, const std::string& state) {
        fork_states[forkId] = state;
        displayStates();
    }

    void eat(int id) {
        int firstFork = id;
        int secondFork = (id + 1) % numPhilosophers;

        if (id % 2 == 0) {
            std::swap(firstFork, secondFork);
        }

        updateState(id, "hungry");

        std::lock_guard<std::mutex> lock1(forks[firstFork]);
        updateForkState(firstFork, "in use by philosopher " + std::to_string(id));
        updateState(id, "has one fork");
        
        std::lock_guard<std::mutex> lock2(forks[secondFork]);
        updateForkState(secondFork, "in use by philosopher " + std::to_string(id));
        updateState(id, "eating");

        std::this_thread::sleep_for(std::chrono::milliseconds(eatTime) * (std::rand() % 3 + 1));
        
        updateState(id, "putting down forks");
        updateForkState(firstFork, "free");
        updateForkState(secondFork, "free");
    }

public:
    DiningPhilosophers(int n, int timer) : numPhilosophers(n), running(true), thinkTime(timer), eatTime(timer) {
        forks = std::vector<std::mutex>(n);
        states = std::vector<std::string>(n, "waiting");
        fork_states = std::vector<std::string>(n, "free");
    }
    void updateState(int id, const std::string& state) {
        states[id] = state;
        displayStates();
    }
    void think(int id) {
        updateState(id, "thinking");
        std::this_thread::sleep_for(std::chrono::milliseconds(thinkTime)* (std::rand() % 3 + 1));
    }
    void start() {
        system("cls");  // Clear console at start
        for (int i = 0; i < numPhilosophers; i++) {
            philosophers.emplace_back([this, i]() { philosopherLife(i); });
        }
    }
    void philosopherLife(int id) {
        while (running) {
            think(id);
            eat(id);
        }
    }
    void stop() {
        running = false;
        for (auto& phil : philosophers) {
            if (phil.joinable()) {
                phil.join();
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <number_of_philosophers> <timer_in_ms>\n";
        return 1;
    }

    int numPhilosophers = std::atoi(argv[1]);
    int timer = std::atoi(argv[2]);

    if (numPhilosophers < 2) {
        std::cout << "Number of philosophers must be at least 2\n";
        return 1;
    }

    if (timer < 100) {
        std::cout << "Timer must be at least 100ms\n";
        return 1;
    }

    DiningPhilosophers dp(numPhilosophers, timer);
    dp.start();

    std::cout << "Press Enter to stop the simulation...\n";
    std::cin.get();

    dp.stop();
    return 0;
}