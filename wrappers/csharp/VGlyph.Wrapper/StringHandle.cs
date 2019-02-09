using Microsoft.Win32.SafeHandles;
using System;
using System.Runtime.InteropServices;
using System.Text;

namespace VGlyph
{
    internal class StringHandle : SafeHandleZeroOrMinusOneIsInvalid
    {
        private string _string;

        public override bool IsInvalid => handle == IntPtr.Zero;

        public StringHandle() : base(false)
        {
        }

        public StringHandle(IntPtr utf8, bool ownsHandle) : base(false)
        {
            SetHandle(utf8);
        }

        public StringHandle(string str) : base(true)
        {
            SetHandle(StringToUtf8(str));
        }

        public string GetString()
        {
            if (_string == null)
                _string = Utf8ToString(handle);

            return _string;
        }

        public static implicit operator string(StringHandle stringHandle)
        {
            return stringHandle.GetString();
        }

        protected override bool ReleaseHandle()
        {
            Marshal.FreeHGlobal(handle);
            return true;
        }

        private static string Utf8ToString(IntPtr utf8)
        {
            if (utf8 == IntPtr.Zero)
                return null;

            var length = 0;

            while (Marshal.ReadByte(utf8, length) != 0)
                ++length;

            var buffer = new byte[length];
            Marshal.Copy(utf8, buffer, 0, length);

            return Encoding.UTF8.GetString(buffer);
        }

        private static IntPtr StringToUtf8(string str)
        {
            if (str == null)
                return IntPtr.Zero;

            var length = Encoding.UTF8.GetByteCount(str);
            var utf8 = Marshal.AllocHGlobal(length + 1);

            try
            {
                Marshal.Copy(Encoding.UTF8.GetBytes(str), 0, utf8, length);
                Marshal.WriteByte(utf8, length, 0);
            }
            catch
            {
                Marshal.FreeHGlobal(utf8);
                return IntPtr.Zero;
            }

            return utf8;
        }
    }
}
