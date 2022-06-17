#include "Backend.h"
#include "Hooks.h"
#include "WaLibc.h"
#include "Debugf.h"
#include <GL/glew.h>
#include <Windows.h>

Backend::CustomGL *(__stdcall *origConstructOpenGlCPU)(int a1, int a2);
Backend::CustomGL *__stdcall hookConstructOpenGlCPU(int a1, int a2) {
	auto renderer = (Backend::CustomGL *)WaLibc::waMalloc(sizeof(Backend::CustomGL));
	memset(renderer, 0, sizeof(Backend::CustomGL));
	renderer->vtable = (DWORD)&Backend::CustomGL::vt_hook;
	renderer->dword10 = a1;
	renderer->dword24 = a2;
	return renderer;
}

Backend::CustomGL *(__stdcall *origConstructOpenGlShader)(int a1, int a2);
Backend::CustomGL *__stdcall hookConstructOpenGlShader(int a1, int a2) {
	auto renderer = (Backend::CustomGL *)WaLibc::waMalloc(sizeof(Backend::CustomGL));
	memset(renderer, 0, sizeof(Backend::CustomGL));
	renderer->vtable = (DWORD)&Backend::CustomGL::vt_hook;
	renderer->dword10 = a1;
	renderer->dword24 = a2;
	return renderer;
}

void Backend::install() {
	DWORD addrWaMain = _ScanPattern("WaMain", "\x55\x8D\x6C\x24\x88\x83\xEC\x78\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x51\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x53\x56\x8B\x35\x00\x00\x00\x00\x57\x89\x65\xF0\x8B\xF9\x33\xDB\x68\x00\x00\x00\x00", "??????xxxxx????xx????xxxx????xx????x????xxxx????xxxxxxxxx????");

	// always use OpenGL (CPU) as backend
	unsigned char useRendererOpenGl[] = {0xB8, 0x05, 0x00, 0x00, 0x00, 0x90}; // mov eax, 5; nop
	_PatchAsm(addrWaMain + 0x1E5D, (unsigned char*)&useRendererOpenGl, sizeof(useRendererOpenGl));

	DWORD addrConstructOpenGlCPU = (addrWaMain + 0x2020) + *(DWORD*)(addrWaMain + 0x201C);
	addrOpenGLCpuVtable = *(DWORD**)(addrConstructOpenGlCPU + 0x2F);

	DWORD addrConstructOpenGlShader = (addrWaMain + 0x2066) + *(DWORD*)(addrWaMain + 0x2062);
	addrOpenGLShaderVtable = *(DWORD**)(addrConstructOpenGlShader + 0x32);
	DWORD * addrOperationsVtable = *(DWORD**)(addrWaMain + 0x2026);
	debugf("addrOpenGLCpuVtable: 0x%X addrOpenGLShaderVtable: 0x%X addrOperationsVtable: 0x%X\n", addrOpenGLCpuVtable, addrOpenGLShaderVtable, addrOperationsVtable);

	for(int i = 0; i < CustomGL::vt_original.size(); i++) {
		CustomGL::vt_original[i] = addrOpenGLCpuVtable[i];
//		CustomGL::vt_original[i] = addrOpenGLShaderVtable[i];
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
	CustomGL::vt_hook[12] = (DWORD) &CustomGL::draw_framebuffer_as_quad_vt12;
	CustomGL::vt_hook[13] = (DWORD) &CustomGL::swap_buffers_vt13;
	CustomGL::vt_hook[14] = (DWORD)&CustomGL::vt14;

	for(int i = 0; i < CustomOperations::vt_original.size(); i++) {
		CustomOperations::vt_original[i] = addrOperationsVtable[i];
	}
	CustomOperations::vt_hook[0] = (DWORD)&CustomOperations::vt0;
	CustomOperations::vt_hook[1] = (DWORD)&CustomOperations::vt1;
	CustomOperations::vt_hook[2] = (DWORD)&CustomOperations::vt2;
	CustomOperations::vt_hook[3] = (DWORD)&CustomOperations::vt3;
	CustomOperations::vt_hook[4] = (DWORD)&CustomOperations::vt4;
	CustomOperations::vt_hook[5] = (DWORD)&CustomOperations::vt5;
	CustomOperations::vt_hook[6] = (DWORD)&CustomOperations::vt6;
	CustomOperations::vt_hook[7] = (DWORD)&CustomOperations::vt7;
	CustomOperations::vt_hook[8] = (DWORD)&CustomOperations::vt8;
	CustomOperations::vt_hook[9] = (DWORD)&CustomOperations::vt9;
	CustomOperations::vt_hook[10] = (DWORD)&CustomOperations::vt10;
	CustomOperations::vt_hook[11] = (DWORD)&CustomOperations::vt11;
	CustomOperations::vt_hook[12] = (DWORD)&CustomOperations::vt12;
	CustomOperations::vt_hook[13] = (DWORD)&CustomOperations::vt13;
	CustomOperations::vt_hook[14] = (DWORD)&CustomOperations::vt14;
	CustomOperations::vt_hook[15] = (DWORD)&CustomOperations::vt15;
	CustomOperations::vt_hook[16] = (DWORD)&CustomOperations::vt16;
	CustomOperations::vt_hook[17] = (DWORD)&CustomOperations::vt17;
	CustomOperations::vt_hook[18] = (DWORD)&CustomOperations::vt18;
	CustomOperations::vt_hook[19] = (DWORD)&CustomOperations::vt19;
	CustomOperations::vt_hook[20] = (DWORD)&CustomOperations::vt20;
	CustomOperations::vt_hook[21] = (DWORD)&CustomOperations::vt21;
	CustomOperations::vt_hook[22] = (DWORD)&CustomOperations::vt22;
	CustomOperations::vt_hook[23] = (DWORD)&CustomOperations::vt23;
	CustomOperations::vt_hook[24] = (DWORD)&CustomOperations::vt24;

	unsigned char hookOperations[] = {0xC7, 0x06, 0x00, 0x00, 0x00, 0x00}; // mov     dword ptr [esi], offset
	*(DWORD**)(&hookOperations[2]) = (DWORD*)&CustomOperations::vt_hook;
	_PatchAsm(addrWaMain + 0x2024, (unsigned char*)&hookOperations, sizeof(hookOperations));


	DWORD * addrBitbucketVtable = *(DWORD**)(addrOperationsVtable[22] + 0x18);
	for(int i = 0; i < CustomBitbucket::vt_original.size(); i++) {
		CustomBitbucket::vt_original[i] = addrBitbucketVtable[i];
	}
	CustomBitbucket::vt_hook[0] = (DWORD)&CustomBitbucket::vt0;
	CustomBitbucket::vt_hook[1] = (DWORD)&CustomBitbucket::vt1;
	CustomBitbucket::vt_hook[2] = (DWORD)&CustomBitbucket::vt2;
	CustomBitbucket::vt_hook[3] = (DWORD)&CustomBitbucket::vt3;
	CustomBitbucket::vt_hook[4] = (DWORD)&CustomBitbucket::vt4;
	CustomBitbucket::vt_hook[5] = (DWORD)&CustomBitbucket::vt5;
	CustomBitbucket::vt_hook[6] = (DWORD)&CustomBitbucket::vt6;
	CustomBitbucket::vt_hook[7] = (DWORD)&CustomBitbucket::vt7;
	CustomBitbucket::vt_hook[8] = (DWORD)&CustomBitbucket::vt8;
	CustomBitbucket::vt_hook[9] = (DWORD)&CustomBitbucket::vt9;
	CustomBitbucket::vt_hook[10] = (DWORD)&CustomBitbucket::vt10;
	CustomBitbucket::vt_hook[11] = (DWORD)&CustomBitbucket::vt11;
	// vtable returned in CustomOperations::vt22

	gl_dword8AC8BC = *(DWORD*)(addrOpenGLCpuVtable[0] + 0xB);
	op_dword8ACCD4 = *(DWORD*)(addrOperationsVtable[3] + 0x19);
	bitbucket_dword8AC8C4 = *(DWORD*)(addrBitbucketVtable[10] + 0x108);
	_HookDefault(ConstructOpenGlCPU);
	_HookDefault(ConstructOpenGlShader);
}


DWORD * __fastcall Backend::CustomGL::vt0(Backend::CustomGL * This, DWORD *a2, int a3, int a4) {
	auto ret = ((DWORD* (__fastcall *)(Backend::CustomGL*, DWORD*, int, int))(vt_original[0]))(This, a2, a3, a4);
//	debugf("a2: 0x%X a3: %d a4: %d, ret: 0x%X\n", a2, a3, a4, ret);

	//	_DWORD *result; // eax
	//
	//	result = a2;
	//	*(_DWORD *)(a1 + 32) = a4;
	//	*a2 = dword_8AC8BC;
	//	return result;

	return ret;
}

DWORD * __fastcall Backend::CustomGL::vt1(Backend::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Backend::CustomGL*, DWORD*))(vt_original[1]))(This, a2);
//	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

	//  _DWORD *v2; // edx
	//  _DWORD *result; // eax
	//
	//  result = v2;
	//  *v2 = dword_8AC8BC;
	//  return result;

	return ret;
}

DWORD * __fastcall Backend::CustomGL::vt2(Backend::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Backend::CustomGL*, DWORD*))(vt_original[2]))(This, a2);
//	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

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

DWORD * __fastcall Backend::CustomGL::vt3(Backend::CustomGL *This, DWORD *a2, DWORD *a3) {
	auto ret = ((DWORD* (__fastcall *)(Backend::CustomGL*, DWORD*, DWORD*))(vt_original[3]))(This, a2, a3);
//	debugf("a2: 0x%X a3: 0x%X, ret: 0x%X\n", a2, a3, ret);

	//  _DWORD *result; // eax
	//
	//  result = a2;
	//  *a3 = *(_DWORD *)(a1 + 44);
	//  a3[1] = *(_DWORD *)(a1 + 48);
	//  *a2 = dword_8AC8BC;
	//  return result;

	return ret;
}

DWORD * __fastcall Backend::CustomGL::vt4(Backend::CustomGL *This, DWORD *a2, int a3, void (__stdcall *a4)(DWORD, DWORD, int)) {
	auto ret = ((DWORD* (__fastcall *)(Backend::CustomGL*, DWORD*, int, void (__stdcall *)(DWORD, DWORD, int)))(vt_original[4]))(This, a2, a3, a4);
//	debugf("a2: 0x%X a3: 0x%X a4: 0x%X, ret: 0x%X\n", a2, a3, a4, ret);

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

void __fastcall Backend::CustomGL::vt5(Backend::CustomGL *This) {
//	debugf("...\n");
}

int __fastcall Backend::CustomGL::vt6(Backend::CustomGL *This, int a2, int a3, int a4) {
	auto ret = ((int (__fastcall *)(Backend::CustomGL*, int, int, int))(vt_original[6]))(This, a2, a3, a4);
//	debugf("a2: %d a3: %d a4: %d, ret: %d\n", a2, a3, a4, ret);
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

int * __fastcall Backend::CustomGL::vt7(Backend::CustomGL *This, int *a2, int a3) {
	auto ret = ((int* (__fastcall *)(Backend::CustomGL*, int*, int))(vt_original[7]))(This, a2, a3);
//	debugf("a2: 0x%X a3: %d, ret: 0x%X\n", a2, a3, ret);

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

DWORD * __fastcall Backend::CustomGL::vt8(Backend::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Backend::CustomGL*, DWORD*))(vt_original[8]))(This, a2);
//	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

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

int __fastcall Backend::CustomGL::vt9(Backend::CustomGL *This, int a2, int a3, int a4) {
	auto ret = ((int (__fastcall *)(Backend::CustomGL*, int, int, int))(vt_original[3]))(This, a2, a3, a4);
//	debugf("a2: %d a3: %d a4: %d, ret: %d\n", a2, a3, a4, ret);

	//  (*(void (__fastcall **)(int, int, int, int))(*(_DWORD *)a1 + 24))(a1, a2, a3, a4);
	//  return a2;

	return ret;
}
int __fastcall Backend::CustomGL::vt10(Backend::CustomGL *This, int a2) {
	auto ret = ((int (__fastcall *)(Backend::CustomGL*, int))(vt_original[10]))(This, a2);
//	debugf("a2: %d, ret: %d\n", a2, ret);

	//  (*(void (__fastcall **)(_DWORD *, int, _DWORD, _DWORD))(*a1 + 24))(a1, a2, a1[11], a1[12]);
	//  return a2;

	return ret;
}

DWORD * __fastcall Backend::CustomGL::vt11(Backend::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Backend::CustomGL*, DWORD*))(vt_original[11]))(This, a2);
//	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

	//  _DWORD *result; // eax
	//
	//  result = a2;
	//  *a2 = dword_7C03CC;
	//  return result;

	return ret;
}

// called from operations_vt13 (0x005A26DA)
int __fastcall Backend::CustomGL::draw_framebuffer_as_quad_vt12(Backend::CustomGL *This, int a2, unsigned char *a3) {

	glEnable(GL_TEXTURE_2D);
//	auto ret = ((int (__fastcall *)(Backend::CustomGL*, int, unsigned char*))(vt_original[12]))(This, a2, a3);
	glDisable(GL_TEXTURE_2D);
	*(DWORD*)a2 = 0;
	return a2;

//	*(DWORD*)a2 = gl_dword8AC8BC;
	//debugf("a2: %d a3: 0x%X, ret: 0x%X\n", a2, a3, ret);

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

//	return ret;
}

DWORD * __fastcall Backend::CustomGL::swap_buffers_vt13(Backend::CustomGL *This, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(Backend::CustomGL*, DWORD*))(vt_original[13]))(This, a2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	SwapBuffers((HDC)This->hdc_dword18);
//	*a2 = gl_dword8AC8BC;
//	return a2;


//	debugf("a2: 0x%X, ret: 0x%X\n", a2, ret);

	//  sub_5A2100((_DWORD *)a1, *(_DWORD *)(a1 + 44), *(char **)(a1 + 48));
	//  if ( *(_DWORD *)(a1 + 40) )
	//    glFlush();
	//  SwapBuffers(*(HDC *)(a1 + 24));
	//  sub_5A2350((_DWORD *)a1);
	//  *a2 = dword_8AC8BC;
	//  return a2;

	return ret;
}

