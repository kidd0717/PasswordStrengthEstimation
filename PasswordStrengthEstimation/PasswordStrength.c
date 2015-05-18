//
//  main.cpp
//  PasswordStrength
//
//  Created by MMY on 2014/10/6.
//  Copyright (c) 2014年 MMY. All rights reserved.
//
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "PasswordStrength.h"

//using namespace std;
#pragma mark - mem check
int newSize = 0;
int delSize = 0;
#define new(TYPE, n) malloc(n*sizeof(TYPE)); newSize+=n*sizeof(TYPE)
#define del(ptr, TYPE, n) free(ptr); delSize+=n*sizeof(TYPE)
#define mcheck() printf("Memory:newSize=%d delSize=%d leakSize=%d\n", \
newSize, delSize, newSize-delSize);




void getPasswordStrength(const char *password, int *score , char** strength);
char* calculateStrenth(int score);

int plusScore(const char *password);
int minusScore(const char *password);

enum charType {CHAR_TYPE_UPPER,CHAR_TYPE_LOWER,CHAR_TYPE_NUMBER,CHAR_TYPE_OTHER};
struct charCount
{
    char c;
    int count;
    struct charCount *next;
};
//#pragma mark - class
//passwordStrength::passwordStrength()
//{
//    _password = (char*)"init";
//    _score = 0;
//}
//passwordStrength::passwordStrength(char* password)
//{
//    _password = password;
//    _score = calculate(password);
//}
//int passwordStrength::score()
//{
//    return _score;
//}

//function
#pragma mark - public function
void getPasswordStrength(const char *password, int *score , char** strength)
{
    *score = plusScore(password) - minusScore(password);
    *strength = calculateStrenth(*score);
    
    printf("score:%d",*score);
}
#pragma mark - private function
char* calculateStrenth(int score)
{
    if(score <= 30)
    {
        return PASSWORD_STRENGTH_LOW;
    }
    else if(score > 30 && score <= 60)
    {
        return PASSWORD_STRENGTH_MID;
    }
    else if(score > 60 && score <= 80)
    {
        return PASSWORD_STRENGTH_HIGH;
    }
    else if(score > 80)
    {
        return PASSWORD_STRENGTH_VERY_HIGH;
    }
    return PASSWORD_STRENGTH_LOW;
}

