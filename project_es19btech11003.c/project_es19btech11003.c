    #include<stdio.h>//including standard libraries
    #include<stdlib.h>
    #include <time.h>

    #define MAX_VERTICES 100//defining max vertices as 100 for easy running of code
    #define MAX_EDGES 30

  struct queue//defining tree structure
  {
    int time;//to store no of days
    char event;//to store type of event
    int num;//to store node number
    struct queue *next;//to store next node address
  }*head=NULL;//assigning head to NULL

 struct Recovery//defining Recovery structure
 {
  int data;//to store serial number of a node
  struct Recovery *link;//to store next node address
 }*root=NULL;//assigning root to null

 typedef unsigned char vertex;

 void transmit(int a,int b)//function to add in priority queue
  {  
     int t=1;//defining variables
     struct queue *temp,*temp1;//defining queue nodes
        
     temp=(struct queue *)malloc(sizeof(struct queue));//alloting memory to temp

     while(rand()%2==1)//probability is 0.5
        {
          t++;//increment by 1
        }
     temp->time=t+b;//storing in temp node
     temp->event='T';
     temp->num=a;
    
    if(head==NULL || temp->time<head->time)//adding newnode in the priority queue
      {
        temp->next=head;
        head=temp;
      }
    else
      { 
        temp1=head;           
        while(temp1->next!=NULL && temp1->next->time<=temp->time)
          {  
            temp1=temp1->next;
          }
        temp->next=temp1->next;
        temp1->next=temp;            
      }
  }

void recovery(int a,int b)//function to add new node to priority queue 
{   
    int t=1;//defining variables
    struct queue *temp,*temp1;//defining nodes of queue structure
    temp=(struct queue *)malloc(sizeof(struct queue));//alloting memory to NULL
    
    while(rand()%10>2)
     {
       t++; 
     }
    temp->time=t+b;
    temp->event='R';
    temp->num=a;
    if(head==NULL || temp->time<head->time)//adding newnode in the priority queue
     {
       temp->next=head;
       head=temp;
     }
    else
     { 
       temp1=head;
       while(temp1->next!=NULL && temp1->next->time<=temp->time)
         {  
          temp1=temp1->next;
         }
       temp->next=temp1->next;
       temp1->next=temp;                    
     }
}

void RECOVERY(int a)//function to add recovered elements in a seperate linked list
{
  struct Recovery *newnode,*temp;//defining nodes of recovery structure
  newnode=(struct Recovery *)malloc(sizeof(struct Recovery));//allocating memory to newnode
  newnode->data=a;//storing serial number in data of newnode

  if(root==NULL)//adding newnode in recovery linked list
   {
    root=newnode;
    root->link=NULL;
   }
  else
   {
    temp=root;
    while(temp->link!=NULL)
     {
      temp=temp->link;
     }
    temp->link=newnode;
    newnode->link=NULL;
   }
}

int find(int a)//function to find whether given element is in recovery linked list or not
{
  struct Recovery *temp;//defining struct recovery nodes
  temp=root;//storing root in temp
  while(temp!=NULL && temp->data!=a)//condition to find whether given element is in recovery linked list or not
   {
    temp=temp->link;//shifting temp
   }
  if(temp==NULL)
   {
    return 1;//if not found return 1
   }
  else
   {
    return 0;//if found return 0
   }
}