int __fastcall Backend::CustomGL::vt14(Backend::CustomGL *This, int a2) {
	auto ret = ((int (__fastcall *)(Backend::CustomGL*, int))(vt_original[14]))(This, a2);
//	debugf("a2: %d, ret: %d\n", a2, ret);

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

const std::array<DWORD, 15> &Backend::CustomGL::getVtOriginal() {
	return vt_original;
}

const std::array<DWORD, 15> &Backend::CustomGL::getVtHook() {
	return vt_hook;
}

int __fastcall Backend::CustomOperations::vt0(int a1, int a2, int a3, int a4) {
	auto ret = ((int (__fastcall *)(int, int, int, int))(vt_original[0]))(a1, a2, a3, a4);
//	debugf("a1: %d a2: %d a3: %d a4: %d, ret: %d\n", a1, a2, a3, a4, ret);

	//  (***(void (__fastcall ****)(_DWORD, int, int, int))(a1 + 24))(*(_DWORD *)(a1 + 24), a2, a3, a4);
	//  return a2;

	return ret;
}

int __fastcall Backend::CustomOperations::vt1(int a1, int a2) {
	auto ret = ((int (__fastcall *)(int, int))(vt_original[1]))(a1, a2);
//	debugf("a1: %d a2: %d, ret: %d\n", a1, a2, ret);

	//  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(a1 + 24) + 4))(*(_DWORD *)(a1 + 24));
	//  return a2;

	return ret;
}

int __fastcall Backend::CustomOperations::vt2(int a1, int a2) {
	auto ret = ((int (__fastcall *)(int, int))(vt_original[2]))(a1, a2);
//	debugf("a1: %d a2: %d, ret: %d\n", a1, a2, ret);

	//  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(a1 + 24) + 8))(*(_DWORD *)(a1 + 24));
	//  return a2;

	return ret;
}
DWORD* __fastcall Backend::CustomOperations::vt3(int a1, DWORD* a2, DWORD* a3) {
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*, DWORD*))(vt_original[3]))(a1, a2, a3);
//	debugf("a1: %d a2: 0x%X a3: 0x%X, ret: 0x%X\n", a1, a2, a3, ret);

	//  _DWORD *result; // eax
	//
	//  result = a2;
	//  *a3 = dword_7A0EF0;
	//  a3[1] = dword_7A0EF4;
	//  *a2 = dword_8ACCD4;
	//  return result;

	return ret;
}

int __fastcall Backend::CustomOperations::vt4(int a1, int a2, int a3, int a4) {
	auto ret = ((int (__fastcall *)(int, int, int, int))(vt_original[4]))(a1, a2, a3, a4);
//	debugf("a1: %d a2: %d a3: %d a4: %d, ret: %d\n", a1, a2, a3, a4, ret);

	//  (*(void (__fastcall **)(_DWORD, int, int, int))(**(_DWORD **)(a1 + 24) + 16))(*(_DWORD *)(a1 + 24), a2, a3, a4);
	//  return a2;

	return ret;
}

int __fastcall Backend::CustomOperations::vt5(DWORD** a1) {
	auto ret = ((int (__fastcall *)(DWORD**))(vt_original[5]))(a1);
//	debugf("a1: 0x%X, ret: %d\n", a1, ret);

	//  return (*(int (__thiscall **)(_DWORD *))(*this[6] + 20))(this[6]);

	return ret;
}

int __fastcall Backend::CustomOperations::vt6(int* a1, int a2, int a3, int a4) {
	auto ret = ((int (__fastcall *)(int*, int, int, int))(vt_original[6]))(a1, a2, a3, a4);
//	debugf("a1: 0x%X a2: %d a3: %d a4: %d, ret: %d\n", a1, a2, a3, a4, ret);

	//  void *v6; // eax
	//  int v7; // edx
	//  void (__thiscall *v8)(int *); // eax
	//  char v10[4]; // [esp+10h] [ebp-4h] BYREF
	//
	//  if ( dword_7A0EEC )
	//    (*(void (__fastcall **)(int *, char *, _DWORD))(*a1 + 28))(a1, v10, 0);
	//  v6 = operator new(a4 * a3);
	//  v7 = *a1;
	//  dword_7A0EEC = v6;
	//  v8 = *(void (__thiscall **)(int *))(v7 + 80);
	//  dword_7A0EF0 = a3;
	//  dword_7A0EF4 = a4;
	//  v8(a1);
	//  (*(void (__fastcall **)(int, int, int, int))(*(_DWORD *)a1[6] + 24))(a1[6], a2, a3, a4);
	//  return a2;

	return ret;
}

DWORD* __fastcall Backend::CustomOperations::vt7(int a1, DWORD * a2, int a3) {
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*, int))(vt_original[7]))(a1, a2, a3);
//	debugf("a1: %d a2: 0x%X a3: %d, ret: %d\n", a1, a2, a3, ret);

	//  (*(void (__fastcall **)(_DWORD, _DWORD *, int))(**(_DWORD **)(a1 + 24) + 28))(*(_DWORD *)(a1 + 24), a2, a3);
	//  if ( *a2 == dword_8ACCD4 )
	//  {
	//    j__free(dword_7A0EEC);
	//    dword_7A0EEC = 0;
	//    dword_7A0EF0 = 0;
	//    dword_7A0EF4 = 0;
	//  }
	//  return a2;

	return ret;
}

int __fastcall Backend::CustomOperations::vt8(int a1, int a2) {
	auto ret = ((int (__fastcall *)(int, int))(vt_original[8]))(a1, a2);
//	debugf("a1: %d a2: %d, ret: %d\n", a1, a2, ret);

	//  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(a1 + 24) + 32))(*(_DWORD *)(a1 + 24));
	//  return a2;

	return ret;
}

int __fastcall Backend::CustomOperations::vt9(int *a1, int a2, int a3, int a4) {
	auto ret = ((int (__fastcall *)(int*, int, int, int))(vt_original[9]))(a1, a2, a3, a4);
//	debugf("a1: 0x%X a2: %d a3: %d a4: %d, ret: %d\n", a1, a2, a3, a4, ret);

	//  void *v6; // eax
	//  int v7; // edx
	//  void (__thiscall *v8)(int *); // eax
	//
	//  if ( dword_7A0EF0 != a3 || dword_7A0EF4 != a4 || !dword_7A0EEC )
	//  {
	//    j__free(dword_7A0EEC);
	//    v6 = operator new(a4 * a3);
	//    v7 = *a1;
	//    dword_7A0EEC = v6;
	//    v8 = *(void (__thiscall **)(int *))(v7 + 80);
	//    dword_7A0EF0 = a3;
	//    dword_7A0EF4 = a4;
	//    v8(a1);
	//  }
	//  (*(void (__fastcall **)(int, int, int, int))(*(_DWORD *)a1[6] + 36))(a1[6], a2, a3, a4);
	//  return a2;

	return ret;
}

int __fastcall Backend::CustomOperations::vt10(int a1, int a2) {
	auto ret = ((int (__fastcall *)(int, int))(vt_original[10]))(a1, a2);
//	debugf("a1: %d a2: %d, ret: %d\n", a1, a2, ret);

	//  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(a1 + 24) + 40))(*(_DWORD *)(a1 + 24));
	//  return a2;

	return ret;
}

int __fastcall Backend::CustomOperations::vt11(int a1, int a2) {
	auto ret = ((int (__fastcall *)(int, int))(vt_original[11]))(a1, a2);
//	debugf("a1: %d a2: %d, ret: %d\n", a1, a2, ret);

	//  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(a1 + 24) + 44))(*(_DWORD *)(a1 + 24));
	//  return a2;

	return ret;
}

