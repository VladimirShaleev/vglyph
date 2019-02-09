using VGlyph;
using Xunit;

public class VersionTest
{
    public class Cctor
    {
        [Fact]
        public void NoParams()
        {
            var version = new Version();
            Assert.Equal(0, version.Major);
            Assert.Equal(0, version.Minor);
            Assert.Equal(0, version.Micro);
        }

        [Theory]
        [InlineData(0)]
        [InlineData(1)]
        [InlineData(byte.MaxValue / 2)]
        [InlineData(byte.MaxValue)]
        public void OneParam(byte major)
        {
            var version = new Version(major);
            Assert.Equal(major, version.Major);
            Assert.Equal(0, version.Minor);
            Assert.Equal(0, version.Micro);
        }

        [Theory]
        [InlineData(0, 0)]
        [InlineData(1, 0)]
        [InlineData(byte.MaxValue / 2, 0)]
        [InlineData(byte.MaxValue, 0)]
        [InlineData(0, 1)]
        [InlineData(0, byte.MaxValue / 2)]
        [InlineData(0, byte.MaxValue)]
        [InlineData(4, 3)]
        [InlineData(byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(byte.MaxValue / 2, byte.MaxValue)]
        public void TwoParams(byte major, byte minor)
        {
            var version = new Version(major, minor);
            Assert.Equal(major, version.Major);
            Assert.Equal(minor, version.Minor);
            Assert.Equal(0, version.Micro);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(1, 0, 0)]
        [InlineData(byte.MaxValue / 2, 0, 0)]
        [InlineData(byte.MaxValue, 0, 0)]
        [InlineData(0, 1, 0)]
        [InlineData(0, byte.MaxValue / 2, 0)]
        [InlineData(0, byte.MaxValue, 0)]
        [InlineData(0, 0, 1)]
        [InlineData(0, 0, byte.MaxValue / 2)]
        [InlineData(0, 0, byte.MaxValue)]
        [InlineData(4, 3, 5)]
        [InlineData(0, byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(byte.MaxValue / 2, byte.MaxValue, 2)]
        [InlineData(byte.MaxValue / 2, 0, byte.MaxValue)]
        public void ThreeParams(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);
            Assert.Equal(major, version.Major);
            Assert.Equal(minor, version.Minor);
            Assert.Equal(micro, version.Micro);
        }

        [Theory]
        [InlineData(0)]
        [InlineData(10000)]
        [InlineData(65536)]
        [InlineData(16777215)]
        [InlineData(16777216)]
        [InlineData(33554430)]
        public void Internal(uint internalVersion)
        {
            var major = (internalVersion >> 16) & 0xFF;
            var minor = (internalVersion >> 8) & 0xFF;
            var micro = (internalVersion >> 0) & 0xFF;

            var version = new Version(internalVersion);
            Assert.Equal(major, version.Major);
            Assert.Equal(minor, version.Minor);
            Assert.Equal(micro, version.Micro);
        }
    }

    public class Properties
    {
        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(5, 1, byte.MaxValue)]
        public void Setters(byte major, byte minor, byte micro)
        {
            var version = new Version
            {
                Major = major,
                Minor = minor,
                Micro = micro
            };

            Assert.Equal(major, version.Major);
            Assert.Equal(minor, version.Minor);
            Assert.Equal(micro, version.Micro);
        }

