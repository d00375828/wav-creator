#include "ApplicationData.h"
#include "score_editor_aux.h"
#include <iostream>

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return score_editor(app_data);
}
