#include <stdio.h>
#define MAX_NUM 100

int main(int argc, char *argv[])
{
    signed long powers[MAX_NUM], values[MAX_NUM], currentPower, number, ten;
    int i, j, count;
    number = 7;
    // Khởi tạo mảng powers với giá trị 0
    for (i = 0; i < MAX_NUM; i++)
        powers[i] = 0;

    // Khởi tạo biến đếm
    count = 0;
    ten = 1;

    // Tìm lũy thừa của các số
    for (currentPower = 1; currentPower < MAX_NUM; currentPower++)
    {
        values[currentPower] = ten;

        // Kiểm tra nếu lũy thừa hiện tại đã được gán cho một số khác
        // Nếu chưa, gán lũy thừa hiện tại cho vị trí tương ứng trong mảng powers
        for (j = 0; j < MAX_NUM; j++)
            if (powers[j] && !powers[(j + ten) % number] && powers[j] != currentPower)
                powers[(j + ten) % number] = currentPower;

        if (!powers[ten])
            powers[ten] = currentPower;
        ten = (10 * ten) % number;
        if (powers[0])
            break;
    }

    currentPower = number;
    printf("%ld\tdivides\t", currentPower);
    if (powers[0])
    {
        while (currentPower)
        {   
            count--;
            while (count > powers[currentPower % number] - 1){
                count--;
                printf("0");
            }
            count = powers[currentPower % number] - 1;
            printf("1");
            currentPower = (number + currentPower - values[powers[currentPower % number]]) % number;
        }
        while (count-- > 0)
            printf("0");
    }
}