# Symbol Visibility Test

This test app serves to make symbol visibility easier to test in a C++ environment, especially one in which dynamic libraries are involved.

This project is currently macOS only.

# How to Use

The project specifies a dynamic library (`libvis`) and a host application, `vistest`. Both `libvis` and `vistest` compile and link `vis.cpp` where a handful of routines are defined with various visibility settings.

Each test grabs the function pointer for routines with the same name: one in `libvis` and one in `vistest`. It then compares the pointers for equality. Given that each symbol in the host application is visible for the host, the function pointers will (mis)match depending on the visibility settings of each function in the `libvis`.

To ensure the call into `libvis` is fetching `libvis`'s variant of the symbol, there are "getter" functions compiled into `libvis` alone.

Build and run the project and you'll see output in accordance with the tests.

## Example Output

```shell
MISMATCH for 'default'
    dylib: 0x100025f60
    local: 0x100000f00
MATCH for 'default_weak'
    dylib: 0x100000f10
    local: 0x100000f10
MISMATCH for 'hidden'
    dylib: 0x100025f80
    local: 0x100000f20
MISMATCH for 'hidden_weak'
    dylib: 0x100025f90
    local: 0x100000f30
```

# Additional Tests

You can run `nm` on both `libvis` and the `vistest` to see what symbols both export.

## Example Output

```shell
$ nm -C /path/to/liblibvis.dylib
0000000000000f80 t vis::hidden_function()
0000000000000f60 T vis::default_function()
0000000000000f40 T vis::get_hidden_function()
0000000000000f20 T vis::get_default_function()
0000000000000f90 t vis::hidden_weak_function()
0000000000000f70 T vis::default_weak_function()
0000000000000f50 T vis::get_hidden_weak_function()
0000000000000f30 T vis::get_default_weak_function()
```

```shell
$ nm -C /path/to/vistest
0000000100000df0 T compare_routines(char const*, void* (*)(), void* (*)())
0000000100000f20 t vis::hidden_function()
0000000100000f00 T vis::default_function()
                 U vis::get_hidden_function()
                 U vis::get_default_function()
0000000100000f30 t vis::hidden_weak_function()
0000000100000f10 T vis::default_weak_function()
                 U vis::get_hidden_weak_function()
                 U vis::get_default_weak_function()
0000000100000000 T __mh_execute_header
0000000100000e70 T _main
                 U _printf
```

Both `vistest` and `libvis` use `printf`-formatted output to keep from including C++ symbols and polluting the symbol tables of each artifact.

# Links

These are listed in no particular order. NOTE: Clang supports all attributes defined for GCC.

- Clang
    - [Clang attribute: `type_visibility`](https://clang.llvm.org/docs/AttributeReference.html#type-visibility)
    - [Clang attribute: `visibility`](https://clang.llvm.org/docs/AttributeReference.html#visibility)
    - [Clang bug: `visibility` attribute of a template method of a template class ignored](https://github.com/llvm/llvm-project/issues/103477)
    - [Clang command-line option `-fvisibility`](https://clang.llvm.org/docs/ClangCommandLineReference.html#cmdoption-clang-fvisibility)
- GCC
    - [GCC common function attributes: `visibility`](https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-visibility-function-attribute)
    - [GCC common type attributes: `visibility`](https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html#index-visibility-type-attribute)
    - [GCC common variable attributes: `visibility`](https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#index-visibility-variable-attribute)
    - [GCC command-line option `-fvisibility-ms-compat`](https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html#index-fvisibility-ms-compat)
    - [GCC wiki: Visibility](https://gcc.gnu.org/wiki/Visibility)
- nm
    - [`nm` symbol types and their meanings](https://sourceware.org/binutils/docs/binutils/nm.html)
