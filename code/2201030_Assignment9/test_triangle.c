float calculateAreaWithBaseHeight(float base, float height) {
    float area;
    
    area = 0.5 * base * height;
    
    return area;
}

float calculateAreaWithSides(float a, float b, float c) {
    float s;
    float area;
    
    // Calculate semi-perimeter
    s = (a + b + c) / 2.0;
    
    area = s * (s - a) * (s - b) * (s - c);
    
    float x = area / 2.0;
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        x = (x + area / x) / 2.0;
    }
    
    area = x;
    
    return area;
}

int isValidTriangle(float a, float b, float c) {
    // Triangle inequality theorem
    if (a + b > c && b + c > a && a + c > b) {
        return 1; // Valid triangle
    } else {
        return 0; // Invalid triangle
    }
}

int main() {
    float base;
    float height;
    float side1;
    float side2;
    float side3;
    float area1;
    float area2;
    int valid;
    
    // Example input values
    base = 5.0;
    height = 4.0;
    side1 = 3.0;
    side2 = 4.0;
    side3 = 5.0;
    
    area1 = calculateAreaWithBaseHeight(base, height);
    
    valid = isValidTriangle(side1, side2, side3);
    
    if (valid) {
        area2 = calculateAreaWithSides(side1, side2, side3);
    }
    
    return 0;
}