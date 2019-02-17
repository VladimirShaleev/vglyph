# Face.AddGlyph Method (Glyph, Int32)
Back to <a href="Home.md">Home page</a> 

Add <a href="T_VGlyph_Glyph.md">Glyph</a> to <a href="T_VGlyph_Face.md">Face</a>

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void AddGlyph(
	Glyph glyph,
	int charCode
)
```

**VB**<br />
``` VB
Public Sub AddGlyph ( 
	glyph As Glyph,
	charCode As Integer
)
```

**F#**<br />
``` F#
member AddGlyph : 
        glyph : Glyph * 
        charCode : int -> unit 

```


#### Parameters
&nbsp;<dl><dt>glyph</dt><dd>Type: <a href="T_VGlyph_Glyph.md">VGlyph.Glyph</a><br /><a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>charCode</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />char code</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>glyph is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td>glyph is invalid</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Face.md">Face Class</a><br /><a href="Overload_VGlyph_Face_AddGlyph.md">AddGlyph Overload</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />