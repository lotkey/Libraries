/*
 * Static SoundManager class
 * Loads, manages, and plays sounds for Unity projects
 * Created by https://github.com/lotkey/
 * Based on https://www.youtube.com/watch?v=6OT43pvUyfY (Brackey - Introduction to AUDIO in Unity)
 */
using UnityEngine;
using System.Collections.Generic;

/// <summary>
/// Static class to load, manage, and play sounds for Unity projects.
/// </summary>
public static class SoundManager
{
    // Unity TextAsset for the JSON file
    private static TextAsset jsonFile;
    // Relative path to JSON file from Assets/Resources/
    private static readonly string jsonFilePath = "Lotkey Libraries/sounds";
    // Relative path to audio files from Assets/Resources/
    private static readonly string soundsPath = "Lotkey Libraries/sounds/";

    private static List<List<Sound>> sounds;
    private static List<string> tags;
    private static GameObject soundObject = null;
    private static float globalVolume = 1.0f;

    #region Methods

    /// <summary>
    /// Loads all audio <br/>
    /// Called the first time that the SoundManager class is referenced
    /// </summary>
    static SoundManager()
    {
        if (soundObject != null) return;

        soundObject = new GameObject("SoundManager AudioSources"); // Create a GameObject to hold all AudioSources
        GameObject.DontDestroyOnLoad(soundObject); // Do not destroy the GameObject between scenes

        jsonFile = Resources.Load<TextAsset>($"{jsonFilePath}"); // Load text asset containing the JSON for the sounds
        if (!jsonFile) // if jsonFile is null then it cannot be found
        {
            Debug.LogError($"No JSON file at \"Assets/Resources/{jsonFilePath}.json\""); // Display an error message
            return;
        }

        tags = new List<string>(); // Create a list of strings for the tags
        
        sounds = new List<List<Sound>>(); // Create a 2D array of Sounds
        // First dimension is based on the tag of the audio, first entry being the "untagged" tag
        // Second dimension is the Sounds with the tag of the first dimension, order is arbitrary

        JsonRoot JsonRoot = JsonUtility.FromJson<JsonRoot>(jsonFile.text); // Load the JSON as a JsonRoot (list of JsonSounds)
        for (int i = 0; i < JsonRoot.JsonSound.Count; i++) // Loop through JsonRoot and convert from JsonSounds to Sounds
        {
            Sound s = new Sound(JsonRoot.JsonSound[i]); // Create a new Sound from the JsonSound
            if (!tags.Contains(s.tag)) // If the tag has not been added yet...
            {
                sounds.Add(new List<Sound>()); // Add a new list for the Sound with the new tag
                tags.Add(s.tag); // Add a new tag to the tag list
            }

            int tagIndex = tags.IndexOf(s.tag); // Get the index of the tag so the Sound can be added to the right list

            s.source = soundObject.AddComponent<AudioSource>(); // Add an AudioSource to the SoundManager GameObject
            s.source.playOnAwake = false; // Do not play on Awake
            s.source.clip = s.clip; // Set the AudioSource's clip to the Sound's clip
            s.source.volume = s.localVolume * globalVolume; // Set the AudioSource's volume to the global volume times the local volume
            s.source.pitch = s.pitch; // Set the AudioSource's pitch to the Sound's pitch

            sounds[tagIndex].Add(s); // Add the Sound to the list with the same tag
        }

        int untaggedIndex = tags.IndexOf("untagged");
        if (tags.Count > 1 && untaggedIndex != -1 && untaggedIndex != 0)
        {
            List<Sound> untaggedList = sounds[untaggedIndex];
            List<Sound> taggedList = sounds[0];

            sounds[untaggedIndex] = taggedList;
            sounds[0] = untaggedList;
        }
    }

    /// <summary>
    /// Plays a Sound from a specified string name
    /// </summary>
    /// <param name="name"> string name of the Sound to play </param>
    /// <returns> true if the Sound is found and played <br/>
    /// false otherwise </returns>
    public static bool Play(string name)
    {
        Sound s = FindSound(name); // Find the Sound from the list
        
        if (s == null) // If the Sound cannot be found...
        {
            Debug.LogError($"Sound \"{name}\" cannot be played because it cannot be found.");
            return false;
        }

        s.Play(); // Otherwise, play the Sound and return true
        return true;
    }

    /// <summary>
    /// Plays a Sound as a one-shot from a specified string name
    /// </summary>
    /// <param name="name"> string name of the Sound to play </param>
    /// <returns> true if the Sound is found and played <br/>
    /// false otherwise </returns>
    public static bool PlayOneShot(string name)
    {
        Sound s = FindSound(name); // Find the Sound from the list

        if (s == null) // If the Sound cannot be found...
        {
            Debug.LogError($"Sound \"{name}\" cannot be played as a oneshot because it cannot be found.");
            return false;
        }

        // Otherwise, play the Sound as a one-shot and return true
        s.PlayOneShot();
        return true;
    }

