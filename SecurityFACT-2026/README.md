# 스터디 개요

월요일 : 온라인/과제
수요일 : 오프라인 (6시)

# 스터디 기록

## 04-06 (오프라인)

(1) 프로세스 메모리 및 권한

(2) 디버깅 개요
 
**과제**

(1) 실습 환경 구축

(2) 분석 도구 설치

(3) [이론] 함수 호출 규약

(4) [이론] x86 어셈블리어

(5) [실습] handray


## 05-11 (온라인)

**과제**

(1) 분석 도구 설치

(2) [Uninitialized Memory] handray 분석


## 05-13 (오프라인)

(1) pwntools, pwndbg, docker 설치 및 실습

(2) Buffer Overflow

(3) Stack Canary

(4) ROP

**과제**

(1) [이론/실습] pwntools 명령어 학습

(2) [이론/실습] 버퍼오버플로우

(3) [이론] Stack Canary

(4) [이론] ASLR / PIE 조사


## 05-25 (온라인)

**과제**

[실습] [ret2libc](https://dreamhack.io/wargame/challenges/353)

## 05-27 

(1) 문제 분석, 디버깅, 익스플로잇 코드 작성 전과정 학습 & 복습

`미티게이션 확인 - checksec`
`정적 분석 - objdump`
`동적 분석 - gdb`
`익스플로잇 작성 - pwntools`
`ASLR/PIE`
`ret2libc`
`canary`

(2) ROP

(3) RELRO

(4) format string bug

(5) RELRO / GOT Overwrite


**과제** 

(1) [이론] format string bug

(2) [이론] RELRO / lazy binding

(3) [실습/기한X] [FSB]

(4) [실습/기한X] [PIE]


## 06-01 (오프라인)

**과제**

(1) [이론/실습] shellcode (문제 : https://github.com/dretoh/Pwnable101/tree/main/SecurityFACT-2026/prob/orw)

hint : open - read - write 시스템 호출 활용

(2) [이론/실습] tcache / tcache poisoning 조사

(3) [실습] [tcache_poisoning](https://dreamhack.io/wargame/challenges/358/)

(4) [기한X, ROP 문제] babyrop


## 06-22, 24 (방학-온라인)

(1) Heap 개요

**과제**

(1) [실습] IDA Free 설치

## 07-01 (방학-온라인)

(1) babyrop 문제 풀이 

(2) FSB 문제 풀이

(3) Heap Exploit 개요 

(4) Double Free, Use After Free

(5) tcache poisoning

## 스터디 진행 사항 정리

| 주차 | 핵심 | 세부사항 |
|---|---|---|
| 1주차(04-06~04-12) | Linux, C | 프로세스 메모리 구조 및 권한, 함수호출 규약과 어셈블리 |
| 2주차(04-13~04-19) | 과제 기간 |  |
| 3주차(04-20~04-26) | midterm |  |
| 4주차(04-27~05-03) | midterm |  |
| 5주차(05-04~05-10) | 과제 기간 |  |
| 6주차(05-11~05-17) | REVERSING, BOF |  |
| 7주차(05-18~05-24) | ROP |  |
| 8주차(05-25~05-31) | FSB |  |
| 9주차(06-01~06-07) | SHELLCODE |  |
| 10주차(06-08~06-14) | 과제 기간 |  |
| 11주차(06-15~06-21) | final |  |
| 12주차(06-22~06-28) | final |  |
| 13주차(06-29~07-05) | HEAP 개요, Double Free, UAF | tcache poisoning |
| 14주차(07-06~07-12) | X |  |
| 15주차(07-13~07-19) | X |  |
| 16주차(07-20~07-26) | X |  |

## 학습 개념 및 기술

| 단계 | 개념 및 기술 |
|---|---|
| STEP1 |  |
| STEP2 |  |

## 풀이과정 공개

| 문제 | 문제 링크 | 풀이 과정 링크 | 세부사항 |
|---|---|---|---|
| FSB | [FSB](https://github.com/dretoh/Pwnable101/blob/main/03-Format-String-Bug/prob.c) | [EXPLOIT](https://github.com/dretoh/Pwnable101/blob/main/03-Format-String-Bug/ex.py) | __stack_chk_fail 활용 |
| BABYROP | [BABYROP](https://github.com/dretoh/Pwnable101/blob/main/SecurityFACT-2026/prob/babyrop) | [EXPLOIT](https://github.com/dretoh/Pwnable101/blob/main/SecurityFACT-2026/prob/babyrop-exploit.py) | Stack Pivot, RET2DLRESOLVE |
| PIE-PROB | [PIE-PROB](https://github.com/dretoh/Pwnable101/blob/main/SecurityFACT-2026/prob/pie-prob) | [EXPLOIT](https://github.com/dretoh/Pwnable101/blob/main/SecurityFACT-2026/prob/pie-prob-exploit.py) | |