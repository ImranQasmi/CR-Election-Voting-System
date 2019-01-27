#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>

typedef struct{
	char name[100] ,
		 roll[100];
}candidate_info_t;

typedef struct{
	candidate_info_t candidates_per_sec[5];
	char section[5];
	int votes[5];
	float percent[5];
}candidate_t;

typedef struct{
	candidate_info_t students_per_sec[100];
}student_t;

int passwordCheck(char *passWord);
int resetPass(char *resetCode);
int candidateChoice(candidate_t *total_candidates, student_t *total_students, int *cand_per_sec, char sec, int *access_poll, int *student_in_sec);
void viewCandidates(candidate_t *total_candidsates, int access_poll);
void displayStudent(student_t total_stu_display, char display_section);
void previousResult();
int startPolling(candidate_t *total_candidates, student_t *total_students, int cand_per_sec, char sec, int student_in_sec);
int voteCast(candidate_info_t *repeat_ID, char *voter_ID, int itterations);

int main()
{
	int a,tie=0; int tries=1, access_poll=0 , max=0 , student_in_sec=0 ;
	char choice='0' , display_section,j=0;
	
	int valid=0 , cand_per_sec=0 , access=0 ;
	char password[16] , oldPass[16] , secureCode[10] , sec;
	candidate_t total_candidates;
	student_t total_students , total_stu_display;
	
	while(choice!='7')
	{
	system("cls");
	
	printf("\n\t\t");
	for(a=0; a<50; a++)
	printf("=");
	printf("\n\n\t\t\t\tVOTING MANAGEMENT SYSTEM\n\n");
	printf("\t\t");
	
	for(a=0; a<50; a++)
	printf("=");
	
	printf("\n\n\t\t1.\t\t Start Polling");
	printf("\n\n\t\t2.\t\t Choose Candidates");
	printf("\n\n\t\t3.\t\t View Candidates");
	printf("\n\n\t\t4.\t\t View Students");
	printf("\n\n\t\t5.\t\t Change Password");
	printf("\n\n\t\t6.\t\t View Previous Result");
	printf("\n\n\t\t7.\t\t Exit\n\n");
	choice=getch();
	
	if(choice<'1' || choice>'7')
	{
		printf("\nInvalid Choice!");
		getch();
	}
	else
	{
		system("cls");
		switch(choice)
		{
			case '1':
				if (tries<=5)
				{
					printf("\n\n\n\n\t\t\tEnter password: ");
					char *p;
					p=(char*)calloc(100,sizeof(char));
					int i=0;
					p[i]=getch();
					while(p[i]!=13)
					{
						if(p[i++]!=NULL);
							printf("*");
						p[i]=getch();
					}
					p[i]='\0';
					strcpy(password, p);
					
					if (strlen(password)>15 || strlen(password)<3)
					{
						printf("\n\t\t\tERROR. Incorrect Password");
						tries++;
						getch();
					}
					else
					{
						valid=passwordCheck(password);
						switch(valid)
						{
							case 1:
								if (access_poll>=1)
								{
									printf("\n\t\t\t");
									system("pause");
									tie=startPolling(&total_candidates, &total_students, cand_per_sec,sec,student_in_sec);
									if(tie==1)break;
									else
									{
									system("cls");
									printf("\n\n\t\t\tSYSTEM BROUGHT TO YOU BY:\n\n\t\t\tFarhan Ahmed (16K-3798)\n\t\t\tAakash Panhwar(16K-3787)\n\t\t\tWaseem hassan (16K-3773)\n\t\t\tFurqan Polani (16K-3775)\n\n");
									system("pause");
									exit(1);
									}
								}
								else
								{
									printf("\n\t\tYou need to select at least 2 candidates!\n" );
									getch();
								}
								break;
							case 0:
								printf("\n\t\t\tERROR. Incorrect Password");
								tries++;
								getch();
								break;
						}
					}
				}
				else
				{
					printf("\n\n\t\tSet new password. Please enter security code\n\n\t\t\t\t");
					
					char *s;
					s=(char*)calloc(100,sizeof(char));
					scanf("%s",s);
					strcpy(secureCode, s);
					free(s);
					
					resetPass(secureCode);
					getch();
				}
				break;
			case '2':
				printf("\n\n\n\n\t\t\tEnter password: ");
				
				char *q;
					q=(char*)calloc(100,sizeof(char));
					q[j]=getch();
					while(q[j]!=13)
					{
						if(q[j++]!=NULL);
						printf("*");
						q[j]=getch();
					}
					q[j]='\0';
				strcpy(password, q);
				free(q);
					
				valid=passwordCheck(password);
				if (valid==1)
				{
					printf("\n\n\t\t\tEnter section: ");
					scanf(" %c",&sec);
					if (islower(sec))
					{
						sec=toupper(sec);
					}
					while (sec<'A' || sec>'I')
					{
						printf("\n\t\t\tInvald selection!");
						printf("\n\n\t\t\tEnter section: ");
						scanf(" %c",&sec);
						if (islower(sec))
						{
							sec=toupper(sec);
						}
					}
					if (max==0)
					{
						candidateChoice(&total_candidates,&total_students,&cand_per_sec, sec , &access_poll, &student_in_sec);
						max=1;
					}
					else
					{
						printf("\n\t\t\tCandidates already chosen");
						getch();
					}
				}
				else
				{
					printf("\n\n\n\n\t\t\tERROR. Incorrect Password");
					getch();
				}
				break;
			case '3':
				if (access_poll>=1)
				{
					viewCandidates(&total_candidates,access_poll);
					getch();
				}
				else
				{
					printf("\n\n\n\t\t\tNo Candidates Selected!\n" );
					getch();
				}
				break;
			case '4':
				printf("\n\n\n\t\tEnter section: ");
				scanf(" %c",&display_section);
				if(islower(display_section))
				{
					display_section=toupper(display_section);
				}
				while (display_section<'A' || display_section>'I')
				{
					printf("\n\t\t\tInvald selection!");
					printf("\n\n\t\t\tEnter section: ");
					scanf(" %c",&display_section);
					if(islower(display_section))
					{
						display_section=toupper(display_section);
					}
				}
				displayStudent(total_stu_display, display_section);
				break;
			case '5':
				printf("\n\n\t\tEnter old password: ");
				
				char *r;
					r=(char*)calloc(100,sizeof(char));
					j=0;
					r[j]=getch();
					while(r[j]!=13)
					{
						if(r[j++]!=NULL);
						printf("*");
						r[j]=getch();
					}
					r[j]='\0';
				strcpy(oldPass, r);
				free(r);
				
				FILE *pass;
				pass=fopen("password.txt","r");
				fscanf(pass,"%s",&password);
				if (strcmp(oldPass,password)==0)
				{
					printf("\n\n\t\tEnter security code: ");
					
					char *c;
					c=(char*)calloc(100,sizeof(char));
					j=0;
					c[j]=getch();
					while(c[j]!=13)
					{
						if(c[j++]!=NULL);
						printf("*");
						c[j]=getch();
					}
					c[j]='\0';
					strcpy(secureCode, c);
					free(c);
					
					resetPass(secureCode);
				}
				else
				{
					printf("\n\n\t\tERROR. Incorrect password\n\n\t\t");
		
					getch();
				}
				fclose(pass);
				break;
			case '6':
				previousResult();
				break;
			}
		}
	}
	system("cls");
	printf("\n\n\t\t\tSYSTEM BROUGHT TO YOU BY:\n\n\t\t\tFarhan Ahmed (16K-3798)\n\t\t\tAakash Panhwar(16K-3787)\n\t\t\tWaseem hassan (16K-3773)\n\t\t\tFurqan Polani (16K-3775)\n\n");
	system("pause");
	return 0;
}

