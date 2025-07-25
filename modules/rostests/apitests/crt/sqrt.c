/*
 * PROJECT:     ReactOS API tests
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     Tests for sqrt
 * COPYRIGHT:   Copyright 2021 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

#if !defined(_CRTBLD) && !defined(_M_IX86)
#define _CRTBLD // we don't want inline sqrt!
#endif
#include "math_helpers.h"

#ifdef _MSC_VER
#pragma function(sqrt)
#endif

#if !defined(_M_IX86)
#define HAS_SQRTF
#elif (defined(TEST_UCRTBASE) || defined(TEST_STATIC_CRT))
#define HAS_LIBM_SSE2
#endif


// These are expected to match exactly
static TESTENTRY_DBL s_sqrt_exact_tests[] =
{
    { 0x0000000000000000 /*  0.000000 */, 0x0000000000000000 /*  0.000000 */ },
    { 0x8000000000000000 /* -0.000000 */, 0x8000000000000000 /* -0.000000 */ },
    { 0x7ff0000000000000 /*  1.#INF00 */, 0x7ff0000000000000 /*  1.#INF00 */ },
    { 0x7ff0000000000001 /*  1.#SNAN0 */, 0x7ff8000000000001 /*  1.#QNAN0 */ },
    { 0x7ff7ffffffffffff /*  1.#SNAN0 */, 0x7fffffffffffffff /*  1.#QNAN0 */ },
    { 0x7ff8000000000000 /*  1.#QNAN0 */, 0x7ff8000000000000 /*  1.#QNAN0 */ },
    { 0x7ff8000000000001 /*  1.#QNAN0 */, 0x7ff8000000000001 /*  1.#QNAN0 */ },
    { 0x7fffffffffffffff /*  1.#QNAN0 */, 0x7fffffffffffffff /*  1.#QNAN0 */ },
    { 0xfff0000000000000 /* -1.#INF00 */, 0xfff8000000000000 /* -1.#IND00 */ },
    { 0xfff0000000000001 /* -1.#SNAN0 */, 0xfff8000000000001 /* -1.#QNAN0 */ },
    { 0xfff7ffffffffffff /* -1.#SNAN0 */, 0xffffffffffffffff /* -1.#QNAN0 */ },
    { 0xfff8000000000000 /* -1.#IND00 */, 0xfff8000000000000 /* -1.#IND00 */ },
    { 0xfff8000000000001 /* -1.#QNAN0 */, 0xfff8000000000001 /* -1.#QNAN0 */ },
    { 0xffffffffffffffff /* -1.#QNAN0 */, 0xffffffffffffffff /* -1.#QNAN0 */ },
};

void Test_sqrt_exact(void)
{
    for (int i = 0; i < _countof(s_sqrt_exact_tests); i++)
    {
        double x = u64_to_dbl(s_sqrt_exact_tests[i].x);
        double z = sqrt(x);
        ok_eq_dbl_exact("sqrt", s_sqrt_exact_tests[i].x, z, s_sqrt_exact_tests[i].result);
    }
}