DWORD* __fastcall Backend::CustomOperations::vt12(int a1, DWORD* a2, int a3) {
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*, int))(vt_original[12]))(a1, a2, a3);
//	debugf("a1: %d a2: 0x%X a3: %d, ret: 0x%X\n", a1, a2, a3, ret);

	//  _DWORD *result; // eax
	//  _DWORD *v4; // ecx
	//
	//  result = a2;
	//  v4 = (_DWORD *)((char *)&unk_8ACE98 + 12 * (dword_8ACE8C++ & 0xF));
	//  *a2 = v4;
	//  *v4 = 2101;
	//  v4[1] = 0;
	//  v4[2] = 0;
	//  return result;

	return ret;
}

// called from 0x00403B9E
DWORD* __fastcall Backend::CustomOperations::vt13(int a1, DWORD* a2) {
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*))(vt_original[13]))(a1, a2);
//	debugf("a1: %d a2: 0x%X, ret: 0x%X\n", a1, a2, ret);

	//  int v5; // [esp+8h] [ebp-4h] BYREF
	//
	//  (*(void (__fastcall **)(_DWORD, int *, void *))(**(_DWORD **)(a1 + 24) + 48))(*(_DWORD *)(a1 + 24), &v5, dword_7A0EEC);
	//  if ( v5 )
	//    *a2 = v5;
	//  else
	//    (*(void (__fastcall **)(_DWORD, _DWORD *))(**(_DWORD **)(a1 + 24) + 52))(*(_DWORD *)(a1 + 24), a2);
	//  return a2;

	return ret;
}

int __fastcall Backend::CustomOperations::vt14() {
	auto ret = ((int (__fastcall *)())(vt_original[14]))();
//	debugf("ret: %d\n", ret);

	//  return 0;

	return ret;
}

DWORD* __fastcall Backend::CustomOperations::vt15(int a1, DWORD* a2, DWORD* a3, DWORD* a4) {
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*, DWORD*, DWORD*))(vt_original[15]))(a1, a2, a3, a4);
//	debugf("a1: %d a2: 0x%X a3: 0x%X a4: 0x%X, ret: 0x%X\n", a1, a2, a3, a4, ret);

	//  _DWORD *result; // eax
	//
	//  result = a2;
	//  *a3 = dword_7A0EEC;
	//  *a4 = dword_7A0EF0;
	//  *a2 = dword_8ACCD4;
	//  return result;

	return ret;
}

DWORD* __fastcall Backend::CustomOperations::vt16(int a1, DWORD* a2, int a3) {
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*, int))(vt_original[16]))(a1, a2, a3);
//	debugf("a1: %d a2: 0x%X a3: %d, ret: 0x%X\n", a1, a2, a3, ret);

	//  _DWORD *result; // eax
	//
	//  result = a2;
	//  *a2 = dword_8ACCD4;
	//  return result;

	return ret;
}

DWORD* __fastcall Backend::CustomOperations::vt17(int a1, DWORD* a2, DWORD* a3, DWORD* a4) {
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*, DWORD*, DWORD*))(vt_original[17]))(a1, a2, a3, a4);
//	debugf("a1: %d a2: 0x%X a3: 0x%X a4: 0x%X, ret: 0x%X\n", a1, a2, a3, a4, ret);

	//  _DWORD *result; // eax
	//
	//  result = a2;
	//  *a3 = dword_7A0EEC;
	//  *a4 = dword_7A0EF0;
	//  *a2 = dword_8ACCD4;
	//  return result;

	return ret;
}

DWORD* __fastcall Backend::CustomOperations::vt18(int a1, DWORD* a2, int a3) {
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*, int))(vt_original[18]))(a1, a2, a3);
//	debugf("a1: %d a2: 0x%X a3: %d, ret: 0x%X\n", a1, a2, a3, ret);

	//  _DWORD *result; // eax
	//
	//  result = a2;
	//  *a2 = dword_8ACCD4;
	//  return result;

	return ret;
}

DWORD* __fastcall Backend::CustomOperations::vt19(int a1, DWORD* a2, int a3, int a4, int a5, int a6, int a7) {
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*, int, int, int, int, int))(vt_original[19]))(a1, a2, a3, a4, a5, a6, a7);
//	debugf("a1: %d a2: 0x%X a3: %d a4: %d, a5: %d a6: %d a7: %d ret: 0x%X\n", a1, a2, a3, a4, a5, a6, a7, ret);

	//  int v7; // ebx
	//  void (__fastcall *v8)(int, _DWORD *, int *, int *); // eax
	//  _DWORD *v9; // ebp
	//  char *v10; // esi
	//  int v11; // ebx
	//  size_t v12; // ebp
	//  int v13; // edi
	//  int v15; // [esp+Ch] [ebp-10h] BYREF
	//  int v16; // [esp+10h] [ebp-Ch] BYREF
	//  int v17; // [esp+14h] [ebp-8h]
	//  _DWORD *v18; // [esp+18h] [ebp-4h]
	//
	//  v7 = a1;
	//  v8 = *(void (__fastcall **)(int, _DWORD *, int *, int *))(*(_DWORD *)a1 + 68);
	//  v9 = a2;
	//  v18 = a2;
	//  v17 = a1;
	//  v16 = 0;
	//  v15 = 0;
	//  v8(a1, a2, &v16, &v15);
	//  if ( *v9 == dword_8ACCD4 )
	//  {
	//    v10 = (char *)(a3 + v16 + a4 * v15);
	//    if ( a6 > 0 )
	//    {
	//      v11 = Val;
	//      v12 = Size;
	//      v13 = a6;
	//      do
	//      {
	//        memset(v10, v11, v12);
	//        v10 += v15;
	//        --v13;
	//      }
	//      while ( v13 );
	//      v7 = v17;
	//      v9 = v18;
	//    }
	//    (*(void (__fastcall **)(int, int *, int))(*(_DWORD *)v7 + 72))(v7, &a4, v16);
	//  }
	//  return v9;

	return ret;
}

void* __fastcall Backend::CustomOperations::vt20() {
	auto ret = ((void* (__fastcall *)())(vt_original[20]))();
//	debugf("ret: 0x%X\n", ret);

	// void *result; // eax
	//
	//  if ( dword_7A0EF0 > 0 )
	//  {
	//    result = (void *)dword_7A0EF4;
	//    if ( dword_7A0EF4 > 0 )
	//      return memset(dword_7A0EEC, 0, dword_7A0EF0 * dword_7A0EF4);
	//  }
	//  return result;

	return ret;
}

int __fastcall Backend::CustomOperations::vt21(int a1) {
	auto ret = ((int (__fastcall *)(int))(vt_original[21]))(a1);
//	debugf("a1: %d, ret: %d\n", a1, ret);

	//  return (*(int (__thiscall **)(void *))(*(_DWORD *)this + 80))(this);

	return ret;
}

