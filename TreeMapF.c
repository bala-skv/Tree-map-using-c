#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define Space 20

struct tree
{
    int key;
    char value[100];
    int color;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
};

struct tree *root = NULL;
struct tree * nil;


struct tree* maxValueNode(struct tree*);
struct tree* minValueNode(struct tree*);
void inorder (struct tree*);
void Insert(int, char*);
void Delete (int);
void clear (struct tree*);
bool Empty ();
struct tree* begin ();
struct tree* end ();
void Emplace (int, char*);
struct tree* find (int);
struct tree* Insert_fixup (struct tree*);
struct tree* LeftRotate (struct tree*);
struct tree* RightRotate (struct tree*);
void Traversal1to1 (struct tree*, struct tree*);
void Transplant (struct tree*, struct tree*);
void Delete_fixup (struct tree*);
void Rand_Insertion ();
void draw (struct tree*, int);
void setHighLow (struct tree*, int, int);
void inorder_range (struct tree*, int, int);
void Update_string (int key);

int main ()
{
    nil=(struct tree*)malloc(sizeof(struct tree));
    nil->color=0;
	nil->right=NULL;
	nil->left=NULL;
	nil->parent=NULL;
    int choice;
    char input[100];
    while (choice != 11)
    {
        printf("\n=========MENU========\n");
        printf("==> 1. Insert\n");
        printf("==> 2. Erase\n");
        printf("==> 3. Traversal\n");
        printf("==> 4. Clear\n");
        printf("==> 5. Find\n");
        printf("==> 6. Empty check\n");
        printf("==> 7. Print tree\n");
        printf("==> 8. Random insert\n");
        printf("==> 9. Find keys in a particular range\n");
        printf("==> 10. Update string attached to a particular key\n");
        printf("==> 11. Exit\n");
        printf("=====================\n");
        printf("\nEnter your choice: ");
        scanf("%s",input);
        if (sscanf(input, "%d", &choice) != 1)
        {
            printf("Enter valid integer.\n");
        }
        else
        {
            switch (choice)
            {
                case 1 :
                {
                    int key;
                    char keyin[100];
                    printf("Enter the key:\n");
                    scanf("%s",keyin);
                    if (sscanf(keyin, "%d", &key) != 1)
                    {
                        printf("Enter a valid integer.\n");
                    }
                    else
                    {
                        char value[100];
                        printf("Enter the value:\n");
                        scanf(" %[^\n]s",value);
                        Emplace (key,value);
                    }

                    break;
                }

                case 2 :
                {
                    int key;
                    char keyin[100];
                    printf("Enter the key you want to delete:\n");
                    scanf(" %[^\n]s",keyin);
                    if (sscanf(keyin, "%d", &key) != 1)
                    {
                        printf("Enter a valid integer.\n");
                    }

                    else
                    {
                        if (find(key)!=nil){
                        Delete(key);
                        printf("Deleted node\n");
                        }
                        else{
                        printf("key does not exist\n");
                        }
                    }
                    break;
                }

                case 3 :
                {
                    inorder(root);
                    break;
                }

                case 4 :
                {
                    if (Empty())
                    {
                        printf("Tree is already empty.\n");
                    }
                    else
                        clear(root);
                    break;
                }

                case 5:
                {
                int key;
                char keyin[100];
                printf("Enter the key you want to find:\n");
                scanf(" %[^\n]s",keyin);
                if (sscanf(keyin, "%d", &key) != 1)
                {
                    printf("Enter a valid integer.\n");
                }
                else
                {
                    struct tree* found = find(key);
                    if(found!=nil && found!=NULL)
                        printf("Key found with value: %s\n",found->value);
                    else
                        printf("Key does not exist.\n");
                }
                break;
                }

                case 6:
                {
                if (Empty())
                    printf("Tree is empty.\n");
                else
                    printf("Tree is not empty.\n");
                break;
                }

                case 7:
                {
                    if (Empty()  || root == nil)
                    printf("Empty Tree.\n");
                    else
                    draw (root, 10);
                    break;
                }

                case 8:
                {
                    Rand_Insertion ();
                    break;
                }

                case 9:
                {
                    int key1, key2;
                    printf("Enter the key from which you want to traverse:\n");
                    scanf("%d",&key1);
                    printf("Enter the key to which you want to traverse:\n");
                    scanf("%d",&key2);
                    setHighLow(root,key1,key2);
                    break;
                }

                case 10:
                {
                    int key;
                    char keyin[100];
                    printf("Enter the key you want to update:\n");
                    scanf(" %[^\n]s",keyin);
                    if (sscanf(keyin, "%d", &key) != 1)
                    {
                        printf("Enter a valid integer.\n");
                    }
                    else
                        Update_string(key);
                    break;
                }

                case 11:
                {
                clear(root);
                break;
                }


                default :
                {
                    printf("Enter a valid choice.\n");
                }
            }
        }
    }
}

