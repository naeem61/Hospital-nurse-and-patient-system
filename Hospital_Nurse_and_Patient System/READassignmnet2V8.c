/***********************************************************************
 * READassignmnet2V8.c
 * Program to read patient details
 * Mohammed Naeem
 * Version 8
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Struct with the patient details*/
struct patientdetailsread
{
    char firstname[20];
    char lastname[20];
    int Day;
    int month;
    int year;
    int patientheight;
    int patientwaistmeasure;
    int patientweight;
    char patientcomments[500];
};
/*Struct wihe the search for the file*/
struct Searchforthefile
{
    char lastnametosearch[20];
    int Daytosearch;
    int monthtosearch;
    int yeartosearch;
};
/*Structure for the nurse details*/
struct nurse
{
	char name[40];
	char ID[9];
	char Password[9];
};

FILE *openpatientdetailstoread(char Filename[35]);
int Readpatientdetails(FILE *fp, struct patientdetailsread detailsofpatients[]);
void Displaypatientdetails(struct patientdetailsread detailsofpatients[], int patientLine, struct Searchforthefile Filesearch, int end,FILE *fp, struct nurse list[], char Filename[35]);
void DisplayReadpatientsdetailtitle(void);
void Displaymaintitle(void);
char addnotetofile(struct Searchforthefile Filesearch, struct patientdetailsread detailsofpatients[], int patientLine, int end, FILE *fp, struct nurse list[], char Filename[35]);
int addNurse(struct nurse list[], int end);
void save(struct nurse list[], int end);
void emptytheBuffer(void);
void Consultantmenuoptions(FILE *fp, struct patientdetailsread detailsofpatients[], int patientLine, struct Searchforthefile Filesearch, struct nurse list[], int end, char Filename[35]);
void consultantmenu(FILE *fp, struct patientdetailsread detailsofpatients[], int patientLine, struct Searchforthefile Filesearch, struct nurse list[], int end, char Filename[35]);
void listallnurses(struct nurse list[], int end);
int deleteNurse(struct nurse list[], int end);
void Consultationlogins(void);
int main (void)
{
 	struct nurse list[50]; 
    int end = 0;
	char Filename[35];
    Displaymaintitle();
    Consultationlogins();
    DisplayReadpatientsdetailtitle();
	FILE *fp = openpatientdetailstoread(Filename);
	struct patientdetailsread detailsofpatients[200];
	struct Searchforthefile Filesearch[300];
	int patientLine = Readpatientdetails(fp, detailsofpatients);
 
	Consultantmenuoptions(fp, detailsofpatients, patientLine, Filesearch[300],list,end, Filename);

	 
	return 0;
	
}
/*Displays the read patient title*/
void DisplayReadpatientsdetailtitle(void)
{
    printf("\t\n\n\tREAD PATIENT DETAILS\n");
    printf("\t====================\n\n");
}
	
