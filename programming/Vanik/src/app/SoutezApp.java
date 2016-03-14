package app;

import java.io.IOException;

import com.googlecode.lanterna.terminal.Terminal;
import com.googlecode.lanterna.terminal.DefaultTerminalFactory;
import com.googlecode.lanterna.screen.Screen;
import com.googlecode.lanterna.screen.TerminalScreen;
import com.googlecode.lanterna.TextCharacter;
import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;


public class SoutezApp {

    public static void main(String[] args) throws IOException {
        Terminal terminal = new DefaultTerminalFactory().createTerminal();
    	Screen screen = new TerminalScreen(terminal);
        screen.startScreen();
        int skore = 0;

        boolean[][] pritomnost = new boolean [29][9];
        char[][] pole = new char [29][9];
        for (int i = 0; i < 29; i++) {
			for (int j = 0; j < 9; j++) {
				pole[i][j] = '.';
				screen.setCharacter(i, j, new TextCharacter(pole[i][j]));
				pritomnost[i][j] = false;
			}
		}
        for (int i = 0; i < 29; i++) {
			pole[i][0] = 'X';
			screen.setCharacter(i, 0, new TextCharacter(pole[i][0]));
			pole[i][8] = 'X';
			screen.setCharacter(i, 8, new TextCharacter(pole[i][8]));
		}
        for (int i = 0; i < 9; i++) {
			pole[0][i] = 'X';
			screen.setCharacter(0, i, new TextCharacter(pole[i][0]));
			pole[28][i] = 'X';
			screen.setCharacter(28, i, new TextCharacter(pole[i][8]));
		}
        for (int i = 0; i < 29; i++) {
			if (i != 1 && i != 14 && i!= 27) {
				pole[i][2] = 'X';
				screen.setCharacter(i, 2, new TextCharacter(pole[i][2]));
				pole[i][6] = 'X';
				screen.setCharacter(i, 6, new TextCharacter(pole[i][6]));

			}
		}
        for (int i = 0; i < 29; i++) {
			if (i != 7 && i != 19) {
				pole[i][4] = 'X';
				screen.setCharacter(i, 4, new TextCharacter(pole[i][4]));
			}
		}
        //vytvoøíme herní plochu 29*9, podminka pritomnost oznaèuje zda se Pacman na políèku nacházel
        screen.setCharacter(Packman.sloupec, Packman.radek, new TextCharacter(Packman.vzhled));
        screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(Blinky.vzhled));
        screen.refresh();
        // na hrní ploše si vytvoøíme Pacmana a Blinky
       boolean podminka = true;
       KeyStroke key;
       
