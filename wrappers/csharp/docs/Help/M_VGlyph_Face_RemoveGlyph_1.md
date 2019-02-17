# Face.RemoveGlyph Method (UInt32)
Back to <a href="Home.md">Home page</a> 

Remove <a href="T_VGlyph_Glyph.md">Glyph</a> from <a href="T_VGlyph_Face.md">Face</a>

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public bool RemoveGlyph(
	uint charCode
)
```

**VB**<br />
``` VB
Public Function RemoveGlyph ( 
	charCode As UInteger
) As Boolean
```

**F#**<br />
``` F#
member RemoveGlyph : 
        charCode : uint32 -> bool 

```


#### Parameters
&nbsp;<dl><dt>charCode</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/ctys3981" target="_blank">System.UInt32</a><br />char code</dd></dl>

#### Return Value
Type: <a href="http://msdn2.microsoft.com/en-us/library/a28wyd50" target="_blank">Boolean</a><br />Return true is remove <a href="T_VGlyph_Glyph.md">Glyph</a> from face. And false if glyph not found

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Face.md">Face Class</a><br /><a href="Overload_VGlyph_Face_RemoveGlyph.md">RemoveGlyph Overload</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />