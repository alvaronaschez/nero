#include <iostream>

enum X: unsigned char {
    A,
    a=0,
    B,
    C,
};

int main(){
    std::cout << (int)X::A << std::endl;
    std::cout << (int)X::a << std::endl;
    std::cout << (int)X::B << std::endl;
    std::cout << (int)X::C << std::endl;
    return 0;
}