void Insert (int key, char* value)
{
    struct tree* x = (struct tree*)malloc(sizeof(struct tree));
    struct tree *temp1, *temp2;
    temp1 = root;
    x->key = key;
    strcpy(x->value,value);
    x->left =nil;
    x->right =nil;
    x->color = 1;

    if (root == NULL || root == nil)
    {
        root = x;
        x->parent =nil;
    }

    else
    {
        while (temp1 !=nil)
        {
            temp2 = temp1;
            if (x->key < temp1->key)
            {
                temp1 = temp1->left;
            }
            else
            {
                temp1 = temp1->right;
            }
        }
        x->parent = temp2;
        if (temp2->key > x->key)
            temp2->left = x;
        else
            temp2-> right = x;
    }

    Insert_fixup (x);
    root->color = 0;
}

struct tree* RightRotate (struct tree* x)
{
    struct tree* y = x->left;
    struct tree* t1 = y->right;

    x->left = t1;
    if (t1 !=nil)
        t1->parent = x;
    y->parent = x->parent;
    if (x->parent ==nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;

    return y;
}

struct tree* LeftRotate (struct tree* x)
{
    struct tree* y = x->right;
    struct tree* t1 = y->left;

    x->right = t1;
    if (t1 !=nil)
        t1->parent = x;
    y->parent = x->parent;
    if (x->parent ==nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;

    return y;
}

void inorder (struct tree* x)
{
    if (x!=nil && x!=NULL)
    {
        inorder(x->left);
        printf("%d-%s(%d) \t",x->key,x->value,x->color);
        inorder(x->right);
    }
}

struct tree* Insert_fixup (struct tree* x)
{
    while (x != root && x->parent->color == 1)
    {
        struct tree* y;
        if (x->parent == x->parent->parent->left)
        {
            y = x->parent->parent->right;
            if (y!=nil && y->color == 1)
            {
                x->parent->color = 0;
                y->color = 0;
                x->parent->parent->color = 1;
                x = x->parent->parent;
            }

            else
            {
                if (x == x->parent->right)
                {
                    x = x->parent;
                    LeftRotate (x);
                }
                x->parent->color = 0;
                x->parent->parent->color = 1;
                RightRotate (x->parent->parent);
            }
        }

        else
        {
            y = x->parent->parent->left;
            if (y!=nil && y->color == 1)
            {
                x->parent->color = 0;
                y->color = 0;
                x->parent->parent->color = 1;
                x = x->parent->parent;
            }

            else
            {
                if (x == x->parent->left)
                {
                    x = x->parent;
                    RightRotate (x);
                }
                x->parent->color = 0;
                x->parent->parent->color = 1;
                LeftRotate (x->parent->parent);
            }
        }

    }

    root->color = 0;
    return x;
}

struct tree* find (int key)
{
    if(Empty() || root == nil){
    return nil;
    }
    struct tree* x = root;
    while (x!=nil && x->key!=key)
    {
        if (x->key < key)
        {
            x = x->right;
        }
        else if (x->key > key)
        {
            x = x->left;
        }
    }

