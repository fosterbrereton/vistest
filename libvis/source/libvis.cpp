#include <iostream>

namespace vis {

__attribute__((__visibility__("default")))
void* default_function() {
    return reinterpret_cast<void*>(&default_function);
}

__attribute__((__weak__, __visibility__("default")))
void* default_weak_function() {
    return reinterpret_cast<void*>(&default_weak_function);
}

__attribute__((__visibility__("hidden")))
void* hidden_function() {
    return reinterpret_cast<void*>(&hidden_function);
}

__attribute__((__weak__, __visibility__("hidden")))
void* hidden_weak_function() {
    return reinterpret_cast<void*>(&hidden_weak_function);
}

} // namespace vis
