# dedup-cache

Fixed-capacity FIFO of recently seen ids.

Part of [integra-lib](https://gitlab.integrasources.com/internal-projects/integra-lib).
Header-only C++20, no exceptions, no RTTI.

## Use it

```bash
git submodule add ../dedup-cache.git external/integra/dedup-cache
```

```cmake
add_subdirectory(external/integra/dedup-cache)
target_link_libraries(app PRIVATE Integra::dedup_cache)
```

```cpp
#include <integra/dedup_cache.hpp>
```

## Develop it

```bash
cmake -S . -B build && cmake --build build -j && ctest --test-dir build
```

Tests are built only when this repository is the top-level project, so a consumer
never builds them. Style and pipeline come from the `ci-shared` submodule; run
`git submodule update --init` before `pre-commit`.
