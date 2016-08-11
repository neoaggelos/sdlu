/* 
 * OpenGL symbols - the values are the same for all implementations and the
 * OpenGL headers are not included, so we have to define them here
 */

#define GL_UNSIGNED_BYTE 0x1401
#define GL_RGBA 0x1908
#define GL_NEAREST 0x2600
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_2D 0x0DE1
#define GL_EXTENSIONS 0x1F03
#define GL_BLEND 0x0BE2

typedef unsigned char GLubyte;
typedef unsigned int GLenum;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef int GLint;
typedef void GLvoid;
typedef float GLfloat;

#ifdef __APPLE__
typedef void* GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif

#if defined(_MSC_VER) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
# define APIENTRY   __stdcall
#else
# define APIENTRY
#endif

typedef GLubyte* (APIENTRY *GL_GETSTRING)(GLenum);
typedef void (APIENTRY *GL_BINDTEXTURE)(GLenum, GLuint);
typedef void (APIENTRY *GL_COLOR4F)(GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRY *GL_DISABLE)(GLenum);
typedef void (APIENTRY *GL_GENTEXTURES)(GLsizei, GLuint*);
typedef void (APIENTRY *GL_POPMATRIX)(void);
typedef void (APIENTRY *GL_PUSHMATRIX)(void);
typedef void (APIENTRY *GL_TEXIMAGE2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*);
typedef void (APIENTRY *GL_TEXPARAMETERI)(GLenum, GLenum, GLint);
typedef void (APIENTRY *GL_USEPROGRAM)(GLuint);
typedef void (APIENTRY *GL_USEPROGRAMOBJECTARB)(GLhandleARB);

#define load_gl_func(func, type)                        \
    func = (type) SDL_GL_GetProcAddress(#func);         \
    if (!func) {                                        \
        SDLU_ExitError("could not load " #func, 0);     \
    }

