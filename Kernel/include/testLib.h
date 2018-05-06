//
// Created by juangod on 18/04/18.
//

#ifndef TP2_TEMPORARY_TESTLIB_H
#define TP2_TEMPORARY_TESTLIB_H

#define TB_SUCCESS 0
#define TG_SUCCESS 255
#define TR_SUCCESS 0

#define TB_FAIL 0
#define TG_FAIL 0
#define TR_FAIL 255

#define TB 0
#define TG 255
#define TR 255

void checkIsNotNull(void * pointer);
void ok();
void fail(char * errorMsg);
void notImplemented();
void thenSuccess();
void checkStringsEqual(char* str1, char* str2);
void givenNothing();
#endif //TP2_TEMPORARY_TESTLIB_H
