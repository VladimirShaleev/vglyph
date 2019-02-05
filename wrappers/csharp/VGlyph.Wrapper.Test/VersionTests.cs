using Xunit;

namespace VGlyph.Wrapper.Tests
{
    public class VersionTests
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
        }
    }
}
