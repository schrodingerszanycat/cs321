float area(float a, float b, float c)
{
    float s;
    s = (a + b + c) / 2;
    float temp;
    temp = s * (s - a) * (s - b) * (s - c);
    return temp;
}

// int main(void)
// {
//     float side1;
//     float side2;
//     float side3;
//     float result;
//     side1 = 3.0;
//     side2 = 4.0;
//     side3 = 5.0;
//     result = area(side1, side2, side3);
//     return 0;
// }