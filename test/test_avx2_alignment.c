#include <immintrin.h>
#include <stdio.h>
#include <assert.h>

int main() {
  // Test AVX2 intrinsics with different alignments
  __m256 vec = _mm256_set_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
  
  // Allocate memory with different alignments
  float *aligned_32 = (float*)_mm_malloc(32, 32);
  float *aligned_64 = (float*)_mm_malloc(64, 64);
  float *unaligned = (float*)malloc(32);
  
  if (!aligned_32 || !aligned_64 || !unaligned) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }
  
  // Test unaligned load/store
  _mm256_storeu_ps(unaligned, vec);
  __m256 loaded_unaligned = _mm256_loadu_ps(unaligned);
  printf("Unaligned: %f\n", _mm256_cvtss_f32(loaded_unaligned));
  assert(_mm256_cvtss_f32(loaded_unaligned) == 8.0f);
  
  // Test aligned load/store
  _mm256_store_ps(aligned_32, vec);
  __m256 loaded_aligned = _mm256_load_ps(aligned_32);
  printf("Aligned (32): %f\n", _mm256_cvtss_f32(loaded_aligned));
  assert(_mm256_cvtss_f32(loaded_aligned) == 8.0f);
  
  
  // Test aligned load/store with 64-byte alignment
  _mm256_store_ps(aligned_64, vec);
  __m256 loaded_aligned_64 = _mm256_load_ps(aligned_64);
  printf("Aligned (64): %f\n", _mm256_cvtss_f32(loaded_aligned_64));
  assert(_mm256_cvtss_f32(loaded_aligned_64) == 8.0f);
  
  // Test with misaligned data
  float *misaligned = unaligned + 1;
  _mm256_storeu_ps(misaligned, vec);
  __m256 loaded_misaligned = _mm256_loadu_ps(misaligned);
  printf("Misaligned: %f\n", _mm256_cvtss_f32(loaded_misaligned));
  assert(_mm256_cvtss_f32(loaded_misaligned) == 8.0f);
  
  
  // Free memory
  _mm_free(aligned_32);
  _mm_free(aligned_64);
  free(unaligned);
  return 0;
}