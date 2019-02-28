# Format.Create Method 
Back to <a href="Home.md">Home page</a> 

Create <a href="T_VGlyph_Format.md">Format</a>

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public static Format Create(
	string format,
	Endianness endianness
)
```

**VB**<br />
``` VB
Public Shared Function Create ( 
	format As String,
	endianness As Endianness
) As Format
```

**F#**<br />
``` F#
static member Create : 
        format : string * 
        endianness : Endianness -> Format 

```


#### Parameters
&nbsp;<dl><dt>format</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/s1wwdcbf" target="_blank">System.String</a><br />Format</dd><dt>endianness</dt><dd>Type: <a href="T_VGlyph_Endianness.md">VGlyph.Endianness</a><br />Byte order</dd></dl>

#### Return Value
Type: <a href="T_VGlyph_Format.md">Format</a><br />Return <a href="T_VGlyph_Format.md">Format</a>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td>Format string is empty of param *format*</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/b5s9cs7s" target="_blank">FormatException</a></td><td>Invalid format of param *format*</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Format.md">Format Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />