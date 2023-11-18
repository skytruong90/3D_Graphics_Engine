#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    GLFWwindow* window;

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "3D Graphics Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window\n";
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle
        glBegin(GL_TRIANGLES);
        glVertex3f(-0.6f, -0.4f, 0.0f);
        glVertex3f(0.6f, -0.4f, 0.0f);
        glVertex3f(0.0f, 0.6f, 0.0f);
        glEnd();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
