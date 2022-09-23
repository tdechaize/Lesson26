/*		This code has been created by Banu Cosmin aka Choko - 20 may 2000
 *		and uses NeHe tutorials as a starting point (window initialization,
 *		texture loading, GL initialization and code for keypresses) - very good
 *		tutorials, Jeff. If anyone is interested about the presented algorithm
 *		please e-mail me at boct@romwest.ro
 *
 *		Code Commmenting And Clean Up By Jeff Molofee ( NeHe )
 *		NeHe Productions	...		http://nehe.gamedev.net
 *      Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/24
 */

 /* **************************************************************
 *  Project: $(project)
 *  Function : Main program
 ***************************************************************
 *  $Author: Jeff Molofee 2000
 *  $Name:  $
 ***************************************************************
 *
 *  Copyright NeHe Production
 *
 ***************************************************************/

/**         Comments manageable by Doxygen
*
*  Modified smoothly by Thierry DECHAIZE
*
*  Paradigm : obtain one source (only one !) compatible for multiple free C Compilers
*    and provide for all users an development environment on Windows (64 bits compatible),
*    the great Code::Blocks manager (version 20.03), and don't use glaux.lib or glaux.dll.
*
*	a) Mingw 32 bits, version officielle gcc 9.2.0 : downloadable on http://sourceforge.net/projects/mingw/ (official)
*	b) Mingw 64 bits included in new IDE Red Panda Dev-Cpp, version gcc 10.3.0 : donwloadable on http://sourceforge.net/projects/dev-cpp-2020/
*	c) Mingw 64 bits included in package Code::Blocks (version 20.03), version gcc 8.1.0 : downloadable on http://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/
*	d) Mingw 32 and 64 bits packagés, version gcc 11.2.0 : downloadable on  https://winlibs.com/ (and CLANG included in, 32 and 64 bits), two kits :
*			- winlibs-i686-posix-dwarf-gcc-11.2.0-llvm-13.0.0-mingw-w64ucrt-9.0.0-r2.7z (32 bits)
*			- winlibs-x86_64-posix-seh-gcc-11.2.0-llvm-13.0.0-mingw-w64ucrt-9.0.0-r2.7z (64 bits)
*	e) Cygwin64, 32 et 64 bits, version gcc 11.0.0 : downloadable on http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
*	f) TDM GCC, 32 et 64 bits, version 10.3.0 : downloadable on http://sourceforge.net/projects/TDM-GCC
*	g) MSYS2 environnement MINGW32 and MINGW64, 32 et 64 bits, version de 2022 (msys2-x86_64-20220118.exe), version gcc 11.2.0 : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220118.exe
*	h) Visual Studio 2022, 32 et 64 bits, community edition for free : downloadable on https://visualstudio.microsoft.com/fr/thank-you-downloading-visual-studio/?sku=Community&rel=17
*	i) Borland C/C++ 32 bits, version 5.5 : downloadable on https://developerinsider.co/download-and-install-borland-c-compiler-on-windows-10/
*	j) Digital Mars Compiler C 32 bits version 8.57 : downloadable on http://www.digitalmars.com (the more old compiler, the more bugged, dead branch !)
*	k) OpenWatcom 32 et 64 bits, version 2.0 : downloadable on http://openwatcom.mirror.fr/ (only 32 bits version run correctly !)
*	l) Lcc and Lcc64, 32 et 64 bits: downloadable http://www.cs.virginia.edu/~lcc-win32/
*	m) PELLES C, 32 et 64 bits, version 11.0 : downloadable on http://www.smorgasbordet.com/pellesc/
*	o) CLANG, adossé aux environnements MINGW64 et MINGW32, version 13.0.0 (version gcc 12.0.0) : downloadable on https://winlibs.com/
*	p) CLANG, adossé aux environnements Visual Studio 2022 (+ kits Microsoft), version 13.0.0 : downloadable on https://releases.llvm.org/download.html
*	q) CLANG de la version MSYS2, adossé aux environnements MINGW64 et MINGW32, version 13.0.0 (version gcc 11.2.0) : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220118.exe
*	r) CLANG de la version CYGWIN, adossé aux environnements MINGW64 et MINGW32, version 8.0.0 (version gcc 11.0.0) : downloadable http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
*
*   TDE -> Add resource file and resource header for restitute version + icon OpenGL.ico for fun
*			because versionning is important, same for freeware :-) !
*
*  Date : 2022/02/16
*
* \file            Lesson26.c
* \author          Banu Octavian & Jeff Molofee (NeHe) originely, Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/24
* \author          After adapted by Thierry Dechaize to verify paradigm : one source for multiple C Compilers
* \version         2.0.1.0
* \date            16 février 2022
* \brief           Ouvre une fenêtre Windows et dessine une boule (en trois couleurs) que l'on peut faire tourner avec les flêches de déplacement clavier au dessus d'un "plancher".
* \details         Ce programme ne gére que trois événements : le clic sur le bouton "Fermé" de la fenêtre, la sortie par la touche ESC et les flêches de déplacement clavier.
*
*
*/

