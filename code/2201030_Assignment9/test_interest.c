/*
 * Interest Calculation Program
 * Calculates simple and compound interest
 */

 float calculateSimpleInterest(float principal, float rate, int time) {
    float interest;
    
    // Simple interest formula: I = P * R * T / 100
    interest = principal * rate * time / 100.0;
    
    return interest;
}

float calculateCompoundInterest(float principal, float rate, int time) {
    float amount;
    float interest;
    int i;
    
    // Initialize amount with principal
    amount = principal;
    
    // Calculate compound interest using iteration
    for (i = 0; i < time; i = i + 1) {
        amount = amount + (amount * rate / 100.0);
    }
    
    interest = amount - principal;
    
    return interest;
}

int main() {
    float principal;
    float rate;
    int time;
    float simpleInterest;
    float compoundInterest;
    
    // Example input values
    principal = 1000.0;
    rate = 5.0;
    time = 3;
    
    simpleInterest = calculateSimpleInterest(principal, rate, time);
    compoundInterest = calculateCompoundInterest(principal, rate, time);
    
    return 0;
}