Backend::CustomBitbucket* __fastcall Backend::CustomOperations::vt22() {
	CustomBitbucket *bucket = (CustomBitbucket*)WaLibc::waMalloc(sizeof(CustomBitbucket));
	if(!bucket) return 0;

	bucket->dword0 = (DWORD)&CustomBitbucket::vt_hook;
	bucket->dword4 = 0;
	bucket->dword8 = 0;
	bucket->dwordC = 0;
	bucket->dword10 = 0;
	return bucket;

	//auto ret = ((DWORD* (__fastcall *)())(vt_original[22]))();
//	debugf("ret: 0x%X\n", ret);
	// return ret;

	//  _DWORD *result; // eax
	//
	//  result = operator new(0x14u);
	//  if ( !result )
	//    return 0;
	//  result[1] = 0;
	//  result[2] = 0;
	//  *result = &bitbucket_off_677570;
	//  result[3] = 0;
	//  *((_BYTE *)result + 16) = 0;
	//  return result;
}

DWORD* __fastcall Backend::CustomOperations::vt23(int a1, DWORD* a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, char a10) {
//	*a2 = op_dword8ACCD4;
//	return a2;
//	DWORD * ret;
	auto ret = ((DWORD* (__fastcall *)(int, DWORD*, int, int, int, int, int, int, int, char))(vt_original[23]))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
//	debugf("a1: %d a2: 0x%X a3: %d a4: %d, a5: %d, a6: %d, a7: %d, a8: %d, a9: %d, a10: %d, ret: 0x%X\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ret);

	//  int v12; // eax
	//  int v13; // esi
	//  signed int v14; // ebx
	//  int v15; // edx
	//  _BYTE *v16; // eax
	//  _BYTE *v17; // esi
	//  _BYTE *v18; // edi
	//  signed int v19; // eax
	//  _BYTE *v20; // edx
	//  _DWORD *v21; // esi
	//  int v23; // ecx
	//  _DWORD *v24; // eax
	//  int v25; // [esp+10h] [ebp-38h] BYREF
	//  int v26; // [esp+14h] [ebp-34h] BYREF
	//  int v27; // [esp+18h] [ebp-30h] BYREF
	//  int v28; // [esp+1Ch] [ebp-2Ch] BYREF
	//  int v29; // [esp+20h] [ebp-28h]
	//  _DWORD *v30; // [esp+24h] [ebp-24h] BYREF
	//  int v31; // [esp+28h] [ebp-20h] BYREF
	//  int v32; // [esp+2Ch] [ebp-1Ch]
	//  int v33; // [esp+30h] [ebp-18h]
	//  int v34; // [esp+34h] [ebp-14h]
	//  int v35; // [esp+44h] [ebp-4h]
	//
	//  v30 = a2;
	//  v29 = a1;
	//  sub_5A0E20(a3, &v31);
	//  v35 = 0;
	//  if ( v34 )
	//  {
	//    *a2 = v34;
	//    goto LABEL_36;
	//  }
	//  if ( !a1 || (v12 = v32) == 0 )
	//  {
	//    v23 = dword_8ACE8C + 1;
	//    v24 = (_DWORD *)((char *)&unk_8ACE98 + 12 * (dword_8ACE8C & 0xF));
	//    *a2 = v24;
	//    dword_8ACE8C = v23;
	//    *v24 = 2090;
	//    *(_DWORD *)(*a2 + 4) = 0;
	//    *(_DWORD *)(*a2 + 8) = 0;
	//LABEL_36:
	//    v35 = -1;
	//    v12 = v32;
	//    if ( v32 )
	//      goto LABEL_37;
	//    return a2;
	//  }
	//  if ( a4 >= dword_7A0EF0 )
	//  {
	//    *a2 = dword_8ACCD4;
	//    v35 = -1;
	//LABEL_37:
	//    (*(void (__fastcall **)(int, _DWORD **, int))(*(_DWORD *)v31 + 8))(v31, &v30, v12);
	//    return a2;
	//  }
	//  v13 = a5;
	//  if ( a5 >= dword_7A0EF4 )
	//  {
	//    *a2 = dword_8ACCD4;
	//LABEL_9:
	//    v35 = -1;
	//    sub_5A0E90(&v31);
	//    return a2;
	//  }
	//  if ( dword_8ACCD4 != *(_DWORD *)(*(int (__fastcall **)(int, int *, int *, int *))(*(_DWORD *)a1 + 68))(
	//                                    a1,
	//                                    &v27,
	//                                    &v26,
	//                                    &v28) )
	//  {
	//    sub_427180((int)a2, 2094, 0, 0);
	//    goto LABEL_9;
	//  }
	//  v14 = a8;
	//  if ( a4 >= 0 )
	//  {
	//    v15 = a4;
	//  }
	//  else
	//  {
	//    a6 -= a4;
	//    v14 = a4 + a8;
	//    a8 += a4;
	//    v15 = 0;
	//  }
	//  if ( a5 < 0 )
	//  {
	//    a7 -= a5;
	//    a9 += a5;
	//    v13 = 0;
	//  }
	//  if ( v15 + v14 > dword_7A0EF0 )
	//  {
	//    v14 = dword_7A0EF0 - v15;
	//    a8 = dword_7A0EF0 - v15;
	//  }
	//  if ( v13 + a9 > dword_7A0EF4 )
	//    a9 = dword_7A0EF4 - v13;
	//  if ( v14 <= 0 || a9 <= 0 )
	//  {
	//    *a2 = dword_8ACCD4;
	//    goto LABEL_9;
	//  }
	//  v16 = (_BYTE *)(v15 + v26 + v13 * dword_7A0EF0);
	//  v17 = (_BYTE *)(a6 + v32 + a7 * v33);
	//  v18 = v16;
	//  if ( (a10 & 2) != 0 )
	//  {
	//    (*(void (__fastcall **)(int, int *, int *, int))(*(_DWORD *)a3 + 32))(a3, &v25, &v27, 16);
	//    v25 = a9;
	//    do
	//    {
	//      v19 = 0;
	//      v20 = v17;
	//      if ( v14 > 0 )
	//      {
	//        do
	//        {
	//          if ( (unsigned __int8)*v20 != v27 )
	//            v18[v19] = *v20;
	//          v14 = a8;
	//          ++v19;
	//          ++v20;
	//        }
	//        while ( v19 < a8 );
	//      }
	//      v18 += dword_7A0EF0;
	//      v17 += v33;
	//      --v25;
	//    }
	//    while ( v25 );
	//  }
	//  else
	//  {
	//    v25 = a9;
	//    do
	//    {
	//      memcpy_0(v18, v17, v14);
	//      v18 += v28;
	//      v17 += v33;
	//      --v25;
	//    }
	//    while ( v25 );
	//  }
	//  (*(void (__fastcall **)(int, int *, int))(*(_DWORD *)v29 + 72))(v29, &v27, v26);
	//  v21 = v30;
	//  *v30 = dword_8ACCD4;
	//  v35 = -1;
	//  sub_5A0E90(&v31);
	//  return v21;

	return ret;
}