#if defined __CYGWIN__ || defined __LCC__
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>								// Header File For Windows
#if defined(__LCC__)
#ifndef WINGDIAPI
#   define WINGDIAPI __stdcall
#endif
#endif

#include <stdio.h>									// Header File For Standard Input / Output
#include <gl\gl.h>									// Header File For The OpenGL32 Library
#include <gl\glu.h>									// Header File For The GLu32 Library
#include <gl\glext.h>		                        // Header File For The GLext Library
/* #include <gl\glaux.h>		                    // Header File For The Glaux Library  */

#if defined __GNUC__ || defined __LCC__ || defined _MSC_VER || defined __TURBOC__
#include <stdbool.h>
#endif

#if defined(__SC__) || defined(__DMC__)
#include <wtypes.h>
// typedef BOOLEAN         bool;
#endif

// A user defined ``bool'' type for compilers that don't yet support one.
//
#if defined(__BORLANDC__) && (__BORLANDC__ < 0x500) || defined(__WATCOMC__)
  #define DONT_HAVE_BOOL_TYPE
#endif

// A ``bool'' type for compilers that don't yet support one.
#if defined(DONT_HAVE_BOOL_TYPE)
  typedef char bool;

  #ifdef true
    #warning Better check include file ``mytypes.h''.
    #undef true
  #endif
  #define true 1

  #ifdef false
    #warning Better check include file ``mytypes.h''.
    #undef false
  #endif
  #define false 0
#endif

HDC			hDC=NULL;									// Private GDI Device Context
HGLRC		hRC=NULL;									// Permanent Rendering Context
HWND		hWnd=NULL;									// Holds Our Window Handle
HINSTANCE	hInstance = NULL;							// Holds The Instance Of The Application

int         loop=0;                                        // Generic Loop1
BOOL		keys[256];									// Array Used For The Keyboard Routine
BOOL		active=TRUE;								// Window Active Flag Set To TRUE By Default
BOOL		fullscreen=TRUE;							// Fullscreen Flag Set To Fullscreen Mode By Default

// Light Parameters
static GLfloat LightAmb[] = {0.7f, 0.7f, 0.7f, 1.0f};	// Ambient Light
static GLfloat LightDif[] = {1.0f, 1.0f, 1.0f, 1.0f};	// Diffuse Light
static GLfloat LightPos[] = {4.0f, 4.0f, 6.0f, 1.0f};	// Light Position

GLUquadricObj	*q;										// Quadratic For Drawing A Sphere

GLfloat		xrot		=  0.0f;						// X Rotation
GLfloat		yrot		=  0.0f;						// Y Rotation
GLfloat		xrotspeed	=  0.0f;						// X Rotation Speed
GLfloat		yrotspeed	=  0.0f;						// Y Rotation Speed
GLfloat		zoom		= -7.0f;						// Depth Into The Screen
GLfloat		height		=  2.0f;						// Height Of Ball From Floor

GLuint		texture[3],texid[3];						// 3 Textures

static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,												// Version Number
		PFD_DRAW_TO_WINDOW |							// Format Must Support Window
		PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,								// Must Support Double Buffering
		PFD_TYPE_RGBA,									// Request An RGBA Format
		0,  											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,								// Color Bits Ignored
		0,												// No Alpha Buffer
		0,												// Shift Bit Ignored
		0,												// No Accumulation Buffer
		0, 0, 0, 0,										// Accumulation Bits Ignored
		16,												// 16Bit Z-Buffer (Depth Buffer)
		1,												// Use Stencil Buffer ( * Important * )
		0,												// No Auxiliary Buffer
		PFD_MAIN_PLANE,									// Main Drawing Layer
		0,												// Reserved
		0, 0, 0											// Layer Masks Ignored
    };

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

/**	            This Code Resize the main window.
*
* \brief      Fonction ReSizeGLScene : redimensionnement de la fenêtre Windows gérant OpenGL
* \details    En entrée les deux nouvelles dimensions de la fenêtre
* \param	  width			Width of the GL Window Or Fullscreen Mode				*
* \param	  height		Height of the GL Window Or Fullscreen Mode			    *
* \return     GLvoid        un void OpenGL (aucun retour).
*
*/

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

/**	            This Code Creates Texture From a Bitmap File.
*
* \brief      Fonction NeHeLoadBitmap3 : charge trois fichier BMP en mémoire pour générer un tableau de trois textures
* \details    En entrée les trois noms des fichier Bitmap et en sortie le tableau des trois textures utilisables avec OpenGL
* \param	  szFN1			        nom du premier fichier BMP				                            *
* \param	  szFN2			        nom du deuxième fichier BMP				                            *
* \param	  szFN3			        nom du troisième fichier BMP				                        *
* \param	  texid			        un pointeur sur le tableau des trois textures générées			    *
* \return     bool                  un booleen, le tableau des trois textures créé ou non.              *
*
*/

bool NeHeLoadBitmap3(LPTSTR szFN1,LPTSTR szFN2,LPTSTR szFN3,GLuint *texid)					// Creates Texture From A Bitmap File
{
	HBITMAP hBMP1,hBMP2,hBMP3 ;														// Handle Of The Bitmap
	BITMAP	BMP1,BMP2,BMP3 ;														// Bitmap Structure

	glGenTextures(3, &texid[0]);											// Create The Texture
	hBMP1=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFN1, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP1)															// Does The Bitmap Exist?
		return FALSE;													// If Not Return False

    // Get The Object
	GetObject(hBMP1, sizeof(BMP1), &BMP1);								// hBMP:        Handle To Graphics Object
																		// sizeof(BMP): Size Of Buffer For Object Information
																		// &BMP:        Buffer For Object Information
	hBMP2=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFN2, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP2)															// Does The Bitmap Exist?
		return FALSE;													// If Not Return False

    // Get The Object
	GetObject(hBMP2, sizeof(BMP2), &BMP2);								// hBMP:        Handle To Graphics Object
																		// sizeof(BMP): Size Of Buffer For Object Information
																		// &BMP:        Buffer For Object Information
	hBMP3=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFN3, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP3)															// Does The Bitmap Exist?
		return FALSE;													// If Not Return False

    // Get The Object
	GetObject(hBMP3, sizeof(BMP3), &BMP3);								// hBMP:        Handle To Graphics Object
																		// sizeof(BMP): Size Of Buffer For Object Information

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);								// Pixel Storage Mode (Word Alignment / 4 Bytes)

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid[0]);								// Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Mag Filter
//	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP1.bmWidth, BMP1.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP1.bmBits);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP1.bmWidth, BMP1.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP1.bmBits);

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid[1]);								// Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP2.bmWidth, BMP2.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP2.bmBits);

    // Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid[2]);								// Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP3.bmWidth, BMP3.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP3.bmBits);

	DeleteObject(hBMP1);													// Delete The Object
	DeleteObject(hBMP2);													// Delete The Object
	DeleteObject(hBMP3);													// Delete The Object

	return TRUE;														// Loading Was Successful
}