        [Theory]
        [InlineData(0, 0, 0, 0)]
        [InlineData(0xC80A05, 200, 10, 5)]
        [InlineData(0x5FF03, 5, byte.MaxValue, 3)]
        [InlineData(0xFFFFFF, byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void InternalGetter(uint version32, byte major, byte minor, byte micro)
        {
            var version = new Version
            {
                Major = major,
                Minor = minor,
                Micro = micro
            };

            Assert.Equal(version32, version.Version32);
        }
    }

    public class Cloneable
    {
        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(5, 100, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void Clone(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var cloneVersion = version.Clone() as Version;

            Assert.Equal(version.Major, cloneVersion.Major);
            Assert.Equal(version.Minor, cloneVersion.Minor);
            Assert.Equal(version.Micro, cloneVersion.Micro);
        }
    }

    public class Comparator
    {
        [Theory]
        [InlineData(0, 0, 0, 0, 0, 0, 0)]
        [InlineData(0, 4, 100, 2, 4, 100, 2)]
        [InlineData(1, 0, 0, 1, 0, 0, 0)]
        [InlineData(1, 100, 2, 5, 80, 255, 150)]
        [InlineData(1, 5, 100, 100, 4, 100, 100)]
        [InlineData(-1, 4, 100, 100, 7, 1, 2)]
        [InlineData(-1, 0, 0, 0, 0, 0, 1)]
        public void CompareToObject(int compare, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1) as System.IComparable;
            var version2 = new Version(major2, minor2, micro2);

            var result = version1.CompareTo(version2);

            Assert.Equal(compare, result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void CompareToObjectTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro) as System.IComparable;

            var result = version.CompareTo(null);

            Assert.Equal(1, result);
        }

        [Fact]
        public void CompareToObjectIsNotVersion()
        {
            var version = new Version() as System.IComparable;

            var exception = Assert.Throws<System.ArgumentException>(() => version.CompareTo(new object()));

            Assert.Equal("version", exception.ParamName);
        }

        [Theory]
        [InlineData(0, 0, 0, 0, 0, 0, 0)]
        [InlineData(0, 4, 100, 2, 4, 100, 2)]
        [InlineData(1, 0, 0, 1, 0, 0, 0)]
        [InlineData(1, 100, 2, 5, 80, 255, 150)]
        [InlineData(1, 5, 100, 100, 4, 100, 100)]
        [InlineData(-1, 4, 100, 100, 7, 1, 2)]
        [InlineData(-1, 0, 0, 0, 0, 0, 1)]
        public void CompareTo(int compare, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1) as System.IComparable<Version>;
            var version2 = new Version(major2, minor2, micro2);

            var result = version1.CompareTo(version2);

            Assert.Equal(compare, result);
        }
        
        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void CompareToTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro) as System.IComparable<Version>;

            var result = version.CompareTo(null);

            Assert.Equal(1, result);
        }

