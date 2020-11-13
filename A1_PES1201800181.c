#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	char* val;
	struct node* left;
	struct node* right;
};
typedef struct node node_t;

struct tree
{
	node_t *root;
};
typedef struct tree tree_t;

struct hist{
	int level;
	node_t* node;
};
typedef struct hist hist_t;

void init_tree(tree_t* ptr_t){
	ptr_t->root = NULL;
	//initialise the GPT
}

node_t* create_node(char* str){
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->val = strdup(str);
	node->left = node->right = NULL;
	return node;
}

void create_tree(tree_t* ptr_t){
	int num_lines = 100;
	char c;
	/*for(c = getc(stdin); c != EOF; c = getc(stdin)){
		if(c == '\n'){
			num_lines += 1;
		}
	}*/
    char str[1024];
    char data[1024];
    hist_t** hist = (hist_t**)malloc(sizeof(hist_t*) * num_lines);
    int hist_arr = 0;
    int num_tab;
    int str_l;
    node_t* parent = NULL;
    int f= 0;
	while(fgets(str, 1024, stdin) != NULL){
		num_tab = 0;
		str_l = 0;
		for(int i=0; i< strlen(str); i++){
			if(str[i] == '\t'){
				num_tab +=1;
			}
			else{
				data[str_l] = str[i];
				str_l += 1;
			}
		}	
		data[str_l - 1] = '\0';
		hist_t* new_h = (hist_t*)malloc(sizeof(hist));
		if (f==0){
			ptr_t->root = create_node(data);
			new_h->level = 0;
			new_h-> node = ptr_t->root;
			hist[0] = new_h;
			//printf("root\n");
		}
		else{
			new_h->level = num_tab;
			new_h->node = create_node(data);
		}
		if(hist_arr == num_lines){
			num_lines *= 2;
			hist = (hist_t**)realloc(hist, sizeof(hist_t*) * num_lines);
		}
		hist[hist_arr] = new_h;	
		for(int i = hist_arr-1; i>-1; i--){
			if(hist[i]->level == (new_h->level - 1)){
				parent = hist[i]->node;
				//printf("Parent: %s\n", parent->val);
				break;
			}
		}
		if(f != 0 && new_h->level == 0){
			parent = hist[0]->node;
			node_t* temp = parent;
			while(temp->right!= NULL){
				temp = temp->right;
			}
			temp->right = new_h->node;
		}
		else if(f!=0){
			if(parent->left == NULL){
				parent->left = new_h->node;
				//printf("%s left\n",new_h->node->val);
			}
			else{
				node_t* temp = parent->left;
				//printf("%s right\n",new_h->node->val);
				while(temp->right!= NULL){
					temp = temp->right;
				}
				temp->right = new_h->node;
			}
		}
		f=1; // To indicate the root
		hist_arr += 1;
	}	
	for(int i=0; i<hist_arr; i++){
		free(hist[i]);
	}
	free(hist);
}

void gen_header(){
	printf("#include<stdio.h>\n\n");
}

void prolog(){
	printf("int main()\n");
	printf("{\n");
}


void gen_while(){
	printf("\twhile (opt){\n");
}

void gen_switch(){
	printf("\tswitch(opt){\n");
}

void gen_scanf(){
	printf("\tscanf(\"%%d\",&opt);\n");
}
void end_while(){
	printf("\t}\n"); // close switch
	gen_scanf();
	printf("\t}\n"); // close while
}

void gen_break(){
	printf("\tbreak;\n");
}
void switch_case(char* s, int val){
	printf("\tcase %d:\n", val);
	printf("\tprintf(\"%s\\n\");\n",s);
}

void gen_default(){
	printf("\tdefault:\n");
	gen_break();
}

void preorder(node_t* n, int case_no){
	if(n==NULL){
		return;
	}
	//printf("\t%s\n", n->val);
	switch_case(n->val, case_no);
	if(n->left != NULL){
		gen_scanf();	
		gen_while();
		gen_switch();
	}
	else{
		gen_break();
	}
	//gen_break();
	//printf("%s %d\n",n->val,case_no);
	//printf("left %s %d\n", n->val, case_no);
	preorder(n->left,1);
	if(n->left != NULL){
		gen_default();
		end_while();
		gen_break();
	}
	//printf("right %s %d \n",n->val, case_no);
	preorder(n->right,case_no+1);
}

void right(node_t* n){
	if(n==NULL){
		return;
	}
	printf("%s\n", n->val);
	right(n->right);	
}
void parse(tree_t* t){
	preorder(t->root,1);
	//right(t->root);
}               

void epilog(){
	printf("\treturn 0;\n");
	printf("}\n");
}

void delete_tree(node_t* n){
	if(n==NULL){
		return;
	}
	delete_tree(n->left);
	delete_tree(n->right);
	free(n);
}
void free_tree(tree_t* t){
	if(t==NULL){
		return;
	}
	delete_tree(t->root);
	//free(t);
}
int main(int argc, char* argv[]){
	tree_t t	;
	init_tree(&t);
	create_tree(&t); // Creates tree
	gen_header(); 
	prolog();
	printf("\tint opt;\n");
	gen_scanf();	
	gen_while();
	gen_switch();
	parse(&t);	// parse tree in preorder
	end_while();
	epilog();
	free_tree(&t);
	return 0;
}
