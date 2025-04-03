int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1;
    int num2;
    int result;
    
    // Example input values
    num1 = 48;
    num2 = 18;
    
    result = gcd(num1, num2);
    
    return 0;
}