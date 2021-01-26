///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Trevor Amann
// Email:            trevor.amann9@gmail.com
// Label:            (program's label from assignment list)
// Title:            (short title from assignment, if any)
// Course:           (course number and prefix)
// Semester:         (semester and year)
//
// Description:
//       describe program here thoroughly 
//
// Usage:
//       how to use the program if necessary
//
// Files:            (list of all source files used in this program)
/////////////////////////////////////////////////////////////////////////////////





#include <iostream>

using namespace std;

/* In this section we are declaring a class called CircularArrayQue. 
* In the private section we initialize class variables and a function called init that we can call later.
*/
class CircularArrayQue {
private:
    int *Container;
    int Front;
    int Rear;
    int QueSize; // items in the queue
    int CurrentSize;
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    bool Full() {
        return CurrentSize == QueSize;
    }

// in the public section of this class we declare all of our functions that we use in the future to run our program. 

public:
    //This is the constructor for our class and it initializes the object which is our array or queue. 
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }

    //This is the second constructor of our class but this one is the parameterized constructor. 
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }

    //Below is our push function that we can call to add new items to our queue. 
    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }

    //Below is the pop function that we call when we want to pop whatever integer is at the back of the queue off of the queue. 
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }

    //This friend function is just letting us actually access the private variables in the class.
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

//This is our overloading function that we use to traverse the queue and then print out our end result after we go through our main function. 
ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}
