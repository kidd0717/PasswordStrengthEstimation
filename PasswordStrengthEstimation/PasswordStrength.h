//
//  passwordStrength.h
//  PasswordStrengthEstimation
//
//  Created by MMY on 2014/10/6.
//  Copyright (c) 2014年 MMY. All rights reserved.
//

#include <stdio.h>

#define PASSWORD_STRENGTH_SHORT 0
#define PASSWORD_STRENGTH_LOW 1
#define PASSWORD_STRENGTH_MID 2
#define PASSWORD_STRENGTH_HIGH 3
#define PASSWORD_STRENGTH_VERY_HIGH 4

void getPasswordStrength(const char *password, int *score , int *strength);