int LoadGLTextures()										// Load Bitmaps And Convert To Textures
{
	// Start Of User Initialization
	if (!NeHeLoadBitmap3("../../Data/EnvWall.bmp","../../Data/Ball.bmp","../../Data/EnvRoll.bmp", texture))		// Load The Bitmap
		return FALSE;

	return TRUE;											// Return The Status
}

/**	            This Code finish the initialization OpenGL of the main window.
*
* \brief      Fonction InitGL : Fin de l'initialisation de la fenêtre Windows gérant OpenGL
* \details    Rien
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	if (!LoadGLTextures())								// If Loading The Textures Failed
	{
		return FALSE;									// Return False
	}
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.2f, 0.5f, 1.0f, 1.0f);				// Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear The Stencil Buffer To 0
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);			// Set The Ambient Lighting For Light0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);			// Set The Diffuse Lighting For Light0
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);		// Set The Position For Light0

	glEnable(GL_LIGHT0);								// Enable Light 0
	glEnable(GL_LIGHTING);								// Enable Lighting

	q = gluNewQuadric();								// Create A New Quadratic
	gluQuadricNormals(q, GL_SMOOTH);					// Generate Smooth Normals For The Quad
	gluQuadricTexture(q, GL_TRUE);						// Enable Texture Coords For The Quad

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping

	return TRUE;										// Initialization Went OK
}

/**	            This Code draw object of scene.
*
* \brief      Fonction DrawObject : dessin dde l'objet de la scène.
* \details    Rien
* \return     void       	un void (rien n'est retourné)
*
*/

void DrawObject()										// Draw Our Ball
{
	glColor3f(1.0f, 1.0f, 1.0f);						// Set Color To White
	glBindTexture(GL_TEXTURE_2D, texture[1]);			// Select Texture 2 (1)
	gluSphere(q, 0.35f, 32, 16);						// Draw First Sphere

	glBindTexture(GL_TEXTURE_2D, texture[2]);			// Select Texture 3 (2)
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);					// Set Color To White With 40% Alpha
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set Blending Mode To Mix Based On SRC Alpha
	glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
	glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping

	gluSphere(q, 0.35f, 32, 16);						// Draw Another Sphere Using New Texture
														// Textures Will Mix Creating A MultiTexture Effect (Reflection)
	glDisable(GL_TEXTURE_GEN_S);						// Disable Sphere Mapping
	glDisable(GL_TEXTURE_GEN_T);						// Disable Sphere Mapping
	glDisable(GL_BLEND);								// Disable Blending
}

/**	            This Code draw floor of scene.
*
* \brief      Fonction DrawFloor : dessin du plancher de la scène.
* \details    Rien
* \return     void       	un void (rien n'est retourné)
*
*/

void DrawFloor()										// Draws The Floor
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Texture 1 (0)
	glBegin(GL_QUADS);									// Begin Drawing A Quad
		glNormal3f(0.0, 1.0, 0.0);						// Normal Pointing Up
			glTexCoord2f(0.0f, 1.0f);					// Bottom Left Of Texture
			glVertex3f(-2.0, 0.0, 2.0);					// Bottom Left Corner Of Floor

			glTexCoord2f(0.0f, 0.0f);					// Top Left Of Texture
			glVertex3f(-2.0, 0.0,-2.0);					// Top Left Corner Of Floor

			glTexCoord2f(1.0f, 0.0f);					// Top Right Of Texture
			glVertex3f( 2.0, 0.0,-2.0);					// Top Right Corner Of Floor

			glTexCoord2f(1.0f, 1.0f);					// Bottom Right Of Texture
			glVertex3f( 2.0, 0.0, 2.0);					// Bottom Right Corner Of Floor
	glEnd();											// Done Drawing The Quad
}

