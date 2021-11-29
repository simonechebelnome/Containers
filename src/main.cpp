#include "../includes/Vector.hpp"

int main(){

    ft::vector<int> Vec1(6, 4);
    ft::vector<int> Vec2(Vec1);

    std::cout << Vec1.size() << std::endl;
    std::cout << Vec2.size() << std::endl;

    Vec2.push_back(4);
    Vec2.insert(Vec2.begin() + 2, 2141);
    std::cout << Vec2.at(2) << std::endl;
    
    return 0;
}