float interest(float p, float r, float t)
{
    float si;
    si = (p * r * t) / 100;
    return si;
}

// int main(void)
// {
//     float principal;
//     float rate;
//     float time;
//     float result;
//     principal = 1000.0;
//     rate = 5.0;
//     time = 2.0;
//     result = interest(principal, rate, time);
//     return 0;
//}