// This table is autogenerated by `python gen_math_tests.py sqrt`
static TESTENTRY_DBL_APPROX s_sqrt_approx_tests[] =
{
//  {    x,                     {    y_rounded,               y_difference           } }
    {                 0x0.0p+0, {                 0x0.0p+0,                 0x0.0p+0 }, 0 }, // sqrt(0.0) == 0.0
    {  0x0.8000000000000p-1022, {   0x1.6a09e667f3bcdp-512,  -0x1.bdd3413b26456p-566 }, 0 }, // sqrt(1.1125369292536007e-308) == 1.0547686614862998913e-154
    {  0x1.0000000000000p-1022, {   0x1.0000000000000p-511,                 0x0.0p+0 }, 0 }, // sqrt(2.2250738585072014e-308) == 1.4916681462400413487e-154
    {  0x0.fffffffffffffp-1022, {   0x1.fffffffffffffp-512,  -0x1.0000000000001p-618 }, 0 }, // sqrt(2.225073858507201e-308) == 1.491668146240041183e-154
    {     0x1.fae147ae147aep-5, {     0x1.fd6efe4c9b8a5p-3,   -0x1.135f48b7eecd4p-58 }, 0 }, // sqrt(0.061875) == 0.24874685927665498757
    {     0x1.fae147ae147aep-4, {     0x1.6839537fece62p-2,   -0x1.1149218ddbc4ep-56 }, 0 }, // sqrt(0.12375) == 0.35178118198675721501
    {     0x1.7c28f5c28f5c2p-3, {     0x1.b92eb28102dedp-2,   -0x1.dd4c6e6767994p-56 }, 0 }, // sqrt(0.18562499999999998) == 0.43084219849035213145
    {     0x1.fae147ae147aep-3, {     0x1.fd6efe4c9b8a5p-2,   -0x1.135f48b7eecd4p-57 }, 0 }, // sqrt(0.2475) == 0.49749371855330997514
    {     0x1.3cccccccccccdp-2, {     0x1.1cc8329668782p-1,   -0x1.558a45c49cf55p-55 }, 0 }, // sqrt(0.309375) == 0.55621488653217473113
    {     0x1.7c28f5c28f5c2p-2, {     0x1.37f68c10e7674p-1,    0x1.02bb1cf94b498p-55 }, 0 }, // sqrt(0.37124999999999997) == 0.60930288034769700152
    {     0x1.bb851eb851eb8p-2, {     0x1.50f568f01cb10p-1,   -0x1.41fc1967f7cefp-57 }, 0 }, // sqrt(0.433125) == 0.65812232905440914103
    {     0x1.fae147ae147aep-2, {     0x1.6839537fece62p-1,   -0x1.1149218ddbc4ep-55 }, 0 }, // sqrt(0.495) == 0.70356236397351443003
    {     0x1.1d1eb851eb852p-1, {     0x1.7e133eb974a7cp-1,   -0x1.1180586e61853p-55 }, 0 }, // sqrt(0.556875) == 0.746240577829964972
    {     0x1.3cccccccccccdp-1, {     0x1.92be1ae1f8271p-1,   -0x1.c18b49f64d347p-55 }, 0 }, // sqrt(0.61875) == 0.78660663612761367436
    {     0x1.5c7ae147ae148p-1, {     0x1.a666666666667p-1,   -0x1.9fce59fce59fdp-55 }, 0 }, // sqrt(0.680625) == 0.82500000000000002153
    {     0x1.7c28f5c28f5c2p-1, {     0x1.b92eb28102dedp-1,   -0x1.dd4c6e6767994p-55 }, 0 }, // sqrt(0.7424999999999999) == 0.8616843969807042629
    {     0x1.9bd70a3d70a3dp-1, {     0x1.cb327c854c96bp-1,   -0x1.e4efbf9097b61p-56 }, 0 }, // sqrt(0.804375) == 0.89686955573260482435
    {     0x1.bb851eb851eb8p-1, {     0x1.dc880e4988d9bp-1,   -0x1.dd55c14a82404p-56 }, 0 }, // sqrt(0.86625) == 0.93072552344931422562
    {     0x1.db33333333333p-1, {     0x1.ed41c63b3b690p-1,    0x1.e2df7ff2641dap-55 }, 0 }, // sqrt(0.928125) == 0.96339244339988466498
    {     0x1.fae147ae147aep-1, {     0x1.fd6efe4c9b8a5p-1,   -0x1.135f48b7eecd4p-56 }, 0 }, // sqrt(0.99) == 0.99498743710661995027
    {     0x1.0000000000000p+0, {     0x1.0000000000000p+0,                 0x0.0p+0 }, 0 }, // sqrt(1.0) == 1.0
    {     0x1.8fd70a3d70a3ep+0, {     0x1.3fef9d46c7c43p+0,    0x1.25726bc495325p-54 }, 0 }, // sqrt(1.5618750000000001) == 1.2497499749949987994
    {     0x1.0fd70a3d70a3ep+1, {     0x1.751236a04f4c6p+0,    0x1.4230998b71f8dp-56 }, 0 }, // sqrt(2.1237500000000002) == 1.4573091641789672931
    {     0x1.57c28f5c28f5cp+1, {     0x1.a3879693e7f9ap+0,    0x1.c7e64d7fd8af5p-55 }, 0 }, // sqrt(2.685625) == 1.6387876616572385974
    {     0x1.9fae147ae147bp+1, {     0x1.cd5541212a31dp+0,    0x1.ab781125df393p-54 }, 0 }, // sqrt(3.2475) == 1.8020821290940099807
    {     0x1.e79999999999ap+1, {     0x1.f3a6ad107e69bp+0,   -0x1.2222f1f2f3c9fp-58 }, 0 }, // sqrt(3.809375) == 1.951762024428183247
    {     0x1.17c28f5c28f5cp+2, {     0x1.0b9dcf23af432p+1,    0x1.048752b3e4e1dp-53 }, 0 }, // sqrt(4.37125) == 2.0907534527055072779
    {     0x1.3bb851eb851ecp+2, {     0x1.1c4bd2aff3a9dp+1,    0x1.d5dfec1857c25p-53 }, 0 }, // sqrt(4.933125) == 2.2210639342441271621
    {     0x1.5fae147ae147bp+2, {     0x1.2c0cd5437ed81p+1,    0x1.70499a54cc435p-55 }, 0 }, // sqrt(5.495) == 2.3441416339462084872
    {     0x1.83a3d70a3d70ap+2, {     0x1.3b04679ac0e23p+1,    0x1.d54b1af5febb8p-53 }, 0 }, // sqrt(6.056875) == 2.4610719209320153037
    {     0x1.a79999999999ap+2, {     0x1.494e02448f18ap+1,   -0x1.1bd56ea8fa29bp-55 }, 0 }, // sqrt(6.61875) == 2.5726931414375870636
    {     0x1.cb8f5c28f5c29p+2, {     0x1.56ff6353105f5p+1,   -0x1.9bdf07b23fe8ap-53 }, 0 }, // sqrt(7.180625) == 2.6796688228212082618
    {     0x1.ef851eb851eb8p+2, {     0x1.642a19d07b4b0p+1,    0x1.931e6a950975ap-53 }, 0 }, // sqrt(7.7425) == 2.7825348155953053081
    {     0x1.09bd70a3d70a4p+3, {     0x1.70dc91d256c82p+1,    0x1.8b8fc7cf8d298p-54 }, 0 }, // sqrt(8.304375) == 2.881731250481210346
    {     0x1.1bb851eb851ecp+3, {     0x1.7d22cffe5d4a6p+1,   -0x1.7ee6debacac42p-57 }, 0 }, // sqrt(8.86625) == 2.9776248924268484582
    {     0x1.2db3333333333p+3, {     0x1.8906f8406e4bbp+1,   -0x1.9d773b35938d1p-53 }, 0 }, // sqrt(9.428125) == 3.0705251993755074286
    {     0x1.3fae147ae147bp+3, {     0x1.9491b0ce92840p+1,    0x1.c3fcaa0e69c5dp-53 }, 0 }, // sqrt(9.99) == 3.1606961258558216882
    {     0x1.4000000000000p+3, {     0x1.94c583ada5b53p+1,   -0x1.b7ed750df3ccap-53 }, 0 }, // sqrt(10.0) == 3.162277660168379332
    {     0x1.f3ccccccccccdp+3, {     0x1.f9dcfc285c39bp+1,    0x1.14b044de717b9p-54 }, 0 }, // sqrt(15.61875) == 3.9520564267226752686
    {     0x1.53ccccccccccdp+4, {     0x1.26f04a8f33a0ap+2,   -0x1.6fee5aec212cep-53 }, 0 }, // sqrt(21.2375) == 4.6084162138418010638
    {     0x1.adb3333333334p+4, {     0x1.4baad4619f12ap+2,   -0x1.39de61efe3304p-54 }, 0 }, // sqrt(26.856250000000003) == 5.1823016122182625084
    {     0x1.03ccccccccccdp+5, {     0x1.6cb73d578155cp+2,    0x1.0a54bacd82e1dp-52 }, 0 }, // sqrt(32.475) == 5.6986840586226572648
    {     0x1.30c0000000000p+5, {     0x1.8b0244b135674p+2,   -0x1.a1e9fcfa11cbep-52 }, 0 }, // sqrt(38.09375) == 6.1720134478142543982
    {     0x1.5db3333333334p+5, {     0x1.a72384fbfeea3p+2,    0x1.92db5d17241b8p-53 }, 0 }, // sqrt(43.712500000000006) == 6.611542936410532431
    {     0x1.8aa6666666667p+5, {     0x1.c183011272020p+2,    0x1.19deed5adbb95p-53 }, 0 }, // sqrt(49.331250000000004) == 7.0236208610658935726
    {     0x1.b79999999999ap+5, {     0x1.da6bc0c4b923ep+2,   -0x1.662c875f5012fp-53 }, 0 }, // sqrt(54.95) == 7.412826721298697863
    {     0x1.e48cccccccccdp+5, {     0x1.f215ffece1627p+2,   -0x1.ad37008177888p-52 }, 0 }, // sqrt(60.56875) == 7.782592755630992248
    {     0x1.08c0000000000p+6, {     0x1.045696ff1d4efp+3,    0x1.6b4421c44d0c1p-53 }, 0 }, // sqrt(66.1875) == 8.1355700476364899897
    {     0x1.1f3999999999ap+6, {     0x1.0f29d5d9ee988p+3,   -0x1.76eef72829852p-51 }, 0 }, // sqrt(71.80625) == 8.4738568550572062212
    {     0x1.35b3333333334p+6, {     0x1.19929e2b011adp+3,    0x1.e9443d42ff0bcp-53 }, 0 }, // sqrt(77.42500000000001) == 8.7991476859977757376
    {     0x1.4c2cccccccccdp+6, {     0x1.239c56cb9d208p+3,   -0x1.ddecbf67a8a6fp-54 }, 0 }, // sqrt(83.04375) == 9.11283435600581971
    {     0x1.62a6666666667p+6, {     0x1.2d50800968d10p+3,    0x1.15a8d037467bfp-51 }, 0 }, // sqrt(88.66250000000001) == 9.4160766776826965539
    {     0x1.7920000000000p+6, {     0x1.36b71e25f0655p+3,    0x1.8848a1ea991a8p-52 }, 0 }, // sqrt(94.28125) == 9.7098532429692262574
    {     0x1.8f9999999999ap+6, {     0x1.3fd7079e03fecp+3,    0x1.7a4c6b37a847fp-54 }, 0 }, // sqrt(99.9) == 9.9949987493746093857
    {     0x1.9000000000000p+6, {     0x1.4000000000000p+3,                 0x0.0p+0 }, 0 }, // sqrt(100.0) == 10.0
    {     0x1.387cccccccccdp+7, {     0x1.8ffdf3b4ee072p+3,   -0x1.daa0d812222dcp-52 }, 0 }, // sqrt(156.24375) == 12.499749997499950226
    {     0x1.a8f999999999ap+7, {     0x1.d27661e925086p+3,    0x1.f281f40187840p-51 }, 0 }, // sqrt(212.4875) == 14.576950984345114802
    {     0x1.0cbb333333333p+8, {     0x1.0649d3fc6480ep+4,    0x1.a55f707af5fdep-50 }, 0 }, // sqrt(268.73125) == 16.393024431141435612
    {     0x1.44f999999999ap+8, {     0x1.206ed999b9204p+4,    0x1.dc02c7410e741p-57 }, 0 }, // sqrt(324.975) == 18.027062988740013351
    {     0x1.7d38000000000p+8, {     0x1.3865adca6c6dap+4,    0x1.008dca5628776p-51 }, 0 }, // sqrt(381.21875) == 19.52482394286821732
    {     0x1.b576666666666p+8, {     0x1.4ea6509d08300p+4,   -0x1.6978219138095p-52 }, 0 }, // sqrt(437.4625) == 20.915604222685032851
    {     0x1.edb4ccccccccdp+8, {     0x1.63831413eb63dp+4,   -0x1.af32f3541e835p-51 }, 0 }, // sqrt(493.70625) == 22.21950156956721681
    {     0x1.12f999999999ap+9, {     0x1.7737592aed76ep+4,    0x1.90dccf964dde7p-50 }, 0 }, // sqrt(549.95) == 23.451012771306915253
    {     0x1.2f18cccccccccp+9, {     0x1.89efa0045f908p+4,   -0x1.53c55d6e887bdp-50 }, 0 }, // sqrt(606.1937499999999) == 24.621002213557430836
    {     0x1.4b38000000000p+9, {     0x1.9bce47901dea6p+4,    0x1.5f34e1cfeec7bp-51 }, 0 }, // sqrt(662.4375) == 25.737861216503596649
    {     0x1.6757333333333p+9, {     0x1.acee83a44bbaap+4,   -0x1.7a46b20fcc3b8p-52 }, 0 }, // sqrt(718.68125) == 26.808231012135059884
    {     0x1.8376666666666p+9, {     0x1.bd664bea33ad5p+4,   -0x1.f244706255ed7p-52 }, 0 }, // sqrt(774.925) == 27.837474741793659228
    {     0x1.9f95999999999p+9, {     0x1.cd47ab5a281eep+4,    0x1.db7ee0268b8d1p-50 }, 0 }, // sqrt(831.1687499999999) == 28.82999739854306563
    {     0x1.bbb4ccccccccdp+9, {     0x1.dca1aae45b81cp+4,   -0x1.1a7202410db36p-50 }, 0 }, // sqrt(887.4125) == 29.789469615956575851
    {     0x1.d7d4000000000p+9, {     0x1.eb80fa025b1bbp+4,    0x1.61ae86774ca18p-50 }, 0 }, // sqrt(943.65625) == 30.718988427355481524
    {     0x1.f3f3333333333p+9, {     0x1.f9f06a9cb9929p+4,    0x1.e231276dbb93dp-52 }, 0 }, // sqrt(999.9) == 31.621195423323261472
    {     0x1.f400000000000p+9, {     0x1.f9f6e4990f227p+4,    0x1.b42e5b5d1e808p-51 }, 0 }, // sqrt(1000.0) == 31.62277660168379332
    {    0x1.869f99999999ap+10, {     0x1.3c3a256cceeaap+5,    0x1.03c41dbdecb6bp-53 }, 0 }, // sqrt(1562.49375) == 39.528391695084181491
    {    0x1.099f99999999ap+11, {     0x1.70c7db89caae5p+5,   -0x1.094739efe7970p-49 }, 0 }, // sqrt(2124.9875) == 46.097586704728916664
    {    0x1.4fef666666666p+11, {     0x1.9eba35990100dp+5,   -0x1.d1da8a91594fep-50 }, 0 }, // sqrt(2687.48125) == 51.840922541945564977
    {    0x1.963f333333333p+11, {     0x1.c81183b4abf87p+5,    0x1.4c338e2cd919bp-49 }, 0 }, // sqrt(3249.975) == 57.008551990030407271
    {    0x1.dc8f000000000p+11, {     0x1.edf6274956fbbp+5,    0x1.80b98ff132eb9p-52 }, 0 }, // sqrt(3812.46875) == 61.745192120520606572
    {    0x1.116f666666666p+12, {     0x1.0892f17b2f90fp+6,    0x1.2c1a6b355d8a9p-49 }, 0 }, // sqrt(4374.9625) == 66.143499302652559586
    {    0x1.34974ccccccccp+12, {     0x1.191171b3b3abap+6,   -0x1.17f6ac41023f6p-49 }, 0 }, // sqrt(4937.456249999999) == 70.267035301057061692
    {    0x1.57bf333333333p+12, {     0x1.28a586fe3af07p+6,    0x1.d2529580a48bap-48 }, 0 }, // sqrt(5499.95) == 74.16164777025925695
    {    0x1.7ae7199999999p+12, {     0x1.377260837fa0fp+6,   -0x1.2d51758c10594p-49 }, 0 }, // sqrt(6062.443749999999) == 77.86169629541858019
    {    0x1.9e0f000000000p+12, {     0x1.45932b15dad73p+6,   -0x1.37accf83f74eap-48 }, 0 }, // sqrt(6624.9375) == 81.393719045145000672
    {    0x1.c136e66666666p+12, {     0x1.531d68991f540p+6,    0x1.df9bd2b54a09ap-49 }, 0 }, // sqrt(7187.43125) == 84.778719322716827864
    {    0x1.e45ecccccccccp+12, {     0x1.60227754af853p+6,    0x1.f92dac60f251fp-50 }, 0 }, // sqrt(7749.924999999999) == 88.033658335888775402
    {    0x1.03c359999999ap+13, {     0x1.6cb09b348b8dap+6,   -0x1.2f77c89092043p-48 }, 0 }, // sqrt(8312.41875) == 91.172467061059616407
    {    0x1.15574ccccccccp+13, {     0x1.78d3b75258b54p+6,    0x1.53d23ccfbd91ap-50 }, 0 }, // sqrt(8874.912499999999) == 94.206754004158314089
    {    0x1.26eb400000000p+13, {     0x1.8495d33cd761ap+6,    0x1.3907f80b02d28p-51 }, 0 }, // sqrt(9437.40625) == 97.1463136202295635
    {    0x1.387f333333333p+13, {     0x1.8fff7ced7beeep+6,   -0x1.51f36a6ee4da2p-48 }, 0 }, // sqrt(9999.9) == 99.999499998749991931
    {    0x1.3880000000000p+13, {     0x1.9000000000000p+6,                 0x0.0p+0 }, 0 }, // sqrt(10000.0) == 100.0
    {    0x1.e847f33333333p+13, {     0x1.f3fff972473a4p+6,   -0x1.dd13bfbf92dd2p-48 }, 0 }, // sqrt(15624.99375) == 124.99997499999749854
    {    0x1.4c07f33333333p+14, {     0x1.238c298ca3074p+7,    0x1.379a0d53eb847p-47 }, 0 }, // sqrt(21249.9875) == 145.77375449647991855
    {    0x1.a3ebeccccccccp+14, {     0x1.47df2f0f9203cp+7,    0x1.99e2be44c0140p-47 }, 0 }, // sqrt(26874.981249999997) == 163.93590592057615823
    {    0x1.fbcfe66666666p+14, {     0x1.688e13c02bfa2p+7,    0x1.047729775bb68p-48 }, 0 }, // sqrt(32499.975) == 180.27749443566159832
    {    0x1.29d9f00000000p+15, {     0x1.868327a633c73p+7,    0x1.003cbf8eac115p-47 }, 0 }, // sqrt(38124.96875) == 195.25616187460000362
    {    0x1.55cbeccccccccp+15, {     0x1.a2546ffff8d71p+7,   -0x1.c4bf5a5c90af1p-47 }, 0 }, // sqrt(43749.962499999994) == 209.16491699135396396
    {    0x1.81bde99999999p+15, {     0x1.bc68d6903111dp+7,    0x1.7eecb446d5846p-47 }, 0 }, // sqrt(49374.956249999996) == 222.20476198767657291
    {    0x1.adafe66666666p+15, {     0x1.d50a96c052265p+7,    0x1.b577b77b63b34p-50 }, 0 }, // sqrt(54999.95) == 234.52068139078906635
    {    0x1.d9a1e33333333p+15, {     0x1.ec715245e5878p+7,    0x1.0e5e6b7f09287p-47 }, 0 }, // sqrt(60624.94375) == 246.22133081843254172
    {    0x1.02c9f00000000p+16, {     0x1.016400775a06bp+8,    0x1.6e6df6559fc5dp-47 }, 0 }, // sqrt(66249.9375) == 257.39063211391357862
    {    0x1.18c2ee6666666p+16, {     0x1.0c18523123b96p+8,    0x1.e44209297858dp-47 }, 0 }, // sqrt(71874.93125) == 268.09500414964840254
    {    0x1.2ebbeccccccccp+16, {     0x1.1663596fa825bp+8,    0x1.25717dc21ade9p-47 }, 0 }, // sqrt(77499.92499999999) == 278.38808343749196543
    {    0x1.44b4eb3333333p+16, {     0x1.20505d521b7ecp+8,    0x1.9b238905552cap-46 }, 0 }, // sqrt(83124.91875) == 288.31392396136541274
    {    0x1.5aade99999999p+16, {     0x1.29e8c3a5ab716p+8,   -0x1.5b81ab46d592ap-46 }, 0 }, // sqrt(88749.91249999999) == 297.90923533855071018
    {    0x1.70a6e80000000p+16, {     0x1.33347a4396291p+8,    0x1.3ed500b17baf1p-47 }, 0 }, // sqrt(94374.90625) == 307.20499060073877647
    {    0x1.869fe66666666p+16, {     0x1.3c3a4482f3553p+8,   -0x1.157adf6e50cd2p-47 }, 0 }, // sqrt(99999.9) == 316.22760790291538709
};