int* __fastcall Backend::CustomOperations::vt24(int a1, int* a2, int a3, int a4) {
	auto ret = ((int* (__fastcall *)(int, int*, int, int))(vt_original[24]))(a1, a2, a3, a4);
//	debugf("a1: %d a2: 0x%X a3: %d a4: %d, ret: 0x%X\n", a1, a2, a3, a4, ret);

	//  int v4; // eax
	//  int v5; // ebx
	//  int *v6; // esi
	//  int v7; // ecx
	//  int v8; // edi
	//  int v9; // esi
	//  int v10; // edi
	//  char *v11; // eax
	//  int v14; // [esp+14h] [ebp-2Ch]
	//  int v15; // [esp+18h] [ebp-28h] BYREF
	//  char v16[4]; // [esp+1Ch] [ebp-24h] BYREF
	//  int v17; // [esp+20h] [ebp-20h] BYREF
	//  int v18; // [esp+24h] [ebp-1Ch]
	//  int v19; // [esp+2Ch] [ebp-14h]
	//  int v20; // [esp+3Ch] [ebp-4h]
	//
	//  v4 = *(_DWORD *)(a3 + 8);
	//  v5 = *(_DWORD *)(a3 + 4);
	//  v15 = a1;
	//  v14 = v4;
	//  sub_5A0E20(a3, &v17);
	//  if ( v19 )
	//  {
	//    v6 = a2;
	//    *a2 = v19;
	//    v20 = -1;
	//    if ( v18 )
	//      (*(void (__fastcall **)(int, int *, int))(*(_DWORD *)v17 + 8))(v17, &v15, v18);
	//  }
	//  else if ( ((unsigned __int8)dword_7A0EEC & 7) != 0
	//         || (v18 & 7) != 0
	//         || dword_7A0EF0 % 8
	//         || v5 != 8 && v5 != 32 && v5 != 64 )
	//  {
	//    v20 = -1;
	//    if ( v18 )
	//      (*(void (__fastcall **)(int, char *, int))(*(_DWORD *)v17 + 8))(v17, v16, v18);
	//    v6 = a2;
	//    sub_5A2080(v15, a2, a3, a4);
	//  }
	//  else
	//  {
	//    v7 = 0;
	//    v8 = a4 + v14;
	//    v9 = a4;
	//    if ( a4 < 0 )
	//    {
	//      v7 = -a4;
	//      v9 = 0;
	//    }
	//    if ( v8 >= dword_7A0EF4 )
	//      v8 = dword_7A0EF4;
	//    v10 = v8 - v9;
	//    if ( v10 > 0 )
	//    {
	//      v11 = (char *)dword_7A0EEC + v9 * dword_7A0EF0;
	//      if ( v5 == 8 )
	//      {
	//        sub_5A2D50((int)v11, (void *)(v18 + 8 * v7), v10);
	//      }
	//      else if ( v5 == 32 )
	//      {
	//        sub_5A2E00((int)v11, (void *)(v18 + 32 * v7), v10);
	//      }
	//      else
	//      {
	//        sub_5A2EC0((int)v11, (void *)(v18 + v5 * v7), v10);
	//      }
	//    }
	//    v6 = a2;
	//    *a2 = dword_8ACCD4;
	//    v20 = -1;
	//    sub_5A0E90(&v17);
	//  }
	//  return v6;

	return ret;
}

const std::array<DWORD, 25> &Backend::CustomOperations::getVtOriginal() {
	return vt_original;
}

const std::array<DWORD, 25> &Backend::CustomOperations::getVtHook() {
	return vt_hook;
}

Backend::CustomBitbucket *Backend::CustomBitbucket::vt0(Backend::CustomBitbucket *a1, int EDX, char a2) {
	auto ret = ((CustomBitbucket* (__fastcall *)(CustomBitbucket*, int, char))(vt_original[0]))(a1, EDX, a2);
//	debugf("a1: 0x%X a2: %d, ret: 0x%X\n", a1, a2, ret);

	//  void *dwordC; // [esp-4h] [ebp-8h]
	//
	//  dwordC = (void *)Block->dwordC;
	//  Block->dword0 = &bitbucket_off_677570;
	//  j__free(dwordC);
	//  Block->dwordC = 0;
	//  Block->dword4 = 0;
	//  Block->dword8 = 0;
	//  Block->dword0 = &off_676A5C;
	//  if ( (a2 & 1) != 0 )
	//    j__free(Block);
	//  return Block;

	return ret;
}

int Backend::CustomBitbucket::vt1(Backend::CustomBitbucket *a1, int a2, DWORD *a3, int a4) {
	auto ret = ((int (__fastcall *)(CustomBitbucket*, int, DWORD*, int))(vt_original[1]))(a1, a2, a3, a4);
//	debugf("a1: 0x%X a2: %d, a3: 0x%X a4: %d ret: %d\n", a1, a2, a3, a4, ret);

	//   (*(void (__fastcall **)(BitBucket *, int, int *, int))(a1->dword0 + 12))(a1, a2, &a4, a4);
	//  if ( a3 )
	//    *a3 = a4;
	//  return a2;

	return ret;
}

DWORD *Backend::CustomBitbucket::vt2(CustomBitbucket* a1, DWORD *a2, int a3) {
	auto ret = ((DWORD* (__fastcall *)(CustomBitbucket*, DWORD*, int))(vt_original[2]))(a1, a2, a3);
//	debugf("a1: 0x%X a2: 0x%X, a3: %d, ret: 0x%X\n", a1, a2, a3, ret);

	//   _DWORD *result; // eax
	//
	//  result = a2;
	//  *a2 = dword_8ACCD4;
	//  return result;

	return ret;
}

DWORD *Backend::CustomBitbucket::vt3(Backend::CustomBitbucket *a1, DWORD *a2, DWORD *a3, DWORD *a4) {
	auto ret = ((DWORD* (__fastcall *)(CustomBitbucket*, DWORD*, DWORD*, DWORD*))(vt_original[3]))(a1, a2, a3, a4);
//	debugf("a1: 0x%X a2: 0x%X, a3: 0x%X a4: 0x%X, ret: 0x%X\n", a1, a2, a3, a4, ret);

	//   _DWORD *result; // eax
	//  _DWORD *v5; // ecx
	//  int v6; // edx
	//
	//  result = a2;
	//  if ( a4 )
	//    *a4 = a1->dword4;
	//  if ( a3 )
	//    *a3 = a1->dwordC;
	//  if ( a1->dwordC )
	//  {
	//    *a2 = dword_8ACCD4;
	//  }
	//  else
	//  {
	//    v5 = (_DWORD *)((char *)&unk_8ACE98 + 12 * (dword_8ACE8C & 0xF));
	//    v6 = dword_8ACE8C + 1;
	//    *result = v5;
	//    dword_8ACE8C = v6;
	//    *v5 = 2090;
	//    v5[1] = 0;
	//    v5[2] = 0;
	//  }
	//  return result;

	return ret;
}

DWORD *Backend::CustomBitbucket::vt4(Backend::CustomBitbucket* a1, DWORD *a2, int a3) {
	auto ret = ((DWORD* (__fastcall *)(CustomBitbucket*, DWORD*, int))(vt_original[4]))(a1, a2, a3);
//	debugf("a1: 0x%X a2: 0x%X, a3: %d, ret: 0x%X\n", a1, a2, a3, ret);

	//   _DWORD *result; // eax
	//
	//  result = a2;
	//  *a2 = dword_8ACCD4;
	//  return result;

	return ret;
}

