#include<stdio.h>
#include<stdlib.h>
int lines;
int machines;
int check,check1=1;
int oppath[100];      //optimised path
int time[100][100];  //each array for min time to reach the exit from the staring point of each of the lines
int path[100][100]; //the optimsed path followed by each of the starting machine of each line to reach the last machine
void display(int e1[],int e2[],int **w1,int ***w2)
{
	int i,j,k;
	printf("1. The entry time for each of the line:\n");
	for(i=0;i<lines;i++)
    		{
    			printf("Line %d: ",i+1);
    			printf("%d",e1[i]);
    			printf("\n");
			}
	printf("\n2. The time taken to process the product in each machine:\n");
	for(i=0;i<lines;i++)
    		{
        		printf("Line %d\n",i+1);
        		for(j=0;j<machines;j++)
        		{
            		printf("    Machine %d: ",j+1);
            		printf("%d",w1[i][j]);
            		printf("\n");
        		}
    		}
    printf("\n3. The time taken to travel from a machine in one level to the machines in the other level:\n\n");
    	for(i=0;i<lines;i++)
			{
				for(j=0;j<machines-1;j++)
				{
					printf("The time taken to travel from Machine %d of Line %d to: \n",j+1,i+1);
					for(k=0;k<lines;k++)
					{	printf("Machine %d of line %d: ",j+2,k+1);
						printf("%d",w2[i][j][k]);
						printf("\n");
					}
				}
			}
	printf("\n4. The exit time for each of the line: \n\n");
	for(i=0;i<lines;i++)
    		{
    			printf("Line %d: ",i+1);
    			printf("%d",e2[i]);
    			printf("\n");
			}
    		printf("\n");
			printf("Press any key to Continue... ");
			getch();
			system("cls");  		
} 
void display1(int e1[],int e2[],int **w1,int ***w2)
{
	check1=0;
	process(e1,e2,w1,w2);
	check1=1;
    int n,i,m;
    printf("Enter the machine number for which the optimized path and time is to be displayed:\n");
    scanf("%d",&n);
    printf("Enter the line number of the machine:\n ");
    scanf("%d",&m);
    if((n<=0)||(n>machines)||(m<=0)||(m>lines))
    {
    	printf("Invalid Input!\n");
	}
	printf("The least time required to reach and operate in machine %d line %d is:",n,m);
    printf("%d\n",time[m-1][n-1]);
	int oppath1[n];
	oppath1[n-1]=m;
	int temp=oppath1[n-1]-1;
	for(i=n-2;i>=0;i--)
	{
		oppath1[i]=path[temp][i];
		temp=oppath1[i]-1;
	}
	for(i=0;i<n;i++)
	{
		printf("%d.) Machine %d of Line %d\n",i+1,i+1,oppath1[i]);
	}
	
		printf("\n");
		printf("Press any key to Continue... ");
		getch();
		system("cls"); 
}
void process(int e1[],int e2[],int **w1,int ***w2)
{
	int i,j,k,t1,minpath,tmin;
	char x;//helps clear screen
	//adding the entry time and the time taken at the first machine in each line
	for(i=0;i<lines;i++)
	{
		time[i][0]=e1[i]+w1[i][0];
	}
	//calc. the min time to reach the next machine with min time required 
	for(i=0;i<machines-1;i++)
	{
		for(j=0;j<lines;j++)
		{
			tmin=time[0][i]+w1[j][i+1]+w2[0][i][j];
			minpath=1;
			for(k=0;k<lines;k++)
			{
				
				if(tmin>time[k][i]+w1[j][i+1]+w2[k][i][j])
				/*
				time[k][i] is the time taken to process till the (k+1)th machine of the (i+1)th line
				w1[j][i+1] is the time taken to process the product in the (i+2)th machine of the (j+1)th line
				w2[k][i][j] is the time taken to send a product form the ith machine of (k+1)th line to the (i+1)th machine of (j+1)th line
				*/
				{
					tmin=time[k][i]+w1[j][i+1]+w2[k][i][j];
					minpath=k+1;
				}
			}
			time[j][i+1]=tmin;
			path[j][i]=minpath;
			
		}
	}
	
	//adding the exit time 
	for(i=0;i<lines;i++)
	{
		time[i][machines]=time[i][machines-1]+e2[i];
	}
	
	//finding the end machine line from which minimum time is obtained
	int min=time[0][machines];//minimum time to exit after passing through the last machine
	int bestendline=1;//will hold the line from which minimum time is obtained
	for(i=1;i<lines;i++)
	{
		if(min>time[i][machines])
		{
			min=time[i][machines];
			bestendline=i+1;
		}
	}
	if(check1!=0)
	{
	printf("The last time requirred for a product to be made is : %d\n\n",time[bestendline-1][machines]);
	check1=1;
    }
	
	//back tracking the path
	oppath[machines-1]=bestendline;
	int temp=oppath[machines-1]-1;
	for(i=machines-2;i>=0;i--)
	{
		oppath[i]=path[temp][i];
		temp=oppath[i]-1;
	}
	
	//printing the path 
	if(check1!=0)
	{
	for(i=0;i<machines;i++)
	{
		printf("%d.) Machine %d of Line %d\n",i+1,i+1,oppath[i]);
	}
	printf("\n\n");
	printf("Press any key to return to the HOME page... ");
	getch();
	scanf("%c",&x);
	system("cls");
	check1=1;}
}//end of the process function
int inputchoice(int count,int ch1)
{
	int ch;//choice that is returned
	char x;//helps clear screen 
	if(count<4)
	{
		printf("What do you want to input?? \n");
    	printf("1. The time taken to process the product in each machine \n");
    	printf("2. The entry time for each of the line \n");
    	printf("3. The exit time for each of the line \n");
    	printf("4. The time taken to travel from a machine in one level to the machines in the other level\n");
    	printf("5. To reset all the inputs\n");
    	printf("6. To start over\n\n");
		printf("Enter the choice: ");
    	scanf("%d",&ch);
    	printf("\n");
		return ch;
	}
	else
	{
		printf("You have entered the data successfully...");
		printf("\n\n");
		printf("Double ENTER to return to the HOME page... ");
		getch();
		scanf("%c",&x);
		system("cls");
		
		return 5;
	}
	
}//end of the inputchoice function

void input(int e1[],int e2[],int **w1,int ***w2)
{
	int flag=0,flag1=0,flag2=0,flag3=0;
	char x;
	int i,j,k;    
    //Inputting the values in the array
	int ch=0;//choice in the switch statement
	int count=0;//helps end the for loop when all the input is done 
	ch=inputchoice(count,ch);
while(count<4)
{	
    switch(ch)
    {
    	case 1:
    		if(flag==1)
    		{printf("You have already inputted this data!\n");}
    		else
    		{
    		flag=1;
    		count=count+1;
			printf("----------------------------------------------------------------------------------------------------------------\n\n");
    		for(i=0;i<lines;i++)
    		{
        		printf("Line %d\n",i+1);
        		for(j=0;j<machines;j++)
        		{
            		printf("    Machine %d: ",j+1);
            		scanf("%d",&w1[i][j]);
            		printf("\n");
        		}
    		}
    	}
    		printf("\n");
			printf("Press any key to Continue... ");
			getch();
			scanf("%c",&x);
			system("cls");
			ch=inputchoice(count,ch);
			break;
    		
    	case 2:
    		if(flag1==1)
    		{printf("You have already inputted this data!\n"); }
    		else
    		{
    		count=count+1;
    		flag1=1;
			printf("----------------------------------------------------------------------------------------------------------------\n\n");
    		for(i=0;i<lines;i++)
    		{
    			printf("Line %d: ",i+1);
    			scanf("%d",&e1[i]);
			}
		    }
			printf("\n");
			printf("Press any key to Continue... ");
			getch();
			scanf("%c",&x);
			system("cls");
			ch=inputchoice(count,ch);
			break;
		case 3:
			if(flag2==1)
    		{ 
    		printf("You have already inputted this data!\n");
			}
    		else
    		{
    		count=count+1;
    		flag2=1;
			printf("----------------------------------------------------------------------------------------------------------------\n\n");
    		for(i=0;i<lines;i++)
    		{
    			printf("Line %d: ",i+1);
    			scanf("%d",&e2[i]);
			} }
			
			printf("\n");
    	
			printf("Press any key to Continue... ");
			getch();
			scanf("%c",&x);
			system("cls");
			ch=inputchoice(count,ch);
			break;
			
		case 4:
			if(flag3==1)
    		{printf("You have already inputted this data!\n");}
    		else
    		{
    		count=count+1;
    		flag3=1;
			printf("----------------------------------------------------------------------------------------------------------------\n\n");
			for(i=0;i<lines;i++)
			{
				for(j=0;j<machines-1;j++)
				{
					printf("The time taken to travel from Machine %d of Line %d to: \n",j+1,i+1);
					for(k=0;k<lines;k++)
					{	printf("Machine %d of line %d: \n",j+2,k+1);
						scanf("%d",&w2[i][j][k]);
					}
				}
			}
		}
			printf("\n");
			printf("Press any key to Continue... ");
			getch();
			scanf("%c",&x);
			system("cls");
			ch=inputchoice(count,ch);
			break;
		case 5:
			flag=0;
			flag1=0;
			flag2=0;
			flag3=0;
			count=0;
			check=0;
			printf("\n");
			printf("The values have been reset!\n\n");
			printf("Press any key to Continue... ");
			getch();
			scanf("%c",&x);
			system("cls");
			ch=inputchoice(count,ch);
			break;
		case 6:
		system("cls");
		count=0;
		check=0;
		main();
		break;
		default:
			printf("Invalid input\n");
			printf("Press any key to Try again... ");
			getch();
			scanf("%c",&x);
			system("cls");
			ch=inputchoice(count,ch);
			break;
	
	}//end of switch
}//end of while
check=count;
}//end of input function

