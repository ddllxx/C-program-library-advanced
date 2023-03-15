
#include "book_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Book *head1 = NULL;
user *head2 = NULL;
FILE *fp1 = NULL;
FILE *fp2 = NULL;

//display the menu
void main_menu()
{
    int flag = 1;
    while(flag)
    {
    	int option;
    	printf("\nPlease choose an option :\n"
	    "1) Register an account\n"
	    "2) Login\n"
	    "3) Search for books\n"
	    "4) Display all books\n"
	    "5) Quit\n");
    	printf("\nOption: ");
    	scanf("%d", &option);
    	
        switch (option)
        {
            case 1:
                Register();
                break;

            case 2:
                Login();
                break;

            case 3:
                SearchBooks();
                break;

            case 4:
                Display(head1);
                break;

            case 5:
                flag = 0;
                printf("\nLogging out...");
                break;
            
            default:
                printf("\nWRONG OPTION!!!\n");
                break;
        }
    } 
}

//menu for librarian
void menu_librarian()
{
    Book *book;
    book = (Book*) malloc (sizeof (Book));
    
    int flag = 1;
    while (flag)
    {
        printf("\n( logged in as : librarian)\n");
        printf("Please choose an option:\n"
        "1) Add a book\n"
        "2) Remove a book\n"
        "3) Search for books\n"
        "4) Display all books\n"
        "5) Log out\n");

        int option;
        printf("\nOption:");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            add_book(*book);
            break;
        
        case 2:
            Display(head1);
            printf("\nWhich book do you want to remove?\n");
            
            unsigned int id;
            scanf("%u", &id);
            book = find_book_by_id( id );
            
            if(book == NULL)
            {
            	printf("\nFail to find this book.\n");
			}
			else{
            	remove_book(*book);
        	}
            break;

        case 3:
            SearchBooks();
            break;

        case 4:
            Display(head1);
            break;

        case 5:
            flag = 0;
            printf("\nLogging out...\n");
            break;

        default:
            printf("\nWRONG OPTION!!!\n");
            break;
        }
    }
}

//menu for reader
void menu_reader(user *u)
{
    int flag = 1;
    while (flag)
    {
        printf("\n( Logged in as : %s )\n", u->name);
        printf("Please choose an option \n"
        "1) Borrow a book\n"
        "2) Return a book\n"
        "3) Search for books\n"
        "4) Display all books\n"
        "5) Log out\n");

        int option;
        printf("\nOption: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            BorrowBook(u);
            break;
        
        case 2:
            ReturnBook(u);
            break;

        case 3:
            SearchBooks();
            break;

        case 4:
            Display(head1);
            break;

        case 5:
            flag = 0;
            printf("\nLogging out...\n");
            break;

        default:
            printf("WRONG OPTION!!!\n");
            break;
        }
    }
}

//Register an account
void Register()
{
    user *n, *p = NULL;
    n = (user*) malloc (sizeof (user));
    n->name = (char*) malloc (sizeof (char) * 50);
    n->password = (char*) malloc (sizeof (char) * 50);
    
	if(n == NULL)
	{
		printf("Memory allocation error!\n");
		exit(1); 
	}
	
    printf("\nname: ");
    scanf("%s", n->name);
    
    if(compare(head2, n->name, 1) != 0)
    {
        printf("password: ");
        scanf("%s", n->password);
        printf("Success!\n\n");
        
     	//store the new user's information to the user list
	    if ( head2 == NULL)
	    {
	        head2 = n;
	        n->next = NULL;
	    }
	    else{
	    	p = head2;
	    	
	        while (p->next != NULL)
	        {
	            p = p->next;
	        }
	        
	        p->next = n;
	        n->next = NULL;
	    }   
    }
	else{
        printf("This account has already existed.\n\n");
    }
}

//Login
void Login()
{
    char *n, *p;
    n = (char*) malloc (sizeof (char) * 50);
    p = (char*) malloc (sizeof (char) * 50);
    
    printf("\nusername: ");
    scanf("%s",n);
 
	if(strcmp(n, "librarian") == 0)
    {
        menu_librarian();
    }
    else if (head2 == NULL || compare(head2, n, 1) != 0)
    {
    	printf("\nThis User does not exist.\n");
        printf("Please register first.\n");
        Register();
    }
    else{
        printf("password: ");
        scanf("%s", p);

        if(compare(head2, p, 2) != 0)
		{
            printf("Security password error!\n"
			"Please try again.\n"
			"password: ");
			scanf("%s", p);

			if(compare(head2, p, 2) != 0)
			{
				printf("\nSecurity password error!\n");
				return;
			}
        }
        else{
            printf("\nLogin successful!\n");
            
            user *u;
            u = (user*) malloc (sizeof (user));
			u->name = (char*) malloc (sizeof (char) * 50);
			u->password = (char*) malloc (sizeof (char) * 50);
            u->name = n;
            u->password = p;
            menu_reader(u);
        }
    }
}

