using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Timers;

namespace pacman
{





    class Program
    {
        static int zadej()
        {


            try
            {
                int zadej = Int32.Parse(Console.ReadLine());
                return zadej;
            }
            catch (Exception)
            {

                zadej();
                return 0;

            }
        }






        static void Main(string[] args)
        {

            Pacman pacman = new Pacman(1,1);
            Plocha plocha = new Plocha();
            Blinky blinky = new Blinky(8, 3);

            

            plocha.napln();







            while(true)
            {

                plocha.zapispac(pacman.x, pacman.y);
                Console.WriteLine("body:" + plocha.body);
                plocha.vypis();
                plocha.smazpac(pacman.x, pacman.y);
                plocha.smazblik(blinky.x, blinky.y);
                pacman.zatoc(zadej());

                if (!plocha.kontrola(pacman.x, pacman.y))//kontroluje naraz do zdi
                    pacman.vrat();

                blinky.tmp = true;
                blinky.najdiPac(pacman.x, pacman.y);
                if (!plocha.kontrola(blinky.x, blinky.y))//kontroluje naraz do zdi blinka
                {
                    blinky.vrat();
                    blinky.tmp = false;
                    blinky.najdiPac(pacman.x, pacman.y);
                }
                plocha.smazblik(blinky.x, blinky.y);
                plocha.zapisblik(blinky.x, blinky.y);

                if (blinky.x == pacman.x && blinky.y == pacman.y)//ukoncuje hru
                {
                    break;
                }
                
                    
                
                

                
                
                

                Console.Clear();
                
            }

            Console.Clear();
            Console.WriteLine("GAME OVER");

            Console.ReadKey();


           


            


        }
    }
}
