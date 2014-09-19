#include "Texture.h"


Texture::Texture(void)
{
	double tWidth, tHeight;
	char* buffer ;
	
	//ball textures loading
	buffer = esLoadTGA("Texture/football.tga",&tWidth,&tHeight);
	glGenTextures ( 1, ballTex);
	glBindTexture ( GL_TEXTURE_2D, ballTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	//tshirt texture
	buffer = esLoadTGA("Texture/Human/tshirt.tga",&tWidth,&tHeight);
	glGenTextures ( 1, tshirtTex);
	glBindTexture ( GL_TEXTURE_2D, tshirtTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//backtshirt texture
	buffer = esLoadTGA("Texture/Human/backtshirt.tga",&tWidth,&tHeight);
	glGenTextures ( 1, tshirtTex+1);
	glBindTexture ( GL_TEXTURE_2D,tshirtTex[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//jeans texture
	buffer = esLoadTGA("Texture/Human/jeans.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &jeansTex);
	glBindTexture ( GL_TEXTURE_2D, jeansTex);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//skin texture
	buffer = esLoadTGA("Texture/Human/skin.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &skinTex);
	glBindTexture ( GL_TEXTURE_2D, skinTex);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//beachball texture
	buffer = esLoadTGA("Texture/beachball.tga",&tWidth,&tHeight);
	glGenTextures ( 1, ballTex+2);
	glBindTexture ( GL_TEXTURE_2D, ballTex[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//tennisball texture
	buffer = esLoadTGA("Texture/tennisball.tga",&tWidth,&tHeight);
	glGenTextures ( 1, ballTex+3);
	glBindTexture ( GL_TEXTURE_2D, ballTex[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//discoball texture
	buffer = esLoadTGA("Texture/discoball.tga",&tWidth,&tHeight);
	glGenTextures ( 1, ballTex+4);
	glBindTexture ( GL_TEXTURE_2D, ballTex[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//pass card texture  loading (Route 66 logo)
	buffer = esLoadTGA("Texture/route.tga",&tWidth,&tHeight);
	glGenTextures ( 1, cardTex);
	glBindTexture ( GL_TEXTURE_2D, cardTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//pass card support texture loading 
	buffer = esLoadTGA("Texture/woodTexture.tga",&tWidth,&tHeight);
	glGenTextures ( 1, cardTex+1);
	glBindTexture ( GL_TEXTURE_2D, cardTex[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//sky textures loading 
	buffer = esLoadTGA("Texture/Skybox-000.tga", &tWidth, &tHeight);
	glGenTextures(1, skyCube);
	glBindTexture(GL_TEXTURE_2D, skyCube[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Skybox-001.tga", &tWidth, &tHeight);
	glGenTextures(1, skyCube+1);
	glBindTexture(GL_TEXTURE_2D, skyCube[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Skybox-002.tga", &tWidth, &tHeight);
	glGenTextures(1, skyCube+2);
	glBindTexture(GL_TEXTURE_2D, skyCube[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Skybox-003.tga", &tWidth, &tHeight);
	glGenTextures(1, skyCube+3);
	glBindTexture(GL_TEXTURE_2D, skyCube[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Skybox-004.tga", &tWidth, &tHeight);
	glGenTextures(1, skyCube+4);
	glBindTexture(GL_TEXTURE_2D, skyCube[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	//ground texture loading 
	buffer = esLoadTGA("Texture/iarba.tga", &tWidth, &tHeight);
	glGenTextures(1, skyCube+5);
	glBindTexture(GL_TEXTURE_2D, skyCube[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	//road texture loading
	buffer = esLoadTGA("Texture/Skybox-005.tga", &tWidth, &tHeight);
	glGenTextures(1, &roadTex);
	glBindTexture(GL_TEXTURE_2D, roadTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	
	//buildings textures loading 
	buffer = esLoadTGA("Texture/7.tga", &tWidth, &tHeight);
	glGenTextures(1, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/001-1.tga", &tWidth, &tHeight);
	glGenTextures(1, textures+1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/002-1.tga", &tWidth, &tHeight);
	glGenTextures(2, textures+2);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/003-1.tga", &tWidth, &tHeight);
	glGenTextures(1, textures+3);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/004-1.tga", &tWidth, &tHeight);
	glGenTextures(1, textures+4);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/005-1.tga", &tWidth, &tHeight);
	glGenTextures(1, textures+5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Brasov/003.tga", &tWidth, &tHeight);
	glGenTextures(1, textures+6);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	
	//doors texture loading
	buffer = esLoadTGA("Texture/Brasov/002.tga", &tWidth, &tHeight);
	glGenTextures(1, &doorTex);
	glBindTexture(GL_TEXTURE_2D, doorTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	
	//doors texture loading
	buffer = esLoadTGA("Texture/door2.tga", &tWidth, &tHeight);
	glGenTextures(1, &doorTex);
	glBindTexture(GL_TEXTURE_2D, doorTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	
	//"you win" texture loading
	buffer = esLoadTGA("Texture/win.tga", &tWidth, &tHeight);
	glGenTextures(1, &winTex);
	glBindTexture(GL_TEXTURE_2D, winTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
}

char* Texture::esLoadTGA(char *fileName, double *width, double *height)
{
	char *buffer = NULL;
	FILE *f;
	unsigned char tgaheader[12];
	unsigned char attributes[6];
	unsigned int imagesize;
	fopen_s(&f, fileName, "rb");
	if (f == NULL) return NULL;
	if (fread(&tgaheader, sizeof(tgaheader), 1, f) == 0)
	{
		fclose(f);
		return NULL;
	}

	if (fread(attributes, sizeof(attributes), 1, f) == 0)
	{
		fclose(f);
		return 0;
	}

	*width = attributes[1] *256 + attributes[0];
	*height = attributes[3] * 256 + attributes[2];
	imagesize = attributes[4] / 8 * *width * *height;
	buffer = (char*)malloc(imagesize);
	if (buffer == NULL)
	{
		fclose(f);
		return 0;
	}

	if (fread(buffer, 1, imagesize, f) != imagesize)
	{
		free(buffer);
		return NULL;
	}
	fclose(f);
	return buffer;
}
Texture& Texture::GetInstance()
{
	static Texture instance;
	return instance;
}