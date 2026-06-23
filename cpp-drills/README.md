# cpp-drills

Self-contained C++ exercises building production fluency from scratch — written
barehand (blank file, no copy-paste), compiled with `-std=c++20 -Wall -Wextra`,
and verified with sanitizers where memory is involved. Each file isolates one
concept; the goal is closing the recognition-vs-recall gap (being able to *write*
C++ from a blank file, not just *read* it).

## Build

```bash
clang++ -std=c++20 -O0 -g 07_matrix_big_five.cpp -o build/07_matrix_big_five
./build/07_matrix_big_five

# memory-sensitive drills: run under AddressSanitizer
clang++ -std=c++20 -O0 -g -fsanitize=address 10_smallvector.cpp -o build/10_smallvector
./build/10_smallvector
```

All build artifacts go in `build/` (git-ignored). Source is `NN_concept.cpp`.

---

## Fundamentals (01–06)

Basic syntax, containers, and operators — rebuilding the production pathway.

| #  | File                   | Concepts |
|----|------------------------|----------|
| 01 | `01_args.cpp`          | `argc`/`argv`, command-line iteration |
| 02 | `02_vector_sum.cpp`    | `std::vector`, raw loop vs `std::accumulate`, signed/unsigned pitfalls |
| 03 | `03_word_count.cpp`    | `std::ifstream`, stream extraction, stream state vs buffer |
| 04 | `04_top_n_freq.cpp`    | `std::map`/`unordered_map`, `map → vector → sort`, lambda comparators |
| 05 | `05_mlir_tokenizer.cpp`| manual scanning, `std::string_view` (≈ LLVM `StringRef`), zero-copy views |
| 06 | `06_vec2_operators.cpp`| operator overloading (member vs free vs friend), const-correctness |

## Memory & ownership (07–13)

Value semantics, RAII, the Big Five, and the full ownership spectrum — owning
vs non-owning, built and observed by hand.

| #  | File                    | Concepts |
|----|-------------------------|----------|
| 07 | `07_matrix_big_five.cpp`| RAII, the Rule of Five, deep vs shallow copy, move semantics |
| 08 | `08_matrix_multiply.cpp`| matmul kernel, return-by-value, RVO/move elision, const accessor |
| 09 | `09_span.cpp`           | non-owning view (≈ LLVM `ArrayRef`), Rule of Zero, lifetime hazards |
| 10 | `10_smallvector.cpp`    | inline-buffer optimization, *conditional* ownership, raw storage + placement-new |
| 11 | `11_unique_ptr.cpp`     | sole ownership, move-only types, Rule of Zero, explicit `clone()` |
| 12 | `12_shared_ptr.cpp`     | reference counting, shared ownership; toy `SharedPtr<T>` w/ copy + move |
| 13 | `13_weak_ptr.cpp`       | non-owning observer, `lock()`/`expired()`, breaking `shared_ptr` cycles |

### Ownership cheat-sheet (the through-line of 07–13)

- **Owning** (frees its resource in the destructor → needs the Big Five, or
  delegates via Rule of Zero): `Matrix`, `SmallVector`, `unique_ptr`, `shared_ptr`.
- **Non-owning** (holds an address but never frees it → Rule of Zero): `Span`,
  `string_view`, `weak_ptr`.
- **The decisive question:** *"When this object dies, does the buffer die with it?"*
  Yes → owner. No → view.
- `unique_ptr` = sole owner (move-only). `shared_ptr` = co-owners (refcounted).
  `weak_ptr` = observer that can *detect* the object's death (`lock()`); needs a
  `shared_ptr` control block. Raw pointer / `Span` = observer that *cannot* detect
  death (dangles silently) — caller must guarantee it doesn't outlive the owner.

---

## Next (14+) — different axis

Templates and generic programming (a separate cluster from memory/ownership):
variadic templates + perfect forwarding, CRTP (the LLVM/MLIR static-polymorphism
idiom), `constexpr`, `std::optional`/`variant`/`expected`, iterators/ranges.
