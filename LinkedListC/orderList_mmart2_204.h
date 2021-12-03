#include <ctype.h>
#include <stdlib.h>

typedef struct _foodNode
{
char *data; /* Food Item Name */
struct _foodNode *next;
} foodNode; 

typedef struct _orderList
{
foodNode *head; /* Pointer to first food item for the order (alphabetical)*/
int count; /* Number of food items in the order */
} orderList;

typedef struct _robotOrder
{
unsigned int robotNum;
orderList *data;
char *deliverTo;
char *restaurant;
struct _robotOrder *next;
} robotOrder;

typedef struct _deliveryList
{
robotOrder *data;
struct _deliveryList *next; /* Pointer to first food item for the order (alphabetical) */
} deliveryList;

/* compares strings for alphabetical ordering */
int strcmpi(char *s, char *t)
{
while (*s && tolower(*s) == tolower(*t))
{
s++;
t++;
}
return tolower(*s) - tolower(*t);
}
/* allocates memory with a check for successful allocation */
void *dmalloc(size_t size)
{
void *p = malloc(size);
if (!p)
{
printf("memory allocation failed\n");
exit(1);
}
return p;
}


orderList *createItem();

int insert(char *str, orderList **s);

void printItems(orderList *s);