    /// <summary>
    /// Plays a Sound from a specified string name at a specified Vector3 point
    /// </summary>
    /// <param name="name"> string name of the Sound to play </param>
    /// <param name="point"> Vector3 position to play the Sound at </param>
    /// <returns> true if the Sound is found and played <br/>
    /// false otherwise </returns>
    public static bool PlayAtPoint(string name, Vector3 point)
    {
        Sound s = FindSound(name); // Find the Sound from the list

        if (s == null) // If the Sound cannot be found...
        {
            Debug.LogError($"Sound \"{name}\" cannot be played at point {point} because it cannot be found.");
            return false;
        }

        // Otherwise, play the sound at the point and return true
        s.PlayAtPoint(point);
        return true;
    }

    /// <summary>
    /// Plays a random Sound from a specified string tag
    /// </summary>
    /// <param name="tag"> string name of tag </param>
    /// <returns> true if there is a playable sound with the provided tag and if it is played <br/>
    /// false otherwise </returns>
    public static bool PlayRandomSoundWithTag(string tag)
    {
        int tagIndex = tags.IndexOf(tag); // Get the index of the provided tag

        if (tagIndex == -1) // If the tag is not added...
        {
            Debug.LogError($"There is no tag \"{tag}.\"");
            return false;
        }
        if (sounds[tagIndex].Count == 0) // If there are no Sounds tagged with the tag...
        {
            Debug.LogError($"There are no sounds tagged with \"{tag}.\"");
            return false;
        }

        int randomIndex = Random.Range(0, sounds[tagIndex].Count); // Otherwise, generate a random index
        sounds[tagIndex][randomIndex].Play(); // Play the Sound at the random index
        return true;
    }

    /// <summary>
    /// Plays a random Sound as a one-shot from a specified string tag
    /// </summary>
    /// <param name="tag"> string name of tag </param>
    /// <returns> true if there is a playable sound with the provided tag and if it is played <br/>
    /// false otherwise </returns>
    public static bool PlayRandomOneShotWithTag(string tag)
    {
        int tagIndex = tags.IndexOf(tag); // Get the index of the provided tag

        if (tagIndex == -1) // If the tag is not added...
        {
            Debug.LogError($"There is no tag \"{tag}.\"");
            return false;
        }
        if (sounds[tagIndex].Count == 0) // If there are no Sounds tagged with the tag...
        {
            Debug.LogError($"There are no sounds tagged with \"{tag}.\"");
            return false;
        }

        int randomIndex = Random.Range(0, sounds[tagIndex].Count); // Otherwise, generate a random index
        sounds[tagIndex][randomIndex].PlayOneShot(); // Play the Sound at the random index
        return true;
    }

    /// <summary>
    /// Plays a random Sound from a specified string tag at a provided Vector3 point
    /// </summary>
    /// <param name="tag"> string name of tag </param>
    /// <param name="point"> Vector3 location to play the Sound at </param>
    /// <returns> true if there is a playable sound with the provided tag and if it is played <br/>
    /// false otherwise </returns>
    public static bool PlayRandomSoundWithTagAtPoint(string tag, Vector3 point)
    {
        int tagIndex = tags.IndexOf(tag);  // Get the index of the provided tag

        if (tagIndex == -1) // If the tag is not added...
        {
            Debug.LogError($"There is no tag \"{tag}.\"");
            return false;
        }
        if (sounds[tagIndex].Count == 0) // If there are no Sounds tagged with the tag...
        {
            Debug.LogError($"There are no sounds tagged with \"{tag}.\"");
            return false;
        }

        int randomIndex = Random.Range(0, sounds[tagIndex].Count);  // Otherwise, generate a random index
        sounds[tagIndex][randomIndex].PlayAtPoint(point);  // Play the Sound at the random index
        return true;
    }

    /// <summary>
    /// Sets the global volume <br/>
    /// All Sounds's volumes will be scaled based on global volume and their own local volumes set in the JSON file
    /// </summary>
    /// <param name="volume"> 
    /// Linearly scaled float in [0.0 - 1.0] <br/> 
    /// 0.0 is muted, 1.0 is full global volume, 0.5 is half global volume, etc. <br/>
    /// Will be converted to a logarithmic scale
    /// </param>
    public static void SetGlobalVolume(float volume)
    {
        globalVolume = volume; // Store the global volume
        for (int i = 0; i < sounds.Count; i++) // Loop through all tags...
        {
            for (int j = 0; j < sounds[i].Count; j++) // Loop through all Sounds...
            {
                float linearVolume = sounds[i][j].localVolume * globalVolume; // Multiply volumes together to scale
                sounds[i][j].source.volume = LinearToLog(linearVolume); // Convert linear volume to logarithmic scale
            }
        }
    }

