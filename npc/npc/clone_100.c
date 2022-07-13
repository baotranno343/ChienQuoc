
void clone( object me )
{
        object who;
        int z, x0, y0, x, y;
        int i, n;

        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);
        for( i = 0; i < 100; i ++ ) 
        {
                who = new( __DIR__ "9999" );

                if( n = get_valid_xy(z, x0 - 25 + random(50), y0 - 25 + random(50), IS_CHAR_BLOCK) )
                {
                        who->add_to_scene(z, n / 1000, n % 1000, 3);
                }
        }
}
