#ifndef VE_KEYCODES
#define VE_KEYCODES

#if 0
// Copied from glfw3.h
#define VE_KEY_SPACE              32
#define VE_KEY_APOSTROPHE         39  /* ' */
#define VE_KEY_COMMA              44  /* , */
#define VE_KEY_MINUS              45  /* - */
#define VE_KEY_PERIOD             46  /* . */
#define VE_KEY_SLASH              47  /* / */
#define VE_KEY_0                  48
#define VE_KEY_1                  49
#define VE_KEY_2                  50
#define VE_KEY_3                  51
#define VE_KEY_4                  52
#define VE_KEY_5                  53
#define VE_KEY_6                  54
#define VE_KEY_7                  55
#define VE_KEY_8                  56
#define VE_KEY_9                  57
#define VE_KEY_SEMICOLON          59  /* ; */
#define VE_KEY_EQUAL              61  /* = */
#define VE_KEY_A                  65
#define VE_KEY_B                  66
#define VE_KEY_C                  67
#define VE_KEY_D                  68
#define VE_KEY_E                  69
#define VE_KEY_F                  70
#define VE_KEY_G                  71
#define VE_KEY_H                  72
#define VE_KEY_I                  73
#define VE_KEY_J                  74
#define VE_KEY_K                  75
#define VE_KEY_L                  76
#define VE_KEY_M                  77
#define VE_KEY_N                  78
#define VE_KEY_O                  79
#define VE_KEY_P                  80
#define VE_KEY_Q                  81
#define VE_KEY_R                  82
#define VE_KEY_S                  83
#define VE_KEY_T                  84
#define VE_KEY_U                  85
#define VE_KEY_V                  86
#define VE_KEY_W                  87
#define VE_KEY_X                  88
#define VE_KEY_Y                  89
#define VE_KEY_Z                  90
#define VE_KEY_LEFT_BRACKET       91  /* [ */
#define VE_KEY_BACKSLASH          92  /* \ */
#define VE_KEY_RIGHT_BRACKET      93  /* ] */
#define VE_KEY_GRAVE_ACCENT       96  /* ` */
#define VE_KEY_WORLD_1            161 /* non-US #1 */
#define VE_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define VE_KEY_ESCAPE             256
#define VE_KEY_ENTER              257
#define VE_KEY_TAB                258
#define VE_KEY_BACKSPACE          259
#define VE_KEY_INSERT             260
#define VE_KEY_DELETE             261
#define VE_KEY_RIGHT              262
#define VE_KEY_LEFT               263
#define VE_KEY_DOWN               264
#define VE_KEY_UP                 265
#define VE_KEY_PAGE_UP            266
#define VE_KEY_PAGE_DOWN          267
#define VE_KEY_HOME               268
#define VE_KEY_END                269
#define VE_KEY_CAPS_LOCK          280
#define VE_KEY_SCROLL_LOCK        281
#define VE_KEY_NUM_LOCK           282
#define VE_KEY_PRINT_SCREEN       283
#define VE_KEY_PAUSE              284
#define VE_KEY_F1                 290
#define VE_KEY_F2                 291
#define VE_KEY_F3                 292
#define VE_KEY_F4                 293
#define VE_KEY_F5                 294
#define VE_KEY_F6                 295
#define VE_KEY_F7                 296
#define VE_KEY_F8                 297
#define VE_KEY_F9                 298
#define VE_KEY_F10                299
#define VE_KEY_F11                300
#define VE_KEY_F12                301
#define VE_KEY_F13                302
#define VE_KEY_F14                303
#define VE_KEY_F15                304
#define VE_KEY_F16                305
#define VE_KEY_F17                306
#define VE_KEY_F18                307
#define VE_KEY_F19                308
#define VE_KEY_F20                309
#define VE_KEY_F21                310
#define VE_KEY_F22                311
#define VE_KEY_F23                312
#define VE_KEY_F24                313
#define VE_KEY_F25                314
#define VE_KEY_KP_0               320
#define VE_KEY_KP_1               321
#define VE_KEY_KP_2               322
#define VE_KEY_KP_3               323
#define VE_KEY_KP_4               324
#define VE_KEY_KP_5               325
#define VE_KEY_KP_6               326
#define VE_KEY_KP_7               327
#define VE_KEY_KP_8               328
#define VE_KEY_KP_9               329
#define VE_KEY_KP_DECIMAL         330
#define VE_KEY_KP_DIVIDE          331
#define VE_KEY_KP_MULTIPLY        332
#define VE_KEY_KP_SUBTRACT        333
#define VE_KEY_KP_ADD             334
#define VE_KEY_KP_ENTER           335
#define VE_KEY_KP_EQUAL           336
#define VE_KEY_LEFT_SHIFT         340
#define VE_KEY_LEFT_CONTROL       341
#define VE_KEY_LEFT_ALT           342
#define VE_KEY_LEFT_SUPER         343
#define VE_KEY_RIGHT_SHIFT        344
#define VE_KEY_RIGHT_CONTROL      345
#define VE_KEY_RIGHT_ALT          346
#define VE_KEY_RIGHT_SUPER        347
#define VE_KEY_MENU               348
#endif

