typedef float float4 __attribute__((vector_size(16)));

float4 identity(float4 v) {
  return v;
}

float4 make(float4 a, float4 b) {
  return identity(a);
}

int main() {
  float4 v;
  identity(v);
  return 0;
}
