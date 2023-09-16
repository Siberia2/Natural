#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ShoppingItem {
    char name[50]; // ��Ʒ����
    int quantity; // ��Ʒ����
    struct ShoppingItem* next; // ָ����һ���ڵ��ָ��
};

struct ShoppingItem* shoppingList = NULL; // ��ʼ�������嵥Ϊ��

struct ShoppingItem* addItem(struct ShoppingItem* list, char itemName[], int itemQuantity) 
{
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    strcpy(newItem->name,itemName);
    newItem->quantity = itemQuantity;
    newItem->next = NULL;
    if(list == NULL)
    {
        list = newItem;
    }
    else
    {
        newItem->next = list;//ͷ�巨
        list = newItem;
    }
    return list;
}

void removeItem(char itemName[]) 
{
     struct ShoppingItem* current = shoppingList;
     struct ShoppingItem* previous = NULL;
     while (current != NULL)
     {
        if (strcmp(current->name, itemName) == 0)
        {
            if (previous != NULL) 
            {
                previous->next = current->next;
            } 
            else
            {
                shoppingList = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
 }
}

void displayList()
{
    struct ShoppingItem* current = shoppingList;
    if(current==NULL)
    {
        printf("��Ǹ�����ﳵΪ�գ�\n");
    }
    while(current!=NULL)
    {
        printf("%s - ����:%d\n",current->name,current->quantity);
        current=current->next;
    }
}

void updateQuantity(char itemName[], int newItemQuantity)
{
    struct ShoppingItem* current = shoppingList;
    while (current != NULL)
    {
        if (strcmp(current->name, itemName) == 0)
        {
            current->quantity = newItemQuantity;
            break;
        }
        current = current->next;
    }
}

void clearList()
{
    struct ShoppingItem* temp = NULL;
    while (shoppingList != NULL)
    {
        temp = shoppingList;
        shoppingList = shoppingList->next;
        free(temp);
    }
    //return ;
}

int totalQuantity() 
{
    struct ShoppingItem* current = shoppingList;
    int total = 0;
    while (current != NULL)
    {
        total=total+current->quantity;
        current=current->next;
    }
    return total;
}

void findItem(char itemName[])
{
    struct ShoppingItem* current = shoppingList;
    printf("������Ʒ \"%s\" ��\n", itemName);
    while (current != NULL)
    {
        if (strcmp(current->name, itemName) == 0)
        {
             printf("%s - ������%d\n", current->name, current->quantity);
             return;
        }
        current=current->next;
    }
    printf("δ�ҵ���Ʒ \"%s\"��\n", itemName);
}

void sortList()
{
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* nextItem = NULL;
    char tempName[50];
    int tempQuantity;
    while (current != NULL)
    {
        nextItem = current->next;
        while (nextItem != NULL)
        {
            if (strcmp(current->name, nextItem->name) > 0)
            {
            // ������Ʒ��Ϣ
            strcpy(tempName,current->name);
            strcpy(current->name,nextItem->name);
            strcpy(nextItem->name,tempName);

            tempQuantity = current->quantity;
            current->quantity = nextItem->quantity;
            nextItem->quantity = tempQuantity;
            }
            nextItem = nextItem->next;
        }
        current = current->next;
    }
}

void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2)
{
    struct ShoppingItem* current = *list1;
 // ��������һ�������嵥��ĩβ
    while(current->next!=NULL)
    {
        current = current->next;
    }
 // ���ڶ��������嵥���ӵ���һ���嵥��ĩβ
    current->next = *list2;
    *list2 = NULL; // ��յڶ��������嵥��ͷָ�룬��ֹ����
}

void deleteItem(char itemName[], int deleteAll)
{
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* prev = NULL;
    while (current != NULL)
    {
    if (strcmp(current->name, itemName) == 0)
    {
        if (prev == NULL)
        {
        // ���Ҫɾ�����ǵ�һ���ڵ�
            struct ShoppingItem* temp = shoppingList;
            shoppingList = shoppingList->next;
            free(temp);
            if (!deleteAll)
            break;
        }
        else
        {
        // ���Ҫɾ���Ĳ��ǵ�һ���ڵ�
            while(strcmp(current->name,itemName)==0)
            {
                struct ShoppingItem* temp = NULL;
                temp = current;
                current = current->next;
                free(temp);
                if (!deleteAll||current==NULL)
                break;
            }
            prev->next=current;
            prev=current;
            if(current!=NULL)
            {
                current = current->next;
            }
            if(!deleteAll)
            break;
        }
    }
    else
    {
        prev = current;
        current = current->next;
    }
    }
}

int main(void)
{
    printf("��ӭ������������С�꣡��ѡ������Ҫ�ķ���\n");
    printf("------------------------------------------\n");
    while(1)
    {
        char name[40];
        int quantity = 0;
        int n=0;
        memset(name,0,sizeof(name));
        printf(" [1] �����Ʒ�����ﳵ\n");
        printf(" [2] �ӹ��ﳵ���Ƴ���Ʒ\n");
        printf(" [3] �鿴���ﳵ\n");
        printf(" [4] �޸Ĺ��ﳵ��Ʒ����\n");
        printf(" [5] ��չ��ﳵ\n");
        printf(" [6] �鿴���ﳵ����Ʒ����\n");
        printf(" [7] ���ҹ��ﳵ����Ʒ\n");
        printf(" [8] �����ﳵ�е���Ʒ\n");
        printf(" [9] �ϲ����ﳵ\n");
        printf("[10] ɾ�����ﳵ�е���Ʒ\n");
        printf(" [0] ����\n");
        printf("------------------------------------------\n");
        scanf("%d",&n);
        if(n==1)
        {
            printf("��������Ʒ���ƺ�������\n");
            printf("Ps:����[0]�������˲�����\n");
            while(scanf("%s",name))
            {
                if(name[0]=='0')
                {
                    printf("�������������\n");
                    break;
                }
                scanf("%d",&quantity);
                shoppingList = addItem(shoppingList, name, quantity);
                quantity = 0;
                memset(name,0,sizeof(name));
            }
            printf("��ǰ���ﳵ��\n");
            displayList();
            printf("\n");
        }
        else if(n==2)
        {
            printf("��������Ҫɾ����Ʒ�����ƣ�\n");
            scanf("%s",name);
            removeItem(name);
            printf("ɾ���ɹ���\n��ǰ���ﳵ��\n");
            displayList();
            printf("\n");
        }
        else if(n==3)
        {
            displayList();
        }
        else if(n==4)
        {
            printf("��������Ʒ���ƺ��޸ĺ��������\n");
            scanf("%s%d",name,&quantity);
            updateQuantity(name,quantity);
            printf("�޸ĳɹ���\n��ǰ���ﳵ��\n");
            displayList();
            printf("\n");
        }
        else if(n==5)
        {
            clearList();
            printf("���ﳵ����գ�����\n");
        }
        else if(n==6)
        {
            printf("����ǰ���ﳵ��Ʒ��������%d\n",totalQuantity());
        }
        else if(n==7)
        {
            printf("����������ҪѰ�ҵ���Ʒ���ƣ�\n");
            scanf("%s",name);
            findItem(name);
        }
        else if(n==8)
        {
            sortList();
            printf("���ﳵ������ϣ�\n��ǰ���ﳵ:\n");
            displayList();
            printf("\n");
        }
        else if(n==9)
        {
            struct ShoppingItem* list1 = NULL;
            struct ShoppingItem* list2 = NULL;
            printf("�嵥1\n");
            printf("��������Ʒ���ƺ�������\n");
            printf("Ps:����Ʒ����Ϊ[0]ʱ���������\n");
            while(scanf("%s",name))
            {
                if(name[0]=='0')
                break;
                scanf("%d",&quantity);
                list1 = addItem(list1,name,quantity);
                quantity = 0;
                memset(name,0,sizeof(name));
            }
            printf("�嵥2\n");
            printf("��������Ʒ���ƺ�������\n");
            printf("Ps:����Ʒ����Ϊ[0]ʱ���������\n");
            while(scanf("%s",name))
            {
                if(name[0]=='0')
                break;
                scanf("%d",&quantity);
                list1 = addItem(list2,name,quantity);
                quantity = 0;
                memset(name,0,sizeof(name));
            }
            printf("\n�嵥�ϲ�ing.......\n");
            clearList();
            mergeLists(&list1,&list2);
            shoppingList = list1;
            printf("�ϲ��ɹ�������\n");
            printf("��ǰ���ﳵ��\n");
            displayList();
            printf("\n");
        }
        else if(n==10)
        {
            printf("����������Ҫɾ������Ʒ��\n");
            int m;
            scanf("%s",name);
            printf("�Ƿ�ȫ��ɾ������[1] ����[0]\n");
            scanf("%d",&m);
            deleteItem(name,m);
            printf("ɾ���ɹ���\n");
            printf("��ǰ���ﳵ��\n");
            displayList();
            printf("\n");
        }
        else if(n==0)
        {
            break;
        }
    }
    return 0;
}