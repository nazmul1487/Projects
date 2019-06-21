#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int p=1;
struct TrainSeat
{
    int S_no;
    char Origination_station[100];
    char Destination_station[100];
    char departure[50];
    struct TrainSeat *next;
};

typedef struct TrainSeat  seat;

void addSeat(seat *list, char Origination_station[], char Destination_station[], char departure[] )
{
    seat *temp;
    temp=(seat*)malloc(sizeof(seat));
    temp->S_no=p;
    strcpy(temp->Origination_station,Origination_station);
    strcpy(temp->Destination_station,Destination_station);
    strcpy(temp->departure,departure);
    temp->next=NULL;
    while(list->next!=NULL)
        list=list->next;
    list->next=temp;
    p++;
}

int rmvSeat(seat *list, int S_no)
{
    if(list->next==NULL)
    {
        printf("\t\t\tNothing left to delete!!!\n\n");
        return;
    }
    while(list->next!=NULL)
    {
        if(list->next->S_no!=S_no)
        {
            list=list->next;
        }else{
            seat *temp;
            temp=list->next;
            list->next=temp->next;
            free(temp);
            return 1;
        }
    }
    printf("\t\t\tInvalid seat!!!\n\n");
    return 0;
}

void displaySeat(seat *list)
{
    FILE *fp;
    fp = fopen("data.txt","w");
    if(list->next==NULL)
    {
        printf("\t\t\tNo seats available!\n\n");
        return;
    }
    while(list->next!=NULL)
    {
        list=list->next;
        printf("S_no: %d\t  From: %s \tTo: %s \tDeparture: %s\n", list->S_no,list->Origination_station,list->Destination_station,list->departure);
        fprintf(fp,"%d\t%s\t%s\t%s\n", list->S_no,list->Origination_station,list->Destination_station,list->departure);
    }
    fclose(fp);
    printf("\n\n");
}

void read_data(seat *list){
    FILE *fp;
    seat data;
    fp = fopen("data.txt","r");
    while(fscanf(fp,"%d %s %s %s",&p,data.Origination_station,data.Destination_station,data.departure)!=EOF){
        addSeat(list,data.Origination_station,data.Destination_station,data.departure);
    }
    fclose(fp);
}

int main()
{
    int a,b,S_no;
    seat *list;
    list = (seat*)malloc(sizeof(seat));
    list->next=NULL;
    read_data(list);
    char Origination_station[100];
    char Destination_station[100];
    char departure[50];
    printf("\t\t------------------------------------------------------------\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t|                ONLINE TICKET SELL(BASIC)                 |\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t------------------------------------------------------------\n");
    printf("\n\n");
    menu1:
    while(1)
    {
        printf("\t\t\t\t Select Your Operation\n\n");
        printf("\t\t\tPress 1 For Administrator's Operation\n\t\t\tPress 2 For User's Operation\n\t\t\tPress 3 For Exit Operation\n\n");
        scanf("%d", &a);
        switch(a)
        {
        case 1:
            goto adminMenu;
            break;
        case 2:
            goto userMenu;
            break;
        case 3:
            exit(0);
        default:
            printf("\t\t\tInvalid Input!\n\n");
            break;
        }
    }
    adminMenu:
    while(1)
    {
        printf("\t\t\tPress 1 For Add Seat\n\t\t\tPress 2 For Remove Seat\n\t\t\tPress 3 For Display Seat\n\t\t\tPress 4 For Log out\n\n");
        scanf("%d", &b);
        switch(b)
        {
        case 1:
            printf("Enter Starting Station: ");
            scanf("%s",Origination_station);
            printf("\nEnter Ending Station: ");
            scanf("%s",Destination_station);
            printf("\nEnter Departure Time: ");
            scanf("%s",departure);
            addSeat(list,Origination_station,Destination_station,departure);
            printf("\n\t\t\tNew Seat added!\n\n");
            displaySeat(list);
            break;
        case 2:
            displaySeat(list);
            printf("Enter S_no No. to delete: ");
            scanf("%d",&S_no);
            printf("\n");
            if(rmvSeat(list,S_no)==1)
                printf("\n\t\t\tSeat no. %d has been deleted!!!\n\n");
            break;
        case 3:
            printf("\n\nDisplaying available seats...\n\n");
            displaySeat(list);
            break;
        case 4:
            goto menu1;
            break;
        default:
            printf("Invalid Input!\n\n");
            break;
        }
        }
    userMenu:
        while(1)
        {
        printf("\t\t\tPress 1 For Buy Seats\n\t\t\tPress 2 For Display Seats\n\t\t\tPress 3 For Log out\n");
        scanf("%d", &b);
        switch(b)
        {
        case 1:
            displaySeat(list);
            printf("Enter S_no no. to buy: ");
            scanf("%d", &S_no);
            if(rmvSeat(list,S_no)==1)
                printf("\n\nSuccessfully bought Seat no. %d",S_no);
                printf("\t\t\t THANK YOU!!!\n");
            break;
        case 2:
            displaySeat(list);
            break;
        case 3:
            goto menu1;
            break;
        default:
            printf("\t\t\tInvalid Input!!!\n\n");
            break;
        }
        }
    return 0;
}

