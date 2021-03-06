/* 
 * File:   main.cpp
 * Author: Sebastian Hall
 * Created on July 17, 2017, 11:37 PM
 * Purpose:  Final Project - Hammurabi Strategy Game
 */

//System Libraries
#include <iostream>  //Input - Output Library
#include <ctime>     //For Time Function
#include <cstdlib>   //For Rand and Srand
#include <fstream>   //For File Input/Output
#include <iomanip>   //Formatting
#include <cmath>     //For the math functions
using namespace std; //Name-space under which system libraries exist

//User Libraries

//Global Constants

//Function Prototypes
void gtTitle();//Output title using file input/output
void seeRule();//Letting the player see the rules of the game
void dspYear(int &,float ,int ,float &,int &,int &,int ,int ,int);//Display  
                                              //the status for the current year
short priceL();     //New price each year
short neoPop();     //The new population each year
short cropRnd();//Random crop growth each year
short ratFd(int);//Percentage eaten by rats
int india(float ,int);


//Execution begins here
int main() {
    //Setting random seed
    srand(static_cast<unsigned int>(time(0)));
    //Constants
    short const ENDYR=11;//The year on which all games of Hammurabi end

    //Define menu choice variable
    short plyAgn;//Play Again?
    
    //Do while to loop for replays
    do{
    
    //Display The Title
    gtTitle();
    cout<<endl;
    
    //Optional Rules To See
    seeRule();
    
    //Declare and initialize variables
    int year=1;//The first year
    float newPpl=0;//New people to be determined by random
    int strvd=0;//The number of people you failed to feed and killed
    float pop=100;//The city population. Starts at 100
    int acres=1000;//City starts with 1000 acres
    int totBush=2800;//Total bushels starting at 2800
    int crops=0;//Amount harvested each year
    int ratFood=0;//The amount the rats happened to eat that year
    int lndPrc=rand()%10+17;//The current going rate for land in bushels range [17,26]
    short sellBuy=0;//The number of acres one wishes to sell or buy
    short acrsWrk=0;//The amount of acres you decided to work
    int pplFood;//People food
    int perAcre=3;//Bushels per acre
    
    
    
    
    //Display the first years data
    dspYear(year,newPpl,strvd,pop,acres,totBush,perAcre,ratFood,lndPrc);
   
    
    
    //Starting Loop For Years 1-11
    for(year+=1;year<11;++year){
        //Displaying the output questions

        cout<<endl<<"How Many Acres Do You Wish To Buy/Sell:   ";
        cin>>sellBuy;           //Acres for sale/purchase question
    
        
        while(sellBuy<0&&sellBuy<(acres*-1)||sellBuy>0&&sellBuy>totBush/lndPrc){
            cout<<"\nI Am Afraid That Amount Is Not Possible Hammurabi-Senpai\n"
                    "Enter Again\n";
            cin>>sellBuy;
        }       //Validates for both selling more land than you have and for
                //purchasing more land than you could afford
        
        
        
        
        //Updating and displaying important values
        acres+=sellBuy;             
        totBush-=sellBuy*lndPrc; //Printing new values to help make decisions 
        cout<<endl<<"New Acres:   "<<acres<<endl;
        cout<<"Total Bushels:     "<<totBush<<endl;


        //Next question
        cout<<"How Many Grains Would You Like To Feed Your People:   ";
        cin>>pplFood;       //Feeding people question & answer
        while(pplFood<=0||pplFood>totBush){
            cout<<"\nThat Is Not A Possible Amount My King\n"
                    "Enter Feeding Grains\n";
            cin>>pplFood;       //Answer validation
        }
        //Decision making info output
        totBush-=pplFood;
        strvd=india(pop,pplFood);
        cout<<"\nTotal Acres:       "<<acres;
        cout<<"\nTotal Bushels:     "<<totBush<<endl;
        cout<<"Total Population:  "<<pop<<endl;
        
        //Question 3
        cout<<"How Many Acres Do You Wish To Plant With Seed:   ";
        cin>>acrsWrk;       //Crop growing answer
        while(acrsWrk>acres||acrsWrk<0||acrsWrk>pop*100){
            cout<<"\nThat Is Not Possible, My Lord\n"
                    "Enter Again\n";
            cin>>acrsWrk;       //Answer validation
            cout<<endl;
        }
        //Updating total bushels for next calculations
        totBush-=acrsWrk;
        cout<<endl<<endl<<endl<<endl;


        //Next Year Data Processing
        pop-=strvd;//Taking away the people who died
        
        //Game Failure                      //If number dead exceeds 45% in 1 
        if(strvd>=static_cast<float>(pop)*0.45){//year the game ends and loses
            cout<<"You Have Killed "<<strvd<<" people in 1 year\n"
                    "You Have Been Dethroned And Executed For Incompetence\n"
                    "You Lose The Game\n";break;//Ending for loop    
        }
        //Continue Data Processing For Next Iteration
        lndPrc=priceL();//Random land price
        newPpl=neoPop();//Random new population
        pop+=newPpl;//Adding new population to old population
        perAcre=cropRnd();//Crops grown per acre
        crops=perAcre*acrsWrk;//Total Acres worked
        totBush+=crops;//Total bushels after getting crops
        ratFood=ratFd(totBush);//Eaten by rats. takes away from totBush
        totBush-=ratFood;
        
        
           //Displaying recurring header for each year  
    dspYear(year,newPpl,strvd,pop,acres,totBush,perAcre,ratFood,lndPrc);
    
    }
    
    
    //Output for losing with no land
    if(year==11&&acres<1){
        cout<<endl<<endl<<endl<<"You Are A King Without A Kingdom And A Failure"
                " Of A Man\nYou Finished With No Land And "<<pop<<" People\n"
                "\nYou Lose";
    }           //Congratulations output
    else if(year==11&&acres>0){
        cout<<"\n\n\nCongratulations, You Survived "
                "All Ten Years Without Failing\n"
                "Horribly And Causing Mass Genocides And Revolts\n";
        cout<<"You Ended With "<<pop<<" People And "<<acres<<" Acres.\n"
                "That Averages To About "<<acres/static_cast<float>(pop)
                <<" Acres Per Person\n\nYou Win";
    (acres/static_cast<float>(pop)>=12)?cout<<"\nYou Lead A Country Like Trump":
        cout<<"\nYou Have Not Yet Reached Trump Status";
    }    //Compares you with great leaders based on score like original does
    
    //Asking to play again or quit
    cout<<"\n\n\n1.) Play Again\n2.) Quit\n";
    cin>>plyAgn;        //play again answers
    if(plyAgn>2||plyAgn<1){
        cout<<"\nInvalid Answer Input\nEnterAgain\n";
        cin>>plyAgn;//Answer validation
        if(plyAgn>9){//Nested loop
            cout<<"Enter A Single Digit Number From 1 To 2 To Proceed\n";
            cin>>plyAgn;
        }
    }
    switch(plyAgn){
        case 1:cout<<"\nGame Restarting\n\n\n";break;//Playing Again option
        case 2:cout<<"\nGame Ending\n\n\n";         //Ending Game option
    }
    
    
    }
    while(plyAgn!=2);//Replays game if choice does not equal two
    //A Sebastian Production
    return 0;
}


