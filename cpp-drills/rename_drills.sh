#!/bin/bash
set -e
rename_one() {
  old="$1"; new="$2"
  if [ -f "$old" ]; then
    git mv "$old" "$new" 2>/dev/null || mv "$old" "$new"
    echo "renamed: $old -> $new"
  else
    echo "skip (not found): $old"
  fi
}
rename_one r1.cpp  01_args.cpp
rename_one r2.cpp  02_vector_sum.cpp
rename_one r3.cpp  03_word_count.cpp
rename_one r4.cpp  04_top_n_freq.cpp
rename_one r5.cpp  05_mlir_tokenizer.cpp
rename_one r6.cpp  06_vec2_operators.cpp
rename_one r7.cpp  07_matrix_big_five.cpp
rename_one r8.cpp  08_matrix_multiply.cpp
rename_one r9.cpp  09_span.cpp
rename_one r10.cpp 10_smallvector.cpp
