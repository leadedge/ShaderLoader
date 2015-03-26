//
//		ShaderLoader.h
//
//		------------------------------------------------------------
//
//		Copyright (c) 2015, Lynn Jarvis, Leading Edge. Pty. Ltd. All rights reserved.
//
//		Redistribution and use in source and binary forms, with or without modification, 
//		are permitted provided that the following conditions are met:
//
//		1. Redistributions of source code must retain the above copyright notice, 
//		   this list of conditions and the following disclaimer.
//
//		2. Redistributions in binary form must reproduce the above copyright notice, 
//		   this list of conditions and the following disclaimer in the documentation 
//		   and/or other materials provided with the distribution.
//
//		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"	AND ANY 
//		EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
//		OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE	ARE DISCLAIMED. 
//		IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
//		INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
//		PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
//		INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//		LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//		OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//		--------------------------------------------------------------
//
#pragma once
#ifndef ShaderLoader_H
#define ShaderLoader_H

#include <FFGLShader.h>
#include "../FFGLPluginSDK.h"

class ShaderLoader : public CFreeFrameGLPlugin
{

public:

	ShaderLoader();
	virtual ~ShaderLoader();

	///////////////////////////////////////////////////
	// FreeFrameGL plugin methods
	///////////////////////////////////////////////////
	
	DWORD SetParameter(const SetParameterStruct* pParam);		
	DWORD GetParameter(DWORD dwIndex);					
	DWORD ProcessOpenGL(ProcessOpenGLStruct* pGL);
	DWORD InitGL(const FFGLViewportStruct *vp);
	DWORD DeInitGL();

	DWORD GetInputStatus(DWORD dwIndex);
	char * GetParameterDisplay(DWORD dwIndex);

	///////////////////////////////////////////////////
	// Factory method
	///////////////////////////////////////////////////
	static DWORD __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance)  {
  		*ppOutInstance = new ShaderLoader();
		if (*ppOutInstance != NULL)
			return FF_SUCCESS;
		return FF_FAIL;
	}

protected:	

	// FFGL user parameters
	char  m_HostName[MAX_PATH];
	char  m_ShaderPath[MAX_PATH];
	char  m_ShaderName[256];
	char  m_UserInput[MAX_PATH];
	char  m_UserShaderName[256];
	char  m_UserShaderPath[MAX_PATH];
	char  m_DisplayValue[16];
	float m_UserSpeed;
	float m_UserMouseX;
	float m_UserMouseY;
	float m_UserMouseLeftX;
	float m_UserMouseLeftY;
	float m_UserRed;
	float m_UserGreen;
	float m_UserBlue;
	float m_UserAlpha;

	bool bInitialized;
	bool bStarted;
	bool bDialogOpen;
	bool bSpoutPanelOpened;

	SHELLEXECUTEINFOA ShExecInfo;
	HWND hwndEditor;

	// Local fbo and texture
	GLuint m_glTexture0;
	GLuint m_glTexture1;
	GLuint m_glTexture2;
	GLuint m_glTexture3;
	GLuint m_fbo;

	// Viewport
	float m_vpWidth;
	float m_vpHeight;
	
	// Time
	double startTime, elapsedTime, lastTime, PCFreq;
	__int64 CounterStart;

	//
	// Shader uniforms
	//

	// Time
	float m_time;

	// Date (year, month, day, time in seconds)
	float m_dateYear;
	float m_dateMonth;
	float m_dateDay;
	float m_dateTime;

	// Channel playback time (in seconds)
	// iChannelTime components are always equal to iGlobalTime
	float m_channelTime[4];

	// Channel resolution in pixels - 4 channels with width, height, depth each
	float m_channelResolution[4][3];

	// Mouse
	float m_mouseX;
	float m_mouseY;

	// Mouse left and right
	float m_mouseLeftX;
	float m_mouseLeftY;
	float m_mouseRightX;
	float m_mouseRightY;

	int m_initResources;
	FFGLExtensions m_extensions;
    FFGLShader m_shader;

	GLint m_inputTextureLocation;
	GLint m_inputTextureLocation1;
	GLint m_inputTextureLocation2;
	GLint m_inputTextureLocation3;
	
	GLint m_timeLocation;
	GLint m_dateLocation;
	GLint m_channeltimeLocation;
	GLint m_channelresolutionLocation;
	GLint m_mouseLocation;
	GLint m_resolutionLocation;
	GLint m_mouseLocationVec4;
	GLint m_screenLocation;
	GLint m_surfaceSizeLocation;
	GLint m_surfacePositionLocation;
	GLint m_vertexPositionLocation;

	// ShaderLoader extras
	GLint m_inputColourLocation;

	void SetDefaults();
	void StartCounter();
	double GetCounter();
	HMODULE GetCurrentModule();
	bool AddModulePath(const char *filename, char *filepath);
	bool LoadShaderFile(const char *path);
	bool LoadShader(std::string shaderString);
	bool WritePathToRegistry(const char *filepath, const char *subkey, const char *valuename);
	bool ReadPathFromRegistry(const char *filepath, const char *subkey, const char *valuename);
	bool SelectSpoutPanel(const char *message);
	bool OpenEditor(const char *filename);
	bool CheckSpoutPanel();
	void CreateRectangleTexture(FFGLTextureStruct Texture, FFGLTexCoords maxCoords, GLuint &glTexture, GLenum texunit, GLuint &fbo, GLuint hostFbo);

};


#endif
