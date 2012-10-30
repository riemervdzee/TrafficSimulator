#ifndef _VERTEXATTRIBBUFFER_H_
#define _VERTEXATTRIBBUFFER_H_

#include "GL/glew.h"

// representing a openGL buffer object
class VertexBuffer
{
public:
	VertexBuffer(): mID(0){}

	// create the buffer
	template <typename T>
	void Create(T *buffer, unsigned int size, GLenum usage)
	{
		// generate buffer
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);

		// fill with data
		glBufferData(GL_ARRAY_BUFFER, size, buffer, usage);

		// unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// create an empty buffer
	void Create(unsigned int size, GLenum usage)
	{
		// generate buffer
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);

		// create a empty buffer of the size specified
		glBufferData(GL_ARRAY_BUFFER, size, 0, usage);

		// unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	template <typename T>
	void SubData(T buffer, unsigned int size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mID);

		glBufferSubData(GL_ARRAY_BUFFER, 0, size, buffer);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SetAttribPointer(unsigned int position, unsigned int attribSize, GLenum attribMemType, unsigned int stride, void* offset)
	{
		glVertexAttribPointer(position, attribSize, attribMemType, GL_FALSE, stride, offset);
	}

	// dispose of the buffer
	void Dispose()
	{
		// unbind buffer and delete
		if(mID != 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDeleteBuffers(1, &mID);
		}
	}

	// GETTERS & SETTERS
	void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, mID); }
	void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	unsigned int GetID() const { return mID; }

private:
	GLuint mID;
};

#endif
