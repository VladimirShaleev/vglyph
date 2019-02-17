# Library.IsVersionCompatible Method 
Back to <a href="Home.md">Home page</a> 

Check of compatible library

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public static bool IsVersionCompatible(
	Version version
)
```

**VB**<br />
``` VB
Public Shared Function IsVersionCompatible ( 
	version As Version
) As Boolean
```

**F#**<br />
``` F#
static member IsVersionCompatible : 
        version : Version -> bool 

```


#### Parameters
&nbsp;<dl><dt>version</dt><dd>Type: <a href="T_VGlyph_Version.md">VGlyph.Version</a><br />Version of 'compile time' library</dd></dl>

#### Return Value
Type: <a href="http://msdn2.microsoft.com/en-us/library/a28wyd50" target="_blank">Boolean</a><br />Return true is runtime library is compatible

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>Argument *version* is null</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Library.md">Library Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />