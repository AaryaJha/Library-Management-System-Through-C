//library management system 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int rate=2;
//passcode=12345
typedef struct book{
    char name[30];
    char author[30];
    char publisher[30];
    char units[2];
    
}book;
typedef struct node{
    book* binfo;
    
    struct node* next;
}node;
struct node* head=NULL;


typedef struct date{
    char day[2];
    char month[2];
    char year[4];
}date;

typedef struct student{
    char name[30];
    char ID[6];
}student;

typedef struct record{
    char bname[30];
    char sid[5];
    //date from;
    //date to;
    
}record;

/*typedef struct blist{
    book bnode;
    book* next;
}

typedef struct rlist{
    record rnode;
    record* next;
}
*/

char regstu[100][5];
int stucnt=0;

void read_book(){
    FILE* fp;
    char name[20];
    fp=fopen("books.txt","r");
    while(fscanf(fp," %[^\t]",name)!=EOF){
        //printf("\n Here");
        node* nbook=(node*)malloc(sizeof(node));
        nbook->binfo=(book*)malloc(sizeof(book));   

        char author[30];
        fseek(fp,0,SEEK_CUR);
        fscanf(fp," %[^\t]",author);
        char pub[15];
        fseek(fp,0,SEEK_CUR);
        fscanf(fp," %[^\t]",pub);
        fseek(fp,0,SEEK_CUR);
        char units[2];
        fscanf(fp," %[^\n]",units);
        strcpy(nbook->binfo->name,name);
        strcpy(nbook->binfo->author,author);
        strcpy(nbook->binfo->publisher,pub);
        strcpy(nbook->binfo->units,units);
         
        if(head==NULL){
            head=nbook;
            nbook->next=NULL;
        }
        else{
            nbook->next=head;
            head=nbook;
        } 
            
    }    
    
    fclose(fp);
    
}

void revise() //revise  fee
{
    char psswrd[6];
    getchar();
    printf("\n\n\n\n ADMIN ONLY\n Enter the five digit passcode:");
    scanf("%[0-9]",psswrd);
    if(strcmp(psswrd,"12345")==0){
        printf("\n Enter the new rate: ");
        scanf("%d",&rate);
    }
    else{
        printf("\n I N V A L I D     P A S S W O R D\n");
    }
}

void ll_add(book* toadd){
    node* nbook=(node*)malloc(sizeof(node));
    nbook->binfo=(book*)malloc(sizeof(book));
    strcpy(nbook->binfo->name,toadd->name);
    strcpy(nbook->binfo->author,toadd->author);
    strcpy(nbook->binfo->publisher,toadd->publisher);
    strcpy(nbook->binfo->units,toadd->units);
    
    nbook->next=NULL;
    if (head==NULL){
        head=nbook;
    }
    else{
        nbook->next=head;
        head=nbook;
    }
}
void search()  //searches for author/book
{
    node* ptr=head;
    char substr[30];
    char op[2]="0";
    int flag=1;
    do{
        printf("\n Enter the substring you want to search in book data base (CASE SENSITIVE): ");
        scanf(" %[^\n]",substr);
        while(ptr!=NULL){
        if(strstr(ptr->binfo->name,substr)!=NULL || strstr(ptr->binfo->author,substr)!=NULL || strstr(ptr->binfo->publisher,substr)!=NULL){
            flag=0;
            printf("%s\t%s\t%s\n",ptr->binfo->name,ptr->binfo->author,ptr->binfo->publisher);
        }
        ptr=ptr->next;
        }
    
    if(flag==1){
        printf("\n Please capitalize the name you search\n Example: Great Gatsby or Linear Algebra");
        printf("\n Do you want to try again?(0-Yes,1-No");
        scanf("%[0,1]",op);
        }
    if(flag==0){
        break;
    }
    }while(strcmp(op,"0")==0);
}
int search_book(char name[]){   //returns the number of units available of the book
    if(head==NULL){
        printf("\n Library is empty");
    }
    node* ptr=head;
    
    while(ptr!=NULL){
        //printf("%s",ptr->binfo->name);
        //printf("%d",strcmp(ptr->binfo->name,name));
        if(strcmp(ptr->binfo->name,name)==0){
            //printf("%s",ptr->binfo->units);

            return ptr->binfo->units[0]-'0';
        }
        ptr=ptr->next;
    }
    return 0;
}
//modifies the number of available books, 1 to add a unit 0 to subtract a unit
int modify_avbook(char name[],int status){
    if(head==NULL){
        printf("\n Library is empty");
    }
    node* ptr=head;
    while(ptr!=NULL){
        if(strcmp(ptr->binfo->name,name)==0){
            if(status==1){
                ptr->binfo->units[0]+=1;
            }
            else{
                ptr->binfo->units[0]-=1;
            }
            return 1;
        }
        ptr=ptr->next;
    }
    return 0;     //return 1 incase of success or 0
}