/**	            This Code draw the scene OpenGL in the main window.
*
* \brief      Fonction DrawGLScene : Dessin sous OpenGL dans la fenêtre Windows.
* \details    Rien
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int DrawGLScene(GLvoid)									// Draw Everything
{
	// Clip Plane Equations
	double eqr[] = {0.0f,-1.0f, 0.0f, 0.0f};			// Plane Equation To Use For The Reflected Objects

	// Clear Screen, Depth Buffer & Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslatef(0.0f, -0.6f, zoom);					// Zoom And Raise Camera Above The Floor (Up 0.6 Units)
	glColorMask(0,0,0,0);								// Set Color Mask
	glEnable(GL_STENCIL_TEST);							// Enable Stencil Buffer For "marking" The Floor
	glStencilFunc(GL_ALWAYS, 1, 1);						// Always Passes, 1 Bit Plane, 1 As Mask
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);			// We Set The Stencil Buffer To 1 Where We Draw Any Polygon
														// Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
														// Replace If Test Passes
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	DrawFloor();										// Draw The Floor (Draws To The Stencil Buffer)
														// We Only Want To Mark It In The Stencil Buffer
	glEnable(GL_DEPTH_TEST);							// Enable Depth Testing
	glColorMask(1,1,1,1);								// Set Color Mask to TRUE, TRUE, TRUE, TRUE
	glStencilFunc(GL_EQUAL, 1, 1);						// We Draw Only Where The Stencil Is 1
														// (I.E. Where The Floor Was Drawn)
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);				// Don't Change The Stencil Buffer
	glEnable(GL_CLIP_PLANE0);							// Enable Clip Plane For Removing Artifacts
														// (When The Object Crosses The Floor)
	glClipPlane(GL_CLIP_PLANE0, eqr);					// Equation For Reflected Objects
	glPushMatrix();										// Push The Matrix Onto The Stack
		glScalef(1.0f, -1.0f, 1.0f);					// Mirror Y Axis
		glLightfv(GL_LIGHT0, GL_POSITION, LightPos);	// Set Up Light0
		glTranslatef(0.0f, height, 0.0f);				// Position The Object
		glRotatef(xrot, 1.0f, 0.0f, 0.0f);				// Rotate Local Coordinate System On X Axis
		glRotatef(yrot, 0.0f, 1.0f, 0.0f);				// Rotate Local Coordinate System On Y Axis
		DrawObject();									// Draw The Sphere (Reflection)
	glPopMatrix();										// Pop The Matrix Off The Stack
	glDisable(GL_CLIP_PLANE0);							// Disable Clip Plane For Drawing The Floor
	glDisable(GL_STENCIL_TEST);							// We Don't Need The Stencil Buffer Any More (Disable)
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);		// Set Up Light0 Position
	glEnable(GL_BLEND);									// Enable Blending (Otherwise The Reflected Object Wont Show)
	glDisable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);					// Set Color To White With 80% Alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blending Based On Source Alpha And 1 Minus Dest Alpha
	DrawFloor();										// Draw The Floor To The Screen
	glEnable(GL_LIGHTING);								// Enable Lighting
	glDisable(GL_BLEND);								// Disable Blending
	glTranslatef(0.0f, height, 0.0f);					// Position The Ball At Proper Height
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);					// Rotate On The X Axis
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);					// Rotate On The Y Axis
	DrawObject();										// Draw The Ball
	xrot += xrotspeed;									// Update X Rotation Angle By xrotspeed
	yrot += yrotspeed;									// Update Y Rotation Angle By yrotspeed
	glFlush();											// Flush The GL Pipeline
	return TRUE;										// Everything Went OK
}

/**	            This Code test keyboard press.
*
* \brief      Fonction ProcessKeyboard : Gestion des touches clavier.
* \details    Rien
* \return     void       	un void (rien n'est retourné)
*
*/

