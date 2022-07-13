
// 函数：获取宝石文件
string get_stone_file()
{
        int p = random(10000);

        if( p < 225 ) return "/item/89/8901";
        else if( p < 475 ) return "/item/89/8902";
        else if( p < 750 ) return "/item/89/8903";
        else if( p < 1000 ) return "/item/89/8904";
        else if( p < 1005 ) return "/item/89/8905";
        else if( p < 1010 ) return "/item/89/8906";
        else if( p < 1020 ) return "/item/89/8907";
        else if( p < 1030 ) return "/item/89/8908";
        else if( p < 1105 ) return "/item/89/8909";
        else if( p < 1205 ) return "/item/89/8910";
        else if( p < 1305 ) return "/item/89/8911";
        else if( p < 1380 ) return "/item/89/8912";
        else if( p < 1455 ) return "/item/89/8913";
        else if( p < 1480 ) return "/item/89/8914";
        else if( p < 1505 ) return "/item/89/8915";
        else if( p < 1530 ) return "/item/89/8916";
        else if( p < 1630 ) return "/item/89/8917";
        else if( p < 1880 ) return "/item/89/8918";
        else if( p < 2130 ) return "/item/89/8919";
        else if( p < 2355 ) return "/item/89/8920";
        else if( p < 2380 ) return "/item/89/8921";
        else if( p < 2700 ) return "/item/89/8922";
        else if( p < 3000 ) return "/item/89/8923";
        else if( p < 7000 ) return "/item/std/8900";
        else if( p < 10000 ) return "/item/std/0089";
}

// 函数：获取宝石文件(残破藏宝图)
string get_stone_file_2()
{
        int p = random(10000);

        if( p < 850 ) return "/item/89/8951";
        else if( p < 1790 ) return "/item/89/8952";
        else if( p < 2790 ) return "/item/89/8953";
        else if( p < 3730 ) return "/item/89/8954";
        else if( p < 3750 ) return "/item/89/8955";
        else if( p < 3770 ) return "/item/89/8956";
        else if( p < 3800 ) return "/item/89/8957";
        else if( p < 3830 ) return "/item/89/8958";
        else if( p < 4110 ) return "/item/89/8959";
        else if( p < 4480 ) return "/item/89/8960";
        else if( p < 4850 ) return "/item/89/8961";
        else if( p < 5130 ) return "/item/89/8962";
        else if( p < 5410 ) return "/item/89/8963";
        else if( p < 5500 ) return "/item/89/8964";
        else if( p < 5590 ) return "/item/89/8965";
        else if( p < 5680 ) return "/item/89/8966";
        else if( p < 6050 ) return "/item/89/8967";
        else if( p < 6990 ) return "/item/89/8968";
        else if( p < 7930 ) return "/item/89/8969";
        else if( p < 8780 ) return "/item/89/8970";
        else if( p < 8870 ) return "/item/89/8971";
        else if( p < 8870 ) return "/item/89/8972";
        else if( p < 10000 ) return "/item/89/8973";
}


string get_diamond_file()
{
	return sprintf("/item/93/%d", 9301+random(10));
}