void calculate_fee(char sid[]){
    FILE* fp;
    fp=fopen("records.txt","r");
    int flag=0;
    int d,m,y;
    getchar();
    printf("\n Enter the date of return of the book: ");
    scanf(" %d-%d-%d",&d,&m,&y);
    //printf("%d %d %d",d,m,y);
    //char state[2];
    //fgets(state,2*sizeof(char),fp);
    int state;
    while(fscanf(fp," %d",&state)!=EOF){
       
        if(state==0){
            continue;
        }
        fseek(fp,1,SEEK_CUR);
        char id[6];
        fgets(id,6*sizeof(char),fp);
        
        if(strcmp(id,sid)==0){
            
            fseek(fp,1,SEEK_CUR);
            char name[15];
            fscanf(fp,"%[^\t]",name);
            fseek(fp,1,SEEK_CUR);
            //char date[11];
            //fgets(date,11*sizeof(char),fp);
            int iday,imonth,iyear;
            fscanf(fp,"%d-%d-%d",&iday,&imonth,&iyear);
            fseek(fp,1,SEEK_CUR);
            //char date[11];
            //fgets(date,11*sizeof(char),fp);
            int tday,tmonth,tyear;
            fscanf(fp,"%d-%d-%d",&tday,&tmonth,&tyear);
           
            //printf("\n Here!");
            printf("\nID: %s Name: %s\n Issue Date: %d-%d-%d\n Due Date: %d-%d-%d\n",id,name,iday,imonth,iyear,tday,tmonth,tyear);
            //calculating fine
            if(y<tyear){
                printf("\n INVALID RETURN DATE!\n");
                break;
            }
            if(tyear>=y){
                if(tyear==y && tmonth>=m){
                    if(tmonth==m && tday<=d){
                        flag=0;
                    }
                    else{
                        flag=0;
                    }
                }
                else{
                    flag=0;
                }
            }
            printf("\n Rate of fine: Rs %d day after submission day",rate);
            
            
            if((tmonth-m)<0){
                flag+=(m-tmonth-1)*31+(31-tday+d);
                //printf("%d",flag);
                for(int i=tmonth;i<m;i++){
                    if(i==4 || i==6||i==8||i==9||i==11){
                        flag-=1;
                    }
                    if(i==2){
                        flag-=2;
                    }
                }
                
            }
            if((tmonth-m)>0 || ((tmonth==m) && (y-tyear>0))){
                flag+=(31-tday+d)+(12-tmonth+m-1)*31;
                for(int i=tmonth;(i%12)!=(m-1);i++){
                    if(i==3 || i==5 || i==7 ||i==8|| i==10){
                        flag-=1;
                    }
                    if(i==1){
                        flag-=2;
                    }
                }
                flag-=1;
                
            }
            if(tmonth==m){
                if(tyear==y){
                    flag+=d-tday;
                }
            }
            if(y-tyear>1){
                flag+=365*(y-tyear-1);
            }
            if(y<=tyear){
                if(m<=tmonth){
                    if(d<=tday){
                        flag=0;
                    }
                }
            }

        }

    }
    fclose(fp); 
    printf("\nNumber of additional days: %d\nAmount to be paid as fine: %d",flag,flag*rate);
}

void addBook(){
    book* b=(book*)malloc(sizeof(book));
    getchar();
    printf("\n Name: ");
    scanf(" %[^\n]",&(b->name));
    
    printf("\n Author: ");
    scanf(" %[^\n]",b->author);
    printf("\n Publisher: ");
    scanf(" %[^\n]",&(b->publisher));    
    printf("\n Units: ");
    scanf(" %[^\n]",&(b->units));  
    FILE* fp;
    fp=fopen("books.txt","a");
    fputs(b->name,fp);fputs("\t",fp);
    fputs(b->author,fp);fputs("\t",fp);
    fputs(b->publisher,fp);fputs("\t",fp);
    
    fputs(b->units,fp); fputs("\n",fp);
     
    fclose(fp);
    ll_add(b);
}

int isRegistered(char* id){
    
    for(int i=0;i<stucnt;i++){
        if(strcmp(regstu[i],id)==0){
            return 1;
        }
    }
    return 0;
}

void deleteRecord(char* sid){
    FILE* fp;
    int flag=0;
    fp=fopen("records.txt","r+");
    char state[2];
    
    while(fgets(state,2*sizeof(char),fp)!=NULL)
    {
    
    //printf("\n%s ",state);
    fseek(fp,1,SEEK_CUR);
    char id[5];
    fgets(id,6*sizeof(char),fp);
    printf("\n%s",id);
    
    if(strcmp(id,sid)==0){
        fseek(fp,-7,SEEK_CUR);        
        fputs("0 ",fp);
        fseek(fp,7,SEEK_CUR);
        flag=1;
        break;
    }
    char throw[100];
    fgets(throw,sizeof(throw),fp);
    
    }
    if(flag==0){
        printf("\n No records to show");
    }
    else{
        printf("\n Record deleted");
    }

}