//Search books
void SearchBooks()
{
    int option;

    printf("\nSearch by:\n1)title\n2)author\n3)year\n"
    "Option: ");
    scanf("%d", &option);

		switch (option)
		    {
		    case 1:
		    {
		        char title[100];
		        getchar();
		        printf("\nPlease input the title:");
		        scanf("%[^\n]", title);
		        find_book_by_title(title);
		        break;
		    }
		
		    case 2:
		    {
		        char author[50];
		        getchar();
		        printf("\nPlease input the author:");
		        scanf("%[^\n]", author);
		        find_book_by_author(author);
		        break;
		    }
		
		    case 3:
		    {
		        unsigned int year;
		        getchar();
		        printf("\nPlease input the year:");
		        scanf("%u", &year);
		        find_book_by_year(year);
		        break;
		    }
		
		    default:
		        printf("\nWRONG OPTION!!!\n");
		        break;
		}
}

//Display all books
void Display(Book *head)
{
    Book *p;
    p = head;

    if( !p )
    {
        printf("\nThe booklist is empty!\n");
        return;
    }
    else{
        printf("\nID\ttitle\t\t\t\t\t\tauthors\t\t\t\t\tyear\t\tcopies\n");
        while ( p )
        {
            printf("%u\t%-44s%-44s%4u\t\t%u\n",
            p->id, p->title, p->authors, p->year, p->copies);
            p = p->next;
        }
    }
}


//---------------------------------------------------------------------------

//saves the database of readers in the specified file
void store_readers(FILE *file)
{
    file = fopen("user.txt", "w");

    if( !head2 )
    {
        printf("This list is empty!\n");
        return;
    }

    user *p = (user*) malloc (sizeof(user));
    p = head2->next;

    if(file == NULL)
    {
        printf("Can't open the file!\n");
        exit(1);
    }

    fputs("Reader\tpassword\n", file);
    while (p)
    {
        fprintf(file, "%s\t%s", p->name, p->password);
        fprintf(file, "\n");
        p = p->next;
    }

    printf("\n");
    fclose(file);
}

//open the file and read the information
void load_users(FILE *file)
{
	file = fopen("user.txt", "r");
	
    char *n, *password;//the pointers of name and password
	n = (char*) malloc (sizeof (char)*50);
    password = (char*) malloc (sizeof (char)*50);
    
    user *p = NULL, *q = NULL;
    
    if(file == NULL)
    {
        printf("Fail to open the file!\n");
        return;
    }
	else{
		//get the first line of the file
		char *b = (char*) malloc (sizeof (char)*100);
		fgets(b, 100, file);
		
	    while (fscanf(file, "%s\t%s\n", n, password) != EOF)
	    {
	    	p = (user*) malloc (sizeof (user));
	    	p->name = (char*) malloc (sizeof (char)*50);
	    	p->password = (char*) malloc (sizeof (char)*50);
	    	
	    	if( p == NULL)
	    	{
	    		printf("\nMemory allocation error!\n");
	    		exit(1);
			}
	    	
	    	if(head2 == NULL)
	    	{
	    		head2 = p;
	    		p->next = NULL;
			}
			else
			{
				q = head2;
				
				while( q->next != NULL )
				{
					q = q->next;
				}
				
				q->next = p;
				p->next = NULL;
			}
	    	
	        strcpy(p->name, n);
	        strcpy(p->password, password);
	
	    }
	}
	
    fclose(file);
    printf("\nLoad successfully!\n\n");
}

//traverse list to find whether the new reader exists
int compare(struct user *head, char *target, int order)
{
    struct user *temp;//temp is the intermediate variable of the list
	int i;//the returned value of function strcmp

	temp = head;
	if(head == NULL)
	{
		return 2;
	}

    if( order == 1 )
    {
        while ( temp && (i = strcmp(temp->name, target)))
	    {
			temp = temp->next;
	    }
    }
	if( order == 2 )
    {
        while ( temp && (i = strcmp(temp->password, target)))
	    {
			temp = temp->next;
	    }
    }

	return i;
	//When temp->name/password and target are the same, 
	//i=0 which means that this account exists.
}

