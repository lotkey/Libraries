# Using *sounds.json*

## Overview

*sounds.json* contains information in JSON (JavaScript Object Notation) about each sound to be loaded. This makes it easy to automate loading audio. Say goodbye to clicking and dragging game objects in the Unity editor. Just add your sound files to *./Sounds/* and add the necessary changes to *sounds.json* detailed below.

## Structure

*sounds.json* contains a single object: a *JsonRoot* object. You only need to know that the *JsonRoot* object contains a single field: a field called *JsonSound* that is a list of *JsonSound* objects which will be used to construct a list of usable *Sound* objects. 

The opening and closing curly brackets enclose the *JsonRoot* object. 

```
{
    ...
}
```

The "JsonSound" tag denotes the variable called "JsonSound", which contains a list of *JsonSound* objects enclosed by the square brackets. 

```
{
    "JsonSound": [
        ...
    ]
}
```

Each set of curly brackets in the square brackets enclose a *JsonSound* object. Commas separate each *JsonSound* object.

```
{
  "JsonSound": [
    {
        ...
    },
    {
        ...
    }
  ]
}
```

Each *JsonSound* object contains fields for loading, managing, and playing audio. This is where the user will add their own entries.

Each field is enclosed in quotation marks and followed by a colon and a value. String values are enclosed in quotation marks. Floating point numbers (decimals) are not, but they must have a digit before the decimal point (*.1* is not valid, but *0.1* is). Boolean values are either *true* or *false* with no capitalization. Each field is separated by commas.

```
{
  "JsonSound": [
    {
        "Name": "example name 1",
        "Path": "example1",
        "Volume": 1.0,
        "Pitch": 1.0,
        "RandomizePitch": true,
        "RandomPitchRange": 0.1
    },
    {
        "Name": "example name 2",
        "Path": "example2",
        "Volume": 1.0,
        "Pitch": 1.0,
        "RandomizePitch": false
    }
  ]
}
```

## Fields

### Required Fields
These fields must be filled out.

"Name"
 - String name to store the audio as
 - This will be the name used to play the audio in Unity
 - Does not have to be the name of the audio file

"Path"
 - String path of audio file relative to ./Sounds/
 - Includes filename, does not include file extension

### Optional Fields
These fields have defaults. They can be filled out to override the default values but they are not required.

"Tag"
 - String value
 - Default value is *"untagged"*
 - Can be used to randomly play a sound from a tag (useful for impact sounds such as footsteps, for example)

"Volume"
 - Floating point number in *[0.0, 1.0]*
 - Default value is *1.0*
 - Controls volume of the single audio entry
    - Volume of all entries can be controlled through the SoundManager class in code
 - Linearly scaled volume 
    - *0.0* is muted
    - *1.0* is full volume
    - *0.5* is half volume

"Pitch"
 - Floating point number
 - Default value is *0.0*
 - Controls pitch of the single audio entry based on semitones
   - *1.0* shifts the pitch up 1 semitone
   - *-1.0* shifts the pitch down 1 semitone
   - *0.5* shifts the pitch up half a semitone

"RandomizePitch"
 - Boolean value
 - Default value is *false*
 - Controls whether or not the pitch is randomized when played
 - Can be used to add variety to sounds (similar to sounds in Minecraft like hitting blocks, footsteps, animal noises, etc.)

"RandomPitchRange"
 - Positive floating point number
 - Default value is *0.0*
 - Controls how much the pitch is randomized from the base pitch (in semitones)
 - Random pitch is selected from *["Pitch" - "RandomPitchRange", "Pitch" + "RandomPitchRange"]*

 ## Adding an Entry

 To add an entry, add a set of curly brackets in the square brackets. In between the curly brackets, fill in the "Name" and "Path" arguments (as well as any optional arguments). Make sure each entry is separated by commas.

 Before adding an entry:

 ```
{
  "JsonSound": [
    {
        "Name": "example name 1",
        "Path": "example1",
        "Volume": 1.0,
        "Pitch": 1.0,
        "RandomizePitch": true,
        "RandomPitchRange": 0.1
    }
  ]
}
```

After adding an entry:

```
{
  "JsonSound": [
    {
        "Name": "example name 1",
        "Path": "example1",
        "Volume": 1.0,
        "Pitch": 1.0,
        "RandomizePitch": true,
        "RandomPitchRange": 0.1
    },
    {
        "Name": "example name 2",
        "Path": "example2",
        "Volume": 1.0,
        "Pitch": 1.0,
        "RandomizePitch": false
    }
  ]
}
```