void Test_sqrt_approx(void)
{
    for (int i = 0; i < _countof(s_sqrt_approx_tests); i++)
    {
        double x = s_sqrt_approx_tests[i].x;
        double expected = s_sqrt_approx_tests[i].expected.rounded;
        double z = sqrt(x);
        int64_t error = abs(ulp_error_precise(&s_sqrt_approx_tests[i].expected, z));
        ok(error <= s_sqrt_approx_tests[i].max_error,
            "sqrt(%.17e) = %.17e, expected %.17e, error %I64d ULPs, max %u ULPs\n",
            x, z, expected, error, s_sqrt_approx_tests[i].max_error);
    }
}

#if defined(HAS_SQRTF)

// These are expected to match exactly
static TESTENTRY_DBL s_sqrtf_exact_tests[] =
{
    { 0x00000000 /*  0.000000 */, 0x00000000 /*  0.000000 */ },
    { 0x80000000 /* -0.000000 */, 0x00000000 /*  0.000000 */ },
    { 0x7f800000 /*  1.#INF00 */, 0x00000000 /*  0.000000 */ },
    { 0x7f800001 /*  1.#SNAN0 */, 0x00000000 /*  0.000000 */ },
    { 0x7fBFffff /*  1.#SNAN0 */, 0x00000000 /*  0.000000 */ },
    { 0x7fC00000 /*  1.#QNAN0 */, 0x00000000 /*  0.000000 */ },
    { 0x7fC80001 /*  1.#QNAN0 */, 0x00000000 /*  0.000000 */ },
    { 0x7fFfffff /*  1.#QNAN0 */, 0x00000000 /*  0.000000 */ },
    { 0xff800000 /* -1.#INF00 */, 0x00000000 /*  0.000000 */ },
    { 0xff800001 /* -1.#SNAN0 */, 0x00000000 /*  0.000000 */ },
    { 0xffBfffff /* -1.#SNAN0 */, 0x00000000 /*  0.000000 */ },
    { 0xffC00000 /* -1.#IND00 */, 0x00000000 /*  0.000000 */ },
    { 0xfff80001 /* -1.#QNAN0 */, 0x00000000 /*  0.000000 */ },
    { 0xffffffff /* -1.#QNAN0 */, 0x00000000 /*  0.000000 */ },
};