int main()
{
	int c=0;//for choice of switch
	printf("\t\tHere we go!!\n\n");
	char x;//helps clear screen
	printf("First enter the number of lines and machines in your factory...\n");
    printf("The number of lines: ");
    scanf("%d",&lines);
    printf("The number of machines in each line: ");
    scanf("%d",&machines);
    printf("\n\n");
	printf("Press any key to Continue... ");
	getch();
	scanf("%c",&x);
	system("cls");

	//Initialisation of arrays 
	
	int i,j,k;//for for loops
    int e1[lines];//entry time array
    int e2[lines];//exit time array
    
    int *w1[lines];//time required to process by each machine
    for (i=0; i<lines; i++)
    {
        w1[i] = (int *)malloc(machines * sizeof(int));
    }
    
    int **w2[lines];//time required to trasnfer the product to another machine
    for (i=0; i<lines; i++)
    {
        w2[i] = (int **)malloc((machines-1) * sizeof(int));
        for(j=0;j<machines-1;j++)
        {
            w2[i][j]=(int *)malloc(lines*sizeof(int));
        }
    }
	while(c!=5)
	{
		printf("\t\t\tHOME PAGE:\n\n");
		printf("Press 1 to Input the data\n");
		printf("Press 2 to Display the optimized path and time to the chosen machine \n");
		printf("Press 3 to Display the data inputted\n");
		printf("Press 4 to Process and Display the most optimised path\n");
		printf("Press 5 to END  the program\n\n");
		printf("Enter the choice: ");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
				system("cls");
				input(e1,e2,w1,w2);
				break;
			case 2:
				system("cls");
				if(check!=4)
				{printf("Insufficient Data!\n\n");
				printf("Press any key to Continue... ");
				getch();
				system("cls");
				}
				else
				{display1(e1,e2,w1,w2);}
				break;
			case 3:
				system("cls");
				if(check!=4)
				{printf("Insufficient Data!\n\n");
				printf("Press any key to Continue... ");
				getch();
				system("cls");
				}
			    else
				{display(e1,e2,w1,w2);}
				break;
			case 4:
				system("cls");
				if(check!=4)
				{printf("Insufficient Data!\n\n");
				printf("Press any key to Continue... ");
				getch();
				system("cls");
				}
				else
				{process(e1,e2,w1,w2);}
				break;
			case 5:
				system("cls");
				printf("\n\n\t\tBye Bye...\n\n");
				break;
			default:
				system("cls");
				printf("Invalid entry ....Please try again...\n");
				printf("Press any key to Continue... ");
				getch();
				system("cls");
				break;
		}
	}
}
