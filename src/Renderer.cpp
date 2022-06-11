#include "Renderer.h"
#include "Hooks.h"
#include "WaLibc.h"
#include "Debugf.h"

Renderer::CustomGL *(__stdcall *origConstructOpenGlCPU)(int a1, int a2);
Renderer::CustomGL *__stdcall hookConstructOpenGlCPU(int a1, int a2) {
	auto renderer = (Renderer::CustomGL *)WaLibc::waMalloc(sizeof(Renderer::CustomGL));
	memset(renderer, 0, sizeof(Renderer::CustomGL));
	renderer->vtable = (DWORD)&Renderer::CustomGL::vt_hook;
	renderer->dword10 = a1;
	renderer->dword24 = a2;
	return renderer;
}

void Renderer::install() {
	DWORD addrWaMain = _ScanPattern("WaMain", "\x55\x8D\x6C\x24\x88\x83\xEC\x78\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x51\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x53\x56\x8B\x35\x00\x00\x00\x00\x57\x89\x65\xF0\x8B\xF9\x33\xDB\x68\x00\x00\x00\x00", "??????xxxxx????xx????xxxx????xx????x????xxxx????xxxxxxxxx????");

	// always use OpenGL (CPU) as backend
	unsigned char useRendererOpenGlCPU[] = {0xB8, 0x05, 0x00, 0x00, 0x00, 0x90}; // mov eax, 5; nop
	_PatchAsm(addrWaMain + 0x1E5D, (unsigned char*)&useRendererOpenGlCPU, sizeof(useRendererOpenGlCPU));

	DWORD addrConstructOpenGlCPU = (addrWaMain + 0x2020) + *(DWORD*)(addrWaMain + 0x201C);
	DWORD* addrOpenGLCpuVtable = *(DWORD**)(addrConstructOpenGlCPU + 0x2F);

	for(int i = 0; i < CustomGL::vt_original.size(); i++) {
		CustomGL::vt_original[i] = addrOpenGLCpuVtable[i];
	}
	CustomGL::vt_hook[0] = (DWORD)&CustomGL::vt0;
	CustomGL::vt_hook[1] = (DWORD)&CustomGL::vt1;
	CustomGL::vt_hook[2] = (DWORD)&CustomGL::vt2;
	CustomGL::vt_hook[3] = (DWORD)&CustomGL::vt3;
	CustomGL::vt_hook[4] = (DWORD)&CustomGL::vt4;
	CustomGL::vt_hook[5] = (DWORD)&CustomGL::vt5;
	CustomGL::vt_hook[6] = (DWORD)&CustomGL::vt6;
	CustomGL::vt_hook[7] = (DWORD)&CustomGL::vt7;
	CustomGL::vt_hook[8] = (DWORD)&CustomGL::vt8;
	CustomGL::vt_hook[9] = (DWORD)&CustomGL::vt9;
	CustomGL::vt_hook[10] = (DWORD)&CustomGL::vt10;
	CustomGL::vt_hook[11] = (DWORD)&CustomGL::vt11;
	CustomGL::vt_hook[12] = (DWORD)&CustomGL::vt12;
	CustomGL::vt_hook[13] = (DWORD)&CustomGL::vt13;
	CustomGL::vt_hook[14] = (DWORD)&CustomGL::vt14;

	_HookDefault(ConstructOpenGlCPU);
}


DWORD * __fastcall Renderer::CustomGL::vt0(Renderer::CustomGL * This, DWORD *a2, int a3, int a4) {
	auto ret = ((DWORD* (__fastcall *)(Renderer::CustomGL*, DWORD*, int, int))(vt_original[0]))(This, a2, a3, a4);
	debugf("a2: 0x%X a3: %d a4: %d, ret: 0x%X\n", a2, a3, a4, ret);

	//	_DWORD *result; // eax
	//
	//	result = a2;
	//	*(_DWORD *)(a1 + 32) = a4;
	//	*a2 = dword_8AC8BC;
	//	return result;

	return ret;
}

DWORD * __fastcall Renderer::CustomGL::vt1(Renderer::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Renderer::CustomGL*, DWORD*))(vt_original[1]))(This, a2);
	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

	//  _DWORD *v2; // edx
	//  _DWORD *result; // eax
	//
	//  result = v2;
	//  *v2 = dword_8AC8BC;
	//  return result;

	return ret;
}

