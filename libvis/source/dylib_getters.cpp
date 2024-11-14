#include <vector>

#include "libvis/libvis.hpp"

namespace vis {

void* get_default_function() {
    return default_function();
}

void* get_default_weak_function() {
    return default_weak_function();
}

void* get_hidden_function() {
    return hidden_function();
}

void* get_hidden_weak_function() {
    return hidden_weak_function();
}


} // namespace vis
