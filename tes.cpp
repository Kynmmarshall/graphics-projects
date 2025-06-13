#include <graphics.h>
#include <cmath>
#include <vector>
#include <conio.h> // For kbhit()

struct Point3D { float x, y, z; };

// Convert 3D to 2D with perspective projection
void project(Point3D p, int width, int height, int& screenX, int& screenY) {
    float scale = 500.0f / (500.0f + p.z); // Perspective factor
    screenX = int(width / 2 + p.x * scale);
    screenY = int(height / 2 - p.y * scale); // Flip Y-axis
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int width = getmaxx(), height = getmaxy();

    // Define cube vertices (3D)
    std::vector<Point3D> cube = {
        {-50, -50, -50}, {50, -50, -50}, {50, 50, -50}, {-50, 50, -50}, // Front face
        {-50, -50,  50}, {50, -50,  50}, {50, 50,  50}, {-50, 50,  50}  // Back face
    };

    // Define cube faces (vertex indices for each face)
    std::vector<std::vector<int>> faces = {
        {0, 1, 2, 3}, // Front face
        {4, 5, 6, 7}, // Back face
        {0, 1, 5, 4}, // Bottom face
        {2, 3, 7, 6}, // Top face
        {0, 3, 7, 4}, // Left face
        {1, 2, 6, 5}  // Right face
    };

    // Colors for each face
    int faceColors[] = {RED, BLUE, GREEN, YELLOW, MAGENTA, CYAN};

    float angle = 0.0f;
    while (!kbhit()) {
        cleardevice();

        // Rotate cube around Y and X axes
        for (auto& p : cube) {
            // Y-axis rotation
            float x = p.x * cos(angle) - p.z * sin(angle);
            float z = p.x * sin(angle) + p.z * cos(angle);
            p.x = x;
            p.z = z;

            // X-axis rotation
            float y = p.y * cos(angle) - p.z * sin(angle);
            z = p.y * sin(angle) + p.z * cos(angle);
            p.y = y;
            p.z = z;
        }

        // Draw and fill each face
        for (int i = 0; i < faces.size(); i++) {
            int face[4][2]; // Stores projected 2D points for the face
            for (int j = 0; j < 4; j++) {
                project(cube[faces[i][j]], width, height, face[j][0], face[j][1]);
            }

            // Draw the face boundary
            setcolor(WHITE);
            for (int j = 0; j < 4; j++) {
                line(face[j][0], face[j][1], face[(j + 1) % 4][0], face[(j + 1) % 4][1]);
            }

            // Fill the face with color
            setfillstyle(SOLID_FILL, faceColors[i]);
            floodfill((face[0][0] + face[2][0]) / 2, (face[0][1] + face[2][1]) / 2, WHITE);
        }

        angle += 0.01f; // Reduced from 0.05f to 0.01f for slower rotation
        delay(100);     // Increased from 50ms to 100ms for smoother slow motion
    }

    closegraph();
    return 0;
}qq