DWORD * __fastcall Renderer::CustomGL::vt2(Renderer::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Renderer::CustomGL*, DWORD*))(vt_original[2]))(This, a2);
	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

	//  int v3; // eax
	//
	//  v3 = *(_DWORD *)(a1 + 64);
	//  if ( v3 )
	//  {
	//    (*(void (__stdcall **)(int))(*(_DWORD *)v3 + 8))(v3);
	//    *(_DWORD *)(a1 + 64) = 0;
	//    *a2 = dword_8AC8BC;
	//    return a2;
	//  }
	//  else
	//  {
	//    *a2 = dword_8AC8BC;
	//    return a2;
	//  }

	return ret;
}

DWORD * __fastcall Renderer::CustomGL::vt3(Renderer::CustomGL *This, DWORD *a2, DWORD *a3) {
	auto ret = ((DWORD* (__fastcall *)(Renderer::CustomGL*, DWORD*, DWORD*))(vt_original[3]))(This, a2, a3);
	debugf("a2: 0x%X a3: 0x%X, ret: 0x%X\n", a2, a3, ret);

	//  _DWORD *result; // eax
	//
	//  result = a2;
	//  *a3 = *(_DWORD *)(a1 + 44);
	//  a3[1] = *(_DWORD *)(a1 + 48);
	//  *a2 = dword_8AC8BC;
	//  return result;

	return ret;
}

DWORD * __fastcall Renderer::CustomGL::vt4(Renderer::CustomGL *This, DWORD *a2, int a3, void (__stdcall *a4)(DWORD, DWORD, int)) {
	auto ret = ((DWORD* (__fastcall *)(Renderer::CustomGL*, DWORD*, int, void (__stdcall *)(DWORD, DWORD, int)))(vt_original[4]))(This, a2, a3, a4);
	debugf("a2: 0x%X a3: 0x%X a4: 0x%X, ret: 0x%X\n", a2, a3, a4, ret);

	//  DWORD v5; // esi
	//  DEVMODEA DevMode; // [esp+Ch] [ebp-9Ch] BYREF
	//
	//  memset(&DevMode, 0, sizeof(DevMode));
	//  v5 = 0;
	//  DevMode.dmSize = 156;
	//  if ( EnumDisplaySettingsA(0, 0, &DevMode) )
	//  {
	//    do
	//    {
	//      if ( DevMode.dmBitsPerPel == 32 )
	//        a4(DevMode.dmPelsWidth, DevMode.dmPelsHeight, a3);
	//      ++v5;
	//    }
	//    while ( EnumDisplaySettingsA(0, v5, &DevMode) );
	//    *a2 = dword_8AC8BC;
	//    return a2;
	//  }
	//  else
	//  {
	//    *a2 = dword_8AC8BC;
	//    return a2;
	//  }

	return ret;
}

void __fastcall Renderer::CustomGL::vt5(Renderer::CustomGL *This) {
	debugf("...\n");
}

