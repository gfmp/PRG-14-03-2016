using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace pacman
{
    class Plocha
    {
        
        int delka_y = 40;
        int delka_x = 9;
        public int body = 0;
        public string[,] hraci_pole = new string[9, 40];




        public void zapisblik(int x, int y)

        {
            hraci_pole[x, y] = "1";
        }

        public void smazblik(int x, int y)//maze stary 
        {


            hraci_pole[x, y] = ".";


        }

        public void zapispac(int x, int y)//zobrazuje pacmana + pocita body
        {

            if (hraci_pole[x, y] == ".")
            {
                body++;
            }
            hraci_pole[x, y] = "0";
            

        }

        public void smazpac(int x, int y)//maze stary zaznampacmana
        {

            hraci_pole[x, y] = " ";


        }

        public bool kontrola(int x, int y)//kontroluje nabourani do zdi
        {
            if (hraci_pole[x, y] == "X")
            {
                return false;
            }
            return true;
        }




        public void vypis()//vykresluje pole
        {


            for (int i = 0; i < hraci_pole.GetLength(0); i++)
            {
                for (int j = 0; j < hraci_pole.GetLength(1); j++)
                {
                    Console.Write(hraci_pole[i, j]);
                }
                Console.WriteLine();
            }
        }


        public void napln()//naplnuje hraci plochu
        {
            for (int i = 0; i < hraci_pole.GetLength(0); i++)//vyplni cele pole X
            {
                for (int j = 0; j < hraci_pole.GetLength(1); j++)
                {
                    hraci_pole[i, j] = "X";
                }
            }

            for (int a = 1; a < hraci_pole.GetLength(1) - 1; a++)
            {
                hraci_pole[1,a] = ".";
            }

            hraci_pole[2,1] = ".";//treti radek
            hraci_pole[2, delka_y -2] = ".";
            hraci_pole[2, delka_y /2] = ".";

            for (int a = 1; a < hraci_pole.GetLength(1) - 1; a++)//ctvrty
            {
                hraci_pole[3, a] = ".";
            }

            hraci_pole[4, delka_y/ 3] = ".";//paty
            hraci_pole[4, 2 * (delka_y / 3)] = ".";

            for (int a = 1; a < hraci_pole.GetLength(1) - 1; a++)//sesty
            {
                hraci_pole[5, a] = ".";
            }

            hraci_pole[6, 1] = ".";//sedmy
            hraci_pole[6, delka_y - 2] = ".";
            hraci_pole[6, delka_y / 2] = ".";

            for (int a = 1; a < hraci_pole.GetLength(1) - 1; a++)//osmy
            {
                hraci_pole[7, a] = ".";
            }

            //using (StreamReader sr = new StreamReader("@test1.txt"))
            //{
            //    string s;
            //    while ((s = sr.ReadLine()) != null)
            //    {
            //        Console.WriteLine(s);

                   
            //            for (int j = 0; j < hraci_pole.GetLength(1); j++)
            //            {
            //                hraci_pole[j,] = s.Split();
            //            }
                        
                   


            //    }

            }




        }



    }

