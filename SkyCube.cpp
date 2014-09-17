#include "SkyCube.h"
#include "Texture.h"

SkyCube::SkyCube(void):Drawable(Point())
{
}

void SkyCube::Draw()
{	
	Texture tex=Texture::GetInstance();
	glEnable(GL_TEXTURE_2D);

	//Front
	glBindTexture(GL_TEXTURE_2D,tex.skyCube[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( center.x + DIST_FROM_SKY + 2, -DIST_FROM_SKY/4, center.z - DIST_FROM_SKY );
	glTexCoord2f(1, 0); glVertex3f( center.x - DIST_FROM_SKY- 2, -DIST_FROM_SKY/4, center.z - DIST_FROM_SKY );
	glTexCoord2f(1, 1); glVertex3f( center.x - DIST_FROM_SKY- 2, DIST_FROM_SKY/2, center.z - DIST_FROM_SKY );
	glTexCoord2f(0, 1); glVertex3f( center.x + DIST_FROM_SKY+ 2, DIST_FROM_SKY/2, center.z - DIST_FROM_SKY );
	glEnd();

	//Back
	glBindTexture(GL_TEXTURE_2D,tex.skyCube[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( center.x - DIST_FROM_SKY - 2, -DIST_FROM_SKY/4, center.z + DIST_FROM_SKY );
	glTexCoord2f(1, 0); glVertex3f( center.x + DIST_FROM_SKY +2, -DIST_FROM_SKY/4, center.z + DIST_FROM_SKY );
	glTexCoord2f(1, 1); glVertex3f( center.x + DIST_FROM_SKY +2, DIST_FROM_SKY/2, center.z + DIST_FROM_SKY );
	glTexCoord2f(0, 1); glVertex3f( center.x - DIST_FROM_SKY -2, DIST_FROM_SKY/2, center.z + DIST_FROM_SKY );
	glEnd();

	//Left
	glBindTexture(GL_TEXTURE_2D,tex.skyCube[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( center.x - DIST_FROM_SKY, -DIST_FROM_SKY/4, center.z - DIST_FROM_SKY -2);
	glTexCoord2f(1, 0); glVertex3f( center.x - DIST_FROM_SKY, -DIST_FROM_SKY/4, center.z + DIST_FROM_SKY +2);
	glTexCoord2f(1, 1); glVertex3f( center.x - DIST_FROM_SKY, DIST_FROM_SKY/2, center.z + DIST_FROM_SKY +2);
	glTexCoord2f(0, 1); glVertex3f( center.x - DIST_FROM_SKY, DIST_FROM_SKY/2, center.z - DIST_FROM_SKY -2);
	glEnd();

	//Right
	glBindTexture(GL_TEXTURE_2D,tex.skyCube[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( center.x + DIST_FROM_SKY, -DIST_FROM_SKY/4, center.z + DIST_FROM_SKY +2);
	glTexCoord2f(1, 0); glVertex3f( center.x + DIST_FROM_SKY, -DIST_FROM_SKY/4, center.z - DIST_FROM_SKY -2);
	glTexCoord2f(1, 1); glVertex3f( center.x + DIST_FROM_SKY, DIST_FROM_SKY/2, center.z - DIST_FROM_SKY -2);
	glTexCoord2f(0, 1); glVertex3f( center.x + DIST_FROM_SKY, DIST_FROM_SKY/2, center.z + DIST_FROM_SKY +2);
	glEnd();

	//Top
	glBindTexture(GL_TEXTURE_2D,tex.skyCube[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f( center.x - DIST_FROM_SKY, DIST_FROM_SKY/2, center.z - DIST_FROM_SKY );
	glTexCoord2f(0, 0); glVertex3f( center.x - DIST_FROM_SKY, DIST_FROM_SKY/2,  DIST_FROM_SKY );
	glTexCoord2f(1, 0); glVertex3f( center.x + DIST_FROM_SKY, DIST_FROM_SKY/2,  DIST_FROM_SKY );
	glTexCoord2f(1, 1); glVertex3f( center.x + DIST_FROM_SKY, DIST_FROM_SKY/2, center.z - DIST_FROM_SKY);
	glEnd();

	//Bottom
	glBindTexture(GL_TEXTURE_2D,tex.skyCube[5]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( -SIZE_OF_GROUND, -0.1, -SIZE_OF_GROUND );
		glTexCoord2f(0, GROUND_TEXTURE_MULTIPLIER); glVertex3f( -SIZE_OF_GROUND, -0.1,  SIZE_OF_GROUND);
		glTexCoord2f(GROUND_TEXTURE_MULTIPLIER, GROUND_TEXTURE_MULTIPLIER); glVertex3f(  SIZE_OF_GROUND, -0.1,  SIZE_OF_GROUND );
		glTexCoord2f(GROUND_TEXTURE_MULTIPLIER, 0); glVertex3f( SIZE_OF_GROUND, -0.1, -SIZE_OF_GROUND);
	glEnd();
}
void SkyCube::SetPoz(Point p)
{
	center.x=p.x;
	center.z=p.z;
}
