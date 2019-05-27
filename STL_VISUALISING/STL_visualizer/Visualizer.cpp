#include "stdafx.h"
#include "Visualizer.h"

namespace stl
{
    namespace visualization
    {
        inline void Visualizer::LoadMVP()
        {
            // Compute the MVP matrix from keyboard and mouse input
            controls.computeMatricesFromInputs(window);
            glm::mat4 ProjectionMatrix = controls.getProjectionMatrix();
            glm::mat4 ViewMatrix = controls.getViewMatrix();
            glm::mat4 ModelMatrix = glm::mat4(1.0);
            glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

            // in the "MVP" uniform
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
            glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
            glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        }

        inline void Visualizer::initGLFW()
        {
            // Initialise GLFW
            if (!glfwInit())
            {
                throw std::exception("Failed to initialize GLFW");
            }

            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // Open a window and create its OpenGL context
            window = glfwCreateWindow(resolution.x, resolution.y, "Stl visualizer", NULL, NULL);
            if (window == NULL) {
                glfwTerminate();
                throw std::exception("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
            }
            glfwMakeContextCurrent(window);
        }

        inline void Visualizer::cleanup()
        {
            // Cleanup VBO and shader
            glDeleteBuffers(1, &vertexbuffer);
            glDeleteBuffers(1, &normalbuffer);
            glDeleteProgram(programID);
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        inline void Visualizer::initGLEW()
        {
            // Initialize GLEW
            glewExperimental = true; // Needed for core profile
            if (glewInit() != GLEW_OK) {
                glfwTerminate();
                throw std::exception("Failed to initialize GLEW\n");
            }
        }

        inline void Visualizer::setupEnv()
        {
            // Ensure we can capture the escape key being pressed below
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
            // Hide the mouse and enable unlimited mouvement
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            // Set the mouse at the center of the screen
            glfwPollEvents();
            glfwSetCursorPos(window, resolution.x / 2, resolution.y / 2);

            glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

            // Enable depth test
            glEnable(GL_DEPTH_TEST);
            // Accept fragment if it closer to the camera than the former one
            glDepthFunc(GL_LESS);

            // Cull triangles which normal is not towards the camera
            glEnable(GL_CULL_FACE);
        }

        int Visualizer::run()
        {
            initGLFW();
            ScopeGuard guard{ glfwTerminate };

            initGLEW();

            setupEnv();

            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            // Create and compile our GLSL program from the shaders
            programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");

            // Get a handle for our "MVP" uniform
            MatrixID = glGetUniformLocation(programID, "MVP");
            ViewMatrixID = glGetUniformLocation(programID, "V");
            ModelMatrixID = glGetUniformLocation(programID, "M");

            vertexbuffer = genericGenBuffer(vertices);
            normalbuffer = genericGenBuffer(normals);

            // Get a handle for our "LightPosition" uniform
            glUseProgram(programID);
            GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

            do
            {
                // Clear the screen
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // Use our shader
                glUseProgram(programID);

                LoadMVP();

                glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

                // 1rst attribute buffer : vertices
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(
                    0,                  // attribute
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );

                // 3rd attribute buffer : normals
                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
                glVertexAttribPointer(
                    1,                                // attribute
                    3,                                // size
                    GL_FLOAT,                         // type
                    GL_FALSE,                         // normalized?
                    0,                                // stride
                    (void*)0                          // array buffer offset
                );

                // Draw the triangles !
                glDrawArrays(GL_TRIANGLES, 0, vertices.size());

                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);

                // Swap buffers
                glfwSwapBuffers(window);
                glfwPollEvents();

            } // Check if the ESC key was pressed or the window was closed
            while (
                glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
                glfwWindowShouldClose(window) == 0);

            cleanup();
            return 0;
        }
    }
}