DWORD *Backend::CustomBitbucket::vt5(Backend::CustomBitbucket *a1, DWORD *a2, int a3, int a4, int a5) {
	auto ret = ((DWORD* (__fastcall *)(CustomBitbucket*, DWORD*, int, int, int))(vt_original[5]))(a1, a2, a3, a4, a5);
//	debugf("a1: 0x%X a2: 0x%X, a3: %d a4: %d, a5: %d, ret: 0x%X\n", a1, a2, a3, a4, a5, ret);

	//   char v8[4]; // [esp+10h] [ebp-4h] BYREF
	//
	//  (*(void (__fastcall **)(BitBucket *, char *))(a1->dword0 + 24))(a1, v8);
	//  a1->dwordC = operator new(a4 * a3);
	//  a1->dword4 = a3;
	//  a1->dword8 = a4;
	//  *a2 = dword_8ACCD4;
	//  return a2;

	return ret;
}

DWORD *Backend::CustomBitbucket::vt6(Backend::CustomBitbucket *a1, DWORD *a2) {
	auto ret = ((DWORD* (__fastcall *)(CustomBitbucket*, DWORD*))(vt_original[6]))(a1, a2);
//	debugf("a1: 0x%X a2: 0x%X, ret: 0x%X\n", a1, a2, ret);

	//   j__free((void *)a1->dwordC);
	//  a1->dwordC = 0;
	//  a1->dword4 = 0;
	//  a1->dword8 = 0;
	//  *a2 = dword_8ACCD4;
	//  return a2;

	return ret;
}

DWORD *Backend::CustomBitbucket::vt7(Backend::CustomBitbucket *a1, DWORD *a2, char a3, int a4) {
	auto ret = ((DWORD* (__fastcall *)(CustomBitbucket*, DWORD*, char, int))(vt_original[7]))(a1, a2, a3, a4);
//	debugf("a1: 0x%X a2: 0x%X, a3: %d a4: %d, ret: 0x%X\n", a1, a2, a3, a4, ret);

	//   _DWORD *result; // eax
	//
	//  result = a2;
	//  LOBYTE(a1->dword10) = a3;
	//  *a2 = dword_8ACCD4;
	//  return result;

	return ret;
}

DWORD *Backend::CustomBitbucket::vt8(Backend::CustomBitbucket *a1, DWORD *a2, DWORD *a3, int a4) {
	auto ret = ((DWORD* (__fastcall *)(CustomBitbucket*, DWORD*, DWORD*, int))(vt_original[8]))(a1, a2, a3, a4);
//	debugf("a1: 0x%X a2: 0x%X, a3: 0x%X a4: %d, ret: 0x%X\n", a1, a2, a3, a4, ret);

	//   _DWORD *result; // eax
	//
	//  result = a2;
	//  *a3 = LOBYTE(a1->dword10);
	//  *a2 = dword_8ACCD4;
	//  return result;

	return ret;
}

char Backend::CustomBitbucket::vt9() {
//	debugf("...\n");
	return 0;
}

DWORD *Backend::CustomBitbucket::vt10(Backend::CustomBitbucket *a1, DWORD *a2, int a3, int a4, size_t a5, int a6, int a7) {
	auto ret = ((DWORD* (__fastcall *)(CustomBitbucket*, DWORD*, int, int, size_t, int, int))(vt_original[10]))(a1, a2, a3, a4, a5, a6, a7);
//	debugf("a1: 0x%X a2: 0x%X, a3: %d a4: %d, a5: %d, a6: %d a7: %d ret: 0x%X\n", a1, a2, a3, a4, a5, a6, a7, ret);

	//  int v10; // eax
	//  signed int v11; // edi
	//  int v12; // edx
	//  int v13; // ecx
	//  int dword4; // esi
	//  int dword8; // eax
	//  char *v16; // esi
	//  int v17; // ebx
	//  _DWORD *v18; // esi
	//  int v19; // eax
	//  char *v20; // edx
	//  bool v21; // zf
	//  _DWORD *v22; // [esp+10h] [ebp-28h] BYREF
	//  char v23; // [esp+14h] [ebp-24h] BYREF
	//  int v24; // [esp+18h] [ebp-20h] BYREF
	//  int v25; // [esp+1Ch] [ebp-1Ch]
	//  int v26; // [esp+20h] [ebp-18h]
	//  int v27; // [esp+24h] [ebp-14h]
	//  int v28; // [esp+34h] [ebp-4h]
	//
	//  v22 = a2;
	//  sub_5A0EB0((int)a1, &v24);
	//  if ( !v27 )
	//  {
	//    v10 = a3;
	//    v11 = Size;
	//    if ( a3 < 0 )
	//    {
	//      v11 = a3 + Size;
	//      v10 = 0;
	//      a3 = 0;
	//    }
	//    v12 = a4;
	//    v13 = a6;
	//    if ( a4 < 0 )
	//    {
	//      v13 = a4 + a6;
	//      v12 = 0;
	//    }
	//    dword4 = a1->dword4;
	//    if ( v11 + v10 > dword4 )
	//      v11 = dword4 - a3;
	//    dword8 = a1->dword8;
	//    if ( v12 + v13 > dword8 )
	//      v13 = dword8 - v12;
	//    if ( v11 <= 0 || v13 <= 0 )
	//    {
	//      v18 = v22;
	//      v28 = -1;
	//      v19 = v25;
	//      v21 = v25 == 0;
	//      *v22 = dword_8AC8C4;
	//      if ( v21 )
	//        return v18;
	//      v20 = (char *)&v22;
	//    }
	//    else
	//    {
	//      if ( a3 || v11 != dword4 )
	//      {
	//        v16 = (char *)(v25 + v12 * v26);
	//        v17 = v13;
	//        do
	//        {
	//          memset(v16, Val, v11);
	//          v16 += v26;
	//          --v17;
	//        }
	//        while ( v17 );
	//      }
	//      else
	//      {
	//        memset((void *)(v25 + v12 * v26), Val, v13 * v26);
	//      }
	//      v18 = v22;
	//      *v22 = dword_8AC8C4;
	//      v28 = -1;
	//      v19 = v25;
	//      if ( !v25 )
	//        return v18;
	//      v20 = &v23;
	//    }
	//    (*(void (__fastcall **)(int, char *, int))(*(_DWORD *)v24 + 16))(v24, v20, v19);
	//    return v18;
	//  }
	//  *a2 = v27;
	//  v28 = -1;
	//  if ( v25 )
	//    (*(void (__fastcall **)(int, _DWORD **, int))(*(_DWORD *)v24 + 16))(v24, &v22, v25);
	//  return a2;

	return ret;
}

