using Microsoft.Win32.SafeHandles;
using System;

namespace VGlyph
{
    internal class ObjectHandle : SafeHandleZeroOrMinusOneIsInvalid
    {
        public override bool IsInvalid => handle == IntPtr.Zero;

        public ObjectHandle() : base(true)
        {
        }

        public ObjectHandle(IntPtr obj) : base(true)
        {
            SetHandle(obj);
        }

        protected override bool ReleaseHandle()
        {
            Import.ObjectDestroy(handle);
            return true;
        }
    }
}
