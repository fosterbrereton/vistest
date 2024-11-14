#include <cstdio>

namespace vis {
void* get_default_function();
void* get_default_weak_function();
void* get_hidden_function();
void* get_hidden_weak_function();
} // namespace vis

#include "libvis/libvis.hpp"

using nullary_fn = void*(*)();

void compare_routines(const char* name, nullary_fn dylib, nullary_fn local) {
    const auto value_dylib = dylib();
    const auto value_local = local();

    std::printf("%s for '%s'\n", value_dylib == value_local ? "MATCH" : "MISMATCH", name);
    std::printf("    dylib: %p\n", value_dylib);
    std::printf("    local: %p\n", value_local);
}

int main(int argc, const char * argv[]) {
    compare_routines("default", vis::get_default_function, vis::default_function);
    compare_routines("default_weak", vis::get_default_weak_function, vis::default_weak_function);
    compare_routines("hidden", vis::get_hidden_function, vis::hidden_function);
    compare_routines("hidden_weak", vis::get_hidden_weak_function, vis::hidden_weak_function);

    return 0;
}