void searchbyID(char sid[])
{
    FILE* fp;
    fp=fopen("records.txt","r+");
    char state[2];
    
    while(fgets(state,2*sizeof(char),fp)!=NULL)
    {
    
    if (strcmp(state,"0")==0){
        continue;
    }
    fseek(fp,1,SEEK_CUR);
    char id[5];
    fgets(id,6*sizeof(char),fp);
     fseek(fp,1,SEEK_CUR);
    char throw[100];
    fgets(throw,sizeof(throw),fp);
    if(strcmp(id,sid)==0){
        printf("\nStudent ID: %s",id); 
        printf(" %s",throw);
    }
    
    }

}
void addRecord()
{
    char idate[15],sdate[15];
    record* r=(record*)malloc(sizeof(record));
    printf("\nBook Name: ");
    scanf(" %[^\n]",&(r->bname));
    printf("\nEnter the 5 digit student ID: ");
    scanf(" %[^\n]",&(r->sid));
    printf("\nEnter the Issuing Date ");
    scanf(" %[^\n]",idate);   
    //printf("%s",idate);
    printf("\n Enter the Due Date: ");
    scanf(" %[^\n]",sdate);
    //write it on to the text file
    FILE* fp;
    fp=fopen("records.txt","a");
    fputs("1\t",fp);
    fputs(r->sid,fp);fputs("\t",fp);
    fputs(r->bname,fp);fputs("\t",fp);
    fputs(idate,fp);fputs("\t",fp);
    fputs(sdate,fp);fputs("\n",fp);
    //fputs("\n",fp);
    fclose(fp);
    //check if student is alaready registered 
    int flag=isRegistered(r->sid);
    if(flag==0)
    {
        fp=fopen("student.txt","a");
        fputs(r->sid,fp);fputs("\t",fp);
        printf("\n New Student ID\n Please Enter the Name of the Student: ");
        char name[30];
        scanf(" %[^\n]",name);
        fputs(strcat(name,"\n"),fp);
        strcpy(regstu[stucnt++],r->sid);
        fclose(fp);
    }
    modify_avbook(r->bname,0);
}

int main(){  //addBook,search,ll_add,addRecord,searchbyID,calculate_fee,delete checked. Need info in linked list to be read from file and stored 
    printf("\t\t\t\t\t\t L I B R A R A R Y     M A N A G E M E N T      S Y S T E M");
    printf("\n\nPlease Enter your choice\n\n");
    int op=0;
    do{
        read_book();
        printf("\n Press 1 to add a book in your records");
        printf("\n Press 2 to add a record of borrowing");
        printf("\n Press 3 to calculate fine and delte a record");
        printf("\n Press 4 to search the book data base");
        printf("\n Press 5 to check availability of a book");
        printf("\n Press 6 to print current record of a student");
        printf("\n ADMIN ONLY Press 7 to change current per day rate of fine");
        printf("\n Press 8 to exit the menu\n\n Your Choice: ");
        scanf(" %d",&op);
        switch(op){
            case 1:{
                addBook();
                break;
            }
            case 2:{
                char bname[20];
                printf("\n Enter the name of the book: ");
                scanf(" %[^\n]",bname);
                if(search_book(bname)==0){
                    printf("\n Book is not available!");
                }
                else{
                    printf("\n Enter the following details: ");
                    addRecord();
                }
                break;
            }
            case 3:{
                printf("\n Enter the five digit student ID: ");
                char sid[6];
                scanf(" %[0-9]",sid);
                char bname[30];
                printf("\n Enter the book name: ");
                scanf(" %[^\n]",bname);
                calculate_fee(sid);
                printf("\n Do you want to delete the record? (0-Yes 1-No) ");
                int o;
                scanf(" %d",&o);
                if(o==0){
                    deleteRecord(sid);
                    modify_avbook(bname,1);
                }
                break;
            }
            case 4:{
                search();
                break;
            }
            case 5:{
                char bname[20];
                printf("\n Enter the name of the book: ");
                scanf(" %[^\n]s",bname);
                printf(" Units Available: %d",search_book(bname));
                break;
            }
            case 6:{
                char sid[6];
                printf("\n Enter the student ID: ");
                scanf(" %s",sid);
                searchbyID(sid);
                break;
            }
            case 7:{
                revise();
                break;
            }
            case 8:{
                printf("\n Exiting..");
                return 0;
            }
            default:{
                printf("\n Invalid choice!");
            }
        }

    }while(op!=8);    
    return 0;
}



