
#ifndef WKCUSTOMRENDERER_BACKEND_H
#define WKCUSTOMRENDERER_BACKEND_H

#include <array>

typedef unsigned long DWORD;
class Backend {
public:
	class CustomGL;
	class CustomOperations;
	class CustomBitbucket;

	class CustomGL {
	public:
		// it would be cool to use virtual interface, but these functions utilize fastcall convention
		static DWORD * __fastcall vt0(CustomGL *This, DWORD *a2, int a3, int a4);
		static DWORD * __fastcall vt1(CustomGL *This, DWORD *a2);
		static DWORD * __fastcall vt2(CustomGL *This, DWORD *a2);
		static DWORD * __fastcall vt3(CustomGL *This, DWORD *a2, DWORD *a3);
		static DWORD * __fastcall vt4(CustomGL *This, DWORD *a2, int a3, void (__stdcall *a4)(DWORD, DWORD, int));
		static void __fastcall vt5(CustomGL *This);
		static int __fastcall setup_gl_vt6(CustomGL *This, int a2, int a3, int a4);
		static int * __fastcall vt7(CustomGL *This, int *a2, int a3);
		static DWORD * __fastcall vt8(CustomGL *This, DWORD *a2);
		static int __fastcall vt9(CustomGL *This, int a2, int a3, int a4);
		static int __fastcall vt10(CustomGL *This, int a2);
		static DWORD * __fastcall vt11(CustomGL *This, DWORD *a2);
		static int __fastcall draw_framebuffer_as_quad_vt12(CustomGL *This, int a2, unsigned char *a3);
		static DWORD * __fastcall swap_buffers_vt13(CustomGL *This, DWORD *a2);
		static int __fastcall vt14(CustomGL *This, int a2);

		DWORD vtable;
		DWORD dword4;
		DWORD dword8;
		DWORD dwordC;
		DWORD dword10;
		DWORD dword14;
		DWORD hdc_dword18;
		DWORD dword1C;
		DWORD dword20;
		DWORD dword24;
		DWORD dword28;
		DWORD width_dword2C;
		DWORD height_dword30;
		DWORD dword34;
		DWORD texture_width_dword38;
		DWORD texture_height_dword3C;
		DWORD dword40;
		DWORD screen_buffer_dword44;

		static inline std::array<DWORD, 15> vt_original;
		static inline std::array<DWORD, 15> vt_hook;

		static const std::array<DWORD, 15> &getVtOriginal();
		static const std::array<DWORD, 15> &getVtHook();
	};

	class CustomOperations {
	public:
		static int __fastcall vt0(int a1, int a2, int a3, int a4);
		static int __fastcall vt1(int a1, int a2);
		static int __fastcall vt2(int a1, int a2);
		static DWORD* __fastcall vt3(int a1, DWORD* a2, DWORD* a3);
		static int __fastcall vt4(int a1, int a2, int a3, int a4);
		static int __fastcall vt5(DWORD** a1);
		static int __fastcall vt6(int* a1, int a2, int a3, int a4);
		static DWORD* __fastcall vt7(int a1, DWORD * a2, int a3);
		static int __fastcall vt8(int a1, int a2);
		static int __fastcall vt9(int *a1, int a2, int a3, int a4);
		static int __fastcall vt10(int a1, int a2);
		static int __fastcall vt11(int a1, int a2);
		static DWORD* __fastcall vt12(int a1, DWORD* a2, int a3);
		static DWORD* __fastcall vt13(int a1, DWORD* a2);
		static int __fastcall vt14();
		static DWORD* __fastcall vt15(int a1, DWORD* a2, DWORD* a3, DWORD* a4);
		static DWORD* __fastcall vt16(int a1, DWORD* a2, int a3);
		static DWORD* __fastcall vt17(int a1, DWORD* a2, DWORD* a3, DWORD* a4);
		static DWORD* __fastcall vt18(int a1, DWORD* a2, int a3);
		static DWORD* __fastcall vt19(int a1, DWORD* a2, int a3, int a4, int a5, int a6, int a7);
		static void* __fastcall vt20();
		static int __fastcall vt21(int a1);
		static CustomBitbucket* __fastcall vt22();
		static DWORD* __fastcall draw_bitbucket_vt23(int a1, DWORD *a2, Backend::CustomBitbucket *src, int posX, int posY, int offsetX, int offsetY, int width, int height, int flag);
		static int* __fastcall vt24(int a1, int* a2, int a3, int a4);

		static inline std::array<DWORD, 25> vt_original;
		static inline std::array<DWORD, 25> vt_hook;
		static const std::array<DWORD, 25> &getVtOriginal();
		static const std::array<DWORD, 25> &getVtHook();
	};


	class CustomBitbucket {
	public:
		DWORD dword0;
		DWORD dword4;
		DWORD dword8;
		DWORD dwordC;
		DWORD dword10;

		static CustomBitbucket *__fastcall vt0(CustomBitbucket *a1, int EDX, char a2);
		static int __fastcall vt1(CustomBitbucket *a1, int a2, DWORD *a3, int a4);
		static DWORD *__fastcall vt2(CustomBitbucket* a1, DWORD *a2, int a3);
		static DWORD *__fastcall vt3(CustomBitbucket *a1, DWORD *a2, DWORD *a3, DWORD *a4);
		static DWORD *__fastcall vt4(CustomBitbucket* a1, DWORD *a2, int a3);
		static DWORD *__fastcall vt5(CustomBitbucket *a1, DWORD *a2, int a3, int a4, int a5);
		static DWORD *__fastcall vt6(CustomBitbucket *a1, DWORD *a2);
		static DWORD *__fastcall vt7(CustomBitbucket *a1, DWORD *a2, char a3, int a4);
		static DWORD *__fastcall vt8(CustomBitbucket *a1, DWORD *a2, DWORD *a3, int a4);
		static char vt9();
		static DWORD *__fastcall vt10(CustomBitbucket *a1, DWORD *a2, int a3, int a4, size_t Size, int a6, int Val);
		static DWORD *__fastcall vt11(CustomBitbucket *a1, int *a2, int a3, int a4, int a5, int a6, int a7, size_t Size, int a9, int a10);

		static inline std::array<DWORD, 12> vt_original;
		static inline std::array<DWORD, 12> vt_hook;
		static const std::array<DWORD, 12> &getVtOriginal();
		static const std::array<DWORD, 12> &getVtHook();
	};


private:
	static inline DWORD * addrOpenGLCpuVtable;
	static inline DWORD * addrOpenGLShaderVtable;
	static inline DWORD gl_dword8AC8BC; // usef for return values in CustomGL, no clue
	static inline DWORD op_dword8ACCD4; // used for return values in CustomOperations, no clue
	static inline DWORD bitbucket_dword8AC8C4; // used for return values in CustomBitbucket, no clue
public:
	static void install();
};


#endif //WKCUSTOMRENDERER_BACKEND_H
