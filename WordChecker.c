#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define RED 1
#define BLACK 0

int stampa=0;
//Struttura albero_RB

//nodo albero
struct node{
	char * parola; //parola
    int filter; // 0 o 1
	int c; // 1-red, 0-black
	struct node* p; // parent
	struct node* r; // right-child
	struct node* l; // left child
};



void inorder_graph_dot_string(struct node* T){
	if (T == NULL) return;
    //left
	if (T->l != NULL){
		printf(" %s ", T->parola);
		printf("->");
		printf(" %s [label=\"L\"]\n", T->l->parola);
		char* tester=T->l->parola;
	}
	
	inorder_graph_dot_string(T->l);
	//if (T->c==1) printf("%s [color=RED]\n", T->parola);
	
    //right
	if (T->r != NULL){
		printf(" %s ", T->parola);
		printf("->");
		printf(" %s \n", T->r->parola);
	}
	inorder_graph_dot_string(T->r);
}


// rightrotate del nodo passato all interno della funzione
void rightrotate(struct node* radice, struct node* x){
	struct node* y = x->l;
	x->l = y->r;	//il sottoalbero destro di y diventa quello sinistro di x
	if (x->l)
		x->l->p = x;
	y->p = x->p;  //attacca il padre di x a y
	if (!x->p)
		radice = y;
	else if (x == x->p->l)
		x->p->l = y;
	else
		x->p->r = y;
	y->r = x; //mette x a destra di y
	x->p = y;
}

// leftrotate del nodo passato all interno della funzione
void leftrotate(struct node* radice, struct node* x){
	struct node* y = x->r;
	x->r = y->l; //il sottoalbero sinistro di y diventa quello destro di x
	if (x->r)
		x->r->p = x;
	y->p = x->p; //attacca il padre di x a y
	if (!x->p)
		radice = y;
	else if (x == x->p->l)
		x->p->l = y;
	else x->p->r = y;
	y->l = x; //mette x a sinistra di y
	x->p = y;
}

void fixup(struct node* T, struct node* z)
{
	struct node* y=NULL;
	
	while (z->p != NULL && z->p->p->r != NULL && z->p->c==RED){
		if (z->p->p != NULL && z->p==z->p->p->l )
		{
			y= z->p->p->r;
			if (y->c==RED){
				z->p->c=BLACK;
				y->c=BLACK;
				z->p->p->c=RED;
				z=z->p->p;
			}else if (z==z->p->r){
				z=z->p;
				leftrotate(T,z);
			}
			z->p->c=BLACK;
			z->p->p->c=RED;
			rightrotate(T,z->p->p);

		}
		else{
			y= z->p->p->r;
			if (y->c==RED)
			{
				z->p->c=BLACK;
				y->c=BLACK;
				z->p->p->c=RED;
				z=z->p->p;
			}else if (z==z->p->r){
				z=z->p;
				rightrotate(T,z);
			}
			z->p->c=BLACK;
			z->p->p->c=RED;
			leftrotate(T,z->p->p);
		}
	}
	return;
}
//Funzione inserisci nodo
	struct node* RB_BST_INSERT(struct node* T,struct node* z ){
    struct node* y=NULL;
    struct node* x=T;
	struct node* tester=T; //ELIM

    while (x!=NULL)
    {
        y=x;
        if (strcmp(z->parola,x->parola)<0 ){
            x=x->l;
        }
        else x=x->r;
    }
    z->p=y;
    if (y==NULL)
    {
    	T=z;
    }else if (strcmp(z->parola,y->parola)<0)
    {
        y->l=z;
    }else y->r=z;
	tester=T; //ELIM


    fixup(T,z);

	// Return the (unchanged) node pointer
	
	return T;
}


struct node* crea_nodo(char* stringa){
	struct node* z=(struct node*)malloc(sizeof(struct node));
	z->filter=0;
	z->c=RED;
	z->l=NULL;
	z->p=NULL;
	z->r=NULL;
	z->parola=stringa;
	return z;
}

/*void lettura_parole(){
	//char* parola = calloc(k+1,sizeof(char));
	char end[]= "end";
	char dizion[5][4]={{"abc"},{"bua"},{"cao"},{"dai"},{"fio"}};

	while(strcmp(parola,end)!=0){
		scanf("%s",parola);
		struct node* z=crea_nodo(parola);
		RB_INSERT(root,z);
	}
	for(int i=0; i<5;i++){
		struct node* z= crea_nodo(dizion[i]);
		RB_BST_INSERT()
		struct node* radice = root;
	}

	return;
}*/



// driver code

int main()
{
    int k;
    //printf("inzia:");
    //scanf("%d",&k);
//Inizializzo radice:
	struct node* radice =(struct node*)malloc(sizeof(struct node));
	radice=NULL;

    char dizion[5][4]={{"abc"},{"bua"},{"cao"},{"dai"},{"fio"}};

	for(int i=0; i<5;i++){
		radice = RB_BST_INSERT(radice,crea_nodo(dizion[i]));
	}

	printf("Albero:\n");
	inorder_graph_dot_string(radice);


	return 0;
}