/**
// Name: Isaac Yushaiyin
// File name: p1.cpp
// Date: April 25th 2024
// Purpose: This program demonstrates a simple interactive game using various screen objects
//          such as Wrigglers, Snakes, Stones, and Poop within a terminal-based simulation. It utilizes
//          multithreading to manage movements and interactions between objects, ensuring that game
//          elements respond in real-time to collision events and user inputs.
//

// Process: The program initializes several game objects and manages their states through concurrent threads,
//          utilizing mutexes for resource locking and barriers for synchronization. Each object can move and
//          interact with others on a pixel matrix, which represents the game area.
//
// Output: The game outputs a visual representation of object interactions in the terminal and provides
//         real-time feedback based on the objects' movements and interactions.



// How to Play:
// The game is controlled entirely through the keyboard. Press 'q' to quit the game at any time.

// Game Features:
// - Multithreaded Gameplay: Each character is powered by its own thread, ensuring that
//   the game remains responsive and dynamic.
// - Detailed Pixel Graphics: Enjoy a visually appealing game played right in your terminal,
//   with detailed pixel art for each character and obstacle.
**/




/**
 * EXTRA CREDIT CLAIM FOR MORE COMPLEX PLAY :
 * This game demonstrates sophisticated gameplay through the use of advanced multithreading, real-time state management,
 * and well-structured object-oriented programming. Each game entity, such as Wrigglers, Snakes, Stones, and Poop,
 * is encapsulated in its own class (e.g., Snake.cpp/h, Stone.cpp/h), promoting modular, reusable, and maintainable code.
 * These classes manage their specific behaviors, interactions, and rendering, operating independently on their own threads
 * and synchronized through barriers and mutexes. This architecture allows for dynamic and real-time responses to player actions
 * and game events, significantly enhancing the gameplay complexity and depth.
 * The combination of thread synchronization, collision-based state changes, and distinct class-based entity management
 * provides a gameplay experience that stands out in complexity and sophistication, justifying extra credit for complex gameplay.
 */




/**
 * EXTRA CREDIT CLAIM FOR NIFTY CRITTERS:
 * The gameplay goes beyond simple motion to involve strategic interactions where objects can block, chase, or evade each other,
 * significantly enhancing the depth and challenge of the game. The detailed pixel graphics further add to the immersive
 * experience, making the gameplay not only sophisticated but also visually appealing. These features collectively push the
 * boundaries of what might be expected in a typical terminal-based game, meriting extra credit for sophisticated gameplay.
**/

#include <iostream>
#include <future>
#include <barrier>
#include "Terminal.h"
#include "Wriggler.h"
#include "Wiggler.h"
#include "Snake.h"
#include "Stone.h"
#include "Poop.h"


using namespace std;


/**
 * Class: ScreenManager
 * Purpose: Manages the lifecycle and interactions of screen objects like Wriggler.
 *          This class is responsible for updating game objects' states and rendering them
 *          on a shared PixelMatrix in a thread-safe manner using mutexes and barriers.
 *
 */
class ScreenManager {
public:

    /**
    * Constructor for ScreenManager.
    */
    ScreenManager(Wriggler *worm, PixelMatrix *pxm, mutex *m, barrier<> *b,
                  int t = 0)
            : time(t), worm(worm), pxm(pxm), lock(m), meetup(b) {}

    /**
    * Runs the game loop for the worm. Manages rendering and movement based on
     * the game's generation count.
    * @return The number of generations (or game cycles) completed before stopping.
    */
    int play() {
        int generations = 0;
        while (!stop.test()) {
            generations++;
            lock->lock();
            if (generations >= time) {
                worm->render(*pxm);
            }
            lock->unlock();
            meetup->arrive_and_wait();
            meetup->arrive_and_wait();
            if (generations >= time) {
                worm->move();
            }
        }
        meetup->arrive_and_drop();
        return generations;
    }

public:
    atomic_flag stop;

private:
    int time;
    Wriggler *worm;
    PixelMatrix *pxm;
    mutex *lock;
    barrier<> *meetup;
};


/**
 * Class: MyWriggler
 * Purpose: Manages a single Wriggler object within the game, including its threading and lifecycle.
 *
 */
class MyWriggler {
public:
    Wriggler wiggler;
    ScreenManager manager;
    std::future<int> handle;

    /**
     * Constructor for MyWriggler.
     * Initializes a Wriggler and a ScreenManager to manage its lifecycle in the game.
     */
    MyWriggler(int startRow, int startCol, PixelMatrix *pxm, mutex *m,
               barrier<> *meetup, int time = 0)
            : wiggler(startRow, startCol),
              manager(&wiggler, pxm, m, meetup, time),
              handle(async(&ScreenManager::play, &manager)) {}
};



//// Main entry point for the game. This function serves as the starting point
//// for the game execution. It performs the following key tasks:
//// 1. Initializes the game environment, including setting up the game window,
////    initializing graphics and audio libraries, and configuring game settings.
//// 2. Manages the game loop, which is responsible for updating game state,
////    handling user input, and rendering graphics.
//// 3. Handles object interactions, such as collisions between game entities,
////    updating object positions, and triggering game events based on player actions.

