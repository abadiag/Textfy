using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace TextfyConsumer.Api
{
    public struct rgb_t
    {
        public uint red;
        public uint green;
        public uint blue;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public static class ImageStruct //or 'struct'  
    {
        public static string bff;
        public static int size;
    }

    public static class BitmapApi
    {
        private const string DllPath = @"F:\Repository\Textfy\TextfyLib\x64\Release\TextfyLib.dll";

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void open_bmp(string file_name);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void resize_bmp(string file_in, string file_out);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void save_bmp(string file_name);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void flip_bmp(string V_H);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern rgb_t get_pixel_bmp(int x, int y);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void set_pixel_bmp(int x, int y, rgb_t rgb);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern int get_bmp_width();

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern int get_bmp_height();

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void get_bmp_stream([Out] out byte[] buffer, out int size);

        // The array size cannot be changed, but the array is copied back.
        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern int get_bmp_data(ref byte[] array, ref int size);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern IntPtr TestStringInStruct();

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern int TestArrayOfStrings(string[] ppStrArray, int count);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void SayHello();

        //[return: MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_UI1)]
        //public static extern byte[] get_bmp_array();

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void get_bmp_array([MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_I4)] ref int[] ar);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern int get_coincidence(string file_name_a, string file_name_b, int threshold);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern string process_document(string file_name, int threshold);

        [Pure, DllImport(DllPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern void create_templates();
    }
}