       while (podminka) { // zde zaèíná hra
    	   if (Blinky.radek == Packman.radek && Blinky.sloupec == Packman.sloupec)  {
   			break;
   		}
    	if (pritomnost[Packman.sloupec][Packman.radek] == false) {
			skore++;
		}
    	pritomnost[Packman.sloupec][Packman.radek] = true;   
    	   screen.setCharacter(Packman.sloupec, Packman.radek, new TextCharacter(' '));
    	   key = screen.readInput();
    	   switch (key.getKeyType()) {// snímáme maèkání klávesnice
		case  ArrowUp:		
			if (pole[Packman.sloupec][Packman.radek - 1] == 'X') { // pacman nesmí procházet zdmi
				break;
			}
			Packman.radek--;		// hýbeme s Pacmanem	
			break;
		case ArrowDown:
			if (pole[Packman.sloupec][Packman.radek + 1] == 'X') {
				break;
			}
			Packman.radek++;
		break;
		case ArrowLeft:
			if (pole[Packman.sloupec - 1][Packman.radek] == 'X') {
				break;
			}
			Packman.sloupec--;
			break;
		case ArrowRight:
			if (pole[Packman.sloupec + 1][Packman.radek] == 'X') {
				break;
			}
			Packman.sloupec++;
			break;
		}
    	   screen.setCharacter(Packman.sloupec,Packman.radek ,new TextCharacter('0'));
    	   screen.refresh();
    	   int rozdilSloupcu = Blinky.sloupec - Packman.sloupec;
    	   int rozdilRadku = Blinky.radek - Packman.radek;
    	   boolean[] smer = new boolean[2];
    	   for (int i = 0; i < smer.length; i++) {
			smer[i] = true;
			// algoritmus pohybu mé blinky spoèívá v tom, že zkracuje nejdelší vzdálenost mezi ní a Pacmanem, bu vodorovnou, nebo svislou;
		}
    	   if (Math.abs(rozdilRadku)>=Math.abs(rozdilSloupcu)) {
			if (rozdilRadku >= 0) {
				if (pole[Blinky.sloupec][Blinky.radek - 1] !='X') { // ani blinky nemùže procházet zdmi
					if (pritomnost[Blinky.sloupec][Blinky.radek] == true) {     // blinky nemùže pøidávat teèky nebo je mazat, to co udìlá závisí jen na tom, zda tu packman byl
						screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(' '));
					}
					else screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter('.'));
					screen.setCharacter(Blinky.sloupec, Blinky.radek - 1, new TextCharacter('A'));
					Blinky.radek--;
				// premìòujeme znaky a také posuváme blinky
				}
				else smer[0] = false; // blinky se vždy musí pohybovat, proto s ní pak pohneme
			}
			
		}
    	   if (Math.abs(rozdilRadku)>=Math.abs(rozdilSloupcu)) {
   			if (rozdilRadku < 0) {
   				if (pole[Blinky.sloupec][Blinky.radek + 1] !='X') {
   					if (pritomnost[Blinky.sloupec][Blinky.radek] == true) {
						screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(' '));
					}
					else screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter('.'));
   					screen.setCharacter(Blinky.sloupec, Blinky.radek + 1, new TextCharacter('A'));
   					Blinky.radek++;
   				}
   				else smer[0] = false;
   			}
   			
   		}   
    	   if (Math.abs(rozdilRadku)<Math.abs(rozdilSloupcu)) {
   			if (rozdilSloupcu >= 0) {
   				if (pole[Blinky.sloupec - 1][Blinky.radek] !='X') {
   					if (pritomnost[Blinky.sloupec][Blinky.radek] == true) {
						screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(' '));
					}
					else screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter('.'));
   					screen.setCharacter(Blinky.sloupec - 1, Blinky.radek, new TextCharacter('A'));
   					Blinky.sloupec--;
   				}
   				else smer[1] = false;
   			}
   			
   		}  
    	   if (Math.abs(rozdilRadku)<Math.abs(rozdilSloupcu)) {
      			if (rozdilSloupcu < 0) {
      				if (pole[Blinky.sloupec + 1][Blinky.radek] !='X') {
      					if (pritomnost[Blinky.sloupec][Blinky.radek] == true) {
    						screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(' '));
    					}
    					else screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter('.'));
      					screen.setCharacter(Blinky.sloupec + 1, Blinky.radek, new TextCharacter('A'));
      					Blinky.sloupec++;
      				}
      				else smer[1] = false;
      			}
      			
      		} 
    	   
    	   if (smer[0] == false && rozdilSloupcu >= 0) { // v tìchto pøípadech se Blinky nehnula, a tak s ní nepohneme v nejdelší vzdálenosti, ale v té druhé
    			if (pritomnost[Blinky.sloupec][Blinky.radek] == true) {
					screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(' '));
				}
				else screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter('.'));
				screen.setCharacter(Blinky.sloupec - 1, Blinky.radek, new TextCharacter('A'));
				Blinky.sloupec--;
		}
    	   if (smer[0] == false && rozdilSloupcu < 0) {
    			if (pritomnost[Blinky.sloupec][Blinky.radek] == true) {
					screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(' '));
				}
				else screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter('.'));
    			screen.setCharacter(Blinky.sloupec + 1, Blinky.radek, new TextCharacter('A'));
					Blinky.sloupec++;
		}
    	   
    	   if (smer[1] == false && rozdilRadku >= 0) {
    			if (pritomnost[Blinky.sloupec][Blinky.radek] == true) {
					screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(' '));
				}
				else screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter('.'));
    			screen.setCharacter(Blinky.sloupec, Blinky.radek - 1, new TextCharacter('A'));
				Blinky.radek--;
		}    
    	  if (smer[1] == false && rozdilRadku < 0) {
    			if (pritomnost[Blinky.sloupec][Blinky.radek] == true) {
					screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(' '));
				}
				else screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter('.'));
    			screen.setCharacter(Blinky.sloupec, Blinky.radek + 1, new TextCharacter('A'));
					Blinky.radek++;
					
		} 
    	
    	   screen.refresh(); // zobrazíme zmìny
    	   
    	   
    	   if (skore==115) {
			System.out.println("Vyhrál jsi");
			break;
		}
    	   
    	   if (Blinky.radek == Packman.radek && Blinky.sloupec == Packman.sloupec)  {
    	       System.out.println("Prohrál jsi se skorem" + skore);
			break;// pokud se shodují pozice Pacmana a Blinky hráè prohrál
		}
       	}

        
        screen.readInput();
        screen.stopScreen();
    }

}