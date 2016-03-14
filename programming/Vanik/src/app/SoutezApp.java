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
        //vytvo��me hern� plochu 29*9, podminka pritomnost ozna�uje zda se Pacman na pol��ku nach�zel
        screen.setCharacter(Packman.sloupec, Packman.radek, new TextCharacter(Packman.vzhled));
        screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(Blinky.vzhled));
        screen.refresh();
        // na hrn� plo�e si vytvo��me Pacmana a Blinky
       boolean podminka = true;
       KeyStroke key;
       
       while (podminka) { // zde za��n� hra
    	   if (Blinky.radek == Packman.radek && Blinky.sloupec == Packman.sloupec)  {
   			break;
   		}
    	if (pritomnost[Packman.sloupec][Packman.radek] == false) {
			skore++;
		}
    	pritomnost[Packman.sloupec][Packman.radek] = true;   
    	   screen.setCharacter(Packman.sloupec, Packman.radek, new TextCharacter(' '));
    	   key = screen.readInput();
    	   switch (key.getKeyType()) {// sn�m�me ma�k�n� kl�vesnice
		case  ArrowUp:		
			if (pole[Packman.sloupec][Packman.radek - 1] == 'X') { // pacman nesm� proch�zet zdmi
				break;
			}
			Packman.radek--;		// h�beme s Pacmanem	
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
			// algoritmus pohybu m� blinky spo��v� v tom, �e zkracuje nejdel�� vzd�lenost mezi n� a Pacmanem, bu� vodorovnou, nebo svislou;
		}
    	   if (Math.abs(rozdilRadku)>=Math.abs(rozdilSloupcu)) {
			if (rozdilRadku >= 0) {
				if (pole[Blinky.sloupec][Blinky.radek - 1] !='X') { // ani blinky nem��e proch�zet zdmi
					if (pritomnost[Blinky.sloupec][Blinky.radek] == true) {     // blinky nem��e p�id�vat te�ky nebo je mazat, to co ud�l� z�vis� jen na tom, zda tu packman byl
						screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter(' '));
					}
					else screen.setCharacter(Blinky.sloupec, Blinky.radek, new TextCharacter('.'));
					screen.setCharacter(Blinky.sloupec, Blinky.radek - 1, new TextCharacter('A'));
					Blinky.radek--;
				// prem��ujeme znaky a tak� posuv�me blinky
				}
				else smer[0] = false; // blinky se v�dy mus� pohybovat, proto s n� pak pohneme
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
    	   
    	   if (smer[0] == false && rozdilSloupcu >= 0) { // v t�chto p��padech se Blinky nehnula, a tak s n� nepohneme v nejdel�� vzd�lenosti, ale v t� druh�
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
    	
    	   screen.refresh(); // zobraz�me zm�ny
    	   
    	   
    	   if (skore==115) {
			System.out.println("Vyhr�l jsi");
			break;
		}
    	   
    	   if (Blinky.radek == Packman.radek && Blinky.sloupec == Packman.sloupec)  {
    	       System.out.println("Prohr�l jsi se skorem" + skore);
			break;// pokud se shoduj� pozice Pacmana a Blinky hr�� prohr�l
		}
       	}

        
        screen.readInput();
        screen.stopScreen();
    }

}