int passwordCheck(char *passWord)
{
	int x;
	char verify[16];
	FILE *pass;
	
	pass=fopen("password.txt","r");
	fscanf(pass,"%s",&verify);
	
	if(strcmp(verify, passWord)==0)
	x=1;
	else
	x=0;
	fclose(pass);
	return x;
}

int resetPass(char *resetCode)
{
	char verify[15], ch[16], newPass[16];
	FILE *pass;
	
	pass=fopen("password.txt","r");
	fscanf(pass,"%s",&ch);
	fscanf(pass,"%s",&verify);
	
	if ( strcmp(verify,resetCode)==0)
	{
		fclose(pass);
		pass=fopen("password.txt","w");
		printf("\n\n\t\tEnter New Password: ");
		
		char *p;
		p=(char*)calloc(100,sizeof(char));
		int i=0;
		p[i]=getch();
		while(p[i]!=13)
		{
			if(p[i++]!=NULL);
			printf("*");
			p[i]=getch();
		}
		p[i]='\0';
		strcpy(newPass, p);
		free(p);
		
		while( strlen(newPass) > 15 || strlen(newPass) < 3 )
		{
			printf("\n\n\t\tPassword should contain 3 - 15 characters!");
			printf("\n\n\t\tEnter New Password: ");
			
			p=(char*)calloc(100,sizeof(char));
	    	int i=0;
			p[i]=getch();
			while(p[i]!=13)
			{
				if(p[i++]!=NULL);
				printf("*");
				p[i]=getch();
			}
			p[i]='\0';
			strcpy(newPass, p);
			free(p);
			
		}
		fprintf(pass,"%s\n%s",newPass,"1234");
		printf("\n\n\t\tPassword changed.\n");
		system("pause");
		fclose(pass);
	}
	else
	{
		printf("\n\n\t\t\tInvalid Code");
		getch();
	}
	fclose(pass);
}

