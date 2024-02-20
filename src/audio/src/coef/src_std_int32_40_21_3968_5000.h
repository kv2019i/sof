/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright(c) 2019 Intel Corporation. All rights reserved.
 *
 * Author: Seppo Ingalsuo <seppo.ingalsuo@linux.intel.com>
 */

#include <stdint.h>

static const int32_t src_int32_40_21_3968_5000_fir[1600] = {
	-168855,
	272170,
	-146895,
	-471617,
	1853523,
	-4156572,
	7280198,
	-10729938,
	13540996,
	-14306929,
	11340829,
	-2964323,
	-12118589,
	34440019,
	-63475661,
	97536602,
	-133922773,
	169414536,
	-201393135,
	232583555,
	1697488506,
	187762244,
	-183236549,
	161445844,
	-131468995,
	98255158,
	-65859411,
	37444768,
	-15045790,
	-525135,
	9564778,
	-13194094,
	12980964,
	-10562246,
	7342657,
	-4316715,
	2022565,
	-603930,
	-63582,
	230188,
	-184607,
	314338,
	-232044,
	-333409,
	1671211,
	-3972240,
	7180141,
	-10846980,
	14042542,
	-15365248,
	13085584,
	-5421563,
	-9093380,
	31226546,
	-60747741,
	96327864,
	-135756020,
	176701544,
	-219044777,
	278604306,
	1694726677,
	144240568,
	-164670491,
	152845919,
	-128416081,
	98486878,
	-67891952,
	40228866,
	-17861985,
	1884331,
	7766549,
	-12032986,
	12366101,
	-10345571,
	7367885,
	-4452351,
	2177780,
	-729820,
	17514,
	188618,
	-200141,
	356457,
	-318627,
	-189875,
	1476266,
	-3764169,
	7042303,
	-10911933,
	14482185,
	-16362985,
	14789953,
	-7884940,
	-5983811,
	27817456,
	-57684468,
	94627933,
	-136949984,
	183258659,
	-236095758,
	325719144,
	1689211170,
	102113260,
	-145789821,
	143667189,
	-124787934,
	98237396,
	-69568033,
	42781612,
	-20554884,
	4252705,
	5955245,
	-10830000,
	11700276,
	-10081794,
	7356429,
	-4563289,
	2318694,
	-848808,
	96035,
	147673,
	-215343,
	398286,
	-406221,
	-41628,
	1269406,
	-3532939,
	6866689,
	-10923599,
	14856764,
	-17294290,
	16444922,
	-10342351,
	-2804126,
	24226988,
	-54296418,
	92438173,
	-137488691,
	189040172,
	-252450488,
	373817864,
	1680958263,
	61469328,
	-126688433,
	133963793,
	-120610816,
	97514576,
	-70884195,
	45093563,
	-23112957,
	6568968,
	4139908,
	-9591643,
	10987552,
	-9773001,
	7309010,
	-4649468,
	2444916,
	-960463,
	171646,
	107557,
	-230091,
	439575,
	-494386,
	110677,
	1051427,
	-3279262,
	6653497,
	-10881026,
	15163398,
	-18153559,
	18041597,
	-12781563,
	430898,
	20470457,
	-50595894,
	89762346,
	-137359059,
	194003128,
	-268013879,
	422785750,
	1669992298,
	22391800,
	-107458900,
	123791305,
	-115913189,
	96328447,
	-71838762,
	47156567,
	-25525481,
	8822498,
	2329478,
	-8324503,
	10232159,
	-9421467,
	7226515,
	-4710954,
	2556140,
	-1064401,
	244038,
	68463,
	-244266,
	480068,
	-582665,
	266348,
	823200,
	-3003976,
	6403119,
	-10783520,
	15399499,
	-18935468,
	19571254,
	-15190267,
	3706024,
	16564193,
	-46596894,
	86606628,
	-136551007,
	198107567,
	-282691722,
	472503926,
	1656345595,
	-15042498,
	-88192139,
	113206463,
	-110725549,
	94691121,
	-72431830,
	48963786,
	-27782577,
	11003123,
	532745,
	-7035213,
	9438476,
	-9029639,
	7109990,
	-4747933,
	2652141,
	-1160290,
	312930,
	30570,
	-257742,
	519507,
	-670588,
	424659,
	585669,
	-2708050,
	6116144,
	-10630656,
	15562795,
	-19635001,
	21025380,
	-17556146,
	7005615,
	12525472,
	-42315059,
	82979613,
	-135057545,
	201316760,
	-296391070,
	522849728,
	1640058343,
	-50763144,
	-68977079,
	102266891,
	-105080254,
	92616713,
	-72665240,
	50509711,
	-29875254,
	13101161,
	-1241687,
	-5730422,
	8611000,
	-8600125,
	6960632,
	-4760713,
	2732779,
	-1247845,
	378065,
	-5958,
	-270397,
	557629,
	-757674,
	584851,
	339845,
	-2392575,
	5793355,
	-10422276,
	15651345,
	-20247479,
	22395719,
	-19866930,
	10313713,
	8372446,
	-37767622,
	78892305,
	-132874857,
	203597432,
	-309020617,
	573697092,
	1621178452,
	-84706294,
	-49900349,
	91030827,
	-99011346,
	90121243,
	-72542550,
	51790175,
	-31795437,
	15107462,
	-2985443,
	-4416755,
	7754328,
	-8135679,
	6779783,
	-4749717,
	2797993,
	-1326834,
	439218,
	-40968,
	-282106,
	594170,
	-843430,
	746137,
	86807,
	-2058767,
	5435734,
	-10158505,
	15663550,
	-20768592,
	23674322,
	-22110459,
	13614109,
	4124065,
	-32973345,
	74358098,
	-130002366,
	204919974,
	-320491074,
	624916956,
	1599761386,
	-116814834,
	-31045969,
	79556847,
	-92554363,
	87222533,
	-72068991,
	52802352,
	-33535997,
	17013446,
	-4690412,
	-3100788,
	6873131,
	-7639180,
	6568915,
	-4715481,
	2847803,
	-1397076,
	496187,
	-74323,
	-292746,
	628866,
	-927360,
	907702,
	-172307,
	-1707956,
	5044456,
	-9839745,
	15598173,
	-21194424,
	24853583,
	-24274745,
	16890426,
	-200009,
	-27952445,
	69392745,
	-126442792,
	205258643,
	-330715548,
	676377676,
	1575869968,
	-147038504,
	-12495068,
	67903600,
	-85746156,
	83940101,
	-71251427,
	53544758,
	-35090774,
	18811136,
	-6348787,
	-1789011,
	5972127,
	-7113619,
	6329625,
	-4658645,
	2882309,
	-1458437,
	548802,
	-105900,
	-302195,
	661455,
	-1008959,
	1068713,
	-436301,
	-1341587,
	4620887,
	-9466683,
	15454345,
	-21521477,
	25926287,
	-26348037,
	20126188,
	-4579486,
	-22726518,
	64014314,
	-122202181,
	204591748,
	-339609909,
	727945454,
	1549574158,
	-175333994,
	5674390,
	56129532,
	-78624693,
	80295044,
	-70098297,
	54017238,
	-36454591,
	20493193,
	-7953098,
	-487799,
	5056059,
	-6562081,
	6063621,
	-4579951,
	2901683,
	-1510837,
	596922,
	-135590,
	-310335,
	691677,
	-1087724,
	1228317,
	-703929,
	-961214,
	4166582,
	-9040292,
	15231575,
	-21746696,
	26885651,
	-28318874,
	23304911,
	-8993543,
	-17318448,
	58243136,
	-117289939,
	202901823,
	-347093155,
	779484777,
	1520950803,
	-201665015,
	23387864,
	44292634,
	-71228864,
	76309915,
	-68619551,
	54220951,
	-37623272,
	22052940,
	-9496242,
	796619,
	4129671,
	-5987729,
	5772718,
	-4480238,
	2906175,
	-1554241,
	640432,
	-163301,
	-317051,
	719279,
	-1163153,
	1385648,
	-973900,
	-568492,
	3683280,
	-8561829,
	14929765,
	-21867490,
	27725360,
	-30176157,
	26410177,
	-13420914,
	-11752316,
	52101737,
	-111718831,
	200175781,
	-353087771,
	830858861,
	1490083373,
	-226002347,
	40574471,
	32450182,
	-63598288,
	72008596,
	-66826591,
	54158349,
	-38593647,
	23484388,
	-10971516,
	2058186,
	3197685,
	-5393787,
	5458817,
	-4360432,
	2896102,
	-1588663,
	679247,
	-188954,
	-322230,
	744011,
	-1234744,
	1539833,
	-1244880,
	-165169,
	3172898,
	-8032834,
	14549208,
	-21881751,
	28439610,
	-31909198,
	29425717,
	-17839995,
	-6053297,
	45614759,
	-105504979,
	196405051,
	-357520072,
	881930109,
	1457061661,
	-248323854,
	57167212,
	20658488,
	-55773114,
	67416168,
	-64732190,
	53833148,
	-39363553,
	24782256,
	-12372643,
	3291047,
	2264776,
	-4783521,
	5123903,
	-4221542,
	2871849,
	-1614165,
	713310,
	-212487,
	-325767,
	765634,
	-1302007,
	1689990,
	-1515503,
	246915,
	2637522,
	-7455127,
	14090596,
	-21787875,
	29023139,
	-33507786,
	32335495,
	-22228941,
	-247552,
	38808874,
	-98667838,
	191585708,
	-360320545,
	932560567,
	1421981472,
	-268614476,
	73103165,
	8972659,
	-47793824,
	62558772,
	-62350415,
	53250293,
	-39931836,
	25941985,
	-13693797,
	4489574,
	1335549,
	-4160223,
	4770028,
	-4064656,
	2833867,
	-1630852,
	742592,
	-233851,
	-327563,
	783917,
	-1364459,
	1835241,
	-1784377,
	665841,
	2079406,
	-6830802,
	13555025,
	-21584772,
	29471264,
	-34962240,
	35123789,
	-26565772,
	5637885,
	31712684,
	-91230157,
	185718569,
	-361424166,
	982612388,
	1384944284,
	-286866197,
	88323674,
	-2553629,
	-39701039,
	57463474,
	-59696545,
	52415919,
	-40298338,
	26959756,
	-14929627,
	5648393,
	414522,
	-3527195,
	4399302,
	-3890925,
	2782664,
	-1638874,
	767089,
	-253014,
	-327524,
	798643,
	-1421629,
	1974711,
	-2050086,
	1089618,
	1500954,
	-6162223,
	12943993,
	-21271882,
	29779911,
	-36263465,
	37775275,
	-30828478,
	11575231,
	24356608,
	-83217923,
	178809283,
	-360770719,
	1031948298,
	1346056897,
	-303077981,
	102774510,
	-13868359,
	-31535325,
	52158116,
	-56786978,
	51337307,
	-40463890,
	27832496,
	-16075274,
	6762402,
	-493901,
	-2887731,
	4013880,
	-3701568,
	2718806,
	-1638420,
	786825,
	-269954,
	-325566,
	809604,
	-1473062,
	2107534,
	-2311202,
	1516194,
	904720,
	-5452016,
	12259395,
	-20849184,
	29945642,
	-37403006,
	40275101,
	-34995128,
	17536074,
	16772767,
	-74660293,
	170868395,
	-358305085,
	1080432061,
	1305431055,
	-317255691,
	116406008,
	-24921381,
	-23337003,
	46671183,
	-53639138,
	50022832,
	-40430294,
	28557880,
	-17126390,
	7826796,
	-1385447,
	-2245101,
	3615950,
	-3497853,
	2642910,
	-1629722,
	801848,
	-284668,
	-321612,
	816609,
	-1518323,
	2232858,
	-2566291,
	1943459,
	293389,
	-4703057,
	11503528,
	-20317206,
	29965683,
	-38373095,
	42608976,
	-39043979,
	23491506,
	8994848,
	-65589506,
	161911397,
	-353977526,
	1127928940,
	1263183059,
	-329411973,
	129173193,
	-35664609,
	-15145963,
	41031647,
	-50271382,
	48481910,
	-40200300,
	29134339,
	-18079154,
	8837086,
	-2255994,
	-1602535,
	3207723,
	-3281097,
	2555640,
	-1613045,
	812231,
	-297164,
	-315596,
	819484,
	-1556997,
	2349852,
	-2813918,
	2369263,
	-330228,
	-3918465,
	10679079,
	-19677026,
	29837948,
	-39166703,
	44763240,
	-42953582,
	29412257,
	1057967,
	-56040784,
	151958746,
	-347743943,
	1174306161,
	1219433365,
	-339566127,
	141035880,
	-46052212,
	-7001478,
	35268831,
	-46702893,
	46724941,
	-39777580,
	29561053,
	-18930279,
	9789116,
	-3101589,
	-963209,
	2791421,
	-3052657,
	2457706,
	-1588692,
	818071,
	-307462,
	-307462,
	818071,
	-1588692,
	2457706,
	-3052657,
	2791421,
	-963209,
	-3101589,
	9789116,
	-18930279,
	29561053,
	-39777580,
	46724941,
	-46702893,
	35268831,
	-7001478,
	-46052212,
	141035880,
	-339566127,
	1219433365,
	1174306161,
	-347743943,
	151958746,
	-56040784,
	1057967,
	29412257,
	-42953582,
	44763240,
	-39166703,
	29837948,
	-19677026,
	10679079,
	-3918465,
	-330228,
	2369263,
	-2813918,
	2349852,
	-1556997,
	819484,
	-315596,
	-297164,
	812231,
	-1613045,
	2555640,
	-3281097,
	3207723,
	-1602535,
	-2255994,
	8837086,
	-18079154,
	29134339,
	-40200300,
	48481910,
	-50271382,
	41031647,
	-15145963,
	-35664609,
	129173193,
	-329411973,
	1263183059,
	1127928940,
	-353977526,
	161911397,
	-65589506,
	8994848,
	23491506,
	-39043979,
	42608976,
	-38373095,
	29965683,
	-20317206,
	11503528,
	-4703057,
	293389,
	1943459,
	-2566291,
	2232858,
	-1518323,
	816609,
	-321612,
	-284668,
	801848,
	-1629722,
	2642910,
	-3497853,
	3615950,
	-2245101,
	-1385447,
	7826796,
	-17126390,
	28557880,
	-40430294,
	50022832,
	-53639138,
	46671183,
	-23337003,
	-24921381,
	116406008,
	-317255691,
	1305431055,
	1080432061,
	-358305085,
	170868395,
	-74660293,
	16772767,
	17536074,
	-34995128,
	40275101,
	-37403006,
	29945642,
	-20849184,
	12259395,
	-5452016,
	904720,
	1516194,
	-2311202,
	2107534,
	-1473062,
	809604,
	-325566,
	-269954,
	786825,
	-1638420,
	2718806,
	-3701568,
	4013880,
	-2887731,
	-493901,
	6762402,
	-16075274,
	27832496,
	-40463890,
	51337307,
	-56786978,
	52158116,
	-31535325,
	-13868359,
	102774510,
	-303077981,
	1346056897,
	1031948298,
	-360770719,
	178809283,
	-83217923,
	24356608,
	11575231,
	-30828478,
	37775275,
	-36263465,
	29779911,
	-21271882,
	12943993,
	-6162223,
	1500954,
	1089618,
	-2050086,
	1974711,
	-1421629,
	798643,
	-327524,
	-253014,
	767089,
	-1638874,
	2782664,
	-3890925,
	4399302,
	-3527195,
	414522,
	5648393,
	-14929627,
	26959756,
	-40298338,
	52415919,
	-59696545,
	57463474,
	-39701039,
	-2553629,
	88323674,
	-286866197,
	1384944284,
	982612388,
	-361424166,
	185718569,
	-91230157,
	31712684,
	5637885,
	-26565772,
	35123789,
	-34962240,
	29471264,
	-21584772,
	13555025,
	-6830802,
	2079406,
	665841,
	-1784377,
	1835241,
	-1364459,
	783917,
	-327563,
	-233851,
	742592,
	-1630852,
	2833867,
	-4064656,
	4770028,
	-4160223,
	1335549,
	4489574,
	-13693797,
	25941985,
	-39931836,
	53250293,
	-62350415,
	62558772,
	-47793824,
	8972659,
	73103165,
	-268614476,
	1421981472,
	932560567,
	-360320545,
	191585708,
	-98667838,
	38808874,
	-247552,
	-22228941,
	32335495,
	-33507786,
	29023139,
	-21787875,
	14090596,
	-7455127,
	2637522,
	246915,
	-1515503,
	1689990,
	-1302007,
	765634,
	-325767,
	-212487,
	713310,
	-1614165,
	2871849,
	-4221542,
	5123903,
	-4783521,
	2264776,
	3291047,
	-12372643,
	24782256,
	-39363553,
	53833148,
	-64732190,
	67416168,
	-55773114,
	20658488,
	57167212,
	-248323854,
	1457061661,
	881930109,
	-357520072,
	196405051,
	-105504979,
	45614759,
	-6053297,
	-17839995,
	29425717,
	-31909198,
	28439610,
	-21881751,
	14549208,
	-8032834,
	3172898,
	-165169,
	-1244880,
	1539833,
	-1234744,
	744011,
	-322230,
	-188954,
	679247,
	-1588663,
	2896102,
	-4360432,
	5458817,
	-5393787,
	3197685,
	2058186,
	-10971516,
	23484388,
	-38593647,
	54158349,
	-66826591,
	72008596,
	-63598288,
	32450182,
	40574471,
	-226002347,
	1490083373,
	830858861,
	-353087771,
	200175781,
	-111718831,
	52101737,
	-11752316,
	-13420914,
	26410177,
	-30176157,
	27725360,
	-21867490,
	14929765,
	-8561829,
	3683280,
	-568492,
	-973900,
	1385648,
	-1163153,
	719279,
	-317051,
	-163301,
	640432,
	-1554241,
	2906175,
	-4480238,
	5772718,
	-5987729,
	4129671,
	796619,
	-9496242,
	22052940,
	-37623272,
	54220951,
	-68619551,
	76309915,
	-71228864,
	44292634,
	23387864,
	-201665015,
	1520950803,
	779484777,
	-347093155,
	202901823,
	-117289939,
	58243136,
	-17318448,
	-8993543,
	23304911,
	-28318874,
	26885651,
	-21746696,
	15231575,
	-9040292,
	4166582,
	-961214,
	-703929,
	1228317,
	-1087724,
	691677,
	-310335,
	-135590,
	596922,
	-1510837,
	2901683,
	-4579951,
	6063621,
	-6562081,
	5056059,
	-487799,
	-7953098,
	20493193,
	-36454591,
	54017238,
	-70098297,
	80295044,
	-78624693,
	56129532,
	5674390,
	-175333994,
	1549574158,
	727945454,
	-339609909,
	204591748,
	-122202181,
	64014314,
	-22726518,
	-4579486,
	20126188,
	-26348037,
	25926287,
	-21521477,
	15454345,
	-9466683,
	4620887,
	-1341587,
	-436301,
	1068713,
	-1008959,
	661455,
	-302195,
	-105900,
	548802,
	-1458437,
	2882309,
	-4658645,
	6329625,
	-7113619,
	5972127,
	-1789011,
	-6348787,
	18811136,
	-35090774,
	53544758,
	-71251427,
	83940101,
	-85746156,
	67903600,
	-12495068,
	-147038504,
	1575869968,
	676377676,
	-330715548,
	205258643,
	-126442792,
	69392745,
	-27952445,
	-200009,
	16890426,
	-24274745,
	24853583,
	-21194424,
	15598173,
	-9839745,
	5044456,
	-1707956,
	-172307,
	907702,
	-927360,
	628866,
	-292746,
	-74323,
	496187,
	-1397076,
	2847803,
	-4715481,
	6568915,
	-7639180,
	6873131,
	-3100788,
	-4690412,
	17013446,
	-33535997,
	52802352,
	-72068991,
	87222533,
	-92554363,
	79556847,
	-31045969,
	-116814834,
	1599761386,
	624916956,
	-320491074,
	204919974,
	-130002366,
	74358098,
	-32973345,
	4124065,
	13614109,
	-22110459,
	23674322,
	-20768592,
	15663550,
	-10158505,
	5435734,
	-2058767,
	86807,
	746137,
	-843430,
	594170,
	-282106,
	-40968,
	439218,
	-1326834,
	2797993,
	-4749717,
	6779783,
	-8135679,
	7754328,
	-4416755,
	-2985443,
	15107462,
	-31795437,
	51790175,
	-72542550,
	90121243,
	-99011346,
	91030827,
	-49900349,
	-84706294,
	1621178452,
	573697092,
	-309020617,
	203597432,
	-132874857,
	78892305,
	-37767622,
	8372446,
	10313713,
	-19866930,
	22395719,
	-20247479,
	15651345,
	-10422276,
	5793355,
	-2392575,
	339845,
	584851,
	-757674,
	557629,
	-270397,
	-5958,
	378065,
	-1247845,
	2732779,
	-4760713,
	6960632,
	-8600125,
	8611000,
	-5730422,
	-1241687,
	13101161,
	-29875254,
	50509711,
	-72665240,
	92616713,
	-105080254,
	102266891,
	-68977079,
	-50763144,
	1640058343,
	522849728,
	-296391070,
	201316760,
	-135057545,
	82979613,
	-42315059,
	12525472,
	7005615,
	-17556146,
	21025380,
	-19635001,
	15562795,
	-10630656,
	6116144,
	-2708050,
	585669,
	424659,
	-670588,
	519507,
	-257742,
	30570,
	312930,
	-1160290,
	2652141,
	-4747933,
	7109990,
	-9029639,
	9438476,
	-7035213,
	532745,
	11003123,
	-27782577,
	48963786,
	-72431830,
	94691121,
	-110725549,
	113206463,
	-88192139,
	-15042498,
	1656345595,
	472503926,
	-282691722,
	198107567,
	-136551007,
	86606628,
	-46596894,
	16564193,
	3706024,
	-15190267,
	19571254,
	-18935468,
	15399499,
	-10783520,
	6403119,
	-3003976,
	823200,
	266348,
	-582665,
	480068,
	-244266,
	68463,
	244038,
	-1064401,
	2556140,
	-4710954,
	7226515,
	-9421467,
	10232159,
	-8324503,
	2329478,
	8822498,
	-25525481,
	47156567,
	-71838762,
	96328447,
	-115913189,
	123791305,
	-107458900,
	22391800,
	1669992298,
	422785750,
	-268013879,
	194003128,
	-137359059,
	89762346,
	-50595894,
	20470457,
	430898,
	-12781563,
	18041597,
	-18153559,
	15163398,
	-10881026,
	6653497,
	-3279262,
	1051427,
	110677,
	-494386,
	439575,
	-230091,
	107557,
	171646,
	-960463,
	2444916,
	-4649468,
	7309010,
	-9773001,
	10987552,
	-9591643,
	4139908,
	6568968,
	-23112957,
	45093563,
	-70884195,
	97514576,
	-120610816,
	133963793,
	-126688433,
	61469328,
	1680958263,
	373817864,
	-252450488,
	189040172,
	-137488691,
	92438173,
	-54296418,
	24226988,
	-2804126,
	-10342351,
	16444922,
	-17294290,
	14856764,
	-10923599,
	6866689,
	-3532939,
	1269406,
	-41628,
	-406221,
	398286,
	-215343,
	147673,
	96035,
	-848808,
	2318694,
	-4563289,
	7356429,
	-10081794,
	11700276,
	-10830000,
	5955245,
	4252705,
	-20554884,
	42781612,
	-69568033,
	98237396,
	-124787934,
	143667189,
	-145789821,
	102113260,
	1689211170,
	325719144,
	-236095758,
	183258659,
	-136949984,
	94627933,
	-57684468,
	27817456,
	-5983811,
	-7884940,
	14789953,
	-16362985,
	14482185,
	-10911933,
	7042303,
	-3764169,
	1476266,
	-189875,
	-318627,
	356457,
	-200141,
	188618,
	17514,
	-729820,
	2177780,
	-4452351,
	7367885,
	-10345571,
	12366101,
	-12032986,
	7766549,
	1884331,
	-17861985,
	40228866,
	-67891952,
	98486878,
	-128416081,
	152845919,
	-164670491,
	144240568,
	1694726677,
	278604306,
	-219044777,
	176701544,
	-135756020,
	96327864,
	-60747741,
	31226546,
	-9093380,
	-5421563,
	13085584,
	-15365248,
	14042542,
	-10846980,
	7180141,
	-3972240,
	1671211,
	-333409,
	-232044,
	314338,
	-184607,
	230188,
	-63582,
	-603930,
	2022565,
	-4316715,
	7342657,
	-10562246,
	12980964,
	-13194094,
	9564778,
	-525135,
	-15045790,
	37444768,
	-65859411,
	98255158,
	-131468995,
	161445844,
	-183236549,
	187762244,
	1697488506,
	232583555,
	-201393135,
	169414536,
	-133922773,
	97536602,
	-63475661,
	34440019,
	-12118589,
	-2964323,
	11340829,
	-14306929,
	13540996,
	-10729938,
	7280198,
	-4156572,
	1853523,
	-471617,
	-146895,
	272170,
	-168855

};

static const struct src_stage src_int32_40_21_3968_5000 = {
	11, 21, 40, 40, 1600, 21, 40, 0, 0,
	src_int32_40_21_3968_5000_fir};