void gtTitle(){
    //Opening and writing to the Rules File
    ofstream title;     //Input file variable name
    string ttl;         //Variable used to read file info to
    
    title.open("title.dat");        //Opening file
    
    title<<"Hammurabi: A Game Of Strategy";//Reading title to file
    title.close();          //Closing file
    
    ifstream titleO;        //Input file variable
    titleO.open("title.dat");       //Opening input file
    
    while(titleO>>ttl){         //Displaying file name one string at a time
        cout<<ttl<<" ";
    }
    titleO.close();
    cout<<endl;
}

void seeRule(){
    char ans;               //The answer given (just to check off char)
    bool choice;            //Boolean value for the rules display choice
    
    cout<<"Press 0 And Enter To See The Game Rules.\nPress "//Rules input prompt
            "1 To Continue And Play The Game\n";
    cin>>ans;        //inputting choice to see rules
    if(ans==0)
        ans=1;
    choice=ans-48;   //Setting the char to the boolean
    
    if(choice==false){
        cout<<"You Are Hammurabi. Ruler Of This Land\n\n"
    "1.) The game will last 10 rounds each being one year\n"
    "2.) Each living person needs 20 bushels of grain per\n"//The Game Rules
    <<setw(4)<<""<<"year and can work up to 10 acres of land annually\n"
    "3.) Each acre of land requires 1 bushel to farm on it\n"
    "4.) If you kill enough people in one year you will be\n"
    <<setw(4)<<""<<"impeached and lose the game\n"
    "5.) Enter a negative value to sell land, positive to buy\n"
    "6.) Reach year 11 successfully to win the game\n\n";
        
        cout<<"Press Enter To Play\n";
        cin.ignore();       //Clear null terminator out of keyboard buffer
        cin.get();          //Enter to go to the next screen
    }
    cout<<endl<<endl;
}

void dspYear(int &year,float newPpl,int strvd,float &pop,int &acres
,int &totBush,int perAcre,int ratFood, int lndPrc){
    
    cout<<"Hammurabi: I beg to report to you,\n"
            "In year "<<year<<endl;                  //Header similar to real
    cout<<strvd<<" People starved\n";                //In game header
    cout<<newPpl<<" People came to the city\n";
    cout<<"The city population is now "<<pop<<endl;
    cout<<"The city now owns "<<acres<<" acres\n";
    cout<<"You harvested "<<perAcre<<" bushels per acre\n";
    cout<<"Rats ate "<<ratFood<<" bushels\n";
    cout<<"You now have "<<totBush<<" in store\n";
    cout<<"Land is trading at "<<lndPrc<<" bushels per acre\n";
    
}

short priceL(){
    //Setting the random seed
    srand(static_cast<unsigned int>(time(0)));
    short lndPrc=rand()%10+17;//Assigning land price to random
    
    return pow(lndPrc,1);//Returning land price for each round
//Just to technically use cmath . No uses of it in this program
}

short neoPop(){
    //Setting the random seed
    srand(static_cast<unsigned int>(time(0)));
    short newPop=rand()%10+3;//Range [3,17]
    return newPop;//returning the amount of new people
}

short cropRnd(){
    //Random Seed Set
    srand(static_cast<unsigned int>(time(0)));
    short perAcre=0;//Initialize to 0
    perAcre=rand()%5+1;//Range [1,5] crops per acre
    
    return perAcre;//Returning bushels per acre variable
}

short ratFd(int totBush){
    //Time seed random
    srand(static_cast<unsigned int>(time(0)));
    short poss=rand()%3+1;//Possibility of rats eating grain is 1/3
    short eaten=0;//The numeric amount eaten
    
    if(poss==2){//If poss =2 then rats will come else
    float perc;//Percentage of crops ravaged by rats
    perc=rand()%50+1;//Range of [1,50] percent
    eaten=(totBush*perc/100);
    }
    else
        eaten=0;//No rats = np food eaten
    return eaten;//send back amount eaten
}


int india(float pop,int pplFood){
    short strvd;
    if(pplFood/20<=pop){
        strvd=pop-pplFood/20;//Calculate how many starved if inadequate food
    }                        //Is offered
    else
        strvd=0;    //If enough food is given, strvd is default 0
    return strvd;//Return dead people
    }