int candidateChoice(candidate_t *total_candidates, student_t *total_students, int *cand_per_sec, char sec, int *access_poll, int *student_in_sec)
{
	int i , j=0 ,k, found=0 , num_candidates ;
	char candidate_roll[15];
	FILE *vote;
	
	printf("\n\t\t\tEnter no. of candidates: ");
	scanf("%d",&num_candidates);
	while (num_candidates<2 || num_candidates>5)
	{
		printf("\n\t\t\tThere should be 2-5 candidates!");
		printf("\n\t\t\tEnter no. of candidates: ");
		scanf("%d",&num_candidates);
	}
	
	switch(sec)
	{
		case 'A':
			vote=fopen("record-A.txt","r");
			fscanf(vote,"%d",student_in_sec);
			for(i=0; i<*student_in_sec; i++)
			{
				fscanf(vote,"%s",total_students->students_per_sec[i].roll);
				fscanf(vote,"%[^\n]s",total_students->students_per_sec[i].name);
			}
			fclose(vote);
			break;
		case 'B':
			vote=fopen("record-B.txt","r");
			fscanf(vote,"%d",student_in_sec);
			for(i=0; i<*student_in_sec; i++)
			{
				fscanf(vote,"%s",total_students->students_per_sec[i].roll);
				fscanf(vote,"%[^\n]s",total_students->students_per_sec[i].name);
			}
			fclose(vote);
			break;
		case 'C':
			vote=fopen("record-C.txt","r");
			fscanf(vote,"%d",student_in_sec);
			for(i=0; i<*student_in_sec; i++)
			{
				fscanf(vote,"%s",total_students->students_per_sec[i].roll);
				fscanf(vote,"%[^\n]s",total_students->students_per_sec[i].name);
			}
			fclose(vote);
			break;
		case 'D':
			vote=fopen("record-D.txt","r");
			fscanf(vote,"%d",student_in_sec);
			for(i=0; i<*student_in_sec; i++)
			{
				fscanf(vote,"%s",total_students->students_per_sec[i].roll);
				fscanf(vote,"%[^\n]s",total_students->students_per_sec[i].name);
			}
			fclose(vote);
			break;
		case 'E':
			vote=fopen("record-E.txt","r");
			fscanf(vote,"%d",student_in_sec);
			for(i=0; i<*student_in_sec; i++)
			{
				fscanf(vote,"%s",total_students->students_per_sec[i].roll);
				fscanf(vote,"%[^\n]s",total_students->students_per_sec[i].name);
			}
			fclose(vote);
			break;
		case 'F':
			vote=fopen("record-F.txt","r");
			fscanf(vote,"%d",student_in_sec);
			for(i=0; i<*student_in_sec; i++)
			{
				fscanf(vote,"%s",total_students->students_per_sec[i].roll);
				fscanf(vote,"%[^\n]s",total_students->students_per_sec[i].name);
			}
			fclose(vote);
			break;
		case 'G':
			vote=fopen("record-G.txt","r");
			fscanf(vote,"%d",student_in_sec);
			for(i=0; i<*student_in_sec; i++)
			{
				fscanf(vote,"%s",total_students->students_per_sec[i].roll);
				fscanf(vote,"%[^\n]s",total_students->students_per_sec[i].name);
			}
			fclose(vote);
			break;
		case 'H':
			vote=fopen("record-H.txt","r");
			fscanf(vote,"%d",student_in_sec);
			for(i=0; i<*student_in_sec; i++)
			{
				fscanf(vote,"%s",total_students->students_per_sec[i].roll);
				fscanf(vote,"%[^\n]s",total_students->students_per_sec[i].name);
			}
			fclose(vote);
			break;
		case 'I':
			vote=fopen("record-I.txt","r");
			fscanf(vote,"%d",student_in_sec);
			for(i=0; i<*student_in_sec; i++)
			{
				fscanf(vote,"%s",total_students->students_per_sec[i].roll);
				fscanf(vote,"%[^\n]s",total_students->students_per_sec[i].name);
			}
			fclose(vote);
			break;
		}
		
		while (*cand_per_sec<num_candidates)
			{
				printf("\n\n\t\t\tSECTION '%c' RECORD\n\n",sec);
				for(i=0; i<*student_in_sec; i++)
				{
					printf("\t\t\t%s",total_students->students_per_sec[i].roll);
					printf("\t%s\n",total_students->students_per_sec[i].name);
				}
				printf("\n\n\t\t\tEnter roll no. of candidate%d: ",*cand_per_sec+1);
				scanf("%s",candidate_roll);
				float GPA;
				for (k=0; k<*student_in_sec; k++)
				{
					found=0;
					if (strcmp(total_students->students_per_sec[k].roll , candidate_roll)==0)
					{
						printf("\n\t\t\tEnter the GPA of Candidate%d: ",j+1);
						scanf("%f",&GPA);
						if(GPA<2.0)
						{
							found=-1;
							break;
						}
						else
						{
						
						strcpy( total_candidates->candidates_per_sec[j].name, total_students->students_per_sec[k].name);
						strcpy( total_candidates->candidates_per_sec[j].roll, total_students->students_per_sec[k].roll);
						total_candidates->section[j]=sec;
						
						printf("\n\n\t\t\tYour candidate%d: %s\n", j+1 , total_candidates->candidates_per_sec[j].name);
						*cand_per_sec=*cand_per_sec+1;
						
						j++;
						found=1;
						*access_poll = *access_poll + 1;
						getch();
						break;
						}
					}
				}
				if(found==-1)
				{
					printf("\n\t\t\tThe Candidate is not eligible of becoming a CR, Select any other candidate.");
					getch();
				}
				if(found==0)
				{
					printf("\n\t\t\tRecord not found!");
					getch();
				}
				system("cls");
			}
	return 1;
}

