#include<stdio.h>
#include<malloc.h>

typedef struct node
{
	int data;
	struct node *next;	
}ListNode,*ListNodePtr;
typedef ListNodePtr List,*ListPtr;

//����ͷ����ѭ��������Ĵ��� 
ListNodePtr List_Create(int elem[],int n){
	ListNodePtr p,q;
	int i=n-1;
	q=(ListNodePtr)malloc(sizeof(ListNode));
	q->data=-1;
	q->next=q;
	while(i>=0){
		p=(ListNodePtr)malloc(sizeof(ListNode));
		p->data=elem[i];
		p->next=q->next;
		q->next=p;
		i=i-1;
	}
	p=q;
    while(p->next!=q)
    {
        p=p->next;
    }
    p->next=q->next;
    free(q);
    p=p->next;
	return p;
}

int main(){
//	��ȡN,K,M 
	float N,K,M;
	int MM;
	scanf("%f",&N);
	scanf("%f",&K);
	scanf("%f",&M);
	if(N>0&&K>=0&&M>=0&&(N-(int)N==0)&&(K-(int)K==0)&&(M-(int)M==0)&&N>=K){
		if(K==0){
			printf("0");
		}else{
			N=(int)N;
			K=(int)K;
			MM=(int)M;
			//	����N���������飬������1��N��Ԫ�� 
				int *Array,i;
				Array=(int*)calloc(N,sizeof(int));
				for(i=0;i<N;i++){
					Array[i]=i+1;
				}
				
			//	������ת��Ϊѭ�������� 
				ListNode *pp,*pos,*pre,*del;
				pp=List_Create(Array,N);
				
			//	����ɾ������ 
				int n,j,j2;
				n=N;
				pos=pp;
				while(n!=K){
					j=0;
					j2=0;
					while(j!=0||j2==0){
						pre=pos;
						pos=pos->next;
						j++;
						j=j%MM;
						j2=1;
					}
					if(pos==pp){
						del=pos;
						pre->next=pos->next;
						pos=pos->next;
						pp=pos;
						free(del);
						n--;
					}else{
						del=pos;
						pre->next=pos->next;
						pos=pos->next;
						free(del);
						n--;
					}
				} 
				
			//	��� 
				pos=pp;
				while(pp!=pos->next)
			    {
			        printf("%d,",pos->data);
			        pos=pos->next;
			    }
			    printf("%d",pos->data);
		}
	}else{
		printf("ERROR");
	} 
	return 0;
}
