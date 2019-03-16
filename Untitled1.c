#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define route_size 5
#define size 11

char logged_in_username[100];   // store successfully logged in "user name"

struct user_info{
     char name[100]; // add username all separately here
    char pass[100];

};


char *route_arr[5][5] = {{"Savar", "Mirpur 10", "Mirpur 10",  "savar", "mirpur 10"},
                        {"NSU", "farmgate", "lalbagh fort", "airport", "suhrawardi hospital"}};  // 1st col ftom , 2nd col to           // 2nd  col to



// Function declaration
void menu();
void top_design();

//create account function
void create_account_put_value_in_file(char [], char[]);
void create_account();

//user login function
void userlogin();
void check_login(char [],char [],struct user_info []);
void user_menu();
struct user_info *read_val_user(); //read value from user file
//** sub menu of user_login function **
void recent_travels(char []);
void select_destination(char []);
void Send_message_admin(char []);
//predict jam
void jam_details(int, int, int);
int predict_jam(int , int);
void buy_ticket(int, int,int);
void confirm_buy_ticket(int , int , int ,int ,int);
void save_travel_history(char [], int);

//fun game functions
void fun_game();
int recursion(int );

//admin functions
void admin_login();
void user_list(struct user_info []);
void admin_menu();
void admin_read_msg();

//exit function
void exit_all();

//forget password
void forget_pass();

//programmer info
void programmer_info();

// main body
int main(){
    top_design(); // for header design function
    menu(); // menu function

}


//menu function
void menu(){
    printf("\n\nMenu\n");
    printf("---------\n");
    printf("Press 1 - admin login\n");
    printf("Press 2 - user login\n");
    printf("Press 3 - create account\n");
    printf("Press 4 - forget password\n");
    printf("Press 5 - Fun game\n");
    printf("Press 6 - programmer info\n");
    printf("Press 7 - Exit\n");


        int input_from_menu;    // store value of user pressed in menu
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu



    switch(input_from_menu){
        case 1: admin_login();  //if user press 1 go to "admin_login" function
        break;
        case 2: userlogin();    // if user press 2 go to "user_login" function
        break;
        case 3: create_account();
        break;
        case 4: forget_pass();
        break;
        case 5: fun_game();
        break;
        case 6: programmer_info();
        break;
        case 7: exit_all(); // if user press 6 - exit the program
        break;

    default: printf("\n ** ERROR : Choice something from menu"); menu();    // if user press invalid number , call "menu" function again
    break;
    };
}

/* user login functions start*/
void userlogin(){
    char username[100]; //put input here
    char pwd[1000]; //put input here

    printf("\n");
    printf("Login Menu: \n");
    printf("-----------------\n");
    fflush(stdin);

    struct user_info *struct_user;
    struct_user = read_val_user(); // read_val_user() will return struct and "struct_user" will catch it

    printf("Enter Username: "); //get username
    gets(username);

/* get password as **** */
#define ENTER 13
#define TAB 9
#define BKSP 8

        int i=0;
    char ch;
    printf("Enter New password:");

    while(1)
    {
        ch=getch();
        if(ch==ENTER || ch==TAB)
        {
            pwd[i]='\0';
            printf("\n");
            break;
        }
        else if(ch==BKSP)
            {

               if(i>0)
                i--;
                printf(" \b \b");
            }
        else
        {
            pwd[i++]=ch;
            printf("* \b");
        }

    }
/* get password as **** */

    check_login(username,pwd,struct_user); // if value is 0 not found else user found

}
// read value from user
struct user_info *read_val_user(){
        static struct user_info a[size];  // array struct . to store value

        FILE *fuser;    // file pointer
        fuser = fopen("user.txt", "r");    //open file to read

        int count;
        if(fuser != NULL){ // check if file pointer is empty or not
            for(count=0; 1; count++){
                if(feof(fuser)){
                    break;
                }else{
                     fscanf(fuser, "%s", a[count].name);
                     fscanf(fuser, "%s", a[count].pass);
                }

            }
        }else{
             printf("** Error: File not found. Press 3 and create account");
             menu();
        }