void viewCandidates(candidate_t *total_candidates, int access_poll)
{
	int i;
	printf("\n\n\n\t\t\tCandidates:\n\n\n");
	
	for(i=0;i<access_poll;i++)
	{
		printf("%d-\t\t\t%s\t", i+1,total_candidates->candidates_per_sec[i].name);
		printf("\t'%c'\t%s\n\n", total_candidates->section[i], total_candidates->candidates_per_sec[i].roll);
	}
	getch();
}

void displayStudent(student_t total_stu_display, char display_section)
{
	FILE *display;
	int i , student_sec;
	
	printf("\n\n\t\t\tSECTION '%c' RECORD\n\n",display_section);
	switch(display_section)
	{
		case 'A':
			display=fopen("record-A.txt","r");
			fscanf(display,"%d",&student_sec);
			for(i=0; i<student_sec; i++)
			{
				fscanf(display,"%s",total_stu_display.students_per_sec[i].roll);
				fscanf(display,"%[^\n]s",total_stu_display.students_per_sec[i].name);
				printf("\t\t%s\t%s\n", total_stu_display.students_per_sec[i].roll, total_stu_display.students_per_sec[i].name);
			}
			fclose(display);
			break;
		case 'B':
			display=fopen("record-B.txt","r");
			fscanf(display,"%d",&student_sec);
			for(i=0; i<student_sec; i++)
			{
				fscanf(display,"%s",total_stu_display.students_per_sec[i].roll);
				fscanf(display,"%[^\n]s",total_stu_display.students_per_sec[i].name);
				printf("\t\t%s\t%s\n", total_stu_display.students_per_sec[i].roll, total_stu_display.students_per_sec[i].name);
			}
			fclose(display);
			break;
		case 'C':
			display=fopen("record-C.txt","r");
			fscanf(display,"%d",&student_sec);
			for(i=0; i<student_sec; i++)
			{
				fscanf(display,"%s",total_stu_display.students_per_sec[i].roll);
				fscanf(display,"%[^\n]s",total_stu_display.students_per_sec[i].name);
				printf("\t\t%s\t%s\n", total_stu_display.students_per_sec[i].roll, total_stu_display.students_per_sec[i].name);
			}
			fclose(display);
			break;
		case 'D':
			display=fopen("record-D.txt","r");
			fscanf(display,"%d",&student_sec);
			for(i=0; i<student_sec; i++)
			{
				fscanf(display,"%s",total_stu_display.students_per_sec[i].roll);
				fscanf(display,"%[^\n]s",total_stu_display.students_per_sec[i].name);
				printf("\t\t%s\t%s\n", total_stu_display.students_per_sec[i].roll, total_stu_display.students_per_sec[i].name);
			}
			fclose(display);
			break;
		case 'E':
			display=fopen("record-E.txt","r");
			fscanf(display,"%d",&student_sec);
			for(i=0; i<student_sec; i++)
			{
				fscanf(display,"%s",total_stu_display.students_per_sec[i].roll);
				fscanf(display,"%[^\n]s",total_stu_display.students_per_sec[i].name);
				printf("\t\t%s\t%s\n", total_stu_display.students_per_sec[i].roll, total_stu_display.students_per_sec[i].name);
			}
			fclose(display);
			break;
		case 'F':
			display=fopen("record-F.txt","r");
			fscanf(display,"%d",&student_sec);
			for(i=0; i<student_sec; i++)
			{
				fscanf(display,"%s",total_stu_display.students_per_sec[i].roll);
				fscanf(display,"%[^\n]s",total_stu_display.students_per_sec[i].name);
				printf("\t\t%s\t%s\n", total_stu_display.students_per_sec[i].roll, total_stu_display.students_per_sec[i].name);
			}
			fclose(display);
			break;
		case 'G':
			display=fopen("record-G.txt","r");
			fscanf(display,"%d",&student_sec);
			for(i=0; i<student_sec; i++)
			{
				fscanf(display,"%s",total_stu_display.students_per_sec[i].roll);
				fscanf(display,"%[^\n]s",total_stu_display.students_per_sec[i].name);
				printf("\t\t%s\t%s\n", total_stu_display.students_per_sec[i].roll, total_stu_display.students_per_sec[i].name);
			}
			fclose(display);
			break;
		case 'H':
			display=fopen("record-H.txt","r");
			fscanf(display,"%d",&student_sec);
			for(i=0; i<student_sec; i++)
			{
				fscanf(display,"%s",total_stu_display.students_per_sec[i].roll);
				fscanf(display,"%[^\n]s",total_stu_display.students_per_sec[i].name);
				printf("\t\t%s\t%s\n", total_stu_display.students_per_sec[i].roll, total_stu_display.students_per_sec[i].name);
			}
			fclose(display);
			break;
		case 'I':
			display=fopen("record-I.txt","r");
			fscanf(display,"%d",&student_sec);
			for(i=0; i<student_sec; i++)
			{
				fscanf(display,"%s",total_stu_display.students_per_sec[i].roll);
				fscanf(display,"%[^\n]s",total_stu_display.students_per_sec[i].name);
				printf("\t\t%s\t%s\n", total_stu_display.students_per_sec[i].roll, total_stu_display.students_per_sec[i].name);
			}
			fclose(display);
			break;
	}
	getch();
}

