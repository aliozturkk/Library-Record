/*
ALÝ ÖZTÜRK
150114061
HW3
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 typedef struct Library{
	int id;
	char name[50];
	char author[50];
	
	struct Library *nextPtr;
	
}library;

void read_file(library *r1); // for read file and write on node 
void write_file(library *w); // for write
void print_list(library *p1); //for print on screen
void update_book(library *update); //for updte book
void create_book(library *c);// 
void CompareLists();
int string_control(char ar[20]);
int int_control(char ar[20]);
int id_control(library *lib,int val);
library *delete_book(library *delete,int value);
library *sort_book_id( library *start );
library *sort_book_name( library *start );
library *sort_book_author( library *start );


int main(){
	
	library *root;
	
	root= (library *) malloc (sizeof(library));
    int add_type=0;
	
	read_file(root);
	
	
	
	
	while(1){
		

    
	printf("LIBRARY PROGRAM\n1 - List all books\n2 - Update a book\n3 - Create a new book\n4 - Delete a book\n5 - Sort all books according to id\n");
    printf("6 - Sort all books according to book name\n7 - Sort all books according to author name\n8 - Exit\nEnter your choice :\n");
	
	int choose;
	scanf("%d",&choose);
	
	
	if(choose==1){
		
	print_list(root);
	
	}else if(choose==2){
			
	 update_book(root);
		
	}else if(choose==3){
		
		
	if(add_type==0){ // normal add
		create_book(root);
	}else if(add_type==1){ // add for id
		create_book(root);
		root=sort_book_id(root);
	}else if(add_type==2){ // add for name
		create_book(root);
		root=sort_book_name(root);
	}else if(add_type==3){ // add for author
		create_book(root);
		root=sort_book_author(root);
	}	
		
	
	
	}else if(choose==4){
	int value;
	
	
	printf("Enter the record number to delete : ");
	scanf("%d",&value);
	
		
	root=delete_book(root,value);


	
	write_file(root);
		
	}else if(choose==5){
		
		root=sort_book_id(root);
		write_file(root);
		
		add_type=1;
		
	}else if(choose==6){
		root=sort_book_name(root);
		
		add_type=2;
	}else if(choose==7){
		
		root=sort_book_author(root);
		add_type=3;
	}else if(choose==8){
		root=sort_book_id(root);
		write_file(root);
			printf("Bye...\n");
		exit(1);
	}else{
		
		printf("Invaild input !\n");
	}
	
	}
	
	
	return 0;
}
/*read file*/
void read_file(library *r1){
	
	library *r=r1;
	library *r2;
	
	
	FILE *file;
	file=fopen("record.txt","r");/*open file for read*/
	
	if(file==NULL){ // if file do not exist there , create a file
		
		
		file=fopen("record.txt","a");
		fclose(file);
		r1->nextPtr=NULL;
		return 0;
		
	}
	
	
	while(fscanf(file,"%d %s %s",&r->id,r->name,r->author)!=EOF){/*write information on linked list from file */
	r2=r;
	r->nextPtr = (library *) malloc (sizeof(library)); /* open a location for new variable */
	r=r->nextPtr;/* pass to next struct*/
	
	}
	free(r2->nextPtr);
	r2->nextPtr=NULL;  /*last struct equal null for not exist segmantation fault error*/
     
	
		fclose(file);// close file
	
	
}

/*write file*/

void write_file(library *w){
	FILE *file;
	file = fopen("record2.txt","a");
	
			while(w!=NULL){/*write list until null variable*/
	
	fprintf(file,"%d  %s  %s\n",w->id ,w->name,w->author);
	w=w->nextPtr; /*pass to next struct */
	}
			 // close file
			fclose(file);
			
			// remove file 
			remove("record.txt");
    // rename file name
     rename("record2.txt","record.txt");
}

/*Print list */
void print_list(library *p1){
	
	library *p=p1;
	printf("Id       Book Name       Author Name\n");
	printf("==       ==========      ===========\n");
	while(p!=NULL){
		
	
		printf("%d       %s         %s\n",p->id ,p->name,p->author);
		p=p->nextPtr;
	}
}

/*Update Book*/
void update_book(library *update){
	
	FILE *file2;
	library *u;
		u=update;
		int input;
		char a1[10];
		int b;
		int check=0;
		
			printf("Please enter the record number of the book you want to update :");
		scanf("%s",a1);
		b=int_control(a1); 
	
		if(b==1){
			printf("Invalid input !\n");
			return 0;
		}    
       input=atoi(a1);
		while(u!=NULL){/*print list until null variable*/
	
	if(u->id==input){
     check=1;   	
	break;
	}
	u=u->nextPtr; /*pass to next struct */
		
		}
		
		if(check==0){
			printf("Not fount !\n");
         return 0;			
		}
		
		printf("%d %s %s\n",u->id ,u->name,u->author);
		printf("1 - Update book name\n2 - Update author name");
		scanf("%d",&input);
		if(input==1){
			printf("Enter the new book name :");
			scanf("%s",u->name);
			
			printf("%d %s %s\n",u->id ,u->name,u->author);
		}else if(input==2){
			printf("Enter the new author name :");
			
			
		scanf("%s",a1);	
		b=string_control(a1);           /*is it string or not*/ 
		if(b==1){
			printf("Invalid input !\n");  
			return 0;
		}
         strcpy(u->author,a1);
			
			
			
			printf("%d %s %s\n",u->id ,u->name,u->author);
		}else{
			printf("Invaild input!\n");
		}
		u=update;
		write_file(u);// write file 
}

