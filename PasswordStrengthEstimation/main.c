//
//  main.c
//  PasswordStrengthEstimation
//
//  Created by MITAKE on 2014/10/3.
//  Copyright (c) 2014年 mitake. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "passwordStrength.h"

int main(int argc, const char * argv[])
{
    while (1)
    {
        
    // get password
        printf("password string:");
        char password[20];
        scanf("%s",password);
        
        int score ;
        int level;
        getPasswordStrength(password, &score, &level);
        
        
        printf("score:%d\n",score);
        printf("strength:%d\n",level);
        
    }
    return 0;
}