//Borrow a book
void BorrowBook()
{
    int id;
    Display(head1);
    SearchBooks();
    
    printf("\nPlease input the id of book: ");
    scanf("%d", &id);
    
    Book *p;
    p = (Book*) malloc (sizeof (Book));
    
    if( p == NULL)
	{
		printf("\nMemory allocation error!\n");
		exit(1);
	}
    
    p = find_book_by_id(id);

    if( p == NULL )
    {
        printf("\nThe book was not found!\n");
        return;
    }
    else if (p->copies < 1)
    {
        printf("\nSorry, there is no this book.\n");
        return;
    }
    else
    {
        p->copies--;
        printf("\nBorrow successfully!\n");
    }
}

//Return a book
void ReturnBook()
{
    int id;
    printf("\nPlease input the id of the book you want to return: ");
    scanf("%d", &id);

    Book *p;
    p = (Book*) malloc (sizeof (Book));
    
    if( p == NULL)
	{
		printf("\nMemory allocation error!\n");
		exit(1);
	}
    
    p = find_book_by_id(id);
    
    if (p == NULL) 
    {
    	printf("\nFail to return the book!\n");
        return;
    }
    else{
        p->copies++;
        printf("\nReturn successfully!\n");
    }
}


//-------------------------------------------------------------------------------------------

//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file)
{
    file = fopen("book.txt", "w");

    if ( !head1 )
    {
        printf("This list is empty!\n");
        return 1;
    }
    
    Book *p;
    p = (Book*) malloc (sizeof (Book));
    p = head1->next;

    if(file == NULL)
    {
        printf("Fail to open the file!\n");
        exit(1);
    }

    while (p)
    {
        fprintf(file, "%u\t%s\t%s\t%u\t%u\n", p->id, p->title, p->authors, p->year, p->copies);
        p = p->next;
    }

    printf("\n");
    fprintf(file, "\n");
    fclose(file);
    
    return 0;
}

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file)
{
    file = fopen("book.txt", "r");

    char *n, *a;//the pointers of name and author
    n = (char*) malloc (sizeof (char)*100);
    a = (char*) malloc (sizeof (char)*100);
    
    unsigned int i, y, c;//id,year,copies

    Book *p = NULL, *q = NULL;

    if(file == NULL)
    {
        perror("Fail to open the file!\n");
        return 1;
    }
    
    char *b = (char*) malloc (sizeof (char)*100);
	fgets(b, 100, file);//get the first line of the file
	
    while (fscanf(file, "%u\t%[^\t]\t%[^\t]\t%u\t%u\r", &i, n, a, &y, &c) != EOF)
    {	
     	p = (Book*) malloc (sizeof(Book));
     	p->title = (char*) malloc (sizeof (char)*100);
     	p->authors = (char*) malloc (sizeof (char)*100);
		   
        if(head1 == NULL)
        {
            head1 = p;
            p ->next = NULL;
        }
        else{
            q = head1;
            
            while ( q ->next )
            {
                q = q->next;
            }
            
            q->next = p;
        	p->next = NULL;
        }
        
        p->id = i;
        strcpy(p->title, n);
        strcpy(p->authors, a);
        p->year = y;
        p->copies = c;
		
    }

    fclose(file);
    printf("\nLoad successfully!\n");

    return 0;
}

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book)
{
    Book *p, *q = NULL;
    p = (Book*) malloc (sizeof(Book));
    p->title = (char*) malloc (sizeof (char)*100);
    p->authors = (char*) malloc (sizeof (char)*100);

    if( p == NULL)
    {
        printf("Memory allocation error!\n");
        exit(1);
    }
        
    getchar();
    printf("\nid: ");
	scanf("%u",&p->id);
    printf("\n");
        
    printf("title: ");
    getchar();
    gets(p->title);
    printf("\n");
        
    printf("author: ");
    gets(p->authors);
    printf("\n");
        
    printf("year: ");
    scanf("%u",&p->year);
    printf("\n");
        
    printf("copies: ");
    getchar();
    scanf("%u",&p->copies);
    printf("\n");
        
    if( head1 == NULL)
    {
        head1 = p;
        p->next = NULL;
    }
    else{
        q = head1;

        while (q->next != NULL)
        {
            q = q->next;
        }

        q->next = p;
        p->next = NULL;
    }
        
    printf("\nID\ttitle\t\t\t\t\t\tauthors\t\t\t\t\tyear\t\tcopies\n");
	printf("%u\t%-44s%-44s%4u\t\t%u\n",
	p->id, p->title, p->authors, p->year, p->copies);
        
    printf("\nAdd successfully!\n");
    
    return 0;
}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book)
{
    Book *p = head1;
    Book *q;

    if ( head1 == NULL)
    {
        printf("The list is empty.\n");
        exit(1);
    }

    for ( ; p->id != book.id; p = p->next)
    {
        q = p;
    }

    if(q == NULL)
    {
        head1 = p->next;
    }
    else
    {
        q->next = p->next;
    }

    free(p);
    q =NULL;

    printf("\nRemove successfully!\n");
    return 0;
}

