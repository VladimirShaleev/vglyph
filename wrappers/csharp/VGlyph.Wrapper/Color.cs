using System;
using System.Globalization;
using System.Runtime.Serialization;
using System.Security;

namespace VGlyph
{
    /// <summary>
    /// Color
    /// </summary>
    [Serializable]
    public sealed class Color : ICloneable, IEquatable<Color>, ISerializable
    {
        [Explicit] private double _red;
        [Explicit] private double _green;
        [Explicit] private double _blue;
        [Explicit] private double _alpha;

        /// <summary>
        /// Red component of color
        /// </summary>
        public double Red
        {
            get => _red;
            set => _red = value;
        }

        /// <summary>
        /// Green component of color
        /// </summary>
        public double Green
        {
            get => _green;
            set => _green = value;
        }

        /// <summary>
        /// Blue component of color
        /// </summary>
        public double Blue
        {
            get => _blue;
            set => _blue = value;
        }

        /// <summary>
        /// Alpha component of color
        /// </summary>
        public double Alpha
        {
            get => _alpha;
            set => _alpha = value;
        }

        /// <summary>
        /// Initialize <see cref="Color"/>
        /// </summary>
        /// <remarks>
        /// Initialize RGB components to 0.0 and <see cref="Alpha"/> component to 1.0
        /// </remarks>
        public Color() : this(0.0, 0.0, 0.0, 1.0)
        {
        }

        /// <summary>
        /// Initialize <see cref="Color"/>
        /// </summary>
        /// <remarks>
        /// Initialize RGB components and <see cref="Alpha"/> component to 1.0
        /// </remarks>
        /// <param name="grayscale">Initialize components <see cref="Red"/>, <see cref="Green"/>
        /// , <see cref="Blue"/> to <paramref name="grayscale"/>.</param>
        public Color(byte grayscale)
            : this(grayscale, grayscale, grayscale)
        {
        }

        /// <summary>
        /// Initialize <see cref="Color"/>
        /// </summary>
        /// <param name="grayscale">Initialize components <see cref="Red"/>, <see cref="Green"/>
        /// , <see cref="Blue"/> to <paramref name="grayscale"/>.</param>
        /// <param name="alpha">Initialize <see cref="Alpha"/> component to <paramref name="alpha"/></param>
        public Color(byte grayscale, byte alpha)
            : this(grayscale, grayscale, grayscale, alpha)
        {
        }

        /// <summary>
        /// Initialize <see cref="Color"/>
        /// </summary>
        /// <remarks>
        /// Initialize RGB components and <see cref="Alpha"/> component to 1.0
        /// </remarks>
        /// <param name="red"><see cref="Red"/> component of <see cref="Color"/></param>
        /// <param name="green"><see cref="Green"/> component of <see cref="Color"/></param>
        /// <param name="blue"><see cref="Blue"/> component of <see cref="Color"/></param>
        public Color(byte red, byte green, byte blue)
            : this(red, green, blue, byte.MaxValue)
        {
        }

        /// <summary>
        /// Initialize <see cref="Color"/>
        /// </summary>
        /// <param name="red"><see cref="Red"/> component of <see cref="Color"/></param>
        /// <param name="green"><see cref="Green"/> component of <see cref="Color"/></param>
        /// <param name="blue"><see cref="Blue"/> component of <see cref="Color"/></param>
        /// <param name="alpha"><see cref="Alpha"/> component of <see cref="Color"/></param>
        public Color(byte red, byte green, byte blue, byte alpha)
            : this(red / 255.0, green / 255.0, blue / 255.0, alpha / 255.0)
        {
        }

        /// <summary>
        /// Initialize <see cref="Color"/>
        /// </summary>
        /// <remarks>
        /// Initialize RGB components and <see cref="Alpha"/> component to 1.0
        /// </remarks>
        /// <param name="grayscale">Initialize components <see cref="Red"/>, <see cref="Green"/>
        /// , <see cref="Blue"/> to <paramref name="grayscale"/>.</param>
        public Color(double grayscale)
            : this(grayscale, grayscale, grayscale)
        {
        }

