#include <stdio.h>

int main() {

    printf("%llu\n", 0x7FFFFFFFFFFFFFFF );
    printf("%llu\n", 0x7FFFFFFFFFFFFFFE );
    printf("%llu\n", 0x7FFFFFFFFFFFFFFD );
    printf("%llu\n", 0x7FFFFFFF00000000 );
    printf("%llu\n", 0x000000007FFFFFFF );
    

//   i = 1; co_test[i].num = MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFF); co_test[i].expected = "9223372036854775807";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFE); co_test[i].expected = "9223372036854775806";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFD); co_test[i].expected = "9223372036854775805";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x7FFFFFFF00000000); co_test[i].expected = "9223372032559808512";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x000000007FFFFFFF); co_test[i].expected = "2147483647";

//   i++; co_test[i].num = MPRNT_OFF_T_C(0x7FFF000000000000); co_test[i].expected = "9223090561878065152";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x00007FFF00000000); co_test[i].expected = "140733193388032";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x000000007FFF0000); co_test[i].expected = "2147418112";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000007FFF); co_test[i].expected = "32767";

//   i++; co_test[i].num = MPRNT_OFF_T_C(0x7F00000000000000); co_test[i].expected = "9151314442816847872";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x007F000000000000); co_test[i].expected = "35747322042253312";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x00007F0000000000); co_test[i].expected = "139637976727552";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000007F00000000); co_test[i].expected = "545460846592";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x000000007F000000); co_test[i].expected = "2130706432";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x00000000007F0000); co_test[i].expected = "8323072";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000007F00); co_test[i].expected = "32512";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x000000000000007F); co_test[i].expected = "127";

//   i++; co_test[i].num = MPRNT_OFF_T_C(0x7000000000000000); co_test[i].expected = "8070450532247928832";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0700000000000000); co_test[i].expected = "504403158265495552";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0070000000000000); co_test[i].expected = "31525197391593472";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0007000000000000); co_test[i].expected = "1970324836974592";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000700000000000); co_test[i].expected = "123145302310912";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000070000000000); co_test[i].expected = "7696581394432";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000007000000000); co_test[i].expected = "481036337152";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000700000000); co_test[i].expected = "30064771072";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000070000000); co_test[i].expected = "1879048192";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000007000000); co_test[i].expected = "117440512";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000700000); co_test[i].expected = "7340032";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000070000); co_test[i].expected = "458752";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000007000); co_test[i].expected = "28672";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000700); co_test[i].expected = "1792";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000070); co_test[i].expected = "112";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000007); co_test[i].expected = "7";

//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000001); co_test[i].expected = "1";
//   i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000000); co_test[i].expected = "0";

//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFF) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223372036854775808";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFE) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223372036854775807";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFD) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223372036854775806";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFFFFFF00000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223372032559808513";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x000000007FFFFFFF) -MPRNT_OFF_T_C(1); co_test[i].expected = "-2147483648";

//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFF000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223090561878065153";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x00007FFF00000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-140733193388033";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x000000007FFF0000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-2147418113";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000007FFF) -MPRNT_OFF_T_C(1); co_test[i].expected = "-32768";

//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x7F00000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9151314442816847873";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x007F000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-35747322042253313";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x00007F0000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-139637976727553";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000007F00000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-545460846593";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x000000007F000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-2130706433";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x00000000007F0000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-8323073";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000007F00) -MPRNT_OFF_T_C(1); co_test[i].expected = "-32513";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x000000000000007F) -MPRNT_OFF_T_C(1); co_test[i].expected = "-128";

//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x7000000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-8070450532247928833";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0700000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-504403158265495553";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0070000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-31525197391593473";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0007000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-1970324836974593";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000700000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-123145302310913";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000070000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-7696581394433";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000007000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-481036337153";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000700000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-30064771073";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000070000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-1879048193";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000007000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-117440513";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000700000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-7340033";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000070000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-458753";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000007000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-28673";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000000700) -MPRNT_OFF_T_C(1); co_test[i].expected = "-1793";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000000070) -MPRNT_OFF_T_C(1); co_test[i].expected = "-113";
//   i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000000007) -MPRNT_OFF_T_C(1); co_test[i].expected = "-8";

//   i++; co_test[i].num =  MPRNT_OFF_T_C(0x0000000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-1";
return 0;
}
