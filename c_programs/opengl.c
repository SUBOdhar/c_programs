#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to check if a point (x, y) lies on the circumference of the circle
int isOnCircle(int x, int y, int h, int k, int r)
{
    int dx = x - h;
    int dy = y - k;
    int distanceSquared = dx * dx + dy * dy;
    int radiusSquared = r * r;

    // Check if the distance to the center is approximately equal to the radius squared
    return abs(distanceSquared - radiusSquared) <= r;
}

// Function to draw a hollow circle with center (h, k) and radius r
void drawHollowCircle(int h, int k, int r)
{
    // Loop through a bounding box around the circle
    for (int y = k - r; y <= k + r; y++)
    {
        for (int x = h - r; x <= h + r; x++)
        {
            if (isOnCircle(x, y, h, k, r))
            {
                printf("*"); // Print '*' for points on the circumference of the circle
            }
            else
            {
                printf(" "); // Print ' ' for points inside or outside the circle
            }
        }
        printf("\n"); // Move to the next line after each row
    }
}

int main()
{
    int centerX = 5; // x-coordinate of the center of the circle
    int centerY = 5; // y-coordinate of the center of the circle
    int radius = 3;  // radius of the circle

    drawHollowCircle(centerX, centerY, radius);

    return 0;
}
