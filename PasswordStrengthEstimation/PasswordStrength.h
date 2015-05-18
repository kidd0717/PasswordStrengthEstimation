//
//  passwordStrength.h
//  PasswordStrengthEstimation
//
//  Created by MMY on 2014/10/6.
//  Copyright (c) 2014年 MMY. All rights reserved.
//

#include <stdio.h>

#define PASSWORD_STRENGTH_SHORT "這密碼太短了！"
#define PASSWORD_STRENGTH_LOW "這密碼太簡單了！"
#define PASSWORD_STRENGTH_MID "請再加強密碼複雜度"
#define PASSWORD_STRENGTH_HIGH "這個是夠安全的密碼"
#define PASSWORD_STRENGTH_VERY_HIGH "天衣無縫的密碼"

void getPasswordStrength(const char *password, int *score , char** strength);