#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "../../Source/TrafficSimulator/Renderer/Buffers/VertexBuffer.h"
#include "../../Source/TrafficSimulator/Renderer/Buffers/IndexBuffer.h"
#include "../../Source/TrafficSimulator/Renderer/Textures/TextureCube.h"
#include "../../Source/TrafficSimulator/Renderer/Shader.h"
#include "../../Source/TrafficSimulator/Camera.h"
#include "../../Source/TrafficSimulator/Util.h"

// representing the skybox
class Skybox
{
private:
	// features
	Camera* mCamera;
	TextureCube mTexCube;
	ShaderProgram mShader;

	// buffers
	VertexBuffer mVertices;
	IndexBuffer mIndices;
	GLuint vaoID;
	int mProjViewMatrix;

public:
	void Init(std::string fileName, Camera* camera)
	{
		mCamera = camera;

		// vertex position in object space
		GLfloat verticeAttrib[] =
		{
			// front
			-1.0, -1.0, -1.0,
			1.0, -1.0,  -1.0,
			1.0,  1.0,  -1.0,
			-1.0,  1.0, -1.0,

			// top
			-1.0,  1.0, -1.0,
			1.0,  1.0,  -1.0,
			1.0,  1.0,   1.0,
			-1.0,  1.0,  1.0,

			// back
			1.0, -1.0,  1.0,
			-1.0, -1.0, 1.0,
			-1.0,  1.0, 1.0,
			1.0,  1.0,  1.0,

			// bottom
			-1.0, -1.0, 1.0,
			1.0, -1.0,  1.0,
			1.0, -1.0, -1.0,
			-1.0, -1.0,-1.0,

			// left
			-1.0, -1.0,  1.0,
			-1.0, -1.0, -1.0,
			-1.0,  1.0, -1.0,
			-1.0,  1.0,  1.0,

			// right
			1.0, -1.0,  -1.0,
			1.0, -1.0,   1.0,
			1.0,  1.0,   1.0,
			1.0,  1.0,  -1.0,
		};

		GLushort elements[] = {
			// front
			0,  2,  1,
			2,  0,  3,

			// top
			4,  6,  5,
			6,  4,  7,

			// back
			8,  10, 9,
			10, 8,  11,

			// bottom
			12, 14, 13,
			14, 12, 15,

			// left
			16, 18, 17,
			18, 16, 19,

			// right
			20, 22, 21,
			22, 20, 23,
		};

		// generate vertex array object to melt all buffer objects
		glGenVertexArrays(1,&vaoID);
		glBindVertexArray(vaoID);

		// create vertex buffer object
		mVertices.Create(verticeAttrib, sizeof(verticeAttrib),  GL_STATIC_DRAW);

		// create the index buffer object
		mIndices.Create(elements, sizeof(elements), GL_STATIC_DRAW);

		// load texture
		mTexCube.LoadTGA(fileName);

		// shader data
		std::string vertex;
		std::string fragment;

		// creating shaders
		LoadTextFile("Data\\shaders\\skybox.vert", vertex);
		LoadTextFile("Data\\shaders\\skybox.frag", fragment);

		// load shaders
		mShader.CreateProgram(vertex, fragment);

		// get used uniforms
		mProjViewMatrix = glGetUniformLocation(mShader.GetID(), "projView");
	}

	void Dispose()
	{
		mTexCube.Dispose();
		mShader.Dispose();
		mVertices.Dispose();
		mIndices.Dispose();

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vaoID);
	}

	void Draw()
	{
		GLint OldCullFaceMode;
		glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
		GLint OldDepthFuncMode;
		glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);

		//get matrix uniform
		mShader.Bind();
		mVertices.Bind();
		mTexCube.Bind();

		Mat4 projView = mCamera->GetProjection() * mCamera->GetView() * Mat4::Translate(mCamera->GetWorld().GetPosition()) * Mat4::ScaleUniform(10);
		glUniformMatrix4fv(mProjViewMatrix, 1, GL_FALSE, (GLfloat*)&projView);

		//enable vertex position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		mIndices.Bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

		glDisableVertexAttribArray(0); // vertex positions

		glCullFace(OldCullFaceMode);
		glDepthFunc(OldDepthFuncMode);

		mVertices.Unbind();
		mTexCube.Unbind();
		mShader.Unbind();
	}
};

#endif
