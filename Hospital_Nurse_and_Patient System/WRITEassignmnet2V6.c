/***********************************************************************
 * WRITEassignmnet2V6.c
 * Program to write patient details
 * Mohammed Naeem
 * Version 6
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
/*struct with the patient details*/
struct patientdetails
{
    char firstname[20];
    char lastname[20];
    int Day;
    int month;
    int year;
    int patientheight;
    int patientwaistmeasure;
    int patientweight;
    char patientcomments[300];
};
/*Struct with the nurse accounts*/
struct Nursesaccounts
{
    char name[30];
    char ID[9];
    char Password[9];
};
/*prodotypes*/
struct patientdetails getpatientdetails(void);
void Savepatientdetailstofile(struct patientdetails patient);
void Displaymaintitle(void);
int Readnursesaccounts(struct Nursesaccounts nursesaccountsdetail[],
 FILE *fpoints);
void Displaynursesdetails(struct Nursesaccounts nursesaccountsdetail[],
int patientLine);
FILE *opennursedfiletoread(void);
void Nurselogins(void);
/*Main function*/
int main(void)
{
    struct Nursesaccounts nursesaccountsdetail[200];
	Displaymaintitle();
	Nurselogins();
	FILE *fpoints = opennursedfiletoread();
	int patientLine = Readnursesaccounts(nursesaccountsdetail,fpoints);
    struct patientdetails apatient = getpatientdetails(); 
	Savepatientdetailstofile(apatient);
	return 0;
} /*Displaying main title*/
void Displaymaintitle(void)
{
	printf("\tENTER PATIENT DETAILS\n");
	printf("\t=====================");
} /*Getting patients details*/
struct patientdetails getpatientdetails(void)
{
    struct patientdetails patient;
    printf("\n\nEnter patient first name: ");
    scanf("%s", patient.firstname);
    printf("Enter patient last name: ");
    scanf("%s", patient.lastname);
    printf("\nEnter Date of birth (D/M/YYYY): ");
    scanf("%d/%d/%d", &patient.Day, &patient.month, &patient.year);
    printf("\nEnter Patient height(cm): ");
    scanf("%d", &patient.patientheight);
    printf("\nEnter Patient waist measurement(cm): ");
    scanf("%d", &patient.patientwaistmeasure); 
    printf("\nEnter Patient weight(kg): ");
    scanf("%d", &patient.patientweight);
   return patient; 
}
/* Save the details to file*/
void Savepatientdetailstofile(struct patientdetails patient)
{
	char nameoffile[25];
	sprintf(nameoffile, "%s%d%d%d.aow", patient.lastname, patient.Day, 
    patient.month, patient.year);
	FILE *fout = fopen(nameoffile, "w"); 
	
	fprintf(fout, "%s %s", patient.firstname, patient.lastname);
	fprintf(fout, "\n%d/%d/%d", patient.Day, patient.month,
     patient.year);
	fprintf(fout, "\n%dcm", patient.patientheight);
	fprintf(fout, "\n%dcm", patient.patientwaistmeasure);
	fprintf(fout, "\n%dkg", patient.patientweight);
	fprintf(fout, "\n%s\n", patient.patientcomments);
}
/*Opening files to read*/
FILE *opennursedfiletoread(void) 
{ 
    FILE *fpoints =  fopen("Nurseaccounts.txt", "r");
    
    if(!(fpoints = fopen("Nurseaccounts.txt", "r")))
    { 
        puts("\nERROR - Unable to open File\n"); 
        exit(1); 
    } 
    return fpoints; 
} 
/*Reading nurse accounts*/
int Readnursesaccounts(struct Nursesaccounts nursesaccountsdetail[], 
FILE *fpoints)
{
	int count = 0;
	while(fscanf(fpoints,"%s", nursesaccountsdetail[count].name) == 1)
	{
		count++;
	}
		while(fscanf(fpoints,"%s", nursesaccountsdetail[count].ID) == 1)
	{
		count++;
	}
		while(fscanf(fpoints,"%s", nursesaccountsdetail[count].Password) == 1)
	{
		count++;
	}
	fclose(fpoints);
	return count;
}
/*Displaying nurses details*/
void Displaynursesdetails(struct Nursesaccounts nursesaccountsdetail[],
int patientLine)
{
	for(int i = 0; i < patientLine; i++) 
    { 
        printf("\n%s", nursesaccountsdetail[i].name);
		printf("%s\n", nursesaccountsdetail[i].ID);
		printf("%s\n", nursesaccountsdetail[i].Password);	
    } 
}
/*Program to get nurse logins"*/
void Nurselogins(void)
{
    char nurseID[10];
    char nursespass[9];
    int i, len = 0;
    
    printf("\n\nEnter nurse ID: ");
    scanf("%s", nurseID);
    printf("Enter Nurse Password: ");
    scanf("%s", nursespass);  
    if(strcmp(nurseID,"Starmer9") == 0)
    { 
        if(strcmp(nursespass,"Star1209")==0)
        { 
        printf("\nLogin Successfull\n");
        printf("\nWelcome Keir Starmer");
        }
    }
    else if(strcmp(nurseID,"Johnson3") == 0)
    { 
        if(strcmp(nursespass,"Bojo2468")==0)
        
        { 
        printf("\nLogin Successfull\n");
        printf("\nWelcome Boris Johnson");
        }
    }
    else if(strcmp(nurseID,"Lucas678") == 0)
    { 
        if(strcmp(nursespass,"Carlu098")==0)
        
        { 
        printf("\nLogin Successfull\n");
        printf("\nWelcome Caroline Lucas");
        }
    }   
    else if(strcmp(nurseID,"Sturge09") == 0)
    { 
        if(strcmp(nursespass,"Nicole70")==0)
        
        { 
        printf("\nLogin Successfull\n");
        printf("\nWelcome Nicola Sturgeon");
        }
    }
     else if(strcmp(nurseID,"Eddie254") == 0)
    { 
        if(strcmp(nursespass,"Davey123")==0)
        
        { 
        printf("\nLogin Successfull\n");
        printf("\nWelcome Ed Davey");
        }
    }
    else
    {
        printf("\nIncorrect ID or Password, try again");
        Nurselogins();
    }
}


