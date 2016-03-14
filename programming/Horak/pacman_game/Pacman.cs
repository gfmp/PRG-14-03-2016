using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pacman_game
{
    class Pacman
    {
        int x, y;
        int zakladnaX, zakladnaY;
        private int zivoty = 3;
        private int  skore=0;
        public Pacman(int _x ,int _y)
        {
            zakladnaX = _x;
                zakladnaY=_y;
            this.x = _x;
            this.y = _y;
        }

        public void pridej_bod()
        {
            skore++;
        }
        private void odeber_zivot()
        {
            zivoty--;
        }
        public int poziceX()
        {
            return x;
        }
        public int poziceY()
        {
            return y;
        }
        public int pocet_bodu()
        {
            return skore ;
        }
        public int pocet_zivotu()
        {
            return zivoty;
        }
        public void zemrel()
        {
            odeber_zivot();
            x = zakladnaX;
            y = zakladnaY;
        }
        public void pohyb(char klavesa )
        {
            if(klavesa == 's')
            {
                try
                {
                    if (World.sachovnice[x, y + 1].je_tu_zed() != true)
                        y++;

                }
                catch (Exception)
                {
                    
                    
                }

            }
            else if (klavesa == 'w')
            {
                try
                {
                    if (World.sachovnice[x, y - 1].je_tu_zed() != true)
                        y--;

                }
                catch (Exception)
                {

                    
                }
            }
            else if (klavesa == 'a')
            {
                try
                {
                    if (World.sachovnice[x - 1, y].je_tu_zed() != true)
                        x--;

                }
                catch (Exception)
                {

                    
                }
            }


            else if (klavesa == 'd')
            {
                try
                {
                    if (World.sachovnice[x+1, y ].je_tu_zed() != true)
                        x++;

                }
                catch (Exception)
                {

                    
                }
            }
        }
    }
}
