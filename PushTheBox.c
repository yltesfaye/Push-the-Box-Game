#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
//ctrl + backslash
//raw mode

/*Important: application is compiler specific. Works on Putty's Compiler */

char gb[10][10] = {

	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', '#', ' ', '+', ' ', ' ', 'D', ' ', ' ', '#'},
	{'#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}


};


char gb2[10][10] = {

	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', ' ', ' ', '#', '#', '#', '#', '#', '#', '#'},
	{'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', 'D', ' ', ' ', 'D', ' ', ' ', '#'},
	{'#', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#'},
	{'#', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', '+', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', '#', '#', '#', '#', ' ', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '+', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

char gb3[10][10] = {

	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '+', '#', '#', '#', '#'},
	{'#', '#', ' ', ' ', '#', ' ', '#', '#', '#', '#'},
	{'#', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', '#'},
	{'#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#'},
	{'#', ' ', '#', '+', ' ', ' ', '#', '#', '#', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
};

int t = 0;
int tries = 0;
int px;
int py;
int running; 
char dir;


void render(int ans);

char quickchar(float delay) {

	int flags;
	char c;

	usleep((int)(delay * 1000000));

	flags = fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
	c = getchar();
	fcntl(0, F_SETFL, flags ^ O_NONBLOCK);

	return c;

}

int main() {

	printf("\e[31;1m");
	printf(" ,------.                ,--.           ,--.  ,--.                ,-----.                   \r\n");
	printf(" |  .--. ',--.,--. ,---. |  ,---.     ,-'  '-.|  ,---.  ,---.     |  |) /_  ,---.,--.  ,--. \r\n");
	printf(" |  '--' ||  ||  |(  .-' |  .-.  |    '-.  .-'|  .-.  || .-. :    |  .-.  || .-. ||  `'  /  \r\n"); 
	printf(" |  | --' '  ''  '.-'  `)|  | |  |      |  |  |  | |  ||   --.    |  '--' /' '-' '/  /.  |  \r\n");
	printf(" `---'      `--'  `----' `--' `--'      `--'  `--' `--' `----'    `------' `----'`---''---'  \r\n");
	printf("\e[0m");

	printf("\e[36;2m");
	printf("\r\n\tInstructions: \r\n");
	printf("  Your charcter is the @ sign. Your mission is to push the 'D' box to the '+' sign.\r\n");
	printf("  Use 'w a s d' to move\r\n");
	printf("  You only have 10 seconds to complete each level. You could try play again if you lose a round except one.\r\n");
	printf("  You only have one shot for the Advanced level. Good Luck Cadet!\r\n");
	printf("\e[0m");
	
	int ans;
	
	printf("\e[35;3m");
	printf("\r\n  Choose a level:\r\n");
	printf("\t  1. Beginner\r\n");
	printf("\t  2. Intermediate\r\n");
	printf("\t  3. Advanced \r\n\n");
	/*printf("\t4. IMPOSSIBLE(coming soon) \r\n");*/
	printf("  Your choice: ");
	scanf("%d", &ans);
	printf("\e[0m");
	
	int re;

	if(ans == 1) {

/*while(re == 1 & ans == 1) {*/

		px = 8;
    	py = 2;

		running = 1;

	system("stty -echo raw"	);



	while(running == 1 ) {
		
		render(ans);
	

        if (dir == 'w' && gb[py][px] == 'D' && gb[py-1][px] != '#') {
            gb[py][px] = ' ';
			gb[py-1][px] = 'D';
		} else if(dir == 'a' && gb[py][px] == 'D' && gb[py][px-1] != '#') {
            gb[py][px] = ' ';
			gb[py][px-1] = 'D';
		} else if(dir == 's' && gb[py][px] == 'D' && gb[py+1][px] != '#') {
            gb[py][px] = ' ';
			gb[py+1][px] = 'D';
		} else if(dir == 'd' && gb[py][px] == 'D' && gb[py][px+1] != '#') {
            gb[py][px] = ' ';
			gb[py][px+1] = 'D';

        }
        
        int x,y;

		dir  = quickchar(0.01);
		t++;
		
	



		if (dir == 'w' && gb[py-1][px] != '#') {
				py--;
		} else if(dir == 'a' && gb[py][px-1] != '#') {
				px--;
		} else if(dir == 's' && gb[py + 1][px] != '#') {
				py++;
		} else if(dir == 'd' && gb[py][px + 1] != '#') {
				px++;
		} else if(dir == 'q') {
				running = 0;
		}


		if(t/100 >= 10 && ans == 1) {

		   system("clear");
		   printf("\e[31;1m");
		   printf("\r\n");
		   printf("\tYOU LOST!!!\r\n");
		   printf("\r\n");
		   
	
		  printf(" Do you want to play again? 1 - for Yes, 2 - for No: ");
		 scanf("%d", &re);

		  printf("\e[0m");



		   if(re == 1) {

			   int i,j;
			   for(j = 0; j <= 10; j++) {
				   for(i = 0; i <= 10; i++) {
					   if(gb[j][i] != '#') {
						   gb[j][i] = ' ';
						   gb[3][3] = '+';
						   gb[3][6] = 'D';
						   px = 8;
    					   py = 2;
					   }
				   }
			   }
                t = 0;
                px = 8;
    	        py = 2;
			    ans = 1;
				

		   } else {
			    break;
			    return 0;
		   }		   
		  
	   } else if(gb[3][3] == 'D') {


            gb[3][3] = 'D';
            

			system("clear");

			printf("\e[32;7m");
            printf("\r\n\t Congrats! You won the 1st Round!!\r\n\n");
			printf("\e[0m");

			
			break;
			return 0;
		}
			
		}

	} else if(ans == 2) {

		py = 3;
    	px = 5;
		
	running = 1;

	system("stty -echo raw"	);


	while(running == 1) {
		
		render(ans);
		
		/*if(gb[py][px] == 'D') {
			
			gb[py][px] = ' ';
			gb[py][px-1] = 'D'; */

        if (dir == 'w' && gb2[py][px] == 'D' && gb2[py-1][px] != '#' && gb2[py-1][px] != 'D') {
            gb2[py][px] = ' ';
			gb2[py-1][px] = 'D';
		} else if(dir == 'a' && gb2[py][px] == 'D' && gb2[py][px-1] != '#' && gb2[py-1][px] != 'D') {
            gb2[py][px] = ' ';
			gb2[py][px-1] = 'D';
		} else if(dir == 's' && gb2[py][px] == 'D' && gb2[py+1][px] != '#' && gb2[py-1][px] != 'D') {
            gb2[py][px] = ' ';
			gb2[py+1][px] = 'D';
		} else if(dir == 'd' && gb2[py][px] == 'D' && gb2[py][px+1] != '#' && gb2[py-1][px] != 'D') {
            gb2[py][px] = ' ';
			gb2[py][px+1] = 'D';

        }
        
        int x,y;

		dir  = quickchar(0.01);
		t++;

	   if(t/100 >= 10 && ans == 2) {

		   system("clear");

			
		   printf("\r\n");
		   printf("\e[31;1m");
		   printf("\tYOU LOST!!!\r\n");
		   printf("\r\n");
		   
		   
		  printf(" Do you want to play again? 1 - for Yes, 2 - for No: ");	
		  scanf("%d", &re);
		
		  printf("\e[0m");

		   scanf("%d", &re);

		   if(re == 1) {
			   	py = 3;
    			px = 5;
		
               int i,j;
			   for(j = 0; j <= 10; j++) {
				   for(i = 0; i <= 10; i++) {
					   if(gb2[j][i] != '#') {

						   gb2[j][i] = ' ';
						   gb2[6][1] = '+';
						   gb2[3][3] = 'D';
						   gb2[3][6] = 'D';
						   gb2[8][5] = '+';
						 
					   }
				   }
			   }
                t = 0;
			    ans = 2;
				

		   } else {
			    break;
			    return 0;
		   }		 
        } else if(gb2[6][1] == 'D' && gb2[8][5] == 'D') {

           char a;

            gb2[6][1] = 'D';
			gb2[8][5] = 'D';
            render(ans);

			system("clear");

			printf("\e[32;7m");
            printf("\r\n\t You survived the second level! Mildly Impressive!\r\n\n");
			printf("\e[0m");
    

           break;
     
	}

		if (dir == 'w' && gb2[py-1][px] != '#') {
				py--;
		} else if(dir == 'a' && gb2[py][px-1] != '#') {
				px--;
		} else if(dir == 's' && gb2[py + 1][px] != '#') {
				py++;
		} else if(dir == 'd' && gb2[py][px + 1] != '#') {
				px++;
		} else if(dir == 'q') {
				running = 0;
		}
	}


	}  else if(ans == 3) {

		py = 3;
    	px = 7;

		running = 1;

	system("stty -echo raw"	);


	while(running == 1) {
		
		
		render(ans);
	
        if (dir == 'w' && gb3[py][px] == 'D' && gb3[py-1][px] != '#') {
            gb3[py][px] = ' ';
			gb3[py-1][px] = 'D';
		} else if(dir == 'a' && gb3[py][px] == 'D' && gb3[py][px-1] != '#') {
            gb3[py][px] = ' ';
			gb3[py][px-1] = 'D';
		} else if(dir == 's' && gb3[py][px] == 'D' && gb3[py+1][px] != '#') {
            gb3[py][px] = ' ';
			gb3[py+1][px] = 'D';
		} else if(dir == 'd' && gb3[py][px] == 'D' && gb3[py][px+1] != '#') {
            gb3[py][px] = ' ';
			gb3[py][px+1] = 'D';
        } 

        int x,y;

		dir  = quickchar(0.01);
		t++;

      if(t/100 >= 10 && ans == 3) {
		   system("clear");

		  
		   printf("\r\n");
		    printf("\e[31;1m");
		   printf("\t YOU LOST!!!\r\n");
		   printf("\r\n");
			printf("\e[0m");
			
			    break;
			    return 0;

        }else if(gb3[1][5] == 'D' & gb3[7][3] == ' ') {

           char a;

            gb3[7][3] = ' ';
			gb3[1][5] = 'D';
            

			system("clear");

			printf("\e[32;7m");
            printf("\r\n\t You have made it to the top Sergeant! \n");
			printf("\n Your skills are beyond IMPRESSIVE! \r\n\n");
			printf("\e[0m");


			system("stty echo -raw");
			break;

		
       }


		if (dir == 'w' && gb3[py-1][px] != '#') {
				py--;
		} else if(dir == 'a' && gb3[py][px-1] != '#') {
				px--;
		} else if(dir == 's' && gb3[py + 1][px] != '#') {
				py++;
		} else if(dir == 'd' && gb3[py][px + 1] != '#') {
				px++;
		} else if(dir == 'q') {
				running = 0;
		}

	
	}
	}

}

void render(int ans) {
    
	int x, y;
	
	system("clear");


	if(t/100 < 10) {
	printf("\e[33;1m Time: %d \r\n\e[0m", 10 - t/100);
	printf("\r\n");
	}	

	for(y=0; y<10; y++) {
		
		printf("\t");
		for(x=0; x<10; x++) {
         
		 if(ans == 1) {

		if(y == py && x == px) {
			printf("\e[35;1m@\e[0m");
		} else if(gb[y][x] == '+'){
			printf("\e[31;1m");
			printf("%c", gb[y][x]);
			printf("\e[0m");
		} else if(gb[y][x] == '#'){
			printf("\e[32;7m");
			printf("%c", gb[y][x]);
			printf("\e[0m");
		} else {
			printf("%c", gb[y][x]);
		}

		} else if(ans == 2) {

			if(y == py && x == px) {
			printf("\e[35;1m@\e[0m");
		} else if(gb2[y][x] == '+'){
			printf("\e[31;1m");
			printf("%c", gb2[y][x]);
			printf("\e[0m");
		} else if(gb2[y][x] == '#'){
			printf("\e[32;7m");
			printf("%c", gb2[y][x]);
			printf("\e[0m");
		} else {
			printf("%c", gb2[y][x]);
		}

		} else if(ans == 3) {

			if(y == py && x == px) {
			printf("\e[35;1m@\e[0m");
		} else if(gb3[y][x] == '+'){
			printf("\e[31;1m");
			printf("%c", gb3[y][x]);
			printf("\e[0m");
		} else if(gb3[y][x] == '#'){
			printf("\e[32;7m");
			printf("%c", gb3[y][x]);
			printf("\e[0m");
		}  else {
			printf("%c", gb3[y][x]);
		}

		}
	}

		printf("\r\n");
    }

}