        fclose(fuser);

        return a;
};

void check_login(char username[], char password[], struct user_info k[]){
         int count;
        int flag; // flag = 0 if user name and pass don't matched
        for(count=0; count < size; count++){
          if((strcmp(k[count].name, username) == 0) && (strcmp(k[count].pass, password) == 0)){ // compare username input to  all value of struct info(a)
            printf("\n username & pass found index at : %d \n", count);
                flag = 1;
                break;
          }else{
                flag = 0;
          }
        }

        if(flag == 0){  // password haven't matched
            printf("\n ** Invalid username or password");
            userlogin();    // open userlogin() function again , ask to username and pass again
        }else{  // username and password matched
            strcpy(logged_in_username, username); // set value to global variable "logged_in_username"
            user_menu(username);
        }

}

/* user login functions END*/

/* users menu after login functions start*/

void user_menu(){
    printf("\n\nUser Menu \t\t Welcome %s\n", logged_in_username);
    printf("---------------------------------------\n\n");
    printf("Press 1 - Recent Travel history\n");
    printf("Press 2 - Select Destination\n");
    printf("Press 3 - Send message to admin\n");
    printf("Press 4 - Logout & Exit\n");


    int input_from_menu;    // store value of user user pressed in menu

    printf("user choice: ");
    scanf("%d", &input_from_menu);  // scan what user pressed in menu

    switch(input_from_menu){
        case 1: recent_travels(logged_in_username);  //if user press 1 go to "admin_login" function
        break;
        case 2: select_destination(logged_in_username);    // if user press 2 go to "user_login" function
        break;
        case 3: Send_message_admin(logged_in_username);   // Send_message_admin function call
        break;
        case 4: exit_all(); // if user press 4 - exit the program
        break;

    default: printf("\n ** ERROR : Choice something from menu"); user_menu(logged_in_username);    // if user press invalid number , call "menu" function again
    break;
    };


}

/* users menu after login functions END*/

/*sub menu of login_user *** start here*/

Send_message_admin(char username[]){
    FILE *fmsg;
    char file_name[100];
    fmsg = fopen("msg.txt", "a");
    char msg[10000];

        fflush(stdin);
        printf("\n\nWrite your msg<*Dont user space>: ");
        gets(msg);

        int count_arr=0;
        // replace space with dash
        while(msg[count_arr] != '\0'){
            if(msg[count_arr] == ' '){
                msg[count_arr] = '-';
            }
            count_arr++;
        }

    if(fmsg != NULL){

        fprintf(fmsg, "%s ", username);
        fprintf(fmsg, "%s\n", msg);
        printf("\n***Message Sent");
    }else{
        printf("\nERROR: file not found\n");
        fmsg = fopen("msg.txt", "w");
        printf("\nERROR: file has been created\n");
        Send_message_admin(username);
    }

    fclose(fmsg);

    user_menu(username);
}

void recent_travels(char username[]){


    printf("\nRecent Travel history\n");
    printf("-----------------------\n\n");

    printf("FROM \t\t TO \n");
    printf("----- \t\t ----\n");


    char username_check[100];
    int i=0,j; // count
    int route[300];

    FILE *fp = fopen("history.txt", "r");
    if(fp != NULL){
        while(!feof(fp)){
            fscanf(fp, "%s", username_check);
            if(strcmp(username_check, logged_in_username)== 0){
                fscanf(fp, "%d", &route[i]);
                i++;
            }
        }

    fclose(fp);
    }else{printf("\nhistory.txt not found\n");}

    for(j=0; j<=i; j++){
        if(route[j] == 1){
                    printf("%s \t\t %s \n",route_arr[0][0], route_arr[1][0]);

                }else if(route[j] == 2){
                    printf("%s \t\t %s \n",route_arr[0][1], route_arr[1][1]);

                }else if(route[j] == 3){
                    printf("%s \t\t %s \n",route_arr[0][2], route_arr[1][2]);

                }else if(route[j] == 4){
                    printf("%s \t\t %s \n",route_arr[0][3], route_arr[1][3]);

                }else if(route[j] == 5){
                    printf("%s \t\t %s \n",route_arr[0][4], route_arr[1][4]);

                }

    }





    printf("\n\n0 - Back\n");

    int input_from_menu;    // store value of user user pressed in menu


    do{
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu

    }while(input_from_menu != 0);

    user_menu(username);

}

