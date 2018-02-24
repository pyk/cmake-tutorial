#include <iostream>
#include "math.h"

using namespace std;

int main(int argc, char **argv) {
    int result;

    result = math::add(1, 2);
    cout << "add 1 + 2 : " << result << endl;

    result = math::add(4, 2);
    cout << "add 4 + 2 : " << result << endl;

    result = math::sub(1, 2);
    cout << "sub 1 - 2 : " << result << endl;

    result = math::sub(4, 2);
    cout << "sub 4 - 2 : " << result << endl;

    result = math::mul(1, 2);
    cout << "mul 1 * 2 : " << result << endl;

    result = math::mul(4, 2);
    cout << "mul 4 * 2 : " << result << endl;
}
