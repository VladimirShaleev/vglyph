# Version.TryParse Method 
Back to <a href="Home.md">Home page</a> 

Try parse string to <a href="T_VGlyph_Version.md">Version</a>

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public static bool TryParse(
	string input,
	out Version result
)
```

**VB**<br />
``` VB
Public Shared Function TryParse ( 
	input As String,
	<OutAttribute> ByRef result As Version
) As Boolean
```

**F#**<br />
``` F#
static member TryParse : 
        input : string * 
        result : Version byref -> bool 

```


#### Parameters
&nbsp;<dl><dt>input</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/s1wwdcbf" target="_blank">System.String</a><br />string with version</dd><dt>result</dt><dd>Type: <a href="T_VGlyph_Version.md">VGlyph.Version</a><br />result of parse string to <a href="T_VGlyph_Version.md">Version</a></dd></dl>

#### Return Value
Type: <a href="http://msdn2.microsoft.com/en-us/library/a28wyd50" target="_blank">Boolean</a><br />Result of parse string

## See Also


#### Reference
<a href="T_VGlyph_Version.md">Version Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />