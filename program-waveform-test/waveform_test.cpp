#include "ApplicationData.h"
#include "waveform_test_aux.h"
#include <iostream>

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return waveform_test(app_data);
}
