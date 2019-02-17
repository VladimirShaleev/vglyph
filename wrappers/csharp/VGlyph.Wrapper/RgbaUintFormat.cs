using System;
using VGlyph.Import;

namespace VGlyph
{
    /// <summary>
    /// Format of <see cref="Surface"/>
    /// </summary>
    public class RgbaUintFormat : Format
    {
        internal static new ObjectHandle Type
            => Api.GetRgbaUintFormatType();

        /// <summary>
        /// Constructs new object <see cref="RgbaUintFormat"/>
        /// </summary>
        /// <param name="packagingBytes">Packaging bytes</param>
        /// <param name="components">Map RGB channels</param>
        /// <param name="bitCount">Bits per channel</param>
        /// <exception cref="ArgumentNullException">one or some arguments is null</exception>
        public RgbaUintFormat(PackagingBytes packagingBytes, RgbaComponents components, RgbaUintBitCount bitCount) :
            base(CreateHandle(packagingBytes, components, bitCount))
        {
        }

        /// <summary>
        /// Constructs new object <see cref="RgbaUintFormat"/> for unmanaged handle
        /// </summary>
        /// <param name="handle">Unmanaged handle of vglyph library</param>
        /// <exception cref="ArgumentException">Invalid unmanaged handle</exception>
        protected RgbaUintFormat(IntPtr handle) : base(handle)
        {
        }

        internal RgbaUintFormat(ObjectHandle handle) : base(handle)
        {
        }

        /// <summary>
        /// Get Map RGBA components
        /// </summary>
        public RgbaComponents Components
        {
            get
            {
                CheckDisposed();
                Api.RgbaUintFormatGetComponents(Object, out var result);
                Object.CheckState();

                return new RgbaComponents
                {
                    Red = (Component)result.r,
                    Green = (Component)result.g,
                    Blue = (Component)result.b,
                    Alpha = (Component)result.a
                };
            }
        }

        /// <summary>
        /// Get bits per channel
        /// </summary>
        public RgbaUintBitCount BitCount
        {
            get
            {
                CheckDisposed();
                Api.RgbaUintFormatGetBitCount(Object, out var result);
                Object.CheckState();

                return new RgbaUintBitCount
                {
                    Red = result.r,
                    Green = result.g,
                    Blue = result.b,
                    Alpha = result.a
                };
            }
        }

        private static ObjectHandle CreateHandle(PackagingBytes packagingBytes, RgbaComponents components, RgbaUintBitCount bitCount)
        {
            if (packagingBytes == null)
                throw new ArgumentNullException(nameof(packagingBytes));

            if (components == null)
                throw new ArgumentNullException(nameof(components));

            if (bitCount == null)
                throw new ArgumentNullException(nameof(bitCount));

            var unmanagedPackagingBytes = new Import.PackagingBytes
            {
                byteCount = (uint)packagingBytes.ByteCount,
                endianness = packagingBytes.Endianness.GetUnmanagedEndianness()
            };

            var unmanagedComponents = new Import.RgbaComponents
            {
                r = components.Red.GetUnmanagedComponent(),
                g = components.Green.GetUnmanagedComponent(),
                b = components.Blue.GetUnmanagedComponent(),
                a = components.Alpha.GetUnmanagedComponent(),
            };

            var unmanagedBitCount = new Import.RgbaUintBitCount
            {
                r = bitCount.Red,
                g = bitCount.Green,
                b = bitCount.Blue,
                a = bitCount.Alpha,
            };

            return Api.RgbaUintFormatCreate(ref unmanagedPackagingBytes, ref unmanagedComponents, ref unmanagedBitCount);
        }

        private void CheckDisposed()
        {
            if (Object == null)
                throw new ObjectDisposedException(nameof(RgbaUintFormat));

            Object.CheckDisposed(nameof(RgbaUintFormat));
        }
    }
}