void previousResult()
{
	system("cls");
	char cand[100] , erase[100] ;
	FILE *prev;
	prev=fopen("Candidate.txt","r");
	if (prev==NULL)
	{
		printf("\n\n\n\n\t\t\t\tNo Record Found\n");
		getch();
	}
	else
	{
		while (!feof (prev))
		{
			fflush(stdin);
			fgets(cand,100,prev);
			if (strcmp(erase,cand)!=0)
			printf("\n\n\t\t   %s",cand);
			strcpy(erase,cand);
		}
		getch();
		fclose(prev);
	}
}

int startPolling(candidate_t *total_candidates, student_t *total_students, int cand_per_sec, char sec,  int student_in_sec)
{
	int a , i=0 , r=0 , voteChoice , validCount=0 , self=0 , repeat_vote=0 , total_votes=0 , validPass=0 , trigger=0 , trigger1=0;
	int max_votes=0 , tie=0 , winner;
	char voter_ID[15] , password[15];
	candidate_info_t repeat_ID[student_in_sec];
	for(a=0; a<cand_per_sec; a++)
	{
		total_candidates->votes[a]=0;
		total_candidates->percent[a]=0;
	}
	do
	{
		if (total_votes >= student_in_sec - cand_per_sec)
		{
			printf("\n\t\t\tAll votes cast\n");
			printf("\n\t\t\tPress any key to view results\n\t\t");
			getch();
			break;
		}
		validCount=0;
		i=0;
		self=0;
		system("cls");
		printf("\t\t");
		for(a=0; a<50; a++)
		{
			printf("=");
		}
		printf("\n\n\t\t\t\tSECTION '%c' VOTING\n\n\t\t", sec);
		for(a=0; a<50; a++)
		{
			printf("=");
		}
		printf("\n\n\t\t\tCandidate\t\t\tVotes\n\n");
		for(a=0; a<cand_per_sec; a++)
		{
			printf("\t%d- %s ( %s )\t\t\t",a+1 , total_candidates->candidates_per_sec[a].name , total_candidates->candidates_per_sec[a].roll);
			printf(" %d\n\n", total_candidates->votes[a]);
		}
		printf("\t%d - Stop Polling\n\n",cand_per_sec+1);
		printf("\n\t\t\tSelect choice: ");
		scanf("%d",&voteChoice);
		while (voteChoice == cand_per_sec+1 && total_votes == 0)
		{
			printf("\n\t\t\tPlease cast a vote first!");
			printf("\n\t\t\tSelect choice: ");
			scanf("%d",&voteChoice);
		}
		if (voteChoice == cand_per_sec+1)
		{
			trigger=0;
			printf("\n\t\t\tEnter password: ");
			
			char *p;
			p=(char*)calloc(100,sizeof(char));
			int i=0;
			p[i]=getch();
			while(p[i]!=13)
			{
				if(p[i++]!=NULL);
				printf("*");
				p[i]=getch();
			}
			p[i]='\0';
					
			strcpy(password, p);
			free(p);
			
			validPass=passwordCheck(password);
			switch(validPass)
			{
				case 1:
					trigger=1;
					break;
				case 0:
					printf("\n\t\t\tERROR.Incorrect Password");
					printf("\n\t\t\tEnter password: ");
					
					p=(char*)calloc(100,sizeof(char));
					scanf("%s",p);
					strcpy(password, p);
					free(p);
					
					validPass=passwordCheck(password);
					trigger1=1;
					break;
			}
			if (trigger==1 || trigger1==1)
			break;
		}
		if (voteChoice>cand_per_sec+1||voteChoice<=0)
		{
			printf("\n\t\t\tInvalid choice");
			getch();
		}
		else
		{
			printf( "\n\t\t\tEnter your roll no: ");
			scanf("%s",voter_ID);
			repeat_vote=voteCast(repeat_ID ,voter_ID,total_votes);
			while(repeat_vote==1)
			{
				printf("\n\n\t\t\t\tYour vote has already been cast");
				printf( "\n\t\t\tEnter your roll no: ");
				scanf("%s",voter_ID);
				repeat_vote=voteCast(repeat_ID ,voter_ID,total_votes);
			}
			for (a=0; a<student_in_sec; a++)
			{
				i=0;
				if (strcmp(total_students->students_per_sec[a].roll,voter_ID)==0)
				{
					while(i<student_in_sec)
					{
						if ( strcmp(total_students->students_per_sec[a].roll,total_candidates->candidates_per_sec[i].roll)==0)
						{
							printf("\n\tSorry, a candidate cannot vote for himself or other candidates!");
							self=1;
							break;
						}	
						i++;
					}
					if(self!=1)
					{
						printf("\n\t\t\tIdentity confirmed, vote added");
						total_candidates->votes[voteChoice-1]++;
						validCount++;
						total_votes++;
						strcpy(repeat_ID[r++].roll,voter_ID);
						break;
					}
//					i++;
				}
			}
			if (validCount==0 && self==0)
			{
				printf("\n\t\t\tSorry, you are ineligible to vote!");
			}
			getch();
		}
	}while(voteChoice!=cand_per_sec+1);
	system("cls");
	printf("\t\t");
	for(a=0; a<50; a++)
	{
		printf("=");
	}
	printf("\n\n\t\t\t\tVOTING RESULTS\n\n\t\t", sec);
	for(a=0; a<50; a++)
	{
		printf("=");
	}
	printf("\n\n\t\t\t     TOTAL VOTES CAST: %d", total_votes);
	printf("\n\n\t\t\tTOTAL NUMBER OF CANDIDATES: %d",cand_per_sec);
	printf("\n\n\tCandidate\t\t      Votes\t\tPercent of votes\n\n");
	printf("\t");
	for(a=0; a<64; a++)
	{
		printf("-");
	}
	for(a=0; a<cand_per_sec; a++)
	{
		if (total_candidates->votes[a] == max_votes && max_votes!=0)
		{
			tie++;
		}
		if (total_candidates->votes[a] > max_votes)
		{
			max_votes=total_candidates->votes[a];
			winner=a;
		}
		total_candidates->percent[a] = (float) total_candidates->votes[a] * 100 / total_votes ;
	}
	for(a=0; a<cand_per_sec; a++)
	{
		printf("\n\n\t%s\t\t\t%d\t\t\t", total_candidates->candidates_per_sec[a].name, total_candidates->votes[a]);
		printf("%.1f%%\n",total_candidates->percent[a]);
	}
	printf("\n\t");
	for(a=0; a<64; a++)
	{
		printf("-");
	}
	if (tie==0)
	{
		printf("\n\n\t\tWINNER: %s\t%s\n", total_candidates->candidates_per_sec[winner].name,total_candidates->candidates_per_sec[winner].roll);
		printf("\n\t\tVOTES:\t\t%d\n\n\t", max_votes);
		for(a=0; a<64; a++)
		{
			printf("-");
		}
		FILE *rec;
		rec=fopen("Candidate.txt","a");
		fprintf(rec,"%s\t%s\tSection'%c'",total_candidates->candidates_per_sec[winner].name,total_candidates->candidates_per_sec[winner].roll,sec);
		fclose(rec);
	}
	else
	{
		printf("\n\n\t\t\t\tVoting tied!\n\n\t");
		for(a=0; a<64; a++)
		{
			printf("-");
		}
		printf("\n\n\t\t\t\tStart Polling Again!\n\n\t");
		system("pause");
		return 1;
		
	}
	printf("\n\n\t\t\t\tVOTES CAST BY \n\n");
	for (a=0; a<total_votes; a++)
	{
		printf("\t\t\t\t%s\n\n",repeat_ID[a].roll);
	}
	system("pause");
}

int voteCast(candidate_info_t *repeat_ID, char *voter_ID, int itterations)
{
	if (itterations==0)
	return 0;
	int i=0;
	for(i=0; i<itterations; i++)
	{
		if (strcmp(voter_ID,repeat_ID[i].roll)==0)
		{
			return 1;
			break;
		}
	}
	return 0;
}
