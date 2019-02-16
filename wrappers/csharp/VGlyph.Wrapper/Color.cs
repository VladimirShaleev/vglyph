using System;

namespace VGlyph
{
    /// <summary>
    /// Color
    /// </summary>
    [Serializable]
    public class Color
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
    }
}