DWORD *Backend::CustomBitbucket::vt11(Backend::CustomBitbucket *a1, int *a2, int a3, int a4, int a5, int a6, int a7, size_t a8, int a9, int a10) {
//	*a2 = op_dword8ACCD4;
//	return (DWORD*)a2;
	auto ret = ((DWORD* (__fastcall *)(CustomBitbucket*, int*, int a3, int a4, int, int, int, size_t, int, int))(vt_original[11]))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
//	debugf("a1: 0x%X a2: 0x%X, a3: %d a4: %d, a5: %d, a6: %d, a7: %d, a8: %d, a9: %d, a10: %d ret: 0x%X\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ret);

	//  int v12; // edx
	//  signed int v13; // ebx
	//  int v14; // esi
	//  int v15; // edi
	//  int dword4; // eax
	//  int dword8; // eax
	//  int v18; // eax
	//  int v19; // eax
	//  char *v20; // edi
	//  char *v21; // esi
	//  int v22; // eax
	//  int *v23; // esi
	//  signed int v24; // ecx
	//  char *v25; // eax
	//  bool v26; // zf
	//  int v27; // eax
	//  int v28; // eax
	//  int *v29; // edx
	//  int v30; // eax
	//  char *v33; // [esp+18h] [ebp-50h]
	//  int v34; // [esp+18h] [ebp-50h]
	//  int v35; // [esp+1Ch] [ebp-4Ch] BYREF
	//  int v36; // [esp+20h] [ebp-48h]
	//  int v37; // [esp+24h] [ebp-44h]
	//  int v38; // [esp+28h] [ebp-40h] BYREF
	//  int v39; // [esp+2Ch] [ebp-3Ch] BYREF
	//  int v40; // [esp+30h] [ebp-38h] BYREF
	//  int v41; // [esp+34h] [ebp-34h] BYREF
	//  int v42; // [esp+38h] [ebp-30h] BYREF
	//  int v43; // [esp+3Ch] [ebp-2Ch]
	//  int v44; // [esp+40h] [ebp-28h]
	//  int v45; // [esp+44h] [ebp-24h]
	//  int v46; // [esp+48h] [ebp-20h] BYREF
	//  int v47; // [esp+4Ch] [ebp-1Ch]
	//  int v48; // [esp+50h] [ebp-18h]
	//  int v49; // [esp+54h] [ebp-14h]
	//  int v50; // [esp+64h] [ebp-4h]
	//
	//  sub_5A0EB0((int)a1, &v42);
	//  v50 = 0;
	//  if ( v45 )
	//  {
	//    *a2 = v45;
	//    v50 = -1;
	//    if ( v43 )
	//      (*(void (__fastcall **)(int, int *, int))(*(_DWORD *)v42 + 16))(v42, &v41, v43);
	//    return a2;
	//  }
	//  sub_5A0E20(a5, &v46);
	//  LOBYTE(v50) = 1;
	//  if ( !v49 )
	//  {
	//    v12 = a3;
	//    v13 = Size;
	//    if ( a3 < 0 )
	//    {
	//      a6 += a3;
	//      v13 = a3 + Size;
	//      Size += a3;
	//      v12 = 0;
	//    }
	//    v14 = a4;
	//    v15 = a7;
	//    if ( a4 < 0 )
	//    {
	//      a9 += a4;
	//      v15 = a4 + a7;
	//      v14 = 0;
	//    }
	//    dword4 = a1->dword4;
	//    if ( v12 + v13 > dword4 )
	//    {
	//      v13 = dword4 - v12;
	//      Size = dword4 - v12;
	//    }
	//    dword8 = a1->dword8;
	//    if ( v14 + a9 > dword8 )
	//      a9 = dword8 - v14;
	//    v18 = *(_DWORD *)(a5 + 4);
	//    if ( v13 + a6 > v18 )
	//    {
	//      v13 = v18 - a6;
	//      Size = v18 - a6;
	//    }
	//    v19 = *(_DWORD *)(a5 + 8);
	//    if ( v15 + a9 > v19 )
	//      a9 = v19 - v15;
	//    if ( v13 <= 0 || a9 <= 0 )
	//    {
	//      v23 = a2;
	//      LOBYTE(v50) = 0;
	//      v30 = v47;
	//      v26 = v47 == 0;
	//      *a2 = dword_8AC8C4;
	//      if ( !v26 )
	//        (*(void (__fastcall **)(int, int *, int))(*(_DWORD *)v46 + 8))(v46, &v41, v30);
	//      v50 = -1;
	//      v28 = v43;
	//      if ( !v43 )
	//        return v23;
	//      v29 = &v41;
	//      goto LABEL_53;
	//    }
	//    v37 = v48;
	//    v36 = v44;
	//    v20 = (char *)(a6 + v47 + v15 * v48);
	//    v21 = (char *)(v12 + v43 + v14 * v44);
	//    v33 = v20;
	//    v39 = a10 & 2;
	//    if ( (a10 & 2) == 0 && (a10 & 4) == 0 )
	//    {
	//      v34 = a9;
	//      do
	//      {
	//        memcpy_0(v21, v20, v13);
	//        v21 += v36;
	//        v20 += v37;
	//        --v34;
	//      }
	//      while ( v34 );
	//LABEL_45:
	//      v23 = a2;
	//      LOBYTE(v50) = 0;
	//      v27 = v47;
	//      v26 = v47 == 0;
	//      *a2 = dword_8AC8C4;
	//      if ( !v26 )
	//        (*(void (__fastcall **)(int, int *, int))(*(_DWORD *)v46 + 8))(v46, &v41, v27);
	//      v50 = -1;
	//      v28 = v43;
	//      if ( !v43 )
	//        return v23;
	//      v29 = &v39;
	//LABEL_53:
	//      (*(void (__fastcall **)(int, int *, int))(*(_DWORD *)v42 + 16))(v42, v29, v28);
	//      return v23;
	//    }
	//    v38 = 8 * (a10 & 6);
	//    (*(void (__fastcall **)(int, int *, int *, int))(*(_DWORD *)a5 + 32))(a5, &v35, &v40, v38);
	//    v22 = v35;
	//    if ( v35
	//      || (v22 = *(_DWORD *)(*(int (__fastcall **)(BitBucket *, int *, int *, int))(a1->dword0 + 32))(
	//                             a1,
	//                             &v38,
	//                             &v41,
	//                             v38),
	//          (v35 = v22) != 0) )
	//    {
	//      v23 = a2;
	//      *a2 = v22;
	//      LOBYTE(v50) = 0;
	//      sub_5A0E90(&v46);
	//      v50 = -1;
	//      sub_5A0F20(&v42);
	//      return v23;
	//    }
	//    v35 = a9;
	//    while ( 1 )
	//    {
	//      v24 = 0;
	//      v25 = v20;
	//      if ( v39 )
	//      {
	//        if ( v13 > 0 )
	//        {
	//          do
	//          {
	//            if ( (unsigned __int8)*v25 != v40 )
	//              v21[v24] = *v25;
	//            v13 = Size;
	//            ++v24;
	//            ++v25;
	//          }
	//          while ( v24 < (int)Size );
	//LABEL_43:
	//          v20 = v33;
	//        }
	//      }
	//      else if ( v13 > 0 )
	//      {
	//        do
	//        {
	//          if ( (unsigned __int8)*v25 != v41 )
	//            v21[v24] = *v25;
	//          v13 = Size;
	//          ++v24;
	//          ++v25;
	//        }
	//        while ( v24 < (int)Size );
	//        goto LABEL_43;
	//      }
	//      v20 += v37;
	//      v21 += v36;
	//      v26 = v35-- == 1;
	//      v33 = v20;
	//      if ( v26 )
	//        goto LABEL_45;
	//    }
	//  }
	//  *a2 = v49;
	//  LOBYTE(v50) = 0;
	//  if ( v47 )
	//    (*(void (__fastcall **)(int, int *, int))(*(_DWORD *)v46 + 8))(v46, &v41, v47);
	//  v50 = -1;
	//  if ( !v43 )
	//    return a2;
	//  (*(void (__fastcall **)(int, int *, int))(*(_DWORD *)v42 + 16))(v42, &v41, v43);
	//  return a2;

	return ret;
}

const std::array<DWORD, 12> &Backend::CustomBitbucket::getVtOriginal() {
	return vt_original;
}

const std::array<DWORD, 12> &Backend::CustomBitbucket::getVtHook() {
	return vt_hook;
}
