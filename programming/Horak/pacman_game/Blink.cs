using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Threading.Tasks;

namespace pacman_game
{
    class Blink
    {
        private int x, y;
        public Blink(int _x, int _y)
        {

            this.x = _x;
            this.y = _y;
            napln_svetik();
            vyplnit_Svetik();

        }
        private int[,] svetik = new int[World.sachovnice.GetLength(0),World.sachovnice.GetLength(1)];

    
         
         
      
         public int poziceX()
         {
             return x;
         }
         public int poziceY()
         {
             return y;
         }
        private void napln_svetik()
         {
             for (int x = 0; x < svetik.GetLength(0); x++)
             {
                 for (int y = 0; y < svetik.GetLength(1); y++)
                 {
                     int nova = -1;
                     svetik[x, y] = nova;

                 }
             }
         }
        private void vyplnit_Svetik()
        {
            for (int x = 0; x < svetik.GetLength(0); x++)
            {
                for (int y = 0; y < svetik.GetLength(1); y++)
                {
                    bool aaa = World.sachovnice[x, y].je_tu_zed();
                   if(aaa==true)
                    svetik[x, y] = -2;

                }
            } 
        }

        public void tah()
        {
          
            zjisti_pozici_pacmana();
            pohyb();
        }

        //následující metody nejsou moc zajímavé tak nerozbalovat !!!
























































































        private void najdi_cestu(int x, int y, int cislo)
        {
            try
            {
                if(svetik[x-1,y]==-1)
                {
                    svetik[x - 1, y] = cislo + 1;
                    najdi_cestu(x - 1, y, cislo + 1);
                }
            }
            catch (Exception)
            {
                
                throw;
            }
            try
            {
                if (svetik[x + 1, y] == -1)
                {
                    svetik[x + 1, y] = cislo + 1;
                    najdi_cestu(x + 1, y, cislo + 1);
                }
            }
            catch (Exception)
            {

                throw;
            }
            try
            {
                if (svetik[x, y+1] == -1)
                {
                    svetik[x , y+1] = cislo + 1;
                    najdi_cestu(x, y+1, cislo + 1);
                }
            }
            catch (Exception)
            {

                throw;
            }
            try
            {
                if (svetik[x , y-1] == -1)
                {
                    svetik[x , y-1] = cislo + 1;
                    najdi_cestu(x , y-1, cislo + 1);
                }
            }
            catch (Exception)
            {

                throw;
            }
            
        }
        private void zjisti_pozici_pacmana() //+ doplnění souřadnic
        {
            int pacx = World.pacman.poziceX();
            int pacy = World.pacman.poziceY();

            najdi_cestu(x, y, 0);

        }

        private void pohyb()
        {
            //jsme na stejném patře
            najdi_cestu(x, y, 0);
            if (World.pacman.poziceY() == y)
            {
                //pacman je vlevo
                if (World.pacman.poziceX() < x)
                {
                    if (svetik[x - 1, y] != -2)
                    x--;
                }
                    //pacman je vpravo
                else if (World.pacman.poziceX() > x)
                {
                    if (svetik[x + 1, y] != -2)
                    x++;
                }
            } //pokud nejsme na stejném patře
            else if(World.pacman.poziceY() != y)
            {
                // o patro nahoru
               
                if (World.pacman.poziceY() > y)
                {
                    if (svetik[x, y+ 1] == -2)
                    {

                        ArrayList seznamX = new ArrayList();
                        ArrayList seznamY = new ArrayList();
                        for (int i = 0; i < svetik.GetLength(0); i++)
                        {
                            if (svetik[i, y + 1] == -2)
                            {
                                seznamX.Add(i);
                                seznamY.Add(y + 1);

                            }


                        } ArrayList cesta = rozliseni_cest(seznamX, seznamY);
                        int index = nejvetsi(cesta);
                        stejne_patro_rozhodovani((int)seznamX[index]);

                    }
                    else { y++; }
                }
                // o patro nahoru
                else if (World.pacman.poziceY() < y)
                {
                    if(svetik[x,y-1] ==-2){

                        ArrayList seznamX = new ArrayList();
                        ArrayList seznamY = new ArrayList();
                        for (int i = 0; i < svetik.GetLength(0); i++)
                        {
                            if (svetik[i, y - 1] == -2)
                            {
                                seznamX.Add(i);
                                seznamY.Add(y - 1);

                            }


                        } ArrayList cesta = rozliseni_cest(seznamX, seznamY);
                        int index = nejvetsi(cesta);
                        stejne_patro_rozhodovani((int)seznamX[index]);

                    }
                    else { y--; }
                }
            }

          
           
           
        }
    private ArrayList rozliseni_cest(ArrayList x, ArrayList y)
        {
ArrayList vysledek = new ArrayList();
for (int i = 0; i < x.Capacity; i++)
{
    try
    {
        int cislo = (int)x[i] + this.x;
        cislo = (int)Math.Round(Math.Sqrt(cislo));
        vysledek.Add(cislo);
    }
    catch (Exception)
    {
        
       
    }
    
}
       
return vysledek;
        }
        private int  nejvetsi(ArrayList vstup)
    {
        int nejvetsi = 0;
        for (int i = 0; i < vstup.Count; i++)
        {
            for (int z = 0; z < vstup.Count; z++)
            {
                if ((int)vstup[z] < nejvetsi)
                { nejvetsi =(int) vstup[z]; }
            }
            if(nejvetsi == (int)vstup[i])
                return i;
        }
        return 0;


    }
        private void stejne_patro_rozhodovani( int _x)
        {
            //pacman je vlevo
            if (_x < x)
            {
                if(svetik[x-1,y]!=-2)
                x--;
            }
            //pacman je vpravo
            else if (_x > x)
            {
                if (svetik[x+1, y] != -2)
                x++;
            }
        }
    }
}
