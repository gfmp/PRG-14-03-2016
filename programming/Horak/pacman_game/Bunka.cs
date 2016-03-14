using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pacman_game
{
    class Bunka
    {
        bool bod = false;
        bool zed = false;
        
        public void tvorba_zed()
        {
            zed = true;
        }
        public void tvorba_bodu() 
        {
            bod = true;
        }
        public void sebrani_bodu()//od packamena
        {
            bod = false;
        }
        public bool je_tu_zed()
        {
            bool pravda = false;
            if (zed == true)
                pravda = true;
            return pravda;

        }
        public bool je_tu_bod()
        {
            bool pravda = false;
            if (bod == true)
                pravda = true;
            return pravda;

        }
    }
}
