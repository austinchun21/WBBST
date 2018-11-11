
#include "weightBalancedBST.hpp"
#include "testing-logger.hpp"

#include "signal.h" // For signal
#include "unistd.h" // For alarm
#include <iostream>

using namespace std;

bool constructorTest(){
    TestingLogger log{"constructor test"};
    cout << "--------------" << endl;

    WBBST w;

    affirm(w.size() == 0);
    affirm(w.height() == -1);
    affirm(w.empty());

    return log.summarize();
}

bool insertTest(){
    TestingLogger log{"insert test"};
    cout << "--------------" << endl;

    WBBST w;

    w.insert(5);
    affirm(w.size() == 1);
    affirm(w.height() == 0);
    affirm(!w.empty());

    w.insert(10);
    affirm(w.size() == 2);
    affirm(w.height() == 1);
    
    w.insert(10);
    w.insert(1);
    w.insert(15);
    w.insert(14);
    affirm(w.size() == 5);

    return log.summarize();
}


// bool inorderTest(){
//     TestingLogger log{"inorder test"};
//     cout << "--------------" << endl;
//     WBBST w;
//     w.insert(10);
//     w.insert(1);
//     w.insert(16);
//     w.insert(14);
//     w.insert(12);
//     w.insert(7);
//     w.insert(15);

//     cout << w << endl;
//     w.printInOrder(cout); cout << endl;

//     // vector<int> res = w.inorder();

//     for(int i : res){
//         cout << i << ",";
//     }
//     cout << endl;


//     return log.summarize();
// }

bool printTest(){
    TestingLogger log{"print test"};
    cout << "--------------" << endl;
    
    WBBST w;
    
    w.insert(5);
    w.insert(10);    
    w.insert(1);
    w.insert(15);
    w.insert(10);
    w.insert(14);

    cout << w << endl;
    // w.print(cout);

    return log.summarize();
}

bool rebalanceTest(){
    TestingLogger log{"print test"};
    cout << "--------------" << endl;
    
    WBBST w (0.6);
    for(int i = 0; i < 20; ++i){
        w.insert(i);
    }
    // w.insert(10);
    // w.insert(1);
    // w.insert(16);
    // w.insert(14);
    // w.insert(12);
    // w.insert(7);
    // w.insert(15);
    // w.insert(20);
    // w.insert(21);
    // w.insert(22);
    // w.insert(23);
    // w.insert(24);
    // w.insert(25);

    cout << w << endl;
    cout << " Size: " << w.size() << ", Height: " << w.height() << endl;
    // w.rebalance();
    // cout << w << endl;

    return log.summarize();

}


 // Called if the test runs too long.
static void timeout_handler(int)
{
    // We go super-low-level here, because we can't trust anything in
    // the C/C++ library to really be working right.
    write(STDERR_FILENO, "Timeout occurred!\n", 18);
    abort();
}

int main()
{
    TestingLogger alltests{"All tests"};
    signal(SIGALRM, timeout_handler);   // Call this when the timer expires
    alarm(10);                          // set the timer at 10 seconds

    // List tests
    // affirm(constructorTest());
    // affirm(insertTest());
    // // affirm(inorderTest());
    // affirm(printTest());
    affirm(rebalanceTest());



    if (alltests.summarize(true)) {
        return 0;       // Error code of 0 == Success!
    } else {
        return 2;       // Arbitrarily chosen exit code of 2 means tests failed.
    }
}