void select_destination(char username[]){
    printf("\nSelect Destination\n");
    printf("-----------------------\n\n");

    int input_hour, input_min; ; // store input from user
    do{
        printf("Enter Time ex<13 30 >: ");
        scanf("%d %d", &input_hour, &input_min);

    }while(input_hour < 0 || input_hour > 24 || input_min < 0 || input_min > 60 ); /*-- kaj baki---*/

    printf("\nSelect Destination: \n\n");
    printf("Press \t\t FROM \t\t TO \n");
    printf("----- \t\t ----- \t\t -----\n");

    int count;
    for(count =0; count <route_size; count++){

              printf("%d \t\t %s \t\t %s \n", count+1,route_arr[0][count], route_arr[1][count]);

    }

    printf("\n\n0 - Back\n");

    int input_from_menu;    // store value of user user pressed in menu
    do{
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu

    }while(input_from_menu < 0 || input_from_menu > 6);

    switch(input_from_menu){
        case 1: jam_details(input_hour,input_min, 1);  //if user press 1 go to "admin_login" function
        break;
        case 2: jam_details(input_hour,input_min, 2);     // if user press 2 go to "user_login" function
        break;
        case 3: jam_details(input_hour,input_min, 3);
        break;
        case 4: jam_details(input_hour,input_min, 4);
        break;
        case 5: jam_details(input_hour,input_min, 5);
        break;
        case 0: user_menu(username); // if user press 4 - exit the program
        break;

    };


}


/*sub menu of login_user *** END here*/

/*Jam predict start */

void jam_details(int hour, int min,int route){
    printf("\nTraffic Update\n");
    printf("--------------\n");
    printf("\nDetails for route : %d \t\t Time: %d:%d\n", route,hour,min);
    int x; // collect value from predict_jam function [1 - jam, 2 - free road]

    x = predict_jam(hour, route);

    if(x == 1){ //[1 = jam]
        printf("\nStatus: Road not free");
    }else{
        printf("\nStatus: Road free\n");
    }


            //alternative road *** kaj baki
            if(route == 1){
                printf("\nShowing details for:");
                printf(" Savar-> hemayetpur -> Mirpur 10 -> kalshi road->NSU\n");
                printf("\nAlternative roads:\n");
                printf("\n1) Savar-> Abdullah Pur -> NSU\n");
            }else if(route == 2){
                printf("\nShowing details for:");
                printf(" Mirpur 10-> Begum Rokeya Avenue Road-> Indira Rd -> Farmgate\n");
            }else if(route == 3){
                printf("\nShowing details for:");
                printf(" Mirpur 10 -> Begum Rokeya Avenue -> Sonargaon Road -> Lalbagh road->Lalbagh\n");
                printf("\nAlternative roads:\n");
                printf("\n1) Mirpur 10 ->  Principal Abul Kashem Rd -> Zahir Raihan Rd -> Dhakeshwari Rd -> lalbagh\n");
            }else if(route == 4){
                printf("\nShowing details for:");
                printf(" Savar -> Mirpur 10 -> bisso road -> airport\n");
                printf("\nAlternative roads:\n");
                printf("\n1) Savar ->  Abdullah pur -> airport road -> airport\n");
            }else{
                printf("\nShowing details for:");
                printf(" Mirpur 10 -> Begum Rokeya Avenue -> Bijoy Sarani -> sohrawardi uddan\n");

            }
 // save travel history
                save_travel_history(logged_in_username, route);






        printf("\n\nPress 1 - Another search");
        printf("\nPress 2 - BUY bus ticket");
        printf("\nPress 0 - Back\n");

    int input_from_menu;    // store value of user user pressed in menu
    do{
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu

    }while(input_from_menu < 0 || input_from_menu > 2);

    if(input_from_menu == 0){
        user_menu(logged_in_username);////
    }else if(input_from_menu == 2){
        buy_ticket(route,hour,min);
    }else{
        select_destination(logged_in_username);
    }

}

