#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

#include "GL/glew.h"

class IndexBuffer
{
public:
	IndexBuffer(): mID(0){}

	// create the buffer
	void Create(GLushort *indices, unsigned int size, GLenum usage)
	{
		// generate buffer
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);

		// fill with data
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * size, indices, usage);

		// unbind
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// dispose of the buffer
	void Dispose()
	{
		if(mID != 0)
		{
			// unbind buffer and delete
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glDeleteBuffers(1, &mID);
		}
	}
	// GETTERS & SETTERS
	void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID); }
	void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	unsigned int GetID() const { return mID; }
private:
	GLuint mID;
};

#endif
