#ifndef __WZLIB_C_H
#define __WZLIB_C_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>
#include <stdio.h>

#define WZLIB_HAVE_SDL

#ifdef WZLIB_HAVE_SDL
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#endif

/*some macros for typecasting*/
#define WZLIB_PRIMITIVEPROPERTY(prop)	((WZLib_PrimitiveProperty*)prop)
#define WZLIB_PROPERTY(prop)		((WZLib_Property*)prop)
#define WZLIB_SUBPROPERTY(prop)		((WZLib_SubProperty*)prop)
#define WZLIB_CANVASPROPERTY(prop)	((WZLib_CanvasProperty*)prop)
#define WZLIB_OBJECT(prop)		((WZLib_Object*)prop)
#define WZLIB_SPROPTYPE(prop)		((WZLib_PropertyType)(((int)(WZLIB_PROPERTY(prop)->propType))/100*100))
#define WZLIB_FILE(obj)			((WZLib_File*)obj)

struct _struct_WZLib_Key; /*there will only be one of these*/

struct _struct_WZLib_Object;
struct _struct_WZLib_Directory;
struct _struct_WZLib_File;
struct _struct_WZLib_Image;

struct _struct_WZLib_Property;
struct _struct_WZLib_PrimitiveProperty;
struct _struct_WZLib_SubProperty;
struct _struct_WZLib_CanvasProperty;
struct _struct_WZLib_PNGProperty;

struct _struct_LL_Entry;

typedef enum _enum_WZLib_ObjectType{
	WZLib_ObjectType_Unknown=0,
	WZLib_ObjectType_File,
	WZLib_ObjectType_Header,
	WZLib_ObjectType_Image,
	WZLib_ObjectType_Directory,
	WZLib_ObjectType_Property,
}WZLib_ObjectType;

typedef enum _enum_PropertyType{
	WZLib_Prop_Unknown		=0,
	WZLib_Prop_Primitive		=400,
	WZLib_Prop_Null				=401,
	WZLib_Prop_UnsignedShort		=402,
	WZLib_Prop_CompressedInt		=403,
	WZLib_Prop_Vector			=404,
	WZLib_Prop_Float			=405,
	WZLib_Prop_Double			=406,
	WZLib_Prop_String			=407,
	WZLib_Prop_UOL				=408,
	WZLib_Prop_Sub			=500,
	WZLib_Prop_Canvas			=501,
	WZLib_Prop_Convex			=502,
	WZLib_Prop_PNG			=700,
	WZLib_Prop_MP3			=800,
}WZLib_PropertyType;

char*		WZLib_PropertyType_GetName(WZLib_PropertyType propType);

typedef enum _enum_ErrorCode{
	WZLib_Error_NoError=0,
	WZLib_Error_File_Parse_BadFileName,
	WZLib_Error_Image_Parse_Error1,
	WZLib_Error_Directory_Parse_Error1,
}ErrorCode;

const char* WZLib_GetError();
char*		WZLib_GetError_copy();

typedef struct _struct_WZLib_Object{
	struct _struct_WZLib_Object*	parent;
	char*				name;
	WZLib_ObjectType		type;
	int				parsed;
	int				blockSize;
	int				checksum;
	unsigned int			offset;
	unsigned int	objectID;
	unsigned int	refCount;
}WZLib_Object;

char*		WZLib_ObjectType_GetName(WZLib_ObjectType type);
int		WZLib_Object_GetSize(WZLib_Object* obj);
WZLib_Object*	WZLib_Object_Get_n(WZLib_Object* obj,const char* name);
WZLib_Object*	WZLib_Object_Get_nv(WZLib_Object* obj,...);
WZLib_Object*	WZLib_Object_Get_i(WZLib_Object* obj,int index);
WZLib_Object*	WZLib_Object_Get_iv(WZLib_Object* obj,...);

typedef struct _struct_WZLib_Header{
	struct _struct_WZLib_Object	inh;
	char*				ident;
	unsigned long long		fileSize;
	unsigned int			fileStart;
	short				version;
	char*				copyright;
	unsigned int			versionHash;
}WZLib_Header;

typedef struct _struct_WZLib_File{
	struct _struct_WZLib_Object		inh;
	int					_fileVersion;
	FILE*					_stream;
	struct _struct_WZLib_Directory*		_wzDir;
	const char*				_fileName;
	struct _struct_WZLib_Header*		_header;
}WZLib_File;

