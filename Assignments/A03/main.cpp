                ///////////////////////////////////////////////////////////////////////////////
                //                   
                // Author:           Trevor Amann
                // Email:            trevor.amann9@gmail.com
                // Label:            A03
                // Title:            Basic Program Organization - Commenting
                // Course:           CMPS 2143
                // Semester:         Spring 2021
                //
                // Description:
                //    The program we have created here is a circular array queue. The program pushes
                //    and pops integers from a queue.
                //
                // Usage:
                //       To use this program you must tell it what to push, pop, and when to print the list out. 
                //
                // Files:   main.cpp
                /////////////////////////////////////////////////////////////////////////////////


                #include <iostream>

                using namespace std;

                /**
                 * CircularArrayQue
                 * 
                 * Description:
                 *      This class implements a compressions algorithm called CircularArrayQue Coding.
                 *      CircularArrayQue coding assigns codes to characters such that the length of the 
                 *      code depends on the relative frequency or weight of the corresponding 
                 *      character   CircularArrayQue codes are of variable-length, and prefix-free
                 * 
                 * Public Methods:
                 *                          CircularArrayQue()
                 *                          CircularArrayQue(int size)    
                 *      void                Push(int item)
                 *      int                 Pop()
                 *      friend              ostream &operator 
                 * 
                 * Private Methods:
                 *      void                init()
                 *      bool                Full()
                 *
                 * 
                 * Usage: 
                 * 
                 *      Must call your push and pop functions in the main and tell it what integers to push and when to pop. 
                 *      Also tell it whent to print which is what the ostream is for.  
                 *      
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
                    /**
                     * Public : CircularArrayQue
                     * 
                     * Description:
                     *      The default constructor that intializes our queue. 
                     * 
                     * Params:
                     *      Container   : queue
                     *      int[10]     : queue size
                     * 
                     * Returns:
                     *      Nothing.
                     */
                    CircularArrayQue() {
                        Container = new int[10];
                        init(10);
                    }

                    /**
                     * Public : CircularArrayQue(int size)
                     * 
                     * Description:
                     *      Defines a queue of whatever size we choose in main. 
                     * 
                     * Params:
                     *      Container   : queue with size we declare in main.
                     *      int[size]   : queue size
                     * 
                     * Returns:
                     *      Nothing.
                     */
                    CircularArrayQue(int size) {
                        Container = new int[size];
                        init(size);
                    }

                    /**
                     * Public : Push(int item)
                     * 
                     * Description:
                     *      Pushes an integer onto the queue.
                     * 
                     * Params:
                     *      item    :  integer we are pushing
                     *      Rear    :  the rear of the queue
                     * 
                     * Returns:
                     *      FULL if we push too many integers onto the queue.
                     */
                    void Push(int item) {
                        if (!Full()) {
                            Container[Rear] = item;
                            Rear = (Rear + 1) % QueSize;
                            CurrentSize++;
                        } else {
                            cout << "FULL!!!!" << endl;
                        }
                    }

                    /**
                     * Public : Pop
                     * 
                     * Description:
                     *      Removes an integer from the queue. 
                     * 
                     * Params:
                     *      temp        :  a temporary slot that we use
                     *      Front       : The front of our queue
                     *      CurrentSize : the current size of the queue
                     *      QueSize     : the size of the queue that we declared
                     * 
                     * Returns:
                     *      List*   : a pointer to a linked list of integers.
                     */
                    int Pop() {
                        int temp = Container[Front];
                        Front = (Front + 1) % QueSize;
                        CurrentSize--;
                        return temp;
                    }

                    //This friend function is just letting us actually access the private variables in the class.
                    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
                };

                /**
                     * ostream &operator 
                     * 
                     * Description:
                     *      Prints the queue after pushing and popping
                     * 
                     * Params:
                     *      other.Front       : calls the front of our queue
                     *      other.CurrentSize : calls the current size of the queue
                     *      other.QueSize     : calls the size of the queue that we declared
                     * 
                     * Returns:
                     *      List*   : a pointer to a linked list of integers.
                     */
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
                    CircularArrayQue C1(5); //Declared the queue to be size 5 and named C1.

                    // C1.Push(34);
                    // C1.Push(38);
                    // C1.Push(44);
                    // C1.Push(22);
                    // C1.Push(99);
                    // C1.Push(100);

                    C1.Push(1);          //Pushed the integer 1 onto the queue.
                    C1.Push(2);          //Pushed the integer 2 onto the queue.
                    C1.Push(3);          //Pushed the integer 3 onto the queue.
                    // C1.Push(6);
                    // C1.Push(7);
                    cout << C1 << endl;  //Printed the queue. 

                    // C1.Push(1);
                    // C1.Push(2);
                    // C1.Push(3);

                    cout << C1 << endl;  //Printed the queue again. 
                }
