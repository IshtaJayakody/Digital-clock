#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define TC_NRM "\x1B[0m"    //terminal letter color to normal

#define TC_BLACK "\x1B[30m" //terminal letter colour to black
#define TC_RED "\x1B[31m" //terminal letter color to red
#define TC_GREEN "\x1B[32m" //terminal letter colour to green
#define TC_YELLOW "\x1B[33m" //terminal letter colour to yellow
#define TC_BLUE "\x1B[34m" //terminal letter colour to blue
#define TC_MAGENTA "\x1B[35m" //terminal letter colour to magenta
#define TC_CYAN "\x1B[36m" //terminal letter colour to cyan
#define TC_WHITE "\x1B[37m" //terminal letter colour to white

#define TC_B_BLACK "\x1B[40m" //terminal letter backgrount color to black
#define TC_B_RED "\x1B[41m" //terminal letter backgrount color to red
#define TC_B_GREEN "\x1B[42m" //terminal letter backgrount color to green
#define TC_B_YELLOW "\x1B[43m" //terminal letter backgrount color to yellow
#define TC_B_BLUE "\x1B[44m" //terminal letter backgrount color to blue
#define TC_B_MAGENTA "\x1B[45m" //terminal letter backgrount color to magenta
#define TC_B_CYAN "\x1B[46m" //terminal letter backgrount color to cyan
#define TC_B_WHITE "\x1B[47m" //terminal letter backgrount color to white

#define T_save_screen() printf("\e[?47h") //to save the screen
#define T_restore_screen() printf("\e[?47l") //to restore the screen
#define T_clear_scrn() printf("\x1B[2J") //clear screen
#define T_hide_cursor() printf("\e[?25l") //hide the cursor 
#define T_normal_cursor() printf("\e[?25h")//to re-enable the cursor

#define T_move_cursor(X,Y) printf("\033[%d;%dH",X,Y) //move cursor x,y coordinates
#define T_up(X) printf("\033[%dA",X) //move cursor up x times
#define T_down(X) printf("\033[%dB",X) //move cursor down x times
#define T_right(X) printf("\033[%dC",X) //move the cursor right x times
#define T_left(X) printf("\033[%dD",X) //move the cursor left x times
#define T_restore() printf("\033[u") //restore cursor position

//while running the code not to  disabletyping if we press any key
#define DONT_TYPE "\
	stty -echo  \n\
	"

//after running the code to enable  typing if we press any key
#define DO_TYPE "\
	stty echo \n\
	"




// FOR THE TIME MANIPULATIONS
char* timeToString( char stringT[]  ) ;
char* getTime(char stringT[] , char time[] ) ;
char* monthToNumber(char stringMonth[],char stringT[]) ;
char* getDate(char date[],char stringT[],char stringMonth[]) ;
int S_check(char s1[],char s2[]) ;//to check two strings are equal without considering case 
char color_check(char s[]) ; //to get the color
int SF_check(char s1[],char s2[]) ; //to check two strings are equal considering case 
char flag_check(char s[]) ; // to get the flag 'C'->"-c"  'H'->"-h" 'Z'-> not any two
char special_color_check(char s[]) ;//to filter -cCOLOR



// FOR THE TERMINAL GRAPHICS MANIPULATION
void Pbox(char c) ;
void Pspace() ;
void Pzero(char c) ;
void Pone(char c) ;
void Ptwo(char c) ; 
void Pthree(char c) ; 
void Pfour(char c) ; 
void Pfive(char c) ; 
void Psix(char c) ; 
void Pseven(char c) ; 
void Peight(char c) ; 
void Pnine(char c) ;
void Pcolun(char c) ;
void Pgap() ;
void Psymbol(char a,char c) ;
void Ptime(char time[],char c) ;
void Pdate(char date[],char c) ;


//TO HANDLE SIGNAL CTRL+C
void SignalHandle(int i) ;