WZLib_File*		WZLib_File_Open(const char* name);
void			WZLib_File_Close(WZLib_File* file);
ErrorCode		WZLib_File_Parse(WZLib_File* file);
WZLib_Object*		WZLib_File_Get_n(WZLib_File* file,const char* name);
WZLib_Object*		WZLib_File_Get_i(WZLib_File* file,int i);
int			WZLib_File_GetSize(WZLib_File* file);

typedef struct _struct_WZLib_Directory{
	struct _struct_WZLib_Object		inh;
	struct _struct_WZLib_File*		parentFile;
	struct _struct_LL_Entry*		_firstChild;
}WZLib_Directory;

WZLib_Object*		WZLib_Directory_Get_n(WZLib_Directory* dir,const char* name);
WZLib_Object*		WZLib_Directory_Get_i(WZLib_Directory* dir,int i);
int				WZLib_Directory_GetSize(WZLib_Directory* dir);

typedef struct _struct_WZLib_Image{
	struct _struct_WZLib_Object	inh;
	struct _struct_WZLib_File*	parentFile;
	struct _struct_WZLib_SubProperty*	_sub;
	FILE*				_stream;
}WZLib_Image;

ErrorCode			WZLib_Image_Parse(WZLib_Image* image);
void				WZLib_Image_Unparse(WZLib_Image* image);
struct _struct_WZLib_Property*	WZLib_Image_Get_n(WZLib_Image* image,const char* name);
struct _struct_WZLib_Property*	WZLib_Image_Get_i(WZLib_Image* image,int i);
int				WZLib_Image_GetSize(WZLib_Image* image);
void				WZLib_Image_ResolveUOLs(WZLib_Image* image);

typedef struct _struct_WZLib_Property{
	struct _struct_WZLib_Object	inh;
	struct _struct_WZLib_Image*	parentImg;
	WZLib_PropertyType		propType;
	int		uolD;
}WZLib_Property;

/* deep copy */
WZLib_Property* WZLib_Property_Copy(WZLib_Property* prop);

typedef union _union_WZLib_ValUnion{
	char*	strVal;
	double	dblVal;
	int	intVal;
	int	vecVal[2];
	void*	nullVal;
}WZLib_ValUnion;

typedef struct _struct_WZLib_PrimitiveProperty{
	struct _struct_WZLib_Property	inh;
	WZLib_ValUnion val;
}WZLib_PrimitiveProperty;

struct _struct_WZLib_Property*	WZLib_UOLProperty_Resolve(WZLib_PrimitiveProperty* uolProp);

typedef struct _struct_WZLib_SubProperty{
	struct _struct_WZLib_Property	inh;
	struct _struct_LL_Entry*	_firstChild;
}WZLib_SubProperty;

typedef struct _struct_WZLib_SubProperty WZLib_ConvexProperty;

struct _struct_WZLib_Property*	WZLib_SubProperty_Get_n(WZLib_SubProperty* subProp,const char* name);
struct _struct_WZLib_Property*	WZLib_SubProperty_Get_i(WZLib_SubProperty* subProp,int i);
int				WZLib_SubProperty_GetSize(WZLib_SubProperty* subProp);
void				WZLib_SubProperty_ResolveUOLs(WZLib_SubProperty* subProp);

typedef struct _struct_WZLib_PNGProperty{
	struct _struct_WZLib_Property	inh;
	int				pngParsed;
	int				width;
	int				height;
	int				_format;
	int				_format2;
	int				_length;
	unsigned char*			_compBytes;
	int				_decLen;
	unsigned char*			_decBytes;
	FILE*				_stream;
#	ifdef WZLIB_HAVE_SDL
	SDL_Surface*			png;
#	endif
}WZLib_PNGProperty;

ErrorCode		WZLib_PNGProperty_Parse(WZLib_PNGProperty* pngProp);
void			WZLib_PNGProperty_DisplayFormatAlpha(WZLib_PNGProperty* pngProp);
void			WZLib_PNGProperty_Unparse(WZLib_PNGProperty* pngProp);

typedef struct _struct_WZLib_CanvasProperty{
	struct _struct_WZLib_SubProperty	inh;
	struct _struct_WZLib_PNGProperty*	png;
}WZLib_CanvasProperty;

typedef struct _struct_WZLib_SoundProperty{
	struct _struct_WZLib_Property	inh;
	int				_lenData;
	int				lenMS;
	unsigned char*			_data;
#	ifdef WZLIB_HAVE_SDL
	Mix_Music*			_mus;
#	endif
}WZLib_SoundProperty;

void WZLib_SoundProperty_Play(WZLib_SoundProperty* prop);
void WZLib_SoundProperty_Pause(WZLib_SoundProperty* prop);

#ifdef __cplusplus
}
#endif

#endif
