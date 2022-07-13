
// 函数：按等级获取草药
string get_herb_file( int level ) 
{
        int p = random(100);

        switch( level )
        {
      default : if( p <  60 ) return "/item/90/9001";
                if( p <  89 ) return "/item/90/9002";
                if( p <  99 ) return "/item/90/9003";
                if( p < 100 ) return "/item/90/9004";
                break;
       case 2 : if( p <  60 ) return "/item/90/9010";
                if( p <  90 ) return "/item/90/9011";
                if( p < 100 ) return "/item/90/9012";
                break;
       case 3 : if( p <  58 ) return "/item/90/9020";
                if( p <  88 ) return "/item/90/9021";
                if( p <  98 ) return "/item/90/9022";
                if( p < 100 ) return "/item/90/9023";
                break;
       case 4 : if( p <  60 ) return "/item/90/9030";
                if( p <  90 ) return "/item/90/9031";
                if( p < 100 ) return "/item/90/9032";
                break;
       case 5 : if( p <  60 ) return "/item/90/9040";
                if( p <  90 ) return "/item/90/9041";
                if( p < 100 ) return "/item/90/9042";
                break;
       case 6 : if( p <  60 ) return "/item/90/9050";
                if( p <  90 ) return "/item/90/9051";
                if( p < 100 ) return "/item/90/9052";
                break;
       case 7 : if( p <  60 ) return "/item/90/9060";
                if( p <  90 ) return "/item/90/9061";
                if( p < 100 ) return "/item/90/9062";
                break;
        }
}
