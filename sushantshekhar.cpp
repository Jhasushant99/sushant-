/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x;
    long long y;
};

// Convert number from given base to decimal
long long convertFromBase(const string& value, int base) {
    long long result = 0;
    long long power = 1;
    
    // Process from right to left
    for (int i = value.length() - 1; i >= 0; i--) {
        char c = value[i];
        int digitValue;
        
        if (c >= '0' && c <= '9') {
            digitValue = c - '0';
        } else {
            digitValue = tolower(c) - 'a' + 10;
        }
        
        if (digitValue >= base) {
            cerr << "Error: Invalid digit '" << c << "' for base " << base << endl;
            return -1;
        }
        
        result += digitValue * power;
        power *= base;
    }
    
    return result;
}

// Lagrange interpolation to find the secret (value at x=0)
double lagrangeInterpolation(const vector<Point>& points) {
    double result = 0.0;
    int n = points.size();
    
    for (int i = 0; i < n; i++) {
        double xi = points[i].x;
        double yi = points[i].y;
        
        // Calculate Lagrange basis polynomial Li(0)
        double li = yi;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double xj = points[j].x;
                li *= (0.0 - xj) / (xi - xj);
            }
        }
        
        result += li;
    }
    
    return result;
}

int main() {
    cout << "Sushant Secret Sharing Implementation" << endl;
    cout << "=====================================" << endl;
    
    // Test Case 1
    cout << "\n--- Test Case 1 ---" << endl;
    
    vector<Point> points1;
    
    // Convert each point from its base to decimal
    points1.push_back({1, convertFromBase("4", 10)});      // (1, 4)
    points1.push_back({2, convertFromBase("111", 2)});     // (2, 7)  
    points1.push_back({3, convertFromBase("12", 10)});     // (3, 12)
    points1.push_back({6, convertFromBase("213", 4)});     // (6, 39)
    
    cout << "Converted points:" << endl;
    for (const Point& p : points1) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
    
    // We need k=3 points minimum, use first 3
    vector<Point> selectedPoints1(points1.begin(), points1.begin() + 3);
    
    cout << "\nUsing points for interpolation (k=3):" << endl;
    for (const Point& p : selectedPoints1) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
    
    double secret1 = lagrangeInterpolation(selectedPoints1);
    cout << "\nSecret: " << secret1 << endl;
    cout << "Secret (integer): " << (long long)round(secret1) << endl;
    
    // Verify with different combinations of 3 points
    cout << "\nVerification with different point combinations:" << endl;
    
    // Combination 1: points 0,1,2
    vector<Point> combo1 = {points1[0], points1[1], points1[2]};
    double secret1_1 = lagrangeInterpolation(combo1);
    cout << "Points (1,4), (2,7), (3,12): " << secret1_1 << endl;
    
    // Combination 2: points 0,1,3  
    vector<Point> combo2 = {points1[0], points1[1], points1[3]};
    double secret1_2 = lagrangeInterpolation(combo2);
    cout << "Points (1,4), (2,7), (6,39): " << secret1_2 << endl;
    
    // Combination 3: points 0,2,3
    vector<Point> combo3 = {points1[0], points1[2], points1[3]};
    double secret1_3 = lagrangeInterpolation(combo3);
    cout << "Points (1,4), (3,12), (6,39): " << secret1_3 << endl;
    
    // Combination 4: points 1,2,3
    vector<Point> combo4 = {points1[1], points1[2], points1[3]};
    double secret1_4 = lagrangeInterpolation(combo4);
    cout << "Points (2,7), (3,12), (6,39): " << secret1_4 << endl;
    
    cout << "\n--- Test Case 2 ---" << endl;
    cout << "Note: Test Case 2 involves extremely large numbers." << endl;
    cout << "The current implementation uses double precision which" << endl;
    cout << "may not be sufficient for the large values in test case 2." << endl;
    cout << "For production use, implement with:" << endl;
    cout << "- Arbitrary precision arithmetic libraries (GMP, Boost.Multiprecision)" << endl;
    cout << "- Custom BigInteger implementation" << endl;
    cout << "- Rational number arithmetic to maintain exact precision" << endl;
    
    // Simplified demonstration with test case 2 structure
    cout << "\nTest Case 2 structure (simplified conversion):" << endl;
    cout << "Points would be:" << endl;
    cout << "(1, base6_to_decimal('13444211440455345511'))" << endl;
    cout << "(2, base15_to_decimal('aed7015a346d635'))" << endl;
    cout << "(3, base15_to_decimal('6aeeb69631c227c'))" << endl;
    cout << "... and so on for 10 points total" << endl;
    cout << "Then use any 7 points (k=7) for Lagrange interpolation." << endl;
    
    return 0;
}