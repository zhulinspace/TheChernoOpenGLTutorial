#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include "GLErrorMessage.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

//#include "Camera.h"
//#include<DbgHelp.h>

const unsigned int ScreenWidth = 1280;
const unsigned int ScreenHeight = 960;
//float lastX = ScreenWidth / 2.0f;
//float lastY = ScreenHeight / 2.0f;
//bool firstMouse = true;
//void mouse_callback(GLFWwindow *window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//	lastX = xpos;
//	lastY = ypos;
//
//
//}

int main(void)
{

	/*FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
*/

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	
	window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew init failed!" << std::endl;
	}


	//configure global opengl state
	glEnable(GL_DEPTH_TEST);
	{

		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};

		

		VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices),36);
		VertexBufferLayout layout;
		layout.Push<float>(3);//position
		layout.Push<float>(3);//normal
		layout.Push<float>(2);//texturecoord
		va.AddBuffer(vb, layout);

		VertexArray lightVa;
		VertexBufferLayout lightLayout(8*sizeof(float));
		lightLayout.Push<float>(3);
		lightVa.AddBuffer(vb, lightLayout);

		glm::mat4 proj = glm::mat4(1.0f);

	
		proj = glm::perspective(glm::radians(45.0f), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);


		Shader lightShader("res/shaders/light.shader");
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		//transformation
		shader.SetUniformMat4f("u_Projection", proj);
		//textures
		Texture diffuseMap("res/textures/container2.png");
		Texture specularMap("res/textures/container2_specular.png");
		diffuseMap.Bind(0);
		specularMap.Bind(1);
		shader.SetUniform1i("u_material.diffuse", 0);
		shader.SetUniform1i("u_material.specular", 1);

		/*Texture texture("res/textures/wall.jpg");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);*/

		//unbind
		va.Unbind();
		lightVa.Unbind();
		vb.Unbind();
		shader.Unbind();
		lightShader.Unbind();

		Renderer renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		const char* glsl_version = "#version 130";
		ImGui_ImplOpenGL3_Init(glsl_version);
		ImGui::StyleColorsDark();

		float angel = 0;
		glm::vec3 translation(0.0f, 0.0f, 0.0f);
		glm::vec3 eye(0.0f, 0.0f, 3.0f);
		glm::vec3 center(0.0f, 0.0f, 0.0f);
		glm::vec3 up(0.0f, 1.0f, 0.0f);

		//≤‚ ‘ 
		glm::vec4 test(-0.5f, -0.5f, -0.5f, 1);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
		
			model = glm::rotate(model, glm::radians(-angel), glm::vec3(0.5f, 1.0f, 0.0f));
			view = glm::lookAt(eye, center, up);

			//view = glm::translate(view, translation);
			

			
			glm::vec4 m = model * test;
		
			glm::vec4 v = view * m;
			
			glm::vec4 p = proj * v;
		
		
		



			glm::vec3 lightPos(0.8f, 0.2f, 2.0f);
			glm::vec3 ViewPos(0.0f,0.0f,3.0f);

			{
				
				shader.Bind();
				shader.SetUniformVec3f("u_light.position",lightPos);
				shader.SetUniformVec3f("u_viewPos", ViewPos);
				//light properties
				shader.SetUniformVec3f("u_light.ambient", 0.2f, 0.2f, 0.2f);
				shader.SetUniformVec3f("u_light.diffuse", 0.5f, 0.5f, 0.5f);
				shader.SetUniformVec3f("u_light.specular", 1.0f, 1.0f, 1.0f);
				//material 
				shader.SetUniform1f("u_material.shininess", 64.0f);
				shader.SetUniformMat4f("u_Model", model);
				shader.SetUniformMat4f("u_View", view);
				renderer.Draw(va, vb, shader);
			}

			/*{
				lightShader.Bind();
				lightShader.SetUniformMat4f("projection", proj);
				lightShader.SetUniformMat4f("view", view);
				model = glm::mat4(1.0f);
				model = glm::translate(model, lightPos);
				model = glm::scale(model, glm::vec3(0.2f));
				lightShader.SetUniformMat4f("model", model);
				renderer.Draw(lightVa, vb, lightShader);
			}*/

			{
				ImGui::SliderFloat("angel", &angel, -180.0f, 180.0f);      
				ImGui::SliderFloat3("translation", &translation.x,-2.0f,2.0f);
				ImGui::Text("origin test vector: %s",glm::to_string(test).c_str());
				ImGui::Text("model matrix: \n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f",   model[0][0], model[1][0], model[2][0], model[3][0], 
																																							model[0][1], model[1][1], model[2][1], model[3][1], 
																																							model[0][2], model[1][2], model[2][2], model[3][2],
																																							model[0][3], model[1][3], model[2][3], model[3][3] );
				ImGui::Text("after model matrix: %s", glm::to_string(m).c_str());
				ImGui::Text("view matrix: \n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f",	    view[0][0], view[1][0], view[2][0], view[3][0],
																																							view[0][1], view[1][1], view[2][1], view[3][1],
																																							view[0][2], view[1][2], view[2][2], view[3][2],
																																							view[0][3], view[1][3], view[2][3], view[3][3]);

				ImGui::Text("after view matrix: %s", glm::to_string(v).c_str());
				ImGui::Text("projection matrix: \n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f",	    proj[0][0], proj[1][0], proj[2][0],proj[3][0],
																																									proj[0][1], proj[1][1], proj[2][1],proj[3][1],
																																									proj[0][2], proj[1][2], proj[2][2],proj[3][2],
																																									proj[0][3], proj[1][3], proj[2][3],proj[3][3]);
				ImGui::Text("after projection matrix: %s", glm::to_string(p).c_str());
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
