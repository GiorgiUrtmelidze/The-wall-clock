#include <iostream>
#include "Time.h"

using namespace std;

int main() {
    Time t {};

    t.set_radius(300);
    t.draw_clock();

    return 0;
}
