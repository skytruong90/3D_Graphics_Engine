#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Initialize GLFW library
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "3D Graphics Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window\n";
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Define the vertex shader source code
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n" // Position variable of type vec3
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n" // Set the position of the vertex
    "}\0";

    // Define the fragment shader source code
    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n" // Output color variable
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // Set the color to orange
    "}\0";

    // Compile the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Compile the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create a shader program and attach the shaders to it
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shader objects once linked
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Define the vertices of the triangle
    float vertices[] = {
        -0.6f, -0.4f, 0.0f, // Vertex 1 (X, Y, Z)
         0.6f, -0.4f, 0.0f, // Vertex 2 (X, Y, Z)
         0.0f,  0.6f, 0.0f  // Vertex 3 (X, Y, Z)
    };

    // Generate a Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO and then bind and set VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Render the background color
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program and bind the VAO
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Deallocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
