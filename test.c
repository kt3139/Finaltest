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
//case 2 사원등록에 필요한 함수
DATA *pinsert();                    //사원등록시 필요한 데이터를 입력받음
int checknode(Tree *T,char *);      //이중 원형링크 내에 중복검사
int samesearch(Tree *T,char *);     //전체 노드에 checknode를 이용하여 중복검사
void Tsearch(Tree *, DATA *);       //입력한 데이터에서 직책데이터와 같은 노드를 찾고 addsearch와 insearch를 이용하여 이중원형링크 연걸
void addsearch(Tree *, DATA *);     //Tsearch에서 정렬을 하기 위한 함수
void insearch(Tree *, DATA *);      //Tsearch에서 정렬을 하기 위한 함수
//case 3
void inquirysearch(Tree *, char *);
void inquiryprint(Tree *, char *);
//case 4
void deletesearch(Tree *,char *);
void deletenode(Tree *, char *);
void Tdeletenode(Tree *, char *);
//case 6
int countnode(Tree *, char *);
int searchcount(Tree *,char *);
//open 여러 기능에서 사용하는 함수.
void searchfile(Tree *, FILE *);
void insertfile(Tree *, FILE *);
void printsearch(Tree *); 
void printnode1(Tree *);

int main(){
  Tree *T;
  Tree **ap;
  DATA *data;
  char *pos[]={"사장","전무","과장","차장","이사","주임","사원"};
  FILE *ifp;
  char sea[20];
  int s,i=0,same=0, same1=0;
  int count1; // count잘못 가져왔을 가능성 있음.
  char nam[3]={};
  char posi[20];
  
  while(1){
    s=printnode();  //메뉴를 출력하고 상요자가 선택한 값을 얻음
    switch(s){
         case 1:
            for(i=0;i<(sizeof(pos)/sizeof(*pos));i++){
               createfile(&ifp,pos[i]);
               insertnode(T,pos[i]);
            }
            printf("개방 성공\n");
            levelorder(T);
            printf("\n");
          break;
          case 2:

            if(strcmp(T->data,"")==0){
               printf("트리 없음\n");
               break;
            }
            data=createnode1();
            data=pinsert();
            same=samesearch(T, data->num);
            if(same!=1){
               Tsearch(T, data);
               searchfile(T, ifp);
               printf("성공\n");
            }
            else{
               printf("번호중복\n");
            }
            printsearch(T);
         break;
        case 3:
            if(strcmp(T->data,"")==0){
               printf("트리 없음\n");
               break;
            }
            printf("수정 할 사원 번호 : ");
            __fpurge(stdin);
            scanf("%s", sea);
            same=samesearch(T, sea);
            if(same!=1){
               printf("사원 번호 오류\n");
            }
            else{
               deletesearch(T,sea);
               while(1){
                  printf("*****  수정  *****\n");
                  data=createnode1();
                  data=pinsert();
                  same1=samesearch(T, data->num);
                  if(same1!=1){
                    Tsearch(T,data);
                    printf("수정완료\n");
                    break; 
                  }
                  else{
                     printf("번호 중복\n");
                     printsearch(T);
                  }
               }
               searchfile(T, ifp);
            }
         break;

         case 4:
            if(strcmp(T->data,"")==0){
               printf("트리 없음\n");
               break;
            }
            printf("지울 사원 번호 : ");
            __fpurge(stdin);
            scanf("%s", sea);
            deletesearch(T,sea);
            searchfile(T,ifp);
            printsearch(T);
         break;
         case 5:
            printf("***** 조회 *****\n");
            if(strcmp(T->data,"")==0){
               printf("트리 없음\n");
               break;
            }
            printf("성을 입력하세요 ");
            __fpurge(stdin);
            gets(nam);
            inquirysearch(T,nam);
         break;
         case 6:
            if(strcmp(T->data,"")==0){
              printf("트리 없음 \n");
            }
            else{
               printf("제거할 직책 트리 : ");
               __fpurge(stdin);
               scanf("%s", posi);
               count1=countnode(T,posi);
               if(count1>0){
                  printf("트리제거 불가\n");
               }
               else{
                  printf("트리제거 완료\n");
                  Tdeletenode(T,posi);
               }
            } 
            levelorder(T);
            printf("\n");
         break;
         case 7:
         break;
         default:
           printf("키가 없음\n");
           break;
    }
    if(s==7)break;
  }
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
   return i; //원하는 숫자 항목을 입력받아 그입력받은 숫자를 리턴시켜서 메인 함수로보냄
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

DATA *pinsert(){
   DATA *data;

   data=createnode1();
   printf("사원명 : ");
   __fpurge(stdin);
   gets(data->name);
//   scanf("%s", data->name);
   printf("전화번호 : ");
   __fpurge(stdin);
   scanf("%s", data->num);
   printf("직책 : ");
   __fpurge(stdin);
   scanf("%s", data->cls);
   printf("부서 : ");
   __fpurge(stdin);
   scanf("%s", data->cas);

   return data;
}

int checknode(Tree *T,char *data){
   Tree *p;
   DATA *q;

   p=T;
   q=p->inside;
   if(q->rlink!=NULL){
      do{
         q=q->rlink;
         if(strcmp(q->num,data)==0){printf("\n");return 1;}
      }while(p->inside->rlink!=q->rlink);
   }
   return 0;
}

int samesearch(Tree *T,char *data){
   int count;
   if(T){
      return count=checknode(T,data)+samesearch(T->left,data)+samesearch(T->right,data);
   }
}

void Tsearch(Tree *T, DATA *data){
    Tree *p;
    DATA *q, *r;
    int ft=0;

    p=T;
    q=data;
    printf("%s\n", q->cls);
   
    if(strcmp(p->data,"")==0){
       printf("no value\n");
    }
    else{
       while(p){
          if(strcmp(p->data,q->cls)==0){
             if(p->inside->rlink==NULL){
                  p->inside->rlink=q;
                  q->rlink=p->inside->rlink;
                  q->llink=p->inside->rlink; 
                  printf("성공\n");
             }
             else{
               if(strcmp(p->inside->rlink->llink->name,q->name)<0){
                  addsearch(p,data);
               }
               else{
                  insearch(p,data);
               }
             }
             break;
          }
          else if(strcmp(p->data,q->cls)<0){
             p=p->right; 
          }
          else if(strcmp(p->data,q->cls)>0){
             p=p->left;
          }
          else{
             printf("novalue\n");
             break;
          }
       }
    }
}

void addsearch(Tree *T, DATA *data){
   Tree *p;
   DATA *q;

   p=T;
   q=data;
   
   p->inside->rlink->llink->rlink=q;
   q->llink=p->inside->rlink->llink;
   q->rlink=p->inside->rlink;
   p->inside->rlink->llink=q;

}

void insearch(Tree *T, DATA *data){
   Tree *p;
   DATA *q, *r;

   p=T;
   q=data;
   r=p->inside; 

   if(strcmp(p->inside->rlink->name,q->name)>0){
      q->llink=p->inside->rlink->llink;
      p->inside->rlink->llink->rlink=q;
      q->rlink=p->inside->rlink;
      p->inside->rlink->llink=q;
      p->inside->rlink=q;
   }
   else{
      do{
         r=r->rlink;
         if(strcmp(r->rlink->name,q->name)>0){break;}
      }while(r->rlink!=p->inside->rlink);
      q->rlink=r->rlink;
      r->rlink->llink=q;
      r->rlink=q;
      q->llink=r;
   }
}
void inquirysearch(Tree *T, char *data){
   if(T){
      inquiryprint(T,data);
      inquirysearch(T->left,data);
      inquirysearch(T->right,data);
   }
}
//스위치 번호 3번으로 들어왓을때
void inquiryprint(Tree *T, char *data){
   Tree *p;
   DATA *q;
   char nam[4];
   int i;
   if(T->inside->rlink!=NULL){
      p=T;
      q=p->inside;
      do{
         q=q->rlink;
         for(i=0;i<3;i++){
            nam[i]=q->name[i];
         }
         nam[i]='\0';
         if(strcmp(nam,data)==0){
            printf("%s %s %s %s\n", q->name, q->num, q->cls, q->cas);
         }
      }while(q->rlink!=p->inside->rlink);
   }
}
//case 4 : delete 서치 까지만 함 나머지 부분 
void deletesearch(Tree *T,char *data){
   if(T){
      deletenode(T, data);
      deletesearch(T->left,data);
      deletesearch(T->right,data);
   }
} 
void deletenode(Tree *T, char *data){
   Tree *p;
   DATA *q;

   if(T->inside->rlink!=NULL){
      p=T;
      q=p->inside;
      do{
         q=q->rlink;
         if(strcmp(q->num,data)==0){
            if(q->rlink==q->rlink->rlink){
               p->inside->rlink=NULL;
            }
            else if(p->inside->rlink==q){
               p->inside->rlink=q->rlink;
               q->rlink->llink=q->llink;
               q->llink->rlink=q->rlink;
            }
            else{
              q->rlink->llink=q->llink;
              q->llink->rlink=q->rlink;
            }
            free(q);
            break;
         }
      }while(q->rlink!=p->inside->rlink);
   }
}

void Tdeletenode(Tree *T, char *data){
Tree *p, *q, *r, *z;
   p=T;
   r=p;

   if(strcmp(T->data,data)==0 && T->right==NULL && T->left==NULL){
       strcpy(T->data,"");
   }
   else{
      while(p){
         if(strcmp(p->data,data)==0){
            if(p->right==NULL && p->left==NULL){
               if(strcmp(r->data,data)>0){
                  r->left=NULL;
                  free(p);
                  break;
               }
               else{
                  r->right=NULL;
                  free(p);
                  break;
               }
            }    
            else if(p->right==NULL){
               if(p==T){
                  p=p->left;
                  strcpy(T->data,p->data);
                  T->left=p->left;
                  T->right=p->right;
                  free(p);
                  break;
               }
               else if(strcmp(r->data,data)>0){
                   r->left=p->left;
                   free(p);
                   break;
               }
               else{
                   r->right=p->left;
                   free(p);
                   break;
               }  
            }
            else if(p->left==NULL){
               if(p==T){
                  p=p->right;
                  strcpy(T->data,p->data);
                  T->right=p->right;
                  T->left=p->left;
                  free(p); 
                  break;
               }
               else if(strcmp(r->data,data)>0){
                  r->left=p->right;
                  free(p);
                  break;
               }
               else{
                 r->right=p->right;
                 free(p);
                 break;
               }
            }
            else{
               if(p==T){
                 p=p->right;
                 if(p->left==NULL){
                    strcpy(T->data,p->data);
                    T->right=p->right;
                    free(p);
                    break;
                 }
                 else{
                    while(p->left!=NULL){
                       q=p;
                       p=p->left; 
                    }
                    q->left=p->left;
                    strcpy(T->data,p->data);
                    free(p); 
                    break;
                 } 
               }
               else if(strcmp(r->data,data)>0){
                  z=p->right;
                  q=z;
                  if(z->left==NULL){
                     z->left=p->left;
                     r->left=z;
                     free(p);
                     break;
                  }
                  else{
                     while(z->left!=NULL){
                        q=z;
                        z=z->left;
                     }
                     q->left=z->left;
                     z->right=p->right;
                     z->left=p->left;
                     r->left=z;
                     free(p);
                     break; 
                  }
               }
               else{
                 z=p->right;
                 q=z;
                 if(z->left==NULL){
                     z->left=p->left;
                     r->right=z;
                     free(p);
                 }
                 else{
                    while(z->left!=NULL){
                       q=z;
                       z=z->left;
                    }
                    q->left=z->left;
                    z->right=p->right;
                    z->left=p->left;
                    r->right=z;
                    free(p);
                    break;
                 }
               }
            }
         }
         else if(strcmp(p->data,data)>0){
            r=p;
            p=p->left;
         }
         else if(strcmp(p->data,data)<0){
            r=p;
            p=p->right;
         }
         else{
            printf("no value\n");
            break;
         }
      }
   }

}


int countnode(Tree *T, char *data){
   Tree *p;
   int tf=0;
   p=T;
  
   if(strcmp(p->data,"")==0){
      printf("no value\n");
   }
   else{
      while(1){
         if(strcmp(p->data,data)==0){
            tf=searchcount(p,data);
            break;
         }
         else if(strcmp(p->data,data)<0){
            if(p->right==NULL){
               break;
            }
            p=p->right;
         }
         else if(strcmp(p->data,data)>0){
            if(p->left==NULL){
               break;
            }
            p=p->left;
         }
      }
   }
   return tf;
} 
int searchcount(Tree *T, char *data){
   Tree *p;
   DATA *q;

   p=T;
   q=p->inside;
   if(q->rlink!=NULL){
      do{
         q=q->rlink;
         if(strcmp(q->num,"")!=0){return 1;}
      }while(p->inside->rlink!=q->rlink);
   }
   return 0;
}
//open
void searchfile(Tree *T, FILE *ifp){
   if(T){
      insertfile(T,ifp);
      searchfile(T->left, ifp);
      searchfile(T->right, ifp);
   }
}
void insertfile(Tree *T, FILE *ifp){
   Tree *p;
   DATA *q, *r;
   char str[20];
  
   p=T;
   if(strcmp(p->data,"")==0){
      printf("no value\n");
   }
   else{
      p=T;
      q=p->inside;
      strcpy(str,p->data);
      strcat(str,".txt");
      ifp=fopen(str,"w");
      if(ifp==NULL){
         printf("출력 파일 개방 실패.\n");
         return ;
      }
      if(T->inside->rlink!=NULL){
         if(q->rlink!=NULL){
            printf("입력\n");
            do{
               q=q->rlink;
               fprintf(ifp,"%s %s %s %s\n",q->name, q->num, q->cls, q->cas);
            }while(q->rlink!=p->inside->rlink);
         }
      }
      fclose(ifp);
   }
}

void printsearch(Tree *T){
   if(T){
      printnode1(T);
      printsearch(T->left);
      printsearch(T->right);
   }
}

void printnode1(Tree *T){
   Tree *p;
   DATA *q;

   p=T;
   q=p->inside;
   printf("%s = ", T->data);
   if(p->inside->rlink!=NULL){
      do{
         q=q->rlink; 
         printf("*%s*", q->num);
      }while(q->rlink!=p->inside->rlink);  
   }
   printf("\n");
}