void ProcessKeyboard()									// Process Keyboard Results
{
	if (keys[VK_RIGHT])		yrotspeed += 0.08f;			// Right Arrow Pressed (Increase yrotspeed)
	if (keys[VK_LEFT])		yrotspeed -= 0.08f;			// Left Arrow Pressed (Decrease yrotspeed)
	if (keys[VK_DOWN])		xrotspeed += 0.08f;			// Down Arrow Pressed (Increase xrotspeed)
	if (keys[VK_UP])		xrotspeed -= 0.08f;			// Up Arrow Pressed (Decrease xrotspeed)

	if (keys['A'])			zoom +=0.05f;				// 'A' Key Pressed ... Zoom In
	if (keys['Z'])			zoom -=0.05f;				// 'Z' Key Pressed ... Zoom Out

	if (keys[VK_PRIOR])		height +=0.03f;				// Page Up Key Pressed Move Ball Up
	if (keys[VK_NEXT])		height -=0.03f;				// Page Down Key Pressed Move Ball Down
}

/**	            This Code destroy all resources of this program.
*
* \brief      Fonction KillGLWindow : Destruction de toutes les ressources du programme.
* \details    Rien
* \param	  GLvoid			un void OpenGL.
* \return     GLvoid        	un void OpenGL.
*
*/

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/**	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *  \brief          Creation of our OpenGL Window
 *  \param 			title			- Title To Appear At The Top Of The Window				*
 *	\param 			width			- Width Of The GL Window Or Fullscreen Mode				*
 *	\param 			height			- Height Of The GL Window Or Fullscreen Mode			*
 *	\param          bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	\param          fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*
 *  \return         BOOL            - un entier booleen (OK ou non).
 */

BOOL CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
	GLuint		PixelFormat;							// Holds The Results After Searching For A Match
	WNDCLASS	wc;										// Windows Class Structure
	DWORD		dwExStyle;								// Window Extended Style
	DWORD		dwStyle;								// Window Style

	fullscreen=fullscreenflag;							// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);		// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;			// WndProc Handles Messages
	wc.cbClsExtra		= 0;							// No Extra Window Data
	wc.cbWndExtra		= 0;							// No Extra Window Data
	wc.hInstance		= hInstance;					// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);	// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);	// Load The Arrow Pointer
	wc.hbrBackground	= NULL;							// No Background Required For GL
	wc.lpszMenuName		= NULL;							// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";						// Set The Class Name

	if (!RegisterClass(&wc))							// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (fullscreen)										// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;						// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);	// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;		// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;		// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;			// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;						// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;							// Return FALSE
			}
		}
	}

	if (fullscreen)										// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;						// Window Extended Style
		dwStyle=WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
		ShowCursor(FALSE);								// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
	}

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,				// Extended Style For The Window
								"OpenGL",				// Class Name
								title,					// Window Title
								dwStyle,				// Window Style
								0, 0,					// Window Position
								width, height,			// Selected Width And Height
								NULL,					// No Parent Window
								NULL,					// No Menu
								hInstance,				// Instance
								NULL)))					// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

    pfd.cColorBits = bits;

    if (!(hDC=GetDC(hWnd)))                         // Did We Get A Device Context?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))		// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))			// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))					// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))						// Try To Activate The Rendering Context
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);							// Show The Window
	SetForegroundWindow(hWnd);							// Slightly Higher Priority
	SetFocus(hWnd);										// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);						// Set Up Our Perspective GL Screen

	if (!InitGL())										// Initialize Our Newly Created GL Window
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	return TRUE;										// Success
}

