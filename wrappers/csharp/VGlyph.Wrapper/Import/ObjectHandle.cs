using Microsoft.Win32.SafeHandles;
using System;

namespace VGlyph.Import
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

        public void CheckState()
        {
            var state = Api.ObjectGetState(this);

            if (state != State.Success)
            {
                using (var errorMessage = Api.StateToString(state))
                {
                    Api.ObjectResetState(this);

                    switch (state)
                    {
                        case State.OutOfMemory:
                            throw new OutOfMemoryException(errorMessage);

                        case State.InvalidCast:
                            throw new InvalidCastException(errorMessage);

                        case State.InvalidFormat:
                            throw new FormatException(errorMessage);

                        default:
                            throw new Exception(errorMessage);
                    }
                }
            }
        }

        public void CheckDisposed(string objectName)
        {
            if (IsClosed)
                throw new ObjectDisposedException(objectName);
        }

        protected override bool ReleaseHandle()
        {
            Api.ObjectDestroy(handle);
            return true;
        }
    }
}