// HID Keycodes

enum 
{
    /* Zero, does not correspond to any key. */
    VE_KEY_None = 0,

    /* Keycode definitions. */
    VE_KEY_A = 4,
    VE_KEY_B = 5,
    VE_KEY_C = 6,
    VE_KEY_D = 7,
    VE_KEY_E = 8,
    VE_KEY_F = 9,
    VE_KEY_G = 10,
    VE_KEY_H = 11,
    VE_KEY_I = 12,
    VE_KEY_J = 13,
    VE_KEY_K = 14,
    VE_KEY_L = 15,
    VE_KEY_M = 16,
    VE_KEY_N = 17,
    VE_KEY_O = 18,
    VE_KEY_P = 19,
    VE_KEY_Q = 20,
    VE_KEY_R = 21,
    VE_KEY_S = 22,
    VE_KEY_T = 23,
    VE_KEY_U = 24,
    VE_KEY_V = 25,
    VE_KEY_W = 26,
    VE_KEY_X = 27,
    VE_KEY_Y = 28,
    VE_KEY_Z = 29,
    VE_KEY_1 = 30,
    VE_KEY_2 = 31,
    VE_KEY_3 = 32,
    VE_KEY_4 = 33,
    VE_KEY_5 = 34,
    VE_KEY_6 = 35,
    VE_KEY_7 = 36,
    VE_KEY_8 = 37,
    VE_KEY_9 = 38,
    VE_KEY_0 = 39,
    VE_KEY_Escape = 41,
    VE_KEY_Delete = 42,
    VE_KEY_Tab = 43,
    VE_KEY_Space = 44,
    VE_KEY_Minus = 45,
    VE_KEY_Equals = 46,
    VE_KEY_LeftBracket = 47,
    VE_KEY_RightBracket = 48,
    VE_KEY_Backslash = 49,
    VE_KEY_Semicolon = 51,
    VE_KEY_Quote = 52,
    VE_KEY_Grave = 53,
    VE_KEY_Comma = 54,
    VE_KEY_Period = 55,
    VE_KEY_Slash = 56,
    VE_KEY_CapsLock = 57,
    VE_KEY_F1 = 58,
    VE_KEY_F2 = 59,
    VE_KEY_F3 = 60,
    VE_KEY_F4 = 61,
    VE_KEY_F5 = 62,
    VE_KEY_F6 = 63,
    VE_KEY_F7 = 64,
    VE_KEY_F8 = 65,
    VE_KEY_F9 = 66,
    VE_KEY_F10 = 67,
    VE_KEY_F11 = 68,
    VE_KEY_F12 = 69,
    VE_KEY_PrintScreen = 70,
    VE_KEY_ScrollLock = 71,
    VE_KEY_Pause = 72,
    VE_KEY_Insert = 73,
    VE_KEY_Home = 74,
    VE_KEY_PageUp = 75,
    VE_KEY_DeleteForward = 76,
    VE_KEY_End = 77,
    VE_KEY_PageDown = 78,
    VE_KEY_Right = 79,
    VE_KEY_Left = 80,
    VE_KEY_Down = 81,
    VE_KEY_Up = 82,
    VE_KP_NumLock = 83,
    VE_KP_Divide = 84,
    VE_KP_Multiply = 85,
    VE_KP_Subtract = 86,
    VE_KP_Add = 87,
    VE_KP_Enter = 88,
    VE_KP_1 = 89,
    VE_KP_2 = 90,
    VE_KP_3 = 91,
    VE_KP_4 = 92,
    VE_KP_5 = 93,
    VE_KP_6 = 94,
    VE_KP_7 = 95,
    VE_KP_8 = 96,
    VE_KP_9 = 97,
    VE_KP_0 = 98,
    VE_KP_Point = 99,
    VE_KEY_NonUSBackslash = 100,
    VE_KP_Equals = 103,
    VE_KEY_F13 = 104,
    VE_KEY_F14 = 105,
    VE_KEY_F15 = 106,
    VE_KEY_F16 = 107,
    VE_KEY_F17 = 108,
    VE_KEY_F18 = 109,
    VE_KEY_F19 = 110,
    VE_KEY_F20 = 111,
    VE_KEY_F21 = 112,
    VE_KEY_F22 = 113,
    VE_KEY_F23 = 114,
    VE_KEY_F24 = 115,
    VE_KEY_Help = 117,
    VE_KEY_Menu = 118,
    VE_KEY_Mute = 127,
    VE_KEY_SysReq = 154,
    VE_KEY_Return = 158,
    VE_KP_Clear = 216,
    VE_KP_Decimal = 220,
    VE_KEY_LeftControl = 224,
    VE_KEY_LeftShift = 225,
    VE_KEY_LeftAlt = 226,
    VE_KEY_LeftGUI = 227,
    VE_KEY_RightControl = 228,
    VE_KEY_RightShift = 229,
    VE_KEY_RightAlt = 230,
    VE_KEY_RightGUI = 231
};

#endif