/**         Comments manageable by Doxygen
*
* \brief      Fonction CALLBACK de traitement des messages Windows
* \details    Traitement de la boucle infinie des messages Windows
* \param      hWnd         L'header de la fenêtre principale.
* \param      uMsg         Un entier non signé.
* \param      wParam       Les paramétres en entrée.
* \param      lParam       Autres paramétres en entrée.
* \return     LRESULT 	   Un LRESULT donnant le status du traitement du message.
*
*/

LRESULT CALLBACK WndProc(	HWND	hWnd,				// Handle For This Window
							UINT	uMsg,				// Message For This Window
							WPARAM	wParam,				// Additional Message Information
							LPARAM	lParam)				// Additional Message Information
{
	switch (uMsg)										// Check For Windows Messages
	{
		case WM_ACTIVATE:								// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))						// Check Minimization State
			{
				active=TRUE;							// Program Is Active
			}
			else										// Otherwise
			{
				active=FALSE;							// Program Is No Longer Active
			}

			return 0;									// Return To The Message Loop
		}

		case WM_SYSCOMMAND:								// Intercept System Commands
		{
			switch (wParam)								// Check System Calls
			{
				case SC_SCREENSAVE:						// Screensaver Trying To Start?
				case SC_MONITORPOWER:					// Monitor Trying To Enter Powersave?
				return 0;								// Prevent From Happening
			}
			break;										// Exit
		}

		case WM_CLOSE:									// Did We Receive A Close Message?
		{
			PostQuitMessage(0);							// Send A Quit Message
			return 0;									// Jump Back
		}

		case WM_KEYDOWN:								// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;						// If So, Mark It As TRUE
			return 0;									// Jump Back
		}

		case WM_KEYUP:									// Has A Key Been Released?
		{
			keys[wParam] = FALSE;						// If So, Mark It As FALSE
			return 0;									// Jump Back
		}

		case WM_SIZE:									// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;									// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);		// Return Unhandled Messages
}

/**	This Code is mandatory to create windows application (function WinMain)					*
 *  \brief          Creation of our application on Windows System (not console application) *
 *  \param 			hInstance		- Header de l'instance Windows				            *
 *	\param 			hPrevInstance	- Header de l'instance précédente de Windows 			*
 *	\param 			lpCmdLine		- Un pointeur sur la ligne de commande 			        *
 *	\param          nCmdShow		- Un indicateur d'état			                        *
 *  \return         int             - un entier booleen (OK ou non).                        *
 *	                                                                                        *
 */

int WINAPI WinMain(	HINSTANCE	hInstance,				// Instance
					HINSTANCE	hPrevInstance,			// Previous Instance
					LPSTR		lpCmdLine,				// Command Line Parameters
					int			nCmdShow)				// Window Show State
{
	MSG		msg;										// Windows Message Structure
	BOOL	done=FALSE;									// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;								// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Banu Octavian & NeHe's Stencil & Reflection Tutorial", 640, 480, 32, fullscreen))
	{
		return 0;										// Quit If Window Was Not Created
	}

	while(!done)										// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))		// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)					// Have We Received A Quit Message?
			{
				done=TRUE;								// If So done=TRUE
			}
			else										// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);					// Translate The Message
				DispatchMessage(&msg);					// Dispatch The Message
			}
		}
		else											// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)									// Program Active?
			{
				if (keys[VK_ESCAPE])					// Was Escape Pressed?
				{
					done=TRUE;							// ESC Signalled A Quit
				}
				else									// Not Time To Quit, Update Screen
				{
					DrawGLScene();						// Draw The Scene
					SwapBuffers(hDC);					// Swap Buffers (Double Buffering)

					ProcessKeyboard();					// Processed Keyboard Presses
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();										// Kill The Window
	return (msg.wParam);								// Exit The Program
}
