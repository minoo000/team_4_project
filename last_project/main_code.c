#include <stdio.h>
#pragma warning(disable:4996)
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Circle_Queue.h"
#define _CRT_SECURE_NO_WARNINGS

int main()
{
    int id;
    char name[MAX_NAME_LEN];
    int birth; //[E][수정] 정수배열 불필요
    char phone[MAX_PHONENUMBER_LEN]; //[E][수정] pn >> phone
    char grade[MAX_GRADE_LEN]; //grade: 회원등급
    person user[DataNum] = { 0 }; //DECLARE ARRANGEMENT LENGTH X //[E][수정] 구조체 배열 struct person arr >> struct person user
    person* p = user;
    char* userName[DataNum] = { "Harry", "David", "Liam", "Michael", "Jenney" }; //[E][추가] userName테이블;
    char* userPhone[DataNum] = { "01092928123","01044332281","01038492021","01038921230", "01036563048" }; //[E][추가] userPhone테이블 //[E][수정] 전화번호의 자리수가 int의 max(2147483647) 넘음 >> 문자열];
    int userBirth[DataNum] = { 20220210, 202220310, 20220410, 20220510, 20220610 }; //[E][추가] userBirth테이블;
    char* userGrade[DataNum] = { "vip", "normal", "normal", "normal", "vip" }; //[E][추가] userName테이블;

    /*PrintIntArray(userBirth, MaxComfirmNum); //[E][테스팅]테이블 확인, 정상
    printf("\n");
    PrintIntArray(userPhone, MaxComfirmNum);*/
    int check;
    int person_cnt = 0;
    Queue q;
    init_Queue(&q);
    for (int i = 0; i < 5; i++)
    {
        insert_Queue(&q, i+1, userName[i], userBirth[i], userPhone[i], userGrade[i]);
    }
    Queue_print(q);
    /*while (1)
    {
        printf("=============================\n");
        printf("예약 (1)\n");
        printf("예약 취소 (2)\n");
        printf("현재 대기열 확인(3)\n");
        printf("프로그램 종료 (1, 2를 제외한 모든 정수)\n");

        scanf_s("%d", &check);

        if (check == 1)
        {
            printf("생년월일 : ");
            scanf("%s", user[person_cnt].birth);
            printf("전화번호 : ");
            scanf("%s", user[person_cnt].phone);
            printf("이름 : ");
            scanf("%s", user[person_cnt].name);
            printf("회원등급 : ");
            scanf("%s", user[person_cnt].grade);
            user[person_cnt].id = person_cnt + 1;
            insert_Queue(&q, user[person_cnt].id, user[person_cnt].name, user[person_cnt].birth, user[person_cnt].phone, user[person_cnt].grade);
            person_cnt++;

        }
        else if (check == 2)
        {
            printf("당신의 회원등급은?");
            scanf("%s", grade);
            printf("생년월일 : ");
            scanf_s("%s", birth);
            printf("전화번호 : ");
            scanf("%s", phone);
            printf("이름 : ");
            scanf("%s", name);
            printf("회원등급 : ");
            scanf("%s", grade);
            printf("id: ");
            scanf("%d", &id);
            del_data(&q, id, name, birth, phone, grade);
            person_cnt--;
        }
        else if (check == 3)
        {
            printf("============일반 대기열============\n");
            Queue_print(q);
            printf("\n");
        }
        
    }*/
    free(q.data);

    return 0;
}