int predict_jam(int hour, int route){ // editing
    int jam_from_time;
    int jam_to_time;
    int route_f;

    FILE *fp = fopen("jam.txt", "r");
    int count=0;
    int flag = 0; // flag = 1 means road not free, flag = 2 means road free

    if(fp != NULL){
        while(1){
            if(feof(fp)){
                break;
            }else{
                fscanf(fp, "%d %d %d", &route_f, &jam_from_time, &jam_to_time);
                    if(route == route_f){
                         if(hour >= jam_from_time && hour <= jam_to_time){
                                flag = 1;
                                break;
                            }else{
                                flag = 2;


                        }
                    }
            }

        }
       fclose(fp);

    }else{printf("jam.txt file not found");}

    if(flag == 1){
         return 1; // yes you will face jams
    }else{
     return 2; // free road
    }

}
void save_travel_history(char username[], int route){
    FILE *fp = fopen("history.txt", "a");
    if(fp != NULL){
        fprintf(fp, "%s %d\n", username, route);
        fclose(fp);
    }else{
        fp = fopen("history.txt", "w");
        printf("\nFile history.txt has been created\n");
        save_travel_history(logged_in_username, route);
        }
}

/*Jam predict END */


/*buy ticket start */
void buy_ticket(int route, int hour, int min){
    char *bus_arr[2][5]={{"BUS 1","BUS 2","BUS 3","BUS 4","BUS 5"}, // bus name and ticket price
                        {22,25,30,27,26}};

    printf("\nAvailable Bus for route: %d\n", route);
    printf("-----------------------------\n");
    printf("\n\nPress \t\t Bus Name \t\t Ticket price\n");
    printf("----------\t -------- \t\t ---------- \n");

    int i;
    for(i=0; i<5; i++){
        printf("%d \t\t %s \t\t\t %d \n", i+1, bus_arr[0][i], bus_arr[1][i]);
    }
        printf("\n\n Press 0 - back\n\n");
        int input_from_menu;    // store value of user user pressed in menu
    do{
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu

    }while(input_from_menu < 0 || input_from_menu > 6);


    switch(input_from_menu){
        case 1: confirm_buy_ticket(route, 1, hour, min,22);  //if user press 1 go to "admin_login" function
        break;
        case 2: confirm_buy_ticket(route, 2, hour, min,25);    // if user press 2 go to "user_login" function
        break;
        case 3: confirm_buy_ticket(route, 3, hour, min,30);
        break;
        case 4: confirm_buy_ticket(route, 3, hour, min,27);
        break;
        case 5: confirm_buy_ticket(route, 3, hour, min,26);
        break;
        case 0: select_destination(logged_in_username);   // Send_message_admin function call


    };
}

void confirm_buy_ticket(int route, int bus_no, int hour, int min,int price){

    //pay slip for ticket

    printf("\npayment Option\n");
    printf("-----------\n");
    printf("Press 1 - Bkash\nPress 2 - DBBL\n");

        int input_from_menu;
    do{
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu

    }while(input_from_menu < 0 || input_from_menu > 2);


    // payment choice

    int payment_phone;
    char payment_confirm;

    if(input_from_menu == 1){
        printf("\nBkash Payment\n");

    }else{
        printf("\nDBBL Payment\n");

    }
        char pay_name[1000];
        printf("----------------\n");

        printf("Enter your mobile number: ");
        scanf("%d", &payment_phone);
        fflush(stdin);
        printf("Enter your Full name: ");
        gets(pay_name);
        printf("\nTotal price %d", price);
        fflush(stdin);
        printf("\nPress Y - confirm\nPress N - cancel\n");
        printf("User choice: ");
        scanf("%c", &payment_confirm);

        if(toupper(payment_confirm) == 'Y'){
            printf("\nPayment successful\n\n");
            printf("\npayment receipt\n");
            printf("---------------\n");
            printf("User Name: %s \nName: %s\nBus Name: %s \t Time: %d:%d\nTotal: %d", logged_in_username,pay_name,"bus name",hour,min,price);
        }else{
            user_menu(logged_in_username);
        }

        printf("\n\n Press 0 - Back\n");

    do{
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu

    }while(input_from_menu != 0);
    user_menu(logged_in_username);

}
/*buy ticket END */