        [Theory]
        [InlineData(true, 0, 0, 0, 0, 0, 0)]
        [InlineData(true, 10, 5, 200, 10, 5, 200)]
        [InlineData(true, 0, byte.MaxValue, byte.MaxValue / 2, 0, byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(true, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        [InlineData(false, 0, 0, 0, 0, 0, 1)]
        [InlineData(false, 100, 5, 200, 10, 5, 200)]
        [InlineData(false, 0, byte.MaxValue / 2, byte.MaxValue / 2, 0, byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(false, byte.MaxValue, byte.MaxValue, 0, 0, byte.MaxValue, byte.MaxValue)]
        public void EqualsObject(bool equal, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1) as object;
            var version2 = new Version(major2, minor2, micro2);

            var result = version1.Equals(version2);

            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void EqualsObjectTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro) as object;

            var result = version.Equals(null);

            Assert.False(result);
        }

        [Fact]
        public void EqualsObjectIsNotVersion()
        {
            var version = new Version() as object;

            var result = version.Equals(new object());

            Assert.False(result);
        }
        
        [Theory]
        [InlineData(true, 0, 0, 0, 0, 0, 0)]
        [InlineData(true, 10, 5, 200, 10, 5, 200)]
        [InlineData(true, 0, byte.MaxValue, byte.MaxValue / 2, 0, byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(true, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        [InlineData(false, 0, 0, 0, 0, 0, 1)]
        [InlineData(false, 100, 5, 200, 10, 5, 200)]
        [InlineData(false, 0, byte.MaxValue / 2, byte.MaxValue / 2, 0, byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(false, byte.MaxValue, byte.MaxValue, 0, 0, byte.MaxValue, byte.MaxValue)]
        public void Equal(bool equal, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1) as System.IEquatable<Version>;
            var version2 = new Version(major2, minor2, micro2);

            var result = version1.Equals(version2);

            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void EqualsTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro) as System.IEquatable<Version>;

            var result = version.Equals(null);

            Assert.False(result);
        }

        [Fact]
        public void EqualsIsNotVersion()
        {
            var version = new Version() as System.IEquatable<Version>;

            var result = version.Equals(new object());

            Assert.False(result);
        }

        [Theory]
        [InlineData(true, 0, 0, 0, 0, 0, 0)]
        [InlineData(true, 10, 5, 200, 10, 5, 200)]
        [InlineData(true, 0, byte.MaxValue, byte.MaxValue / 2, 0, byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(true, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        [InlineData(false, 0, 0, 0, 0, 0, 1)]
        [InlineData(false, 100, 5, 200, 10, 5, 200)]
        [InlineData(false, 0, byte.MaxValue / 2, byte.MaxValue / 2, 0, byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(false, byte.MaxValue, byte.MaxValue, 0, 0, byte.MaxValue, byte.MaxValue)]
        public void OperatorEquality(bool equal, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1);
            var version2 = new Version(major2, minor2, micro2);

            var result = version1 == version2;

            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorEqualityOneParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = version == null;

            Assert.False(result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorEqualityTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = null == version;

            Assert.False(result);
        }

        [Fact]
        public void OperatorEqualityAllParamsIsNull()
        {
            var method = typeof(Version).GetMethod("op_Equality");

            var result = (bool)method.Invoke(null, new object[] { null, null });

            Assert.True(result);
        }
        
        [Theory]
        [InlineData(false, 0, 0, 0, 0, 0, 0)]
        [InlineData(false, 10, 5, 200, 10, 5, 200)]
        [InlineData(false, 0, byte.MaxValue, byte.MaxValue / 2, 0, byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(false, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        [InlineData(true, 0, 0, 0, 0, 0, 1)]
        [InlineData(true, 100, 5, 200, 10, 5, 200)]
        [InlineData(true, 0, byte.MaxValue / 2, byte.MaxValue / 2, 0, byte.MaxValue, byte.MaxValue / 2)]
        [InlineData(true, byte.MaxValue, byte.MaxValue, 0, 0, byte.MaxValue, byte.MaxValue)]
        public void OperatorInequality(bool equal, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1);
            var version2 = new Version(major2, minor2, micro2);

            var result = version1 != version2;

            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorInequalityOneParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = version != null;

            Assert.True(result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorInequalityTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = null != version;

            Assert.True(result);
        }

        [Fact]
        public void OperatorInequalityAllParamsIsNull()
        {
            var method = typeof(Version).GetMethod("op_Inequality");

            var result = (bool)method.Invoke(null, new object[] { null, null });
            
            Assert.False(result);
        }

        [Theory]
        [InlineData(false, 0, 0, 0, 0, 0, 0)]
        [InlineData(false, 4, 100, 2, 4, 100, 2)]
        [InlineData(false, 0, 0, 1, 0, 0, 0)]
        [InlineData(false, 100, 2, 5, 80, 255, 150)]
        [InlineData(false, 5, 100, 100, 4, 100, 100)]
        [InlineData(true, 4, 100, 100, 7, 1, 2)]
        [InlineData(true, 0, 0, 0, 0, 0, 1)]
        public void OperatorLessThan(bool equal, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1);
            var version2 = new Version(major2, minor2, micro2);
        
            var result = version1 < version2;
        
            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorLessThanOneParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);
        
            var result = version < null;
        
            Assert.False(result);
        }
        
        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorLessThanTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);
        
            var result = null < version;
        
            Assert.True(result);
        }
        
        [Fact]
        public void OperatorLessThanAllParamsIsNull()
        {
            var method = typeof(Version).GetMethod("op_LessThan");
        
            var result = (bool)method.Invoke(null, new object[] { null, null });
        
            Assert.False(result);
        }
        
        [Theory]
        [InlineData(false, 0, 0, 0, 0, 0, 0)]
        [InlineData(false, 4, 100, 2, 4, 100, 2)]
        [InlineData(true, 0, 0, 1, 0, 0, 0)]
        [InlineData(true, 100, 2, 5, 80, 255, 150)]
        [InlineData(true, 5, 100, 100, 4, 100, 100)]
        [InlineData(false, 4, 100, 100, 7, 1, 2)]
        [InlineData(false, 0, 0, 0, 0, 0, 1)]
        public void OperatorGreaterThan(bool equal, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1);
            var version2 = new Version(major2, minor2, micro2);

            var result = version1 > version2;

            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorGreaterThanOneParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = version > null;

            Assert.True(result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorGreaterThanTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = null > version;

            Assert.False(result);
        }

        [Fact]
        public void OperatorGreaterThanAllParamsIsNull()
        {
            var method = typeof(Version).GetMethod("op_GreaterThan");

            var result = (bool)method.Invoke(null, new object[] { null, null });

            Assert.False(result);
        }
        
        [Theory]
        [InlineData(true, 0, 0, 0, 0, 0, 0)]
        [InlineData(true, 4, 100, 2, 4, 100, 2)]
        [InlineData(false, 0, 0, 1, 0, 0, 0)]
        [InlineData(false, 100, 2, 5, 80, 255, 150)]
        [InlineData(false, 5, 100, 100, 4, 100, 100)]
        [InlineData(true, 4, 100, 100, 7, 1, 2)]
        [InlineData(true, 0, 0, 0, 0, 0, 1)]
        public void OperatorLessThanOrEqual(bool equal, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1);
            var version2 = new Version(major2, minor2, micro2);

            var result = version1 <= version2;

            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorLessThanOrEqualOneParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = version <= null;

            Assert.False(result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorLessThanOrEqualTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = null <= version;

            Assert.True(result);
        }

        [Fact]
        public void OperatorLessThanOrEqualAllParamsIsNull()
        {
            var method = typeof(Version).GetMethod("op_LessThanOrEqual");

            var result = (bool)method.Invoke(null, new object[] { null, null });

            Assert.True(result);
        }

        [Theory]
        [InlineData(true, 0, 0, 0, 0, 0, 0)]
        [InlineData(true, 4, 100, 2, 4, 100, 2)]
        [InlineData(true, 0, 0, 1, 0, 0, 0)]
        [InlineData(true, 100, 2, 5, 80, 255, 150)]
        [InlineData(true, 5, 100, 100, 4, 100, 100)]
        [InlineData(false, 4, 100, 100, 7, 1, 2)]
        [InlineData(false, 0, 0, 0, 0, 0, 1)]
        public void OperatorGreaterThanOrEqual(bool equal, byte major1, byte minor1, byte micro1, byte major2, byte minor2, byte micro2)
        {
            var version1 = new Version(major1, minor1, micro1);
            var version2 = new Version(major2, minor2, micro2);

            var result = version1 >= version2;

            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorGreaterThanOrEqualOneParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = version >= null;

            Assert.True(result);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(4, 100, 2)]
        [InlineData(80, 255, 150)]
        [InlineData(4, 100, 100)]
        [InlineData(7, 1, 2)]
        [InlineData(0, 0, 1)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void OperatorGreaterThanOrEqualTwoParamIsNull(byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro);

            var result = null >= version;

            Assert.False(result);
        }

        [Fact]
        public void OperatorGreaterThanOrEqualAllParamsIsNull()
        {
            var method = typeof(Version).GetMethod("op_GreaterThanOrEqual");

            var result = (bool)method.Invoke(null, new object[] { null, null });

            Assert.True(result);
        }
    }

    public class HashCode
    {
        [Fact]
        public void GetHash()
        {
            var version1 = new Version(0xFFFFFF);
            var version2 = new Version(version1.Major, version1.Minor, version1.Micro);
            var version3 = new Version(version1.Major, version1.Minor, 10);

            Assert.Equal(version1.GetHashCode(), version2.GetHashCode());
            Assert.NotEqual(version2.GetHashCode(), version3.GetHashCode());
        }
    }

    public class Stringize
    {
        [Theory]
        [InlineData("0.0.0", 0, 0, 0)]
        [InlineData("1.0.5", 1, 0, 5)]
        [InlineData("200.10.230", 200, 10, 230)]
        [InlineData("255.255.255", byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void GetString(string ver, byte major, byte minor, byte micro)
        {
            var version = new Version(major, minor, micro).ToString();
            Assert.Equal(ver, version);
        }
    }

    public class ParseFromString
    {
        [Theory]
        [InlineData("0.0", 0, 0, 0)]
        [InlineData("2.7", 2, 7, 0)]
        [InlineData("5.255", 5, 255, 0)]
        [InlineData("0.0.0", 0, 0, 0)]
        [InlineData("2.5.3", 2, 5, 3)]
        [InlineData("10.255.0", 10, 255, 0)]
        [InlineData("255.255.255", 255, 255, 255)]
        [InlineData("3  . 5. 30", 3, 5, 30)]
        [InlineData("  2  . -00. 000", 2, 0, 0)]
        public void Parse(string ver, byte major, byte minor, byte micro)
        {
            var version = Version.Parse(ver);

            Assert.Equal(major, version.Major);
            Assert.Equal(minor, version.Minor);
            Assert.Equal(micro, version.Micro);
        }

        [Fact]
        public void ParseArgumentNullException()
        {
            Assert.Throws<System.ArgumentNullException>(() => Version.Parse(null));
        }

        [Theory]
        [InlineData("0")]
        [InlineData("0.0.0.0")]
        [InlineData("1")]
        [InlineData("2.5.3.0")]
        [InlineData("2.5.3.")]
        [InlineData(".2.5.3")]
        [InlineData("2,5,3")]
        public void ParseArgumentException(string ver)
        {
            Assert.Throws<System.ArgumentException>(() => Version.Parse(ver));
        }

        [Theory]
        [InlineData("2.a.c")]
        [InlineData("2.2 55.4")]
        [InlineData("3.4,5.255")]
        public void ParseFormatException(string ver)
        {
            Assert.Throws<System.FormatException>(() => Version.Parse(ver));
        }

        [Theory]
        [InlineData("2.256.1")]
        [InlineData("-2.5.4")]
        [InlineData("2.-5.124")]
        [InlineData("2.500.270")]
        public void ParseOverflowException(string ver)
        {
            Assert.Throws<System.OverflowException>(() => Version.Parse(ver));
        }

        [Theory]
        [InlineData("0.0", 0, 0, 0)]
        [InlineData("2.7", 2, 7, 0)]
        [InlineData("5.255", 5, 255, 0)]
        [InlineData("0.0.0", 0, 0, 0)]
        [InlineData("2.5.3", 2, 5, 3)]
        [InlineData("10.255.0", 10, 255, 0)]
        [InlineData("255.255.255", 255, 255, 255)]
        [InlineData("3  . 5. 30", 3, 5, 30)]
        [InlineData("  2  . -00. 000", 2, 0, 0)]
        public void TryParseTrue(string ver, byte major, byte minor, byte micro)
        {
            var result = Version.TryParse(ver, out var version);

            Assert.True(result);
            Assert.Equal(major, version.Major);
            Assert.Equal(minor, version.Minor);
            Assert.Equal(micro, version.Micro);
        }

        [Theory]
        [InlineData(null)]
        [InlineData("0")]
        [InlineData("0.0.0.0")]
        [InlineData("1")]
        [InlineData("2.5.3.0")]
        [InlineData("2.5.3.")]
        [InlineData(".2.5.3")]
        [InlineData("2,5,3")]
        [InlineData("2.a.c")]
        [InlineData("2.2 55.4")]
        [InlineData("3.4,5.255")]
        [InlineData("2.256.1")]
        [InlineData("-2.5.4")]
        [InlineData("2.-5.124")]
        [InlineData("2.500.270")]
        public void TryParseFalse(string ver)
        {
            var result = Version.TryParse(ver, out var version);
            Assert.False(result);
        }
    }
}
