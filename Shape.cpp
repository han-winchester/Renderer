#include "Shape.h"

float Shape::cubeVertices[] = {
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

Shape::Shape(Primitive shape, bool hasTexture)
	:
	m_Shape(shape),
	m_hasTexture(hasTexture)
{
	
	/* 
	if(cube)
	{
		SetVertices(cube);
	}
	else ...
	*/
}

float* Shape::GetVertices() const
{
    switch(m_Shape)
    {
        case Cube:
            return cubeVertices;
    }



}

int Shape::GetPositionCount() const
{
}

int Shape::GetNormalCount() const
{
}

int Shape::GetTextureCount() const
{
}

float Shape::GetStrideSize() const
{
}

float Shape::GetPositionOffsetSize() const
{
}

float Shape::GetNormalOffsetSize() const
{
}

float Shape::GetTextureOffsetSize() const
{
}