int __fastcall Renderer::CustomGL::vt6(Renderer::CustomGL *This, int a2, int a3, int a4) {
	auto ret = ((int (__fastcall *)(Renderer::CustomGL*, int, int, int))(vt_original[6]))(This, a2, a3, a4);
	debugf("a2: %d a3: %d a4: %d, ret: %d\n", a2, a3, a4, ret);

	// int v4; // edi
	//  int result; // eax
	//  int v8; // eax
	//  int v9; // edi
	//  int v10; // eax
	//  int v11; // edi
	//  GLsizei v12; // ebx
	//  int v13; // ecx
	//  _DWORD *v14; // eax
	//
	//  v4 = cy;
	//  sub_59F000(a1, (int)&cy, width, cy);
	//  if ( cy == dword_8AC8BC )
	//  {
	//    if ( *(_DWORD *)(a1 + 68) )
	//      j__free(*(void **)(a1 + 68));
	//    *(_DWORD *)(a1 + 68) = operator new(4 * v4 * width);
	//    v8 = ((((((((*(_DWORD *)(a1 + 44) - 1) >> 1) | (*(_DWORD *)(a1 + 44) - 1)) >> 2) | ((*(_DWORD *)(a1 + 44) - 1) >> 1) | (*(_DWORD *)(a1 + 44) - 1)) >> 4) | ((((*(_DWORD *)(a1 + 44) - 1) >> 1) | (*(_DWORD *)(a1 + 44) - 1)) >> 2) | ((*(_DWORD *)(a1 + 44) - 1) >> 1) | (*(_DWORD *)(a1 + 44) - 1)) >> 8) | ((((((*(_DWORD *)(a1 + 44) - 1) >> 1) | (*(_DWORD *)(a1 + 44) - 1)) >> 2) | ((*(_DWORD *)(a1 + 44) - 1) >> 1) | (*(_DWORD *)(a1 + 44) - 1)) >> 4) | ((((*(_DWORD *)(a1 + 44) - 1) >> 1) | (*(_DWORD *)(a1 + 44) - 1)) >> 2) | ((*(_DWORD *)(a1 + 44) - 1) >> 1) | (*(_DWORD *)(a1 + 44) - 1);
	//    v9 = v8 | (v8 >> 16);
	//    v10 = ((((((((*(_DWORD *)(a1 + 48) - 1) >> 1) | (*(_DWORD *)(a1 + 48) - 1)) >> 2) | ((*(_DWORD *)(a1 + 48) - 1) >> 1) | (*(_DWORD *)(a1 + 48) - 1)) >> 4) | ((((*(_DWORD *)(a1 + 48) - 1) >> 1) | (*(_DWORD *)(a1 + 48) - 1)) >> 2) | ((*(_DWORD *)(a1 + 48) - 1) >> 1) | (*(_DWORD *)(a1 + 48) - 1)) >> 8) | ((((((*(_DWORD *)(a1 + 48) - 1) >> 1) | (*(_DWORD *)(a1 + 48) - 1)) >> 2) | ((*(_DWORD *)(a1 + 48) - 1) >> 1) | (*(_DWORD *)(a1 + 48) - 1)) >> 4) | ((((*(_DWORD *)(a1 + 48) - 1) >> 1) | (*(_DWORD *)(a1 + 48) - 1)) >> 2) | ((*(_DWORD *)(a1 + 48) - 1) >> 1) | (*(_DWORD *)(a1 + 48) - 1);
	//    v11 = v9 + 1;
	//    v12 = (v10 | (v10 >> 16)) + 1;
	//    *(_DWORD *)(a1 + 52) = 0;
	//    cy = v11;
	//    glGenTextures(1, (GLuint *)(a1 + 52));
	//    if ( glGetError() )
	//    {
	//      (*(void (__fastcall **)(int, int *, _DWORD))(*(_DWORD *)a1 + 28))(a1, &cy, 0);
	//      v13 = dword_8ACE8C;
	//      v14 = (_DWORD *)((char *)&unk_8ACE98 + 12 * (dword_8ACE8C & 0xF));
	//      *(_DWORD *)a2 = v14;
	//      dword_8ACE8C = v13 + 1;
	//      *v14 = 0;
	//      *(_DWORD *)(*(_DWORD *)a2 + 4) = "OpenGL: glGenTextures";
	//      *(_DWORD *)(*(_DWORD *)a2 + 8) = 0;
	//      return a2;
	//    }
	//    else
	//    {
	//      glBindTexture(0xDE1u, *(_DWORD *)(a1 + 52));
	//      if ( glGetError() )
	//      {
	//        (*(void (__fastcall **)(int, int *, _DWORD))(*(_DWORD *)a1 + 28))(a1, &cy, 0);
	//        debug_log_sub_4E3190(a2, (int)"OpenGL: glBindTexture", 0);
	//        return a2;
	//      }
	//      else
	//      {
	//        glTexParameteri(0xDE1u, 0x2801u, 9729);
	//        glTexParameteri(0xDE1u, 0x2800u, 9729);
	//        if ( glGetError() )
	//        {
	//          (*(void (__fastcall **)(int, int *, _DWORD))(*(_DWORD *)a1 + 28))(a1, &cy, 0);
	//          debug_log_sub_4E3190(a2, (int)"OpenGL: glTexParameteri", 0);
	//          return a2;
	//        }
	//        else
	//        {
	//          glTexImage2D(0xDE1u, 0, 32849, v11, v12, 0, 0x80E1u, 0x1401u, 0);
	//          if ( glGetError() )
	//          {
	//            (*(void (__fastcall **)(int, int *, _DWORD))(*(_DWORD *)a1 + 28))(a1, &cy, 0);
	//            debug_log_sub_4E3190(a2, (int)"OpenGL: glTexImage2D", 0);
	//            return a2;
	//          }
	//          else
	//          {
	//            result = a2;
	//            *(float *)(a1 + 56) = (double)*(int *)(a1 + 44) / (double)cy;
	//            *(float *)(a1 + 60) = (double)*(int *)(a1 + 48) / (double)v12;
	//            *(_DWORD *)a2 = dword_8AC8BC;
	//          }
	//        }
	//      }
	//    }
	//  }
	//  else
	//  {
	//    *(_DWORD *)a2 = cy;
	//    return a2;
	//  }
	//  return result;

	return ret;
}

