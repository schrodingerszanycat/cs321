

int main() {
    int i;
    int j;
    int sum;
    int choice;
    
    
    sum = 0;
    for(i = 1; i <= 10; i = i + 1) {
        sum = sum + i;
    }
    
    choice = 1;
    switch(choice) {
        case 1:
            sum = sum + 1;
            break;
        case 2:
            sum = sum + 2;
            break;
        case 3:
            sum = sum + 3;
            break;
        default:
            sum = sum + 4;
            break;
    }
    
    return sum;
}