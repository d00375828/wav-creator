#include "product_aux.h"
#include <iostream>
#include <cmath>
#include <string>

int product(ApplicationData& /*app_data*/) {
    int factor1, factor2;

    std::cout << "Factor 1? ";
    std::cin >> factor1;

    std::cout << "Factor 2? ";
    std::cin >> factor2;

    int result = factor1 * factor2;
    std::cout << "Product: " << result << std::endl;

    if (result == 0) {
        return 0;
    } else if (result < 0) {
        return 1;
    } else {
        return 2;
    }
}