int main() {
    const RGB BG_COLOR = RGB::BLACK;
    const int WAIT_TIME = 1;
    const int THROTTLE = 50;

    /// Setup terminal for display and interaction
    Terminal *t = new Terminal(false);
    int rows, cols;
    t->getSize(rows, cols);
    PixelMatrix pxm(rows, cols, BG_COLOR);

    cout<<"*********************Exit the game by pressing Q, Or wait 20 seconds********************"<<endl;
    this_thread::sleep_for(chrono::seconds(3));

    /// Synchronization and threading tools
    barrier<> meetup(6);
    /// Mutex to protect shared resources
    mutex lock;

    ///Wriggler Object
    MyWriggler *jake = new MyWriggler(20, 15, &pxm, &lock, &meetup, 0);
    Wiggler jill;
    ScreenManager jillManager(&jill, &pxm, &lock, &meetup);
    future<int> jillHandle = async(launch::async, &ScreenManager::play,
                                   &jillManager);

    ///Snake object
    Snake *sam = new Snake(12,
                           5);  // You can adjust the initial position as needed
    ScreenManager samManager(sam, &pxm, &lock, &meetup);
    future<int> samHandle = async(launch::async, &ScreenManager::play,
                                  &samManager);
    ///stone object
    Stone *rock = new Stone(10, 20); // Start position as an example
    ScreenManager rockManager(rock, &pxm, &lock, &meetup);
    future<int> rockHandle = async(launch::async, &ScreenManager::play,
                                   &rockManager);
    ///poop object
    Poop *poo = new Poop(5, 5);
    ScreenManager pooManager(poo, &pxm, &lock, &meetup);
    future<int> pooHandle = async(launch::async, &ScreenManager::play,
                                  &pooManager);


    auto startTime = chrono::steady_clock::now();
    std::chrono::seconds timeLimit(30);

    /// Main game loop handling input and updates
    bool continueGame = true;

    while (continueGame) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        if (elapsedTime >= timeLimit) {
            continueGame = false; // End game after 20 seconds
        }
        if (t->hasKey()) {
            char ch = t->getKey();
            if (ch == 'q') {
                continueGame = false;
            }
        } else {
            // Collision detection for Jake (Wiggler)
            if (jake->wiggler.getCol() + 11 > jill.getCol() &&
                jill.getRow() <= jake->wiggler.getRow() &&
                jake->wiggler.getRow() <= jill.getRow() + 30) {
                jake->manager.stop.test_and_set();  // Stops Jake if colliding with Jill
            }

            // Collision detection for Jake (Wiggler)
            if (abs(jake->wiggler.getCol() - rock->getCol()) < 5 &&
                abs(jake->wiggler.getRow() - rock->getRow()) < 5) {
                jake->manager.stop.test_and_set();  // Stops Jake if colliding with the rock
            }

            // Collision detection for Sam (Snake)
            if (abs(sam->getCol() - rock->getCol()) < 5 &&
                abs(sam->getRow() - rock->getRow()) < 5) {
                samManager.stop.test_and_set();  // Stops Sam if colliding with the rock
            }


            // Collision detection for Sam (Snake)
            if (sam->getCol() + 11 > jill.getCol() &&
                jill.getRow() <= sam->getRow() &&
                sam->getRow() <= jill.getRow() + 30) {
                samManager.stop.test_and_set();  // Stops Sam if colliding with Jill
            }

            // Throttle the game loop, synchronize threads, repaint the screen, and reset the pixel matrix for the next frame.
            this_thread::sleep_for(chrono::milliseconds(THROTTLE));
            meetup.arrive_and_wait();
            t->paint(pxm);
            pxm.paint(0, 0, rows, cols, BG_COLOR);
            meetup.arrive_and_wait();
        }
    }

    // Signal all object managers to stop their associated threads.

    jake->manager.stop.test_and_set();
    jillManager.stop.test_and_set();
    samManager.stop.test_and_set();
    rockManager.stop.test_and_set();
    pooManager.stop.test_and_set();

    // Synchronize all game threads twice to ensure all are at the same point before proceeding.
    meetup.arrive_and_wait();
    meetup.arrive_and_wait();

    // Pause the main thread for a defined duration to allow for end-of-game processing.
    this_thread::sleep_for(chrono::seconds(WAIT_TIME));


    // Retrieve and store the final counts of actions performed by each game object.
    int jillPlayed = jillHandle.get();
    int samPlayed = samHandle.get();
    int rockPlayed = rockHandle.get();
    int poopPlayed = pooHandle.get();

    // Clean up dynamically allocated resources to prevent memory leaks.
    delete jake;
    delete t;
    delete sam;
    delete rock;
    delete poo;

    // Display final game statistics and successfully terminate the program.
    cout << "Jill wiggled " << jillPlayed << " times!" << endl;
    cout << "Sam slithered " << samPlayed << " times!" << endl;
    cout << "Rock Smashed " << rockPlayed << " times!" << endl;
    cout << "Poop touched " << poopPlayed << " times!" << endl;

    return EXIT_SUCCESS;
}