    return x;
}

struct tree* minValueNode(struct tree* x)
{
    struct tree* y = x;
    while (y->left!=nil)
    {
        y=y->left;
    }
    return y;
}

struct tree* maxValueNode(struct tree* x)
{
    struct tree* y = x;
    while (y->right!=nil)
    {
        y=y->right;
    }
    return y;
}

void Emplace (int key, char* value)
{
    struct tree* ptr = find (key);
    if (ptr==nil || ptr == NULL)
    {
        Insert (key, value);
    }

    else
    {
        printf("The key already exists. Try some other key value.");
    }
}

bool Empty()
{
    return (root == NULL);
}

struct tree* begin()
{
    return minValueNode(root);
}

struct tree* end()
{
    return maxValueNode(root);
}

void clear (struct tree* x)
{
    if (x != nil)
    {
        clear (x->left);
        clear (x->right);
        free (x);
    }

    root = NULL;
}


void Rand_Insertion(){
    int i;
    for(i=0; i<20; i++) {
        int key=rand()%100;
        char value[100];
        int value2=rand()%26;
        char s[4];
        s[0]= value2+65;
        value2=rand()%26;
        s[1]= value2+65;
        value2=rand()%26;
        s[2]= value2+65;
        s[3] = '\0';
        strcpy(value,s);
        if(Empty())
        {
        Insert(key,value);
        }
        else{
        struct tree* ptr=find(key);
        if(ptr==nil)
        Insert(key, value);
        }
    }
    printf("\nSuccessfully Added 20 Nodes\n\n");
}
void draw(struct tree* node,int s)
{
if (node == nil)
return;

s += Space;

draw(node->right, s);
int i;
for (i = Space; i < s; i++)
printf(" ");
if (node->color == 0)
{
if (node->left != nil || node->right != nil)
{
printf("%d %s (B)----------|\n", node->key,node->value);
}
else
printf("%d %s (B)\n", node->key,node->value);
}
else
{
if (node->left != nil && node->right != nil)
printf("%d %s (R)----------|\n", node->key,node->value);
else
printf("%d %s (R)\n", node->key,node->value);
}
draw(node->left, s);
}

void inorder_range(struct tree* root, int low, int high) {
    if(root==NULL) {
    return;
    }

    if(root->key>low) {
    inorder_range(root->left,low,high);
    }

    if(root->key>=low && root->key<=high) {
    printf("%d-%s\n",root->key,root->value);
    }

    if(root->key<high) {
    inorder_range(root->right,low,high);
    }
}

void setHighLow(struct tree* root,int key1,int key2) {
    if(root==NULL) {
    printf("Tree is empty.\n");
    return;
    }
    int low, high;

    if (key1 < key2)
    {
        low = key1;
        high = key2;
    }

    else
    {
        low = key2;
        high = key1;
    }

    printf("Keys between these numbers are as follows -\n");
    inorder_range(root, low, high);
}

void Transplant(struct tree * a,struct tree *b){
 if(a->parent==nil){
  root=b;
 }
 else if(a==a->parent->left){
  a->parent->left=b;
 }
 else{
  a->parent->right=b;
 }
 b->parent=a->parent;
}

void Delete(int key){
 struct tree * p;
 p=find(key);
 struct tree * q;
 struct tree * r;
 q=p;
 int Q_original_colour=q->color;
 if(p->left==nil){
  r=p->right;
  Transplant(p,p->right);
 }
 else if (p->right==nil){
  r=p->left;
  Transplant(p,p->left);
 }
 else{
  q=minValueNode(p->right);
  Q_original_colour=q->color;
  r=q->right;
  if(q!=p->right){
   Transplant(q,q->right);
   q->right=p->right;
   q->right->parent=q;
  }
  else{
   r->parent=q;
  }
  Transplant(p,q);
  q->left=p->left;
  q->left->parent=q;
  q->color=p->color;
 }
 if(Q_original_colour==0){
   Delete_fixup(r);
 }
 free(p);
}

void Delete_fixup(struct tree * x){
 struct tree * w;
 while(x!=root && x->color==0){
  if(x==x->parent->left){
   w=x->parent->right;
   if(w->color==1){
    w->color=0;
    x->parent->color=1;
    LeftRotate(x->parent);
    w=x->parent->right;
   }
   if(w->left->color==0 && w->right->color==0){
    w->color=1;
    x=x->parent;
   }
   else{
    if(w->right->color==0){
     w->left->color=0;
     w->color=1;
     RightRotate(w);
     w=x->parent->right;
    }
    w->color=x->parent->color;
    x->parent->color=0;
    w->right->color=0;
    LeftRotate(x->parent);
    x=root;
   }
  }
 else{
  w=x->parent->left;
  if(w->color==1){
    w->color=0;
    x->parent->color=1;
    RightRotate(x->parent);
    w=x->parent->left;
   }
   if(w->right->color==0 && w->left->color==0){
    w->color=1;
    x=x->parent;
   }
   else{
    if(w->left->color==0){
     w->right->color=0;
     w->color=1;
     LeftRotate(w);
     w=x->parent->left;
    }
    w->color=x->parent->color;
    x->parent->color=0;
    w->left->color=0;
    RightRotate(x->parent);
    x=root;
   }
  }
 }
 x->color=0;
}


void Update_string (int key)
{
struct tree *x = find(key);
if (x == nil)
{
printf("Node not found\n");
return;
}
else
{
char s[100];
printf("Current string is %s\nEnter the new string : ",x->value);
scanf(" %[^\n]s",s);
strcpy(x->value,s);
}
return ;
}
