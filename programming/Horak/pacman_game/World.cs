using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;
using System.Threading.Tasks;

namespace pacman_game
{
  class World
    { Timer casovac;
      DateTime cas = new DateTime(1, 1, 1, 0, 0, 0);
     public static Bunka[,] sachovnice = new Bunka[30, 10]; // neměnit nebo to padne - mapa nepujde vytvořit !
      public static Pacman pacman = new Pacman(15,3);
      public Blink blinky;
      public Ink inky;
      private int pocet_bodu_zbyva=0;
      //System.Threading.Thread vlakno =new System.Threading.Thread()
      static int velikostX, velikostY;
      public World()
      {
          velikostX = sachovnice.GetLength(0);
          velikostY = sachovnice.GetLength(1);
          tvorba_bunek();
          tvorba_bodu();
          tvorba_zdi();
          Console.Clear();
        blinky = new Blink(1, 1);
          inky= new Ink(0, 0);
        // timerTimer();
          do
          {
              tah();
              blinky.tah();
             // inky.tah();
              cas = cas.AddSeconds(1);
          } while (true);
         
              
      }
      private void tvorba_bunek() // naplní šachovnici
      {
          for (int x = 0; x < sachovnice.GetLength(0); x++)
          {
              for (int y = 0; y < sachovnice.GetLength(1); y++)
              {
                  Bunka nova = new Bunka();
                  sachovnice[x, y] = nova;
                
              }
          }
      }
      private void tvorba_zdi()
      {
          try
          {
              for (int x = 0; x < sachovnice.GetLength(0); x++)
              {
                  sachovnice[x, 0].tvorba_zed();

              }
              for (int x = 0; x < sachovnice.GetLength(0); x++)
              {
                  sachovnice[x, 9].tvorba_zed();

              }
              for (int x = 0; x < sachovnice.GetLength(0); x++)
              {
                  if (x != 1 && x != 13 && x != 28)
                      sachovnice[x, 2].tvorba_zed();

              }
              for (int x = 0; x < sachovnice.GetLength(0); x++)
              {
                  if (x != 7 && x != 21)
                      sachovnice[x, 4].tvorba_zed();

              }
              for (int x = 0; x < sachovnice.GetLength(0); x++)
              {
                  if (x != 1 && x != 13 && x != 28)
                      sachovnice[x, 6].tvorba_zed();

              }
              for (int x = 0; x < sachovnice.GetLength(0); x++)
              {
                  sachovnice[x, 8].tvorba_zed();

              }
              for (int y = 0; y < sachovnice.GetLength(1); y++)
              {
                  sachovnice[0, y].tvorba_zed();

              }
              for (int y = 0; y < sachovnice.GetLength(1); y++)
              {
                  sachovnice[29, y].tvorba_zed();

              }
          }
          catch (Exception)
          {

              Console.WriteLine("! změnili jste velikost světa !! to jste neměli !");
              System.Environment.Exit(0);
          }
         

      }
      private void tvorba_bodu()
      {
          foreach (Bunka item in sachovnice)
          {
              if(item.je_tu_zed()==false)
              {
                  item.tvorba_bodu();
                  pocet_bodu_zbyva++;
              }
            
          }
          sachovnice[pacman.poziceX(), pacman.poziceY()].sebrani_bodu();
           pocet_bodu_zbyva--;
      }
      
      private void vypis()
      {
         Console.Clear();

          for (int y = 0; y < sachovnice.GetLength(1) - 1; y++)
               {
                   for (int x = 0; x < sachovnice.GetLength(0); x++)
                   {

                   if(sachovnice[x,y].je_tu_zed()==true)
          
                   {  Console.ForegroundColor = ConsoleColor.Gray;
                     Console.Write("X");
          
                   }
                   else if (blinky.poziceX() ==x && blinky.poziceY() == y)
                   {
                       Console.ForegroundColor = ConsoleColor.Red
;
                       Console.Write(".");

                   }
                   else if (inky.poziceX() == x && inky.poziceY() == y)
                   {
                       Console.ForegroundColor = ConsoleColor.Blue;
;
                       Console.Write(".");

                   }
                   else if (pacman.poziceX() == x && pacman.poziceY() == y)
                   {
                       Console.ForegroundColor = ConsoleColor.Yellow;
                       Console.Write(".");

                   }
                   else if (sachovnice[x, y].je_tu_bod() == true)
                   {
                       Console.ForegroundColor = ConsoleColor.White;
                       Console.Write(".");

                   }
               
                   else
                   {
                       Console.ForegroundColor = ConsoleColor.Black;
                       Console.Write(" ");
                   }
          }
               Console.WriteLine();
             
          }
          Console.WriteLine("Počet bodů : {0}  zbývá:{1}   Počet životů : {2}", pacman.pocet_bodu(), (pocet_bodu_zbyva-180), pacman.pocet_zivotu());
          Console.WriteLine(" čas :" + cas.Hour +":"+cas.Minute+":"+cas.Second);
      }
      private void pacman_pohyb()
      {
          char klavesa = Console.ReadKey().KeyChar;     
          if(klavesa !='p')
        pacman.pohyb(klavesa);
          else
          {
            //  timer_stop();
          }
     
      }
      private void kontrola()
      {
          kontrola_pacmana_a_ghostu();
          kontrola_poctu_zivotu();
          kontrola_pacman_bod();
          kontrola_poctu_bodu();
          
      }
      private void kontrola_pacman_bod()
      {
          if(sachovnice[pacman.poziceX(),pacman.poziceY()].je_tu_bod()==true)
          {
              sachovnice[pacman.poziceX(), pacman.poziceY()].sebrani_bodu();
              pacman.pridej_bod();
              pocet_bodu_zbyva--;
          }
      }
      private void kontrola_pacmana_a_ghostu()
      {
      if (blinky.poziceX() == pacman.poziceX() && blinky.poziceY() == pacman.poziceY())
      {
          pacman.zemrel();
      }
      else if (inky.poziceX() == pacman.poziceX() && inky.poziceY() == pacman.poziceY())
      {
          pacman.zemrel();
      }

      }
      private void kontrola_poctu_bodu()
      {
          if(pocet_bodu_zbyva==180)
          {
              Console.WriteLine();
              Console.WriteLine("vyhráli jste");
              System.Environment.Exit(0);
          }
      }
  private void kontrola_poctu_zivotu()
      {
          if (pacman.pocet_zivotu() == 0)
          {
              Console.WriteLine();
              Console.WriteLine("Prohráli jste");
              System.Environment.Exit(0);
          }
      }
private  void timerTimer()
{
   casovac = new Timer(1000);
    casovac.AutoReset = true;
    casovac.Elapsed += new System.Timers.ElapsedEventHandler(timeaction);
    casovac.Start();
    
}
 private void timeaction ( object sender, System.Timers.ElapsedEventArgs e)
{
    cas = cas.AddSeconds(1);
   
    tah();
  
     

}
    private  void tah()
    {
        vypis();
        pacman_pohyb();


        blinky.tah();
                kontrola();
        // inky.tah();
    }
      private void timer_stop()
      {
          casovac.Stop();
          char klavesa;
          do
          { klavesa = Console.ReadKey().KeyChar;
          if (klavesa != 'p')
              timer_start();
              
          } while (klavesa !='p');
      }
        private void timer_start()
      {
          casovac.Start();
      }
}
}