/*Opens the patient files*/
FILE *openpatientdetailstoread(char Filename[35]) 
{ 
    FILE *fp;
    
    printf("Enter patient's lastname and DOB (lastnamedaymonthyear.aow): ");
    scanf("%s", Filename);
    
    if(!(fp = fopen(Filename, "r")))
    { 
        puts("\nERROR - Unable to open File\n"); 
        exit(1); 
    } 
    return fp; 
} 
/*Reads the patient details*/
int Readpatientdetails(FILE *fp, struct patientdetailsread detailsofpatients[])
{
	int count = 0;
	while(fscanf(fp, "%[^ ] %s\n%d/%d/%d\n%dcm\n%dcm\n%dkg%s", detailsofpatients[count].firstname, detailsofpatients[count].lastname, &detailsofpatients[count].Day, &detailsofpatients[count].month, &detailsofpatients[count].year, &detailsofpatients[count].patientheight, &detailsofpatients[count].patientwaistmeasure, &detailsofpatients[count].patientweight, detailsofpatients[count].patientcomments) == 9)
	{
		count++;
	}
	fclose(fp);
	return count;
}
/*Displays the patient details*/
void Displaypatientdetails(struct patientdetailsread detailsofpatients[], int patientLine, struct Searchforthefile Filesearch, int end,FILE *fp, struct nurse list[], char Filename[])
{
	for(int i = 0; i < patientLine; i++) 
    { 
        printf("\nPatient: %s %s\n", detailsofpatients[i].firstname, detailsofpatients[i].lastname);
		printf("DOB: %d/%d/%d\n", detailsofpatients[i].Day, detailsofpatients[i].month, detailsofpatients[i].year);
		printf("Height: %dcm\n", detailsofpatients[i].patientheight);
		printf("Waist Measurement: %dcm\n", detailsofpatients[i].patientwaistmeasure);
		printf("Weight: %dkg", detailsofpatients[i].patientweight);
		printf("\nComments: %s", detailsofpatients[i].patientcomments);
    } 
        addnotetofile(Filesearch, detailsofpatients, patientLine, end, fp,  list, Filename);
        
}
/*Adds the note to file*/
char addnotetofile(struct Searchforthefile Filesearch, struct patientdetailsread detailsofpatients[], int patientLine, int end, FILE *fp, struct nurse list[], char Filename[])
{
    int num;
    
    printf("\n\n1. Add note to file\n");
    printf("2. Return to menu");
    printf("\n\nAdd note to file?: ");
    scanf("%d%*c", &num);
    if(num == 1)
    {
        printf("Add note: ");
        scanf("%[^\n]%*c", detailsofpatients[0].patientcomments);
        fopen(Filename,"a");
        fprintf(fp, "%s", detailsofpatients[0].patientcomments);
        fclose(fp);
    }
    Consultantmenuoptions(fp, detailsofpatients,patientLine,Filesearch,  list,end, Filename);
    
}
/*Displays the main title*/
void Displaymaintitle(void)
{
    printf("\n\tACTION ON WEIGHT - CONSULTANT MODE\n");
    printf("\tConsultant - Michel Barnier\n");
    printf("\t===========================");
}
/*Adds a nurse to file*/
int addNurse(struct nurse list[], int end) 
{ 
    printf("\nNurse %d.\nEnter Nurse Name: ", end + 1); 
    scanf("%30[^\n]", list[end].name); 
    printf("Nurse ID: "); 
    scanf("%s%*c", &list[end].ID);
    printf("Password: "); 
    scanf("%s%*c", &list[end].Password); 
    return ++end; 
}
/*Saves nurse to file*/
void save(struct nurse list[], int end) 
{ 
    FILE *fpointer;
    /*if(end < 1) 
    { 
        printf("\nCan't write empty list.\n"); 
        return; 
    } 
    FILE *fpointer; */
    if((fpointer = fopen("Nurseaccounts123.txt", "w")) == NULL) 
    { 
        printf("\nCan't open file Nurseaccounts123.txt\n"); 
        return; 
    } 
    for(int i = 0; i < end; i++) 
    { 
        fprintf(fpointer, "%s %s %s\n", list[end].name, list[end].ID, list[end].Password); 
    } 
    fclose(fpointer); 
    printf("\nFile of %d records written.\n", end); 
}
/*Displays the consultant menu options*/
void Consultantmenuoptions(FILE *fp, struct patientdetailsread detailsofpatients[], int patientLine, struct Searchforthefile Filesearch, struct nurse list[], int end, char Filename[35])
{
	int numofmenu;
	printf("\nCONSULTANT MENU\n");
	printf("=================");
	printf("\n1. READ PATIENTS DETAIL");
	printf("\n2. MAINTENANCE MODE");
	printf("\nChoose an option: ");
	scanf("%d%*c", &numofmenu);
	if(numofmenu == 1)
	{
		Readpatientdetails(fp, detailsofpatients);
		Displaypatientdetails(detailsofpatients,  patientLine, Filesearch, end,fp, list, Filename);
		Consultantmenuoptions(fp, detailsofpatients, patientLine, Filesearch, list, end, Filename);
	}
	else if(numofmenu == 2)
	{
		consultantmenu(fp, detailsofpatients, patientLine, Filesearch, list, end, Filename);
	}	
		
}
/*Displays the consultant menu*/
void consultantmenu(FILE *fp, struct patientdetailsread detailsofpatients[], int patientLine, struct Searchforthefile Filesearch, struct nurse list[], int end, char Filename[35])
{
    int numoption;
    
	printf("\n\n\tMAINTENANCE MODE\n");
	printf("\t================");
	printf("\n1. ADD NURSE ");
	printf("\n2. DELETE NURSE ");
	printf("\n3. CHANGE NURSE's ID ");
	printf("\n4. CHANGE NURSE's PASSWORD ");
	printf("\n5. RETURN BACK TO MENU");
	printf("\n Choose an option: ");
	scanf("%d%*c", &numoption);
	
	if(numoption == 1)
	{
		addNurse(list,end);
		save(list, end);
		Consultantmenuoptions(fp,detailsofpatients, patientLine, Filesearch, list, end, Filename);
	}
	else if(numoption == 2)
	{
	 	 deleteNurse(list, end);
	 	 Consultantmenuoptions(fp,detailsofpatients, patientLine, Filesearch, list, end, Filename);
	}
	else if(numoption == 3)
	{
		
	}
	else if(numoption == 4)
	{
		
	}
	else if(numoption == 5)
	{
		Consultantmenuoptions(fp,detailsofpatients, patientLine, Filesearch, list, end, Filename);
	}
	
}
/*Lists the nurses*/
void listallnurses(struct nurse list[], int end) 
{ 
    if(end < 1) 
    { 
        printf("\nEmpty list. - no nurses found\n"); 
        return; 
    } 
    for(int i = 0; i < end; i++) 
    { 
        printf("Nurse %d\n\t{ ", i + 1); 
        printf("%-20s %03s %s }\n", list[i].name, list[i].ID, 
                list[i].Password); 
    } 
}
/*Deletes the nurses*/
int deleteNurse(struct nurse list[], int end) 
{ 
    int Nursenumber; 
    printf("\nSelect nurse to delete:\n"); 
    listallnurses(list, end); 
    printf("\nNurse number: "); 
    if((scanf("%d%*c", &Nursenumber) != 1) || Nursenumber < 1 
                || Nursenumber > end) 
    { 
        printf("\nERROR - Valid record not selected\n"); 
        return end; 
    } 
    while(Nursenumber <= end) 
    { 
        list[Nursenumber - 1] = list[Nursenumber]; 
        Nursenumber++; 
    } 
    return --end; 
} 
void Consultationlogins(void)
{
    char ConsultantID[10];
    char ConsultantPass[9];
    int i;
    
    printf("\n\nEnter Consultant ID: ");
    scanf("%s", ConsultantID);
    printf("Enter Consultant Password: ");
    scanf("%s", ConsultantPass);
    
    if(strcmp(ConsultantID,"Michel25") == 0)
    { 
        if(strcmp(ConsultantPass,"Barns245")==0)
        { 
        printf("\nLogin Successfull\n");
        printf("\nWelcome Michel Barnier");
        }
    }
    else
        {
            printf("\nIncorrect ID or Password, try again");
            Consultationlogins();
        }
}



/*Clears the buffer*/
void emptytheBuffer(void)
{
        while(getchar() != '\n')
            {
                ;  
            }
}

 
