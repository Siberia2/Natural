#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ShoppingItem {
    char name[50]; // 商品名称
    int quantity; // 商品数量
    struct ShoppingItem* next; // 指向下一个节点的指针
};

struct ShoppingItem* shoppingList = NULL; // 初始化购物清单为空

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
        newItem->next = list;//头插法
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
        printf("抱歉！购物车为空！\n");
    }
    while(current!=NULL)
    {
        printf("%s - 数量:%d\n",current->name,current->quantity);
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
    printf("查找商品 \"%s\" ：\n", itemName);
    while (current != NULL)
    {
        if (strcmp(current->name, itemName) == 0)
        {
             printf("%s - 数量：%d\n", current->name, current->quantity);
             return;
        }
        current=current->next;
    }
    printf("未找到商品 \"%s\"。\n", itemName);
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
            // 交换商品信息
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
 // 遍历到第一个购物清单的末尾
    while(current->next!=NULL)
    {
        current = current->next;
    }
 // 将第二个购物清单连接到第一个清单的末尾
    current->next = *list2;
    *list2 = NULL; // 清空第二个购物清单的头指针，防止误用
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
        // 如果要删除的是第一个节点
            struct ShoppingItem* temp = shoppingList;
            shoppingList = shoppingList->next;
            free(temp);
            if (!deleteAll)
            break;
        }
        else
        {
        // 如果要删除的不是第一个节点
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
    printf("欢迎来到争鸣购物小店！请选择您想要的服务！\n");
    printf("------------------------------------------\n");
    while(1)
    {
        char name[40];
        int quantity = 0;
        int n=0;
        memset(name,0,sizeof(name));
        printf(" [1] 添加商品至购物车\n");
        printf(" [2] 从购物车中移除商品\n");
        printf(" [3] 查看购物车\n");
        printf(" [4] 修改购物车商品数量\n");
        printf(" [5] 清空购物车\n");
        printf(" [6] 查看购物车中商品总数\n");
        printf(" [7] 查找购物车中商品\n");
        printf(" [8] 排序购物车中的商品\n");
        printf(" [9] 合并购物车\n");
        printf("[10] 删除购物车中的商品\n");
        printf(" [0] 结束\n");
        printf("------------------------------------------\n");
        scanf("%d",&n);
        if(n==1)
        {
            printf("请输入商品名称和数量：\n");
            printf("Ps:输入[0]来结束此操作！\n");
            while(scanf("%s",name))
            {
                if(name[0]=='0')
                {
                    printf("输入结束！！！\n");
                    break;
                }
                scanf("%d",&quantity);
                shoppingList = addItem(shoppingList, name, quantity);
                quantity = 0;
                memset(name,0,sizeof(name));
            }
            printf("当前购物车：\n");
            displayList();
            printf("\n");
        }
        else if(n==2)
        {
            printf("请输入您要删除商品的名称：\n");
            scanf("%s",name);
            removeItem(name);
            printf("删除成功！\n当前购物车：\n");
            displayList();
            printf("\n");
        }
        else if(n==3)
        {
            displayList();
        }
        else if(n==4)
        {
            printf("请输入商品名称和修改后的数量：\n");
            scanf("%s%d",name,&quantity);
            updateQuantity(name,quantity);
            printf("修改成功！\n当前购物车：\n");
            displayList();
            printf("\n");
        }
        else if(n==5)
        {
            clearList();
            printf("购物车已清空！！！\n");
        }
        else if(n==6)
        {
            printf("您当前购物车商品总数量：%d\n",totalQuantity());
        }
        else if(n==7)
        {
            printf("请输入您想要寻找的商品名称：\n");
            scanf("%s",name);
            findItem(name);
        }
        else if(n==8)
        {
            sortList();
            printf("购物车排序完毕！\n当前购物车:\n");
            displayList();
            printf("\n");
        }
        else if(n==9)
        {
            struct ShoppingItem* list1 = NULL;
            struct ShoppingItem* list2 = NULL;
            printf("清单1\n");
            printf("请输入商品名称和数量：\n");
            printf("Ps:当商品名称为[0]时，输入结束\n");
            while(scanf("%s",name))
            {
                if(name[0]=='0')
                break;
                scanf("%d",&quantity);
                list1 = addItem(list1,name,quantity);
                quantity = 0;
                memset(name,0,sizeof(name));
            }
            printf("清单2\n");
            printf("请输入商品名称和数量：\n");
            printf("Ps:当商品名称为[0]时，输入结束\n");
            while(scanf("%s",name))
            {
                if(name[0]=='0')
                break;
                scanf("%d",&quantity);
                list1 = addItem(list2,name,quantity);
                quantity = 0;
                memset(name,0,sizeof(name));
            }
            printf("\n清单合并ing.......\n");
            clearList();
            mergeLists(&list1,&list2);
            shoppingList = list1;
            printf("合并成功！！！\n");
            printf("当前购物车：\n");
            displayList();
            printf("\n");
        }
        else if(n==10)
        {
            printf("请输入您想要删除的商品：\n");
            int m;
            scanf("%s",name);
            printf("是否全部删除？是[1] 不是[0]\n");
            scanf("%d",&m);
            deleteItem(name,m);
            printf("删除成功！\n");
            printf("当前购物车：\n");
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