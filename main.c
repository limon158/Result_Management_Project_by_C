#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    char NAME[30];
    int ROLL;
    float CGPA;
} Student;
int takeTotalStudent(); //functionf to take number of total student:
int takeRoll(); //function to student roll number:
float takeGPA(); //function to take student roll number:
void interchange(Student *a,Student *b); //swapping
void sortStdlist(Student list[],int n); //sort student list gy CGPA:
int main(){
    system("color 9");
    printf("\t\t========RESULT MANAGEMENT DIU======\n");
    int key;
    while(1){
                printf("\n1.ADD NEW STUDENT DATA PRESS[1]");
                printf("\n2.FIND EXISTING STUDENT DATA PRESS[2]");
                printf("\n3.EXIT? PRESS ANY KEY");
                printf("\nEnter choice: ");
                scanf("%d",&key);
                fflush(stdin);
                FILE *fp1;
                FILE *fp2;
                switch (key){
                case 1:{
                        /*STEP-1: tAKING INPUT*/
                        system("cls");
                        char date[25];
                        printf("\nENTER DATE(DD/MM/YY): ");
                        gets(date);
                        fflush(stdin);
                        int total_student=takeTotalStudent();
                        system("cls");
                        Student students[total_student];
                        int i;
                        for(i=0;i<total_student;i++){
                            printf("\nENTER STUDENT DATA FOR STUDENT %d:\n",i+1);
                            printf("NAME: ");
                            fflush(stdin);
                            gets(students[i].NAME);
                            students[i].ROLL=takeRoll();
                            students[i].CGPA=takeGPA();
                            system("cls");
                        }
                        /*STEP-2: SORTING*/
                        sortStdlist(students,total_student);
                        /*STEP-3: LIST OUTPUT PRINTING*/
                        printf("\n---------------------- SORTED NEW ADDED LIST BY CGPA --------------------\n\n");
                        printf("TOTAL STUDENT ADDED : %d\n\n", total_student);
                        printf("\n\tSL.\t\tNAME\t\tROLL NO.\t\tCGPA");
                        printf("\n_________________________________________________________________________");
                        for(i=0;i<total_student;i++){
                            printf("\n\t%d.\t\t%s\t\t%d\t\t%.2f",i+1,students[i].NAME,students[i].ROLL,students[i].CGPA);
                            printf("\n_________________________________________________________________________");
                        }
                        /*STEP-4: FILTERING AND PRINT TO FILE*/
                        fp1=fopen("Bonus.txt","a");
                        fp2=fopen("Normal.txt", "a");
                        if (fp1==NULL||fp2==NULL){
                            printf("\n\t\tError: file not opened\n");
                            return 1;
                        }
                        fprintf(fp1,"\n------ADDING DATE: %s------\n", date);
                        fprintf(fp1,"NAME\tROLL\tCGPA\tBONUS\n\n");
                        fprintf(fp2,"\n------ADDING DATE: %s------\n", date);
                        fprintf(fp2,"NAME\tROLL\tCGPA\tBONUS\n\n");
                        for(i=0;i<total_student;i++){
                            if(students[i].CGPA>3.79)
                                fprintf(fp1, "%s\t%d\t%.2f\t1\n",students[i].NAME,students[i].ROLL, students[i].CGPA);
                            else
                                fprintf(fp2, "%s\t%d\t%.2f\t0\n",students[i].NAME,students[i].ROLL,students[i].CGPA);
                        }
                        fclose(fp2);
                        fclose(fp1);
                        break;
                    }
                case 2:{
                        system("cls");
                        printf("\n1. SEARCH FROM BONUS STUDENT PRESS[1]");
                        printf("\n2. SEARCH FROM NORMAL STUDENT PRESS[2]");
                        printf("\n3. EXIT? PRESS ANY KEY");
                        int key;
                        printf("\nEnter choice: ");
                        scanf("%d",&key);
                        fflush(stdin);
                        Student search_student;
                        int found=0;
                        switch(key)
                        {
                        case 1:{
                            char search_name[30];
                            printf("\n\nENTER STUDENT NAME TO GET DATA: ");
                            gets(search_name);
                            fp1=fopen("Bonus.txt","r");
                            if (fp1==NULL){
                                printf("\n\t\tError: file not opened\n");
                                return 1;
                            }
                            while(fscanf(fp1, "%s %d %f", search_student.NAME,&search_student.ROLL,&search_student.CGPA)!=EOF){
                                if(strcmp(search_student.NAME, search_name)==0){
                                    system("cls");
                                    printf("NAME: %s\n",search_student.NAME);
                                    printf("ROLL: %d\n",search_student.ROLL);
                                    printf("CGPA: %.2f\n",search_student.CGPA);
                                    found=1;
                                    break;
                                }
                            }
                            if (!found)
                            printf("\n\t\tError: Student not found.\n");
                            fclose(fp1);
                        }
                        break;
                        case 2:{
                            char search_name[30];
                            printf("\n\nENTER STUDENT NAME TO GET DATA: ");
                            gets(search_name);
                            fp2=fopen("Normal.txt","r");
                            if (fp2==NULL){
                                printf("\n\t\tError: file not opened\n");
                                return 1;
                            }
                            while (fscanf(fp1, "%s %d %f",search_student.NAME,&search_student.ROLL,&search_student.CGPA)!=EOF){
                                if (strcmp(search_student.NAME, search_name)==0){
                                    system("cls");
                                    printf("NAME: %s\n",search_student.NAME);
                                    printf("ROLL: %d\n",search_student.ROLL);
                                    printf("CGPA: %.2f\n",search_student.CGPA);
                                    found=1;
                                    break;
                                }
                            }
                            if(!found)
                            printf("\n\t\tError: Student not found.\n");
                            fclose(fp2);
                        }
                        break;
                        default:
                            return 0;
                        }
                        break;
                    }
                default:
                    return 0;
            }
    }
    return 0;
}

int takeTotalStudent() {
    int n;
    char input[50];
    while(1){
        printf("\n\nTOTAL STUDENT: ");
        if(fgets(input, sizeof(input),stdin)){
            if(sscanf(input,"%d",&n)==1){ //if character type input print Error
                if(n>0) //if negetive integer print error
                return n;
                printf("\t\t\tError: No. of student cannot be less than 1.");
            }else{
                printf("\t\t\tError: NaN invalid input.");
            }
        }
    }
}
int takeRoll() {
    int n;
    char input[50];
    while(1){
        printf("ROLL: ");
        if(fgets(input, sizeof(input),stdin)){
            if(sscanf(input,"%d",&n)==1){ //if character type input print Error
                if(n>0) //if negetive integer print error
                return n;
                printf("\t\t\tError: Roll of student cannot be less than 1.\n");
            }else{
                printf("\t\t\tError: NaN invalid input.\n");
            }
        }
    }
}
float takeGPA(){
    float n;
    char input[50];
    while(1){
        printf("CGPA: ");
        if(fgets(input, sizeof(input),stdin)){
            if(sscanf(input,"%f",&n)==1){ //if character type input print Error
                if(n>=1&&n<=4) //if negetive integer print error
                return n;
                printf("\t\t\tError: CGPA of student have to (1.00 to 4.00)\n");
            }else{
                printf("\t\t\tError: NaN invalid input.\n");
            }
        }
    }
}
void interchange(Student *std1,Student *std2){
    Student temp=*std1;
    *std1=*std2;
    *std2=temp;
}
void sortStdlist(Student list[],int n){
    for(int i=0; i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(list[j].CGPA<list[j+1].CGPA){
                interchange(&list[j],&list[j+1]);
            }
        }
    }
}
