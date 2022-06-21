#pragma once
/*
   @brief	: 원형큐(대기열 본체)와 큐(예약자 저장리스트)를 이용한 대기열 프로그램
   @author	: 김민음, 박민광, 박민우, 최수빈
   @date	: 2022_06_21_16:13
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

/**
 * @brief  :원형 큐 관련 매크로.
 */
//[G](12~16)원형 큐 관련 매크로
#define True 1
#define False 0
#define Error -1
#define MaxQueSize 6 //[E][수정] Max_Size >> MaxQueSize
//[W](14~18) person구조체 배열 관련 매크로
/**
 * @brief	:person구조체 배열 관련 매크로
 * @details :이름, 전화번호, 회원등급, 예약자 수, 테이블에 넣어진 데이터 수의 최대값을 정의
 *			 userName, userPhone, userBirth, userName 테이블
 * @bug     :전화번호의 자리수가 int의 max(2147483647) 넘음 >> 문자열
 */
#define MAX_NAME_LEN 10 //name MAXIMUM LENGTH 
#define MAX_PHONENUMBER_LEN 12  //phone MAXIMUM LENGTH
#define MAX_GRADE_LEN 10 //grade MAXIMUM LENGTH
#define MaxComfirmNum 200 //[E][추가] 최대 예약자수
#define DataNum 5 //[E][추가] 테이블에 넣어진 데이터 수


 /**
  * @brief	:person구조체 정의
  * @details :Circle_Queue.h의 기존 struct element 과 struct person 통합
  * @todo    :birth정의 수정(정수형 배열 필요x)
  */
typedef struct person { //DEFINE STRUCT(person) //[G,W][원본][E][수정] Circle_Queue.h의 기존 struct element 과 struct person 통합
	int id;
	char name[MAX_NAME_LEN];
	int birth; //[E][수정] 정수배열 불필요
	char phone[MAX_PHONENUMBER_LEN]; //[E][수정] pn >> phone
	char grade[MAX_GRADE_LEN];
}person;

/**
 * @brief	:각 유저정보 테이블에 있는 값을 person[i]의 각 원소에 대입하는 함수
 */

void SetUserData(person* p, int id, char name[DataNum], int birth[DataNum], char phone[DataNum], char grade[DataNum]) { //[E][추가] 각 유저정보 테이블에 있는 값을 person[i]의 각 원소에 대입하는 함수
	for (int i = 0; i < DataNum; i++)
	{
		p[i].id = i;
		*p[i].name = name[i];
		p[i].birth = birth[i];
		*p[i].phone = phone[i];
		*p[i].grade = grade[i];
	}
}

/**
 * @brief	:char형 배열 초기화 함수.
 */
void InitCharArray(char arr[]) { for (int i = 0; i < strlen(arr); i++) arr[i] = 0; }

/**
 * @brief	:char형 배열에 char형 배열의 값을 대입하는 함수, arr1(값 받음), arr2(값 전달)
 */
void CollegeCharArray(char arr1[], char arr2[])
{
	/*if (strlen(arr1) == strlen(arr2)) //두 배열의 사이즈가 다를 때
		for (int i = 0; i < strlen(arr2); i++) arr1[i] = arr2[i];
	else
	{
		if (strlen(arr1) < strlen(arr2)) {
			//[요청] 이 줄에 arr1의 배열의 길이를 arr2Size로 바꿔 재정의 하기
			for (int i = 0; i < strlen(arr1); i++) arr1[i] = 0;
			for (int i = 0; i < strlen(arr2); i++) arr1[i] = arr2[i];
		}
		else {
			for (int i = 0; i < strlen(arr1); i++) arr1[i] = 0;
			for (int i = 0; i < strlen(arr2); i++) arr1[i] = arr2[i];
		}
	}*/
	InitCharArray(arr1);
	for (int i = 0; i < strlen(arr2); i++) arr1[i] = arr2[i];
}

/**
 * @brief	:ARRAY EXCEPTION CODE CHECK NUMBER,SPECIAL ALPHA(배열 예외처리)
 * @details	:문자열에 숫자, 특수문자가 들어있는지 확인.ASCII코드 범위 설정
 */
int isStringCheck(char* s) {
	size_t size = strlen(s);
	if (size == 0)
		return 0;

	for (int i = 0; i < (int)size; i++)
	{
		if (s[i] < 32 || s[i]>65)
			if (s[i] < 91 || s[i]>96)
				if (s[i] < 123 || s[i]>126)
					return 0;
	}

	return 1;
}

/**
 * @brief	:EXCEPTION CODE CHECK ALPHA,SPECIAL ALPHA
 * @details	:문자, 특수문자가 들어있는지 확인.ASCII코드 범위 설정
 */
int isStringCheck1(char* s) {
	size_t size = strlen(s);
	if (size == 0)
		return 0;

	for (int i = 0; i < (int)size; i++)
	{
		if (s[i] > 47 || s[i] < 0)
			if (s[i] < 58 || s[i]>127)
				return 0;
	}

	return 1;
}

