#include "../includes/Vector.hpp"
#include "../includes/List.hpp"

int main(){

    //* ################# VECTOR TEST #################

    ft::vector<int> Vec1(6, 4);
    ft::vector<int> Vec2(Vec1);

    std::cout << Vec1.size() << std::endl;
    std::cout << Vec2.size() << std::endl;

    Vec2.push_back(4);
    Vec2.insert(Vec2.begin() + 2, 2141);
    std::cout << Vec2.at(2) << std::endl;
    
    //* ################# LIST TEST #################

    ft::list<std::string> myList (4, "dio porco");
    ft::list<int> myList2 (3, 6);
    myList2.display();

    ft::list<int> myList3 (myList2);
    //myList3.display();

    return 0;
}