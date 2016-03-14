using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pacman
{
    class Pacman
    {
        public int x,y;//souradnice
        public int zivot;
        public bool zije;
        int sx, sy;//zalohovani souradnic pacmana


        public Pacman (int x, int y)
        {
            this.x = x;
            this.y = y;
            this.zivot = 3;
            this.zije = true;
            this.sx = 0;
            this.sy = 0;
        }


        public void vrat()//opravuje souradnice v pripade narazu
        {
            x = sx;
            y = sy;
        }

        public void zatoc(int smer)
        {


            sx = x;
            sy = y;




                switch (smer)
                {
                    case 4:
                        y--;
                        break;

                    case 8:
                        x--;
                        break;

                    case 2:
                        x++;
                        break;

                    case 6:
                        y++;
                        break;

                    default:
                        break;


                }
            
            
              

        }

        



    }
}