/*start create account*/
void create_account(){
    char username[100];
    char password[100];

    fflush(stdin);
    printf("Enter New user name:");
    scanf("%s", username);
    fflush(stdin);
    printf("Enter New password:");
    gets(password);
    create_account_put_value_in_file(username,password);    // send value to "create_account_put_value_in_file" function to save those in file

}


void create_account_put_value_in_file(char username[], char password[]){

    FILE *fuser;    // file pointer
    fuser = fopen("user.txt", "a");    //open file to read
    int flag = 0; // flag =1 means successfull; flag to see if account has been created or not
    if(fuser != NULL){ // check if file pointer is empty or not
        fprintf(fuser,"%s ", username);
        fprintf(fuser,"%s\n", password);
        printf("\n** Successfully created new account");
        flag = 1;
    }else{
        fuser = fopen("user.txt", "w");
        printf("** File has been created \n");
        create_account(username, password);
    }

    fclose(fuser);

    if(flag == 1){
         menu();
    }

}
/*END create account*/


void forget_pass(){
    struct user_info *a;
    a=read_val_user();
    char username[100];
    fflush(stdin);
    printf("Enter Username: ");
    gets(username);

    int count;
    int flag = 0;
    for(count=0; count<size; count++){
        if(strcmp(username, a[count].name) == 0){
            flag = 1;
            break;
        }else{
            flag = 0;
            }
    }

    if(flag == 1){
        printf("\n**Password is : %s\n", a[count].pass);
    }else{
        printf("Not found \n");
    }

    printf("\n1 - Search another account \n");
    printf("\n0 - back \n");
    int input_from_menu;

    do{
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu

    }while(input_from_menu < 0 || input_from_menu > 1);

    switch(input_from_menu){
        case 0: menu();  //if user press 1 go to "admin_login" function
        break;
        case 1: forget_pass();
    };


}
void admin_login(){
     char username[100]; //put input here
    char pwd[1000]; //put input here
    printf("\n");
    printf("Admin Login Menu: \n");
    printf("-----------------\n");
    fflush(stdin);
    printf("\nDefault- User name: admin . and password: 123\n\n");


    printf("Enter Username: "); //get username
    gets(username);


/* get password as **** */
#define ENTER 13
#define TAB 9
#define BKSP 8

        int i=0;
    char ch;
    printf("Enter password: ");

    while(1)
    {
        ch=getch();
        if(ch==ENTER || ch==TAB)
        {
            pwd[i]='\0';
            printf("\n");
            break;
        }
        else if(ch==BKSP)
            {

               if(i>0)
                i--;
                printf(" \b \b");
            }
        else
        {
            pwd[i++]=ch;
            printf("* \b");
        }

    }
/* get password as **** */


    check_admin_login(username,pwd); // send all value to 'check_login' function

}

void check_admin_login(char username[], char passowrd[]){
    if((strcmp(username, "admin") == 0) && (strcmp(passowrd, "123") == 0)){
        admin_menu();
    }else{
        printf("\nError: invalid username or password.");
        admin_login(); // run "admin_login" function. ask for username and password again
    }
}