int detect(int a)//function to find whether given serial number of node is present in priority queue or not
{
  struct queue *temp;//defining queue structure
  temp=head;//storing head in temp
  while(temp!=NULL && temp->num!=a)//condition to find whether given serial number of node is present in priority queue or not
   {
    temp=temp->next;//shifting temp
   }
  if(temp==NULL)
   {
    return 1;//if not found return 1
   }
  else
   {
    return 0;//if found return 0
   }
}

 int n;//defining global variable n

 int main()//execution of main function
  {
    int S=0;//defining variables and assigning their values to 0
    int R=0;
    int I=0;
    srand ( time(NULL) );
    int numberOfVertices = rand() % MAX_VERTICES;//finding numberOfVertices using random function

    srand ( time(NULL) );
    int maxNumberOfEdges = rand() % MAX_EDGES;//finding maxNubmerOfEdges using random function

    if( numberOfVertices == 0)
        numberOfVertices++;//increment by 1 if it is 0

    n=numberOfVertices;//storing in n
    int **A;//defining double pointer to store a large matrix
    int j;//defining variabes
    int u,v;
       A=(int **)malloc(n*sizeof(int*));//allocating space
        for(j=0;j<n;j++)
         {
           A[j]=(int*)malloc(n*sizeof(int));//allocating space for a 2-D matrix
         }

        for(u=0;u<n;u++)//making all elements of matrix 0
           for(v=0;v<n;v++)
             A[u][v]=0;

    vertex ***graph;

        if ((graph = (vertex ***) malloc(sizeof(vertex **) * numberOfVertices)) == NULL)//if equals to NULL
         {
            printf("Could not allocate memory for graph\n");
            exit(1);
         }

        int vertexCounter = 0;//defining variables and assigning their values to 0
        int edgeCounter = 0;

        for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++)
         {
            if ((graph[vertexCounter] = (vertex **) malloc(sizeof(vertex *) * maxNumberOfEdges)) == NULL)//if equals to NULL
             {
                printf("Could not allocate memory for edges\n");
                exit(1);
             }

            for (edgeCounter = 0; edgeCounter < maxNumberOfEdges; edgeCounter++)
             {
                if ((graph[vertexCounter][edgeCounter] = (vertex *) malloc(sizeof(vertex))) == NULL)//if equals to NULL
                 {
                    printf("Could not allocate memory for vertex\n");
                    exit(1);
                 }
             }
         }
        vertexCounter = 0;edgeCounter = 0;

        for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++)
         {
            for (edgeCounter=0; edgeCounter < maxNumberOfEdges; edgeCounter++)
             {
                if (rand()%2 == 1)//using random function to link elements
                 {  
                    int linkedVertex = rand() % numberOfVertices;
                    if(vertexCounter!=linkedVertex)
                     {
                        A[vertexCounter][linkedVertex]=1;//storing 1 in elemnts of 2-D matrix if those 2 numbers have links 
                        A[linkedVertex][vertexCounter]=1;//converting directed to undirected graph by storing 1 in transpose element also
                     }
                 }
                else
                 { 
                    graph[vertexCounter][edgeCounter] = NULL;
                 }
             }

         }
              
      char Arr[n];//defining a character array of size n
        for(v=0;v<n;v++)
          {
            Arr[v]='S';//initially assigning all elements of character array to 'S'
          }
        S=n-1;//storing n-1 value in S
        I=1;//storing 1 in I
        int i=0;//defining variables
        int x,y;

        for(u=0;u<300;u++)//running for loop for 300 days as asked in the question to print data for 300 days
         {  
          if(i==0)//initial case which runs only once in entire for loop to make 1st element as infected
           {           
             Arr[u]='I';//storing I in Arr[0]
             recovery(i,u);//calling recovery function to store infected node in priority queue
             for(v=0;v<n;v++)
              {
                if(A[i][v]==1)//finding links which are connected with 0
                 {
                   x=find(v);//to find whether given element is already in the recovery linked list or not 
                   y=detect(v);//to find whether given element is in priority queue or not
                   if(x*y==1)
                    transmit(v,u);//calling transmit function to add all linked elements to priority queue 
                 }
              }     
             i=1;//assigning 1 to i
            }
          else if(head!=NULL)//condition
            {
             while(head!=NULL && head->time==u)//if head->time is equal to u
                { 
                 if(head->event=='R')//if event is Recovery
                  {
                    R++;//increment by 1
                    I--;//decrement by 1
                    Arr[head->num]='R';//storing R in that particular element of that array
                    RECOVERY(head->num);//calling RECOVERY function to store head->num in recovery linked list
                    head=head->next;//shifting head
                  }
                 else if(head->event=='T')//if event is Transmission
                  {
                    S--;//decrement by 1  
                    I++;//increment by 1
                    Arr[head->num]='I';//storing I in that particular element of that array 
                    for(v=0;v<n;v++)//for loop to find connections with linked ones
                      {
                       if(A[head->num][v]==1)
                        {
                          x=find(v);//to find whether given element is already in the recovery linked list or not 
                          y=detect(v);//to find whether given element is in priority queue or not
                          if(x*y==1)
                           transmit(v,u);//adding newly connected elements to the priority queue 
                        }
                      }
                    recovery(head->num,u);//calling recovery function to store newnode in the priority queue
                    head=head->next;//shifting head
                  }
                }
            }

          printf("\nfor day-%d",u);//prompt to convey day number
          printf("\nSuspected:");//prompt
          for(v=0;v<n;v++)
           {
            if(Arr[v]=='S')//condition to print serial numbers of all array elements which store 'S'
             {
              printf("%d,",v);
             }
           }
          printf("\nInfected:");//prompt
          for(v=0;v<n;v++)
           {
            if(Arr[v]=='I')//condition to print serial numbers of all array elements which store 'I' 
             {
              printf("%d,",v);
             }
           }
          printf("\nRecovered:");//prompt
          for(v=0;v<n;v++)
           {
            if(Arr[v]=='R')//condition to print serial numbers of all array elements which store 'R' 
             {
              printf("%d,",v);
             }
           }
          printf("\nS=%d,I=%d,R=%d",S,I,R);//printing S,I &R numbers to know the count 
         
       }
  }