//finds books with a given id
Book* find_book_by_id(unsigned int id)
{
    Book *p;
    int flag = 0;
    p = head1;
    
    if( !head1 )
    {
    	printf("\nThis list is empty!\n");
	}
	else
    {
		while( p != NULL)
	    {
	        if( id == p->id )
	        {
	        	flag = 1;
	        	printf("\nFind it!\n");
	            return p;
	        }
	        p = p->next;
	    }
	    if( flag == 0 )
	    {
	    	printf("Fail to find this book!\n");
	    	return NULL;
		}
	}
}

//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title (const char *title)
{
    Book *p = head1, *q, *temp = NULL;

    BookList i;
    i.list = NULL;
    i.length = 0;

    if( !head1 )
    {
        printf("This list is empty!\n\n");
    }
	else{
		while( p != NULL)
		{
		    if( !strcmp( title, p->title) )
		    {
	            q = (Book*) malloc (sizeof (Book));
	            q->title = (char*) malloc (sizeof (char)*100);
	            q->authors = (char*) malloc (sizeof (char)*100);

                q->id = p->id;
                q->year = p->year;
                q->copies = p->copies;
                strcpy( q->title, p->title);
                strcpy( q->authors, p->authors);
                
                if ( !i.list )
                {
                    i.list = q;
                    q->next = NULL;
                }
                else{
                    temp = i.list;

                    while ( temp->next )
                    {
                        temp = temp->next;
                    }
                    
                    temp->next = q;
                    q->next = NULL;
                }

		    	i.length++;
		    }

		    p = p->next;
		}
	}
	
    Display(i.list);
    return i;
}

//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author (const char *author)
{
    Book *p, *q, *temp = NULL;

    BookList i;
    i.list = NULL;
    i.length = 0;
    p = head1;
   
    if( !p )
    {
        printf("This list is empty!\n");
    }
	else{
		while( p != NULL)
		{
		    if( !strcmp( author, p->authors) )
		    {
	            q = (Book*) malloc (sizeof (Book));
	            q->title = (char*) malloc (sizeof (char)*100);
	            q->authors = (char*) malloc (sizeof (char)*100);
            
			    q->id = p->id;
                q->year = p->year;
                q->copies = p->copies;
                strcpy( q->title, p->title );
                strcpy( q->authors, p->authors );
                
                if ( !i.list )
                {
                    i.list = q;
                    q->next = NULL;
                }
                else{
                    temp = i.list;

                    while ( temp->next )
                    {
                        temp = temp->next;
                    }
                    
                    temp->next = q;
                    q->next = NULL;
                }

		    	i.length++;
		    }
		    
		    p = p->next;
		}
	}
    
    Display(i.list);
    return i;
}

//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year (unsigned int year)
{
    Book *p, *q, *temp = NULL;

    BookList i;
    i.list = NULL;
    i.length = 0;
    p = head1;

    if( !p )
    {
        printf("This list is empty!\n");
    }
	else{
		while( p != NULL)
		{
		    if( year == p->year )
		    {
            	q = (Book*) malloc (sizeof (Book));
	            q->title = (char*) malloc (sizeof (char)*100);
	            q->authors = (char*) malloc (sizeof (char)*100);
	            
		    	q->id = p->id;
                q->year = p->year;
                q->copies = p->copies;
                strcpy( q->title, p->title);
                strcpy( q->authors, p->authors);
                
                if ( !i.list )
                {
                    i.list = q;
                    q->next = NULL;
                }
                else{
                    temp = i.list;

                    while ( temp->next )
                    {
                        temp = temp->next;
                    }
                    
                    temp->next = q;
                    q->next = NULL;
                }
		    	i.length++;
			}
            p = p->next;
		}

	}
	
	Display(i.list);
    return i;
}



//------------------------------------------------------------------------------------------------------------

void run()
{
    load_books(fp1);
    load_users(fp2);

    main_menu();

    store_books(fp1);
    store_readers(fp2);
}
