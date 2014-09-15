#include "Ball.h"
#include "windows.h"
#include "Texture.h"


Ball::~Ball(void)
{
}

Ball::Ball(float radius, Point center)
: Drawable(center)
{			
			this->boolX=false;
			this->boolZ=false;
			alphaX=0,alphaZ=0;
			float const R = 1./(float)(rings-1);
			float const S = 1./(float)(sectors-1);
			int r, s;
			
			vertices.resize(rings * sectors * 3);
			normals.resize(rings * sectors * 3);
			texcoords.resize(rings * sectors * 2);
			std::vector<GLfloat>::iterator v = vertices.begin();
			std::vector<GLfloat>::iterator n = normals.begin();
			std::vector<GLfloat>::iterator t = texcoords.begin();
			for(r = 0; r < rings; r++) 
				for(s = 0; s < sectors; s++) {
					float const y = sin( -PI/2 +PI * r * R );
					float const x = cos(2*PI * s * S) * sin( PI * r * R );
					float const z = sin(2*PI * s * S) * sin( PI * r * R );

					*t++ = s*S;
					*t++ = r*R;

					*v++ = x * radius;
					*v++ = y * radius;
					*v++ = z * radius;

					*n++ = x;
					*n++ = y;
					*n++ = z;
			}

			indices.resize(rings * sectors * 4);
			std::vector<GLushort>::iterator i = indices.begin();
			for(r = 0; r < rings-1; r++) 
				for(s = 0; s < sectors-1; s++) {
					*i++ = r * sectors + s;
					*i++ = r * sectors + (s+1);
					*i++ = (r+1) * sectors + (s+1);
					*i++ = (r+1) * sectors + s;
			}
			canJump=true;
}

void Ball::SetTexNr(int nr){
	this->texnr=nr;
}


void Ball::Draw()
{
		Texture tex=Texture::GetInstance();
        glMatrixMode(GL_MODELVIEW);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex.ballTex[texnr]);
        glPushMatrix();
		glTranslatef(this->center.x, this->center.y - 0.5, this->center.z);

		if(this->boolZ==true)
		{
			glRotatef(alphaZ, 0.0f, 0.0f, 1.0f);
			glRotatef(alphaX, 1.0f, 0.0f, 0.0f);
		}
		if(this->boolX==true)
		{
			glRotatef(alphaX, 1.0f, 0.0f, 0.0f);
			glRotatef(alphaZ, 0.0f, 0.0f, 1.0f);
		}

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glNormalPointer(GL_FLOAT, 0, &normals[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
        glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
        glPopMatrix();

		glDisable(GL_TEXTURE_2D);
}

void Ball::MoveX(double dx)
{
		boolZ=true;
		boolX=false;
		if(dx>0)
			alphaZ-=10;
		else
			alphaZ+=10;
}

void Ball::MoveZ(double dz)
{
		boolX=true;
		boolZ=false;
		if(dz>0)
			alphaX-=10;
		else
			alphaX+=10;
}

void Ball::Jump(bool &isJump)
{
	if(canJump)
	{
		canJump=false;
		energy=POWER;
	}
	center.y+=energy;
	if(center.y<=0)
	{
		center.y=0;
		canJump=true;
		isJump = false;
	}
	else
	{
		energy-=GRAVITY;
	}
}