int * __fastcall Renderer::CustomGL::vt7(Renderer::CustomGL *This, int *a2, int a3) {
	auto ret = ((int* (__fastcall *)(Renderer::CustomGL*, int*, int))(vt_original[7]))(This, a2, a3);
	debugf("a2: 0x%X a3: %d, ret: 0x%X\n", a2, a3, ret);

	// sub_59EF80(a1, &a3, a3);
	//  if ( a3 == dword_8AC8BC )
	//  {
	//    if ( *(_DWORD *)(a1 + 68) )
	//    {
	//      j__free(*(void **)(a1 + 68));
	//      *(_DWORD *)(a1 + 68) = 0;
	//    }
	//    *a2 = dword_8AC8BC;
	//    return a2;
	//  }
	//  else
	//  {
	//    *a2 = a3;
	//    return a2;
	//  }

	return ret;
}

DWORD * __fastcall Renderer::CustomGL::vt8(Renderer::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Renderer::CustomGL*, DWORD*))(vt_original[8]))(This, a2);
	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

	//  _DWORD *v2; // edx
	//  _DWORD *v3; // esi
	//  int v5; // [esp+4h] [ebp-4h] BYREF
	//
	//  v3 = v2;
	//  (*(void (__fastcall **)(int, int *, _DWORD))(*(_DWORD *)this + 28))(this, &v5, 0);
	//  if ( v5 == dword_8AC8BC )
	//    *v3 = dword_8AC8BC;
	//  else
	//    *v3 = v5;
	//  return v3;

	return ret;
}

int __fastcall Renderer::CustomGL::vt9(Renderer::CustomGL *This, int a2, int a3, int a4) {
	auto ret = ((int (__fastcall *)(Renderer::CustomGL*, int, int, int))(vt_original[3]))(This, a2, a3, a4);
	debugf("a2: %d a3: %d a4: %d, ret: %d\n", a2, a3, a4, ret);

	//  (*(void (__fastcall **)(int, int, int, int))(*(_DWORD *)a1 + 24))(a1, a2, a3, a4);
	//  return a2;

	return ret;
}
int __fastcall Renderer::CustomGL::vt10(Renderer::CustomGL *This, int a2) {
	auto ret = ((int (__fastcall *)(Renderer::CustomGL*, int))(vt_original[10]))(This, a2);
	debugf("a2: %d, ret: %d\n", a2, ret);

	//  (*(void (__fastcall **)(_DWORD *, int, _DWORD, _DWORD))(*a1 + 24))(a1, a2, a1[11], a1[12]);
	//  return a2;

	return ret;
}

DWORD * __fastcall Renderer::CustomGL::vt11(Renderer::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Renderer::CustomGL*, DWORD*))(vt_original[11]))(This, a2);
	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

	//  _DWORD *result; // eax
	//
	//  result = a2;
	//  *a2 = dword_7C03CC;
	//  return result;

	return ret;
}

