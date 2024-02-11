//Limin Mhari Allen E.
//Admin Function: Input 295 at main menu
//Username: TUPadmin
//Password: tupmanila

#include <iostream>     //standard input/output
#include <fstream>      //header file for file handling
#include <iomanip>      //header file for manipulator functions for the output
#include <conio.h>
#include <cstring>
#include <string.h>
#include <ctime>
#include <windows.h>

//using namespace std;
#define LP 7
#define TP 3
#define RP 100


//max number of students
#define MAX 100

typedef struct regist{
std::string NAME;
int age;
int day;
int month;
int year;
std::string course;
std::string section;
std::string nationality;
int id;
std::string pass;
struct regist *next;
} REG;

typedef struct candidates{ // Structure for the Candidate's data
    std::string CandName;
    int PVoteCount;
    int VPVoteCount;
    int SecVoteCount;
    std::string Pres;
    std::string VPres;
    std::string Secre;
    struct candidates *next;
}CAND;

typedef struct counter {
	int PCount;
   	int VPCount;
   	int SecCount;
	struct counter *next;
} CNT;


class REC
{
    private:
        REG *rg;
        REG *re;
        CAND *cd;
        CNT *cn;
    public:
        void gotoxy(int a, int b); //function for accurate placements
        void border(const char *title, const char *subtitle); //function for menu design borders
        void coverpage(); //function for the project's cover page
        int mainmenu(); //function for menu display and input
        void display(); //display the whole list as well as computing for data average and remarks
        //MM functions:
        void makenull(); //resets the last value of the list
        int insertCard(); //function for detecting the usb for ID verification
        void registration(); //function for entering voter's data
        int IDGen(); //function for producing a unique Voter ID
        void REGinsert(REG g); //function for data transfer to structure
        void REGsave(); //function for saving the data from the list to the database file
        void REGretrieve(); //function for retrieving past list data from the database file
        //int isfull(); //function for checking if the list is full
        int isempty(); //function for checking if the list is empty
        //int pos(std::string n[MAX]); //compares the inputted string if it's smaller than the string value in the array
        //int locate(std::string n[MAX]); //locates the inputted data them compares it to the list

        //Voter menu & functions:
        int votemenu(); //function for the voting menu
        void Voting(CAND c); //function for the actual voting process
        void VDispCand(); //function for displaying the available candidates
        void saveCand(); //function for saving entered candidates
        void CandRetrieve(); //function for refilling the candidate file with candidates
        int locateCand(std::string n, int i ); //function for finding the index of the candidate name entered
        int locatevoter(); //function for finding the index of the voter name

        //admin menu & functions:
        void admin(); //function for the admin control
        int adminmenu(); //function for displaying the admin menu
        void addCand(CAND c); //admin function for adding candidates
        void delCand(CAND c); //admin function for removing candidates
        void DispPres();
        void DispCand(); //admin function for displaying the candidates and their amount of votes

        };



