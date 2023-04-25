#include "stdio.h"
#include "math.h"
#include "./random.h"


//generates a pseudo-random number, using some assembly, because why not lol
float random() {
    float x = 1;
    __asm__(".intel_syntax noprefix"); // i'm working with intel syntax
    __asm__ __volatile__(
        "rdtsc\n"
        "mov ebx, eax\n" // Get's ticks and move them to ebx
        "rdtsc\n"
        "mov ecx, 0\n" // Get's ticks and then resets ecx and edx
        "mov edx, 0\n" // Did this 'cause they will be used to count how many times the loop runned
        "r:\n" // Executes a bunch of operations to pretend it's generating a random number
        "   xor eax, ebx\n"
        "   rdtsc\n"
        "   add eax, ebx\n"
        "   add ecx, 1\n"
        "   xor ebx, ecx\n" 
        "   cmp ecx, 255\n" // Doing this to see if it runned enough times
        "   jae addt\n"
        "   jmp r\n"
        "addt:\n" // This is used to check if it already did enough loops
        "   mov ecx, 0\n"
        "   add edx, 1\n"
        "   cmp edx, 255\n"
        "   jb r\n" // if no go to r, if yes store the number in "x"
        "   mov %0, eax\n"
        : "=m" (x)
        :
        :"eax", "ebx", "ecx","edx"
    );
    return x;
}

// Generates a, probably, decimal pseudo-random number
double drandom() {
    float r1 = random();
    // Doing this to mess with the amount of ticks
    printf("");
    sqrt(cos(3));
    int i = 0;
    while(i < 100) i++;
    float r3 = random();
    printf("");
    i = 0;
    while(i < 100) i++;
    float r2 = random();
    // Some random operations to pretend it's a random number, i could do way more things to help with this
    // But that's the most efficient i've tested so far
    // Don't use it on any serious project please
    return ((sqrt((r1/r2))*r3)*cos(r2))/r1;
}

// It was a fun little project
int main() {
    // Example of use: drandom()
    float i2 = drandom();
    printf("%f\n", i2);
    // Example of use: random()
    i2 = random();
    printf("%f\n", i2);
    return 0;
}