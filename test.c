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
