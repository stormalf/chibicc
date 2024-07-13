#define BT_OFFSET_MASK                             0x0FFF
#define INDEX_MAX_KEYS		32

StaticAssertDecl(BT_OFFSET_MASK >= INDEX_MAX_KEYS,
				 "BT_OFFSET_MASK can't fit INDEX_MAX_KEYS");

//static_assert(8 > 10, "8 can't be greater than 10");
;
				 
int main() {
    int c = BT_OFFSET_MASK;
    return 0;
}