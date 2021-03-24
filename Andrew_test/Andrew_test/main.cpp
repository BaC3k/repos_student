#include <iostream>
#include <algorithm>
#include <map>
#include "rectangle.h"
#include "stack.h"
#include "allocator.h"

int main() {
    size_t N;
    float S;
    char option = '0';
    containers::stack<Rectangle<int>, allocators::my_allocator<Rectangle<int>, 800>> st;
    Rectangle<int> rec{};
    while (option != 'q') {
        std::cout << "choose option (m - man)" << std::endl;
        std::cin >> option;
        switch (option) {
            case 'q':
                break;
            case 'm':
                std::cout << "1) push new element into stack\n"
                          << "2) insert element into chosen position\n"
                          << "3) pop element from the stack\n"
                          << "4) delete element from the chosen position\n"
                          << "5) print stack\n"
                          << "6) count elements with area less then chosen value\n"
                          << "7) print top element\n"
                          << "8) test containers\n"
                          << "q) - quit" << std::endl;
                break;
            case '1': {
                rec =  Rectangle<int>(std::cin);
                st.push(rec);
                break;
            }
            case '2': {
                std::cout << "enter position to insert" << std::endl;
                std::cin >> N;
                std::cout << "enter rectangle" << std::endl;
                rec =  Rectangle<int>(std::cin);
                st.insert_by_number(N + 1, rec);
                break;
            }
            case '3': {
                st.pop();
                break;
            }
            case '4': {
                std::cout << "enter position to delete" << std::endl;
                std::cin >> N;
                st.delete_by_number(N + 1);
                break;
            }
            case '5': {
                std::for_each(st.begin(), st.end(), [](Rectangle<int> &REC) { REC.Print(std::cout); });
                break;
            }
            case '6': {
                std::cout << "enter max area" <<std::endl;
                std::cin >> S;
                std::cout << std::count_if(st.begin(), st.end(), [=](Rectangle<int> &X) { return X.Area() < S; })
                          << std::endl;
                break;
            }
            case '7' : {
                st.top().Print(std::cout);
                break;
            }
            case '8': {
                std::map<int, int, std::less<>, allocators::my_allocator<std::pair<const int, int>, 100>> mp;
                for(int i = 0; i < 2; ++i){
                    mp[i] = i * i;
                }
                std::for_each(mp.begin(), mp.end(), [](std::pair<int, int> X) { std::cout << X.first << ' ' << X.second << ",  "; });
                std::cout << std::endl;
                for(int i = 2; i < 10; ++i){
                    mp.erase(i - 2);
                    mp[i] = i * i;
                }
                std::for_each(mp.begin(), mp.end(), [](std::pair<int, int> X) { std::cout << X.first << ' ' << X.second << ",  "; });
                std::cout << std::endl;
                break;
            }
            default:
                std::cout << "Wrong. Try m - manual" << std::endl;
                break;
        }
    }
    return 0;
}