int * __fastcall Renderer::CustomGL::vt12(Renderer::CustomGL *This, int a2, unsigned char *a3) {
	auto ret = ((int* (__fastcall *)(Renderer::CustomGL*, int, unsigned char*))(vt_original[12]))(This, a2, a3);
	debugf("a2: %d a3: 0x%X, ret: 0x%X\n", a2, a3, ret);

	//  int v5; // ecx
	//  _DWORD *v6; // eax
	//  int v8; // ecx
	//  _DWORD *v9; // eax
	//  char v10[4]; // [esp+18h] [ebp-404h] BYREF
	//  char v11[1024]; // [esp+1Ch] [ebp-400h] BYREF
	//
	//  if ( glGetError() )
	//  {
	//    (*(void (__fastcall **)(int, char *, _DWORD))(*(_DWORD *)a1 + 28))(a1, v10, 0);
	//    v5 = dword_8ACE8C;
	//    v6 = (_DWORD *)((char *)&unk_8ACE98 + 12 * (dword_8ACE8C & 0xF));
	//    *(_DWORD *)a2 = v6;
	//    dword_8ACE8C = v5 + 1;
	//    *v6 = 0;
	//    *(_DWORD *)(*(_DWORD *)a2 + 4) = "OpenGL: _";
	//    *(_DWORD *)(*(_DWORD *)a2 + 8) = 0;
	//    return a2;
	//  }
	//  else
	//  {
	//    sub_5A1FA0((int)v11, (int)&unk_8AC8C8);
	//    sub_5A2020(
	//      *(_DWORD **)(a1 + 48),
	//      a3,
	//      *(_DWORD *)(a1 + 44),
	//      *(_DWORD *)(a1 + 44),
	//      *(_DWORD **)(a1 + 68),
	//      4 * *(_DWORD *)(a1 + 44),
	//      (int)v11);
	//    glTexSubImage2D(
	//      0xDE1u,
	//      0,
	//      0,
	//      0,
	//      *(_DWORD *)(a1 + 44),
	//      *(_DWORD *)(a1 + 48),
	//      0x80E1u,
	//      0x1401u,
	//      *(const GLvoid **)(a1 + 68));
	//    if ( glGetError() )
	//    {
	//      (*(void (__fastcall **)(int, char *, _DWORD))(*(_DWORD *)a1 + 28))(a1, v10, 0);
	//      v8 = dword_8ACE8C;
	//      v9 = (_DWORD *)((char *)&unk_8ACE98 + 12 * (dword_8ACE8C & 0xF));
	//      *(_DWORD *)a2 = v9;
	//      dword_8ACE8C = v8 + 1;
	//      *v9 = 0;
	//      *(_DWORD *)(*(_DWORD *)a2 + 4) = "OpenGL: glTexSubImage2D";
	//      *(_DWORD *)(*(_DWORD *)a2 + 8) = 0;
	//      return a2;
	//    }
	//    else
	//    {
	//      glBegin(7u);
	//      glTexCoord2f(0.0, *(float *)(a1 + 60));
	//      glVertex2i(0, 0);
	//      glTexCoord2f(*(float *)(a1 + 56), *(float *)(a1 + 60));
	//      glVertex2i(*(_DWORD *)(a1 + 44), 0);
	//      glTexCoord2f(*(float *)(a1 + 56), 0.0);
	//      glVertex2i(*(_DWORD *)(a1 + 44), *(_DWORD *)(a1 + 48));
	//      glTexCoord2f(0.0, 0.0);
	//      glVertex2i(0, *(_DWORD *)(a1 + 48));
	//      glEnd();
	//      if ( glGetError() )
	//      {
	//        (*(void (__fastcall **)(int, char *, _DWORD))(*(_DWORD *)a1 + 28))(a1, v10, 0);
	//        debug_log_sub_4E3190(a2, (int)"OpenGL: GL_QUADS", 0);
	//      }
	//      else
	//      {
	//        *(_DWORD *)a2 = dword_8AC8BC;
	//      }
	//      return a2;
	//    }
	//  }

	return ret;
}

DWORD * __fastcall Renderer::CustomGL::vt13(Renderer::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Renderer::CustomGL*, DWORD*))(vt_original[13]))(This, a2);
	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

	//  sub_5A2100((_DWORD *)a1, *(_DWORD *)(a1 + 44), *(char **)(a1 + 48));
	//  if ( *(_DWORD *)(a1 + 40) )
	//    glFlush();
	//  SwapBuffers(*(HDC *)(a1 + 24));
	//  sub_5A2350((_DWORD *)a1);
	//  *a2 = dword_8AC8BC;
	//  return a2;

	return ret;
}

int __fastcall Renderer::CustomGL::vt14(Renderer::CustomGL *This, int a2) {
	auto ret = ((int (__fastcall *)(Renderer::CustomGL*, int))(vt_original[14]))(This, a2);
	debugf("a2: %d, ret: %d\n", a2, ret);

	//  LPVOID *v2; // esi
	//  int v5; // edi
	//  LPDIRECTDRAW lpDD; // [esp+8h] [ebp-4h] BYREF
	//
	//  v2 = (LPVOID *)(a1 + 64);
	//  if ( !*(_DWORD *)(a1 + 64) )
	//  {
	//    if ( DirectDrawCreate(0, &lpDD, 0) )
	//      return 0;
	//    v5 = lpDD->lpVtbl->QueryInterface(lpDD, &CLSID_IDirectDraw2, v2);
	//    lpDD->lpVtbl->Release(lpDD);
	//    if ( v5 )
	//      return 0;
	//  }
	//  (*(void (__stdcall **)(LPVOID, int))(*(_DWORD *)*v2 + 68))(*v2, a2);
	//  (*(void (__stdcall **)(LPVOID, int))(*(_DWORD *)*v2 + 64))(*v2, a2 + 4);
	//  return 1;

	return ret;
}