int main(int argc , char **argv) {

	

	
	//getting the current time date month year to string
	time_t rawT ;
	char stringT[50] ;
	char t1[10] ;
	char stringMonth[3];
	char date[11] ;
	
	int wrongFlagCheck ;
	int cPos =0;
	int sp_Pos =0 ;
	int c=0 , l;



	

	if(argc==1 || (argc==2 && flag_check(argv[1])=='Z') ){

	
		T_hide_cursor() ;
		T_save_screen() ;
		T_clear_scrn();
		T_move_cursor(2,2) ;
		system(DONT_TYPE) ;
		signal(SIGINT, SignalHandle) ;

		while(1){
			
			time(&rawT) ;
			timeToString(stringT) ;
			getTime(stringT , t1) ;

			monthToNumber(stringMonth,stringT) ;
			getDate(date , stringT , stringMonth ) ;

			Ptime(t1,'w') ;
			

			T_down(6) ;
			T_right(21) ;

			Pdate(date,'w') ;
			

		}


	}else if(argc==2 && flag_check(argv[1])=='H'){

		
	
		printf("usage : clock -h                quick help on cmd\n") ;
		printf("usage : clock -c <color>        print clock with a color\n") ;
		printf("<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
		return 1;
	}else if(argc>=2 ){
	

		for(wrongFlagCheck=1 ; wrongFlagCheck < argc ; wrongFlagCheck++ ){
		
			if(flag_check(argv[wrongFlagCheck])=='X' || ( flag_check(argv[argc-1])=='C'&& flag_check(argv[argc-2])!='C' )){
			
				 printf("Invalid use of arguments.\n") ;
				 printf("usage : clock -h                quick help on cmd\n") ;
				 printf("usage : clock -c <color>        print clock with a color\n") ;

				 return 1;
			}

			if(flag_check(argv[wrongFlagCheck])=='H' && flag_check(argv[wrongFlagCheck-1])!='C'){
			
				printf("usage : clock -h                quick help on cmd\n") ;
                        	printf("usage : clock -c <color>        print clock with a color\n") ;
                        	printf("<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");


                       		return 1 ;
			}

			if(flag_check(argv[wrongFlagCheck])=='C'){
				
				cPos = wrongFlagCheck ;	

			}else if(special_color_check(argv[wrongFlagCheck])!='z'){
			
				sp_Pos = wrongFlagCheck ;
			}
		}



		if(flag_check(argv[cPos])=='C'&& flag_check(argv[cPos-1])=='C' ){

				for(l=cPos ; flag_check(argv[l]) == 'C' ; l-- ){
				
					c++ ;
				} 
		
				if(c%2==0){
					printf("%s :This is not a valid color, Please enter one of these colours: ",argv[cPos]) ;
                                	printf("black, red, green, yellow, blue, magenta, cyan, white \n") ;
					

                                
                               		 return 1;
				}else{
				
					printf("Invalid use of arguments.\n") ;
	                		printf("usage : clock -h                quick help on cmd\n") ;
        		        	printf("usage : clock -c <color>        print clock with a color\n") ;

                			return 1 ;

				}
		}
		
		if((cPos +1) >= sp_Pos && argc>2){
		
			if(color_check(argv[cPos+1])!='z'){
			
				T_save_screen() ;
                		T_clear_scrn();
              			T_move_cursor(2,2) ;
                		system(DONT_TYPE) ;
                		signal(SIGINT, SignalHandle) ;
                		T_hide_cursor() ;

                		while(1){


                        		time(&rawT) ;
                        		timeToString(stringT) ;
                       		 	getTime(stringT , t1) ;

                        		monthToNumber(stringMonth,stringT) ;
                      		  	getDate(date , stringT , stringMonth ) ;

		
                	        	Ptime(t1,color_check(argv[cPos+1])) ;

	
        	                	T_down(6) ;
                	        	T_right(21) ;

	
        	                	Pdate(date,color_check(argv[cPos+1])) ;

                		}
			}else if(cPos==sp_Pos){
			
				T_save_screen() ;
                                T_clear_scrn();
                                T_move_cursor(2,2) ;
                                system(DONT_TYPE) ;
                                signal(SIGINT, SignalHandle) ;
                                T_hide_cursor() ;

                                while(1){


                                        time(&rawT) ;
                                        timeToString(stringT) ;
                                        getTime(stringT , t1) ;

                                        monthToNumber(stringMonth,stringT) ;
                                        getDate(date , stringT , stringMonth ) ;


                                        Ptime(t1,'w') ;


                                        T_down(6) ;
                                        T_right(21) ;


                                        Pdate(date,'w') ;
				}

			}else{
			
				printf("%s :This is not a valid color, Please enter one of these colours: ",argv[cPos+1]) ;
                		printf("black, red, green, yellow, blue, magenta, cyan, white \n") ;

				
                		return 1;
			}
			
		}else{
		
			T_save_screen() ;
                	T_clear_scrn();
                	T_move_cursor(2,2) ;
                	system(DONT_TYPE) ;
                	signal(SIGINT, SignalHandle) ;
                	T_hide_cursor() ;

                	while(1){


                        	time(&rawT) ;
                        	timeToString(stringT) ;
                        	getTime(stringT , t1) ;

                        	monthToNumber(stringMonth,stringT) ;
                        	getDate(date , stringT , stringMonth ) ;


                        	Ptime(t1,special_color_check(argv[sp_Pos])) ;


                        	T_down(6) ;
                        	T_right(21) ;


                        	Pdate(date,special_color_check(argv[sp_Pos])) ;

                	}
		}

	}
		


		
	

	return 0;
}


//part 1 time to string
char* timeToString( char stringT[] ) {
	
	time_t rawT ;

	time(&rawT) ;

        int i ;

	for(i=0 ; ctime(&rawT)[i]!='\0' ; i++){

                stringT[i]=ctime(&rawT)[i] ;
        }
        stringT[i-1] = '\0' ;

	return stringT;

}

//part 2 getting the time
char* getTime(char stringT[] , char time[] ) {

	int i=0 ;
	int j ; 
	for(j=11 ; j<20 ; j++){

		if(j==19){
		
			time[i]='\0';
			break ;
		}
	
		time[i]=stringT[j] ;
		i++;
	}
	

	return time ;
}

//part 3 convert month to string
char* monthToNumber(char stringMonth[], char stringT[]) {

	if(stringT[4]=='J' && stringT[5]=='a'){
	
		stringMonth[0]='0';
		stringMonth[1]='1';
	}else if(stringT[4]=='F'){
	
		stringMonth[0]='0';
		stringMonth[1]='2';
	}else if(stringT[4]=='M' && stringT[6]=='r'){
	
		stringMonth[0]='0';
		stringMonth[1]='3';
	}else if(stringT[4]=='A' && stringT[5]=='p'){
	
		stringMonth[0]='0';
		stringMonth[1]='4';
	}else if(stringT[4]=='M' && stringT[6]=='y'){
		stringMonth[0]='0';
		stringMonth[1]='5';

	}else if(stringT[4]=='J' && stringT[6]=='n'){
		stringMonth[0]='0';
		stringMonth[1]='6';

	}else if(stringT[4]=='J' && stringT[6]=='l'){
		stringMonth[0]='0';
		stringMonth[1]='7';

	}else if(stringT[4]=='A' && stringT[5]=='u'){
		stringMonth[0]='0';
		stringMonth[1]='8';

	}else if(stringT[4]=='S'){
		stringMonth[0]='0';
		stringMonth[1]='9';

	}else if(stringT[4]=='O'){
		stringMonth[0]='1';
		stringMonth[1]='0';

	}else if(stringT[4]=='N'){
		stringMonth[0]='1';
		stringMonth[1]='1';

	}else{
		stringMonth[0]='1';
		stringMonth[1]='2';

	}

	stringMonth[2]='\0' ;
	
	return stringMonth ;
}

//to get the date as a char array
char* getDate(char date[],char stringT[],char stringMonth[]) {
	int i ;
	int j =20 ;

	for(i=0 ; i<4 ; i++){
		date[i]=stringT[j] ;
		j++;

	}
	
	date[i]='-' ;
	j=0;
	
	for(i=5 ; i<7 ; i++){
	
		date[i]=stringMonth[j] ;
		j++;
	}
	
	date[i]='-';
	j=8;

	for(i=8 ; i<10 ; i++){
		if(stringT[j] == ' '){
		
			date[i] = '0' ;
			j++ ;
		}else{	
			date[i]=stringT[j] ;
			j++ ;
		}

	}

	date[i]='\0' ;

	return date ;



}

//to check two strings are equal lower case neglecting case
int S_check(char s1[],char s2[]) {

	for(int i=0 ; s1[i]!='\0' ; i++){
	
		if(tolower(s1[i])!=tolower(s2[i])){
			
			return 0 ;
		}
	}

	for(int j = 0 ; s2[j]!='\0' ; j++){
	
		if(tolower(s2[j])!=tolower(s1[j])){
		
			return 0;
		}
	}

	return 1 ;
}


//to check two strings are equal considering case
int SF_check(char s1[],char s2[]){

	for(int i=0 ; s1[i]!='\0' ; i++){
	
		if(s1[i]!= s2[i]){
		
			return 0;
		}
	}
	
	for(int j = 0 ; s2[j]!='\0' ; j++){
	
		if(s2[j] != s1[j]){
		
			return 0 ;
		}
	}

	return 1;
	
}

//to get the colour 
char color_check(char s[]) {

	if(S_check(s,"black") ){
	
		return 'k' ;
	}else if(S_check(s,"red") ){
	
		return 'r' ;
	}else if(S_check(s,"blue") ){
	
		return 'b' ;
	}else if(S_check(s,"green") ){
	
		return 'g' ;
	}else if(S_check(s,"yellow") ){
	
		return 'y' ;
	}else if(S_check(s,"magenta") ){
	
		return 'm' ;
	}else if(S_check(s,"cyan") ) {
	
		return 'c' ;
	}else if(S_check(s,"white") ){
	
		return 'w' ;
	}else{
	
		return 'z' ;
	}
}


// to filter the -cCOLOR
char special_color_check(char s[]) {

        if(S_check(s,"-cblack") ){

                return 'k' ;
        }else if(S_check(s,"-cred") ){

                return 'r' ;
        }else if(S_check(s,"-cblue") ){

                return 'b' ;
        }else if(S_check(s,"-cgreen") ){

                return 'g' ;
        }else if(S_check(s,"-cyellow") ){

                return 'y' ;
        }else if(S_check(s,"-cmagenta") ){

                return 'm' ;
        }else if(S_check(s,"-ccyan") ) {

                return 'c' ;
        }else if(S_check(s,"-cwhite") ){

                return 'w' ;
        }else{

                return 'z' ;
        }
}

       

//to check the flag whether it is -c >> 'C'.whether it is -h >> 'H'.If starts with '-'>> 'X'else'Z' -COLOR >> 'S'
char flag_check(char s[]){
	
	if(SF_check(s,"-c")){
	
		return 'C' ;
	}else if(special_color_check(s) != 'z'){
	
		return 'S' ;

	}else if(SF_check(s,"-h")){
	
		return 'H' ;
	}else if(s[0]=='-'){

		if(strlen(s)==1){
		
			return 'Z' ;
		}else{
		
			return 'X' ;
		}
	
		return 'X' ;
	}else{
	
		return 'Z' ;
	}
}


//**********   WE ARE GOGING TO DO THER TERMINAL GRAPHICS   *****************

//print a box
void Pbox(char c){
	
	switch(c){
	
		case 'k' : printf("%s%s**%s",TC_BLACK,TC_B_BLACK,TC_NRM) ; break ;
		case 'r' : printf("%s%s**%s",TC_RED,TC_B_RED,TC_NRM) ; break ;
		case 'g' : printf("%s%s**%s",TC_GREEN,TC_B_GREEN,TC_NRM) ; break ;
		case 'y' : printf("%s%s**%s",TC_YELLOW,TC_B_YELLOW,TC_NRM) ;break ;
		case 'b' : printf("%s%s**%s",TC_BLUE,TC_B_BLUE,TC_NRM) ; break ;
		case 'm' : printf("%s%s**%s",TC_MAGENTA,TC_B_MAGENTA,TC_NRM);break;
		case 'c' : printf("%s%s**%s",TC_CYAN,TC_B_CYAN,TC_NRM) ; break ;
		case 'w' : printf("%s%s**%s",TC_WHITE,TC_B_WHITE,TC_NRM) ; break ;
	}
	
}

//print a black box
void Pspace(){
	printf("  ") ;

}

//print zero
void Pzero(char c){

	for(int i =0 ; i<5 ; i++){
	
		for(int j=0 ; j <3 ; j++){
		
			if((i>0 && i<4)&&(j==1)){
			
				Pspace() ;
			}else{
			
				Pbox(c) ;
			}
		}

		T_left(6) ;
		T_down(1) ;
			
	}
}

//print one
void Pone(char c) {

        for(int i =0 ; i<5 ; i++){

		        for(int j=0 ; j <3 ; j++){

				if(j==2){

					Pbox(c) ;
				}else{
				
					Pspace() ;
				}
			}
			T_left(6) ;
			T_down(1) ;

	}

}


//print two
void Ptwo(char c){

	for(int i =0 ; i<5 ; i++){
	
		for(int j=0 ; j <3 ; j++){
		
			if(((i==1)&&(j<2))||((i==3)&&(j>0))){
			
				Pspace(); 
			}else{
				
				Pbox(c) ;
			}
		}
		T_left(6) ;
		T_down(1) ;
	}
}

//print three
void Pthree(char c){

	for(int i=0 ; i<5 ; i++){
	
		for(int j=0 ; j<3 ; j++){
		
			if((i==1 && j<2)||(i==3 && j<2)){
			
				Pspace();
			}else{
			
				Pbox(c) ;
			}
		}

		T_left(6) ;
		T_down(1) ;
	}
}
// print four
void Pfour(char c) {

	for(int i=0 ; i<5 ; i++){
	
		for(int j=0; j<3 ; j++){
		
			if((j==2)||(i==2)||((j==0)&&(i<3))){
			
				Pbox(c);
			}else{
			
				Pspace() ;
			}
		}
		T_left(6) ;
		T_down(1) ;
	}
}

//print five
void Pfive(char c) {

	for(int i=0 ; i<5 ; i++){
	
		for(int j=0; j<3 ; j++){
		
			if(((i==1)&&(j>0))||((i==3)&&(j<2))){
				Pspace();

			}else{
				Pbox(c);

			}
		}
		T_left(6) ;
		T_down(1) ;
	}
}

//print six
void Psix(char c) {

	for(int i=0 ; i<5 ; i++){
	
		for(int j=0; j<3 ; j++){
		
			if(((i==1 && j>0)||(i==3 && j==1))){
			
				Pspace() ;
			}else{
			
				Pbox(c) ;
			}
		}
		T_left(6) ;
		T_down(1) ;
	}
}

//print seven
void Pseven(char c) {

	for(int i=0 ; i<5 ; i++){
	
		for(int j=0; j<3 ; j++){
		
			if(i==0 || j==2){
			
				Pbox(c) ;
			}else{
			
				Pspace() ;
			}
		}
		T_left(6) ;
		T_down(1) ;
	}
}

//print eight
void Peight(char c) {

	for(int i=0 ; i<5 ; i++){
	
		for(int j=0; j<3 ; j++){
		
			if((i==1 && j==1)||(i==3 && j==1)){
			
				Pspace() ;
			}else{
			
				Pbox(c) ;
			}
		}
		T_left(6) ;
		T_down(1) ;
	}
}

//print nine
void Pnine(char c) {

	for(int i=0 ; i<5 ; i++){
	
		for(int j=0; j<3 ; j++){
			
			if(((i==1 && j==1)||(i==3 && j<2))){
				Pspace() ;
			}else{
			
				Pbox(c) ;
			}

		}
		T_left(6) ;
		T_down(1) ;
	}
}

//print colun
void Pcolun(char c) {

	for(int i=0 ; i<5 ; i++){
	
		for(int j=0; j<3 ; j++){
		
			if((i==1 && j==1)||(i==3 && j==1)){
			
				Pbox(c) ;
			}else if((i==0 && j==1)||(i==2 && j==1)||(i==4 && j==1)){
			
				Pspace() ;
			}else{
			
				putchar(' ') ;
			}
		}
		T_left(4) ;
		T_down(1) ;
	}
}

//print the gap betwee two number
void Pgap(){

	for(int i=0 ; i<5 ; i++){
	
		putchar(' ') ;
		T_down(1) ;
		T_left(1) ;
	}
}

//print the symbol in digital way
void Psymbol(char a,char c){
	switch(a){
	
		case '0' :Pzero(c);break;
		case '1' :Pone(c) ; break ;
		case '2' :Ptwo(c) ; break ;
		case '3' :Pthree(c); break ;
		case '4' :Pfour(c) ; break ;
		case '5' :Pfive(c) ; break ;
		case '6' :Psix(c) ; break ;
		case '7' :Pseven(c) ; break ;
		case '8' :Peight(c) ; break ;
		case '9' :Pnine(c) ; break ;
		case ':' :Pcolun(c) ; break ;

		default:
			  return;
	}

}

//print the given string time
void Ptime(char time[],char c){

	for(int i=0 ; time[i]!='\0';i++){
	
		if(time[i]==':'){
			
			Psymbol(time[i],c);
			T_up(5) ;
			T_right(4) ;

			Pgap() ;
			T_up(5);
			T_right(1) ;
		
		}else{
			
			Psymbol(time[i],c);
			T_up(5) ;
			T_right(6);

			Pgap() ;
			T_up(5);
			T_right(1) ;

		}
		
	}
	T_move_cursor(2,2) ;
}

//print the date and move the cursor
void Pdate(char date[],char c){

	switch(c){
	
		case 'k' : printf("%s%s%s",TC_BLACK,date,TC_NRM) ; break ;
		case 'r' : printf("%s%s%s",TC_RED,date,TC_NRM) ; break ;
		case 'g' : printf("%s%s%s",TC_GREEN,date,TC_NRM) ; break ;
		case 'y' : printf("%s%s%s",TC_YELLOW,date,TC_NRM) ; break ;
		case 'b' : printf("%s%s%s",TC_BLUE,date,TC_NRM) ; break ;
		case 'm' : printf("%s%s%s",TC_MAGENTA,date,TC_NRM) ; break ;
		case 'c' : printf("%s%s%s",TC_CYAN,date,TC_NRM) ; break ;
		case 'w' : printf("%s%s%s",TC_WHITE,date,TC_NRM) ; break ;

	}


	T_move_cursor(2,2) ;

}


//to handle the signal
void SignalHandle(int i){

	T_clear_scrn() ;

	T_normal_cursor() ;

	system(DO_TYPE) ;

	printf("%s",TC_NRM) ;

	T_restore_screen() ;


	exit(1) ;
	
}


