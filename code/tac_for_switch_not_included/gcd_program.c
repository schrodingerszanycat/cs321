int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        int temp;
        temp = a % b;
        return gcd(b, temp);
    }
}

// int main(void)
// {
//     int x;
//     int y;
//     int result;
//     x = 48;
//     y = 18;
//     result = gcd(x, y);
//     return 0;
// }