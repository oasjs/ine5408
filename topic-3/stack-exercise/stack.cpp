#include <iostream>
using namespace std;
const int MAXSTACK = 30;

class Stack {
    private:
    int data[MAXSTACK];
    int head; 

    public: 
    Stack() {
        head = -1;
    }
    bool isFull() {
        if (head == MAXSTACK - 1) return true;
        else return false;
    }
    bool isEmpty() {
        if (head == -1) return true;
        else return false;
    }
    int add(int input) {
        if (this->isFull()) return -1;
        else {
            head++;
            data[head] = input;
            return head;
        }
    }
    int remove() {
        if (this->isEmpty()) return -1;
        else {
            head--;
            return data[head + 1];
        }
    }
    int clear() {
        head = -1;
        return head;
    }
    int getHead() {
        if (this->isEmpty()) return -1;
        else return data[head];
    }
    void printStack() {
        if (this->isEmpty()) {
            cout << "The stack is empty!\n";
            return;
        }
        cout << "\n";
        cout << "The stack:\n";
        for (int i = 0; i <= head; i++) {
            printf("[%d] %d\n", i, data[i]);
            cout << "";
        }
    }
};

class UserInterface {
    public:
    UserInterface() {}

    void displayDialog() {
        cout << "\n";
        cout << "Please select an option:\n";
        cout << "[1] Add\n[2] Remove\n[3] Clear\n[4] Show\n[5] Exit\n";
    }
    int requestAdd() {
        int input;
        cout << "Insert an integer to add to the stack:\n";
        cin >> input;
        printf("%d added to the stack.\n", input);
        cout << "";
        return input;
    }
};

int running = true;
int main() {
    Stack myStack;
    UserInterface ui;
    cout << "Welcome to Stack Manager!\n";
    
    while (running) {
        ui.displayDialog();
        int input;
        cin >> input;
        switch (input)
        {
        case 1:
        {
            int addInput = ui.requestAdd();
            myStack.add(addInput);
            break;
        }
        case 2:
            myStack.remove();
            break;
        case 3:
            myStack.clear();
            break;
        case 4:
            myStack.printStack();
            break;
        case 5:
            running = false;
            break;
        default:
            cout << "Please select a valid option.\n";
            break;
        }
    }
}