/**
 * @brief   :CircleQueue 관련 코드.
 */
int cur_size = 0;
/**
 * @brief   :Queue구조체 정의 .
 * @todo    :insert_Queue에 인자 추가
 */
typedef struct circlequeue {
	int rear;
	int front;
	person* data;
}Queue;

void init_Queue(Queue* q);
void insert_Queue(Queue* q, int id, char name[MAX_NAME_LEN], int birth, char phone[MAX_PHONENUMBER_LEN], char grade[MAX_GRADE_LEN]); 
person delete_Queue(Queue* q);
bool is_full(Queue* q);
bool is_empty(Queue* q);
void Queue_print(Queue q);

void init_Queue(Queue* q)
{
	q->front = 0;
	q->rear = 0;
	q->data = (person*)malloc(sizeof(person) * MaxQueSize);
}
/**
 * @todo	:(q->data[q->rear].name, name) char형 배열 대입 함수 호출
 */
void insert_Queue(Queue* q, int id, char name[MAX_NAME_LEN], int birth, char phone[MAX_PHONENUMBER_LEN], char grade[MAX_GRADE_LEN])
{
	if (is_full(q)) {
		printf("대기열이 다 찼습니다.\n");
		return;
	}
	else
	{
		q->rear = (q->rear + 1) % (MaxQueSize); //front+1이 최댓값이면 0으로 돌아가라
		q->data[q->rear].id = id;
		CollegeCharArray(q->data[q->rear].name, name); //[E][수정] char형 배열 대입 함수 호출
		q->data[q->rear].birth = birth;
		CollegeCharArray(q->data[q->rear].phone, phone);
		CollegeCharArray(q->data[q->rear].grade, grade);
	}
	cur_size++;
	return;
}

person delete_Queue(Queue* q)
{
	if (is_empty(q))
	{
		printf("대기열이 비었습니다.\n");
	}
	q->front = (q->front + 1) % (MaxQueSize);
	return q->data[q->front];
	cur_size--;
}

bool is_empty(Queue* q) {
	if (q->front == q->rear)
		return True;
	else
		return False;
}

bool is_full(Queue* q)
{
	if (((q->rear + 1) % MaxQueSize) == q->front)
		return True;
	else
		return False;
}
/**
 * @todo	:void del_data 인자 추가, (q->data[i].name) char형 배열 초기화 함수(InitCharArray) 호출,
 *			 (q->data[target].name, q->data[i].name) char형 배열 대입 함수(CollegeCharArray) 호출
 */
void del_data(Queue* q, int del_id, char del_name[MAX_NAME_LEN], int del_birth, char del_phone[MAX_PHONENUMBER_LEN], char del_grade[MAX_GRADE_LEN]) //[E][수정] 인자 추가
{
	printf("삭제된 id: %d\n", del_id);
	int cnt = 0;
	for (int i = q->front; i <= q->rear; i = (i + 1) % MaxQueSize)
	{
		if (q->data[i].id == del_id
			&& strcmp(q->data[i].name, del_name) == 0
			&& q->data[i].birth == del_birth
			&& strcmp(q->data[i].phone, del_phone) == 0
			&& strcmp(q->data[i].grade, del_grade) == 0)
		{
			q->data[i].id = 0;
			InitCharArray(q->data[i].name); //[E][수정] char형 배열 초기화 함수 호출
			q->data[i].birth = 0;
			InitCharArray(q->data[i].phone);
			InitCharArray(q->data[i].grade);
			cnt++;
		}
		else if (cnt > 0)
		{
			int target = i - cnt;
			if (target < 0)
				target += MaxQueSize;
			q->data[target].id = q->data[i].id;
			CollegeCharArray(q->data[target].name, q->data[i].name); //[E][수정] char형 배열 대입 함수 호출
			q->data[target].birth = q->data[i].birth;
			CollegeCharArray(q->data[target].phone, q->data[i].phone);
			CollegeCharArray(q->data[target].grade, q->data[i].grade);

			q->data[i].id = 0;
			InitCharArray(q->data[i].name); //[E][수정] char형 배열 초기화 함수 호출
			q->data[i].birth = 0;
			InitCharArray(q->data[i].phone);
			InitCharArray(q->data[i].grade);
		}
	}
}

void Queue_print(Queue q)
{
	int i = q.front;
	if (is_empty(&q)) {
		printf("대기열이 비어있습니다.\n");
		return;
	}

	do {
		i = (i + 1) % MaxQueSize;
		printf("대기자 id : %d   ||", q.data[i].id);
		printf("   대기자 이름 : %s", q.data[i].name); //[E][추가](222~225)각 char형 배열, int형 변수 출력 
		printf("   ||   대기자 생년월일 : %d", q.data[i].birth);
		printf("   ||   대기자 연락처 : %s", q.data[i].phone);
		printf("   ||   대기자 등급 : %s", q.data[i].grade);
		printf("   ||   (rear : % d)\n", q.rear);
		printf("\n\n");
		if (i == q.rear)
			break;
	} while (i != q.front);
	printf("\n\n\n");
}