void user_list(struct user_info g[]){
    printf("\All Users List: \n\n");
    printf("Press \t\t User Name\n");
    printf("----- \t\t ----- \n");
    int count;

    for(count =0; count<size ; count ++){
         printf("%d \t\t %s \n", count+1,g[count].name);
    }

    printf("\n0 - back \n");
    int input_from_menu;

    do{
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu

    }while(input_from_menu < 0 || input_from_menu > size+1);

    switch(input_from_menu){
        case 0: admin_menu();  //if user press 1 go to "admin_login" function
        break;

    default:    // if user press invalid number , call "menu" function again
    break;
    };

}
void admin_menu(){
    struct user_info *a = read_val_user();

    printf("\n\nAdmin Menu \t\t Welcome Admin\n");
    printf("---------------------------------------\n\n");
    printf("Press 1 - User list\n");
    printf("Press 2 - Read message\n");
    printf("Press 3 - Logout & Exit\n");

    int input_from_menu;    // store value of user user pressed in menu

    printf("user choice: ");
    scanf("%d", &input_from_menu);  // scan what user pressed in menu

    switch(input_from_menu){
        case 1: user_list(a);  //if user press 1 go to "admin_login" function
        break;
        case 2:   admin_read_msg(); // if user press 2 go to "user_login" function
        break;
        case 3: exit_all(); // if user press 4 - exit the program
        break;

    default: printf("\n ** ERROR : Choice something from menu"); admin_menu();    // if user press invalid number , call "menu" function again
    break;
    };


}

struct msg_store{
    char msg[100000];
    char username[1000];
};

/*admin read message start*/
char msg[1000];
    char username[100];

struct msg_store k[30]; //test

void admin_read_msg(){

    int i=0,j;
    FILE *fmsg = fopen("msg.txt", "r");
    if(fmsg != NULL){
        while(1){
            if(feof(fmsg)){ //problem
                break;
            }else{
                fscanf(fmsg, "%s %s", k[i].username, k[i].msg);
                i++;
            }

        }
    }else{
        printf("\nError: msg.txt file not found\n");
        }

         int count_arr;
for(j=0; j<i; j++){
        count_arr=0;
        // replace dash with space
        while(k[j].msg[count_arr] != '\0'){ // test
            if(k[j].msg[count_arr] == '-'){
                k[j].msg[count_arr] = ' ';
            }
            count_arr++;
        }
    printf("\nUser name: %s \n msg: %s\n", k[j].username, k[j].msg);
}



        printf("\n\n Press 0 - Back\n");


    int input_from_menu;
    do{
        printf("user choice: ");
        scanf("%d", &input_from_menu);  // scan what user pressed in menu

    }while(input_from_menu != 0);
    admin_menu(); // test

}
void top_design(){
    printf("************************************\n");
    printf("*** Welcome to --------------- **** \n");
    printf("************************************\n");
}

void exit_all(){
    printf("\n Thanks for using our app");
    exit(0);
}

void fun_game(){
    printf("\nFun game using recursion<find factor of a number>\n");

    int a;
    int *x = &a;
    printf("Enter a value: ");
    scanf("%d", x);
   int ans = recursion(*x);
    printf("%d", ans);
}

int recursion(int x){
    int cal;
    if(x == 0){
        return 1;
    }else{
        cal = x*recursion(x-1);
    }

    return cal;

}

/*programmer credits*/
struct info{

    char name[50];
    int ID;
}infos[3];

void programmer_info(){

strcpy(infos[0].name,"Kayes Ibna Kayem");

FILE *write=fopen("test7.txt","w");

int i;
for(i=0;i<3;i++)
    fprintf(write,"%s,%d\n",infos[i].name,infos[i].ID);
fclose(write);

FILE *read=fopen("test7.txt","r");
int j=0;
while(!feof(read)){
    fscanf(read,"%[^,],%d",infos[j].name,&infos[j].ID);
    j++;
}
printf("          ==============================================\n");
printf("          ==========  PROGRAMMER INFORMATION  ==========\n");
printf("          ==============================================\n");

for(i=0;i<3;i++)
        printf("%d) %s\nID: %d\n",i+1,infos[i].name,infos[i].ID);

fclose(read);


}
