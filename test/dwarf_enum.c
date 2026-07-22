// Test: named enum must emit correct DWARF (abbrev 20, with DW_AT_name).
// Compile: ./chibicc -g -c issues/issue_enum_dwarf.c -o /tmp/issue_enum_dwarf.o
// Verify: readelf --debug-dump=info /tmp/issue_enum_dwarf.o | grep -A10 DW_TAG_enumeration_type
// Expected: Abbrev Number: 20, DW_AT_name: Color, DW_AT_byte_size: 4

enum Color { RED = 0, GREEN = 1, BLUE = 2 };

int main() {
    enum Color c = RED;
    return (int)c;
}
