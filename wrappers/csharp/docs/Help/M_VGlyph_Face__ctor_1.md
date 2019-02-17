# Face Constructor (IntPtr)
Back to <a href="Home.md">Home page</a> 

Constructs new object <a href="T_VGlyph_Face.md">Face</a> for unmanaged handle

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
protected Face(
	IntPtr handle
)
```

**VB**<br />
``` VB
Protected Sub New ( 
	handle As IntPtr
)
```

**F#**<br />
``` F#
new : 
        handle : IntPtr -> Face
```


#### Parameters
&nbsp;<dl><dt>handle</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/5he14kz8" target="_blank">System.IntPtr</a><br />Unmanaged handle of vglyph library</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td>Invalid unmanaged handle</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Face.md">Face Class</a><br /><a href="Overload_VGlyph_Face__ctor.md">Face Overload</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />