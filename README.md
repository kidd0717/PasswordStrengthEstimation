# Password Strength Estimation in C

## `PasswordStrengthEstimation 1.0` 
 
This is a C library for estimation the password strength defined by The [Password Meter](http://www.passwordmeter.com/).You can simplely input a string and 2 int pass by address and get the result.

## Compatibility

This library is design for mobile development like **iOS** or **Android**, I don't really know if it was compatible for other platform . It will be appreciated if you would just try it and tell me the compatibility.

## Installation

Simplely copy **PasswordStrength.h** and **PasswordStrength.c** into your project and include it.

## Usage

Call *getPasswordStrength(password, &score, &level);*, you can seee more detail in example project.

