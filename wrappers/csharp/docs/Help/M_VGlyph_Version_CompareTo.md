# Version.CompareTo Method (Object)
Back to <a href="Home.md">Home page</a> 

Compare versions

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public int CompareTo(
	Object version
)
```

**VB**<br />
``` VB
Public Function CompareTo ( 
	version As Object
) As Integer
```

**F#**<br />
``` F#
abstract CompareTo : 
        version : Object -> int 
override CompareTo : 
        version : Object -> int 
```


#### Parameters
&nbsp;<dl><dt>version</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">System.Object</a><br />Compare version</dd></dl>

#### Return Value
Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">Int32</a><br />Compare result

#### Implements
<a href="http://msdn2.microsoft.com/en-us/library/4ah99705" target="_blank">IComparable.CompareTo(Object)</a><br />

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td>Argument *version* is not a <a href="T_VGlyph_Version.md">Version</a></td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Version.md">Version Class</a><br /><a href="Overload_VGlyph_Version_CompareTo.md">CompareTo Overload</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />