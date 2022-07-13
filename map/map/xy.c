
// 函数：获取合法坐标(等级地图)
int get_xy_point( int level, int flag )
{
        if( level < 0 ) level = random(110);    // 随机地图

        switch( level / 5 )    // 每 5 级不同地图  // z * 1000000
        {
      case  0 : switch( random(3) )
                {
               case 0 : return 001000000 + efun::get_xy_point(001, flag);
               case 1 : return 002000000 + efun::get_xy_point(002, flag);
               case 2 : return 003000000 + efun::get_xy_point(003, flag);
                }
                break;
      case  1 : switch( random(5) )
                {
               case 0 : return 161000000 + efun::get_xy_point(161, flag);
               case 1 : return 162000000 + efun::get_xy_point(162, flag);
               case 2 : return 061000000 + efun::get_xy_point(061, flag);
               case 3 : return 062000000 + efun::get_xy_point(062, flag);
               case 4 : return 063000000 + efun::get_xy_point(063, flag);
                }
                break;
      case  2 : switch( random(4) )
                {
               case 0 : return 281000000 + efun::get_xy_point(281, flag);
               case 1 : return 282000000 + efun::get_xy_point(282, flag);
               case 2 : return 283000000 + efun::get_xy_point(283, flag);
               case 3 : return 284000000 + efun::get_xy_point(284, flag);
                }
                break;
      case  3 : switch( random(3) )
                {
               case 0 : return 081000000 + efun::get_xy_point(081, flag);
               case 1 : return 082000000 + efun::get_xy_point(082, flag);
               case 2 : return 251000000 + efun::get_xy_point(251, flag);
                }
                break;
      case  4 : switch( random(8) )
                {
               case 0 : return 021000000 + efun::get_xy_point(021, flag);
               case 1 : return 041000000 + efun::get_xy_point(041, flag);
               case 2 : return 042000000 + efun::get_xy_point(042, flag);
               case 3 : return 043000000 + efun::get_xy_point(043, flag);
               case 4 : return 089000000 + efun::get_xy_point(089, flag);
               case 5 : return 141000000 + efun::get_xy_point(141, flag);
               case 6 : return 142000000 + efun::get_xy_point(142, flag);
               case 7 : return 211000000 + efun::get_xy_point(211, flag);
                }
                break;
      case  5 : switch( random(11) )
                {
               case 0 : return 241000000 + efun::get_xy_point(241, flag);
               case 1 : return 242000000 + efun::get_xy_point(242, flag);
               case 2 : return 243000000 + efun::get_xy_point(243, flag);
               case 3 : return 271000000 + efun::get_xy_point(271, flag);
               case 4 : return 272000000 + efun::get_xy_point(272, flag);
               case 5 : return 131000000 + efun::get_xy_point(131, flag);
               case 6 : return 132000000 + efun::get_xy_point(132, flag);
               case 7 : return 231000000 + efun::get_xy_point(231, flag);
               case 8 : return 181000000 + efun::get_xy_point(181, flag);
               case 9 : return 182000000 + efun::get_xy_point(182, flag);
               case 10 : return 155000000 + efun::get_xy_point(155, flag);
                }
                break;
      case  6 : switch( random(6) )
                {
               case 0 : return 163000000 + efun::get_xy_point(163, flag);
               case 1 : return 164000000 + efun::get_xy_point(164, flag);
               case 2 : return 261000000 + efun::get_xy_point(261, flag);
               case 3 : return 262000000 + efun::get_xy_point(262, flag);
               case 4 : return 263000000 + efun::get_xy_point(263, flag);
               case 5 : return 264000000 + efun::get_xy_point(264, flag);
                }
                break;
      case  7 : switch( random(4) )
                {
               case 0 : return 265000000 + efun::get_xy_point(265, flag);
               case 1 : return 266000000 + efun::get_xy_point(266, flag);
               case 2 : return 111000000 + efun::get_xy_point(111, flag);
               case 3 : return 112000000 + efun::get_xy_point(112, flag);
                }
                break;
      case  8 : switch( random(5) )
                {
               case 0 : return 011000000 + efun::get_xy_point(011, flag);
               case 1 : return 012000000 + efun::get_xy_point(012, flag);
               case 2 : return 013000000 + efun::get_xy_point(013, flag);
               case 3 : return 014000000 + efun::get_xy_point(014, flag);
               case 4 : return 015000000 + efun::get_xy_point(015, flag);
                }
                break;
      case  9 : switch( random(3) )
                {
               case 0 : return 151000000 + efun::get_xy_point(151, flag);
               case 1 : return 152000000 + efun::get_xy_point(152, flag);
               case 2 : return 153000000 + efun::get_xy_point(153, flag);
                }
                break;
      case 10 : switch( random(4) )
                {
               case 0 : return 171000000 + efun::get_xy_point(171, flag);
               case 1 : return 172000000 + efun::get_xy_point(172, flag);
               case 2 : return 173000000 + efun::get_xy_point(173, flag);
               case 3 : return 174000000 + efun::get_xy_point(174, flag);
                }
                break;
      case 11 : switch( random(3) )
                {
               case 0 : return 071000000 + efun::get_xy_point(071, flag);
               case 1 : return 072000000 + efun::get_xy_point(072, flag);
               case 2 : return 073000000 + efun::get_xy_point(073, flag);
                }
                break;
      case 12 : switch( random(3) )
                {
               case 0 : return 031000000 + efun::get_xy_point(031, flag);
               case 1 : return 032000000 + efun::get_xy_point(032, flag);
               case 2 : return 033000000 + efun::get_xy_point(033, flag);
                }
                break;
      case 13 : switch( random(3) )
                {
               case 0 : return 051000000 + efun::get_xy_point(051, flag);
               case 1 : return 052000000 + efun::get_xy_point(052, flag);
               case 2 : return 053000000 + efun::get_xy_point(053, flag);
                }
                break;
      case 14 : switch( random(3) )
                {
               case 0 : return 321000000 + efun::get_xy_point(321, flag);
               case 1 : return 322000000 + efun::get_xy_point(322, flag);
               case 2 : return 323000000 + efun::get_xy_point(323, flag);
                }
                break;
      case 15 : switch( random(3) )
                {
               case 0 : return 311000000 + efun::get_xy_point(311, flag);
               case 1 : return 312000000 + efun::get_xy_point(312, flag);
               case 2 : return 313000000 + efun::get_xy_point(313, flag);
                }
                break;
      case 16 : switch( random(5) )
                {
               case 0 : return 331000000 + efun::get_xy_point(331, flag);
               case 1 : return 332000000 + efun::get_xy_point(332, flag);
               case 2 : return 333000000 + efun::get_xy_point(333, flag);
               case 3 : return 334000000 + efun::get_xy_point(334, flag);
               case 4 : return 335000000 + efun::get_xy_point(335, flag);
                }
                break;
      case 17 : switch( random(5) )
                {
               case 0 : return 341000000 + efun::get_xy_point(341, flag);
               case 1 : return 342000000 + efun::get_xy_point(342, flag);
               case 2 : return 343000000 + efun::get_xy_point(343, flag);
               case 3 : return 344000000 + efun::get_xy_point(344, flag);
               case 4 : return 345000000 + efun::get_xy_point(345, flag);
                }
                break;
      case 18 : switch( random(3) )
                {
               case 0 : return 291000000 + efun::get_xy_point(291, flag);
               case 1 : return 292000000 + efun::get_xy_point(292, flag);
               case 2 : return 293000000 + efun::get_xy_point(293, flag);
                }
                break;
      case 19 : switch( random(5) )
                {
               case 0 : return 381000000 + efun::get_xy_point(381, flag);
               case 1 : return 382000000 + efun::get_xy_point(382, flag);
               case 2 : return 383000000 + efun::get_xy_point(383, flag);
               case 3 : return 384000000 + efun::get_xy_point(384, flag);
               case 4 : return 385000000 + efun::get_xy_point(385, flag);
                }
                break;
      case 20 : switch( random(4) )
                {
               case 0 : return 371000000 + efun::get_xy_point(371, flag);
               case 1 : return 372000000 + efun::get_xy_point(372, flag);
               case 2 : return 373000000 + efun::get_xy_point(373, flag);
               case 3 : return 374000000 + efun::get_xy_point(374, flag);
                }
                break;
      case 21 : switch( random(4) )
                {
               case 0 : return 091000000 + efun::get_xy_point(091, flag);
               case 1 : return 092000000 + efun::get_xy_point(092, flag);
               case 2 : return 093000000 + efun::get_xy_point(093, flag);
               case 3 : return 095000000 + efun::get_xy_point(095, flag);
                }
                break;
      default : switch( random(3) )
                {
               case 0 : return 391000000 + efun::get_xy_point(391, flag);
               case 1 : return 392000000 + efun::get_xy_point(392, flag);
               case 2 : return 393000000 + efun::get_xy_point(393, flag);
                }
                break;
        }
}

// 函数：获取合法坐标(新手村地图)
int get_newbie_point( int flag )
{
        switch( random(3) )
        {
      default : return 1000000 + efun::get_xy_point(001, flag);    // z * 1000000
       case 1 : return 2000000 + efun::get_xy_point(002, flag);
       case 2 : return 3000000 + efun::get_xy_point(003, flag);
        }
}

// 函数：获取合法坐标(城市地图)
int get_city_point( int city, int flag )
{
        if( city < 0 ) city = random(8);    // 随机城市

        switch( city )
        {
       case 1 : return 10000000 + efun::get_xy_point(010, flag);    // z * 1000000
       case 2 : return 20000000 + efun::get_xy_point(020, flag);
       case 3 : return 30000000 + efun::get_xy_point(030, flag);
       case 4 : return 40000000 + efun::get_xy_point(040, flag);
       case 5 : return 50000000 + efun::get_xy_point(050, flag);
       case 6 : return 60000000 + efun::get_xy_point(060, flag);
       case 7 : return 70000000 + efun::get_xy_point(070, flag);
      default : return 80000000 + efun::get_xy_point(080, flag);
        }
}

// 函数：获取合法坐标(小贩地图) -- 城市、野外(禁止长城、地洞、花园)
int get_seller_point( int flag )
{
        switch( random(11) )    // 注意：根据 case 调整
        {
      case  0 : switch( random(3) )
                {
               case 0 : return 001000000 + efun::get_xy_point(001, flag);    // z * 1000000
               case 1 : return 002000000 + efun::get_xy_point(002, flag);
               case 2 : return 003000000 + efun::get_xy_point(003, flag);
                }
                break;
      case  1 : switch( random(2) )
                {
               case 0 : return 161000000 + efun::get_xy_point(161, flag);
               case 1 : return 162000000 + efun::get_xy_point(162, flag);
//             case 2 : return 061000000 + efun::get_xy_point(061, flag);
//             case 3 : return 062000000 + efun::get_xy_point(062, flag);
//             case 4 : return 063000000 + efun::get_xy_point(063, flag);
                }
                break;
      case  2 : switch( random(4) )
                {
               case 0 : return 281000000 + efun::get_xy_point(281, flag);
               case 1 : return 282000000 + efun::get_xy_point(282, flag);
               case 2 : return 283000000 + efun::get_xy_point(283, flag);
               case 3 : return 284000000 + efun::get_xy_point(284, flag);
                }
                break;
      case  3 : switch( random(3) )
                {
               case 0 : return 081000000 + efun::get_xy_point(081, flag);
               case 1 : return 082000000 + efun::get_xy_point(082, flag);
               case 2 : return 251000000 + efun::get_xy_point(251, flag);
                }
                break;
      case  4 : switch( random(8) )
                {
               case 0 : return 021000000 + efun::get_xy_point(021, flag);
               case 1 : return 041000000 + efun::get_xy_point(041, flag);
               case 2 : return 042000000 + efun::get_xy_point(042, flag);
               case 3 : return 043000000 + efun::get_xy_point(043, flag);
               case 4 : return 089000000 + efun::get_xy_point(089, flag);
               case 5 : return 141000000 + efun::get_xy_point(141, flag);
               case 6 : return 142000000 + efun::get_xy_point(142, flag);
               case 7 : return 211000000 + efun::get_xy_point(211, flag);
                }
                break;
      case  5 : switch( random(11) )
                {
               case 0 : return 241000000 + efun::get_xy_point(241, flag);
               case 1 : return 242000000 + efun::get_xy_point(242, flag);
               case 2 : return 243000000 + efun::get_xy_point(243, flag);
               case 3 : return 271000000 + efun::get_xy_point(271, flag);
               case 4 : return 272000000 + efun::get_xy_point(272, flag);
               case 5 : return 131000000 + efun::get_xy_point(131, flag);
               case 6 : return 132000000 + efun::get_xy_point(132, flag);
               case 7 : return 231000000 + efun::get_xy_point(231, flag);
               case 8 : return 181000000 + efun::get_xy_point(181, flag);
               case 9 : return 182000000 + efun::get_xy_point(182, flag);
               case 10 : return 155000000 + efun::get_xy_point(155, flag);
                }
                break;
      case  6 : switch( random(6) )
                {
               case 0 : return 163000000 + efun::get_xy_point(163, flag);
               case 1 : return 164000000 + efun::get_xy_point(164, flag);
               case 2 : return 261000000 + efun::get_xy_point(261, flag);
               case 3 : return 262000000 + efun::get_xy_point(262, flag);
               case 4 : return 263000000 + efun::get_xy_point(263, flag);
               case 5 : return 264000000 + efun::get_xy_point(264, flag);
                }
                break;
      case  7 : switch( random(4) )
                {
               case 0 : return 265000000 + efun::get_xy_point(265, flag);
               case 1 : return 266000000 + efun::get_xy_point(266, flag);
               case 2 : return 111000000 + efun::get_xy_point(111, flag);
               case 3 : return 112000000 + efun::get_xy_point(112, flag);
                }
                break;
      case  8 : switch( random(5) )
                {
               case 0 : return 011000000 + efun::get_xy_point(011, flag);
               case 1 : return 012000000 + efun::get_xy_point(012, flag);
               case 2 : return 013000000 + efun::get_xy_point(013, flag);
               case 3 : return 014000000 + efun::get_xy_point(014, flag);
               case 4 : return 015000000 + efun::get_xy_point(015, flag);
                }
                break;
/*    case  9 : switch( random(3) )
                {
               case 0 : return 151000000 + efun::get_xy_point(151, flag);
               case 1 : return 152000000 + efun::get_xy_point(152, flag);
               case 2 : return 153000000 + efun::get_xy_point(153, flag);
                }
                break;  */
      case  9 : switch( random(4) )
                {
               case 0 : return 171000000 + efun::get_xy_point(171, flag);
               case 1 : return 172000000 + efun::get_xy_point(172, flag);
               case 2 : return 173000000 + efun::get_xy_point(173, flag);
               case 3 : return 174000000 + efun::get_xy_point(174, flag);
                }
                break;

      default : switch( random(8) )
                {
               case 1 : return 10000000 + efun::get_xy_point(010, flag);    // z * 1000000
               case 2 : return 20000000 + efun::get_xy_point(020, flag);
               case 3 : return 30000000 + efun::get_xy_point(030, flag);
               case 4 : return 40000000 + efun::get_xy_point(040, flag);
               case 5 : return 50000000 + efun::get_xy_point(050, flag);
               case 6 : return 60000000 + efun::get_xy_point(060, flag);
               case 7 : return 70000000 + efun::get_xy_point(070, flag);
              default : return 80000000 + efun::get_xy_point(080, flag);
                }
                break;
        }
}

// 函数：新小贩地图
int get_seller_point_2()
{
        switch( random(8) ) 
	{
               case 1 : return 502181168;
               case 2 : return 530158150;
               case 3 : return 528165092;
               case 4 : return 512127180;
               case 5 : return 511116128;
               case 6 : return 526212110;
               case 7 : return 524158150;
              default : return 516093143;
	}
}