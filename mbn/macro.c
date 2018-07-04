#include <stdio.h>

#define length(a) sizeof((a))/sizeof((a)[0])

#define round(a) (int)((a)+0.5)

#define roundArr(a) do{\
    for(i=0;i<length((a));i++)\
        (a)[i]=round((a)[i]);\
    }while(0,0);

#define printArr(a) do{\
    printf("%d",(int)(a)[0]);\
    for(i=1;i<length((a));i++)\
        printf(",%d",(int)(a)[i]);\
    }while(0,0);

int macro() {
    int i;
    float abc[] = {2.9, 3, 22.5, 22.6, 3.999999, 3.000001, 6.1, 6.2, 6.3, 6.4, 6.7, 6.8};

    printf("3=%d\n", round(2.9));
    printf("3=%d\n", round(3));
    printf("23=%d\n", round(22.5));
    printf("23=%d\n", round(22.6));
    printf("4=%d\n", round(3.999999999));
    printf("3=%d\n", round(3.00000001));
    printf("6=%d\n", round(6.1));
    printf("6=%d\n", round(6.2));
    printf("6=%d\n", round(6.3));
    printf("6=%d\n", round(6.4));
    printf("7=%d\n", round(6.7));
    printf("7=%d\n", round(6.8));
    roundArr(abc);
    printArr(abc);
    return 0;
}