void Test_sqrtf_exact(void)
{
    for (int i = 0; i < _countof(s_sqrtf_exact_tests); i++)
    {
        float x = u64_to_dbl(s_sqrtf_exact_tests[i].x);
        float z = sqrtf(x);
        ok_eq_flt_exact("sqrtf", s_sqrtf_exact_tests[i].x, z, s_sqrtf_exact_tests[i].result);
    }
}

#endif // defined(HAS_SQRTF)

#if defined(HAS_SQRTF)

static TESTENTRY_DBL_APPROX s_sqrtf_approx_tests[] =
{
//  {    x,                     {    y_rounded,               y_difference           } }
    {                 0x0.0p+0, {                 0x0.0p+0,                 0x0.0p+0 }, 0 }, // sqrtf(0.0) == 0.0
    {                 0x0.0p+0, {                 0x0.0p+0,                 0x0.0p+0 }, 0 }, // sqrtf(0.0) == 0.0
    {                 0x0.0p+0, {                 0x0.0p+0,                 0x0.0p+0 }, 0 }, // sqrtf(0.0) == 0.0
    {                 0x0.0p+0, {                 0x0.0p+0,                 0x0.0p+0 }, 0 }, // sqrtf(0.0) == 0.0
    {     0x1.fae1480000000p-5, {     0x1.fd6efe75c6202p-3,    0x1.1e5043abf1c4bp-57 }, 0 }, // sqrtf(0.06187500059604645) == 0.24874686047475342509
    {     0x1.fae1480000000p-4, {     0x1.6839539d08cddp-2,    0x1.4c9d3c3a49320p-57 }, 0 }, // sqrtf(0.1237500011920929) == 0.35178118368112427441
    {     0x1.7c28f60000000p-3, {     0x1.b92eb2a4a98d9p-2,   -0x1.10e33e4dd4ad9p-56 }, 0 }, // sqrtf(0.18562500178813934) == 0.43084220056551951381
    {     0x1.fae1480000000p-3, {     0x1.fd6efe75c6202p-2,    0x1.1e5043abf1c4bp-56 }, 0 }, // sqrtf(0.2475000023841858) == 0.49749372094950685017
    {     0x1.3ccccc0000000p-2, {     0x1.1cc8323a5b79dp-1,   -0x1.72275e898356ap-55 }, 0 }, // sqrtf(0.30937498807907104) == 0.55621487581605640199
    {     0x1.7c28f60000000p-2, {     0x1.37f68c2a1cf15p-1,   -0x1.61848bfb2207dp-56 }, 0 }, // sqrtf(0.3712500035762787) == 0.60930288328242685785
    {     0x1.bb851e0000000p-2, {     0x1.50f568aa183e1p-1,    0x1.fe4e005d3fa82p-56 }, 0 }, // sqrtf(0.43312498927116394) == 0.65812232090331349012
    {     0x1.fae1480000000p-2, {     0x1.6839539d08cddp-1,    0x1.4c9d3c3a49320p-56 }, 0 }, // sqrtf(0.4950000047683716) == 0.70356236736224854882
    {     0x1.1d1eb80000000p-1, {     0x1.7e133e8291354p-1,    0x1.087a2407ae16ap-56 }, 0 }, // sqrtf(0.5568749904632568) == 0.74624057144010659583
    {     0x1.3ccccc0000000p-1, {     0x1.92be1a5fca382p-1,   -0x1.631a493bbccc7p-56 }, 0 }, // sqrtf(0.6187499761581421) == 0.78660662097273379729
    {     0x1.5c7ae20000000p-1, {     0x1.a66666d61bed5p-1,    0x1.7cac2ff5cd276p-56 }, 0 }, // sqrtf(0.6806250214576721) == 0.82500001300464966668
    {     0x1.7c28f60000000p-1, {     0x1.b92eb2a4a98d9p-1,   -0x1.10e33e4dd4ad9p-55 }, 0 }, // sqrtf(0.7425000071525574) == 0.86168440113103902761
    {     0x1.9bd70a0000000p-1, {     0x1.cb327c630bf4ap-1,    0x1.55d1d3271c0b5p-57 }, 0 }, // sqrtf(0.8043749928474426) == 0.8968695517450922065
    {     0x1.bb851e0000000p-1, {     0x1.dc880de683da0p-1,   -0x1.40e1de9cfbc04p-60 }, 0 }, // sqrtf(0.8662499785423279) == 0.9307255119219242079
    {     0x1.db33340000000p-1, {     0x1.ed41c6a585ebap-1,    0x1.fcfec594bcd66p-59 }, 0 }, // sqrtf(0.9281250238418579) == 0.96339245577379207031
    {     0x1.fae1480000000p-1, {     0x1.fd6efe75c6202p-1,    0x1.1e5043abf1c4bp-55 }, 0 }, // sqrtf(0.9900000095367432) == 0.99498744189901370034
    {     0x1.0000000000000p+0, {     0x1.0000000000000p+0,                 0x0.0p+0 }, 0 }, // sqrtf(1.0) == 1.0
    {     0x1.8fd70a0000000p+0, {     0x1.3fef9d2e330d4p+0,   -0x1.1eabd2d8bb307p-54 }, 0 }, // sqrtf(1.5618749856948853) == 1.2497499692718080855
    {     0x1.0fd70a0000000p+1, {     0x1.75123676265d8p+0,    0x1.d023d9e8ee035p-54 }, 0 }, // sqrtf(2.1237499713897705) == 1.4573091543628519003
    {     0x1.57c2900000000p+1, {     0x1.a38796f7e1eb5p+0,    0x1.93ffa59539804p-56 }, 0 }, // sqrtf(2.6856250762939453) == 1.6387876849347951188
    {     0x1.9fae140000000p+1, {     0x1.cd5540dcfa1ecp+0,   -0x1.5e4523d9042f3p-54 }, 0 }, // sqrtf(3.247499942779541) == 1.8020821132178025743
    {     0x1.e7999a0000000p+1, {     0x1.f3a6ad44f58efp+0,    0x1.1807096400cbbp-55 }, 0 }, // sqrtf(3.809375047683716) == 1.9517620366437389593
    {     0x1.17c2900000000p+2, {     0x1.0b9dcf720c786p+1,   -0x1.a4c9b4cd24a2dp-54 }, 0 }, // sqrtf(4.371250152587891) == 2.0907534891966318622
    {     0x1.3bb8520000000p+2, {     0x1.1c4bd2b92c309p+1,    0x1.14c9b359a5372p-53 }, 0 }, // sqrtf(4.933125019073486) == 2.2210639385378995271
    {     0x1.5fae140000000p+2, {     0x1.2c0cd50f13504p+1,    0x1.78c3c888b155dp-55 }, 0 }, // sqrtf(5.494999885559082) == 2.3441416095362246761
    {     0x1.83a3d80000000p+2, {     0x1.3b0467fe9cc4cp+1,    0x1.03422bdd9c90ep-53 }, 0 }, // sqrtf(6.056875228881836) == 2.4610719674324511589
    {     0x1.a7999a0000000p+2, {     0x1.494e026c5c92fp+1,    0x1.fefc19dd7ce73p-54 }, 0 }, // sqrtf(6.618750095367432) == 2.5726931599721393205
    {     0x1.cb8f5c0000000p+2, {     0x1.56ff6343c74abp+1,   -0x1.c8cd59d14b629p-53 }, 0 }, // sqrtf(7.180624961853027) == 2.6796688157033561568
    {     0x1.ef851e0000000p+2, {     0x1.642a198e3d672p+1,   -0x1.3ed8fad23aa07p-53 }, 0 }, // sqrtf(7.742499828338623) == 2.7825347847490825298
    {     0x1.09bd700000000p+3, {     0x1.70dc9160a12b4p+1,    0x1.d78b8f99cfbf5p-54 }, 0 }, // sqrtf(8.304374694824219) == 2.8817311975311331508
    {     0x1.1bb8520000000p+3, {     0x1.7d22d00c1ecf0p+1,   -0x1.47a820b5acd68p-54 }, 0 }, // sqrtf(8.866250038146973) == 2.9776248988324524447
    {     0x1.2db3340000000p+3, {     0x1.8906f8c5d405fp+1,   -0x1.34f76751541e8p-53 }, 0 }, // sqrtf(9.428125381469727) == 3.0705252614935000014
    {     0x1.3fae140000000p+3, {     0x1.9491b080d13adp+1,   -0x1.c85a1b2991df4p-55 }, 0 }, // sqrtf(9.989999771118164) == 3.1606960896483173367
    {     0x1.4000000000000p+3, {     0x1.94c583ada5b53p+1,   -0x1.b7ed750df3ccap-53 }, 0 }, // sqrtf(10.0) == 3.162277660168379332
    {     0x1.f3cccc0000000p+3, {     0x1.f9dcfbc0b7cf8p+1,   -0x1.aa3fedfc0dbf5p-54 }, 0 }, // sqrtf(15.618749618530273) == 3.9520563784604937538
    {     0x1.53cccc0000000p+4, {     0x1.26f04a3652207p+2,    0x1.9e835513e2e17p-52 }, 0 }, // sqrtf(21.237499237060547) == 4.6084161310650481312
    {     0x1.adb3340000000p+4, {     0x1.4baad4b0a8dcbp+2,   -0x1.1f1bd64ba9010p-53 }, 0 }, // sqrtf(26.856250762939453) == 5.1823016858283591367
    {     0x1.03cccc0000000p+5, {     0x1.6cb73cc7c0b2cp+2,   -0x1.61b7846053190p-52 }, 0 }, // sqrtf(32.474998474121094) == 5.6986839247427202567
    {     0x1.30c0000000000p+5, {     0x1.8b0244b135674p+2,   -0x1.a1e9fcfa11cbep-52 }, 0 }, // sqrtf(38.09375) == 6.1720134478142543982
    {     0x1.5db3340000000p+5, {     0x1.a7238577e6783p+2,   -0x1.5a2940742fbdcp-56 }, 0 }, // sqrtf(43.712501525878906) == 6.611543051805599961
    {     0x1.8aa6660000000p+5, {     0x1.c18300d820ba6p+2,    0x1.b85f634e6d9edp-54 }, 0 }, // sqrtf(49.33124923706055) == 7.0236208067534900823
    {     0x1.b7999a0000000p+5, {     0x1.da6bc0fbfa913p+2,   -0x1.7b817c1bcf408p-53 }, 0 }, // sqrtf(54.95000076293945) == 7.4128267727594615041
    {     0x1.e48ccc0000000p+5, {     0x1.f215ff839eaeep+2,    0x1.ed9b50a6c240dp-52 }, 0 }, // sqrtf(60.568748474121094) == 7.7825926575994643759
    {     0x1.08c0000000000p+6, {     0x1.045696ff1d4efp+3,    0x1.6b4421c44d0c1p-53 }, 0 }, // sqrtf(66.1875) == 8.1355700476364899897
    {     0x1.1f399a0000000p+6, {     0x1.0f29d60a44d7cp+3,   -0x1.0daf0a36d6cbap-54 }, 0 }, // sqrtf(71.8062515258789) == 8.4738569450917040042
    {     0x1.35b3340000000p+6, {     0x1.19929e881aaf8p+3,   -0x1.bf4e2e5bc93aap-56 }, 0 }, // sqrtf(77.42500305175781) == 8.7991478594098992729
    {     0x1.4c2ccc0000000p+6, {     0x1.239c5671b7f51p+3,    0x1.d92be0b648394p-51 }, 0 }, // sqrtf(83.04374694824219) == 9.1128341885629734912
    {     0x1.62a6660000000p+6, {     0x1.2d507fdde8cc6p+3,   -0x1.72f89a215c391p-52 }, 0 }, // sqrtf(88.6624984741211) == 9.4160765966575003085
    {     0x1.7920000000000p+6, {     0x1.36b71e25f0655p+3,    0x1.8848a1ea991a8p-52 }, 0 }, // sqrtf(94.28125) == 9.7098532429692262574
    {     0x1.8f999a0000000p+6, {     0x1.3fd707c6ff008p+3,   -0x1.72a207c0774f0p-51 }, 0 }, // sqrtf(99.9000015258789) == 9.9949988257067297291
    {     0x1.9000000000000p+6, {     0x1.4000000000000p+3,                 0x0.0p+0 }, 0 }, // sqrtf(100.0) == 10.0
    {     0x1.387ccc0000000p+7, {     0x1.8ffdf331daecap+3,   -0x1.2335af6b43ba9p-54 }, 0 }, // sqrtf(156.24374389648438) == 12.499749753354439655
    {     0x1.a8f99a0000000p+7, {     0x1.d276622157cccp+3,    0x1.b1750cb17f972p-51 }, 0 }, // sqrtf(212.4875030517578) == 14.57695108902262224
    {     0x1.0cbb340000000p+8, {     0x1.0649d46056691p+4,   -0x1.f62db7bdc8e51p-51 }, 0 }, // sqrtf(268.73126220703125) == 16.393024803465382728
    {     0x1.44f99a0000000p+8, {     0x1.206ed9c72a7acp+4,    0x1.80bc6da889a93p-50 }, 0 }, // sqrtf(324.9750061035156) == 18.027063158027588854
    {     0x1.7d38000000000p+8, {     0x1.3865adca6c6dap+4,    0x1.008dca5628776p-51 }, 0 }, // sqrtf(381.21875) == 19.52482394286821732
    {     0x1.b576660000000p+8, {     0x1.4ea65075dd741p+4,    0x1.d27f6809e58b6p-50 }, 0 }, // sqrtf(437.4624938964844) == 20.915604076776849693
    {     0x1.edb4cc0000000p+8, {     0x1.638313ca2eb5fp+4,   -0x1.84ea7fb5b4e5fp-51 }, 0 }, // sqrtf(493.70623779296875) == 22.219501294875381383
    {     0x1.12f99a0000000p+9, {     0x1.77375970cad98p+4,    0x1.e9a1da965b400p-53 }, 0 }, // sqrtf(549.9500122070312) == 23.451013031573524116
    {     0x1.2f18cc0000000p+9, {     0x1.89ef9f7f489eap+4,    0x1.a61a670aacc94p-52 }, 0 }, // sqrtf(606.1937255859375) == 24.621001717759931548
    {     0x1.4b38000000000p+9, {     0x1.9bce47901dea6p+4,    0x1.5f34e1cfeec7bp-51 }, 0 }, // sqrtf(662.4375) == 25.737861216503596649
    {     0x1.6757340000000p+9, {     0x1.acee841e86e50p+4,   -0x1.46796d4f941fap-51 }, 0 }, // sqrtf(718.6812744140625) == 26.808231467481447796
    {     0x1.8376660000000p+9, {     0x1.bd664baf58903p+4,   -0x1.220941b22e829p-50 }, 0 }, // sqrtf(774.9249877929688) == 27.837474522538296344
    {     0x1.9f959a0000000p+9, {     0x1.cd47ab92fc85ep+4,    0x1.55b856506fe73p-50 }, 0 }, // sqrtf(831.1687622070312) == 28.82999761025018278
    {     0x1.bbb4cc0000000p+9, {     0x1.dca1aa765bdd5p+4,    0x1.4326c94312910p-51 }, 0 }, // sqrtf(887.4124755859375) == 29.789469206179849287
    {     0x1.d7d4000000000p+9, {     0x1.eb80fa025b1bbp+4,    0x1.61ae86774ca18p-50 }, 0 }, // sqrtf(943.65625) == 30.718988427355481524
    {     0x1.f3f3340000000p+9, {     0x1.f9f06b045a01bp+4,   -0x1.e0fcb3ce1b020p-51 }, 0 }, // sqrtf(999.9000244140625) == 31.621195809362784122
    {     0x1.f400000000000p+9, {     0x1.f9f6e4990f227p+4,    0x1.b42e5b5d1e808p-51 }, 0 }, // sqrtf(1000.0) == 31.62277660168379332
    {    0x1.869f9a0000000p+10, {     0x1.3c3a259641c7ep+5,   -0x1.5f0645382adb8p-50 }, 0 }, // sqrtf(1562.4937744140625) == 39.52839200390097452
    {    0x1.099f9a0000000p+11, {     0x1.70c7dbd0e02e1p+5,    0x1.1eb6427b59c8cp-54 }, 0 }, // sqrtf(2124.987548828125) == 46.097587234345844882
    {    0x1.4fef660000000p+11, {     0x1.9eba3559cb901p+5,   -0x1.25d3daded48e5p-49 }, 0 }, // sqrtf(2687.481201171875) == 51.840922071003665743
    {    0x1.963f340000000p+11, {     0x1.c8118427a1446p+5,    0x1.db9798a213570p-49 }, 0 }, // sqrtf(3249.97509765625) == 57.008552846535667871
    {    0x1.dc8f000000000p+11, {     0x1.edf6274956fbbp+5,    0x1.80b98ff132eb9p-52 }, 0 }, // sqrtf(3812.46875) == 61.745192120520606572
    {    0x1.116f660000000p+12, {     0x1.0892f149a520fp+6,   -0x1.9c85d35872f81p-49 }, 0 }, // sqrtf(4374.96240234375) == 66.143498564437533085
    {    0x1.34974c0000000p+12, {     0x1.191171566f4d6p+6,   -0x1.e0002b55b176ap-48 }, 0 }, // sqrtf(4937.4560546875) == 70.267033911269515034
    {    0x1.57bf340000000p+12, {     0x1.28a58756996f7p+6,    0x1.c02bf9192be1fp-48 }, 0 }, // sqrtf(5499.9501953125) == 74.161649087061838339
    {    0x1.7ae71a0000000p+12, {     0x1.377260ad955b8p+6,    0x1.8eb9948bf93fep-50 }, 0 }, // sqrtf(6062.44384765625) == 77.861696922532134086
    {    0x1.9e0f000000000p+12, {     0x1.45932b15dad73p+6,   -0x1.37accf83f74eap-48 }, 0 }, // sqrtf(6624.9375) == 81.393719045145000672
    {    0x1.c136e60000000p+12, {     0x1.531d6872789e6p+6,    0x1.c428ddccb91f2p-50 }, 0 }, // sqrtf(7187.43115234375) == 84.778718746768932283
    {    0x1.e45ecc0000000p+12, {     0x1.6022770a3dca9p+6,    0x1.93ae11caff170p-50 }, 0 }, // sqrtf(7749.9248046875) == 88.03365722658294741
    {    0x1.03c35a0000000p+13, {     0x1.6cb09b7c6d2dbp+6,    0x1.0d717e9aeba09p-48 }, 0 }, // sqrtf(8312.4189453125) == 91.172468132175186826
    {    0x1.15574c0000000p+13, {     0x1.78d3b6c736d87p+6,   -0x1.4190574ae135ep-48 }, 0 }, // sqrtf(8874.912109375) == 94.206751930925842742
    {    0x1.26eb400000000p+13, {     0x1.8495d33cd761ap+6,    0x1.3907f80b02d28p-51 }, 0 }, // sqrtf(9437.40625) == 97.1463136202295635
    {    0x1.387f340000000p+13, {     0x1.8fff7d708e885p+6,    0x1.0584b1476a1a3p-49 }, 0 }, // sqrtf(9999.900390625) == 99.999501951884740374
    {    0x1.3880000000000p+13, {     0x1.9000000000000p+6,                 0x0.0p+0 }, 0 }, // sqrtf(10000.0) == 100.0
    {    0x1.e847f40000000p+13, {     0x1.f3fff9db22c74p+6,   -0x1.21a3dcb68ee35p-48 }, 0 }, // sqrtf(15624.994140625) == 124.99997656249780273
    {    0x1.4c07f40000000p+14, {     0x1.238c29e68d2f8p+7,   -0x1.f46a43a6f6b48p-47 }, 0 }, // sqrtf(21249.98828125) == 145.77375717614607741
    {    0x1.a3ebec0000000p+14, {     0x1.47df2ebf9dfefp+7,    0x1.a9c006def08a0p-48 }, 0 }, // sqrtf(26874.98046875) == 163.93590353778515714
    {    0x1.fbcfe60000000p+14, {     0x1.688e139bd1a60p+7,    0x1.0df7b42ba9d85p-47 }, 0 }, // sqrtf(32499.974609375) == 180.27749335226236166
    {    0x1.29d9f00000000p+15, {     0x1.868327a633c73p+7,    0x1.003cbf8eac115p-47 }, 0 }, // sqrtf(38124.96875) == 195.25616187460000362
    {    0x1.55cbec0000000p+15, {     0x1.a2546f82a4a70p+7,    0x1.5e94d15eb358ap-48 }, 0 }, // sqrtf(43749.9609375) == 209.1649132562629396
    {    0x1.81bdea0000000p+15, {     0x1.bc68d6cb2dc02p+7,    0x1.610ee9ef325cdp-47 }, 0 }, // sqrtf(49374.95703125) == 222.20476374562719982
    {    0x1.adafe60000000p+15, {     0x1.d50a96886e7c4p+7,   -0x1.f6b384b7b3b7dp-48 }, 0 }, // sqrtf(54999.94921875) == 234.52067972515771301
    {    0x1.d9a1e40000000p+15, {     0x1.ec7152b05d087p+7,   -0x1.4fea15b797b91p-49 }, 0 }, // sqrtf(60624.9453125) == 246.22133399139076226
    {    0x1.02c9f00000000p+16, {     0x1.016400775a06bp+8,    0x1.6e6df6559fc5dp-47 }, 0 }, // sqrtf(66249.9375) == 257.39063211391357862
    {    0x1.18c2ee0000000p+16, {     0x1.0c1852003fd9cp+8,   -0x1.6681b9e69364cp-46 }, 0 }, // sqrtf(71874.9296875) == 268.09500123556947812
    {    0x1.2ebbec0000000p+16, {     0x1.166359117deb8p+8,   -0x1.05b3c46740258p-46 }, 0 }, // sqrtf(77499.921875) == 278.38807782482352561
    {    0x1.44b4ec0000000p+16, {     0x1.20505dad07d00p+8,   -0x1.9f9f81827a66fp-46 }, 0 }, // sqrtf(83124.921875) == 288.31392938080532497
    {    0x1.5aadea0000000p+16, {     0x1.29e8c3d1aac00p+8,   -0x1.eac0d44e404fep-46 }, 0 }, // sqrtf(88749.9140625) == 297.90923796099375072
    {    0x1.70a6e80000000p+16, {     0x1.33347a4396291p+8,    0x1.3ed500b17baf1p-47 }, 0 }, // sqrtf(94374.90625) == 307.20499060073877647
    {    0x1.869fe60000000p+16, {     0x1.3c3a4459807c0p+8,   -0x1.8326441e0a1e5p-48 }, 0 }, // sqrtf(99999.8984375) == 316.22760543238472937
};