        /// <summary>
        /// Initialize <see cref="Color"/>
        /// </summary>
        /// <param name="grayscale">Initialize components <see cref="Red"/>, <see cref="Green"/>
        /// , <see cref="Blue"/> to <paramref name="grayscale"/>.</param>
        /// <param name="alpha">Initialize <see cref="Alpha"/> component to <paramref name="alpha"/></param>
        public Color(double grayscale, double alpha)
            : this(grayscale, grayscale, grayscale, alpha)
        {
        }

        /// <summary>
        /// Initialize <see cref="Color"/>
        /// </summary>
        /// <remarks>
        /// Initialize RGB components and <see cref="Alpha"/> component to 1.0
        /// </remarks>
        /// <param name="red"><see cref="Red"/> component of <see cref="Color"/></param>
        /// <param name="green"><see cref="Green"/> component of <see cref="Color"/></param>
        /// <param name="blue"><see cref="Blue"/> component of <see cref="Color"/></param>
        public Color(double red, double green, double blue)
            : this(red, green, blue, 1.0)
        {
        }

        /// <summary>
        /// Initialize <see cref="Color"/>
        /// </summary>
        /// <param name="red"><see cref="Red"/> component of <see cref="Color"/></param>
        /// <param name="green"><see cref="Green"/> component of <see cref="Color"/></param>
        /// <param name="blue"><see cref="Blue"/> component of <see cref="Color"/></param>
        /// <param name="alpha"><see cref="Alpha"/> component of <see cref="Color"/></param>
        public Color(double red, double green, double blue, double alpha)
        {
            Red = red;
            Green = green;
            Blue = blue;
            Alpha = alpha;
        }

        private Color(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
                throw new ArgumentNullException(nameof(info));

            Red = info.GetDouble(nameof(Red));
            Green = info.GetDouble(nameof(Green));
            Blue = info.GetDouble(nameof(Blue));
            Alpha = info.GetDouble(nameof(Alpha));
        }

        /// <summary>
        /// Clone of object <see cref="Color"/>
        /// </summary>
        /// <returns>Return clone object</returns>
        public object Clone()
        {
            return new Color(Red, Green, Blue, Alpha);
        }

        /// <summary>
        /// Equals colors
        /// </summary>
        /// <param name="color">Equals color</param> 
        /// <returns>Result of equal</returns>
        public override bool Equals(object color)
        {
            if (color is Color c)
                return Equals(c);

            return false;
        }

        /// <summary>
        /// Equals colors
        /// </summary>
        /// <param name="color">Equals color</param> 
        /// <returns>Result of equal</returns>
        public bool Equals(Color color)
        {
            if (color is null)
                return false;

            return
                Red == color.Red &&
                Green == color.Green &&
                Blue == color.Blue &&
                Alpha == color.Alpha;
        }

        /// <summary>
        /// Get hash code of <see cref="Color"/>
        /// </summary>
        /// <returns>Return hash code</returns>
        public override int GetHashCode()
        {
            return CombineHashCodes(
                CombineHashCodes(Red.GetHashCode(), Green.GetHashCode()), 
                CombineHashCodes(Blue.GetHashCode(), Alpha.GetHashCode()));
        }

        /// <summary>
        /// Convert <see cref="Color"/> to string
        /// </summary>
        /// <returns>String representation of <see cref="Color"/></returns>
        public override string ToString()
        {
            return string.Format(CultureInfo.InvariantCulture, "{{{0},{1},{2},{3}}}", Red, Green, Blue, Alpha);
        }

        [SecurityCritical]
        void ISerializable.GetObjectData(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
                throw new ArgumentNullException(nameof(info));

            info.AddValue(nameof(Red), Red);
            info.AddValue(nameof(Green), Green);
            info.AddValue(nameof(Blue), Blue);
            info.AddValue(nameof(Alpha), Alpha);
        }

        private static int CombineHashCodes(int h1, int h2)
        {
            return ((h1 << 5) + h1) ^ h2;
        }
    }
}
