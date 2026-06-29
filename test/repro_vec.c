typedef float float4 __attribute__((vector_size(16)));

float4 make_vec(float a, float b, float c, float d) {
  return (float4){a, b, c, d};
}

int main() {
  float4 v = make_vec(1.0f, 2.0f, 3.0f, 4.0f);
  return 0;
}