#endif // defined(HAS_SQRTF) || defined(HAS_LIBM_SSE2)

#if defined(HAS_SQRTF)

void Test_sqrtf_approx(void)
{
    for (int i = 0; i < _countof(s_sqrtf_approx_tests); i++)
    {
        float x = s_sqrtf_approx_tests[i].x;
        float expected = s_sqrtf_approx_tests[i].expected.rounded;
        float z = sqrtf(x);
        int64_t error = abs(ulp_error_flt(expected, z));
        ok(error <= s_sqrt_approx_tests[i].max_error,
            "sqrt(%.6e) = %.7e, expected %.7e, error %I64d ULPs, max %u ULPs\n",
            x, z, expected, error, s_sqrt_approx_tests[i].max_error);
    }
}

#endif // defined(HAS_SQRTF)

#if defined(HAS_LIBM_SSE2)

__ATTRIBUTE_SSE2__ __m128d _libm_sse2_sqrt_precise(__m128d Xmm0);

__ATTRIBUTE_SSE2__
void Test_libm_sse2_sqrt(void)
{
    int i;
    for (i = 0; i < _countof(s_sqrt_approx_tests); i++)
    {
        double x = s_sqrt_approx_tests[i].x;
        double expected = s_sqrt_approx_tests[i].expected.rounded;
        __m128d xmm0 = _mm_set_sd(x);
        __m128d xmm1 = _libm_sse2_sqrt_precise(xmm0);
        double z = _mm_cvtsd_f64(xmm1);
        int64_t error = ulp_error_precise(&s_sqrt_approx_tests[i].expected, z);
        ok(error <= s_sqrt_approx_tests[i].max_error,
            "_libm_sse2_sqrt_precise(%.17e) = %.17e, expected %.17e, error %I64d ULPs, max %u ULPs\n",
            x, z, expected, error, s_sqrt_approx_tests[i].max_error);
    }
}

#endif // defined(HAS_LIBM_SSE2)

START_TEST(sqrt)
{
    Test_sqrt_exact();
    Test_sqrt_approx();
#if defined(HAS_SQRTF)
    Test_sqrtf_exact();
    Test_sqrtf_approx();
#endif
#if defined(HAS_LIBM_SSE2)
    Test_libm_sse2_sqrt();
#endif
}
