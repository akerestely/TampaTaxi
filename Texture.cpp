#include "Texture.h"


Texture::Texture(void)
{
	double tWidth, tHeight;
	char* buffer ;
	
	
	//male body texture1 front
	buffer = esLoadTGA("Texture/Human/mBodyTex00.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &mBodyTex[0][0]);
	glBindTexture ( GL_TEXTURE_2D, mBodyTex[0][0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//male body texture1 back
	buffer = esLoadTGA("Texture/Human/mBodyTex01.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &mBodyTex[0][1]);
	glBindTexture ( GL_TEXTURE_2D,mBodyTex[0][1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

		//male body texture2 front
	buffer = esLoadTGA("Texture/Human/mBodyTex10.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &mBodyTex[1][0]);
	glBindTexture ( GL_TEXTURE_2D, mBodyTex[1][0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//male body texture2 back
	buffer = esLoadTGA("Texture/Human/mBodyTex11.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &mBodyTex[1][1]);
	glBindTexture ( GL_TEXTURE_2D,mBodyTex[1][1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );


	//male body texture3 front
	buffer = esLoadTGA("Texture/Human/mBodyTex20.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &mBodyTex[2][0]);
	glBindTexture ( GL_TEXTURE_2D, mBodyTex[2][0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//male body texture3 back
	buffer = esLoadTGA("Texture/Human/mBodyTex21.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &mBodyTex[2][1]);
	glBindTexture ( GL_TEXTURE_2D,mBodyTex[2][1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//female body texture1 front
	buffer = esLoadTGA("Texture/Human/fBodyTex00.tga",&tWidth,&tHeight);
	glGenTextures ( 1,&fBodyTex[0][0]);
	glBindTexture ( GL_TEXTURE_2D, fBodyTex[0][0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//female body texture1 back
	buffer = esLoadTGA("Texture/Human/fBodyTex01.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &fBodyTex[0][1]);
	glBindTexture ( GL_TEXTURE_2D,fBodyTex[0][1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//female body texture2 front
	buffer = esLoadTGA("Texture/Human/fBodyTex10.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &fBodyTex[1][0]);
	glBindTexture ( GL_TEXTURE_2D, fBodyTex[1][0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//female body texture2 back
	buffer = esLoadTGA("Texture/Human/fBodyTex11.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &fBodyTex[1][1]);
	glBindTexture ( GL_TEXTURE_2D,fBodyTex[1][1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );


	//female body texture3 front
	buffer = esLoadTGA("Texture/Human/fBodyTex20.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &fBodyTex[2][0]);
	glBindTexture ( GL_TEXTURE_2D, fBodyTex[2][0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//female body texture3 back
	buffer = esLoadTGA("Texture/Human/fBodyTex21.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &fBodyTex[2][1]);
	glBindTexture ( GL_TEXTURE_2D, fBodyTex[2][1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );


	//legs texture1
	buffer = esLoadTGA("Texture/Human/mLegsTex1.tga",&tWidth,&tHeight);
	glGenTextures ( 1, mLegsTex);
	glBindTexture ( GL_TEXTURE_2D, mLegsTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//legs texture2
	buffer = esLoadTGA("Texture/Human/mLegsTex2.tga",&tWidth,&tHeight);
	glGenTextures ( 1, mLegsTex+1);
	glBindTexture ( GL_TEXTURE_2D, mLegsTex[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//legs texture3
	buffer = esLoadTGA("Texture/Human/mLegsTex3.tga",&tWidth,&tHeight);
	glGenTextures ( 1, mLegsTex+2);
	glBindTexture ( GL_TEXTURE_2D, mLegsTex[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );


	//skirt texture1
	buffer = esLoadTGA("Texture/Human/skirtTex1.tga",&tWidth,&tHeight);
	glGenTextures ( 1, skirtTex);
	glBindTexture ( GL_TEXTURE_2D, skirtTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//skirt texture2
	buffer = esLoadTGA("Texture/Human/skirtTex2.tga",&tWidth,&tHeight);
	glGenTextures ( 1, skirtTex+1);
	glBindTexture ( GL_TEXTURE_2D, skirtTex[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//skirt texture3
	buffer = esLoadTGA("Texture/Human/skirtTex3.tga",&tWidth,&tHeight);
	glGenTextures ( 1, skirtTex+2);
	glBindTexture ( GL_TEXTURE_2D, skirtTex[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//male face texture
	buffer = esLoadTGA("Texture/Human/mFaceTex.tga",&tWidth,&tHeight);
	glGenTextures ( 1, mFaceTex);
	glBindTexture ( GL_TEXTURE_2D, mFaceTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//female face texture
	buffer = esLoadTGA("Texture/Human/fFaceTex.tga",&tWidth,&tHeight);
	glGenTextures ( 1, fFaceTex);
	glBindTexture ( GL_TEXTURE_2D, fFaceTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//male feet texture
	buffer = esLoadTGA("Texture/Human/mFeetTex.tga",&tWidth,&tHeight);
	glGenTextures ( 1, mFeetTex);
	glBindTexture ( GL_TEXTURE_2D, mFeetTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//female feet texture
	buffer = esLoadTGA("Texture/Human/fFeetTex.tga",&tWidth,&tHeight);
	glGenTextures ( 1, fFeetTex);
	glBindTexture ( GL_TEXTURE_2D, fFeetTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	//skin texture
	buffer = esLoadTGA("Texture/Human/skinTex.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &skinTex);
	glBindTexture ( GL_TEXTURE_2D, skinTex);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	//taxi icon texture
	buffer = esLoadTGA("Texture/Human/getTaxiTex.tga",&tWidth,&tHeight);
	glGenTextures ( 1, &getTaxiTex);
	glBindTexture ( GL_TEXTURE_2D, getTaxiTex);
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

	buffer = esLoadTGA("Texture/hudTex.tga", &tWidth, &tHeight);
	glGenTextures(1, &hudText);
	glBindTexture(GL_TEXTURE_2D, hudText);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/numberBun.tga", &tWidth, &tHeight);
	glGenTextures(1, &hudNumbers);
	glBindTexture(GL_TEXTURE_2D, hudNumbers);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/dollarSignBun.tga", &tWidth, &tHeight);
	glGenTextures(1, &moneyTex);
	glBindTexture(GL_TEXTURE_2D, moneyTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Road/roadV3.tga", &tWidth, &tHeight);
	glGenTextures(1, &roadTex);
	glBindTexture(GL_TEXTURE_2D, roadTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Road/node.tga", &tWidth, &tHeight);
	glGenTextures(1, &nodeTex);
	glBindTexture(GL_TEXTURE_2D, nodeTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Road/sideway.tga", &tWidth, &tHeight);
	glGenTextures(1, &sidewayTex);
	glBindTexture(GL_TEXTURE_2D, sidewayTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Car/Golf7/vw_tire2_tex.tga", &tWidth, &tHeight);
	glGenTextures(1, &wheelSide);
	glBindTexture(GL_TEXTURE_2D, wheelSide);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Car/Golf7/wheelTire.tga", &tWidth, &tHeight);
	glGenTextures(1, &wheelBase);
	glBindTexture(GL_TEXTURE_2D, wheelBase);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Car/Golf7/vw-golf7.tga", &tWidth, &tHeight);
	glGenTextures(1, &carSide);
	glBindTexture(GL_TEXTURE_2D, carSide);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	
	buffer = esLoadTGA("Texture/Car/Golf7/vw-golf7-front.tga", &tWidth, &tHeight);
	glGenTextures(1, &carFront);
	glBindTexture(GL_TEXTURE_2D, carFront);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Car/Golf7/vw-golf7-back.tga", &tWidth, &tHeight);
	glGenTextures(1, &carBack);
	glBindTexture(GL_TEXTURE_2D, carBack);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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