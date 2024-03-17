#define BT_OFFSET_MASK                             0x0FFF
#define INDEX_MAX_KEYS		32

StaticAssertDecl(BT_OFFSET_MASK >= INDEX_MAX_KEYS,
				 "BT_OFFSET_MASK can't fit INDEX_MAX_KEYS");
int main() {
    int c = BT_OFFSET_MASK;
    return 0;
}