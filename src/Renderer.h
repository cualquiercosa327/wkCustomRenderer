
#ifndef WKCUSTOMRENDERER_RENDERER_H
#define WKCUSTOMRENDERER_RENDERER_H

#include <array>

typedef unsigned long DWORD;
class Renderer {
public:
	class CustomGL {
	public:
		// it would be cool to use virtual interface, but these functions utilize fastcall convention
		static DWORD * __fastcall vt0(CustomGL *This, DWORD *a2, int a3, int a4);
		static DWORD * __fastcall vt1(CustomGL *This, DWORD *a2);
		static DWORD * __fastcall vt2(CustomGL *This, DWORD *a2);
		static DWORD * __fastcall vt3(CustomGL *This, DWORD *a2, DWORD *a3);
		static DWORD * __fastcall vt4(CustomGL *This, DWORD *a2, int a3, void (__stdcall *a4)(DWORD, DWORD, int));
		static void __fastcall vt5(CustomGL *This);
		static int __fastcall vt6(CustomGL *This, int a2, int a3, int a4);
		static int * __fastcall vt7(CustomGL *This, int *a2, int a3);
		static DWORD * __fastcall vt8(CustomGL *This, DWORD *a2);
		static int __fastcall vt9(CustomGL *This, int a2, int a3, int a4);
		static int __fastcall vt10(CustomGL *This, int a2);
		static DWORD * __fastcall vt11(CustomGL *This, DWORD *a2);
		static int * __fastcall vt12(CustomGL *This, int a2, unsigned char *a3);
		static DWORD * __fastcall vt13(CustomGL *This, DWORD *a2);
		static int __fastcall vt14(CustomGL *This, int a2);

		static inline std::array<DWORD, 15> vt_original;
		static inline std::array<DWORD, 15> vt_hook;

		DWORD vtable;
		DWORD dword4;
		DWORD dword8;
		DWORD dwordC;
		DWORD dword10;
		DWORD dword14;
		DWORD dword18;
		DWORD dword1C;
		DWORD dword20;
		DWORD dword24;
		DWORD dword28;
		DWORD dword2C;
		DWORD dword30;
		DWORD dword34;
		DWORD dword38;
		DWORD dword3C;
		DWORD dword40;
		DWORD dword44;
	};


private:
	static inline DWORD * addrOpenGLCpuVtable;
public:
	static void install();
};


#endif //WKCUSTOMRENDERER_RENDERER_H