/*Create node*/
void create_book(library *c){
library *c1=c;


    int a;
	char d[20];
  while(c->nextPtr!=NULL){
	  c=c->nextPtr;
	   }
	
	
printf("Enter the record number to create a new record :");
	int input;
	char a1[20];
	int b;
	scanf("%s",a1);
			input=atoi(a1);
			b=int_control(a1); 
		if(b==1){
			printf("Invalid input !\n");
			return 0;
		}    
       
	   b=id_control(c1,input);
	   if(b==1){
			printf("This record have been use.! \n");
			return 0;
		}  
	  
	
	
	char a2[20];
	
	printf("Enter the book name :");
	scanf("%s",a2);
	printf("Enter the author name :");
	scanf("%s",a1);
	b=string_control(a1);
	if(b==1){
			printf("Invalid input !\n");
			return 0;
		} 
	
    
	
	 c->nextPtr = (library *) malloc (sizeof(library));
    c =c->nextPtr;
	c->id=input;
	strcpy(c->author,a1);
	strcpy(c->name,a2);
	c->nextPtr=NULL;
	
	
	
	
	

}
/*delete book*/
library *delete_book(library *delete, int value)
{
		
  if (delete == NULL){ // check delete id , there is or not 
	  CompareLists();
	  return NULL;
  }
    
  if (delete->id == value) {
  
    library *temp;
printf("%d %s %s \nDeleted.\n",delete->id,delete->name,delete->author);    
temp = delete->nextPtr;
    free(delete); 
    return temp;
  }
delete->nextPtr = delete_book(delete->nextPtr, value);
  return delete;
} 



void CompareLists()// for delete function 
{
  printf("Not fount !\n");
}



/* sort for id */ 

library *sort_book_id( library *start )
{
   library *p, *q, *top;
    int changed = 1;
library *l1;
library *l2;
   top = (library *)malloc(sizeof(library));

    top->nextPtr = start;
    if( start != NULL && start->nextPtr != NULL ) {

        while( changed ) {
            changed = 0;
            q = top;
            p = top->nextPtr;
            while( p->nextPtr != NULL ) {
               
                if( p->id > p->nextPtr->id ) {
					l1=p;
					l2=p->nextPtr;
					l1->nextPtr = l2->nextPtr;
                    l2->nextPtr = l1;
                    q->nextPtr = l2;
					 
                    changed = 1;
                }
                q = p;
                if( p->nextPtr != NULL )
                    p = p->nextPtr;
            }
        }
    }
    p = top->nextPtr;
    free( top );
    return p;
}
/* sort for name */ 

library *sort_book_name( library *start )
{
   library *p, *q, *top;
   library *l1;
   library *l2;
    int changed = 1;

   top = (library *)malloc(sizeof(library));

    top->nextPtr = start;
    if( start != NULL && start->nextPtr != NULL ) {

        while( changed ) {
            changed = 0;
            q = top;
            p = top->nextPtr;
            while( p->nextPtr != NULL ) {
               
                if( strcmp(p->name , p->nextPtr->name)>0 ) {
                    l1=p;
					l2=p->nextPtr;
					l1->nextPtr = l2->nextPtr;
                    l2->nextPtr = l1;
                    q->nextPtr = l2;
                    changed = 1;
                }
                q = p;
                if( p->nextPtr != NULL )
                    p = p->nextPtr;
            }
        }
    }
    p = top->nextPtr;
    free( top );
    return p;
}

/* sort for name */ 

library *sort_book_author( library *start )
{
   library *p, *q, *top;
   library *l1;
   library *l2;
    int changed = 1;

   top = (library *)malloc(sizeof(library));

    top->nextPtr = start;
    if( start != NULL && start->nextPtr != NULL ) {

        while( changed ) {
            changed = 0;
            q = top;
            p = top->nextPtr;
            while( p->nextPtr != NULL ) {
               
                if( strcmp(p->author , p->nextPtr->author)>0 ) {
                  l1=p;
					l2=p->nextPtr;
					l1->nextPtr = l2->nextPtr;
                    l2->nextPtr = l1;
                    q->nextPtr = l2;
                    changed = 1;
                }
                q = p;
                if( p->nextPtr != NULL )
                    p = p->nextPtr;
            }
        }
    }
    p = top->nextPtr;
    free( top );
    return p;
}

int string_control(char ar[20]){
		  int i=0;
			while(1){
				if(ar[i]==NULL){
					break;
				}
				if((int)ar[i]>=48&&(int)ar[i]<=57){	
					return 1;
                 }
				i++;
				 }	
	return 0;
}

int int_control(char ar[20]){
		  int i=0;
			while(1){
				if(ar[i]==NULL){
					break;
				}
				if((int)ar[i]<=47||(int)ar[i]>=58){	
					return 1;
                 }
				i++;
				 }	
	return 0;
}

int id_control(library *lib,int val){
	
	library *lib2=lib;
	
	
	while(lib2->nextPtr!=NULL){
		
		if(lib2->id==val){
			
			return 1;
		}
		lib2=lib2->nextPtr;
	}
	
	
	
	
	return 0;
}