    /// <summary>
    /// Private method <br/>
    /// Finds a Sound from a specified string name
    /// </summary>
    /// <param name="name"> string name of Sound to find </param>
    /// <returns> a Sound in the sounds List with the specified name if found <br/>
    /// null otherwise </returns>
    private static Sound FindSound(string name)
    {
        for (int i = 0; i < sounds.Count; i++) // Loop through all tags...
        {
            Sound s = sounds[i].Find(sound => sound.name == name); // Search the tagged list for the Sound
            if (s != null) return s; // If found, return it
        }
        return null; // Not found, return null
    }

    /// <summary>
    /// Takes a linear float and converts to logarithmic scale
    /// </summary>
    /// <param name="linear"> Linearly scaled float in [0.0 - 1.0] </param>
    /// <returns> Logarithmically scaled float in [0.0 - 1.0] </returns>
    private static float LinearToLog(float linear)
    {
        linear = (linear <= 0) ? float.Epsilon : (linear >= 1) ? 1 : linear; // Ensure float is in [float.Epsilon, 1.0]
        return Mathf.Abs(Mathf.Log10(1 - linear)); // Return logarithmically scaled float
    }

    #endregion

    #region Helper Classes

    /// <summary>
    /// Private helper class <br/>
    /// Stores all necessary information to play and find Sounds <br/>
    /// Has all necessary methods to play Sounds
    /// </summary>
    private class Sound
    {
        // Fields for loading/managing Sounds
        public AudioClip clip;
        public AudioSource source;
        public string name;
        public string tag = "untagged";
        public string path;

        // Fields for controlling parameters
        public float localVolume = 1f;
        public float pitch = 1f;
        public bool randomizePitch = false;
        public float randomPitchRange = 0f;

        /// <summary>
        /// Constructs a Sound object
        /// </summary>
        /// <param name="jsound"> JsonSound object to construct a Sound from </param>
        public Sound(JsonSound jsound)
        {
            // Copy all fields from the JsonSound
            name = jsound.Name;
            path = jsound.Path;
            if (jsound.Tag != null) tag = jsound.Tag;
            else tag = "untagged";
            localVolume = jsound.Volume;
            pitch = jsound.Pitch;
            randomizePitch = jsound.RandomizePitch;
            randomPitchRange = jsound.RandomPitchRange;

            clip = Resources.Load<AudioClip>($"{soundsPath}{path}"); // Load the clip from the path
        }

        /// <summary>
        /// Tests for equality based on string names
        /// </summary>
        /// <param name="s"> Sound to test equality with </param>
        /// <returns> true if equal string names <br/>
        /// false otherwise <br/> </returns>
        public bool Equals(Sound s)
        {
            return this.name == s.name;
        }

        /// <summary>
        /// Plays the Sound
        /// </summary>
        public void Play()
        {
            Randomize(); // Randomize fields
            source.Play(); // Play the AudioSource
        }

        /// <summary>
        /// Plays the Sound as a one-shot
        /// </summary>
        public void PlayOneShot()
        {
            Randomize(); // Randomize fields
            source.PlayOneShot(clip); // Play the AudioSource
        }

        /// <summary>
        /// Plays the Sound at a Vector3 point
        /// </summary>
        /// <param name="point"> Vector3 position to play the Sound at </param>
        public void PlayAtPoint(Vector3 point)
        {
            Randomize(); // Randomize fields
            AudioSource.PlayClipAtPoint(clip, point); // Play AudioClip at point
        }

        /// <summary>
        /// Randomizes pitch
        /// </summary>
        private void Randomize()
        {
            if (!randomizePitch) return; // Do not randomize
            float max = randomPitchRange / 2f; // Maximum pitch increase allowed
            float min = -randomPitchRange / 2f; // Maximum pitch decrease allowed
            source.pitch = pitch + Random.Range(min, max); // Sets the AudioSource's pitch to the random pitch
        }
    }

    /// <summary>
    /// Private helper class <br/>
    /// Necessary for converting from JSON text to a Sound
    /// </summary>
    [System.Serializable]
    private class JsonSound
    {
        // Fields to be loaded from JSON
        public string Name;
        public string Path;
        public string Tag;
        public float Volume;
        public float Pitch;
        public bool RandomizePitch;
        public float RandomPitchRange;
    }

    /// <summary>
    /// Private helper class <br/>
    /// Necessary for converting from JSON text to a List of Sounds
    /// </summary>
    [System.Serializable]
    private class JsonRoot
    {
        public List<JsonSound> JsonSound = new List<JsonSound>(); // List of JsonSounds to be loaded
    }

    #endregion
}