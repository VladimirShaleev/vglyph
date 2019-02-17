# Version.Parse Method 
Back to <a href="Home.md">Home page</a> 

Parse string to <a href="T_VGlyph_Version.md">Version</a>

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public static Version Parse(
	string input
)
```

**VB**<br />
``` VB
Public Shared Function Parse ( 
	input As String
) As Version
```

**F#**<br />
``` F#
static member Parse : 
        input : string -> Version 

```


#### Parameters
&nbsp;<dl><dt>input</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/s1wwdcbf" target="_blank">System.String</a><br />string with version</dd></dl>

#### Return Value
Type: <a href="T_VGlyph_Version.md">Version</a><br />Result of parse string

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>Argument *input* is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td>Argument *input* has an incorrect format</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/b5s9cs7s" target="_blank">FormatException</a></td><td>Argument *input* has an incorrect format of component</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/41ktf3wy" target="_blank">OverflowException</a></td><td>Component of argument *input* out of range 0-255</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Version.md">Version Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />