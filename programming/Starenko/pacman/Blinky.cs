using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pacman
{
    class Blinky
    {
        public int x, y;//souradnice
        public bool tmp;
        int sx, sy;

                public Blinky (int x, int y)
        {
            this.x = x;
            this.y = y;
            this.tmp = true;
        }


        private void zkontroluj(int ypac)
                {
            if (y > ypac && y < ypac)
                tmp =true;
            else
                tmp = false;


                }

        public void vrat()//opravuje souradnice v pripade narazu
        {
            x = sx;
            y = sy;
        }

        public void najdiPac(int xpac, int ypac)
        {

            sx = x;
            sy = y;

            switch (tmp)
            {
                case true:
            if (x > xpac)
                x--;//nahoru

            if (x < xpac)
                x++;//dolu
                    break;



                case false:
            if (y < ypac)
                y++;//doprava

            if (y > ypac)
                y--;//doleva
                    break;



                default:
                    break;
            }
            //if (x > xpac && x < xpac)
            //{

            //if (x > xpac)
            //    x--;

            //if (x < xpac)
            //    x++;
            //}
            //else
            //{

            //if (y < ypac)
            //    y++;

            //if (y > ypac)
            //    y--;

            //}
        }





    }
}
