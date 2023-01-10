#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include <filesystem>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Lights/SpotLight.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void UpdateLights(SpotLight flashLight, DirectionalLight directionalLight, GLFWwindow* window);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

// screen settings
const unsigned int SCR_WIDTH{800};
const unsigned int SCR_HEIGHT{600};

// camera settings
Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};
float lastX{SCR_WIDTH / 2.0f};
float lastY{SCR_HEIGHT / 2.0f};
bool firstMouse{true};

// timing
float deltaTime{0.0f}; // time between current and last frame
float lastFrame{0.0f}; // time of last frame

bool isBlackLight{false};
bool enableFlashLight{true};
bool enableDirectionalLight{true};


int main()
{
    // -------------------------------------------------------------------------------------------
    // glfw: initialize and configure
    glfwInit();
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // -------------------------------------------------------------------------------------------
    GLFWwindow* window{glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Renderer", NULL, NULL)};
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // -------------------------------------------------------------------------------------------
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;




    // -------------------------------------------------------------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // -------------------------------------------------------------------------------------------
    glEnable(GL_DEPTH_TEST);

    // -------------------------------------------------------------------------------------------
    // build and compile our shaders
    Shader cubeShader{"Shaders/CubeShader.vert", "Shaders/CubeShader.frag"};
    Shader lightShader{"Shaders/LightShader.vert", "Shaders/LightShader.frag"};
    Shader modelShader{"Shaders/ModelShader.vert", "Shaders/ModelShader.frag"};

    // -------------------------------------------------------------------------------------------
    // load models
    Model flashlightModel{"../Assets/flashlight/1.obj"};
    Model ourModel{"../Assets/backpack/backpack.obj"};
    

    // -------------------------------------------------------------------------------------------
    // set up vertex data (and buffers) and configure vertex attributes
    float vertices[] = {
    // positions            // tex coords   // normals
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,     0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f,     0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f,     0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,    -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,    -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,    -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 1.0f,     0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,     0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,     0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,     0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f,  1.0f,  0.0f
    };

    /*
    Shape square{primitive type = square, textured? = true}
    square.GetVertices();
    square.GetPositionCount();
    square.GetStrideCount();
    square.GetOffset();
    */

    unsigned int VBO{}, VAO{};
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    //                    (Attrib location in shader, Number of, Type, GL_FALSE, stride, offset)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO{};
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // -------------------------------------------------------------------------------------------
    // load and create a texture 
    unsigned int diffuseMap{loadTexture("../Assets/Textures/Diffuse/container.jpg")};

    unsigned int specularmap{loadTexture("../Assets/Textures/Specular/containerspecular.png")};

    unsigned int emissionmap{loadTexture("../Assets/Textures/Emission/matrix.jpg")};

    // -------------------------------------------------------------------------------------------
    // tell opengl for each sampler to which texture unit it belongs to
    cubeShader.use();
    cubeShader.setInt("material.diffuse", 0);
    cubeShader.setInt("material.specular", 1);
    cubeShader.setInt("material.emission", 2);
   
    // -------------------------------------------------------------------------------------------
    // Initialize objects
    // rotating wooden box cubes
    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // -------------------------------------------------------------------------------------------
    // Initialize Light objects
    // NOTE: If adding more lights remember to increase the number in the cubeShader
    
    // The flashlight the player controls
    SpotLight flashLight
    {
        camera.Position, 
        camera.Front, 
        glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3(1.0f, 1.0f, 1.0f), 
        glm::vec3(1.0f, 1.0f, 1.0f), 
        1.0f, 
        0.09f, 
        0.032f, 
        glm::cos(glm::radians(5.5f)), 
        glm::cos(glm::radians(10.5f))
    };
    
    // Directional Lights
    DirectionalLight directionalLight{glm::vec3(-0.2f, -1.0f, -0.3f),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.05f, 0.05f, 0.05),glm::vec3(0.2f, 0.2f, 0.2f)};

    // Create PointLights
    PointLight p1{glm::vec3(0.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f};
    PointLight p2{glm::vec3(0.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f};
    PointLight p3(glm::vec3(0.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    PointLight p4{glm::vec3(0.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f};

    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

    // -------------------------------------------------------------------------------------------
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("SceneWindow");
        ImGui::BeginChild("SceneRender");
        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImVec2 wsize = ImGui::GetWindowSize();
        ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
        ImGui::End();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }


        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // -------------------------------------------------------------------------------------------
        // input
        processInput(window);

        // -------------------------------------------------------------------------------------------
        // render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



        // create projection
        glm::mat4 projection{glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f)};

        // camera/view transformation
        glm::mat4 view{camera.GetViewMatrix()};

        // create transformations
        glm::mat4 model{glm::mat4(1.0f)}; // make sure to initialize matrix to identity matrix first
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f)); // Rotates the front most cube in the scene

        // -------------------------------------------------------------------------------------------
        // render model
        // activate model shader
        modelShader.use();
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", view);

        // render the backpack model
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        modelShader.setMat4("model", model);
        ourModel.Draw(modelShader);

        // flashlight model
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(camera.Position.x+0.3f,camera.Position.y-0.4f,camera.Position.z-0.3f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f,0.0f,0.0f));
        model = glm::rotate(model, glm::radians(2.0f), glm::vec3(0.0f,0.0f,1.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	
        modelShader.setMat4("model", model);
        flashlightModel.Draw(modelShader);



         // render boxes
        // -------------------------------------------------------------------------------------------
        // activate boxes shader
        cubeShader.use();

        cubeShader.setVec3("viewPos", camera.Position);
        cubeShader.setFloat("material.shininess", 32.0f);
        cubeShader.setFloat("time", sin(glfwGetTime()));
        cubeShader.setBool("isBlackLight", isBlackLight);

        // -------------------------------------------------------------------------------------------
        // render lights
        // Rainbow effect
        glm::vec3 lightColor{};
        lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
        lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
        lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
        glm::vec3 diffuseColor{lightColor * glm::vec3(0.5f)};
        glm::vec3 ambientColor{diffuseColor * glm::vec3(0.2f)};

        // -------------------------------------------------------------------------------------------
        // Render Point Lights
        
        // Also used to render the cubes to visualize the light points as well
        glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f + sin(glfwGetTime()) * 2.0f,  0.2f + sin(glfwGetTime() / 2.0f) * 1.0f,  2.0f),
            glm::vec3(2.3f + sin(glfwGetTime()) * 2.0f, -3.3f + sin(glfwGetTime() / 2.0f) * 1.0f, -4.0f),
            glm::vec3(-4.0f + sin(glfwGetTime()) * 2.0f,  2.0f + sin(glfwGetTime() / 2.0f) * 1.0f, -12.0f),
            glm::vec3(0.0f + sin(glfwGetTime()) * 2.0f,  0.0f + sin(glfwGetTime() / 2.0f) * 1.0f, -3.0f)
        };

        // change point light positions every frame
        p1.SetPosition(pointLightPositions[0]);
        p2.SetPosition(pointLightPositions[1]);
        p3.SetPosition(pointLightPositions[2]);
        p4.SetPosition(pointLightPositions[3]);

        for(const auto& pointLight : PointLight::pointLights)
        {
            pointLight.Draw(cubeShader);
        }

        // -------------------------------------------------------------------------------------------
        // Render Spot Lights
        for(const auto& spotLight : SpotLight::spotLights)
        {
            spotLight.Draw(cubeShader);
        }

        // -------------------------------------------------------------------------------------------
        // Render Directional Lights
        for(const auto& directionalLight : DirectionalLight::directionalLights)
        {
            directionalLight.Draw(cubeShader);
        }
        
        // -------------------------------------------------------------------------------------------
        

        UpdateLights(flashLight, directionalLight, window); // Move to ProcessInput???

       
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        cubeShader.setMat4("model", model);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularmap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, emissionmap);

        // render boxes now
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36); // Only render 1 box in scene - comment out the for loop below
        
        // renders multiple rotating boxes
        for (unsigned int i{0}; i < 10; i++)
        {
            glm::mat4 model{glm::mat4(1.0f)};
            model = glm::translate(model, cubePositions[i]);
            float angle{20.0f * i};
            if(i%3==0)
                model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
            else
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            cubeShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // render light
        // ------------------------------
        // activate light cube shader
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);

        glBindVertexArray(lightVAO);

        // renders multiple translating white cubes to visualize the point lights
        for (auto i{0}; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        
    }

    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void UpdateLights(SpotLight flashLight, DirectionalLight directionalLight, GLFWwindow* window)
{
    // Make SpotLight like a flashlight; Always in front of player
    flashLight.SetPosition(camera.Position);
    flashLight.SetDirection(camera.Front);

    // enable/disable spotlight
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        enableFlashLight = !enableFlashLight;
        flashLight.EnableSpotLight(enableFlashLight);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        isBlackLight = !isBlackLight;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        enableDirectionalLight = !enableDirectionalLight;
        directionalLight.EnableDirectionalLight(enableDirectionalLight);
    }
        
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos{static_cast<float>(xposIn)};
    float ypos{static_cast<float>(yposIn)};

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file (Sourced from LearnOpenGL, created by Joey de Vries)
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID{};
    glGenTextures(1, &textureID);

    int width{}, height{}, nrComponents{};
    unsigned char* data{stbi_load(path, &width, &height, &nrComponents, 0)};
    if (data)
    {
        GLenum format{};
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}