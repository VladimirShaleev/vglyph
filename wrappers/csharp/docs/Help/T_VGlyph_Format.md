# Format Class
Back to <a href="Home.md">Home page</a> 

Format of <a href="T_VGlyph_Surface.md">Surface</a>


## Inheritance Hierarchy
<a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">System.Object</a><br />&nbsp;&nbsp;VGlyph.Format<br />&nbsp;&nbsp;&nbsp;&nbsp;<a href="T_VGlyph_RgbaUintFormat.md">VGlyph.RgbaUintFormat</a><br />
**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public abstract class Format : IDisposable
```

**VB**<br />
``` VB
Public MustInherit Class Format
	Implements IDisposable
```

**F#**<br />
``` F#
[<AbstractClassAttribute>]
type Format =  
    class
        interface IDisposable
    end
```

The Format type exposes the following members.


## Constructors
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Format__ctor.md">Format</a></td><td>
Constructs new object Format for unmanaged handle</td></tr></table>&nbsp;
<a href="#format-class">Back to Top</a>

## Properties
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Format_BitsPerPixel.md">BitsPerPixel</a></td><td>
Get bits per pixel</td></tr><tr><td>![Protected property](media/protproperty.gif "Protected property")</td><td><a href="P_VGlyph_Format_Handle.md">Handle</a></td><td>
Unmanaged handle of vglyph library</td></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Format_PackagingBytes.md">PackagingBytes</a></td><td>
Get packaging bytes</td></tr></table>&nbsp;
<a href="#format-class">Back to Top</a>

## Methods
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public method](media/pubmethod.gif "Public method")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Format_Create.md">Create</a></td><td>
Create Format</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Format_Dispose.md">Dispose()</a></td><td>
Dispose object</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Format_Dispose_1.md">Dispose(Boolean)</a></td><td>
Dispose object</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/bsc2ak47" target="_blank">Equals</a></td><td>
Determines whether the specified object is equal to the current object.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Format_Finalize.md">Finalize</a></td><td>
Free resources and perform other cleanup operations
 (Overrides <a href="http://msdn2.microsoft.com/en-us/library/4k87zsw7" target="_blank">Object.Finalize()</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/zdee4b3y" target="_blank">GetHashCode</a></td><td>
Serves as the default hash function.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/dfwy45w9" target="_blank">GetType</a></td><td>
Gets the <a href="http://msdn2.microsoft.com/en-us/library/42892f65" target="_blank">Type</a> of the current instance.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/57ctke0a" target="_blank">MemberwiseClone</a></td><td>
Creates a shallow copy of the current <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/7bxwbwt2" target="_blank">ToString</a></td><td>
Returns a string that represents the current object.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr></table>&nbsp;
<a href="#format-class">Back to Top</a>

## Fields
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_A1R5G5B5Uint.md">A1R5G5B5Uint</a></td><td>
Format A1R5G5B5_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_A2B10G10R10Uint.md">A2B10G10R10Uint</a></td><td>
Format A2B10G10R10_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_A2R10G10B10Uint.md">A2R10G10B10Uint</a></td><td>
Format A2R10G10B10_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_A4R4G4B4Uint.md">A4R4G4B4Uint</a></td><td>
Format A4R4G4B4_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_A8B8G8R8Uint.md">A8B8G8R8Uint</a></td><td>
Format A8B8G8R8_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_A8R8G8B8Uint.md">A8R8G8B8Uint</a></td><td>
Format A8R8G8B8_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_B4G4R4A4Uint.md">B4G4R4A4Uint</a></td><td>
Format B4G4R4A4_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_B5G5R5A1Uint.md">B5G5R5A1Uint</a></td><td>
Format B5G5R5A1_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_B5G6R5Uint.md">B5G6R5Uint</a></td><td>
Format B5G6R5_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_B8G8R8A8Uint.md">B8G8R8A8Uint</a></td><td>
Format B8G8R8A8_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_B8G8R8Uint.md">B8G8R8Uint</a></td><td>
Format B8G8R8_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R16Float.md">R16Float</a></td><td>
Format R16_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R16G16B16A16Float.md">R16G16B16A16Float</a></td><td>
Format R16G16B16A16_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R16G16B16A16Uint.md">R16G16B16A16Uint</a></td><td>
Format R16G16B16A16_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R16G16B16Float.md">R16G16B16Float</a></td><td>
Format R16G16B16_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R16G16B16Uint.md">R16G16B16Uint</a></td><td>
Format R16G16B16_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R16G16Float.md">R16G16Float</a></td><td>
Format R16G16_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R16G16Uint.md">R16G16Uint</a></td><td>
Format R16G16_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R16Uint.md">R16Uint</a></td><td>
Format R16_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R32Float.md">R32Float</a></td><td>
Format R32_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R32G32B32A32Float.md">R32G32B32A32Float</a></td><td>
Format R32G32B32A32_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R32G32B32A32Uint.md">R32G32B32A32Uint</a></td><td>
Format R32G32B32A32_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R32G32B32Float.md">R32G32B32Float</a></td><td>
Format R32G32B32_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R32G32B32Uint.md">R32G32B32Uint</a></td><td>
Format R32G32B32_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R32G32Float.md">R32G32Float</a></td><td>
Format R32G32_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R32G32Uint.md">R32G32Uint</a></td><td>
Format R32G32_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R32Uint.md">R32Uint</a></td><td>
Format R32_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R4G4B4A4Uint.md">R4G4B4A4Uint</a></td><td>
Format R4G4B4A4_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R4G4Uint.md">R4G4Uint</a></td><td>
Format R4G4_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R5G5B5A1Uint.md">R5G5B5A1Uint</a></td><td>
Format R5G5B5A1_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R5G6B5Uint.md">R5G6B5Uint</a></td><td>
Format R5G6B5_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R64Float.md">R64Float</a></td><td>
Format R64_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R64G64B64A64Float.md">R64G64B64A64Float</a></td><td>
Format R64G64B64A64_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R64G64B64A64Uint.md">R64G64B64A64Uint</a></td><td>
Format R64G64B64A64_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R64G64B64Float.md">R64G64B64Float</a></td><td>
Format R64G64B64_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R64G64B64Uint.md">R64G64B64Uint</a></td><td>
Format R64G64B64_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R64G64Float.md">R64G64Float</a></td><td>
Format R64G64_FLOAT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R64G64Uint.md">R64G64Uint</a></td><td>
Format R64G64_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R64Uint.md">R64Uint</a></td><td>
Format R64_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R8G8B8A8Uint.md">R8G8B8A8Uint</a></td><td>
Format R8G8B8A8_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R8G8B8Uint.md">R8G8B8Uint</a></td><td>
Format R8G8B8_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R8G8Uint.md">R8G8Uint</a></td><td>
Format R8G8_UINT</td></tr><tr><td>![Public field](media/pubfield.gif "Public field")![Static member](media/static.gif "Static member")</td><td><a href="F_VGlyph_Format_R8Uint.md">R8Uint</a></td><td>
Format R8_UINT</td></tr></table>&nbsp;
<a href="#format-class">Back to Top</a>

## See Also


#### Reference
<a href="N_VGlyph.md">VGlyph Namespace</a><br />