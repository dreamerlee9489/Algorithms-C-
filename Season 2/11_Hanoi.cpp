#include <iostream>

using namespace std;

void move(int no, string from, string to) {
    cout << "move plate " << no << " from " + from + " to " + to << "\n";
}

void hanoi(int n, string p1, string p2, string p3) {
    if (n == 1) {
        move(n, p1, p3);
        return;
    }
    hanoi(n - 1, p1, p3, p2);
    move(n, p1, p3);
    hanoi(n - 1, p2, p1, p3);
}

int main(int argc, char const *argv[]) {
    hanoi(3, "A", "B", "C");
    return 0;
}

/*
move plate 1 from A to C
move plate 2 from A to B
move plate 1 from C to B
move plate 3 from A to C
move plate 1 from B to A
move plate 2 from B to C
move plate 1 from A to C
*/