//Design & Main Menu:
void REC::gotoxy(int a, int b) //function for accurate placements
{
    COORD c;
    c.X=a; //assigning the x coord to a
    c.Y=b; //assigning the y coord to b
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void REC::border(const char *title, const char *subtitle) //function for menu design borders
{
    REC r;
    // Left and Right Borders
    for(int i = TP; i < 7; i++)  //for loop terminates when i is less than 7 where i is equal to TP
    {
        r.gotoxy(LP, i);
        std::cout<<"||";
    }
    for(int i = TP; i < 7; i++)  //for loop terminates when i is less than 7 where i is equal to TP
    {
        r.gotoxy(RP, i);
        std::cout<<"||";
    }
    // Top and Bottom Borders
    for(int i = LP; i < 100; i++)  //for loop terminates when i is less than 100 where i is equal to LP
    {
        r.gotoxy(i, 2);
        std::cout<<"=";
    }
    for(int i = LP; i < 100; i++)  //for loop terminates when i is less than 100 where i is equal to LP
    {
        r.gotoxy(i, 7);
        std::cout<<"=";
    }

    // Corners
    r.gotoxy(7, 2);
    std::cout<<"[]";
    r.gotoxy(100, 2);
    std::cout<<"[]";
    r.gotoxy(7, 7);
    std::cout<<"[]";
    r.gotoxy(100, 7);
    std::cout<<"[]";


    // Texts
    r.gotoxy((((LP + RP) / 2) - (strlen(title) / 2)), TP + 1);
        for(int i = 0; i < strlen(title); i++)
            {
            for(int j = 0; j < 10000000; j++);
            std::cout<<title[i];//219
            }

    r.gotoxy((((LP + RP) / 2) - (strlen(subtitle) / 2)), TP + 2);
        for(int i = 0; i < strlen(subtitle); i++)
            {
            for(int j = 0; j < 10000000; j++);
            std::cout<<subtitle[i];//219
            }
}

void REC::coverpage() //function for the project's cover page
{
time_t t;
REC r;

    system ("color 0E");
    r.gotoxy(39,5);     //assigning coordinates
    std::cout<<"Technological University of the Philippines";
    r.gotoxy(48,6);     //assigning coordinates
    std::cout<<"BSCS 2AB First Project";
    r.gotoxy(53,8);
    std::cout<<"Prepared by:";
    r.gotoxy(50,10);     //assigning coordinates
    std::cout<<" Mhari Allen Limin";
    r.gotoxy(48,11);     //assigning coordinates
    std::cout<<"Christian Noel Nacario";
    r.gotoxy(43,21);     //assigning coordinates
    time(&t);
    std::cout<<"Date today: "<< ctime(&t);
    r.gotoxy(47,22);     //assigning coordinates
    system("pause");
}

int REC::mainmenu() //function for menu display and input
{
    REC r;
    int i, optn;
    const char *men[] = {"Login", "Register", "Exit"}; //main menu options
    system ("cls");

    r.border("TECHNOLOGICAL UNIVERSITY OF THE PHILIPPINES", "AUTOMATED VOTING SYSTEM\n\n\n");

    for (i=0;i<3;i++)
        std::cout<<"\t\t\t\t\t   "<<i+1<<".) "<<men[i]<<"\n";//layout of menu display
        std::cout<<"\t\t\t\t___________________________________________\n";
        std::cout<<"\n\t\t\t\t\t Please Select (1-3): ";
        std::cin>>optn;

    return(optn); //return the option chosen
}

//MM Functions
void REC::makenull() //resets the last value of the list
{
    rg = NULL;
    re = NULL;
    cd = NULL;
    cn = NULL;
}

int REC::insertCard() //function for detecting the usb for ID verification
{
    REG *r;
    r=rg;
    int user,i,s,cnt;
    char pwrd[40];
    std::fstream fp;
    do
    {
        fp.open("d:\\voter.txt", std::ios::in);
        system("cls");
        std::cout<<"Please insert card...\n";
    }while(!fp); //will keep looping until it detects the card (usb) has been plugged in
     {
        fp >> user >> pwrd; //takes the password from the file after the card is detected
        //std::cout <<pwrd;
        //system("pause");
        cnt = strlen(pwrd);
        /*cnt = 0;
        for(s=0; pwrd[s]; s++)
            {
                if(pwrd[s] != ' ')
                {
                    cnt ++; //increases count
                }

            }*/
        std::cout<<"\n\nCard Detected! Please wait...\n";
        std::cout<<"\n\nValidating your credentials...";
        std::cout<<"\nID: "<< user<<" \n";
        std::cout<<"PW: ";

        for(i=0; i<cnt; i++) //hides the password with asterisks
        {
            std::cout<<"*";
        }

     }
     std::cout<<"\n";
     fp.close();

    std::string strpass(pwrd);

    while(r!=NULL)
    {
        if(r->id == user && r->pass == strpass) //compare if the string inputted by the user is the same as the one on the loop
        {
            return(i);
        }
        r = r->next;
    }
    return (-1);
}

void REC::registration() //function for entering voter's data
{
    REC c;
    REG g;
    //variables
    int i;

    i=0;

    //printf("Registration for Voting");
    c.border("Automated Voting System", "  Registration\n\n\n");

    //voter information the user inputs
    std::cout<<"\n\tEnter your surname: ";
    std::cin>>g.NAME;
    std::cout<<std::endl;

    std::cout << "\tEnter Age: ";
    std::cin >> g.age;
    std::cout<<std::endl;

    std::cout <<"\tEnter Birthday: ";
    std::cout<<std::endl;
    std::cout <<"\n\t\tDay: ";
    std::cin >> g.day;


    std::cout<<"\n\t\tMonth: ";
    std::cin>>g.month;

    std::cout<<"\n\t\tYear: ";
    std::cin>>g.year;

    std::cout<<"\n\tEnter your course (eg. Civil_Eng): ";
    std::cin>>g.course;

    std::cout<<"\n\tEnter your section (eg. 1A/2B): ";
    std::cin>>g.section;

    std::cout<<"\n\tEnter Nationality: ";
    std::cin>>g.nationality;



    g.id = c.IDGen(); //generates the voter's ID

    std::cout<<"\n\tPlease insert your desired password: "; //gets the password the voter enters
    std::cin>>g.pass;

    std::cout<<"\n\n\tCongratulations you are now registered in our system! \n\tRedirecting you to Voting Menu...";
    std::cout<<"\n";
    system("pause");
    c.REGinsert(g); //insert all the variables the user input into the structure
    c.REGsave(); //saves the specific user ID and PW for future reference
}

int REC::IDGen() //function for producing a unique Voter ID
{
    int ID;
    int lower = 100000;
    int higher = 999999;

    srand(time(NULL)); //initialize for the id to be random every run

    ID = (rand() % (higher - lower + 1)) + lower; //calculates the ID
    std::cout<<"\n\tYour Designated ID Number is: \n\t"<<ID;
    return (ID);

}

void REC::REGinsert(REG g) //function to input the data of the voter for the ID
{
  REC r;
  REG *p, *q, *temp;  //declaration of struct pointers

        p=q=rg;//initialize data in p q and st to be equal
        temp = new REG;//creating new records
        temp->NAME = g.NAME;  //changes the temp struct with the inputted content
        temp->age = g.age;
        temp->day = g.day;
        temp->month = g.month;
        temp->year = g.year;
        temp->course = g.course;
        temp->section = g.section;
        temp->nationality = g.nationality;
        temp->id = g.id;
        temp->pass = g.pass;

        while(p!=NULL&& p->NAME < g.NAME){//while p has content and the last name save in p is less than the input in terms of ascii value
            q=p;
            p=p->next;//changes the address p by the address p next
        }
        if(p == rg){
        rg=temp;
        }

        else{
            q->next = temp;//address of the next element to q is = address of temp
        }
        temp->next = p;//address of the next element to temp is = address of p
        std::cout << std::endl;

}


void REC::REGsave() //function for saving the data from the list to the database file
{
    std::fstream fp;
    REG *r,*s;
    r=rg;
    fp.open("voterec.dbf", std::ios::app); //opens voterec for writing
    if (fp.fail()) //if no file found goes to error
    {
        std::cout<<"File Error.\n";
        system("pause");
    }
    else
    {
    while(r!=NULL){
        fp << r->NAME << " " << r->age << " " << r->day << " " << r->month << " " << r->year << " " << r->course << " " << r->section << " " << r->nationality << " " << r->id << " " << r->pass << std::endl;
        std::cout << r->NAME << " " << r->age << " " << r->day << " " << r->month << " " << r->year << " " << r->course << " " << r->section << " " << r->nationality << " " << r->id << " " << r->pass << std::endl;
        r = r->next;

    }
    fp.close();
    }
    s=rg;
    fp.open("d:\\voter.txt", std::ios::app); //opens the file in the card (usb) for writing
    if (fp.fail())
    {
        std::cout<<"File Error.\n";
        system("pause");
    }
    else
    {
    while(s!=NULL){
        fp << s->id << " " << s->pass << std::endl;
        s = s->next;
    }
    fp.close();
    }
}

void REC::REGretrieve() //function for retrieving past list data from the database file
{
    //REC c;
    REG r;

    //int a,d,m,y,id;

    std::fstream fp;
    //fp >> r.NAME >> r.age >> r.day >> r.month >> r.year >> r.course >> r.section >> r.nationality >> r.id >> r.pass;
    fp.open("voterec.dbf", std::ios::in);
    if(!fp){ //if file does not exist, creates a new file for storing and retrieving data
        fp.open("voterec.dbf", std::ios::out);//opening the file
        }
    else
    {
            while(true){
                fp >> r.NAME >> r.age >> r.day >> r.month >> r.year >> r.course >> r.section >> r.nationality >> r.id >> r.pass;
                if(fp.eof()){
                    break;
                }
            REGinsert(r);//passes the data to function for inserting student record
            }
        }


    fp.close();
}

/*int REC::isfull() //function for checking if the list is full
{
    return(rg == MAX-1);
    return(cd == MAX-1);
    return(cn == MAX-1);
}*/

int REC::isempty()//function for checking if the list is empty
{
    return(rg == NULL);
    return(cd == NULL);
    return(cn == NULL);
}

/*int REC::locate (std::string n[MAX]) //locates the inputted data them compares it to the list
{
    for(int i=0;i<=L->last;i++) //loop for locating the input from the list
    {
        if(memcmp(L->info[i].NAME, n, sizeof(L->info[i].NAME)) == 0)// == 0) //compare if the string inputted by the user is the same as the one on the loop
        {
        std::cout<<"nagreturn ng i";
        return(i);
        }
    }
    std::cout<<"nagreturn ng -1";
    return(-1);
}

int REC::pos(std::string n[31]) //compares the inputted string if it's smaller than the string value in the array
{
    int i;
    for(i=0;i<=L->last;i++) //loop for comparing if the input name is lower or before the array name data
    {
        if(memcmp(L->info[i].NAME, n, sizeof(L->info[i].NAME)) == 0) //returns the index number if they are the same string
        {
            return(i);
        }
    }
    return(i);
}*/

//voter menu & functions:
int REC::votemenu() //function for menu display and input
{
    REC r;
    int i, choice;

    const char *menu[] = {"Vote", "See Candidates", "Logout"}; //options for the voting menu
    system ("cls");
    r.border("   TECHNOLOGICAL UNIVERSITY OF THE PHILIPPLINES", "    STUDENT COUNCIL VOTING MENU\n\n\n");

    for (i=0;i<3;i++)
        std::cout<<"\t\t\t\t\t   "<<i+1<<".) "<<menu[i]<<"\n";//layout of menu display
        std::cout<<"\t\t\t\t\t_________________________________\n";
        std::cout<<"\n\t\t\t\t\t Please Select (1-3): ";
        std::cin>> choice;

    return(choice); //returns the chosen option from the menu
}

void REC::Voting(CAND c){ //function for the actual voting process

    REC r;
    CAND *p, *q;
    p=q=cd;
    int l, i,ch;



        while(p!=NULL && p->Pres!=c.Pres){//while p has content and the id save in p is not equal to input
                q=p; //address q is now = to address p
                p=p->next; //address p is now the address p next
                }
            if(p==NULL){//no match is found
                    std::cout << "President not found!" << std::endl;
                }
                else{
                    /*if(p==cd){//if address p is equal to starting address
                        cd=cd->next;//address st is now address p next
                    }
                    else{*/
                        //q->next=p->next;//address q next is now address p next
                        p->PVoteCount++; //deletes p
                    //}
                    }
        p=q=cd;

        while(p!=NULL && p->VPres!=c.VPres){//while p has content and the id save in p is not equal to input
                q=p; //address q is now = to address p
                p=p->next; //address p is now the address p next
                }
                if(p==NULL){//no match is found
                    std::cout << "Vice President not found!" << std::endl;
                }
                else{
                    /*if(p==cd){//if address p is equal to starting address
                        cd=cd->next;//address st is now address p next
                    }
                    else{*/
                        //q->next=p->next;//address q next is now address p next
                        p->VPVoteCount++; //deletes p
                   // }
                    }
        p=q=cd;

        while(p!=NULL && p->Secre!=c.Secre){//while p has content and the id save in p is not equal to input
                q=p; //address q is now = to address p
                p=p->next; //address p is now the address p next
                }
                if(p==NULL){//no match is found
                    std::cout << "Secretary not found!" << std::endl;
                }
                else{
                    /*if(p==cd){//if address p is equal to starting address
                        cd=cd->next;//address st is now address p next
                    }
                    else{*/
                        //q->next=p->next;//address q next is now address p next
                        p->SecVoteCount++; //deletes p
                    //}
                    }



        }



void REC::VDispCand(){ //function for displaying the available candidates
    REC r;
    CAND *q;
    q = cd;
    std::string ps,vps,sec;
    if(r.isempty()){ //checks if the list to display is empty
        std::cout<<"List is empty!\n";
        std::cout<<"Press any button to continue.\n";
        getch();
    }

    else{
        int i=0;
        std::cout<<"\n\t\t LIST OF CANDIDATES\n";
        std::cout<<"\n\t\tCandidates for President: ";
        //std::cout<<"\n\t\tNAME\t\tNo. of Votes\n"; //if not shows the same list as the display candidates function, but with the amount of votes they have. ONLY FOR ADMINS.

        while(q != NULL){
               std::cout<<"\n\t\t"<< i+1<<".) "<< q->Pres;
               //std::cout<<"\t\t"<< q->PVoteCount;
               q = q->next;
               i++;


               /*ps = q->Pres;
               vps = q->VPres;
               sec = q->Secre;
               q = q->next;*/

        }
            i=0;
            q=cd;
            std::cout<<"\n\t\tCandidates for Vice President: ";
            //std::cout<<"\n\t\tNAME\t\tNo. of Votes\n";
            while(q != NULL){
               std::cout<<"\n\t\t"<< i+1<<".) "<< q->VPres;
               //std::cout<<"\t\t"<< q->VPVoteCount;
               q = q->next;
               i++;
            }
            i=0;
            q=cd;
            std::cout<<"\n\t\tCandidates for Secretary: ";
            //std::cout<<"\n\t\tNAME\t\tNo. of Votes\n";
            while(q != NULL){
               std::cout<<"\n\t\t"<< i+1<<".) "<< q->Secre;
               //std::cout<<"\t\t"<< q->SecVoteCount;
               q = q->next;
               i++;
            }
            std::cout<<std::endl;
}
}

void REC::saveCand(){ //function for saving entered candidates
    std::fstream fp;
    CAND *c;
    c=cd;
    fp.open("Partylist.dbf", std::ios::out); //opens voterec for writing
    if (fp.fail()) //if no file found goes to error
    {
        std::cout<<"File Error.\n";
        system("pause");
    }
    else
    {
    while(c!=NULL){
        fp << c->Pres <<" "<< c->PVoteCount <<" "<< c->VPres<<" "<< c->VPVoteCount <<" "<< c->Secre<<" "<< c->SecVoteCount << std::endl;
        c = c->next;

    }
    fp.close();
    }

}

void REC::CandRetrieve(){ //function for refilling the candidate file with candidates
    CAND c;

    std::fstream fp;
    //fp >> r.NAME >> r.age >> r.day >> r.month >> r.year >> r.course >> r.section >> r.nationality >> r.id >> r.pass;
    fp.open("Partylist.dbf", std::ios::in);
    if(!fp){ //if file does not exist, creates a new file for storing and retrieving data
        fp.open("Partylist.dbf", std::ios::out);//opening the file
        }
    else
    {
            while(true){
                fp >> c.Pres >> c.PVoteCount >> c.VPres >> c.VPVoteCount >> c.Secre >> c.SecVoteCount;
                if(fp.eof()){
                    break;
                }
            addCand(c);//passes the data to function for inserting student record
            }
        }


    fp.close();
}

int REC::locateCand (std::string n, int i ) //function for finding the index of the candidate name entered
{
    int TierChoice, k;
    CNT *p;
    CAND *q;
    int pc, vpc, sc;
    p = cn;
    std::string pn,vpn,sn;

    pc = p->PCount;
    vpc = p->VPCount;
    sc = p->SecCount;

    TierChoice = i;
    k = 0;

    switch(TierChoice){ //switch statement for retrieving the candidates from their respective tiers

     case 1:
        while(i<=pc) //loop for locating the president from the list
    {
        pn = q->Pres;
        if(n.compare(pn)) //compare if the president inputted by the user is the same as the one on the loop
        {
        return(i); //returns the index if found successfully
        }
        k++;
        q = q->next;
    }
        break;

     case 2:
        while(i<=vpc) //loop for locating the vice president from the list
    {
        vpn = q->VPres;
        if(n.compare(vpn)) //compare if the vice president inputted by the user is the same as the one on the loop
        {
        return(i); //returns the index if found successfully
        }
        k++;
        q = q->next;
    }
        break;

    case 3:
        while(i<=sc) //loop for locating the secretary from the list
    {
        sn = q->Secre;
        if(n.compare(sn)) //compare if the secretary inputted by the user is the same as the one on the loop
        {
        return(i); //returns the index if found successfully
        }
        k++;
        q = q->next;
    }
        break;
    default:
        std::cout<<"This is not supposed to happen";
        exit(0);
    }
    return(-1);
}

int REC::locatevoter () //locates the inputted data them compares it to the list
{
    //variables used
    int usr;
    std::string  pword[MAX];
    std::string status[MAX];

    std::fstream fp;
    fp.open("d:\\voter.txt", std::ios::in); //opens the file in the card (usb)
    fp >> usr >> pword[MAX] >> status[MAX]; //gets the username, password, and their voting status


        if(memcmp(status, "Voted", sizeof (status))) //compare if the string inputted by the user is the same as the one on the loop
        {
        return(0); //if voted they will no longer be able to access the voting
        }
    fp.close();
    return(-1);
}


//admin menu & functions:
/*void REC::admin(){ //function for the admin control
    REC r;
    CAND cn;
    REG *j;
    b:
    //variables used
    system("cls");
    //system("color 0A");
    std::string n[20];
    std::string UN;
    std::string PW[MAX];
    std::string PWord;
    //str::string PASS;
    char pswd[40];
    int adminchoice, i=0;

    std::cout<<"\n\t\t\t Admin Log-in Panel";
    std::cout<<"\n\t\t\t_________________________";
    std::cout<<"\n\t\t\t Enter admin username: ";
    std::cin>> UN; //takes the username of the admin for login

    std::cout<<"\n\t\t\t Enter admin password: ";
    std::cin>> PWord;

        //std::cout<<" "<<UN;
    if (UN == "TUPadmin"){// sizeof(UN))==0){

        if(PWord == "tupmanila"){ //if both strcmp are successfull can access the admin menu

            std::cout<<"\n\n\t\t\t Welcome Admin, redirecting you to the admin menu...\n\t\t\t";
            system("pause");

while(1){
            //system("color 0A");
            adminchoice = r.adminmenu();
            switch(adminchoice){
            case 1: //add candidates case
                system("cls");
                system("color B0");
                r.border("STUDENT COUNCIL 2021", "ADD CANDIDATES\n\n\n");
                r.addCand(c); //adds the candidates to the list
                r.saveCand(); //saves the added candidate to the file
                break;
            case 2: //delete candidates case
                system("cls");
                system("color C0");
                r.border("STUDENT COUNCIL 2021", "DELETE CANDIDATES\n\n\n");
                //r.DispCand(); //displays the all the candidates from all tiers
                //std::cin.getline(n, MAX);
                r.delCand(); //deletes the candidate from the list
                r.saveCand(); //saves the deleted candidate to the file
                break;
            case 3: //display candidates case
                system("cls");
                system("color E0");
                r.border("STUDENT COUNCIL 2021", "DISPLAY VOTES\n\n\n");
                r.DispCand(); //displays all the candidates in the list
                system("pause");
                break;
            case 4: //display voters case
                system("cls");
                system("color 70");
                r.border("STUDENT COUNCIL 2021", "DISPLAY VOTERS\n\n\n");
                r.display(); //displays all the voters in the list
                system("pause");
                break;
            case 5: //exit case
                std::cout<<"\nThank you for using the Admin Program :)";
                exit(0); //exits the program
            default: //default in case the number selected isn't from 1-5
            std::cout<<"Number not found! Please pick from 1-5 only!";
            getch();

            }

            }
        }
        else{
            std::cout<<"\n\n\t\t\t Password entered is invalid\n";
            system("pause");
            goto b; //if wrong password we return to the start of the admin input

        }
    }
    else{
        std::cout<<"\n\n\t\t\t Username / Password entered is invalid\n";
        system("pause");
        goto b; //if wrong password we return to the start of the admin input


    }
}*/

int REC::adminmenu(){ //function for displaying the admin menu
    REC r;
    int i, select;
    const char *menu[] = {"Add Partylist", "Remove Partylist", "Display Candidates", "Display Voters", "Exit"}; //options for the admin menu
    system ("cls");
    r.border("STUDENT COUNCIL 2021", "ADMIN MENU\n\n\n");

    for (i=0;i<5;i++){ //outputs the choices that the admin can choose
        std::cout<<"\t\t\t\t         "<<i+1<<".) "<<menu[i]<<"\n";//layout of menu display
    }
        std::cout<<"\t\t\t\t_______________________________________\n";
        std::cout<<"\n\t\t\t\t\t Please Select (1-5): ";
        std::cin>> select;

    return (select); //returns the chosen menu option
}

void REC::addCand(CAND c){ //admin function for adding candidates
    CAND *p, *q, *temp;
    REC r;
    int i;
    int choice;

    p=q=cd;
    temp = new CAND;
    temp->Pres = c.Pres;
    temp->VPres = c.VPres;
    temp->Secre = c.Secre;
    temp->PVoteCount = c.PVoteCount;
    temp->VPVoteCount = c.VPVoteCount;
    temp->SecVoteCount = c.SecVoteCount;

    while(p!=NULL && p->Pres < c.Pres){//while p has content and the last name save in p is less than the input in terms of ascii value
            q=p;//puts the contents in p to q
            p=p->next;//changes the address p by the address p next
        }
            if(p==cd){//puts on the memory block on the start
            cd = temp;
                }
            else{
                q->next = temp;//address of the next element to q is = address of temp
            }
            temp->next = p;//address of the next element to temp is = address of p
    }



void REC::delCand(CAND c){ //admin function for removing candidates
    REC r;
    CAND *p, *q;
    p=q=cd;
    int l, i,ch;
    if (r.isempty()){ //checks if there is nothing to remove
        std::cout<<"List is Empty.";
        getch();
    }
    else{
                while(p!=NULL && p->Pres!=c.Pres){//while p has content and the id save in p is not equal to input
                    q=p; //address q is now = to address p
                    p=p->next; //address p is now the address p next
                }

                if(p==NULL){//no match is found
                    std::cout << "President not Found!" << std::endl;
                    system("pause");
                }
                else{
                    if(p==cd){//if address p is equal to starting address
                        cd=cd->next;//address st is now address p next
                    }
                    else{
                        q->next=p->next;//address q next is now address p next
                        delete(p); //deletes p
                    }
                    std::cout << std::endl << "Partylist Deleted!" << std::endl;//prints text for successful delete
                    system("pause");
                    }
        }
    }

void REC::DispPres(){ //admin function for displaying the candidates and their amount of votes
    REC r;
    CAND *q;
    q = cd;
    std::string ps,vps,sec;
    if(r.isempty()){ //checks if the list to display is empty
        std::cout<<"List is empty!\n";
        std::cout<<"Press any button to continue.\n";
        getch();
    }

    else{
        int i=0;
        std::cout<<"\n\t\t LIST OF CANDIDATES\n";
        std::cout<<"\n\t\tCandidates for President: ";
        std::cout<<"\n\t\tNAME\t\tNo. of Votes\n"; //if not shows the same list as the display candidates function, but with the amount of votes they have. ONLY FOR ADMINS.

        while(q != NULL){
               std::cout<<"\n\t\t"<< i+1<<".) "<< q->Pres;
               std::cout<<"\t\t"<< q->PVoteCount;
               q = q->next;
               i++;


               /*ps = q->Pres;
               vps = q->VPres;
               sec = q->Secre;
               q = q->next;*/

        }
    }
}

void REC::DispCand(){ //admin function for displaying the candidates and their amount of votes
    REC r;
    CAND *q;
    q = cd;
    std::string ps,vps,sec;
    if(r.isempty()){ //checks if the list to display is empty
        std::cout<<"List is empty!\n";
        std::cout<<"Press any button to continue.\n";
        getch();
    }

    else{
        int i=0;
        std::cout<<"\n\t\t LIST OF CANDIDATES\n";
        std::cout<<"\n\t\tCandidates for President: ";
        std::cout<<"\n\t\tNAME\t\tNo. of Votes\n"; //if not shows the same list as the display candidates function, but with the amount of votes they have. ONLY FOR ADMINS.

        while(q != NULL){
               std::cout<<"\n\t\t"<< i+1<<".) "<< q->Pres;
               std::cout<<"\t\t"<< q->PVoteCount;
               q = q->next;
               i++;

        }
            i=0;
            q=cd;
            std::cout<<"\n\t\tCandidates for Vice President: ";
            std::cout<<"\n\t\tNAME\t\tNo. of Votes\n";
            while(q != NULL){
               std::cout<<"\n\t\t"<< i+1<<".) "<< q->VPres;
               std::cout<<"\t\t"<< q->VPVoteCount;
               q = q->next;
               i++;
            }
            i=0;
            q=cd;
            std::cout<<"\n\t\tCandidates for Secretary: ";
            std::cout<<"\n\t\tNAME\t\tNo. of Votes\n";
            while(q != NULL){
               std::cout<<"\n\t\t"<< i+1<<".) "<< q->Secre;
               std::cout<<"\t\t"<< q->SecVoteCount;
               q = q->next;
               i++;
            }
        std::cout<<std::endl;

    }
}


void REC::display() //display the whole list as well as computing for data average and remarks
{
    REG *j;
    j=rg;
    int i, ID, AGE, DAY, MONTH, YEAR;
    std::string NM, COURSE, SECTION, NATIONALITY;
    i=0;

    if(isempty()){
        std::cout << std::endl << "\t\t\tVoter List is empty.";              //call isempty function then determined value returned
        getch();
    }
    else{
    std::cout<<"\n\t\t\t\t\t   VOTER's INFORMATION DATABASE\n";
    std::cout<<"\t_______________________________________________________________________________________________________"<<std::endl;
    std::cout<<"\t      ID#             NAME            AGE        BIRTHDAY       COURSE        SECTION      NATIONALITY    "<<std::endl;
    std::cout<<"\t_______________________________________________________________________________________________________"<<std::endl;
    while(j!=NULL) //loop for displaying the values of the structure array variables as well as computing individual average
        {
        std::cout<<"\t "<<i+1<<".)  "<< j->id<< "\t    "<< j->NAME<<"\t      "<< j->age<<"\t"<< j->day<<"/"<< j->month<<"/"<< j->year<<"\t "<< j->course<< "\t\t"<< j->section<<"\t    "<< j->nationality<<std::endl;
        j=j->next;
        i++;
        //std::cout<<"\nIf display is not displaying as intended, kindly maximize the window, thank you :D\n";
    }

}
}


int main(){
  REC r;
  CAND c;
  //local declarations for the switch statements
  std::string n, p, l;
  int option,i,user,pw;
  int VChoice,MChoice;

  r.coverpage(); //shows the starting cover page of the project
  r.makenull(); //resets last value of list
  r.REGretrieve(); //populatate the list with the data from the file
  //r.REGsave();
  r.CandRetrieve(); //populate the list with the data from candidates file

a:
    system("color F0");
    MChoice = r.mainmenu(); //recall menu function for menu display

    switch(MChoice) // case for menu input
    {
      case 1 :
          //r.display();
          //system("pause");
          r.insertCard(); //case 1 verifies the card if there is any voter info in there

      if (r.insertCard()>=0) //if there is a card (usb) in the computer no need for further registration
      {
          std::cout<<"\n";
          system("pause");
          std::cout<<"\nVoter Information verified!\n ";
          system("pause");

      }
      else //but if not go here and register in order to put info in the card (usb)
      {
          std::cout<<"\n";
          system("pause");
          std::cout<<"You are not yet registered, please register first..";
          system("pause");
          system("cls");
          r.registration();
      }
          break;

      case 2 : //straight to registration for more voter ids
          system("cls");
          r.registration();
          break;

      case 3 : //Exit the program
          std::cout<<"\n\n\t\t\t\t\t Thank you for using the program!";
          exit(0);
          break;

      case 295 : //case for admin menu and functions
          b:
          //variables used
            system("cls");
            system("color 0A");
            std::string n[20];
            std::string UN;
            std::string PW[MAX];
            std::string PWord;
            //str::string PASS;
            char pswd[40];
            int adminchoice, i=0;

            std::cout<<"\n\t\t\t Admin Log-in Panel";
            std::cout<<"\n\t\t\t_________________________";
            std::cout<<"\n\t\t\t Enter admin username: ";
            std::cin>> UN; //takes the username of the admin for login

            std::cout<<"\n\t\t\t Enter admin password: ";
            std::cin>> PWord;

                //std::cout<<" "<<UN;
            if (UN == "TUPadmin"){// sizeof(UN))==0){

                if(PWord == "tupmanila"){ //if both strcmp are successfull can access the admin menu

                    std::cout<<"\n\n\t\t\t Welcome Admin, redirecting you to the admin menu...\n\t\t\t";
                    system("pause");

        while(1){
                    //system("color 0A");
                    adminchoice = r.adminmenu();
                    switch(adminchoice){
                    case 1: //add candidates case
                        system("cls");
                        system("color B0");
                        r.border("STUDENT COUNCIL 2021", "ADD CANDIDATES\n\n\n");

                        std::cout<<"\t\t--President--"; //continue if not full
                        std::cout<<"\nEnter the name of Candidate you wish to add: ";
                        std::cin >> c.Pres ;
                        c.PVoteCount = 0;

                        std::cout<<"\t\t--Vice President--";
                        std::cout<<"\nEnter the name of Candidate you wish to add: ";
                        std::cin >> c.VPres;
                        c.VPVoteCount = 0;


                        std::cout<<"\t\t--Secretary--";
                        std::cout<<"\nEnter the name of Candidate you wish to add: ";
                        std::cin >> c.Secre;
                        c.SecVoteCount = 0;

                        r.addCand(c); //adds the candidates to the list
                        r.saveCand(); //saves the added candidate to the file
                        std::cout<<"Partylist Added Successfully";
                        system("pause");
                        break;
                    case 2: //delete candidates case
                        system("cls");
                        system("color C0");
                        r.border("STUDENT COUNCIL 2021", "DELETE Partylist\n\n\n");
                        r.DispPres(); //displays the all the candidates from all tiers
                        std::cout<<"\n\nEnter the name of the Partylist's President you wish to delete: ";
                        std::cin>>c.Pres;
                        r.delCand(c); //deletes the candidate from the list
                        r.saveCand(); //saves the deleted candidate to the file
                        break;
                    case 3: //display candidates case
                        system("cls");
                        system("color E0");
                        r.border("STUDENT COUNCIL 2021", "DISPLAY VOTES\n\n\n");
                        r.DispCand(); //displays all the candidates in the list
                        system("pause");
                        break;
                    case 4: //display voters case
                        system("cls");
                        system("color 70");
                        r.border("STUDENT COUNCIL 2021", "DISPLAY VOTERS\n\n\n");
                        r.display(); //displays all the voters in the list
                        system("pause");
                        break;
                    case 5: //exit case
                        std::cout<<"\nThank you for using the Admin Program :)";
                        exit(0); //exits the program
                    default: //default in case the number selected isn't from 1-5
                    std::cout<<"Number not found! Please pick from 1-5 only!";
                    getch();

                    }

                    }
                }
                else{
                    std::cout<<"\n\n\t\t\t Password entered is invalid\n";
                    system("pause");
                    goto b; //if wrong password we return to the start of the admin input

                }
            }
            else{
                std::cout<<"\n\n\t\t\t Username / Password entered is invalid\n";
                system("pause");
                goto b; //if wrong password we return to the start of the admin input


            }
                  break;

            }


while(1){ //loop while true
    VChoice = r.votemenu(); //vote menu function for the switch case below

    switch(VChoice){
        case 1: //case for voting
            system("cls");
            r.border("STUDENT COUNCIL 2021", "   Vote Candidate\n\n\n");
            r.VDispCand(); //display all the available candidates
            /*if(r.locatevoter()>=0) //checks if the voter in question has already voted or not
                    {
                        std::cout<<"\nYou can only vote once... Thank you for Voting!\n";
                        system("pause");
                    }
                    else*/
                    {
                        std::cout<<"\nEnter the name of the President you want to vote: ";
                        std::cin >> c.Pres;
                        std::cout<<"\nEnter the name of the Vice President you want to vote: ";
                        std::cin>> c.VPres;
                        std::cout<<"\nEnter the name of the Secretary you want to vote: ";
                        std::cin >> c.Secre;
                        //std::cout<<"\nThank you for voting!\n";
                        system("pause");
                        r.Voting(c); //enters the names of the candidates the voter chose
                        r.saveCand(); //saves the candidates in their respective files
                    }
                    break;

        case 2: //case for displaying the candidates
            system("cls");
            r.border("STUDENT COUNCIL 2021", "  Candidate List\n\n\n");
            r.VDispCand(); //displays the candidates
            system("pause");
            break;

        case 3: //case for going back to the main menu
            system("cls");
            std::cout<<"Thank you for Voting!";
            goto a; //goes back to the top at the menu switch

        default:
            std::cout<<"\n Option chosen not included.";
            getch();
            system("cls");

    }

}

}
