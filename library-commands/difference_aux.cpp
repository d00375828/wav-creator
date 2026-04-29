#include "difference_aux.h"
#include <iostream>
#include <cmath>
#include <string>

int difference(ApplicationData& /*app_data*/) {
    int minuend, subtrahend;

    std::cout << "Minuend? ";
    std::cin >> minuend;

    std::cout << "Subtrahend? ";
    std::cin >> subtrahend;

    int result = minuend - subtrahend;
    std::cout << "Difference " << result << std::endl;

    if (result == 0) {
        return 0;
    } else if (result < 0) {
        return 1;
    } else {
        return 2;
    }
}