int plusScore(const char *password)
{
    int upperCount = 0;
    int lowerCount = 0;
    int numberCount = 0;
    int punctCount = 0;
    int middleNumberCount = 0;
    int conditionCount = 0;
    
    for(int i = 0 ; i < strlen(password) ; i++)
    {
        if(isupper(password[i]))
        {
            upperCount++;
            
        }
        else if(islower(password[i]))
        {
            lowerCount++;
        }
        else if(isdigit(password[i]))
        {
            numberCount++;
            if(i > 0 && i < strlen(password) - 1)
            {
                middleNumberCount++;
            }
        }
        else if(ispunct(password[i]))
        {
            punctCount++;
            if(i > 0 && i < strlen(password) - 1)
            {
                middleNumberCount++;
            }
        }
    }
    if(numberCount > 0)
    {
        conditionCount++;
    }
    if((upperCount != 0 && lowerCount != 0 ) || numberCount != 0 || punctCount != 0)
    {
        if(upperCount > 0)
        {
            conditionCount++;
        }
        
        if(lowerCount > 0)
        {
            conditionCount++;
        }
    }
    if(punctCount > 0)
    {
        conditionCount++;
    }
    
    if(strlen(password) >= 8)
    {
        conditionCount++;
    }
    else
    {
        conditionCount = 0;
    }
    
    
    // calculate upper , lower , number , punctuation score
    int stringLength = (int)strlen(password);
    int upperScore = 0;
    int lowerScore = 0;
    int numberScore = 0;
    int punctScore = 0;
    int middleNumberScore = 0;
    int coditionScore = 0;
    
    // upper & lower score
    if((upperCount != 0 && lowerCount != 0 ) || numberCount != 0 || punctCount != 0)
    {
        if(upperCount > 0)
        {
            upperScore = (stringLength - upperCount) * 2;
        }
        
        if(lowerCount > 0)
        {
            lowerScore = (stringLength - lowerCount) * 2;
        }
    }
    //number score
    if(upperCount != 0 || lowerCount != 0 || punctCount != 0)
    {
        numberScore = numberCount * 4;
    }
    //punctuation score
    punctScore = punctCount * 6;
    
    //middle number score
    middleNumberScore = middleNumberCount * 2;
    
    //condition count score
    
    coditionScore = conditionCount * 2;
    
    //calculate score
    int score = stringLength*4 + upperScore + lowerScore + numberScore + punctScore + middleNumberScore + coditionScore;
    //    printf("length:%d , upper:%d , lower:%d , number:%d , punctuaion:%d , middle number:%d , condition:%d\n",stringLength,upperCount,lowerCount,numberCount,punctCount,middleNumberCount,conditionCount);
    //    printf("length score:%D , upper score:%d , lower score:%d , number score:%d , punctuaion score:%d , middle score:%d , condition score:%d\n",stringLength*4,upperScore,lowerScore,numberScore,punctScore,middleNumberScore,coditionScore);
    
    return score;
}
int minusScore(const char *password)
{
    int strLen = (int)strlen(password);
    
    int minusScore = 0;
    int isAllAlpha = 1;
    int isAllNumber = 1;
    enum charType lastCharType = CHAR_TYPE_OTHER;
    int continueCharTypeCount = 0;
    //    map<char, int> dictionary;
    int continueCharCount = 0;
    
    // link list
    struct charCount *head = NULL;
    struct charCount *current = NULL;
    struct charCount *prev = NULL;
    
    for(int i = 0 ; i < strlen(password) ; i++)
    {
        if(!isalpha(password[i]))
        {
            isAllAlpha = 0;
        }
        if(!isdigit(password[i]))
        {
            isAllNumber = 0;
        }
        
        //check if char type is continue
        if(isupper(password[i]))
        {
            if(lastCharType == CHAR_TYPE_UPPER)
            {
                continueCharTypeCount++;
            }
            lastCharType = CHAR_TYPE_UPPER;
        }
        else if(islower(password[i]))
        {
            if(lastCharType == CHAR_TYPE_LOWER)
            {
                continueCharTypeCount++;
            }
            lastCharType = CHAR_TYPE_LOWER;
        }
        else if(isdigit(password[i]))
        {
            if(lastCharType == CHAR_TYPE_NUMBER)
            {
                continueCharTypeCount++;
            }
            lastCharType = CHAR_TYPE_NUMBER;
        }
        else
        {
            lastCharType = CHAR_TYPE_OTHER;
        }
        
        //find if char is exist
        current = head;
        //從list內尋找字母，找到就count+1
        while (current != NULL)
        {
            if(current->c == toupper(password[i]) )
            {
                current->count++;
                break;
            }
            current = current->next;
        }
        //沒從list內找到字母
        if(current == NULL)
        {
            //生成一個新的node
            current = (struct charCount*)malloc(sizeof(struct charCount));
            current->next = NULL;
            current->c = toupper(password[i]);
            current->count = 1;
            
            if(head == NULL)
            {
                head = current;
            }
            else
            {
                prev->next = current;
            }
            prev = current;
        }
        
        //        map<char, int>::iterator keyDic = dictionary.find(toupper(password[i]));
        //        if(keyDic != dictionary.end())
        //        {
        //            keyDic->second++;
        //        }
        //        else
        //        {
        //            dictionary.insert(make_pair(toupper(password[i]), 1));
        //        }
        
        //check continue number or alpha
        if(i - 2 >= 0)
        {
            char first = toupper(password[i-2]);
            char second = toupper(password[i-1]);
            char third = toupper(password[i]);
            
            if((isalpha(first) && isalpha(second) && isalpha(third)) ||
               (isdigit(first) && isdigit(second) && isdigit(third)))
            {
                if((first+2 == third && second+1 == third)
                   || (first-2 == third && second-1 == third))
                {
                    continueCharCount++;
                }
            }
        }
        
    }
    
    //calculate minus score
    //all alpha or all number
    if(isAllAlpha || isAllNumber)
    {
        minusScore += strLen ;
    }
    //same char
    //    for(auto iterator = dictionary.begin() ; iterator != dictionary.end() ; iterator++)
    //    {
    //        if(iterator->second > 1)
    //        {
    //            minusScore += iterator->second * (iterator->second - 1);
    //        }
    //    }
    
    //continue char type
    //從list內計算重複字母要扣掉的分數
    current = head;
    while (current != NULL)
    {
        if(current->count > 1)
        {
            minusScore += current->count * (current->count - 1);
        }
        
        prev = current;
        current = current->next;
//        printf("prev count:%d",prev->count);
        free(prev);
    }
    
    minusScore += continueCharTypeCount * 2;
    
    minusScore += continueCharCount * 3;
    //    printf("minus score:%d\n",minusScore);
    
    return minusScore;
}

