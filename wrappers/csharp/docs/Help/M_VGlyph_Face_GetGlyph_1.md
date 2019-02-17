# Face.GetGlyph Method (UInt32)
Back to <a href="Home.md">Home page</a> 

Get <a href="T_VGlyph_Glyph.md">Glyph</a> on char code

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public Glyph GetGlyph(
	uint charCode
)
```

**VB**<br />
``` VB
Public Function GetGlyph ( 
	charCode As UInteger
) As Glyph
```

**F#**<br />
``` F#
member GetGlyph : 
        charCode : uint32 -> Glyph 

```


#### Parameters
&nbsp;<dl><dt>charCode</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/ctys3981" target="_blank">System.UInt32</a><br />char code</dd></dl>

#### Return Value
Type: <a href="T_VGlyph_Glyph.md">Glyph</a><br />Get <a href="T_VGlyph_Glyph.md">Glyph</a>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/9a35cy81" target="_blank">KeyNotFoundException</a></td><td>char code not found</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Face.md">Face Class</a><br /><a href="Overload_VGlyph_Face_GetGlyph.md">GetGlyph Overload</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />