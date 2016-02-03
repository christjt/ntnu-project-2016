#ifndef ROBOROBO2_MEMORY_H
#define ROBOROBO2_MEMORY_H
#include <memory>
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif //ROBOROBO2_MEMORY_H
