/*
  직책트리를 구성하고 각 노드(직책)에 속한 사원들의 정보를 이중원형으로 연결하고 그 내용을 파일에 저장하는 프로그램.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
//사원 직책 부서 등 정보저장.
typedef struct data{
   char name[20];
   char num[20];
   char cls[20];
   char cas[20];
   struct data *llink, *rlink;
}DATA;
//직책 트리
typedef struct list{
   char data[20];
   DATA *inside;
   struct list *left, *right;
}Tree;

Tree *createnode();   //트리 노드 생성
DATA *createnode1();  //이중원형 링크 생성
int printnode();      //메뉴출력
//case 1(직책트리생성)에 필요한 함수
void createfile(FILE **, char *);   //변수에 저장된 값으로 파일생성
void insertnode(Tree *, char *);    //트리에 값 설정
void levelorder(Tree *);            //현재 트리를 레벨단위로 출력

int main(){
  return 0;
}

int printnode(){
   int i;
   printf("1.직책트리 생성\n");  //파일생성 
   printf("2.사원등록\n");       //직책별 파일 기록
   printf("3.사원수정\n");
   printf("4.사원삭제\n");
   printf("5.사원조회\n");
   printf("6.트리삭제\n");
   printf("7.종료\n");
   scanf("%d", &i);
   return i;
}
  
Tree *createnode(){
    Tree *p;
    p=(Tree *)calloc(1,sizeof(Tree));
    p->inside=createnode1();
    return p;
}

DATA *createnode1(){
   DATA *p;
   p=(DATA *)calloc(1,sizeof(DATA));
   strcpy(p->name," ");
   return p;
}

//case 1
void createfile(FILE **ifp,char *data){
    char str[20];
    
    strcpy(str,data);
    strcat(str,".txt");
    *ifp=fopen(str,"w");
    if(ifp==NULL){
       printf("개방 실패\n");
    }
    fclose(*ifp);     
}

void insertnode(Tree *T, char *data){
   Tree *q;
   q=createnode();
   strcpy(q->data,data);

   if(strcmp(data,"")==0){
      printf("no value\n");
      return; 
   }

   if(strcmp(T->data,"")==0){
      strcpy(T->data,data);
   }
   else if(strcmp(T->data,data)<0){
      if(T->right==NULL){
         T->right=q;
         return;
      }
      insertnode(T->right,data);
   }
   else if(strcmp(T->data,data)>0){
      if(T->left==NULL){
         T->left=q;
         return;
      }
      insertnode(T->left,data);
   }
}

void levelorder(Tree *T){
   int count=0;
   int count1=1;
   int z=1, si=1;
   int i=1,sc=0,j;
   Tree **ap;
   Tree *t;

   t=(Tree *)calloc(1,sizeof(Tree));
   ap=(Tree **)calloc(1,sizeof(Tree *));
   ap[0]=(Tree *)calloc(1,sizeof(Tree*));
   while(1){
      z=z*2;
      ap=(Tree **)realloc(ap,(z)*sizeof(Tree *));
      if(count == 0){
         ap[count+1]=T;
         if((T->right==NULL)&&(T->left==NULL)){break;}
         count++;
      }
      else{
         for(i=1;i<=count1;i++){
            if(ap[count]->left==NULL){
               ap[count*2]=t;
            }
            else{
               ap[count*2]=ap[count]->left;
            }
            if(ap[count]->right==NULL){
              ap[(count*2+1)]=t;
            }
            else{
               ap[(count*2+1)]=ap[count]->right;
            }
            count++;
         }
         count1=count1*2;
      }
      for(i=si;i<z;i++){
         if((ap[i]->right!=NULL) ||( ap[i]->left!=NULL)){
            sc++;
            break;
         }
      }
      if(sc==0){
         break;
      }
      sc=0;
      si=z;
   }
   i=1;
   j=1;
   sc=1;
   while(i<=z){
      printf("Lv.%d ", sc);
      for(j;j<=i;j++){
         printf("%s ", ap[j]->data);
      }
      printf("\n");
      i=i*2+1;
      sc++;
   }
}

