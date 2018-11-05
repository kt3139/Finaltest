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
