#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

bool is_white(unsigned int piece) {
    return piece >= 0 && piece <= 5;
}
bool is_black(unsigned int piece) {
    return piece > 5 && piece < 12;
}

bool is_piece(unsigned piece) {
    return piece >= 0 && piece < 12; 
}
#endif