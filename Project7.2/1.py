import matplotlib.pyplot as plt
x = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498]

y8 = [17582,27083,9209,12168,11607,11285,9807,9424,9407,10019,11348,11421,11465,12503,11555,12590,13629,14198,14252,39009,38391,22650,20452,21795,21365,22546,26188,24084,25034,32057,32451,27999,27648,29469,39617,34640,35492,35125,34336,30725,46848,56283,51015,38717,35875,36264,36469,38204,40068,39956,42442,41162,42374,46633,57879,46187,49306,48413,72990,56861,52659,49701,51393,49364,51260,54436,50681,52482,54254,54418,54141,57480,57888,70958,57135,63077,62376,61833,63648,63493,66219,66145,72170,67130,65887,69864,68475,71644,69794,69719,72794,90029,78537,77074,74541,76076,75831,78795,77772,80970,88959,89752,81646,82734,85486,82795,85807,84367,89723,85122,88082,90543,90273,89240,88100,95169,97093,92682,90334,95048,91546,92887,99600,105448,96529,103248,102294,103172,102613,103095,103016,102270,114454,109308,106790,105524,108375,112379,112485,117690,115510,107634,79918,80638,81608,80787,82795,84893,86245,83064,88196,85128,101462,96540,87625,92917,88696,92885,92303,91277,93561,95181,92889,96010,95231,97444,111066,99875,102559,104306,102069,127000,120975,117557,104437,108674,107288,107521,109555,111423,110954,112559,113420,112305,115781,112767,112160,114877,116996,116447,116603,117847,116296,120222,118402,120976,120974,121146,121058,121471,122324,125094,123075,126609,125610,126544,125411,129735,126657,128720,128957,128954,129448,131695,131369,141268,131951,131627,226877,159012,132687,135422,140621,140814,136432,136969,137125,144245,137461,141248,139638,139323,142382,142262,143753,146119,146077,147950,146915,154483,152265,158109,155223,154717,155271,149894,150961,148001,150518,161795,151382,151178,166974,154454,152629,166478,153495,154455,157514,155461,160896,177034,162191,161906,161098,157766,161525,165629,160498,162897,161780,162388,160832,163938,164658,166015,166067,166904,166181,167993,174996,167149,175907,171242,170450,167883,166350,169367,170568,167905,171897,177707,169395,171881,174440,181662,173451,175757,185224,174081,179813,174577,174207,177511,179457,181427,179916,179985,180094,178805,180198,181398,183322,181666,194055,181372,183473,183692,182073,184682,187649,187366,186830,190298,187581,185673,188028,190359,197966,189768,190335,201323,201799,193600,193837,194551,194113,198011,194411,195129,197069,199318,242911,238176,208371,208249,199584,200488,205200,214154,203339,204558,202581,203563,205306,205310,204314,207093,205867,211478,207142,209767,208948,212654,209058,211159,211491,210629,212422,214091,212751,212906,213520,213191,216637,216451,228860,216785,219257,219507,217152,236835,258752,240729,228107,227145,229430,244181,230549,235452,236487,231199,231690,236537,233066,245201,230191,232202,233915,236419,233594,235805,235081,236176,240686,238963,236095,237139,240426,240004,240959,240703,245034,250867,444065,252282,243366,244145,246127,251824,245626,249126,246501,271988,245938,250916,252454,252805,250656,285931,254048,264391,256240,252327,254697,265920,254740,263600,254573,256763,254554,255621,258418,264751,255398,255652,256314,256832,257636,258695,275172,259001,261702,271689,259861,272840,264091,262864,264663,268172,262496,265194,265859,270968,267700,267797,267564,267753,279008,329723,359420,331311,328222,331545,281741,293839,274918,276871,274530,275783,274678,289787,279957,279820,280288,275742,280465,279737,278409,281914,278930,303616,281433,280529,286170,292257,288308,309728,308908]
plt.plot(x, y8) 
plt.show()
