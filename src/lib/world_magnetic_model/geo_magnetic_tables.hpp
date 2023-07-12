/****************************************************************************
 *
 *   Copyright (c) 2020-2022 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// *INDENT-OFF*
// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2023.526,
static constexpr const int16_t declination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ {  25962, 24217, 22472, 20726, 18981, 17236, 15490, 13745, 12000, 10254,  8509,  6764,  5018,  3273,  1528,  -217, -1963, -3708, -5453, -7198, -8944,-10689,-12434,-14180,-15925,-17670,-19416,-21161,-22907,-24652,-26397,-28143,-29888, 31198, 29453, 27708, 25962, },
	/* LAT: -80 */ {  22526, 20398, 18460, 16688, 15048, 13511, 12048, 10637,  9262,  7913,  6581,  5263,  3954,  2649,  1341,    21, -1321, -2694, -4106, -5559, -7056, -8594,-10173,-11794,-13460,-15179,-16966,-18840,-20824,-22944,-25220,-27655,-30223, 29971, 27356, 24853, 22526, },
	/* LAT: -70 */ {  14984, 13584, 12455, 11491, 10620,  9786,  8943,  8054,  7100,  6081,  5011,  3918,  2834,  1781,   760,  -250, -1288, -2396, -3601, -4905, -6290, -7723, -9173,-10617,-12045,-13462,-14892,-16381,-18009,-19931,-22465,-26282, 30630, 24109, 19620, 16854, 14984, },
	/* LAT: -60 */ {   8444,  8194,  7908,  7630,  7372,  7115,  6804,  6368,  5751,  4929,  3927,  2815,  1697,   674,  -202,  -955, -1683, -2510, -3521, -4727, -6065, -7440, -8764, -9975,-11038,-11936,-12650,-13144,-13315,-12867,-10757, -3427,  5000,  7712,  8467,  8585,  8444, },
	/* LAT: -50 */ {   5503,  5538,  5479,  5386,  5309,  5269,  5231,  5102,  4755,  4088,  3074,  1800,   461,  -711, -1571, -2125, -2515, -2958, -3655, -4685, -5943, -7228, -8371, -9269, -9862,-10093, -9890, -9124, -7609, -5241, -2332,   417,  2527,  3953,  4827,  5301,  5503, },
	/* LAT: -40 */ {   3968,  4060,  4065,  4017,  3954,  3917,  3920,  3907,  3731,  3192,  2163,   716,  -846, -2150, -2999, -3437, -3609, -3663, -3842, -4436, -5437, -6524, -7407, -7937, -8032, -7641, -6739, -5350, -3642, -1946,  -490,   729,  1775,  2644,  3303,  3736,  3968, },
	/* LAT: -30 */ {   2995,  3080,  3108,  3089,  3027,  2946,  2884,  2849,  2721,  2238,  1193,  -334, -1940, -3182, -3907, -4239, -4305, -4080, -3643, -3447, -3845, -4608, -5301, -5638, -5497, -4897, -3930, -2725, -1527,  -592,    80,   679,  1306,  1914,  2428,  2794,  2995, },
	/* LAT: -20 */ {   2352,  2397,  2411,  2408,  2362,  2265,  2154,  2077,  1931,  1430,   363, -1134, -2610, -3658, -4173, -4275, -4058, -3485, -2618, -1837, -1590, -1965, -2616, -3075, -3099, -2730, -2090, -1277,  -511,   -31,   225,   525,   969,  1455,  1883,  2196,  2352, },
	/* LAT: -10 */ {   1959,  1952,  1926,  1918,  1886,  1798,  1684,  1590,  1405,   850,  -220, -1603, -2871, -3685, -3933, -3689, -3103, -2317, -1472,  -725,  -275,  -324,  -803, -1306, -1510, -1414, -1098,  -602,  -112,   121,   162,   319,   695,  1141,  1542,  1835,  1959, },
	/* LAT:   0 */ {   1745,  1711,  1651,  1637,  1622,  1549,  1439,  1321,  1066,   443,  -602, -1830, -2876, -3447, -3428, -2914, -2142, -1362,  -714,  -182,   225,   327,    38,  -379,  -629,  -682,  -583,  -324,   -40,    42,   -26,    59,   405,   857,  1285,  1612,  1745, },
	/* LAT:  10 */ {   1606,  1614,  1568,  1580,  1603,  1549,  1422,  1231,   854,   136,  -886, -1959, -2777, -3102, -2883, -2268, -1491,  -783,  -272,   105,   428,   571,   402,    79,  -152,  -260,  -286,  -210,  -110,  -158,  -304,  -280,    26,   490,   979,  1392,  1606, },
	/* LAT:  20 */ {   1417,  1565,  1623,  1713,  1797,  1773,  1613,  1307,   762,   -93, -1133, -2079, -2666, -2763, -2426, -1819, -1108,  -462,    -6,   300,   558,   700,   604,   360,   162,    43,   -54,  -125,  -210,  -404,  -646,  -705,  -467,   -13,   534,  1057,  1417, },
	/* LAT:  30 */ {   1107,  1473,  1732,  1956,  2114,  2123,  1932,  1508,   780,  -246, -1358, -2226, -2631, -2561, -2157, -1575,  -920,  -304,   155,   457,   687,   830,   806,   656,   508,   381,   218,    -2,  -291,  -669, -1040, -1199, -1035,  -604,   -25,   586,  1107, },
	/* LAT:  40 */ {    740,  1325,  1820,  2213,  2463,  2507,  2291,  1757,   848,  -374, -1602, -2458, -2771, -2614, -2166, -1573,  -919,  -291,   216,   578,   846,  1041,  1131,  1118,  1042,   891,   615,   194,  -353,  -963, -1483, -1724, -1604, -1185,  -587,    83,   740, },
	/* LAT:  50 */ {    438,  1183,  1865,  2426,  2796,  2905,  2678,  2027,   892,  -593, -2002, -2906, -3195, -3002, -2512, -1866, -1156,  -459,   154,   658,  1073,  1425,  1701,  1869,  1885,  1692,  1237,   516,  -388, -1292, -1966, -2246, -2118, -1677, -1046,  -321,   438, },
	/* LAT:  60 */ {    225,  1074,  1881,  2581,  3091,  3311,  3105,  2306,   810, -1125, -2824, -3798, -4050, -3793, -3223, -2479, -1655,  -817,   -11,   738,  1428,  2056,  2595,  2986,  3140,  2943,  2289,  1155,  -270, -1588, -2447, -2749, -2582, -2092, -1407,  -616,   225, },
	/* LAT:  70 */ {    -41,   890,  1786,  2588,  3208,  3513,  3280,  2185,    14, -2639, -4577, -5415, -5439, -4969, -4208, -3280, -2261, -1199,  -127,   930,  1953,  2917,  3782,  4485,  4925,  4945,  4316,  2814,   596, -1515, -2803, -3241, -3083, -2558, -1818,  -959,   -41, },
	/* LAT:  80 */ {   -850,    69,   919,  1610,  2002,  1849,   748, -1652, -4671, -6775, -7583, -7509, -6922, -6034, -4963, -3778, -2523, -1225,    95,  1418,  2730,  4011,  5238,  6377,  7375,  8137,  8479,  8019,  6019,  2084, -1598, -3300, -3642, -3300, -2619, -1770,  -850, },
	/* LAT:  90 */ { -29465,-27719,-25974,-24228,-22483,-20738,-18992,-17247,-15502,-13757,-12011,-10266, -8521, -6776, -5031, -3286, -1540,   205,  1950,  3695,  5440,  7186,  8931, 10676, 12421, 14167, 15912, 17658, 19403, 21149, 22894, 24640, 26385, 28131, 29876,-31210,-29465, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2023.526,
static constexpr const int16_t inclination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ { -12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565,-12565, },
	/* LAT: -80 */ { -13648,-13515,-13354,-13174,-12980,-12778,-12575,-12375,-12184,-12009,-11852,-11718,-11608,-11522,-11458,-11417,-11397,-11399,-11426,-11480,-11564,-11679,-11824,-11998,-12196,-12414,-12643,-12876,-13104,-13316,-13503,-13652,-13755,-13806,-13802,-13747,-13648, },
	/* LAT: -70 */ { -14096,-13777,-13458,-13135,-12804,-12460,-12106,-11749,-11407,-11099,-10848,-10665,-10554,-10502,-10487,-10489,-10495,-10502,-10525,-10580,-10689,-10864,-11112,-11428,-11802,-12221,-12670,-13134,-13600,-14052,-14469,-14812,-14998,-14941,-14710,-14412,-14096, },
	/* LAT: -60 */ { -13512,-13158,-12820,-12487,-12143,-11771,-11357,-10903,-10436,-10008, -9680, -9508, -9507, -9645, -9849,-10038,-10158,-10197,-10180,-10164,-10211,-10373,-10666,-11078,-11579,-12137,-12724,-13321,-13909,-14471,-14968,-15256,-15075,-14689,-14281,-13887,-13512, },
	/* LAT: -50 */ { -12493,-12150,-11818,-11496,-11172,-10826,-10427, -9957, -9428, -8909, -8523, -8404, -8611, -9075, -9637,-10144,-10496,-10649,-10610,-10453,-10311,-10321,-10549,-10972,-11518,-12112,-12699,-13236,-13681,-13977,-14084,-14010,-13807,-13522,-13193,-12844,-12493, },
	/* LAT: -40 */ { -11239,-10889,-10540,-10194, -9855, -9517, -9157, -8733, -8213, -7651, -7231, -7199, -7670, -8499, -9419,-10243,-10894,-11318,-11444,-11265,-10917,-10650,-10653,-10944,-11411,-11916,-12359,-12677,-12833,-12837,-12748,-12612,-12434,-12203,-11916,-11587,-11239, },
	/* LAT: -30 */ {  -9602, -9220, -8838, -8447, -8055, -7680, -7326, -6937, -6426, -5816, -5372, -5472, -6258, -7469, -8718, -9807,-10713,-11412,-11796,-11769,-11386,-10878,-10553,-10563,-10821,-11142,-11395,-11503,-11437,-11261,-11090,-10959,-10816,-10611,-10330, -9983, -9602, },
	/* LAT: -20 */ {  -7373, -6926, -6504, -6074, -5630, -5202, -4814, -4405, -3842, -3159, -2722, -3006, -4140, -5764, -7389, -8747, -9799,-10561,-10984,-11002,-10625,-10005, -9451, -9216, -9271, -9434, -9572, -9584, -9409, -9138, -8949, -8869, -8772, -8568, -8251, -7837, -7373, },
	/* LAT: -10 */ {  -4418, -3873, -3413, -2973, -2515, -2066, -1656, -1208,  -588,   110,   458,     5, -1352, -3284, -5253, -6843, -7919, -8535, -8786, -8710, -8287, -7593, -6931, -6593, -6558, -6651, -6766, -6786, -6596, -6302, -6154, -6175, -6146, -5935, -5551, -5020, -4418, },
	/* LAT:   0 */ {   -911,  -276,   196,   602,  1021,  1438,  1823,  2258,  2834,  3403,  3591,  3072,  1751,  -176, -2215, -3843, -4827, -5236, -5282, -5102, -4648, -3922, -3217, -2853, -2794, -2862, -2984, -3055, -2925, -2692, -2646, -2805, -2882, -2703, -2278, -1643,  -911, },
	/* LAT:  10 */ {   2557,  3193,  3634,  3978,  4334,  4700,  5048,  5427,  5869,  6231,  6255,  5749,  4648,  3070,  1382,    25,  -758,  -987,  -884,  -641,  -220,   427,  1060,  1393,  1456,  1416,  1318,  1227,  1269,  1369,  1284,  1003,   796,   862,  1215,  1823,  2557, },
	/* LAT:  20 */ {   5413,  5948,  6332,  6630,  6944,  7286,  7626,  7967,  8293,  8486,  8389,  7916,  7069,  5966,  4843,  3946,  3433,  3328,  3487,  3735,  4072,  4543,  5004,  5257,  5316,  5303,  5257,  5199,  5185,  5163,  4982,  4639,  4331,  4236,  4409,  4836,  5413, },
	/* LAT:  30 */ {   7568,  7944,  8263,  8547,  8856,  9203,  9557,  9894, 10165, 10273, 10122,  9694,  9061,  8348,  7691,  7186,  6903,  6871,  7019,  7234,  7485,  7787,  8077,  8250,  8309,  8325,  8330,  8320,  8295,  8209,  7982,  7623,  7262,  7039,  7024,  7220,  7568, },
	/* LAT:  40 */ {   9266,  9487,  9744, 10029, 10355, 10715, 11081, 11417, 11665, 11743, 11589, 11227, 10753, 10281,  9888,  9609,  9465,  9466,  9581,  9745,  9923, 10110, 10282, 10407, 10486, 10549, 10606, 10640, 10621, 10507, 10262,  9908,  9538,  9252,  9109,  9122,  9266, },
	/* LAT:  50 */ {  10802, 10923, 11123, 11392, 11714, 12067, 12420, 12734, 12953, 13010, 12869, 12571, 12208, 11864, 11591, 11407, 11318, 11318, 11387, 11492, 11608, 11726, 11843, 11959, 12078, 12202, 12317, 12389, 12378, 12249, 12001, 11671, 11331, 11046, 10856, 10776, 10802, },
	/* LAT:  60 */ {  12320, 12391, 12540, 12756, 13025, 13323, 13624, 13889, 14064, 14091, 13956, 13708, 13421, 13151, 12932, 12777, 12689, 12659, 12677, 12726, 12796, 12882, 12989, 13122, 13283, 13459, 13624, 13732, 13735, 13612, 13386, 13107, 12828, 12592, 12422, 12330, 12320, },
	/* LAT:  70 */ {  13757, 13798, 13891, 14031, 14208, 14410, 14617, 14797, 14902, 14885, 14751, 14552, 14336, 14133, 13961, 13827, 13733, 13680, 13661, 13675, 13718, 13791, 13896, 14033, 14201, 14388, 14572, 14712, 14756, 14681, 14519, 14320, 14126, 13962, 13841, 13772, 13757, },
	/* LAT:  80 */ {  14993, 15004, 15040, 15098, 15172, 15256, 15333, 15379, 15365, 15290, 15181, 15060, 14938, 14825, 14726, 14644, 14583, 14542, 14524, 14528, 14555, 14605, 14677, 14770, 14882, 15010, 15145, 15278, 15385, 15428, 15387, 15298, 15201, 15115, 15050, 15008, 14993, },
	/* LAT:  90 */ {  15399, 15399, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15398, 15399, 15399, 15399, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2023.526,
static constexpr const int16_t strength_table[19][37] {
	//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
	/* LAT: -90 */ {  5446, 5446, 5446, 5446, 5446, 5446, 5446, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5445, 5446, 5446, 5446, 5446, 5446, 5446, 5446, 5446, 5446, 5446, 5446, },
	/* LAT: -80 */ {  6052, 5988, 5909, 5816, 5713, 5601, 5483, 5361, 5238, 5119, 5005, 4899, 4806, 4726, 4664, 4619, 4595, 4593, 4615, 4662, 4733, 4827, 4942, 5074, 5218, 5368, 5518, 5662, 5792, 5906, 5998, 6067, 6111, 6130, 6125, 6099, 6052, },
	/* LAT: -70 */ {  6297, 6163, 6011, 5846, 5666, 5474, 5269, 5054, 4835, 4620, 4418, 4236, 4078, 3948, 3844, 3768, 3721, 3709, 3738, 3815, 3944, 4125, 4355, 4623, 4919, 5227, 5530, 5814, 6064, 6267, 6418, 6513, 6554, 6545, 6495, 6410, 6297, },
	/* LAT: -60 */ {  6182, 5989, 5786, 5577, 5357, 5122, 4865, 4587, 4295, 4006, 3739, 3513, 3334, 3200, 3101, 3028, 2978, 2958, 2984, 3076, 3246, 3499, 3828, 4215, 4638, 5073, 5494, 5878, 6202, 6450, 6612, 6690, 6691, 6627, 6512, 6360, 6182, },
	/* LAT: -50 */ {  5840, 5609, 5376, 5145, 4911, 4666, 4395, 4092, 3763, 3432, 3131, 2892, 2731, 2641, 2593, 2558, 2523, 2496, 2502, 2575, 2751, 3044, 3443, 3916, 4424, 4930, 5405, 5823, 6161, 6401, 6539, 6578, 6535, 6424, 6261, 6061, 5840, },
	/* LAT: -40 */ {  5391, 5144, 4898, 4657, 4422, 4185, 3930, 3646, 3332, 3006, 2708, 2486, 2371, 2346, 2365, 2385, 2388, 2375, 2362, 2391, 2525, 2805, 3227, 3743, 4291, 4814, 5279, 5666, 5957, 6144, 6232, 6234, 6163, 6031, 5849, 5630, 5391, },
	/* LAT: -30 */ {  4877, 4635, 4395, 4160, 3933, 3714, 3495, 3263, 3007, 2732, 2474, 2293, 2225, 2251, 2318, 2388, 2453, 2501, 2521, 2533, 2603, 2807, 3174, 3666, 4198, 4694, 5110, 5424, 5626, 5725, 5751, 5724, 5644, 5511, 5331, 5114, 4877, },
	/* LAT: -20 */ {  4320, 4106, 3897, 3691, 3495, 3312, 3143, 2979, 2801, 2602, 2412, 2279, 2241, 2286, 2376, 2487, 2614, 2740, 2826, 2860, 2886, 2986, 3231, 3619, 4071, 4497, 4843, 5075, 5179, 5186, 5155, 5108, 5026, 4898, 4731, 4534, 4320, },
	/* LAT: -10 */ {  3790, 3628, 3474, 3327, 3191, 3071, 2967, 2875, 2777, 2661, 2539, 2441, 2397, 2424, 2512, 2642, 2798, 2955, 3076, 3136, 3150, 3179, 3306, 3562, 3890, 4212, 4475, 4635, 4668, 4615, 4548, 4485, 4397, 4272, 4123, 3958, 3790, },
	/* LAT:   0 */ {  3412, 3318, 3234, 3160, 3105, 3066, 3040, 3020, 2994, 2945, 2866, 2772, 2693, 2665, 2709, 2813, 2946, 3081, 3194, 3268, 3298, 3321, 3398, 3558, 3769, 3983, 4162, 4266, 4271, 4202, 4114, 4022, 3911, 3779, 3645, 3520, 3412, },
	/* LAT:  10 */ {  3282, 3251, 3230, 3225, 3249, 3296, 3351, 3403, 3436, 3426, 3357, 3243, 3117, 3025, 3001, 3044, 3126, 3224, 3324, 3409, 3472, 3535, 3624, 3744, 3881, 4020, 4139, 4209, 4210, 4147, 4037, 3893, 3732, 3572, 3436, 3339, 3282, },
	/* LAT:  20 */ {  3399, 3401, 3426, 3479, 3570, 3691, 3818, 3934, 4014, 4026, 3952, 3811, 3645, 3508, 3434, 3424, 3460, 3534, 3631, 3728, 3819, 3918, 4030, 4142, 4252, 4365, 4467, 4533, 4542, 4483, 4345, 4142, 3914, 3704, 3540, 3439, 3399, },
	/* LAT:  30 */ {  3722, 3727, 3780, 3879, 4020, 4191, 4365, 4521, 4628, 4654, 4581, 4427, 4239, 4077, 3974, 3930, 3935, 3987, 4075, 4174, 4272, 4378, 4495, 4613, 4733, 4861, 4983, 5069, 5094, 5035, 4877, 4637, 4362, 4107, 3907, 3778, 3722, },
	/* LAT:  40 */ {  4222, 4218, 4281, 4403, 4569, 4755, 4937, 5094, 5198, 5224, 5156, 5009, 4824, 4652, 4525, 4451, 4427, 4451, 4512, 4592, 4680, 4778, 4893, 5026, 5178, 5340, 5492, 5602, 5639, 5583, 5426, 5188, 4914, 4655, 4444, 4298, 4222, },
	/* LAT:  50 */ {  4832, 4822, 4875, 4983, 5128, 5287, 5436, 5558, 5632, 5642, 5579, 5454, 5292, 5130, 4994, 4898, 4844, 4834, 4860, 4911, 4981, 5072, 5192, 5342, 5518, 5702, 5868, 5985, 6028, 5982, 5850, 5654, 5431, 5216, 5036, 4905, 4832, },
	/* LAT:  60 */ {  5393, 5377, 5403, 5463, 5548, 5642, 5729, 5796, 5830, 5823, 5770, 5677, 5558, 5430, 5312, 5217, 5151, 5118, 5117, 5145, 5202, 5289, 5408, 5555, 5722, 5890, 6036, 6139, 6182, 6158, 6076, 5950, 5805, 5663, 5541, 5448, 5393, },
	/* LAT:  70 */ {  5726, 5704, 5699, 5710, 5731, 5757, 5781, 5796, 5797, 5779, 5741, 5685, 5616, 5540, 5467, 5404, 5356, 5329, 5325, 5345, 5390, 5460, 5552, 5661, 5778, 5892, 5990, 6062, 6101, 6104, 6075, 6022, 5955, 5885, 5819, 5765, 5726, },
	/* LAT:  80 */ {  5790, 5772, 5757, 5744, 5734, 5724, 5714, 5703, 5688, 5671, 5649, 5624, 5598, 5572, 5547, 5527, 5514, 5509, 5514, 5530, 5556, 5591, 5634, 5682, 5731, 5779, 5822, 5856, 5880, 5893, 5895, 5888, 5873, 5854, 5832, 5810, 5790, },
	/* LAT:  90 */ {  5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, 5684, },
};
